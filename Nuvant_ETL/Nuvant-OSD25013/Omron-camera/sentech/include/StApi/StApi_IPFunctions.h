//------------------------------------------------------------------------------
// StApi
//------------------------------------------------------------------------------
/*!
	@file	StApi_IPFunctions.h
	@~english	@details
	@~japanese	@details
	@ingroup	StApiIP_PublicImpl
*/
#ifndef STAPI_IP_FUNCTIONS_H__
#define STAPI_IP_FUNCTIONS_H__

#ifdef _MSC_VER
#pragma warning(push)	
#pragma warning(disable : 4819)	
#include "StApi_IPDef.h"
#pragma warning(pop)	
#else
#include "StApi_IPDef.h"
#endif

namespace StApi
{

	//-------------------------------------------------------------------------
	// C Functions
	//-------------------------------------------------------------------------	
	/*!
		@ingroup	StApiIP_PublicImpl
		@~english	@brief	Acquire IStConverterReleasable. The image format and image size may change after the conversion process.
		@~english	@details	Acquire IStConverterReleasable. The image format and image size may change after the conversion process.
		@~english	@param[in] eConverterType	Type of converter.
		@~english	@return	IStConverterReleasable pointer.
		@~english	@attention	If the acquired interface pointer of IStConverterReleasable does not needed anymore, call IStConverterReleasable::Release() to release it. 
		@~english	@exception	Throw out a GenICam::GenericException when StApi is not initialized or memory allocation is failed.
		@~japanese	@brief	IStConverterReleasable インターフェースポインターを取得します。IStConverterReleasable で行われる画像処理では、 IStFilterReleasable で行われる画像処理と異なり、ピクセルフォーマットや画像サイズが変化することがあります。
		@~japanese	@details	IStConverterReleasable インターフェースポインターを取得します。IStConverterReleasable で行われる画像処理では、 IStFilterReleasable で行われる画像処理と異なり、ピクセルフォーマットや画像サイズが変化することがあります。
		@~japanese	@param[in] eConverterType	使用するコンバーターのタイプ
		@~japanese	@return	IStConverterReleasable インターフェースポインター
		@~japanese	@attention	取得された IStConverterReleasable インターフェースが不要になったら、 IStConverterReleasable::Release() を呼び出して解放してください。
		@~japanese	@exception	初期化されていない場合、メモリーの割り当てに失敗した場合や引数が不正な場合は、例外 GenICam::GenericException が発生します。
	*/
	ST_API_IP StApi::IStConverterReleasable* ST_API_CALL_TYPE CreateIStConverter(EStConverterType_t eConverterType);
	
	/*!
		@ingroup	StApiIP_PublicImpl
		@~english	@brief	Acquire IStFilterReleasable. IStFilterReleasable is for image processing and statistic. The image format and image size will not be affected by the filter processing.
		@~english	@details	Acquire IStFilterReleasable. IStFilterReleasable is for image processing and statistic. The image format and image size will not be affected by the filter processing.
		@~english	@param[in] eFilterType	Type of filter.
		@~english	@return	IStFilterReleasable pointer.
		@~english	@attention	If the IStFilterReleasable is no longer needed, call IStFilterReleasable::Release() to release it. 
		@~english	@exception	Throw out a GenICam::GenericException when StApi is not initialized or memory allocation is failed.
		@~japanese	@brief	IStFilterReleasable インターフェースポインターを取得します。IStFilterReleasable で行われる画像処理では、 IStConverterReleasable で行われる画像処理と異なり、ピクセルフォーマットや画像サイズが変化しません。
		@~japanese	@details	IStFilterReleasable インターフェースポインターを取得します。IStFilterReleasable で行われる画像処理では、 IStConverterReleasable で行われる画像処理と異なり、ピクセルフォーマットや画像サイズが変化しません。
		@~japanese	@param[in] eFilterType	使用するフィルターのタイプ
		@~japanese	@return	IStFilterReleasable インターフェースポインター
		@~japanese	@attention	取得された IStFilterReleasable インターフェースが不要になったら、 IStFilterReleasable::Release() を呼び出して解放してください。
		@~japanese	@exception	初期化されていない場合、メモリーの割り当てに失敗した場合や引数が不正な場合は、例外 GenICam::GenericException が発生します。
	*/
	ST_API_IP StApi::IStFilterReleasable* ST_API_CALL_TYPE CreateIStFilter(StApi::EStFilterType_t eFilterType);
	
	/*!
		@ingroup	StApiIP_PublicImpl
		@~english	@brief	Acquire IStFilterInfo. IStFilterInfo is used for obtaining the filter's supported pixel format.
		@~english	@details	Acquire IStFilterInfo. IStFilterInfo is used for obtaining the filter's supported pixel format.
		@~english	@param[in] eFilterType	Type of filter.
		@~english	@return	IStFilterInfo pointer.
		@~english	@exception	Throw out a GenICam::GenericException when StApi is not initialized orthere is an invalied parameter.
		@~japanese	@brief	IStFilterInfo インターフェースポインターを取得します。
		@~japanese	@details	IStFilterInfo インターフェースポインターを取得します。
		@~japanese	@param[in] eFilterType	使用するフィルターのタイプ
		@~japanese	@return	IStFilterInfo インターフェースポインター
		@~japanese	@exception	初期化されていない場合や引数が不正な場合は、例外 GenICam::GenericException が発生します。
	*/
	ST_API_IP StApi::IStFilterInfo* ST_API_CALL_TYPE GetIStFilterInfo(StApi::EStFilterType_t eFilterType);

