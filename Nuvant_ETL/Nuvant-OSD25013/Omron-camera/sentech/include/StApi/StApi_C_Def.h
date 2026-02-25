/* This file is encoded in UTF-8,  */
/* but BOM has not been added to accommodate environments not compatible with BOM. */
/*
 StApi C
*/
/*!
	@ingroup	StApiC_PublicImpl
	@file StApi_C.h
	@~english	@details
	@~japanese	@details
*/

#if !defined(STAPI_C_DEF_H__)
#define STAPI_C_DEF_H__

#ifdef __BORLANDC__
#include <_stddef.h>
#endif /* __BORLANDC__ */

#include <stdio.h>

#if (defined(_MSC_VER) && (1600 <= _MSC_VER)) || (!defined(_WIN32))
/*VC++2010- */
#include <stdint.h>
#else
#ifndef _STDINT
typedef char int8_t;
typedef unsigned char uint8_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#endif /*_STDINT */
#endif /* 1600 <= _MSC_VER */

#include <GenICamVersion.h>
#include <StApi_TLDef.h>
#include <StApi_IPDef.h>
#include <StApi_GUIDef.h>
#include <StGenTL_Def.h>
#include <StApi_PixelFormat.h>
#include <StGenApi_Def.h>

#ifdef STAPI_C_EXPORTS
#   define STAPI_API_EXPORTS /* __declspec(dllexport) */
#   define STAPI_CALLTYPE __stdcall
#else
#   if defined(_WIN32)
#       if defined(_MSC_VER)
            /* MSVC */
#           define STAPI_API_EXPORTS
#       elif defined(__BORLANDC__)
            /* BCC */
#           define STAPI_API_EXPORTS __declspec(dllimport)	
#       elif defined(__GNUC__)
            /* gcc(MinGW) */
#           define STAPI_API_EXPORTS __declspec(dllimport)	
#       endif
#       define STAPI_CALLTYPE __stdcall
#   else
        /* non windows */
#       define STAPI_API_EXPORTS __attribute__((visibility("default")))
#       define STAPI_CALLTYPE 
#   endif
#endif





