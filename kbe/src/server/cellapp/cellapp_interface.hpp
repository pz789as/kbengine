/*
This source file is part of KBEngine
For the latest info, see http://www.kbengine.org/

Copyright (c) 2008-2012 KBEngine.

KBEngine is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

KBEngine is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.
 
You should have received a copy of the GNU Lesser General Public License
along with KBEngine.  If not, see <http://www.gnu.org/licenses/>.
*/

#if defined(DEFINE_IN_INTERFACE)
	#undef __CELLAPP_INTERFACE_H__
#endif


#ifndef __CELLAPP_INTERFACE_H__
#define __CELLAPP_INTERFACE_H__

// common include	
#if defined(CELLAPP)
#include "entity.hpp"
#include "cellapp.hpp"
#endif
#include "cellapp_interface_macros.hpp"
#include "entity_interface_macros.hpp"
#include "network/interface_defs.hpp"
//#define NDEBUG
// windows include	
#if KBE_PLATFORM == PLATFORM_WIN32
#else
// linux include
#endif
	
namespace KBEngine{

/**
	cellapp所有消息接口在此定义
*/
NETWORK_INTERFACE_DECLARE_BEGIN(CellappInterface)
	// 某app注册自己的接口地址到本app
	CELLAPP_MESSAGE_DECLARE_ARGS8(onRegisterNewApp,							MERCURY_VARIABLE_MESSAGE,
									int32,									uid, 
									std::string,							username,
									int8,									componentType, 
									uint64,									componentID, 
									uint32,									intaddr, 
									uint16,									intport,
									uint32,									extaddr, 
									uint16,									extport)

	// 某app主动请求look。
	CELLAPP_MESSAGE_DECLARE_ARGS0(lookApp,									MERCURY_FIXED_MESSAGE)

	// 某个app请求查看该app负载状态。
	CELLAPP_MESSAGE_DECLARE_ARGS0(queryLoad,								MERCURY_FIXED_MESSAGE)

	// console远程执行python语句。
	CELLAPP_MESSAGE_DECLARE_STREAM(onExecScriptCommand,						MERCURY_VARIABLE_MESSAGE)

	// dbmgr告知已经启动的其他baseapp或者cellapp的地址
	// 当前app需要主动的去与他们建立连接
	CELLAPP_MESSAGE_DECLARE_ARGS8(onGetEntityAppFromDbmgr,					MERCURY_VARIABLE_MESSAGE,
									int32,									uid, 
									std::string,							username,
									int8,									componentType, 
									uint64,									componentID, 
									uint32,									intaddr, 
									uint16,									intport,
									uint32,									extaddr, 
									uint16,									extport)

	// 某app请求获取一个entityID段的回调
	CELLAPP_MESSAGE_DECLARE_ARGS2(onReqAllocEntityID,						MERCURY_FIXED_MESSAGE,
									ENTITY_ID,								startID,
									ENTITY_ID,								endID)

	// 某app请求获取一个entityID段的回调
	CELLAPP_MESSAGE_DECLARE_ARGS5(onDbmgrInitCompleted,						MERCURY_FIXED_MESSAGE,
									GAME_TIME,								gametime, 
									ENTITY_ID,								startID,
									ENTITY_ID,								endID,
									int32,									startGlobalOrder,
									int32,									startGroupOrder)

	// global数据改变
	CELLAPP_MESSAGE_DECLARE_STREAM(onBroadcastGlobalDataChange,				MERCURY_VARIABLE_MESSAGE)
	CELLAPP_MESSAGE_DECLARE_STREAM(onBroadcastCellAppDataChange,			MERCURY_VARIABLE_MESSAGE)

	// baseEntity请求创建在一个新的space中。
	CELLAPP_MESSAGE_DECLARE_STREAM(onCreateInNewSpaceFromBaseapp,			MERCURY_VARIABLE_MESSAGE)

	// baseapp请求在这个cellapp上创建一个entity。
	CELLAPP_MESSAGE_DECLARE_STREAM(onCreateCellEntityFromBaseapp,			MERCURY_VARIABLE_MESSAGE)

