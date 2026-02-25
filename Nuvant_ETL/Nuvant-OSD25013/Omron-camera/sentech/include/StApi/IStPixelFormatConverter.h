//------------------------------------------------------------------------------
// StApi
//------------------------------------------------------------------------------
/*!
	@ingroup	StApiIP_PublicInterface
	@file
	@~english	@details	Definition of interface IStPixelFormatConverter
	@~japanese	@details	IStPixelFormatConverter インターフェースの定義
*/
#ifndef STPIXELFORMATCONVERTER_H
#define STPIXELFORMATCONVERTER_H

#include "IStConverter.h"

namespace StApi
{

	interface IStImage;

	// ---------------------------------------------------------------------
	// interface IStPixelFormatConverter
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiIP_PublicInterface
		@interface IStPixelFormatConverter
		@~english	@brief	Interface for Pixel Format Converter.
		@~english	@details	Interface for Pixel Format Converter.
		@sa	CreateIStConverter()
		@~japanese	@brief	ピクセルフォーマットコンバーター用インターフェース
		@~japanese	@details	ピクセルフォーマットコンバーター用インターフェース
		@sa	CreateIStConverter()
	*/
	interface PUBLIC_INTERFACE IStPixelFormatConverter : public IStConverter
	{
		/*!
			@~english	@brief	Acquire the pixel format of conversion target.
			@~english	@details	Acquire the pixel format of conversion target.
			@~english	@return	Pixel format.
			@~english	@exception	None.
			@~japanese	@brief	変換先のピクセルフォーマット値を取得します。
			@~japanese	@details	変換先のピクセルフォーマット値を取得します。
			@~japanese	@return	変換先のピクセルフォーマット値
			@~japanese	@exception	なし
		*/
		virtual EStPixelFormatNamingConvention_t GetDestinationPixelFormat() const = 0;

		/*!
			@~english	@brief	Set the pixel format of conversion target.
			@~english	@details	Set the pixel format of conversion target.
			@~english	@param[in]	ePFNC	Pixel format.
			@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument. 
			@~japanese	@brief	変換先のピクセルフォーマット値を設定します。
			@~japanese	@details	変換先のピクセルフォーマット値を設定します。
			@~japanese	@param[in]	ePFNC	変換先のピクセルフォーマット値
			@~japanese	@exception	不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void SetDestinationPixelFormat(EStPixelFormatNamingConvention_t ePFNC) = 0;

		/*!
			@~english	@brief	Acquire the setting of Y-axis reversion.
			@~english	@details	Acquire the setting of Y-axis reversion.
			@~english	@return	Y-axis reversion setting.
			@~english	@exception	None.
			@~japanese	@brief	上下反転設定を取得します。
			@~japanese	@details	上下反転設定を取得します。
			@~japanese	@return	上下反転が有効な場合、 true を返します。
			@~japanese	@exception	なし
		*/
		virtual bool GetReverseY() const = 0;

		/*!
			@~english	@brief	Set the setting of Y-axis reversion.
			@~english	@details	Set the setting of Y-axis reversion.
			@~english	@attention	This function may not work on some pixel format. If the image is in Bayer pixel format, the output image format will be changed during the conversion.
			@~english	@param[in]	value	True to apply Y-axis reversion.
			@~english	@exception	None.
			@~japanese	@brief	上下反転を設定します。
			@~japanese	@details	上下反転を設定します。
			@~japanese	@attention	ピクセルフォーマットによっては、機能しないことがあります。また、上下反転を有効にした状態でベイヤー形式の画像を入力した場合、出力される画像のフォーマットが変化する場合があります。
			@~japanese	@param[in]	value	上下反転を行う場合、 true を指定します。
			@~japanese	@exception	なし
		*/
		virtual void SetReverseY(bool value) = 0;

		/*!
			@~english	@brief	Get the current Bayer interpolation method.
			@~english	@details	Get the current Bayer interpolation method.
			@~english	@return	Bayer interpolation method.
			@~english	@exception	None.
			@~japanese	@brief	ベイヤー変換処理設定を取得します。
			@~japanese	@details	ベイヤー変換処理設定を取得します。
			@~japanese	@return	ベイヤー変換処理設定
			@~japanese	@exception	なし
		*/
		virtual EStBayerInterpolationMethod_t GetBayerInterpolationMethod() const = 0;

