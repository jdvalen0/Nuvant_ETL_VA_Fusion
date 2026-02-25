//------------------------------------------------------------------------------
//  StApi
//------------------------------------------------------------------------------
/*!
	@ingroup	StApiIP_PublicInterface
	@file	
	@~english	@details	Definition of interface IStChromaSuppressionFilter
	@~japanese	@details	IStChromaSuppressionFilter インターフェースの定義
*/
#ifndef ST_CHROMA_SUPPRESSION_FILTER_H
#define ST_CHROMA_SUPPRESSION_FILTER_H

#include "IStFilter.h"

namespace StApi
{

	// ---------------------------------------------------------------------
	// interface IStChromaSuppressionFilter
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiIP_PublicInterface
		@interface IStChromaSuppressionFilter
		@~english	@brief	Interface for Chroma Suppression Filter.
		@~english	@details	Interface for Chroma Suppression Filter.
		@sa	CreateIStFilter(), GetIStFilterInfo()
		@~japanese	@brief	クロマサプレスフィルター用インターフェース
		@~japanese	@details	クロマサプレスフィルター用インターフェース
		@sa	CreateIStFilter(), GetIStFilterInfo()
	*/
	interface PUBLIC_INTERFACE IStChromaSuppressionFilter : public IStFilter
	{
		/*!
			@~english	@brief	Acquire the threshold value of chroma suppression activate.
			@~english	@details	Acquire the threshold value of chroma suppression activate.
			@~english	@param[in] eCSPS	The target of eCSPS.
			@~english	@return	Value of threshold.
			@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument.
			@~japanese	@brief	クロマサプレス処理を開始するスレッショルド値を取得します。
			@~japanese	@details	クロマサプレス処理を開始するスレッショルド値を取得します。
			@~japanese	@param[in] eCSPS	設定の対象部を指定します。
			@~japanese	@return	スレッショルド値
			@~japanese	@exception	不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual uint32_t GetThresholdValue(EStChromaSuppressionPartSelector_t eCSPS) const = 0;
		
		/*!
			@~english	@brief	Set the threshold value of chroma suppression activate.
			@~english	@details	Set the threshold value of chroma suppression activate.
			@~english	@param[in]	eCSPS	The target eCSPS for setting.
			@~english	@param[in]	value	Threshold value(0 ~ 255).
			@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument.
			@~japanese	@brief	クロマサプレス処理を開始するスレッショルド値を設定します。
			@~japanese	@details	クロマサプレス処理を開始するスレッショルド値を設定します。
			@~japanese	@param[in]	eCSPS	設定の対象部を指定します。
			@~japanese	@param[in]	value	スレッショルド値(0～255)
			@~japanese	@exception	不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void SetThresholdValue(EStChromaSuppressionPartSelector_t eCSPS, uint32_t value) = 0;

		/*!
			@~english	@brief	Acquire the supression value of chroma supression function.
			@~english	@details	Acquire the supression value of chroma supression function.
			@~english	@param[in] eCSPS	The target of eCSPS.
			@~english	@return	Supression value.
			@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument.
			@~japanese	@brief	クロマサプレス処理の抑圧値を取得します。
			@~japanese	@details	クロマサプレス処理の抑圧値を取得します。
			@~japanese	@param[in] eCSPS	設定の対象部を指定します。
			@~japanese	@return	抑圧値
			@~japanese	@exception	不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual uint32_t GetSuppressionValue(EStChromaSuppressionPartSelector_t eCSPS) const = 0;
		
		/*!
			@~english	@brief	Set the supression value of chroma supression function.
			@~english	@details	Set the supression value of chroma supression function.
			@~english	@param[in]	eCSPS	The target eCSPS for setting.
			@~english	@param[in]	value	Supression value(0 ~ 255).
			@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument.
			@~japanese	@brief	クロマサプレス処理を開始する抑圧値を設定します。
			@~japanese	@details	クロマサプレス処理を開始する抑圧値を設定します。
			@~japanese	@param[in]	eCSPS	設定の対象部を指定します。
			@~japanese	@param[in]	value	抑圧値(0～255)
			@~japanese	@exception	不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void SetSuppressionValue(EStChromaSuppressionPartSelector_t eCSPS, uint32_t value) = 0;
	};

	//---------------------------------------------------------------------
	// typedef CIStChromaSuppressionFilterPtr
	//---------------------------------------------------------------------
	/*!
		@ingroup StApiIP_PublicImpl
		@typedef CIStChromaSuppressionFilterPtr
		@~english	@brief	The auto management class of IStChromaSuppressionFilter class.
		@~english	@details	The auto management class of IStChromaSuppressionFilter class.Use this class instead of managing the initial/release of IStChromaSuppressionFilter class yourself. The destructor of this class will automatically call IStFilterReleasable::Release().
		@sa	CreateIStFilter(), GetIStFilterInfo()
		@~japanese	@brief	クロマサプレスフィルター用インターフェースポインターの自動管理用クラスです。
		@~japanese	@details	クロマサプレスフィルター用インターフェースポインターの自動管理用クラスです。このクラスのデストラクタから IStFilterReleasable::Release() が自動的に呼び出されます。
		@sa	CreateIStFilter(), GetIStFilterInfo()
	*/
	typedef CStAutoPtr<IStFilterReleasable, IStChromaSuppressionFilter> CIStChromaSuppressionFilterPtr;
}
#endif //ST_CHROMA_SUPPRESSION_FILTER_H



