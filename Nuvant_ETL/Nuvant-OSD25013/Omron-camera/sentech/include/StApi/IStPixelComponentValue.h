//------------------------------------------------------------------------------
// StApi
//------------------------------------------------------------------------------
/*!
	@ingroup	StApiTL_PublicInterface
	@file
	@~english	@details	Definition of interface IStPixelComponentValue
	@~japanese	@details	IStPixelComponentValue インターフェースの定義
*/
#ifndef ISTPIXELCOMPONENTVALUE_H__
#define ISTPIXELCOMPONENTVALUE_H__

#include "IStPixelComponentInfo.h"

namespace StApi
{
	//---------------------------------------------------------------------
	// interface IStPixelComponentValue
	//---------------------------------------------------------------------
	/*!
		@ingroup StApiTL_PublicInterface
		@interface IStPixelComponentValue
		@~english	@brief	Interface to access pixel component.
		@~english	@details	Interface to access pixel component.
		@~japanese	@brief	ピクセル構成要素用インターフェース
		@~japanese	@details	ピクセル構成要素用インターフェース
	*/
	interface PUBLIC_INTERFACE IStPixelComponentValue
	{
		/*!
			@~english	@brief	Get the number of pixel component.
			@~english	@details	Get the number of pixel component.
			@~english	@return	Number of pixel component.
			@~english	@exception	None.
			@~japanese	@brief	ピクセル構成要素数を取得します。
			@~japanese	@details	ピクセル構成要素数を取得します。
			@~japanese	@return	ピクセル構成要素数
			@~japanese	@exception	なし
		*/
		virtual size_t GetCount() const = 0;
		
		/*!
			@~english	@brief	Get pixel data of the pixel component.
			@~english	@details	Get pixel data of the pixel component.
			@~english	@param[in]	nIndex	Index of the pixel component.
			@~english	@return	Pixel data of the pixel component.
			@~english	@exception	Throw GenICam::GenericException if the index value is not correct.
			@~japanese	@brief	画素値を取得します。
			@~japanese	@details	画素値を取得します。
			@~japanese	@param[in]	nIndex	構成要素のインディックス値
			@~japanese	@return	画素値
			@~japanese	@exception	不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual int64_t GetValue(size_t nIndex) const = 0;

		/*!
			@~english	@brief	Pixel value of the pixel component.
			@~english	@details	Pixel value of the pixel component.
			@~english	@param[in]	nIndex	Index of the pixel component.
			@~english	@return	Pixel value of the pixel component.
			@~english	@exception	Throw GenICam::GenericException if the index value is not correct.
			@~japanese	@brief	ピクセル構成要素値を取得します。
			@~japanese	@details	ピクセル構成要素値を取得します。
			@~japanese	@param[in]	nIndex	構成要素のインディックス値
			@~japanese	@return	ピクセル構成要素値
			@~japanese	@exception	不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual EStPixelComponent_t GetPixelComponent(size_t nIndex) const = 0;
	};
}
#endif //ISTPIXELCOMPONENTVALUE_H__

