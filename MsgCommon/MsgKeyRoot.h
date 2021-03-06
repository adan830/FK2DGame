/**
*	created:		2012-6-29   14:47
*	filename: 		MsgKeyRoot
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		根消息码定义
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
/*  消息码定义结构
 *		根消息码
 *		主消息码
 *		子消息码
 */
//------------------------------------------------------------------------
// 登录态消息码
#define CMD_ROOT_LOGIN			0x0001

// 选择人物态消息码
#define CMD_ROOT_SELECTACTOR	0x0002

// 聊天消息管理消息码
//（只有当服务器转到运行态，也就是说选定人物后，服务器方会处理）
#define CMD_ROOT_CHAT			0x0003

// 管理员专用消息码
//（只有当服务器转到运行态，也就是说选定人物后，服务器方会处理）
#define CMD_ROOT_MANAGER		0x0004

// 逻辑对象专用消息码
//（只有当服务器转到运行态，也就是说选定人物后，服务器方会处理）
#define CMD_ROOT_THING			0x0005

// 切换地图专用消息码
//（只有当服务器转到运行态，也就是说选定人物后，服务器方会处理）
#define CMD_ROOT_SWITCH			0x0006

// 错误报警专用消息码
#define CMD_ROOT_ERROR			0x0007

// 好友消息管理消息码
//（只有当服务器转到运行态，也就是说选定人物后，服务器方会处理）
#define CMD_ROOT_FRIEND			0x0008

// 组队专用消息码
//（只有当服务器转到运行态，也就是说选定人物后，服务器方会处理）
#define CMD_ROOT_TEAM			0x0009

// 氏族专用消息码
//（只有当服务器转到运行态，也就是说选定人物后，服务器方会处理）
#define CMD_ROOT_CLAN           0x000A

// 城战专用消息码
//（只有当服务器转到运行态，也就是说选定人物后，服务器方会处理）
#define CM_ROOT_SIEGE			0x000B

// 最大ROOT消息码
#define CMD_ROOT_MAX			0x0010
//------------------------------------------------------------------------