//------------------------------------------------------------------------------
// StApi
//------------------------------------------------------------------------------
/*!
	@ingroup	StApiTL_PublicInterface
	@file
	@~english	@details	Definition of interface IStPixelComponentInfo
	@~japanese	@details	IStPixelComponentInfo インターフェースの定義
*/
#ifndef ISTPIXELCOMPONENTINFO_H__
#define ISTPIXELCOMPONENTINFO_H__

#include "StApi_Platform.h"

namespace StApi
{
	//---------------------------------------------------------------------
	// interface IStPixelComponentInfo
	//---------------------------------------------------------------------
	/*!
		@ingroup StApiTL_PublicInterface
		@interface IStPixelComponentInfo
		@~english	@brief	Interface for the pixel component related information.
		@~english	@details	Interface for the pixel component related information.
		@~english	@sa GetIStPixelComponentInfo()
		@~japanese	@brief	ピクセル構成要素情報用インターフェース
		@~japanese	@details	ピクセル構成要素情報用インターフェース
		@~japanese	@sa GetIStPixelComponentInfo()
	*/
	interface PUBLIC_INTERFACE IStPixelComponentInfo
	{
		/*!
			@~english	@brief	Get the value of the pixel component.
			@~english	@details	Get the value of the pixel component.
			@~english	@return	Value of pixel component.
			@~english	@exception	None.
			@~japanese	@brief	ピクセルコンポーネント値を取得します。
			@~japanese	@details	ピクセルコンポーネント値を取得します。
			@~japanese	@return	ピクセルコンポーネント値
			@~japanese	@exception	なし
		*/
		virtual EStPixelComponent_t GetValue() const = 0;

		/*!
			@~english	@brief	Get the name of the pixel component.
			@~english	@details	Get the name of the pixel component.
			@~english	@return	Name of pixel component.
			@~english	@exception	None.
			@~japanese	@brief	構成要素の名前を取得します。
			@~japanese	@details	構成要素の名前を取得します。
			@~japanese	@return	構成要素の名前
			@~japanese	@exception	なし
		*/
		virtual GenICam::gcstring GetName() const = 0;

		/*!
			@~english	@brief	Get the bits count of pixel component.
			@~english	@details	Get the bits count of pixel component.
			@~english	@return	Bits count of pixel component.
			@~english	@exception	None.
			@~japanese	@brief	構成要素のビット数を取得します。
			@~japanese	@details	構成要素のビット数を取得します。
			@~japanese	@return	ビット数
			@~japanese	@exception	なし
		*/
		virtual size_t GetBitCount() const = 0;
	};
}
#endif //ISTPIXELCOMPONENTINFO_H__

