//------------------------------------------------------------------------------
//  StApi
//------------------------------------------------------------------------------
/*!
@ingroup	StApiIP_PublicInterface
@file
@~english	@details	Definition of interface IStGraphDataBufferList
@~japanese	@details	IStGraphDataBufferList インターフェースの定義
*/
#ifndef ISTGRAPHDATABUFFERLIST_H__
#define ISTGRAPHDATABUFFERLIST_H__

#include "IStGraphDataBuffer.h"

namespace StApi
{
	//---------------------------------------------------------------------
	// interface IStGraphDataBufferList
	//---------------------------------------------------------------------
	/*!
		@ingroup StApiIP_PublicInterface
		@interface IStGraphDataBufferList
		@~english	@brief	Interface for Graph Data List object.
		@~english	@details	Interface for Graph Data List object.
		@~japanese	@brief	グラフデータリスト用インターフェース
		@~japanese	@details	グラフデータリスト用インターフェース
		@since StApi v1.1.1
	*/
	interface PUBLIC_INTERFACE IStGraphDataBufferList
	{
		/*!
			@~english	@brief	Acquire count of the Graph Data.
			@~english	@details	Acquire count of the Graph Data.
			@~english	@return	Count of the Graph Data.
			@~english	@exception	None.
			@~japanese	@brief	グラフデータの数を取得します。
			@~japanese	@details	グラフデータの数を取得します。
			@~japanese	@return	グラフデータの数
			@~japanese	@exception	なし
		*/
		virtual size_t	GetGraphDataBufferCount() const = 0;

		/*!
			@~english	@brief	Acquire IStGraphDataBuffer interface pointer.
			@~english	@details	Acquire IStGraphDataBuffer interface pointer.
			@~english	@param[in] nIndex	Index of the component.
			@~english	@return	IStGraphData interface pointer.
			@~english	@exception	Throw out a GenICam::GenericException if the graph data buffer does not exist.
			@~japanese	@brief	IStGraphDataBuffer インターフェースポインターを取得します。
			@~japanese	@details	IStGraphDataBuffer インターフェースポインターを取得します。
			@~japanese	@param[in] nIndex	取得するグラフデータを指定するインディックス値
			@~japanese	@return	IStGraphData インターフェースポインター
			@~japanese	@exception	バッファが存在しない場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual const IStGraphDataBuffer*	GetIStGraphDataBuffer(size_t nIndex) const = 0;
		
		/*!
			@~english	@brief	Check if the current graph data can be saved as the graph data file format.
			@~english	@details	Check if the current graph data can be saved as the graph data file format.
			@~english	@param[in]	eSGDF	Graph data file format.
			@~english	@return	True if save is supported.
			@~english	@exception	None.
			@~japanese	@brief	指定したフォーマットが現在のグラフデータの保存に対応しているかを確認します。
			@~japanese	@details	指定したフォーマットが現在のグラフデータの保存に対応しているかを確認します。
			@~japanese	@param[in]	eSGDF	グラフデータファイルフォーマット
			@~japanese	@return	対応している場合、 true が返されます。
			@~japanese	@exception	なし
		*/
		virtual bool IsSaveSupported(EStGraphDataFileFormat_t eSGDF) const = 0;

		/*!
			@~english	@brief	Save graph data to file.
			@~english	@details	Save graph data to file.
			@~english	@param[in]	eSGDF	Graph data file format.
			@~english	@param[in]	strFileName	File name.
			@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument. 
			@~japanese	@brief	グラフデータをファイルへ保存します。
			@~japanese	@details	グラフデータをファイルへ保存します。
			@~japanese	@param[in]	eSGDF	グラフデータファイルフォーマット
			@~japanese	@param[in]	strFileName	ファイル名
			@~japanese	@exception	不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void Save(EStGraphDataFileFormat_t eSGDF, const GenICam::gcstring &strFileName) const = 0;

	};
	//---------------------------------------------------------------------
	// interface IStGraphDataBufferListResizable
	//---------------------------------------------------------------------
	/*!
		@ingroup StApiIP_PublicInterface
		@interface IStGraphDataBufferListResizable
		@~english	@brief	Interface for Graph Data List object.
		@~english	@details	Interface for Graph Data List object.
		@~japanese	@brief	グラフデータリスト用インターフェース
		@~japanese	@details	グラフデータリスト用インターフェース
		@since StApi v1.1.1
	*/
	interface PUBLIC_INTERFACE IStGraphDataBufferListResizable : public IStGraphDataBufferList
	{

		/*!
			@~english	@brief	Check if the current graph data can be loaded as the graph data file format.
			@~english	@details	Check if the current graph data can be loaded as the graph data file format.
			@~english	@attention	Currently this only supports StGraphDataFileFormat_StApiRaw.
			@~english	@param[in]	eSGDF	Graph data file format.
			@~english	@return	True if load is supported.
			@~english	@exception	None.
			@~japanese	@brief	指定したフォーマットの読み込みに対応しているかを確認します。
			@~japanese	@details	指定したフォーマットの読み込みに対応しているかを確認します。
			@~japanese	@attention	現在、読み込みに対応しているのは StGraphDataFileFormat_StApiRaw フォーマットのみとなります。
			@~japanese	@param[in]	eSGDF	静止画ファイルフォーマット
			@~japanese	@return	対応している場合、 true が返されます。
			@~japanese	@exception	なし
		*/
		virtual bool IsLoadSupported(EStGraphDataFileFormat_t eSGDF) const = 0;

