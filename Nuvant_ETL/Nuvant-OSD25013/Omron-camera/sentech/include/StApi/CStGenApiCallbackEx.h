//------------------------------------------------------------------------------
//  StApi
//------------------------------------------------------------------------------
/*!
	@ingroup	StApiTL_PublicImpl
	@file	CStGenApiCallbackEx.h
	@~english	@details	Definition of RegisterCallback and GenApi related callback class.
	@~japanese	@details	RegisterCallback およびGenApiコールバック関数関連クラスの定義
*/
#ifndef STAPI_GENAPI_CALLBACK_EX_H__
#define STAPI_GENAPI_CALLBACK_EX_H__

#include "IStCallback.h"
namespace StApi
{
	/*************************************************************************/
	// C functions as callbacks
	/*************************************************************************/

	//---------------------------------------------------------------------
	// class Function_NodeCallbackEx
	//---------------------------------------------------------------------
	/*!
		@~english	@brief	Class for managing C-style function callback.
		@~english	@details      Class for managing C-style function callback.
		@~english	@tparam	Function	Type of the callback function.
		@~english	@tparam Parameter	Type of the argument for the callback function.
		@~japanese	@brief	C関数をコールバック関数として登録するために使用されるクラス
		@~japanese	@details	C関数をコールバック関数として登録するために使用されるクラス
		@~japanese	@tparam	Function	コールバック関数の型
		@~japanese	@tparam Parameter	コールバック関数に渡されるユーザー用パラメータの型
	*/
	template <class Function, class Parameter>
	class Function_NodeCallbackEx : public GenApi::CNodeCallback, public IStRegisteredCallbackReleasable
	{
	public:
		// Constructor.
		Function_NodeCallbackEx(GenApi::INode *pINode, Function& function, Parameter param, GenApi::ECallbackType callbackType) :
			GenApi::CNodeCallback(pINode, callbackType),
			m_pFunction(function),
			m_Param(param),
			m_hCallbackHandleType((GenApi::CallbackHandleType)NULL)
		{}

		// Virtual destructor.
		virtual ~Function_NodeCallbackEx() {};

		// Execute operation.
		virtual void operator()(GenApi::ECallbackType callbackType) const
		{
			if (m_pFunction && m_CallbackType == callbackType)
			{
				m_pFunction(m_pNode, m_Param);
			}
		}

		// Destroy the object.
		virtual void Destroy()
		{
			delete this;
		}

		// Deregister a callback function.
		void Release()
		{
			if (m_hCallbackHandleType)
			{
				GenApi::Deregister(m_hCallbackHandleType);
			}
		}

		// Registers a callback function.
		void RegisterCallback()
		{
			m_hCallbackHandleType = m_pNode->RegisterCallback(this);
		}
	private:
		// The callback function.
		Function const m_pFunction;

		// The parameter of the callback function.
		Parameter const m_Param;

		// No assignment operator
		Function_NodeCallbackEx& operator=(Function_NodeCallbackEx&);

		GenApi::CallbackHandleType m_hCallbackHandleType;
	};

	//---------------------------------------------------------------------
	// 
	//---------------------------------------------------------------------
	/*!
		@ingroup	StApiTL_PublicImpl
		@~english	@brief	Register a C-function as a callback.
		@~english	@details	Register a C-function as a callback.
		@~english	@tparam	Function	Type of the callback function.
		@~english	@tparam Parameter	Type of the argument for the callback function.
		@~english	@param[in]	pINode	INode interface pointer for registering as callback function.
		@~english	@param[in]	pFunc	Callback function pointer.
		@~english	@param[in]	param	Argument to the callback function.
		@~english	@param[in]	callbackType	The type of callback.
		@~english	@return	IStRegisteredCallbackReleasable interface pointer.
		@~english	@attention	When deregistering a callback function, IStRegisteredCallbackReleasable::Release() will be called.
		@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed.
		@~japanese	@brief	C関数をコールバック関数として登録します。
		@~japanese	@details	C関数をコールバック関数として登録します。
		@~japanese	@tparam	Function	コールバック関数の型
		@~japanese	@tparam Parameter	コールバック関数に渡されるユーザー用パラメータの型
		@~japanese	@param[in]	pINode	コールバック関数の登録するノードの INode インターフェースポインター
		@~japanese	@param[in]	pFunc	コールバック関数ポインタ
		@~japanese	@param[in]	param	コールバック関数に渡されるユーザー用パラメータ
		@~japanese	@param[in]	callbackType	コールバック関数のタイプ
		@~japanese	@return	IStRegisteredCallbackReleasable インターフェースポインター。
		@~japanese	@attention	コールバック関数の登録を解除するには IStRegisteredCallbackReleasable::Release() を呼び出します。
		@~japanese	@exception	メモリー確保に失敗した場合は、例外 GenICam::GenericException が発生します。
	*/
	template<class Function, class Parameter>
	IStRegisteredCallbackReleasable *RegisterCallback(GenApi::INode *pINode, Function pFunc, Parameter param, GenApi::ECallbackType callbackType = GenApi::cbPostInsideLock)
	{
		try
		{
			Function_NodeCallbackEx<Function, Parameter> *pFunction_NodeCallbackEx = new Function_NodeCallbackEx<Function, Parameter>(pINode, pFunc, param, callbackType);
			pFunction_NodeCallbackEx->RegisterCallback();
			return(pFunction_NodeCallbackEx);
		}
		catch (const std::bad_alloc &e)
		{
			throw BAD_ALLOC_EXCEPTION(e.what());
		}
	}

