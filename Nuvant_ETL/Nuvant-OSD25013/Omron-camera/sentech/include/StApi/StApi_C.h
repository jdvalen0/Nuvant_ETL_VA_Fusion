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

#if !defined(STAPI_C_H__)
#define STAPI_C_H__

#include <stddef.h>

#ifdef _MSC_VER
#pragma warning(push)	
#pragma warning(disable : 4819)	
#include "StApi_C_Def.h"
#include "StApi_C_GenApi.h"
#include "StApi_C_StApi.h"
#pragma warning(pop)	
#else
#include "StApi_C_Def.h"
#include "StApi_C_GenApi.h"
#include "StApi_C_StApi.h"
#endif



#ifdef __cplusplus
extern "C" {
	using namespace GenTL;
	using namespace StApi;
#endif /* __cplusplus */

	/*!
		@ingroup StApiC_PublicImpl
		@struct ApiFunctions
		@~english	@brief	This structure holds the address of the C language wrapper function of StApi.
		@~english	@details	This structure holds the address of the C language wrapper function of StApi.
		@~japanese	@brief	この構造体は、StApiのC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は、StApiのC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _ApiFunctions
	{
		/*!
			@copydoc GenApi_Functions_t
		*/
		GenApi_Functions_t	*GenApi;

		/*!
			@copydoc StApi_Functions_t
		*/
		StApi_Functions_t	*StApi;
	}ApiFunctions, *PApiFunctions;

	/*!
		@ingroup	StApiC_PublicImpl
		@~english	@brief	Initialize StApiC.
		@~english	@details	Initialize StApiC. This function must be called before using other StApiC functions. 
		@~english	@attention	Call StApiCTerminate() to release the resource of StApiC when it is no longer needed. 
		@~english	@param[in]	nStApiVersion	StApi build time version (STAPI_VERSION).
		@~english	@param[out]	pApiFunctions	StApiC functions.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	StApiCライブラリを初期化します。
		@~japanese	@details	StApiCライブラリを初期化します。他のStApi関数を呼び出す前にこの関数を呼び出して、StApiCライブラリを初期化してください。
		@~japanese	@attention	StApiCライブラリが不要になったら StApiCTerminate() を呼び出してリソースを解放してください。 
		@~japanese	@param[in]	nStApiVersion	ビルド時StApiバージョン(STAPI_VERSION)
		@~japanese	@param[out]	ppApiFunctions	StApic 関数群
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_API_EXPORTS EStApiCError_t STAPI_CALLTYPE StApiCInitialize(uint32_t nStApiVersion, PApiFunctions *ppApiFunctions);

#if !defined(STAPI_C_EXPORTS)
#	if defined(_WIN32) && defined(_MSC_VER)
		/* MSVC */
#		include <StApi_Linkage.h>
#		pragma message("Link : " ST_FILE_NAME("StApi_C", ".lib"))
#		pragma comment(lib, ST_FILE_NAME("StApi_C", ".lib"))
#	endif

#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STAPI_C_H__ */
