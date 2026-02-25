//------------------------------------------------------------------------------
//  StApi
//------------------------------------------------------------------------------
/*!
	@ingroup	StApiTL_PublicImpl
	@file	CStAutoPtrArray.h
	@~english
		@details	CStAutoPtrArray declaration
	@~japanese
		@details	クラス CStAutoPtrArrayの定義
*/
#ifndef STAPI_AUTO_PTR_ARRAY_H__
#define STAPI_AUTO_PTR_ARRAY_H__

#include "StApi_Platform.h"

namespace StApi
{
	// ---------------------------------------------------------------------
	// class CStAutoPtrArray
	// ---------------------------------------------------------------------
	/*!
		@ingroup	StApiTL_PublicImpl
		@~english
			@brief	This class represents an array of interface pointers. It will automatically finalize the assigned interface pointers.
			@details	This class represents an array of interface pointers. It will automatically finalize the assigned interface pointers.
			@tparam	T	Interface which is invoked during the termination process.
			@tparam UT	Interface for user to control.
		@~japanese
			@brief	指定されたインターフェースポインターの終了処理を自動化するクラスの実装
			@details	指定されたインターフェースポインターの終了処理を自動化するクラスの実装
			@tparam	T	終了処理の呼び出しに使用されるインタフェース
			@tparam UT	ユーザーが制御に使用するインターフェース
	*/
	template <class T, class UT>
	class ST_API_BASE CStAutoPtrArray
	{
	public:
		/*!
			@~english
				@brief	Default Constructor.
				@details	    Default Constructor.
				@exception	Throw out a GenICam::GenericException if memory allocation is failed.
			@~japanese
				@brief	コンストラクタ
				@details	コンストラクタ
				@exception	メモリー確保に失敗した場合は、例外 GenICam::GenericException が発生します。
		*/
		CStAutoPtrArray();

		/*!
			@~english	@brief	Destructor.
			@~english	@details	Destructor. In destructor, the assigned interface pointers will be finalized by (T::Release ()).
			@~english	@exception	None.
			@~japanese	@brief	デストラクタ。
			@~japanese	@details	デストラクタ。保持されているインターフェースポインターに対して終了処理( T::Release() )が呼び出されます。
			@~japanese	@exception	なし
		*/
		virtual ~CStAutoPtrArray();
		
		/*!
			@~english	@brief	Register the interface pointer to the array.
			@~english	@details	Register the interface pointer to the array.
			@~english	@param[in]	pIDeletable	Interface pointer
			@~english	@return	The number of elements in the array.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed.
			@~japanese	@brief	配列にインターフェースポインターを登録します。
			@~japanese	@details	配列にインターフェースポインターを登録します。
			@~japanese	@param[in]	pIDeletable	インターフェースポインター
			@~japanese	@return	配列内の要素の数を返します。
			@~japanese	@exception	メモリー確保に失敗した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual size_t Register(T* pIDeletable);
		
		
		/*!
			@~english	@brief	Delete target registered interface pointer from the array.
			@~english	@details	Delete target registered interface pointer from the array.
			@~english	@param[in] nIndex	The position of the array element.
			@~english	@return	Interface pointer
			@~english	@exception	Throw out a GenICam::GenericException if the position specified is greater than or equal to the size of the array.
			@~japanese	@brief	配列内のインターフェースポインターの登録を解除します。
			@~japanese	@details	配列内のインターフェースポインターの登録を解除します。
			@~japanese	@param[in] nIndex	登録を解除する配列の要素の位置を指定します。
			@~japanese	@return	インターフェースポインター
			@~japanese	@exception	引数が不正な場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual T* Deregister(size_t nIndex);

		/*!
			@~english	@brief	Get the number of elements in the array.
			@~english	@details	Get the number of elements in the array.
			@~english	@return	The number of elements in the array.
			@~english	@exception	None.
			@~japanese	@brief	配列内の要素の数を取得します。
			@~japanese	@details	配列内の要素の数を取得します。
			@~japanese	@return	配列内の要素の数を返します。
			@~japanese	@exception	なし
		*/
		virtual size_t GetSize() const;

		/*!
			@~english	@brief	Returns an interface pointer of the array element at the specified position.
			@~english	@details	Returns an interface pointer of the array element at the specified position.
			@~english	@param[in] nIndex	The position of the array element.
			@~english	@return	The number of elements in the array.
			@~english	@exception	Throw out a GenICam::GenericException if the position specified is greater than or equal to the size of the array.
			@~japanese	@brief	配列内の要素を取得します。
			@~japanese	@details	配列内の要素を取得します。
			@~japanese	@param[in] nIndex	取得する配列の要素の位置を指定します。
			@~japanese	@return	配列内の要素を返します。
			@~japanese	@exception	引数が不正な場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual UT* operator[](size_t nIndex) const;
		
	private:
		// Copy is prohibited.
		CStAutoPtrArray(CStAutoPtrArray &rhs);

		// Reference is prohibited.
		CStAutoPtrArray & operator= (CStAutoPtrArray &rhs);

		// Heap area creation is prohibited.
		void* operator new(size_t nSize);

		// Array data.
		typedef std::vector<T*> vector_t;
		vector_t *m_pVector;
	};
}
#endif //STAPI_AUTO_PTR_ARRAY_H__

