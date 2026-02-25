//------------------------------------------------------------------------------
// StApi
//------------------------------------------------------------------------------
/*!
	@ingroup	StApiTL_PublicImpl
	@file
	@~english	@details	Include file for using StApi Transport Layer module.
	@~japanese	@details	StApi トランスポート層モジュール用インクルードファイル
*/
#ifndef STAPI_TL_H__
#define STAPI_TL_H__

#ifdef _WIN32
#   define _WINSOCKAPI_	// To prevent including winsock.h when included windows.h which has WinSock2.h.
#endif

#if !defined(STAPI_DEBUG_BUILD)
#	if !defined(GENICAM_USER_ALWAYS_LINK_RELEASE)
#		define GENICAM_USER_ALWAYS_LINK_RELEASE
#	endif
#endif

#ifdef _MSC_VER
#pragma warning(push)	
#pragma warning(disable : 4819)	
#include "StApi_Linkage.h"
#pragma warning(pop)	
#else
#include "StApi_Linkage.h"
#endif

#include "StApi_Utilities.h"


#include "CStGenApiCallbackEx.h"
#include "CStCallback.h"
#include "CStException.h"

#ifdef _MSC_VER
#pragma warning(push)	
#pragma warning(disable : 4819)	
#include "StApi_TLFunctions.h"
#pragma warning(pop)	
#else
#include "StApi_TLFunctions.h"
#endif

#if defined(_WIN32) && !defined(STSDK_TL_EXPORTS)
#pragma comment(lib, ST_FILE_NAME("STApi_TL", ".lib"))
#endif

#endif //STAPI_TL_H__
