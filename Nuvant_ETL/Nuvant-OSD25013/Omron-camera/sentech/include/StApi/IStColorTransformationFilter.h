//------------------------------------------------------------------------------
//  StApi
//------------------------------------------------------------------------------
/*!
	@ingroup	StApiIP_PublicInterface
	@file	
	@~english	@details	Definition of interface IStColorTransformationFilter
	@~japanese	@details	IStColorTransformationFilter インターフェースの定義
*/
#ifndef STCOLORCORRECTION_H
#define STCOLORCORRECTION_H

#include "IStFilter.h"

namespace StApi
{
	interface IStImage;

	// ---------------------------------------------------------------------
	// interface IStColorTransformationFilter
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiIP_PublicInterface
		@interface IStColorTransformationFilter
		@~english	@brief	Interface for Color Transformation Filter.
		@~english	@details	Interface for Color Transformation Filter.
		@sa	CreateIStFilter(), GetIStFilterInfo()
		@~japanese	@brief	色変換フィルター用インターフェース
		@~japanese	@details	色変換フィルター用インターフェース
		@sa	CreateIStFilter(), GetIStFilterInfo()
	*/
	interface PUBLIC_INTERFACE IStColorTransformationFilter : public IStFilter
	{
		/*!
			@~english	@brief	Acquire current setting of color transformation.
			@~english	@details	Acquire current setting of color transformation.
			@~english	@return	True/false for current setting.
			@~english	@exception	None.
			@~japanese	@brief	色変換処理の有効/無効を取得します。
			@~japanese	@details	色変換処理の有効/無効を取得します。
			@~japanese	@return	有効な時 true が返されます。
			@~japanese	@exception	なし
		*/
		virtual bool GetColorTransformationEnable() const = 0;
		
		/*!
			@~english	@brief	Enable/disable the color transformation function.
			@~english	@details	Enable/disable the color transformation function.
			@~english	@param[in]	value	True/false for current setting.
			@~english	@exception	None.
			@~japanese	@brief	色変換処理の有効/無効を設定します。
			@~japanese	@details	色変換処理の有効/無効を設定します。
			@~japanese	@param[in]	value	有効にする場合、 true を指定します。
			@~japanese	@exception	なし
		*/
		virtual void SetColorTransformationEnable(bool value) = 0;

		/*!
			@~english	@brief	Acquire the parameter of color transformation of target.
			@~english	@details	Acquire the parameter of color transformation of target.
			@~english	@param[in] eCTVS	Type of the setting.
			@~english	@return	Color conversion matrix value.
			@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument.
			@~japanese	@brief	色変換行列の値を取得します。
			@~japanese	@details	色変換行列の値を取得します。
			@~japanese	@param[in] eCTVS	対象とする行列の要素を指定します。
			@~japanese	@return	色変換行列値
			@~japanese	@exception	不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual double GetColorTransformationValue(EStColorTransformationValueSelector_t eCTVS) const = 0;

		/*!
			@~english	@brief	Set the parameter of color transformation to target.
			@~english	@details	Set the parameter of color transformation to target.
			@~english	@param[in] eCTVS	Parameter for setting.
			@~english	@param[in]	value	Color conversion matrix value.
			@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument.
			@~japanese	@brief	色変換行列の値を設定します。
			@~japanese	@details	色変換行列の値を設定します。
			@~japanese	@param[in] eCTVS	対象とする行列の要素を指定します。
			@~japanese	@param[in]	value	色変換行列値(ゲイン値:-16.0～16.0, オフセット値:-65535～65535)
			@~japanese	@exception	不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void SetColorTransformationValue(EStColorTransformationValueSelector_t eCTVS, double value) = 0;

		/*!
			@~english	@brief	Acquire the correction value of hue.
			@~english	@details	Acquire the correction value of hue.
			@~english	@return	Current correction value.
			@~english	@exception	None.
			@~japanese	@brief	色相の補正値を取得します。
			@~japanese	@details	色相の補正値を取得します。
			@~japanese	@return	補正値
			@~japanese	@exception	なし
		*/
		virtual double GetHueCorrection() const = 0;

		/*!
			@~english	@brief	Set the correction value to hue.
			@~english	@details	Set the correction value to hue.
			@~english	@param[in]	value	Correction value (-180.0 ~ +180.0).
			@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument.
			@~japanese	@brief	色相の補正値を設定します。
			@~japanese	@details	色相の補正値を設定します。
			@~japanese	@param[in]	value	補正値(-180.0～180.0)
			@~japanese	@exception	不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void SetHueCorrection(double value) = 0;

		/*!
			@~english	@brief	Acquire the correction value of saturation.
			@~english	@details	Acquire the correction value of saturation.
			@~english	@return	Current correction value.
			@~english	@exception	None.
			@~japanese	@brief	彩度の補正値を取得します。
			@~japanese	@details	彩度の補正値を取得します。
			@~japanese	@return	補正値
			@~japanese	@exception	なし
		*/
		virtual double GetSaturationCorrection() const = 0;

		/*!
			@~english	@brief	Set the correction value to saturation.
			@~english	@details	Set the correction value to saturation.
			@~english	@param[in]	value	Correction value (0.0 ~ 4.0).
			@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument.
			@~japanese	@brief	彩度の補正値を設定します。
			@~japanese	@details	彩度の補正値を設定します。
			@~japanese	@param[in]	value	補正値(0.0～4.0)
			@~japanese	@exception	不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void SetSaturationCorrection(double value) = 0;
	};

	//---------------------------------------------------------------------
	// typedef CIStColorTransformationFilterPtr
	//---------------------------------------------------------------------
	/*!
		@ingroup StApiIP_PublicImpl
		@typedef CIStColorTransformationFilterPtr
		@~english	@brief	The auto management class of IStColorTransformationFilter class for color transformation.
		@~english	@details	The auto management class of IStColorTransformationFilter class for color transformation.Use this class instead of managing the initial/release of IStColorTransformationFilter class yourself. The destructor of this class will automatically call IStFilterReleasable::Release().
		@sa	CreateIStFilter(), GetIStFilterInfo()
		@~japanese	@brief	色変換フィルター用インターフェースポインターの自動管理用クラスです。
		@~japanese	@details	色変換フィルター用インターフェースポインターの自動管理用クラスです。このクラスのデストラクタから IStFilterReleasable::Release() が自動的に呼び出されます。
		@sa	CreateIStFilter(), GetIStFilterInfo()
	*/
	typedef CStAutoPtr<IStFilterReleasable, IStColorTransformationFilter> CIStColorTransformationFilterPtr;
}
#endif //STCOLORCORRECTION_H



