/**
*	created:		2012-2-29   4:43
*	filename: 		FKBigInt
*	author:			FreeKnight
*	Copyright (C): 	TianCong (2012) FreeKnightServerEngine
*	purpose:		
*/
//------------------------------------------------------------------------
#include "FKBigInt.h"
//------------------------------------------------------------------------
//构造大数对象并初始化为零  
CBigInt::CBigInt()  
{  
	m_nLength=1;  
	for(int i=0;i <BI_MAXLEN;i++)m_ulValue[i]=0;  
}  
//------------------------------------------------------------------------
//大数比较  
int CBigInt::Cmp(CBigInt& A)  
{  
	if(m_nLength>A.m_nLength)return 1;  
	if(m_nLength <A.m_nLength)return -1;  
	for(int i=m_nLength-1;i>=0;i--)  
	{  
		if(m_ulValue[i]>A.m_ulValue[i])return 1;  
		if(m_ulValue[i] <A.m_ulValue[i])return -1;  
	}  
	return 0;  
}  
//------------------------------------------------------------------------
//大数赋值  
void CBigInt::Mov(CBigInt& A)  
{  
	m_nLength=A.m_nLength;  
	for(int i=0;i <BI_MAXLEN;i++)  
		m_ulValue[i]=A.m_ulValue[i];  
}  
void CBigInt::Mov(unsigned __int64 A)  
{  
	if(A>0xffffffff)  
	{  
		m_nLength=2;  
		m_ulValue[1]=(unsigned long)(A>>32);  
		m_ulValue[0]=(unsigned long)A;  
	}  
	else  
	{  
		m_nLength=1;  
		m_ulValue[0]=(unsigned long)A;  
	}  
	for(int i=m_nLength;i <BI_MAXLEN;i++)m_ulValue[i]=0;  
}  
//------------------------------------------------------------------------
//大数相减  
CBigInt CBigInt::Sub(CBigInt& A)  
{  
	CBigInt X;  
	X.Mov(*this);  
	if(X.Cmp(A) <=0){X.Mov(0);return X;}  
	unsigned carry=0;  
	unsigned __int64 num;  
	unsigned i;  
	for(i=0;i <m_nLength;i++)  
	{  
		if((m_ulValue[i]>A.m_ulValue[i])||((m_ulValue[i]==A.m_ulValue[i])&&(carry==0)))  
		{  
			X.m_ulValue[i]=m_ulValue[i]-carry-A.m_ulValue[i];  
			carry=0;  
		}  
		else  
		{  
			num=0x100000000+m_ulValue[i];  
			X.m_ulValue[i]=(unsigned long)(num-carry-A.m_ulValue[i]);  
			carry=1;  
		}  
	}  
	while(X.m_ulValue[X.m_nLength-1]==0)X.m_nLength--;  
	return X;  
}  
//------------------------------------------------------------------------
CBigInt CBigInt::Sub(unsigned long A)  
{  
	CBigInt X;  
	X.Mov(*this);  
	if(X.m_ulValue[0]>=A){X.m_ulValue[0]-=A;return X;}  
	if(X.m_nLength==1){X.Mov(0);return X;}  
	unsigned __int64 num=0x100000000+X.m_ulValue[0];  
	X.m_ulValue[0]=(unsigned long)(num-A);  
	int i=1;  
	while(X.m_ulValue[i]==0){X.m_ulValue[i]=0xffffffff;i++;}  
	X.m_ulValue[i]--;  
	if(X.m_ulValue[i]==0)X.m_nLength--;  
	return X;  
}  
//------------------------------------------------------------------------
//大数相乘  
CBigInt CBigInt::Mul(CBigInt& A)  
{  
	if(A.m_nLength==1)return Mul(A.m_ulValue[0]);  
	CBigInt X;  
	unsigned __int64 sum,mul=0,carry=0;  
	unsigned i,j;  
	X.m_nLength=m_nLength+A.m_nLength-1;  
	for(i=0;i <X.m_nLength;i++)  
	{  
		sum=carry;  
		carry=0;  
		for(j=0;j <A.m_nLength;j++)  
		{  
			if(((i-j)>=0)&&((i-j) <m_nLength))  
			{  
				mul=m_ulValue[i-j];  
				mul*=A.m_ulValue[j];  
				carry+=mul>>32;  
				mul=mul&0xffffffff;  
				sum+=mul;  
			}  
		}  
		carry+=sum>>32;  
		X.m_ulValue[i]=(unsigned long)sum;  
	}  
	if(carry){X.m_nLength++;X.m_ulValue[X.m_nLength-1]=(unsigned long)carry;}  
	return X;  
}  
//------------------------------------------------------------------------
CBigInt CBigInt::Mul(unsigned long A)  
{  
	CBigInt X;  
	unsigned __int64 mul;  
	unsigned long carry=0;  
	X.Mov(*this);  
	for(unsigned i=0;i <m_nLength;i++)  
	{  
		mul=m_ulValue[i];  
		mul=mul*A+carry;  
		X.m_ulValue[i]=(unsigned long)mul;  
		carry=(unsigned long)(mul>>32);  
	}  
	if(carry){X.m_nLength++;X.m_ulValue[X.m_nLength-1]=carry;}  
	return X;  
}  
//------------------------------------------------------------------------
//大数相除  
CBigInt CBigInt::Div(unsigned long A)  
{  
	CBigInt X;  
	X.Mov(*this);  
	if(X.m_nLength==1){X.m_ulValue[0]=X.m_ulValue[0]/A;return X;}  
	unsigned __int64 div,mul;  
	unsigned long carry=0;  
	for(int i=X.m_nLength-1;i>=0;i--)  
	{  
		div=carry;  
		div=(div << 32)+X.m_ulValue[i];  
		X.m_ulValue[i]=(unsigned long)(div/A);  
		mul=(div/A)*A;  
		carry=(unsigned long)(div-mul);  
	}  
	if(X.m_ulValue[X.m_nLength-1]==0)X.m_nLength--;  
	return X;  
}  
//------------------------------------------------------------------------
//大数求模  
CBigInt CBigInt::Mod(CBigInt& A)  
{  
	if(A.m_nLength==1)  
	{  
		CBigInt X;  
		X.m_ulValue[0]=Mod(A.m_ulValue[0]);  
		return X;  
	}  
	CBigInt X,Y;  
	int len;  
	unsigned __int64 num,div;  
	unsigned long carry=0;  
	X.Mov(*this);  
	while(X.Cmp(A)>0)  
	{   
		if(X.m_ulValue[X.m_nLength-1]>A.m_ulValue[A.m_nLength-1])  
		{  
			len=X.m_nLength-A.m_nLength;  
			div=X.m_ulValue[X.m_nLength-1]/(A.m_ulValue[A.m_nLength-1]+1);  
		}  
		else if(X.m_nLength>A.m_nLength)  
		{  
			len=X.m_nLength-A.m_nLength-1;  
			num=X.m_ulValue[X.m_nLength-1];  
			num=(num << 32)+X.m_ulValue[X.m_nLength-2];  
			if(A.m_ulValue[A.m_nLength-1]==0xffffffff)div=(num>>32);  
			else div=num/(A.m_ulValue[A.m_nLength-1]+1);  
		}  
		else  
		{  
			X.Mov(X.Sub(A));  
			break;  
		}  
		Y.Mov(div);  
		Y.Mov(Y.Mul(A));  
		Y.m_nLength+=len;  
		for(int i=Y.m_nLength-1;i>=len;i--)
		{
			Y.m_ulValue[i]=Y.m_ulValue[i-len];
		}
		for(int i=0;i <len;i++)
		{
			Y.m_ulValue[i]=0;
		}
		X.Mov(X.Sub(Y));  
	}  
	if(X.Cmp(A)==0)X.Mov(0);  
	return X;  
}  
//------------------------------------------------------------------------
unsigned long CBigInt::Mod(unsigned long A)  
{  
	if(m_nLength==1)return(m_ulValue[0]%A);  
	unsigned __int64 div;  
	unsigned long carry=0;  
	for(int i=m_nLength-1;i>=0;i--)  
	{  
		div=carry*0x100000000+m_ulValue[i];  
		carry=(unsigned long)(div-((div/A)*A));  
	}  
	return carry;  
}  
//------------------------------------------------------------------------
//蒙哥马利算法求模幂  
CBigInt CBigInt::ModExp(CBigInt& A, CBigInt& B)  
{  
	CBigInt X,Y,Z;  
	X.Mov(1);  
	Y.Mov(*this);  
	Z.Mov(A);  
	while((Z.m_nLength!=1) || Z.m_ulValue[0])  
	{  
		if(Z.m_ulValue[0]&1)  
		{  
			Z.Mov(Z.Sub(1));  
			X.Mov(X.Mul(Y));  
			X.Mov(X.Mod(B));  
		}  
		else  
		{  
			Z.Mov(Z.Div(2));  
			Y.Mov(Y.Mul(Y));  
			Y.Mov(Y.Mod(B));  
		}  
	}  
	return X;  
}  
//------------------------------------------------------------------------