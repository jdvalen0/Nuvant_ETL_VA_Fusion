//------------------------------------------------------------------------------
//  StApi
//------------------------------------------------------------------------------
/*!
@ingroup	StApiTL_PublicInterface
@file
@~english	@details	Definition of interface IStEventCtrl
@~japanese	@details	IStEventCtrl インターフェースの定義
*/
#ifndef ISTEVENTCTRL_H__
#define ISTEVENTCTRL_H__

#include "StApi_Platform.h"

namespace StApi
{
	// ---------------------------------------------------------------------
	// interface IStEventCtrl
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiTL_PublicInterface
		@interface IStEventCtrl
		@~english	@brief	Interface for accessing event control feature.
		@~english	@details	Interface for accessing event control feature.
		@~japanese	@brief	イベント機能制御用インターフェース
		@~japanese	@details	イベント機能制御用インターフェース
	*/
	interface PUBLIC_INTERFACE IStEventCtrl
	{
		/*!
			@~english	@brief	Start the event handling thread.
			@~english	@details	Start the event handling thread.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed.
			@~japanese	@brief	イベント取得用スレッドを起動します。
			@~japanese	@details	イベント取得用スレッドを起動します。
			@~japanese	@exception	メモリー確保に失敗した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void StartEventAcquisitionThread() = 0;

		/*!
			@~english	@brief	Stop the event handling thread.
			@~english	@details	Stop the event handling thread.
			@~english	@exception	Throw out a GenICam::GenericException if GenTL function is failed.
			@~japanese	@brief	イベント取得用スレッドを停止します。
			@~japanese	@details	イベント取得用スレッドを停止します。
			@~japanese	@exception	GenTL 関数がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void StopEventAcquisitionThread() = 0;
	};
}
#endif //ISTEVENTCTRL_H__

