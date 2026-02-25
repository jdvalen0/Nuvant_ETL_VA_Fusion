/* This file is encoded in UTF-8,  */
/* but BOM has not been added to accommodate environments not compatible with BOM. */
/*
 StApi
*/
/*!
	@ingroup	StApiTL_PublicImpl
	@file StApi_TLDef.h
	@~english	@details	
	@~japanese	@details	
*/
#ifndef STAPI_TLDEF_H__
#define STAPI_TLDEF_H__

#ifdef __cplusplus
namespace StApi
{
#endif /* __cplusplus */
	//-------------------------------------------------------------------------
	//Definition
	//-------------------------------------------------------------------------
	
	/*! 
		@ingroup	StApiTL_PublicImpl
		@~english	@details	StApi major version.
		@~english	@sa	GetStApiVersion()
		@~japanese	@details	ビルド時StApiメジャーバージョン
		@~japanese	@sa	GetStApiVersion()
	*/
	#define STAPI_VERSION_MAJOR 1

	/*! 
		@ingroup	StApiTL_PublicImpl
		@~english	@details	StApi minor version.
		@~english	@sa	GetStApiVersion()
			@~japanese	@details	ビルド時StApiマイナーバージョン
			@~japanese	@sa	GetStApiVersion()
	*/
	#define STAPI_VERSION_MINOR 1

	/*! 
		@ingroup	StApiTL_PublicImpl
		@~english	@details	StApi sub minor version.
		@~english	@sa	GetStApiVersion()
			@~japanese	@details	ビルド時StApiサブマイナーバージョン
			@~japanese	@sa	GetStApiVersion()
	*/
	#define STAPI_VERSION_SUBMINOR 2

	/*! 
		@ingroup	StApiTL_PublicImpl
		@~english	@details	StApi version.
		@~english	@sa	GetStApiVersion()
			@~japanese	@details	ビルド時StApiバージョン
			@~japanese	@sa	GetStApiVersion()
	*/
	#define STAPI_VERSION ((((STAPI_VERSION_MAJOR & 0xFF) << 24) | (STAPI_VERSION_MINOR & 0xFF) << 16) | (STAPI_VERSION_SUBMINOR & 0xFFFF))


	/*! 
		@ingroup	StApiTL_PublicImpl
		@~english	@details	StApi build time compiler version.
			@~japanese	@details	StApi ビルド時コンパイラーバージョン
	*/
#ifdef _WIN32
	#define STAPI_COMPILER VC141
#else
    #define STAPI_COMPILER GCC
#endif

	//! StApi major version string
	#define STAPI_VERSION_MAJOR_STR TOSTRING(STAPI_VERSION_MAJOR)

	//! StApi minor version string
	#define STAPI_VERSION_MINOR_STR TOSTRING(STAPI_VERSION_MINOR)

	//! StApi sub minor version string
	#define STAPI_VERSION_SUBMINOR_STR TOSTRING(STAPI_VERSION_SUBMINOR)

	//! StApi version string
	#define STAPI_VERSION_STR STAPI_VERSION_MAJOR_STR "." STAPI_VERSION_MINOR_STR "." STAPI_VERSION_SUBMINOR_STR

	//! StApi build time compiler version string
	#define STAPI_COMPILER_STR TOSTRING(STAPI_COMPILER)

	//-------------------------------------------------------------------------
	//Enumerator
	//-------------------------------------------------------------------------
	/*! 
		@ingroup	StApiTL_PublicImpl
		@enum _EStSystemVendor_t
		@~english	@brief	Enumerator for system vendor.
		@~english	@details	Enumerator for system vendor.
		@~japanese	@brief	システムベンダー列挙子
		@~japanese	@details	システムベンダー列挙子
	*/
	typedef enum _EStSystemVendor_t
	{
		/*!
			@~english	@details	Default system for USB3Vision and GigEVision.
			@~japanese	@details	デフォルトシステム(USB3VisionおよびGigEVisionに対応)
		*/
		StSystemVendor_Default = 0,

		/*!
			@~english	@details	Sentech for USB3Vision and GigEVision.
			@~japanese	@details	センテック製(USB3VisionおよびGigEVisionに対応)
		*/
		StSystemVendor_Sentech = 0,

		/*!
			@~english	@details	Euresys for CoaXPress.
			@~japanese	@details	Euresys社製(CoaXPressに対応)
		*/
		StSystemVendor_Euresys = 1,

		/*!
			@~english	@details	Kaya for CoaXPress.
			@~japanese	@details	Kaya社製(CoaXPressに対応)
		*/
		StSystemVendor_Kaya = 2,

		/*!
			@~english	@details	SiliconSoftware for CoaXPress.
			@~japanese	@details	SiliconSoftware社製(CoaXPressに対応)
		*/
		StSystemVendor_SiliconSoftware = 3,

		/*!
			@~english	@details	ActiveSilicon for CoaXPress.
			@~japanese	@details	ActiveSilicon社製(CoaXPressに対応)
		*/
		StSystemVendor_ActiveSilicon = 4,

		/*!
			@~english	@details	Count of vendor.
			@~japanese	@details	ベンダー数
		*/
		StSystemVendor_Count
	} EStSystemVendor_t, *PEStSystemVendor_t;
	
