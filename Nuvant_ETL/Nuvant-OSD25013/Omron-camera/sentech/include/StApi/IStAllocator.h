//------------------------------------------------------------------------------
//  StApi
//------------------------------------------------------------------------------
/*!
	@ingroup	StApiTL_PublicInterface
	@file	IStAllocator.h
	@~english
		@details	Definition of interface IStAllocator.
	@~japanese
		@details	IStAllocator インターフェースの定義
*/
#ifndef ISTALLOCATOR_H__
#define ISTALLOCATOR_H__

#include "StApi_Platform.h"
#include "StApi_TLDef.h"

namespace StApi
{
	// ---------------------------------------------------------------------
	// interface IStAllocator
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiTL_PublicInterface
		@interface IStAllocator
		@~english
			@brief	Interface for memory allocation.
			@details	Interface for memory allocation.
		@~japanese
			@brief	メモリーの割り当て用インターフェース
			@details	メモリーの割り当て用インターフェース
	*/
	interface PUBLIC_INTERFACE IStAllocator
	{
		/*!
			@~english
				@brief	Allocate memory with requested size.
				@details	Allocate memory with requested size.
				@param[out]	ppBuffer	The pointer to the pointer of the allocated memory.
				@param[in]	nSize	The size of memory to allocate.
				@param[out]	ppContext	The pointer to the pointer of the private data.
				@exception	None.
			@~japanese
				@brief	指定されたサイズのメモリーを割り当てます。
				@details	指定されたサイズのメモリーを割り当てます。
				@param[out]	ppBuffer	割り当てられたメモリーへのポインター
				@param[in]	nSize	割り当てるメモリーのサイズ[Bytes]。
				@param[out]	ppContext	メモリーと関連付けするユーザー用ポインター
				@exception	なし
		*/
		virtual void Allocate(void **ppBuffer, size_t nSize, void **ppContext) throw() = 0;
		
		/*!
			@~english
				@brief	Free the memory.
				@details	Free the memory.
				@param[in]	pBuffer	The pointer to the allocated memory.
				@param[in]	nSize	The size of the allocated memory.
				@param[in]	pContext	The pointer to the private data.
				@exception	None.
			@~japanese
				@brief	メモリーを解放します。
				@details	メモリーを解放します。
				@param[in]	pBuffer	解放するメモリーへのポインター
				@param[in]	nSize	割り当てられたメモリーのサイズ[Bytes]。
				@param[in]	pContext	メモリーと関連付けされているユーザー用ポインター
				@exception	なし
		*/
		virtual void Deallocate(void *pBuffer, size_t nSize, void *pContext) throw() = 0;

		/*!
			@~english
				@brief	Called when the allocator is no longer needed.
				@details	Called when the allocator is no longer needed.
				@exception	None.
			@~japanese
				@brief	割り当てられたメモリーが不要になった際に呼び出されます。
				@details	割り当てられたメモリーが不要になった際に呼び出されます。
				@exception	なし
		*/
		virtual void OnDeregister() throw() = 0;
	};
	
	/*!
		@ingroup StApiTL_PublicInterface
		@interface IStSpecificTypeAllocator
		@~english
			@brief	Interface for memory allocation.
			@details	Interface for memory allocation.
		@~japanese
			@brief	メモリーの割り当て用インターフェース
			@details	メモリーの割り当て用インターフェース
	*/
	interface PUBLIC_INTERFACE IStSpecificTypeAllocator
	{
		/*!
			@~english
				@brief	Allocate memory with requested size.
				@details	Allocate memory with requested size.
				@param[out]	ppBuffer	The pointer to the pointer of the allocated memory.
				@param[in]	eDataType	Type of the data.
				@param[in]	nSize	Count of the data.
				@param[out]	ppContext	The pointer to the pointer of the private data.
				@exception	None.
			@~japanese
				@brief	指定されたサイズのメモリーを割り当てます。
				@details	指定されたサイズのメモリーを割り当てます。
				@param[out]	ppBuffer	割り当てられたメモリーへのポインター
				@param[in] eDataType 割り当てるデータの型
				@param[in]	nCount	割り当てるデータの数
				@param[out]	ppContext	メモリーと関連付けするユーザー用ポインター
				@exception	なし
		*/
		virtual void Allocate(void **ppBuffer, EStNumberDataType_t eDataType, size_t nCount, void **ppContext) throw() = 0;
		
		/*!
			@~english
				@brief	Free the memory.
				@details	Free the memory.
				@param[in]	pBuffer	The pointer to the allocated memory.
				@param[in]	eDataType	Type of the data.
				@param[in]	nSize	Count of the data.
				@param[in]	pContext	The pointer to the private data.
				@exception	None.
			@~japanese
				@brief	メモリーを解放します。
				@details	メモリーを解放します。
				@param[in]	pBuffer	解放するメモリーへのポインター
				@param[in] eDataType 割り当てられたデータの型
				@param[in]	nCount	割り当てられたデータの数
				@param[in]	pContext	メモリーと関連付けされているユーザー用ポインター
				@exception	なし
		*/
		virtual void Deallocate(void *pBuffer, EStNumberDataType_t eDataType, size_t nCount, void *pContext) throw() = 0;

		/*!
			@~english
				@brief	Called when the allocator is no longer needed.
				@details	Called when the allocator is no longer needed.
				@exception	None.
			@~japanese
				@brief	割り当てられたメモリーが不要になった際に呼び出されます。
				@details	割り当てられたメモリーが不要になった際に呼び出されます。
				@exception	なし
		*/
		virtual void OnDeregister() throw() = 0;
	};
}
#endif //ISTALLOCATOR_H__
