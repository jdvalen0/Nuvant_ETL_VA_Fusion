//------------------------------------------------------------------------------
// StApi
//------------------------------------------------------------------------------
/*!
	@ingroup	StApiTL_PublicInterface
	@file
	@~english	@details	Definition of interface IStPixelFormatInfo
	@~japanese	@details	IStPixelFormatInfo インターフェースの定義
*/
#ifndef ISTPIXELFORMATINFO_H__
#define ISTPIXELFORMATINFO_H__

#include "StApi_Platform.h"

#ifdef _MSC_VER
#pragma warning(push)	
#pragma warning(disable : 4819)	
#include "StApi_PixelFormat.h"
#pragma warning(pop)	
#else
#include "StApi_PixelFormat.h"
#endif

namespace StApi
{
	//---------------------------------------------------------------------
	// interface IStPixelFormatInfo
	//---------------------------------------------------------------------
	/*!
		@ingroup StApiTL_PublicInterface
		@interface IStPixelFormatInfo
		@~english	@brief	Interface for acquiring pixel format related info.
		@~english	@details	Interface for acquiring pixel format related info.
		@~english	@sa	GetIStPixelFormatInfo()
		@~japanese	@brief	ピクセルフォーマット情報用インターフェース
		@~japanese	@details	ピクセルフォーマット情報用インターフェース
		@~japanese	@sa	GetIStPixelFormatInfo()
	*/
	interface PUBLIC_INTERFACE IStPixelFormatInfo
	{
		/*!
			@~english	@brief	Acquire pixel format value.
			@~english	@details	Acquire pixel format value.
			@~english	@return	Acquire pixel format value.
			@~english	@exception	None.
			@~japanese	@brief	ピクセルフォーマット値を取得します。
			@~japanese	@details	ピクセルフォーマット値を取得します。
			@~japanese	@return	ピクセルフォーマット値
			@~japanese	@exception	なし
		*/
		virtual EStPixelFormatNamingConvention_t GetValue() const = 0;

		/*!
			@~english	@brief	Get pixel format name.
			@~english	@details	Get pixel format name.
			@~english	@return	Pixel format name.
			@~english	@exception	None.
			@~japanese	@brief	ピクセルフォーマット名を取得します。
			@~japanese	@details	ピクセルフォーマット名を取得します。
			@~japanese	@return	ピクセルフォーマット名
			@~japanese	@exception	なし
		*/
		virtual GenICam::gcstring GetName() const = 0;

		/*!
			@~english	@brief	Get description of pixel format.
			@~english	@details	Get description of pixel format.
			@~english	@return	Pixel format description.
			@~english	@exception	None.
			@~japanese	@brief	ピクセルフォーマットの説明文を取得します。
			@~japanese	@details	ピクセルフォーマットの説明文を取得します。
			@~japanese	@return	ピクセルフォーマットの説明文
			@~japanese	@exception	なし
		*/
		virtual GenICam::gcstring GetDescription() const = 0;
		
		/*!
			@~english	@brief	Get the total bit counts of each pixel.
			@~english	@details	Get the total bit counts of each pixel.
			@~english	@return	Total bit counts of each pixel.
			@~english	@exception	None.
			@~japanese	@brief	ピクセルごとの合計ビット数を取得します。
			@~japanese	@details	ピクセルごとの合計ビット数を取得します。
			@~japanese	@return	ピクセルごとの合計ビット数
			@~japanese	@exception	なし
		*/
		virtual size_t GetEachPixelTotalBitCount() const = 0;						//ex.BGRA12:64
		
		/*!
			@~english	@brief	Get the total bit counts of each component of a pixel.
			@~english	@details	Get the total bit counts of each component of a pixel.
			@~english	@return	Total bit counts of each component of a pixel.
			@~english	@exception	None.
			@~japanese	@brief	構成要素ごとの全体のビット数を取得します。
			@~japanese	@details	構成要素ごとの全体のビット数を取得します。
			@~japanese	@return	構成要素ごとの全体のビット数
			@~japanese	@exception	なし
		*/
		virtual size_t GetEachComponentTotalBitCount() const = 0;		//ex.BGRA12:16

		/*!
			@~english	@brief	Get the effective bit counts of each component of a pixel.
			@~english	@details	Get the effective bit counts of each component of a pixel.
			@~english	@return	Effective bit counts of each component of a pixel.
			@~english	@exception	None.
			@~japanese	@brief	構成要素ごとの有効なビット数を取得します。
			@~japanese	@details	構成要素ごとの有効なビット数を取得します。
			@~japanese	@return	構成要素ごとの有効なビット数
			@~japanese	@exception	なし
		*/
		virtual size_t GetEachComponentValidBitCount() const = 0;	//ex.BGRA12:12

