//------------------------------------------------------------------------------
//  StApi
//------------------------------------------------------------------------------
/*!
	@ingroup	StApiIP_PublicInterface
	@file	
	@~english	@details	Definition of interface IStEdgeEnhancementFilter
	@~japanese	@details	IStEdgeEnhancementFilter インターフェースの定義
*/
#ifndef STEDGEENHANCEMENT_H
#define STEDGEENHANCEMENT_H

#include "IStFilter.h"

namespace StApi
{
	interface IStImage;

	// ---------------------------------------------------------------------
	// interface IStEdgeEnhancementFilter
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiIP_PublicInterface
		@interface IStEdgeEnhancementFilter
		@~english	@brief	Interface for Edge Enhancement Filter.
		@~english	@details	Interface for Edge Enhancement Filter.
		@sa	CreateIStFilter(), GetIStFilterInfo()
		@~japanese	@brief	エッジ強調フィルター用インターフェース
		@~japanese	@details	エッジ強調フィルター用インターフェース
		@sa	CreateIStFilter(), GetIStFilterInfo()
	*/
	interface PUBLIC_INTERFACE IStEdgeEnhancementFilter : public IStFilter
	{
		/*!
			@~english	@brief	Get the edge enhancement value.
			@~english	@details	Get the edge enhancement value.
			@~english	@return	Enhancement value.
			@~english	@exception	None.
			@~japanese	@brief	強調度を取得します。
			@~japanese	@details	強調度を取得します。
			@~japanese	@return	強調度
			@~japanese	@exception	なし
		*/
		virtual double GetStrength() const = 0;
		
		/*!
			@~english	@brief	Set the edge enhancement value.
			@~english	@details	Set the edge enhancement value.
			@~english	@param[in]	value	Enhancement value(0 ~ 32.0).
			@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument. 
			@~japanese	@brief	強調度を設定します。
			@~japanese	@details	強調度を設定します。
			@~japanese	@param[in]	value	強調度(0～32.0)
			@~japanese	@exception	不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void SetStrength(double value) = 0;

		/*!
			@~english	@brief	Get threshold of the edge enhancement.
			@~english	@details	Get threshold of the edge enhancement.
			@~english	@return	Threshold.
			@~english	@exception	None.
			@~japanese	@brief	スレッショルド値を取得します。
			@~japanese	@details	スレッショルド値を取得します。
			@~japanese	@return	スレッショルド値
			@~japanese	@exception	なし
		*/
		virtual uint32_t GetThresh() const = 0;

		/*!
			@~english	@brief	Set threshold of the edge enhancement.
			@~english	@details	Set threshold of the edge enhancement.
			@~english	@param[in]	value	Threshold(0 ~ 255).
			@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument. 
			@~japanese	@brief	スレッショルド値を設定します。
			@~japanese	@details	スレッショルド値を設定します。
			@~japanese	@param[in]	value	スレッショルド値(0～255)
			@~japanese	@exception	不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void SetThresh(uint32_t value) = 0;
	};

	//---------------------------------------------------------------------
	// typedef CIStEdgeEnhancementFilterPtr
	//---------------------------------------------------------------------
	/*!
		@ingroup StApiIP_PublicImpl
		@typedef CIStEdgeEnhancementFilterPtr
		@~english	@brief	The auto management class of IStEdgeEnhancementFilter class.
		@~english	@details	The auto management class of IStEdgeEnhancementFilter class.Use this class instead of managing the initial/release of IStEdgeEnhancementFilter class yourself. The destructor of this class will automatically call IStFilterReleasable::Release().
		@sa	CreateIStFilter(), GetIStFilterInfo()
		@~japanese	@brief	エッジ強調フィルター用インターフェースポインターの自動管理用クラスです。
		@~japanese	@details	エッジ強調フィルター用インターフェースポインターの自動管理用クラスです。このクラスのデストラクタから IStFilterReleasable::Release() が自動的に呼び出されます。
		@sa	CreateIStFilter(), GetIStFilterInfo()
	*/
	typedef CStAutoPtr<IStFilterReleasable, IStEdgeEnhancementFilter> CIStEdgeEnhancementFilterPtr;

}
#endif //STEDGEENHANCEMENT_H



