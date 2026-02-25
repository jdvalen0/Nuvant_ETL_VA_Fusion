//------------------------------------------------------------------------------
//  StApi
//------------------------------------------------------------------------------
/*!
	@ingroup	StApiIP_PublicInterface
	@file
	@~english	@details	Definition of interface IStFlatFieldCorrectionFilter
	@~japanese	@details	IStFlatFieldCorrectionFilter インターフェースの定義
*/
#ifndef ST_FLAT_FIELD_CORRECTION_FILTER_H
#define ST_FLAT_FIELD_CORRECTION_FILTER_H

#include "IStFilter.h"

namespace StApi
{
	// ---------------------------------------------------------------------
	// interface IStFlatFieldCorrectionFilter
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiIP_PublicInterface
		@interface IStFlatFieldCorrectionFilter
		@~english	@brief	Interface for Field FlatCorrection Filter.
		@~english	@details	Interface for Field FlatCorrection Filter.
		@sa	CreateIStFilter(), GetIStFilterInfo()
		@~japanese	@brief	フラットフィールド補正フィルター用インターフェース
		@~japanese	@details	フラットフィールド補正フィルター用インターフェース
		@sa	CreateIStFilter(), GetIStFilterInfo()
	*/
	interface PUBLIC_INTERFACE IStFlatFieldCorrectionFilter : public IStFilter
	{
		/*!
			@~english	@brief	Acquire FFC mode setting.
			@~english	@details	Acquire FFC mode setting.
			@~english	@return	FFC mode.
			@~english	@exception	None.
			@~japanese	@brief	FFCモードを取得します。
			@~japanese	@details	FFCモードを取得します。
			@~japanese	@return	FFCモード
			@~japanese	@exception	なし
		*/
		virtual EStFlatFieldCorrectionMode_t GetFlatFieldCorrectionMode() const = 0;
		
		/*!
			@~english	@brief	Set FFC mode.
			@~english	@details	Set FFC mode.
			@~english	@param[in]	eFFCM FFC mode.
			@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument. 
			@~japanese	@brief	FFCモードを設定します。
			@~japanese	@details	FFCモードを設定します。
			@~japanese	@param[in]	eFFCM FFCモード
			@~japanese	@exception	不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void SetFlatFieldCorrectionMode(EStFlatFieldCorrectionMode_t eFFCM) = 0;

		/*!
			@~english	@brief	Acquire calibration function status.
			@~english	@details	Acquire calibration function status.
			@~english	@return	Return true if calibration is enabled.
			@~english	@exception	None.
			@~japanese	@brief	キャリブレーションの有効/無効を取得します。
			@~japanese	@details	キャリブレーションの有効/無効を取得します。
			@~japanese	@return	キャリブレーションが有効な場合、 true を返します。
			@~japanese	@exception	なし
		*/
		virtual bool GetCalibrationEnable() const = 0;
		
		/*!
			@~english	@brief	Set calibration function enable/disable.
			@~english	@details	Set calibration function enable/disable.
			@~english	@param[in]	value	Set true to enable calibration or set false to disable.
			@~english	@exception	None.
			@~japanese	@brief	キャリブレーションの有効/無効を設定します。
			@~japanese	@details	キャリブレーションの有効/無効を設定します。有効に設定している間に与えられた画像データをもとに補正値を算出します。無効に設定されると、補正値をもとに補正を行います。
			@~japanese	@param[in]	value	キャリブレーションを有効へ設定する場合は、 true を指定します。
			@~japanese	@exception	なし
		*/
		virtual void SetCalibrationEnable(bool value) = 0;

		/*!
			@~english	@brief	Get calibration target value.
			@~english	@details	Get calibration target value.
			@~english	@return	Calibration target value.
			@~english	@exception	None.
			@~japanese	@brief	キャリブレーション時の目標値を取得します。
			@~japanese	@details	キャリブレーション時の目標値を取得します。
			@~japanese	@return	キャリブレーション時の目標値
			@~japanese	@exception	なし
		*/
		virtual uint32_t GetCalibrationTargetValue() const = 0;

		/*!
			@~english	@brief	Set calibration target value.
			@~english	@details	Set calibration target value.
			@~english	@param[in]	value	Calibration target value(0 ~ 65535).
			@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument. 
			@~japanese	@brief	キャリブレーション時の目標値を設定します。
			@~japanese	@details	キャリブレーション時の目標値を設定します。
			@~japanese	@param[in]	value	キャリブレーション時の目標値(0～65535)
			@~japanese	@exception	不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void SetCalibrationTargetValue(uint32_t value) = 0;
	};

	//---------------------------------------------------------------------
	// typedef CIStFlatFieldCorrectionFilterPtr
	//---------------------------------------------------------------------
	/*!
		@ingroup StApiIP_PublicImpl
		@typedef CIStFlatFieldCorrectionFilterPtr
		@~english	@brief	The auto management class of IStFlatFieldCorrectionFilter class.
		@~english	@details	The auto management class of IStFlatFieldCorrectionFilter class.Use this class instead of managing the initial/release of IStFlatFieldCorrectionFilter class yourself. The destructor of this class will automatically call IStFilterReleasable::Release().
		@sa	CreateIStFilter(), GetIStFilterInfo()
		@~japanese	@brief	フラットフィールド補正フィルター用インターフェースポインターの自動管理用クラスです。
		@~japanese	@details	フラットフィールド補正フィルター用インターフェースポインターの自動管理用クラスです。このクラスのデストラクタから IStFilterReleasable::Release() が自動的に呼び出されます。
		@sa	CreateIStFilter(), GetIStFilterInfo()
	*/
	typedef CStAutoPtr<IStFilterReleasable, IStFlatFieldCorrectionFilter> CIStFlatFieldCorrectionFilterPtr;
}
#endif //ST_FLAT_FIELD_CORRECTION_FILTER_H
