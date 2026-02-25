//------------------------------------------------------------------------------
//  StApi
//------------------------------------------------------------------------------
/*!
	@ingroup	StApiTL_PublicInterface
	@file	IStCallback.h
	@~english	@details	Definition of interface IStCallback
	@~japanese	@details	IStCallback インターフェースおよびコールバック関連インターフェースの定義
*/
#ifndef ISTCALLBACK_H__
#define ISTCALLBACK_H__

#include <GenICam.h>

#ifdef _MSC_VER
#pragma warning(push)	
#pragma warning(disable : 4819)	
#include "StGenTL_Def.h"
#include "StApi_TLDef.h"
#pragma warning(pop)	
#else
#include "StGenTL_Def.h"
#include "StApi_TLDef.h"
#endif

#include "IStReleasable.h"

namespace StApi
{
	interface IStSystem;
	interface IStInterface;
	interface IStDevice;
	interface IStDataStream;
	interface IStStreamBuffer;
	
	// ---------------------------------------------------------------------
	// interface IStCallbackParamBase
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiTL_PublicInterface
		@interface IStCallbackParamBase
		@~english	@brief	Interface for StApi callback parameter.
		@~english	@details	Interface for StApi callback parameter.
		@~japanese	@brief	コールバックパラメーター取得用インターフェース
		@~japanese	@details	コールバックパラメーター取得用インターフェース
	*/
	interface PUBLIC_INTERFACE IStCallbackParamBase
	{
		/*!
			@~english	@brief	Return the callback type.
			@~english	@details	Return the callback type.
			@~english	@return	The callback type.
			@~english	@exception	None.
			@~japanese	@brief	コールバックタイプを取得します。
			@~japanese	@details	コールバックタイプを取得します。
			@~japanese	@return	コールバックタイプ
			@~japanese	@exception	なし
		*/
		virtual EStCallbackType_t GetCallbackType() const = 0;
	};

	// ---------------------------------------------------------------------
	// interface IStCallbackParamGenTLEventError
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiTL_PublicInterface
		@interface IStCallbackParamGenTLEventError
		@~english	@brief	Interface for GenTL error event callback parameter.
		@~english	@details	Interface for GenTL error event callback parameter.
		@~japanese	@brief	GenTLエラーイベントコールバックパラメータ用インターフェース
		@~japanese	@details	GenTLエラーイベントコールバックパラメータ用インターフェース
	*/
	interface PUBLIC_INTERFACE IStCallbackParamGenTLEventError : public IStCallbackParamBase
	{
		/*!
			@~english	@brief	Acquire error code of GenTL.
			@~english	@details	Acquire error code of GenTL.
			@~english	@return	The GenTL error code.
			@~english	@exception	None.
			@~japanese	@brief	GenTLのエラーコードを取得します。
			@~japanese	@details	GenTLのエラーコードを取得します。
			@~japanese	@return	GenTLエラーコード
			@~japanese	@exception	なし
		*/
		virtual GenTL::GC_ERROR GetGCError() const = 0;

		/*!
			@~english	@brief	Acquire the description of the error.
			@~english	@details	Acquire the description of the error.
			@~english	@return	The description of the error.
			@~english	@exception	None.
			@~japanese	@brief	GenTLのエラーの説明文を取得します。
			@~japanese	@details	GenTLのエラーの説明文を取得します。
			@~japanese	@return	GenTLのエラーの説明文
			@~japanese	@exception	なし
		*/
		virtual const GenICam::gcstring &GetDescription() const = 0;
	};
	