#ifdef __cplusplus
extern "C" {
	using namespace GenTL;
	using namespace StApi;
#endif /* __cplusplus */




	/*************************************************************************/
	/* Typedef */
	/*************************************************************************/
	/*************************************************************************/
	/* Enumerator */
	/*************************************************************************/
	/*!
		@ingroup	StApiC_PublicImpl
		@enum EStApiCError_t
		@~english	@brief	Enumerator for error code.
		@~english	@details	Enumerator for error code.
		@~japanese	@brief	エラーコード列挙子
		@~japanese	@details	エラーコード列挙子
	*/
	typedef enum _EStApiCError_t
	{
		/*!
			@~english	@details	Successed.
			@~japanese	@details	正常終了
		*/
		StApiCError_NoError = (int)0x00000000L,

		/*!
			@~english	@details	Error.
			@~japanese	@details	エラー
		*/
		StApiCError_Error = (int)0xC0000000L,

		/*!
			@~english	@details	Bad allocation.
			@~japanese	@details	メモリー割り当てエラー
		*/
		StApiCError_BadAlloc = (int)0xC0000001L,

		/*!
			@~english	@details	Argument is invalid.
			@~japanese	@details	引数が不正
		*/
		StApiCError_InvalidArgument = (int)0xC0000002L,

		/*!
			@~english	@details	Argument is out of range.
			@~japanese	@details	引数が範囲外
		*/
		StApiCError_OutOfRange = (int)0xC0000003L,

		/*!
			@~english	@details	Property access fails.
			@~japanese	@details	プロパティアクセスエラー
		*/
		StApiCError_Property = (int)0xC0000004L,

		/*!
			@~english	@details	Runtime error.
			@~japanese	@details	ランタイムエラー
		*/
		StApiCError_Runtime = (int)0xC0000005L,

		/*!
			@~english	@details	Logical error.
			@~japanese	@details	論理エラー
		*/
		StApiCError_LogicalError = (int)0xC0000006L,

		/*!
			@~english	@details	Access error.
			@~japanese	@details	アクセスエラー
		*/
		StApiCError_AccessError = (int)0xC0000007L,

		/*!
			@~english	@details	Timeout error.
			@~japanese	@details	タイムアウトエラー
		*/
		StApiCError_Timeout = (int)0xC0000008L,

		/*!
			@~english	@details	Dynamic cast was zero.
			@~japanese	@details	ダイナミックキャストエラー
		*/
		StApiCError_DynamicCast = (int)0xC0000009L,

		/*!
			@~english	@details	GenTL error.
			@~japanese	@details	GenTLエラー
		*/
		StApiCError_GenTLError = (int)0xC000000AL,

#if defined(_WIN32)
		/*!
			@~english	@details	Win32 error.
			@~japanese	@details	Win32エラー
		*/
		StApiCError_Win32Error = (int)0xC000000BL,
#elif defined(__linux__)
		/*!
			@~english	@details	Linux error.
			@~japanese	@details	Linuxエラー
		*/
		StApiCError_LinuxError = (int)0xC000000BL,
#elif defined(__APPLE__)
		/*!
			@~english	@details	MacOS error.
			@~japanese	@details	MacOSエラー
		*/
		StApiCError_OSXError = (int)0xC000000BL,
#endif
	}EStApiCError_t, *PEStApiCError_t;

#define STAPI_CALL STAPI_API_EXPORTS EStApiCError_t STAPI_CALLTYPE
#define STAPI_PCALL(function) typedef  EStApiCError_t (STAPI_CALLTYPE *function)

	/*!
		@ingroup	StApiC_PublicImpl
		@enum EApiHandleType
		@~english	@brief	Handle type.
		@~english	@details	Handle type.
		@~japanese	@brief	ハンドルタイプ
		@~japanese	@details	ハンドルタイプ
	*/
	typedef enum _EApiHandleType
	{
		/*!
			@~english	@details	Unknown handle.
			@~japanese	@details	不明なハンドル
		*/
		ApiHandleType_IUnknown,

		/*************************************************************************/
		/* GenICam */
		/*************************************************************************/
		/*!
			@~english	@details	gcstring handle.
			@~japanese	@details	gcstring ハンドル
		*/
		/*ApiHandleType_GenICam_gcstring = 0x1000, */

		/*!
			@~english	@details	gcstring_vector handle.
			@~japanese	@details	gcstring_vector ハンドル
		*/
		/*ApiHandleType_GenICam_gcstring_vector, */

		/*************************************************************************/
		/* GenApi */
		/*************************************************************************/
		ApiHandleType_GenApi_INodeMap = 0x2000,
		ApiHandleType_GenApi_IDeviceInfo,
		ApiHandleType_GenApi_IUserData,
		ApiHandleType_GenApi_ILock,
		
		ApiHandleType_GenApi_IBase,
		ApiHandleType_GenApi_INode,
		ApiHandleType_GenApi_IPort,
		ApiHandleType_GenApi_IChunkPort,
		ApiHandleType_GenApi_IValue,

		ApiHandleType_GenApi_IBoolean,
		ApiHandleType_GenApi_ICategory,
		ApiHandleType_GenApi_ICommand,
		ApiHandleType_GenApi_IEnumEntry,
		ApiHandleType_GenApi_IEnumeration,
		ApiHandleType_GenApi_IFloat,
		ApiHandleType_GenApi_IInteger,
		ApiHandleType_GenApi_IRegister,
		ApiHandleType_GenApi_ISelector,
		ApiHandleType_GenApi_IString,

		
	    /*	
		ApiHandleType_GenApi_IDestroy,
		ApiHandleType_GenApi_IPortRecorder,
		ApiHandleType_GenApi_IPortReplay,
		ApiHandleType_GenApi_IPortWriteList,
        */

		/*************************************************************************/
		/* StApi TL */
		/*************************************************************************/
		/*!
			@~english	@details	IStPort handle.
			@~japanese	@details	IStPort ハンドル
		*/
		ApiHandleType_StApi_IStPort = 0x3000,

		/*!
			@~english	@details	IStPortURLInfo handle.
			@~japanese	@details	IStPortURLInfo ハンドル
		*/
		ApiHandleType_StApi_IStPortURLInfo,

		/*!
			@~english	@details	IStPortInfo handle.
			@~japanese	@details	IStPortInfo ハンドル
		*/
		ApiHandleType_StApi_IStPortInfo,

		/*!
			@~english	@details	IStSystem handle.
			@~japanese	@details	IStSystem ハンドル
		*/
		ApiHandleType_StApi_IStSystem,

		/*!
			@~english	@details	IStSystemInfo handle.
			@~japanese	@details	IStSystemInfo ハンドル
		*/
		ApiHandleType_StApi_IStSystemInfo,

		/*!
			@~english	@details	IStInterface handle.
			@~japanese	@details	IStInterface ハンドル
		*/
		ApiHandleType_StApi_IStInterface,

		/*!
			@~english	@details	IStInterfaceInfo handle.
			@~japanese	@details	IStInterfaceInfo ハンドル
		*/
		ApiHandleType_StApi_IStInterfaceInfo,


		/*!
		@~english	@details	IStDevice handle.
		@~japanese	@details	IStDevice ハンドル
		*/
		ApiHandleType_StApi_IStDevice,

		/*!
			@~english	@details	IStDeviceInfo handle.
			@~japanese	@details	IStDeviceInfo ハンドル
		*/
		ApiHandleType_StApi_IStDeviceInfo,

		/*!
			@~english	@details	IStDataStream handle.
			@~japanese	@details	IStDataStream ハンドル
		*/
		ApiHandleType_StApi_IStDataStream,

		/*!
			@~english	@details	IStDataStreamInfo handle.
			@~japanese	@details	IStDataStreamInfo ハンドル
		*/
		ApiHandleType_StApi_IStDataStreamInfo,

		/*!
			@~english	@details	IStStreamBuffer handle.
			@~japanese	@details	IStStreamBuffer ハンドル
		*/
		ApiHandleType_StApi_IStStreamBuffer,

		/*!
			@~english	@details	IStStreamBufferInfo handle.
			@~japanese	@details	IStStreamBufferInfo ハンドル
		*/
		ApiHandleType_StApi_IStStreamBufferInfo,

		/*!
			@~english	@details	IStImage handle.
			@~japanese	@details	IStImage ハンドル
		*/
		ApiHandleType_StApi_IStImage,

		/*!
			@~english	@details	IStImageBuffer handle.
			@~japanese	@details	IStImageBuffer ハンドル
		*/
		ApiHandleType_StApi_IStImageBuffer,

		/*!
			@~english	@details	IStPixelFormatInfo handle.
			@~japanese	@details	IStPixelFormatInfo ハンドル
		*/
		ApiHandleType_StApi_IStPixelFormatInfo,

		/*!
			@~english	@details	IStPixelComponentInfo handle.
			@~japanese	@details	IStPixelComponentInfo ハンドル
		*/
		ApiHandleType_StApi_IStPixelComponentInfo,

		/*!
		@~english	@details	IStPixelComponentValue handle.
		@~japanese	@details	IStPixelComponentValue ハンドル
		*/
		ApiHandleType_StApi_IStPixelComponentValue,

		/*!
			@~english	@details	IStFeatureBag handle.
			@~japanese	@details	IStFeatureBag ハンドル
		*/
		ApiHandleType_StApi_IStFeatureBag,

		/*!
			@~english	@details	IStAllocator handle.
			@~japanese	@details	IStAllocator ハンドル
		*/
		ApiHandleType_StApi_IStAllocator,

		/*!
			@~english	@details	IStRegisteredCallback handle.
			@~japanese	@details	IStRegisteredCallback ハンドル
		*/
		ApiHandleType_StApi_IStRegisteredCallback,

		/*!
			@~english	@details	IStCallbackParamBase handle.
			@~japanese	@details	IStCallbackParamBase ハンドル
		*/
		ApiHandleType_StApi_IStCallbackParamBase,

		/*!
			@~english	@details	IStSpecificTypeAllocator handle.
			@~japanese	@details	IStSpecificTypeAllocator ハンドル
		*/
		ApiHandleType_StApi_IStSpecificTypeAllocator,

		/*************************************************************************/
		/* StApi IP */
		/*************************************************************************/
		/*!
			@~english	@details	IStConverter handle.
			@~japanese	@details	IStConverter ハンドル
		*/
		ApiHandleType_StApi_IStConverter = 0x4000,

		/*!
			@~english	@details	IStConverterInfo handle.
			@~japanese	@details	IStConverterInfo ハンドル
		*/
		ApiHandleType_StApi_IStConverterInfo,

		/*!
			@~english	@details	IStFilter handle.
			@~japanese	@details	IStFilter ハンドル
		*/
		ApiHandleType_StApi_IStFilter,

		/*!
			@~english	@details	IStFilterInfo handle.
			@~japanese	@details	IStFilterInfo ハンドル
		*/
		ApiHandleType_StApi_IStFilterInfo,

		/*!
		@~english	@details	IStFiler handle.
		@~japanese	@details	IStFiler ハンドル
		*/
		ApiHandleType_StApi_IStFiler,

		/*!
		@~english	@details	IStFilerInfo handle.
		@~japanese	@details	IStFilerInfo ハンドル
		*/
		ApiHandleType_StApi_IStFilerInfo,

		/*!
			@~english	@details	IStPixelFormatConverter handle.
			@~japanese	@details	IStPixelFormatConverter ハンドル
		*/
		ApiHandleType_StApi_IStPixelFormatConverter,

		/*!
			@~english	@details	IStReverseConverter handle.
			@~japanese	@details	IStReverseConverter ハンドル
		*/
		ApiHandleType_StApi_IStReverseConverter,

		/*!
			@~english	@details	IStBalanceRatioFilter handle.
			@~japanese	@details	IStBalanceRatioFilter ハンドル
		*/
		ApiHandleType_StApi_IStBalanceRatioFilter,

		/*!
			@~english	@details	IStChromaSuppressionFilter handle.
			@~japanese	@details	IStChromaSuppressionFilter ハンドル
		*/
		ApiHandleType_StApi_IStChromaSuppressionFilter,

		/*!
			@~english	@details	IStColorTransformationFilter handle.
			@~japanese	@details	IStColorTransformationFilter ハンドル
		*/
		ApiHandleType_StApi_IStColorTransformationFilter,

		/*!
			@~english	@details	IStEdgeEnhancementFilter handle.
			@~japanese	@details	IStEdgeEnhancementFilter ハンドル
		*/
		ApiHandleType_StApi_IStEdgeEnhancementFilter,

		/*!
			@~english	@details	IStFlatFieldCorrectionFilter handle.
			@~japanese	@details	IStFlatFieldCorrectionFilter ハンドル
		*/
		ApiHandleType_StApi_IStFlatFieldCorrectionFilter,

		/*!
			@~english	@details	IStGammaCorrectionFilter handle.
			@~japanese	@details	IStGammaCorrectionFilter ハンドル
		*/
		ApiHandleType_StApi_IStGammaCorrectionFilter,

		/*!
			@~english	@details	IStNoiseReductionFilter handle.
			@~japanese	@details	IStNoiseReductionFilter ハンドル
		*/
		ApiHandleType_StApi_IStNoiseReductionFilter,

		/*!
			@~english	@details	IStSNMeasurementFilter handle.
			@~japanese	@details	IStSNMeasurementFilter ハンドル
		*/
		ApiHandleType_StApi_IStSNMeasurementFilter,

		/*!
			@~english	@details	IStSNMeasurementResult handle.
			@~japanese	@details	IStSNMeasurementResult ハンドル
		*/
		ApiHandleType_StApi_IStSNMeasurementResult,

		/*!
			@~english	@details	IStStillImageFiler handle.
			@~japanese	@details	IStStillImageFiler ハンドル
		*/
		ApiHandleType_StApi_IStStillImageFiler,

		/*!
			@~english	@details	IStVideoFiler handle.
			@~japanese	@details	IStVideoFiler ハンドル
		*/
		ApiHandleType_StApi_IStVideoFiler,

		/*!
			@~english	@details	IStGraphData handle.
			@~japanese	@details	IStGraphData ハンドル
		*/
		ApiHandleType_StApi_IStGraphData,

		/*!
			@~english	@details	IStGraphDataBuffer handle.
			@~japanese	@details	IStGraphDataBuffer ハンドル
		*/
		ApiHandleType_StApi_IStGraphDataBuffer,

		/*!
			@~english	@details	IStGraphDataBufferResizable handle.
			@~japanese	@details	IStGraphDataBufferResizable ハンドル
		*/
		ApiHandleType_StApi_IStGraphDataBufferResizable,

		/*!
			@~english	@details	IStGraphDataBufferList handle.
			@~japanese	@details	IStGraphDataBufferList ハンドル
		*/
		ApiHandleType_StApi_IStGraphDataBufferList,

		/*!
			@~english	@details	IStGraphDataBufferListResizable handle.
			@~japanese	@details	IStGraphDataBufferListResizable ハンドル
		*/
		ApiHandleType_StApi_IStGraphDataBufferListResizable,

		/*!
			@~english	@details	IStGraphDataFilter handle.
			@~japanese	@details	IStGraphDataFilter ハンドル
		*/
		ApiHandleType_StApi_IStGraphDataFilter,

		/*!
			@~english	@details	IStImageAveragingFilter handle.
			@~japanese	@details	IStImageAveragingFilter ハンドル
		*/
		ApiHandleType_StApi_IStImageAveragingFilter,

		/*!
			@~english	@details	IStDefectivePixelDetectionFilter handle.
			@~japanese	@details	IStDefectivePixelDetectionFilter ハンドル
		*/
		ApiHandleType_StApi_IStDefectivePixelDetectionFilter,

		/*************************************************************************/
		/* StApi GUI */
		/*************************************************************************/
		/*!
			@~english	@details	IStWnd handle.
			@~japanese	@details	IStWnd ハンドル
		*/
		ApiHandleType_StApi_IStWnd = 0x5000,

		
		/*!
			@~english	@details	IStWndInf handle.
			@~japanese	@details	IStWndInf ハンドル
		*/
		ApiHandleType_StApi_IStWndInfo,
		
		/*!
			@~english	@details	IStDeviceSelectionWnd handle.
			@~japanese	@details	IStDeviceSelectionWnd ハンドル
		*/
		ApiHandleType_StApi_IStDeviceSelectionWnd,
		
		/*!
			@~english	@details	IStNodeMapDisplayWnd handle.
			@~japanese	@details	IStNodeMapDisplayWnd ハンドル
		*/
		ApiHandleType_StApi_IStNodeMapDisplayWnd,
		
		/*!
			@~english	@details	IStImageDisplayWnd handle.
			@~japanese	@details	IStImageDisplayWnd ハンドル
		*/
		ApiHandleType_StApi_IStImageDisplayWnd,
		
		/*!
			@~english	@details	RegisteredINode handle.
			@~japanese	@details	RegisteredINode ハンドル
		*/
		ApiHandleType_StApi_RegisteredINode,
		
		/*!
			@~english	@details	IStDrawingTool handle.
			@~japanese	@details	IStDrawingTool ハンドル
		*/
		ApiHandleType_StApi_IStDrawingTool,
		
		/*!
			@~english	@details	IStGraphDisplayWnd handle.
			@~japanese	@details	IStGraphDisplayWnd ハンドル
		*/
		ApiHandleType_StApi_IStGraphDisplayWnd,
	}EApiHandleType, *PEApiHandleType;

	/*************************************************************************/
	/* struct StApiHandle_t */
	/*************************************************************************/
	/*!
		@ingroup StApiC_PublicImpl
		@struct StApiHandle_t
		@~english	@brief	Struct for genaral handle.
		@~english	@details	Struct for genaral handle.
		@~japanese	@brief	汎用的なハンドル用構造体
		@~japanese	@details	汎用的なハンドル用構造体
	*/
	typedef struct _StApiHandle_t
	{

		/*!
			@~english	@details	Handle.
			@~japanese	@details	ハンドル
		*/
		void *Handle;

		/*!
			@~english	@details	Handle type.
			@~japanese	@details	ハンドルタイプ
		*/
		EApiHandleType	HandleType;
	} StApiHandle_t, *PStApiHandle_t;

	typedef void (STAPI_CALLTYPE fNodeCallbackFunc_t)(PStApiHandle_t psINodeHandle, void* pvContext);
	typedef void (STAPI_CALLTYPE fStCallbackFunc_t)(PStApiHandle_t, void*);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STAPI_C_DEF_H__ */
