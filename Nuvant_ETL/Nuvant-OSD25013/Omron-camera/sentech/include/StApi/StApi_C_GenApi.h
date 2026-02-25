/* This file is encoded in UTF-8,  */
/* but BOM has not been added to accommodate environments not compatible with BOM. */
/*
 StApi C
*/
/*!
	@ingroup	GenApiC_PublicImpl
	@file StApi_C_GenApi.h
	@~english	@details
	@~japanese	@details
*/

#if !defined(STAPI_C_GENAPI_H__)
#define STAPI_C_GENAPI_H__

#include "StApi_C_Def.h"


#ifdef __cplusplus
extern "C" {
	using namespace GenTL;
	using namespace StApi;
#endif /* __cplusplus */


	/*************************************************************************/
	/* GenApi::PublicInterface */
	/*************************************************************************/
	/*!
		@~english	@brief	Check whether reading is possible.
		@~english	@details	Check whether reading is possible.
		@~english	@param[in] AccessMode	Access Mode.
		@~english	@param[out] pbValue	If reading is possible, true is returned.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	読み込みが可能かどうか確認します。
		@~japanese	@details	読み込みが可能かどうか確認します。
		@~japanese	@param[in] AccessMode	アクセスモード
		@~japanese	@param[out] pbValue	読み込みが可能な場合、trueが返されます。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IPublic_IsReadable_t)(EAccessMode AccessMode, bool8_t *pbValue);

	/*!
		@~english	@brief	Check whether writting is possible.
		@~english	@details	Check whether writting is possible.
		@~english	@param[in] AccessMode	Access Mode.
		@~english	@param[out] pbValue	If writting is possible, true is returned.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	書き込みが可能かどうか確認します。
		@~japanese	@details	書き込みが可能かどうか確認します。
		@~japanese	@param[in] AccessMode	アクセスモード
		@~japanese	@param[out] pbValue	書き込みが可能な場合、trueが返されます。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IPublic_IsWritable_t)(EAccessMode AccessMode, bool8_t *pbValue);

	/*!
		@~english	@brief	Check that it is implemented.
		@~english	@details	Check that it is implemented.
		@~english	@param[in] AccessMode	Access Mode.
		@~english	@param[out] pbValue	If it is implemented, ture is returned.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	実装されていることをチェックします。
		@~japanese	@details	実装されていることをチェックします。
		@~japanese	@param[in] AccessMode	アクセスモード
		@~japanese	@param[out] pbValue	実装されている場合、trueが返されます。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IPublic_IsImplemented_t)(EAccessMode AccessMode, bool8_t *pbValue);

	/*!
		@~english	@brief	Check that it is available.
		@~english	@details	Check that it is available.
		@~english	@param[in] AccessMode	Access Mode.
		@~english	@param[out] pbValue	If it is available, ture is returned.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	利用可能であることをチェックします。
		@~japanese	@details	利用可能であることをチェックします。
		@~japanese	@param[in] AccessMode	アクセスモード
		@~japanese	@param[out] pbValue	利用可能な場合、trueが返されます。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IPublic_IsAvailable_t)(EAccessMode AccessMode, bool8_t *pbValue);

	/*!
		@~english	@brief	Computes which access mode the two guards allow together.
		@~english	@details	Computes which access mode the two guards allow together.
		@~english	@param[in] AccessMode1	Access Mode 1.
		@~english	@param[in] AccessMode2	Access Mode 2.
		@~english	@param[out] pnValue	Combined Access Mode.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	アクセスモードを合成します。
		@~japanese	@details	アクセスモードを合成します。
		@~japanese	@param[in] AccessMode1	アクセスモード1
		@~japanese	@param[in] AccessMode2	アクセスモード2
		@~japanese	@param[out] pbValue	合成されたアクセスモード
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IPublic_CombineAccessMode_t)(EAccessMode AccessMode1, EAccessMode AccessMode2, EAccessMode *pnValue);

	/*!
		@~english	@brief	Tests Visibility.
		@~english	@details	Tests Visibility.
		@~english	@param[in] Visibility	Visibility.
		@~english	@param[in] VisiblityMode	VisiblityMode.
		@~english	@param[out] pbValue	Returns true if it is visible.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	可視性の値と可視性のモードから、可視か否かをチェックします。
		@~japanese	@details	可視性の値と可視性のモードから、可視か否かをチェックします。
		@~japanese	@param[in] Visibility	可視性の値
		@~japanese	@param[in] VisiblityMode	可視性のモード
		@~japanese	@param[out] pbValue	可視の場合、trueが返されます。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IPublic_IsVisible_t)(EVisibility Visibility, EVisibility VisiblityMode, bool8_t *pbValue);
	
	/*!
		@~english	@brief	Computes which visibility the two guards allow together.
		@~english	@details	Computes which visibility the two guards allow together.
		@~english	@param[in] Visibility1	Visibility 1.
		@~english	@param[in] Visibility2	Visibility 2.
		@~english	@param[out] pnValue	Combined Visibility.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	可視性を合成します。
		@~japanese	@details	可視性を合成します。
		@~japanese	@param[in] Visibility1	可視性1
		@~japanese	@param[in] Visibility2	可視性2
		@~japanese	@param[out] pbValue	合成された可視性
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IPublic_CombineVisibility_t)(EVisibility Visibility1, EVisibility Visibility2, EVisibility *pnValue);

	/*!
		@~english	@brief	Tests Cacheability.
		@~english	@details	Tests Cacheability.
		@~english	@param[in] CachingMode1	Caching Mode.
		@~english	@param[out] pnValue	If the cache is valid, true is returned.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	キャッシュが有効なモードかどうかチェックします。
		@~japanese	@details	キャッシュが有効なモードかどうかチェックします。
		@~japanese	@param[in] CachingMode	キャッシングモード
		@~japanese	@param[out] pbValue	キャッシュが有効な場合、trueが返されます。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IPublic_IsCacheable_t)(ECachingMode CachingMode, bool8_t *pbValue);

	/*!
		@~english	@brief	Computes which CachingMode results from a combination.
		@~english	@details	Computes which CachingMode results from a combination.
		@~english	@param[in] CachingMode1	Caching Mode 1.
		@~english	@param[in] CachingMode2	Caching Mode 2.
		@~english	@param[out] pnValue	Combined Visibility.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	キャッシングモードを合成します。
		@~japanese	@details	キャッシングモードを合成します。
		@~japanese	@param[in] CachingMode1	キャッシングモード1
		@~japanese	@param[in] CachingMode2	キャッシングモード2
		@~japanese	@param[out] pbValue	合成されたキャッシングモード
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IPublic_CombineCachingMode_t)(ECachingMode CachingMode1, ECachingMode CachingMode2, ECachingMode *pnValue);
	
	/*!
		@~english	@brief	Get interface name.
		@~english	@details	Get interface name.
		@~english	@param[in] eInterfaceType	Interface Type.
		@~english	@param[in,out] szText	Interface name.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	インターフェース名を取得します。
		@~japanese	@details	インターフェース名を取得します。
		@~japanese	@param[in] eInterfaceType	インターフェースタイプ
		@~japanese	@param[in,out] szText	インターフェース名
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IPublic_GetInterfaceNameA_t)(EInterfaceType eInterfaceType, const char **szText);

	/*!
		@ingroup GenApiC_PublicImpl
		@struct GenApi_IPublic_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of public functions.
		@~english	@details	This structure holds the address of the C language wrapper function of public functions.
		@~japanese	@brief	この構造体は パブリック関数 のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は パブリック関数 のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _GenApi_IPublic_Functions_t
	{
		/*!
			@copydoc PGenApi_IPublic_IsReadable_t()
		*/
		PGenApi_IPublic_IsReadable_t	IsReadable;

		/*!
			@copydoc PGenApi_IPublic_IsWritable_t()
		*/
		PGenApi_IPublic_IsWritable_t	IsWritable;

		/*!
			@copydoc PGenApi_IPublic_IsImplemented_t()
		*/
		PGenApi_IPublic_IsImplemented_t	IsImplemented;

		/*!
			@copydoc PGenApi_IPublic_IsAvailable_t()
		*/
		PGenApi_IPublic_IsAvailable_t	IsAvailable;

		/*!
			@copydoc PGenApi_IPublic_CombineAccessMode_t()
		*/
		PGenApi_IPublic_CombineAccessMode_t	CombineAccessMode;

		/*!
			@copydoc PGenApi_IPublic_IsVisible_t()
		*/
		PGenApi_IPublic_IsVisible_t	IsVisible;

		/*!
			@copydoc PGenApi_IPublic_CombineVisibility_t()
		*/
		PGenApi_IPublic_CombineVisibility_t	CombineVisibility;

		/*!
			@copydoc PGenApi_IPublic_IsCacheable_t()
		*/
		PGenApi_IPublic_IsCacheable_t	IsCacheable;

		/*!
		@copydoc PGenApi_IPublic_CombineCachingMode_t()
		*/
		PGenApi_IPublic_CombineCachingMode_t	CombineCachingMode;

		/*!
		@copydoc PGenApi_IPublic_GetInterfaceNameA_t()
		*/
		PGenApi_IPublic_GetInterfaceNameA_t	GetInterfaceNameA;
	}GenApi_IPublic_Functions_t, *PGenApi_IPublic_Functions_t;


	/*************************************************************************/
	/* GenApi::INodeMap */
	/*************************************************************************/
	/*!
		@~english	@brief	Get INodeMap handle.
		@~english	@details	Get INodeMap handle.
		@~english	@param[in] pSourceHandle	Interface handle that is enable to convert to INodeMap interface handle.
		@~english	@param[in,out] pINodeMapHandle	INodeMap interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	INodeMapハンドルを取得します。
		@~japanese	@details	INodeMapハンドルを取得します。
		@~japanese	@param[in] pSourceHandle	INodeMap インターフェースハンドルに変換可能なインターフェースハンドル
		@~japanese	@param[in,out] pINodeHandle	INodeMap インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_INodeMap_GetINodeMap_t)(const PStApiHandle_t pSourceHandle, PStApiHandle_t pINodeMapHandle);

	/*!
		@~english	@brief	Retrieves the nodes from the central map.
		@~english	@details	Retrieves the nodes from the central map.
		@~english	@param[in] pINodeMapHandle	INodeMap interface handle.
		@~english	@param[in,out] pINodeHandleArray	INode interface handles arrray.
		@~english	@param[in,out] pnCount	input:Array size of pINodeHandleArray, output:Count of INode interface handles.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ノードマップからノードを取得します。
		@~japanese	@details	ノードマップからノードを取得します。
		@~japanese	@param[in] pINodeMapHandle	INodeMap インターフェースハンドル配列
		@~japanese	@param[in,out] pINodeHandleArray	INode インターフェースハンドル配列
		@~japanese	@param[in,out] pnCount	配列のサイズを入力し、 INode インターフェースハンドルの数を取得します
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_INodeMap_GetNodes_t)(const PStApiHandle_t pINodeMapHandle, PStApiHandle_t pINodeHandleArray, size_t *pnCount);

	/*!
		@~english	@brief	Retrieves the node from the central map by Name.
		@~english	@details	Retrieves the node from the central map by Name.
		@~english	@param[in] pINodeMapHandle	INodeMap interface handle.
		@~english	@param[in] szName	Name of the node.
		@~english	@param[in,out] pINodeHandle	INode interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	名前を指定してノードマップからノードを取得します。
		@~japanese	@details	名前を指定してノードマップからノードを取得します。
		@~japanese	@param[in] pINodeMapHandle	INodeMap インターフェースハンドル
		@~japanese	@param[in] szName	ノードの名前.
		@~japanese	@param[in,out] pINodeHandle	INode インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_INodeMap_GetNodeA_t)(const PStApiHandle_t pINodeMapHandle, const char *szName, PStApiHandle_t pINodeHandle);
	
	/*!
		@~english	@brief	Invalidates all nodes.
		@~english	@details	Invalidates all nodes.
		@~english	@param[in] pINodeMapHandle	INodeMap interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	すべてのノードを無効化(キャッシュをクリア)します。
		@~japanese	@details	すべてのノードを無効化(キャッシュをクリア)します。
		@~japanese	@param[in] pINodeMapHandle	INodeMap インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_INodeMap_InvalidateNodes_t)(const PStApiHandle_t pINodeMapHandle);
	
	/*!
		@~english	@brief	Get a name of the device.
		@~english	@details	Get a name of the device.
		@~english	@param[in] pINodeMapHandle	INodeMap interface handle.
		@~english	@param[in,out] szText	Name of the device.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	デバイス名を取得します。
		@~japanese	@details	デバイス名を取得します。
		@~japanese	@param[in] pINodeMapHandle	INodeMap インターフェースハンドル
		@~japanese	@param[in,out] szText	デバイス名
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_INodeMap_GetDeviceNameA_t)(const PStApiHandle_t pINodeMapHandle, char *szText, size_t *pnLen);

	/*!
		@~english	@brief	Fires nodes which have a polling time.
		@~english	@details	Fires nodes which have a polling time.
		@~english	@param[in] pINodeMapHandle	INodeMap interface handle.
		@~english	@param[in] ElapsedTime	Elapsed time [ms].
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	Polling timeが指定されているノードへ経過時間を通知し、必要に応じてポーリングを行います。
		@~japanese	@details	Polling timeが指定されているノードへ経過時間を通知し、必要に応じてポーリングを行います。
		@~japanese	@param[in] pINodeMapHandle	INodeMap インターフェースハンドル
		@~japanese	@param[in] ElapsedTime	経過時間[ms]
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_INodeMap_Poll_t)(const PStApiHandle_t pINodeMapHandle, int64_t ElapsedTime);

	/*!
		@~english	@brief	Returns the lock which guards the node map.
		@~english	@details	Returns the lock which guards the node map.
		@~english	@param[in] pINodeMapHandle	INodeMap interface handle.
		@~english	@param[in,out] pLockHandle	ILock handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ノードマップを保護するロックを取得します。
		@~japanese	@details	ノードマップを保護するロックを取得します。
		@~japanese	@param[in] pINodeMapHandle	INodeMap インターフェースハンドル
		@~japanese	@param[in,out] pLockHandle	ILock インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_INodeMap_GetLock_t)(const PStApiHandle_t pINodeMapHandle, PStApiHandle_t pILockHandle);

	/*!
		@~english	@brief	Get the number of nodes in the map.
		@~english	@details	Get the number of nodes in the map.
		@~english	@param[in] pINodeMapHandle	INodeMap interface handle.
		@~english	@param[out] pnValue	The number of nodes in the map.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ノードマップのノードの数を取得します。
		@~japanese	@details	ノードマップのノードの数を取得します。
		@~japanese	@param[in] pINodeMapHandle	INodeMap インターフェースハンドル
		@~japanese	@param[out] pnValue	ノードの数
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_INodeMap_GetNumNodes_t)(const PStApiHandle_t pINodeMapHandle, uint64_t *pnValue);

	
	/*!
		@ingroup GenApiC_PublicImpl
		@struct GenApi_INodeMap_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of INodeMap.
		@~english	@details	This structure holds the address of the C language wrapper function of INodeMap.
		@~japanese	@brief	この構造体は INodeMap のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は INodeMap のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _GenApi_INodeMap_Functions_t
	{
		/*!
			@copydoc PGenApi_INodeMap_GetINodeMap_t()
		*/
		PGenApi_INodeMap_GetINodeMap_t			GetINodeMap;

		/*!
			@copydoc PGenApi_INodeMap_GetNumNodes_t()
		*/
		PGenApi_INodeMap_GetNumNodes_t			GetNumNodes;

		/*!
			@copydoc PGenApi_INodeMap_GetNodes_t()
		*/
		PGenApi_INodeMap_GetNodes_t				GetNodes;

		/*!
			@copydoc PGenApi_INodeMap_GetNodeA_t()
		*/
		PGenApi_INodeMap_GetNodeA_t				GetNodeA;

		/*!
			@copydoc PGenApi_INodeMap_InvalidateNodes_t()
		*/
		PGenApi_INodeMap_InvalidateNodes_t		InvalidateNodes;

		/*!
			@copydoc PGenApi_INodeMap_GetDeviceNameA_t()
		*/
		PGenApi_INodeMap_GetDeviceNameA_t		GetDeviceNameA;

		/*!
			@copydoc PGenApi_INodeMap_Poll_t()
		*/
		PGenApi_INodeMap_Poll_t					Poll;

		/*!
			@copydoc PGenApi_INodeMap_GetLock_t()
		*/
		PGenApi_INodeMap_GetLock_t				GetLock;
	}GenApi_INodeMap_Functions_t, *PGenApi_INodeMap_Functions_t;

	/*************************************************************************/
	/* GenApi::IDeviceInfo */
	/*************************************************************************/
	/*!
		@~english	@brief	Get IDeviceInfo handle.
		@~english	@details	Get IDeviceInfo handle.
		@~english	@param[in] pSourceHandle	Interface handle that is enable to convert to IDeviceInfo interface handle.
		@~english	@param[in,out] pIDeviceInfoHandle	IDeviceInfo interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IDeviceInfoハンドルを取得します。
		@~japanese	@details	IDeviceInfoハンドルを取得します。
		@~japanese	@param[in] pSourceHandle	IDeviceInfo インターフェースハンドルに変換可能なインターフェースハンドル
		@~japanese	@param[in,out] pIDeviceInfoHandle	IDeviceInfo インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IDeviceInfo_GetIDeviceInfo_t)(const PStApiHandle_t pSourceHandle, PStApiHandle_t pIDeviceInfoHandle);

	/*!
		@~english	@brief	Get the model name.
		@~english	@details	Get the model name.
		@~english	@param[in] pIDeviceInfoHandle	IDeviceInfo interface handle.
		@~english	@param[in,out] szText	Name of the model.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	モデル名を取得します。
		@~japanese	@details	モデル名を取得します。
		@~japanese	@param[in] pIDeviceInfoHandle	IDeviceInfo インターフェースハンドル
		@~japanese	@param[in,out] szText	モデル名
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IDeviceInfo_GetModelNameA_t)(const PStApiHandle_t pIDeviceInfoHandle, char *szText, size_t *pnLen);

	/*!
		@~english	@brief	Get the vendor name.
		@~english	@details	Get the vendor name.
		@~english	@param[in] pIDeviceInfoHandle	IDeviceInfo interface handle.
		@~english	@param[in,out] szText	Name of the vendor.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ベンダー名を取得します。
		@~japanese	@details	ベンダー名を取得します。
		@~japanese	@param[in] pIDeviceInfoHandle	IDeviceInfo インターフェースハンドル
		@~japanese	@param[in,out] szText	ベンダー名
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IDeviceInfo_GetVendorNameA_t)(const PStApiHandle_t pIDeviceInfoHandle, char *szText, size_t *pnLen);

	/*!
		@~english	@brief	Get the tool tip.
		@~english	@details	Get the tool tip.
		@~english	@param[in] pIDeviceInfoHandle	IDeviceInfo interface handle.
		@~english	@param[in,out] szText	Tool tip.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ツールチップを取得します。
		@~japanese	@details	ツールチップを取得します。
		@~japanese	@param[in] pIDeviceInfoHandle	IDeviceInfo インターフェースハンドル
		@~japanese	@param[in,out] szText	ツールチップ
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IDeviceInfo_GetToolTipA_t)(const PStApiHandle_t pIDeviceInfoHandle, char *szText, size_t *pnLen);

	/*!
		@~english	@brief	Get the standard name space.
		@~english	@details	Get the standard name space.
		@~english	@param[in] pIDeviceInfoHandle	IDeviceInfo interface handle.
		@~english	@param[in,out] szText	Standard name space.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	標準的なネームスペースを取得します。
		@~japanese	@details	標準的なネームスペースを取得します。
		@~japanese	@param[in] pIDeviceInfoHandle	IDeviceInfo インターフェースハンドル
		@~japanese	@param[in,out] szText	標準的なネームスペース
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IDeviceInfo_GetStandardNameSpaceA_t)(const PStApiHandle_t pIDeviceInfoHandle, char *szText, size_t *pnLen);

	/*!
		@~english	@brief	Get the version of the DLL's GenApi implementation.
		@~english	@details	Get the version of the DLL's GenApi implementation.
		@~english	@param[in] pIDeviceInfoHandle	IDeviceInfo interface handle.
		@~english	@param[out] pnMajor	Major version.
		@~english	@param[out] pnMinor	Minor version.
		@~english	@param[out] pnSubMinor	Sub minor version.
		@~english	@param[out] pnBuild	Buld version.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenApiのバージョンを取得します。
		@~japanese	@details	GenApiのバージョンを取得します。
		@~japanese	@param[in] pIDeviceInfoHandle	IDeviceInfo インターフェースハンドル
		@~japanese	@param[out] pnMajor	メジャーバージョン
		@~japanese	@param[out] pnMinor	マイナーバージョン
		@~japanese	@param[out] pnSubMinor	サブマイナーバージョン
		@~japanese	@param[out] pnBuild	ビルドバージョン
		@~japanese	@return	EStApiCError_t error code.
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IDeviceInfo_GetGenApiVersion_t)(const PStApiHandle_t pIDeviceInfoHandle, uint16_t *pnMajor, uint16_t *pnMinor, uint16_t *pnSubMinor, uint16_t *pnBuild);

	/*!
		@~english	@brief	Get the schema version number.
		@~english	@details	Get the schema version number.
		@~english	@param[in] pIDeviceInfoHandle	IDeviceInfo interface handle.
		@~english	@param[out] pnMajor	Major version.
		@~english	@param[out] pnMinor	Minor version.
		@~english	@param[out] pnSubMinor	Sub minor version.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	Schemaのバージョンを取得します。
		@~japanese	@details	Schemaのバージョンを取得します。
		@~japanese	@param[in] pIDeviceInfoHandle	IDeviceInfo インターフェースハンドル
		@~japanese	@param[out] pnMajor	メジャーバージョン
		@~japanese	@param[out] pnMinor	マイナーバージョン
		@~japanese	@param[out] pnSubMinor	サブマイナーバージョン
		@~japanese	@return	EStApiCError_t error code.
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IDeviceInfo_GetSchemaVersion_t)(const PStApiHandle_t pIDeviceInfoHandle, uint16_t *pnMajor, uint16_t *pnMinor, uint16_t *pnSubMinor);

	/*!
		@~english	@brief	Get the version of the device description file.
		@~english	@details	Get the version of the device description file.
		@~english	@param[in] pIDeviceInfoHandle	IDeviceInfo interface handle.
		@~english	@param[out] pnMajor	Major version.
		@~english	@param[out] pnMinor	Minor version.
		@~english	@param[out] pnSubMinor	Sub minor version.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	XMLファイルのバージョンを取得します。
		@~japanese	@details	XMLファイルのバージョンを取得します。
		@~japanese	@param[in] pIDeviceInfoHandle	IDeviceInfo インターフェースハンドル
		@~japanese	@param[out] pnMajor	メジャーバージョン
		@~japanese	@param[out] pnMinor	マイナーバージョン
		@~japanese	@param[out] pnSubMinor	サブマイナーバージョン
		@~japanese	@return	EStApiCError_t error code.
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IDeviceInfo_GetDeviceVersion_t)(const PStApiHandle_t pIDeviceInfoHandle, uint16_t *pnMajor, uint16_t *pnMinor, uint16_t *pnSubMinor);

	/*!
		@~english	@brief	Get the Guid describing the product.
		@~english	@details	Get the Guid describing the product.
		@~english	@param[in] pIDeviceInfoHandle	IDeviceInfo interface handle.
		@~english	@param[in,out] szText	Guid.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	製品用Guidを取得します。
		@~japanese	@details	製品用Guidを取得します。
		@~japanese	@param[in] pIDeviceInfoHandle	IDeviceInfo インターフェースハンドル
		@~japanese	@param[in,out] szText	Guid
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IDeviceInfo_GetProductGuidA_t)(const PStApiHandle_t pIDeviceInfoHandle, char *szText, size_t *pnLen);

	/*!
		@~english	@brief	Get the Guid describing the product version.
		@~english	@details	Get the Guid describing the product version.
		@~english	@param[in] pIDeviceInfoHandle	IDeviceInfo interface handle.
		@~english	@param[in,out] szText	Guid.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	バージョン用Guidを取得します。
		@~japanese	@details	バージョン用Guidを取得します。
		@~japanese	@param[in] pIDeviceInfoHandle	IDeviceInfo インターフェースハンドル
		@~japanese	@param[in,out] szText	Guid
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IDeviceInfo_GetVersionGuidA_t)(const PStApiHandle_t pIDeviceInfoHandle, char *szText, size_t *pnLen);

	/*!
		@ingroup GenApiC_PublicImpl
		@struct GenApi_IDeviceInfo_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IDeviceInfo.
		@~english	@details	This structure holds the address of the C language wrapper function of IDeviceInfo.
		@~japanese	@brief	この構造体は IDeviceInfo のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IDeviceInfo のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _GenApi_IDeviceInfo_Functions_t
	{
		/*!
			@copydoc PGenApi_IDeviceInfo_GetIDeviceInfo_t()
		*/
		PGenApi_IDeviceInfo_GetIDeviceInfo_t				GetIDeviceInfo;

		/*!
			@copydoc PGenApi_IDeviceInfo_GetModelNameA_t()
		*/
		PGenApi_IDeviceInfo_GetModelNameA_t	GetModelNameA;

		/*!
			@copydoc PGenApi_IDeviceInfo_GetVendorNameA_t()
		*/
		PGenApi_IDeviceInfo_GetVendorNameA_t	GetVendorNameA;

		/*!
			@copydoc PGenApi_IDeviceInfo_GetToolTipA_t()
		*/
		PGenApi_IDeviceInfo_GetToolTipA_t	GetToolTipA;

		/*!
			@copydoc PGenApi_IDeviceInfo_GetStandardNameSpaceA_t()
		*/
		PGenApi_IDeviceInfo_GetStandardNameSpaceA_t	GetStandardNameSpaceA;

		/*!
			@copydoc PGenApi_IDeviceInfo_GetGenApiVersion_t()
		*/
		PGenApi_IDeviceInfo_GetGenApiVersion_t	GetGenApiVersion;

		/*!
			@copydoc PGenApi_IDeviceInfo_GetSchemaVersion_t()
		*/
		PGenApi_IDeviceInfo_GetSchemaVersion_t	GetSchemaVersion;

		/*!
			@copydoc PGenApi_IDeviceInfo_GetDeviceVersion_t()
		*/
		PGenApi_IDeviceInfo_GetDeviceVersion_t	GetDeviceVersion;

		/*!
			@copydoc PGenApi_IDeviceInfo_GetProductGuidA_t()
		*/
		PGenApi_IDeviceInfo_GetProductGuidA_t	GetProductGuidA;

		/*!
			@copydoc PGenApi_IDeviceInfo_GetVersionGuidA_t()
		*/
		PGenApi_IDeviceInfo_GetVersionGuidA_t	GetVersionGuidA;

	}GenApi_IDeviceInfo_Functions_t, *PGenApi_IDeviceInfo_Functions_t;

	/*************************************************************************/
	/* GenApi::IUserData */
	/*************************************************************************/
	/*!
		@~english	@brief	Get IUserData handle.
		@~english	@details	Get IUserData handle.
		@~english	@param[in] pSourceHandle	Interface handle that is enable to convert to IUserData interface handle.
		@~english	@param[in,out] pIUserDataHandle	IUserData interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IUserDataハンドルを取得します。
		@~japanese	@details	IUserDataハンドルを取得します。
		@~japanese	@param[in] pSourceHandle	IUserData インターフェースハンドルに変換可能なインターフェースハンドル
		@~japanese	@param[in,out] pIUserDataHandle	IUserData インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IUserData_GetIUserData_t)(const PStApiHandle_t pSourceHandle, PStApiHandle_t pIUserDataHandle);

	/*!
		@~english	@brief	Returns the stored user defined data.
		@~english	@details	Returns the stored user defined data.
		@~english	@param[in] pIUserDataHandle	IUserData interface handle.
		@~english	@param[out] ppUserData	Stored user defined data.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	保持されているユーザーデータを取得します。
		@~japanese	@details	保持されているユーザーデータを取得します。
		@~japanese	@param[in] pIUserDataHandle	IUserData インターフェースハンドル
		@~japanese	@param[out] ppUserData	ユーザーデータ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IUserData_GetUserData_t)(const PStApiHandle_t pIUserDataHandle, void **ppUserData);

	/*!
		@~english	@brief	Stores user defined data without taking ownership. Returns the previously stored value.
		@~english	@details	Stores user defined data without taking ownership. Returns the previously stored value.
		@~english	@param[in] pIUserDataHandle	IUserData interface handle.
		@~english	@param[in] pUserData	New user defined data.
		@~english	@param[out] ppPrevUserData	Stored user defined data.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	新たにユーザーデータを設定し、事前に保持されていたユーザーデータを取得します。
		@~japanese	@details	新たにユーザーデータを設定し、事前に保持されていたユーザーデータを取得します。
		@~japanese	@param[in] pIUserDataHandle	IUserData インターフェースハンドル
		@~japanese	@param[in] pUserData	新たなユーザーデータ
		@~japanese	@param[out] ppPrevUserData	保持されていたユーザーデータ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IUserData_SetUserData_t)(const PStApiHandle_t pIUserDataHandle, void *pUserData, void **ppPrevUserData);

	/*!
		@ingroup GenApiC_PublicImpl
		@struct GenApi_IUserData_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IUserData.
		@~english	@details	This structure holds the address of the C language wrapper function of IUserData.
		@~japanese	@brief	この構造体は IUserData のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IUserData のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _GenApi_IUserData_Functions_t
	{
		/*!
			@copydoc PGenApi_IUserData_GetIUserData_t()
		*/
		PGenApi_IUserData_GetIUserData_t				GetIUserData;

		/*!
			@copydoc PGenApi_IUserData_GetUserData_t()
		*/
		PGenApi_IUserData_GetUserData_t				GetUserData;

		/*!
			@copydoc PGenApi_IUserData_SetUserData_t()
		*/
		PGenApi_IUserData_SetUserData_t				SetUserData;
	}GenApi_IUserData_Functions_t, *PGenApi_IUserData_Functions_t;
	
	/*************************************************************************/
	/* GenApi::ILock */
	/*************************************************************************/
	/*!
		@~english	@brief	Tries to enter the critical section.
		@~english	@details	Tries to enter the critical section.
		@~english	@param[in] pILockHandle	ILock interface handle.
		@~english	@param[out] pbValue	Returns true if successful
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ロックを試みます。
		@~japanese	@details	ロックを試みます。
		@~japanese	@param[in] pILockHandle	ILock インターフェースハンドル
		@~japanese	@param[out] pbValue	ロックできた場合はtrueを返します。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_ILock_TryLock_t)(const PStApiHandle_t pILockHandle, bool8_t *pbValue);

	/*!
		@~english	@brief	Enters the critical section (may block).
		@~english	@details	Enters the critical section (may block).
		@~english	@param[in] pILockHandle	ILock interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ロックを行います。ブロックされる可能性があります。
		@~japanese	@details	ロックを行います。ブロックされる可能性があります。
		@~japanese	@param[in] pILockHandle	ILock インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_ILock_Lock_t)(const PStApiHandle_t pILockHandle);

	/*!
		@~english	@brief	Leaves the critical section.
		@~english	@details	Leaves the critical section.
		@~english	@param[in] pILockHandle	ILock interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ロックを解除します。
		@~japanese	@details	ロックを解除します。
		@~japanese	@param[in] pILockHandle	ILock インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_ILock_Unlock_t)(const PStApiHandle_t pILockHandle);
	
	/*!
		@ingroup GenApiC_PublicImpl
		@struct GenApi_ILock_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of ILock.
		@~english	@details	This structure holds the address of the C language wrapper function of ILock.
		@~japanese	@brief	この構造体は ILock のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は ILock のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _GenApi_ILock_Functions_t
	{
		/*!
			@copydoc PGenApi_ILock_TryLock_t()
		*/
		PGenApi_ILock_TryLock_t				TryLock;
		
		/*!
			@copydoc PGenApi_ILock_Lock_t()
		*/
		PGenApi_ILock_Lock_t				Lock;
		
		/*!
			@copydoc PGenApi_ILock_Unlock_t()
		*/
		PGenApi_ILock_Unlock_t				Unlock;
	}GenApi_ILock_Functions_t, *PGenApi_ILock_Functions_t;

	/*************************************************************************/
	/* GenApi::INode */
	/*************************************************************************/
	/*!
		@~english	@brief	Get INode handle.
		@~english	@details	Get INode handle.
		@~english	@param[in] pSourceHandle	Interface handle that is enable to convert to INode interface handle.
		@~english	@param[in,out] pINodeHandle	INode interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	INodeハンドルを取得します。
		@~japanese	@details	INodeハンドルを取得します。
		@~japanese	@param[in] pSourceHandle	INode インターフェースハンドルに変換可能なインターフェースハンドル
		@~japanese	@param[in,out] pINodeHandle	INode インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_INode_GetINode_t)(const PStApiHandle_t pSourceHandle, PStApiHandle_t pINodeHandle);

	/*!
		@~english	@brief	Get node name.
		@~english	@details	Get node name.
		@~english	@param[in] pINodeHandle	INode interface handle.
		@~english	@param[in] FullQualified If you specify true, it is qualified with a string representing the namespace. The initial value for C ++ language is false.
		@~english	@param[in,out] szText	Node name.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ノード名を取得します。
		@~japanese	@details	ノード名を取得します。
		@~japanese	@param[in] pINodeHandle	INode インターフェースハンドル
		@~japanese	@param[in] FullQualified	trueを指定した場合、名前空間を表す文字列で修飾されます。 C++言語用の初期値はfalseです。
		@~japanese	@param[in,out] szText	ノード名
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_INode_GetNameA_t)(const PStApiHandle_t pINodeHandle, bool8_t FullQualified, char *szText, size_t *pnLen);

	/*!
		@~english	@brief	Get name space.
		@~english	@details	Get name space.
		@~english	@param[in] pINodeHandle	INode interface handle.
		@~english	@param[out] pnValue	Name space enumaration value.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ネームスペースを取得します。
		@~japanese	@details	ネームスペースを取得します。
		@~japanese	@param[in] pINodeHandle	INode インターフェースハンドル
		@~japanese	@param[out] pnValue	ネームスペース値を取得します。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_INode_GetNameSpace_t)(const PStApiHandle_t pINodeHandle, ENameSpace *pnValue);

	/*!
		@~english	@brief	Get the recommended visibility of the node.
		@~english	@details	Get the recommended visibility of the node.
		@~english	@param[in] pINodeHandle	INode interface handle.
		@~english	@param[out] pnValue	The recommended visibility of the node.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ノード推奨される可視性を取得します。
		@~japanese	@details	ノード推奨される可視性を取得します。
		@~japanese	@param[in] pINodeHandle	INode インターフェースハンドル
		@~japanese	@param[out] pnValue	推奨される可視性。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_INode_GetVisibility_t)(const PStApiHandle_t pINodeHandle, EVisibility *pnValue);

	/*!
		@~english	@brief	Indicates that the node's value may have changed. Fires the callback on this and all dependent nodes.
		@~english	@details	Indicates that the node's value may have changed. Fires the callback on this and all dependent nodes.
		@~english	@param[in] pINodeHandle	INode interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ノードのキャッシュされた値を無効化し、このノードと依存するすべてのノードに対するコールバック関数を呼び出します。
		@~japanese	@details	ノードのキャッシュされた値を無効化し、このノードと依存するすべてのノードに対するコールバック関数を呼び出します。
		@~japanese	@param[in] pINodeHandle	INode インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_INode_InvalidateNode_t)(const PStApiHandle_t pINodeHandle);

	/*!
		@~english	@brief	Is the node value cachable.
		@~english	@details	Is the node value cachable.
		@~english	@param[in] pINodeHandle	INode interface handle.
		@~english	@param[out] pbValue	True if the node value can be cached.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ノードの値がキャッシュ可能かどうかチェックします。
		@~japanese	@details	ノードの値がキャッシュ可能かどうかチェックします。
		@~japanese	@param[in] pINodeHandle	INode インターフェースハンドル
		@~japanese	@param[out] pbValue	キャッシュ可能な場合、trueが返されます。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_INode_IsCachable_t)(const PStApiHandle_t pINodeHandle, bool8_t *pbValue);

	/*!
		@~english	@brief	Is the AccessMode cachable.
		@~english	@details	Is the AccessMode cachable.
		@~english	@param[in] pINodeHandle	INode interface handle.
		@~english	@param[out] pbValue	True if the AccessMode can be cached.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	アクセスモードがキャッシュ可能かどうかチェックします。
		@~japanese	@details	アクセスモードがキャッシュ可能かどうかチェックします。
		@~japanese	@param[in] pINodeHandle	INode インターフェースハンドル
		@~japanese	@param[out] pbValue	キャッシュ可能な場合、trueが返されます。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_INode_IsAccessModeCacheable_t)(const PStApiHandle_t pINodeHandle, EYesNo *pnValue);

	/*!
		@~english	@brief	Get Caching Mode.
		@~english	@details	Get Caching Mode.
		@~english	@param[in] pINodeHandle	INode interface handle.
		@~english	@param[out] pnValue	Caching Mode.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	キャッシングモードを取得します。
		@~japanese	@details	キャッシングモードを取得します。
		@~japanese	@param[in] pINodeHandle	INode インターフェースハンドル
		@~japanese	@param[out] pnValue	キャッシングモード。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_INode_GetCachingMode_t)(const PStApiHandle_t pINodeHandle, ECachingMode *pnValue);

	/*!
		@~english	@brief	Get recommended polling time (for not cachable nodes).
		@~english	@details	Get recommended polling time (for not cachable nodes).
		@~english	@param[in] pINodeHandle	INode interface handle.
		@~english	@param[out] pnValue	Recommended polling time.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	キャッシングが無効なノードに対する推奨されるポーリング間隔を取得します。
		@~japanese	@details	キャッシングが無効なノードに対する推奨されるポーリング間隔を取得します。
		@~japanese	@param[in] pINodeHandle	INode インターフェースハンドル
		@~japanese	@param[out] pnValue	ポーリング間隔
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_INode_GetPollingTime_t)(const PStApiHandle_t pINodeHandle, int64_t *pnValue);
	
	/*!
		@~english	@brief	Get a short description of the node.
		@~english	@details	Get a short description of the node.
		@~english	@param[in] pINodeHandle	INode interface handle.
		@~english	@param[in,out] szText	Short description of the node.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	短い説明文を取得します。
		@~japanese	@details	短い説明文を取得します。
		@~japanese	@param[in] pINodeHandle	INode インターフェースハンドル
		@~japanese	@param[in,out] szText	短い説明文
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_INode_GetToolTipA_t)(const PStApiHandle_t pINodeHandle, char *szText, size_t *pnLen);
	
	/*!
		@~english	@brief	Get a long description of the node.
		@~english	@details	Get a long description of the node.
		@~english	@param[in] pINodeHandle	INode interface handle.
		@~english	@param[in,out] szText	Long description of the node.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	長い説明文を取得します。
		@~japanese	@details	長い説明文を取得します。
		@~japanese	@param[in] pINodeHandle	INode インターフェースハンドル
		@~japanese	@param[in,out] szText	長い説明文
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_INode_GetDescriptionA_t)(const PStApiHandle_t pINodeHandle, char *szText, size_t *pnLen);

	/*!
		@~english	@brief	Get a name string for display.
		@~english	@details	Get a name string for display.
		@~english	@param[in] pINodeHandle	INode interface handle.
		@~english	@param[in,out] szText	Name string for display.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	表示に使用される名称を取得します。
		@~japanese	@details	表示に使用される名称を取得します。
		@~japanese	@param[in] pINodeHandle	INode インターフェースハンドル
		@~japanese	@param[in,out] szText	表示に使用される名称
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_INode_GetDisplayNameA_t)(const PStApiHandle_t pINodeHandle, char *szText, size_t *pnLen);

	/*!
		@~english	@brief	Get a name of the device.
		@~english	@details	Get a name of the device.
		@~english	@param[in] pINodeHandle	INode interface handle.
		@~english	@param[in,out] szText	Name of the device.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	デバイス名を取得します。
		@~japanese	@details	デバイス名を取得します。
		@~japanese	@param[in] pINodeHandle	INode インターフェースハンドル
		@~japanese	@param[in,out] szText	デバイス名
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_INode_GetDeviceNameA_t)(const PStApiHandle_t pINodeHandle, char *szText, size_t *pnLen);

	/*!
		@~english	@brief	Get nodes this node directly depends on.
		@~english	@details	Get nodes this node directly depends on.
		@~english	@param[in] pINodeHandle	INode interface handle.
		@~english	@param[in] LinkType	The link type. Default value for C++ is ctReadingChildren.
		@~english	@param[in,out] pINodeHandleArray	INode interface handles array.
		@~english	@param[in,out] pnCount	Input : Size of the array. Output : Count of the handles.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	このノードが依存しているノードを取得します。
		@~japanese	@details	このノードが依存しているノードを取得します。
		@~japanese	@param[in] pINodeHandle	INode インターフェースハンドル
		@~japanese	@param[in] LinkType	リンクタイプ C++用の初期値はctReadingChildrenです。
		@~japanese	@param[in,out] pINodeHandleArray	INode インターフェースハンドル配列
		@~japanese	@param[in,out] pnCount	配列のサイズを入力し、ハンドルの数を受け取ります。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_INode_GetChildren_t)(const PStApiHandle_t pINodeHandle, ELinkType LinkType, PStApiHandle_t pINodeHandleArray, size_t *pnCount);

	/*!
		@~english	@brief	Get nodes this node is directly depending on.
		@~english	@details	Get nodes this node is directly depending on.
		@~english	@param[in] pINodeHandle	INode interface handle.
		@~english	@param[in,out] pINodeHandleArray	INode interface handles array.
		@~english	@param[in,out] pnCount	Input : Size of the array. Output : Count of the handles.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	このノードに依存しているノードを取得します。
		@~japanese	@details	このノードに依存しているノードを取得します。
		@~japanese	@param[in] pINodeHandle	INode インターフェースハンドル配列
		@~japanese	@param[in,out] pINodeHandleArray	INode interface handle.
		@~japanese	@param[in,out] pnCount	ノードの数
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_INode_GetParents_t)(const PStApiHandle_t pINodeHandle, PStApiHandle_t pINodeHandleArray, size_t *pnCount);

	/*!
		@~english	@brief	Register callback function.
		@~english	@details	Register callback function.
		@~english	@param[in] pINodeHandle	INode interface handle.
		@~english	@param[in] pFunc	Callback function pointer.
		@~english	@param[in] eCallbackType	Callback type.
		@~english	@param[in] pvContext	User context for callback function parameter.
		@~english	@param[in,out] pIStRegisteredCallbackHandle	IStRegisteredCallback interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	コールバック関数を登録します。
		@~japanese	@details	コールバック関数を登録します。
		@~japanese	@param[in] pINodeHandle	INode インターフェースハンドル
		@~japanese	@param[in] pFunc	コールバック関数ポインタ
		@~japanese	@param[in] eCallbackType	コールバックタイプ
		@~japanese	@param[in] pvContext	コールバック関数用ユーザーパラメータ
		@~japanese	@param[in,out] pIStRegisteredCallbackHandle	IStRegisteredCallback インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_INode_RegisterCallback_t)(const PStApiHandle_t pINodeHandle, fNodeCallbackFunc_t *pFunc, ECallbackType eCallbackType, void *pvContext, PStApiHandle_t pIStRegisteredCallbackHandle);

	/*!
		@~english	@brief	Retrieves the central node map.
		@~english	@details	Retrieves the central node map.
		@~english	@param[in] pINodeHandle	INode interface handle.
		@~english	@param[in,out] pINodeMapHandle	INodeMap interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	INodeMap インターフェースハンドルを取得します。
		@~japanese	@details	INodeMap インターフェースハンドルを取得します。
		@~japanese	@param[in] pINodeHandle	INode インターフェースハンドル
		@~japanese	@param[in,out] pINodeMapHandle	INodeMap インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_INode_GetNodeMap_t)(const PStApiHandle_t pINodeHandle, PStApiHandle_t pINodeMapHandle);

	/*!
		@~english	@brief	Get the EventID of the node.
		@~english	@details	Get the EventID of the node.
		@~english	@param[in] pINodeHandle	INode interface handle.
		@~english	@param[in,out] szText	EventID.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	EventIDを取得します。
		@~japanese	@details	EventIDを取得します。
		@~japanese	@param[in] pINodeHandle	INode インターフェースハンドル
		@~japanese	@param[in,out] szText	EventID
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_INode_GetEventIDA_t)(const PStApiHandle_t pINodeHandle, char *szText, size_t *pnLen);

	/*!
		@~english	@brief	Check the node is streamable or not.
		@~english	@details	Check the node is streamable or not.
		@~english	@param[in] pINodeHandle	INode interface handle.
		@~english	@param[out] pbValue	True if the node is streamable
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ノードがストリーム可能かどうかチェックします。
		@~japanese	@details	ノードがストリーム可能かどうかチェックします。
		@~japanese	@param[in] pINodeHandle	INode インターフェースハンドル
		@~japanese	@param[out] pbValue	ノードがストリーム可能な場合trueを返します。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_INode_IsStreamable_t)(const PStApiHandle_t pINodeHandle, bool8_t *pbValue);
	
	/*!
		@~english	@brief	Get the number of the properties.
		@~english	@details	Get the number of the properties.
		@~english	@param[in] pINodeHandle	INode interface handle.
		@~english	@param[out] pnValue	Number of the properties.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	プロパティの数を取得します。
		@~japanese	@details	プロパティの数を取得します。
		@~japanese	@param[in] pINodeHandle	INode インターフェースハンドル
		@~japanese	@param[out] pnValue	プロパティの数
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_INode_GetNumPropertyNames_t)(const PStApiHandle_t pINodeHandle, size_t *pnValue);

	/*!
		@~english	@brief	Get a property name.
		@~english	@details	Get a property name.
		@~english	@param[in] pINodeHandle	INode interface handle.
		@~english	@param[in] nIndex	Index value of the property.
		@~english	@param[in,out] szText	Property name.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	プロパティ名を取得します。
		@~japanese	@details	プロパティ名を取得します。
		@~japanese	@param[in] pINodeHandle	INode インターフェースハンドル
		@~japanese	@param[in] nIndex	プロパティのインディックス値
		@~japanese	@param[in,out] szText	プロパティ名
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_INode_GetPropertyNameByIndexA_t)(const PStApiHandle_t pINodeHandle, size_t nIndex, char *szText, size_t *pnLen);
	
	/*!
		@~english	@brief	Retrieves a property plus an additional attribute by name.
		@~english	@details	Retrieves a property plus an additional attribute by name.
		@~english	@param[in] pINodeHandle	INode interface handle.
		@~english	@param[in] szPropertyName	Property name.
		@~english	@param[in,out] szValue	Value.
		@~english	@param[in,out] pnValueLen	Value buffer/string length.
		@~english	@param[in,out] szAttributeText	Attribute.
		@~english	@param[in,out] pnAttributeLen	Attribute buffer/string length.
		@~english	@attention If a property has multiple values/attribute they come with Tabs as delimiters
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	プロパティの値と追加の属性を取得します。
		@~japanese	@details	プロパティの値と追加の属性を取得します。
		@~japanese	@param[in] pINodeHandle	INode インターフェースハンドル
		@~japanese	@param[in] szPropertyName	プロパティ名.
		@~japanese	@param[in,out] szValue	プロパティの値
		@~japanese	@param[in,out] pnValueLen	プロパティの値用バッファ/文字列長
		@~japanese	@param[in,out] szAttributeText	属性
		@~japanese	@param[in,out] pnAttributeLen	属性用バッファ/文字列長
		@~japanese	@attention プロパテ意に複数の値や属性がある場合は、タブで区切られます。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_INode_GetPropertyA_t)(const PStApiHandle_t pINodeHandle, const char *szPropertyName, char *szValue, size_t *pnValueLen, char *szAttributeText, size_t *pnAttributeLen);
	
	/*!
		@~english	@brief	Imposes an access mode to the natural access mode of the node.
		@~english	@details	Imposes an access mode to the natural access mode of the node.
		@~english	@param[in] pINodeHandle	INode interface handle.
		@~english	@param[in] ImposedAccessMode	Imposed Access Mode.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	既定のアクセスモードに制限を加えます。
		@~japanese	@details	既定のアクセスモードに制限を加えます。
		@~japanese	@param[in] pINodeHandle	INode インターフェースハンドル
		@~japanese	@param[in] ImposedAccessMode	制限アクセスモード
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_INode_ImposeAccessMode_t)(const PStApiHandle_t pINodeHandle, EAccessMode ImposedAccessMode);

	/*!
		@~english	@brief	Imposes a visibility  to the natural visibility of the node.
		@~english	@details	Imposes a visibility  to the natural visibility of the node.
		@~english	@param[in] pINodeHandle	INode interface handle.
		@~english	@param[in] ImposedVisibility	Imposed Visibility.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	既定の可視性に制限を加えます。
		@~japanese	@details	既定の可視性に制限を加えます。
		@~japanese	@param[in] pINodeHandle	INode インターフェースハンドル
		@~japanese	@param[in] ImposedVisibility	可視性への制限
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_INode_ImposeVisibility_t)(const PStApiHandle_t pINodeHandle, EVisibility ImposedVisibility);

	/*!
		@~english	@brief	Retrieves the a node which describes the same feature in a different way.
		@~english	@details	Retrieves the a node which describes the same feature in a different way.
		@~english	@param[in] pINodeHandle	INode interface handle.
		@~english	@param[out] pAliasINodeHandle	INode interface handle for alias.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	同じ機能を異なる方法で対応したノードのインターフェースハンドルを取得します。
		@~japanese	@details	同じ機能を異なる方法で対応したノードのインターフェースハンドルを取得します。
		@~japanese	@param[in] pINodeHandle	INode インターフェースハンドル
		@~japanese	@param[out] pAliasINodeHandle	別名ノードの INode インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_INode_GetAlias_t)(const PStApiHandle_t pINodeHandle, PStApiHandle_t pAliasINodeHandle);

	/*!
		@~english	@brief	Retrieves the a node which describes the same feature so that it can be casted.
		@~english	@details	Retrieves the a node which describes the same feature so that it can be casted.
		@~english	@param[in] pINodeHandle	INode interface handle.
		@~english	@param[out] pAliasINodeHandle	INode interface handle for alias.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	同じ機能をキャストできるように対応したノードのインターフェースハンドルを取得します。
		@~japanese	@details	同じ機能をキャストできるように対応したノードのインターフェースハンドルを取得します。
		@~japanese	@param[in] pINodeHandle	INode インターフェースハンドル
		@~japanese	@param[out] pAliasINodeHandle	別名ノードの INode インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_INode_GetCastAlias_t)(const PStApiHandle_t pINodeHandle, PStApiHandle_t pAliasINodeHandle);

	/*!
		@~english	@brief	Gets a URL pointing to the documentation of that feature.
		@~english	@details	Gets a URL pointing to the documentation of that feature.
		@~english	@param[in] pINodeHandle	INode interface handle.
		@~english	@param[in,out] szText	Property name.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	この機能のドキュメントに対するURLを取得します。
		@~japanese	@details	この機能のドキュメントに対するURLを取得します。
		@~japanese	@param[in] pINodeHandle	INode インターフェースハンドル
		@~japanese	@param[in,out] szText	URL
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_INode_GetDocuURLA_t)(const PStApiHandle_t pINodeHandle, char *szText, size_t *pnLen);

	/*!
		@~english	@brief	Checks if this feature is deprecated.
		@~english	@details	Checks if this feature is deprecated.
		@~english	@param[in] pINodeHandle	INode interface handle.
		@~english	@param[out] pbValue	True if the node should not be used any more.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	この機能が廃止予定か否かを取得します。
		@~japanese	@details	この機能が廃止予定か否かを取得します。
		@~japanese	@param[in] pINodeHandle	INode インターフェースハンドル
		@~japanese	@param[out] pbValue	廃止予定の場合、trueが返されます。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_INode_IsDeprecated_t)(const PStApiHandle_t pINodeHandle, bool8_t *pbValue);

	/*!
		@~english	@brief	Get the type of the main interface of a node.
		@~english	@details	Get the type of the main interface of a node.
		@~english	@param[in] pINodeHandle	INode interface handle.
		@~english	@param[out] pnValue	Main interface of a node.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ノードの主要インターフェースのタイプを取得します。
		@~japanese	@details	ノードの主要インターフェースのタイプを取得します。
		@~japanese	@param[out] pnValue	主要インターフェースのタイプ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_INode_GetPrincipalInterfaceType_t)(const PStApiHandle_t pINodeHandle, EInterfaceType *pnValue);

	/*!
		@~english	@brief	Checks if this node can be reached via category nodes from a category node named "Root".
		@~english	@details	Checks if this node can be reached via category nodes from a category node named "Root".
		@~english	@param[in] pINodeHandle	INode interface handle.
		@~english	@param[out] pbValue	True if the node can be reached via category nodes from a category node named "Root"
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	このノードがRootカテゴリーノードから参照可能かどうかをチェックします。
		@~japanese	@details	このノードがRootカテゴリーノードから参照可能かどうかをチェックします。
		@~japanese	@param[out] pbValue	このノードがRootカテゴリーノードから参照可能な場合、trueが返されます。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_INode_IsFeature_t)(const PStApiHandle_t pINodeHandle, bool8_t *pbValue);
	
	/*!
		@~english	@brief	Get interface name.
		@~english	@details	Get interface name.
		@~english	@param[in] pINodeHandle	INode interface handle.
		@~english	@param[in,out] szText	Interface name.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	インターフェース名を取得します。
		@~japanese	@details	インターフェース名を取得します。
		@~japanese	@param[in] pINodeHandle	INode インターフェースハンドル
		@~japanese	@param[in,out] szText	インターフェース名
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_INode_GetInterfaceNameA_t)(const PStApiHandle_t pINodeHandle, const char **szText);
	
	/*!
		@ingroup GenApiC_PublicImpl
		@struct GenApi_INode_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of INode.
		@~english	@details	This structure holds the address of the C language wrapper function of INode.
		@~japanese	@brief	この構造体は INode のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は INode のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _GenApi_INode_Functions_t
	{
		/*!
			@copydoc PGenApi_INode_GetINode_t()
		*/
		PGenApi_INode_GetINode_t	GetINode;

		/*!
			@copydoc PGenApi_INode_GetNameA_t()
		*/
		PGenApi_INode_GetNameA_t	GetNameA;

		/*!
			@copydoc PGenApi_INode_GetNameSpace_t()
		*/
		PGenApi_INode_GetNameSpace_t	GetNameSpace;

		/*!
			@copydoc PGenApi_INode_GetVisibility_t()
		*/
		PGenApi_INode_GetVisibility_t	GetVisibility;

		/*!
			@copydoc PGenApi_INode_InvalidateNode_t()
		*/
		PGenApi_INode_InvalidateNode_t	InvalidateNode;

		/*!
			@copydoc PGenApi_INode_IsCachable_t()
		*/
		PGenApi_INode_IsCachable_t	IsCachable;

		/*!
			@copydoc PGenApi_INode_IsAccessModeCacheable_t()
		*/
		PGenApi_INode_IsAccessModeCacheable_t	IsAccessModeCacheable;

		/*!
			@copydoc PGenApi_INode_GetCachingMode_t()
		*/
		PGenApi_INode_GetCachingMode_t	GetCachingMode;

		/*!
			@copydoc PGenApi_INode_GetPollingTime_t()
		*/
		PGenApi_INode_GetPollingTime_t	GetPollingTime;

		/*!
			@copydoc PGenApi_INode_GetToolTipA_t()
		*/
		PGenApi_INode_GetToolTipA_t	GetToolTipA;

		/*!
			@copydoc PGenApi_INode_GetDescriptionA_t()
		*/
		PGenApi_INode_GetDescriptionA_t	GetDescriptionA;

		/*!
			@copydoc PGenApi_INode_GetDisplayNameA_t()
		*/
		PGenApi_INode_GetDisplayNameA_t	GetDisplayNameA;

		/*!
			@copydoc PGenApi_INode_GetDeviceNameA_t()
		*/
		PGenApi_INode_GetDeviceNameA_t	GetDeviceNameA;

		/*!
			@copydoc PGenApi_INode_GetChildren_t()
		*/
		PGenApi_INode_GetChildren_t	GetChildren;

		/*!
			@copydoc PGenApi_INode_GetParents_t()
		*/
		PGenApi_INode_GetParents_t	GetParents;

		/*!
			@copydoc PGenApi_INode_RegisterCallback_t()
		*/
		PGenApi_INode_RegisterCallback_t	RegisterCallback;

		/*!
			@copydoc PGenApi_INode_GetNodeMap_t()
		*/
		PGenApi_INode_GetNodeMap_t	GetNodeMap;

		/*!
			@copydoc PGenApi_INode_GetEventIDA_t()
		*/
		PGenApi_INode_GetEventIDA_t	GetEventIDA;

		/*!
			@copydoc PGenApi_INode_IsStreamable_t()
		*/
		PGenApi_INode_IsStreamable_t	IsStreamable;

		/*!
			@copydoc PGenApi_INode_GetNumPropertyNames_t()
		*/
		PGenApi_INode_GetNumPropertyNames_t	GetNumPropertyNames;

		/*!
			@copydoc PGenApi_INode_GetPropertyNameByIndexA_t()
		*/
		PGenApi_INode_GetPropertyNameByIndexA_t	GetPropertyNameByIndexA;

		/*!
			@copydoc PGenApi_INode_GetPropertyA_t()
		*/
		PGenApi_INode_GetPropertyA_t	GetPropertyA;

		/*!
			@copydoc PGenApi_INode_ImposeAccessMode_t()
		*/
		PGenApi_INode_ImposeAccessMode_t	ImposeAccessMode;

		/*!
			@copydoc PGenApi_INode_ImposeVisibility_t()
		*/
		PGenApi_INode_ImposeVisibility_t	ImposeVisibility;

		/*!
			@copydoc PGenApi_INode_GetAlias_t()
		*/
		PGenApi_INode_GetAlias_t	GetAlias;

		/*!
			@copydoc PGenApi_INode_GetCastAlias_t()
		*/
		PGenApi_INode_GetCastAlias_t	GetCastAlias;

		/*!
			@copydoc PGenApi_INode_GetDocuURLA_t()
		*/
		PGenApi_INode_GetDocuURLA_t	GetDocuURLA;

		/*!
			@copydoc PGenApi_INode_IsDeprecated_t()
		*/
		PGenApi_INode_IsDeprecated_t	IsDeprecated;

		/*!
			@copydoc PGenApi_INode_GetPrincipalInterfaceType_t()
		*/
		PGenApi_INode_GetPrincipalInterfaceType_t	GetPrincipalInterfaceType;
		
		/*!
			@copydoc PGenApi_INode_GetInterfaceNameA_t()
		*/
		PGenApi_INode_GetInterfaceNameA_t	GetInterfaceNameA;

		/*!
			@copydoc PGenApi_INode_IsFeature_t()
		*/
		PGenApi_INode_IsFeature_t	IsFeature;
	}GenApi_INode_Functions_t, *PGenApi_INode_Functions_t;

	/*************************************************************************/
	/* GenApi::IBase */
	/*************************************************************************/
	/*!
		@~english	@brief	Get IBase handle.
		@~english	@details	Get IBase handle.
		@~english	@param[in] pSourceHandle	Interface handle that is enable to convert to IBase interface handle.
		@~english	@param[in,out] pIBaseHandle	IBase interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IBaseハンドルを取得します。
		@~japanese	@details	IBaseハンドルを取得します。
		@~japanese	@param[in] pSourceHandle	IBase インターフェースハンドルに変換可能なインターフェースハンドル
		@~japanese	@param[in,out] pIBaseHandle	IBase インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IBase_GetIBase_t)(const PStApiHandle_t pSourceHandle, PStApiHandle_t pIBaseHandle);

	/*!
		@~english	@brief	Get the access mode of the node.
		@~english	@details	Get the access mode of the node.
		@~english	@param[in] pIBaseHandle	IBase interface handle.
		@~english	@param[out] pnValue	Access mode.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ノードのアクセスモードを取得します。
		@~japanese	@details	ノードのアクセスモードを取得します。
		@~japanese	@param[in] pIBaseHandle	IBase インターフェースハンドル
		@~japanese	@param[out] pnValue	アクセスモード
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IBase_GetAccessMode_t)(const PStApiHandle_t pIBaseHandle, EAccessMode *pnValue);

	/*!
		@~english	@brief	Checks if a node is readable.
		@~english	@details	Checks if a node is readable.
		@~english	@param[in] pIBaseHandle	IBase interface handle.
		@~english	@param[out] pbValue	If readable, true is returned.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ノードが読み込み可能かどうかチェックします。
		@~japanese	@details	ノードが読み込み可能かどうかチェックします。
		@~japanese	@param[in] pIBaseHandle	IBase インターフェースハンドル
		@~japanese	@param[out] pbValue	読み込み可能な場合、trueが返されます。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IBase_IsReadable_t)(const PStApiHandle_t pIBaseHandle, bool8_t *pbValue);

	/*!
		@~english	@brief	Checks if a node is writable.
		@~english	@details	Checks if a node is writable.
		@~english	@param[in] pIBaseHandle	IBase interface handle.
		@~english	@param[out] pbValue	If writable, true is returned.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ノードが書き込み可能かどうかチェックします。
		@~japanese	@details	ノードが書き込み可能かどうかチェックします。
		@~japanese	@param[in] pIBaseHandle	IBase インターフェースハンドル
		@~japanese	@param[out] pbValue	書き込み可能な場合、trueが返されます。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IBase_IsWritable_t)(const PStApiHandle_t pIBaseHandle, bool8_t *pbValue);

	/*!
		@~english	@brief	Checks if a node is implemented.
		@~english	@details	Checks if a node is implemented.
		@~english	@param[in] pIBaseHandle	IBase interface handle.
		@~english	@param[out] pbValue	If implemented, true is returned.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ノードが実装されているかどうかチェックします。
		@~japanese	@details	ノードが実装されているかどうかチェックします。
		@~japanese	@param[in] pIBaseHandle	IBase インターフェースハンドル
		@~japanese	@param[out] pbValue	実装されている場合、trueが返されます。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IBase_IsImplemented_t)(const PStApiHandle_t pIBaseHandle, bool8_t *pbValue);

	/*!
		@~english	@brief	Checks if a node is available.
		@~english	@details	Checks if a node is available.
		@~english	@param[in] pIBaseHandle	IBase interface handle.
		@~english	@param[out] pbValue	If available, true is returned.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ノードが利用可能かどうかチェックします。
		@~japanese	@details	ノードが利用可能かどうかチェックします。
		@~japanese	@param[in] pIBaseHandle	IBase インターフェースハンドル
		@~japanese	@param[out] pbValue	利用可能な場合、trueが返されます。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IBase_IsAvailable_t)(const PStApiHandle_t pIBaseHandle, bool8_t *pbValue);

	/*!
		@ingroup GenApiC_PublicImpl
		@struct GenApi_IBase_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IBase.
		@~english	@details	This structure holds the address of the C language wrapper function of IBase.
		@~japanese	@brief	この構造体は IBase のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IBase のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _GenApi_IBase_Functions_t
	{
		/*!
			@copydoc PGenApi_IBase_GetIBase_t()
		*/
		PGenApi_IBase_GetIBase_t	GetIBase;

		/*!
			@copydoc PGenApi_IBase_GetAccessMode_t()
		*/
		PGenApi_IBase_GetAccessMode_t	GetAccessMode;

		/*!
			@copydoc PGenApi_IBase_IsReadable_t()
		*/
		PGenApi_IBase_IsReadable_t	IsReadable;

		/*!
			@copydoc PGenApi_IBase_IsWritable_t()
		*/
		PGenApi_IBase_IsWritable_t	IsWritable;

		/*!
			@copydoc PGenApi_IBase_IsImplemented_t()
		*/
		PGenApi_IBase_IsImplemented_t	IsImplemented;

		/*!
			@copydoc PGenApi_IBase_IsAvailable_t()
		*/
		PGenApi_IBase_IsAvailable_t	IsAvailable;
	}GenApi_IBase_Functions_t, *PGenApi_IBase_Functions_t;


	/*************************************************************************/
	/* GenApi::IValue */
	/*************************************************************************/
	/*!
		@~english	@brief	Get IValue handle.
		@~english	@details	Get IValue handle.
		@~english	@param[in] pSourceHandle	Interface handle that is enable to convert to IValue interface handle.
		@~english	@param[in,out] pIValueHandle	IValue interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IValueハンドルを取得します。
		@~japanese	@details	IValueハンドルを取得します。
		@~japanese	@param[in] pSourceHandle	IValue インターフェースハンドルに変換可能なインターフェースハンドル
		@~japanese	@param[in,out] pIValueHandle	IValue インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IValue_GetIValue_t)(const PStApiHandle_t pSourceHandle, PStApiHandle_t pIValueHandle);

	/*!
		@~english	@brief	Get content of the node as string.
		@~english	@details	Get content of the node as string.
		@~english	@param[in] pIValueHandle	IValue interface handle.
		@~english	@param[in] Verify	Enables Range verification. Default value for C++ is false. The AccessMode is always checked.
		@~english	@param[in] IgnoreCache	If true the value is read ignoring any caches. Default value for C++ is false. 
		@~english	@param[in,out] szText	Content of the node.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ノードの内容を文字列で取得します。
		@~japanese	@details	ノードの内容を文字列で取得します。
		@~japanese	@param[in] pINodeHandle	IValue インターフェースハンドル
		@~japanese	@param[in] Verify	 範囲のチェックを有効にします。C++言語用の初期値はfalseです。アクセスモードは常にチェックされます。
		@~japanese	@param[in] IgnoreCache	trueが指定されるとキャッシュを無視して、読み込みを行います。C++言語用の初期値はfalseです。
		@~japanese	@param[in,out] szText	ノードの内容
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IValue_ToStringA_t)(const PStApiHandle_t pIValueHandle, bool8_t Verify, bool8_t IgnoreCache, char *szText, size_t *pnLen);

	/*!
		@~english	@brief	Set content of the node as string.
		@~english	@details	Set content of the node as string.
		@~english	@param[in] pIValueHandle	IValue interface handle.
		@~english	@param[in] szValue	The value to set.
		@~english	@param[in] Verify	Enables AccessMode and Range verification. Default value for C++ is true.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ノードの内容を文字列で設定します。
		@~japanese	@details	ノードの内容を文字列で設定します。
		@~japanese	@param[in] pINodeHandle	IValue インターフェースハンドル
		@~japanese	@param[in] szValue	設定する値
		@~japanese	@param[in] Verify	 アクセスモードと範囲のチェックを有効にします。C++言語用の初期値はtrueです。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IValue_FromStringA_t)(const PStApiHandle_t pIValueHandle, const char *szValue, bool8_t Verify);

	/*!
		@~english	@brief	 Checks if the value cache is valid.
		@~english	@details	Checks if the value cache is valid.
		@~english	@param[in] pIValueHandle	IValue interface handle.
		@~english	@param[out] pbValue	True if the value cache is valid.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	キャッシュが有効かどうかチェックします。
		@~japanese	@details	キャッシュが有効かどうかチェックします。
		@~japanese	@param[in] pINodeHandle	IValue インターフェースハンドル
		@~japanese	@param[out] pbValue	 キャッシュが有効な場合、trueが返されます。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IValue_IsValueCacheValid_t)(const PStApiHandle_t pIValueHandle, bool8_t *pbValue);
	
	/*!
		@ingroup GenApiC_PublicImpl
		@struct GenApi_IValue_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IValue.
		@~english	@details	This structure holds the address of the C language wrapper function of IValue.
		@~japanese	@brief	この構造体は IValue のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IValue のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _GenApi_IValue_Functions_t
	{
		/*!
			@copydoc PGenApi_IValue_GetIValue_t()
		*/
		PGenApi_IValue_GetIValue_t	GetIValue;

		/*!
			@copydoc PGenApi_IValue_ToStringA_t()
		*/
		PGenApi_IValue_ToStringA_t	ToStringA;

		/*!
			@copydoc PGenApi_IValue_FromStringA_t()
		*/
		PGenApi_IValue_FromStringA_t	FromStringA;

		/*!
			@copydoc PGenApi_IValue_IsValueCacheValid_t()
		*/
		PGenApi_IValue_IsValueCacheValid_t	IsValueCacheValid;
	}GenApi_IValue_Functions_t, *PGenApi_IValue_Functions_t;

	/*************************************************************************/
	/* GenApi::IPort */
	/*************************************************************************/
	/*!
		@~english	@brief	Get IPort handle.
		@~english	@details	Get IPort handle.
		@~english	@param[in] pSourceHandle	Interface handle that is enable to convert to IPort interface handle.
		@~english	@param[in,out] pIPortHandle	IPort interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IPortハンドルを取得します。
		@~japanese	@details	IPortハンドルを取得します。
		@~japanese	@param[in] pSourceHandle	IPort インターフェースハンドルに変換可能なインターフェースハンドル
		@~japanese	@param[in,out] pIPortHandle	IPort インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IPort_GetIPort_t)(const PStApiHandle_t pSourceHandle, PStApiHandle_t pIPortHandle);

	/*!
		@~english	@brief	Reads a chunk of bytes from the port.
		@~english	@details	Reads a chunk of bytes from the port.
		@~english	@param[in] pIPortHandle	IPort interface handle.
		@~english	@param[out] pBuffer	Pointer of the bufffer.
		@~english	@param[in] Address	Start address.
		@~english	@param[in] Length	Buffer/Read length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ポートからバイトデータを読み込みます。
		@~japanese	@details	ポートからバイトデータを読み込みます。
		@~japanese	@param[in] pIPortHandle	IPort インターフェースハンドル
		@~japanese	@param[out] pBuffer	バッファのポインター
		@~japanese	@param[in] Address	 開始アドレス
		@~japanese	@param[in] Length	 バッファ/読み込みサイズ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IPort_Read_t)(const PStApiHandle_t pIPortHandle, void *pBuffer, int64_t Address, int64_t Length);

	/*!
		@~english	@brief	Writes a chunk of bytes to the port.
		@~english	@details	Writes a chunk of bytes to the port.
		@~english	@param[in] pIPortHandle	IPort interface handle.
		@~english	@param[out] pBuffer	Pointer of the bufffer.
		@~english	@param[in] Address	Start address.
		@~english	@param[in] Length	Buffer/Write length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ポートへバイトデータを書き込みます。
		@~japanese	@details	ポートへバイトデータを書き込みます。
		@~japanese	@param[in] pIPortHandle	IPort インターフェースハンドル
		@~japanese	@param[out] pBuffer	バッファのポインター
		@~japanese	@param[in] Address	 開始アドレス
		@~japanese	@param[in] Length	 バッファ/書き込みサイズ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IPort_Write_t)(const PStApiHandle_t pIPortHandle, const void *pBuffer, int64_t Address, int64_t Length);
	
	/*!
		@ingroup GenApiC_PublicImpl
		@struct GenApi_IPort_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IPort.
		@~english	@details	This structure holds the address of the C language wrapper function of IPort.
		@~japanese	@brief	この構造体は IPort のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IPort のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _GenApi_IPort_Functions_t
	{
		/*!
			@copydoc PGenApi_IPort_GetIPort_t()
		*/
		PGenApi_IPort_GetIPort_t	GetIPort;
		/*!
			@copydoc PGenApi_IPort_Read_t()
		*/
		PGenApi_IPort_Read_t	Read;
		/*!
			@copydoc PGenApi_IPort_Write_t()
		*/
		PGenApi_IPort_Write_t	Write;
	}GenApi_IPort_Functions_t, *PGenApi_IPort_Functions_t;

	/*************************************************************************/
	/* GenApi::IChunkPort */
	/*************************************************************************/
	/*!
		@~english	@brief	Get IChunkPort handle.
		@~english	@details	Get IChunkPort handle.
		@~english	@param[in] pSourceHandle	Interface handle that is enable to convert to IChunkPort interface handle.
		@~english	@param[in,out] pIChunkPortHandle	IChunkPort interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IChunkPortハンドルを取得します。
		@~japanese	@details	IChunkPortハンドルを取得します。
		@~japanese	@param[in] pSourceHandle	IChunkPort インターフェースハンドルに変換可能なインターフェースハンドル
		@~japanese	@param[in,out] pIChunkPortHandle	IChunkPort インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IChunkPort_GetIChunkPort_t)(const PStApiHandle_t pSourceHandle, PStApiHandle_t pIChunkPortHandle);

	/*!
		@~english	@brief	Get the Id of the chunk the port should be attached to.
		@~english	@details	Get the Id of the chunk the port should be attached to.
		@~english	@param[in] pIChunkPortHandle	IChunkPort interface handle.
		@~english	@param[in,out] szText	Id of the chunk.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ポートに割り振られたチャンクIDを取得します。
		@~japanese	@details	ポートに割り振られたチャンクIDを取得します。
		@~japanese	@param[in] pIChunkPortHandle	IChunkPort interface handle.
		@~japanese	@param[in,out] szText	チャンクID
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IChunkPort_GetChunkIDA_t)(const PStApiHandle_t pIChunkPortHandle, char *szText, size_t *pnLen);

	/*!
		@~english	@brief	Indicates if the chunk a adapter must hold a cached version of the chunk data.
		@~english	@details	Indicates if the chunk a adapter must hold a cached version of the chunk data.
		@~english	@param[in] pIChunkPortHandle	IChunkPort interface handle.
		@~english	@param[out] peValue	If chunk data caching is enabled a copy of the chunk data is held even if the corresponding buffer is detached.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	チャンクデータのキャッシュが有効かどうかをチェックします。
		@~japanese	@details	チャンクデータのキャッシュが有効かどうかをチェックします。
		@~japanese	@param[in] pIChunkPortHandle	IChunkPort interface handle.
		@~japanese	@param[out] peValue	チャンクデータのキャッシュが有効(Yes)な場合、チャンクデータはキャッシュされ、対応するバッファが取り外された後も有効になります。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IChunkPort_CacheChunkData_t)(const PStApiHandle_t pIChunkPortHandle, EYesNo *peValue);

	/*!
		@ingroup GenApiC_PublicImpl
		@struct GenApi_IChunkPort_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IChunkPort.
		@~english	@details	This structure holds the address of the C language wrapper function of IChunkPort.
		@~japanese	@brief	この構造体は IChunkPort のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IChunkPort のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _GenApi_IChunkPort_Functions_t
	{
		/*!
			@copydoc PGenApi_IChunkPort_GetIChunkPort_t()
		*/
		PGenApi_IChunkPort_GetIChunkPort_t	GetIChunkPort;
		
		/*!
			@copydoc PGenApi_IChunkPort_GetChunkIDA_t()
		*/
		PGenApi_IChunkPort_GetChunkIDA_t	GetChunkIDA;
		
		/*!
			@copydoc PGenApi_IChunkPort_CacheChunkData_t()
		*/
		PGenApi_IChunkPort_CacheChunkData_t	CacheChunkData;
	}GenApi_IChunkPort_Functions_t, *PGenApi_IChunkPort_Functions_t;

	/*************************************************************************/
	/* GenApi::IBoolean */
	/*************************************************************************/
	/*!
		@~english	@brief	Get IBoolean handle.
		@~english	@details	Get IBoolean handle.
		@~english	@param[in] pSourceHandle	Interface handle that is enable to convert to IBoolean interface handle.
		@~english	@param[in,out] pIBooleanHandle	IBoolean interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IBooleanハンドルを取得します。
		@~japanese	@details	IBooleanハンドルを取得します。
		@~japanese	@param[in] pSourceHandle	IBoolean インターフェースハンドルに変換可能なインターフェースハンドル
		@~japanese	@param[in,out] pIBooleanHandle	IBoolean インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IBoolean_GetIBoolean_t)(const PStApiHandle_t pSourceHandle, PStApiHandle_t pIBooleanHandle);

	/*!
		@~english	@brief	Set node value.
		@~english	@details	Set node value.
		@~english	@param[in] pIBooleanHandle	IBoolean interface handle.
		@~english	@param[in] Value	The value to set.
		@~english	@param[in] Verify Enables AccessMode and Range verification. Default value for C++ is true.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ノードの値を設定します。
		@~japanese	@details	ノードの値を設定します。
		@~japanese	@param[in] pIBooleanHandle	IBoolean インターフェースハンドル
		@~japanese	@param[in] Value	 設定する値
		@~japanese	@param[in] Verify	 アクセスモードと値の範囲チェックを有効化します。C++言語用の初期値はtrueです。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IBoolean_SetValue_t)(const PStApiHandle_t pIBooleanHandle, bool8_t Value, bool8_t Verify);

	/*!
		@~english	@brief	Get node value.
		@~english	@details	Get node value.
		@~english	@param[in] pIBooleanHandle	IBoolean interface handle.
		@~english	@param[in] Verify Enables Range verification. The AccessMode is always checked. Default value for C++ is false.
		@~english	@param[in] IgnoreCache If true the value is read ignoring any caches. Default value for C++ is false.
		@~english	@param[out] pbValue	The value read.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ノードの値を取得します。
		@~japanese	@details	ノードの値を取得します。
		@~japanese	@param[in] pIBooleanHandle	IBoolean インターフェースハンドル
		@~japanese	@param[in] Verify	 値の範囲チェックを有効化します。アクセスモードは常にチェックされます。C++言語用の初期値はfalseです。
		@~japanese	@param[in] IgnoreCache	 trueを指定するとキャッシュを無視して値を読み込みます。C++言語用の初期値はfalseです。
		@~japanese	@param[out] pbValue	 取得した値
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IBoolean_GetValue_t)(const PStApiHandle_t pIBooleanHandle, bool8_t Verify, bool8_t IgnoreCache, bool8_t *pbValue);

	
	/*!
		@ingroup GenApiC_PublicImpl
		@struct GenApi_IBoolean_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IBoolean.
		@~english	@details	This structure holds the address of the C language wrapper function of IBoolean.
		@~japanese	@brief	この構造体は IBoolean のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IBoolean のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _GenApi_IBoolean_Functions_t
	{
		/*!
			@copydoc PGenApi_IBoolean_GetIBoolean_t()
		*/
		PGenApi_IBoolean_GetIBoolean_t	GetIBoolean;
		/*!
			@copydoc PGenApi_IBoolean_SetValue_t()
		*/
		PGenApi_IBoolean_SetValue_t	SetValue;
		/*!
			@copydoc PGenApi_IBoolean_GetValue_t()
		*/
		PGenApi_IBoolean_GetValue_t	GetValue;
	}GenApi_IBoolean_Functions_t, *PGenApi_IBoolean_Functions_t;

	/*************************************************************************/
	/* GenApi::ICategory */
	/*************************************************************************/
	/*!
		@~english	@brief	Get ICategory handle.
		@~english	@details	Get ICategory handle.
		@~english	@param[in] pSourceHandle	Interface handle that is enable to convert to ICategory interface handle.
		@~english	@param[in,out] pICategoryHandle	ICategory interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ICategoryハンドルを取得します。
		@~japanese	@details	ICategoryハンドルを取得します。
		@~japanese	@param[in] pSourceHandle	ICategory インターフェースハンドルに変換可能なインターフェースハンドル
		@~japanese	@param[in,out] pICategoryHandle	ICategory インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_ICategory_GetICategory_t)(const PStApiHandle_t pSourceHandle, PStApiHandle_t pICategoryHandle);

	/*!
		@~english	@brief	Get features of the category.
		@~english	@details	Get features of the category.
		@~english	@param[in] pICategoryHandle	ICategory interface handle.
		@~english	@param[in,out] pIValueHandleArray	IValue interface handles array.
		@~english	@param[in,out] pnCount	Input : Size of the array. Output : Count of the handles.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	インディックスを指定して機能を取得します。
		@~japanese	@details	インディックスを指定して機能を取得します。
		@~japanese	@param[in] pICategoryHandle	ICategory インターフェースハンドル
		@~japanese	@param[in,out] pIValueHandleArray	IValue インターフェースハンドル配列
		@~japanese	@param[in,out] pnCount 配列のサイズを指定し、ハンドルの数を取得します。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_ICategory_GetFeatures_t)(const PStApiHandle_t pICategoryHandle, PStApiHandle_t pIValueHandleArray, size_t *pnCount);
	
	/*!
		@ingroup GenApiC_PublicImpl
		@struct GenApi_ICategory_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of ICategory.
		@~english	@details	This structure holds the address of the C language wrapper function of ICategory.
		@~japanese	@brief	この構造体は ICategory のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は ICategory のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _GenApi_ICategory_Functions_t
	{
		/*!
			@copydoc PGenApi_ICategory_GetICategory_t()
		*/
		PGenApi_ICategory_GetICategory_t	GetICategory;

		/*!
			@copydoc PGenApi_ICategory_GetFeatures_t()
		*/
		PGenApi_ICategory_GetFeatures_t	GetFeatures;
	}GenApi_ICategory_Functions_t, *PGenApi_ICategory_Functions_t;

	
	/*************************************************************************/
	/* GenApi::ICommand */
	/*************************************************************************/
	/*!
		@~english	@brief	Get ICommand handle.
		@~english	@details	Get ICommand handle.
		@~english	@param[in] pSourceHandle	Interface handle that is enable to convert to ICommand interface handle.
		@~english	@param[in,out] pICommandHandle	ICommand interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ICommandハンドルを取得します。
		@~japanese	@details	ICommandハンドルを取得します。
		@~japanese	@param[in] pSourceHandle	ICommand インターフェースハンドルに変換可能なインターフェースハンドル
		@~japanese	@param[in,out] pICommandHandle	ICommand インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_ICommand_GetICommand_t)(const PStApiHandle_t pSourceHandle, PStApiHandle_t pICommandHandle);

	/*!
		@~english	@brief	Execute the command.
		@~english	@details	Execute the command.
		@~english	@param[in] pICommandHandle	ICommand interface handle.
		@~english	@param[in] Verify	Enables AccessMode and Range verification. Default value for C++ is true.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	コマンドを実行します。
		@~japanese	@details	コマンドを実行します。
		@~japanese	@param[in] pICommandHandle	ICommand インターフェースハンドル
		@~japanese	@param[in] Verify	trueを指定すると、アクセスモードと値の範囲チェックを行います。C++言語用の初期値はtrueです。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_ICommand_Execute_t)(const PStApiHandle_t pICommandHandle, bool8_t Verify);

	/*!
		@~english	@brief	Query whether the command is executed.
		@~english	@details	Query whether the command is executed.
		@~english	@param[in] pICommandHandle	ICommand interface handle.
		@~english	@param[in] Verify	Enables Range verification. The AccessMode is always checked. Default value for C++ is true.
		@~english	@param[out] pbDone	True if the Execute command has finished; false otherwise.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	コマンドが実行されたか問い合わせを行います。
		@~japanese	@details	コマンドが実行されたか問い合わせを行います。
		@~japanese	@param[in] pICommandHandle	ICommand インターフェースハンドル
		@~japanese	@param[in] Verify	trueを指定すると、値の範囲チェックを行います。アクセスモードは常にチェックされます。C++言語用の初期値はtrueです。
		@~japanese	@param[out] pbDone	コマンドの実行が完了していたら、trueが返されます。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_ICommand_IsDone_t)(const PStApiHandle_t pICommandHandle, bool8_t Verify, bool8_t *pbDone);

	/*!
		@ingroup GenApiC_PublicImpl
		@struct GenApi_ICommand_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of ICommand.
		@~english	@details	This structure holds the address of the C language wrapper function of ICommand.
		@~japanese	@brief	この構造体は ICommand のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は ICommand のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _GenApi_ICommand_Functions_t
	{
		/*!
			@copydoc PGenApi_ICommand_GetICommand_t()
		*/
		PGenApi_ICommand_GetICommand_t	GetICommand;
		/*!
			@copydoc PGenApi_ICommand_Execute_t()
		*/
		PGenApi_ICommand_Execute_t	Execute;
		/*!
			@copydoc PGenApi_ICommand_IsDone_t()
		*/
		PGenApi_ICommand_IsDone_t	IsDone;
	}GenApi_ICommand_Functions_t, *PGenApi_ICommand_Functions_t;
	
	/*************************************************************************/
	/* GenApi::IEnumEntry */
	/*************************************************************************/
	/*!
		@~english	@brief	Get IEnumEntry handle.
		@~english	@details	Get IEnumEntry handle.
		@~english	@param[in] pSourceHandle	Interface handle that is enable to convert to IEnumEntry interface handle.
		@~english	@param[in,out] pIEnumEntryHandle	IEnumEntry interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IEnumEntryハンドルを取得します。
		@~japanese	@details	IEnumEntryハンドルを取得します。
		@~japanese	@param[in] pSourceHandle	IEnumEntry インターフェースハンドルに変換可能なインターフェースハンドル
		@~japanese	@param[in,out] pIEnumEntryHandle	IEnumEntry インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IEnumEntry_GetIEnumEntry_t)(const PStApiHandle_t pSourceHandle, PStApiHandle_t pIEnumEntryHandle);
	
	/*!
		@~english	@brief	Get numeric enum value.
		@~english	@details	Get numeric enum value.
		@~english	@param[in] pIEnumEntryHandle	IEnumEntry interface handle.
		@~english	@param[out] pnValue	Numeric enum value.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	列挙肢の整数値を取得します。
		@~japanese	@details	列挙肢の整数値を取得します。
		@~japanese	@param[in] pIEnumEntryHandle	IEnumEntry インターフェースハンドル
		@~japanese	@param[out] pnValue	列挙肢の整数値
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IEnumEntry_GetValue_t)(const PStApiHandle_t pIEnumEntryHandle, int64_t *pnValue);

	/*!
		@~english	@brief	Get symbolic enum value.
		@~english	@details	Get symbolic enum value.
		@~english	@param[in] pIEnumEntryHandle	IEnumEntry interface handle.
		@~english	@param[out] szText	Symbolic enum value.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	列挙肢の名前を取得します。
		@~japanese	@details	列挙肢の名前を取得します。
		@~japanese	@param[in] pIEnumEntryHandle	IEnumEntry インターフェースハンドル
		@~japanese	@param[out] szText	列挙肢の文字列
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IEnumEntry_GetSymbolicA_t)(const PStApiHandle_t pIEnumEntryHandle, char *szText, size_t *pnLen);

	/*!
		@~english	@brief	Get floating point number associated with the entry.
		@~english	@details	Get floating point number associated with the entry.
		@~english	@param[in] pIEnumEntryHandle	IEnumEntry interface handle.
		@~english	@param[out] pdblValue	Floating point number.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	列挙肢に関連付けられた浮動小数点数を取得します。
		@~japanese	@details	列挙肢に関連付けられた浮動小数点数を取得します。
		@~japanese	@param[in] pIEnumEntryHandle	IEnumEntry インターフェースハンドル
		@~japanese	@param[out] pdblValue	列挙肢に関連付けられた浮動小数点数
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IEnumEntry_GetNumericValue_t)(const PStApiHandle_t pIEnumEntryHandle, double *pdblValue);

	/*!
		@~english	@brief	Indicates if the corresponding EnumEntry is self clearing.
		@~english	@details	Indicates if the corresponding EnumEntry is self clearing.
		@~english	@param[in] pIEnumEntryHandle	IEnumEntry interface handle.
		@~english	@param[out] pbValue	If it is cleared automatically, true is returned.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	列挙肢に関連付けられた浮動小数点数を取得します。
		@~japanese	@details	列挙肢に関連付けられた浮動小数点数を取得します。
		@~japanese	@param[in] pIEnumEntryHandle	IEnumEntry インターフェースハンドル
		@~japanese	@param[out] pbValue	自動的にクリアされる場合、trueが返されます。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IEnumEntry_IsSelfClearing_t)(const PStApiHandle_t pIEnumEntryHandle, bool8_t *pbValue);
	
	/*!
		@ingroup GenApiC_PublicImpl
		@struct GenApi_IEnumEntry_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IEnumEntry.
		@~english	@details	This structure holds the address of the C language wrapper function of IEnumEntry.
		@~japanese	@brief	この構造体は IEnumEntry のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IEnumEntry のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _GenApi_IEnumEntry_Functions_t
	{
		/*!
			@copydoc PGenApi_IEnumEntry_GetIEnumEntry_t()
		*/
		PGenApi_IEnumEntry_GetIEnumEntry_t	GetIEnumEntry;
		/*!
			@copydoc PGenApi_IEnumEntry_GetValue_t()
		*/
		PGenApi_IEnumEntry_GetValue_t	GetValue;
		/*!
			@copydoc PGenApi_IEnumEntry_GetSymbolicA_t()
		*/
		PGenApi_IEnumEntry_GetSymbolicA_t	GetSymbolicA;
		/*!
			@copydoc PGenApi_IEnumEntry_GetNumericValue_t()
		*/
		PGenApi_IEnumEntry_GetNumericValue_t	GetNumericValue;
		/*!
			@copydoc PGenApi_IEnumEntry_IsSelfClearing_t()
		*/
		PGenApi_IEnumEntry_IsSelfClearing_t	IsSelfClearing;
	}GenApi_IEnumEntry_Functions_t, *PGenApi_IEnumEntry_Functions_t;
	

	/*************************************************************************/
	/* GenApi::IEnumeration */
	/*************************************************************************/
	/*!
		@~english	@brief	Get IEnumeration handle.
		@~english	@details	Get IEnumeration handle.
		@~english	@param[in] pSourceHandle	Interface handle that is enable to convert to IEnumeration interface handle.
		@~english	@param[in,out] pIEnumerationHandle	IEnumeration interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IEnumerationハンドルを取得します。
		@~japanese	@details	IEnumerationハンドルを取得します。
		@~japanese	@param[in] pSourceHandle	IEnumeration インターフェースハンドルに変換可能なインターフェースハンドル
		@~japanese	@param[in,out] pIEnumerationHandle	IEnumeration インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IEnumeration_GetIEnumeration_t)(const PStApiHandle_t pSourceHandle, PStApiHandle_t pIEnumerationHandle);

	/*!
		@~english	@brief	Get a number of symbolic values.
		@~english	@details	Get a number of symbolic values.
		@~english	@param[in] pIEnumerationHandle	IEnumeration interface handle.
		@~english	@param[out] pnValue Number of symbolic values.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	列挙肢の数を取得します。
		@~japanese	@details	列挙肢の数を取得します。
		@~japanese	@param[in] pIEnumerationHandle	IEnumeration インターフェースハンドル
		@~japanese	@param[out] pnValue 列挙肢の数
		@~japanese	@return	EStApiCError_t エラーコード
		@~japanese	@attention GetNumEntriesと異なり、Availableな列挙肢のみが対象となります。
	*/
	STAPI_PCALL(PGenApi_IEnumeration_GetNumSymbolics_t)(const PStApiHandle_t pIEnumerationHandle, size_t *pnValue);

	/*!
		@~english	@brief	Get a symbolic value by index.
		@~english	@details	Get a symbolic value by index.
		@~english	@param[in] pIEnumerationHandle	IEnumeration interface handle.
		@~english	@param[in] nIndex	Index value.
		@~english	@param[in,out] szText	Symbolic value.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	インディックスを指定して列挙肢名を取得します。
		@~japanese	@details	インディックスを指定して列挙肢名を取得します。
		@~japanese	@param[in] pIEnumerationHandle	IEnumeration インターフェースハンドル
		@~japanese	@param[in] nIndex	インディックス値
		@~japanese	@param[in,out] szText	列挙肢名
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IEnumeration_GetSymbolicByIndexA_t)(const PStApiHandle_t pIEnumerationHandle, size_t nIndex, char *szText, size_t *pnLen);

	/*!
		@~english	@brief	Get entry nodes.
		@~english	@details	Get entry nodes.
		@~english	@param[in] pIEnumerationHandle	IEnumeration interface handle.
		@~english	@param[in,out] pINodeHandleArray	INode interface handle array.
		@~english	@param[in,out] pnCount	Input : Size of the array. Output : Count of the handles.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	Entryノードを取得します。
		@~japanese	@details	Entryノードを取得します。
		@~japanese	@param[in] pIEnumerationHandle	IEnumeration インターフェースハンドル
		@~japanese	@param[in,out] pINodeHandleArray	INode インターフェースハンドル配列
		@~japanese	@param[in,out] pnCount 配列のサイズを指定して、ハンドルの数を取得します。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IEnumeration_GetEntries_t)(const PStApiHandle_t pIEnumerationHandle, PStApiHandle_t pINodeHandleArray, size_t *pnCount);

	/*!
		@~english	@brief	Set string node value.
		@~english	@details	Set string node value.
		@~english	@param[in] pIEnumerationHandle	IEnumeration interface handle.
		@~english	@param[in] szValue String node value.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	文字列でノードの値を設定します。
		@~japanese	@details	文字列でノードの値を設定します。
		@~japanese	@param[in] pIEnumerationHandle	IEnumeration インターフェースハンドル
		@~japanese	@param[in] szValue 文字列ノード値
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IEnumeration_SetStringValueA_t)(const PStApiHandle_t pIEnumerationHandle, const char *szValue);

	/*!
		@~english	@brief	Set integer node value.
		@~english	@details	Set integer node value.
		@~english	@param[in] pIEnumerationHandle	IEnumeration interface handle.
		@~english	@param[in] Value The value to set.
		@~english	@param[in] Verify Enables AccessMode and Range verification. Default value for C++ is true.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	整数値でノードの値を設定します。
		@~japanese	@details	整数値でノードの値を設定します。
		@~japanese	@param[in] pIEnumerationHandle	IEnumeration インターフェースハンドル
		@~japanese	@param[in] Value 整数ノード値
		@~japanese	@param[in] Verify trueが指定されると、アクセスモードと値の範囲がチェックされます。C++言語用の初期値はtrueです。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IEnumeration_SetIntValue_t)(const PStApiHandle_t pIEnumerationHandle, int64_t Value, bool8_t Verify);

	/*!
		@~english	@brief	Get string node value.
		@~english	@details	Get string node value.
		@~english	@param[in] pIEnumerationHandle	IEnumeration interface handle.
		@~english	@param[in,out] szText	String node value.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ノードの文字列値を取得します。
		@~japanese	@details	ノードの文字列値を取得します。
		@~japanese	@param[in] pIEnumerationHandle	IEnumeration インターフェースハンドル
		@~japanese	@param[in,out] szText	ノードの文字列値
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IEnumeration_GetStringValueA_t)(const PStApiHandle_t pIEnumerationHandle, char *szText, size_t *pnLen);

	/*!
		@~english	@brief	Get integer node value.
		@~english	@details	Get integer node value.
		@~english	@param[in] pIEnumerationHandle	IEnumeration interface handle.
		@~english	@param[in] Verify Enables Range verification. The AccessMode is always checked. Default value for C++ is false.
		@~english	@param[in] IgnoreCache If true the value is read ignoring any caches. Default value for C++ is false.
		@~english	@param[out] pnValue The value read.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ノードの整数値を取得します。
		@~japanese	@details	ノードの整数値を取得します。
		@~japanese	@param[in] pIEnumerationHandle	IEnumeration インターフェースハンドル
		@~japanese	@param[in] Verify trueが指定されると、値の範囲がチェックされます。アクセスモードは常にチェックされます。C++言語用の初期値はfalseです。
		@~japanese	@param[in] IgnoreCache trueが指定されると、キャッシュを無視して読み込みを行います。C++言語用の初期値はfalseです。
		@~japanese	@param[out] pnValue 整数ノード値
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IEnumeration_GetIntValue_t)(const PStApiHandle_t pIEnumerationHandle, bool8_t Verify, bool8_t IgnoreCache, int64_t *pnValue);

	/*!
		@~english	@brief	Get an entry node by name.
		@~english	@details	Get an entry node by name.
		@~english	@param[in] pIEnumerationHandle	IEnumeration interface handle.
		@~english	@param[in] szSymbolic Name of the entry node.
		@~english	@param[in,out] pIEnumEntryHandle	IEnumEntry interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	名前を指定してEntryノードを取得します。
		@~japanese	@details	名前を指定してEntryノードを取得します。
		@~japanese	@param[in] pIEnumerationHandle	IEnumeration インターフェースハンドル
		@~japanese	@param[in] szSymbolic Entryノードの名前
		@~japanese	@param[in,out] pIEnumEntryHandle	IEnumEntry インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IEnumeration_GetEntryByNameA_t)(const PStApiHandle_t pIEnumerationHandle, const char *szSymbolic, PStApiHandle_t pIEnumEntryHandle);

	/*!
		@~english	@brief	Get an entry node by its IntValue.
		@~english	@details	Get an entry node by its IntValue.
		@~english	@param[in] pIEnumerationHandle	IEnumeration interface handle.
		@~english	@param[in] IntValue IntValue of the entry node.
		@~english	@param[in,out] pIEnumEntryHandle	IEnumEntry interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ノードの整数値を指定してEntryノードを取得します。
		@~japanese	@details	ノードの整数値を指定してEntryノードを取得します。
		@~japanese	@param[in] pIEnumerationHandle	IEnumeration インターフェースハンドル
		@~japanese	@param[in] IntValue ノードの整数値
		@~japanese	@param[in,out] pIEnumEntryHandle	IEnumEntry インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IEnumeration_GetEntryByIntValue_t)(const PStApiHandle_t pIEnumerationHandle, const int64_t IntValue, PStApiHandle_t pIEnumEntryHandle);

	/*!
		@~english	@brief	Get the current entry.
		@~english	@details	Get the current entry.
		@~english	@param[in] pIEnumerationHandle	IEnumeration interface handle.
		@~english	@param[in] Verify Enables Range verification. The AccessMode is always checked. Default value for C++ is false.
		@~english	@param[in] IgnoreCache If true the value is read ignoring any caches. Default value for C++ is false.
		@~english	@param[in,out] pIEnumEntryHandle	IEnumEntry interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ノードの整数値を指定してEntryノードを取得します。
		@~japanese	@details	ノードの整数値を指定してEntryノードを取得します。
		@~japanese	@param[in] pIEnumerationHandle	IEnumeration インターフェースハンドル
		@~japanese	@param[in] Verify trueが指定されると、値の範囲がチェックされます。アクセスモードは常にチェックされます。C++言語用の初期値はfalseです。
		@~japanese	@param[in] IgnoreCache trueが指定されると、キャッシュを無視して読み込みを行います。C++言語用の初期値はfalseです。
		@~japanese	@param[in,out] pIEnumEntryHandle	IEnumEntry インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IEnumeration_GetCurrentEntry_t)(const PStApiHandle_t pIEnumerationHandle, bool8_t Verify, bool8_t IgnoreCache, PStApiHandle_t pIEnumEntryHandle);
	
	/*!
		@ingroup GenApiC_PublicImpl
		@struct GenApi_IEnumeration_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IEnumeration.
		@~english	@details	This structure holds the address of the C language wrapper function of IEnumeration.
		@~japanese	@brief	この構造体は IEnumeration のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IEnumeration のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _GenApi_IEnumeration_Functions_t
	{
		/*!
			@copydoc PGenApi_IEnumeration_GetIEnumeration_t()
		*/
		PGenApi_IEnumeration_GetIEnumeration_t	GetIEnumeration;
		/*!
			@copydoc PGenApi_IEnumeration_GetNumSymbolics_t()
		*/
		PGenApi_IEnumeration_GetNumSymbolics_t	GetNumSymbolics;
		/*!
			@copydoc PGenApi_IEnumeration_GetSymbolicByIndexA_t()
		*/
		PGenApi_IEnumeration_GetSymbolicByIndexA_t	GetSymbolicByIndexA;

		/*!
			@copydoc PGenApi_IEnumeration_GetEntries_t()
		*/
		PGenApi_IEnumeration_GetEntries_t	GetEntries;
		/*!
			@copydoc PGenApi_IEnumeration_SetStringValueA_t()
		*/
		PGenApi_IEnumeration_SetStringValueA_t	SetStringValueA;
		/*!
			@copydoc PGenApi_IEnumeration_SetIntValue_t()
		*/
		PGenApi_IEnumeration_SetIntValue_t	SetIntValue;
		/*!
			@copydoc PGenApi_IEnumeration_GetStringValueA_t()
		*/
		PGenApi_IEnumeration_GetStringValueA_t	GetStringValueA;
		/*!
			@copydoc PGenApi_IEnumeration_GetIntValue_t()
		*/
		PGenApi_IEnumeration_GetIntValue_t	GetIntValue;
		/*!
			@copydoc PGenApi_IEnumeration_GetEntryByNameA_t()
		*/
		PGenApi_IEnumeration_GetEntryByNameA_t	GetEntryByNameA;
		/*!
			@copydoc PGenApi_IEnumeration_GetEntryByIntValue_t()
		*/
		PGenApi_IEnumeration_GetEntryByIntValue_t	GetEntryByIntValue;
		/*!
			@copydoc PGenApi_IEnumeration_GetCurrentEntry_t()
		*/
		PGenApi_IEnumeration_GetCurrentEntry_t	GetCurrentEntry;
	}GenApi_IEnumeration_Functions_t, *PGenApi_IEnumeration_Functions_t;


	/*************************************************************************/
	/* GenApi::IFloat */
	/*************************************************************************/
	/*!
		@~english	@brief	Get IFloat handle.
		@~english	@details	Get IFloat handle.
		@~english	@param[in] pSourceHandle	Interface handle that is enable to convert to IFloat interface handle.
		@~english	@param[in,out] pIFloatHandle	IFloat interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IFloatハンドルを取得します。
		@~japanese	@details	IFloatハンドルを取得します。
		@~japanese	@param[in] pSourceHandle	IFloat インターフェースハンドルに変換可能なインターフェースハンドル
		@~japanese	@param[in,out] pIFloatHandle	IFloat インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IFloat_GetIFloat_t)(const PStApiHandle_t pSourceHandle, PStApiHandle_t pIFloatHandle);

	/*!
		@~english	@brief	Set node value.
		@~english	@details	Set node value.
		@~english	@param[in] pIFloatHandle	IFloat interface handle.
		@~english	@param[in] Value	The value to set.
		@~english	@param[in] Verify	Enables AccessMode and Range verification. Default value for C++ is true.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ノードに値を設定します。
		@~japanese	@details	ノードに値を設定します。
		@~japanese	@param[in] pIFloatHandle	IFloat インターフェースハンドル
		@~japanese	@param[in] Value	設定する値
		@~japanese	@param[in] Verify	trueを指定すると、アクセスモードと値の範囲チェックを行います。C++言語用の初期値はtrueです。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IFloat_SetValue_t)(const PStApiHandle_t pIFloatHandle, double Value, bool8_t Verify);

	/*!
		@~english	@brief	Get node value.
		@~english	@details	Get node value.
		@~english	@param[in] pIFloatHandle	IFloat interface handle.
		@~english	@param[in] Verify	Enables Range verification. The AccessMode is always checked. Default value for C++ is false.
		@~english	@param[in] IgnoreCache	If true the value is read ignoring any caches. Default value for C++ is false.
		@~english	@param[out] pdblValue	The value read.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ノードの値を取得します。
		@~japanese	@details	ノードの値を取得します。
		@~japanese	@param[in] pIFloatHandle	IFloat インターフェースハンドル
		@~japanese	@param[in] Verify	trueを指定すると、値の範囲チェックを行います。アクセスモードは常にチェックされます。C++言語用の初期値はfalseです。
		@~japanese	@param[in] IgnoreCache	trueを指定すると、キャッシュを無視して読み込みを行います。C++言語用の初期値はfalseです。
		@~japanese	@param[out] pdblValue	ノードの値
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IFloat_GetValue_t)(const PStApiHandle_t pIFloatHandle, bool8_t Verify, bool8_t IgnoreCache, double *pdblValue);

	/*!
		@~english	@brief	Get minimum value allowed.
		@~english	@details	Get minimum value allowed.
		@~english	@param[in] pIFloatHandle	IFloat interface handle.
		@~english	@param[out] pdblValue	Minimum value.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	許容される最小値を取得します。
		@~japanese	@details	許容される最小値を取得します。
		@~japanese	@param[in] pIFloatHandle	IFloat インターフェースハンドル
		@~japanese	@param[out] pdblValue	最小値
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IFloat_GetMin_t)(const PStApiHandle_t pIFloatHandle, double *pdblValue);

	/*!
		@~english	@brief	Get maximum value allowed.
		@~english	@details	Get maximum value allowed.
		@~english	@param[in] pIFloatHandle	IFloat interface handle.
		@~english	@param[out] pdblValue	Maximum value.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	許容される最大値を取得します。
		@~japanese	@details	許容される最大値を取得します。
		@~japanese	@param[in] pIFloatHandle	IFloat インターフェースハンドル
		@~japanese	@param[out] pdblValue	最大値
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IFloat_GetMax_t)(const PStApiHandle_t pIFloatHandle, double *pdblValue);

	/*!
		@~english	@brief	Checks if the float has a constant increment.
		@~english	@details	Checks if the float has a constant increment.
		@~english	@param[in] pIFloatHandle	IFloat interface handle.
		@~english	@param[out] pbValue	True if the float has a constant increment.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	増分値があるかどうかチェックします。
		@~japanese	@details	増分値があるかどうかチェックします。
		@~japanese	@param[in] pIFloatHandle	IFloat インターフェースハンドル
		@~japanese	@param[out] pbValue	増分値がある場合、trueが返されます。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IFloat_HasInc_t)(const PStApiHandle_t pIFloatHandle, bool8_t *pbValue);

	/*!
		@~english	@brief	Get increment mode.
		@~english	@details	Get increment mode.
		@~english	@param[in] pIFloatHandle	IFloat interface handle.
		@~english	@param[out] peValue	True if the float has a constant increment.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	増分モードを取得します。
		@~japanese	@details	増分モードを取得します。
		@~japanese	@param[in] pIFloatHandle	IFloat インターフェースハンドル
		@~japanese	@param[out] peValue	増分モード
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IFloat_GetIncMode_t)(const PStApiHandle_t pIFloatHandle, EIncMode *peValue);

	/*!
		@~english	@brief	Get the constant increment if there is any.
		@~english	@details	Get the constant increment if there is any.
		@~english	@param[in] pIFloatHandle	IFloat interface handle.
		@~english	@param[out] pdblValue	Constant increment.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	増分値を取得します。
		@~japanese	@details	増分値を取得します。
		@~japanese	@param[in] pIFloatHandle	IFloat インターフェースハンドル
		@~japanese	@param[out] pdblValue	増分値
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IFloat_GetInc_t)(const PStApiHandle_t pIFloatHandle, double *pdblValue);

	/*!
		@~english	@brief	Get valid values.
		@~english	@details	Get valid values.
		@~english	@param[in] pIFloatHandle	IFloat interface handle.
		@~english	@param[in] bounded	When true is specified, only values from the minimum value to the maximum value are considered. Default value for C++ is true.
		@~english	@param[out] pdblValueArray	Array of valid value.
		@~english	@param[in,out] pnCount	Input : Size of the array. Output : Count of the handles.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	許容される値を取得します。
		@~japanese	@details	許容される値を取得します。
		@~japanese	@param[in] pIFloatHandle	IFloat インターフェースハンドル
		@~japanese	@param[in] bounded	trueを指定した場合、最小値以上、最大値以下の値のみが対象となります。C++言語用の初期値はtrueです。
		@~japanese	@param[out] pdblValueArray	許容される値の配列
		@~japanese	@param[in,out] pnCount	配列のサイズを指定し、値の数を取得します。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IFloat_GetListOfValidValues_t)(const PStApiHandle_t pIFloatHandle, bool8_t bounded, double *pdblValueArray, size_t *pnCount);

	/*!
		@~english	@brief	Get recommended representation.
		@~english	@details	Get recommended representation.
		@~english	@param[in] pIFloatHandle	IFloat interface handle.
		@~english	@param[out] peValue	Recommended representation.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	推奨される表示形式を取得します。
		@~japanese	@details	推奨される表示形式を取得します。
		@~japanese	@param[in] pIFloatHandle	IFloat インターフェースハンドル
		@~japanese	@param[out] peValue	推奨される表示形式
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IFloat_GetRepresentation_t)(const PStApiHandle_t pIFloatHandle, ERepresentation  *peValue);

	/*!
		@~english	@brief	Get the physical unit name.
		@~english	@details	Get the physical unit name.
		@~english	@param[in] pIFloatHandle	IFloat interface handle.
		@~english	@param[in,out] szText	Unit name.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	単位を取得します。
		@~japanese	@details	単位を取得します。
		@~japanese	@param[in] pIFloatHandle	IFloat インターフェースハンドル
		@~japanese	@param[in,out] szText	単位
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IFloat_GetUnitA_t)(const PStApiHandle_t pIFloatHandle, char *szText, size_t *pnLen);

	/*!
		@~english	@brief	Get the way the float should be converted to a string.
		@~english	@details	Get the way the float should be converted to a string.
		@~english	@param[in] pIFloatHandle	IFloat interface handle.
		@~english	@param[out] peValue	Conversion method.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	浮動小数点数から文字列への変換方法を取得します。
		@~japanese	@details	浮動小数点数から文字列への変換方法を取得します。
		@~japanese	@param[in] pIFloatHandle	IFloat インターフェースハンドル
		@~japanese	@param[out] peValue	変換方法
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IFloat_GetDisplayNotation_t)(const PStApiHandle_t pIFloatHandle, EDisplayNotation *peValue);

	/*!
		@~english	@brief	Get the precision to be used when converting the float to a string.
		@~english	@details	Get the precision to be used when converting the float to a string.
		@~english	@param[in] pIFloatHandle	IFloat interface handle.
		@~english	@param[out] pnValue	Precision.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	浮動小数点数から文字列への変換する際の精度を取得します。
		@~japanese	@details	浮動小数点数から文字列への変換する際の精度を取得します。
		@~japanese	@param[in] pIFloatHandle	IFloat インターフェースハンドル
		@~japanese	@param[out] pnValue	精度
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IFloat_GetDisplayPrecision_t)(const PStApiHandle_t pIFloatHandle, int64_t *pnValue);

	/*!
		@~english	@brief	Restrict minimum value.
		@~english	@details	Restrict minimum value.
		@~english	@param[in] pIFloatHandle	IFloat interface handle.
		@~english	@param[in] Value	Minimum value.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	最小値に制限をかけます。
		@~japanese	@details	最小値に制限をかけます。
		@~japanese	@param[in] pIFloatHandle	IFloat インターフェースハンドル
		@~japanese	@param[in] Value	最小値
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IFloat_ImposeMin_t)(const PStApiHandle_t pIFloatHandle, double Value);

	/*!
		@~english	@brief	Restrict maximum value.
		@~english	@details	Restrict maximum value.
		@~english	@param[in] pIFloatHandle	IFloat interface handle.
		@~english	@param[in] Value	Maximum value.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	最大値に制限をかけます。
		@~japanese	@details	最大値に制限をかけます。
		@~japanese	@param[in] pIFloatHandle	IFloat インターフェースハンドル
		@~japanese	@param[in] Value	最大値
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IFloat_ImposeMax_t)(const PStApiHandle_t pIFloatHandle, double Value);

		
	/*!
		@ingroup GenApiC_PublicImpl
		@struct GenApi_IFloat_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IFloat.
		@~english	@details	This structure holds the address of the C language wrapper function of IFloat.
		@~japanese	@brief	この構造体は IFloat のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IFloat のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _GenApi_IFloat_Functions_t
	{
		/*!
			@copydoc PGenApi_IFloat_GetIFloat_t()
		*/
		PGenApi_IFloat_GetIFloat_t GetIFloat;
		/*!
			@copydoc PGenApi_IFloat_SetValue_t()
		*/
		PGenApi_IFloat_SetValue_t SetValue;
		/*!
			@copydoc PGenApi_IFloat_GetValue_t()
		*/
		PGenApi_IFloat_GetValue_t GetValue;
		/*!
			@copydoc PGenApi_IFloat_GetMin_t()
		*/
		PGenApi_IFloat_GetMin_t GetMin;
		/*!
			@copydoc PGenApi_IFloat_GetMax_t()
		*/
		PGenApi_IFloat_GetMax_t GetMax;
		/*!
			@copydoc PGenApi_IFloat_HasInc_t()
		*/
		PGenApi_IFloat_HasInc_t HasInc;
		/*!
			@copydoc PGenApi_IFloat_GetIncMode_t()
		*/
		PGenApi_IFloat_GetIncMode_t GetIncMode;
		/*!
			@copydoc PGenApi_IFloat_GetInc_t()
		*/
		PGenApi_IFloat_GetInc_t GetInc;
		/*!
			@copydoc PGenApi_IFloat_GetListOfValidValues_t()
		*/
		PGenApi_IFloat_GetListOfValidValues_t GetListOfValidValues;
		/*!
			@copydoc PGenApi_IFloat_GetRepresentation_t()
		*/
		PGenApi_IFloat_GetRepresentation_t GetRepresentation;
		/*!
			@copydoc PGenApi_IFloat_GetUnitA_t()
		*/
		PGenApi_IFloat_GetUnitA_t GetUnitA;
		/*!
			@copydoc PGenApi_IFloat_GetDisplayNotation_t()
		*/
		PGenApi_IFloat_GetDisplayNotation_t GetDisplayNotation;
		/*!
			@copydoc PGenApi_IFloat_GetDisplayPrecision_t()
		*/
		PGenApi_IFloat_GetDisplayPrecision_t GetDisplayPrecision;
		/*!
			@copydoc PGenApi_IFloat_ImposeMin_t()
		*/
		PGenApi_IFloat_ImposeMin_t ImposeMin;
		/*!
			@copydoc PGenApi_IFloat_ImposeMax_t()
		*/
		PGenApi_IFloat_ImposeMax_t ImposeMax;

	}GenApi_IFloat_Functions_t, *PGenApi_IFloat_Functions_t;



	/*************************************************************************/
	/* GenApi::IInteger */
	/*************************************************************************/
	/*!
		@~english	@brief	Get IInteger handle.
		@~english	@details	Get IInteger handle.
		@~english	@param[in] pSourceHandle	Interface handle that is enable to convert to IInteger interface handle.
		@~english	@param[in,out] pIIntegerHandle	IInteger interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IIntegerハンドルを取得します。
		@~japanese	@details	IIntegerハンドルを取得します。
		@~japanese	@param[in] pSourceHandle	IInteger インターフェースハンドルに変換可能なインターフェースハンドル
		@~japanese	@param[in,out] pIIntegerHandle	IInteger インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IInteger_GetIInteger_t)(const PStApiHandle_t pSourceHandle, PStApiHandle_t pIIntegerHandle);
	
	/*!
		@~english	@brief	Set node value.
		@~english	@details	Set node value.
		@~english	@param[in] pIIntegerHandle	IInteger interface handle.
		@~english	@param[in] Value	The value to set.
		@~english	@param[in] Verify	Enables AccessMode and Range verification. Default value for C++ is true.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ノードの値を設定します。
		@~japanese	@details	ノードの値を設定します。
		@~japanese	@param[in] pIIntegerHandle	IInteger インターフェースハンドル
		@~japanese	@param[in] Value	ノードの値
		@~japanese	@param[in] Verify	trueを指定すると、アクセスモードと値の範囲のチェックが行われます。C++言語用の初期値はtrueです。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IInteger_SetValue_t)(const PStApiHandle_t pIIntegerHandle, int64_t Value, bool8_t Verify);

	/*!
		@~english	@brief	Get node value.
		@~english	@details	Get node value.
		@~english	@param[in] pIIntegerHandle	IInteger interface handle.
		@~english	@param[in] Verify	Verify Enables Range verification. The AccessMode is always checked. Default value for C++ is false.
		@~english	@param[in] IgnoreCache	If true the value is read ignoring any caches. Default value for C++ is false.
		@~english	@param[out] pnValue	The value read.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ノードの値を取得します。
		@~japanese	@details	ノードの値を取得します。
		@~japanese	@param[in] pIIntegerHandle	IInteger インターフェースハンドル
		@~japanese	@param[in] Verify	trueを指定すると値の範囲のチェックが行われます。アクセスモードは常にチェックされます。C++言語用の初期値はfalseです。
		@~japanese	@param[in] IgnoreCache	trueを指定すると、キャッシュを無視して読み込みが行われます。C++言語用の初期値はfalseです。
		@~japanese	@param[out] pnValue	ノードの値
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IInteger_GetValue_t)(const PStApiHandle_t pIIntegerHandle, bool8_t Verify, bool8_t IgnoreCache, int64_t *pnValue);

	/*!
		@~english	@brief	Get minimum value allowed.
		@~english	@details	Get minimum value allowed.
		@~english	@param[in] pIIntegerHandle	IInteger interface handle.
		@~english	@param[out] pnValue	Minimum value.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	最小値を取得します。
		@~japanese	@details	最小値を取得します。
		@~japanese	@param[in] pIIntegerHandle	IInteger インターフェースハンドル
		@~japanese	@param[out] pnValue	最小値
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IInteger_GetMin_t)(const PStApiHandle_t pIIntegerHandle, int64_t *pnValue);

	/*!
		@~english	@brief	Get maximum value allowed.
		@~english	@details	Get maximum value allowed.
		@~english	@param[in] pIIntegerHandle	IInteger interface handle.
		@~english	@param[out] pnValue	Maximum value.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	最大値を取得します。
		@~japanese	@details	最大値を取得します。
		@~japanese	@param[in] pIIntegerHandle	IInteger インターフェースハンドル
		@~japanese	@param[out] pnValue	最大値
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IInteger_GetMax_t)(const PStApiHandle_t pIIntegerHandle, int64_t *pnValue);

	/*!
		@~english	@brief	Get increment mode.
		@~english	@details	Get increment mode.
		@~english	@param[in] pIIntegerHandle	IInteger interface handle.
		@~english	@param[out] peValue	Increment mode.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	増分モードを取得します。
		@~japanese	@details	増分モードを取得します。
		@~japanese	@param[in] pIIntegerHandle	IInteger インターフェースハンドル
		@~japanese	@param[out] peValue	増分モード
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IInteger_GetIncMode_t)(const PStApiHandle_t pIIntegerHandle, EIncMode *peValue);

	/*!
		@~english	@brief	Get increment value.
		@~english	@details	Get increment value.
		@~english	@param[in] pIIntegerHandle	IInteger interface handle.
		@~english	@param[out] pnValue	Increment value.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	増分値を取得します。
		@~japanese	@details	増分値を取得します。
		@~japanese	@param[in] pIIntegerHandle	IInteger インターフェースハンドル
		@~japanese	@param[out] pnValue	増分値
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IInteger_GetInc_t)(const PStApiHandle_t pIIntegerHandle, int64_t *pnValue);

	/*!
		@~english	@brief	Get valid values.
		@~english	@details	Get valid values.
		@~english	@param[in] pIIntegerHandle	IInteger interface handle.
		@~english	@param[in] bounded	When true is specified, only values from the minimum value to the maximum value are considered. Default value for C++ is true.
		@~english	@param[out] pnValue	Array of valid value.
		@~english	@param[in,out] pnCount	Input : Size of the array. Output : Count of the handles.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	許容される値を取得します。
		@~japanese	@details	許容される値を取得します。
		@~japanese	@param[in] pIIntegerHandle	IInteger インターフェースハンドル
		@~japanese	@param[in] bounded	trueを指定した場合、最小値以上、最大値以下の値のみが対象となります。C++言語用の初期値はtrueです。
		@~japanese	@param[out] pnValue	許容される値の配列
		@~japanese	@param[in,out] pnCount	配列のサイズを指定し、値の数を取得します。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IInteger_GetListOfValidValues_t)(const PStApiHandle_t pIIntegerHandle, bool8_t bounded, int64_t *pnValue, size_t *pnCount);

	/*!
		@~english	@brief	Get recommended representation.
		@~english	@details	Get recommended representation.
		@~english	@param[in] pIIntegerHandle	IInteger interface handle.
		@~english	@param[out] peValue	Recommended representation.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	推奨される表示形式を取得します。
		@~japanese	@details	推奨される表示形式を取得します。
		@~japanese	@param[in] pIIntegerHandle	IInteger インターフェースハンドル
		@~japanese	@param[out] peValue	推奨される表示形式
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IInteger_GetRepresentation_t)(const PStApiHandle_t pIIntegerHandle, ERepresentation *peValue);

	/*!
		@~english	@brief	Get the physical unit name.
		@~english	@details	Get the physical unit name.
		@~english	@param[in] pIIntegerHandle	IInteger interface handle.
		@~english	@param[in,out] szText	Unit name.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	単位を取得します。
		@~japanese	@details	単位を取得します。
		@~japanese	@param[in] pIIntegerHandle	IInteger インターフェースハンドル
		@~japanese	@param[in,out] szText	単位
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IInteger_GetUnitA_t)(const PStApiHandle_t pIIntegerHandle, char *szText, size_t *pnLen);

	/*!
		@~english	@brief	Restrict minimum value.
		@~english	@details	Restrict minimum value.
		@~english	@param[in] pIIntegerHandle	IInteger interface handle.
		@~english	@param[in] Value	Minimum value.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	最小値に制限をかけます。
		@~japanese	@details	最小値に制限をかけます。
		@~japanese	@param[in] pIIntegerHandle	IInteger インターフェースハンドル
		@~japanese	@param[in] Value	最小値
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IInteger_ImposeMin_t)(const PStApiHandle_t pIIntegerHandle, int64_t Value);

	/*!
		@~english	@brief	Restrict maximum value.
		@~english	@details	Restrict maximum value.
		@~english	@param[in] pIIntegerHandle	IInteger interface handle.
		@~english	@param[in] Value	Maximum value.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	最大値に制限をかけます。
		@~japanese	@details	最大値に制限をかけます。
		@~japanese	@param[in] pIIntegerHandle	IInteger インターフェースハンドル
		@~japanese	@param[in] Value	最大値
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IInteger_ImposeMax_t)(const PStApiHandle_t pIIntegerHandle, int64_t Value);
	
	/*!
		@ingroup GenApiC_PublicImpl
		@struct GenApi_IInteger_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IInteger.
		@~english	@details	This structure holds the address of the C language wrapper function of IInteger.
		@~japanese	@brief	この構造体は IInteger のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IInteger のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _GenApi_IInteger_Functions_t
	{
		/*!
			@copydoc PGenApi_IInteger_GetIInteger_t()
		*/

		PGenApi_IInteger_GetIInteger_t GetIInteger;
		/*!
			@copydoc PGenApi_IInteger_SetValue_t()
		*/
		PGenApi_IInteger_SetValue_t SetValue;
		/*!
			@copydoc PGenApi_IInteger_GetValue_t()
		*/
		PGenApi_IInteger_GetValue_t GetValue;
		/*!
			@copydoc PGenApi_IInteger_GetMin_t()
		*/
		PGenApi_IInteger_GetMin_t GetMin;
		/*!
			@copydoc PGenApi_IInteger_GetMax_t()
		*/
		PGenApi_IInteger_GetMax_t GetMax;
		/*!
			@copydoc PGenApi_IInteger_GetIncMode_t()
		*/
		PGenApi_IInteger_GetIncMode_t GetIncMode;
		/*!
			@copydoc PGenApi_IInteger_GetInc_t()
		*/
		PGenApi_IInteger_GetInc_t GetInc;
		/*!
			@copydoc PGenApi_IInteger_GetListOfValidValues_t()
		*/
		PGenApi_IInteger_GetListOfValidValues_t GetListOfValidValues;
		/*!
			@copydoc PGenApi_IInteger_GetRepresentation_t()
		*/
		PGenApi_IInteger_GetRepresentation_t GetRepresentation;
		/*!
			@copydoc PGenApi_IInteger_GetUnitA_t()
		*/
		PGenApi_IInteger_GetUnitA_t GetUnitA;
		/*!
			@copydoc PGenApi_IInteger_ImposeMin_t()
		*/
		PGenApi_IInteger_ImposeMin_t ImposeMin;
		/*!
			@copydoc PGenApi_IInteger_ImposeMax_t()
		*/
		PGenApi_IInteger_ImposeMax_t ImposeMax;
	}GenApi_IInteger_Functions_t, *PGenApi_IInteger_Functions_t;



	/*************************************************************************/
	/* GenApi::IRegister */
	/*************************************************************************/
	/*!
		@~english	@brief	Get IRegister handle.
		@~english	@details	Get IRegister handle.
		@~english	@param[in] pSourceHandle	Interface handle that is enable to convert to IRegister interface handle.
		@~english	@param[in,out] pIRegisterHandle	IRegister interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IRegisterハンドルを取得します。
		@~japanese	@details	IRegisterハンドルを取得します。
		@~japanese	@param[in] pSourceHandle	IRegister インターフェースハンドルに変換可能なインターフェースハンドル
		@~japanese	@param[in,out] pIRegisterHandle	IRegister インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IRegister_GetIRegister_t)(const PStApiHandle_t pSourceHandle, PStApiHandle_t pIRegisterHandle);

	/*!
		@~english	@brief	Set the register's contents.
		@~english	@details	Set the register's contents.
		@~english	@param[in] pIRegisterHandle	IRegister interface handle.
		@~english	@param[in] pBuffer	The buffer containing the data to set.
		@~english	@param[in] Length	The number of bytes in pBuffer.
		@~english	@param[in] Verify	Enables AccessMode and Range verification. Default value for C++ is true.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	レジスターに書き込みます。
		@~japanese	@details	レジスターに書き込みます。
		@~japanese	@param[in] pIRegisterHandle	IRegister インターフェースハンドル
		@~japanese	@param[in] pBuffer	書き込むデータへのポインター
		@~japanese	@param[in] Length	書き込むデータのサイズ(バイト単位)
		@~japanese	@param[in] Verify	trueを指定すると、アクセスモードと範囲のチェックが有効になります。C++言語用の初期値はtrueです。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IRegister_Set_t)(const PStApiHandle_t pIRegisterHandle, const uint8_t *pBuffer, int64_t Length, bool8_t Verify);

	/*!
		@~english	@brief	Fills a buffer with the register's contents.
		@~english	@details	Fills a buffer with the register's contents.
		@~english	@param[in] pIRegisterHandle	IRegister interface handle.
		@~english	@param[out] pBuffer	The buffer receiving the data to read.
		@~english	@param[in] Length	The number of bytes to retrieve.
		@~english	@param[in] Verify	Enables Range verification. The AccessMode is always checked. Default value for C++ is false.
		@~english	@param[in] IgnoreCache	If true the value is read ignoring any caches. Default value for C++ is false.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	レジスターから読み込みます。
		@~japanese	@details	レジスターから読み込みます。
		@~japanese	@param[in] pIRegisterHandle	IRegister インターフェースハンドル
		@~japanese	@param[out] pBuffer	データを読み込むバッファへのポインター
		@~japanese	@param[in] Length	読み込むデータのサイズ(バイト単位)
		@~japanese	@param[in] Verify	trueを指定すると、アクセスモードと範囲のチェックが有効になります。C++言語用の初期値はfalseです。
		@~japanese	@param[in] IgnoreCache	trueを指定すると、キャッシュを無視して読み込みを行います。C++言語用の初期値はfalseです。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IRegister_Get_t)(const PStApiHandle_t pIRegisterHandle, uint8_t *pBuffer, int64_t Length, bool8_t Verify, bool8_t IgnoreCache);

	/*!
		@~english	@brief	Retrieves the Length of the register.
		@~english	@details	Retrieves the Length of the register.
		@~english	@param[in] pIRegisterHandle	IRegister interface handle.
		@~english	@param[out] pnValue	Length [Bytes].
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	レジスターのサイズを取得します。
		@~japanese	@details	レジスターのサイズを取得します。
		@~japanese	@param[in] pIRegisterHandle	IRegister インターフェースハンドル
		@~japanese	@param[out] pnValue	レジスターのサイズ(バイト単位)
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IRegister_GetLength_t)(const PStApiHandle_t pIRegisterHandle, int64_t *pnValue);

	/*!
		@~english	@brief	Retrieves the Address of the register.
		@~english	@details	Retrieves the Address of the register.
		@~english	@param[in] pIRegisterHandle	IRegister interface handle.
		@~english	@param[out] pnValue	Address.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	レジスターのアドレスを取得します。
		@~japanese	@details	レジスターのアドレスを取得します。
		@~japanese	@param[in] pIRegisterHandle	IRegister インターフェースハンドル
		@~japanese	@param[out] pnValue	アドレス
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IRegister_GetAddress_t)(const PStApiHandle_t pIRegisterHandle, int64_t *pnValue);
	
	/*!
		@ingroup GenApiC_PublicImpl
		@struct GenApi_IRegister_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IRegister.
		@~english	@details	This structure holds the address of the C language wrapper function of IRegister.
		@~japanese	@brief	この構造体は IRegister のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IRegister のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _GenApi_IRegister_Functions_t
	{
		/*!
			@copydoc PGenApi_IRegister_GetIRegister_t()
		*/
		PGenApi_IRegister_GetIRegister_t	GetIRegister;
		/*!
			@copydoc PGenApi_IRegister_Set_t()
		*/
		PGenApi_IRegister_Set_t	Set;
		/*!
			@copydoc PGenApi_IRegister_Get_t()
		*/
		PGenApi_IRegister_Get_t	Get;
		/*!
			@copydoc PGenApi_IRegister_GetLength_t()
		*/
		PGenApi_IRegister_GetLength_t	GetLength;
		/*!
			@copydoc PGenApi_IRegister_GetAddress_t()
		*/
		PGenApi_IRegister_GetAddress_t	GetAddress;
	}GenApi_IRegister_Functions_t, *PGenApi_IRegister_Functions_t;


	/*************************************************************************/
	/* GenApi::ISelector */
	/*************************************************************************/
	/*!
		@~english	@brief	Get ISelector handle.
		@~english	@details	Get ISelector handle.
		@~english	@param[in] pSourceHandle	Interface handle that is enable to convert to ISelector interface handle.
		@~english	@param[in,out] pISelectorHandle	ISelector interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ISelectorハンドルを取得します。
		@~japanese	@details	ISelectorハンドルを取得します。
		@~japanese	@param[in] pSourceHandle	ISelector インターフェースハンドルに変換可能なインターフェースハンドル
		@~japanese	@param[in,out] pISelectorHandle	ISelector インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_ISelector_GetISelector_t)(const PStApiHandle_t pSourceHandle, PStApiHandle_t pISelectorHandle);
	
	/*!
		@~english	@brief	Checks if this feature selects a group of features.
		@~english	@details	Checks if this feature selects a group of features.
		@~english	@param[in] pISelectorHandle	ISelector interface handle.
		@~english	@param[out] pbValue	True if this feature selects a group of features.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	この機能が機能グループを選択するかどうかチェックします。
		@~japanese	@details	この機能が機能グループを選択するかどうかチェックします。
		@~japanese	@param[in] pISelectorHandle	ISelector インターフェースハンドル
		@~japanese	@param[out] pbValue	選択する場合、trueが返されます。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_ISelector_IsSelector_t)(const PStApiHandle_t pISelectorHandle, bool8_t *pbValue);

	/*!
		@~english	@brief	Retrieve a selected features.
		@~english	@details	Retrieve a selected features.
		@~english	@param[in] pISelectorHandle	ISelector interface handle.
		@~english	@param[in,out] pIValueHandleArray	IValue interface handle array.
		@~english	@param[in,out] pnCount	Input : Size of the array. Output : Count of the handles.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	この機能によって値が選択される機能を取得します。
		@~japanese	@details	この機能によって値が選択される機能を取得します。
		@~japanese	@param[in] pISelectorHandle	ISelector インターフェースハンドル
		@~japanese	@param[in,out] pIValueHandleArray	IValue インターフェースハンドル配列
		@~japanese	@param[in,out] pnCount 配列のサイズを指定して、ハンドルの数を取得します。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_ISelector_GetSelectedFeatures_t)(const PStApiHandle_t pISelectorHandle, PStApiHandle_t pIValueHandleArray, size_t *pnCount);

	/*!
		@~english	@brief	Retrieve features selecting this node.
		@~english	@details	Retrieve features selecting this node.
		@~english	@param[in] pISelectorHandle	ISelector interface handle.
		@~english	@param[in,out] pIValueHandle	IValue interface handle array.
		@~english	@param[in,out] pnCount	Input : Size of the array. Output : Count of the handles.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	この機能の値を選択する機能を取得します。
		@~japanese	@details	この機能の値を選択する機能を取得します。
		@~japanese	@param[in] pISelectorHandle	ISelector インターフェースハンドル
		@~japanese	@param[in,out] pIValueHandle	IValue インターフェースハンドル配列
		@~japanese	@param[in,out] pnCount	配列のサイズを指定して、ハンドルの数を取得します。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_ISelector_GetSelectingFeatures_t)(const PStApiHandle_t pISelectorHandle, PStApiHandle_t pIValueHandle, size_t *pnCount);
	
	/*!
		@ingroup GenApiC_PublicImpl
		@struct GenApi_ISelector_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of ISelector.
		@~english	@details	This structure holds the address of the C language wrapper function of ISelector.
		@~japanese	@brief	この構造体は ISelector のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は ISelector のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _GenApi_ISelector_Functions_t
	{
		/*!
			@copydoc PGenApi_ISelector_GetISelector_t()
		*/

		PGenApi_ISelector_GetISelector_t	GetISelector;
		/*!
			@copydoc PGenApi_ISelector_IsSelector_t()
		*/
		PGenApi_ISelector_IsSelector_t	IsSelector;

		/*!
			@copydoc PGenApi_ISelector_GetSelectedFeatures_t()
		*/
		PGenApi_ISelector_GetSelectedFeatures_t	GetSelectedFeatures;

		/*!
			@copydoc PGenApi_ISelector_GetSelectingFeatures_t()
		*/
		PGenApi_ISelector_GetSelectingFeatures_t	GetSelectingFeatures;
	}GenApi_ISelector_Functions_t, *PGenApi_ISelector_Functions_t;

	/*************************************************************************/
	/* GenApi::IString */
	/*************************************************************************/
	/*!
		@~english	@brief	Get IString handle.
		@~english	@details	Get IString handle.
		@~english	@param[in] pSourceHandle	Interface handle that is enable to convert to IString interface handle.
		@~english	@param[in,out] pIStringHandle	IString interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStringハンドルを取得します。
		@~japanese	@details	IStringハンドルを取得します。
		@~japanese	@param[in] pSourceHandle	IString インターフェースハンドルに変換可能なインターフェースハンドル
		@~japanese	@param[in,out] pIStringHandle	IString インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IString_GetIString_t)(const PStApiHandle_t pSourceHandle, PStApiHandle_t pIStringHandle);

	/*!
		@~english	@brief	Set node value.
		@~english	@details	Set node value.
		@~english	@param[in] pIStringHandle	IString interface handle.
		@~english	@param[in] szValue	The value to set.
		@~english	@param[in] Verify Enables AccessMode and Range verification. Default value for C++ is true.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ノードの値を設定します。
		@~japanese	@details	ノードの値を設定します。
		@~japanese	@param[in] pIStringHandle	IString インターフェースハンドル
		@~japanese	@param[in] szValue	設定する値
		@~japanese	@param[in] Verify trueを指定すると、アクセスモードと範囲のチェックが行われます。C++言語用の初期値はtrueです。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IString_SetValueA_t)(const PStApiHandle_t pIStringHandle, const char *szValue, bool8_t Verify);

	/*!
		@~english	@brief	Get node value.
		@~english	@details	Get node value.
		@~english	@param[in] pIStringHandle	IString interface handle.
		@~english	@param[in] Verify Enables Range verification. Default value for C++ is false. The AccessMode is always checked
		@~english	@param[in] IgnoreCache If true the value is read ignoring any caches. Default value for C++ is false.
		@~english	@param[in,out] szText	The value read.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ノードの値を取得します。
		@~japanese	@details	ノードの値を取得します。
		@~japanese	@param[in] pIStringHandle	IString インターフェースハンドル
		@~japanese	@param[in] Verify trueを指定すると範囲のチェックが行われます。C++言語用の初期値はfalseです。アクセスモードのチェックは常に行われます。
		@~japanese	@param[in] IgnoreCache trueを指定するとキャッシュを無視して読み込みが行われます。C++言語用の初期値はfalseです。
		@~japanese	@param[in] pIStringHandle	IString インターフェースハンドル
		@~japanese	@param[in,out] szText	値
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IString_GetValueA_t)(const PStApiHandle_t pIStringHandle, bool8_t Verify, bool8_t IgnoreCache, char *szText, size_t *pnLen);

	/*!
		@~english	@brief	Retrieves the maximum length of the string in bytes.
		@~english	@details	Retrieves the maximum length of the string in bytes.
		@~english	@param[in] pIStringHandle	IString interface handle.
		@~english	@param[out] pnValue	Maximum length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	文字列の最大長(バイト単位)を取得します。
		@~japanese	@details	文字列の最大長(バイト単位)を取得します。
		@~japanese	@param[in] pIStringHandle	IString インターフェースハンドル
		@~japanese	@param[out] pnValue	最大長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PGenApi_IString_GetMaxLength_t)(const PStApiHandle_t pIStringHandle, int64_t *pnValue);
	
	/*!
		@ingroup GenApiC_PublicImpl
		@struct GenApi_IString_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IString.
		@~english	@details	This structure holds the address of the C language wrapper function of IString.
		@~japanese	@brief	この構造体は IString のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IString のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _GenApi_IString_Functions_t
	{
		/*!
			@copydoc PGenApi_IString_GetIString_t()
		*/

		PGenApi_IString_GetIString_t	GetIString;
		/*!
			@copydoc PGenApi_IString_SetValueA_t()
		*/
		PGenApi_IString_SetValueA_t	SetValueA;
		/*!
			@copydoc PGenApi_IString_GetValueA_t()
		*/
		PGenApi_IString_GetValueA_t	GetValueA;
		/*!
			@copydoc PGenApi_IString_GetMaxLength_t()
		*/
		PGenApi_IString_GetMaxLength_t	GetMaxLength;
	}GenApi_IString_Functions_t, *PGenApi_IString_Functions_t;

	/*!
		@ingroup GenApiC_PublicImpl
		@struct GenApi_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of GenApi.
		@~english	@details	This structure holds the address of the C language wrapper function of GenApi.
		@~japanese	@brief	この構造体はGenApiのC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体はGenApiのC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _GenApi_Functions_t
	{
		/*!
			@copydoc GenApi_IPublic_Functions_t
		*/
		GenApi_IPublic_Functions_t				*IPublic;

		/*!
			@copydoc GenApi_INodeMap_Functions_t
		*/
		GenApi_INodeMap_Functions_t				*INodeMap;

		/*!
			@copydoc GenApi_IDeviceInfo_Functions_t
		*/
		GenApi_IDeviceInfo_Functions_t				*IDeviceInfo;

		/*!
			@copydoc GenApi_IUserData_Functions_t
		*/
		GenApi_IUserData_Functions_t				*IUserData;
			
		/*!
			@copydoc GenApi_ILock_Functions_t
		*/
		GenApi_ILock_Functions_t				*ILock;

		/*!
			@copydoc GenApi_IBase_Functions_t
		*/
		GenApi_IBase_Functions_t				*IBase;

		/*!
			@copydoc GenApi_IValue_Functions_t
		*/
		GenApi_IValue_Functions_t				*IValue;

		/*!
			@copydoc GenApi_INode_Functions_t
		*/
		GenApi_INode_Functions_t				*INode;

		/*!
			@copydoc GenApi_IPort_Functions_t
		*/
		GenApi_IPort_Functions_t				*IPort;

		/*!
			@copydoc GenApi_IChunkPort_Functions_t
		*/
		GenApi_IChunkPort_Functions_t				*IChunkPort;

		/*!
			@copydoc GenApi_IBoolean_Functions_t
		*/
		GenApi_IBoolean_Functions_t				*IBoolean;

		/*!
			@copydoc GenApi_ICategory_Functions_t
		*/
		GenApi_ICategory_Functions_t			*ICategory;

		/*!
			@copydoc GenApi_ICommand_Functions_t
		*/
		GenApi_ICommand_Functions_t				*ICommand;

		/*!
			@copydoc GenApi_IEnumEntry_Functions_t
		*/
		GenApi_IEnumEntry_Functions_t			*IEnumEntry;

		/*!
			@copydoc GenApi_IEnumeration_Functions_t
		*/
		GenApi_IEnumeration_Functions_t			*IEnumeration;

		/*!
			@copydoc GenApi_IFloat_Functions_t
		*/
		GenApi_IFloat_Functions_t				*IFloat;

		/*!
			@copydoc GenApi_IInteger_Functions_t
		*/
		GenApi_IInteger_Functions_t				*IInteger;

		/*!
			@copydoc GenApi_IRegister_Functions_t
		*/
		GenApi_IRegister_Functions_t			*IRegister;

		/*!
			@copydoc GenApi_ISelector_Functions_t
		*/
		GenApi_ISelector_Functions_t			*ISelector;

		/*!
			@copydoc GenApi_IString_Functions_t
		*/
		GenApi_IString_Functions_t				*IString;
	}GenApi_Functions_t, *PGenApi_Functions_t;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STAPI_C_GENAPI_H__ */