	// ---------------------------------------------------------------------
	// interface IStCallbackParamGenTLEventErrorTL
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiTL_PublicInterface
		@interface IStCallbackParamGenTLEventErrorTL
		@~english	@brief	Interface for StCallbackType_GenTLEvent_SystemError callback parameter.
		@~english	@details	Interface for StCallbackType_GenTLEvent_SystemError callback parameter.
		@~japanese	@brief	StCallbackType_GenTLEvent_SystemError コールバックのパラメーター用インターフェース
		@~japanese	@details	StCallbackType_GenTLEvent_SystemError コールバックのパラメーター用インターフェース
	*/
	interface PUBLIC_INTERFACE IStCallbackParamGenTLEventErrorTL : public IStCallbackParamGenTLEventError
	{
		/*!
			@~english	@brief	Acquire IStSystem interface pointer.
			@~english	@details	Acquire IStSystem interface pointer.
			@~english	@return	IStSystem Interface pointer.
			@~english	@exception	None.
			@~japanese	@brief	IStSystem インターフェースポインターを取得します。
			@~japanese	@details	IStSystem インターフェースポインターを取得します。
			@~japanese	@return	IStSystem インターフェースポインター
			@~japanese	@exception	なし
		*/
		virtual IStSystem	*GetIStSystem() const = 0;
	};

	// ---------------------------------------------------------------------
	// interface IStCallbackParamGenTLEventErrorIF
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiTL_PublicInterface
		@interface IStCallbackParamGenTLEventErrorIF
		@~english	@brief	Interface for StCallbackType_GenTLEvent_InterfaceError callback parameter.
		@~english	@details	Interface for StCallbackType_GenTLEvent_InterfaceError callback parameter.
		@~japanese	@brief	StCallbackType_GenTLEvent_InterfaceError コールバックのパラメーター用インターフェース
		@~japanese	@details	StCallbackType_GenTLEvent_InterfaceError コールバックのパラメーター用インターフェース
	*/
	interface PUBLIC_INTERFACE IStCallbackParamGenTLEventErrorIF : public IStCallbackParamGenTLEventError
	{
		/*!
			@~english@brief		Acquire IStInterface pointer.
			@~english	@details	Acquire IStInterface pointer.
			@~english	@return	IStInterface Interface pointer.
			@~english	@exception	None.
			@~japanese	@brief	IStInterface インターフェースポインターを取得します。
			@~japanese	@details	IStInterface インターフェースポインターを取得します。
			@~japanese	@return	IStInterface インターフェースポインター
			@~japanese	@exception	なし
		*/
		virtual IStInterface	*GetIStInterface() const = 0;
	};
	
	// ---------------------------------------------------------------------
	// interface IStCallbackParamGenTLEventErrorDEV
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiTL_PublicInterface
		@interface IStCallbackParamGenTLEventErrorDEV
		@~english	@brief	Interface for StCallbackType_GenTLEvent_DeviceError callback parameter.
		@~english	@details	Interface for StCallbackType_GenTLEvent_DeviceError callback parameter.
		@~japanese	@brief	StCallbackType_GenTLEvent_DeviceError コールバックのパラメーター用インターフェース
		@~japanese	@details	StCallbackType_GenTLEvent_DeviceError コールバックのパラメーター用インターフェース
	*/
	interface PUBLIC_INTERFACE IStCallbackParamGenTLEventErrorDEV : public IStCallbackParamGenTLEventError
	{
		/*!
			@~english	@brief	Acquire IStDevice pointer.
			@~english	@details	Acquire IStDevice pointer.
			@~english	@return	IStDevice Interface pointer.
			@~english	@exception	None.
			@~japanese	@brief	IStDevice インターフェースポインターを取得します。
			@~japanese	@details	IStDevice インターフェースポインターを取得します。
			@~japanese	@return	IStDevice インターフェースポインター
			@~japanese	@exception	なし
		*/
		virtual IStDevice	*GetIStDevice() const = 0;
	};
	
	// ---------------------------------------------------------------------
	// interface IStCallbackParamGenTLEventErrorDS
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiTL_PublicInterface
		@interface IStCallbackParamGenTLEventErrorDS
		@~english	@brief	Interface for StCallbackType_GenTLEvent_DataStreamError callback parameter.
		@~english	@details	Interface for StCallbackType_GenTLEvent_DataStreamError callback parameter.
		@~japanese	@brief	StCallbackType_GenTLEvent_DataStreamError コールバックのパラメーター用インターフェース
		@~japanese	@details	StCallbackType_GenTLEvent_DataStreamError コールバックのパラメーター用インターフェース
	*/
	interface PUBLIC_INTERFACE IStCallbackParamGenTLEventErrorDS : public IStCallbackParamGenTLEventError
	{
		/*!
			@~english	@brief	Acquire IStDataStream pointer.
			@~english	@details	Acquire IStDataStream pointer.
			@~english	@return	IStDataStream Interface pointer.
			@~english	@exception	None.
			@~japanese	@brief	IStDataStream インターフェースポインターを取得します。
			@~japanese	@details	IStDataStream インターフェースポインターを取得します。
			@~japanese	@return	IStDataStream インターフェースポインター
			@~japanese	@exception	なし
		*/
		virtual IStDataStream	*GetIStDataStream() const = 0;
	};
	