	// 销毁某个cellEntity。
	CELLAPP_MESSAGE_DECLARE_ARGS1(onDestroyCellEntityFromBaseapp,			MERCURY_FIXED_MESSAGE,
									ENTITY_ID,								eid)

	// 某个app向本app告知处于活动状态。
	CELLAPP_MESSAGE_DECLARE_ARGS2(onAppActiveTick,							MERCURY_FIXED_MESSAGE,
									COMPONENT_TYPE,							componentType, 
									COMPONENT_ID,							componentID)

	// entity收到一封mail, 由某个app上的mailbox发起
	CELLAPP_MESSAGE_DECLARE_STREAM(onEntityMail,							MERCURY_VARIABLE_MESSAGE)

	// client访问entity的cell方法
	CELLAPP_MESSAGE_DECLARE_STREAM(onRemoteCallMethodFromClient,			MERCURY_VARIABLE_MESSAGE)

	// executeRawDatabaseCommand从dbmgr的回调
	CELLAPP_MESSAGE_DECLARE_STREAM(onExecuteRawDatabaseCommandCB,			MERCURY_VARIABLE_MESSAGE)

	// base请求获取celldata
	CELLAPP_MESSAGE_DECLARE_STREAM(reqBackupEntityCellData,					MERCURY_VARIABLE_MESSAGE)

	// base请求获取WriteToDB
	CELLAPP_MESSAGE_DECLARE_STREAM(reqWriteToDBFromBaseapp,					MERCURY_VARIABLE_MESSAGE)

	// 客户端直接发送消息给cell实体
	CELLAPP_MESSAGE_DECLARE_STREAM(forwardEntityMessageToCellappFromClient,	MERCURY_VARIABLE_MESSAGE)

	// 请求关闭服务器
	CELLAPP_MESSAGE_DECLARE_STREAM(reqCloseServer,							MERCURY_VARIABLE_MESSAGE)

	// 请求查询watcher数据
	CELLAPP_MESSAGE_DECLARE_STREAM(queryWatcher,							MERCURY_VARIABLE_MESSAGE)

	//--------------------------------------------Entity----------------------------------------------------------
	//远程呼叫entity方法
	ENTITY_MESSAGE_DECLARE_STREAM(onRemoteMethodCall,						MERCURY_VARIABLE_MESSAGE)

	//客户端设置新位置
	ENTITY_MESSAGE_DECLARE_ARGS2(setPosition_XZ_int,						MERCURY_FIXED_MESSAGE,
									int32,									x, 
									int32,									z)
	
	//客户端设置新位置
	ENTITY_MESSAGE_DECLARE_ARGS3(setPosition_XYZ_int,						MERCURY_FIXED_MESSAGE,
									int32,									x, 
									int32,									y, 
									int32,									z)

	//客户端设置新位置
	ENTITY_MESSAGE_DECLARE_ARGS2(setPosition_XZ_float,						MERCURY_FIXED_MESSAGE,
									float,									x, 
									float,									z)

	//客户端设置新位置
	ENTITY_MESSAGE_DECLARE_ARGS3(setPosition_XYZ_float,						MERCURY_FIXED_MESSAGE,
									float,									x, 
									float,									y, 
									float,									z)

	//entity绑定了一个观察者(客户端)
	ENTITY_MESSAGE_DECLARE_ARGS0(onGetWitness,								MERCURY_FIXED_MESSAGE)

	//entity丢失了一个观察者(客户端)
	ENTITY_MESSAGE_DECLARE_ARGS0(onLoseWitness,								MERCURY_FIXED_MESSAGE)

	// entity传送。
	ENTITY_MESSAGE_DECLARE_ARGS3(teleportFromBaseapp,						MERCURY_FIXED_MESSAGE,
									COMPONENT_ID,							cellAppID,
									ENTITY_ID,								targetEntityID,
									COMPONENT_ID,							sourceBaseAppID)
NETWORK_INTERFACE_DECLARE_END()

#ifdef DEFINE_IN_INTERFACE
	#undef DEFINE_IN_INTERFACE
#endif

}
#endif
