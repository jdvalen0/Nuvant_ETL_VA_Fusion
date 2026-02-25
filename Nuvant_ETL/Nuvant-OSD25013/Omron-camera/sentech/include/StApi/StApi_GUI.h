//------------------------------------------------------------------------------
// StApi
//------------------------------------------------------------------------------
/*!
	@ingroup	StApiGUI_PublicImpl
	@file
	@~english	@details	Include file for using StApi GUI module
	@~japanese	@details	StApi GUIモジュール用インクルードファイル
*/
#ifndef STAPI_GUI_H__
#define STAPI_GUI_H__

#include "IStImageDisplayWnd.h"
#include "IStNodeMapDisplayWnd.h"
#include "IStDeviceSelectionWnd.h"
#include "IStGraphDisplayWnd.h"	//@since 1.1.1

#ifdef _WIN32
#   ifndef STSDK_GUI_EXPORTS
#       pragma comment(lib, ST_FILE_NAME("STApi_GUI", ".lib"))
#   endif
#endif

#include "StApi_GUIFunctions.h"

#endif //STAPI_GUI_H__
