//------------------------------------------------------------------------------
// StApi
//------------------------------------------------------------------------------
/*!
	@ingroup	StApiTL_PublicInterface
	@file
	@~english	@details	Definition of interface IStReleasable
	@~japanese	@details	IStReleasableインターフェースの定義
*/
#ifndef IStReleasable_H__
#define IStReleasable_H__

#include "StApi_Platform.h"

namespace StApi
{
	//---------------------------------------------------------------------
	// interface IStReleasable
	//---------------------------------------------------------------------
	/*!
		@ingroup StApiTL_PublicInterface
		@interface IStReleasable
		@~english	@brief	Interface for Release.
		@~english	@details	Interface for Release.
		@~japanese	@brief	解放用インターフェース
		@~japanese	@details	解放用インターフェース
	*/
	interface PUBLIC_INTERFACE IStReleasable
	{
		/*!
			@~english	@brief	Release object.
			@~english	@details	Release object.
			@~english	@exception	None.
			@~japanese	@brief	解放します。
			@~japanese	@details	解放します。
			@~japanese	@exception	なし
		*/
		virtual void Release() = 0;
	};
}
#endif //IStReleasable_H__
