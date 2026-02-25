//------------------------------------------------------------------------------
//  StApi
//------------------------------------------------------------------------------
/*!
@ingroup	StApiTL_PublicImpl
@file	CStAutoPtr.h
@~english
	@details	CStAutoPtr definition
@~japanese
	@details	クラス CStAutoPtrの定義
*/
#ifndef STAUTOPTR_H__
#define STAUTOPTR_H__

namespace StApi
{
	// ---------------------------------------------------------------------
	// class CStAutoPtr
	// ---------------------------------------------------------------------
	/*!
		@ingroup	StApiTL_PublicImpl
		@~english
			@brief	This class implements auto finalization of the assigned interface pointer.
			@details      This class implements auto finalization of the assigned interface pointer.
			@tparam	T	Interface which is invoked during the termination process.
			@tparam UT	Interface for user to control.
		@~japanese
			@brief	指定されたインターフェースポインターの終了処理を自動化するクラスの実装
			@details	指定されたインターフェースポインターの終了処理を自動化するクラスの実装
			@tparam	T	終了処理の呼び出しに使用されるインタフェース
			@tparam UT	ユーザーが制御に使用するインターフェース
	*/
	template<class T, class UT>
	class CStAutoPtr
	{
	public:
		/*!
			@~english
				@brief	Default constructor.
				@details	Default constructor.
				@exception	None.
			@~japanese
				@brief	保持するインターフェースポインターが指定されないコンストラクタ
				@details	保持するインターフェースポインターが指定されないコンストラクタ
				@exception	なし
		*/
		CStAutoPtr() : m_pT(NULL)
		{
		}

		/*! 
			@~english
				@brief	Constructor with specified pointer to be invoked during termination process.
				@details      Constructor with specified pointer to be invoked during termination process.
				@param[in]	pT	Pointer to the interface, which is invoked during termination process.
				@exception	None.
			@~japanese
				@brief	保持するインターフェースポインターが指定されたコンストラクタ
				@details	保持するインターフェースポインターが指定されたコンストラクタ
				@param[in]	pT	終了処理の呼び出しに使用されるインターフェースポインター
				@exception	なし
		*/
		/*explicit*//* <-Commentary for compatibility*/ CStAutoPtr(T *pT) : m_pT(pT)
		{
		}

		/*!
			@~english
				@brief	Destructor.
				@details	Destructor.
				@attention	Finalization of the assigned interface pointer (T::Release ()) is called.
				@exception	None.
			@~japanese
				@brief	デストラクタ
				@details	デストラクタ
				@attention	保持されているインターフェースに対して終了処理(T::Release())が呼び出されます。
				@exception	なし
		*/
		virtual ~CStAutoPtr()
		{
			try
			{
				Reset();
			}
			catch (...)
			{

			}
		};

		/*!
			@~english
				@brief	Assign new interface pointer.
				@details	Assign new interface pointer.
				@attention	Finalization of the assigned interface pointer (T::Release ()) is called.
				@param	pT	Pointer to the interface, which is for ending the process.
				@exception	Throw out a GenICam::GenericException if T::Release() is failed.
			@~japanese
				@brief	引数で渡されたインターフェースポインターを保持します。
				@details	引数で渡されたインターフェースポインターを保持します。
				@attention	すでに保持されているインターフェースに対して終了処理(T::Release())が呼び出されます。
				@param	pT	新たに保持するインターフェースポインターを指定します。
				@exception	T::Release() が失敗した場合は、例外 GenICam::GenericException が発生します。
		*/
		void Reset(T *pT = NULL)
		{
			if (m_pT)
			{
				// Finalization of the assigned interface pointer is called.
				m_pT->Release();
				m_pT = NULL;
			}

			// Assign new interface pointer.
			m_pT = pT;
		}

		/*!
			@~english
				@brief	Assign new interface pointer.
				@details	Assign new interface pointer.
				@attention	Finalization of the assigned interface pointer (T::Release ()) is called.
				@param[in]	pT	Pointer to the interface, which is for ending the process.
				@return	The holding interface pointer.
				@exception	Throw out a GenICam::GenericException if T::Release() is failed.
			@~japanese
				@brief	引数で渡されたインターフェースポインターを保持します。
				@details	引数で渡されたインターフェースポインターを保持します。
				@attention	すでに保持されているインターフェースに対して終了処理(T::Release())が呼び出されます。
				@param[in]	pT	新たに保持するインターフェースポインターを指定します。
				@return	新たに保持されたインターフェースポインター
				@exception	T::Release() が失敗した場合は、例外 GenICam::GenericException が発生します。
		*/
		T* operator=(T *pT)
		{
			Reset(pT);
			return(m_pT);
		}

