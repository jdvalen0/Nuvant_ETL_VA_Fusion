//------------------------------------------------------------------------------
//  StApi
//------------------------------------------------------------------------------
/*!
	@ingroup	StApiIP_PublicInterface
	@file	
	@~english	@details	Definition of interface IStBalanceRatioFilter
	@~japanese	@details	IStBalanceRatioFilter インターフェースの定義
*/
#ifndef STGAIN_H
#define STGAIN_H

#include "IStFilter.h"

namespace StApi
{
	interface IStImage;

	// ---------------------------------------------------------------------
	// interface IStBalanceRatioFilter
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiIP_PublicInterface
		@interface IStBalanceRatioFilter
		@~english	@brief	Interface of Balance Ratio Filter.
		@~english	@details	Interface of Balance Ratio Filter.
		@sa	CreateIStFilter(), GetIStFilterInfo()
		@~japanese	@brief	バランスレートフィルター用インターフェース
		@~japanese	@details	バランスレートフィルター用インターフェース
		@sa	CreateIStFilter(), GetIStFilterInfo()
	*/
	interface PUBLIC_INTERFACE IStBalanceRatioFilter : public IStFilter
	{
		/*!
			@~english	@brief	Get the value of white balance gain.
			@~english	@details	Get the value of white balance gain.
			@~english	@param[in] eBRS	The target of this function.
			@~english	@return	The value of white balance gain.
			@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument.
			@~japanese	@brief	ホワイトバランスゲインの値を取得します。
			@~japanese	@details	ホワイトバランスゲインの値を取得します。
			@~japanese	@param[in] eBRS	対象を指定します。
			@~japanese	@return	ホワイトバランスゲインの値
			@~japanese	@exception	不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual double GetBalanceRatio(EStBalanceRatioSelector_t eBRS)  const = 0;
		
		/*!
			@~english	@brief	Set the value of white balance gain.
			@~english	@details	Set the value of white balance gain.
			@~english	@param[in] eBRS	The target of this function.
			@~english	@param[in] value Gain value of white balance(0 ~ 16.0).
			@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument.
			@~japanese	@brief	ホワイトバランスゲインの値を設定します。
			@~japanese	@details	ホワイトバランスゲインの値を設定します。
			@~japanese	@param[in] eBRS	対象を指定します。
			@~japanese	@param[in] value ホワイトバランスゲインの値(0～16.0)。
			@~japanese	@exception	不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void SetBalanceRatio(EStBalanceRatioSelector_t eBRS, double value) = 0;

		/*!
			@~english	@brief	Get the offset value before gain processing.
			@~english	@details	Get the offset value before gain processing.
			@~english	@param[in] eBRS	The target of this function.
			@~english	@return	Offset value.
			@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument.
			@~japanese	@brief	ホワイトバランスゲイン処理前のオフセット値を取得します。
			@~japanese	@details	ホワイトバランスゲイン処理前のオフセット値を取得します。
			@~japanese	@param[in] eBRS	対象を指定します。
			@~japanese	@return	オフセット値
			@~japanese	@exception	不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual int32_t GetOffsetLevelBeforeGain(EStBalanceRatioSelector_t eBRS)  const = 0;
		
		/*!
			@~english	@brief	Set the offset value before gain processing.
			@~english	@details	Set the offset value before gain processing.
			@~english	@param[in] eBRS	The target of this function.
			@~english	@param[in] value Offset value(-255 ~ 255).
			@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument.
			@~japanese	@brief	ホワイトバランスゲイン処理前のオフセット値を設定します。
			@~japanese	@details	ホワイトバランスゲイン処理前のオフセット値を設定します。
			@~japanese	@param[in] eBRS	対象を指定します。
			@~japanese	@param[in] value オフセット値(-255～255)。
			@~japanese	@exception	不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void SetOffsetLevelBeforeGain(EStBalanceRatioSelector_t eBRS, int32_t value) = 0;

		/*!
			@~english	@brief	Get the offset value after gain processing.
			@~english	@details	Get the offset value after gain processing.
			@~english	@param[in] eBRS	The target of this function.
			@~english	@return	Offset value.
			@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument.
			@~japanese	@brief	ホワイトバランスゲイン処理後のオフセット値を取得します。
			@~japanese	@details	ホワイトバランスゲイン処理後のオフセット値を取得します。
			@~japanese	@param[in] eBRS	対象を指定します。
			@~japanese	@return	オフセット値
			@~japanese	@exception	不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual int32_t GetOffsetLevelAfterGain(EStBalanceRatioSelector_t eBRS)  const = 0;
		
		/*!
			@~english	@brief	Set the offset value after gain processing.
			@~english	@details	Set the offset value after gain processing.
			@~english	@param[in] eBRS	The target of this function.
			@~english	@param[in] value Offset value(-255 ~ 255).
			@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument.
			@~japanese	@brief	ホワイトバランスゲイン処理後のオフセット値を設定します。
			@~japanese	@details	ホワイトバランスゲイン処理後のオフセット値を設定します。
			@~japanese	@param[in] eBRS	対象を指定します。
			@~japanese	@param[in] value オフセット値(-255～255)。
			@~japanese	@exception	不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void SetOffsetLevelAfterGain(EStBalanceRatioSelector_t eBRS, int32_t value) = 0;

		/*!
			@~english	@brief	Get current setting of BalanceWhiteAuto.
			@~english	@details	Get current setting of BalanceWhiteAuto.
			@~english	@return	BalanceWhiteAuto setting.
			@~english	@exception	None.
			@~japanese	@brief	オートホワイトバランス設定を取得します。
			@~japanese	@details	オートホワイトバランス設定を取得します。
			@~japanese	@return	オートホワイトバランス設定値
			@~japanese	@exception	なし
		*/
		virtual EStBalanceWhiteAuto_t GetBalanceWhiteAuto()  const = 0;

		/*!
			@~english	@brief	Set BalanceWhiteAuto.
			@~english	@details	Set BalanceWhiteAuto.
			@~english	@param[in] eBWA	BalanceWhiteAuto setting.
			@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument.
			@~japanese	@brief	オートホワイトバランスを設定します。
			@~japanese	@details	オートホワイトバランスを設定します。
			@~japanese	@param[in] eBWA	オートホワイトバランス設定
			@~japanese	@exception	不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void SetBalanceWhiteAuto(EStBalanceWhiteAuto_t eBWA) = 0;
	};
	
	//---------------------------------------------------------------------
	// typedef CIStBalanceRatioFilterPtr
	//---------------------------------------------------------------------
	/*!
		@ingroup StApiIP_PublicImpl
		@typedef CIStBalanceRatioFilterPtr
		@~english	@brief	The auto management class of IStBalanceRatioFilter class.
		@~english	@details	The auto management class of IStBalanceRatioFilter class. Use this class instead of managing the initial/release of IStBalanceRatioFilter class yourself. The destructor of this class will automatically call IStFilterReleasable::Release().
		@sa	CreateIStFilter(), GetIStFilterInfo()
		@~japanese	@brief	バランスレートフィルター用インターフェースポインターの自動管理用クラスです。
		@~japanese	@details	バランスレートフィルター用インターフェースポインターの自動管理用クラスです。このクラスのデストラクタから IStFilterReleasable::Release() が自動的に呼び出されます。
		@sa	CreateIStFilter(), GetIStFilterInfo()
	*/
	typedef CStAutoPtr<IStFilterReleasable, IStBalanceRatioFilter> CIStBalanceRatioFilterPtr;
}
#endif //STGAIN_H
