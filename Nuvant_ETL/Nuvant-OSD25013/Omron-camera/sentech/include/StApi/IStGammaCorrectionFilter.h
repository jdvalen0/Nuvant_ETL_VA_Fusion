//------------------------------------------------------------------------------
//  StApi
//------------------------------------------------------------------------------
/*!
	@ingroup	StApiIP_PublicInterface
	@file
	@~english	@details	Definition of interface IStGammaCorrectionFilter
	@~japanese	@details	IStGammaCorrectionFilter インターフェースの定義
*/
#ifndef StGAMMACORRECTIONFILTER_H
#define StGAMMACORRECTIONFILTER_H

#include "IStFilter.h"

namespace StApi
{
	interface IStImage;

	// ---------------------------------------------------------------------
	// interface IStGammaCorrectionFilter
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiIP_PublicInterface
		@interface IStGammaCorrectionFilter
		@~english	@brief	Interface for Gamma Correction Filter.
		@~english	@details	Interface for Gamma Correction Filter.
		@sa	CreateIStFilter(), GetIStFilterInfo()
		@~japanese	@brief	ガンマ補正フィルター用インターフェース
		@~japanese	@details	ガンマ補正フィルター用インターフェース
		@sa	CreateIStFilter(), GetIStFilterInfo()
	*/
	interface PUBLIC_INTERFACE IStGammaCorrectionFilter : public IStFilter
	{
		/*!
			@~english	@brief	Acquire gamma correction value.
			@~english	@details	Acquire gamma correction value.
			@~english	@return	Gamma correction value.
			@~english	@exception	None.
			@~japanese	@brief	ガンマ補正値を取得します。
			@~japanese	@details	ガンマ補正値を取得します。
			@~japanese	@return	ガンマ補正値
			@~japanese	@exception	なし
		*/
		virtual double GetGammaValue() const = 0;
		
		/*!
			@~english	@brief	Set gamma correction value.
			@~english	@details	Set gamma correction value.
			@~english	@param[in]	value	Gamma correction value(0 ~ 4.0).
			@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument.
			@~japanese	@brief	ガンマ補正値を設定します。
			@~japanese	@details	ガンマ補正値を設定します。
			@~japanese	@param[in]	value	ガンマ補正値(0.0～4.0) 
			@~japanese	@exception	不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void SetGammaValue(double value) = 0;
	};

	//---------------------------------------------------------------------
	// typedef CIStGammaCorrectionFilterPtr
	//---------------------------------------------------------------------
	/*!
		@ingroup StApiIP_PublicImpl
		@typedef CIStGammaCorrectionFilterPtr
		@~english	@brief	 The auto management class of IStGammaCorrectionFilter class.
		@~english	@details	 The auto management class of IStGammaCorrectionFilter class.Use this class instead of managing the initial/release of IStGammaCorrectionFilter class yourself. The destructor of this class will automatically call IStFilterReleasable::Release().
		@sa	CreateIStFilter(), GetIStFilterInfo()
		@~japanese	@brief	ガンマ補正フィルター用インターフェースポインターの自動管理用クラスです。
		@~japanese	@details	ガンマ補正フィルター用インターフェースポインターの自動管理用クラスです。このクラスのデストラクタから IStFilterReleasable::Release() が自動的に呼び出されます。
		@sa	CreateIStFilter(), GetIStFilterInfo()
	*/
	typedef CStAutoPtr<IStFilterReleasable, IStGammaCorrectionFilter> CIStGammaCorrectionFilterPtr;
}
#endif //StGAMMACORRECTIONFILTER_H