	/*! 
		@ingroup	StApiTL_PublicImpl
		@enum EStInterfaceType_t
		@~english	@brief	Enumerator for interface.
		@~english	@details	Enumerator for interface.
		@~japanese	@brief	インターフェースタイプ列挙子
		@~japanese	@details	インターフェースタイプ列挙子
	*/
	typedef enum _EStInterfaceType_t
	{
		/*!
			@~english	@details	Invalid value.
			@~japanese	@details	不正な値
		*/
		StInterfaceType_Unknown = 0,

		/*!
			@~english	@details	USB3Vision
			@~japanese	@details	USB3Vision
		*/
		StInterfaceType_USB3Vision = 1,	

		/*!
			@~english	@details	GigEVision
			@~japanese	@details	GigEVision
		*/
		StInterfaceType_GigEVision = 2,

		/*!
			@~english	@details	CoaXPress
			@~japanese	@details	CoaXPress
		*/
		StInterfaceType_CoaXPress = 4,

#ifdef _WIN32
		/*!
			@~english	@details	CameraLink
			@~japanese	@details	CameraLink
		*/
		StInterfaceType_CameraLink = 8,
#endif //_WIN32

		/*!
			@~english	@details	All
			@~japanese	@details	すべてのインターフェース
		*/
		StInterfaceType_All = -1
	} EStInterfaceType_t, *PEStInterfaceType_t;

	/*! 
		@ingroup	StApiTL_PublicImpl
		@enum EStCallbackType_t
		@~english	@brief	Enumerator for the type of callback function.
		@~english	@details	Enumerator for the type of callback function.
		@~japanese	@brief	コールバックタイプ列挙子
		@~japanese	@details	コールバックタイプ列挙子
	*/
	typedef enum _EStCallbackType_t
	{	
		/*!
			@~english	@details	Error events that have occurred on the GenTL system module.
			@~japanese	@details	GenTLシステムモジュールエラーコールバック
		*/
		StCallbackType_GenTLEvent_SystemError,
		
		/*!
			@~english	@details	Error events that have occurred on the GenTL interface module.
			@~japanese	@details	GenTLインターフェースモジュールエラーコールバック
		*/
		StCallbackType_GenTLEvent_InterfaceError,
		
		/*!
			@~english	@details	Error events that have occurred on the GenTL device module.
			@~japanese	@details	GenTLデバイスモジュールエラーコールバック
		*/
		StCallbackType_GenTLEvent_DeviceError,
		
		/*!
			@~english	@details	Error events that have occurred on the GenTL data stream module.
			@~japanese	@details	GenTLデータストリームモジュールエラーコールバック
		*/
		StCallbackType_GenTLEvent_DataStreamError,
		
		/*!
			@~english	@details	Error events that have occurred on the GenTL buffer module.
			@~japanese	@details	GenTL(ストリーム)バッファモジュールエラーコールバック
		*/
		StCallbackType_GenTLEvent_StreamBufferError,
		
		/*!
			@~english	@details	New buffer events that have occurred on the GenTL data stream module.
			@~japanese	@details	GenTLNewBufferコールバック
		*/
		StCallbackType_GenTLEvent_DataStreamNewBuffer,
		
		/*!
			@~english	@details	File open events that have occurred on the StApi::IStVideoFiler.
			@~japanese	@details	動画ファイルオープンコールバック
		*/
		StCallbackType_StApiIPEvent_VideoFilerOpen,
		
		/*!
			@~english	@details	File closing events that have occurred on the StApi::IStVideoFiler.
			@~japanese	@details	動画ファイルクローズコールバック
		*/
		StCallbackType_StApiIPEvent_VideoFilerClose,
		
		/*!
			@~english	@details	Error events that have occurred on the StApi::IStVideoFiler.
			@~japanese	@details	動画ファイルエラーコールバック
		*/
		StCallbackType_StApiIPEvent_VideoFilerError,
		
		/*!
			@~english	@details	Drawing events that have occurred on the StApi::IStImageDisplayWnd.
			@~japanese	@details	画像プレビューウィンドウ描画コールバック
		*/
		StCallbackType_StApiGUIEvent_DisplayImageWndDrawing,
		
		/*!
			@~english	@details	Create events that have occurred on the StApi::IStWnd.
			@~japanese	@details	ウィンドウ生成コールバック
		*/
		StCallbackType_StApiGUIEvent_WndCreate,
		
		/*!
			@~english	@details	Closing events that have occurred on the StApi::IStWnd.
			@~japanese	@details	ウィンドウクローズコールバック(ウィンドウが閉じられようとしているときに発生します)
		*/
		StCallbackType_StApiGUIEvent_WndClose,
		
		/*!
			@~english	@details	Destroy events that have occurred on the StApi::IStWnd.
			@~japanese	@details	ウィンドウクローズコールバック(ウィンドウが閉じらたときに発生します)
		*/
		StCallbackType_StApiGUIEvent_WndDestroy,
		
		/*!
			@~english	@details	Error events that have occurred on the StApi::IStWnd.
			@~japanese	@details	ウィンドウエラーコールバック
		*/
		StCallbackType_StApiGUIEvent_WndError,

		/*!
			@~english	@details	Count of type of callback.
			@~japanese	@details	コールバックタイプ数
		*/
		StCallbackType_Count
	}EStCallbackType_t, *PEStCallbackType_t;

