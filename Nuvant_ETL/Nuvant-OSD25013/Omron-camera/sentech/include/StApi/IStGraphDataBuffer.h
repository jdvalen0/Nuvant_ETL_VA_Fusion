//------------------------------------------------------------------------------
//  StApi
//------------------------------------------------------------------------------
/*!
@ingroup	StApiIP_PublicInterface
@file
@~english	@details	Definition of interface IStGraphDataBuffer
@~japanese	@details	IStGraphDataBuffer インターフェースの定義
*/
#ifndef ISTGRAPHDATABUFFER_H__
#define ISTGRAPHDATABUFFER_H__


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
	//---------------------------------------------------------------------
	// interface IStGraphData
	//---------------------------------------------------------------------
	/*!
		@ingroup StApiIP_PublicInterface
		@interface IStGraphData
		@~english	@brief	Interface for Graph Data object.
		@~english	@details	Interface for Graph Data object.
		@~japanese	@brief	グラフデータ用インターフェース
		@~japanese	@details	グラフデータ用インターフェース
		@since StApi v1.1.1
	*/
	interface PUBLIC_INTERFACE IStGraphData
	{
		/*!
			@~english	@brief	Acquire the type of the graph data.
			@~english	@details	Acquire the type of the graph data.
			@~english	@return	Type of the graph data.
			@~english	@exception	None.
			@~japanese	@brief	データのタイプを取得します。
			@~japanese	@details	データのタイプを取得します。
			@~japanese	@return	データのタイプ
			@~japanese	@exception	なし
		*/
		virtual EStGraphDataType_t GetGraphDataType() const = 0;
		
		/*!
			@~english	@brief	Acquire the type of the data.
			@~english	@details	Acquire the type of the data.
			@~english	@return	Type of the data.
			@~english	@exception	None.
			@~japanese	@brief	データの型を取得します。
			@~japanese	@details	データの型を取得します。
			@~japanese	@return	データの型
			@~japanese	@exception	なし
		*/
		virtual EStNumberDataType_t GetNumberDataType() const = 0;
		
		/*!
			@~english	@brief	Acquire the count of the data.
			@~english	@details	Acquire the count of the data.
			@~english	@return	Count of the data.
			@~english	@exception	None.
			@~japanese	@brief	データの数を取得します。
			@~japanese	@details	データの数を取得します。
			@~japanese	@return	データの数
			@~japanese	@exception	なし
		*/
		virtual size_t GetDataCount() const = 0;

		/*!
			@~english	@brief	Acquire the pointer of the data.
			@~english	@details	Acquire the pointer of the data.
			@~english	@return	Pointer of the data.
			@~english	@exception	None.
			@~japanese	@brief	データへのポインターを取得します。
			@~japanese	@details	データへのポインターを取得します。
			@~japanese	@return	データへのポインター
			@~japanese	@exception	なし
		*/
		virtual void *GetDataPtr() = 0;

		/*!
			@~english	@brief	Acquire the pointer of the data.
			@~english	@details	Acquire the pointer of the data.
			@~english	@return	Pointer of the data.
			@~english	@exception	None.
			@~japanese	@brief	データへのポインターを取得します。
			@~japanese	@details	データへのポインターを取得します。
			@~japanese	@return	データへのポインター
			@~japanese	@exception	なし
		*/
		virtual const void *GetDataPtr() const = 0;


		/*!
			@~english	@brief	Get user context.
			@~english	@details	Get user context.
			@~english	@return	Return user context pointer. If there is no user context data, return NULL.
			@~english	@exception	None.
			@~japanese	@brief	ユーザー用データポインターを取得します。
			@~japanese	@details	ユーザー用データポインターを取得します。
			@~japanese	@return	ユーザー用データポインター。指定されていない場合は、NULLが返されます。
			@~japanese	@exception	なし
		*/
		virtual void* GetUserContext() const = 0;

		/*!
			@~english	@brief	Acquire the graph data information of type uint32_t.
			@~english	@details	Acquire the graph data information of type uint32_t.
			@~english	@param[in] eGDIU	Type of graph data info.
			@~english	@return	Graph data information.
			@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument.
			@~japanese	@brief	グラフデータ情報(uint32_t型)を取得します。
			@~japanese	@details	グラフデータ情報(uint32_t型)を取得します。
			@~japanese	@param[in] eGDIU	グラフデータ情報のタイプ。
			@~japanese	@return	グラフデータ情報
			@~japanese	@exception	不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual uint32_t GetGraphDataInfoUint32(EStGraphDataInfoUint32_t  eGDIU) const = 0;
		
		/*!
			@~english	@brief	Acquire the graph data information of type double.
			@~english	@details	Acquire the graph data information of type double.
			@~english	@param[in] eGDIF	Type of graph data info.
			@~english	@return	Graph data information.
			@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument.
			@~japanese	@brief	グラフデータ情報(double型)を取得します。
			@~japanese	@details	グラフデータ情報(double型)を取得します。
			@~japanese	@param[in] eGDIF	グラフデータ情報のタイプ。
			@~japanese	@return	グラフデータ情報
			@~japanese	@exception	不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual double GetGraphDataInfoFloat64(EStGraphDataInfoFloat64_t eGDIF) const = 0;
	};
	

	//---------------------------------------------------------------------
	// interface IStGraphDataBuffer
	//---------------------------------------------------------------------
	/*!
		@ingroup StApiIP_PublicInterface
		@interface IStGraphDataBuffer
		@~english	@brief	Interface for Graph Data Buffer object.
		@~english	@details	Interface for Graph Data Buffer object.
		@~japanese	@brief	グラフデータバッファ用インターフェース
		@~japanese	@details	グラフデータバッファ用インターフェース
		@since StApi v1.1.1
	*/
	interface PUBLIC_INTERFACE IStGraphDataBuffer
	{
		/*!
			@~english	@brief	Acquire IStGraphData interface pointer.
			@~english	@details	Acquire IStGraphData interface pointer.
			@~english	@return	IStGraphData interface pointer.
			@~english	@exception	Throw out a GenICam::GenericException if the memory for graph data does not been properly allocated.
			@~japanese	@brief	IStGraphData インターフェースポインターを取得します。
			@~japanese	@details	IStGraphData インターフェースポインターを取得します。
			@~japanese	@return	IStGraphData インターフェースポインター
			@~japanese	@exception	グラフデータが存在しない場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual IStGraphData*	GetIStGraphData() = 0;

		/*!
			@~english	@brief	Acquire IStGraphData interface pointer.
			@~english	@details	Acquire IStGraphData interface pointer.
			@~english	@return	IStGraphData interface pointer.
			@~english	@exception	Throw out a GenICam::GenericException if the memory for graph data does not been properly allocated.
			@~japanese	@brief	IStGraphData インターフェースポインターを取得します。
			@~japanese	@details	IStGraphData インターフェースポインターを取得します。
			@~japanese	@return	IStGraphData インターフェースポインター
			@~japanese	@exception	グラフデータが存在しない場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual const IStGraphData*	GetIStGraphData() const = 0;

		/*!
			@~english	@brief	Acquire the size of the buffer.
			@~english	@details	Acquire the size of the buffer.
			@~english	@return	Size of the buffer.
			@~english	@exception	None.
			@~japanese	@brief	バッファーサイズを取得します。
			@~japanese	@details	バッファーサイズを取得します。
			@~japanese	@return	バッファーサイズ
			@~japanese	@exception	なし
		*/
		virtual size_t GetBufferSize() const = 0;

		/*!
			@~english	@brief	Acquire the pointer of the buffer.
			@~english	@details	Acquire the pointer of the buffer.
			@~english	@return	Pointer of the buffer.
			@~english	@exception	None.
			@~japanese	@brief	バッファへのポインターを取得します。
			@~japanese	@details	バッファへのポインターを取得します。
			@~japanese	@return	バッファへのポインター
			@~japanese	@exception	なし
		*/
		virtual void *GetBufferPtr() = 0;

		/*!
			@~english	@brief	Acquire the pointer of the buffer.
			@~english	@details	Acquire the pointer of the buffer.
			@~english	@return	Pointer of the buffer.
			@~english	@exception	None.
			@~japanese	@brief	バッファへのポインターを取得します。
			@~japanese	@details	バッファへのポインターを取得します。
			@~japanese	@return	バッファへのポインター
			@~japanese	@exception	なし
		*/
		virtual const void *GetBufferPtr() const = 0;
		
	};
	
	/*!
		@ingroup StApiIP_PublicInterface
		@interface IStGraphDataBufferResizable
		@~english	@brief	Interface for Resizable Graph Data Buffer object.
		@~english	@details	Interface for Resizable Graph Data Buffer object.
		@~japanese	@brief	サイズ変更可能なグラフデータバッファ用インターフェース
		@~japanese	@details	サイズ変更可能なグラフデータバッファ用インターフェース
		@since StApi v1.1.1
	*/
	interface PUBLIC_INTERFACE IStGraphDataBufferResizable : public IStGraphDataBuffer
	{
		/*!
			@~english	@brief	Copy Graph Data.
			@~english	@details	Copy Graph Data.
			@~english	@param[in] pIStGraphData	Source of the IStGraphDataBuffer interface pointer to be copied.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or there is an invalid argument.
			@~japanese	@brief	グラフデータをコピーします。
			@~japanese	@details	グラフデータをコピーします。
			@~japanese	@param[in] pIStGraphData	コピーしたいグラフデータデータの IStGraphDataBuffer インターフェースポインター
			@~japanese	@exception	メモリー確保に失敗した場合や不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void CopyGraphData(const IStGraphDataBuffer *pIStGraphDataBuffer) = 0;

		
		/*!
			@~english	@brief	Resize Graph Data Buffer.
			@~english	@details	Resize Graph Data Buffer.
			@~english	@param[in] eDataType Type of the data. Currently only StNumberDataType_uint32 supported.
			@~english	@param[in] nDataCount	Count of the data.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or there is an invalid argument.
			@~japanese	@brief	グラフデータバッファをリサイズします。
			@~japanese	@details	グラフデータバッファをリサイズします。
			@~japanese	@param[in] eDataType データの型(現在のバージョンでは、 StNumberDataType_uint32 のみ対応)
			@~japanese	@param[in] nDataCount	グラフデータの数
			@~japanese	@exception	メモリー確保に失敗した場合や不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void Resize(EStNumberDataType_t eDataType, size_t nDataCount) = 0;
		
		/*!
			@~english	@brief	Set the graph data information of type uint32_t.
			@~english	@details	Set the graph data information of type uint32_t.
			@~english	@param[in] eGDIU	Type of graph data info.
			@~english	@param[in] nValue	Graph data information.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or there is an invalid argument.
			@~japanese	@brief	グラフデータ情報(uint32_t型)を設定します。
			@~japanese	@details	グラフデータ情報(uint32_t型)を設定します。
			@~japanese	@param[in] eGDIU	グラフデータ情報のタイプ.
			@~japanese	@param[in] nValue	グラフデータ情報
			@~japanese	@exception	メモリー確保に失敗した場合や不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual	void SetGraphDataInfoUint32(EStGraphDataInfoUint32_t eGDIU, uint32_t nValue) = 0;

		
		/*!
			@~english	@brief	Set the graph data information of type double.
			@~english	@details	Set the graph data information of type double.
			@~english	@param[in] eGDIF	Type of graph data info.
			@~english	@param[in] dblValue	Graph data information.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or there is an invalid argument.
			@~japanese	@brief	グラフデータ情報(double型)を設定します。
			@~japanese	@details	グラフデータ情報(double型)を設定します。
			@~japanese	@param[in] eGDIF	グラフデータ情報のタイプ.
			@~japanese	@param[in] dblValue	グラフデータ情報
			@~japanese	@exception	メモリー確保に失敗した場合や不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual	void SetGraphDataInfoFloat64(EStGraphDataInfoFloat64_t eGDIF, double dblValue) = 0;
	};


	//---------------------------------------------------------------------
	// interface IStGraphDataBufferResizableReleasable
	//---------------------------------------------------------------------
	/*!
		@ingroup IStGraphDataBufferResizableReleasable
		@interface IStGraphDataBufferResizableReleasable
		@~english	@brief	Interface for the GraphData Buffer Releasable module.
		@~english	@details	Interface for the GraphData Buffer Releasable module.
		@~english	@sa	CreateIStGraphDataBufferResizable()
		@~japanese	@brief	解放可能なグラフデータバッファ用インターフェース
		@~japanese	@details	解放可能なグラフデータバッファ用インターフェース
		@~japanese	@sa	CreateIStGraphDataBufferResizable()
		@since StApi v1.1.1
	*/
	interface PUBLIC_INTERFACE IStGraphDataBufferResizableReleasable : public IStGraphDataBufferResizable, public IStReleasable
	{

	};
}
#endif //ISTGRAPHDATABUFFER_H__

