//------------------------------------------------------------------------------
// StApi
//------------------------------------------------------------------------------
/*!
	@ingroup	StApiIP_PublicInterface
	@file
	@~english	@details	Definition of interface IStNoiseReductionFilter
	@~japanese	@details	IStNoiseReductionFilter インターフェースの定義
*/
#ifndef ST_NOISE_REDUCTION_FILTER_H
#define ST_NOISE_REDUCTION_FILTER_H

#include "IStFilter.h"

namespace StApi
{
	// ---------------------------------------------------------------------
	// interface IStNoiseReductionFilter
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiIP_PublicInterface
		@interface IStNoiseReductionFilter
		@~english	@brief	Interface for Noise Reduction Filter.
		@~english	@details	Interface for Noise Reduction Filter.
		@sa	CreateIStFilter(), GetIStFilterInfo()
		@~japanese	@brief	 ノイズ軽減フィルター用インターフェース
		@~japanese	@details	ノイズ軽減フィルター用インターフェース
		@sa	CreateIStFilter(), GetIStFilterInfo()
	*/
	interface PUBLIC_INTERFACE IStNoiseReductionFilter : public IStFilter
	{
		/*!
			@~english	@brief	Acquire noise reduction mode.
			@~english	@details	Acquire noise reduction mode.
			@~english	@return	Noise reduction mode.
			@~english	@exception	None.
			@~japanese	@brief	 ノイズ軽減モードを取得します。
			@~japanese	@details	ノイズ軽減モードを取得します。
			@~japanese	@return	ノイズ軽減モード
			@~japanese	@exception	なし
		*/
		virtual EStNoiseReductionMode_t GetNoiseReductionMode() const = 0;
		
		/*!
			@~english	@brief	Set noise reduction mode.
			@~english	@details	Set noise reduction mode.
			@~english	@param[in]	eNRM	Noise reduction mode.
			@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument. 
			@~japanese	@brief	 ノイズ軽減モードを設定します。
			@~japanese	@details	ノイズ軽減モードを設定します。
			@~japanese	@param[in]	eNRM	ノイズ軽減モード
			@~japanese	@exception	不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void SetNoiseReductionMode(EStNoiseReductionMode_t eNRM) = 0;

		/*!
			@~english	@brief	Check if calibration is enabled.
			@~english	@details	Check if calibration is enabled.
			@~english	@return	Return true if it is enabled.
			@~english	@exception	None.
			@~japanese	@brief	 キャリブレーションの有効/無効を取得します。
			@~japanese	@details	キャリブレーションの有効/無効を取得します。
			@~japanese	@return	キャリブレーションが有効な場合、 true を返します。
			@~japanese	@exception	なし
		*/
		virtual bool GetCalibrationEnable() const = 0;

		/*!
			@~english	@brief	Enable/disable calibration.
			@~english	@details	Enable/disable calibration.
			@~english	@param[in]	value	True to enable; false to disable.
			@~english	@exception	None.
			@~japanese	@brief	 キャリブレーションの有効/無効を設定します。
			@~japanese	@details	キャリブレーションの有効/無効を設定します。有効に設定している間に与えられた画像データをもとに補正値を算出します。無効に設定されると、補正値をもとに補正を行います。
			@~japanese	@param[in]	value	キャリブレーションを有効へ設定する場合は、 true を指定します。
			@~japanese	@exception	なし
		*/
		virtual void SetCalibrationEnable(bool value) = 0;
	};

	//---------------------------------------------------------------------
	// typedef CIStNoiseReductionFilterPtr
	//---------------------------------------------------------------------
	/*!
		@ingroup StApiIP_PublicImpl
		@typedef CIStNoiseReductionFilterPtr
		@~english	@brief	 The auto management class of IStNoiseReductionFilter class for noise reduction filter.
		@~english	@details	 The auto management class of IStNoiseReductionFilter class for noise reduction filter.Use this class instead of managing the initial/release of IStNoiseReductionFilter class yourself. The destructor of this class will automatically call IStFilterReleasable::Release().
		@sa	CreateIStFilter(), GetIStFilterInfo()
		@~japanese	@brief	 ノイズ軽減フィルター用インターフェースポインターの自動管理用クラスです。
		@~japanese	@details	ノイズ軽減フィルター用インターフェースポインターの自動管理用クラスです。このクラスのデストラクタから IStFilterReleasable::Release() が自動的に呼び出されます。
		@sa	CreateIStFilter(), GetIStFilterInfo()
	*/
	typedef CStAutoPtr<IStFilterReleasable, IStNoiseReductionFilter> CIStNoiseReductionFilterPtr;
}
#endif //ST_NOISE_REDUCTION_FILTER_H