	// ---------------------------------------------------------------------
	// interface IStCallbackParamGenTLEventErrorSB
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiTL_PublicInterface
		@interface IStCallbackParamGenTLEventErrorSB
		@~english	@brief	Interface for StCallbackType_GenTLEvent_StreamBufferError callback parameter.
		@~english	@details	Interface for StCallbackType_GenTLEvent_StreamBufferError callback parameter.
		@~japanese	@brief	StCallbackType_GenTLEvent_StreamBufferError コールバックのパラメーター用インターフェース
		@~japanese	@details	StCallbackType_GenTLEvent_StreamBufferError コールバックのパラメーター用インターフェース
	*/
	interface PUBLIC_INTERFACE IStCallbackParamGenTLEventErrorSB : public IStCallbackParamGenTLEventError
	{
		/*!
			@~english	@brief	Acquire IStStreamBuffer pointer.
			@~english	@details	Acquire IStStreamBuffer pointer.
			@~english	@return	IStStreamBuffer Interface pointer.
			@~english	@exception	None.
			@~japanese	@brief	IStStreamBuffer インターフェースポインターを取得します。
			@~japanese	@details	IStStreamBuffer インターフェースポインターを取得します。
			@~japanese	@return	IStStreamBuffer インターフェースポインター
			@~japanese	@exception	なし
		*/
		virtual IStStreamBuffer	*GetIStStreamBuffer() const = 0;
	};
	
	// ---------------------------------------------------------------------
	// interface IStCallbackParamGenTLEventNewBuffer
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiTL_PublicInterface
		@interface IStCallbackParamGenTLEventNewBuffer
		@~english	@brief	Interface for StCallbackType_GenTLEvent_DataStreamNewBuffer callback parameter.
		@~english	@details	Interface for StCallbackType_GenTLEvent_DataStreamNewBuffer callback parameter.
		@~japanese	@brief	StCallbackType_GenTLEvent_DataStreamNewBuffer コールバックのパラメーター用インターフェース
		@~japanese	@details	StCallbackType_GenTLEvent_DataStreamNewBuffer コールバックのパラメーター用インターフェース
	*/
	interface PUBLIC_INTERFACE IStCallbackParamGenTLEventNewBuffer : public IStCallbackParamBase
	{
		/*!
			@~english	@brief	Acquire IStDataStream pointer.
			@~english	@details	Acquire IStDataStream pointer.
			@~english	@return	IStDataStream Interface pointer.
			@~english	@exception	None.
			@~japanese	@brief	IStDataStream インターフェースポインターを取得します。
			@~japanese	@details	IStDataStream インターフェースポインターを取得します。
			@~japanese	@return	IStDataStream インターフェースポインター
			@~japanese	@exception	なし
		*/
		virtual IStDataStream	*GetIStDataStream() const = 0;
	};

	
	// ---------------------------------------------------------------------
	// interface IStCallback
	// ---------------------------------------------------------------------
	/*!
		@interface IStCallback
		@~english	@brief	Interface for StApi callback.
		@~english	@details	Interface for StApi callback.
		@~japanese	@brief	StApiコールバック用インターフェース
		@~japanese	@details	StApiコールバック用インターフェース
	*/
	interface PUBLIC_INTERFACE IStCallback
	{
		/*!
			@~english	@brief	Execute the callback.
			@~english	@details	Execute the callback.
			@~english	@param[in]	pIStCallbackParamBase	IStCallbackParamBase interface pointer.
			@~english	@exception	None.
			@~japanese	@brief	コールバック関数を呼び出します。
			@~japanese	@details	コールバック関数を呼び出します。
			@~japanese	@param[in]	pIStCallbackParamBase	IStCallbackParamBase インターフェースポインター
			@~japanese	@exception	なし
		*/
		virtual void operator()(IStCallbackParamBase *pIStCallbackParamBase) throw() = 0;

