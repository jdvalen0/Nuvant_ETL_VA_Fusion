//------------------------------------------------------------------------------
//  StApi
//------------------------------------------------------------------------------
/*!
	@ingroup	StApiTL_PublicInterface
	@file
	@~english	@details	Definition of interface IStImage
	@~japanese	@details	IStImage インターフェースの定義
*/
#ifndef ISTIMAGE_H__
#define ISTIMAGE_H__

#include "IStPixelFormatInfo.h"
#include "IStPixelComponentValue.h"

namespace StApi
{
	//---------------------------------------------------------------------
	// interface IStImage
	//---------------------------------------------------------------------
	/*!
		@ingroup StApiTL_PublicInterface
		@interface IStImage
		@~english	@brief	Interface for Image object.
		@~english	@details	Interface for Image object.
		@~japanese	@brief	画像用インターフェース
		@~japanese	@details	画像用インターフェース
	*/
	interface PUBLIC_INTERFACE IStImage
	{
		/*!
			@~english	@brief	Acquire the width of the image.
			@~english	@details	Acquire the width of the image.
			@~english	@return	Width of the image.
			@~english	@exception	None.
			@~japanese	@brief	画像の横サイズを取得します。
			@~japanese	@details	画像の横サイズを取得します。
			@~japanese	@return	画像の横サイズ
			@~japanese	@exception	なし
		*/
		virtual size_t GetImageWidth() const = 0;

		/*!
			@~english	@brief	Acquire the height of the image.
			@~english	@details	Acquire the height of the image.
			@~english	@return	Height of the image.
			@~english	@exception	None.
			@~japanese	@brief	画像の縦サイズを取得します。
			@~japanese	@details	画像の縦サイズを取得します。
			@~japanese	@return	画像の縦サイズ
			@~japanese	@exception	なし
		*/
		virtual size_t GetImageHeight() const = 0;

		/*!
			@~english	@brief	Acquire the line pitch (numbers of bytes within one line) of the image.
			@~english	@details	Acquire the line pitch (numbers of bytes within one line) of the image.
			@~english	@return	Line pitch of the image.
			@~english	@exception	None.
			@~japanese	@brief	画像のラインピッチ(1ライン当たりのバイト数)を取得します。
			@~japanese	@details	画像のラインピッチ(1ライン当たりのバイト数)を取得します。
			@~japanese	@return	画像のラインピッチ
			@~japanese	@exception	なし
		*/
		virtual size_t GetImageLinePitch() const = 0;

		/*!
			@~english	@brief	Acquire the image plane pitch (numbers of bytes within one plane).
			@~english	@details	Acquire the image plane pitch (numbers of bytes within one plane).
			@~english	@return	Plane pitch of the image.
			@~english	@exception	None.
			@~japanese	@brief	画像のプレーンあたりのバイト数を取得します。
			@~japanese	@details	画像のプレーンあたりのバイト数を取得します。
			@~japanese	@return	画像のプレーンピッチ
			@~japanese	@exception	なし
		*/
		virtual size_t GetImagePlanePitch() const = 0;

		/*!
			@~english	@brief	Acquire the pixel format of the image.
			@~english	@details	Acquire the pixel format of the image.
			@~english	@return	Pixel format of the image.
			@~english	@exception	None.
			@~japanese	@brief	画像のピクセルフォーマットを取得します。
			@~japanese	@details	画像のピクセルフォーマットを取得します。
			@~japanese	@return	画像のピクセルフォーマット
			@~japanese	@exception	なし
		*/
		virtual EStPixelFormatNamingConvention_t GetImagePixelFormat() const = 0;

		/*!
			@~english	@brief	Acquire the buffer address of the image.
			@~english	@details	Acquire the buffer address of the image.
			@~english	@return	Buffer address of the image.
			@~english	@exception	None.
			@~japanese	@brief	画像バッファーのアドレスを取得します。
			@~japanese	@details	画像バッファーのアドレスを取得します。
			@~japanese	@return	画像バッファーのアドレス
			@~japanese	@exception	なし
		*/
		virtual void* GetImageBuffer() const = 0;

		/*!
			@~english	@brief	Get user context.
			@~english	@details	Get user context.
			@~english	@return	Return user context pointer. If there is no user context data, return NULL.
			@~english	@exception	None.
			@~japanese	@brief	ユーザー用データポインターを取得します。
			@~japanese	@details	ユーザー用データポインターを取得します。
			@~japanese	@return	ユーザー用データポインター。指定されていない場合は、NULLが返されます。
			@~japanese	@exception	なし
		*/
		virtual void* GetUserContext() const = 0;

		/*!
			@~english	@brief	Acquire ROI data from the image data.
			@~english	@details	Acquire ROI data of from the image data. The ROI data will be acquired as a IStImage interface pointer. If the original IStImage is updated or GetROIImage is called again, the acquired ROI area image data will become invalid.
			@~english	@param[in]	x	Horizontal offset of the image.
			@~english	@param[in]	y	Vertical offset of the image.
			@~english	@param[in]	width	Width of the ROI image.
			@~english	@param[in]	height	Height of the ROI image.
			@~english	@return	IStImage interface pointer.
			@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument. 
			@~japanese	@brief	切り取った画像用の IStImage インターフェースポインターを取得します。
			@~japanese	@details	切り取った画像用の IStImage インターフェースポインターを取得します。 データのコピーは行われず、元のデータが参照されます。そのため、元の画像が変化したり、再度この関数が呼び出された場合は、以前取得された IStImage は無効になります。
			@~japanese	@param[in]	x	横方向のオフセット値
			@~japanese	@param[in]	y	縦方向のオフセット値
			@~japanese	@param[in]	width	ROI画像の横サイズ
			@~japanese	@param[in]	height	ROI画像の縦サイズ
			@~japanese	 @return	IStImage インターフェースポインター
			@~japanese	@exception	不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual IStImage *GetROIImage(size_t x, size_t y, size_t width, size_t height) = 0;

		/*!
			@~english	@brief	Acquire pixel information.
			@~english	@details	Acquire pixel information.
			@~english	@param[in]	x	Horizontal poisition of the image.
			@~english	@param[in]	y	Vertical poisition of the image.
			@~english	@return	IStPixelComponentValue interface pointer.
            @~english   @attention  When this function is called, the return value from IStPixelComponentValue interface pointer will change. The acquired IStPixelComponentValue interface pointer will be invalid if the original image is discarded.
			@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument. 
			@~japanese	@brief	指定した位置の画素情報を取得します。
			@~japanese	@details	指定した位置の画素情報を取得します。
			@~japanese	@param[in]	x	横方向の位置
			@~japanese	@param[in]	y	縦方向の位置
			@~japanese	@return	IStPixelComponentValue インターフェースポインター
			@~japanese	@attention	再度この関数が呼び出されると、 IStPixelComponentValue インターフェースポインターを使用して得られる値が変化します。取得された IStPixelComponentValue インターフェースポインターは元の画像が破棄されると無効になります。
			@~japanese	@exception	不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual IStPixelComponentValue *GetIStPixelComponentValue(size_t x, size_t y) = 0;
	};
}
#endif //ISTIMAGE_H__