		/*!
			@~english	@brief	Set the Bayer interpolation method.
			@~english	@details	Set the Bayer interpolation method.
			@~english	@attention	This setting only takes effect on image with Bayer pixel format.
			@~english	@param[in]	eBIM	Bayer interpolation method.
			@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument.
			@~japanese	@brief	ベイヤー変換処理を設定します。
			@~japanese	@details	ベイヤー変換処理を設定します。
			@~japanese	@attention	この設定はベイヤー配列の入力画像にのみ有効になります。
			@~japanese	@param[in]	eBIM	ベイヤー変換処理設定 
			@~japanese	@exception	不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void SetBayerInterpolationMethod(EStBayerInterpolationMethod_t eBIM) = 0;

		/*!
			@~english	@brief	Get the Gamma value of conversion.
			@~english	@details	Get the Gamma value of conversion.
			@~english	@return	Gamma value.
			@~english	@exception	None.
			@~japanese	@brief	ガンマ補正値を取得します。
			@~japanese	@details	ガンマ補正値を取得します。
			@~japanese	@return	ガンマ補正値
			@~japanese	@exception	なし
		*/
		virtual double GetGammaValue() const = 0;

		/*!
			@~english	@brief	Set the Gamma value of conversion.
			@~english	@details	Set the Gamma value of conversion.
			@~english	@attention	This setting only takes effect on image with changing bit during the conversion.
			@~english	@param[in]	value	Gamma value(0 ~ 4.0).
			@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument. 
			@~japanese	@brief	ガンマ補正値を設定します。
			@~japanese	@details	ガンマ補正値を設定します。
			@~japanese	@attention	この設定は変換時にビット数が変化する場合のみ有効になります。
			@~japanese	@param[in]	value	ガンマ補正値(0.0～4.0)
			@~japanese	@exception	不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void SetGammaValue(double value) = 0;

		/*!
			@~english	@brief	Acquire current status of target pixel format node lock.
			@~english	@details	Acquire current status of target pixel format node lock.
			@~english	@return	Lock status. True if locked; false otherwise.
			@~english	@exception	None.
			@~japanese	@brief	変換先のピクセルフォーマットノードのロック状態を取得します。
			@~japanese	@details	変換先のピクセルフォーマットノードのロック状態を取得します。
			@~japanese	@return	変換先のピクセルフォーマットノードがロックされている場合、 true が返されます。
			@~japanese	@exception	なし
		*/
		virtual bool GetDestinationPixelFormatNodeLock() const = 0;
		
		/*!
			@~english	@brief	Set target pixel format node lock. This will prevent the pixel format modification from GUI.
			@~english	@details	Set target pixel format node lock. This will prevent the pixel format modification from GUI.
			@~english	@param[in]	value	True to lock; false to unlock.
			@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument. 
			@~japanese	@brief	変換先のピクセルフォーマットノードのロック状態を設定します。
			@~japanese	@details	変換先のピクセルフォーマットノードのロック状態を設定します。
			@~japanese	@param[in]	value	変換先のピクセルフォーマットノードをロックする場合、 true を指定します。
			@~japanese	@exception	不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void SetDestinationPixelFormatNodeLock(bool value) = 0;
	};


	//---------------------------------------------------------------------
	// typedef CIStPixelFormatConverterPtr
	//---------------------------------------------------------------------
	/*!
		@ingroup StApiIP_PublicImpl
		@typedef CIStPixelFormatConverterPtr
		@~english	@brief	The auto management class of IStConverterReleasable class for pixel format conversions.
		@~english	@details	The auto management class of IStConverterReleasable class for pixel format conversions.Use this class instead of managing the initial/release of IStConverterReleasable class yourself. The destructor of this class will automatically call IStConverterReleasable::Release().
		@sa	CreateIStConverter()
		@~japanese	@brief	ピクセルフォーマットコンバーター用インターフェースポインターの自動管理用クラスです。
		@~japanese	@details	ピクセルフォーマットコンバーター用インターフェースポインターの自動管理用クラスです。このクラスのデストラクタから IStConverterReleasable::Release() が自動的に呼び出されます。
		@sa	CreateIStConverter()
	*/
	typedef CStAutoPtr<IStConverterReleasable, IStPixelFormatConverter> CIStPixelFormatConverterPtr;
}
#endif //STPIXELFORMATCONVERTER_H
