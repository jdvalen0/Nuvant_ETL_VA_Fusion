//------------------------------------------------------------------------------
//  StApi
//------------------------------------------------------------------------------
/*!
	@ingroup	StApiTL_PublicImpl
	@file	CStCallback.h
	@~english	@details  Definition of CStCallback and other callback related functions
	@~japanese	@details	RegisterCallback およびコールバック関数関連クラスの定義
*/
#ifndef ST_CALLBACK_H__
#define ST_CALLBACK_H__

#include "IStCallback.h"
#include "CStAutoPtr.h"

namespace StApi
{
	//---------------------------------------------------------------------
	// class CStCallback
	//---------------------------------------------------------------------
	/*!
		@~english	@brief	Callback base class
		@~english	@details	Callback base class
		@~japanese	@brief	StApi インターフェースポインター用コールバックインスタンス用クラス
		@~japanese	@details	StApi インターフェースポインター用コールバックインスタンス用クラス
	*/
	class CStCallback : public StApi::IStCallback, public IStRegisteredCallbackReleasable
	{
	public:
		// Constructor.
		explicit CStCallback(StApi::IStRegisterCallback *pIStRegisterCallback) : m_pIStRegisterCallback(pIStRegisterCallback), m_hCallback(NULL) {};

		// Virtual destructor.
		virtual ~CStCallback(){};
		
		// Register a callback function.
		void Register()
		{
			if(m_hCallback == NULL)
			{
				m_hCallback = m_pIStRegisterCallback->RegisterCallback(this);
			}
		}
		
		// Deregister a callback function.
		void Release()
		{
			if(m_hCallback)
			{
				m_pIStRegisterCallback->DeregisterCallback(m_hCallback);
			}
		}
	
	private:
		// IStRegisterCallback interface pointer for this callback entry.
		StApi::IStRegisterCallback * const m_pIStRegisterCallback;

		// Callback function registration identifier
		StApiCallbackHandle_t	m_hCallback;

		//! no assignment operator
		const CStCallback& operator = (const CStCallback&);
	};

	/*************************************************************************/
	// C functions as callbacks
	/*************************************************************************/
	
	//---------------------------------------------------------------------
	// class CFlatFunction_StCallback
	//---------------------------------------------------------------------
	/*!
		@~english	@brief	Callback with C-style function
		@~english	@details	Callback with C-Style function
		@~english	@tparam	Function	Type of the callback function.
		@~english	@tparam Parameter	Type of the argument for the callback function.
		@~japanese	@brief	C関数をコールバック関数として登録するために使用されるクラス
		@~japanese	@details	C関数をコールバック関数として登録するために使用されるクラス
		@~japanese	@tparam	Function	コールバック関数の型
		@~japanese	@tparam Parameter	コールバック関数に渡されるユーザー用パラメータの型
	*/
	template <class Function, class Parameter>
	class CFlatFunction_StCallback : public CStCallback
	{
	public:
		// Constructor.
		CFlatFunction_StCallback(StApi::IStRegisterCallback *pIStRegisterCallback, Function *pFunc, Parameter Param) :
		  CStCallback(pIStRegisterCallback), m_pFunc(pFunc), m_Param(Param)
		  {
		  };

		// Virtual destructor.
		virtual ~CFlatFunction_StCallback(){};

        // Execute operation: call the function.
		virtual void operator()(IStCallbackParamBase *pIStCallbackParamBase) throw()
		{
			if(m_pFunc)
			{
				m_pFunc(pIStCallbackParamBase, m_Param);
			}
		};

		// Destroy the object.
		virtual void Destroy() throw()
		{
			delete this;
		}
	private:
		Function * const m_pFunc;
		Parameter const m_Param;
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
		@~english	@param[in]	pIStRegisterCallback	IStRegisterCallback interface pointer for registering the callback function.
		@~english	@param[in]	pFunc	Callback function pointer.
		@~english	@param[in]	param	Argument to the callback function.
		@~english	@return	IStRegisteredCallbackReleasable interface pointer.
		@~english	@attention	When deregistering a callback function, IStRegisteredCallbackReleasable::Release() will be called.
		@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed.
		@~japanese	@brief	C関数をコールバック関数として登録します。
		@~japanese	@details	C関数をコールバック関数として登録します。
		@~japanese	@tparam	Function	コールバック関数の型
		@~japanese	@tparam Parameter	コールバック関数に渡されるユーザー用パラメータの型
		@~japanese	@param[in]	pIStRegisterCallback	コールバック関数の登録に使用する IStRegisterCallback インターフェースポインター
		@~japanese	@param[in]	pFunc	コールバック関数ポインタ
		@~japanese	@param[in]	param	コールバック関数に渡されるユーザー用パラメータ
		@~japanese	@return	IStRegisteredCallbackReleasable インターフェースポインター。
		@~japanese	@attention	コールバック関数の登録を解除するには IStRegisteredCallbackReleasable::Release() を呼び出します。
		@~japanese	@exception	メモリー確保に失敗した場合は、例外 GenICam::GenericException が発生します。
	*/
	template<class Function, class Parameter>
	IStRegisteredCallbackReleasable *RegisterCallback(StApi::IStRegisterCallback *pIStRegisterCallback, Function *pFunc, Parameter param)
	{
		CStCallback *pCStCallback = NULL;
		try
		{
			pCStCallback = new CFlatFunction_StCallback<Function, Parameter>(pIStRegisterCallback, pFunc, param);
			pCStCallback->Register();
		}
		catch (const std::bad_alloc &e)
		{
			throw BAD_ALLOC_EXCEPTION(e.what());
		}
		return(pCStCallback);
	}

	