	/*************************************************************************/
	// C++ Member function as callbacks
	/*************************************************************************/
	/*!
		@~english	@brief	Container for a member function pointer (C++ class member as callback).
		@~english	@details	Container for a member function pointer (C++ class member as callback).
		@~english	@tparam	Client	Class of the callback method.
		@~english	@tparam	Method	Type of the callback method.
		@~english	@tparam Parameter	Type of the argument for the callback function.
		@~japanese	@brief	C++クラスメソッドをコールバック関数として登録するために使用されるクラス
		@~japanese	@details	C++クラスメソッドをコールバック関数として登録するために使用されるクラス
		@~japanese	@tparam	Client	コールバック関数として使用するメソッドが含まれたクラスの型
		@~japanese	@tparam	Method	コールバック関数として使用するメソッドの型
		@~japanese	@tparam Parameter	コールバック関数に渡されるユーザー用パラメータの型
	*/
	template <class Client, class Method, class Parameter>
	class CClassMethod_NodeCallbackEx : public GenApi::CNodeCallback, public IStRegisteredCallbackReleasable
	{
	public:
		// Member function type.
		typedef void(Client::*PMETHOD_TYPE)(GenApi::INode*, Parameter);

		// Constructor.
		CClassMethod_NodeCallbackEx(GenApi::INode *pINode, Client& client, Method method, Parameter param, GenApi::ECallbackType callbackType) :
			GenApi::CNodeCallback(pINode, callbackType),
			m_Client(client),
			m_pMethod(method),
			m_Param(param),
			m_hCallbackHandleType((GenApi::CallbackHandleType)NULL)
		{}

		// Virtual destructor.
		virtual ~CClassMethod_NodeCallbackEx()
		{

		}

		// Execute operation.
		virtual void operator()(GenApi::ECallbackType callbackType) const
		{
			if (m_pMethod && m_CallbackType == callbackType)
			{
				(m_Client.*m_pMethod)(m_pNode, m_Param);
			}
		}

		// Destroy the object.
		virtual void Destroy()
		{
			delete this;
		}

		// Deregister a callback function.
		void Release()
		{
			if (m_hCallbackHandleType)
			{
				GenApi::Deregister(m_hCallbackHandleType);
			}
		}

		// Registers a callback function.
		void RegisterCallback()
		{
			if (m_hCallbackHandleType == (GenApi::CallbackHandleType)NULL)
			{
				m_hCallbackHandleType = m_pNode->RegisterCallback(this);
			}
		}
	private:
		// The object which the method function belongs to
		Client& m_Client;

		// The method to call.
		PMETHOD_TYPE const m_pMethod;

		// The parameter of the callback function.
		Parameter const m_Param;

		// No assignment operator
		CClassMethod_NodeCallbackEx& operator=(CClassMethod_NodeCallbackEx&);

		GenApi::CallbackHandleType m_hCallbackHandleType;
	};

	//---------------------------------------------------------------------
	// 
	//---------------------------------------------------------------------
	/*!
		@ingroup	StApiTL_PublicImpl
		@~english	@brief	Register a C++ member function as callback.
		@~english	@details	Register a C++ member function as callback.
		@~english	@tparam	Client	Class of the callback method.
		@~english	@tparam	Method	Type of the callback method.
		@~english	@tparam Parameter	Type of the argument for the callback function.
		@~english	@param[in]	pINode	INode interface pointer for registering as callback function.
		@~english	@param[in]	client	A reference to the object which the method function belongs to.
		@~english	@param[in]	member	A method function.
		@~english	@param[in]	param	Argument to the callback function.
		@~english	@param[in]	callbackType	The type of callback.
		@~english	@return	IStRegisteredCallbackReleasable interface pointer.
		@~english	@attention	When deregistering a callback function, IStRegisteredCallbackReleasable::Release() will be called.
		@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed.
		@~japanese	@brief	C++クラスメンバ関数をコールバック関数として登録します。
		@~japanese	@details	C++クラスメンバ関数をコールバック関数として登録します。
		@~japanese	@tparam	Client	コールバック関数として使用するメソッドが含まれたクラスの型
		@~japanese	@tparam	Method	コールバック関数として使用するメソッドの型
		@~japanese	@tparam Parameter	コールバック関数に渡されるユーザー用パラメータの型
		@~japanese	@param[in]	pINode	コールバック関数の登録するノードの INode インターフェースポインター
		@~japanese	@param[in]	client	コールバックさせるメソッドを含んだオブジェクト
		@~japanese	@param[in]	member	コールバック関数として使用するメソッド
		@~japanese	@param[in]	param	コールバック関数に渡されるユーザー用パラメータ
		@~japanese	@param[in]	callbackType	コールバック関数のタイプ
		@~japanese	@return	IStRegisteredCallbackReleasable インターフェースポインター。
		@~japanese	@attention	コールバック関数の登録を解除するには IStRegisteredCallbackReleasable::Release() を呼び出します。
		@~japanese	@exception	メモリー確保に失敗した場合は、例外 GenICam::GenericException が発生します。
	*/
	template<class Client, class Member, class Parameter>
	IStRegisteredCallbackReleasable *RegisterCallback(GenApi::INode *pINode, Client& client, Member member, Parameter param, GenApi::ECallbackType callbackType = GenApi::cbPostInsideLock)
	{
		try
		{
			CClassMethod_NodeCallbackEx<Client, Member, Parameter> *pMember_NodeCallbackEx = new CClassMethod_NodeCallbackEx<Client, Member, Parameter>(pINode, client, member, param, callbackType);
			pMember_NodeCallbackEx->RegisterCallback();
			return(pMember_NodeCallbackEx);
		}
		catch (const std::bad_alloc &e)
		{
			throw BAD_ALLOC_EXCEPTION(e.what());
		}
	}

}

#endif //STAPI_GENAPI_CALLBACK_EX_H__