	/*!
		@ingroup	StApiIP_PublicImpl
		@~english	@brief	Acquire IStFilerReleasable. IStFilerReleasable is used for still image or video file creation.
		@~english	@details	Acquire IStFilerReleasable. IStFilerReleasable is used for still image or video file creation.
		@~english	@param[in] eFilerType	Type of filer.
		@~english	@return	IStFilerReleasable pointer.
		@~english	@attention	If the IStFilerReleasable is no longer needed, call IStFilerReleasable::Release() to release it. 
		@~english	@exception	Throw out a GenICam::GenericException when StApi is not initialized or memory allocation is failed.
		@~japanese	@brief	IStFilerReleasable インターフェースポインターを取得します。 IStFilerReleasable インターフェースポインターを使用して静止画ファイルや動画ファイルを生成します。
		@~japanese	@details	IStFilerReleasable インターフェースポインターを取得します。 IStFilerReleasable インターフェースポインターを使用して静止画ファイルや動画ファイルを生成します。
		@~japanese	@param[in] eFilerType	使用するファイラーのタイプ
		@~japanese	@return	IStFilerReleasable インターフェースポインター
		@~japanese	@attention	取得された IStFilerReleasable インターフェースが不要になったら、 IStFilerReleasable::Release() を呼び出して解放してください。
		@~japanese	@exception	初期化されていない場合、メモリーの割り当てに失敗した場合や引数が不正な場合は、例外 GenICam::GenericException が発生します。
	*/
	ST_API_IP StApi::IStFilerReleasable* ST_API_CALL_TYPE CreateIStFiler(EStFilerType_t eFilerType);

	/*!
		@ingroup	StApiIP_PublicImpl
		@~english	@brief	Acquire IStFilterReleasable. IStFilterReleasable is for image processing and statistic. The image format and image size will not be affected by the filter processing.
		@~english	@details	Acquire IStFilterReleasable. IStFilterReleasable is for image processing and statistic. The image format and image size will not be affected by the filter processing.
		@~english	@param[in]	pIStSpecificTypeAllocator	IStSpecificTypeAllocator pointer.
		@~english	@return	IStFilterReleasable pointer.
		@~english	@attention	If the IStFilterReleasable is no longer needed, call IStFilterReleasable::Release() to release it. 
		@~english	@exception	Throw out a GenICam::GenericException when StApi is not initialized or memory allocation is failed.
		@~japanese	@brief	IStFilterReleasable インターフェースポインターを取得します。IStFilterReleasable で行われる画像処理では、 IStConverterReleasable で行われる画像処理と異なり、ピクセルフォーマットや画像サイズが変化しません。
		@~japanese	@details	IStFilterReleasable インターフェースポインターを取得します。IStFilterReleasable で行われる画像処理では、 IStConverterReleasable で行われる画像処理と異なり、ピクセルフォーマットや画像サイズが変化しません。
		@~japanese	@param[in]	pIStSpecificTypeAllocator	IStSpecificTypeAllocator インターフェースポインター
		@~japanese	@return	IStFilterReleasable インターフェースポインター
		@~japanese	@attention	取得された IStFilterReleasable インターフェースが不要になったら、 IStFilterReleasable::Release() を呼び出して解放してください。
		@~japanese	@exception	初期化されていない場合、メモリーの割り当てに失敗した場合や引数が不正な場合は、例外 GenICam::GenericException が発生します。
	*/
	ST_API_IP StApi::IStFilterReleasable* ST_API_CALL_TYPE CreateIStGraphDataFilter(StApi::IStSpecificTypeAllocator *pIStSpecificTypeAllocator = NULL);

	/*!
		@ingroup	StApiIP_PublicImpl
		@~english	@brief	Create object for keeping graph data buffer list and acquire IStGraphDataBufferListResizableReleasable.
		@~english	@details	Create object for keeping graph data buffer list and acquire IStGraphDataBufferListResizableReleasable. Call IStGraphDataBufferListResizableReleasable::Release() to release IStGraphDataBufferListResizableReleasable interface pointer if it is no longer necessary.
		@~english	@param[in] pIStSpecificTypeAllocator	IStSpecificTypeAllocator interface pointer for allocating and releasing memory. If NULL, the buffer memory allocation and deallocation are handled inside the StApi.
		@~english	@return	IStGraphDataBufferListResizableReleasable pointer.
		@~english	@exception	 Throw out a GenICam::GenericException when StApi is not initialized or memory allocation is failed.
		@~english	@sa	 IStSpecificTypeAllocator
		@~japanese	@brief	グラフデータバッファリストを保持するためのオブジェクトを生成し、 IStGraphDataBufferListResizableReleasable インターフェースポインターを取得します。
		@~japanese	@details	グラフデータバッファリストを保持するためのオブジェクトを生成し、 IStGraphDataBufferListResizableReleasable インターフェースポインターを取得します。オブジェクトが不要になったら IStGraphDataBufferListResizableReleasable::Release() を呼び出して解放してください。
		@~japanese	@param[in] pIStSpecificTypeAllocator	IStSpecificTypeAllocator インターフェースポインター。画像保持用メモリーの確保および解放をカスタマイズする際に指定します。NULLが指定された場合は、StApi内部でメモリーの割り当ておよび解放を行います。
		@~japanese	@return	IStGraphDataBufferListResizableReleasable インターフェースポインター
		@~japanese	@exception	初期化されていない場合、メモリーの割り当てに失敗した場合は、例外 GenICam::GenericException が発生します。
		@~japanese	@sa	 IStSpecificTypeAllocator
	*/
	ST_API_IP StApi::IStGraphDataBufferListResizableReleasable* ST_API_CALL_TYPE CreateIStGraphDataBufferListResizable(StApi::IStSpecificTypeAllocator *pIStSpecificTypeAllocator = NULL);

}
#endif //STAPI_IP_FUNCTIONS_H__