	/*************************************************************************/
	// C++ Member function as callbacks
	/*************************************************************************/
	//---------------------------------------------------------------------
	// class CClassMethod_StCallback
	//---------------------------------------------------------------------
	/*!
		@~english	@brief	Container for a member function pointer (C++ class member as callback).
		@~english	@details	Container for a member function pointer (C++ class member as callback).
		@~english	@tparam	Client	Class of the callback method.
		@~english	@tparam	Method	Type of the callback method.
		@~english	@tparam Parameter	Type of the argument for the callback function.
		@~japanese	@brief	C++クラスメソッドをコールバック関数として登録するために使用されるクラス
		@~japanese	@details	C++クラスメソッドをコールバック関数として登録するために使用されるクラス
		@~japanese	@tparam	Client	コールバック関数として使用するメソッドが含まれたクラス
		@~japanese	@tparam	Method	コールバック関数として使用するメソッド
		@~japanese	@tparam Parameter	コールバック関数に渡されるユーザー用パラメータの型
	*/
	template <class Client, class Method, class Parameter>
	class CClassMethod_StCallback : public CStCallback
	{
	public:
		// Method type.
		typedef void (Client::*PMETHOD_TYPE)(IStCallbackParamBase *, Parameter);

		// Constructor.
		CClassMethod_StCallback(StApi::IStRegisterCallback *pIStRegisterCallback, Client& client, Method method, Parameter Param) :
		  CStCallback(pIStRegisterCallback), m_Client(client), m_pMethod(method), m_Param(Param)
		  {
		  };

		// Virtual destructor.
		virtual ~CClassMethod_StCallback(){};

		// Execute operation: call the function.
		virtual void operator()(IStCallbackParamBase *pIStCallbackParamBase) throw()
		{
			if(m_pMethod)
			{
				(m_Client.*m_pMethod)(pIStCallbackParamBase, m_Param);
			}
		};


		// Destroy the object.
		virtual void Destroy() throw()
		{
			delete this;
		}
	private:
		Client& m_Client;
		PMETHOD_TYPE const m_pMethod;
		Parameter const m_Param;
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
		@~english	@param[in]	pIStRegisterCallback	IStRegisterCallback interface pointer for registering the callback function.
		@~english	@param[in]	client	A reference to object which the method function belongs to.
		@~english	@param[in]	method	Indicate the pointer to the class method.
		@~english	@param[in]	param	Argument for the callback function.
		@~english	@return	IStRegisteredCallbackReleasable interface pointer.
		@~english	@attention	When deregistering a callback function, IStRegisteredCallbackReleasable::Release() will be called.
		@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed.
		@~japanese	@brief	C++クラスメソッドをコールバック関数として登録します。
		@~japanese	@details	C++クラスメソッドをコールバック関数として登録します。
		@~japanese	@tparam	Client	コールバック関数として使用するメソッドが含まれたクラス
		@~japanese	@tparam	Method	コールバック関数として使用するメソッド
		@~japanese	@tparam Parameter	コールバック関数に渡されるユーザー用パラメータの型
		@~japanese	@param[in]	pIStRegisterCallback	コールバック関数の登録に使用する IStRegisterCallback インターフェースポインター
		@~japanese	@param[in]	client	コールバック関数として使用するメソッドが含まれたクラスインスタンスへの参照
		@~japanese	@param[in]	method	コールバック関数として使用するクラスメソッド
		@~japanese	@param[in]	param	コールバック関数に渡されるユーザー用パラメータ
		@~japanese	@return	IStRegisteredCallbackReleasable インターフェースポインター。
		@~japanese	@attention	コールバック関数の登録を解除するには IStRegisteredCallbackReleasable::Release() を呼び出します。
		@~japanese	@exception	メモリー確保に失敗した場合は、例外 GenICam::GenericException が発生します。
	*/
	template<class Client, class Method, class Parameter>
	IStRegisteredCallbackReleasable *RegisterCallback(StApi::IStRegisterCallback *pIStRegisterCallback, Client &client, Method method, Parameter param)
	{
		CStCallback *pCStCallback = NULL;
		try
		{
			pCStCallback = new CClassMethod_StCallback<Client, Method, Parameter>(pIStRegisterCallback, client, method, param);
			pCStCallback->Register();
		}
		catch (const std::bad_alloc &e)
		{
			throw BAD_ALLOC_EXCEPTION(e.what());
		}
		return(pCStCallback);
	}

	// ---------------------------------------------------------------------
	// typedef CIStRegisteredCallbackPtr
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiTL_PublicImpl
		@typedef CIStRegisteredCallbackPtr
		@~english	@brief	This class is for life time management of IStRegisteredCallback.
		@~english	@details	This class is for life time management of IStRegisteredCallback. The destructor of this class will automatically call IStRegisteredCallbackReleasable::Release().
		@~japanese	@brief	IStRegisteredCallbackReleasable インターフェースポインターの自動管理用クラスです。
		@~japanese	@details	IStRegisteredCallbackReleasable インターフェースポインターの自動管理用クラスです。このクラスのデストラクタから IStRegisteredCallbackReleasable::Release() が自動的に呼び出されます。
	*/
	typedef CStAutoPtr<IStRegisteredCallbackReleasable, IStRegisteredCallback> CIStRegisteredCallbackPtr;
}
#endif //ST_CALLBACK_H__