		/*!
			@~english	@brief	Get the total component counts of a pixel.
			@~english	@details	Get the total component counts of a pixel.
			@~english	@return	Total component counts of a pixel.
			@~english	@exception	None.
			@~japanese	@brief	ピクセルごとの構成要素の数を取得します。
			@~japanese	@details	ピクセルごとの構成要素の数を取得します。
			@~japanese	@return	ピクセルごとの構成要素の数
			@~japanese	@exception	なし
		*/
		virtual size_t GetEachPixelTotalComponentCount() const = 0;		//ex.BGRA12:4

		/*!
			@~english	@brief	Get plane counts.
			@~english	@details	Get plane counts.
			@~english	@return	Plane counts.
			@~english	@exception	None.
			@~japanese	@brief	プレーン数を取得します。
			@~japanese	@details	プレーン数を取得します。
			@~japanese	@return	プレーン数
			@~japanese	@exception	なし
		*/
		virtual size_t GetPlaneCount()  const = 0;

		/*!
			@~english	@brief	Get the minimum unit (in pixel) of image in horizontal.
			@~english	@details	Get the minimum unit (in pixel) of image in horizontal.
			@~english	@return	Minimum unit (in pixel) of image in horizontal.
			@~english	@exception	None.
			@~japanese	@brief	横方向の画像の最小単位を取得します。
			@~japanese	@details	横方向の画像の最小単位を取得します。
			@~japanese	@return	横方向の画像の最小単位
			@~japanese	@exception	なし
		*/
		virtual size_t GetPixelIncrementX() const = 0;					//ex.BGRA12:1

		/*!
			@~english	@brief	Get the minimum unit (in pixel) of image in vertical.
			@~english	@details	Get the minimum unit (in pixel) of image in vertical.
			@~english	@return	Minimum unit (in pixel) of image in vertical.
			@~english	@exception	None.
			@~japanese	@brief	縦方向の画像の最小単位を取得します。
			@~japanese	@details	縦方向の画像の最小単位を取得します。
			@~japanese	@return	縦方向の画像の最小単位
			@~japanese	@exception	なし
		*/
		virtual size_t GetPixelIncrementY() const = 0;					//ex.BGRA12:1

		/*!
			@~english	@brief	Check if the image data contains color information.
			@~english	@details	Check if the image data contains color information.
			@~english	@return	True if the image data contains color information.
			@~english	@exception	None.
			@~japanese	@brief	カラー画像かどうかを確認します。
			@~japanese	@details	カラー画像かどうかを確認します。
			@~japanese	@return	カラー画像の時 true が返されます。
			@~japanese	@exception	なし
		*/
		virtual bool IsColor() const = 0;

		/*!
			@~english	@brief	Check if the image data is monochrome.
			@~english	@details	Check if the image data is monochrome.
			@~english	@return	True if the image data is monochrome.
			@~english	@exception	None.
			@~japanese	@brief	モノクロ画像かどうかを確認します。
			@~japanese	@details	モノクロ画像かどうかを確認します。
			@~japanese	@return	モノクロ画像の時 true が返されます。
			@~japanese	@exception	なし
		*/
		virtual bool IsMono() const = 0;

		/*!
			@~english	@brief	Check if the image data is in Bayer arrangement.
			@~english	@details	Check if the image data is in Bayer arrangement.
			@~english	@return	True if the image data is in Bayer arrangement.
			@~english	@exception	None.
			@~japanese	@brief	ベイヤー配列画像かどうかを確認します。
			@~japanese	@details	ベイヤー配列画像かどうかを確認します。
			@~japanese	@return	ベイヤー配列画像の時 true が返されます。
			@~japanese	@exception	なし
		*/
		virtual bool IsBayer() const = 0;
		
		/*!
			@~english	@brief	Check if the image data is compressed data.
			@~english	@details	Check if the image data is compressed data.
			@~english	@return	True if the image data is compressed.
			@~english	@exception	None.
			@~japanese	@brief	圧縮された画像かどうかを確認します。
			@~japanese	@details	圧縮された画像かどうかを確認します。
			@~japanese	@return	圧縮された画像の時 true が返されます。
			@~japanese	@exception	なし
		*/
		virtual bool IsCompressed()  const = 0;

		/*!
			@~english	@brief	Get pixel color filter (color arrangement data) from a given image position.
			@~english	@details	Get pixel color filter (color arrangement data) from a a given image position.
			@~english	@attention	This function is applicable only to image data with Bayer arrangement.
			@~english	@param[in] x	X-axis offset value(in pixel).
			@~english	@param[in] y	Y-axis offset value(in pixel).
			@~english	@return	Filter arrangement information.
			@~english	@exception	None.
			@~japanese	@brief	指定した位置のカラーフィルターを取得します。
			@~japanese	@details	指定した位置のカラーフィルターを取得します。
			@~japanese	@attention	ベイヤー配列画像時のみ有効な値が取得されます。
			@~japanese	@param[in] x	横方向の位置
			@~japanese	@param[in] y	縦方向の位置
			@~japanese	@return	カラーフィルター
			@~japanese	@exception	なし
		*/
		virtual EStPixelColorFilter_t GetPixelColorFilter(size_t x = 0, size_t y = 0) const = 0;
	};
}
#endif //ISTPIXELFORMATINFO_H__