		/*!
			@~english	@brief	Destroy the object.
			@~english	@details	Destroy the object.
			@~english	@exception	None.
			@~japanese	@brief	オブジェクトを破棄します。
			@~japanese	@details	オブジェクトを破棄します。
			@~japanese	@exception	なし
		*/
		virtual void Destroy() throw() = 0;
	};
	
	// ---------------------------------------------------------------------
	// typedef CIStRegisteredCallbackPtr
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiTL_PublicImpl
		@typedef StApiCallbackHandle_t
		@~english	@brief	Type for identifying the callback function that has been registered.
		@~english	@details	Type for identifying the callback function that has been registered.
		@~japanese	@brief	登録されたコールバック関数識別用ハンドル型
		@~japanese	@details	登録されたコールバック関数識別用ハンドル型
	*/
	typedef void* StApiCallbackHandle_t;

	// ---------------------------------------------------------------------
	// interface IStRegisterCallback
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiTL_PublicInterface
		@interface IStRegisterCallback
		@~english	@brief	Interface for registering callback.
		@~english	@details	Interface for registering callback.
		@~japanese	@brief	StApiコールバック関数の登録および登録解除に使用されるインターフェース
		@~japanese	@details	StApiコールバック関数の登録および登録解除に使用されるインターフェース
	*/
	interface PUBLIC_INTERFACE IStRegisterCallback
	{
		/*!
			@~english	@brief	Register a callback function.
			@~english	@details	Register a callback function.
			@~english	@param[in] pIStCallback	IStCallback interface pointer.
			@~english	@return	Callback function registration identifier.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed.
			@~japanese	@brief	コールバック関数を登録します。
			@~japanese	@details	コールバック関数を登録します。
			@~japanese	@param[in] pIStCallback	IStCallback インターフェースポインター
			@~japanese	@return	コールバック関数識別子
			@~japanese	@exception	メモリー確保に失敗した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual StApiCallbackHandle_t RegisterCallback(IStCallback *pIStCallback) = 0;

		/*!
			@~english	@brief	Deregister a callback function.
			@~english	@details	Deregister a callback function.
			@~english	@param[in] hCallback	Callback function registration identifier. ( Returned value of the RegisterCallback call)
			@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument.
			@~japanese	@brief	コールバック関数の登録を解除します。
			@~japanese	@details	コールバック関数の登録を解除します。
			@~japanese	@param[in] hCallback	コールバック関数識別子
			@~japanese	@exception	引数が不正な場合例外 GenICam::GenericException が発生します。
		*/
		virtual void DeregisterCallback(StApiCallbackHandle_t hCallback) = 0;
	};

	// ---------------------------------------------------------------------
	// interface IStRegisteredCallback
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiTL_PublicInterface
		@interface IStRegisteredCallback
		@~english	@brief	Interface for extending the already-registered StApi callback function
		@~english	@details      Interface for extending the already-registered StApi callback function
		@~japanese	@brief	登録済みStApiコールバック関数に対するインターフェース(拡張用)
		@~japanese	@details	登録済みStApiコールバック関数に対するインターフェース(拡張用)
	*/
	interface IStRegisteredCallback
	{
	};

	// ---------------------------------------------------------------------
	// interface IStRegisteredCallbackReleasable
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiTL_PublicInterface
		@interface IStRegisteredCallbackReleasable
		@~english	@brief	Interface for extending the already-registered releasable StApi callback function
		@~english	@details	    Interface for extending the already-registered releasable StApi callback function
		@~japanese	@brief	解放可能な登録済みStApiコールバック関数に対するインターフェース(拡張用)
		@~japanese	@details	解放可能な登録済みStApiコールバック関数に対するインターフェース(拡張用)
	*/
	interface IStRegisteredCallbackReleasable : public IStRegisteredCallback, public IStReleasable
	{
	};
}
#endif //ISTCALLBACK_H__

