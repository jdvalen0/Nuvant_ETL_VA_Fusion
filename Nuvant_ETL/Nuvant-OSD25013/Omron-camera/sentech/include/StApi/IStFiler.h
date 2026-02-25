//------------------------------------------------------------------------------
//  StApi
//------------------------------------------------------------------------------
/*!
	@ingroup	StApiIP_PublicInterface
	@file	
	@~english	@details	Definition of interface IStFiler
	@~japanese	@details	IStFiler インターフェースの定義
*/
#ifndef ISTFILER_H
#define ISTFILER_H

#include "StApi_TL.h"

#ifdef _MSC_VER
#pragma warning(push)	
#pragma warning(disable : 4819)	
#include "StApi_IPDef.h"
#pragma warning(pop)	
#else
#include "StApi_IPDef.h"
#endif

namespace StApi
{
	// ---------------------------------------------------------------------
	// interface IStFilerInfo
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiIP_PublicInterface
		@interface IStFilerInfo
		@~english	@brief	Interface for FilerInfo.
		@~english	@details	Interface for FilerInfo.
		@~japanese	@brief	ファイラー情報用インターフェース
		@~japanese	@details	ファイラー情報用インターフェース
	*/
	interface IStFilerInfo
	{
		/*!
			@~english	@brief	Acquire filer type.
			@~english	@details	Acquire filer type.
			@~english	@return	Filer type.
			@~english	@exception	None.
			@~japanese	@brief	ファイラータイプを取得します。
			@~japanese	@details	ファイラータイプを取得します。
			@~japanese	@return	ファイラータイプ
			@~japanese	@exception	なし
		*/
		virtual EStFilerType_t GetFilerType() const = 0;

		/*!
			@~english	@brief	Acquire filer name.
			@~english	@details	Acquire filer name.
			@~english	@return	Filer name.
			@~english	@exception	None.
			@~japanese	@brief	ファイラー名を取得します。
			@~japanese	@details	ファイラー名を取得します。
			@~japanese	@return	ファイラー名
			@~japanese	@exception	なし
		*/
		virtual GenICam::gcstring GetFilerName() const = 0;
	};

	// ---------------------------------------------------------------------
	// interface IStFiler
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiIP_PublicInterface
		@interface IStFiler
		@~english	@brief	Interface for Filer.
		@~english	@details	Interface for Filer.
		@sa	CreateIStFiler()
		@~japanese	@brief	ファイラー用インターフェース
		@~japanese	@details	ファイラー用インターフェース
		@sa	CreateIStFiler()
	*/
	interface PUBLIC_INTERFACE IStFiler : public IStRegisterCallback
	{
		/*!
			@~english	@brief	Acquire IStFilerInfo interface pointer.
			@~english	@details	Acquire IStFilerInfo interface pointer.
			@~english	@return	IStFilerInfo interface pointer.
			@~english	@exception	None.
			@~japanese	@brief	IStFilerInfo インターフェースポインターを取得します。
			@~japanese	@details	IStFilerInfo インターフェースポインターを取得します。
			@~japanese	@return	IStFilerInfo インターフェースポインター
			@~japanese	@exception	なし
		*/
		virtual IStFilerInfo *GetIStFilerInfo() const = 0;

		/*!
			@~english	@brief	Acquire INodeMap interface pointer.
			@~english	@details	Acquire INodeMap interface pointer.
			@~english	@return	INodeMap interface pointer.
			@~english	@exception	None.
			@~japanese	@brief	INodeMap インターフェースポインターを取得します。
			@~japanese	@details	INodeMap インターフェースポインターを取得します。
			@~japanese	@return	INodeMap インターフェースポインター
			@~japanese	@exception	なし
		*/
		virtual GenApi::INodeMap *GetINodeMap() = 0;
	};

	// ---------------------------------------------------------------------
	// interface IStFilerReleasable
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiIP_PublicInterface
		@interface IStFilerReleasable
		@~english	@brief	Interface for FilerReleasable.
		@~english	@details	Interface for FilerReleasable.
		@sa	CreateIStFiler()
		@~japanese	@brief	解放可能なファイラー用インターフェース
		@~japanese	@details	解放可能なファイラー用インターフェース
		@sa	CreateIStFiler()
	*/
	interface PUBLIC_INTERFACE IStFilerReleasable : public IStFiler, public IStReleasable
	{

	};

}
#endif //ISTFILER_H