		/*!
			@~english
				@brief	Discard the ownership of the assigned interface pointer.
				@details	Discard the ownership of the assigned interface pointer.
				@attention	Finalization of the assigned interface pointer (T::Release ()) will not be called.
				@return	The holding interface pointer.
				@exception	None.
			@~japanese
				@brief	保持されているインターフェースポインターの所有権を破棄します。
				@details	保持されているインターフェースポインターの所有権を破棄します。
				@attention	保持されているインターフェースに対して終了処理(T::Release())は呼び出されません。
				@return	保持されていたインターフェースポインター
				@exception	なし
		*/
		T* Move()
		{
			T *pT = m_pT;
			m_pT = NULL;
			return(pT);
		}

		// Dereference.
		operator UT*(void) const
		{
			if (NULL == m_pT)
			{
				throw LOGICAL_ERROR_EXCEPTION("NULL pointer dereferenced");
			}
			UT *pUT = dynamic_cast<UT*>(m_pT);
			CHECK_DYNAMIC_CAST_POINTER(pUT);
			return(pUT);
		}

        // Dereference.
		UT& operator*(void) const
		{
			if (NULL == m_pT)
			{
				throw LOGICAL_ERROR_EXCEPTION("NULL pointer dereferenced");
			}
			UT *pUT = dynamic_cast<UT*>(m_pT);
			CHECK_DYNAMIC_CAST_POINTER(pUT);
			return *pUT;
        }

        // Dereference.
		UT& operator()(void) const
		{
			if (NULL == m_pT)
			{
				throw LOGICAL_ERROR_EXCEPTION("NULL pointer dereferenced");
			}
			UT *pUT = dynamic_cast<UT*>(m_pT);
			CHECK_DYNAMIC_CAST_POINTER(pUT);
			return *pUT;
        }

		// Dereference.
		UT* operator->() const
		{
			if (NULL == m_pT)
			{
				throw LOGICAL_ERROR_EXCEPTION("NULL pointer dereferenced");
			}
			UT *pUT = dynamic_cast<UT*>(m_pT);
			CHECK_DYNAMIC_CAST_POINTER(pUT);
			return(pUT);
		};

		/*!
			@~english
				@brief	Return true if the interface pointer is valid.
				@details	Return true if the interface pointer is valid.
				@return	The holding interface pointer.
				@exception	None.
			@~japanese
				@brief	有効なインターフェースポインターが保持されていることを確認します。
				@details	有効なインターフェースポインターが保持されていることを確認します。
				@return	インターフェースポインターが保持されている場合、 true が返されます。
				@exception	なし
		*/
		bool IsValid() const
		{
			return m_pT != NULL;
		}
		
		/*!
			@copydoc IsValid()
		*/
		operator bool(void) const
		{
			return(m_pT != NULL);
		}

		// Check if interface pointer is equal.
		bool operator==(const UT* pUT) const
		{
			return(dynamic_cast<UT*>(m_pT) == pUT);
		}

		// Check if interface pointer is equal.
		bool operator==(const T* pT) const
		{
			return(m_pT == pT);
		}

		// Check if interface pointer is equal.
		bool operator==(int nMustBeNull) const
		{
			if (0 != nMustBeNull)
			{
				throw LOGICAL_ERROR_EXCEPTION("Argument must be NULL");
			}
			return(m_pT == NULL);
		}

		// Check if interface pointer is not equal.
		bool operator!=(const UT* pUT) const
		{
			return(dynamic_cast<UT*>(m_pT) != pUT);
		}

		// Check if interface pointer is not equal.
		bool operator!=(const T* pT) const
		{
			return(m_pT != pT);
		}

		// Check if interface pointer is not equal.
		bool operator!=(int nMustBeNull) const
		{
			if (0 != nMustBeNull)
			{
				throw LOGICAL_ERROR_EXCEPTION("Argument must be NULL");
			}
			return(m_pT != NULL);
		}

	private:
		// Assignment is prohibited.
		CStAutoPtr<T, UT> & operator= (const CStAutoPtr<T, UT> &rhs);
		
		// Copy is prohibited.
		CStAutoPtr(const CStAutoPtr<T, UT> &rhs);

		// Assigned interface pointer
		T *m_pT;
	};
	
}

#endif //STAUTOPTR_H__