		/*!
			@~english	@brief	Read graph data from file.
			@~english	@details	Read graph data from file.
			@~english	@attention	Currently this only supports StGraphDataFileFormat_StApiRaw.
			@~english	@param[in]	strFileName	File name.
			@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument. 
			@~japanese	@brief	グラフデータファイルをバッファへ読み込みます。
			@~japanese	@details	グラフデータファイルをバッファへ読み込みます。
			@~japanese	@attention	現在、読み込みに対応しているのは StGraphDataFileFormat_StApiRaw フォーマットのみとなります。
			@~japanese	@param[in]	strFileName	ファイル名
			@~japanese	@exception	不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void Load(const GenICam::gcstring &strFileName) = 0;

		/*!
			@~english	@brief	Create an Graph Data buffer based on the given parameters.
			@~english	@details      Create an Graph Data buffer based on the given parameters.
			@~english	@attention Buffers generated here are deleted automatically when you create the buffers again or when you release the Graph Data Buffer object.
			@~english	@param[in] nComponentCount	Count of the components.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or there is an invalid argument.
			@~japanese	@brief	指定されたパラメータに従ってバッファを作成します。
			@~japanese	@details	指定されたパラメータに従ってバッファを作成します。
			@~japanese	@attention ここで生成されたバッファは、再度バッファを作成した際や IStGraphDataBufferList インターフェースハンドルのRelease時に自動的に削除されます。
			@~japanese	@param[in] nComponentCount	構成要素の数
			@~japanese	@exception	メモリー確保に失敗した場合や不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void CreateBufferList(size_t nComponentCount) = 0;

		/*!
			@~english	@brief	Copy Graph Data.
			@~english	@details	Copy Graph Data.
			@~english	@param[in] pIStGraphDataBufferList	Source of the IStGraphDataBufferList interface pointer to be copied.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or there is an invalid argument.
			@~japanese	@brief	グラフデータをコピーします。
			@~japanese	@details	グラフデータをコピーします。
			@~japanese	@param[in] pIStGraphDataBufferList	コピーしたいグラフデータデータの IStGraphDataBufferList インターフェースポインター
			@~japanese	@exception	メモリー確保に失敗した場合や不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void CopyGraphDataBufferList(const IStGraphDataBufferList *pIStGraphDataBufferList) = 0;

		/*!
			@~english	@brief	Acquire IStGraphDataBufferResizable interface pointer.
			@~english	@details	Acquire IStGraphDataBufferResizable interface pointer.
			@~english	@param[in] nIndex	Index of the component.
			@~english	@return	IStGraphData interface pointer.
			@~english	@exception	Throw out a GenICam::GenericException if the graph data buffer does not exist.
			@~japanese	@brief	IStGraphDataBufferResizable インターフェースポインターを取得します。
			@~japanese	@details	IStGraphDataBufferResizable インターフェースポインターを取得します。
			@~japanese	@param[in] nIndex	取得するグラフデータを指定するインディックス値
			@~japanese	@return	IStGraphData インターフェースポインター
			@~japanese	@exception	バッファが存在しない場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual IStGraphDataBufferResizable *GetIStGraphDataBuffer(size_t nIndex) = 0;
	};
	
	//---------------------------------------------------------------------
	// interface IStGraphDataBufferListResizableReleasable
	//---------------------------------------------------------------------
	/*!
		@ingroup StApiIP_PublicInterface
		@interface IStGraphDataBufferListResizableReleasable
		@~english	@brief	Interface for the Graph Data List Releasable module.
		@~english	@details	Interface for the Graph Data List Releasable module.
		@~japanese	@brief	解放可能なグラフデータリスト用インターフェース
		@~japanese	@details	解放可能なグラフデータリスト用インターフェース
		@since StApi v1.1.1
	*/
	interface PUBLIC_INTERFACE IStGraphDataBufferListResizableReleasable : public IStGraphDataBufferListResizable, public IStReleasable
	{

	};
	
	// ---------------------------------------------------------------------
	// typedef CIStGraphDataBufferListResizablePtr
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiIP_PublicImpl
		@typedef CIStGraphDataBufferListResizablePtr
		@~english	@brief	This class is for lifetime management of IStGraphDataBufferListReleasable.
		@~english	@details	This class is for lifetime management of IStGraphDataBufferListReleasable. The destructor of this class will automatically call IStGraphDataBufferReleasable::Release().
		@~japanese	@brief	IStGraphDataBufferListReleasable インターフェースポインターの自動管理用クラスです。
		@~japanese	@details	IStGraphDataBufferListReleasable インターフェースポインターの自動管理用クラスです。このクラスのデストラクタから IStGraphDataBufferReleasable::Release() が自動的に呼び出されます。
		@since StApi v1.1.1
	*/
	typedef CStAutoPtr<IStGraphDataBufferListResizableReleasable, IStGraphDataBufferListResizable> CIStGraphDataBufferListResizablePtr;
}


#endif //ISTGRAPHDATABUFFERLIST_H__