	/*! 
		@ingroup	StApiTL_PublicImpl
		@enum EStTimeoutHandling_t
		@~english	@brief	Enumerator for dealing with timeout.
		@~english	@details	Enumerator for dealing with timeout.
		@~japanese	@brief	タイムアウト対処列挙子
		@~japanese	@details	タイムアウト対処列挙子
	*/
	typedef enum /* _EStTimeoutHandling_t */
	{
		/*!
			@~english	@details	Return
			@~japanese	@details	関数から戻ります。
		*/
		StTimeoutHandling_Return,

		/*!
			@~english	@details	Throw exception
			@~japanese	@details	例外を発生させます。
		*/
		StTimeoutHandling_ThrowException,

		/*!
			@~english	@details	Count of type of timeout handling.
			@~japanese	@details	タイムアウト対処列挙子数
		*/
		StTimeoutHandling_Count
	}EStTimeoutHandling_t, *PEStTimeoutHandling_t;

	/*! 
		@ingroup	StApiTL_PublicImpl
		@enum EStMemoryInitialization_t
		@~english	@brief	Enumerator for initialization process of memory allocation.
		@~japanese	@brief	メモリ初期化方法列挙子
		@~english	@details	Enumerator for initialization process of memory allocation.
		@~japanese	@details	メモリ初期化方法列挙子
	*/
	typedef enum _EStMemoryInitialization_t
	{
		/*!
			@~english	@details	Do nothing
			@~japanese	@details	なにもしない(初期値は不定になります)
		*/
		StMemoryInitialization_DoNothing = 0,

		/*!
			@~english	@details	All filled with 0
			@~japanese	@details	0で初期化します。
		*/
		StMemoryInitialization_FilledWith0 = 1,

		/*!
			@~english	@details	All filled with 1
			@~japanese	@details	1(0xFF)で初期化します。
		*/
		StMemoryInitialization_FilledWith1 = 2,

		/*!
			@~english	@details	Chart(if supported)
			@~japanese	@details	対応している場合チャート1を生成します。
		*/
		StMemoryInitialization_Chart_1 = 3,

		/*!
			@~english	@details	Count of type of memory initialization.
			@~japanese	@details	メモリ初期化方法数
		*/
		StMemoryInitialization_Count
	} EStMemoryInitialization_t, *PEStMemoryInitialization_t;

	
	/*! 
		@ingroup	StApiTL_PublicImpl
		@enum EStNumberDataType_t
		@~english	@brief	Enumerator for data type.
		@~japanese	@brief	データタイプ列挙子
		@~english	@details	Enumerator for data type.
		@~japanese	@details	データタイプ列挙子
	*/
	typedef enum _EStNumberDataType_t
	{
		/*!
			@~english	@details	Unknown.
			@~japanese	@details	不明なデータタイプ
		*/
		StNumberDataType_Unknown = 0,

		/*!
			@~english	@details	8bit unsigned integer.
			@~japanese	@details	8ビット符号なし整数
		*/
		StNumberDataType_uint8 = 0x00000008,

		/*!
			@~english	@details	8bit signed integer.
			@~japanese	@details	8ビット符号あり整数
		*/
		StNumberDataType_int8 = 0x00010008,
		/*!
			@~english	@details	16bit unsigned integer.
			@~japanese	@details	16ビット符号なし整数
		*/

		StNumberDataType_uint16 = 0x00000010,

		/*!
			@~english	@details	16bit signed integer.
			@~japanese	@details	16ビット符号あり整数
		*/
		StNumberDataType_int16 = 0x00010010,

		/*!
			@~english	@details	32bit unsigned integer.
			@~japanese	@details	32ビット符号なし整数
		*/
		StNumberDataType_uint32 = 0x00000020,

		/*!
			@~english	@details	32bit signed integer.
			@~japanese	@details	32ビット符号あり整数
		*/
		StNumberDataType_int32 = 0x00010020,

		/*!
			@~english	@details	32bit floating point.
			@~japanese	@details	32ビット浮動小数点数
		*/
		StNumberDataType_float32 = 0x00030020,

		/*!
			@~english	@details	64bit unsigned integer.
			@~japanese	@details	64ビット符号なし整数
		*/
		StNumberDataType_uint64 = 0x00000040,

		/*!
			@~english	@details	64bit signed integer.
			@~japanese	@details	64ビット符号あり整数
		*/
		StNumberDataType_int64 = 0x00010040,

		/*!
			@~english	@details	64bit floating point.
			@~japanese	@details	64ビット浮動小数点数
		*/
		StNumberDataType_float64 = 0x00030040,
	} EStNumberDataType_t, *PEStNumberDataType_t;

#define GetStNumberDataTypeBitCount(e) ((e) & 0xFFFF)
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif //STAPI_TLDEF_H__


