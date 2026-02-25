/* This file is encoded in UTF-8,  */
/* but BOM has not been added to accommodate environments not compatible with BOM. */
/*
 StApi C
*/
/*!
	@ingroup	StApiC_PublicImpl
	@file StApi_C_StApi.h
	@~english	@details
	@~japanese	@details
*/

#if !defined(STAPI_C_STAPI_H__)
#define STAPI_C_STAPI_H__

#include "StApi_C_Def.h"

#ifdef _WIN32
#include "windows.h"	/* HWND, HDC */
#else
#include "StApi_Platform.h"
#endif

#ifdef __cplusplus
extern "C" {
	using namespace GenTL;
	using namespace StApi;
#endif /* __cplusplus */


	/*************************************************************************/
	/* StApi */
	/*************************************************************************/
	/*!
		@~english	@brief	Uninitialize StApiC.
		@~english	@details	Uninitialize StApiC. Call this function to release resources and deinitialize the StApiC. 
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	StApiCライブラリの終了処理を行います。
		@~japanese	@details	StApiCライブラリの終了処理を行います。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApi_StApiCTerminate_t)(void);

	/*!
		@~english	@brief	Acquire version of the running StApi.
		@~english	@details	Acquire version of the running StApi.
		@~english	@param[out]	pnVersion	Version of the running StApi.
		@~english	@return	EStApiCError_t error code.
		@~english	@sa	 STAPI_VERSION_MAJOR
		@~japanese	@brief	実行中のStApiのバージョンを取得します。
		@~japanese	@details	StApiのバージョンを取得します。bit31-24:メジャーバージョン, bit23-16:マイナーバージョン, bit15-0:サブマイナーバージョン。
		@~japanese	@param[out]	pnVersion	StApi実行時バージョン
		@~japanese	@sa	 STAPI_VERSION_MAJOR
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApi_GetStApiVersion_t)(uint32_t *pnVersion);
	
	/*!
		@~english	@brief	Acquire version of the running StApi.
		@~english	@details	Acquire version of the running StApi.
		@~english	@param[in,out] szText	Version of the running StApi.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~english	@sa	 STAPI_VERSION_MAJOR
		@~japanese	@brief	実行中のStApiのバージョンを取得します。
		@~japanese	@details	StApiのバージョンを取得します。Major.Minor.SubMinor
		@~japanese	@param[in,out] szText	StApi実行時バージョン文字列
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
		@~japanese	@sa	 STAPI_VERSION_MAJOR
	*/
	STAPI_PCALL(PStApi_GetStApiVersionTextA_t)(char *szText, size_t *pnLen);
	
	/*!
		@~english	@brief	Acquire the description string of the last error.
		@~english	@details	Acquire the description string of the last error.
		@~english	@param[in,out] szText	The description string of the last error.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	最後に発生したエラーの詳細文字列を取得します。
		@~japanese	@details	最後に発生したエラーの詳細文字列を取得します。
		@~japanese	@param[in,out] szText	エラー詳細文字列
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApi_GetLastErrorDescriptionA_t)(char *szText, size_t *pnLen);

	/*!
		@~english	@brief	Acquire the description string of the last error.
		@~english	@details	Acquire the description string of the last error.
		@~english	@param[in,out] szText	The description string of the last error.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	最後に発生したエラーの詳細文字列を取得します。
		@~japanese	@details	最後に発生したエラーの詳細文字列を取得します。
		@~japanese	@param[in,out] szText	エラー詳細文字列
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
		@since StApi v1.1.1
	*/
	STAPI_PCALL(PStApi_GetLastErrorDescriptionW_t)(wchar_t *szText, size_t *pnLen);

	/*************************************************************************/
	/* StApi::IStPort */
	/*************************************************************************/
	/*!
		@~english	@brief	Acquire the number of available URLs of this port.
		@~english	@details	Acquire the number of available URLs of this port.
		@~english	@param[in] pIStPortHandle	IStPort interface handle.
		@~english	@param[in] pnCount	Number of avaliable URLs of this port.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	このポートの利用可能なURLの数を取得します。
		@~japanese	@details	このポートの利用可能なURLの数を取得します。
		@~japanese	@param[in] pIStPortHandle	IStPort インターフェースハンドル
		@~japanese	@param[in] pnCount	このポートの利用可能なURLの数
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStPort_GetPortURLCount_t)(const PStApiHandle_t pIStPortHandle, uint32_t *pnCount);

	/*!
		@~english	@brief	Acquire the index of the Port URL.
		@~english	@details	Acquire the index of the Port URL.
		@~english	@param[in] pIStPortHandle	IStPort interface handle.
		@~english	@param[in] pnIndex	Index of the Port URL.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ポートURLインディックスの設定値を取得します。
		@~japanese	@details	ポートURLインディックスの設定値を取得します。
		@~japanese	@param[in] pIStPortHandle	IStPort インターフェースハンドル
		@~japanese	@param[in] pnIndex	ポートURLインディックス
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStPort_GetPortURLIndex_t)(const PStApiHandle_t pIStPortHandle, uint32_t *pnIndex);

	/*!
		@~english	@brief	Set the index of the Port URL.
		@~english	@details	Set the index of the Port URL.
		@~english	@param[in] pIStPortHandle	IStPort interface handle.
		@~english	@param[in] nIndex	Index of the Port URL.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ポートURLインディックスの値を設定します。
		@~japanese	@details	ポートURLインディックスの値を設定します。
		@~japanese	@param[in] pIStPortHandle	IStPort インターフェースハンドル
		@~japanese	@param[in] nIndex	ポートURLインディックス
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStPort_SetPortURLIndex_t)(const PStApiHandle_t pIStPortHandle, uint32_t nIndex);

	/*!
		@~english	@brief	Acquire IStPortURLInfo interface handle of the Port URL.
		@~english	@details	Acquire IStPortURLInfo interface handle of the Port URL.
		@~english	@param[in] pIStPortHandle	IStPort interface handle.
		@~english	@param[in,out] pIStPortURLInfoHandle	IStPortURLInfo interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStPortURLInfo インターフェースハンドルを取得します。
		@~japanese	@details	IStPortURLInfo インターフェースハンドルを取得します。
		@~japanese	@param[in] pIStPortHandle	IStPort インターフェースハンドル
		@~japanese	@param[in,out] pIStPortURLInfoHandle	IStPortURLInfo インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStPort_GetIStPortURLInfo_t)(const PStApiHandle_t pIStPortHandle, PStApiHandle_t pIStPortURLInfoHandle);

	/*!
		@~english	@brief	Acquire INodeMap interface handle of this port.
		@~english	@details	Acquire INodeMap interface handle of this port.
		@~english	@param[in] pIStPortHandle	IStPort interface handle.
		@~english	@param[in,out] pINodeMapHandle	INodeMap interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	INodeMap インターフェースハンドルを取得します。
		@~japanese	@details	INodeMap インターフェースハンドルを取得します。
		@~japanese	@param[in] pIStPortHandle	IStPort インターフェースハンドル
		@~japanese	@param[in,out] pINodeMapHandle	INodeMap インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStPort_GetINodeMap_t)(const PStApiHandle_t pIStPortHandle, PStApiHandle_t pINodeMapHandle);

	/*!
		@~english	@brief	Acquire IStPortInfo interface handle of this port.
		@~english	@details	Acquire IStPortInfo interface handle of this port.
		@~english	@param[in] pIStPortHandle	IStPort interface handle.
		@~english	@param[in,out] pIStPortInfoHandle	IStPortInfo interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStPortInfo インターフェースハンドルを取得します。
		@~japanese	@details	IStPortInfo インターフェースハンドルを取得します。
		@~japanese	@param[in] pIStPortHandle	IStPort インターフェースハンドル
		@~japanese	@param[in,out] pIStPortInfoHandle	IStPortInfo インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStPort_GetIStPortInfo_t)(const PStApiHandle_t pIStPortHandle, PStApiHandle_t pIStPortInfoHandle);

	/*!
		@~english	@brief	Acquire the XML file name.
		@~english	@details	Acquire the XML file name.
		@~english	@param[in] pIStPortHandle	IStPort interface handle.
		@~english	@param[in,out] szText	XML file name.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	XMLファイルのファイル名を取得します。
		@~japanese	@details	XMLファイルのファイル名を取得します。
		@~japanese	@param[in] pIStPortHandle	IStPort インターフェースハンドル
		@~japanese	@param[in,out] szText	XMLファイルのファイル名
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStPort_GetXMLFileNameW_t)(const PStApiHandle_t pIStPortHandle, wchar_t *szText, size_t *pnLen);

	/*!
		@~english	@brief	Acquire the XML file name.
		@~english	@details	Acquire the XML file name.
		@~english	@param[in] pIStPortHandle	IStPort interface handle.
		@~english	@param[in,out] szText	XML file name.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	XMLファイルのファイル名を取得します。
		@~japanese	@details	XMLファイルのファイル名を取得します。
		@~japanese	@param[in] pIStPortHandle	IStPort インターフェースハンドル
		@~japanese	@param[in,out] szText	XMLファイルのファイル名
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStPort_GetXMLFileNameA_t)(const PStApiHandle_t pIStPortHandle, char *szText, size_t *pnLen);

	/*!
		@~english	@brief	Save the Port XML data a file.
		@~english	@details	Save the Port XML data to a file.
		@~english	@param[in] pIStPortHandle	IStPort interface handle.
		@~english	@param[in] szFileName	File name.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	このポートで使用されているXMLファイルを保存します。
		@~japanese	@details	このポートで使用されているXMLファイルを保存します。
		@~japanese	@param[in] pIStPortHandle	IStPort インターフェースハンドル
		@~japanese	@param[in] szFileName	ファイル名
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStPort_SaveXMLFileW_t)(const PStApiHandle_t pIStPortHandle, const wchar_t *szFileName);

	/*!
		@~english	@brief	Save the Port XML data a file.
		@~english	@details	Save the Port XML data to a file.
		@~english	@param[in] pIStPortHandle	IStPort interface handle.
		@~english	@param[in] szFileName	File name.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	このポートで使用されているXMLファイルを保存します。
		@~japanese	@details	このポートで使用されているXMLファイルを保存します。
		@~japanese	@param[in] pIStPortHandle	IStPort インターフェースハンドル
		@~japanese	@param[in] szFileName	ファイル名
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStPort_SaveXMLFileA_t)(const PStApiHandle_t pIStPortHandle, const char *szFileName);
	
	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStPort_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IStPort.
		@~english	@details	This structure holds the address of the C language wrapper function of IStPort.
		@~japanese	@brief	この構造体はIStPortのC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体はIStPortのC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_IStPort_Functions_t
	{
		/*!
			@copydoc PStApiTL_IStPort_GetPortURLCount_t()
		*/
		PStApiTL_IStPort_GetPortURLCount_t	GetPortURLCount;

		/*!
			@copydoc PStApiTL_IStPort_GetPortURLIndex_t()
		*/
		PStApiTL_IStPort_GetPortURLIndex_t	GetPortURLIndex;

		/*!
			@copydoc PStApiTL_IStPort_SetPortURLIndex_t()
		*/
		PStApiTL_IStPort_SetPortURLIndex_t	SetPortURLIndex;

		/*!
			@copydoc PStApiTL_IStPort_GetIStPortURLInfo_t()
		*/
		PStApiTL_IStPort_GetIStPortURLInfo_t	GetIStPortURLInfo;

		/*!
			@copydoc PStApiTL_IStPort_GetINodeMap_t()
		*/
		PStApiTL_IStPort_GetINodeMap_t	GetINodeMap;

		/*!
			@copydoc PStApiTL_IStPort_GetIStPortInfo_t()
		*/
		PStApiTL_IStPort_GetIStPortInfo_t	GetIStPortInfo;

		/*!
			@copydoc PStApiTL_IStPort_GetXMLFileNameW_t()
		*/
		PStApiTL_IStPort_GetXMLFileNameW_t	GetXMLFileNameW;

		/*!
			@copydoc PStApiTL_IStPort_GetXMLFileNameA_t()
		*/
		PStApiTL_IStPort_GetXMLFileNameA_t	GetXMLFileNameA;

		/*!
			@copydoc PStApiTL_IStPort_SaveXMLFileW_t()
		*/
		PStApiTL_IStPort_SaveXMLFileW_t	SaveXMLFileW;

		/*!
			@copydoc PStApiTL_IStPort_SaveXMLFileA_t()
		*/
		PStApiTL_IStPort_SaveXMLFileA_t	SaveXMLFileA;
	}StApi_IStPort_Functions_t, *PStApi_IStPort_Functions_t;


	/*************************************************************************/
	/* StApi::IStPortURLInfo */
	/*************************************************************************/
	/*!
		@~english	@brief	GenTL::GCGetPortURLInfo() is used to acquire data of GenTL::URL_INFO_URL.
		@~english	@details	GenTL::GCGetPortURLInfo() is used to acquire data of GenTL::URL_INFO_URL.
		@~english	@param[in] pIStPortURLInfoHandle	IStPortURLInfo interface handle.
		@~english	@param[in,out] szText	URL_INFO_URL data.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::GCGetPortURLInfo() を使用して GenTL::URL_INFO_URL の情報を取得します。
		@~japanese	@details	GenTL::GCGetPortURLInfo() を使用して GenTL::URL_INFO_URL の情報を取得します。
		@~japanese	@param[in] pIStPortURLInfoHandle	IStPortURLInfo インターフェースハンドル
		@~japanese	@param[in,out] szText	URL_INFO_URL データ
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStPortURLInfo_GetURLA_t)(const PStApiHandle_t pIStPortURLInfoHandle, char *szText, size_t *pnLen);

	/*!
		@~english	@brief	GenTL::GCGetPortURLInfo() is used to acquire data of GenTL::URL_INFO_SCHEMA_VER_MAJOR.
		@~english	@details	GenTL::GCGetPortURLInfo() is used to acquire data of GenTL::URL_INFO_SCHEMA_VER_MAJOR.
		@~english	@param[in] pIStPortURLInfoHandle	IStPortURLInfo interface handle.
		@~english	@param[out] pnValue	URL_INFO_SCHEMA_VER_MAJOR data.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::GCGetPortURLInfo() を使用して GenTL::URL_INFO_SCHEMA_VER_MAJOR の情報を取得します。
		@~japanese	@details	GenTL::GCGetPortURLInfo() を使用して GenTL::URL_INFO_SCHEMA_VER_MAJOR の情報を取得します。
		@~japanese	@param[in] pIStPortURLInfoHandle	IStPortURLInfo インターフェースハンドル
		@~japanese	@param[out] pnValue	URL_INFO_SCHEMA_VER_MAJOR データ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStPortURLInfo_GetSchemaVerMajor_t)(const PStApiHandle_t pIStPortURLInfoHandle, int32_t *pnValue);

	/*!
		@~english	@brief	GenTL::GCGetPortURLInfo() is used to acquire data of GenTL::URL_INFO_SCHEMA_VER_MINOR.
		@~english	@details	GenTL::GCGetPortURLInfo() is used to acquire data of GenTL::URL_INFO_SCHEMA_VER_MINOR.
		@~english	@param[in] pIStPortURLInfoHandle	IStPortURLInfo interface handle.
		@~english	@param[in] pIStPortURLInfoHandle	IStPortURLInfo interface handle.
		@~english	@param[out] pnValue	URL_INFO_SCHEMA_VER_MINOR data.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::GCGetPortURLInfo() を使用して GenTL::URL_INFO_SCHEMA_VER_MINOR の情報を取得します。
		@~japanese	@details	GenTL::GCGetPortURLInfo() を使用して GenTL::URL_INFO_SCHEMA_VER_MINOR の情報を取得します。
		@~japanese	@param[in] pIStPortURLInfoHandle	IStPortURLInfo インターフェースハンドル
		@~japanese	@param[out] pnValue	URL_INFO_SCHEMA_VER_MINOR データ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStPortURLInfo_GetSchemaVerMinor_t)(const PStApiHandle_t pIStPortURLInfoHandle, int32_t *pnValue);

	/*!
		@~english	@brief	GenTL::GCGetPortURLInfo() is used to acquire data of GenTL::URL_INFO_FILE_VER_MAJOR.
		@~english	@details	GenTL::GCGetPortURLInfo() is used to acquire data of GenTL::URL_INFO_FILE_VER_MAJOR.
		@~english	@param[in] pIStPortURLInfoHandle	IStPortURLInfo interface handle.
		@~english	@param[out] pnValue	URL_INFO_FILE_VER_MAJOR data.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::GCGetPortURLInfo() を使用して GenTL::URL_INFO_FILE_VER_MAJOR の情報を取得します。
		@~japanese	@details	GenTL::GCGetPortURLInfo() を使用して GenTL::URL_INFO_FILE_VER_MAJOR の情報を取得します。
		@~japanese	@param[in] pIStPortURLInfoHandle	IStPortURLInfo インターフェースハンドル
		@~japanese	@param[out] pnValue	URL_INFO_FILE_VER_MAJOR データ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStPortURLInfo_GetFileVerMajor_t)(const PStApiHandle_t pIStPortURLInfoHandle, int32_t *pnValue);

	/*!
		@~english	@brief	GenTL::GCGetPortURLInfo() is used to acquire data of GenTL::URL_INFO_FILE_VER_MINOR.
		@~english	@details	GenTL::GCGetPortURLInfo() is used to acquire data of GenTL::URL_INFO_FILE_VER_MINOR.
		@~english	@param[in] pIStPortURLInfoHandle	IStPortURLInfo interface handle.
		@~english	@param[out] pnValue	URL_INFO_FILE_VER_MINOR data.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::GCGetPortURLInfo() を使用して GenTL::URL_INFO_FILE_VER_MINOR の情報を取得します。
		@~japanese	@details	GenTL::GCGetPortURLInfo() を使用して GenTL::URL_INFO_FILE_VER_MINOR の情報を取得します。
		@~japanese	@param[in] pIStPortURLInfoHandle	IStPortURLInfo インターフェースハンドル
		@~japanese	@param[out] pnValue	URL_INFO_FILE_VER_MINOR データ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStPortURLInfo_GetFileVerMinor_t)(const PStApiHandle_t pIStPortURLInfoHandle, int32_t *pnValue);

	/*!
		@~english	@brief	GenTL::GCGetPortURLInfo() is used to acquire data of GenTL::URL_INFO_FILE_VER_SUBMINOR.
		@~english	@details	GenTL::GCGetPortURLInfo() is used to acquire data of GenTL::URL_INFO_FILE_VER_SUBMINOR.
		@~english	@param[in] pIStPortURLInfoHandle	IStPortURLInfo interface handle.
		@~english	@param[out] pnValue	URL_INFO_FILE_VER_SUBMINOR data.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::GCGetPortURLInfo() を使用して GenTL::URL_INFO_FILE_VER_SUBMINOR の情報を取得します。
		@~japanese	@details	GenTL::GCGetPortURLInfo() を使用して GenTL::URL_INFO_FILE_VER_SUBMINOR の情報を取得します。
		@~japanese	@param[in] pIStPortURLInfoHandle	IStPortURLInfo インターフェースハンドル
		@~japanese	@param[out] pnValue	URL_INFO_FILE_VER_SUBMINOR データ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStPortURLInfo_GetFileVerSubMinor_t)(const PStApiHandle_t pIStPortURLInfoHandle, int32_t *pnValue);

	/*!
		@~english	@brief	GenTL::GCGetPortURLInfo() is used to acquire data of GenTL::URL_INFO_FILE_SHA1_HASH.
		@~english	@details	GenTL::GCGetPortURLInfo() is used to acquire data of GenTL::URL_INFO_FILE_SHA1_HASH.
		@~english	@param[in] pIStPortURLInfoHandle	IStPortURLInfo interface handle.
		@~english	@param[out]	pBuffer	Set a pointer of buffer to receive data.
		@~english	@param[in,out]	pnSize	Set the size of buffer and get the size of data.
		@~english	@return	URL_INFO_FILE_SHA1_HASH data.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::GCGetPortURLInfo() を使用して GenTL::URL_INFO_FILE_SHA1_HASH の情報を取得します。
		@~japanese	@details	GenTL::GCGetPortURLInfo() を使用して GenTL::URL_INFO_FILE_SHA1_HASH の情報を取得します。
		@~japanese	@param[in] pIStPortURLInfoHandle	IStPortURLInfo インターフェースハンドル
		@~japanese	@param[out]	pBuffer	データを受け取るバッファを指定します。
		@~japanese	@return	EStApiCError_t エラーコード
		@~japanese	@return	URL_INFO_FILE_SHA1_HASH データ
		@~japanese	@exception	GenTL::GCGetPortURLInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
	*/
	STAPI_PCALL(PStApiTL_IStPortURLInfo_GetSha1HashBuffer_t)(const PStApiHandle_t pIStPortURLInfoHandle, void *pBuffer, size_t *pnSize);

	/*!
		@~english	@brief	GenTL::GCGetPortURLInfo() is used to acquire data of GenTL::URL_INFO_FILE_REGISTER_ADDRESS.
		@~english	@details	GenTL::GCGetPortURLInfo() is used to acquire data of GenTL::URL_INFO_FILE_REGISTER_ADDRESS.
		@~english	@param[in] pIStPortURLInfoHandle	IStPortURLInfo interface handle.
		@~english	@param[out] pnValue	URL_INFO_FILE_REGISTER_ADDRESS data.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::GCGetPortURLInfo() を使用して GenTL::URL_INFO_FILE_REGISTER_ADDRESS の情報を取得します。
		@~japanese	@details	GenTL::GCGetPortURLInfo() を使用して GenTL::URL_INFO_FILE_REGISTER_ADDRESS の情報を取得します。
		@~japanese	@param[in] pIStPortURLInfoHandle	IStPortURLInfo インターフェースハンドル
		@~japanese	@param[out] pnValue	URL_INFO_FILE_REGISTER_ADDRESS データ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStPortURLInfo_GetFileRegisterAddress_t)(const PStApiHandle_t pIStPortURLInfoHandle, uint64_t *pnValue);

	/*!
		@~english	@brief	GenTL::GCGetPortURLInfo() is used to acquire data of GenTL::URL_INFO_FILE_SIZE.
		@~english	@details	GenTL::GCGetPortURLInfo() is used to acquire data of GenTL::URL_INFO_FILE_SIZE.
		@~english	@param[in] pIStPortURLInfoHandle	IStPortURLInfo interface handle.
		@~english	@param[out] pnValue	URL_INFO_FILE_SIZE data.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::GCGetPortURLInfo() を使用して GenTL::URL_INFO_FILE_SIZE の情報を取得します。
		@~japanese	@details	GenTL::GCGetPortURLInfo() を使用して GenTL::URL_INFO_FILE_SIZE の情報を取得します。
		@~japanese	@param[in] pIStPortURLInfoHandle	IStPortURLInfo インターフェースハンドル
		@~japanese	@param[out] pnValue	URL_INFO_FILE_SIZE データ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStPortURLInfo_GetFileSize_t)(const PStApiHandle_t pIStPortURLInfoHandle, uint64_t *pnValue);

	/*!
		@~english	@brief	GenTL::GCGetPortURLInfo() is used to acquire data of GenTL::URL_INFO_SCHEME.
		@~english	@details	GenTL::GCGetPortURLInfo() is used to acquire data of GenTL::URL_INFO_SCHEME.
		@~english	@param[in] pIStPortURLInfoHandle	IStPortURLInfo interface handle.
		@~english	@param[out] pnValue	URL_INFO_SCHEME data.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::GCGetPortURLInfo() を使用して GenTL::URL_INFO_SCHEME の情報を取得します。
		@~japanese	@details	GenTL::GCGetPortURLInfo() を使用して GenTL::URL_INFO_SCHEME の情報を取得します。
		@~japanese	@param[in] pIStPortURLInfoHandle	IStPortURLInfo インターフェースハンドル
		@~japanese	@param[out] pnValue	URL_INFO_SCHEME データ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStPortURLInfo_GetScheme_t)(const PStApiHandle_t pIStPortURLInfoHandle, URL_SCHEME_ID *pnValue);

	/*!
		@~english	@brief	GenTL::GCGetPortURLInfo() is used to acquire data of GenTL::URL_INFO_FILENAME.
		@~english	@details	GenTL::GCGetPortURLInfo() is used to acquire data of GenTL::URL_INFO_FILENAME.
		@~english	@param[in] pIStPortURLInfoHandle	IStPortURLInfo interface handle.
		@~english	@param[in,out] szText	URL_INFO_FILENAME data.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::GCGetPortURLInfo() を使用して GenTL::URL_INFO_FILENAME の情報を取得します。
		@~japanese	@details	GenTL::GCGetPortURLInfo() を使用して GenTL::URL_INFO_FILENAME の情報を取得します。
		@~japanese	@param[in] pIStPortURLInfoHandle	IStPortURLInfo インターフェースハンドル
		@~japanese	@param[in,out] szText	URL_INFO_FILENAME データ
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStPortURLInfo_GetFileNameA_t)(const PStApiHandle_t pIStPortURLInfoHandle, char *szText, size_t *pnLen);

	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStPortURLInfo_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IStPortURLInfo.
		@~english	@details	This structure holds the address of the C language wrapper function of IStPortURLInfo.
		@~japanese	@brief	この構造体は IStPortURLInfo のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IStPortURLInfo のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_IStPortURLInfo_Functions_t
	{
		/*!
			@copydoc PStApiTL_IStPortURLInfo_GetURLA_t()
		*/
		PStApiTL_IStPortURLInfo_GetURLA_t	GetURLA;

		/*!
			@copydoc PStApiTL_IStPortURLInfo_GetSchemaVerMajor_t()
		*/
		PStApiTL_IStPortURLInfo_GetSchemaVerMajor_t	GetSchemaVerMajor;

		/*!
			@copydoc PStApiTL_IStPortURLInfo_GetSchemaVerMinor_t()
		*/
		PStApiTL_IStPortURLInfo_GetSchemaVerMinor_t	GetSchemaVerMinor;

		/*!
			@copydoc PStApiTL_IStPortURLInfo_GetFileVerMajor_t()
		*/
		PStApiTL_IStPortURLInfo_GetFileVerMajor_t	GetFileVerMajor;

		/*!
			@copydoc PStApiTL_IStPortURLInfo_GetFileVerMinor_t()
		*/
		PStApiTL_IStPortURLInfo_GetFileVerMinor_t	GetFileVerMinor;

		/*!
			@copydoc PStApiTL_IStPortURLInfo_GetFileVerSubMinor_t()
		*/
		PStApiTL_IStPortURLInfo_GetFileVerSubMinor_t	GetFileVerSubMinor;

		/*!
			@copydoc PStApiTL_IStPortURLInfo_GetSha1HashBuffer_t()
		*/
		PStApiTL_IStPortURLInfo_GetSha1HashBuffer_t	GetSha1HashBuffer;

		/*!
			@copydoc PStApiTL_IStPortURLInfo_GetFileRegisterAddress_t()
		*/
		PStApiTL_IStPortURLInfo_GetFileRegisterAddress_t	GetFileRegisterAddress;

		/*!
			@copydoc PStApiTL_IStPortURLInfo_GetFileSize_t()
		*/
		PStApiTL_IStPortURLInfo_GetFileSize_t	GetFileSize;

		/*!
			@copydoc PStApiTL_IStPortURLInfo_GetScheme_t()
		*/
		PStApiTL_IStPortURLInfo_GetScheme_t	GetScheme;

		/*!
			@copydoc PStApiTL_IStPortURLInfo_GetFileNameA_t()
		*/
		PStApiTL_IStPortURLInfo_GetFileNameA_t	GetFileNameA;

	}StApi_IStPortURLInfo_Functions_t, *PStApi_IStPortURLInfo_Functions_t;



	/*************************************************************************/
	/* StApi::IStPortInfo */
	/*************************************************************************/
	/*!
		@~english	@brief	Use GenTL::GCGetPortInfo() to acquire data of GenTL::PORT_INFO_ID.
		@~english	@details	Use GenTL::GCGetPortInfo() to acquire data of GenTL::PORT_INFO_ID.
		@~english	@param[in] pIStPortInfoHandle	IStPortInfo interface handle.
		@~english	@param[in,out] szText	PORT_INFO_ID data.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::GCGetPortInfo() を使用して GenTL::PORT_INFO_ID の情報を取得します。
		@~japanese	@details	GenTL::GCGetPortInfo() を使用して GenTL::PORT_INFO_ID の情報を取得します。
		@~japanese	@param[in] pIStPortInfoHandle	IStPortInfo インターフェースハンドル
		@~japanese	@param[in,out] szText	PORT_INFO_ID データ
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStPortInfo_GetIDA_t)(const PStApiHandle_t pIStPortInfoHandle, char *szText, size_t *pnLen);

	/*!
		@~english	@brief	Use GenTL::GCGetPortInfo() to acquire data of GenTL::PORT_INFO_VENDOR.
		@~english	@details	Use GenTL::GCGetPortInfo() to acquire data of GenTL::PORT_INFO_VENDOR.
		@~english	@param[in] pIStPortInfoHandle	IStPortInfo interface handle.
		@~english	@param[in,out] pStringBufferHandle	PORT_INFO_VENDOR data.
		@~english	@param[in,out] szText	PORT_INFO_VENDOR data.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::GCGetPortInfo() を使用して GenTL::PORT_INFO_VENDOR の情報を取得します。
		@~japanese	@details	GenTL::GCGetPortInfo() を使用して GenTL::PORT_INFO_VENDOR の情報を取得します。
		@~japanese	@param[in] pIStPortInfoHandle	IStPortInfo インターフェースハンドル
		@~japanese	@param[in,out] szText	PORT_INFO_VENDOR データ
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStPortInfo_GetVendorA_t)(const PStApiHandle_t pIStPortInfoHandle, char *szText, size_t *pnLen);

	/*!
		@~english	@brief	Use GenTL::GCGetPortInfo() to acquire data of GenTL::PORT_INFO_MODEL.
		@~english	@details	Use GenTL::GCGetPortInfo() to acquire data of GenTL::PORT_INFO_MODEL.
		@~english	@param[in] pIStPortInfoHandle	IStPortInfo interface handle.
		@~english	@param[in,out] szText	PORT_INFO_MODEL data.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::GCGetPortInfo() を使用して GenTL::PORT_INFO_MODEL の情報を取得します。
		@~japanese	@details	GenTL::GCGetPortInfo() を使用して GenTL::PORT_INFO_MODEL の情報を取得します。
		@~japanese	@param[in] pIStPortInfoHandle	IStPortInfo インターフェースハンドル
		@~japanese	@param[in,out] szText	PORT_INFO_MODEL データ
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStPortInfo_GetModelA_t)(const PStApiHandle_t pIStPortInfoHandle, char *szText, size_t *pnLen);

	/*!
		@~english	@brief	Use GenTL::GCGetPortInfo() to acquire data of GenTL::PORT_INFO_TLTYPE.
		@~english	@details	Use GenTL::GCGetPortInfo() to acquire data of GenTL::PORT_INFO_TLTYPE.
		@~english	@param[in] pIStPortInfoHandle	IStPortInfo interface handle.
		@~english	@param[in,out] szText	PORT_INFO_TLTYPE data.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::GCGetPortInfo() を使用して GenTL::PORT_INFO_TLTYPE の情報を取得します。
		@~japanese	@details	GenTL::GCGetPortInfo() を使用して GenTL::PORT_INFO_TLTYPE の情報を取得します。
		@~japanese	@param[in] pIStPortInfoHandle	IStPortInfo インターフェースハンドル
		@~japanese	@param[in,out] szText	PORT_INFO_TLTYPE データ
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStPortInfo_GetTLTypeA_t)(const PStApiHandle_t pIStPortInfoHandle, char *szText, size_t *pnLen);

	/*!
		@~english	@brief	Use GenTL::GCGetPortInfo() to acquire data of GenTL::PORT_INFO_MODULE.
		@~english	@details	Use GenTL::GCGetPortInfo() to acquire data of GenTL::PORT_INFO_MODULE.
		@~english	@param[in] pIStPortInfoHandle	IStPortInfo interface handle.
		@~english	@param[in,out] szText	PORT_INFO_MODULE data.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::GCGetPortInfo() を使用して GenTL::PORT_INFO_MODULE の情報を取得します。
		@~japanese	@details	GenTL::GCGetPortInfo() を使用して GenTL::PORT_INFO_MODULE の情報を取得します。
		@~japanese	@param[in] pIStPortInfoHandle	IStPortInfo インターフェースハンドル
		@~japanese	@param[in,out] szText	PORT_INFO_MODULE データ
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStPortInfo_GetModuleA_t)(const PStApiHandle_t pIStPortInfoHandle, char *szText, size_t *pnLen);

	/*!
		@~english	@brief	Use GenTL::GCGetPortInfo() to acquire data of GenTL::PORT_INFO_LITTLE_ENDIAN.
		@~english	@details	Use GenTL::GCGetPortInfo() to acquire data of GenTL::PORT_INFO_LITTLE_ENDIAN.
		@~english	@param[in] pIStPortInfoHandle	IStPortInfo interface handle.
		@~english	@return	PORT_INFO_LITTLE_ENDIAN data.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::GCGetPortInfo() を使用して GenTL::PORT_INFO_LITTLE_ENDIAN の情報を取得します。
		@~japanese	@details	GenTL::GCGetPortInfo() を使用して GenTL::PORT_INFO_LITTLE_ENDIAN の情報を取得します。
		@~japanese	@param[in] pIStPortInfoHandle	IStPortInfo インターフェースハンドル
		@~japanese	@return	PORT_INFO_LITTLE_ENDIAN データ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStPortInfo_IsLittleEndian_t)(const PStApiHandle_t pIStPortInfoHandle, bool8_t *pbValue);

	/*!
		@~english	@brief	Use GenTL::GCGetPortInfo() to acquire data of GenTL::PORT_INFO_BIG_ENDIAN.
		@~english	@details	Use GenTL::GCGetPortInfo() to acquire data of GenTL::PORT_INFO_BIG_ENDIAN.
		@~english	@param[in] pIStPortInfoHandle	IStPortInfo interface handle.
		@~english	@param[out] pbValue	PORT_INFO_BIG_ENDIAN data.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::GCGetPortInfo() を使用して GenTL::PORT_INFO_BIG_ENDIAN の情報を取得します。
		@~japanese	@details	GenTL::GCGetPortInfo() を使用して GenTL::PORT_INFO_BIG_ENDIAN の情報を取得します。
		@~japanese	@param[in] pIStPortInfoHandle	IStPortInfo インターフェースハンドル
		@~japanese	@param[out] pbValue	PORT_INFO_BIG_ENDIAN データ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStPortInfo_IsBigEndian_t)(const PStApiHandle_t pIStPortInfoHandle, bool8_t *pbValue);

	/*!
		@~english	@brief	Use GenTL::GCGetPortInfo() to acquire data of GenTL::PORT_INFO_ACCESS_READ.
		@~english	@details	Use GenTL::GCGetPortInfo() to acquire data of GenTL::PORT_INFO_ACCESS_READ.
		@~english	@param[in] pIStPortInfoHandle	IStPortInfo interface handle.
		@~english	@param[out] pbValue	PORT_INFO_ACCESS_READ data.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::GCGetPortInfo() を使用して GenTL::PORT_INFO_ACCESS_READ の情報を取得します。
		@~japanese	@details	GenTL::GCGetPortInfo() を使用して GenTL::PORT_INFO_ACCESS_READ の情報を取得します。
		@~japanese	@param[in] pIStPortInfoHandle	IStPortInfo インターフェースハンドル
		@~japanese	@param[out] pbValue	PORT_INFO_ACCESS_READ データ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStPortInfo_IsAccessRead_t)(const PStApiHandle_t pIStPortInfoHandle, bool8_t *pbValue);

	/*!
		@~english	@brief	Use GenTL::GCGetPortInfo() to acquire data of GenTL::PORT_INFO_ACCESS_WRITE.
		@~english	@details	Use GenTL::GCGetPortInfo() to acquire data of GenTL::PORT_INFO_ACCESS_WRITE.
		@~english	@param[in] pIStPortInfoHandle	IStPortInfo interface handle.
		@~english	@param[out] pbValue	PORT_INFO_ACCESS_WRITE data.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::GCGetPortInfo() を使用して GenTL::PORT_INFO_ACCESS_WRITE の情報を取得します。
		@~japanese	@details	GenTL::GCGetPortInfo() を使用して GenTL::PORT_INFO_ACCESS_WRITE の情報を取得します。
		@~japanese	@param[in] pIStPortInfoHandle	IStPortInfo インターフェースハンドル
		@~japanese	@param[out] pbValue	PORT_INFO_ACCESS_WRITE データ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStPortInfo_IsAccessWrite_t)(const PStApiHandle_t pIStPortInfoHandle, bool8_t *pbValue);

	/*!
		@~english	@brief	Use GenTL::GCGetPortInfo() to acquire data of GenTL::PORT_INFO_ACCESS_NA.
		@~english	@details	Use GenTL::GCGetPortInfo() to acquire data of GenTL::PORT_INFO_ACCESS_NA.
		@~english	@param[in] pIStPortInfoHandle	IStPortInfo interface handle.
		@~english	@param[out] pbValue	PORT_INFO_ACCESS_NA data.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::GCGetPortInfo() を使用して GenTL::PORT_INFO_ACCESS_NA の情報を取得します。
		@~japanese	@details	GenTL::GCGetPortInfo() を使用して GenTL::PORT_INFO_ACCESS_NA の情報を取得します。
		@~japanese	@param[in] pIStPortInfoHandle	IStPortInfo インターフェースハンドル
		@~japanese	@param[out] pbValue	PORT_INFO_ACCESS_NA データ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStPortInfo_IsAccessNA_t)(const PStApiHandle_t pIStPortInfoHandle, bool8_t *pbValue);

	/*!
		@~english	@brief	Use GenTL::GCGetPortInfo() to acquire data of GenTL::PORT_INFO_ACCESS_NI.
		@~english	@details	Use GenTL::GCGetPortInfo() to acquire data of GenTL::PORT_INFO_ACCESS_NI.
		@~english	@param[in] pIStPortInfoHandle	IStPortInfo interface handle.
		@~english	@param[out] pbValue	PORT_INFO_ACCESS_NI data.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::GCGetPortInfo() を使用して GenTL::PORT_INFO_ACCESS_NI の情報を取得します。
		@~japanese	@details	GenTL::GCGetPortInfo() を使用して GenTL::PORT_INFO_ACCESS_NI の情報を取得します。
		@~japanese	@param[in] pIStPortInfoHandle	IStPortInfo インターフェースハンドル
		@~japanese	@param[out] pbValue	PORT_INFO_ACCESS_NI データ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStPortInfo_IsAccessNI_t)(const PStApiHandle_t pIStPortInfoHandle, bool8_t *pbValue);

	/*!
		@~english	@brief	Use GenTL::GCGetPortInfo() to acquire data of GenTL::PORT_INFO_VERSION.
		@~english	@details	Use GenTL::GCGetPortInfo() to acquire data of GenTL::PORT_INFO_VERSION.
		@~english	@param[in] pIStPortInfoHandle	IStPortInfo interface handle.
		@~english	@param[in,out] szText	PORT_INFO_VERSION data.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::GCGetPortInfo() を使用して GenTL::PORT_INFO_VERSION の情報を取得します。
		@~japanese	@details	GenTL::GCGetPortInfo() を使用して GenTL::PORT_INFO_VERSION の情報を取得します。
		@~japanese	@param[in] pIStPortInfoHandle	IStPortInfo インターフェースハンドル
		@~japanese	@param[in,out] szText	PORT_INFO_VERSION データ
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStPortInfo_GetVersionA_t)(const PStApiHandle_t pIStPortInfoHandle, char *szText, size_t *pnLen);

	/*!
		@~english	@brief	Use GenTL::GCGetPortInfo() to acquire data of GenTL::PORT_INFO_PORTNAME.
		@~english	@details	Use GenTL::GCGetPortInfo() to acquire data of GenTL::PORT_INFO_PORTNAME.
		@~english	@param[in] pIStPortInfoHandle	IStPortInfo interface handle.
		@~english	@param[in,out] szText	PORT_INFO_PORTNAME data.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::GCGetPortInfo() を使用して GenTL::PORT_INFO_PORTNAME の情報を取得します。
		@~japanese	@details	GenTL::GCGetPortInfo() を使用して GenTL::PORT_INFO_PORTNAME の情報を取得します。
		@~japanese	@param[in] pIStPortInfoHandle	IStPortInfo インターフェースハンドル
		@~japanese	@param[in,out] szText	PORT_INFO_PORTNAME データ
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStPortInfo_GetPortNameA_t)(const PStApiHandle_t pIStPortInfoHandle, char *szText, size_t *pnLen);

	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStPortInfo_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IStPortInfo.
		@~english	@details	This structure holds the address of the C language wrapper function of IStPortInfo.
		@~japanese	@brief	この構造体は IStPortInfo のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IStPortInfo のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_IStPortInfo_Functions_t
	{
		/*!
			@copydoc PStApiTL_IStPortInfo_GetIDA_t()
		*/
		PStApiTL_IStPortInfo_GetIDA_t	GetIDA;

		/*!
			@copydoc PStApiTL_IStPortInfo_GetVendorA_t()
		*/
		PStApiTL_IStPortInfo_GetVendorA_t	GetVendorA;

		/*!
			@copydoc PStApiTL_IStPortInfo_GetModelA_t()
		*/
		PStApiTL_IStPortInfo_GetModelA_t	GetModelA;

		/*!
			@copydoc PStApiTL_IStPortInfo_GetTLTypeA_t()
		*/
		PStApiTL_IStPortInfo_GetTLTypeA_t	GetTLTypeA;

		/*!
			@copydoc PStApiTL_IStPortInfo_GetModuleA_t()
		*/
		PStApiTL_IStPortInfo_GetModuleA_t	GetModuleA;

		/*!
			@copydoc PStApiTL_IStPortInfo_IsLittleEndian_t()
		*/
		PStApiTL_IStPortInfo_IsLittleEndian_t	IsLittleEndian;

		/*!
			@copydoc PStApiTL_IStPortInfo_IsBigEndian_t()
		*/
		PStApiTL_IStPortInfo_IsBigEndian_t	IsBigEndian;

		/*!
			@copydoc PStApiTL_IStPortInfo_IsAccessRead_t()
		*/
		PStApiTL_IStPortInfo_IsAccessRead_t	IsAccessRead;

		/*!
			@copydoc PStApiTL_IStPortInfo_IsAccessWrite_t()
		*/
		PStApiTL_IStPortInfo_IsAccessWrite_t	IsAccessWrite;

		/*!
			@copydoc PStApiTL_IStPortInfo_IsAccessNA_t()
		*/
		PStApiTL_IStPortInfo_IsAccessNA_t	IsAccessNA;

		/*!
			@copydoc PStApiTL_IStPortInfo_IsAccessNI_t()
		*/
		PStApiTL_IStPortInfo_IsAccessNI_t	IsAccessNI;

		/*!
			@copydoc PStApiTL_IStPortInfo_GetVersionA_t()
		*/
		PStApiTL_IStPortInfo_GetVersionA_t	GetVersionA;

		/*!
			@copydoc PStApiTL_IStPortInfo_GetPortNameA_t()
		*/
		PStApiTL_IStPortInfo_GetPortNameA_t	GetPortNameA;
	}StApi_IStPortInfo_Functions_t, *PStApi_IStPortInfo_Functions_t;

	/*************************************************************************/
	/* StApi::IStSystemInfo */
	/*************************************************************************/
	/*!
		@~english	@brief	GenTL::TLInfo() is used to get the information of GenTL::TL_INFO_ID.
		@~english	@details	GenTL::TLInfo() is used to get the information of GenTL::TL_INFO_ID.
		@~english	@param[in] pIStSystemInfoHandle	IStSystemInfo handle.
		@~english	@param[in,out] szText	TL_INFO_ID
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::TLInfo() を使用して GenTL::TL_INFO_ID の情報を取得します。
		@~japanese	@details	GenTL::TLInfo() を使用して GenTL::TL_INFO_ID の情報を取得します。
		@~japanese	@param[in] pIStSystemInfoHandle	IStSystemInfo インターフェースハンドル
		@~japanese	@param[in,out] szText	TL_INFO_ID
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStSystemInfo_GetIDA_t)(const PStApiHandle_t pIStSystemInfoHandle, char *szText, size_t *pnLen);

	/*!
		@~english	@brief	GenTL::TLInfo() is used to get the information of GenTL::TL_INFO_VENDOR.
		@~english	@details	GenTL::TLInfo() is used to get the information of GenTL::TL_INFO_VENDOR.
		@~english	@param[in] pIStSystemInfoHandle	IStSystemInfo handle.
		@~english	@param[in,out] szText	TL_INFO_VENDOR
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::TLInfo() を使用して GenTL::TL_INFO_VENDOR の情報を取得します。
		@~japanese	@details	GenTL::TLInfo() を使用して GenTL::TL_INFO_VENDOR の情報を取得します。
		@~japanese	@param[in] pIStSystemInfoHandle	IStSystemInfo インターフェースハンドル
		@~japanese	@param[in,out] szText	TL_INFO_VENDOR
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStSystemInfo_GetVendorA_t)(const PStApiHandle_t pIStSystemInfoHandle, char *szText, size_t *pnLen);

	/*!
		@~english	@brief	GenTL::TLInfo() is used to get the information of GenTL::TL_INFO_MODEL.
		@~english	@details	GenTL::TLInfo() is used to get the information of GenTL::TL_INFO_MODEL.
		@~english	@param[in] pIStSystemInfoHandle	IStSystemInfo handle.
		@~english	@param[in,out] szText	TL_INFO_MODEL
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::TLInfo() を使用して GenTL::TL_INFO_MODEL の情報を取得します。
		@~japanese	@details	GenTL::TLInfo() を使用して GenTL::TL_INFO_MODEL の情報を取得します。
		@~japanese	@param[in] pIStSystemInfoHandle	IStSystemInfo インターフェースハンドル
		@~japanese	@param[in,out] szText	TL_INFO_MODEL
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStSystemInfo_GetModelA_t)(const PStApiHandle_t pIStSystemInfoHandle, char *szText, size_t *pnLen);

	/*!
		@~english	@brief	GenTL::TLInfo() is used to get the information of GenTL::TL_INFO_VERSION.
		@~english	@details	GenTL::TLInfo() is used to get the information of GenTL::TL_INFO_VERSION.
		@~english	@param[in] pIStSystemInfoHandle	IStSystemInfo handle.
		@~english	@param[in,out] szText	TL_INFO_VERSION
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::TLInfo() を使用して GenTL::TL_INFO_VERSION の情報を取得します。
		@~japanese	@details	GenTL::TLInfo() を使用して GenTL::TL_INFO_VERSION の情報を取得します。
		@~japanese	@param[in] pIStSystemInfoHandle	IStSystemInfo インターフェースハンドル
		@~japanese	@param[in,out] szText	TL_INFO_VERSION
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStSystemInfo_GetVersionA_t)(const PStApiHandle_t pIStSystemInfoHandle, char *szText, size_t *pnLen);

	/*!
		@~english	@brief	GenTL::TLInfo() is used to get the information of GenTL::TL_INFO_TLTYPE.
		@~english	@details	GenTL::TLInfo() is used to get the information of GenTL::TL_INFO_TLTYPE.
		@~english	@param[in] pIStSystemInfoHandle	IStSystemInfo handle.
		@~english	@param[in,out] szText	TL_INFO_TLTYPE
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::TLInfo() を使用して GenTL::TL_INFO_TLTYPE の情報を取得します。
		@~japanese	@details	GenTL::TLInfo() を使用して GenTL::TL_INFO_TLTYPE の情報を取得します。
		@~japanese	@param[in] pIStSystemInfoHandle	IStSystemInfo インターフェースハンドル
		@~japanese	@param[in,out] szText	TL_INFO_TLTYPE
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStSystemInfo_GetTLTypeA_t)(const PStApiHandle_t pIStSystemInfoHandle, char *szText, size_t *pnLen);

	/*!
		@~english	@brief	GenTL::TLInfo() is used to get the information of GenTL::TL_INFO_NAME.
		@~english	@details	GenTL::TLInfo() is used to get the information of GenTL::TL_INFO_NAME.
		@~english	@param[in] pIStSystemInfoHandle	IStSystemInfo handle.
		@~english	@param[in,out] szText	TL_INFO_NAME
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::TLInfo() を使用して GenTL::TL_INFO_NAME の情報を取得します。
		@~japanese	@details	GenTL::TLInfo() を使用して GenTL::TL_INFO_NAME の情報を取得します。
		@~japanese	@param[in] pIStSystemInfoHandle	IStSystemInfo インターフェースハンドル
		@~japanese	@param[in,out] szText	TL_INFO_NAME
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStSystemInfo_GetNameA_t)(const PStApiHandle_t pIStSystemInfoHandle, char *szText, size_t *pnLen);

	/*!
		@~english	@brief	GenTL::TLInfo() is used to get the information of GenTL::TL_INFO_PATHNAME.
		@~english	@details	GenTL::TLInfo() is used to get the information of GenTL::TL_INFO_PATHNAME.
		@~english	@param[in] pIStSystemInfoHandle	IStSystemInfo handle.
		@~english	@param[in,out] szText	TL_INFO_PATHNAME
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::TLInfo() を使用して GenTL::TL_INFO_PATHNAME の情報を取得します。
		@~japanese	@details	GenTL::TLInfo() を使用して GenTL::TL_INFO_PATHNAME の情報を取得します。
		@~japanese	@param[in] pIStSystemInfoHandle	IStSystemInfo インターフェースハンドル
		@~japanese	@param[in,out] szText	TL_INFO_PATHNAME
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStSystemInfo_GetPathNameA_t)(const PStApiHandle_t pIStSystemInfoHandle, char *szText, size_t *pnLen);

	/*!
		@~english	@brief	GenTL::TLInfo() is used to get the information of GenTL::TL_INFO_DISPLAYNAME.
		@~english	@details	GenTL::TLInfo() is used to get the information of GenTL::TL_INFO_DISPLAYNAME.
		@~english	@param[in] pIStSystemInfoHandle	IStSystemInfo handle.
		@~english	@param[in,out] szText	TL_INFO_DISPLAYNAME
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::TLInfo() を使用して GenTL::TL_INFO_DISPLAYNAME の情報を取得します。
		@~japanese	@details	GenTL::TLInfo() を使用して GenTL::TL_INFO_DISPLAYNAME の情報を取得します。
		@~japanese	@param[in] pIStSystemInfoHandle	IStSystemInfo インターフェースハンドル
		@~japanese	@param[in,out] szText	TL_INFO_DISPLAYNAME
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStSystemInfo_GetDisplayNameA_t)(const PStApiHandle_t pIStSystemInfoHandle, char *szText, size_t *pnLen);

	/*!
		@~english	@brief	GenTL::TLInfo() is used to get the information of GenTL::TL_INFO_CHAR_ENCODING.
		@~english	@details	GenTL::TLInfo() is used to get the information of GenTL::TL_INFO_CHAR_ENCODING.
		@~english	@param[in] pIStSystemInfoHandle	IStSystemInfo handle.
		@~english	@param[out] pnValue	TL_INFO_CHAR_ENCODING data.
		@~english	@return	EStApiCError_t error code.
		@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or GenTL::TLInfo() is failed.
		@~japanese	@brief	GenTL::TLInfo() を使用して GenTL::TL_INFO_CHAR_ENCODING の情報を取得します。
		@~japanese	@details	GenTL::TLInfo() を使用して GenTL::TL_INFO_CHAR_ENCODING の情報を取得します。
		@~japanese	@param[in] pIStSystemInfoHandle	IStSystemInfo インターフェースハンドル
		@~japanese	@param[out] pnValue	TL_INFO_CHAR_ENCODING データ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStSystemInfo_GetCharEncoding_t)(const PStApiHandle_t pIStSystemInfoHandle, TL_CHAR_ENCODING *pnValue);

	/*!
		@~english	@brief	GenTL::TLInfo() is used to get the information of GenTL::TL_INFO_GENTL_VER_MAJOR.
		@~english	@details	GenTL::TLInfo() is used to get the information of GenTL::TL_INFO_GENTL_VER_MAJOR.
		@~english	@param[in] pIStSystemInfoHandle	IStSystemInfo handle.
		@~english	@param[out] pnValue	TL_INFO_GENTL_VER_MAJOR data.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::TLInfo() を使用して GenTL::TL_INFO_GENTL_VER_MAJOR の情報を取得します。
		@~japanese	@details	GenTL::TLInfo() を使用して GenTL::TL_INFO_GENTL_VER_MAJOR の情報を取得します。
		@~japanese	@param[in] pIStSystemInfoHandle	IStSystemInfo インターフェースハンドル
		@~japanese	@param[out] pnValue	TL_INFO_GENTL_VER_MAJOR データ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStSystemInfo_GetGenTLVersionMajor_t)(const PStApiHandle_t pIStSystemInfoHandle, uint32_t *pnValue);

	/*!
		@~english	@brief	GenTL::TLInfo() is used to get the information of GenTL::TL_INFO_GENTL_VER_MINOR.
		@~english	@details	GenTL::TLInfo() is used to get the information of GenTL::TL_INFO_GENTL_VER_MINOR.
		@~english	@param[in] pIStSystemInfoHandle	IStSystemInfo handle.
		@~english	@param[out] pnValue	TL_INFO_GENTL_VER_MINOR data.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::TLInfo() を使用して GenTL::TL_INFO_GENTL_VER_MINOR の情報を取得します。
		@~japanese	@details	GenTL::TLInfo() を使用して GenTL::TL_INFO_GENTL_VER_MINOR の情報を取得します。
		@~japanese	@param[in] pIStSystemInfoHandle	IStSystemInfo インターフェースハンドル
		@~japanese	@param[out] pnValue	TL_INFO_GENTL_VER_MINOR データ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStSystemInfo_GetGenTLVersionMinor_t)(const PStApiHandle_t pIStSystemInfoHandle, uint32_t *pnValue);

	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStSystemInfo_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IStSystemInfo.
		@~english	@details	This structure holds the address of the C language wrapper function of IStSystemInfo.
		@~japanese	@brief	この構造体は IStSystemInfo のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IStSystemInfo のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_IStSystemInfo_Functions_t
	{
		/*!
			@copydoc PStApiTL_IStSystemInfo_GetIDA_t()
		*/
		PStApiTL_IStSystemInfo_GetIDA_t					GetIDA;

		/*!
			@copydoc PStApiTL_IStSystemInfo_GetVendorA_t()
		*/
		PStApiTL_IStSystemInfo_GetVendorA_t				GetVendorA;

		/*!
			@copydoc PStApiTL_IStSystemInfo_GetModelA_t()
		*/
		PStApiTL_IStSystemInfo_GetModelA_t				GetModelA;

		/*!
			@copydoc PStApiTL_IStSystemInfo_GetVersionA_t()
		*/
		PStApiTL_IStSystemInfo_GetVersionA_t			GetVersionA;

		/*!
			@copydoc PStApiTL_IStSystemInfo_GetTLTypeA_t()
		*/
		PStApiTL_IStSystemInfo_GetTLTypeA_t				GetTLTypeA;

		/*!
			@copydoc PStApiTL_IStSystemInfo_GetNameA_t()
		*/
		PStApiTL_IStSystemInfo_GetNameA_t				GetNameA;

		/*!
			@copydoc PStApiTL_IStSystemInfo_GetPathNameA_t()
		*/
		PStApiTL_IStSystemInfo_GetPathNameA_t			GetPathNameA;

		/*!
			@copydoc PStApiTL_IStSystemInfo_GetDisplayNameA_t()
		*/
		PStApiTL_IStSystemInfo_GetDisplayNameA_t		GetDisplayNameA;

		/*!
			@copydoc PStApiTL_IStSystemInfo_GetCharEncoding_t()
		*/
		PStApiTL_IStSystemInfo_GetCharEncoding_t		GetCharEncoding;

		/*!
			@copydoc PStApiTL_IStSystemInfo_GetGenTLVersionMajor_t()
		*/
		PStApiTL_IStSystemInfo_GetGenTLVersionMajor_t	GetGenTLVersionMajor;

		/*!
			@copydoc PStApiTL_IStSystemInfo_GetGenTLVersionMinor_t()
		*/
		PStApiTL_IStSystemInfo_GetGenTLVersionMinor_t	GetGenTLVersionMinor;
	}StApi_IStSystemInfo_Functions_t, *PStApi_IStSystemInfo_Functions_t;

	/*************************************************************************/
	/* StApi::IStSystem */
	/*************************************************************************/
	/*!
		@~english	@brief	Open the system module and interface module of GenTL then acquire IStSystem interface handle.
		@~english	@details	Open the system module and interface module of GenTL then acquire IStSystem interface handle. If the acquired  IStSystem interface handle is no longer needed, call IStSystem->Release(pSytemHandle) to release it.
		@~english	@param[in] eStSystemVendor	GenTL module to use. The StApi functionality may differ depending on the GenTL module.
		@~english	@param[in] eInterfaceMask	The interface to use. For example: StInterfaceType_USB3Vision is used for USB3Vision camera. This will reduce the scanning time because only the specified interface is scanned for devices. Use logical OR to specify more than one interface.
		@~english	@param[in,out]	pIStSystemHandle	ISystem interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTLのシステムモージュールをオープンし、 IStSystem インターフェースハンドルを取得します。
		@~japanese	@details	GenTLのシステムモージュールをオープンし、IStSystem インターフェースハンドルを取得します。 IStSystem インターフェースハンドル が不要になったら、 IStSystem->Release(pSytemHandle) を呼び出して解放してください。
		@~japanese	@param[in] eStSystemVendor	使用するGenTLモジュールを指定します。使用するGenTLモジュールにより、利用可能なStApi関数が変化することがあります。
		@~japanese	@param[in] eInterfaceMask	使用するインターフェースを指定します。USB3Visionカメラのみを使用する場合、 StInterfaceType_USB3Vision を指定することでGigEVisionカメラの検索のような不要な処理を軽減できます。複数のインターフェースを使用する場合は論理和を指定します。
		@~japanese	@param[in,out]	pIStSystemHandle	IStSystem インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStSystem_CreateIStSystem_t)(EStSystemVendor_t eSystemVendor, EStInterfaceType_t eTargetInterface, PStApiHandle_t pIStSystemHandle);

	/*!
		@~english	@brief	Release object.
		@~english	@details	Release object.
		@~english	@param[in] pIStSystemHandle	IStSystem interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	解放します。
		@~japanese	@details	解放します。
		@~japanese	@param[in] pIStSystemHandle	IStSystem interface handle.
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStSystem_Release_t)(PStApiHandle_t pIStSystemHandle);

	/*!
		@~english	@brief	Register a callback function.
		@~english	@details	Register a callback function.
		@~english	@param[in] pIStSystemHandle	IStSystem interface handle.
		@~english	@param[in]	pFunc	Callback function pointer.
		@~english	@param[in]	pContext	Argument for the callback function.
		@~english	@param[in,out] pIStRegisteredCallbackHandle	IStRegisteredCallback Interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	コールバック関数を登録します。
		@~japanese	@details	コールバック関数を登録します。
		@~japanese	@param[in] pIStSystemHandle	IStSystem インターフェースハンドル
		@~japanese	@param[in]	pFunc	コールバック関数として使用する関数
		@~japanese	@param[in]	pContext	コールバック関数に渡されるユーザー用パラメータ
		@~japanese	@param[in,out] pIStRegisteredCallbackHandle	IStRegisteredCallback インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStSystem_RegisterCallback_t)(const PStApiHandle_t pIStSystemHandle, fStCallbackFunc_t *pFunc, void* pContext, PStApiHandle_t pIStRegisteredCallbackHandle);
	
	/*!
		@~english	@brief	Start the event handling thread.
		@~english	@details	Start the event handling thread.
		@~english	@param[in] pIStSystemHandle	IStSystem interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	イベント取得用スレッドを起動します。
		@~japanese	@details	イベント取得用スレッドを起動します。
		@~japanese	@param[in] pIStSystemHandle	IStSystem インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStSystem_StartEventAcquisitionThread_t)(const PStApiHandle_t pIStSystemHandle);

	/*!
		@~english	@brief	Stop the event handling thread.
		@~english	@details	Stop the event handling thread.
		@~english	@param[in] pIStSystemHandle	IStSystem interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	イベント取得用スレッドを停止します。
		@~japanese	@details	イベント取得用スレッドを停止します。
		@~japanese	@param[in] pIStSystemHandle	IStSystem インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStSystem_StopEventAcquisitionThread_t)(const PStApiHandle_t pIStSystemHandle);

	/*!
		@~english	@brief	Acquire the value of EStSystemVendor_t when calling CreateIStSystem.
		@~english	@details	Acquire the value of EStSystemVendor_t when calling CreateIStSystem.
		@~english	@param[in] pIStSystemHandle	IStSystem handle.
		@~english	@param[out] peStSystemVendor	EStSystemVendor_t
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	CreateIStSystem() 呼び出し時に指定された EStSystemVendor_t の値を取得します。
		@~japanese	@details	CreateIStSystem() 呼び出し時に指定された EStSystemVendor_t の値を取得します。
		@~japanese	@param[in] pIStSystemHandle	IStSystem インターフェースハンドル
		@~japanese	@param[out] peStSystemVendor	EStSystemVendor_t
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStSystem_GetStSystemVendor_t)(const PStApiHandle_t pIStSystemHandle, EStSystemVendor_t *peStSystemVendor);

	/*!
		@~english	@brief	Acquire IStPort interface handle.
		@~english	@details	Acquire IStPort interface handle.
		@~english	@param[in] pIStSystemHandle	IStSystem handle.
		@~english	@param[out] pIStPortHandle	IStPort  handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStPort インターフェースハンドルを取得します。
		@~japanese	@details	IStPort インターフェースハンドルを取得します。
		@~japanese	@param[in] pIStSystemHandle	IStSystem インターフェースハンドル
		@~japanese	@param[out] pIStPortHandle	IStPort インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStSystem_GetIStPort_t)(const PStApiHandle_t pIStSystemHandle, PStApiHandle_t pIStPortHandle);

	/*!
		@~english	@brief	Acquire IStSystemInfo interface handle.
		@~english	@details	Acquire IStSystemInfo interface handle.
		@~english	@param[in] pIStSystemHandle	IStSystem handle.
		@~english	@param[out] pIStPortHandle	IStSystemInfo  handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStSystemInfo インターフェースハンドルを取得します。
		@~japanese	@details	IStSystemInfo インターフェースハンドルを取得します。
		@~japanese	@param[in] pIStSystemInfoHandle	IStSystem インターフェースハンドル
		@~japanese	@param[out] pIStPortHandle	IStSystemInfo インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStSystem_GetIStSystemInfo_t)(const PStApiHandle_t pIStSystemHandle, PStApiHandle_t pIStSystemInfoHandle);
		
	/*!
		@~english	@brief	Check the currently available interfaces on this system and update the interface list.
		@~english	@details	Check the currently available interfaces on this system and update the interface list.
		@~english	@param[in] pIStSystemHandle	IStSystem handle.
		@~english	@param[out] pbReval	True if the interface list was changed and false otherwise.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	このシステムで現在利用可能なインターフェースを検出し、インターフェースリストを更新します。
		@~japanese	@details	このシステムで現在利用可能なインターフェースを検出し、インターフェースリストを更新します。
		@~japanese	@param[in] pIStSystemInfoHandle	IStSystem インターフェースハンドル
		@~japanese	@param[out] pbReval インターフェースリストが更新された場合、 true が返されます。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStSystem_UpdateInterfaceList_t)(const PStApiHandle_t pIStSystemHandle, bool8_t *pbReval);

	/*!
		@~english	@brief	Get the number of available interfaces on this system.
		@~english	@details	Get the number of available interfaces on this system.
		@~english	@param[in] pIStSystemHandle	IStSystem handle.
		@~english	@param[out] pnCount	Number of the available interfaces on this system.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	このシステムで現在使用可能なインターフェースの数を取得します。
		@~japanese	@details	このシステムで現在使用可能なインターフェースの数を取得します。
		@~japanese	@param[in] pIStSystemInfoHandle	IStSystem インターフェースハンドル
		@~japanese	@param[out] pnCount 現在使用可能なインターフェースの数
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStSystem_GetInterfaceCount_t)(const PStApiHandle_t pIStSystemHandle, uint32_t *pnCount);

	/*!
		@~english	@brief	Get IStInterface interface handle.
		@~english	@details	Get IStInterface interface handle.
		@~english	@param[in] pIStSystemHandle	IStSystem handle.
		@~english	@param[in] nIndex	Index of the target interface from 0 to GetInterfaceCount()-1.
		@~english	@param[in,out] pIStInterfaceHandle	IStInterface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	指定された IStInterface インターフェースハンドルを取得します。
		@~japanese	@details	指定された IStInterface インターフェースハンドルを取得します。
		@~japanese	@param[in] pIStSystemInfoHandle	IStSystem インターフェースハンドル
		@~japanese	@param[out] nIndex 0から GetInterfaceCount() で取得した数未満の値でインターフェースを指定します。
		@~japanese	@param[in] pIStInterfaceHandle	IStInterface インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStSystem_GetIStInterface_t)(const PStApiHandle_t pIStSystemHandle, size_t nIndex, PStApiHandle_t pIStInterfaceHandle);

	/*!
		@~english	@brief	Acquire IStDevice interface handle for the first device found (Device index = 0). 
		@~english	@details	Acquire IStDevice interface handle for the first device found (Device index = 0).
		@~english	@attention	If IStDevice interface handle is no longer needed, call IStDevice->Release(pDeviceHandle).
		@~english	@param[in] pIStSystemHandle	IStSystem handle.
		@~english	@param[in] eDeviceAccessFlags	Device access flag.
		@~english	@param[in,out] pDeviceHandle	IStDevice handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	このシステムで最初に見つかったデバイスを作成し、 IStDevice インターフェースハンドルを取得します。
		@~japanese	@details	このシステムで最初に見つかったデバイスを作成し、 IStDevice インターフェースハンドルを取得します。
		@~japanese	@attention	取得された IStDevice インターフェースハンドルが不要になったら、 IStDevice->Release(pDeviceHandle) を呼び出して解放してください。
		@~japanese	@param[in] pIStSystemInfoHandle	IStSystem インターフェースハンドル
		@~japanese	@param[out] eDeviceAccessFlags デバイスアクセスフラグを指定します。
		@~japanese	@param[in,out] pDeviceHandle	IStDevice インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStSystem_CreateFirstIStDevice_t)(const PStApiHandle_t pIStSystemHandle, DEVICE_ACCESS_FLAGS eDeviceAccessFlags, PStApiHandle_t pDeviceHandle);

	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStSystem_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IStSystem.
		@~english	@details	This structure holds the address of the C language wrapper function of IStSystem.
		@~japanese	@brief	この構造体は IStSystem のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IStSystem のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_IStSystem_Functions_t
	{
		/*!
			@copydoc PStApiTL_IStSystem_CreateIStSystem_t()
		*/
		PStApiTL_IStSystem_CreateIStSystem_t				CreateIStSystem;

		/*!
			@copydoc PStApiTL_IStSystem_Release_t()
		*/
		PStApiTL_IStSystem_Release_t				Release;

		/*!
		@copydoc PStApiTL_IStSystem_RegisterCallback_t()
		*/
		PStApiTL_IStSystem_RegisterCallback_t		RegisterCallback;

		/*!
		@copydoc PStApiTL_IStSystem_StartEventAcquisitionThread_t()
		*/
		PStApiTL_IStSystem_StartEventAcquisitionThread_t	StartEventAcquisitionThread;

		/*!
		@copydoc PStApiTL_IStSystem_StopEventAcquisitionThread_t()
		*/
		PStApiTL_IStSystem_StopEventAcquisitionThread_t	StopEventAcquisitionThread;

		/*!
			@copydoc PStApiTL_IStSystem_GetStSystemVendor_t()
		*/
		PStApiTL_IStSystem_GetStSystemVendor_t		GetStSystemVendor;

		/*!
			@copydoc PStApiTL_IStSystem_GetIStPort_t()
		*/
		PStApiTL_IStSystem_GetIStPort_t				GetIStPort;

		/*!
			@copydoc PStApiTL_IStSystem_GetIStSystemInfo_t()
		*/
		PStApiTL_IStSystem_GetIStSystemInfo_t		GetIStSystemInfo;

		/*!
			@copydoc PStApiTL_IStSystem_UpdateInterfaceList_t()
		*/
		PStApiTL_IStSystem_UpdateInterfaceList_t	UpdateInterfaceList;

		/*!
			@copydoc PStApiTL_IStSystem_GetInterfaceCount_t()
		*/
		PStApiTL_IStSystem_GetInterfaceCount_t		GetInterfaceCount;

		/*!
			@copydoc PStApiTL_IStSystem_GetIStInterface_t()
		*/
		PStApiTL_IStSystem_GetIStInterface_t		GetIStInterface;

		/*!
			@copydoc PStApiTL_IStSystem_CreateFirstIStDevice_t()
		*/
		PStApiTL_IStSystem_CreateFirstIStDevice_t	CreateFirstIStDevice;
	}StApi_IStSystem_Functions_t, *PStApi_IStSystem_Functions_t;

	/*************************************************************************/
	/* StApi::IStSystemArray */
	/*************************************************************************/
	/*!
		@~english	@brief	Acquire IStDevice interface handle for the first device found (Device index = 0).
		@~english	@details	Acquire IStDevice interface handle for the first device found (Device index = 0).
		@~english	@attention	If IStDevice interface handle is no longer needed, call IStDevice->Release(pDeviceHandle).
		@~english	@param[in] pIStSystemHandleArray	IStSystem handles array.
		@~english	@param[in] nCount	Count of IStSystem handles.
		@~english	@param[in] eDeviceAccessFlags	Device access flag.
		@~english	@param[in,out] pDeviceHandle	IStDevice handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	このシステムで最初に見つかったデバイスを作成し、 IStDevice インターフェースハンドルを取得します。
		@~japanese	@details	このシステムで最初に見つかったデバイスを作成し、 IStDevice インターフェースハンドルを取得します。
		@~japanese	@attention	取得された IStDevice インターフェースハンドルが不要になったら、 IStDevice->Release(pDeviceHandle) を呼び出して解放してください。
		@~japanese	@param[in] pIStSystemHandleArray	IStSystem インターフェースハンドル配列
		@~japanese	@param[in] nCount	IStSystem インターフェースハンドルの数
		@~japanese	@param[out] eDeviceAccessFlags デバイスアクセスフラグを指定します。
		@~japanese	@param[in,out] pDeviceHandle	IStDevice インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStSystemArray_CreateFirstIStDevice_t)(const PStApiHandle_t pIStSystemHandleArray, size_t nCount, DEVICE_ACCESS_FLAGS eDeviceAccessFlags, PStApiHandle_t pDeviceHandle);
	
	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStSystemArray_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of CIStSystemArray.
		@~english	@details	This structure holds the address of the C language wrapper function of CIStSystemArray.
		@~japanese	@brief	この構造体は CIStSystemArray のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は CIStSystemArray のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_IStSystemArray_Functions_t
	{
		/*!
			@copydoc PStApiTL_IStSystemArray_CreateFirstIStDevice_t()
		*/
		PStApiTL_IStSystemArray_CreateFirstIStDevice_t	CreateFirstIStDevice;
	}StApi_IStSystemArray_Functions_t, *PStApi_IStSystemArray_Functions_t;

	/*************************************************************************/
	/* StApi::IStInterfaceInfo */
	/*************************************************************************/
	/*!
		@~english	@brief	GenTL::IFInfo() is used to get information of GenTL::INTERFACE_INFO_ID.
		@~english	@details	GenTL::IFInfo() is used to get information of GenTL::INTERFACE_INFO_ID.
		@~english	@param[in] pIStInterfaceInfoHandle	IStInterfaceInfo interface handle.
		@~english	@param[in,out] szText	INTERFACE_INFO_ID data.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::IFInfo() を使用して GenTL::INTERFACE_INFO_ID の情報を取得します。
		@~japanese	@details	GenTL::IFInfo() を使用して GenTL::INTERFACE_INFO_ID の情報を取得します。
		@~japanese	@param[in] pIStInterfaceInfoHandle	IStInterfaceInfo インターフェースハンドル
		@~japanese	@param[in,out] szText	INTERFACE_INFO_ID データ
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStInterfaceInfo_GetIDA_t)(const PStApiHandle_t pIStInterfaceInfoHandle, char *szText, size_t *pnLen);

	/*!
		@~english	@brief	GenTL::IFInfo() is used to get information of GenTL::INTERFACE_INFO_DISPLAYNAME.
		@~english	@details	GenTL::IFInfo() is used to get information of GenTL::INTERFACE_INFO_DISPLAYNAME.
		@~english	@param[in] pIStInterfaceInfoHandle	IStInterfaceInfo interface handle.
		@~english	@param[in,out] szText	INTERFACE_INFO_DISPLAYNAME data.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::IFInfo() を使用して GenTL::INTERFACE_INFO_DISPLAYNAME の情報を取得します。
		@~japanese	@details	GenTL::IFInfo() を使用して GenTL::INTERFACE_INFO_DISPLAYNAME の情報を取得します。
		@~japanese	@param[in] pIStInterfaceInfoHandle	IStInterfaceInfo インターフェースハンドル
		@~japanese	@param[in,out] szText	INTERFACE_INFO_DISPLAYNAME データ
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStInterfaceInfo_GetDisplayNameA_t)(const PStApiHandle_t pIStInterfaceInfoHandle, char *szText, size_t *pnLen);

	/*!
		@~english	@brief	GenTL::IFInfo() is used to get information of GenTL::INTERFACE_INFO_TLTYPE.
		@~english	@details	GenTL::IFInfo() is used to get information of GenTL::INTERFACE_INFO_TLTYPE.
		@~english	@param[in] pIStInterfaceInfoHandle	IStInterfaceInfo interface handle.
		@~english	@param[in,out] szText	INTERFACE_INFO_TLTYPE data.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::IFInfo() を使用して GenTL::INTERFACE_INFO_TLTYPE の情報を取得します。
		@~japanese	@details	GenTL::IFInfo() を使用して GenTL::INTERFACE_INFO_TLTYPE の情報を取得します。
		@~japanese	@param[in] pIStInterfaceInfoHandle	IStInterfaceInfo インターフェースハンドル
		@~japanese	@param[in,out] szText	INTERFACE_INFO_TLTYPE データ
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStInterfaceInfo_GetTLTypeA_t)(const PStApiHandle_t pIStInterfaceInfoHandle, char *szText, size_t *pnLen);

	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStInterfaceInfo_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IStInterfaceInfo.
		@~english	@details	This structure holds the address of the C language wrapper function of IStInterfaceInfo.
		@~japanese	@brief	この構造体は IStInterfaceInfo のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IStInterfaceInfo のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_IStInterfaceInfo_Functions_t
	{
		/*!
			@copydoc PStApiTL_IStInterfaceInfo_GetIDA_t()
		*/
		PStApiTL_IStInterfaceInfo_GetIDA_t					GetIDA;

		/*!
			@copydoc PStApiTL_IStInterfaceInfo_GetDisplayNameA_t()
		*/
		PStApiTL_IStInterfaceInfo_GetDisplayNameA_t		GetDisplayNameA;

		/*!
			@copydoc PStApiTL_IStInterfaceInfo_GetTLTypeA_t()
		*/
		PStApiTL_IStInterfaceInfo_GetTLTypeA_t				GetTLTypeA;
	}StApi_IStInterfaceInfo_Functions_t, *PStApi_IStInterfaceInfo_Functions_t;

	/*************************************************************************/
	/* StApi::IStInterface */
	/*************************************************************************/
	/*!
		@~english	@brief	Register a callback function.
		@~english	@details	Register a callback function.
		@~english	@param[in] pIStInterfaceHandle	IStInterface interface handle.
		@~english	@param[in]	pFunc	Callback function pointer.
		@~english	@param[in]	pContext	Argument for the callback function.
		@~english	@param[in,out] pIStRegisteredCallbackHandle	IStRegisteredCallback Interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	コールバック関数を登録します。
		@~japanese	@details	コールバック関数を登録します。
		@~japanese	@param[in] pIStInterfaceHandle	IStInterface インターフェースハンドル
		@~japanese	@param[in]	pFunc	コールバック関数として使用する関数
		@~japanese	@param[in]	pContext	コールバック関数に渡されるユーザー用パラメータ
		@~japanese	@param[in,out] pIStRegisteredCallbackHandle	IStRegisteredCallback インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStInterface_RegisterCallback_t)(const PStApiHandle_t pIStInterfaceHandle, fStCallbackFunc_t *pFunc, void* pContext, PStApiHandle_t pIStRegisteredCallbackHandle);
	
	/*!
		@~english	@brief	Start the event handling thread.
		@~english	@details	Start the event handling thread.
		@~english	@param[in] pIStInterfaceHandle	IStInterface interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	イベント取得用スレッドを起動します。
		@~japanese	@details	イベント取得用スレッドを起動します。
		@~japanese	@param[in] pIStInterfaceHandle	IStInterface インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStInterface_StartEventAcquisitionThread_t)(const PStApiHandle_t pIStInterfaceHandle);

	/*!
		@~english	@brief	Stop the event handling thread.
		@~english	@details	Stop the event handling thread.
		@~english	@param[in] pIStInterfaceHandle	IStInterface interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	イベント取得用スレッドを停止します。
		@~japanese	@details	イベント取得用スレッドを停止します。
		@~japanese	@param[in] pIStInterfaceHandle	IStInterface インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStInterface_StopEventAcquisitionThread_t)(const PStApiHandle_t pIStInterfaceHandle);

	/*!
		@~english	@brief	Acquire IStSystem interface handle.
		@~english	@details	Acquire IStSystem interface handle.
		@~english	@param[in] pIStInterfaceHandle	IStInterface interface handle.
		@~english	@param[in,out] pIStSystemHandle	IStSystem interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStSystem インターフェースハンドルを取得します。
		@~japanese	@details	IStSystem インターフェースハンドルを取得します。
		@~japanese	@param[in] pIStInterfaceHandle	IStInterface インターフェースハンドル
		@~japanese	@param[in,out] pIStSystemHandle	IStSystem インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStInterface_GetIStSystem_t)(const PStApiHandle_t pIStInterfaceHandle, PStApiHandle_t pIStSystemHandle);

	/*!
		@~english	@brief	Acquire IStPort interface handle.
		@~english	@details	Acquire IStPort interface handle.
		@~english	@param[in] pIStInterfaceHandle	IStInterface interface handle.
		@~english	@param[in,out] pIStPortHandle	IStPort interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStPort インターフェースハンドルを取得します。
		@~japanese	@details	IStPort インターフェースハンドルを取得します。
		@~japanese	@param[in] pIStInterfaceHandle	IStInterface インターフェースハンドル
		@~japanese	@param[in,out] pIStPortHandle	IStPort インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStInterface_GetIStPort_t)(const PStApiHandle_t pIStInterfaceHandle, PStApiHandle_t pIStPortHandle);

	/*!
		@~english	@brief	Acquire IStInterfaceInfo interface handle.
		@~english	@details	Acquire IStInterfaceInfo interface handle.
		@~english	@param[in] pIStInterfaceHandle	IStInterface interface handle.
		@~english	@param[in,out] pIStInterfaceInfoHandle	IStInterfaceInfo interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStInterfaceInfo インターフェースハンドルを取得します。
		@~japanese	@details	IStInterfaceInfo インターフェースハンドルを取得します。
		@~japanese	@param[in] pIStInterfaceHandle	IStInterface インターフェースハンドル
		@~japanese	@param[in,out] pIStInterfaceInfoHandle	IStInterfaceInfo インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStInterface_GetIStInterfaceInfo_t)(const PStApiHandle_t pIStInterfaceHandle, PStApiHandle_t pIStInterfaceInfoHandle);

	/*!
		@~english	@brief	Scan for connected devices and update the device list.
		@~english	@details      Scan for connected devices and update the device list.
		@~english	@param[in] pIStInterfaceHandle	IStInterface interface handle.
		@~english	@param[out] pbUpdated	True if device list is updated.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	接続されているデバイス(カメラ)を検出し、デバイス(カメラ)リストを更新します。
		@~japanese	@details	接続されているデバイス(カメラ)を検出し、デバイス(カメラ)リストを更新します。
		@~japanese	@param[in] pIStInterfaceHandle	IStInterface インターフェースハンドル
		@~japanese	@param[out] pbUpdated	デバイス(カメラ)リストが変更された場合 true が返されます。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStInterface_UpdateDeviceList_t)(const PStApiHandle_t pIStInterfaceHandle, bool8_t *pbUpdated);

	/*!
		@~english	@brief	Acquire the timeout value for device scanning.
		@~english	@details	Acquire the timeout value for device scanning.
		@~english	@param[in] pIStInterfaceHandle	IStInterface interface handle.
		@~english	@param[out] pnTimtout	The timeout value for device scanning [ms].
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	デバイス(カメラ)リスト更新時のタイムアウト時間を取得します。
		@~japanese	@details	デバイス(カメラ)リスト更新時のタイムアウト時間を取得します。
		@~japanese	@param[in] pIStInterfaceHandle	IStInterface インターフェースハンドル
		@~japanese	@param[out] pnTimtout	デバイス(カメラ)リスト更新時のタイムアウト時間[ms]
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStInterface_GetUpdateDeviceListTimeout_t)(const PStApiHandle_t pIStInterfaceHandle, uint64_t *pnTimtout);
		
	/*!
		@~english	@brief	Set the timeout value for device scanning.
		@~english	@details	Set the timeout value for device scanning.
		@~english	@param[in] pIStInterfaceHandle	IStInterface interface handle.
		@~english	@param[in] iTimeout Set the timeout value for device scanning [ms].
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	デバイス(カメラ)リスト更新時のタイムアウト時間を設定します。
		@~japanese	@details	デバイス(カメラ)リスト更新時のタイムアウト時間を設定します。
		@~japanese	@param[in] pIStInterfaceHandle	IStInterface インターフェースハンドル
		@~japanese	@param[in] iTimeout デバイス(カメラ)リスト更新時のタイムアウト時間[ms]
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStInterface_SetUpdateDeviceListTimeout_t)(const PStApiHandle_t pIStInterfaceHandle, uint64_t iTimeout);

	/*!
		@~english	@brief	Get the number of the detected devices from calling UpdateDeviceList().
		@~english	@details	Get the number of the detected devices from calling UpdateDeviceList().
		@~english	@param[in] pIStInterfaceHandle	IStInterface interface handle.
		@~english	@param[out] pnCount Number of the detected devices.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	認識されているデバイスの数を取得します。接続されたデバイスを認識させるには UpdateDeviceList() を呼び出します。
		@~japanese	@details	認識されているデバイスの数を取得します。接続されたデバイスを認識させるには UpdateDeviceList() を呼び出します。
		@~japanese	@param[in] pIStInterfaceHandle	IStInterface インターフェースハンドル
		@~japanese	@param[out] pnCount	認識されているデバイスの数
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStInterface_GetDeviceCount_t)(const PStApiHandle_t pIStInterfaceHandle, uint32_t *pnCount);

	/*!
		@~english	@brief	Acquire IStDeviceInfo interface handle of a device.
		@~english	@details	Acquire IStDeviceInfo interface handle of a device.
		@~english	@param[in] pIStInterfaceHandle	IStInterface interface handle.
		@~english	@param[in] nIndex	Device index from 0 to (GetDeviceCount() - 1).
		@~english	@param[in,out] pIStDeviceInfoHandle IStDeviceInfo interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	指定したデバイスの IStDeviceInfo インターフェースハンドルを取得します。
		@~japanese	@details	指定したデバイスの IStDeviceInfo インターフェースハンドルを取得します。
		@~japanese	@param[in] pIStInterfaceHandle	IStInterface インターフェースハンドル
		@~japanese	@param[in] nIndex	0から GetDeviceCount() 未満の値でデバイスを指定します。
		@~japanese	@param[in,out] pIStDeviceInfoHandle	IStDeviceInfo インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStInterface_GetIStDeviceInfo_t)(const PStApiHandle_t pIStInterfaceHandle, size_t nIndex, PStApiHandle_t pIStDeviceInfoHandle);

	/*!
		@~english	@brief	Check if a device is accessible.
		@~english	@details  Check if a device is accessible.
		@~english	@param[in] pIStInterfaceHandle	IStInterface interface handle.
		@~english	@param[in] nIndex	Device index from 0 to (GetDeviceCount() - 1).
		@~english	@param[in] eDeviceAccessFlags	Device access flag.
		@~english	@param[out] pbAvailable	True if the device is accessible.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	指定したデバイス(カメラ)が利用可能かどうか確認します。
		@~japanese	@details	指定したデバイス(カメラ)が利用可能かどうか確認します。
		@~japanese	@param[in] pIStInterfaceHandle	IStInterface インターフェースハンドル
		@~japanese	@param[in] nIndex	0から GetDeviceCount() 未満の値でデバイスを指定します。
		@~japanese	@param[in] eDeviceAccessFlags	デバイスアクセスフラグ
		@~japanese	@param[out] pbAvailable	デバイス(カメラ)が利用可能な場合 true が返されます。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStInterface_IsDeviceAvailable_t)(const PStApiHandle_t pIStInterfaceHandle, size_t nIndex, DEVICE_ACCESS_FLAGS eDeviceAccessFlags, bool8_t *pbAvailable);

	/*!
		@~english	@brief	Open Device module of GenTL and acquire IStDevice interface handle.
		@~english	@details	Open Device module of GenTL and acquire IStDevice interface pointer.
		@~english	@param[in] pIStInterfaceHandle	IStInterface interface handle.
		@~english	@attention	If IStDevice interface handle is no longer needed, call IStDevice->Release(pIStDeviceHandle) for release it.
		@~english	@param[in] nIndex	Device index from 0 to (GetDeviceCount() - 1).
		@~english	@param[in] eDeviceAccessFlags	Device access flag.
		@~english	@param[in,out] pIStDeviceHandle	IStDevice Interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	指定したデバイス(カメラ)をオープンし IStDevice インターフェースハンドルを取得します。
		@~japanese	@details	指定したデバイス(カメラ)をオープンし IStDevice インターフェースハンドルを取得します。
		@~japanese	@attention	取得された IStDevice インターフェースが不要になったら、 IStDevice->Release(pIStDeviceHandle) を呼び出して解放してください。
		@~japanese	@param[in] pIStInterfaceHandle	IStInterface インターフェースハンドル
		@~japanese	@param[in] nIndex	0から GetDeviceCount() 未満の値でデバイスを指定します。
		@~japanese	@param[in] eDeviceAccessFlags	デバイスアクセスフラグ
		@~japanese	@param[in,out] pIStDeviceHandle	IStDevice インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStInterface_CreateIStDeviceByIndex_t)(const PStApiHandle_t pIStInterfaceHandle, size_t nIndex, DEVICE_ACCESS_FLAGS eDeviceAccessFlags, PStApiHandle_t pIStDeviceHandle);

	/*!
		@~english	@brief	Open Device module of GenTL and acquire IStDevice interface handle.
		@~english	@details	Open Device module of GenTL and acquire IStDevice interface handle.
		@~english	@param[in] pIStInterfaceHandle	IStInterface interface handle.
		@~english	@attention	If IStDevice interface handle is no longer needed, call IStDevice->Release(pIStDeviceHandle) for release it.
		@~english	@param[in] szID	Device ID.
		@~english	@param[in] eDeviceAccessFlags	The way of access.
		@~english	@param[in,out] pIStDeviceHandle	IStDevice Interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	指定したデバイス(カメラ)をオープンし IStDevice インターフェースハンドルを取得します。
		@~japanese	@details	指定したデバイス(カメラ)をオープンし IStDevice インターフェースハンドルを取得します。
		@~japanese	@attention	取得された IStDevice インターフェースが不要になったら、 IStDevice->Release(pIStDeviceHandle) を呼び出して解放してください。
		@~japanese	@param[in] pIStInterfaceHandle	IStInterface インターフェースハンドル
		@~japanese	@param[in] szID	デバイスID
		@~japanese	@param[in] eDeviceAccessFlags	デバイスアクセスフラグ
		@~japanese	@param[in,out] pIStDeviceHandle	IStDevice インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStInterface_CreateIStDeviceByIDA_t)(const PStApiHandle_t pIStInterfaceHandle, const char *szID, DEVICE_ACCESS_FLAGS eDeviceAccessFlags, PStApiHandle_t pIStDeviceHandle);

	/*!
		@~english	@brief	Open the first detected device module of GenTL (Device index is 0) and acquire IStDevice interface handle.
		@~english	@details	Open the first detected device module of GenTL (Device index is 0) and acquire IStDevice interface handle.
		@~english	@param[in] pIStInterfaceHandle	IStInterface interface handle.
		@~english	@attention	If IStDevice interface handle is no longer needed, call IStDevice->Release(pIStDeviceHandle) for release it.
		@~english	@param[in] eDeviceAccessFlags	Device access flag.
		@~english	@param[in,out] pIStDeviceHandle	IStDevice Interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	最初に見つかったデバイス(カメラ)をオープンし IStDevice インターフェースハンドルを取得します。
		@~japanese	@details	最初に見つかったデバイス(カメラ)をオープンし IStDevice インターフェースハンドルを取得します。
		@~japanese	@attention	取得された IStDevice インターフェースが不要になったら、 IStDevice->Release(pIStDeviceHandle) を呼び出して解放してください。
		@~japanese	@param[in] pIStInterfaceHandle	IStInterface インターフェースハンドル
		@~japanese	@param[in] eDeviceAccessFlags	デバイスアクセスフラグ
		@~japanese	@param[in,out] pIStDeviceHandle	IStDevice インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStInterface_CreateFirstIStDevice_t)(const PStApiHandle_t pIStInterfaceHandle, DEVICE_ACCESS_FLAGS eDeviceAccessFlags, PStApiHandle_t pIStDeviceHandle);

	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStInterface_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IStInterface.
		@~english	@details	This structure holds the address of the C language wrapper function of IStInterface.
		@~japanese	@brief	この構造体は IStInterface のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IStInterface のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_IStInterface_Functions_t
	{
		/*!
			@copydoc PStApiTL_IStInterface_RegisterCallback_t()
		*/
		PStApiTL_IStInterface_RegisterCallback_t	RegisterCallback;
		
		/*!
			@copydoc PStApiTL_IStInterface_StartEventAcquisitionThread_t()
		*/
		PStApiTL_IStInterface_StartEventAcquisitionThread_t	StartEventAcquisitionThread;

		/*!
			@copydoc PStApiTL_IStInterface_StopEventAcquisitionThread_t()
		*/
		PStApiTL_IStInterface_StopEventAcquisitionThread_t	StopEventAcquisitionThread;

		/*!
			@copydoc PStApiTL_IStInterface_GetIStSystem_t()
		*/
		PStApiTL_IStInterface_GetIStSystem_t			GetIStSystem;

		/*!
			@copydoc PStApiTL_IStInterface_GetIStPort_t()
		*/
		PStApiTL_IStInterface_GetIStPort_t				GetIStPort;

		/*!
			@copydoc PStApiTL_IStInterface_GetIStInterfaceInfo_t()
		*/
		PStApiTL_IStInterface_GetIStInterfaceInfo_t		GetIStInterfaceInfo;

		/*!
			@copydoc PStApiTL_IStInterface_UpdateDeviceList_t()
		*/
		PStApiTL_IStInterface_UpdateDeviceList_t			UpdateDeviceList;

		/*!
			@copydoc PStApiTL_IStInterface_GetUpdateDeviceListTimeout_t()
		*/
		PStApiTL_IStInterface_GetUpdateDeviceListTimeout_t	GetUpdateDeviceListTimeout;

		/*!
			@copydoc PStApiTL_IStInterface_SetUpdateDeviceListTimeout_t()
		*/
		PStApiTL_IStInterface_SetUpdateDeviceListTimeout_t	SetUpdateDeviceListTimeout;

		/*!
			@copydoc PStApiTL_IStInterface_GetDeviceCount_t()
		*/
		PStApiTL_IStInterface_GetDeviceCount_t				GetDeviceCount;

		/*!
			@copydoc PStApiTL_IStInterface_GetIStDeviceInfo_t()
		*/
		PStApiTL_IStInterface_GetIStDeviceInfo_t			GetIStDeviceInfo;
		
		/*!
			@copydoc PStApiTL_IStInterface_IsDeviceAvailable_t()
		*/
		PStApiTL_IStInterface_IsDeviceAvailable_t	IsDeviceAvailable;
		
		/*!
			@copydoc PStApiTL_IStInterface_CreateIStDeviceByIndex_t()
		*/
		PStApiTL_IStInterface_CreateIStDeviceByIndex_t	CreateIStDeviceByIndex;
		
		/*!
			@copydoc PStApiTL_IStInterface_CreateIStDeviceByIDA_t()
		*/
		PStApiTL_IStInterface_CreateIStDeviceByIDA_t	CreateIStDeviceByIDA;
		
		/*!
			@copydoc PStApiTL_IStInterface_CreateFirstIStDevice_t()
		*/
		PStApiTL_IStInterface_CreateFirstIStDevice_t	CreateFirstIStDevice;
	}StApi_IStInterface_Functions_t, *PStApi_IStInterface_Functions_t;

	/*************************************************************************/
	/* StApi::IStDeviceInfo */
	/*************************************************************************/
	/*!
		@~english	@brief	GenTL::DevGetInfo() is used to get GenTL::DEVICE_INFO_ID data.
		@~english	@details	GenTL::DevGetInfo() is used to get GenTL::DEVICE_INFO_ID data.
		@~english	@param[in] pIStDeviceInfoHandle	IStDeviceInfo interface handle.
		@~english	@param[in,out] szText	DEVICE_INFO_ID data.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::DevGetInfo() を使用して GenTL::DEVICE_INFO_ID の情報を取得します。
		@~japanese	@details	GenTL::DevGetInfo() を使用して GenTL::DEVICE_INFO_ID の情報を取得します。
		@~japanese	@param[in] pIStDeviceInfoHandle	IStDeviceInfo インターフェースハンドル
		@~japanese	@param[in,out] szText	DEVICE_INFO_ID データ
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStDeviceInfo_GetIDA_t)(const PStApiHandle_t pIStDeviceInfoHandle, char *szText, size_t *pnLen);

	/*!
		@~english	@brief	GenTL::DevGetInfo() is used to get GenTL::DEVICE_INFO_VENDOR data.
		@~english	@details	GenTL::DevGetInfo() is used to get GenTL::DEVICE_INFO_VENDOR data.
		@~english	@param[in] pIStDeviceInfoHandle	IStDeviceInfo interface handle.
		@~english	@param[in,out] szText	DEVICE_INFO_VENDOR data.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::DevGetInfo() を使用して GenTL::DEVICE_INFO_VENDOR の情報を取得します。
		@~japanese	@details	GenTL::DevGetInfo() を使用して GenTL::DEVICE_INFO_VENDOR の情報を取得します。
		@~japanese	@param[in] pIStDeviceInfoHandle	IStDeviceInfo インターフェースハンドル
		@~japanese	@param[in,out] szText	DEVICE_INFO_VENDOR データ
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStDeviceInfo_GetVendorA_t)(const PStApiHandle_t pIStDeviceInfoHandle, char *szText, size_t *pnLen);

	/*!
		@~english	@brief	GenTL::DevGetInfo() is used to get GenTL::DEVICE_INFO_MODEL data.
		@~english	@details	GenTL::DevGetInfo() is used to get GenTL::DEVICE_INFO_MODEL data.
		@~english	@param[in] pIStDeviceInfoHandle	IStDeviceInfo interface handle.
		@~english	@param[in,out] szText	DEVICE_INFO_MODEL data.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::DevGetInfo() を使用して GenTL::DEVICE_INFO_MODEL の情報を取得します。
		@~japanese	@details	GenTL::DevGetInfo() を使用して GenTL::DEVICE_INFO_MODEL の情報を取得します。
		@~japanese	@param[in] pIStDeviceInfoHandle	IStDeviceInfo インターフェースハンドル
		@~japanese	@param[in,out] szText	DEVICE_INFO_MODEL データ
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStDeviceInfo_GetModelA_t)(const PStApiHandle_t pIStDeviceInfoHandle, char *szText, size_t *pnLen);

	/*!
		@~english	@brief	GenTL::DevGetInfo() is used to get GenTL::DEVICE_INFO_TLTYPE data.
		@~english	@details	GenTL::DevGetInfo() is used to get GenTL::DEVICE_INFO_TLTYPE data.
		@~english	@param[in] pIStDeviceInfoHandle	IStDeviceInfo interface handle.
		@~english	@param[in,out] szText	DEVICE_INFO_TLTYPE data.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::DevGetInfo() を使用して GenTL::DEVICE_INFO_TLTYPE の情報を取得します。
		@~japanese	@details	GenTL::DevGetInfo() を使用して GenTL::DEVICE_INFO_TLTYPE の情報を取得します。
		@~japanese	@param[in] pIStDeviceInfoHandle	IStDeviceInfo インターフェースハンドル
		@~japanese	@param[in,out] szText	DEVICE_INFO_TLTYPE データ
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStDeviceInfo_GetTLTypeA_t)(const PStApiHandle_t pIStDeviceInfoHandle, char *szText, size_t *pnLen);

	/*!
		@~english	@brief	GenTL::DevGetInfo() is used to get GenTL::DEVICE_INFO_DISPLAYNAME data.
		@~english	@details	GenTL::DevGetInfo() is used to get GenTL::DEVICE_INFO_DISPLAYNAME data.
		@~english	@param[in] pIStDeviceInfoHandle	IStDeviceInfo interface handle.
		@~english	@param[in,out] szText	DEVICE_INFO_DISPLAYNAME data.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::DevGetInfo() を使用して GenTL::DEVICE_INFO_DISPLAYNAME の情報を取得します。
		@~japanese	@details	GenTL::DevGetInfo() を使用して GenTL::DEVICE_INFO_DISPLAYNAME の情報を取得します。
		@~japanese	@param[in] pIStDeviceInfoHandle	IStDeviceInfo インターフェースハンドル
		@~japanese	@param[in,out] szText	DEVICE_INFO_DISPLAYNAME データ
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStDeviceInfo_GetDisplayNameA_t)(const PStApiHandle_t pIStDeviceInfoHandle, char *szText, size_t *pnLen);

	/*!
		@~english	@brief	GenTL::DevGetInfo() is used to get GenTL::DEVICE_INFO_ACCESS_STATUS data.
		@~english	@details	GenTL::DevGetInfo() is used to get GenTL::DEVICE_INFO_ACCESS_STATUS data.
		@~english	@param[in] pIStDeviceInfoHandle	IStDeviceInfo interface handle.
		@~english	@param[in,out]	peDeviceAccessStatus	DEVICE_INFO_ACCESS_STATUS data.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::DevGetInfo() を使用して GenTL::DEVICE_INFO_ACCESS_STATUS の情報を取得します。
		@~japanese	@details	GenTL::DevGetInfo() を使用して GenTL::DEVICE_INFO_ACCESS_STATUS の情報を取得します。
		@~japanese	@param[in] pIStDeviceInfoHandle	IStDeviceInfo インターフェースハンドル
		@~japanese	@param[in,out]	peDeviceAccessStatus	DEVICE_INFO_ACCESS_STATUS データ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStDeviceInfo_GetAccessStatus_t)(const PStApiHandle_t pIStDeviceInfoHandle, DEVICE_ACCESS_STATUS *peDeviceAccessStatus);

	/*!
		@~english	@brief	GenTL::DevGetInfo() is used to get GenTL::DEVICE_INFO_USER_DEFINED_NAME data.
		@~english	@details	GenTL::DevGetInfo() is used to get GenTL::DEVICE_INFO_USER_DEFINED_NAME data.
		@~english	@param[in] pIStDeviceInfoHandle	IStDeviceInfo interface handle.
		@~english	@param[in,out] szText	DEVICE_INFO_USER_DEFINED_NAME data.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::DevGetInfo() を使用して GenTL::DEVICE_INFO_USER_DEFINED_NAME の情報を取得します。
		@~japanese	@details	GenTL::DevGetInfo() を使用して GenTL::DEVICE_INFO_USER_DEFINED_NAME の情報を取得します。
		@~japanese	@param[in] pIStDeviceInfoHandle	IStDeviceInfo インターフェースハンドル
		@~japanese	@param[in,out] szText	DEVICE_INFO_USER_DEFINED_NAME データ
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStDeviceInfo_GetUserDefinedNameA_t)(const PStApiHandle_t pIStDeviceInfoHandle, char *szText, size_t *pnLen);

	/*!
		@~english	@brief	GenTL::DevGetInfo() is used to get GenTL::DEVICE_INFO_SERIAL_NUMBER data.
		@~english	@details	GenTL::DevGetInfo() is used to get GenTL::DEVICE_INFO_SERIAL_NUMBER data.
		@~english	@param[in] pIStDeviceInfoHandle	IStDeviceInfo interface handle.
		@~english	@param[in,out] szText	DEVICE_INFO_SERIAL_NUMBER data.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::DevGetInfo() を使用して GenTL::DEVICE_INFO_SERIAL_NUMBER の情報を取得します。
		@~japanese	@details	GenTL::DevGetInfo() を使用して GenTL::DEVICE_INFO_SERIAL_NUMBER の情報を取得します。
		@~japanese	@param[in] pIStDeviceInfoHandle	IStDeviceInfo インターフェースハンドル
		@~japanese	@param[in,out] szText	DEVICE_INFO_SERIAL_NUMBER データ
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStDeviceInfo_GetSerialNumberA_t)(const PStApiHandle_t pIStDeviceInfoHandle, char *szText, size_t *pnLen);

	/*!
		@~english	@brief	GenTL::DevGetInfo() is used to get GenTL::DEVICE_INFO_VERSION data.
		@~english	@details	GenTL::DevGetInfo() is used to get GenTL::DEVICE_INFO_VERSION data.
		@~english	@param[in] pIStDeviceInfoHandle	IStDeviceInfo interface handle.
		@~english	@param[in,out] szText	DEVICE_INFO_VERSION data.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::DevGetInfo() を使用して GenTL::DEVICE_INFO_VERSION の情報を取得します。
		@~japanese	@details	GenTL::DevGetInfo() を使用して GenTL::DEVICE_INFO_VERSION の情報を取得します。
		@~japanese	@param[in] pIStDeviceInfoHandle	IStDeviceInfo インターフェースハンドル
		@~japanese	@param[in,out] szText	DEVICE_INFO_VERSION データ
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStDeviceInfo_GetVersionA_t)(const PStApiHandle_t pIStDeviceInfoHandle, char *szText, size_t *pnLen);

	/*!
		@~english	@brief	GenTL::DevGetInfo() is used to get GenTL::DEVICE_INFO_TIMESTAMP_FREQUENCY data.
		@~english	@details	GenTL::DevGetInfo() is used to get GenTL::DEVICE_INFO_TIMESTAMP_FREQUENCY data.
		@~english	@param[in] pIStDeviceInfoHandle	IStDeviceInfo interface handle.
		@~english	@param[in,out]	pStringBufferHandle	DEVICE_INFO_TIMESTAMP_FREQUENCY data.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::DevGetInfo() を使用して GenTL::DEVICE_INFO_TIMESTAMP_FREQUENCY の情報を取得します。
		@~japanese	@details	GenTL::DevGetInfo() を使用して GenTL::DEVICE_INFO_TIMESTAMP_FREQUENCY の情報を取得します。
		@~japanese	@param[in] pIStDeviceInfoHandle	IStDeviceInfo インターフェースハンドル
		@~japanese	@param[in,out]	pStringBufferHandle	DEVICE_INFO_TIMESTAMP_FREQUENCY データ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStDeviceInfo_GetTimestampFrequency_t)(const PStApiHandle_t pIStDeviceInfoHandle, uint64_t *pnFrequency);

	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStDeviceInfo_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IStDeviceInfo.
		@~english	@details	This structure holds the address of the C language wrapper function of IStDeviceInfo.
		@~japanese	@brief	この構造体は IStDeviceInfo のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IStDeviceInfo のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_IStDeviceInfo_Functions_t
	{
		/*!
			@copydoc PStApiTL_IStDeviceInfo_GetIDA_t()
		*/
		PStApiTL_IStDeviceInfo_GetIDA_t	GetIDA;

		/*!
			@copydoc PStApiTL_IStDeviceInfo_GetVendorA_t()
		*/
		PStApiTL_IStDeviceInfo_GetVendorA_t	GetVendorA;

		/*!
			@copydoc PStApiTL_IStDeviceInfo_GetModelA_t()
		*/
		PStApiTL_IStDeviceInfo_GetModelA_t	GetModelA;

		/*!
			@copydoc PStApiTL_IStDeviceInfo_GetTLTypeA_t()
		*/
		PStApiTL_IStDeviceInfo_GetTLTypeA_t	GetTLTypeA;

		/*!
			@copydoc PStApiTL_IStDeviceInfo_GetDisplayNameA_t()
		*/
		PStApiTL_IStDeviceInfo_GetDisplayNameA_t	GetDisplayNameA;

		/*!
			@copydoc PStApiTL_IStDeviceInfo_GetAccessStatus_t()
		*/
		PStApiTL_IStDeviceInfo_GetAccessStatus_t	GetAccessStatus;

		/*!
			@copydoc PStApiTL_IStDeviceInfo_GetUserDefinedNameA_t()
		*/
		PStApiTL_IStDeviceInfo_GetUserDefinedNameA_t	GetUserDefinedNameA;

		/*!
			@copydoc PStApiTL_IStDeviceInfo_GetSerialNumberA_t()
		*/
		PStApiTL_IStDeviceInfo_GetSerialNumberA_t	GetSerialNumberA;

		/*!
			@copydoc PStApiTL_IStDeviceInfo_GetVersionA_t()
		*/
		PStApiTL_IStDeviceInfo_GetVersionA_t	GetVersionA;

		/*!
			@copydoc PStApiTL_IStDeviceInfo_GetTimestampFrequency_t()
		*/
		PStApiTL_IStDeviceInfo_GetTimestampFrequency_t	GetTimestampFrequency;

	}StApi_IStDeviceInfo_Functions_t, *PStApi_IStDeviceInfo_Functions_t;

	/*************************************************************************/
	/* StApi::IStDevice */
	/*************************************************************************/
	/*!
		@~english	@brief	Release object.
		@~english	@details	Release object.
		@~english	@param[in] pIStDeviceHandle	IStDevice interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	解放します。
		@~japanese	@details	解放します。
		@~japanese	@param[in] pIStDeviceHandle	IStDevice インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStDevice_Release_t)(PStApiHandle_t pIStDeviceHandle);

	/*!
		@~english	@brief	Register a callback function.
		@~english	@details	Register a callback function.
		@~english	@param[in] pIStDeviceHandle	IStDevice interface handle.
		@~english	@param[in]	pFunc	Callback function pointer.
		@~english	@param[in]	pContext	Argument for the callback function.
		@~english	@param[in,out] pIStRegisteredCallbackHandle	IStRegisteredCallback Interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	コールバック関数を登録します。
		@~japanese	@details	コールバック関数を登録します。
		@~japanese	@param[in] pIStDeviceHandle	IStDevice インターフェースハンドル
		@~japanese	@param[in]	pFunc	コールバック関数として使用する関数
		@~japanese	@param[in]	pContext	コールバック関数に渡されるユーザー用パラメータ
		@~japanese	@param[in,out] pIStRegisteredCallbackHandle	IStRegisteredCallback インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStDevice_RegisterCallback_t)(const PStApiHandle_t pIStDeviceHandle, fStCallbackFunc_t *pFunc, void* pContext, PStApiHandle_t pIStRegisteredCallbackHandle);

	/*!
		@~english	@brief	Start the event handling thread.
		@~english	@details	Start the event handling thread.
		@~english	@param[in] pIStDeviceHandle	IStDevice interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	イベント取得用スレッドを起動します。
		@~japanese	@details	イベント取得用スレッドを起動します。
		@~japanese	@param[in] pIStDeviceHandle	IStDevice インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStDevice_StartEventAcquisitionThread_t)(const PStApiHandle_t pIStDeviceHandle);

	/*!
		@~english	@brief	Stop the event handling thread.
		@~english	@details	Stop the event handling thread.
		@~english	@param[in] pIStDeviceHandle	IStDevice interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	イベント取得用スレッドを停止します。
		@~japanese	@details	イベント取得用スレッドを停止します。
		@~japanese	@param[in] pIStDeviceHandle	IStDevice インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStDevice_StopEventAcquisitionThread_t)(const PStApiHandle_t pIStDeviceHandle);

	/*!
		@~english	@brief	Acquire IStInterface interface handle.
		@~english	@details	Acquire IStInterface interface handle.
		@~english	@param[in] pIStDeviceHandle	IStDevice interface handle.
		@~english	@param[in,out] pIStInterfaceHandle	IStInterface interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStInterface インターフェースハンドルを取得します。
		@~japanese	@details	IStInterface インターフェースハンドルを取得します。
		@~japanese	@param[in] pIStDeviceHandle	IStDevice インターフェースハンドル
		@~japanese	@param[in,out] pIStInterfaceHandle	IStInterface インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStDevice_GetIStInterface_t)(const PStApiHandle_t pIStDeviceHandle, PStApiHandle_t pIStInterfaceHandle);

	/*!
		@~english	@brief	Acquire interface handle of IStPort for local port. This is for GenTL device module to apply setting to host side.
		@~english	@details	Acquire interface handle of IStPort for local port. This is for GenTL device module to apply setting to host side.
		@~english	@param[in] pIStDeviceHandle	IStDevice interface handle.
		@~english	@param[in,out] pIStPortHandle	IStPort interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ローカルポート用の IStPort インターフェースハンドルを取得します。このポートはGenTLデバイスモジュールのホスト側の設定に使用されます。
		@~japanese	@details	ローカルポート用の IStPort インターフェースハンドルを取得します。このポートはGenTLデバイスモジュールのホスト側の設定に使用されます。
		@~japanese	@param[in] pIStDeviceHandle	IStDevice インターフェースハンドル
		@~japanese	@param[in,out] pIStPortHandle	IStPort インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStDevice_GetLocalIStPort_t)(const PStApiHandle_t pIStDeviceHandle, PStApiHandle_t pIStPortHandle);

	/*!
		@~english	@brief	Acquire IStDeviceInfo interface handle.
		@~english	@details	Acquire IStDeviceInfo interface handle.
		@~english	@param[in] pIStDeviceHandle	IStDevice interface handle.
		@~english	@param[in,out] pIStDeviceInfoHandle	IStDeviceInfo interface handle.
		@~japanese	@brief	IStDeviceInfo インターフェースハンドルを取得します。
		@~japanese	@details	IStDeviceInfo インターフェースハンドルを取得します。
		@~japanese	@param[in] pIStDeviceHandle	IStDevice インターフェースハンドル
		@~japanese	@param[in,out] pIStDeviceInfoHandle	IStDeviceInfo インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStDevice_GetIStDeviceInfo_t)(const PStApiHandle_t pIStDeviceHandle, PStApiHandle_t pIStDeviceInfoHandle);

	/*!
		@~english	@brief	Acquire interface handle of IStPort for remote port. This is for GenTL device module to apply setting to camera side.
		@~english	@details	Acquire interface handle of IStPort for remote port. This is for GenTL device module to apply setting to camera side.
		@~english	@param[in] pIStDeviceHandle	IStDevice interface handle.
		@~english	@param[in,out] pIStPortHandle	IStPort interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	リモートポート用の IStPort インターフェースハンドルを取得します。このポートはGenTLデバイスモジュールのデバイス(カメラ)側の設定に使用されます。
		@~japanese	@details	リモートポート用の IStPort インターフェースハンドルを取得します。このポートはGenTLデバイスモジュールのデバイス(カメラ)側の設定に使用されます。
		@~japanese	@param[in] pIStDeviceHandle	IStDevice インターフェースハンドル
		@~japanese	@param[in,out] pIStPortHandle	IStPort インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStDevice_GetRemoteIStPort_t)(const PStApiHandle_t pIStDeviceHandle, PStApiHandle_t pIStPortHandle);

	/*!
		@~english	@brief	Get the counts of DataStream.
		@~english	@details	Get the counts of DataStream.
		@~english	@param[in] pIStDeviceHandle	IStDevice interface handle.
		@~english	@param[out] pnCount	Counts of DataStream.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	データストリームの数を取得します。
		@~japanese	@details	データストリームの数を取得します。
		@~japanese	@param[in] pIStDeviceHandle	IStDevice インターフェースハンドル
		@~japanese	@param[in,out] pnCount	データストリームの数
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStDevice_GetDataStreamCount_t)(const PStApiHandle_t pIStDeviceHandle, uint32_t *pnCount);

	/*!
		@~english	@brief	Open DataStream module of GenTL and acquire IStDataStream interface handle.
		@~english	@details	Open DataStream module of GenTL and acquire IStDataStream interface handle.
		@~english	@attention	If the acquired interface handle of IStDataStream does not needed anymore, call IStDataStream->Release(pDataStreamHandle) to release it. 
		@~english	@param[in] pIStDeviceHandle	IStDevice interface handle.
		@~english	@param[in] nIndex	IStDevice interface handle.
		@~english	@param[in] pIStAllocatorHandle	IStAllocator interface handle for allocating and releasing memory. If NULL, the buffer memory allocation and deallocation are managed by StApi.
		@~english	@param[in,out] pIStDataStreamHandle	IStDataStream interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	データストリームをオープンし IStDataStream インターフェースハンドルを取得します。
		@~japanese	@details	データストリームをオープンし IStDataStream インターフェースハンドルを取得します。
		@~japanese	@attention	取得された IStDataStream インターフェースハンドルが不要になったら、 IStDataStream->Release(pDataStreamHandle) を呼び出して解放してください。
		@~japanese	@param[in] pIStDeviceHandle	IStDevice インターフェースハンドル
		@~japanese	@param[in] nIndex	0から GetDataStreamCount() 未満の値でデータストリームを指定します。
		@~japanese	@param[in] pIStAllocator	ストリーミングに使用されるバッファの割り当ておよび解放に使用される IStAllocator インターフェースハンドルを指定します。NULLが指定された場合は、StApi内部でバッファの割り当ておよび解放が行われます。
		@~japanese	@param[in,out] pIStDataStreamHandle	IStDataStream インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStDevice_CreateIStDataStream_t)(const PStApiHandle_t pIStDeviceHandle, size_t nIndex, PStApiHandle_t pIStAllocatorHandle, PStApiHandle_t pIStDataStreamHandle);

	/*!
		@~english	@brief	Execute AcquisitionStart command to start data transmission.
		@~english	@details	Execute AcquisitionStart command to start data transmission.
		@~english	@attention	IStDataStream.StartAcquisition() must be called beforehand to enable data acquisition in the host side. To stop acquisition, AcquisitionStop() must be called.
		@~english	@param[in] pIStDeviceHandle	IStDevice interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	カメラのAcquisitionStartコマンドを実行し、カメラからのデータ出力を開始します。
		@~japanese	@details	カメラのAcquisitionStartコマンドを実行し、カメラからのデータ出力を開始します。
		@~japanese	@attention	予め IStDataStream.StartAcquisition() を使用してホスト側のデータ取得を開始しておく必要があります。停止する場合は AcquisitionStop() を呼び出します。
		@~japanese	@param[in] pIStDeviceHandle	IStDevice インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStDevice_AcquisitionStart_t)(const PStApiHandle_t pIStDeviceHandle);

	/*!
		@~english	@brief	Execute AcquisitionStop command to stop data transmission.
		@~english	@details	Execute AcquisitionStop command to stop data transmission.
		@~english	@attention	IStDataStream.StopAcquisition() must be called to stop the data acquisition in the host side.
		@~english	@param[in] pIStDeviceHandle	IStDevice interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	カメラのAcquisitionStopコマンドを実行し、カメラからのデータ出力を停止します。
		@~japanese	@details	カメラのAcquisitionStopコマンドを実行し、カメラからのデータ出力を停止します。
		@~japanese	@attention	別途 IStDataStream.StopAcquisition() を使用してホスト側のデータ取得を停止する必要があります。
		@~japanese	@param[in] pIStDeviceHandle	IStDevice インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStDevice_AcquisitionStop_t)(const PStApiHandle_t pIStDeviceHandle);

	/*!
		@~english	@brief	Check if the camera lost its connection.
		@~english	@details	    Check if the camera lost its connection.
		@~english	@attention	This will be only workable when DeviceLost event of GenTL is supported.
		@~english	@param[in] pIStDeviceHandle	IStDevice interface handle.
		@~english	@param[out] pIsDeviceLost	Return true if disconnected.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	デバイス(カメラ)との接続が切断されたかどうかを確認します。
		@~japanese	@details	デバイス(カメラ)との接続が切断されたかどうかを確認します。
		@~japanese	@attention	DeviceLost イベントがサポートされているGenTLモジュール使用時のみ正常な値が返されます。
		@~japanese	@param[in] pIStDeviceHandle	IStDevice インターフェースハンドル
		@~japanese	@param[out] pIsDeviceLost	デバイス(カメラ)との接続が切断されている場合、 true が返されます。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStDevice_IsDeviceLost_t)(const PStApiHandle_t pIStDeviceHandle, bool8_t *pIsDeviceLost);

	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStDevice_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IStDevice.
		@~english	@details	This structure holds the address of the C language wrapper function of IStDevice.
		@~japanese	@brief	この構造体は IStDevice のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IStDevice のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_IStDevice_Functions_t
	{
		/*!
			@copydoc PStApiTL_IStDevice_Release_t()
		*/
		PStApiTL_IStDevice_Release_t	Release;

		/*!
			@copydoc PStApiTL_IStDevice_RegisterCallback_t()
		*/
		PStApiTL_IStDevice_RegisterCallback_t	RegisterCallback;
		
		/*!
			@copydoc PStApiTL_IStDevice_StartEventAcquisitionThread_t()
		*/
		PStApiTL_IStDevice_StartEventAcquisitionThread_t	StartEventAcquisitionThread;

		/*!
			@copydoc PStApiTL_IStDevice_StopEventAcquisitionThread_t()
		*/
		PStApiTL_IStDevice_StopEventAcquisitionThread_t	StopEventAcquisitionThread;

		/*!
			@copydoc PStApiTL_IStDevice_GetIStInterface_t()
		*/
		PStApiTL_IStDevice_GetIStInterface_t	GetIStInterface;

		/*!
			@copydoc PStApiTL_IStDevice_GetLocalIStPort_t()
		*/
		PStApiTL_IStDevice_GetLocalIStPort_t	GetLocalIStPort;

		/*!
			@copydoc PStApiTL_IStDevice_GetIStDeviceInfo_t()
		*/
		PStApiTL_IStDevice_GetIStDeviceInfo_t		GetIStDeviceInfo;

		/*!
			@copydoc PStApiTL_IStDevice_GetRemoteIStPort_t()
		*/
		PStApiTL_IStDevice_GetRemoteIStPort_t	GetRemoteIStPort;

		/*!
			@copydoc PStApiTL_IStDevice_GetDataStreamCount_t()
		*/
		PStApiTL_IStDevice_GetDataStreamCount_t	GetDataStreamCount;

		/*!
			@copydoc PStApiTL_IStDevice_CreateIStDataStream_t()
		*/
		PStApiTL_IStDevice_CreateIStDataStream_t	CreateIStDataStream;

		/*!
			@copydoc PStApiTL_IStDevice_AcquisitionStart_t()
		*/
		PStApiTL_IStDevice_AcquisitionStart_t		AcquisitionStart;

		/*!
			@copydoc PStApiTL_IStDevice_AcquisitionStop_t()
		*/
		PStApiTL_IStDevice_AcquisitionStop_t		AcquisitionStop;

		/*!
			@copydoc PStApiTL_IStDevice_IsDeviceLost_t()
		*/
		PStApiTL_IStDevice_IsDeviceLost_t	IsDeviceLost;
	}StApi_IStDevice_Functions_t, *PStApi_IStDevice_Functions_t;
	

	/*************************************************************************/
	/* StApi::IStDeviceArray */
	/*************************************************************************/
	/*!
		@~english	@brief	Execute AcquisitionStart command to start data transmission.
		@~english	@details	Execute AcquisitionStart command to start data transmission.
		@~english	@attention	IStDataStream.StartAcquisition() must be called beforehand to enable data acquisition in the host side. To stop acquisition, AcquisitionStop() must be called.
		@~english	@param[in] pIStDeviceHandleArray	IStDevice interface handles array.
		@~english	@param[in] nCount	Count of IStDevice interface handles.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	カメラのAcquisitionStartコマンドを実行し、カメラからのデータ出力を開始します。
		@~japanese	@details	カメラのAcquisitionStartコマンドを実行し、カメラからのデータ出力を開始します。
		@~japanese	@attention	予め IStDataStream.StartAcquisition() を使用してホスト側のデータ取得を開始しておく必要があります。停止する場合は AcquisitionStop() を呼び出します。
		@~japanese	@param[in] pIStDeviceHandleArray	IStDevice インターフェースハンドル配列
		@~japanese	@param[in] nCount	IStDevice インターフェースハンドルの数
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStDeviceArray_AcquisitionStart_t)(const PStApiHandle_t pIStDeviceHandleArray, size_t nCount);

	/*!
		@~english	@brief	Execute AcquisitionStop command to stop data transmission.
		@~english	@details	Execute AcquisitionStop command to stop data transmission.
		@~english	@attention	IStDataStream.StopAcquisition() must be called to stop the data acquisition in the host side.
		@~english	@param[in] pIStDeviceHandleArray	IStDevice interface handles array.
		@~english	@param[in] nCount	Count of IStDevice interface handles.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	カメラのAcquisitionStopコマンドを実行し、カメラからのデータ出力を停止します。
		@~japanese	@details	カメラのAcquisitionStopコマンドを実行し、カメラからのデータ出力を停止します。
		@~japanese	@attention	別途 IStDataStream.StopAcquisition() を使用してホスト側のデータ取得を停止する必要があります。
		@~japanese	@param[in] pIStDeviceHandleArray	IStDevice インターフェースハンドル配列
		@~japanese	@param[in] nCount	IStDevice インターフェースハンドルの数
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStDeviceArray_AcquisitionStop_t)(const PStApiHandle_t pIStDeviceHandleArray, size_t nCount);
	
	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStDeviceArray_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of CIStDeviceArray.
		@~english	@details	This structure holds the address of the C language wrapper function of CIStDeviceArray.
		@~japanese	@brief	この構造体は CIStDeviceArray のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は CIStDeviceArray のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_IStDeviceArray_Functions_t
	{
		/*!
			@copydoc PStApiTL_IStDeviceArray_AcquisitionStart_t()
		*/
		PStApiTL_IStDeviceArray_AcquisitionStart_t		AcquisitionStart;

		/*!
			@copydoc PStApiTL_IStDeviceArray_AcquisitionStop_t()
		*/
		PStApiTL_IStDeviceArray_AcquisitionStop_t		AcquisitionStop;
	}StApi_IStDeviceArray_Functions_t, *PStApi_IStDeviceArray_Functions_t;

	/*************************************************************************/
	/* StApi::IStDataStreamInfo */
	/*************************************************************************/
	/*!
		@~english	@brief	GenTL::DSGetInfo() is used to get the value of GenTL::STREAM_INFO_ID.
		@~english	@details	GenTL::DSGetInfo() is used to get the value of GenTL::STREAM_INFO_ID.
		@~english	@param[in] pIStDataStreamInfoHandle	IStDataStreamInfo interface handle.
		@~english	@param[in,out] szText	STREAM_INFO_ID
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::DSGetInfo() を使用して GenTL::STREAM_INFO_ID の情報を取得します。
		@~japanese	@details	GenTL::DSGetInfo() を使用して GenTL::STREAM_INFO_ID の情報を取得します。
		@~japanese	@param[in] pIStDataStreamInfoHandle	IStDataStreamInfo インターフェースハンドル
		@~japanese	@param[in,out] szText	STREAM_INFO_ID
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStDataStreamInfo_GetIDA_t)(const PStApiHandle_t pIStDataStreamInfoHandle, char *szText, size_t *pnLen);

	/*!
		@~english	@brief	GenTL::DSGetInfo() is used to get the value of GenTL::STREAM_INFO_NUM_DELIVERED.
		@~english	@details	GenTL::DSGetInfo() is used to get the value of GenTL::STREAM_INFO_NUM_DELIVERED.
		@~english	@param[in] pIStDataStreamInfoHandle	IStDataStreamInfo interface handle.
		@~english	@param[out]	pnCount	STREAM_INFO_NUM_DELIVERED
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::DSGetInfo() を使用して GenTL::STREAM_INFO_NUM_DELIVERED の情報を取得します。
		@~japanese	@details	GenTL::DSGetInfo() を使用して GenTL::STREAM_INFO_NUM_DELIVERED の情報を取得します。
		@~japanese	@param[in] pIStDataStreamInfoHandle	IStDataStreamInfo インターフェースハンドル
		@~japanese	@param[out]	pnCount	STREAM_INFO_NUM_DELIVERED
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStDataStreamInfo_GetNumDelivered_t)(const PStApiHandle_t pIStDataStreamInfoHandle, uint64_t *pnCount);

	/*!
		@~english	@brief	GenTL::DSGetInfo() is used to get the value of GenTL::STREAM_INFO_NUM_UNDERRUN.
		@~english	@details	GenTL::DSGetInfo() is used to get the value of GenTL::STREAM_INFO_NUM_UNDERRUN.
		@~english	@param[in] pIStDataStreamInfoHandle	IStDataStreamInfo interface handle.
		@~english	@param[out]	pnCount	STREAM_INFO_NUM_UNDERRUN
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::DSGetInfo() を使用して GenTL::STREAM_INFO_NUM_UNDERRUN の情報を取得します。
		@~japanese	@details	GenTL::DSGetInfo() を使用して GenTL::STREAM_INFO_NUM_UNDERRUN の情報を取得します。
		@~japanese	@param[in] pIStDataStreamInfoHandle	IStDataStreamInfo インターフェースハンドル
		@~japanese	@param[out]	pnCount	STREAM_INFO_NUM_UNDERRUN
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStDataStreamInfo_GetNumUnderrun_t)(const PStApiHandle_t pIStDataStreamInfoHandle, uint64_t *pnCount);

	/*!
		@~english	@brief	GenTL::DSGetInfo() is used to get the value of GenTL::STREAM_INFO_NUM_ANNOUNCED.
		@~english	@details	GenTL::DSGetInfo() is used to get the value of GenTL::STREAM_INFO_NUM_ANNOUNCED.
		@~english	@param[in] pIStDataStreamInfoHandle	IStDataStreamInfo interface handle.
		@~english	@param[out]	pnCount	STREAM_INFO_NUM_ANNOUNCED
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::DSGetInfo() を使用して GenTL::STREAM_INFO_NUM_ANNOUNCED の情報を取得します。
		@~japanese	@details	GenTL::DSGetInfo() を使用して GenTL::STREAM_INFO_NUM_ANNOUNCED の情報を取得します。
		@~japanese	@param[in] pIStDataStreamInfoHandle	IStDataStreamInfo インターフェースハンドル
		@~japanese	@param[out]	pnCount	STREAM_INFO_NUM_ANNOUNCED
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStDataStreamInfo_GetNumAnnounced_t)(const PStApiHandle_t pIStDataStreamInfoHandle, size_t *pnCount);

	/*!
		@~english	@brief	GenTL::DSGetInfo() is used to get the value of GenTL::STREAM_INFO_NUM_QUEUED.
		@~english	@details	GenTL::DSGetInfo() is used to get the value of GenTL::STREAM_INFO_NUM_QUEUED.
		@~english	@param[in] pIStDataStreamInfoHandle	IStDataStreamInfo interface handle.
		@~english	@param[out]	pnCount	STREAM_INFO_NUM_QUEUED
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::DSGetInfo() を使用して GenTL::STREAM_INFO_NUM_QUEUED の情報を取得します。
		@~japanese	@details	GenTL::DSGetInfo() を使用して GenTL::STREAM_INFO_NUM_QUEUED の情報を取得します。
		@~japanese	@param[in] pIStDataStreamInfoHandle	IStDataStreamInfo インターフェースハンドル
		@~japanese	@param[out]	pnCount	STREAM_INFO_NUM_QUEUED
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStDataStreamInfo_GetNumQueued_t)(const PStApiHandle_t pIStDataStreamInfoHandle, size_t *pnCount);

	/*!
		@~english	@brief	GenTL::DSGetInfo() is used to get the value of GenTL::STREAM_INFO_NUM_AWAIT_DELIVERY.
		@~english	@details	GenTL::DSGetInfo() is used to get the value of GenTL::STREAM_INFO_NUM_AWAIT_DELIVERY.
		@~english	@param[in] pIStDataStreamInfoHandle	IStDataStreamInfo interface handle.
		@~english	@param[out]	pnCount	STREAM_INFO_NUM_AWAIT_DELIVERY
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::DSGetInfo() を使用して GenTL::STREAM_INFO_NUM_AWAIT_DELIVERY の情報を取得します。
		@~japanese	@details	GenTL::DSGetInfo() を使用して GenTL::STREAM_INFO_NUM_AWAIT_DELIVERY の情報を取得します。
		@~japanese	@param[in] pIStDataStreamInfoHandle	IStDataStreamInfo インターフェースハンドル
		@~japanese	@param[out]	pnCount	STREAM_INFO_NUM_AWAIT_DELIVERY
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStDataStreamInfo_GetNumAwaitDelivery_t)(const PStApiHandle_t pIStDataStreamInfoHandle, size_t *pnCount);

	/*!
		@~english	@brief	GenTL::DSGetInfo() is used to get the value of GenTL::STREAM_INFO_NUM_STARTED.
		@~english	@details	GenTL::DSGetInfo() is used to get the value of GenTL::STREAM_INFO_NUM_STARTED.
		@~english	@param[in] pIStDataStreamInfoHandle	IStDataStreamInfo interface handle.
		@~english	@param[out]	pnCount	STREAM_INFO_NUM_STARTED
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::DSGetInfo() を使用して GenTL::STREAM_INFO_NUM_STARTED の情報を取得します。
		@~japanese	@details	GenTL::DSGetInfo() を使用して GenTL::STREAM_INFO_NUM_STARTED の情報を取得します。
		@~japanese	@param[in] pIStDataStreamInfoHandle	IStDataStreamInfo インターフェースハンドル
		@~japanese	@param[out]	pnCount	STREAM_INFO_NUM_STARTED
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStDataStreamInfo_GetNumStarted_t)(const PStApiHandle_t pIStDataStreamInfoHandle, uint64_t *pnCount);

	/*!
		@~english	@brief	GenTL::DSGetInfo() is used to get the value of GenTL::STREAM_INFO_PAYLOAD_SIZE.
		@~english	@details	GenTL::DSGetInfo() is used to get the value of GenTL::STREAM_INFO_PAYLOAD_SIZE.
		@~english	@param[in] pIStDataStreamInfoHandle	IStDataStreamInfo interface handle.
		@~english	@param[out]	pnCount	STREAM_INFO_PAYLOAD_SIZE
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::DSGetInfo() を使用して GenTL::STREAM_INFO_PAYLOAD_SIZE の情報を取得します。
		@~japanese	@details	GenTL::DSGetInfo() を使用して GenTL::STREAM_INFO_PAYLOAD_SIZE の情報を取得します。
		@~japanese	@param[in] pIStDataStreamInfoHandle	IStDataStreamInfo インターフェースハンドル
		@~japanese	@param[out]	pnCount	STREAM_INFO_PAYLOAD_SIZE
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStDataStreamInfo_GetPayloadSize_t)(const PStApiHandle_t pIStDataStreamInfoHandle, size_t *pnCount);

	/*!
		@~english	@brief	GenTL::DSGetInfo() is used to get the value of GenTL::STREAM_INFO_IS_GRABBING.
		@~english	@details	GenTL::DSGetInfo() is used to get the value of GenTL::STREAM_INFO_IS_GRABBING.
		@~english	@param[in] pIStDataStreamInfoHandle	IStDataStreamInfo interface handle.
		@~english	@param[out]	pbGrabbing	STREAM_INFO_IS_GRABBING
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::DSGetInfo() を使用して GenTL::STREAM_INFO_IS_GRABBING の情報を取得します。
		@~japanese	@details	GenTL::DSGetInfo() を使用して GenTL::STREAM_INFO_IS_GRABBING の情報を取得します。
		@~japanese	@param[in] pIStDataStreamInfoHandle	IStDataStreamInfo インターフェースハンドル
		@~japanese	@param[out]	pbGrabbing	STREAM_INFO_IS_GRABBING
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStDataStreamInfo_IsGrabbing_t)(const PStApiHandle_t pIStDataStreamInfoHandle, bool8_t *pbGrabbing);

	/*!
		@~english	@brief	GenTL::DSGetInfo() is used to get the value of GenTL::STREAM_INFO_DEFINES_PAYLOADSIZE.
		@~english	@details	GenTL::DSGetInfo() is used to get the value of GenTL::STREAM_INFO_DEFINES_PAYLOADSIZE.
		@~english	@param[in] pIStDataStreamInfoHandle	IStDataStreamInfo interface handle.
		@~english	@param[out]	pbEnable	STREAM_INFO_DEFINES_PAYLOADSIZE
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::DSGetInfo() を使用して GenTL::STREAM_INFO_DEFINES_PAYLOADSIZE の情報を取得します。
		@~japanese	@details	GenTL::DSGetInfo() を使用して GenTL::STREAM_INFO_DEFINES_PAYLOADSIZE の情報を取得します。
		@~japanese	@param[in] pIStDataStreamInfoHandle	IStDataStreamInfo インターフェースハンドル
		@~japanese	@param[out]	pbEnable	STREAM_INFO_DEFINES_PAYLOADSIZE
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStDataStreamInfo_GetDefinesPayloadSize_t)(const PStApiHandle_t pIStDataStreamInfoHandle, bool8_t *pbEnable);

	/*!
		@~english	@brief	GenTL::DSGetInfo() is used to get the value of GenTL::STREAM_INFO_TLTYPE.
		@~english	@details	GenTL::DSGetInfo() is used to get the value of GenTL::STREAM_INFO_TLTYPE.
		@~english	@param[in] pIStDataStreamInfoHandle	IStDataStreamInfo interface handle.
		@~english	@param[in,out] szText	STREAM_INFO_TLTYPE.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::DSGetInfo() を使用して GenTL::STREAM_INFO_TLTYPE の情報を取得します。
		@~japanese	@details	GenTL::DSGetInfo() を使用して GenTL::STREAM_INFO_TLTYPE の情報を取得します。
		@~japanese	@param[in] pIStDataStreamInfoHandle	IStDataStreamInfo インターフェースハンドル
		@~japanese	@param[in,out] szText	STREAM_INFO_TLTYPE
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStDataStreamInfo_GetTLTypeA_t)(const PStApiHandle_t pIStDataStreamInfoHandle, char *szText, size_t *pnLen);

	/*!
		@~english	@brief	GenTL::DSGetInfo() is used to get the value of GenTL::STREAM_INFO_NUM_CHUNKS_MAX.
		@~english	@details	GenTL::DSGetInfo() is used to get the value of GenTL::STREAM_INFO_NUM_CHUNKS_MAX.
		@~english	@param[in] pIStDataStreamInfoHandle	IStDataStreamInfo interface handle.
		@~english	@param[out]	pnCount		STREAM_INFO_NUM_CHUNKS_MAX
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::DSGetInfo() を使用して GenTL::STREAM_INFO_NUM_CHUNKS_MAX の情報を取得します。
		@~japanese	@details	GenTL::DSGetInfo() を使用して GenTL::STREAM_INFO_NUM_CHUNKS_MAX の情報を取得します。
		@~japanese	@param[in] pIStDataStreamInfoHandle	IStDataStreamInfo インターフェースハンドル
		@~japanese	@param[out]	pnCount	STREAM_INFO_NUM_CHUNKS_MAX
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStDataStreamInfo_GetNumChunksMax_t)(const PStApiHandle_t pIStDataStreamInfoHandle, size_t *pnCount);

	/*!
		@~english	@brief	GenTL::DSGetInfo() is used to get the value of GenTL::STREAM_INFO_BUF_ANNOUNCE_MIN.
		@~english	@details	GenTL::DSGetInfo() is used to get the value of GenTL::STREAM_INFO_BUF_ANNOUNCE_MIN.
		@~english	@param[in] pIStDataStreamInfoHandle	IStDataStreamInfo interface handle.
		@~english	@param[out]	pnCount	STREAM_INFO_BUF_ANNOUNCE_MIN
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::DSGetInfo() を使用して GenTL::STREAM_INFO_BUF_ANNOUNCE_MIN の情報を取得します。
		@~japanese	@details	GenTL::DSGetInfo() を使用して GenTL::STREAM_INFO_BUF_ANNOUNCE_MIN の情報を取得します。
		@~japanese	@param[in] pIStDataStreamInfoHandle	IStDataStreamInfo インターフェースハンドル
		@~japanese	@param[out]	pnCount	STREAM_INFO_BUF_ANNOUNCE_MIN
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStDataStreamInfo_GetBufAnnounceMin_t)(const PStApiHandle_t pIStDataStreamInfoHandle, size_t *pnCount);

	/*!
		@~english	@brief	GenTL::DSGetInfo() is used to get the value of GenTL::STREAM_INFO_BUF_ALIGNMENT.
		@~english	@details	GenTL::DSGetInfo() is used to get the value of GenTL::STREAM_INFO_BUF_ALIGNMENT.
		@~english	@param[in] pIStDataStreamInfoHandle	IStDataStreamInfo interface handle.
		@~english	@param[out]	pnCount	STREAM_INFO_BUF_ALIGNMENT
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::DSGetInfo() を使用して GenTL::STREAM_INFO_BUF_ALIGNMENT の情報を取得します。
		@~japanese	@details	GenTL::DSGetInfo() を使用して GenTL::STREAM_INFO_BUF_ALIGNMENT の情報を取得します。
		@~japanese	@param[in] pIStDataStreamInfoHandle	IStDataStreamInfo インターフェースハンドル
		@~japanese	@param[out]	pnCount	STREAM_INFO_BUF_ALIGNMENT
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStDataStreamInfo_GetBufAlignment_t)(const PStApiHandle_t pIStDataStreamInfoHandle, size_t *pnCount);

	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStDataStreamInfo_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IStDataStreamInfo.
		@~english	@details	This structure holds the address of the C language wrapper function of IStDataStreamInfo.
		@~japanese	@brief	この構造体は IStDataStreamInfo のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IStDataStreamInfo のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_IStDataStreamInfo_Functions_t
	{
		/*!
			@copydoc PStApiTL_IStDataStreamInfo_GetIDA_t()
		*/
		PStApiTL_IStDataStreamInfo_GetIDA_t	GetIDA;

		/*!
			@copydoc PStApiTL_IStDataStreamInfo_GetNumDelivered_t()
		*/
		PStApiTL_IStDataStreamInfo_GetNumDelivered_t	GetNumDelivered;

		/*!
			@copydoc PStApiTL_IStDataStreamInfo_GetNumUnderrun_t()
		*/
		PStApiTL_IStDataStreamInfo_GetNumUnderrun_t	GetNumUnderrun;

		/*!
			@copydoc PStApiTL_IStDataStreamInfo_GetNumAnnounced_t()
		*/
		PStApiTL_IStDataStreamInfo_GetNumAnnounced_t	GetNumAnnounced;

		/*!
			@copydoc PStApiTL_IStDataStreamInfo_GetNumQueued_t()
		*/
		PStApiTL_IStDataStreamInfo_GetNumQueued_t	GetNumQueued;

		/*!
			@copydoc PStApiTL_IStDataStreamInfo_GetNumAwaitDelivery_t()
		*/
		PStApiTL_IStDataStreamInfo_GetNumAwaitDelivery_t	GetNumAwaitDelivery;

		/*!
			@copydoc PStApiTL_IStDataStreamInfo_GetNumStarted_t()
		*/
		PStApiTL_IStDataStreamInfo_GetNumStarted_t	GetNumStarted;

		/*!
			@copydoc PStApiTL_IStDataStreamInfo_GetPayloadSize_t()
		*/
		PStApiTL_IStDataStreamInfo_GetPayloadSize_t	GetPayloadSize;

		/*!
			@copydoc PStApiTL_IStDataStreamInfo_IsGrabbing_t()
		*/
		PStApiTL_IStDataStreamInfo_IsGrabbing_t	IsGrabbing;

		/*!
			@copydoc PStApiTL_IStDataStreamInfo_GetDefinesPayloadSize_t()
		*/
		PStApiTL_IStDataStreamInfo_GetDefinesPayloadSize_t	GetDefinesPayloadSize;

		/*!
			@copydoc PStApiTL_IStDataStreamInfo_GetTLTypeA_t()
		*/
		PStApiTL_IStDataStreamInfo_GetTLTypeA_t	GetTLTypeA;

		/*!
			@copydoc PStApiTL_IStDataStreamInfo_GetNumChunksMax_t()
		*/
		PStApiTL_IStDataStreamInfo_GetNumChunksMax_t	GetNumChunksMax;

		/*!
			@copydoc PStApiTL_IStDataStreamInfo_GetBufAnnounceMin_t()
		*/
		PStApiTL_IStDataStreamInfo_GetBufAnnounceMin_t	GetBufAnnounceMin;

		/*!
			@copydoc PStApiTL_IStDataStreamInfo_GetBufAlignment_t()
		*/
		PStApiTL_IStDataStreamInfo_GetBufAlignment_t	GetBufAlignment;
	}StApi_IStDataStreamInfo_Functions_t, *PStApi_IStDataStreamInfo_Functions_t;

	/*************************************************************************/
	/* StApi::IStDataStream */
	/*************************************************************************/
	/*!
		@~english	@brief	Release object.
		@~english	@details	Release object.
		@~english	@param[in] pIStDataStreamHandle	IStDataStream interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	解放します。
		@~japanese	@details	解放します。
		@~japanese	@param[in] pIStDataStreamHandle	IStDataStream インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStDataStream_Release_t)(PStApiHandle_t pIStDataStreamHandle);

	/*!
		@~english	@brief	Register a callback function.
		@~english	@details	Register a callback function.
		@~english	@param[in] pIStDataStreamHandle	IStDataStream interface handle.
		@~english	@param[in]	pFunc	Callback function pointer.
		@~english	@param[in]	pContext	Argument for the callback function.
		@~english	@param[in,out] pIStRegisteredCallbackHandle	IStRegisteredCallback Interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	コールバック関数を登録します。
		@~japanese	@details	コールバック関数を登録します。
		@~japanese	@param[in] pIStDataStreamHandle	IStDataStream インターフェースハンドル
		@~japanese	@param[in]	pFunc	コールバック関数として使用する関数
		@~japanese	@param[in]	pContext	コールバック関数に渡されるユーザー用パラメータ
		@~japanese	@param[in,out] pIStRegisteredCallbackHandle	IStRegisteredCallback インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStDataStream_RegisterCallback_t)(const PStApiHandle_t pIStDataStreamHandle, fStCallbackFunc_t *pFunc, void* pContext, PStApiHandle_t pIStRegisteredCallbackHandle);

	/*!
		@~english	@brief	Start the event handling thread.
		@~english	@details	Start the event handling thread.
		@~english	@param[in] pIStDataStreamHandle	IStDataStream interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	イベント取得用スレッドを起動します。
		@~japanese	@details	イベント取得用スレッドを起動します。
		@~japanese	@param[in] pIStDataStreamHandle	IStDataStream インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStDataStream_StartEventAcquisitionThread_t)(const PStApiHandle_t pIStDataStreamHandle);

	/*!
		@~english	@brief	Stop the event handling thread.
		@~english	@details	Stop the event handling thread.
		@~english	@param[in] pIStDataStreamHandle	IStDataStream interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	イベント取得用スレッドを停止します。
		@~japanese	@details	イベント取得用スレッドを停止します。
		@~japanese	@param[in] pIStDataStreamHandle	IStDataStream インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStDataStream_StopEventAcquisitionThread_t)(const PStApiHandle_t pIStDataStreamHandle);

	/*!
		@~english	@brief	Acquire IStDevice handle.
		@~english	@details	Acquire IStDevice handle.
		@~english	@param[in] pIStDataStreamHandle	IStDataStream interface handle.
		@~english	@param[in,out] pIStDeviceHandle	IStDevice Interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStDevice インターフェースハンドルを取得します。
		@~japanese	@details	IStDevice インターフェースハンドルを取得します。
		@~japanese	@param[in] pIStDataStreamHandle	IStDataStream インターフェースハンドル
		@~japanese	@param[in,out] pIStDeviceHandle	IStDevice インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStDataStream_GetIStDevice_t)(const PStApiHandle_t pIStDataStreamHandle, PStApiHandle_t pIStDeviceHandle);

	/*!
		@~english	@brief	Acquire interface handle of IStPort.
		@~english	@details	Acquire interface handle of IStPort.
		@~english	@param[in] pIStDataStreamHandle	IStDataStream interface handle.
		@~english	@param[in,out] pIStPortHandle	IStPort Interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStPort インターフェースハンドルを取得します。
		@~japanese	@details	IStPort インターフェースハンドルを取得します。
		@~japanese	@param[in] pIStDataStreamHandle	IStDataStream インターフェースハンドル
		@~japanese	@param[in,out] pIStPortHandle	IStPort インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStDataStream_GetIStPort_t)(const PStApiHandle_t pIStDataStreamHandle, PStApiHandle_t pIStPortHandle);

	/*!
		@~english	@brief	Acquire interface handle of IStDataStreamInfo.
		@~english	@details	Acquire interface handle of IStDataStreamInfo.
		@~english	@param[in] pIStDataStreamHandle	IStDataStream interface handle.
		@~english	@param[in,out] pIStDataStreamInfoHandle	IStDataStreamInfo Interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStDataStreamInfo インターフェースハンドルを取得します。
		@~japanese	@details	IStDataStreamInfo インターフェースハンドルを取得します。
		@~japanese	@param[in] pIStDataStreamHandle	IStDataStream インターフェースハンドル
		@~japanese	@param[in,out] pIStDataStreamInfoHandle	IStDataStreamInfo インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStDataStream_GetIStDataStreamInfo_t)(const PStApiHandle_t pIStDataStreamHandle, PStApiHandle_t pIStDataStreamInfoHandle);

	/*!
		@~english	@brief	Acquire the counts of stream buffer.
		@~english	@details	Acquire the counts of stream buffer.
		@~english	@param[in] pIStDataStreamHandle	IStDataStream interface handle.
		@~english	@param[out] pnCount	The counts of stream buffer.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ストリーミング時に作成されるバッファの数を取得します。
		@~japanese	@details	ストリーミング時に作成されるバッファの数を取得します。
		@~japanese	@param[in] pIStDataStreamHandle	IStDataStream インターフェースハンドル
		@~japanese	@param[out] pnCount	ストリーミング時に作成されるバッファの数
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStDataStream_GetStreamBufferCount_t)(const PStApiHandle_t pIStDataStreamHandle, size_t *pnCount);

	/*!
		@~english	@brief	Set the counts of stream buffer.
		@~english	@details	Set the counts of stream buffer.
		@~english	@param[in] pIStDataStreamHandle	IStDataStream interface handle.
		@~english	@param[in]	nCount	Counts of stream buffer.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ストリーミング時に作成されるバッファの数を設定します。
		@~japanese	@details	ストリーミング時に作成されるバッファの数を設定します。
		@~japanese	@param[in] pIStDataStreamHandle	IStDataStream インターフェースハンドル
		@~japanese	@param[in]	nCount	ストリーミング時に作成されるバッファの数
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStDataStream_SetStreamBufferCount_t)(const PStApiHandle_t pIStDataStreamHandle, size_t nCount);

	/*!
		@~english	@brief	Acquire a buffer handle of IStStreamBufferReleasable from a completed transfer buffer.
		@~english	@details	Acquire a buffer handle of IStStreamBufferReleasable from a completed transfer buffer.
		@~english	@attention	Call IStStreamBuffer->Release(pIStStreamBufferHandle) when acquired buffer is no longer needed. This will release the acquired buffer back to receive buffer list.
		@~english	@param[in] pIStDataStreamHandle	IStDataStream interface handle.
		@~english	@param[in]	nTimeoutTime	Indicate the timeout of waiting for transfer finish (0xFFFFFFFF:Infinity).
		@~english	@param[in,out]	pIStStreamBufferHandle	IStStreamBuffer Buffer handle. NULL if timeout occurred.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	転送が完了したバッファ用の IStStreamBufferReleasable インターフェースハンドルを取得します。
		@~japanese	@details	転送が完了したバッファ用の IStStreamBufferReleasable インターフェースハンドルを取得します。
		@~japanese	@attention	取得したバッファが不要になったらバッファが転送バッファとして再利用されるように IStStreamBuffer->Release(pIStStreamBufferHandle) を呼び出してください。
		@~japanese	@param[in] pIStDataStreamHandle	IStDataStream インターフェースハンドル
		@~japanese	@param[in]	nTimeoutTime	転送の完了を待機する時間[ms]を指定します。0xFFFFFFFFを指定すると無限に待機します。
		@~japanese	@param[in,out]	pIStStreamBufferHandle	IStStreamBuffer インターフェースハンドル。引数に StTimeoutHandling_Return が指定されタイムアウトが発生した場合は、 NULL が返されます。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStDataStream_RetrieveBuffer_t)(const PStApiHandle_t pIStDataStreamHandle, uint32_t nTimeoutTime, PStApiHandle_t pIStStreamBufferHandle);

	/*!
		@~english	@brief	Start the data acquisition from host side.
		@~english	@details	Start the data acquisition from host side.
		@~english	@attention	Additional IStDevice::AcquisitionStart() call is required for the device to send the data out. To stop data acquisition, call StopAcquisition().
		@~english	@param[in] pIStDataStreamHandle	IStDataStream interface handle.
		@~english	@param[in]	nNumToAcquire	Number of acquisition (set to GenTL::GENTL_INFINITE for infinity acquisition). The acquisition will stop after reaching this number. Nevertheless, StopAcquisition() is still needed to end the image acquisition.
		@~english	@param[in]	eAcqStartFlags	A start flags for the acquisition engine.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ホスト側のデータ取得を開始します。
		@~japanese	@details	ホスト側のデータ取得を開始します。
		@~japanese	@attention	別途 IStDevice::AcquisitionStart() を呼び出してデバイス(カメラ)側のデータ送信を開始する必要があります。停止する場合は StopAcquisition() を呼び出します。
		@~japanese	@param[in] pIStDataStreamHandle	IStDataStream インターフェースハンドル
		@~japanese	@param[in]	nNumToAcquire	取得するバッファの数を指定します( GenTL::GENTL_INFINITE を指定すると無限)。指定した数のバッファを取得した場合も別途 StopAcquisition() の呼び出しが必要になります。
		@~japanese	@param[in]	eAcqStartFlags	取り込み開始フラグ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStDataStream_StartAcquisition_t)(const PStApiHandle_t pIStDataStreamHandle, uint64_t nNumToAcquire, ACQ_START_FLAGS eAcqStartFlags);

	/*!
		@~english	@brief	Stop the data acquisition from host side.
		@~english	@details	Stop the data acquisition from host side.
		@~english	@attention	Additional IStDevice::AcquisitionStop() call is required for the device to stop sending the data out.
		@~english	@param[in] pIStDataStreamHandle	IStDataStream interface handle.
		@~english	@param[in]	eAcqStopFlags	A stop flags for the acquisition engine.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ホスト側のデータ取得を停止します。
		@~japanese	@details	ホスト側のデータ取得を停止します。
		@~japanese	@attention	予め IStDevice::AcquisitionStop() を呼び出してデバイス(カメラ)側のデータ送信を停止する必要があります。
		@~japanese	@param[in] pIStDataStreamHandle	IStDataStream インターフェースハンドル
		@~japanese	@param[in]	eAcqStopFlags	取り込み停止フラグ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStDataStream_StopAcquisition_t)(const PStApiHandle_t pIStDataStreamHandle, ACQ_STOP_FLAGS eAcqStopFlags);

	/*!
		@~english	@brief	Check if data acquisition is on going.
		@~english	@details	    Check if data acquisition is on going.
		@~english	@attention	Note that even if IStDataStreamInfo::IsGrabbing() is false, if IStDataStreamInfo::GetNumAwaitDelivery() is larger than 0 this will still return true.
		@~english	@param[in] pIStDataStreamHandle	IStDataStream interface handle.
		@~english	@param[out] pIsGrabbing		Return true if data acquisition from the device(camera) is on going.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	デバイス(カメラ)からデータを取得中か否かを確認します。
		@~japanese	@details	デバイス(カメラ)からデータを取得中か否かを確認します。
		@~japanese	@attention	IStDataStreamInfo::IsGrabbing() が false でも、IStDataStreamInfo::GetNumAwaitDelivery() が0より大きい場合は true が返されます。
		@~japanese	@param[in] pIStDataStreamHandle	IStDataStream インターフェースハンドル
		@~japanese	@param[out] pIsGrabbing		デバイス(カメラ)からデータを取得中の場合 true が返されます。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStDataStream_IsGrabbing_t)(const PStApiHandle_t pIStDataStreamHandle, bool8_t *pIsGrabbing);

	/*!
		@~english	@brief	Get the current frame rate.
		@~english	@details	Get the current frame rate
		@~english	@attention	In v1.0.1 only payload containing image data was counted. Since v1.0.2 all payload including chunk without image data is counted. 
		@~english	@param[in] pIStDataStreamHandle	IStDataStream interface handle.
		@~english	@param[out] pdblFPS		Frame rate value [fps].
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	現在のフレーム(ブロック)レートを取得します。
		@~japanese	@details	現在のフレーム(ブロック)レートを取得します。
		@~japanese	@attention	v1.0.1では画像データが含まれたペイロードデータ(ブロック)のみがカウントされておりましたが、v1.0.2以降ではすべてのペイロードデータ(ブロック)がカウントされます。
		@~japanese	@param[in] pIStDataStreamHandle	IStDataStream インターフェースハンドル
		@~japanese	@param[out] pdblFPS			フレーム(ブロック)レート[fps]
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStDataStream_GetCurrentFPS_t)(const PStApiHandle_t pIStDataStreamHandle, double *pdblFPS);

	/*!
		@~english	@brief	Get the current data rate.
		@~english	@details	Get the current data rate.
		@~english	@attention	The payload data excluding the leader, trailer, and event data is counted. Thus the value will be lower than the real data rate.
		@~english	@param[in] pIStDataStreamHandle	IStDataStream interface handle.
		@~english	@param[out] pdblBPS			Value of data rate [bytes/s].
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	現在のデータレートを取得します。
		@~japanese	@details	現在のデータレートを取得します。
		@~japanese	@attention	ペイロードデータのみが対象となり、リーダー、トレイラーおよびイベントデータなどはカウントされないため、実際のデータレートよりも低い値になります。
		@~japanese	@param[in] pIStDataStreamHandle	IStDataStream インターフェースハンドル
		@~japanese	@param[out] pdblBPS			データレート[bytes/s]
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStDataStream_GetCurrentBPS_t)(const PStApiHandle_t pIStDataStreamHandle, double *pdblBPS);

	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStDataStream_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IStDataStream.
		@~english	@details	This structure holds the address of the C language wrapper function of IStDataStream.
		@~japanese	@brief	この構造体は IStDataStream のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IStDataStream のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_IStDataStream_Functions_t
	{
		/*!
			@copydoc PStApiTL_IStDataStream_Release_t()
		*/
		PStApiTL_IStDataStream_Release_t	Release;
		
		/*!
			@copydoc PStApiTL_IStDataStream_RegisterCallback_t()
		*/
		PStApiTL_IStDataStream_RegisterCallback_t	RegisterCallback;
		
		/*!
			@copydoc PStApiTL_IStDataStream_StartEventAcquisitionThread_t()
		*/
		PStApiTL_IStDataStream_StartEventAcquisitionThread_t	StartEventAcquisitionThread;

		/*!
			@copydoc PStApiTL_IStDataStream_StopEventAcquisitionThread_t()
		*/
		PStApiTL_IStDataStream_StopEventAcquisitionThread_t	StopEventAcquisitionThread;

		/*!
			@copydoc PStApiTL_IStDataStream_GetIStDevice_t()
		*/
		PStApiTL_IStDataStream_GetIStDevice_t	GetIStDevice;

		/*!
			@copydoc PStApiTL_IStDataStream_GetIStPort_t()
		*/
		PStApiTL_IStDataStream_GetIStPort_t	GetIStPort;

		/*!
			@copydoc PStApiTL_IStDataStream_GetIStDataStreamInfo_t()
		*/
		PStApiTL_IStDataStream_GetIStDataStreamInfo_t	GetIStDataStreamInfo;

		/*!
			@copydoc PStApiTL_IStDataStream_GetStreamBufferCount_t()
		*/
		PStApiTL_IStDataStream_GetStreamBufferCount_t	GetStreamBufferCount;

		/*!
			@copydoc PStApiTL_IStDataStream_SetStreamBufferCount_t()
		*/
		PStApiTL_IStDataStream_SetStreamBufferCount_t	SetStreamBufferCount;

		/*!
			@copydoc PStApiTL_IStDataStream_RetrieveBuffer_t()
		*/
		PStApiTL_IStDataStream_RetrieveBuffer_t	RetrieveBuffer;

		/*!
			@copydoc PStApiTL_IStDataStream_StartAcquisition_t()
		*/
		PStApiTL_IStDataStream_StartAcquisition_t	StartAcquisition;

		/*!
			@copydoc PStApiTL_IStDataStream_StopAcquisition_t()
		*/
		PStApiTL_IStDataStream_StopAcquisition_t	StopAcquisition;

		/*!
			@copydoc PStApiTL_IStDataStream_IsGrabbing_t()
		*/
		PStApiTL_IStDataStream_IsGrabbing_t	IsGrabbing;

		/*!
			@copydoc PStApiTL_IStDataStream_GetCurrentFPS_t()
		*/
		PStApiTL_IStDataStream_GetCurrentFPS_t	GetCurrentFPS;

		/*!
			@copydoc PStApiTL_IStDataStream_GetCurrentBPS_t()
		*/
		PStApiTL_IStDataStream_GetCurrentBPS_t	GetCurrentBPS;

	}StApi_IStDataStream_Functions_t, *PStApi_IStDataStream_Functions_t;

	/*************************************************************************/
	/* StApi::IStDataStreamArray */
	/*************************************************************************/
	/*!
		@~english	@brief	Acquire a buffer handle of IStStreamBufferReleasable from a completed transfer buffer.
		@~english	@details	Acquire a buffer handle of IStStreamBufferReleasable from a completed transfer buffer.
		@~english	@attention	Call IStStreamBuffer->Release(pIStStreamBufferHandle) when acquired buffer is no longer needed. This will release the acquired buffer back to receive buffer list.
		@~english	@param[in] pIStDataStreamHandleArray	IStDataStream interface handles array.
		@~english	@param[in] nCount	Count of IStDataStream interface handles.
		@~english	@param[in]	nTimeoutTime	Indicate the timeout of waiting for transfer finish (0xFFFFFFFF:Infinity).
		@~english	@param[in,out]	pIStStreamBufferHandle	IStStreamBuffer Buffer handle. NULL if timeout occurred.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	転送が完了したバッファ用の IStStreamBufferReleasable インターフェースハンドルを取得します。
		@~japanese	@details	転送が完了したバッファ用の IStStreamBufferReleasable インターフェースハンドルを取得します。
		@~japanese	@attention	取得したバッファが不要になったらバッファが転送バッファとして再利用されるように IStStreamBuffer->Release(pIStStreamBufferHandle) を呼び出してください。
		@~japanese	@param[in] pIStDataStreamHandleArray	IStDataStream インターフェースハンドル配列
		@~japanese	@param[in] nCount	IStDataStream インターフェースハンドルの数
		@~japanese	@param[in]	nTimeoutTime	転送の完了を待機する時間[ms]を指定します。0xFFFFFFFFを指定すると無限に待機します。
		@~japanese	@param[in,out]	pIStStreamBufferHandle	IStStreamBuffer インターフェースハンドル。引数に StTimeoutHandling_Return が指定されタイムアウトが発生した場合は、 NULL が返されます。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStDataStreamArray_RetrieveBuffer_t)(const PStApiHandle_t pIStDataStreamHandleArray, size_t nCount, uint32_t nTimeoutTime, PStApiHandle_t pIStStreamBufferHandle);

	/*!
		@~english	@brief	Start the data acquisition from host side.
		@~english	@details	Start the data acquisition from host side.
		@~english	@attention	Additional IStDevice::AcquisitionStart() call is required for the device to send the data out. To stop data acquisition, call StopAcquisition().
		@~english	@param[in] pIStDataStreamHandleArray	IStDataStream interface handles array.
		@~english	@param[in] nCount	Count of IStDataStream interface handles.
		@~english	@param[in]	nNumToAcquire	Number of acquisition (set to GenTL::GENTL_INFINITE for infinity acquisition). The acquisition will stop after reaching this number. Nevertheless, StopAcquisition() is still needed to end the image acquisition.
		@~english	@param[in]	eAcqStartFlags	A start flags for the acquisition engine.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ホスト側のデータ取得を開始します。
		@~japanese	@details	ホスト側のデータ取得を開始します。
		@~japanese	@attention	別途 IStDevice::AcquisitionStart() を呼び出してデバイス(カメラ)側のデータ送信を開始する必要があります。停止する場合は StopAcquisition() を呼び出します。
		@~japanese	@param[in] pIStDataStreamHandleArray	IStDataStream インターフェースハンドル配列
		@~japanese	@param[in] nCount	IStDataStream インターフェースハンドルの数
		@~japanese	@param[in]	nNumToAcquire	取得するバッファの数を指定します( GenTL::GENTL_INFINITE を指定すると無限)。指定した数のバッファを取得した場合も別途 StopAcquisition() の呼び出しが必要になります。
		@~japanese	@param[in]	eAcqStartFlags	取り込み開始フラグ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStDataStreamArray_StartAcquisition_t)(const PStApiHandle_t pIStDataStreamHandleArray, size_t nCount, uint64_t nNumToAcquire, ACQ_START_FLAGS eAcqStartFlags);

	/*!
		@~english	@brief	Stop the data acquisition from host side.
		@~english	@details	Stop the data acquisition from host side.
		@~english	@attention	Additional IStDevice::AcquisitionStop() call is required for the device to stop sending the data out.
		@~english	@param[in] pIStDataStreamHandleArray	IStDataStream interface handles array.
		@~english	@param[in] nCount	Count of IStDataStream interface handles.
		@~english	@param[in]	eAcqStopFlags	A stop flags for the acquisition engine.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ホスト側のデータ取得を停止します。
		@~japanese	@details	ホスト側のデータ取得を停止します。
		@~japanese	@attention	予め IStDevice::AcquisitionStop() を呼び出してデバイス(カメラ)側のデータ送信を停止する必要があります。
		@~japanese	@param[in] pIStDataStreamHandleArray	IStDataStream インターフェースハンドル配列
		@~japanese	@param[in] nCount	IStDataStream インターフェースハンドルの数
		@~japanese	@param[in]	eAcqStopFlags	取り込み停止フラグ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStDataStreamArray_StopAcquisition_t)(const PStApiHandle_t pIStDataStreamHandleArray, size_t nCount, ACQ_STOP_FLAGS eAcqStopFlags);

	/*!
		@~english	@brief	Check if data acquisition is on going.
		@~english	@details	    Check if data acquisition is on going.
		@~english	@attention	Note that even if IStDataStreamInfo::IsGrabbing() is false, if IStDataStreamInfo::GetNumAwaitDelivery() is larger than 0 this will still return true.
		@~english	@param[in] pIStDataStreamHandleArray	IStDataStream interface handles array.
		@~english	@param[in] nCount	Count of IStDataStream interface handles.
		@~english	@param[out] pIsGrabbing		Return true if data acquisition from the device(camera) is on going.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	デバイス(カメラ)からデータを取得中か否かを確認します。
		@~japanese	@details	デバイス(カメラ)からデータを取得中か否かを確認します。
		@~japanese	@attention	IStDataStreamInfo::IsGrabbing() が false でも、IStDataStreamInfo::GetNumAwaitDelivery() が0より大きい場合は true が返されます。
		@~japanese	@param[in] pIStDataStreamHandleArray	IStDataStream インターフェースハンドル配列
		@~japanese	@param[in] nCount	IStDataStream インターフェースハンドルの数
		@~japanese	@param[out] pIsGrabbing		デバイス(カメラ)からデータを取得中の場合 true が返されます。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStDataStreamArray_IsGrabbingAll_t)(const PStApiHandle_t pIStDataStreamHandleArray, size_t nCount, bool8_t *pIsGrabbing);

	/*!
		@~english	@brief	Check if data acquisition is on going.
		@~english	@details	    Check if data acquisition is on going.
		@~english	@attention	Note that even if IStDataStreamInfo::IsGrabbing() is false, if IStDataStreamInfo::GetNumAwaitDelivery() is larger than 0 this will still return true.
		@~english	@param[in] pIStDataStreamHandleArray	IStDataStream interface handles array.
		@~english	@param[in] nCount	Count of IStDataStream interface handles.
		@~english	@param[out] pIsGrabbing		Return true if data acquisition from the device(camera) is on going.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	デバイス(カメラ)からデータを取得中か否かを確認します。
		@~japanese	@details	デバイス(カメラ)からデータを取得中か否かを確認します。
		@~japanese	@attention	IStDataStreamInfo::IsGrabbing() が false でも、IStDataStreamInfo::GetNumAwaitDelivery() が0より大きい場合は true が返されます。
		@~japanese	@param[in] pIStDataStreamHandleArray	IStDataStream インターフェースハンドル配列
		@~japanese	@param[in] nCount	IStDataStream インターフェースハンドルの数
		@~japanese	@param[out] pIsGrabbing		デバイス(カメラ)からデータを取得中の場合 true が返されます。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStDataStreamArray_IsGrabbingAny_t)(const PStApiHandle_t pIStDataStreamHandleArray, size_t nCount, bool8_t *pIsGrabbing);
	
	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStDataStreamArray_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of CIStDataStreamArray.
		@~english	@details	This structure holds the address of the C language wrapper function of CIStDataStreamArray.
		@~japanese	@brief	この構造体は CIStDataStreamArray のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は CIStDataStreamArray のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_IStDataStreamArray_Functions_t
	{

		/*!
			@copydoc PStApiTL_IStDataStreamArray_RetrieveBuffer_t()
		*/
		PStApiTL_IStDataStreamArray_RetrieveBuffer_t	RetrieveBuffer;

		/*!
			@copydoc PStApiTL_IStDataStreamArray_StartAcquisition_t()
		*/
		PStApiTL_IStDataStreamArray_StartAcquisition_t	StartAcquisition;

		/*!
			@copydoc PStApiTL_IStDataStreamArray_StopAcquisition_t()
		*/
		PStApiTL_IStDataStreamArray_StopAcquisition_t	StopAcquisition;

		/*!
			@copydoc PStApiTL_IStDataStreamArray_IsGrabbingAll_t()
		*/
		PStApiTL_IStDataStreamArray_IsGrabbingAll_t	IsGrabbingAll;

		/*!
			@copydoc PStApiTL_IStDataStreamArray_IsGrabbingAny_t()
		*/
		PStApiTL_IStDataStreamArray_IsGrabbingAny_t	IsGrabbingAny;
	}StApi_IStDataStreamArray_Functions_t, *PStApi_IStDataStreamArray_Functions_t;


	/*************************************************************************/
	/* StApi::IStStreamBufferInfo */
	/*************************************************************************/
	/*!
		@~english	@brief	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_BASE.
		@~english	@details	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_BASE.
		@~english	@param[in] pIStStreamBufferInfoHandle	IStStreamBufferInfo interface handle.
		@~english	@param[out] ppAddress	BUFFER_INFO_BASE data.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_BASE の情報を取得します。
		@~japanese	@details	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_BASE の情報を取得します。
		@~japanese	@param[in] pIStStreamBufferInfoHandle	IStStreamBufferInfo インターフェースハンドル
		@~japanese	@param[out] ppAddress	BUFFER_INFO_BASE データ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStStreamBufferInfo_GetBaseAddress_t)(const PStApiHandle_t pIStStreamBufferInfoHandle, void **ppAddress);

	/*!
		@~english	@brief	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_SIZE.
		@~english	@details	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_SIZE.
		@~english	@param[in] pIStStreamBufferInfoHandle	IStStreamBufferInfo interface handle.
		@~english	@param[out] pnSize	BUFFER_INFO_SIZE data.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_SIZE の情報を取得します。
		@~japanese	@details	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_SIZE の情報を取得します。
		@~japanese	@param[in] pIStStreamBufferInfoHandle	IStStreamBufferInfo インターフェースハンドル
		@~japanese	@param[out] pnSize	BUFFER_INFO_SIZE データ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStStreamBufferInfo_GetBufferSize_t)(const PStApiHandle_t pIStStreamBufferInfoHandle, size_t *pnSize);

	/*!
		@~english	@brief	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_USER_PTR.
		@~english	@details	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_USER_PTR.
		@~english	@param[in] pIStStreamBufferInfoHandle	IStStreamBufferInfo interface handle.
		@~english	@param[out] pUserPtr	BUFFER_INFO_USER_PTR data.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_USER_PTR の情報を取得します。
		@~japanese	@details	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_USER_PTR の情報を取得します。
		@~japanese	@param[in] pIStStreamBufferInfoHandle	IStStreamBufferInfo インターフェースハンドル
		@~japanese	@param[out] pUserPtr	BUFFER_INFO_USER_PTR データ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStStreamBufferInfo_GetUserPtr_t)(const PStApiHandle_t pIStStreamBufferInfoHandle, void **pUserPtr);

	/*!
		@~english	@brief	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_TIMESTAMP.
		@~english	@details	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_TIMESTAMP.
		@~english	@param[in] pIStStreamBufferInfoHandle	IStStreamBufferInfo interface handle.
		@~english	@param[out] pnTimestamp	BUFFER_INFO_TIMESTAMP data.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_TIMESTAMP の情報を取得します。
		@~japanese	@details	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_TIMESTAMP の情報を取得します。
		@~japanese	@param[in] pIStStreamBufferInfoHandle	IStStreamBufferInfo インターフェースハンドル
		@~japanese	@param[out] pnTimestamp	BUFFER_INFO_TIMESTAMP データ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStStreamBufferInfo_GetTimestamp_t)(const PStApiHandle_t pIStStreamBufferInfoHandle, uint64_t *pnTimestamp);

	/*!
		@~english	@brief	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_NEW_DATA.
		@~english	@details	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_NEW_DATA.
		@~english	@param[in] pIStStreamBufferInfoHandle	IStStreamBufferInfo interface handle.
		@~english	@param[out] pIsNewData	BUFFER_INFO_NEW_DATA data.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_NEW_DATA の情報を取得します。
		@~japanese	@details	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_NEW_DATA の情報を取得します。
		@~japanese	@param[in] pIStStreamBufferInfoHandle	IStStreamBufferInfo インターフェースハンドル
		@~japanese	@param[out] pIsNewData	BUFFER_INFO_NEW_DATA データ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStStreamBufferInfo_IsNewData_t)(const PStApiHandle_t pIStStreamBufferInfoHandle, bool8_t *pIsNewData);

	/*!
		@~english	@brief	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_IS_QUEUED.
		@~english	@details	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_IS_QUEUED.
		@~english	@param[in] pIStStreamBufferInfoHandle	IStStreamBufferInfo interface handle.
		@~english	@param[out] pIsQueued	BUFFER_INFO_IS_QUEUED data.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_IS_QUEUED の情報を取得します。
		@~japanese	@details	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_IS_QUEUED の情報を取得します。
		@~japanese	@param[in] pIStStreamBufferInfoHandle	IStStreamBufferInfo インターフェースハンドル
		@~japanese	@param[out] pIsQueued	BUFFER_INFO_IS_QUEUED データ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStStreamBufferInfo_IsQueued_t)(const PStApiHandle_t pIStStreamBufferInfoHandle, bool8_t *pIsQueued);

	/*!
		@~english	@brief	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_IS_ACQUIRING.
		@~english	@details	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_IS_ACQUIRING.
		@~english	@param[in] pIStStreamBufferInfoHandle	IStStreamBufferInfo interface handle.
		@~english	@param[out] pIsAcquiring	BUFFER_INFO_IS_ACQUIRING data.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_IS_ACQUIRING の情報を取得します。
		@~japanese	@details	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_IS_ACQUIRING の情報を取得します。
		@~japanese	@param[in] pIStStreamBufferInfoHandle	IStStreamBufferInfo インターフェースハンドル
		@~japanese	@param[out] pIsAcquiring	BUFFER_INFO_IS_ACQUIRING データ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStStreamBufferInfo_IsAcquiring_t)(const PStApiHandle_t pIStStreamBufferInfoHandle, bool8_t *pIsAcquiring);

	/*!
		@~english	@brief	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_IS_INCOMPLETE.
		@~english	@details	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_IS_INCOMPLETE.
		@~english	@param[in] pIStStreamBufferInfoHandle	IStStreamBufferInfo interface handle.
		@~english	@param[out] pIsIncomplete	BUFFER_INFO_IS_INCOMPLETE data.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_IS_INCOMPLETE の情報を取得します。
		@~japanese	@details	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_IS_INCOMPLETE の情報を取得します。
		@~japanese	@param[in] pIStStreamBufferInfoHandle	IStStreamBufferInfo インターフェースハンドル
		@~japanese	@param[out] pIsIncomplete	BUFFER_INFO_IS_INCOMPLETE データ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStStreamBufferInfo_IsIncomplete_t)(const PStApiHandle_t pIStStreamBufferInfoHandle, bool8_t *pIsIncomplete);

	/*!
		@~english	@brief	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_TLTYPE.
		@~english	@details	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_TLTYPE.
		@~english	@param[in] pIStStreamBufferInfoHandle	IStStreamBufferInfo interface handle.
		@~english	@param[in,out] szText	BUFFER_INFO_TLTYPE data.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_TLTYPE の情報を取得します。
		@~japanese	@details	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_TLTYPE の情報を取得します。
		@~japanese	@param[in] pIStStreamBufferInfoHandle	IStStreamBufferInfo インターフェースハンドル
		@~japanese	@param[in,out] szText	BUFFER_INFO_TLTYPE データ
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStStreamBufferInfo_GetTLTypeA_t)(const PStApiHandle_t pIStStreamBufferInfoHandle, char *szText, size_t *pnLen);

	/*!
		@~english	@brief	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_SIZE_FILLED.
		@~english	@details	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_SIZE_FILLED.
		@~english	@param[in] pIStStreamBufferInfoHandle	IStStreamBufferInfo interface handle.
		@~english	@param[out] pnSize	BUFFER_INFO_SIZE_FILLED data.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_SIZE_FILLED の情報を取得します。
		@~japanese	@details	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_SIZE_FILLED の情報を取得します。
		@~japanese	@param[in] pIStStreamBufferInfoHandle	IStStreamBufferInfo インターフェースハンドル
		@~japanese	@param[out] pnSize	BUFFER_INFO_SIZE_FILLED データ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStStreamBufferInfo_GetSizeFilled_t)(const PStApiHandle_t pIStStreamBufferInfoHandle, size_t *pnSize);

	/*!
		@~english	@brief	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_WIDTH.
		@~english	@details	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_WIDTH.
		@~english	@param[in] pIStStreamBufferInfoHandle	IStStreamBufferInfo interface handle.
		@~english	@param[out] pnWidth	BUFFER_INFO_WIDTH data.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_WIDTH の情報を取得します。
		@~japanese	@details	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_WIDTH の情報を取得します。
		@~japanese	@param[in] pIStStreamBufferInfoHandle	IStStreamBufferInfo インターフェースハンドル
		@~japanese	@param[out] pnWidth	BUFFER_INFO_WIDTH データ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStStreamBufferInfo_GetWidth_t)(const PStApiHandle_t pIStStreamBufferInfoHandle, size_t *pnWidth);

	/*!
		@~english	@brief	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_HEIGHT.
		@~english	@details	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_HEIGHT.
		@~english	@param[in] pIStStreamBufferInfoHandle	IStStreamBufferInfo interface handle.
		@~english	@param[out] pnHeight	BUFFER_INFO_HEIGHT data.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_HEIGHT の情報を取得します。
		@~japanese	@details	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_HEIGHT の情報を取得します。
		@~japanese	@param[in] pIStStreamBufferInfoHandle	IStStreamBufferInfo インターフェースハンドル
		@~japanese	@param[out] pnHeight	BUFFER_INFO_HEIGHT データ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStStreamBufferInfo_GetHeight_t)(const PStApiHandle_t pIStStreamBufferInfoHandle, size_t *pnHeight);

	/*!
		@~english	@brief	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_XOFFSET.
		@~english	@details	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_XOFFSET.
		@~english	@param[in] pIStStreamBufferInfoHandle	IStStreamBufferInfo interface handle.
		@~english	@param[out] pnXOffset	BUFFER_INFO_XOFFSET data.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_XOFFSET の情報を取得します。
		@~japanese	@details	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_XOFFSET の情報を取得します。
		@~japanese	@param[in] pIStStreamBufferInfoHandle	IStStreamBufferInfo インターフェースハンドル
		@~japanese	@param[out] pnXOffset	BUFFER_INFO_XOFFSET データ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStStreamBufferInfo_GetXOffset_t)(const PStApiHandle_t pIStStreamBufferInfoHandle, size_t *pnXOffset);

	/*!
		@~english	@brief	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_YOFFSET.
		@~english	@details	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_YOFFSET.
		@~english	@param[in] pIStStreamBufferInfoHandle	IStStreamBufferInfo interface handle.
		@~english	@param[out] pnYOffset	BUFFER_INFO_YOFFSET data.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_YOFFSET の情報を取得します。
		@~japanese	@details	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_YOFFSET の情報を取得します。
		@~japanese	@param[in] pIStStreamBufferInfoHandle	IStStreamBufferInfo インターフェースハンドル
		@~japanese	@param[out] pnYOffset	BUFFER_INFO_YOFFSET データ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStStreamBufferInfo_GetYOffset_t)(const PStApiHandle_t pIStStreamBufferInfoHandle, size_t *pnYOffset);

	/*!
		@~english	@brief	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_XPADDING.
		@~english	@details	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_XPADDING.
		@~english	@param[in] pIStStreamBufferInfoHandle	IStStreamBufferInfo interface handle.
		@~english	@param[out] pnXPadding	BUFFER_INFO_XPADDING data.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_XPADDING の情報を取得します。
		@~japanese	@details	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_XPADDING の情報を取得します。
		@~japanese	@param[in] pIStStreamBufferInfoHandle	IStStreamBufferInfo インターフェースハンドル
		@~japanese	@param[out] pnXPadding	BUFFER_INFO_XPADDING データ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStStreamBufferInfo_GetXPadding_t)(const PStApiHandle_t pIStStreamBufferInfoHandle, size_t *pnXPadding);

	/*!
		@~english	@brief	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_YPADDING.
		@~english	@details	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_YPADDING.
		@~english	@param[in] pIStStreamBufferInfoHandle	IStStreamBufferInfo interface handle.
		@~english	@param[out] pnYPadding	BUFFER_INFO_YPADDING data.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_YPADDING の情報を取得します。
		@~japanese	@details	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_YPADDING の情報を取得します。
		@~japanese	@param[in] pIStStreamBufferInfoHandle	IStStreamBufferInfo インターフェースハンドル
		@~japanese	@param[out] pnYPadding	BUFFER_INFO_YPADDING データ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStStreamBufferInfo_GetYPadding_t)(const PStApiHandle_t pIStStreamBufferInfoHandle, size_t *pnYPadding);

	/*!
		@~english	@brief	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_FRAMEID.
		@~english	@details	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_FRAMEID.
		@~english	@param[in] pIStStreamBufferInfoHandle	IStStreamBufferInfo interface handle.
		@~english	@param[out] piValue	BUFFER_INFO_FRAMEID data.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_FRAMEID の情報を取得します。
		@~japanese	@details	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_FRAMEID の情報を取得します。
		@~japanese	@param[in] pIStStreamBufferInfoHandle	IStStreamBufferInfo インターフェースハンドル
		@~japanese	@param[out] piValue	BUFFER_INFO_FRAMEID データ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStStreamBufferInfo_GetFrameID_t)(const PStApiHandle_t pIStStreamBufferInfoHandle, uint64_t *piValue);

	/*!
		@~english	@brief	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_IMAGEPRESENT.
		@~english	@details	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_IMAGEPRESENT.
		@~english	@param[in] pIStStreamBufferInfoHandle	IStStreamBufferInfo interface handle.
		@~english	@param[out] pIsImagePresent	BUFFER_INFO_IMAGEPRESENT data.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_IMAGEPRESENT の情報を取得します。
		@~japanese	@details	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_IMAGEPRESENT の情報を取得します。
		@~japanese	@param[in] pIStStreamBufferInfoHandle	IStStreamBufferInfo インターフェースハンドル
		@~japanese	@param[out] pIsImagePresent	BUFFER_INFO_IMAGEPRESENT データ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStStreamBufferInfo_IsImagePresent_t)(const PStApiHandle_t pIStStreamBufferInfoHandle, bool8_t *pIsImagePresent);

	/*!
		@~english	@brief	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_IMAGEOFFSET.
		@~english	@details	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_IMAGEOFFSET.
		@~english	@param[in] pIStStreamBufferInfoHandle	IStStreamBufferInfo interface handle.
		@~english	@param[out] pnOffset	BUFFER_INFO_IMAGEOFFSET data.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_IMAGEOFFSET の情報を取得します。
		@~japanese	@details	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_IMAGEOFFSET の情報を取得します。
		@~japanese	@param[in] pIStStreamBufferInfoHandle	IStStreamBufferInfo インターフェースハンドル
		@~japanese	@param[out] pnOffset	BUFFER_INFO_IMAGEOFFSET データ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStStreamBufferInfo_GetImageOffset_t)(const PStApiHandle_t pIStStreamBufferInfoHandle, size_t *pnOffset);

	/*!
		@~english	@brief	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_PAYLOADTYPE.
		@~english	@details	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_PAYLOADTYPE.
		@~english	@param[in] pIStStreamBufferInfoHandle	IStStreamBufferInfo interface handle.
		@~english	@param[out] pnType	BUFFER_INFO_PAYLOADTYPE data.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_PAYLOADTYPE の情報を取得します。
		@~japanese	@details	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_PAYLOADTYPE の情報を取得します。
		@~japanese	@param[in] pIStStreamBufferInfoHandle	IStStreamBufferInfo インターフェースハンドル
		@~japanese	@param[out] pnType	BUFFER_INFO_PAYLOADTYPE データ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStStreamBufferInfo_GetPayloadType_t)(const PStApiHandle_t pIStStreamBufferInfoHandle, size_t *pnType);

	/*!
		@~english	@brief	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_PIXELFORMAT.
		@~english	@details	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_PIXELFORMAT.
		@~english	@param[in] pIStStreamBufferInfoHandle	IStStreamBufferInfo interface handle.
		@~english	@param[out] pnPixelFormat	BUFFER_INFO_PIXELFORMAT data.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_PIXELFORMAT の情報を取得します。
		@~japanese	@details	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_PIXELFORMAT の情報を取得します。
		@~japanese	@param[in] pIStStreamBufferInfoHandle	IStStreamBufferInfo インターフェースハンドル
		@~japanese	@param[out] pnPixelFormat	BUFFER_INFO_PIXELFORMAT データ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStStreamBufferInfo_GetPixelFormat_t)(const PStApiHandle_t pIStStreamBufferInfoHandle, uint64_t *pnPixelFormat);

	/*!
		@~english	@brief	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_PIXELFORMAT_NAMESPACE.
		@~english	@details	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_PIXELFORMAT_NAMESPACE.
		@~english	@param[in] pIStStreamBufferInfoHandle	IStStreamBufferInfo interface handle.
		@~english	@param[out] pnNameSpace	BUFFER_INFO_PIXELFORMAT_NAMESPACE data.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_PIXELFORMAT_NAMESPACE の情報を取得します。
		@~japanese	@details	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_PIXELFORMAT_NAMESPACE の情報を取得します。
		@~japanese	@param[in] pIStStreamBufferInfoHandle	IStStreamBufferInfo インターフェースハンドル
		@~japanese	@param[out] pnNameSpace	BUFFER_INFO_PIXELFORMAT_NAMESPACE データ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStStreamBufferInfo_GetPixelFormatNameSpace_t)(const PStApiHandle_t pIStStreamBufferInfoHandle, uint64_t *pnNameSpace);

	/*!
		@~english	@brief	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_DELIVERED_IMAGEHEIGHT.
		@~english	@details	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_DELIVERED_IMAGEHEIGHT.
		@~english	@param[in] pIStStreamBufferInfoHandle	IStStreamBufferInfo interface handle.
		@~english	@param[out] pnHeight	BUFFER_INFO_DELIVERED_IMAGEHEIGHT data.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_DELIVERED_IMAGEHEIGHT の情報を取得します。
		@~japanese	@details	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_DELIVERED_IMAGEHEIGHT の情報を取得します。
		@~japanese	@param[in] pIStStreamBufferInfoHandle	IStStreamBufferInfo インターフェースハンドル
		@~japanese	@param[out] pnHeight	BUFFER_INFO_DELIVERED_IMAGEHEIGHT データ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStStreamBufferInfo_GetDeliveredImageHeight_t)(const PStApiHandle_t pIStStreamBufferInfoHandle, size_t *pnHeight);

	/*!
		@~english	@brief	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_DELIVERED_CHUNKPAYLOADSIZE.
		@~english	@details	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_DELIVERED_CHUNKPAYLOADSIZE.
		@~english	@param[in] pIStStreamBufferInfoHandle	IStStreamBufferInfo interface handle.
		@~english	@param[out] pnSize	BUFFER_INFO_DELIVERED_CHUNKPAYLOADSIZE data.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_DELIVERED_CHUNKPAYLOADSIZE の情報を取得します。
		@~japanese	@details	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_DELIVERED_CHUNKPAYLOADSIZE の情報を取得します。
		@~japanese	@param[in] pIStStreamBufferInfoHandle	IStStreamBufferInfo インターフェースハンドル
		@~japanese	@param[out] pnSize	BUFFER_INFO_DELIVERED_CHUNKPAYLOADSIZE データ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStStreamBufferInfo_GetDeliveredChunkPayloadSize_t)(const PStApiHandle_t pIStStreamBufferInfoHandle, size_t *pnSize);

	/*!
		@~english	@brief	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_CHUNKLAYOUTID.
		@~english	@details	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_CHUNKLAYOUTID.
		@~english	@param[in] pIStStreamBufferInfoHandle	IStStreamBufferInfo interface handle.
		@~english	@param[out] pnID	BUFFER_INFO_CHUNKLAYOUTID data.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_CHUNKLAYOUTID の情報を取得します。
		@~japanese	@details	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_CHUNKLAYOUTID の情報を取得します。
		@~japanese	@param[in] pIStStreamBufferInfoHandle	IStStreamBufferInfo インターフェースハンドル
		@~japanese	@param[out] pnID	BUFFER_INFO_CHUNKLAYOUTID データ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStStreamBufferInfo_GetChunkLayoutID_t)(const PStApiHandle_t pIStStreamBufferInfoHandle, uint64_t *pnID);

	/*!
		@~english	@brief	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_FILENAME.
		@~english	@details	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_FILENAME.
		@~english	@param[in] pIStStreamBufferInfoHandle	IStStreamBufferInfo interface handle.
		@~english	@param[in,out] szText	BUFFER_INFO_FILENAME data.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_FILENAME の情報を取得します。
		@~japanese	@details	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_FILENAME の情報を取得します。
		@~japanese	@param[in] pIStStreamBufferInfoHandle	IStStreamBufferInfo インターフェースハンドル
		@~japanese	@param[in,out] szText	BUFFER_INFO_FILENAME データ
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStStreamBufferInfo_GetFileNameA_t)(const PStApiHandle_t pIStStreamBufferInfoHandle, char *szText, size_t *pnLen);

	/*!
		@~english	@brief	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_PIXEL_ENDIANNESS.
		@~english	@details	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_PIXEL_ENDIANNESS.
		@~english	@param[in] pIStStreamBufferInfoHandle	IStStreamBufferInfo interface handle.
		@~english	@param[out] pnEndianness	BUFFER_INFO_PIXEL_ENDIANNESS data.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_PIXEL_ENDIANNESS の情報を取得します。
		@~japanese	@details	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_PIXEL_ENDIANNESS の情報を取得します。
		@~japanese	@param[in] pIStStreamBufferInfoHandle	IStStreamBufferInfo インターフェースハンドル
		@~japanese	@param[out] pnEndianness	BUFFER_INFO_PIXEL_ENDIANNESS データ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStStreamBufferInfo_GetPixelEndianness_t)(const PStApiHandle_t pIStStreamBufferInfoHandle, int32_t *pnEndianness);

	/*!
		@~english	@brief	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_DATA_SIZE.
		@~english	@details	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_DATA_SIZE.
		@~english	@param[in] pIStStreamBufferInfoHandle	IStStreamBufferInfo interface handle.
		@~english	@param[out] pnSize	BUFFER_INFO_DATA_SIZE data.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_DATA_SIZE の情報を取得します。
		@~japanese	@details	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_DATA_SIZE の情報を取得します。
		@~japanese	@param[in] pIStStreamBufferInfoHandle	IStStreamBufferInfo インターフェースハンドル
		@~japanese	@param[out] pnSize	BUFFER_INFO_DATA_SIZE データ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStStreamBufferInfo_GetDataSize_t)(const PStApiHandle_t pIStStreamBufferInfoHandle, size_t *pnSize);

	/*!
		@~english	@brief	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_TIMESTAMP_NS.
		@~english	@details	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_TIMESTAMP_NS.
		@~english	@param[in] pIStStreamBufferInfoHandle	IStStreamBufferInfo interface handle.
		@~english	@param[out] pnTimestamp	BUFFER_INFO_TIMESTAMP_NS data.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_TIMESTAMP_NS の情報を取得します。
		@~japanese	@details	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_TIMESTAMP_NS の情報を取得します。
		@~japanese	@param[in] pIStStreamBufferInfoHandle	IStStreamBufferInfo インターフェースハンドル
		@~japanese	@param[out] pnTimestamp	BUFFER_INFO_TIMESTAMP_NS データ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStStreamBufferInfo_GetTimestampNS_t)(const PStApiHandle_t pIStStreamBufferInfoHandle, uint64_t *pnTimestamp);

	/*!
		@~english	@brief	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_DATA_LARGER_THAN_BUFFER.
		@~english	@details	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_DATA_LARGER_THAN_BUFFER.
		@~english	@param[in] pIStStreamBufferInfoHandle	IStStreamBufferInfo interface handle.
		@~english	@param[out] pIsDataLarger	BUFFER_INFO_DATA_LARGER_THAN_BUFFER data.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_DATA_LARGER_THAN_BUFFER の情報を取得します。
		@~japanese	@details	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_DATA_LARGER_THAN_BUFFER の情報を取得します。
		@~japanese	@param[in] pIStStreamBufferInfoHandle	IStStreamBufferInfo インターフェースハンドル
		@~japanese	@param[out] pIsDataLarger	BUFFER_INFO_DATA_LARGER_THAN_BUFFER データ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStStreamBufferInfo_IsDataLargerThanBuffer_t)(const PStApiHandle_t pIStStreamBufferInfoHandle, bool8_t *pIsDataLarger);

	/*!
		@~english	@brief	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_CONTAINS_CHUNKDATA.
		@~english	@details	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_CONTAINS_CHUNKDATA.
		@~english	@param[in] pIStStreamBufferInfoHandle	IStStreamBufferInfo interface handle.
		@~english	@param[out] pHasChunkData	BUFFER_INFO_CONTAINS_CHUNKDATA data.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_CONTAINS_CHUNKDATA の情報を取得します。
		@~japanese	@details	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_CONTAINS_CHUNKDATA の情報を取得します。
		@~japanese	@param[in] pIStStreamBufferInfoHandle	IStStreamBufferInfo インターフェースハンドル
		@~japanese	@param[out] pHasChunkData	BUFFER_INFO_CONTAINS_CHUNKDATA データ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStStreamBufferInfo_HasChunkData_t)(const PStApiHandle_t pIStStreamBufferInfoHandle, bool8_t *pHasChunkData);

	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStStreamBufferInfo_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IStStreamBufferInfo.
		@~english	@details	This structure holds the address of the C language wrapper function of IStStreamBufferInfo.
		@~japanese	@brief	この構造体は IStStreamBufferInfo のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IStStreamBufferInfo のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_IStStreamBufferInfo_Functions_t
	{
		/* IStStreamBufferInfo */

		/*!
			@copydoc PStApiTL_IStStreamBufferInfo_GetBaseAddress_t()
		*/
		PStApiTL_IStStreamBufferInfo_GetBaseAddress_t	GetBaseAddress;

		/*!
			@copydoc PStApiTL_IStStreamBufferInfo_GetBufferSize_t()
		*/
		PStApiTL_IStStreamBufferInfo_GetBufferSize_t	GetBufferSize;

		/*!
			@copydoc PStApiTL_IStStreamBufferInfo_GetUserPtr_t()
		*/
		PStApiTL_IStStreamBufferInfo_GetUserPtr_t	GetUserPtr;

		/*!
			@copydoc PStApiTL_IStStreamBufferInfo_GetTimestamp_t()
		*/
		PStApiTL_IStStreamBufferInfo_GetTimestamp_t	GetTimestamp;

		/*!
			@copydoc PStApiTL_IStStreamBufferInfo_IsNewData_t()
		*/
		PStApiTL_IStStreamBufferInfo_IsNewData_t	IsNewData;

		/*!
			@copydoc PStApiTL_IStStreamBufferInfo_IsQueued_t()
		*/
		PStApiTL_IStStreamBufferInfo_IsQueued_t	IsQueued;

		/*!
			@copydoc PStApiTL_IStStreamBufferInfo_IsAcquiring_t()
		*/
		PStApiTL_IStStreamBufferInfo_IsAcquiring_t	IsAcquiring;

		/*!
			@copydoc PStApiTL_IStStreamBufferInfo_IsIncomplete_t()
		*/
		PStApiTL_IStStreamBufferInfo_IsIncomplete_t	IsIncomplete;

		/*!
			@copydoc PStApiTL_IStStreamBufferInfo_GetTLTypeA_t()
		*/
		PStApiTL_IStStreamBufferInfo_GetTLTypeA_t	GetTLTypeA;

		/*!
			@copydoc PStApiTL_IStStreamBufferInfo_GetSizeFilled_t()
		*/
		PStApiTL_IStStreamBufferInfo_GetSizeFilled_t	GetSizeFilled;

		/*!
			@copydoc PStApiTL_IStStreamBufferInfo_GetWidth_t()
		*/
		PStApiTL_IStStreamBufferInfo_GetWidth_t	GetWidth;

		/*!
			@copydoc PStApiTL_IStStreamBufferInfo_GetHeight_t()
		*/
		PStApiTL_IStStreamBufferInfo_GetHeight_t	GetHeight;

		/*!
			@copydoc PStApiTL_IStStreamBufferInfo_GetXOffset_t()
		*/
		PStApiTL_IStStreamBufferInfo_GetXOffset_t	GetXOffset;

		/*!
			@copydoc PStApiTL_IStStreamBufferInfo_GetYOffset_t()
		*/
		PStApiTL_IStStreamBufferInfo_GetYOffset_t	GetYOffset;

		/*!
			@copydoc PStApiTL_IStStreamBufferInfo_GetXPadding_t()
		*/
		PStApiTL_IStStreamBufferInfo_GetXPadding_t	GetXPadding;

		/*!
			@copydoc PStApiTL_IStStreamBufferInfo_GetYPadding_t()
		*/
		PStApiTL_IStStreamBufferInfo_GetYPadding_t	GetYPadding;

		/*!
			@copydoc PStApiTL_IStStreamBufferInfo_GetFrameID_t()
		*/
		PStApiTL_IStStreamBufferInfo_GetFrameID_t	GetFrameID;

		/*!
			@copydoc PStApiTL_IStStreamBufferInfo_IsImagePresent_t()
		*/
		PStApiTL_IStStreamBufferInfo_IsImagePresent_t	IsImagePresent;

		/*!
			@copydoc PStApiTL_IStStreamBufferInfo_GetImageOffset_t()
		*/
		PStApiTL_IStStreamBufferInfo_GetImageOffset_t	GetImageOffset;

		/*!
			@copydoc PStApiTL_IStStreamBufferInfo_GetPayloadType_t()
		*/
		PStApiTL_IStStreamBufferInfo_GetPayloadType_t	GetPayloadType;

		/*!
			@copydoc PStApiTL_IStStreamBufferInfo_GetPixelFormat_t()
		*/
		PStApiTL_IStStreamBufferInfo_GetPixelFormat_t	GetPixelFormat;

		/*!
			@copydoc PStApiTL_IStStreamBufferInfo_GetPixelFormatNameSpace_t()
		*/
		PStApiTL_IStStreamBufferInfo_GetPixelFormatNameSpace_t	GetPixelFormatNameSpace;

		/*!
			@copydoc PStApiTL_IStStreamBufferInfo_GetDeliveredImageHeight_t()
		*/
		PStApiTL_IStStreamBufferInfo_GetDeliveredImageHeight_t	GetDeliveredImageHeight;

		/*!
			@copydoc PStApiTL_IStStreamBufferInfo_GetDeliveredChunkPayloadSize_t()
		*/
		PStApiTL_IStStreamBufferInfo_GetDeliveredChunkPayloadSize_t	GetDeliveredChunkPayloadSize;

		/*!
			@copydoc PStApiTL_IStStreamBufferInfo_GetChunkLayoutID_t()
		*/
		PStApiTL_IStStreamBufferInfo_GetChunkLayoutID_t	GetChunkLayoutID;

		/*!
			@copydoc PStApiTL_IStStreamBufferInfo_GetFileNameA_t()
		*/
		PStApiTL_IStStreamBufferInfo_GetFileNameA_t	GetFileNameA;

		/*!
			@copydoc PStApiTL_IStStreamBufferInfo_GetPixelEndianness_t()
		*/
		PStApiTL_IStStreamBufferInfo_GetPixelEndianness_t	GetPixelEndianness;

		/*!
			@copydoc PStApiTL_IStStreamBufferInfo_GetDataSize_t()
		*/
		PStApiTL_IStStreamBufferInfo_GetDataSize_t	GetDataSize;

		/*!
			@copydoc PStApiTL_IStStreamBufferInfo_GetTimestampNS_t()
		*/
		PStApiTL_IStStreamBufferInfo_GetTimestampNS_t	GetTimestampNS;

		/*!
			@copydoc PStApiTL_IStStreamBufferInfo_IsDataLargerThanBuffer_t()
		*/
		PStApiTL_IStStreamBufferInfo_IsDataLargerThanBuffer_t	IsDataLargerThanBuffer;

		/*!
			@copydoc PStApiTL_IStStreamBufferInfo_HasChunkData_t()
		*/
		PStApiTL_IStStreamBufferInfo_HasChunkData_t	HasChunkData;
	}StApi_IStStreamBufferInfo_Functions_t, *PStApi_IStStreamBufferInfo_Functions_t;

	/*************************************************************************/
	/* StApi::IStStreamBuffer */
	/*************************************************************************/
	/*!
		@~english	@brief	Release object.
		@~english	@details	Release object.
		@~english	@param[in] pIStStreamBufferHandle	IStStreamBuffer interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	解放します。
		@~japanese	@details	解放します。
		@~japanese	@param[in] pIStStreamBufferHandle	IStStreamBuffer インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStStreamBuffer_Release_t)(PStApiHandle_t pIStStreamBufferHandle);

	/*!
		@~english	@brief	Register a callback function.
		@~english	@details	Register a callback function.
		@~english	@param[in] pIStStreamBufferHandle	IStStreamBuffer interface handle.
		@~english	@param[in]	pFunc	Callback function pointer.
		@~english	@param[in]	pContext	Argument for the callback function.
		@~english	@param[in,out] pIStRegisteredCallbackHandle	IStRegisteredCallback Interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	コールバック関数を登録します。
		@~japanese	@details	コールバック関数を登録します。
		@~japanese	@param[in] pIStStreamBufferHandle	IStStreamBuffer インターフェースハンドル
		@~japanese	@param[in]	pFunc	コールバック関数として使用する関数
		@~japanese	@param[in]	pContext	コールバック関数に渡されるユーザー用パラメータ
		@~japanese	@param[in,out] pIStRegisteredCallbackHandle	IStRegisteredCallback インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStStreamBuffer_RegisterCallback_t)(const PStApiHandle_t pIStStreamBufferHandle, fStCallbackFunc_t *pFunc, void* pContext, PStApiHandle_t pIStRegisteredCallbackHandle);

	/*!
		@~english	@brief	Start the event handling thread.
		@~english	@details	Start the event handling thread.
		@~english	@param[in] pIStStreamBufferHandle	IStStreamBuffer interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	イベント取得用スレッドを起動します。
		@~japanese	@details	イベント取得用スレッドを起動します。
		@~japanese	@param[in] pIStStreamBufferHandle	IStStreamBuffer インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStStreamBuffer_StartEventAcquisitionThread_t)(const PStApiHandle_t pIStStreamBufferHandle);

	/*!
		@~english	@brief	Stop the event handling thread.
		@~english	@details	Stop the event handling thread.
		@~english	@param[in] pIStStreamBufferHandle	IStStreamBuffer interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	イベント取得用スレッドを停止します。
		@~japanese	@details	イベント取得用スレッドを停止します。
		@~japanese	@param[in] pIStStreamBufferHandle	IStStreamBuffer インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStStreamBuffer_StopEventAcquisitionThread_t)(const PStApiHandle_t pIStStreamBufferHandle);

	/*!
		@~english	@brief	Acquire IStDataStream handle.
		@~english	@details	Acquire IStDataStream handle.
		@~english	@param[in] pIStStreamBufferHandle	IStStreamBuffer interface handle.
		@~english	@param[in,out] pIStDataStreamHandle	IStDataStream Interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStDataStream インターフェースハンドルを取得します。
		@~japanese	@details	IStDataStream インターフェースハンドルを取得します。
		@~japanese	@param[in] pIStStreamBufferHandle	IStStreamBuffer インターフェースハンドル
		@~japanese	@param[in,out] pIStDataStreamHandle	IStDataStream インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStStreamBuffer_GetIStDataStream_t)(const PStApiHandle_t pIStStreamBufferHandle, PStApiHandle_t pIStDataStreamHandle);

	/*!
		@~english	@brief	Acquire IStPort interface handle.
		@~english	@details	Acquire IStPort interface handle.
		@~english	@param[in] pIStStreamBufferHandle	IStStreamBuffer interface handle.
		@~english	@param[in,out] pIStPortHandle	IStPort Interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStPort インターフェースハンドルを取得します。
		@~japanese	@details	IStPort インターフェースハンドルを取得します。
		@~japanese	@param[in] pIStStreamBufferHandle	IStStreamBuffer インターフェースハンドル
		@~japanese	@param[in,out] pIStPortHandle	IStPort インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStStreamBuffer_GetIStPort_t)(const PStApiHandle_t pIStStreamBufferHandle, PStApiHandle_t pIStPortHandle);

	/*!
		@~english	@brief	Acquire IStStreamBufferInfo handle.
		@~english	@details	Acquire IStStreamBufferInfo handle.
		@~english	@param[in] pIStStreamBufferHandle	IStStreamBuffer interface handle.
		@~english	@param[in,out] pIStStreamBufferInfoHandle	IStStreamBufferInfo Interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStStreamBufferInfo インターフェースハンドルを取得します。
		@~japanese	@details	IStStreamBufferInfo インターフェースハンドルを取得します。
		@~japanese	@param[in] pIStStreamBufferHandle	IStStreamBuffer インターフェースハンドル
		@~japanese	@param[in,out] pIStStreamBufferInfoHandle	IStStreamBufferInfo インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStStreamBuffer_GetIStStreamBufferInfo_t)(const PStApiHandle_t pIStStreamBufferHandle, PStApiHandle_t pIStStreamBufferInfoHandle);

	/*!
		@~english	@brief	Acquire IStImage interface handle.
		@~english	@details	Acquire IStImage interface handle.
		@~english	@param[in] pIStStreamBufferHandle	IStStreamBuffer interface handle.
		@~english	@param[in,out] pIStImageHandle	IStImage Interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStImage インターフェースハンドルを取得します。
		@~japanese	@details	IStImage インターフェースハンドルを取得します。
		@~japanese	@param[in] pIStStreamBufferHandle	IStStreamBuffer インターフェースハンドル
		@~japanese	@param[in,out] pIStImageHandle	IStImage インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStStreamBuffer_GetIStImage_t)(const PStApiHandle_t pIStStreamBufferHandle, PStApiHandle_t pIStImageHandle);

	/*!
		@~english	@brief	Get INodeMap interface handle for accessing chunk data.
		@~english	@details	Get INodeMap interface handle for accessing chunk data.
		@~english	@param[in] pIStStreamBufferHandle	IStStreamBuffer interface handle.
		@~english	@param[in,out] pINodeMapHandle	GenApi::INodeMap Interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	チャンクデータ用の GenApi::INodeMap インターフェースハンドルを取得します。
		@~japanese	@details	チャンクデータ用の GenICam::INodeMap インターフェースハンドルを取得します。
		@~japanese	@param[in] pIStStreamBufferHandle	IStStreamBuffer インターフェースハンドル
		@~japanese	@param[in,out] pINodeMapHandle	GenApi::INodeMap インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStStreamBuffer_GetChunkINodeMap_t)(const PStApiHandle_t pIStStreamBufferHandle, PStApiHandle_t pINodeMapHandle);

	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStStreamBuffer_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IStStreamBuffer.
		@~english	@details	This structure holds the address of the C language wrapper function of IStStreamBuffer.
		@~japanese	@brief	この構造体は IStStreamBuffer のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IStStreamBuffer のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_IStStreamBuffer_Functions_t
	{
		/*!
			@copydoc PStApiTL_IStStreamBuffer_Release_t()
		*/
		PStApiTL_IStStreamBuffer_Release_t	Release;
		
		/*!
			@copydoc PStApiTL_IStStreamBuffer_RegisterCallback_t()
		*/
		PStApiTL_IStStreamBuffer_RegisterCallback_t	RegisterCallback;
		
		/*!
			@copydoc PStApiTL_IStStreamBuffer_StartEventAcquisitionThread_t()
		*/
		PStApiTL_IStStreamBuffer_StartEventAcquisitionThread_t	StartEventAcquisitionThread;

		/*!
			@copydoc PStApiTL_IStStreamBuffer_StopEventAcquisitionThread_t()
		*/
		PStApiTL_IStStreamBuffer_StopEventAcquisitionThread_t	StopEventAcquisitionThread;

		/*!
			@copydoc PStApiTL_IStStreamBuffer_GetIStDataStream_t()
		*/
		PStApiTL_IStStreamBuffer_GetIStDataStream_t	GetIStDataStream;

		/*!
			@copydoc PStApiTL_IStStreamBuffer_GetIStPort_t()
		*/
		PStApiTL_IStStreamBuffer_GetIStPort_t	GetIStPort;

		/*!
			@copydoc PStApiTL_IStStreamBuffer_GetIStStreamBufferInfo_t()
		*/
		PStApiTL_IStStreamBuffer_GetIStStreamBufferInfo_t	GetIStStreamBufferInfo;

		/*!
			@copydoc PStApiTL_IStStreamBuffer_GetIStImage_t()
		*/
		PStApiTL_IStStreamBuffer_GetIStImage_t	GetIStImage;

		/*!
			@copydoc PStApiTL_IStStreamBuffer_GetChunkINodeMap_t()
		*/
		PStApiTL_IStStreamBuffer_GetChunkINodeMap_t	GetChunkINodeMap;
	}StApi_IStStreamBuffer_Functions_t, *PStApi_IStStreamBuffer_Functions_t;

	/*************************************************************************/
	/* StApi::IStImage */
	/*************************************************************************/
	/*!
		@~english	@brief	Acquire the width of the image.
		@~english	@details	Acquire the width of the image.
		@~english	@param[in] pIStImageHandle	IStImage interface handle.
		@~english	@param[out] pnValue	Width of the image.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	画像の横サイズを取得します。
		@~japanese	@details	画像の横サイズを取得します。
		@~japanese	@param[in] pIStImageHandle	IStImage インターフェースハンドル
		@~japanese	@param[out] pnValue	画像の横サイズ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStImage_GetImageWidth_t)(const PStApiHandle_t pIStImageHandle, size_t *pnValue);

	/*!
		@~english	@brief	Acquire the height of the image.
		@~english	@details	Acquire the height of the image.
		@~english	@param[in] pIStImageHandle	IStImage interface handle.
		@~english	@param[out] pnValue	Height of the image.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	画像の縦サイズを取得します。
		@~japanese	@details	画像の縦サイズを取得します。
		@~japanese	@param[in] pIStImageHandle	IStImage インターフェースハンドル
		@~japanese	@param[out] pnValue	画像の縦サイズ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStImage_GetImageHeight_t)(const PStApiHandle_t pIStImageHandle, size_t *pnValue);

	/*!
		@~english	@brief	Acquire the line pitch (numbers of bytes within one line) of the image.
		@~english	@details	Acquire the line pitch (numbers of bytes within one line) of the image.
		@~english	@param[in] pIStImageHandle	IStImage interface handle.
		@~english	@param[out] pnValue	Line pitch of the image.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	画像のラインピッチ(1ライン当たりのバイト数)を取得します。
		@~japanese	@details	画像のラインピッチ(1ライン当たりのバイト数)を取得します。
		@~japanese	@param[in] pIStImageHandle	IStImage インターフェースハンドル
		@~japanese	@param[out] pnValue	画像のラインピッチ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStImage_GetImageLinePitch_t)(const PStApiHandle_t pIStImageHandle, size_t *pnValue);

	/*!
		@~english	@brief	Acquire the image plane pitch (numbers of bytes within one plane).
		@~english	@details	Acquire the image plane pitch (numbers of bytes within one plane). The plane numbers of currently supported image formats are all as 1 and the image size will be the same.
		@~english	@param[in] pIStImageHandle	IStImage interface handle.
		@~english	@param[out] pnValue	Plane pitch of the image.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	画像のプレーンあたりのバイト数を取得します。
		@~japanese	@details	画像のプレーンあたりのバイト数を取得します。現在サポートされている画像フォーマットはすべて1プレーンしかないため、画像サイズと同値になります。
		@~japanese	@param[in] pIStImageHandle	IStImage インターフェースハンドル
		@~japanese	@param[out] pnValue	画像のプレーンピッチ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStImage_GetImagePlanePitch_t)(const PStApiHandle_t pIStImageHandle, size_t *pnValue);

	/*!
		@~english	@brief	Acquire the pixel format of the image.
		@~english	@details	Acquire the pixel format of the image.
		@~english	@param[in] pIStImageHandle	IStImage interface handle.
		@~english	@param[out] pnValue	Pixel format of the image.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	画像のピクセルフォーマットを取得します。
		@~japanese	@details	画像のピクセルフォーマットを取得します。
		@~japanese	@param[in] pIStImageHandle	IStImage インターフェースハンドル
		@~japanese	@param[out] pnValue	画像のピクセルフォーマット
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStImage_GetImagePixelFormat_t)(const PStApiHandle_t pIStImageHandle, EStPixelFormatNamingConvention_t *pnValue);

	/*!
		@~english	@brief	Acquire the buffer address of the image.
		@~english	@details	Acquire the buffer address of the image.
		@~english	@param[in] pIStImageHandle	IStImage interface handle.
		@~english	@param[out] ppvValue	Buffer address of the image.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	画像バッファーのアドレスを取得します。
		@~japanese	@details	画像バッファーのアドレスを取得します。
		@~japanese	@param[in] pIStImageHandle	IStImage インターフェースハンドル
		@~japanese	@param[out] ppvValue	画像バッファーのアドレス
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStImage_GetImageBuffer_t)(const PStApiHandle_t pIStImageHandle, void **ppvValue);

	/*!
		@~english	@brief	Get user context.
		@~english	@details	Get user context.
		@~english	@param[in] pIStImageHandle	IStImage interface handle.
		@~english	@param[out] ppvValue	Return user context pointer. If there is no user context data, return NULL.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ユーザー用データポインターを取得します。
		@~japanese	@details	ユーザー用データポインターを取得します。
		@~japanese	@param[in] pIStImageHandle	IStImage インターフェースハンドル
		@~japanese	@param[out] ppvValue	ユーザー用データポインター。指定されていない場合は、NULLが返されます。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStImage_GetUserContext_t)(const PStApiHandle_t pIStImageHandle, void **ppvValue);

	/*!
		@~english	@brief	Acquire ROI data from the image data.
		@~english	@details	Acquire ROI data of from the image data. The ROI data will be acquired as a IStImage interface pointer. If the original IStImage is updated or GetROIImage is called again, the acquired ROI area image data will become invalid.
		@~english	@param[in] pIStImageHandle	IStImage interface handle.
		@~english	@param[in]	x	Horizontal offset of the image.
		@~english	@param[in]	y	Vertical offset of the image.
		@~english	@param[in]	width	Width of the ROI image.
		@~english	@param[in]	height	Height of the ROI image.
		@~english	@param[in,out] pROIIStImageHandle	IStImage interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	切り取った画像用の IStImage インターフェースハンドルを取得します。
		@~japanese	@details	切り取った画像用の IStImage インターフェースハンドルを取得します。 データのコピーは行われず、元のデータが参照されます。そのため、元の画像が変化したり、再度この関数が呼び出された場合は、以前取得された IStImage は無効になります。
		@~japanese	@param[in] pIStImageHandle	IStImage インターフェースハンドル
		@~japanese	@param[in]	x	横方向のオフセット値
		@~japanese	@param[in]	y	縦方向のオフセット値
		@~japanese	@param[in]	width	ROI画像の横サイズ
		@~japanese	@param[in]	height	ROI画像の縦サイズ
		@~japanese	@param[in,out] pROIIStImageHandle	IStImage インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStImage_GetROIImage_t)(const PStApiHandle_t pIStImageHandle, size_t x, size_t y, size_t width, size_t height, PStApiHandle_t pROIIStImageHandle);

	/*!
		@~english	@brief	Acquire pixel information.
		@~english	@details	Acquire pixel information.
		@~english	@param[in] pIStImageHandle	IStImage interface handle.
		@~english	@param[in]	x	Horizontal poisition of the image.
		@~english	@param[in]	y	Vertical poisition of the image.
		@~english	@param[in,out] pIStPixelComponentValueHandle	IStPixelComponentValue interface handle.
        @~english   @attention  When this function is called, the return value from IStPixelComponentValue interface pointer will change. The acquired IStPixelComponentValue interface pointer will be invalid if the original image is discarded.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	指定した位置の画素情報を取得します。
		@~japanese	@details	指定した位置の画素情報を取得します。
		@~japanese	@param[in] pIStImageHandle	IStImage インターフェースハンドル
		@~japanese	@param[in]	x	横方向の位置
		@~japanese	@param[in]	y	縦方向の位置
		@~japanese	@param[in,out] pIStPixelComponentValueHandle	IStPixelComponentValue インターフェースハンドル
		@~japanese	@attention	再度この関数が呼び出されると、 IStPixelComponentValue インターフェースハンドルを使用して得られる値が変化します。取得された IStPixelComponentValue インターフェースポインターは元の画像が破棄されると無効になります。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStImage_GetIStPixelComponentValue_t)(const PStApiHandle_t pIStImageHandle, size_t x, size_t y, PStApiHandle_t pIStPixelComponentValueHandle);

	/* v1.1.1  */
	/*!
		@ingroup	StApiGUI_PublicImpl
		@~english	@brief	Copy a image to clipboard.
		@~english	@details	Copy a image to clipboard.
		@~english	@attention	Image data in formats other than StPFNC_Mono8, StPFNC_BGR8, and StPFNC_BGRa8 will be copied to the clipboard after conversion. If you want to specify the conversion method, please convert to StPFNC_Mono8, StPFNC_BGR8, StPFNC_BGRa8 using IStPixelFormatConverter beforehand.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	画像データをクリップボードへコピーします。
		@~japanese	@details	画像データをクリップボードへコピーします。
		@~japanese	@attention	StPFNC_Mono8, StPFNC_BGR8, StPFNC_BGRa8 以外のフォーマットの画像データは、変換後にクリップボードへコピーされます。変換方法を指定したい場合は、あらかじめ IStPixelFormatConverter を使用して、 StPFNC_Mono8, StPFNC_BGR8, StPFNC_BGRa8 へ変換された画像データを引数に指定してください。
		@~japanese	@return	EStApiCError_t エラーコード
		@since StApi v1.1.1
	*/
	STAPI_PCALL(PStApiTL_IStImage_SetIStImageToClipboard_t)(const PStApiHandle_t pIStImageHandle);

	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStImage_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IStImage.
		@~english	@details	This structure holds the address of the C language wrapper function of IStImage.
		@~japanese	@brief	この構造体は IStImage のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IStImage のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_IStImage_Functions_t
	{
		/*!
			@copydoc PStApiTL_IStImage_GetImageWidth_t()
		*/
		PStApiTL_IStImage_GetImageWidth_t	GetImageWidth;

		/*!
			@copydoc PStApiTL_IStImage_GetImageHeight_t()
		*/
		PStApiTL_IStImage_GetImageHeight_t	GetImageHeight;

		/*!
			@copydoc PStApiTL_IStImage_GetImageLinePitch_t()
		*/
		PStApiTL_IStImage_GetImageLinePitch_t	GetImageLinePitch;

		/*!
			@copydoc PStApiTL_IStImage_GetImagePlanePitch_t()
		*/
		PStApiTL_IStImage_GetImagePlanePitch_t	GetImagePlanePitch;

		/*!
			@copydoc PStApiTL_IStImage_GetImagePixelFormat_t()
		*/
		PStApiTL_IStImage_GetImagePixelFormat_t	GetImagePixelFormat;

		/*!
			@copydoc PStApiTL_IStImage_GetImageBuffer_t()
		*/
		PStApiTL_IStImage_GetImageBuffer_t	GetImageBuffer;

		/*!
			@copydoc PStApiTL_IStImage_GetUserContext_t()
		*/
		PStApiTL_IStImage_GetUserContext_t	GetUserContext;

		/*!
			@copydoc PStApiTL_IStImage_GetROIImage_t()
		*/
		PStApiTL_IStImage_GetROIImage_t	GetROIImage;

		/*!
			@copydoc PStApiTL_IStImage_GetIStPixelComponentValue_t()
		*/
		PStApiTL_IStImage_GetIStPixelComponentValue_t	GetIStPixelComponentValue;


		/* v1.1.1 */
		/*!
			@copydoc PStApiTL_IStImage_SetIStImageToClipboard_t()
		*/
		PStApiTL_IStImage_SetIStImageToClipboard_t	SetIStImageToClipboard;

	}StApi_IStImage_Functions_t, *PStApi_IStImage_Functions_t;

	/*************************************************************************/
	/* StApi::IStImageBuffer */
	/*************************************************************************/
	/*!
		@~english	@brief	Create object for keeping image data and acquire IStImageBuffer interface handle.
		@~english	@details	Create object for keeping image data and acquire IStImageBuffer interface handle. The acquired IStImageBuffer interface handle can be assign for storing the image after processing. Call IStImageBuffer->Release(pIStImageBufferHandle) to release IStImageBuffer interface handle if it is no longer necessary.
		@~english	@param[in] pIStAllocatorHandle	IStAllocator interface handle for allocating and releasing memory. If NULL, the buffer memory allocation and deallocation are handled inside the StApi.
		@~english	@param[in,out]	pIStImageBufferHandle	IStImageBuffer interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	画像データを保持するためのオブジェクトを生成し、 IStImageBuffer インターフェースハンドルを取得します。
		@~japanese	@details	画像データを保持するためのオブジェクトを生成し、 IStImageBuffer インターフェースハンドルを取得します。オブジェクトが不要になったら IStImageBuffer->Release(pIStImageBufferHandle) を呼び出して解放してください。
		@~japanese	@param[in] pIStAllocatorHandle	IStAllocator インターフェースハンドル。画像保持用メモリーの確保および解放をカスタマイズする際に指定します。NULLが指定された場合は、StApi内部でメモリーの割り当ておよび解放を行います。
		@~english	@param[in,out]	pIStImageBufferHandle	IStImageBuffer インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStImageBuffer_CreateIStImageBuffer_t)(const PStApiHandle_t pIStAllocatorHandle, PStApiHandle_t pIStImageBufferHandle);

	/*!
		@~english	@brief	Release object.
		@~english	@details	Release object.
		@~english	@param[in] pIStImageBufferHandle	IStImageBuffer interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	解放します。
		@~japanese	@details	解放します。
		@~japanese	@param[in] pIStImageBufferHandle	IStImageBuffer interface handle.
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStImageBuffer_Release_t)(PStApiHandle_t pIStImageBufferHandle);

	/*!
		@~english	@brief	Create an image buffer based on the given parameters.
		@~english	@details      Create an image buffer based on the given parameters.
		@~english	@attention Buffers generated here are deleted automatically when you create the buffers again or when you release the IStImageBuffer interface handle.
		@~english	@param[in] pIStImageBufferHandle	IStImageBuffer interface handle.
		@~english	@param[in] nWidth	Width of image.
		@~english	@param[in] nHeight	Height of image.
		@~english	@param[in] nPixelFormat	The pixel format of the image.
		@~english	@param[in] eInitializeMemory	Assign the memory initialization method for this buffer.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	指定されたサイズ・フォーマットに従ってバッファを作成します。
		@~japanese	@details	指定されたサイズ・フォーマットに従ってバッファを作成します。
		@~japanese	@attention ここで生成されたバッファは、再度バッファを作成した際や IStImageBuffer インターフェースハンドルのRelease時に自動的に削除されます。
		@~japanese	@param[in] pIStImageBufferHandle	IStImageBuffer インターフェースハンドル
		@~japanese	@param[in] nWidth	画像の横サイズ
		@~japanese	@param[in] nHeight	画像の縦サイズ
		@~japanese	@param[in] nPixelFormat	画像のピクセルフォーマット
		@~japanese	@param[in] eInitializeMemory	バッファの初期化方法
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStImageBuffer_CreateBuffer_t)(const PStApiHandle_t pIStImageBufferHandle, size_t nWidth, size_t nHeight, EStPixelFormatNamingConvention_t nPixelFormat, EStMemoryInitialization_t eInitializeMemory);

	/*!
		@~english	@brief	Acquire IStImage interface handle.
		@~english	@details	Acquire IStImage interface handle.
		@~english	@param[in] pIStImageBufferHandle	IStImageBuffer interface handle.
		@~english	@param[in,out] pIStImageHandle	IStImage interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStImage インターフェースハンドルを取得します。
		@~japanese	@details	IStImage インターフェースハンドルを取得します。
		@~japanese	@param[in] pIStImageBufferHandle	IStImageBuffer インターフェースハンドル
		@~japanese	@param[in,out] pIStImageHandle	IStImage インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStImageBuffer_GetIStImage_t)(const PStApiHandle_t pIStImageBufferHandle, PStApiHandle_t pIStImageHandle);

	/*!
		@~english	@brief	Copy image data.
		@~english	@details	Copy image data.
		@~english	@param[in] pIStImageBufferHandle	IStImageBuffer interface handle.
		@~english	@param[in] pIStImageHandle	Source of the IStImage interface handle to be copied.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	画像データをコピーします。
		@~japanese	@details	画像データをコピーします。
		@~japanese	@param[in] pIStImageBufferHandle	IStImageBuffer インターフェースハンドル
		@~japanese	@param[in] pIStImageHandle	コピーしたい画像データ用 IStImage インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStImageBuffer_CopyImage_t)(const PStApiHandle_t pIStImageBufferHandle, PStApiHandle_t pIStImageHandle);

	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStImageBuffer_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IStImageBuffer.
		@~english	@details	This structure holds the address of the C language wrapper function of IStImageBuffer.
		@~japanese	@brief	この構造体は IStImageBuffer のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IStImageBuffer のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_IStImageBuffer_Functions_t
	{
		/*!
			@copydoc PStApiTL_IStImageBuffer_CreateIStImageBuffer_t()
		*/
		PStApiTL_IStImageBuffer_CreateIStImageBuffer_t	CreateIStImageBuffer;

		/*!
			@copydoc PStApiTL_IStImageBuffer_Release_t()
		*/
		PStApiTL_IStImageBuffer_Release_t	Release;

		/*!
			@copydoc PStApiTL_IStImageBuffer_CreateBuffer_t()
		*/
		PStApiTL_IStImageBuffer_CreateBuffer_t	CreateBuffer;

		/*!
			@copydoc PStApiTL_IStImageBuffer_GetIStImage_t()
		*/
		PStApiTL_IStImageBuffer_GetIStImage_t	GetIStImage;

		/*!
			@copydoc PStApiTL_IStImageBuffer_CopyImage_t()
		*/
		PStApiTL_IStImageBuffer_CopyImage_t	CopyImage;
	}StApi_IStImageBuffer_Functions_t, *PStApi_IStImageBuffer_Functions_t;

	/*************************************************************************/
	/* StApi::IStPixelFormatInfo */
	/*************************************************************************/
	/*!
		@~english	@brief	Acquire IStPixelFormatInfo interface handle. 
		@~english	@details	Acquire IStPixelFormatInfo interface handle. IStPixelFormatInfo interface handle is used for obtaining information related to the pixel format.
		@~english	@param[in] ePFNC	Pixel format.
		@~english	@param[in,out]	pIStPixelFormatInfoHandle	IStPixelFormatInfo interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStPixelFormatInfo インターフェースハンドルを取得します。
		@~japanese	@details	IStPixelFormatInfo インターフェースハンドルを取得します。 IStPixelFormatInfo インターフェースはピクセルフォーマット関連情報の取得に使用されます。
		@~japanese	@param[in] ePFNC	ピクセルフォーマット値
		@~english	@param[in,out]	pIStPixelFormatInfoHandle	IStPixelFormatInfo インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStPixelFormatInfo_GetIStPixelFormatInfo_t)(EStPixelFormatNamingConvention_t ePFNC, PStApiHandle_t pIStPixelFormatInfoHandle);

	/*!
		@~english	@brief	Acquire pixel format value.
		@~english	@details	Acquire pixel format value.
		@~english	@param[in] pIStPixelFormatInfoHandle	IStPixelFormatInfo interface handle.
		@~english	@param[out] pnValue	Acquire pixel format value.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ピクセルフォーマット値を取得します。
		@~japanese	@details	ピクセルフォーマット値を取得します。
		@~japanese	@param[in] pIStPixelFormatInfoHandle	IStPixelFormatInfo インターフェースハンドル
		@~japanese	@param[out] pnValue	ピクセルフォーマット値
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStPixelFormatInfo_GetValue_t)(const PStApiHandle_t pIStPixelFormatInfoHandle, EStPixelFormatNamingConvention_t *pnValue);

	/*!
		@~english	@brief	Get pixel format name.
		@~english	@details	Get pixel format name.
		@~english	@param[in] pIStPixelFormatInfoHandle	IStPixelFormatInfo interface handle.
		@~english	@param[in,out] szText	Pixel format name.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ピクセルフォーマット名を取得します。
		@~japanese	@details	ピクセルフォーマット名を取得します。
		@~japanese	@param[in] pIStPixelFormatInfoHandle	IStPixelFormatInfo インターフェースハンドル
		@~japanese	@param[in,out] szText	ピクセルフォーマット名
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStPixelFormatInfo_GetNameA_t)(const PStApiHandle_t pIStPixelFormatInfoHandle, char *szText, size_t *pnLen);

	/*!
		@~english	@brief	Get description of pixel format.
		@~english	@details	Get description of pixel format.
		@~english	@param[in] pIStPixelFormatInfoHandle	IStPixelFormatInfo interface handle.
		@~english	@param[in,out] szText	Pixel format description.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ピクセルフォーマットの説明文を取得します。
		@~japanese	@details	ピクセルフォーマットの説明文を取得します。
		@~japanese	@param[in] pIStPixelFormatInfoHandle	IStPixelFormatInfo インターフェースハンドル
		@~japanese	@param[in,out] szText	ピクセルフォーマットの説明文
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStPixelFormatInfo_GetDescriptionA_t)(const PStApiHandle_t pIStPixelFormatInfoHandle, char *szText, size_t *pnLen);
		
	/*!
		@~english	@brief	Get the total bit counts of each pixel.
		@~english	@details	Get the total bit counts of each pixel.
		@~english	@param[in] pIStPixelFormatInfoHandle	IStPixelFormatInfo interface handle.
		@~english	@param[out] pnValue	Total bit counts of each pixel.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ピクセルごとの合計ビット数を取得します。
		@~japanese	@details	ピクセルごとの合計ビット数を取得します。
		@~japanese	@param[in] pIStPixelFormatInfoHandle	IStPixelFormatInfo インターフェースハンドル
		@~japanese	@param[out] pnValue	ピクセルごとの合計ビット数
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStPixelFormatInfo_GetEachPixelTotalBitCount_t)(const PStApiHandle_t pIStPixelFormatInfoHandle, size_t *pnValue);						/* ex.BGRA12:64 */
		
	/*!
		@~english	@brief	Get the total bit counts of each component of a pixel.
		@~english	@details	Get the total bit counts of each component of a pixel.
		@~english	@param[in] pIStPixelFormatInfoHandle	IStPixelFormatInfo interface handle.
		@~english	@param[out] pnValue	Total bit counts of each component of a pixel.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	構成要素ごとの全体のビット数を取得します。
		@~japanese	@details	構成要素ごとの全体のビット数を取得します。
		@~japanese	@param[in] pIStPixelFormatInfoHandle	IStPixelFormatInfo インターフェースハンドル
		@~japanese	@param[out] pnValue	構成要素ごとの全体のビット数
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStPixelFormatInfo_GetEachComponentTotalBitCount_t)(const PStApiHandle_t pIStPixelFormatInfoHandle, size_t *pnValue);		/* ex.BGRA12:16 */

	/*!
		@~english	@brief	Get the effective bit counts of each component of a pixel.
		@~english	@details	Get the effective bit counts of each component of a pixel.
		@~english	@param[in] pIStPixelFormatInfoHandle	IStPixelFormatInfo interface handle.
		@~english	@param[out] pnValue	Effective bit counts of each component of a pixel.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	構成要素ごとの有効なビット数を取得します。
		@~japanese	@details	構成要素ごとの有効なビット数を取得します。
		@~japanese	@param[in] pIStPixelFormatInfoHandle	IStPixelFormatInfo インターフェースハンドル
		@~japanese	@param[out] pnValue	構成要素ごとの有効なビット数
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStPixelFormatInfo_GetEachComponentValidBitCount_t)(const PStApiHandle_t pIStPixelFormatInfoHandle, size_t *pnValue);	/* ex.BGRA12:12 */

	/*!
		@~english	@brief	Get the total component counts of a pixel.
		@~english	@details	Get the total component counts of a pixel.
		@~english	@param[in] pIStPixelFormatInfoHandle	IStPixelFormatInfo interface handle.
		@~english	@param[out] pnValue	Total component counts of a pixel.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ピクセルごとの構成要素の数を取得します。
		@~japanese	@details	ピクセルごとの構成要素の数を取得します。
		@~japanese	@param[in] pIStPixelFormatInfoHandle	IStPixelFormatInfo インターフェースハンドル
		@~japanese	@param[out] pnValue	ピクセルごとの構成要素の数
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStPixelFormatInfo_GetEachPixelTotalComponentCount_t)(const PStApiHandle_t pIStPixelFormatInfoHandle, size_t *pnValue);		/* ex.BGRA12:4 */

	/*!
		@~english	@brief	Get plane counts.
		@~english	@details	Get plane counts.
		@~english	@param[in] pIStPixelFormatInfoHandle	IStPixelFormatInfo interface handle.
		@~english	@param[out] pnValue	Plane counts.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	プレーン数を取得します。
		@~japanese	@details	プレーン数を取得します。
		@~japanese	@param[in] pIStPixelFormatInfoHandle	IStPixelFormatInfo インターフェースハンドル
		@~japanese	@param[out] pnValue	プレーン数
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStPixelFormatInfo_GetPlaneCount_t)(const PStApiHandle_t pIStPixelFormatInfoHandle, size_t *pnValue);

	/*!
		@~english	@brief	Get the minimum unit (in pixel) of image in horizontal.
		@~english	@details	Get the minimum unit (in pixel) of image in horizontal.
		@~english	@param[in] pIStPixelFormatInfoHandle	IStPixelFormatInfo interface handle.
		@~english	@param[out] pnValue	Minimum unit (in pixel) of image in horizontal.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	横方向の画像の最小単位を取得します。
		@~japanese	@details	横方向の画像の最小単位を取得します。
		@~japanese	@param[in] pIStPixelFormatInfoHandle	IStPixelFormatInfo インターフェースハンドル
		@~japanese	@param[out] pnValue	横方向の画像の最小単位
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStPixelFormatInfo_GetPixelIncrementX_t)(const PStApiHandle_t pIStPixelFormatInfoHandle, size_t *pnValue);					/* ex.BGRA12:1 */

	/*!
		@~english	@brief	Get the minimum unit (in pixel) of image in vertical.
		@~english	@details	Get the minimum unit (in pixel) of image in vertical.
		@~english	@param[in] pIStPixelFormatInfoHandle	IStPixelFormatInfo interface handle.
		@~english	@param[out] pnValue	Minimum unit (in pixel) of image in vertical.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	縦方向の画像の最小単位を取得します。
		@~japanese	@details	縦方向の画像の最小単位を取得します。
		@~japanese	@param[in] pIStPixelFormatInfoHandle	IStPixelFormatInfo インターフェースハンドル
		@~japanese	@param[out] pnValue	縦方向の画像の最小単位
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStPixelFormatInfo_GetPixelIncrementY_t)(const PStApiHandle_t pIStPixelFormatInfoHandle, size_t *pnValue);					/* ex.BGRA12:1 */

	/*!
		@~english	@brief	Check if the image data contains color information.
		@~english	@details	Check if the image data contains color information.
		@~english	@param[in] pIStPixelFormatInfoHandle	IStPixelFormatInfo interface handle.
		@~english	@param[out] pbValue	True if the image data contains color information.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	カラー画像かどうかを確認します。
		@~japanese	@details	カラー画像かどうかを確認します。
		@~japanese	@param[in] pIStPixelFormatInfoHandle	IStPixelFormatInfo インターフェースハンドル
		@~japanese	@param[out] pbValue	カラー画像の時 true が返されます。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStPixelFormatInfo_IsColor_t)(const PStApiHandle_t pIStPixelFormatInfoHandle, bool8_t *pbValue);

	/*!
		@~english	@brief	Check if the image data is monochrome.
		@~english	@details	Check if the image data is monochrome.
		@~english	@param[in] pIStPixelFormatInfoHandle	IStPixelFormatInfo interface handle.
		@~english	@param[out] pbValue	True if the image data is monochrome.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	モノクロ画像かどうかを確認します。
		@~japanese	@details	モノクロ画像かどうかを確認します。
		@~japanese	@param[in] pIStPixelFormatInfoHandle	IStPixelFormatInfo インターフェースハンドル
		@~japanese	@param[out] pbValue	モノクロ画像の時 true が返されます。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStPixelFormatInfo_IsMono_t)(const PStApiHandle_t pIStPixelFormatInfoHandle, bool8_t *pbValue);

	/*!
		@~english	@brief	Check if the image data is in Bayer arrangement.
		@~english	@details	Check if the image data is in Bayer arrangement.
		@~english	@param[in] pIStPixelFormatInfoHandle	IStPixelFormatInfo interface handle.
		@~english	@param[out] pbValue	True if the image data is in Bayer arrangement.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ベイヤー配列画像かどうかを確認します。
		@~japanese	@details	ベイヤー配列画像かどうかを確認します。
		@~japanese	@param[in] pIStPixelFormatInfoHandle	IStPixelFormatInfo インターフェースハンドル
		@~japanese	@param[out] pbValue	ベイヤー配列画像の時 true が返されます。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStPixelFormatInfo_IsBayer_t)(const PStApiHandle_t pIStPixelFormatInfoHandle, bool8_t *pbValue);
		
	/*!
		@~english	@brief	Check if the image data is compressed data.
		@~english	@details	Check if the image data is compressed data.
		@~english	@param[in] pIStPixelFormatInfoHandle	IStPixelFormatInfo interface handle.
		@~english	@param[out] pbValue	True if the image data is compressed.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	圧縮された画像かどうかを確認します。
		@~japanese	@details	圧縮された画像かどうかを確認します。
		@~japanese	@param[in] pIStPixelFormatInfoHandle	IStPixelFormatInfo インターフェースハンドル
		@~japanese	@param[out] pbValue	圧縮された画像の時 true が返されます。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStPixelFormatInfo_IsCompressed_t)(const PStApiHandle_t pIStPixelFormatInfoHandle, bool8_t *pbValue);

	/*!
		@~english	@brief	Get pixel color filter (color arrangement data) from a given image position.
		@~english	@details	Get pixel color filter (color arrangement data) from a a given image position.
		@~english	@attention	This function is applicable only to image data with Bayer arrangement.
		@~english	@param[in] pIStPixelFormatInfoHandle	IStPixelFormatInfo interface handle.
		@~english	@param[in] x	X-axis offset value(in pixel).
		@~english	@param[in] y	Y-axis offset value(in pixel).
		@~english	@param[out] pnValue	Filter arrangement information.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	指定した位置のカラーフィルターを取得します。
		@~japanese	@details	指定した位置のカラーフィルターを取得します。
		@~japanese	@attention	ベイヤー配列画像時のみ有効な値が取得されます。
		@~japanese	@param[in] pIStPixelFormatInfoHandle	IStPixelFormatInfo インターフェースハンドル
		@~japanese	@param[in] x	横方向の位置
		@~japanese	@param[in] y	縦方向の位置
		@~japanese	@param[out] pnValue	カラーフィルター
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStPixelFormatInfo_GetPixelColorFilter_t)(const PStApiHandle_t pIStPixelFormatInfoHandle, size_t x, size_t y, EStPixelColorFilter_t *pnValue);

	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStPixelFormatInfo_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IStPixelFormatInfo.
		@~english	@details	This structure holds the address of the C language wrapper function of IStPixelFormatInfo.
		@~japanese	@brief	この構造体は IStPixelFormatInfo のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IStPixelFormatInfo のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_IStPixelFormatInfo_Functions_t
	{
		/*!
			@copydoc PStApiTL_IStPixelFormatInfo_GetIStPixelFormatInfo_t()
		*/
		PStApiTL_IStPixelFormatInfo_GetIStPixelFormatInfo_t	GetIStPixelFormatInfo;

		/*!
			@copydoc PStApiTL_IStPixelFormatInfo_GetValue_t()
		*/
		PStApiTL_IStPixelFormatInfo_GetValue_t	GetValue;

		/*!
			@copydoc PStApiTL_IStPixelFormatInfo_GetNameA_t()
		*/
		PStApiTL_IStPixelFormatInfo_GetNameA_t	GetNameA;

		/*!
			@copydoc PStApiTL_IStPixelFormatInfo_GetDescriptionA_t()
		*/
		PStApiTL_IStPixelFormatInfo_GetDescriptionA_t	GetDescriptionA;

		/*!
			@copydoc PStApiTL_IStPixelFormatInfo_GetEachPixelTotalBitCount_t()
		*/
		PStApiTL_IStPixelFormatInfo_GetEachPixelTotalBitCount_t	GetEachPixelTotalBitCount;

		/*!
			@copydoc PStApiTL_IStPixelFormatInfo_GetEachComponentTotalBitCount_t()
		*/
		PStApiTL_IStPixelFormatInfo_GetEachComponentTotalBitCount_t	GetEachComponentTotalBitCount;

		/*!
			@copydoc PStApiTL_IStPixelFormatInfo_GetEachComponentValidBitCount_t()
		*/
		PStApiTL_IStPixelFormatInfo_GetEachComponentValidBitCount_t	GetEachComponentValidBitCount;

		/*!
			@copydoc PStApiTL_IStPixelFormatInfo_GetEachPixelTotalComponentCount_t()
		*/
		PStApiTL_IStPixelFormatInfo_GetEachPixelTotalComponentCount_t	GetEachPixelTotalComponentCount;

		/*!
			@copydoc PStApiTL_IStPixelFormatInfo_GetPlaneCount_t()
		*/
		PStApiTL_IStPixelFormatInfo_GetPlaneCount_t	GetPlaneCount;

		/*!
			@copydoc PStApiTL_IStPixelFormatInfo_GetPixelIncrementX_t()
		*/
		PStApiTL_IStPixelFormatInfo_GetPixelIncrementX_t	GetPixelIncrementX;

		/*!
			@copydoc PStApiTL_IStPixelFormatInfo_GetPixelIncrementY_t()
		*/
		PStApiTL_IStPixelFormatInfo_GetPixelIncrementY_t	GetPixelIncrementY;

		/*!
			@copydoc PStApiTL_IStPixelFormatInfo_IsColor_t()
		*/
		PStApiTL_IStPixelFormatInfo_IsColor_t	IsColor;

		/*!
			@copydoc PStApiTL_IStPixelFormatInfo_IsMono_t()
		*/
		PStApiTL_IStPixelFormatInfo_IsMono_t	IsMono;

		/*!
			@copydoc PStApiTL_IStPixelFormatInfo_IsBayer_t()
		*/
		PStApiTL_IStPixelFormatInfo_IsBayer_t	IsBayer;

		/*!
			@copydoc PStApiTL_IStPixelFormatInfo_IsCompressed_t()
		*/
		PStApiTL_IStPixelFormatInfo_IsCompressed_t	IsCompressed;

		/*!
			@copydoc PStApiTL_IStPixelFormatInfo_GetPixelColorFilter_t()
		*/
		PStApiTL_IStPixelFormatInfo_GetPixelColorFilter_t	GetPixelColorFilter;
	}StApi_IStPixelFormatInfo_Functions_t, *PStApi_IStPixelFormatInfo_Functions_t;
	
	/*************************************************************************/
	/* StApi::IStPixelComponentInfo */
	/*************************************************************************/
	/*!
		@~english	@brief	Acquire IStPixelComponentInfo interface handle. 
		@~english	@details	Acquire IStPixelComponentInfo interface handle. IStPixelComponentInfo interface handle is used for obtaining information related to the pixel component.
		@~english	@param[in] ePC	Pixel component.
		@~english	@param[in,out]	pIStPixelComponentInfoHandle	IStPixelComponentInfo interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStPixelComponentInfo インターフェースを取得します。
		@~japanese	@details	IStPixelComponentInfo インターフェースを取得します。 IStPixelComponentInfo インターフェースはピクセル構成要素関連情報の取得に使用されます。
		@~japanese	@param[in] ePC	ピクセル構成要素値
		@~english	@param[in,out]	pIStPixelComponentInfoHandle	IStPixelComponentInfo インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStPixelComponentInfo_GetIStPixelComponentInfo_t)(EStPixelComponent_t ePC, PStApiHandle_t pIStPixelComponentInfoHandle);

	/*!
		@~english	@brief	Get the value of the pixel component.
		@~english	@details	Get the value of the pixel component.
		@~english	@param[in] pIStPixelComponentInfoHandle	IStPixelFormatInfo interface handle.
		@~english	@param[out] pnValue	Value of pixel component.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ピクセルコンポーネント値を取得します。
		@~japanese	@details	ピクセルコンポーネント値を取得します。
		@~japanese	@param[in] pIStPixelComponentInfoHandle	IStPixelFormatInfo インターフェースハンドル
		@~japanese	@param[out] pnValue	ピクセルコンポーネント値
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStPixelComponentInfo_GetValue_t)(const PStApiHandle_t pIStPixelComponentInfoHandle, EStPixelComponent_t *pnValue);

	/*!
		@~english	@brief	Get the name of the pixel component.
		@~english	@details	Get the name of the pixel component.
		@~english	@param[in] pIStPixelComponentInfoHandle	IStPixelFormatInfo interface handle.
		@~english	@param[in,out] szText	Name of pixel component.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	構成要素の名前を取得します。
		@~japanese	@details	構成要素の名前を取得します。
		@~japanese	@param[in] pIStPixelComponentInfoHandle	IStPixelFormatInfo インターフェースハンドル
		@~japanese	@param[in,out] szText	構成要素の名前
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStPixelComponentInfo_GetNameA_t)(const PStApiHandle_t pIStPixelComponentInfoHandle, char *szText, size_t *pnLen);

	/*!
		@~english	@brief	Get the bits count of pixel component.
		@~english	@details	Get the bits count of pixel component.
		@~english	@param[in] pIStPixelComponentInfoHandle	IStPixelFormatInfo interface handle.
		@~english	@param[out] pnValue	Bits count of pixel component.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	構成要素のビット数を取得します。
		@~japanese	@details	構成要素のビット数を取得します。
		@~japanese	@param[in] pIStPixelComponentInfoHandle	IStPixelFormatInfo インターフェースハンドル
		@~japanese	@param[out] pnValue	ビット数
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStPixelComponentInfo_GetBitCount_t)(const PStApiHandle_t pIStPixelComponentInfoHandle, size_t *pnValue);

	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStPixelComponentInfo_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IStPixelComponentInfo.
		@~english	@details	This structure holds the address of the C language wrapper function of IStPixelComponentInfo.
		@~japanese	@brief	この構造体は IStPixelComponentInfo のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IStPixelComponentInfo のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_IStPixelComponentInfo_Functions_t
	{
		/*!
			@copydoc PStApiTL_IStPixelComponentInfo_GetIStPixelComponentInfo_t()
		*/
		PStApiTL_IStPixelComponentInfo_GetIStPixelComponentInfo_t	GetIStPixelComponentInfo;


		/*!
			@copydoc PStApiTL_IStPixelComponentInfo_GetValue_t()
		*/
		PStApiTL_IStPixelComponentInfo_GetValue_t	GetValue;

		/*!
			@copydoc PStApiTL_IStPixelComponentInfo_GetNameA_t()
		*/
		PStApiTL_IStPixelComponentInfo_GetNameA_t	GetNameA;

		/*!
			@copydoc PStApiTL_IStPixelComponentInfo_GetBitCount_t()
		*/
		PStApiTL_IStPixelComponentInfo_GetBitCount_t	GetBitCount;
	}StApi_IStPixelComponentInfo_Functions_t, *PStApi_IStPixelComponentInfo_Functions_t;

	/*************************************************************************/
	/* StApi::IStPixelComponentValue */
	/*************************************************************************/
	/*!
		@~english	@brief	Get the number of pixel component.
		@~english	@details	Get the number of pixel component.
		@~english	@param[in] pIStPixelComponentValueHandle	IStPixelComponentValue interface handle.
		@~english	@param[out] pnValue	Number of pixel component.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ピクセル構成要素数を取得します。
		@~japanese	@details	ピクセル構成要素数を取得します。
		@~japanese	@param[in] pIStPixelComponentValueHandle	IStPixelComponentValue インターフェースハンドル
		@~japanese	@param[out] pnValue	Number	ピクセル構成要素数
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStPixelComponentValue_GetCount_t)(const PStApiHandle_t pIStPixelComponentValueHandle, size_t *pnValue);
		
	/*!
		@~english	@brief	Get pixel data of the pixel component.
		@~english	@details	Get pixel data of the pixel component.
		@~english	@param[in] pIStPixelComponentValueHandle	IStPixelComponentValue interface handle.
		@~english	@param[in]	nIndex	Index of the pixel component.
		@~english	@param[out] pnValue	Number	Pixel data of the pixel component.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	画素値を取得します。
		@~japanese	@details	画素値を取得します。
		@~japanese	@param[in] pIStPixelComponentValueHandle	IStPixelComponentValue インターフェースハンドル
		@~japanese	@param[in]	nIndex	構成要素のインディックス値
		@~japanese	@param[out] pnValue	Number	画素値
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStPixelComponentValue_GetValue_t)(const PStApiHandle_t pIStPixelComponentValueHandle, size_t nIndex, int64_t *pnValue);

	/*!
		@~english	@brief	Pixel value of the pixel component.
		@~english	@details	Pixel value of the pixel component.
		@~english	@param[in] pIStPixelComponentValueHandle	IStPixelComponentValue interface handle.
		@~english	@param[in]	nIndex	Index of the pixel component.
		@~english	@param[out] pnValue	Number	Pixel value of the pixel component.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ピクセル構成要素値を取得します。
		@~japanese	@details	ピクセル構成要素値を取得します。
		@~japanese	@param[in] pIStPixelComponentValueHandle	IStPixelComponentValue インターフェースハンドル
		@~japanese	@param[in]	nIndex	構成要素のインディックス値
		@~japanese	@param[out] pnValue	Number	ピクセル構成要素値
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStPixelComponentValue_GetPixelComponent_t)(const PStApiHandle_t pIStPixelComponentValueHandle, size_t nIndex, EStPixelComponent_t *pnValue);

	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStPixelComponentValue_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IStPixelComponentValue.
		@~english	@details	This structure holds the address of the C language wrapper function of IStPixelComponentValue.
		@~japanese	@brief	この構造体は IStPixelComponentValue のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IStPixelComponentValue のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_IStPixelComponentValue_Functions_t
	{
		/*!
			@copydoc PStApiTL_IStPixelComponentValue_GetCount_t()
		*/
		PStApiTL_IStPixelComponentValue_GetCount_t	GetCount;

		/*!
			@copydoc PStApiTL_IStPixelComponentValue_GetValue_t()
		*/
		PStApiTL_IStPixelComponentValue_GetValue_t	GetValue;

		/*!
			@copydoc PStApiTL_IStPixelComponentValue_GetPixelComponent_t()
		*/
		PStApiTL_IStPixelComponentValue_GetPixelComponent_t	GetPixelComponent;
	}StApi_IStPixelComponentValue_Functions_t, *PStApi_IStPixelComponentValue_Functions_t;

	/*************************************************************************/
	/* StApi::IStFeatureBag */
	/*************************************************************************/
	/*!
		@~english	@brief	Acquire IStFeatureBag interface handle. 
		@~english	@details	Acquire IStFeatureBag interface handle. IStFeatureBag interface handle is used for saving/loading setting of cameras to memory or file. Call IStPixelComponentInfo->Release(pIStFeatureBagHandle) to release the object if it is no longer necessary.
		@~english	@param[in,out]	pIStFeatureBagHandle	IStFeatureBag interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStFeatureBagReleasable インターフェースを取得します。
		@~japanese	@details	IStPixelComponentInfo インターフェースハンドルを取得します。オブジェクトが不要になったら IStPixelComponentInfo->Release(pIStFeatureBagHandle) を呼び出して解放してください。
		@~english	@param[in,out]	pIStFeatureBagHandle	IStFeatureBag インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStFeatureBag_Create_t)(PStApiHandle_t pIStFeatureBagHandle);

	/*!
		@~english	@brief	Release object.
		@~english	@details	Release object.
		@~english	@param[in] pIStFeatureBagHandle	IStFeatureBag interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	解放します。
		@~japanese	@details	解放します。
		@~japanese	@param[in] pIStFeatureBagHandle	IStFeatureBag interface handle.
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStFeatureBag_Release_t)(PStApiHandle_t pIStFeatureBagHandle);

	/*!
		@~english	@brief	Store streamable nodes to the feature bag.
		@~english	@details	Store streamable nodes to the feature bag.
		@~english	@param[in] pIStFeatureBagHandle	IStFeatureBag interface handle.
		@~english	@param[in] pINodeMapHandle	The node map to store.
		@~english	@param[in] MaxNumPersistScriptEntries	The max numbers of entries in the container; -1 means unlimited.
		@~english	@param[out] pnValue	Number of entries in the bag
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	指定したノードマップの設定情報をメモリーへ退避します。
		@~japanese	@details	指定したノードマップの設定情報をメモリーへ退避します。
		@~japanese	@param[in] pIStFeatureBagHandle	IStFeatureBag インターフェースハンドル
		@~japanese	@param[in] pINodeMapHandle	ノードマップ
		@~japanese	@param[in] MaxNumPersistSkciptEntries	メモリーへ退避する項目数の最大値を指定します。-1を指定すると無制限になります。
		@~japanese	@param[out] pnValue	退避された項目数
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStFeatureBag_StoreNodeMapToBag_t)(const PStApiHandle_t pIStFeatureBagHandle, PStApiHandle_t pINodeMapHandle, int32_t MaxNumPersistScriptEntries, int64_t *pnValue);

	/*!
		@~english	@brief	Store string to the FeatureBag.
		@~english	@details	Store string to the FeatureBag.
		@~english	@param[in] pIStFeatureBagHandle	IStFeatureBag interface handle.
		@~english	@param[in] szText	The string contents of setting and its value.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	文字列で指定された設定情報をメモリーへ登録します。
		@~japanese	@details	文字列で指定された設定情報をメモリーへ登録します。
		@~japanese	@param[in] pIStFeatureBagHandle	IStFeatureBag インターフェースハンドル
		@~japanese	@param[in] szText	設定名と設定値を含んだ文字列
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStFeatureBag_StoreStringToBagA_t)(const PStApiHandle_t pIStFeatureBagHandle, const char *szText);

	/*!
		@~english	@brief	Read data from saved file to the FeatureBag.
		@~english	@details	Read data from saved file to the FeatureBag.
		@~english	@param[in] pIStFeatureBagHandle	IStFeatureBag interface handle.
		@~english	@param[in] szFileName	The setting file to read. This file must be created using SaveToFile() function.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ファイルへ保存された設定情報をメモリーへ登録します。
		@~japanese	@details	ファイルへ保存された設定情報をメモリーへ登録します。
		@~japanese	@param[in] pIStFeatureBagHandle	IStFeatureBag インターフェースハンドル
		@~japanese	@param[in] szFileName	設定ファイル名
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStFeatureBag_StoreFileToBagA_t)(const PStApiHandle_t pIStFeatureBagHandle, const char *szFileName);

	/*!
		@~english	@brief	Read data from saved file to the FeatureBag.
		@~english	@details	Read data from saved file to the FeatureBag.
		@~english	@param[in] pIStFeatureBagHandle	IStFeatureBag interface handle.
		@~english	@param[in] szFileName	The setting file to read. This file must be created using SaveToFile() function.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ファイルへ保存された設定情報をメモリーへ登録します。
		@~japanese	@details	ファイルへ保存された設定情報をメモリーへ登録します。
		@~japanese	@param[in] pIStFeatureBagHandle	IStFeatureBag インターフェースハンドル
		@~japanese	@param[in] szFileName	設定ファイル名
		@~japanese	@return	EStApiCError_t エラーコード
		@since StApi v1.1.1
	*/
	STAPI_PCALL(PStApiTL_IStFeatureBag_StoreFileToBagW_t)(const PStApiHandle_t pIStFeatureBagHandle, const wchar_t *szFileName);

	/*!
		@~english	@brief	Loads features from the feature bag to the node tree.
		@~english	@details	Loads features from the feature bag to the node tree. If verify is set to true, the list of names in the feature bag will be re-read. If a node is a selector, its value is set to the value from the feature bag; otherwise, the value is read from the camera and compared with the value from the feature bag.
		@~english	@param[in] pIStFeatureBagHandle	IStFeatureBag interface handle.
		@~english	@param[in] pINodeMapHandle	The node map.
		@~english	@param[in] verify	If true, all streamable features will be re-read.
		@~english	@param[out] pbValue	Return false if an error occurs during loading.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	メモリーへ保存された設定情報をノードマップへ反映します。
		@~japanese	@details	メモリーへ保存された設定情報をノードマップへ反映します。
		@~japanese	@param[in] pIStFeatureBagHandle	IStFeatureBag インターフェースハンドル
		@~japanese	@param[in] pINodeMapHandle	反映先のノードマップ
		@~japanese	@param[in] verify	設定反映後に読み込み確認(ベリファイ)を行う場合は true を指定します。
		@~japanese	@param[out] pbValue	エラーが発生した場合、 false が返されます。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStFeatureBag_Load_t)(const PStApiHandle_t pIStFeatureBagHandle, PStApiHandle_t pINodeMapHandle, bool8_t verify, bool8_t *pbValue);

	/*!
		@~english	@brief	Acquire data from the FeatureBag.
		@~english	@details	Acquire data from the FeatureBag.
		@~english	@param[in] pIStFeatureBagHandle	IStFeatureBag interface handle.
		@~english	@param[in,out] szText	Data (String) containing the name and value of the settings stored in the feature bag.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	メモリーへ保存された設定情報を文字列として取得します。
		@~japanese	@details	メモリーへ保存された設定情報を文字列として取得します。
		@~japanese	@param[in] pIStFeatureBagHandle	IStFeatureBag インターフェースハンドル
		@~japanese	@param[in,out] szText	設定名と設定値を含んだ文字列
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStFeatureBag_SaveToStringA_t)(const PStApiHandle_t pIStFeatureBagHandle, char *szText, size_t *pnLen);

	/*!
		@~english	@brief	Save setting in the FeatureBag to a file.
		@~english	@details	Save setting in the FeatureBag to a file.
		@~english	@param[in] pIStFeatureBagHandle	IStFeatureBag interface handle.
		@~english	@param[in] szFileName	File name.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	メモリーへ保存された設定情報をファイルへ保存します。
		@~japanese	@details	メモリーへ保存された設定情報をファイルへ保存します。
		@~japanese	@param[in] pIStFeatureBagHandle	IStFeatureBag インターフェースハンドル
		@~japanese	@param[in] szFileName	ファイル名。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStFeatureBag_SaveToFileA_t)(const PStApiHandle_t pIStFeatureBagHandle, const char *szFileName);

	/*!
		@~english	@brief	Save setting in the FeatureBag to a file.
		@~english	@details	Save setting in the FeatureBag to a file.
		@~english	@param[in] pIStFeatureBagHandle	IStFeatureBag interface handle.
		@~english	@param[in] szFileName	File name.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	メモリーへ保存された設定情報をファイルへ保存します。
		@~japanese	@details	メモリーへ保存された設定情報をファイルへ保存します。
		@~japanese	@param[in] pIStFeatureBagHandle	IStFeatureBag インターフェースハンドル
		@~japanese	@param[in] szFileName	ファイル名。
		@~japanese	@return	EStApiCError_t エラーコード
		@since StApi v1.1.1
	*/
	STAPI_PCALL(PStApiTL_IStFeatureBag_SaveToFileW_t)(const PStApiHandle_t pIStFeatureBagHandle, const wchar_t *szFileName);

	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStFeatureBag_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IStFeatureBag.
		@~english	@details	This structure holds the address of the C language wrapper function of IStFeatureBag.
		@~japanese	@brief	この構造体は IStFeatureBag のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IStFeatureBag のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_IStFeatureBag_Functions_t
	{
		
		/*!
			@copydoc PStApiTL_IStFeatureBag_Create_t()
		*/
		PStApiTL_IStFeatureBag_Create_t		Create;

		/*!
			@copydoc PStApiTL_IStFeatureBag_Release_t()
		*/
		PStApiTL_IStFeatureBag_Release_t			Release;

		/*!
			@copydoc PStApiTL_IStFeatureBag_StoreNodeMapToBag_t()
		*/
		PStApiTL_IStFeatureBag_StoreNodeMapToBag_t	StoreNodeMapToBag;

		/*!
			@copydoc PStApiTL_IStFeatureBag_StoreStringToBagA_t()
		*/
		PStApiTL_IStFeatureBag_StoreStringToBagA_t	StoreStringToBagA;

		/*!
			@copydoc PStApiTL_IStFeatureBag_StoreFileToBagA_t()
		*/
		PStApiTL_IStFeatureBag_StoreFileToBagA_t		StoreFileToBagA;

		/*!
			@copydoc PStApiTL_IStFeatureBag_Load_t()
		*/
		PStApiTL_IStFeatureBag_Load_t				Load;

		/*!
			@copydoc PStApiTL_IStFeatureBag_SaveToStringA_t()
		*/
		PStApiTL_IStFeatureBag_SaveToStringA_t		SaveToStringA;

		/*!
			@copydoc PStApiTL_IStFeatureBag_SaveToFileA_t()
		*/
		PStApiTL_IStFeatureBag_SaveToFileA_t			SaveToFileA;

		/*!
			@copydoc PStApiTL_IStFeatureBag_StoreFileToBagW_t()
		*/
		PStApiTL_IStFeatureBag_StoreFileToBagW_t		StoreFileToBagW;

		/*!
			@copydoc PStApiTL_IStFeatureBag_SaveToFileW_t()
		*/
		PStApiTL_IStFeatureBag_SaveToFileW_t			SaveToFileW;
	}StApi_IStFeatureBag_Functions_t, *PStApi_IStFeatureBag_Functions_t;

	/*************************************************************************/
	/* StApi::IStAllocator */
	/*************************************************************************/
	
	/*!
		@~english
			@brief	It is called when memory allocation is required.
			@details	It is called when memory allocation is required.
			@param[out]	ppBuffer	The pointer to the pointer of the allocated memory.
			@param[in]	nSize	The size of memory to allocate.
			@param[out]	ppContext	The pointer to the pointer of the private data.
		@~japanese
			@brief	メモリーの割り当てが必要になったときに呼び出されます。
			@details	メモリーの割り当てが必要になったときに呼び出されます。
			@param[out]	ppBuffer	割り当てられたメモリーへのポインター
			@param[in]	nSize	割り当てるメモリーのサイズ[Bytes]。
			@param[out]	ppContext	メモリーと関連付けするユーザー用ポインター
	*/
	typedef void (STAPI_CALLTYPE fAllocateCallbackFunc_t)(void **  ppBuffer, size_t  nSize, void **  ppContext);
	
	/*!
		@~english
			@brief	It is called when memory needs to be released.
			@details	It is called when memory needs to be released.
			@param[in]	pBuffer	The pointer to the allocated memory.
			@param[in]	nSize	The size of the allocated memory.
			@param[in]	pContext	The pointer to the private data.
		@~japanese
			@brief	メモリーの解放が必要になったときに呼び出されます。
			@details	メモリーの解放が必要になったときに呼び出されます。
			@param[in]	pBuffer	解放するメモリーへのポインター
			@param[in]	nSize	割り当てられたメモリーのサイズ[Bytes]。
			@param[in]	pContext	メモリーと関連付けされているユーザー用ポインター
	*/
	typedef void (STAPI_CALLTYPE fDeallocateCallbackFunc_t)(void *  pBuffer, size_t  nSize, void *  pContext);
	
	/*!
		@~english
			@brief	Called when the allocator is no longer needed.
			@details	Called when the allocator is no longer needed.
		@~japanese
			@brief	割り当てられたメモリーが不要になった際に呼び出されます。
			@details	割り当てられたメモリーが不要になった際に呼び出されます。
	*/
	typedef void (STAPI_CALLTYPE fOnDeregisterCallbackFunc_t)(void);

	/*!
		@~english	@brief	Create IStAllocator object.
		@~english	@details	Create IStAllocator object.
		@~english	@param[in] pFuncAllocate	Function to allocate memory.
		@~english	@param[in] pFuncDeallocate	Function to deallocate memory.
		@~english	@param[in] pFuncOnDeregister	Function called when the allocator was no longer needed.
		@~english	@param[in,out] pIStAllocatorHandle	IStAllocator interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStAllocator を生成します。
		@~japanese	@details	IStAllocator を生成します。
		@~english	@param[in] pFuncAllocate	メモリー割り当て時に使用される関数
		@~english	@param[in] pFuncDeallocate	メモリー解放時に使用される関数
		@~english	@param[in] pFuncOnDeregister	アロケーターが不要になった時に呼び出される関数
		@~japanese	@param[in,out] pIStAllocatorHandle	IStAllocator インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStAllocator_CreateIStAllocator_t)(fAllocateCallbackFunc_t *pFuncAllocate, fDeallocateCallbackFunc_t *pFuncDeallocate, fOnDeregisterCallbackFunc_t *pFuncOnDeregister, PStApiHandle_t pAllocatorHandle);

	/*!
		@~english	@brief	Release object.
		@~english	@details	Release object.
		@~english	@param[in] pIStAllocatorHandle	IStAllocator interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	解放します。
		@~japanese	@details	解放します。
		@~japanese	@param[in] pIStAllocatorHandle	IStAllocator インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStAllocator_Release_t)(PStApiHandle_t pIStAllocatorHandle);
	/*!
		@~english
		@~english	@brief	Allocate memory with requested size.
		@~english	@details	Allocate memory with requested size.
		@~english	@param[in] pIStAllocatorHandle	IStAllocator interface handle.
		@~english	@param[out]	ppBuffer	The pointer to the pointer of the allocated memory.
		@~english	@param[in]	nSize	The size of memory to allocate.
		@~english	@param[out]	ppContext	The pointer to the pointer of the private data.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	指定されたサイズのメモリーを割り当てます。
		@~japanese	@details	指定されたサイズのメモリーを割り当てます。
		@~japanese	@param[in] pIStAllocatorHandle	IStAllocator インターフェースハンドル
		@~japanese	@param[out]	ppBuffer	割り当てられたメモリーへのポインター
		@~japanese	@param[in]	nSize	割り当てるメモリーのサイズ[Bytes]。
		@~japanese	@param[out]	ppContext	メモリーと関連付けするユーザー用ポインター
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStAllocator_Allocate_t)(const PStApiHandle_t pIStAllocatorHandle, void **ppBuffer, size_t nSize, void **ppContext);
		
	/*!
		@~english	@brief	Free the memory.
		@~english	@details	Free the memory.
		@~english	@param[in] pIStAllocatorHandle	IStAllocator interface handle.
		@~english	@param[in]	pBuffer	The pointer to the allocated memory.
		@~english	@param[in]	nSize	The size of the allocated memory.
		@~english	@param[in]	pContext	The pointer to the private data.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	メモリーを解放します。
		@~japanese	@details	メモリーを解放します。
		@~japanese	@param[in] pIStAllocatorHandle	IStAllocator インターフェースハンドル
		@~japanese	@param[in]	pBuffer	解放するメモリーへのポインター
		@~japanese	@param[in]	nSize	割り当てられたメモリーのサイズ[Bytes]。
		@~japanese	@param[in]	pContext	メモリーと関連付けされているユーザー用ポインター
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStAllocator_Deallocate_t)(const PStApiHandle_t pIStAllocatorHandle, void *pBuffer, size_t nSize, void *pContext);

	/*!
		@~english	@brief	Called when the allocator is no longer needed.
		@~english	@details	Called when the allocator is no longer needed.
		@~english	@param[in] pIStAllocatorHandle	IStAllocator interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	割り当てられたメモリーが不要になった際に呼び出されます。
		@~japanese	@details	割り当てられたメモリーが不要になった際に呼び出されます。
		@~japanese	@param[in] pIStAllocatorHandle	IStAllocator インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStAllocator_OnDeregister_t)(const PStApiHandle_t pIStAllocatorHandle);
	
	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStAllocator_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IStAllocator.
		@~english	@details	This structure holds the address of the C language wrapper function of IStAllocator.
		@~japanese	@brief	この構造体は IStAllocator のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IStAllocator のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_IStAllocator_Functions_t
	{
		/*!
			@copydoc PStApiTL_IStAllocator_CreateIStAllocator_t()
		*/
		PStApiTL_IStAllocator_CreateIStAllocator_t	CreateIStAllocator;

		/*!
			@copydoc PStApiTL_IStAllocator_Release_t()
		*/
		PStApiTL_IStAllocator_Release_t	Release;

		/*!
			@copydoc PStApiTL_IStAllocator_Allocate_t()
		*/
		PStApiTL_IStAllocator_Allocate_t	Allocate;

		/*!
			@copydoc PStApiTL_IStAllocator_Deallocate_t()
		*/
		PStApiTL_IStAllocator_Deallocate_t	Deallocate;

		/*!
			@copydoc PStApiTL_IStAllocator_OnDeregister_t()
		*/
		PStApiTL_IStAllocator_OnDeregister_t	OnDeregister;
	}StApi_IStAllocator_Functions_t, *PStApi_IStAllocator_Functions_t;

	/*************************************************************************/
	/* StApi::IStRegisteredCallback */
	/*************************************************************************/
	/*!
		@~english	@brief	Deregister a callback function.
		@~english	@details	Deregister a callback function.
		@~english	@param[in,out] pIStRegisteredCallbackHandle	IStRegisteredCallback interface handle
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	コールバック関数の登録を解除します。
		@~japanese	@details	コールバック関数の登録を解除します。
		@~japanese	@param[in,out] pIStRegisteredCallbackHandle	IStRegisteredCallback インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStRegisteredCallback_Release_t)(PStApiHandle_t pIStRegisteredCallbackHandle);
	
	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStRegisteredCallback_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IStRegisteredCallback.
		@~english	@details	This structure holds the address of the C language wrapper function of IStRegisteredCallback.
		@~japanese	@brief	この構造体は IStRegisteredCallback のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IStRegisteredCallback のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_IStRegisteredCallback_Functions_t
	{
		/*!
			@copydoc PStApiTL_IStRegisteredCallback_Release_t()
		*/
		PStApiTL_IStRegisteredCallback_Release_t	Release;
	}StApi_IStRegisteredCallback_Functions_t, *PStApi_IStRegisteredCallback_Functions_t;

	/*************************************************************************/
	/* StApi::IStCallbackParamBase */
	/*************************************************************************/
	/*!
		@~english	@brief	Return the callback type.
		@~english	@details	Return the callback type.
		@~english	@param[in] pIStCallbackParamBaseHandle	IStCallbackParamBase interface handle
		@~english	@param[out] pnValue	The callback type.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	コールバックタイプを取得します。
		@~japanese	@details	コールバックタイプを取得します。
		@~japanese	@param[in] pIStCallbackParamBaseHandle	IStCallbackParamBase インターフェースハンドル
		@~japanese	@param[out] pnValue	コールバックタイプ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStCallbackParamBase_GetCallbackType_t)(const PStApiHandle_t pIStCallbackParamBaseHandle, EStCallbackType_t *pnValue);
	
	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStCallbackParamBase_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IStCallbackParamBase.
		@~english	@details	This structure holds the address of the C language wrapper function of IStCallbackParamBase.
		@~japanese	@brief	この構造体は IStCallbackParamBase のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IStCallbackParamBase のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_IStCallbackParamBase_Functions_t
	{
		/*!
			@copydoc PStApiTL_IStCallbackParamBase_GetCallbackType_t()
		*/
		PStApiTL_IStCallbackParamBase_GetCallbackType_t	GetCallbackType;
	}StApi_IStCallbackParamBase_Functions_t, *PStApi_IStCallbackParamBase_Functions_t;
	
	/*************************************************************************/
	/* StApi::IStCallbackParamGenTLEventError */
	/*************************************************************************/
	/*!
		@~english	@brief	Return the callback type.
		@~english	@details	Return the callback type.
		@~english	@param[in] pIStCallbackParamBaseHandle	IStCallbackParamBase interface handle
		@~english	@param[out] pnValue	The GenTL error code.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	コールバックタイプを取得します。
		@~japanese	@details	コールバックタイプを取得します。
		@~japanese	@param[in] pIStCallbackParamBaseHandle	IStCallbackParamBase インターフェースハンドル
		@~japanese	@param[out] pnValue	GenTLエラーコード
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStCallbackParamGenTLEventError_GetGCError_t)(const PStApiHandle_t pIStCallbackParamBaseHandle, GC_ERROR *pnValue);

	/*!
		@~english	@brief	Return the callback type.
		@~english	@details	Return the callback type.
		@~english	@param[in] pIStCallbackParamBaseHandle	IStCallbackParamBase interface handle
		@~english	@param[in,out] szText	The description of the error.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	コールバックタイプを取得します。
		@~japanese	@details	コールバックタイプを取得します。
		@~japanese	@param[in] pIStCallbackParamBaseHandle	IStCallbackParamBase インターフェースハンドル
		@~japanese	@param[in,out] szText	GenTLのエラーの説明文
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStCallbackParamGenTLEventError_GetDescriptionA_t)(const PStApiHandle_t pIStCallbackParamBaseHandle, char *szText, size_t *pnLen);
	
	/*!
		@ingroup IStCallbackParamGenTLEventError
		@struct StApi_IStCallbackParamGenTLEventError_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IStCallbackParamGenTLEventError.
		@~english	@details	This structure holds the address of the C language wrapper function of IStCallbackParamGenTLEventError.
		@~japanese	@brief	この構造体は IStCallbackParamGenTLEventError のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IStCallbackParamGenTLEventError のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_IStCallbackParamGenTLEventError_Functions_t
	{
		/*!
			@copydoc PStApiTL_IStCallbackParamGenTLEventError_GetGCError_t()
		*/
		PStApiTL_IStCallbackParamGenTLEventError_GetGCError_t	GetGCError;

		/*!
			@copydoc PStApiTL_IStCallbackParamGenTLEventError_GetDescriptionA_t()
		*/
		PStApiTL_IStCallbackParamGenTLEventError_GetDescriptionA_t	GetDescriptionA;
	}StApi_IStCallbackParamGenTLEventError_Functions_t, *PStApi_IStCallbackParamGenTLEventError_Functions_t;
	
	/*************************************************************************/
	/* StApi::IStCallbackParamGenTLEventErrorTL */
	/*************************************************************************/
	/*!
		@~english	@brief	Acquire IStSystem interface handle.
		@~english	@details	Acquire IStSystem interface handle.
		@~english	@param[in] pIStCallbackParamBaseHandle	IStCallbackParamBase interface handle
		@~english	@param[in,out] pIStSystemHandle	IStSystem interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStSystem インターフェースハンドルを取得します。
		@~japanese	@details	IStSystem インターフェースハンドルを取得します。
		@~japanese	@param[in] pIStCallbackParamBaseHandle	IStCallbackParamBase インターフェースハンドル
		@~japanese	@param[in,out] pIStSystemHandle	IStSystem インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStCallbackParamGenTLEventErrorTL_GetIStSystem_t)(const PStApiHandle_t pIStCallbackParamBaseHandle, PStApiHandle_t pIStSystemHandle);
	
	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStCallbackParamGenTLEventErrorTL_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IStCallbackParamGenTLEventErrorTL.
		@~english	@details	This structure holds the address of the C language wrapper function of IStCallbackParamGenTLEventErrorTL.
		@~japanese	@brief	この構造体は IStCallbackParamGenTLEventErrorTL のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IStCallbackParamGenTLEventErrorTL のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_IStCallbackParamGenTLEventErrorTL_Functions_t
	{
		/*!
			@copydoc PStApiTL_IStCallbackParamGenTLEventErrorTL_GetIStSystem_t()
		*/
		PStApiTL_IStCallbackParamGenTLEventErrorTL_GetIStSystem_t	GetIStSystem;
	}StApi_IStCallbackParamGenTLEventErrorTL_Functions_t, *PStApi_IStCallbackParamGenTLEventErrorTL_Functions_t;
	
	/*************************************************************************/
	/* StApi::IStCallbackParamGenTLEventErrorIF */
	/*************************************************************************/
	/*!
		@~english	@brief	Acquire IStInterface interface handle.
		@~english	@details	Acquire IStInterface interface handle.
		@~english	@param[in] pIStCallbackParamBaseHandle	IStCallbackParamBase interface handle
		@~english	@param[in,out] pIStInterfaceHandle	IStInterface interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStInterface インターフェースハンドルを取得します。
		@~japanese	@details	IStInterface インターフェースハンドルを取得します。
		@~japanese	@param[in] pIStCallbackParamBaseHandle	IStCallbackParamBase インターフェースハンドル
		@~japanese	@param[in,out] pIStInterfaceHandle	IStInterface インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStCallbackParamGenTLEventErrorIF_GetIStInterface_t)(const PStApiHandle_t pIStCallbackParamBaseHandle, PStApiHandle_t pIStInterfaceHandle);
	
	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStCallbackParamGenTLEventErrorIF_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IStCallbackParamGenTLEventErrorIF.
		@~english	@details	This structure holds the address of the C language wrapper function of IStCallbackParamGenTLEventErrorIF.
		@~japanese	@brief	この構造体は IStCallbackParamGenTLEventErrorIF のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IStCallbackParamGenTLEventErrorIF のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_IStCallbackParamGenTLEventErrorIF_Functions_t
	{
		/*!
			@copydoc PStApiTL_IStCallbackParamGenTLEventErrorIF_GetIStInterface_t()
		*/
		PStApiTL_IStCallbackParamGenTLEventErrorIF_GetIStInterface_t	GetIStInterface;
	}StApi_IStCallbackParamGenTLEventErrorIF_Functions_t, *PStApi_IStCallbackParamGenTLEventErrorIF_Functions_t;

	/*************************************************************************/
	/* StApi::IStCallbackParamGenTLEventErrorDEV */
	/*************************************************************************/
	/*!
		@~english	@brief	Acquire IStDevice interface handle.
		@~english	@details	Acquire IStDevice interface handle.
		@~english	@param[in] pIStCallbackParamBaseHandle	IStCallbackParamBase interface handle
		@~english	@param[in,out] pIStDeviceHandle	IStDevice interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStDevice インターフェースハンドルを取得します。
		@~japanese	@details	IStDevice インターフェースハンドルを取得します。
		@~japanese	@param[in] pIStCallbackParamBaseHandle	IStCallbackParamBase インターフェースハンドル
		@~japanese	@param[in,out] pIStDeviceHandle	IStDevice インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStCallbackParamGenTLEventErrorDEV_GetIStDevice_t)(const PStApiHandle_t pIStCallbackParamBaseHandle, PStApiHandle_t pIStDeviceHandle);

	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStCallbackParamGenTLEventErrorDEV_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IStCallbackParamGenTLEventErrorDEV.
		@~english	@details	This structure holds the address of the C language wrapper function of IStCallbackParamGenTLEventErrorDEV.
		@~japanese	@brief	この構造体は IStCallbackParamGenTLEventErrorDEV のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IStCallbackParamGenTLEventErrorDEV のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_IStCallbackParamGenTLEventErrorDEV_Functions_t
	{
		/*!
			@copydoc PStApiTL_IStCallbackParamGenTLEventErrorDEV_GetIStDevice_t()
		*/
		PStApiTL_IStCallbackParamGenTLEventErrorDEV_GetIStDevice_t	GetIStDevice;
	}StApi_IStCallbackParamGenTLEventErrorDEV_Functions_t, *PStApi_IStCallbackParamGenTLEventErrorDEV_Functions_t;

	/*************************************************************************/
	/* StApi::IStCallbackParamGenTLEventErrorDS */
	/*************************************************************************/
	/*!
		@~english	@brief	Acquire IStDataStream interface handle.
		@~english	@details	Acquire IStDataStream interface handle.
		@~english	@param[in] pIStCallbackParamBaseHandle	IStCallbackParamBase interface handle
		@~english	@param[in,out] pIStDataStreamHandle	IStDataStream interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStDataStream インターフェースハンドルを取得します。
		@~japanese	@details	IStDataStream インターフェースハンドルを取得します。
		@~japanese	@param[in] pIStCallbackParamBaseHandle	IStCallbackParamBase インターフェースハンドル
		@~japanese	@param[in,out] pIStDataStreamHandle	IStDataStream インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStCallbackParamGenTLEventErrorDS_GetIStDataStream_t)(const PStApiHandle_t pIStCallbackParamBaseHandle, PStApiHandle_t pIStDataStreamHandle);

	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStCallbackParamGenTLEventErrorDS_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IStCallbackParamGenTLEventErrorDS.
		@~english	@details	This structure holds the address of the C language wrapper function of IStCallbackParamGenTLEventErrorDS.
		@~japanese	@brief	この構造体は IStCallbackParamGenTLEventErrorDS のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IStCallbackParamGenTLEventErrorDS のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_IStCallbackParamGenTLEventErrorDS_Functions_t
	{
		/*!
			@copydoc PStApiTL_IStCallbackParamGenTLEventErrorDS_GetIStDataStream_t()
		*/
		PStApiTL_IStCallbackParamGenTLEventErrorDS_GetIStDataStream_t	GetIStDataStream;
	}StApi_IStCallbackParamGenTLEventErrorDS_Functions_t, *PStApi_IStCallbackParamGenTLEventErrorDS_Functions_t;

	/*************************************************************************/
	/* StApi::IStCallbackParamGenTLEventErrorSB */
	/*************************************************************************/
	/*!
		@~english	@brief	Acquire IStStreamBuffer interface handle.
		@~english	@details	Acquire IStStreamBuffer interface handle.
		@~english	@param[in] pIStCallbackParamBaseHandle	IStCallbackParamBase interface handle
		@~english	@param[in,out] pIStStreamBufferHandle	IStStreamBuffer interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStStreamBuffer インターフェースハンドルを取得します。
		@~japanese	@details	IStStreamBuffer インターフェースハンドルを取得します。
		@~japanese	@param[in] pIStCallbackParamBaseHandle	IStCallbackParamBase インターフェースハンドル
		@~japanese	@param[in,out] pIStStreamBufferHandle	IStStreamBuffer インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStCallbackParamGenTLEventErrorSB_GetIStStreamBuffer_t)(const PStApiHandle_t pIStCallbackParamBaseHandle, PStApiHandle_t pIStStreamBufferHandle);

	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStCallbackParamGenTLEventErrorSB_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IStCallbackParamGenTLEventErrorSB.
		@~english	@details	This structure holds the address of the C language wrapper function of IStCallbackParamGenTLEventErrorSB.
		@~japanese	@brief	この構造体は IStCallbackParamGenTLEventErrorSB のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IStCallbackParamGenTLEventErrorSB のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_IStCallbackParamGenTLEventErrorSB_Functions_t
	{
		/*!
			@copydoc PStApiTL_IStCallbackParamGenTLEventErrorSB_GetIStStreamBuffer_t()
		*/
		PStApiTL_IStCallbackParamGenTLEventErrorSB_GetIStStreamBuffer_t	GetIStStreamBuffer;
	}StApi_IStCallbackParamGenTLEventErrorSB_Functions_t, *PStApi_IStCallbackParamGenTLEventErrorSB_Functions_t;

	/*************************************************************************/
	/* StApi::IStCallbackParamGenTLEventNewBuffer */
	/*************************************************************************/
	/*!
		@~english	@brief	Acquire IStDataStream interface handle.
		@~english	@details	Acquire IStDataStream interface handle.
		@~english	@param[in] pIStCallbackParamBaseHandle	IStCallbackParamBase interface handle
		@~english	@param[in,out] pIStDataStreamHandle	IStDataStream interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStDataStream インターフェースハンドルを取得します。
		@~japanese	@details	IStDataStream インターフェースハンドルを取得します。
		@~japanese	@param[in] pIStCallbackParamBaseHandle	IStCallbackParamBase インターフェースハンドル
		@~japanese	@param[in,out] pIStDataStreamHandle	IStDataStream インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStCallbackParamGenTLEventNewBuffer_GetIStDataStream_t)(const PStApiHandle_t pIStCallbackParamBaseHandle, PStApiHandle_t pIStDataStreamHandle);

	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStCallbackParamGenTLEventNewBuffer_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IStCallbackParamGenTLEventNewBuffer.
		@~english	@details	This structure holds the address of the C language wrapper function of IStCallbackParamGenTLEventNewBuffer.
		@~japanese	@brief	この構造体は IStCallbackParamGenTLEventNewBuffer のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IStCallbackParamGenTLEventNewBuffer のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_IStCallbackParamGenTLEventNewBuffer_Functions_t
	{
		/*!
			@copydoc PStApiTL_IStCallbackParamGenTLEventNewBuffer_GetIStDataStream_t()
		*/
		PStApiTL_IStCallbackParamGenTLEventNewBuffer_GetIStDataStream_t	GetIStDataStream;
	}StApi_IStCallbackParamGenTLEventNewBuffer_Functions_t, *PStApi_IStCallbackParamGenTLEventNewBuffer_Functions_t;

	/*************************************************************************/
	/* StApi::IStConverter */
	/*************************************************************************/
	/*!
		@~english	@brief	Acquire IStConverter interface handle.
		@~english	@details	Acquire IStConverter interface handle.
		@~english	@param[in] eConverterType	Type of converter.
		@~english	@param[in,out] pIStConverterHandle	IStConverter interface handle.
		@~english	@attention	If the acquired interface handle of IStConverter does not needed anymore, call IStConverter->Release(pIStConverterHandle) to release it. 
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	pIStConverterHandle IStConverter インターフェースハンドルを取得します。
		@~japanese	@details	IStConverter インターフェースハンドルを取得します。
		@~japanese	@param[in] eConverterType	使用するコンバーターのタイプ
		@~japanese	@param[in,out] pIStConverterHandle	IStConverter インターフェースハンドル
		@~japanese	@attention	 IStConverter インターフェースハンドル が不要になったら、 IStConverter->Release(pIStConverterHandle) を呼び出して解放してください。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStConverter_CreateIStConverter_t)(EStConverterType_t eConverterType, PStApiHandle_t pIStConverterHandle);
	
	/*!
		@~english	@brief	Get IStConverter handle.
		@~english	@details	Get IStConverter handle.
		@~english	@param[in] pSourceHandle	Interface handle that is enable to convert to IStConverter interface handle.
		@~english	@param[in,out] pIStConverterHandle	IStConverter interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStConverterハンドルを取得します。
		@~japanese	@details	IStConverterハンドルを取得します。
		@~japanese	@param[in] pSourceHandle	IStConverter インターフェースハンドルに変換可能なインターフェースハンドル
		@~japanese	@param[in,out] pIStConverterHandle	IStConverter インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStConverter_GetIStConverter_t)(const PStApiHandle_t pSourceHandle, PStApiHandle_t pIStConverterHandle);

	/*!
		@~english	@brief	Release object.
		@~english	@details	Release object.
		@~english	@param[in,out] pIStConverterHandle	IStConverter interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	解放します。
		@~japanese	@details	解放します。
		@~japanese	@param[in,out] pIStConverterHandle	IStConverter インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStConverter_Release_t)(PStApiHandle_t pIStConverterHandle);

	/*!
		@~english	@brief	Register a callback function.
		@~english	@details	Register a callback function.
		@~english	@param[in] pIStConverterHandle	IStConverter interface handle.
		@~english	@param[in]	pFunc	Callback function pointer.
		@~english	@param[in]	pContext	Argument for the callback function.
		@~english	@param[in,out] pIStRegisteredCallbackHandle	IStRegisteredCallback Interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	コールバック関数を登録します。
		@~japanese	@details	コールバック関数を登録します。
		@~japanese	@param[in] pIStConverterHandle	IStConverter インターフェースハンドル
		@~japanese	@param[in]	pFunc	コールバック関数として使用する関数
		@~japanese	@param[in]	pContext	コールバック関数に渡されるユーザー用パラメータ
		@~japanese	@param[in,out] pIStRegisteredCallbackHandle	IStRegisteredCallback インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStConverter_RegisterCallback_t)(const PStApiHandle_t pIStConverterHandle, fStCallbackFunc_t *pFunc, void* pContext, PStApiHandle_t pIStRegisteredCallbackHandle);

	/*!
		@~english	@brief	Acquire the interface handle of IStConverterInfo.
		@~english	@details	Acquire the interface handle of IStConverterInfo.
		@~english	@param[in] pIStConverterHandle	IStConverter interface handle.
		@~english	@param[in,out]	pIStConverterInfoHandle	IStConverterInfo interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStConverterInfo インターフェースハンドルを取得します。
		@~japanese	@details	IStConverterInfo インターフェースハンドルを取得します。
		@~japanese	@param[in] pIStConverterHandle	IStConverter インターフェースハンドル
		@~japanese	@param[in,out]	pIStConverterInfoHandle	IStConverterInfo インターフェースハンドル。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStConverter_GetIStConverterInfo_t)(const PStApiHandle_t pIStConverterHandle, PStApiHandle_t pIStConverterInfoHandle);

	/*!
		@~english	@brief	Perform image conversion.
		@~english	@details	Perform image conversion.
		@~english	@param[in] pIStConverterHandle	IStConverter interface handle.
		@~english	@param[in]	pSourceIStImageHandle	Input image buffer.
		@~english	@param[in]	pDestIStImageBufferHandle	Output image buffer.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	画像の変換処理を行います。
		@~japanese	@details	画像の変換処理を行います。
		@~japanese	@param[in] pIStConverterHandle	IStConverter インターフェースハンドル
		@~japanese	@param[in]	pSourceIStImageHandle	入力画像
		@~japanese	@param[in]	pDestIStImageBufferHandle	出力画像バッファー
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStConverter_Convert_t)(const PStApiHandle_t pIStConverterHandle, const PStApiHandle_t pSourceIStImageHandle, const PStApiHandle_t pDestIStImageBufferHandle);

	/*!
		@~english	@brief	Acquire interface handle of INodeMap.
		@~english	@details	Acquire interface handle of INodeMap.
		@~english	@param[in] pIStConverterHandle	IStConverter interface handle.
		@~english	@param[in,out]	pINodeMapHandle	INodeMap interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	INodeMap インターフェースハンドルを取得します。
		@~japanese	@details	INodeMap インターフェースハンドルを取得します。
		@~japanese	@param[in] pIStConverterHandle	IStConverter インターフェースハンドル
		@~japanese	@param[in,out]	pINodeMapHandle		INodeMap インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStConverter_GetINodeMap_t)(const PStApiHandle_t pIStConverterHandle, PStApiHandle_t pINodeMapHandle);

	/*!
		@~english	@brief	Get the line pitch alignment value of the converted image.
		@~english	@details	Get the line pitch alignment value of the converted image.
		@~english	@param[in] pIStConverterHandle	IStConverter interface handle.
		@~english	@param[out]	pnLinePitchAlignment	Line pitch alignment value.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	変換後の画像のラインピッチの最小単位を取得します。
		@~japanese	@details	変換後の画像のラインピッチの最小単位を取得します。
		@~japanese	@param[in] pIStConverterHandle	IStConverter インターフェースハンドル
		@~japanese	@param[out]	pnLinePitchAlignment	変換後の画像のラインピッチの最小単位
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStConverter_GetLinePitchAlignment_t)(const PStApiHandle_t pIStConverterHandle, size_t *pnLinePitchAlignment);

	/*!
		@~english	@brief	Set the line pitch alignment value of the converted image.
		@~english	@details	Set the line pitch alignment value of the converted image.
		@~english	@param[in] pIStConverterHandle	IStConverter interface handle.
		@~english	@param[in]	nLinePitchAlignment	Line pitch alignment value.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	変換後の画像のラインピッチの最小単位を設定します。
		@~japanese	@details	変換後の画像のラインピッチの最小単位を設定します。
		@~japanese	@param[in] pIStConverterHandle	IStConverter インターフェースハンドル
		@~japanese	@param[in]	nLinePitchAlignment	変換後の画像のラインピッチの最小単位
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStConverter_SetLinePitchAlignment_t)(const PStApiHandle_t pIStConverterHandle, size_t nLinePitchAlignment);

	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStConverter_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IStConverter.
		@~english	@details	This structure holds the address of the C language wrapper function of IStConverter.
		@~japanese	@brief	この構造体は IStConverter のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IStConverter のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_IStConverter_Functions_t
	{
		/*!
			@copydoc PStApiIP_IStConverter_CreateIStConverter_t()
		*/
		PStApiIP_IStConverter_CreateIStConverter_t	CreateIStConverter;

		/*!
			@copydoc PStApiIP_IStConverter_GetIStConverter_t()
		*/
		PStApiIP_IStConverter_GetIStConverter_t	GetIStConverter;

		/*!
			@copydoc PStApiIP_IStConverter_Release_t()
		*/
		PStApiIP_IStConverter_Release_t	Release;

		/*!
			@copydoc PStApiIP_IStConverter_RegisterCallback_t()
		*/
		PStApiIP_IStConverter_RegisterCallback_t	RegisterCallback;

		/*!
			@copydoc PStApiIP_IStConverter_GetIStConverterInfo_t()
		*/
		PStApiIP_IStConverter_GetIStConverterInfo_t	GetIStConverterInfo;

		/*!
			@copydoc PStApiIP_IStConverter_Convert_t()
		*/
		PStApiIP_IStConverter_Convert_t	Convert;

		/*!
			@copydoc PStApiIP_IStConverter_GetINodeMap_t()
		*/
		PStApiIP_IStConverter_GetINodeMap_t	GetINodeMap;

		/*!
			@copydoc PStApiIP_IStConverter_GetLinePitchAlignment_t()
		*/
		PStApiIP_IStConverter_GetLinePitchAlignment_t	GetLinePitchAlignment;

		/*!
			@copydoc PStApiIP_IStConverter_SetLinePitchAlignment_t()
		*/
		PStApiIP_IStConverter_SetLinePitchAlignment_t	SetLinePitchAlignment;
	}StApi_IStConverter_Functions_t, *PStApi_IStConverter_Functions_t;

	/*************************************************************************/
	/* StApi::IStConverterInfo */
	/*************************************************************************/
	/*!
		@~english	@brief	Acquire the converter type.
		@~english	@details	Acquire the converter type.
		@~english	@param[in] pIStConverterInfoHandle	IStConverterInfo interface handle.
		@~english	@param[out]	peValue	Type of converter.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	変換タイプを取得します。
		@~japanese	@details	変換タイプを取得します。
		@~japanese	@param[in] pIStConverterInfoHandle	IStConverterInfo インターフェースハンドル
		@~english	@param[out]	peValue	変換タイプ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStConverterInfo_GetConverterType_t)(const PStApiHandle_t pIStConverterInfoHandle, EStConverterType_t *peValue);

	/*!
		@~english	@brief	Acquire converter name.
		@~english	@details	Acquire converter name.
		@~english	@param[in] pIStConverterInfoHandle	IStConverterInfo interface handle.
		@~english	@param[in,out]	szText	Converter name.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	変換名を取得します。
		@~japanese	@details	変換名を取得します。
		@~japanese	@param[in] pIStConverterInfoHandle	IStConverterInfo インターフェースハンドル
		@~japanese	@param[in,out] szText	変換名
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStConverterInfo_GetConverterNameW_t)(const PStApiHandle_t pIStConverterInfoHandle, wchar_t *szText, size_t *pnLen);

	/*!
		@~english	@brief	Acquire converter name.
		@~english	@details	Acquire converter name.
		@~english	@param[in] pIStConverterInfoHandle	IStConverterInfo interface handle.
		@~english	@param[in,out]	szText	Converter name.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	変換名を取得します。
		@~japanese	@details	変換名を取得します。
		@~japanese	@param[in] pIStConverterInfoHandle	IStConverterInfo インターフェースハンドル
		@~japanese	@param[in,out] szText	変換名
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStConverterInfo_GetConverterNameA_t)(const PStApiHandle_t pIStConverterInfoHandle, char *szText, size_t *pnLen);

	/*!
		@~english	@brief	Check if the pixel format is supported.
		@~english	@details	Check if the pixel format is supported.
		@~english	@param[in] pIStConverterInfoHandle	IStConverterInfo interface handle.
		@~english	@param[in] ePFNC	The pixel format.
		@~english	@param[out]	pbValue	True if supported.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	指定したピクセルフォーマットの変換に対応しているか確認します。
		@~japanese	@details	指定したピクセルフォーマットの変換に対応しているか確認します。
		@~japanese	@param[in] pIStConverterInfoHandle	IStConverterInfo インターフェースハンドル
		@~japanese	@param[in] ePFNC	ピクセルフォーマット値
		@~english	@param[out]	pbValue	対応している場合、 true が返されます。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStConverterInfo_IsSupported_t)(const PStApiHandle_t pIStConverterInfoHandle, EStPixelFormatNamingConvention_t ePFNC, bool8_t *pbValue);

	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStConverterInfo_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IStConverterInfo.
		@~english	@details	This structure holds the address of the C language wrapper function of IStConverterInfo.
		@~japanese	@brief	この構造体は IStConverterInfo のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IStConverterInfo のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_IStConverterInfo_Functions_t
	{
		/*!
			@copydoc PStApiIP_IStConverterInfo_GetConverterType_t()
		*/
		PStApiIP_IStConverterInfo_GetConverterType_t	GetConverterType;

		/*!
			@copydoc PStApiIP_IStConverterInfo_GetConverterNameW_t()
		*/
		PStApiIP_IStConverterInfo_GetConverterNameW_t	GetConverterNameW;

		/*!
			@copydoc PStApiIP_IStConverterInfo_GetConverterNameA_t()
		*/
		PStApiIP_IStConverterInfo_GetConverterNameA_t	GetConverterNameA;

		/*!
			@copydoc PStApiIP_IStConverterInfo_IsSupported_t()
		*/
		PStApiIP_IStConverterInfo_IsSupported_t	IsSupported;
	}StApi_IStConverterInfo_Functions_t, *PStApi_IStConverterInfo_Functions_t;
	
	/*************************************************************************/
	/* StApi::IStReverseConverter */
	/*************************************************************************/
	/*!
		@~english	@brief	Get IStReverseConverter handle.
		@~english	@details	Get IStReverseConverter handle.
		@~english	@param[in] pSourceHandle	Interface handle that is enable to convert to IStReverseConverter interface handle.
		@~english	@param[in,out] pIStReverseConverterHandle	IStReverseConverter interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStReverseConverterハンドルを取得します。
		@~japanese	@details	IStReverseConverterハンドルを取得します。
		@~japanese	@param[in] pSourceHandle	IStReverseConverter インターフェースハンドルに変換可能なインターフェースハンドル
		@~japanese	@param[in,out] pIStReverseConverterHandle	IStReverseConverter インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStReverseConverter_GetIStReverseConverter_t)(const PStApiHandle_t pSourceHandle, PStApiHandle_t pIStReverseConverterHandle);

	/*!
		@~english	@brief	Get the current setting of horizontal image mirroring.
		@~english	@details	Get the current setting of horizontal image mirroring.
		@~english	@param[in] pIStReverseConverterHandle	IStReverseConverter interface handle.
		@~english	@param[out] pbValue	True if the current setting is enabled.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	左右反転設定を取得します。
		@~japanese	@details	左右反転設定を取得します。
		@~japanese	@param[in] pIStReverseConverterHandle	IStReverseConverter インターフェースハンドル
		@~english	@param[out]	pbValue	左右反転が有効な場合、 true を返します。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStReverseConverter_GetReverseX_t)(const PStApiHandle_t pIStReverseConverterHandle, bool8_t *pbValue);

	/*!
		@~english	@brief	Set horizontal image mirroring setting.
		@~english	@details	Set horizontal image mirroring setting.
		@~english	@param[in] pIStReverseConverterHandle	IStReverseConverter interface handle.
		@~english	@param[in]	value	True to enable; false to disable.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	左右反転を設定します。
		@~japanese	@details	左右反転を設定します。
		@~japanese	@param[in] pIStReverseConverterHandle	IStReverseConverter インターフェースハンドル
		@~japanese	@param[in]	value	左右反転を行う場合、 true を指定します。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStReverseConverter_SetReverseX_t)(const PStApiHandle_t pIStReverseConverterHandle, bool8_t value);

	/*!
		@~english	@brief	Get the current setting of vertical image mirroring.
		@~english	@details	Get the current setting of vertical image mirroring.
		@~english	@param[in] pIStReverseConverterHandle	IStReverseConverter interface handle.
		@~english	@param[out] pbValue	True if the current setting is enabled.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	上下反転設定を取得します。
		@~japanese	@details	上下反転設定を取得します。
		@~japanese	@param[in] pIStReverseConverterHandle	IStReverseConverter インターフェースハンドル
		@~english	@param[out]	pbValue	上下反転が有効な場合、 true を返します。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStReverseConverter_GetReverseY_t)(const PStApiHandle_t pIStReverseConverterHandle, bool8_t *pbValue);

	/*!
		@~english	@brief	Set vertical image mirroring setting.
		@~english	@details	Set vertical image mirroring setting.
		@~english	@param[in] pIStReverseConverterHandle	IStReverseConverter interface handle.
		@~english	@param[in]	value	True to enable; false to disable.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	上下反転を設定します。
		@~japanese	@details	上下反転を設定します。
		@~japanese	@param[in] pIStReverseConverterHandle	IStReverseConverter インターフェースハンドル
		@~japanese	@param[in]	value	上下反転を行う場合、 true を指定します。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStReverseConverter_SetReverseY_t)(const PStApiHandle_t pIStReverseConverterHandle, bool8_t value);

	/*!
		@~english	@brief	Get current setting of image rotation.
		@~english	@details	Get current setting of image rotation.
		@~english	@param[in] pIStReverseConverterHandle	IStReverseConverter interface handle.
		@~english	@param[out] peValue	Image rotation setting.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	回転モードを取得します。
		@~japanese	@details	回転モードを取得します。
		@~japanese	@param[in] pIStReverseConverterHandle	IStReverseConverter インターフェースハンドル
		@~english	@param[out]	peValue	回転モード
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStReverseConverter_GetRotationMode_t)(const PStApiHandle_t pIStReverseConverterHandle, EStRotationMode_t *peValue);

	/*!
		@~english	@brief	Set current setting of image rotation.
		@~english	@details	Set current setting of image rotation.
		@~english	@param[in] pIStReverseConverterHandle	IStReverseConverter interface handle.
		@~english	@param[in]	eRM	Image rotation setting.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	回転モードを設定します。
		@~japanese	@details	回転モードを設定します。
		@~japanese	@param[in] pIStReverseConverterHandle	IStReverseConverter インターフェースハンドル
		@~japanese	@param[in]	eRM	回転モード
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStReverseConverter_SetRotationMode_t)(const PStApiHandle_t pIStReverseConverterHandle, EStRotationMode_t eRM);
	
	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStReverseConverter_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IStReverseConverter.
		@~english	@details	This structure holds the address of the C language wrapper function of IStReverseConverter.
		@~japanese	@brief	この構造体は IStReverseConverter のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IStReverseConverter のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_IStReverseConverter_Functions_t
	{
		/*!
		@copydoc PStApi_IStReverseConverter_GetIStReverseConverter_t()
		*/
		PStApiIP_IStReverseConverter_GetIStReverseConverter_t	GetIStReverseConverter;

		/*!
		@copydoc PStApiIP_IStReverseConverter_GetReverseX_t()
		*/
		PStApiIP_IStReverseConverter_GetReverseX_t	GetReverseX;

		/*!
		@copydoc PStApiIP_IStReverseConverter_SetReverseX_t()
		*/
		PStApiIP_IStReverseConverter_SetReverseX_t	SetReverseX;

		/*!
		@copydoc PStApiIP_IStReverseConverter_GetReverseY_t()
		*/
		PStApiIP_IStReverseConverter_GetReverseY_t	GetReverseY;

		/*!
		@copydoc PStApiIP_IStReverseConverter_SetReverseY_t()
		*/
		PStApiIP_IStReverseConverter_SetReverseY_t	SetReverseY;

		/*!
		@copydoc PStApiIP_IStReverseConverter_GetRotationMode_t()
		*/
		PStApiIP_IStReverseConverter_GetRotationMode_t	GetRotationMode;

		/*!
		@copydoc PStApiIP_IStReverseConverter_SetRotationMode_t()
		*/
		PStApiIP_IStReverseConverter_SetRotationMode_t	SetRotationMode;
	}StApi_IStReverseConverter_Functions_t, *PStApi_IStReverseConverter_Functions_t;

	/*************************************************************************/
	/* StApi::IStPixelFormatConverter */
	/*************************************************************************/
	/*!
		@~english	@brief	Get IStPixelFormatConverter handle.
		@~english	@details	Get IStPixelFormatConverter handle.
		@~english	@param[in] pSourceHandle	Interface handle that is enable to convert to IStPixelFormatConverter interface handle.
		@~english	@param[in,out] pIStPixelFormatConverterHandle	IStPixelFormatConverter interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStPixelFormatConverterハンドルを取得します。
		@~japanese	@details	IStPixelFormatConverterハンドルを取得します。
		@~japanese	@param[in] pSourceHandle	IStPixelFormatConverter インターフェースハンドルに変換可能なインターフェースハンドル
		@~japanese	@param[in,out] pIStPixelFormatConverterHandle	IStPixelFormatConverter インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStPixelFormatConverter_GetIStPixelFormatConverter_t)(const PStApiHandle_t pSourceHandle, PStApiHandle_t pIStPixelFormatConverterHandle);

	/*!
		@~english	@brief	Acquire the pixel format of conversion target.
		@~english	@details	Acquire the pixel format of conversion target.
		@~english	@param[in] pIStPixelFormatConverterHandle	IStPixelFormatConverter interface handle.
		@~english	@param[out]	peValue	Pixel format.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	変換先のピクセルフォーマット値を取得します。
		@~japanese	@details	変換先のピクセルフォーマット値を取得します。
		@~japanese	@param[in] pIStPixelFormatConverterHandle	IStPixelFormatConverter インターフェースハンドル
		@~japanese	@param[out]	peValue	変換先のピクセルフォーマット値
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStPixelFormatConverter_GetDestinationPixelFormat_t)(const PStApiHandle_t pIStPixelFormatConverterHandle, EStPixelFormatNamingConvention_t *peValue);

	/*!
		@~english	@brief	Set the pixel format of conversion target.
		@~english	@details	Set the pixel format of conversion target.
		@~english	@param[in] pIStPixelFormatConverterHandle	IStPixelFormatConverter interface handle.
		@~english	@param[in]	ePFNC	Pixel format.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	変換先のピクセルフォーマット値を設定します。
		@~japanese	@details	変換先のピクセルフォーマット値を設定します。
		@~japanese	@param[in] pIStPixelFormatConverterHandle	IStPixelFormatConverter インターフェースハンドル
		@~japanese	@param[in]	ePFNC	変換先のピクセルフォーマット値
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStPixelFormatConverter_SetDestinationPixelFormat_t)(const PStApiHandle_t pIStPixelFormatConverterHandle, EStPixelFormatNamingConvention_t ePFNC);

	/*!
		@~english	@brief	Acquire the setting of Y-axis reversion.
		@~english	@details	Acquire the setting of Y-axis reversion.
		@~english	@param[in] pIStPixelFormatConverterHandle	IStPixelFormatConverter interface handle.
		@~english	@param[out]	pbValue	Y-axis reversion setting.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	上下反転設定を取得します。
		@~japanese	@details	上下反転設定を取得します。
		@~japanese	@param[in] pIStPixelFormatConverterHandle	IStPixelFormatConverter インターフェースハンドル
		@~japanese	@param[out]	pbValue	上下反転が有効な場合、 true を返します。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStPixelFormatConverter_GetReverseY_t)(const PStApiHandle_t pIStPixelFormatConverterHandle, bool8_t *pbValue);

	/*!
		@~english	@brief	Set the setting of Y-axis reversion.
		@~english	@details	Set the setting of Y-axis reversion.
		@~english	@attention	This function may not work on some pixel format. If the image is in Bayer pixel format, the output image format will be changed during the conversion.
		@~english	@param[in] pIStPixelFormatConverterHandle	IStPixelFormatConverter interface handle.
		@~english	@param[in]	value	True to apply Y-axis reversion.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	上下反転を設定します。
		@~japanese	@details	上下反転を設定します。
		@~japanese	@attention	ピクセルフォーマットによっては、機能しないことがあります。また、上下反転を有効にした状態でベイヤー形式の画像を入力した場合、出力される画像のフォーマットが変化する場合があります。
		@~japanese	@param[in] pIStPixelFormatConverterHandle	IStPixelFormatConverter インターフェースハンドル
		@~japanese	@param[in]	value	上下反転を行う場合、 true を指定します。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStPixelFormatConverter_SetReverseY_t)(const PStApiHandle_t pIStPixelFormatConverterHandle, bool8_t value);

	/*!
		@~english	@brief	Get the current Bayer interpolation method.
		@~english	@details	Get the current Bayer interpolation method.
		@~english	@param[in] pIStPixelFormatConverterHandle	IStPixelFormatConverter interface handle.
		@~english	@param[out]	peValue	Bayer interpolation method.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ベイヤー変換処理設定を取得します。
		@~japanese	@details	ベイヤー変換処理設定を取得します。
		@~japanese	@param[in] pIStPixelFormatConverterHandle	IStPixelFormatConverter インターフェースハンドル
		@~japanese	@param[out]	peValue	ベイヤー変換処理設定
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStPixelFormatConverter_GetBayerInterpolationMethod_t)(const PStApiHandle_t pIStPixelFormatConverterHandle, EStBayerInterpolationMethod_t *peValue);

	/*!
		@~english	@brief	Set the Bayer interpolation method.
		@~english	@details	Set the Bayer interpolation method.
		@~english	@attention	This setting only takes effect on image with Bayer pixel format.
		@~english	@param[in] pIStPixelFormatConverterHandle	IStPixelFormatConverter interface handle.
		@~english	@param[in]	eBIM	Bayer interpolation method.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ベイヤー変換処理を設定します。
		@~japanese	@details	ベイヤー変換処理を設定します。
		@~japanese	@attention	この設定はベイヤー配列の入力画像にのみ有効になります。
		@~japanese	@param[in] pIStPixelFormatConverterHandle	IStPixelFormatConverter インターフェースハンドル
		@~japanese	@param[in]	eBIM	ベイヤー変換処理設定 
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStPixelFormatConverter_SetBayerInterpolationMethod_t)(const PStApiHandle_t pIStPixelFormatConverterHandle, EStBayerInterpolationMethod_t eBIM);

	/*!
		@~english	@brief	Get the Gamma value of conversion.
		@~english	@details	Get the Gamma value of conversion.
		@~english	@param[in] pIStPixelFormatConverterHandle	IStPixelFormatConverter interface handle.
		@~english	@param[out]	pdblValue	Gamma value.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ガンマ補正値を取得します。
		@~japanese	@details	ガンマ補正値を取得します。
		@~japanese	@param[in] pIStPixelFormatConverterHandle	IStPixelFormatConverter インターフェースハンドル
		@~japanese	@param[out]	pdblValue	ガンマ補正値
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStPixelFormatConverter_GetGammaValue_t)(const PStApiHandle_t pIStPixelFormatConverterHandle, double *pdblValue);

	/*!
		@~english	@brief	Set the Gamma value of conversion.
		@~english	@details	Set the Gamma value of conversion.
		@~english	@attention	This setting only takes effect on image with changing bit during the conversion.
		@~english	@param[in] pIStPixelFormatConverterHandle	IStPixelFormatConverter interface handle.
		@~english	@param[in]	value	Gamma value(0 ~ 4.0).
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ガンマ補正値を設定します。
		@~japanese	@details	ガンマ補正値を設定します。
		@~japanese	@attention	この設定は変換時にビット数が変化する場合のみ有効になります。
		@~japanese	@param[in] pIStPixelFormatConverterHandle	IStPixelFormatConverter インターフェースハンドル
		@~japanese	@param[in]	value	ガンマ補正値(0.0～4.0)
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStPixelFormatConverter_SetGammaValue_t)(const PStApiHandle_t pIStPixelFormatConverterHandle, double value);

	/*!
		@~english	@brief	Acquire current status of target pixel format node lock.
		@~english	@details	Acquire current status of target pixel format node lock.
		@~english	@param[in] pIStPixelFormatConverterHandle	IStPixelFormatConverter interface handle.
		@~english	@param[out]	pbValue	Lock status. True if locked; false otherwise.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	変換先のピクセルフォーマットノードのロック状態を取得します。
		@~japanese	@details	変換先のピクセルフォーマットノードのロック状態を取得します。
		@~japanese	@param[in] pIStPixelFormatConverterHandle	IStPixelFormatConverter インターフェースハンドル
		@~japanese	@param[out]	pbValue	変換先のピクセルフォーマットノードがロックされている場合、 true が返されます。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStPixelFormatConverter_GetDestinationPixelFormatNodeLock_t)(const PStApiHandle_t pIStPixelFormatConverterHandle, bool8_t *pbValue);
		
	/*!
		@~english	@brief	Set target pixel format node lock. This will prevent the pixel format modification from GUI.
		@~english	@details	Set target pixel format node lock. This will prevent the pixel format modification from GUI.
		@~english	@param[in] pIStPixelFormatConverterHandle	IStPixelFormatConverter interface handle.
		@~english	@param[in]	value	True to lock; false to unlock.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	変換先のピクセルフォーマットノードのロック状態を設定します。
		@~japanese	@details	変換先のピクセルフォーマットノードのロック状態を設定します。
		@~japanese	@param[in] pIStPixelFormatConverterHandle	IStPixelFormatConverter インターフェースハンドル
		@~japanese	@param[in]	value	変換先のピクセルフォーマットノードをロックする場合、 true を指定します。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStPixelFormatConverter_SetDestinationPixelFormatNodeLock_t)(const PStApiHandle_t pIStPixelFormatConverterHandle, bool8_t value);

	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStPixelFormatConverter_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IStPixelFormatConverter.
		@~english	@details	This structure holds the address of the C language wrapper function of IStPixelFormatConverter.
		@~japanese	@brief	この構造体は IStPixelFormatConverter のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IStPixelFormatConverter のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_IStPixelFormatConverter_Functions_t
	{
		/*!
			@copydoc PStApiIP_IStPixelFormatConverter_GetIStPixelFormatConverter_t()
		*/
		PStApiIP_IStPixelFormatConverter_GetIStPixelFormatConverter_t	GetIStPixelFormatConverter;

		/*!
			@copydoc PStApiIP_IStPixelFormatConverter_GetDestinationPixelFormat_t()
		*/
		PStApiIP_IStPixelFormatConverter_GetDestinationPixelFormat_t	GetDestinationPixelFormat;
		/*!
			@copydoc PStApiIP_IStPixelFormatConverter_SetDestinationPixelFormat_t()
		*/
		PStApiIP_IStPixelFormatConverter_SetDestinationPixelFormat_t	SetDestinationPixelFormat;
		/*!
			@copydoc PStApiIP_IStPixelFormatConverter_GetReverseY_t()
		*/
		PStApiIP_IStPixelFormatConverter_GetReverseY_t	GetReverseY;
		/*!
			@copydoc PStApiIP_IStPixelFormatConverter_SetReverseY_t()
		*/
		PStApiIP_IStPixelFormatConverter_SetReverseY_t	SetReverseY;
		/*!
			@copydoc PStApiIP_IStPixelFormatConverter_GetBayerInterpolationMethod_t()
		*/
		PStApiIP_IStPixelFormatConverter_GetBayerInterpolationMethod_t	GetBayerInterpolationMethod;
		/*!
		@copydoc PStApiIP_IStPixelFormatConverter_SetBayerInterpolationMethod_t()
		*/
		PStApiIP_IStPixelFormatConverter_SetBayerInterpolationMethod_t	SetBayerInterpolationMethod;
		/*!
			@copydoc PStApiIP_IStPixelFormatConverter_GetGammaValue_t()
		*/
		PStApiIP_IStPixelFormatConverter_GetGammaValue_t	GetGammaValue;
		/*!
			@copydoc PStApiIP_IStPixelFormatConverter_SetGammaValue_t()
		*/
		PStApiIP_IStPixelFormatConverter_SetGammaValue_t	SetGammaValue;
		/*!
			@copydoc PStApiIP_IStPixelFormatConverter_GetDestinationPixelFormatNodeLock_t()
		*/
		PStApiIP_IStPixelFormatConverter_GetDestinationPixelFormatNodeLock_t	GetDestinationPixelFormatNodeLock;
		/*!
			@copydoc PStApiIP_IStPixelFormatConverter_SetDestinationPixelFormatNodeLock_t()
		*/
		PStApiIP_IStPixelFormatConverter_SetDestinationPixelFormatNodeLock_t	SetDestinationPixelFormatNodeLock;
	}StApi_IStPixelFormatConverter_Functions_t, *PStApi_IStPixelFormatConverter_Functions_t;

	/*************************************************************************/
	/* StApi::IStFilter */
	/*************************************************************************/
	/*!
		@~english	@brief	Acquire IStFilter interface handle.
		@~english	@details	Acquire IStFilter interface handle.
		@~english	@param[in] eFilterType	Type of filter.
		@~english	@param[in,out] pIStFilterHandle	IStFilter interface handle.
		@~english	@attention	If the acquired interface handle of IStFilter does not needed anymore, call IStFilter->Release(pIStFilterHandle) to release it. 
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	pIStConverterHandle IStFilter インターフェースハンドルを取得します。
		@~japanese	@details	IStFilter インターフェースハンドルを取得します。
		@~japanese	@param[in] eFilterType	使用するフィルターのタイプ
		@~japanese	@param[in,out] pIStFilterHandle	IStFilter インターフェースハンドル
		@~japanese	@attention	 IStFilter インターフェースハンドル が不要になったら、 IStFilter->Release(pIStFilterHandle) を呼び出して解放してください。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStFilter_CreateIStFilter_t)(EStFilterType_t eFilterType, PStApiHandle_t pIStFilterHandle);
	
	/*!
		@~english	@brief	Get IStFilter handle.
		@~english	@details	Get IStFilter handle.
		@~english	@param[in] pSourceHandle	Interface handle that is enable to convert to IStFilter interface handle.
		@~english	@param[in,out] pIStFilterHandle	IStFilter interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStFilterハンドルを取得します。
		@~japanese	@details	IStFilterハンドルを取得します。
		@~japanese	@param[in] pSourceHandle	IStFilter インターフェースハンドルに変換可能なインターフェースハンドル
		@~japanese	@param[in,out] pIStFilterHandle	IStFilter インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStFilter_GetIStFilter_t)(const PStApiHandle_t pSourceHandle, PStApiHandle_t pIStFilterHandle);

	/*!
		@~english	@brief	Release object.
		@~english	@details	Release object.
		@~english	@param[in] pIStFilterHandle	IStFilter interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	解放します。
		@~japanese	@details	解放します。
		@~japanese	@param[in] pIStFilterHandle	IStFilter インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStFilter_Release_t)(PStApiHandle_t pIStFilterHandle);

	/*!
		@~english	@brief	Register a callback function.
		@~english	@details	Register a callback function.
		@~english	@param[in] pIStFilterHandle	IStFilter interface handle.
		@~english	@param[in]	pFunc	Callback function pointer.
		@~english	@param[in]	pContext	Argument for the callback function.
		@~english	@param[in,out] pIStRegisteredCallbackHandle	IStRegisteredCallback Interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	コールバック関数を登録します。
		@~japanese	@details	コールバック関数を登録します。
		@~japanese	@param[in] pIStFilterHandle	IStFilter インターフェースハンドル
		@~japanese	@param[in]	pFunc	コールバック関数として使用する関数
		@~japanese	@param[in]	pContext	コールバック関数に渡されるユーザー用パラメータ
		@~japanese	@param[in,out] pIStRegisteredCallbackHandle	IStRegisteredCallback インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStFilter_RegisterCallback_t)(const PStApiHandle_t pIStFilterHandle, fStCallbackFunc_t *pFunc, void* pContext, PStApiHandle_t pIStRegisteredCallbackHandle);

	/*!
		@~english	@brief	Acquire the interface handle of IStConverterInfo.
		@~english	@details	Acquire the interface handle of IStConverterInfo.
		@~english	@param[in] pIStFilterHandle	IStFilter interface handle.
		@~english	@param[in,out]	pIStFilterInfoHandle	IStFilterInfo interface pointer.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStConverterInfo インターフェースハンドルを取得します。
		@~japanese	@details	IStConverterInfo インターフェースハンドルを取得します。
		@~japanese	@param[in] pIStFilterHandle	IStFilter インターフェースハンドル
		@~japanese	@param[in,out]	pIStFilterInfoHandle	IStFilterInfo インターフェースハンドル。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStFilter_GetIStFilterInfo_t)(const PStApiHandle_t pIStFilterHandle, PStApiHandle_t pIStFilterInfoHandle);
	
	/*!
		@~english	@brief	Perform image conversion.
		@~english	@details	Perform image conversion.
		@~english	@param[in] pIStFilterHandle	IStFilter interface handle.
		@~english	@param[in,out]	pIStImageHandle	Input/Output image buffer.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	画像の変換処理を行います。
		@~japanese	@details	画像の変換処理を行います。
		@~japanese	@param[in] pIStFilterHandle	IStFilter インターフェースハンドル
		@~japanese	@param[in,out]	pIStImageHandle	入出力画像バッファー
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStFilter_Filter_t)(const PStApiHandle_t pIStFilterHandle, const PStApiHandle_t pIStImageHandle);

	/*!
		@~english	@brief	Acquire interface handle of INodeMap.
		@~english	@details	Acquire interface handle of INodeMap.
		@~english	@param[in] pIStFilterHandle	IStFilter interface handle.
		@~english	@param[in,out]	pINodeMapHandle	INodeMap interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	INodeMap インターフェースハンドルを取得します。
		@~japanese	@details	INodeMap インターフェースハンドルを取得します。
		@~japanese	@param[in] pIStFilterHandle	IStFilter インターフェースハンドル
		@~japanese	@param[in,out]	pINodeMapHandle		INodeMap インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStFilter_GetINodeMap_t)(const PStApiHandle_t pIStFilterHandle, PStApiHandle_t pINodeMapHandle);

	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStFilter_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IStFilter.
		@~english	@details	This structure holds the address of the C language wrapper function of IStFilter.
		@~japanese	@brief	この構造体は IStFilter のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IStFilter のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_IStFilter_Functions_t
	{
		/*!
			@copydoc PStApiIP_IStFilter_CreateIStFilter_t()
		*/
		PStApiIP_IStFilter_CreateIStFilter_t				CreateIStFilter;

		/*!
			@copydoc PStApiIP_IStFilter_GetIStFilter_t()
		*/
		PStApiIP_IStFilter_GetIStFilter_t				GetIStFilter;

		/*!
			@copydoc PStApiIP_IStFilter_Release_t()
		*/
		PStApiIP_IStFilter_Release_t						Release;
			
		/*!
			@copydoc PStApiIP_IStFilter_RegisterCallback_t()
		*/
		PStApiIP_IStFilter_RegisterCallback_t				RegisterCallback;

		/*!
			@copydoc PStApiIP_IStFilter_GetIStFilterInfo_t()
		*/
		PStApiIP_IStFilter_GetIStFilterInfo_t				GetIStFilterInfo;
			
		/*!
			@copydoc PStApiIP_IStFilter_Filter_t()
		*/
		PStApiIP_IStFilter_Filter_t							Filter;

		/*!
			@copydoc PStApiIP_IStFilter_GetINodeMap_t()
		*/
		PStApiIP_IStFilter_GetINodeMap_t					GetINodeMap;
	}StApi_IStFilter_Functions_t, *PStApi_IStFilter_Functions_t;
	

	/*************************************************************************/
	/* StApi::IStFilterArray */
	/*************************************************************************/
	/*!
		@~english	@brief	Perform image conversion.
		@~english	@details	Perform image conversion.
		@~english	@param[in] pIStFilterHandleArray	IStFilter interface handles array.
		@~english	@param[in] nCount	Count of IStFilter interface handles.
		@~english	@param[in,out]	pIStImageHandle	Input/Output image buffer.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	画像の変換処理を行います。
		@~japanese	@details	画像の変換処理を行います。
		@~japanese	@param[in] pIStFilterHandleArray	IStFilter インターフェースハンドル配列
		@~japanese	@param[in] nCount	IStFilter インターフェースハンドルの数
		@~japanese	@param[in,out]	pIStImageHandle	入出力画像バッファー
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStFilterArray_Filter_t)(const PStApiHandle_t pIStFilterHandleArray, size_t nCount, const PStApiHandle_t pIStImageHandle);
	
	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStFilter_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of CIStFilterArray.
		@~english	@details	This structure holds the address of the C language wrapper function of CIStFilterArray.
		@~japanese	@brief	この構造体は CIStFilterArray のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は CIStFilterArray のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_IStFilterArray_Functions_t
	{
		/*!
			@copydoc PStApiIP_IStFilterArray_Filter_t()
		*/
		PStApiIP_IStFilterArray_Filter_t					Filter;
	}StApi_IStFilterArray_Functions_t, *PStApi_IStFilterArray_Functions_t;

	/*************************************************************************/
	/* StApi::IStFilterInfo */
	/*************************************************************************/
	
	/*!
		@~english	@brief	Acquire IStFilterInfo. IStFilterInfo is used for obtaining the filter's supported pixel format.
		@~english	@details	Acquire IStFilterInfo. IStFilterInfo is used for obtaining the filter's supported pixel format.
		@~english	@param[in] eFilterType	Type of filter.
		@~english	@param[in,out] pIStFilterInfoHandle IStFilterInfo interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStFilterInfo インターフェースポインターを取得します。
		@~japanese	@details	IStFilterInfo インターフェースポインターを取得します。
		@~japanese	@param[in] eFilterType	使用するフィルターのタイプ
		@~japanese	@param[in,out] pIStFilterInfoHandle IStFilterInfo インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStFilterInfo_GetIStFilterInfo_t)(EStFilterType_t eFilterType, PStApiHandle_t pIStFilerInfoHandle);

	/*!
		@~english	@brief	Acquire filter type.
		@~english	@details	Acquire filter type.
		@~english	@param[in] pIStFilterInfoHandle IStFilterInfo interface handle.
		@~english	@param[out]	peValue	Filter type.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	フィルタータイプを取得します。
		@~japanese	@details	フィルタータイプを取得します。
		@~japanese	@param[in] pIStFilterInfoHandle IStFilterInfo インターフェースハンドル
		@~japanese	@param[out] peValue	フィルタータイプ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStFilterInfo_GetFilterType_t)(const PStApiHandle_t pIStFilterInfoHandle, EStFilterType_t *peValue);

	/*!
		@~english	@brief	Acquire filter name.
		@~english	@details	Acquire filter name.
		@~english	@param[in] pIStFilterInfoHandle	IStFilterInfo interface handle.
		@~english	@param[in,out]	szText	Filter name.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	フィルター名を取得します。
		@~japanese	@details	フィルター名を取得します。
		@~japanese	@param[in]	pIStFilterInfoHandle	IStFilterInfo インターフェースハンドル
		@~japanese	@param[in,out] szText	フィルター名
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStFilterInfo_GetFilterNameW_t)(const PStApiHandle_t pIStFilterInfoHandle, wchar_t *szText, size_t *pnLen);

	/*!
		@~english	@brief	Acquire filter name.
		@~english	@details	Acquire filter name.
		@~english	@param[in] pIStFilterInfoHandle	IStFilterInfo interface handle.
		@~english	@param[in,out]	szText	Filter name.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	フィルター名を取得します。
		@~japanese	@details	フィルター名を取得します。
		@~japanese	@param[in]	pIStFilterInfoHandle	IStFilterInfo インターフェースハンドル
		@~japanese	@param[in,out] szText	フィルター名
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStFilterInfo_GetFilterNameA_t)(const PStApiHandle_t pIStFilterInfoHandle, char *szText, size_t *pnLen);

	/*!
		@~english	@brief	Check if the pixel format is supported.
		@~english	@details	    Check if the pixel format is supported.
		@~english	@param[in] pIStFilterInfoHandle	IStFilterInfo interface handle.
		@~english	@param[in]	nValue	Pixel format.
		@~english	@param[out]	pbValue	Return true if the pixel format is supported..
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	指定したピクセルフォーマットに対応しているかどうか確認します。
		@~japanese	@details	指定したピクセルフォーマットに対応しているかどうか確認します。
		@~japanese	@param[in]	pIStFilterInfoHandle	IStFilterInfo インターフェースハンドル
		@~japanese	@param[in]	nValue	ピクセルフォーマット
		@~japanese	@param[out] pbValue	対応している場合、 true が返されます。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStFilterInfo_IsSupported_t)(const PStApiHandle_t pIStFilterInfoHandle, EStPixelFormatNamingConvention_t nValue, bool8_t *pbValue);

	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStFilterInfo_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IStFilterInfo.
		@~english	@details	This structure holds the address of the C language wrapper function of IStFilterInfo.
		@~japanese	@brief	この構造体は IStFilterInfo のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IStFilterInfo のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_IStFilterInfo_Functions_t
	{
		/*!
		@copydoc PStApiIP_IStFilterInfo_GetIStFilterInfo_t()
		*/
		PStApiIP_IStFilterInfo_GetIStFilterInfo_t				GetIStFilterInfo;

		/*!
		@copydoc PStApiIP_IStFilterInfo_GetFilterType_t()
		*/
		PStApiIP_IStFilterInfo_GetFilterType_t				GetFilterType;

		/*!
			@copydoc PStApiIP_IStFilterInfo_GetFilterNameW_t()
		*/
		PStApiIP_IStFilterInfo_GetFilterNameW_t				GetFilterNameW;

		/*!
			@copydoc PStApiIP_IStFilterInfo_GetFilterNameA_t()
		*/
		PStApiIP_IStFilterInfo_GetFilterNameA_t				GetFilterNameA;

		/*!
			@copydoc PStApiIP_IStFilterInfo_IsSupported_t()
		*/
		PStApiIP_IStFilterInfo_IsSupported_t				IsSupported;
	}StApi_IStFilterInfo_Functions_t, *PStApi_IStFilterInfo_Functions_t;

	/*************************************************************************/
	/* StApi::IStBalanceRatioFilter */
	/*************************************************************************/
	/*!
		@~english	@brief	Get IStBalanceRatioFilter handle.
		@~english	@details	Get IStBalanceRatioFilter handle.
		@~english	@param[in] pSourceHandle	Interface handle that is enable to convert to IStBalanceRatioFilter interface handle.
		@~english	@param[in,out] pIStBalanceRatioFilterHandle	IStBalanceRatioFilter interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStBalanceRatioFilterハンドルを取得します。
		@~japanese	@details	IStBalanceRatioFilterハンドルを取得します。
		@~japanese	@param[in] pSourceHandle	IStBalanceRatioFilter インターフェースハンドルに変換可能なインターフェースハンドル
		@~japanese	@param[in,out] pIStBalanceRatioFilterHandle	IStBalanceRatioFilter インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStBalanceRatioFilter_GetIStBalanceRatioFilter_t)(const PStApiHandle_t pSourceHandle, PStApiHandle_t pIStBalanceRatioFilterHandle);

	/*!
		@~english	@brief	Get the value of white balance gain.
		@~english	@details	Get the value of white balance gain.
		@~english	@param[in] pIStBalanceRatioFilterHandle IStBalanceRatioFilter interface handle.
		@~english	@param[in] eBRS	The target of this function.
		@~english	@param[out] pdblValue	The value of white balance gain.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ホワイトバランスゲインの値を取得します。
		@~japanese	@details	ホワイトバランスゲインの値を取得します。
		@~japanese	@param[in] pIStBalanceRatioFilterHandle IStBalanceRatioFilter インターフェースハンドル
		@~japanese	@param[in] eBRS	対象を指定します。
		@~japanese	@param[out] pdblValue	ホワイトバランスゲインの値
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStBalanceRatioFilter_GetBalanceRatio_t)(const PStApiHandle_t pIStBalanceRatioFilterHandle, EStBalanceRatioSelector_t eBRS, double *pdblValue);

	/*!
		@~english	@brief	Set the value of white balance gain.
		@~english	@details	Set the value of white balance gain.
		@~english	@param[in] pIStBalanceRatioFilterHandle IStBalanceRatioFilter interface handle.
		@~english	@param[in] eBRS	The target of this function.
		@~english	@param[in] value Gain value of white balance(0 ~ 16.0).
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ホワイトバランスゲインの値を設定します。
		@~japanese	@details	ホワイトバランスゲインの値を設定します。
		@~japanese	@param[in] pIStBalanceRatioFilterHandle IStBalanceRatioFilter インターフェースハンドル
		@~japanese	@param[in] eBRS	対象を指定します。
		@~japanese	@param[in] value ホワイトバランスゲインの値(0～16.0)。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStBalanceRatioFilter_SetBalanceRatio_t)(const PStApiHandle_t pIStBalanceRatioFilterHandle, EStBalanceRatioSelector_t eBRS, double value);

	/*!
		@~english	@brief	Get the offset value before gain processing.
		@~english	@details	Get the offset value before gain processing.
		@~english	@param[in] pIStBalanceRatioFilterHandle IStBalanceRatioFilter interface handle.
		@~english	@param[in] eBRS	The target of this function.
		@~english	@param[out] pnValue	Offset value.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ホワイトバランスゲイン処理前のオフセット値を取得します。
		@~japanese	@details	ホワイトバランスゲイン処理前のオフセット値を取得します。
		@~japanese	@param[in] pIStBalanceRatioFilterHandle IStBalanceRatioFilter インターフェースハンドル
		@~japanese	@param[in] eBRS	対象を指定します。
		@~japanese	@param[out] pnValue	オフセット値
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStBalanceRatioFilter_GetOffsetLevelBeforeGain_t)(const PStApiHandle_t pIStBalanceRatioFilterHandle, EStBalanceRatioSelector_t eBRS, int32_t *pnValue);
		
	/*!
		@~english	@brief	Set the offset value before gain processing.
		@~english	@details	Set the offset value before gain processing.
		@~english	@param[in] pIStBalanceRatioFilterHandle IStBalanceRatioFilter interface handle.
		@~english	@param[in] eBRS	The target of this function.
		@~english	@param[in] value Offset value(-255 ~ 255).
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ホワイトバランスゲイン処理前のオフセット値を設定します。
		@~japanese	@details	ホワイトバランスゲイン処理前のオフセット値を設定します。
		@~japanese	@param[in] pIStBalanceRatioFilterHandle IStBalanceRatioFilter インターフェースハンドル
		@~japanese	@param[in] eBRS	対象を指定します。
		@~japanese	@param[in] value オフセット値(-255～255)。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStBalanceRatioFilter_SetOffsetLevelBeforeGain_t)(const PStApiHandle_t pIStBalanceRatioFilterHandle, EStBalanceRatioSelector_t eBRS, int32_t value);

	/*!
		@~english	@brief	Get the offset value after gain processing.
		@~english	@details	Get the offset value after gain processing.
		@~english	@param[in] pIStBalanceRatioFilterHandle IStBalanceRatioFilter interface handle.
		@~english	@param[in] eBRS	The target of this function.
		@~english	@param[out] pnValue	Offset value.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ホワイトバランスゲイン処理後のオフセット値を取得します。
		@~japanese	@details	ホワイトバランスゲイン処理後のオフセット値を取得します。
		@~japanese	@param[in] pIStBalanceRatioFilterHandle IStBalanceRatioFilter インターフェースハンドル
		@~japanese	@param[in] eBRS	対象を指定します。
		@~japanese	@param[out] pnValue	オフセット値
		@~japanese	@return	EStApiCError_t エラーコード
		@~japanese	@param[in] eBRS	対象を指定します。
	*/
	STAPI_PCALL(PStApiIP_IStBalanceRatioFilter_GetOffsetLevelAfterGain_t)(const PStApiHandle_t pIStBalanceRatioFilterHandle, EStBalanceRatioSelector_t eBRS, int32_t *pnValue);
		
	/*!
		@~english	@brief	Set the offset value after gain processing.
		@~english	@details	Set the offset value after gain processing.
		@~english	@param[in] pIStBalanceRatioFilterHandle IStBalanceRatioFilter interface handle.
		@~english	@param[in] eBRS	The target of this function.
		@~english	@param[in] value Offset value(-255 ~ 255).
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ホワイトバランスゲイン処理後のオフセット値を設定します。
		@~japanese	@details	ホワイトバランスゲイン処理後のオフセット値を設定します。
		@~japanese	@param[in] pIStBalanceRatioFilterHandle IStBalanceRatioFilter インターフェースハンドル
		@~japanese	@param[in] eBRS	対象を指定します。
		@~japanese	@param[in] value オフセット値(-255～255)。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStBalanceRatioFilter_SetOffsetLevelAfterGain_t)(const PStApiHandle_t pIStBalanceRatioFilterHandle, EStBalanceRatioSelector_t eBRS, int32_t value);

	/*!
		@~english	@brief	Get current setting of BalanceWhiteAuto.
		@~english	@details	Get current setting of BalanceWhiteAuto.
		@~english	@param[in] pIStBalanceRatioFilterHandle IStBalanceRatioFilter interface handle.
		@~english	@param[out] peValue	BalanceWhiteAuto setting.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	オートホワイトバランス設定を取得します。
		@~japanese	@details	オートホワイトバランス設定を取得します。
		@~japanese	@param[in] pIStBalanceRatioFilterHandle IStBalanceRatioFilter インターフェースハンドル
		@~japanese	@param[out] peValue	オートホワイトバランス設定値
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStBalanceRatioFilter_GetBalanceWhiteAuto_t)(const PStApiHandle_t pIStBalanceRatioFilterHandle, EStBalanceWhiteAuto_t *peValue);

	/*!
		@~english	@brief	Set BalanceWhiteAuto.
		@~english	@details	Set BalanceWhiteAuto.
		@~english	@param[in] pIStBalanceRatioFilterHandle IStBalanceRatioFilter interface handle.
		@~english	@param[in] eBWA	BalanceWhiteAuto setting.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	オートホワイトバランスを設定します。
		@~japanese	@details	オートホワイトバランスを設定します。
		@~japanese	@param[in] pIStBalanceRatioFilterHandle IStBalanceRatioFilter インターフェースハンドル
		@~japanese	@param[in] eBWA	オートホワイトバランス設定
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStBalanceRatioFilter_SetBalanceWhiteAuto_t)(const PStApiHandle_t pIStBalanceRatioFilterHandle, EStBalanceWhiteAuto_t eBWA);
	
	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStBalanceRatioFilter_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IStBalanceRatioFilter.
		@~english	@details	This structure holds the address of the C language wrapper function of IStBalanceRatioFilter.
		@~japanese	@brief	この構造体は IStBalanceRatioFilter のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IStBalanceRatioFilter のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_IStBalanceRatioFilter_Functions_t
	{

		/*!
			@copydoc PStApiIP_IStBalanceRatioFilter_GetIStBalanceRatioFilter_t()
		*/
		PStApiIP_IStBalanceRatioFilter_GetIStBalanceRatioFilter_t				GetIStBalanceRatioFilter;

		/*!
			@copydoc PStApiIP_IStBalanceRatioFilter_GetBalanceRatio_t()
		*/
		PStApiIP_IStBalanceRatioFilter_GetBalanceRatio_t				GetBalanceRatio;

		/*!
			@copydoc PStApiIP_IStBalanceRatioFilter_SetBalanceRatio_t()
		*/
		PStApiIP_IStBalanceRatioFilter_SetBalanceRatio_t				SetBalanceRatio;

		/*!
			@copydoc PStApiIP_IStBalanceRatioFilter_GetOffsetLevelBeforeGain_t()
		*/
		PStApiIP_IStBalanceRatioFilter_GetOffsetLevelBeforeGain_t				GetOffsetLevelBeforeGain;

		/*!
			@copydoc PStApiIP_IStBalanceRatioFilter_SetOffsetLevelBeforeGain_t()
		*/
		PStApiIP_IStBalanceRatioFilter_SetOffsetLevelBeforeGain_t				SetOffsetLevelBeforeGain;

		/*!
			@copydoc PStApiIP_IStBalanceRatioFilter_GetOffsetLevelAfterGain_t()
		*/
		PStApiIP_IStBalanceRatioFilter_GetOffsetLevelAfterGain_t				GetOffsetLevelAfterGain;

		/*!
			@copydoc PStApiIP_IStBalanceRatioFilter_SetOffsetLevelAfterGain_t()
		*/
		PStApiIP_IStBalanceRatioFilter_SetOffsetLevelAfterGain_t				SetOffsetLevelAfterGain;

		/*!
			@copydoc PStApiIP_IStBalanceRatioFilter_GetBalanceWhiteAuto_t()
		*/
		PStApiIP_IStBalanceRatioFilter_GetBalanceWhiteAuto_t					GetBalanceWhiteAuto;

		/*!
			@copydoc PStApiIP_IStBalanceRatioFilter_SetBalanceWhiteAuto_t()
		*/
		PStApiIP_IStBalanceRatioFilter_SetBalanceWhiteAuto_t				SetBalanceWhiteAuto;
	
	}StApi_IStBalanceRatioFilter_Functions_t, *PStApi_IStBalanceRatioFilter_Functions_t;

	/*************************************************************************/
	/* StApi::IStChromaSuppressionFilter */
	/*************************************************************************/
	/*!
		@~english	@brief	Get IStChromaSuppressionFilter handle.
		@~english	@details	Get IStChromaSuppressionFilter handle.
		@~english	@param[in] pSourceHandle	Interface handle that is enable to convert to IStChromaSuppressionFilter interface handle.
		@~english	@param[in,out] pIStChromaSuppressionFilterHandle	IStChromaSuppressionFilter interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStChromaSuppressionFilterハンドルを取得します。
		@~japanese	@details	IStChromaSuppressionFilterハンドルを取得します。
		@~japanese	@param[in] pSourceHandle	IStChromaSuppressionFilter インターフェースハンドルに変換可能なインターフェースハンドル
		@~japanese	@param[in,out] pIStChromaSuppressionFilterHandle	IStChromaSuppressionFilter インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStChromaSuppressionFilter_GetIStChromaSuppressionFilter_t)(const PStApiHandle_t pSourceHandle, PStApiHandle_t pIStChromaSuppressionFilterHandle);

	/*!
		@~english	@brief	Acquire the threshold value of chroma suppression activate.
		@~english	@details	Acquire the threshold value of chroma suppression activate.
		@~english	@param[in] pIStChromaSuppressionFilterHandle	IStChromaSuppressionFilter interface handle.
		@~english	@param[in] eCSPS	The target of eCSPS.
		@~english	@param[out] pnValue	Value of threshold.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	クロマサプレス処理を開始するスレッショルド値を取得します。
		@~japanese	@details	クロマサプレス処理を開始するスレッショルド値を取得します。
		@~japanese	@param[in]	pIStChromaSuppressionFilterHandle	IStChromaSuppressionFilter インターフェースハンドル
		@~japanese	@param[in] eCSPS	設定の対象部を指定します。
		@~japanese	@param[out] pnValue	スレッショルド値
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStChromaSuppressionFilter_GetThresholdValue_t)(const PStApiHandle_t pIStChromaSuppressionFilterHandle, EStChromaSuppressionPartSelector_t eCSPS, uint32_t *pnValue);
		
	/*!
		@~english	@brief	Set the threshold value of chroma suppression activate.
		@~english	@details	Set the threshold value of chroma suppression activate.
		@~english	@param[in] pIStChromaSuppressionFilterHandle	IStChromaSuppressionFilter interface handle.
		@~english	@param[in] eCSPS	The target of eCSPS.
		@~english	@param[in]	value	Threshold value(0 ~ 255).
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	クロマサプレス処理を開始するスレッショルド値を設定します。
		@~japanese	@details	クロマサプレス処理を開始するスレッショルド値を設定します。
		@~japanese	@param[in]	pIStChromaSuppressionFilterHandle	IStChromaSuppressionFilter インターフェースハンドル
		@~japanese	@param[in] eCSPS	設定の対象部を指定します。
		@~japanese	@param[in]	value	スレッショルド値(0～255)
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStChromaSuppressionFilter_SetThresholdValue_t)(const PStApiHandle_t pIStChromaSuppressionFilterHandle, EStChromaSuppressionPartSelector_t eCSPS, uint32_t value);

	/*!
		@~english	@brief	Acquire the supression value of chroma supression function.
		@~english	@details	Acquire the supression value of chroma supression function.
		@~english	@param[in] pIStChromaSuppressionFilterHandle	IStChromaSuppressionFilter interface handle.
		@~english	@param[in] eCSPS	The target of eCSPS.
		@~english	@param[out] pnValue	Supression value.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	クロマサプレス処理の抑圧値を取得します。
		@~japanese	@details	クロマサプレス処理の抑圧値を取得します。
		@~japanese	@param[in]	pIStChromaSuppressionFilterHandle	IStChromaSuppressionFilter インターフェースハンドル
		@~japanese	@param[in] eCSPS	設定の対象部を指定します。
		@~japanese	@param[out] pnValue	抑圧値
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStChromaSuppressionFilter_GetSuppressionValue_t)(const PStApiHandle_t pIStChromaSuppressionFilterHandle, EStChromaSuppressionPartSelector_t eCSPS, uint32_t *pnValue);
		
	/*!
		@~english	@brief	Set the supression value of chroma supression function.
		@~english	@details	Set the supression value of chroma supression function.
		@~english	@param[in] pIStChromaSuppressionFilterHandle	IStChromaSuppressionFilter interface handle.
		@~english	@param[in] eCSPS	The target of eCSPS.
		@~english	@param[in]	value	Supression value(0 ~ 255).
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	クロマサプレス処理を開始する抑圧値を設定します。
		@~japanese	@details	クロマサプレス処理を開始する抑圧値を設定します。
		@~japanese	@param[in]	pIStChromaSuppressionFilterHandle	IStChromaSuppressionFilter インターフェースハンドル
		@~japanese	@param[in] eCSPS	設定の対象部を指定します。
		@~japanese	@param[in]	value	抑圧値(0～255)
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStChromaSuppressionFilter_SetSuppressionValue_t)(const PStApiHandle_t pIStChromaSuppressionFilterHandle, EStChromaSuppressionPartSelector_t eCSPS, uint32_t value);

	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStChromaSuppressionFilter_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IStChromaSuppressionFilter.
		@~english	@details	This structure holds the address of the C language wrapper function of IStChromaSuppressionFilter.
		@~japanese	@brief	この構造体は IStChromaSuppressionFilter のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IStChromaSuppressionFilter のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_IStChromaSuppressionFilter_Functions_t
	{
		/*!
			@copydoc PStApiIP_IStChromaSuppressionFilter_GetIStChromaSuppressionFilter_t()
		*/
		PStApiIP_IStChromaSuppressionFilter_GetIStChromaSuppressionFilter_t				GetIStChromaSuppressionFilter;

		/*!
			@copydoc PStApiIP_IStChromaSuppressionFilter_GetThresholdValue_t()
		*/
		PStApiIP_IStChromaSuppressionFilter_GetThresholdValue_t				GetThresholdValue;

		/*!
			@copydoc PStApiIP_IStChromaSuppressionFilter_SetThresholdValue_t()
		*/
		PStApiIP_IStChromaSuppressionFilter_SetThresholdValue_t				SetThresholdValue;

		/*!
			@copydoc PStApiIP_IStChromaSuppressionFilter_GetSuppressionValue_t()
		*/
		PStApiIP_IStChromaSuppressionFilter_GetSuppressionValue_t			GetSuppressionValue;

		/*!
			@copydoc PStApiIP_IStChromaSuppressionFilter_SetSuppressionValue_t()
		*/
		PStApiIP_IStChromaSuppressionFilter_SetSuppressionValue_t			SetSuppressionValue;

	}StApi_IStChromaSuppressionFilter_Functions_t, *PStApi_IStChromaSuppressionFilter_Functions_t;

	/*************************************************************************/
	/* StApi::IStColorTransformationFilter */
	/*************************************************************************/
	/*!
		@~english	@brief	Get IStColorTransformationFilter handle.
		@~english	@details	Get IStColorTransformationFilter handle.
		@~english	@param[in] pSourceHandle	Interface handle that is enable to convert to IStColorTransformationFilter interface handle.
		@~english	@param[in,out] pIStColorTransformationFilterHandle	IStColorTransformationFilter interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStColorTransformationFilterハンドルを取得します。
		@~japanese	@details	IStColorTransformationFilterハンドルを取得します。
		@~japanese	@param[in] pSourceHandle	IStColorTransformationFilter インターフェースハンドルに変換可能なインターフェースハンドル
		@~japanese	@param[in,out] pIStColorTransformationFilterHandle	IStColorTransformationFilter インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStColorTransformationFilter_GetIStColorTransformationFilter_t)(const PStApiHandle_t pSourceHandle, PStApiHandle_t pIStColorTransformationFilterHandle);

	/*!
		@~english	@brief	Acquire current setting of color transformation.
		@~english	@details	Acquire current setting of color transformation.
		@~english	@param[in] pIStColorTransformationFilterHandle	IStColorTransformationFilter interface handle.
		@~english	@param[out] pbValue	True/false for current setting.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	色変換処理の有効/無効を取得します。
		@~japanese	@details	色変換処理の有効/無効を取得します。
		@~japanese	@param[in]	pIStColorTransformationFilterHandle	IStColorTransformationFilter インターフェースハンドル
		@~japanese	@param[out] pbValue	有効な時 true が返されます。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStColorTransformationFilter_GetColorTransformationEnable_t)(const PStApiHandle_t pIStColorTransformationFilterHandle, bool8_t *pbValue);
		
	/*!
		@~english	@brief	Enable/disable the color transformation function.
		@~english	@details	Enable/disable the color transformation function.
		@~english	@param[in] pIStColorTransformationFilterHandle	IStColorTransformationFilter interface handle.
		@~english	@param[in]	value	True/false for current setting.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	色変換処理の有効/無効を設定します。
		@~japanese	@details	色変換処理の有効/無効を設定します。
		@~japanese	@param[in]	pIStColorTransformationFilterHandle	IStColorTransformationFilter インターフェースハンドル
		@~japanese	@param[in]	value	有効にする場合、 true を指定します。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStColorTransformationFilter_SetColorTransformationEnable_t)(const PStApiHandle_t pIStColorTransformationFilterHandle, bool8_t value);

	/*!
		@~english	@brief	Acquire the parameter of color transformation of target.
		@~english	@details	Acquire the parameter of color transformation of target.
		@~english	@param[in] pIStColorTransformationFilterHandle	IStColorTransformationFilter interface handle.
		@~english	@param[in] eCTVS	Type of the setting.
		@~english	@param[out] pdblValue	Color conversion matrix value.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	色変換行列の値を取得します。
		@~japanese	@details	色変換行列の値を取得します。
		@~japanese	@param[in]	pIStColorTransformationFilterHandle	IStColorTransformationFilter インターフェースハンドル
		@~japanese	@param[in] eCTVS	対象とする行列の要素を指定します。
		@~japanese	@param[out] pdblValue	色変換行列値
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStColorTransformationFilter_GetColorTransformationValue_t)(const PStApiHandle_t pIStColorTransformationFilterHandle, EStColorTransformationValueSelector_t eCTVS, double *pdblValue);

	/*!
		@~english	@brief	Set the parameter of color transformation to target.
		@~english	@details	Set the parameter of color transformation to target.
		@~english	@param[in] pIStColorTransformationFilterHandle	IStColorTransformationFilter interface handle.
		@~english	@param[in] eCTVS	Parameter for setting.
		@~english	@param[in]	value	Color conversion matrix value.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	色変換行列の値を設定します。
		@~japanese	@details	色変換行列の値を設定します。
		@~japanese	@param[in]	pIStColorTransformationFilterHandle	IStColorTransformationFilter インターフェースハンドル
		@~japanese	@param[in] eCTVS	対象とする行列の要素を指定します。
		@~japanese	@param[in]	value	色変換行列値(ゲイン値:-16.0～16.0, オフセット値:-65535～65535)
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStColorTransformationFilter_SetColorTransformationValue_t)(const PStApiHandle_t pIStColorTransformationFilterHandle, EStColorTransformationValueSelector_t eCTVS, double value);

	/*!
		@~english	@brief	Acquire the correction value of hue.
		@~english	@details	Acquire the correction value of hue.
		@~english	@param[in] pIStColorTransformationFilterHandle	IStColorTransformationFilter interface handle.
		@~english	@param[out] pdblValue	Correction value (-180.0 ~ +180.0).
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	色相の補正値を取得します。
		@~japanese	@details	色相の補正値を取得します。
		@~japanese	@param[in]	pIStColorTransformationFilterHandle	IStColorTransformationFilter インターフェースハンドル
		@~japanese	@param[out] pdblValue	補正値
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStColorTransformationFilter_GetHueCorrection_t)(const PStApiHandle_t pIStColorTransformationFilterHandle, double *pdblValue);

	/*!
		@~english	@brief	Set the correction value to hue.
		@~english	@details	Set the correction value to hue.
		@~english	@param[in] pIStColorTransformationFilterHandle	IStColorTransformationFilter interface handle.
		@~english	@param[in] value	Current correction value (-180.0 ~ +180.0).
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	色相の補正値を設定します。
		@~japanese	@details	色相の補正値を設定します。
		@~japanese	@param[in]	pIStColorTransformationFilterHandle	IStColorTransformationFilter インターフェースハンドル
		@~japanese	@param[in]	value	補正値(-180.0～180.0)
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStColorTransformationFilter_SetHueCorrection_t)(const PStApiHandle_t pIStColorTransformationFilterHandle, double value);

	/*!
		@~english	@brief	Acquire the correction value of saturation.
		@~english	@details	Acquire the correction value of saturation.
		@~english	@param[in] pIStColorTransformationFilterHandle	IStColorTransformationFilter interface handle.
		@~english	@param[out] pdblValue	Current correction value.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	彩度の補正値を取得します。
		@~japanese	@details	彩度の補正値を取得します。
		@~japanese	@param[in]	pIStColorTransformationFilterHandle	IStColorTransformationFilter インターフェースハンドル
		@~japanese	@param[out] pdblValue	補正値
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStColorTransformationFilter_GetSaturationCorrection_t)(const PStApiHandle_t pIStColorTransformationFilterHandle, double *pdblValue);

	/*!
		@~english	@brief	Set the correction value to saturation.
		@~english	@details	Set the correction value to saturation.
		@~english	@param[in] pIStColorTransformationFilterHandle	IStColorTransformationFilter interface handle.
		@~english	@param[in]	value	Correction value (0.0 ~ 4.0).
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	彩度の補正値を設定します。
		@~japanese	@details	彩度の補正値を設定します。
		@~japanese	@param[in]	pIStColorTransformationFilterHandle	IStColorTransformationFilter インターフェースハンドル
		@~japanese	@param[in]	value	補正値(0.0～4.0)
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStColorTransformationFilter_SetSaturationCorrection_t)(const PStApiHandle_t pIStColorTransformationFilterHandle, double value);
	
	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStColorTransformationFilter_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IStColorTransformationFilter.
		@~english	@details	This structure holds the address of the C language wrapper function of IStColorTransformationFilter.
		@~japanese	@brief	この構造体は IStColorTransformationFilter のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IStColorTransformationFilter のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_IStColorTransformationFilter_Functions_t
	{
		/*!
			@copydoc PStApiIP_IStColorTransformationFilter_GetIStColorTransformationFilter_t()
		*/
		PStApiIP_IStColorTransformationFilter_GetIStColorTransformationFilter_t				GetIStColorTransformationFilter;

		/*!
			@copydoc PStApiIP_IStColorTransformationFilter_GetColorTransformationEnable_t()
		*/
		PStApiIP_IStColorTransformationFilter_GetColorTransformationEnable_t				GetColorTransformationEnable;

		/*!
			@copydoc PStApiIP_IStColorTransformationFilter_SetColorTransformationEnable_t()
		*/
		PStApiIP_IStColorTransformationFilter_SetColorTransformationEnable_t				SetColorTransformationEnable;

		/*!
			@copydoc PStApiIP_IStColorTransformationFilter_GetColorTransformationValue_t()
		*/
		PStApiIP_IStColorTransformationFilter_GetColorTransformationValue_t				GetColorTransformationValue;

		/*!
			@copydoc PStApiIP_IStColorTransformationFilter_SetColorTransformationValue_t()
		*/
		PStApiIP_IStColorTransformationFilter_SetColorTransformationValue_t				SetColorTransformationValue;

		/*!
			@copydoc PStApiIP_IStColorTransformationFilter_GetHueCorrection_t()
		*/
		PStApiIP_IStColorTransformationFilter_GetHueCorrection_t				GetHueCorrection;

		/*!
			@copydoc PStApiIP_IStColorTransformationFilter_SetHueCorrection_t()
		*/
		PStApiIP_IStColorTransformationFilter_SetHueCorrection_t				SetHueCorrection;

		/*!
			@copydoc PStApiIP_IStColorTransformationFilter_GetSaturationCorrection_t()
		*/
		PStApiIP_IStColorTransformationFilter_GetSaturationCorrection_t				GetSaturationCorrection;

		/*!
			@copydoc PStApiIP_IStColorTransformationFilter_SetSaturationCorrection_t()
		*/
		PStApiIP_IStColorTransformationFilter_SetSaturationCorrection_t				SetSaturationCorrection;
	}StApi_IStColorTransformationFilter_Functions_t, *PStApi_IStColorTransformationFilter_Functions_t;

	/*************************************************************************/
	/* StApi::IStEdgeEnhancementFilter */
	/*************************************************************************/
	/*!
		@~english	@brief	Get IStEdgeEnhancementFilter handle.
		@~english	@details	Get IStEdgeEnhancementFilter handle.
		@~english	@param[in] pSourceHandle	Interface handle that is enable to convert to IStEdgeEnhancementFilter interface handle.
		@~english	@param[in,out] pIStEdgeEnhancementFilterHandle	IStEdgeEnhancementFilter interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStEdgeEnhancementFilterハンドルを取得します。
		@~japanese	@details	IStEdgeEnhancementFilterハンドルを取得します。
		@~japanese	@param[in] pSourceHandle	IStEdgeEnhancementFilter インターフェースハンドルに変換可能なインターフェースハンドル
		@~japanese	@param[in,out] pIStEdgeEnhancementFilterHandle	IStEdgeEnhancementFilter インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStEdgeEnhancementFilter_GetIStEdgeEnhancementFilter_t)(const PStApiHandle_t pSourceHandle, PStApiHandle_t pIStEdgeEnhancementFilterHandle);

	/*!
		@~english	@brief	Get the edge enhancement value.
		@~english	@details	Get the edge enhancement value.
		@~english	@param[in] pIStEdgeEnhancementFilterHandle	IStEdgeEnhancementFilter interface handle.
		@~english	@param[out] pdblValue	Enhancement value.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	強調度を取得します。
		@~japanese	@details	強調度を取得します。
		@~japanese	@param[in]	pIStEdgeEnhancementFilterHandle	IStEdgeEnhancementFilter インターフェースハンドル
		@~japanese	@param[out] pdblValue	強調度
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStEdgeEnhancementFilter_GetStrength_t)(const PStApiHandle_t pIStEdgeEnhancementFilterHandle, double *pdblValue);
		
	/*!
		@~english	@brief	Set the edge enhancement value.
		@~english	@details	Set the edge enhancement value.
		@~english	@param[in] pIStEdgeEnhancementFilterHandle	IStEdgeEnhancementFilter interface handle.
		@~english	@param[in]	value	Enhancement value(0 ~ 32.0).
		@~english	@return	EStApiCError_t error code. 
		@~japanese	@brief	強調度を設定します。
		@~japanese	@details	強調度を設定します。
		@~japanese	@param[in]	pIStEdgeEnhancementFilterHandle	IStEdgeEnhancementFilter インターフェースハンドル
		@~japanese	@param[in]	value	強調度(0～32.0)
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStEdgeEnhancementFilter_SetStrength_t)(const PStApiHandle_t pIStEdgeEnhancementFilterHandle, double value);

	/*!
		@~english	@brief	Get threshold of the edge enhancement.
		@~english	@details	Get threshold of the edge enhancement.
		@~english	@param[in] pIStEdgeEnhancementFilterHandle	IStEdgeEnhancementFilter interface handle.
		@~english	@param[out] pnValue	Threshold.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	スレッショルド値を取得します。
		@~japanese	@details	スレッショルド値を取得します。
		@~japanese	@param[in]	pIStEdgeEnhancementFilterHandle	IStEdgeEnhancementFilter インターフェースハンドル
		@~japanese	@param[out] pnValue	スレッショルド値
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStEdgeEnhancementFilter_GetThresh_t)(const PStApiHandle_t pIStEdgeEnhancementFilterHandle, uint32_t *pnValue);

	/*!
		@~english	@brief	Set threshold of the edge enhancement.
		@~english	@details	Set threshold of the edge enhancement.
		@~english	@param[in] pIStEdgeEnhancementFilterHandle	IStEdgeEnhancementFilter interface handle.
		@~english	@param[in]	value	Threshold(0 ~ 255).
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	スレッショルド値を設定します。
		@~japanese	@details	スレッショルド値を設定します。
		@~japanese	@param[in]	pIStEdgeEnhancementFilterHandle	IStEdgeEnhancementFilter インターフェースハンドル
		@~japanese	@param[in]	value	スレッショルド値(0～255)
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStEdgeEnhancementFilter_SetThresh_t)(const PStApiHandle_t pIStEdgeEnhancementFilterHandle, uint32_t value);
		
	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStEdgeEnhancementFilter_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IStEdgeEnhancementFilter.
		@~english	@details	This structure holds the address of the C language wrapper function of IStEdgeEnhancementFilter.
		@~japanese	@brief	この構造体は IStEdgeEnhancementFilter のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IStEdgeEnhancementFilter のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_IStEdgeEnhancementFilter_Functions_t
	{
		/*!
			@copydoc PStApiIP_IStEdgeEnhancementFilter_GetIStEdgeEnhancementFilter_t()
		*/
		PStApiIP_IStEdgeEnhancementFilter_GetIStEdgeEnhancementFilter_t				GetIStEdgeEnhancementFilter;

		/*!
			@copydoc PStApiIP_IStEdgeEnhancementFilter_GetStrength_t()
		*/
		PStApiIP_IStEdgeEnhancementFilter_GetStrength_t				GetStrength;

		/*!
			@copydoc PStApiIP_IStEdgeEnhancementFilter_SetStrength_t()
		*/
		PStApiIP_IStEdgeEnhancementFilter_SetStrength_t				SetStrength;

		/*!
			@copydoc PStApiIP_IStEdgeEnhancementFilter_GetThresh_t()
		*/
		PStApiIP_IStEdgeEnhancementFilter_GetThresh_t				GetThresh;

		/*!
			@copydoc PStApiIP_IStEdgeEnhancementFilter_SetThresh_t()
		*/
		PStApiIP_IStEdgeEnhancementFilter_SetThresh_t				SetThresh;
	}StApi_IStEdgeEnhancementFilter_Functions_t, *PStApi_IStEdgeEnhancementFilter_Functions_t;

	/*************************************************************************/
	/* StApi::IStFlatFieldCorrectionFilter */
	/*************************************************************************/
	/*!
		@~english	@brief	Get IStFlatFieldCorrectionFilter handle.
		@~english	@details	Get IStFlatFieldCorrectionFilter handle.
		@~english	@param[in] pSourceHandle	Interface handle that is enable to convert to IStFlatFieldCorrectionFilter interface handle.
		@~english	@param[in,out] pIStFlatFieldCorrectionFilterHandle	IStFlatFieldCorrectionFilter interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStFlatFieldCorrectionFilterハンドルを取得します。
		@~japanese	@details	IStFlatFieldCorrectionFilterハンドルを取得します。
		@~japanese	@param[in] pSourceHandle	IStFlatFieldCorrectionFilter インターフェースハンドルに変換可能なインターフェースハンドル
		@~japanese	@param[in,out] pIStFlatFieldCorrectionFilterHandle	IStFlatFieldCorrectionFilter インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStFlatFieldCorrectionFilter_GetIStFlatFieldCorrectionFilter_t)(const PStApiHandle_t pSourceHandle, PStApiHandle_t pIStFlatFieldCorrectionFilterHandle);

	/*!
		@~english	@brief	Acquire FFC mode setting.
		@~english	@details	Acquire FFC mode setting.
		@~english	@param[in] pIStFlatFieldCorrectionFilterHandle	IStFlatFieldCorrectionFilter interface handle.
		@~english	@param[out] peValue	FFC mode.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	FFCモードを取得します。
		@~japanese	@details	FFCモードを取得します。
		@~japanese	@param[in]	pIStFlatFieldCorrectionFilterHandle	IStFlatFieldCorrectionFilter インターフェースハンドル
		@~japanese	@param[out] peValue	FFCモード
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStFlatFieldCorrectionFilter_GetFlatFieldCorrectionMode_t)(const PStApiHandle_t pIStFlatFieldCorrectionFilterHandle, EStFlatFieldCorrectionMode_t *peValue);
		
	/*!
		@~english	@brief	Set FFC mode.
		@~english	@details	Set FFC mode.
		@~english	@param[in] pIStFlatFieldCorrectionFilterHandle	IStFlatFieldCorrectionFilter interface handle.
		@~english	@param[in]	eFFCM FFC mode.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	FFCモードを設定します。
		@~japanese	@details	FFCモードを設定します。
		@~japanese	@param[in]	pIStFlatFieldCorrectionFilterHandle	IStFlatFieldCorrectionFilter インターフェースハンドル
		@~japanese	@param[in]	eFFCM FFCモード
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStFlatFieldCorrectionFilter_SetFlatFieldCorrectionMode_t)(const PStApiHandle_t pIStFlatFieldCorrectionFilterHandle, EStFlatFieldCorrectionMode_t eFFCM);

	/*!
		@~english	@brief	Acquire calibration function status.
		@~english	@details	Acquire calibration function status.
		@~english	@param[in] pIStFlatFieldCorrectionFilterHandle	IStFlatFieldCorrectionFilter interface handle.
		@~english	@param[out] pbValue	Return true if calibration is enabled.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	キャリブレーションの有効/無効を取得します。
		@~japanese	@details	キャリブレーションの有効/無効を取得します。
		@~japanese	@param[in]	pIStFlatFieldCorrectionFilterHandle	IStFlatFieldCorrectionFilter インターフェースハンドル
		@~japanese	@param[out] pbValue	キャリブレーションが有効な場合、 true を返します。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStFlatFieldCorrectionFilter_GetCalibrationEnable_t)(const PStApiHandle_t pIStFlatFieldCorrectionFilterHandle, bool8_t *pbValue);
		
	/*!
		@~english	@brief	Set calibration function enable/disable.
		@~english	@details	Set calibration function enable/disable.
		@~english	@param[in] pIStFlatFieldCorrectionFilterHandle	IStFlatFieldCorrectionFilter interface handle.
		@~english	@param[in]	value	Set true to enable calibration or set false to disable.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	キャリブレーションの有効/無効を設定します。
		@~japanese	@details	キャリブレーションの有効/無効を設定します。有効に設定している間に与えられた画像データをもとに補正値を算出します。無効に設定されると、補正値をもとに補正を行います。
		@~japanese	@param[in]	pIStFlatFieldCorrectionFilterHandle	IStFlatFieldCorrectionFilter インターフェースハンドル
		@~japanese	@param[in]	value	キャリブレーションを有効へ設定する場合は、 true を指定します。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStFlatFieldCorrectionFilter_SetCalibrationEnable_t)(const PStApiHandle_t pIStFlatFieldCorrectionFilterHandle, bool8_t value);

	/*!
		@~english	@brief	Get calibration target value.
		@~english	@details	Get calibration target value.
		@~english	@param[in] pIStFlatFieldCorrectionFilterHandle	IStFlatFieldCorrectionFilter interface handle.
		@~english	@param[out] pnValue	Calibration target value.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	キャリブレーション時の目標値を取得します。
		@~japanese	@details	キャリブレーション時の目標値を取得します。
		@~japanese	@param[in]	pIStFlatFieldCorrectionFilterHandle	IStFlatFieldCorrectionFilter インターフェースハンドル
		@~japanese	@param[out] pnValue	キャリブレーション時の目標値
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStFlatFieldCorrectionFilter_GetCalibrationTargetValue_t)(const PStApiHandle_t pIStFlatFieldCorrectionFilterHandle, uint32_t *pnValue);

	/*!
		@~english	@brief	Set calibration target value.
		@~english	@details	Set calibration target value.
		@~english	@param[in] pIStFlatFieldCorrectionFilterHandle	IStFlatFieldCorrectionFilter interface handle.
		@~english	@param[in]	value	Calibration target value(0 ~ 65535).
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	キャリブレーション時の目標値を設定します。
		@~japanese	@details	キャリブレーション時の目標値を設定します。
		@~japanese	@param[in]	pIStFlatFieldCorrectionFilterHandle	IStFlatFieldCorrectionFilter インターフェースハンドル
		@~japanese	@param[in]	value	キャリブレーション時の目標値(0～65535)
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStFlatFieldCorrectionFilter_SetCalibrationTargetValue_t)(const PStApiHandle_t pIStFlatFieldCorrectionFilterHandle, uint32_t value);
	
	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStFlatFieldCorrectionFilter_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IStFlatFieldCorrectionFilter.
		@~english	@details	This structure holds the address of the C language wrapper function of IStFlatFieldCorrectionFilter.
		@~japanese	@brief	この構造体は IStFlatFieldCorrectionFilter のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IStFlatFieldCorrectionFilter のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_IStFlatFieldCorrectionFilter_Functions_t
	{
		/*!
			@copydoc PStApiIP_IStFlatFieldCorrectionFilter_GetIStFlatFieldCorrectionFilter_t()
		*/
		PStApiIP_IStFlatFieldCorrectionFilter_GetIStFlatFieldCorrectionFilter_t				GetIStFlatFieldCorrectionFilter;
						
		/*!
			@copydoc PStApiIP_IStFlatFieldCorrectionFilter_GetFlatFieldCorrectionMode_t()
		*/
		PStApiIP_IStFlatFieldCorrectionFilter_GetFlatFieldCorrectionMode_t				GetFlatFieldCorrectionMode;
						
		/*!
			@copydoc PStApiIP_IStFlatFieldCorrectionFilter_SetFlatFieldCorrectionMode_t()
		*/
		PStApiIP_IStFlatFieldCorrectionFilter_SetFlatFieldCorrectionMode_t				SetFlatFieldCorrectionMode;
						
		/*!
			@copydoc PStApiIP_IStFlatFieldCorrectionFilter_GetCalibrationEnable_t()
		*/
		PStApiIP_IStFlatFieldCorrectionFilter_GetCalibrationEnable_t				GetCalibrationEnable;
						
		/*!
			@copydoc PStApiIP_IStFlatFieldCorrectionFilter_SetCalibrationEnable_t()
		*/
		PStApiIP_IStFlatFieldCorrectionFilter_SetCalibrationEnable_t				SetCalibrationEnable;
							
		/*!
			@copydoc PStApiIP_IStFlatFieldCorrectionFilter_GetCalibrationTargetValue_t()
		*/
		PStApiIP_IStFlatFieldCorrectionFilter_GetCalibrationTargetValue_t				GetCalibrationTargetValue;
						
		/*!
			@copydoc PStApiIP_IStFlatFieldCorrectionFilter_SetCalibrationTargetValue_t()
		*/
		PStApiIP_IStFlatFieldCorrectionFilter_SetCalibrationTargetValue_t				SetCalibrationTargetValue;
	}StApi_IStFlatFieldCorrectionFilter_Functions_t, *PStApi_IStFlatFieldCorrectionFilter_Functions_t;

	/*************************************************************************/
	/* StApi::IStGammaCorrectionFilter */
	/*************************************************************************/
	/*!
		@~english	@brief	Get IStGammaCorrectionFilter handle.
		@~english	@details	Get IStGammaCorrectionFilter handle.
		@~english	@param[in] pSourceHandle	Interface handle that is enable to convert to IStGammaCorrectionFilter interface handle.
		@~english	@param[in,out] pIStGammaCorrectionFilterHandle	IStGammaCorrectionFilter interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStGammaCorrectionFilterハンドルを取得します。
		@~japanese	@details	IStGammaCorrectionFilterハンドルを取得します。
		@~japanese	@param[in] pSourceHandle	IStGammaCorrectionFilter インターフェースハンドルに変換可能なインターフェースハンドル
		@~japanese	@param[in,out] pIStGammaCorrectionFilterHandle	IStGammaCorrectionFilter インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStGammaCorrectionFilter_GetIStGammaCorrectionFilter_t)(const PStApiHandle_t pSourceHandle, PStApiHandle_t pIStGammaCorrectionFilterHandle);

	/*!
		@~english	@brief	Acquire gamma correction value.
		@~english	@details	Acquire gamma correction value.
		@~english	@param[in] pIStGammaCorrectionFilterHandle	IStGammaCorrectionFilter interface handle.
		@~english	@param[out]	pdblValue Gamma correction value.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ガンマ補正値を取得します。
		@~japanese	@details	ガンマ補正値を取得します。
		@~japanese	@param[in]	pIStGammaCorrectionFilterHandle	IStGammaCorrectionFilter インターフェースハンドル
		@~japanese	@param[out]	pdblValue	ガンマ補正値
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStGammaCorrectionFilter_GetGammaValue_t)(const PStApiHandle_t pIStGammaCorrectionFilterHandle, double *pdblValue);
		
	/*!
		@~english	@brief	Set gamma correction value.
		@~english	@details	Set gamma correction value.
		@~english	@param[in] pIStGammaCorrectionFilterHandle	IStGammaCorrectionFilter interface handle.
		@~english	@param[in]	value	Gamma correction value(0 ~ 4.0).
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ガンマ補正値を設定します。
		@~japanese	@details	ガンマ補正値を設定します。
		@~japanese	@param[in]	pIStGammaCorrectionFilterHandle	IStGammaCorrectionFilter インターフェースハンドル
		@~japanese	@param[in]	value	ガンマ補正値(0.0～4.0) 
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStGammaCorrectionFilter_SetGammaValue_t)(const PStApiHandle_t pIStGammaCorrectionFilterHandle, double value);

	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStGammaCorrectionFilter_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IStGammaCorrectionFilter.
		@~english	@details	This structure holds the address of the C language wrapper function of IStGammaCorrectionFilter.
		@~japanese	@brief	この構造体は IStGammaCorrectionFilter のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IStGammaCorrectionFilter のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_IStGammaCorrectionFilter_Functions_t
	{
		/*!
			@copydoc PStApiIP_IStGammaCorrectionFilter_GetIStGammaCorrectionFilter_t()
		*/
		PStApiIP_IStGammaCorrectionFilter_GetIStGammaCorrectionFilter_t				GetIStGammaCorrectionFilter;

		/*!
			@copydoc PStApiIP_IStGammaCorrectionFilter_GetGammaValue_t()
		*/
		PStApiIP_IStGammaCorrectionFilter_GetGammaValue_t				GetGammaValue;

		/*!
			@copydoc PStApiIP_IStGammaCorrectionFilter_SetGammaValue_t()
		*/
		PStApiIP_IStGammaCorrectionFilter_SetGammaValue_t				SetGammaValue;
	}StApi_IStGammaCorrectionFilter_Functions_t, *PStApi_IStGammaCorrectionFilter_Functions_t;

	/*************************************************************************/
	/* StApi::IStNoiseReductionFilter */
	/*************************************************************************/
	/*!
		@~english	@brief	Get IStNoiseReductionFilter handle.
		@~english	@details	Get IStNoiseReductionFilter handle.
		@~english	@param[in] pSourceHandle	Interface handle that is enable to convert to IStNoiseReductionFilter interface handle.
		@~english	@param[in,out] pIStNoiseReductionFilterHandle	IStNoiseReductionFilter interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStNoiseReductionFilterハンドルを取得します。
		@~japanese	@details	IStNoiseReductionFilterハンドルを取得します。
		@~japanese	@param[in] pSourceHandle	IStNoiseReductionFilter インターフェースハンドルに変換可能なインターフェースハンドル
		@~japanese	@param[in,out] pIStNoiseReductionFilterHandle	IStNoiseReductionFilter インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStNoiseReductionFilter_GetIStNoiseReductionFilter_t)(const PStApiHandle_t pSourceHandle, PStApiHandle_t pIStNoiseReductionFilterHandle);

	/*!
		@~english	@brief	Acquire noise reduction mode.
		@~english	@details	Acquire noise reduction mode.
		@~english	@param[in] pIStNoiseReductionFilterHandle	IStNoiseReductionFilter interface handle.
		@~english	@param[out] peValue	Noise reduction mode.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	 ノイズ軽減モードを取得します。
		@~japanese	@details	ノイズ軽減モードを取得します。
		@~japanese	@param[in]	pIStNoiseReductionFilterHandle	IStNoiseReductionFilter インターフェースハンドル
		@~japanese	@param[out] peValue	ノイズ軽減モード
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStNoiseReductionFilter_GetNoiseReductionMode_t)(const PStApiHandle_t pIStNoiseReductionFilterHandle, EStNoiseReductionMode_t *peValue);
		
	/*!
		@~english	@brief	Set noise reduction mode.
		@~english	@details	Set noise reduction mode.
		@~english	@param[in] pIStNoiseReductionFilterHandle	IStNoiseReductionFilter interface handle.
		@~english	@param[in]	eNRM	Noise reduction mode.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	 ノイズ軽減モードを設定します。
		@~japanese	@details	ノイズ軽減モードを設定します。
		@~japanese	@param[in]	pIStNoiseReductionFilterHandle	IStNoiseReductionFilter インターフェースハンドル
		@~japanese	@param[in]	eNRM	ノイズ軽減モード
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStNoiseReductionFilter_SetNoiseReductionMode_t)(const PStApiHandle_t pIStNoiseReductionFilterHandle, EStNoiseReductionMode_t eNRM);

	/*!
		@~english	@brief	Check if calibration is enabled.
		@~english	@details	Check if calibration is enabled.
		@~english	@param[in] pIStNoiseReductionFilterHandle	IStNoiseReductionFilter interface handle.
		@~english	@param[out] pbValue	Return true if it is enabled.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	 キャリブレーションの有効/無効を取得します。
		@~japanese	@details	キャリブレーションの有効/無効を取得します。
		@~japanese	@param[in]	pIStNoiseReductionFilterHandle	IStNoiseReductionFilter インターフェースハンドル
		@~japanese	@param[out] pbValue	キャリブレーションが有効な場合、 true を返します。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStNoiseReductionFilter_GetCalibrationEnable_t)(const PStApiHandle_t pIStNoiseReductionFilterHandle, bool8_t *pbValue);

	/*!
		@~english	@brief	Enable/disable calibration.
		@~english	@details	Enable/disable calibration.
		@~english	@param[in] pIStNoiseReductionFilterHandle	IStNoiseReductionFilter interface handle.
		@~english	@param[in]	value	True to enable; false to disable.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	 キャリブレーションの有効/無効を設定します。
		@~japanese	@details	キャリブレーションの有効/無効を設定します。有効に設定している間に与えられた画像データをもとに補正値を算出します。無効に設定されると、補正値をもとに補正を行います。
		@~japanese	@param[in]	pIStNoiseReductionFilterHandle	IStNoiseReductionFilter インターフェースハンドル
		@~japanese	@param[in]	value	キャリブレーションを有効へ設定する場合は、 true を指定します。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStNoiseReductionFilter_SetCalibrationEnable_t)(const PStApiHandle_t pIStNoiseReductionFilterHandle, bool8_t value);
	
	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStNoiseReductionFilter_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IStNoiseReductionFilter.
		@~english	@details	This structure holds the address of the C language wrapper function of IStNoiseReductionFilter.
		@~japanese	@brief	この構造体は IStNoiseReductionFilter のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IStNoiseReductionFilter のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_IStNoiseReductionFilter_Functions_t
	{
		/*!
			@copydoc PStApiIP_IStNoiseReductionFilter_GetIStNoiseReductionFilter_t()
		*/
		PStApiIP_IStNoiseReductionFilter_GetIStNoiseReductionFilter_t				GetIStNoiseReductionFilter;

		/*!
			@copydoc PStApiIP_IStNoiseReductionFilter_GetNoiseReductionMode_t()
		*/
		PStApiIP_IStNoiseReductionFilter_GetNoiseReductionMode_t				GetNoiseReductionMode;

		/*!
			@copydoc PStApiIP_IStNoiseReductionFilter_SetNoiseReductionMode_t()
		*/
		PStApiIP_IStNoiseReductionFilter_SetNoiseReductionMode_t				SetNoiseReductionMode;

		/*!
			@copydoc PStApiIP_IStNoiseReductionFilter_GetCalibrationEnable_t()
		*/
		PStApiIP_IStNoiseReductionFilter_GetCalibrationEnable_t				GetCalibrationEnable;

		/*!
			@copydoc PStApiIP_IStNoiseReductionFilter_SetCalibrationEnable_t()
		*/
		PStApiIP_IStNoiseReductionFilter_SetCalibrationEnable_t				SetCalibrationEnable;
	}StApi_IStNoiseReductionFilter_Functions_t, *PStApi_IStNoiseReductionFilter_Functions_t;

	/*************************************************************************/
	/* StApi::IStSNMeasurementFilter */
	/*************************************************************************/
	/*!
		@~english	@brief	Get IStSNMeasurementFilter handle.
		@~english	@details	Get IStSNMeasurementFilter handle.
		@~english	@param[in] pSourceHandle	Interface handle that is enable to convert to IStSNMeasurementFilter interface handle.
		@~english	@param[in,out] pIStSNMeasurementFilterHandle	IStSNMeasurementFilter interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStSNMeasurementFilterハンドルを取得します。
		@~japanese	@details	IStSNMeasurementFilterハンドルを取得します。
		@~japanese	@param[in] pSourceHandle	IStSNMeasurementFilter インターフェースハンドルに変換可能なインターフェースハンドル
		@~japanese	@param[in,out] pIStSNMeasurementFilterHandle	IStSNMeasurementFilter インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStSNMeasurementFilter_GetIStSNMeasurementFilter_t)(const PStApiHandle_t pSourceHandle, PStApiHandle_t pIStSNMeasurementFilterHandle);

	/*!
		@~english	@brief	Discard the current acquired data.
		@~english	@details	Discard the current acquired data.
		@~english	@param[in] pIStSNMeasurementFilterHandle	IStSNMeasurementFilter interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	保持している画像データを破棄します。
		@~japanese	@details	保持している画像データを破棄します。
		@~japanese	@param[in]	pIStSNMeasurementFilterHandle	IStSNMeasurementFilter インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStSNMeasurementFilter_ClearGrabbedImage_t)(const PStApiHandle_t pIStSNMeasurementFilterHandle);

	/*!
		@~english	@brief	Acquire counts of frame for measurement.
		@~english	@details	Acquire counts of frame for measurement.
		@~english	@param[in] pIStSNMeasurementFilterHandle	IStSNMeasurementFilter interface handle.
		@~english	@param[out] pnValue	Counts of frame for measurement.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	統計値算出に使用するフレーム数を取得します。
		@~japanese	@details	統計値算出に使用するフレーム数を取得します。
		@~japanese	@param[in]	pIStSNMeasurementFilterHandle	IStSNMeasurementFilter インターフェースハンドル
		@~japanese	@param[out] pnValue	統計値算出に使用するフレーム数
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStSNMeasurementFilter_GetFrameCount_t)(const PStApiHandle_t pIStSNMeasurementFilterHandle, size_t *pnValue);

	/*!
		@~english	@brief	Set the number of frames that will be acquired for measurement.
		@~english	@details	Set the number of frames that will be acquired for measurement.
		@~english	@param[in] pIStSNMeasurementFilterHandle	IStSNMeasurementFilter interface handle.
		@~english	@param[in]	value	Number of frames. Can be set from 1 to 1024.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	統計値算出に使用するフレーム数を設定します。
		@~japanese	@details	統計値算出に使用するフレーム数を設定します。
		@~japanese	@param[in]	pIStSNMeasurementFilterHandle	IStSNMeasurementFilter インターフェースハンドル
		@~japanese	@param[in]	value	統計値算出に使用するフレーム数(1～1024)
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStSNMeasurementFilter_SetFrameCount_t)(const PStApiHandle_t pIStSNMeasurementFilterHandle, size_t value);

	/*!
		@~english	@brief	Acquire current ROI mode.
		@~english	@details	Acquire current ROI mode.
		@~english	@param[in] pIStSNMeasurementFilterHandle	IStSNMeasurementFilter interface handle.
		@~english	@param[out] peValue	ROI mode.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ROIモードを取得します。
		@~japanese	@details	ROIモードを取得します。
		@~japanese	@param[in]	pIStSNMeasurementFilterHandle	IStSNMeasurementFilter インターフェースハンドル
		@~japanese	@param[out] peValue		ROIモード
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStSNMeasurementFilter_GetROIMode_t)(const PStApiHandle_t pIStSNMeasurementFilterHandle, EStROIMode_t *peValue);

	/*!
		@~english	@brief	Set ROI mode.
		@~english	@details	Set ROI mode.
		@~english	@param[in] pIStSNMeasurementFilterHandle	IStSNMeasurementFilter interface handle.
		@~english	@param[in] eRM	ROI mode.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ROIモードを設定します。
		@~japanese	@details	ROIモードを設定します。
		@~japanese	@param[in]	pIStSNMeasurementFilterHandle	IStSNMeasurementFilter インターフェースハンドル
		@~japanese	@param[in] eRM	ROIモード
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStSNMeasurementFilter_SetROIMode_t)(const PStApiHandle_t pIStSNMeasurementFilterHandle, EStROIMode_t eRM);

	/*!
		@~english	@brief	Get X-axis offset value of ROI.
		@~english	@details	Get X-axis offset value of ROI.
		@~english	@param[in] pIStSNMeasurementFilterHandle	IStSNMeasurementFilter interface handle.
		@~english	@param[out] pnValue	X-axis offset value.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	横方向のオフセット値を取得します。
		@~japanese	@details	横方向のオフセット値を取得します。
		@~japanese	@param[in]	pIStSNMeasurementFilterHandle	IStSNMeasurementFilter インターフェースハンドル
		@~japanese	@param[out] pnValue	横方向のオフセット値
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStSNMeasurementFilter_GetOffsetX_t)(const PStApiHandle_t pIStSNMeasurementFilterHandle, size_t *pnValue);

	/*!
		@~english	@brief	Set X-axis offset value of ROI.
		@~english	@details	Set X-axis offset value of ROI.
		@~english	@param[in] pIStSNMeasurementFilterHandle	IStSNMeasurementFilter interface handle.
		@~english	@param[in]	value	X-axis offset value.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	横方向のオフセット値を設定します。
		@~japanese	@details	横方向のオフセット値を設定します。
		@~japanese	@param[in]	pIStSNMeasurementFilterHandle	IStSNMeasurementFilter インターフェースハンドル
		@~japanese	@param[in]	value	横方向のオフセット値
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStSNMeasurementFilter_SetOffsetX_t)(const PStApiHandle_t pIStSNMeasurementFilterHandle, size_t value);

	/*!
		@~english	@brief	Get Y-axis offset value of ROI.
		@~english	@details	Get Y-axis offset value of ROI.
		@~english	@param[in] pIStSNMeasurementFilterHandle	IStSNMeasurementFilter interface handle.
		@~english	@param[out] pnValue	Y-axis offset value.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	縦方向のオフセット値を取得します。
		@~japanese	@details	縦方向のオフセット値を取得します。
		@~japanese	@param[in]	pIStSNMeasurementFilterHandle	IStSNMeasurementFilter インターフェースハンドル
		@~japanese	@param[out] pnValue	縦方向のオフセット値
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStSNMeasurementFilter_GetOffsetY_t)(const PStApiHandle_t pIStSNMeasurementFilterHandle, size_t *pnValue);

	/*!
		@~english	@brief	Set Y-axis offset value of ROI.
		@~english	@details	Set Y-axis offset value of ROI.
		@~english	@param[in] pIStSNMeasurementFilterHandle	IStSNMeasurementFilter interface handle.
		@~english	@param[in]	value	Y-axis offset value.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	縦方向のオフセット値を設定します。
		@~japanese	@details	縦方向のオフセット値を設定します。
		@~japanese	@param[in]	pIStSNMeasurementFilterHandle	IStSNMeasurementFilter インターフェースハンドル
		@~japanese	@param[in]	value	縦方向のオフセット値
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStSNMeasurementFilter_SetOffsetY_t)(const PStApiHandle_t pIStSNMeasurementFilterHandle, size_t value);

	/*!
		@~english	@brief	Get width of ROI.
		@~english	@details	Get width of ROI.
		@~english	@param[in] pIStSNMeasurementFilterHandle	IStSNMeasurementFilter interface handle.
		@~english	@param[out] pnValue	Width of ROI.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	横方向のサイズを取得します。
		@~japanese	@details	横方向のサイズを取得します。
		@~japanese	@param[in]	pIStSNMeasurementFilterHandle	IStSNMeasurementFilter インターフェースハンドル
		@~japanese	@param[out] pnValue	横方向のサイズ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStSNMeasurementFilter_GetWidth_t)(const PStApiHandle_t pIStSNMeasurementFilterHandle, size_t *pnValue);

	/*!
		@~english	@brief	Set width of ROI.
		@~english	@details	Set width of ROI.
		@~english	@param[in] pIStSNMeasurementFilterHandle	IStSNMeasurementFilter interface handle.
		@~english	@param[in]	value	Width of ROI.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	横方向のサイズを設定します。
		@~japanese	@details	横方向のサイズを設定します。
		@~japanese	@param[in]	pIStSNMeasurementFilterHandle	IStSNMeasurementFilter インターフェースハンドル
		@~japanese	@param[in]	value	横方向のサイズ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStSNMeasurementFilter_SetWidth_t)(const PStApiHandle_t pIStSNMeasurementFilterHandle, size_t value);

	/*!
		@~english	@brief	Get height of ROI.
		@~english	@details	Get height of ROI.
		@~english	@param[in] pIStSNMeasurementFilterHandle	IStSNMeasurementFilter interface handle.
		@~english	@param[out] pnValue	Height of ROI.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	縦方向のサイズを取得します。
		@~japanese	@details	縦方向のサイズを取得します。
		@~japanese	@param[in]	pIStSNMeasurementFilterHandle	IStSNMeasurementFilter インターフェースハンドル
		@~japanese	@param[out] pnValue	縦方向のサイズ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStSNMeasurementFilter_GetHeight_t)(const PStApiHandle_t pIStSNMeasurementFilterHandle, size_t *pnValue);
		
	/*!
		@~english	@brief	Set height of ROI.
		@~english	@details	Set height of ROI.
		@~english	@param[in] pIStSNMeasurementFilterHandle	IStSNMeasurementFilter interface handle.
		@~english	@param[in]	value	Height of ROI.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	縦方向のサイズを設定します。
		@~japanese	@details	縦方向のサイズを設定します。
		@~japanese	@param[in]	pIStSNMeasurementFilterHandle	IStSNMeasurementFilter インターフェースハンドル
		@~japanese	@param[in]	value	縦方向のサイズ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStSNMeasurementFilter_SetHeight_t)(const PStApiHandle_t pIStSNMeasurementFilterHandle, size_t value);

	/*!
		@~english	@brief	Retrieve SN measurement result.
		@~english	@details	Retrieve SN measurement result.
		@~english	@param[in] pIStSNMeasurementFilterHandle	IStSNMeasurementFilter interface handle.
		@~english	@param[in]	dwTimeout	Timeout [ms].
		@~english	@param[out] pnValue	Return IStSNMeasurementResult interface pointer if success.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	計測結果を取得します。
		@~japanese	@details	計測結果を取得します。指定した時間内に計測が完了しない(指定したフレームを渡さなかった)場合、タイムアウトが発生します。
		@~japanese	@param[in]	pIStSNMeasurementFilterHandle	IStSNMeasurementFilter インターフェースハンドル
		@~japanese	@param[in]	dwTimeout	タイムアウト時間[ms]
		@~japanese	@param[out] pnValue	IStSNMeasurementResult インターフェースハンドルー
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStSNMeasurementFilter_RetrieveIStSNMeasurementResult_t)(const PStApiHandle_t pIStSNMeasurementFilterHandle, uint32_t dwTimeout, PStApiHandle_t pIStSNMeasurementResultHandle);

	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStSNMeasurementFilter_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IStSNMeasurementFilter.
		@~english	@details	This structure holds the address of the C language wrapper function of IStSNMeasurementFilter.
		@~japanese	@brief	この構造体は IStSNMeasurementFilter のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IStSNMeasurementFilter のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_IStSNMeasurementFilter_Functions_t
	{
		/*!
			@copydoc PStApiIP_IStSNMeasurementFilter_GetIStSNMeasurementFilter_t()
		*/
		PStApiIP_IStSNMeasurementFilter_GetIStSNMeasurementFilter_t				GetIStSNMeasurementFilter;

		/*!
			@copydoc PStApiIP_IStSNMeasurementFilter_ClearGrabbedImage_t()
		*/
		PStApiIP_IStSNMeasurementFilter_ClearGrabbedImage_t				ClearGrabbedImage;

		/*!
			@copydoc PStApiIP_IStSNMeasurementFilter_GetFrameCount_t()
		*/
		PStApiIP_IStSNMeasurementFilter_GetFrameCount_t				GetFrameCount;

		/*!
			@copydoc PStApiIP_IStSNMeasurementFilter_SetFrameCount_t()
		*/
		PStApiIP_IStSNMeasurementFilter_SetFrameCount_t				SetFrameCount;

		/*!
			@copydoc PStApiIP_IStSNMeasurementFilter_GetROIMode_t()
		*/
		PStApiIP_IStSNMeasurementFilter_GetROIMode_t				GetROIMode;

		/*!
			@copydoc PStApiIP_IStSNMeasurementFilter_SetROIMode_t()
		*/
		PStApiIP_IStSNMeasurementFilter_SetROIMode_t				SetROIMode;

		/*!
			@copydoc PStApiIP_IStSNMeasurementFilter_GetOffsetX_t()
		*/
		PStApiIP_IStSNMeasurementFilter_GetOffsetX_t				GetOffsetX;

		/*!
			@copydoc PStApiIP_IStSNMeasurementFilter_SetOffsetX_t()
		*/
		PStApiIP_IStSNMeasurementFilter_SetOffsetX_t				SetOffsetX;

		/*!
			@copydoc PStApiIP_IStSNMeasurementFilter_GetOffsetY_t()
		*/
		PStApiIP_IStSNMeasurementFilter_GetOffsetY_t				GetOffsetY;

		/*!
			@copydoc PStApiIP_IStSNMeasurementFilter_SetOffsetY_t()
		*/
		PStApiIP_IStSNMeasurementFilter_SetOffsetY_t				SetOffsetY;

		/*!
			@copydoc PStApiIP_IStSNMeasurementFilter_GetWidth_t()
		*/
		PStApiIP_IStSNMeasurementFilter_GetWidth_t				GetWidth;
	
		/*!
			@copydoc PStApiIP_IStSNMeasurementFilter_SetWidth_t()
		*/
		PStApiIP_IStSNMeasurementFilter_SetWidth_t				SetWidth;

		/*!
			@copydoc PStApiIP_IStSNMeasurementFilter_GetHeight_t()
		*/
		PStApiIP_IStSNMeasurementFilter_GetHeight_t				GetHeight;

		/*!
			@copydoc PStApiIP_IStSNMeasurementFilter_SetHeight_t()
		*/
		PStApiIP_IStSNMeasurementFilter_SetHeight_t				SetHeight;

		/*!
			@copydoc PStApiIP_IStSNMeasurementFilter_RetrieveIStSNMeasurementResult_t()
		*/
		PStApiIP_IStSNMeasurementFilter_RetrieveIStSNMeasurementResult_t				RetrieveIStSNMeasurementResult;
	}StApi_IStSNMeasurementFilter_Functions_t, *PStApi_IStSNMeasurementFilter_Functions_t;

	/*************************************************************************/
	/* StApi::IStSNMeasurementResult */
	/*************************************************************************/
	/*!
		@~english	@brief	Get the component counts of pixel.
		@~english	@details	Get the component counts of pixel.
		@~english	@param[in] pIStSNMeasurementResultHandle	IStSNMeasurementResult interface handle.
		@~english	@param[out] pnValue	Component counts.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	構成要素の数を取得します。
		@~japanese	@details	構成要素の数を取得します。
		@~japanese	@param[in]	pIStSNMeasurementResultHandle	IStSNMeasurementResult インターフェースハンドル
		@~japanese	@param[out] pnValue	構成要素の数
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStSNMeasurementResult_GetComponentCount_t)(const PStApiHandle_t pIStSNMeasurementResultHandle, size_t *pnValue);

	/*!
		@~english	@brief	Get the information of target component. 
		@~english	@details	Get the information of target component. 
		@~english	@param[in] pIStSNMeasurementResultHandle	IStSNMeasurementResult interface handle.
		@~english	@param[in]	nIndex		Index of the target component. Index can be assigned from 0 to GetComponentCount() - 1.
		@~english	@param[out]	pePC		The component type.
		@~english	@param[out]	pnPixelCount	The pixel counts.
		@~english	@param[out]	pdblAverage		The average value.
		@~english	@param[out]	pdblTemporalStandardDeviation	The average of standard deviation of all pixels.
		@~english	@param[out]	pdblFrameStandardDeviation	The average of standard deviation of every frame.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	指定した構成要素の情報を取得します。
		@~japanese	@details	指定した構成要素の情報を取得します。
		@~japanese	@param[in]	pIStSNMeasurementResultHandle	IStSNMeasurementResult インターフェースハンドル
		@~japanese	@param[in]	nIndex		構成要素を指定します。0から GetComponentCount() - 1 の値を指定します。
		@~japanese	@param[out]	pePC		ピクセル構成要素タイプ
		@~japanese	@param[out]	pnPixelCount		ピクセル数
		@~japanese	@param[out]	pdblAverage		平均値
		@~japanese	@param[out]	pdblTemporalStandardDeviation	同じ位置の画素の標準偏差を平均値。同じ位置の画素値が安定していると小さな値になります。
		@~japanese	@param[out]	pdblFrameStandardDeviation	1フレーム内の画素の標準偏差の平均値。均一な被写体を撮像した際に取得された画像が均一になっていると小さな値になります。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStSNMeasurementResult_GetSNMeasurementValue_t)(const PStApiHandle_t pIStSNMeasurementResultHandle, size_t nIndex, EStPixelComponent_t *pePC, size_t *pnPixelCount, double *pdblAverage, double *pdblTemporalStandardDeviation, double *pdblFrameStandardDeviation);

	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStSNMeasurementResult_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IStSNMeasurementResult.
		@~english	@details	This structure holds the address of the C language wrapper function of IStSNMeasurementResult.
		@~japanese	@brief	この構造体は IStSNMeasurementResult のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IStSNMeasurementResult のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_IStSNMeasurementResult_Functions_t
	{
		/*!
		@copydoc PStApiIP_IStSNMeasurementResult_GetComponentCount_t()
		*/
		PStApiIP_IStSNMeasurementResult_GetComponentCount_t				GetComponentCount;

		/*!
			@copydoc PStApiIP_IStSNMeasurementResult_GetSNMeasurementValue_t()
		*/
		PStApiIP_IStSNMeasurementResult_GetSNMeasurementValue_t				GetSNMeasurementValue;
	}StApi_IStSNMeasurementResult_Functions_t, *PStApi_IStSNMeasurementResult_Functions_t;

	/*************************************************************************/
	/* StApi::IStFiler */
	/*************************************************************************/
	/*!
		@~english	@brief	Acquire IStFiler interface handle.
		@~english	@details	Acquire IStFiler interface handle.
		@~english	@param[in] eFilerType	Type of filer.
		@~english	@param[in,out] pIStFilerHandle	IStFiler interface handle.
		@~english	@attention	If the acquired interface handle of IStFiler does not needed anymore, call IStFiler->Release(pIStFilerHandle) to release it. 
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	 IStFiler インターフェースハンドルを取得します。
		@~japanese	@details	IStFiler インターフェースハンドルを取得します。
		@~japanese	@param[in] eFilerype	使用するファイラーのタイプ
		@~japanese	@param[in,out] pIStFilerHandle	IStFiler インターフェースハンドル
		@~japanese	@attention	 IStFiler インターフェースハンドル が不要になったら、 IStFiler->Release(pIStFilerHandle) を呼び出して解放してください。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStFiler_CreateIStFiler_t)(EStFilerType_t eFilerType, PStApiHandle_t pIStFilerHandle);
	
	/*!
		@~english	@brief	Get IStFiler handle.
		@~english	@details	Get IStFiler handle.
		@~english	@param[in] pSourceHandle	Interface handle that is enable to convert to IStFiler interface handle.
		@~english	@param[in,out] pIStFilerHandle	IStFiler interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStFilerハンドルを取得します。
		@~japanese	@details	IStFilerハンドルを取得します。
		@~japanese	@param[in] pSourceHandle	IStFiler インターフェースハンドルに変換可能なインターフェースハンドル
		@~japanese	@param[in,out] pIStFilerHandle	IStFiler インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStFiler_GetIStFiler_t)(const PStApiHandle_t pSourceHandle, PStApiHandle_t pIStFilerHandle);

	/*!
		@~english	@brief	Release object.
		@~english	@details	Release object.
		@~english	@param[in] pIStFilerHandle	IStFiler interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	解放します。
		@~japanese	@details	解放します。
		@~japanese	@param[in] pIStFilerHandle	IStFiler インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStFiler_Release_t)(PStApiHandle_t pIStFilerHandle);

	/*!
		@~english	@brief	Register a callback function.
		@~english	@details	Register a callback function.
		@~english	@param[in] pIStFilerHandle	IStFiler interface handle.
		@~english	@param[in]	pFunc	Callback function pointer.
		@~english	@param[in]	pContext	Argument for the callback function.
		@~english	@param[in,out] pIStRegisteredCallbackHandle	IStRegisteredCallback Interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	コールバック関数を登録します。
		@~japanese	@details	コールバック関数を登録します。
		@~japanese	@param[in] pIStFilerHandle	IStFiler インターフェースハンドル
		@~japanese	@param[in]	pFunc	コールバック関数として使用する関数
		@~japanese	@param[in]	pContext	コールバック関数に渡されるユーザー用パラメータ
		@~japanese	@param[in,out] pIStRegisteredCallbackHandle	IStRegisteredCallback インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStFiler_RegisterCallback_t)(const PStApiHandle_t pIStFilerHandle, fStCallbackFunc_t *pFunc, void* pContext, PStApiHandle_t pIStRegisteredCallbackHandle);

	/*!
		@~english	@brief	Acquire the interface handle of IStFilerInfo.
		@~english	@details	Acquire the interface handle of IStFilerInfo.
		@~english	@param[in] pIStFilerHandle	IStFiler interface handle.
		@~english	@param[in,out]	pIStFilerInfoHandle	IStFilerInfo interface pointer.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStFilerInfo インターフェースハンドルを取得します。
		@~japanese	@details	IStFilerInfo インターフェースハンドルを取得します。
		@~japanese	@param[in] pIStFilerHandle	IStFiler インターフェースハンドル
		@~japanese	@param[in,out]	pIStFilerInfoHandle	IStFilerInfo インターフェースハンドル。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStFiler_GetIStFilerInfo_t)(const PStApiHandle_t pIStFilerHandle, PStApiHandle_t pIStFilerInfoHandle);

	/*!
		@~english	@brief	Acquire interface handle of INodeMap.
		@~english	@details	Acquire interface handle of INodeMap.
		@~english	@param[in] pIStFilerHandle	IStFiler interface handle.
		@~english	@param[in,out]	pINodeMapHandle	INodeMap interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	INodeMap インターフェースハンドルを取得します。
		@~japanese	@details	INodeMap インターフェースハンドルを取得します。
		@~japanese	@param[in] pIStFilerHandle	IStFiler インターフェースハンドル
		@~japanese	@param[in,out]	pINodeMapHandle		INodeMap インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStFiler_GetINodeMap_t)(const PStApiHandle_t pIStFilerHandle, PStApiHandle_t pINodeMapHandle);

	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStFiler_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IStFiler.
		@~english	@details	This structure holds the address of the C language wrapper function of IStFiler.
		@~japanese	@brief	この構造体は IStFiler のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IStFiler のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_IStFiler_Functions_t
	{
		/*!
			@copydoc PStApiIP_IStFiler_CreateIStFiler_t()
		*/
		PStApiIP_IStFiler_CreateIStFiler_t				CreateIStFiler;

		/*!
			@copydoc PStApiIP_IStFiler_GetIStFiler_t()
		*/
		PStApiIP_IStFiler_GetIStFiler_t						GetIStFiler;

		/*!
			@copydoc PStApiIP_IStFiler_Release_t()
		*/
		PStApiIP_IStFiler_Release_t						Release;

		/*!
		@copydoc PStApiIP_IStFiler_RegisterCallback_t()
		*/
		PStApiIP_IStFiler_RegisterCallback_t			RegisterCallback;

		/*!
			@copydoc PStApiIP_IStFiler_GetIStFilerInfo_t()
		*/
		PStApiIP_IStFiler_GetIStFilerInfo_t				GetIStFilerInfo;

		/*!
			@copydoc PStApiIP_IStFiler_GetINodeMap_t()
		*/
		PStApiIP_IStFiler_GetINodeMap_t					GetINodeMap;
	}StApi_IStFiler_Functions_t, *PStApi_IStFiler_Functions_t;

	/*************************************************************************/
	/* StApi::IStFilerInfo */
	/*************************************************************************/
	/*!
		@~english	@brief	Acquire filer type.
		@~english	@details	Acquire filer type.
		@~english	@param[in] pIStFilerInfoHandle	IStFilerInfo interface handle.
		@~english	@param[out]	peValue	Filer type.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ファイラータイプを取得します。
		@~japanese	@details	ファイラータイプを取得します。
		@~japanese	@param[in]	pIStFilerInfoHandle	IStFilerInfo インターフェースハンドル
		@~japanese	@param[out]	peValue	ファイラータイプ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStFilerInfo_GetFilerType_t)(const PStApiHandle_t pIStFilerInfoHandle, EStFilerType_t *peValue);

	/*!
		@~english	@brief	Acquire filer name.
		@~english	@details	Acquire filer name.
		@~english	@param[in] pIStFilerInfoHandle	IStFilerInfo interface handle.
		@~english	@param[in,out]	szText	Filer name.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ファイラー名を取得します。
		@~japanese	@details	ファイラー名を取得します。
		@~japanese	@param[in]	pIStFilerInfoHandle	IStFilerInfo インターフェースハンドル
		@~japanese	@param[in,out] szText	ファイラー名
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStFilerInfo_GetFilerNameW_t)(const PStApiHandle_t pIStFilerInfoHandle, wchar_t *szText, size_t *pnLen);
	

	/*!
		@~english	@brief	Acquire filer name.
		@~english	@details	Acquire filer name.
		@~english	@param[in] pIStFilerInfoHandle	IStFilerInfo interface handle.
		@~english	@param[in,out]	szText	Filer name.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ファイラー名を取得します。
		@~japanese	@details	ファイラー名を取得します。
		@~japanese	@param[in]	pIStFilerInfoHandle	IStFilerInfo インターフェースハンドル
		@~japanese	@param[in,out] szText	ファイラー名
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStFilerInfo_GetFilerNameA_t)(const PStApiHandle_t pIStFilerInfoHandle, char *szText, size_t *pnLen);

	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStFilerInfo_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IStFilerInfo.
		@~english	@details	This structure holds the address of the C language wrapper function of IStFilerInfo.
		@~japanese	@brief	この構造体は IStFilerInfo のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IStFilerInfo のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_IStFilerInfo_Functions_t
	{
		/*!
			@copydoc PStApiIP_IStFilerInfo_GetFilerType_t()
		*/
		PStApiIP_IStFilerInfo_GetFilerType_t				GetFilerType;

		/*!
			@copydoc PStApiIP_IStFilerInfo_GetFilerNameW_t()
		*/
		PStApiIP_IStFilerInfo_GetFilerNameW_t				GetFilerNameW;

		/*!
			@copydoc PStApiIP_IStFilerInfo_GetFilerNameA_t()
		*/
		PStApiIP_IStFilerInfo_GetFilerNameA_t				GetFilerNameA;
	}StApi_IStFilerInfo_Functions_t, *PStApi_IStFilerInfo_Functions_t;

	/*************************************************************************/
	/* StApi::IStStillImageFiler */
	/*************************************************************************/
	/*!
		@~english	@brief	Get IStStillImageFiler handle.
		@~english	@details	Get IStStillImageFiler handle.
		@~english	@param[in] pSourceHandle	Interface handle that is enable to convert to IStStillImageFiler interface handle.
		@~english	@param[in,out] pIStStillImageFilerHandle	IStStillImageFiler interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStStillImageFilerハンドルを取得します。
		@~japanese	@details	IStStillImageFilerハンドルを取得します。
		@~japanese	@param[in] pSourceHandle	IStStillImageFiler インターフェースハンドルに変換可能なインターフェースハンドル
		@~japanese	@param[in,out] pIStStillImageFilerHandle	IStStillImageFiler インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStStillImageFiler_GetIStStillImageFiler_t)(const PStApiHandle_t pSourceHandle, PStApiHandle_t pIStStillImageFilerHandle);

	/*!
		@~english	@brief	Check if the target pixel format can be saved as the still image file format.
		@~english	@details	Check if the target pixel format can be saved as the still image file format.
		@~english	@param[in] pIStStillImageFilerHandle	IStStillImageFiler interface handle.
		@~english	@param[in]	ePFNC	Target pixel format.
		@~english	@param[in]	eSIFF	Still image file format.
		@~english	@param[out] pbValue	True if save is supported.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	指定したピクセルフォーマットの保存に対応しているかを確認します。
		@~japanese	@details	指定したピクセルフォーマットの保存に対応しているかを確認します。
		@~japanese	@param[in]	pIStStillImageFilerHandle	IStStillImageFiler インターフェースハンドル
		@~japanese	@param[in]	ePFNC	ピクセルフォーマット
		@~japanese	@param[in]	eSIFF	静止画ファイルフォーマット
		@~japanese	@param[out] pbValue	対応している場合、 true が返されます。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStStillImageFiler_IsSaveSupported_t)(const PStApiHandle_t pIStStillImageFilerHandle, EStPixelFormatNamingConvention_t ePFNC, EStStillImageFileFormat_t eSIFF, bool8_t *pbValue);

	/*!
		@~english	@brief	Check if the still image file format can be loaded as the target pixel format.
		@~english	@details	Check if the still image file format can be loaded as the target pixel format.
		@~english	@attention	Currently this only supports StStillImageFileFormat_StApiRaw.
		@~english	@param[in] pIStStillImageFilerHandle	IStStillImageFiler interface handle.
		@~english	@param[in]	ePFNC	Target pixel format.
		@~english	@param[in]	eSIFF	Still image file format.
		@~japanese	@param[out] pbValue	pbValue	True if save is supported.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	指定したピクセルフォーマットの読み込みに対応しているかを確認します。
		@~japanese	@details	指定したピクセルフォーマットの読み込みに対応しているかを確認します。
		@~japanese	@attention	現在、読み込みに対応しているのは StStillImageFileFormat_StApiRaw フォーマットのみとなります。
		@~japanese	@param[in]	pIStStillImageFilerHandle	IStStillImageFiler インターフェースハンドル
		@~japanese	@param[in]	ePFNC	ピクセルフォーマット
		@~japanese	@param[in]	eSIFF	静止画ファイルフォーマット
		@~japanese	@param[out] pbValue	対応している場合、 true が返されます。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStStillImageFiler_IsLoadSupported_t)(const PStApiHandle_t pIStStillImageFilerHandle, EStPixelFormatNamingConvention_t ePFNC, EStStillImageFileFormat_t eSIFF, bool8_t *pbValue);

	/*!
		@~english	@brief	Save image data to file.
		@~english	@details	Save image data to file.
		@~english	@param[in] pIStStillImageFilerHandle	IStStillImageFiler interface handle.
		@~english	@param[in]	pImage	Image data.
		@~english	@param[in]	eSIFF	Still image file format.
		@~english	@param[in]	szFileName	File name.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	画像データを静止画ファイルへ保存します。
		@~japanese	@details	画像データを静止画ファイルへ保存します。
		@~japanese	@param[in]	pIStStillImageFilerHandle	IStStillImageFiler インターフェースハンドル
		@~japanese	@param[in]	pImage	保存する画像データ
		@~japanese	@param[in]	eSIFF	静止画ファイルフォーマット
		@~japanese	@param[in]	szFileName	ファイル名
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStStillImageFiler_SaveW_t)(const PStApiHandle_t pIStStillImageFilerHandle, const PStApiHandle_t pIStImageHandle, EStStillImageFileFormat_t eSIFF, const wchar_t *szFileName);
	
	/*!
		@~english	@brief	Save image data to file.
		@~english	@details	Save image data to file.
		@~english	@param[in] pIStStillImageFilerHandle	IStStillImageFiler interface handle.
		@~english	@param[in]	pImage	Image data.
		@~english	@param[in]	eSIFF	Still image file format.
		@~english	@param[in]	szFileName	File name.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	画像データを静止画ファイルへ保存します。
		@~japanese	@details	画像データを静止画ファイルへ保存します。
		@~japanese	@param[in]	pIStStillImageFilerHandle	IStStillImageFiler インターフェースハンドル
		@~japanese	@param[in]	pImage	保存する画像データ
		@~japanese	@param[in]	eSIFF	静止画ファイルフォーマット
		@~japanese	@param[in]	szFileName	ファイル名
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStStillImageFiler_SaveA_t)(const PStApiHandle_t pIStStillImageFilerHandle, const PStApiHandle_t pIStImageHandle, EStStillImageFileFormat_t eSIFF, const char *szFileName);

	/*!
		@~english	@brief	Read image data from file.
		@~english	@details	Read image data from file.
		@~english	@attention	Currently this only supports StStillImageFileFormat_StApiRaw.
		@~english	@param[in] pIStStillImageFilerHandle	IStStillImageFiler interface handle.
		@~english	@param[in]	pIStImageBuffer	Buffer to store image data from file.
		@~english	@param[in]	strFileName	File name.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	静止画ファイルを画像バッファへ読み込みます。
		@~japanese	@details	静止画ファイルを画像バッファへ読み込みます。
		@~japanese	@attention	現在、読み込みに対応しているのは StStillImageFileFormat_StApiRaw フォーマットのみとなります。
		@~japanese	@param[in]	pIStStillImageFilerHandle	IStStillImageFiler インターフェースハンドル
		@~japanese	@param[in]	pIStImageBuffer	画像バッファ
		@~japanese	@param[in]	strFileName	ファイル名
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStStillImageFiler_LoadW_t)(const PStApiHandle_t pIStStillImageFilerHandle, const PStApiHandle_t pIStImageBufferHandle, const wchar_t *szFileName);

	/*!
		@~english	@brief	Read image data from file.
		@~english	@details	Read image data from file.
		@~english	@attention	Currently this only supports StStillImageFileFormat_StApiRaw.
		@~english	@param[in] pIStStillImageFilerHandle	IStStillImageFiler interface handle.
		@~english	@param[in]	pIStImageBuffer	Buffer to store image data from file.
		@~english	@param[in]	strFileName	File name.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	静止画ファイルを画像バッファへ読み込みます。
		@~japanese	@details	静止画ファイルを画像バッファへ読み込みます。
		@~japanese	@attention	現在、読み込みに対応しているのは StStillImageFileFormat_StApiRaw フォーマットのみとなります。
		@~japanese	@param[in]	pIStStillImageFilerHandle	IStStillImageFiler インターフェースハンドル
		@~japanese	@param[in]	pIStImageBuffer	画像バッファ
		@~japanese	@param[in]	strFileName	ファイル名
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStStillImageFiler_LoadA_t)(const PStApiHandle_t pIStStillImageFilerHandle, const PStApiHandle_t pIStImageBufferHandle, const char *szFileName);

	/*!
		@~english	@brief	Acquire JPEG image quality setting.
		@~english	@details	Acquire JPEG image quality setting.
		@~english	@param[in] pIStStillImageFilerHandle	IStStillImageFiler interface handle.
		@~english	@param[out] pnValue		Quality value. 0(Low) ~ 100(High).
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	JPEGファイルの品質設定を取得します。
		@~japanese	@details	JPEGファイルの品質設定を取得します。
		@~japanese	@param[in]	pIStStillImageFilerHandle	IStStillImageFiler インターフェースハンドル
		@~japanese	@param[out] pnValue		品質 0:低品質～100:高品質
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStStillImageFiler_GetQuality_t)(const PStApiHandle_t pIStStillImageFilerHandle, uint32_t *pnValue);
		
	/*!
		@~english	@brief	Set JPEG image quality.
		@~english	@details	Set JPEG image quality.
		@~english	@param[in] pIStStillImageFilerHandle	IStStillImageFiler interface handle.
		@~english	@param[in]	value		Quality value. 0(Low) ~ 100(High).
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	JPEGファイルの品質を設定します。
		@~japanese	@details	JPEGファイルの品質を設定します。
		@~japanese	@param[in]	pIStStillImageFilerHandle	IStStillImageFiler インターフェースハンドル
		@~japanese	@param[in]	value		品質 0:低品質～100:高品質
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStStillImageFiler_SetQuality_t)(const PStApiHandle_t pIStStillImageFilerHandle, uint32_t value);
	
	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStStillImageFiler_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IStStillImageFiler.
		@~english	@details	This structure holds the address of the C language wrapper function of IStStillImageFiler.
		@~japanese	@brief	この構造体は IStStillImageFiler のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IStStillImageFiler のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_IStStillImageFiler_Functions_t
	{
		/*!
			@copydoc PStApiIP_IStStillImageFiler_GetIStStillImageFiler_t()
		*/
		PStApiIP_IStStillImageFiler_GetIStStillImageFiler_t		GetIStStillImageFiler;

		/*!
			@copydoc PStApiIP_IStStillImageFiler_IsSaveSupported_t()
		*/
		PStApiIP_IStStillImageFiler_IsSaveSupported_t		IsSaveSupported;

		/*!
			@copydoc PStApiIP_IStStillImageFiler_IsLoadSupported_t()
		*/
		PStApiIP_IStStillImageFiler_IsLoadSupported_t				IsLoadSupported;

		/*!
			@copydoc PStApiIP_IStStillImageFiler_SaveW_t()
		*/
		PStApiIP_IStStillImageFiler_SaveW_t				SaveW;

		/*!
			@copydoc PStApiIP_IStStillImageFiler_SaveA_t()
		*/
		PStApiIP_IStStillImageFiler_SaveA_t				SaveA;

		/*!
			@copydoc PStApiIP_IStStillImageFiler_LoadW_t()
		*/
		PStApiIP_IStStillImageFiler_LoadW_t				LoadW;

		/*!
			@copydoc PStApiIP_IStStillImageFiler_LoadA_t()
		*/
		PStApiIP_IStStillImageFiler_LoadA_t				LoadA;

		/*!
			@copydoc PStApiIP_IStStillImageFiler_GetQuality_t()
		*/
		PStApiIP_IStStillImageFiler_GetQuality_t				GetQuality;

		/*!
			@copydoc PStApiIP_IStStillImageFiler_SetQuality_t()
		*/
		PStApiIP_IStStillImageFiler_SetQuality_t				SetQuality;

	}StApi_IStStillImageFiler_Functions_t, *PStApi_IStStillImageFiler_Functions_t;

	/*************************************************************************/
	/* StApi::IStVideoFiler */
	/*************************************************************************/
	/*!
		@~english	@brief	Get IStVideoFiler handle.
		@~english	@details	Get IStVideoFiler handle.
		@~english	@param[in] pSourceHandle	Interface handle that is enable to convert to IStVideoFiler interface handle.
		@~english	@param[in,out] pIStVideoFilerHandle	IStVideoFiler interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStVideoFilerハンドルを取得します。
		@~japanese	@details	IStVideoFilerハンドルを取得します。
		@~japanese	@param[in] pSourceHandle	IStVideoFiler インターフェースハンドルに変換可能なインターフェースハンドル
		@~japanese	@param[in,out] pIStVideoFilerHandle	IStVideoFiler インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStVideoFiler_GetIStVideoFiler_t)(const PStApiHandle_t pSourceHandle, PStApiHandle_t pIStVideoFilerHandle);

	/*!
		@~english	@brief	Acquire current video file format setting.
		@~english	@details	Acquire current video file format setting.
		@~english	@param[in] pIStVideoFilerHandle	IStVideoFiler interface handle.
		@~english	@param[out] peValue	Video file format.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	動画ファイルフォーマット設定を取得します。
		@~japanese	@details	動画ファイルフォーマット設定を取得します。
		@~japanese	@param[in]	pIStVideoFilerHandle	IStVideoFiler インターフェースハンドル
		@~japanese	@param[out] peValue	動画ファイルフォーマット
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStVideoFiler_GetVideoFileFormat_t)(const PStApiHandle_t pIStVideoFilerHandle, EStVideoFileFormat_t *peValue);

	/*!
		@~english	@brief	Set video file format. The video file format must be set before adding any image frame.
		@~english	@details	Set video file format. The video file format must be set before adding any image frame.
		@~english	@param[in] pIStVideoFilerHandle	IStVideoFiler interface handle.
		@~english	@param[in]	eVFF	Video file format.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	動画ファイルフォーマットを設定します。
		@~japanese	@details	動画ファイルフォーマットを設定します。
		@~japanese	@param[in]	pIStVideoFilerHandle	IStVideoFiler インターフェースハンドル
		@~japanese	@param[in]	eVFF	動画ファイルフォーマット
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStVideoFiler_SetVideoFileFormat_t)(const PStApiHandle_t pIStVideoFilerHandle, EStVideoFileFormat_t eVFF);

	/*!
		@~english	@brief	Acquire current video file compression format.
		@~english	@details	Acquire current video file compression format.
		@~english	@param[in] pIStVideoFilerHandle	IStVideoFiler interface handle.
		@~english	@param[out] peValue	Video file compression format.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	動画ファイルの圧縮形式設定を取得します。
		@~japanese	@details	動画ファイルの圧縮形式設定を取得します。
		@~japanese	@param[in]	pIStVideoFilerHandle	IStVideoFiler インターフェースハンドル
		@~japanese	@param[out] peValue	動画ファイルの圧縮形式
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStVideoFiler_GetVideoFileCompression_t)(const PStApiHandle_t pIStVideoFilerHandle, EStVideoFileCompression_t *peValue);

	/*!
		@~english	@brief	Set video file compression format. The video file compression format must be set before adding any image frame.
		@~english	@details	Set video file compression format. The video file compression format must be set before adding any image frame.
		@~english	@param[in] pIStVideoFilerHandle	IStVideoFiler interface handle.
		@~english	@param[in]	eVFC	Video file compression format.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	動画ファイルの圧縮形式を設定します。
		@~japanese	@details	動画ファイルの圧縮形式を設定します。
		@~japanese	@param[in]	pIStVideoFilerHandle	IStVideoFiler インターフェースハンドル
		@~japanese	@param[in]	eVFC	動画ファイルの圧縮形式
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStVideoFiler_SetVideoFileCompression_t)(const PStApiHandle_t pIStVideoFilerHandle, EStVideoFileCompression_t eVFC);

	/*!
		@~english	@brief	Get the current video compression rate.
		@~english	@details	Get the current video compression rate.
		@~english	@param[in] pIStVideoFilerHandle	IStVideoFiler interface handle.
		@~english	@param[out] pnValue	Video compression rate (0: high compression rate ~ 100: low compression rate).
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	動画ファイルの品質設定を取得します。
		@~japanese	@details	動画ファイルの品質設定を取得します。
		@~japanese	@param[in]	pIStVideoFilerHandle	IStVideoFiler インターフェースハンドル
		@~japanese	@param[out] pnValue	品質(0:低品質～100:高品質)
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStVideoFiler_GetQuality_t)(const PStApiHandle_t pIStVideoFilerHandle, uint32_t *pnValue);

	/*!
		@~english	@brief	Set video compression rate.
		@~english	@details	Set video compression rate.
		@~english	@param[in] pIStVideoFilerHandle	IStVideoFiler interface handle.
		@~english	@param[in]	value	Video compression rate (0: high compression rate ~ 100: low compression rate).
		@~english	@return	EStApiCError_t error code.
		@~japanese	動画ファイルの品質を設定します。
		@~japanese	@details	動画ファイルの品質を設定します。
		@~japanese	@param[in]	pIStVideoFilerHandle	IStVideoFiler インターフェースハンドル
		@~japanese	@param[in]	value	品質(0:低品質～100:高品質)
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStVideoFiler_SetQuality_t)(const PStApiHandle_t pIStVideoFilerHandle, uint32_t value);

	/*!
		@~english	@brief	Get current Y-axis reversion setting.
		@~english	@details	Get current Y-axis reversion setting.
		@~english	@param[in] pIStVideoFilerHandle	IStVideoFiler interface handle.
		@~english	@param[out] pbValue	True if Y-axis reversion is enabled.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	上下反転設定を取得します。
		@~japanese	@details	上下反転設定を取得します。
		@~japanese	@param[in]	pIStVideoFilerHandle	IStVideoFiler インターフェースハンドル
		@~japanese	@param[out] pbValue	上下反転が有効な場合、 true が返されます。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStVideoFiler_GetReverseY_t)(const PStApiHandle_t pIStVideoFilerHandle, bool8_t *pbValue);

	/*!
		@~english	@brief	Enable or disable Y-axis reversion.
		@~english	@details	Enable or disable Y-axis reversion.
		@~english	@attention  Not all pixel format is supported for Y-axis reversion.
		@~english	@param[in] pIStVideoFilerHandle	IStVideoFiler interface handle.
		@~english	@param[in]	value	True to enable Y-axis reversion.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	上下反転を設定します。
		@~japanese	@details	上下反転を設定します。
		@~japanese	@attention	IStPixelFormatConverter が上下反転をサポートしているピクセルフォーマットに対してのみ有効になります。
		@~japanese	@param[in]	pIStVideoFilerHandle	IStVideoFiler インターフェースハンドル
		@~japanese	@param[in]	value	true を指定すると上下反転が有効になります。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStVideoFiler_SetReverseY_t)(const PStApiHandle_t pIStVideoFilerHandle, bool8_t value);

	/*!
		@~english	@brief	Get current FPS setting for the video file.
		@~english	@details	Get current FPS setting for the video file.
		@~english	@param[in] pIStVideoFilerHandle	IStVideoFiler interface handle.
		@~english	@param[out] pdblValue	FPS.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	動画ファイルのFPS設定を取得します。
		@~japanese	@details	動画ファイルのFPS設定を取得します。
		@~japanese	@param[in]	pIStVideoFilerHandle	IStVideoFiler インターフェースハンドル
		@~japanese	@param[out] pdblValue	FPS
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStVideoFiler_GetFPS_t)(const PStApiHandle_t pIStVideoFilerHandle, double *pdblValue);

	/*!
		@~english	@brief	Set FPS setting for the video file.
		@~english	@details	Set FPS setting for the video file.
		@~english	@attention  This FPS setting is the FPS for playback of the video file.
		@~english	@param[in] pIStVideoFilerHandle	IStVideoFiler interface handle.
		@~english	@param[in]	value	FPS (0.001 ~ 65535.0).
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	動画ファイルのFPSを設定します。
		@~japanese	@details	動画ファイルのFPSを設定します。
		@~japanese	@attention	設定したFPSが再生時の標準速度になります。保存時のFPS(カメラのFPS)よりも小さな値を設定するとスロー再生される動画ファイルが生成されます。
		@~japanese	@param[in]	pIStVideoFilerHandle	IStVideoFiler インターフェースハンドル
		@~japanese	@param[in]	value	FPS(0.001～65535.0)
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStVideoFiler_SetFPS_t)(const PStApiHandle_t pIStVideoFilerHandle, double value);

	/*!
		@~english	@brief	Register video file name. 
		@~english	@details	Register video file name. 
		@~english	@attention  If multiple video file names are registered, multiple video files will be created when the file size or frame numbers exceeds the maximum limit.
		@~english	@param[in] pIStVideoFilerHandle	IStVideoFiler interface handle.
		@~english	@param[in]	strFileName	Video file name.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	動画ファイル名を登録します。 
		@~japanese	@details	動画ファイル名を登録します。
		@~japanese	@attention	複数のファイルを予め登録しておくと、ファイルサイズやフレーム数が上限に達した際、保存中の動画ファイルがクローズされた後に、次の動画ファイルがオープンされるようになります。
		@~japanese	@param[in]	pIStVideoFilerHandle	IStVideoFiler インターフェースハンドル
		@~japanese	@param[in]	strFileName	動画ファイル名
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStVideoFiler_RegisterFileNameW_t)(const PStApiHandle_t pIStVideoFilerHandle, const wchar_t *szFileName);

	/*!
		@~english	@brief	Register video file name. 
		@~english	@details	Register video file name. 
		@~english	@attention  If multiple video file names are registered, multiple video files will be created when the file size or frame numbers exceeds the maximum limit.
		@~english	@param[in] pIStVideoFilerHandle	IStVideoFiler interface handle.
		@~english	@param[in]	strFileName	Video file name.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	動画ファイル名を登録します。 
		@~japanese	@details	動画ファイル名を登録します。
		@~japanese	@attention	複数のファイルを予め登録しておくと、ファイルサイズやフレーム数が上限に達した際、保存中の動画ファイルがクローズされた後に、次の動画ファイルがオープンされるようになります。
		@~japanese	@param[in]	pIStVideoFilerHandle	IStVideoFiler インターフェースハンドル
		@~japanese	@param[in]	strFileName	動画ファイル名
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStVideoFiler_RegisterFileNameA_t)(const PStApiHandle_t pIStVideoFilerHandle, const char *szFileName);

	/*!
		@~english	@brief	Add image data with a specified frame number into video file.
		@~english	@details	Add image data with a specified frame number into video file.
		@~english	@attention
		@~english	@param[in] pIStVideoFilerHandle	IStVideoFiler interface handle.
		@~english	@param[in]	pImage	Image data.
		@~english	@param[in]	iFrameNo	Frame number.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	動画ファイルへ保存する画像データを登録します。
		@~japanese	@details	動画ファイルへ保存する画像データを登録します。
		@~japanese	@attention	渡された画像データはピクセルフォーマットを変換( StPFNC_Mono8 または StPFNC_BGR8 )されて、SDK内部のバッファへ退避されます。SDK内部のバッファに空きがない場合、空きができるまで待機します。登録されたファイル名が空の場合は、画像データの退避は行わずに終了します。
		@~japanese	@param[in]	pIStVideoFilerHandle	IStVideoFiler インターフェースハンドル
		@~japanese	@param[in]	pImage	動画ファイルへ保存する画像データ
		@~japanese	@param[in]	iFrameNo	フレーム番号
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStVideoFiler_RegisterIStImage_t)(const PStApiHandle_t pIStVideoFilerHandle, const PStApiHandle_t pIStImageHandle, uint32_t iFrameNo);
		
	/*!
		@~english	@brief	Check if video recording is stopped.
		@~english	@details	Check if video recording is stopped.
		@~english	@param[in] pIStVideoFilerHandle	IStVideoFiler interface handle.
		@~english	@param[out] pdblValue	True if video recording is stopped or the video file name list is empty.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	動画ファイルの生成が停止しているかどうかを確認します。
		@~japanese	@details	動画ファイルの生成が停止しているかどうかを確認します。
		@~japanese	@param[in]	pIStVideoFilerHandle	IStVideoFiler インターフェースハンドル
		@~japanese	@param[out] pdblValue	動画ファイルの生成が停止(登録ファイルリストが空)の場合、 true が返されます。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStVideoFiler_IsStopped_t)(const PStApiHandle_t pIStVideoFilerHandle, bool8_t *pbValue);

	/*!
		@~english	@brief	Acquire maximum number of frames in one video file.
		@~english	@details	Acquire maximum number of frames in one video file.
		@~english	@param[in] pIStVideoFilerHandle	IStVideoFiler interface handle.
		@~english	@param[out] pnValue	Maximum number of frames in one video file.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	1つの動画ファイルに保存する最大フレーム数を取得します。
		@~japanese	@details	1つの動画ファイルに保存する最大フレーム数を取得します。
		@~japanese	@param[in]	pIStVideoFilerHandle	IStVideoFiler インターフェースハンドル
		@~japanese	@param[out] pnValue	1つの動画ファイルに保存する最大フレーム数
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStVideoFiler_GetMaximumFrameCountPerFile_t)(const PStApiHandle_t pIStVideoFilerHandle, size_t *pnValue);

	/*!
		@~english	@brief	Set maximum number of frames in one video file.
		@~english	@details	Set maximum number of frames in one video file.
		@~english	@attention	The file will be saved and closed when it reached either the maximum number of frames or the file size limit.
		@~english	@param[in] pIStVideoFilerHandle	IStVideoFiler interface handle.
		@~english	@param[in]	value	Maximum number of frames (1 ~ 100000). 
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	1つの動画ファイルに保存する最大フレーム数を設定します。
		@~japanese	@details	1つの動画ファイルに保存する最大フレーム数を設定します。
		@~japanese	@attention	指定したフレーム数に達しない場合も、ファイルサイズが上限に達した場合は、動画ファイルが閉じられます。
		@~japanese	@param[in]	pIStVideoFilerHandle	IStVideoFiler インターフェースハンドル
		@~japanese	@param[in]	value	1つの動画ファイルに保存する最大フレーム数(1～100000) 
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStVideoFiler_SetMaximumFrameCountPerFile_t)(const PStApiHandle_t pIStVideoFilerHandle, size_t value);

	/*!
		@~english	@brief	Close the file if it is opened and clear file name list and image data.
		@~english	@details	Close the file if it is opened and clear file name list and image data.
		@~english	@param[in] pIStVideoFilerHandle	IStVideoFiler interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	生成中の動画ファイルをクローズし、ファイルリストおよび保存待機中の画像データをクリアします。
		@~japanese	@details	生成中の動画ファイルをクローズし、ファイルリストおよび保存待機中の画像データをクリアします。
		@~japanese	@param[in]	pIStVideoFilerHandle	IStVideoFiler インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStVideoFiler_Reset_t)(const PStApiHandle_t pIStVideoFilerHandle);
	
	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStVideoFiler_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IStVideoFiler.
		@~english	@details	This structure holds the address of the C language wrapper function of IStVideoFiler.
		@~japanese	@brief	この構造体は IStVideoFiler のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IStVideoFiler のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_IStVideoFiler_Functions_t
	{
		/*!
			@copydoc PStApiIP_IStVideoFiler_GetIStVideoFiler_t()
		*/
		PStApiIP_IStVideoFiler_GetIStVideoFiler_t		GetIStVideoFiler;

		/*!
			@copydoc PStApiIP_IStVideoFiler_GetVideoFileFormat_t()
		*/
		PStApiIP_IStVideoFiler_GetVideoFileFormat_t		GetVideoFileFormat;

		/*!
			@copydoc PStApiIP_IStVideoFiler_SetVideoFileFormat_t()
		*/
		PStApiIP_IStVideoFiler_SetVideoFileFormat_t		SetVideoFileFormat;
					
		/*!
			@copydoc PStApiIP_IStVideoFiler_GetVideoFileCompression_t()
		*/
		PStApiIP_IStVideoFiler_GetVideoFileCompression_t		GetVideoFileCompression;
					
		/*!
			@copydoc PStApiIP_IStVideoFiler_SetVideoFileCompression_t()
		*/
		PStApiIP_IStVideoFiler_SetVideoFileCompression_t		SetVideoFileCompression;
					
		/*!
			@copydoc PStApiIP_IStVideoFiler_GetQuality_t()
		*/
		PStApiIP_IStVideoFiler_GetQuality_t		GetQuality;
						
		/*!
			@copydoc PStApiIP_IStVideoFiler_SetQuality_t()
		*/
		PStApiIP_IStVideoFiler_SetQuality_t		SetQuality;
					
		/*!
			@copydoc PStApiIP_IStVideoFiler_GetReverseY_t()
		*/
		PStApiIP_IStVideoFiler_GetReverseY_t		GetReverseY;
					
		/*!
			@copydoc PStApiIP_IStVideoFiler_SetReverseY_t()
		*/
		PStApiIP_IStVideoFiler_SetReverseY_t		SetReverseY;
					
		/*!
			@copydoc PStApiIP_IStVideoFiler_GetFPS_t()
		*/
		PStApiIP_IStVideoFiler_GetFPS_t		GetFPS;
					
		/*!
			@copydoc PStApiIP_IStVideoFiler_SetFPS_t()
		*/
		PStApiIP_IStVideoFiler_SetFPS_t		SetFPS;
					
		/*!
			@copydoc PStApiIP_IStVideoFiler_RegisterFileNameW_t()
		*/
		PStApiIP_IStVideoFiler_RegisterFileNameW_t		RegisterFileNameW;
					
		/*!
			@copydoc PStApiIP_IStVideoFiler_RegisterFileNameA_t()
		*/
		PStApiIP_IStVideoFiler_RegisterFileNameA_t		RegisterFileNameA;
					
		/*!
			@copydoc PStApiIP_IStVideoFiler_RegisterIStImage_t()
		*/
		PStApiIP_IStVideoFiler_RegisterIStImage_t		RegisterIStImage;
					
		/*!
			@copydoc PStApiIP_IStVideoFiler_IsStopped_t()
		*/
		PStApiIP_IStVideoFiler_IsStopped_t		IsStopped;
					
		/*!
			@copydoc PStApiIP_IStVideoFiler_GetMaximumFrameCountPerFile_t()
		*/
		PStApiIP_IStVideoFiler_GetMaximumFrameCountPerFile_t		GetMaximumFrameCountPerFile;
					
		/*!
			@copydoc PStApiIP_IStVideoFiler_SetMaximumFrameCountPerFile_t()
		*/
		PStApiIP_IStVideoFiler_SetMaximumFrameCountPerFile_t		SetMaximumFrameCountPerFile;
					
		/*!
			@copydoc PStApiIP_IStVideoFiler_Reset_t()
		*/
		PStApiIP_IStVideoFiler_Reset_t		Reset;
					
	}StApi_IStVideoFiler_Functions_t, *PStApi_IStVideoFiler_Functions_t;

	/*************************************************************************/
	/* StApi::IStCallbackParamStApiIPVideoFilerOpen */
	/*************************************************************************/
	/*!
		@~english	@brief	Acquire IStVideoFiler interface handle.
		@~english	@details	Acquire IStVideoFiler interface handle.
		@~english	@param[in] pIStCallbackParamBaseHandle	IStCallbackParamBase interface handle.
		@~english	@param[out] pIStVideoFilerHandle	IStVideoFiler interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStVideoFiler インターフェースハンドルを取得します。
		@~japanese	@details	IStVideoFiler インターフェースハンドルを取得します。
		@~japanese	@param[in]	pIStCallbackParamBaseHandle	IStCallbackParamBase インターフェースハンドル
		@~japanese	@param[out] pIStVideoFilerHandle	IStVideoFiler インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStCallbackParamStApiIPVideoFilerOpen_GetIStVideoFiler_t)(const PStApiHandle_t pIStCallbackParamBaseHandle, PStApiHandle_t pIStVideoFilerHandle);
		
	/*!
		@~english	@brief	Acquire opened file name.
		@~english	@details	Acquire opened file name.
		@~english	@param[in] pIStCallbackParamBaseHandle	IStCallbackParamBase interface handle.
		@~english	@param[in,out] szText	Opened file name.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	オープンされた動画ファイルのファイル名を取得します。
		@~japanese	@details	オープンされた動画ファイルのファイル名を取得します。
		@~japanese	@param[in]	pIStCallbackParamBaseHandle	IStCallbackParamBase インターフェースハンドル
		@~japanese	@param[in,out] szText	オープンされた動画ファイルのファイル名
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStCallbackParamStApiIPVideoFilerOpen_GetFileNameW_t)(const PStApiHandle_t pIStCallbackParamBaseHandle, wchar_t *szText, size_t *pnLen);
		
	/*!
		@~english	@brief	Acquire opened file name.
		@~english	@details	Acquire opened file name.
		@~english	@param[in] pIStCallbackParamBaseHandle	IStCallbackParamBase interface handle.
		@~english	@param[in,out] szText	Opened file name.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	オープンされた動画ファイルのファイル名を取得します。
		@~japanese	@details	オープンされた動画ファイルのファイル名を取得します。
		@~japanese	@param[in]	pIStCallbackParamBaseHandle	IStCallbackParamBase インターフェースハンドル
		@~japanese	@param[in,out] szText	オープンされた動画ファイルのファイル名
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStCallbackParamStApiIPVideoFilerOpen_GetFileNameA_t)(const PStApiHandle_t pIStCallbackParamBaseHandle, char *szText, size_t *pnLen);

	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStCallbackParamStApiIPVideoFilerOpen_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IStCallbackParamStApiIPVideoFilerOpen.
		@~english	@details	This structure holds the address of the C language wrapper function of IStCallbackParamStApiIPVideoFilerOpen.
		@~japanese	@brief	この構造体は IStCallbackParamStApiIPVideoFilerOpen のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IStCallbackParamStApiIPVideoFilerOpen のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_IStCallbackParamStApiIPVideoFilerOpen_Functions_t
	{
		/*!
			@copydoc PStApiIP_IStCallbackParamStApiIPVideoFilerOpen_GetIStVideoFiler_t()
		*/
		PStApiIP_IStCallbackParamStApiIPVideoFilerOpen_GetIStVideoFiler_t		GetIStVideoFiler;
		/*!
			@copydoc PStApiIP_IStCallbackParamStApiIPVideoFilerOpen_GetFileNameW_t()
		*/
		PStApiIP_IStCallbackParamStApiIPVideoFilerOpen_GetFileNameW_t		GetFileNameW;
		/*!
			@copydoc PStApiIP_IStCallbackParamStApiIPVideoFilerOpen_GetFileNameA_t()
		*/
		PStApiIP_IStCallbackParamStApiIPVideoFilerOpen_GetFileNameA_t		GetFileNameA;
	}StApi_IStCallbackParamStApiIPVideoFilerOpen_Functions_t, *PStApi_IStCallbackParamStApiIPVideoFilerOpen_Functions_t;

	/*************************************************************************/
	/* StApi::IStCallbackParamStApiIPVideoFilerClose */
	/*************************************************************************/
	/*!
		@~english	@brief	Acquire IStVideoFiler interface handle.
		@~english	@details	Acquire IStVideoFiler interface handle.
		@~english	@param[in] pIStCallbackParamBaseHandle	IStCallbackParamBase interface handle.
		@~english	@param[out] pIStVideoFilerHandle	IStVideoFiler interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStVideoFiler インターフェースハンドルを取得します。
		@~japanese	@details	IStVideoFiler インターフェースハンドルを取得します。
		@~japanese	@param[in]	pIStCallbackParamBaseHandle	IStCallbackParamBase インターフェースハンドル
		@~japanese	@param[out] pIStVideoFilerHandle	IStVideoFiler インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStCallbackParamStApiIPVideoFilerClose_GetIStVideoFiler_t)(const PStApiHandle_t pIStCallbackParamBaseHandle, PStApiHandle_t pIStVideoFilerHandle);
	
	/*!
		@~english	@brief	Acquire closed file name.
		@~english	@details	Acquire closed file name.
		@~english	@param[in] pIStCallbackParamBaseHandle	IStCallbackParamBase interface handle.
		@~english	@param[in,out] szText	Closed file name.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	閉じられた動画ファイルのファイル名を取得します。
		@~japanese	@details	閉じられた動画ファイルのファイル名を取得します。
		@~japanese	@param[in]	pIStCallbackParamBaseHandle	IStCallbackParamBase インターフェースハンドル
		@~japanese	@param[in,out] szText	閉じられた動画ファイルのファイル名
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStCallbackParamStApiIPVideoFilerClose_GetFileNameW_t)(const PStApiHandle_t pIStCallbackParamBaseHandle, wchar_t *szText, size_t *pnLen);
	
	/*!
		@~english	@brief	Acquire closed file name.
		@~english	@details	Acquire closed file name.
		@~english	@param[in] pIStCallbackParamBaseHandle	IStCallbackParamBase interface handle.
		@~english	@param[in,out] szText	Closed file name.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	閉じられた動画ファイルのファイル名を取得します。
		@~japanese	@details	閉じられた動画ファイルのファイル名を取得します。
		@~japanese	@param[in]	pIStCallbackParamBaseHandle	IStCallbackParamBase インターフェースハンドル
		@~japanese	@param[in,out] szText	閉じられた動画ファイルのファイル名
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStCallbackParamStApiIPVideoFilerClose_GetFileNameA_t)(const PStApiHandle_t pIStCallbackParamBaseHandle, char *szText, size_t *pnLen);
	
	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStCallbackParamStApiIPVideoFilerClose_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IStCallbackParamStApiIPVideoFilerClose.
		@~english	@details	This structure holds the address of the C language wrapper function of IStCallbackParamStApiIPVideoFilerClose.
		@~japanese	@brief	この構造体は IStCallbackParamStApiIPVideoFilerClose のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IStCallbackParamStApiIPVideoFilerClose のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_IStCallbackParamStApiIPVideoFilerClose_Functions_t
	{
		/*!
			@copydoc PStApiIP_IStCallbackParamStApiIPVideoFilerClose_GetIStVideoFiler_t()
		*/
		PStApiIP_IStCallbackParamStApiIPVideoFilerClose_GetIStVideoFiler_t		GetIStVideoFiler;
		/*!
			@copydoc PStApiIP_IStCallbackParamStApiIPVideoFilerClose_GetFileNameW_t()
		*/
		PStApiIP_IStCallbackParamStApiIPVideoFilerClose_GetFileNameW_t		GetFileNameW;
		/*!
			@copydoc PStApiIP_IStCallbackParamStApiIPVideoFilerClose_GetFileNameA_t()
		*/
		PStApiIP_IStCallbackParamStApiIPVideoFilerOpen_GetFileNameA_t		GetFileNameA;
	}StApi_IStCallbackParamStApiIPVideoFilerClose_Functions_t, *PStApi_IStCallbackParamStApiIPVideoFilerClose_Functions_t;
	
	/*************************************************************************/
	/* StApi::IStCallbackParamStApiIPVideoFilerError */
	/*************************************************************************/
	/*!
		@~english	@brief	Acquire IStVideoFiler interface handle.
		@~english	@details	Acquire IStVideoFiler interface handle.
		@~english	@param[in] pIStCallbackParamBaseHandle	IStCallbackParamBase interface handle.
		@~english	@param[out] pIStVideoFilerHandle	IStVideoFiler interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStVideoFiler インターフェースハンドルを取得します。
		@~japanese	@details	IStVideoFiler インターフェースハンドルを取得します。
		@~japanese	@param[in]	pIStCallbackParamBaseHandle	IStCallbackParamBase インターフェースハンドル
		@~japanese	@param[out] pIStVideoFilerHandle	IStVideoFiler インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStCallbackParamStApiIPVideoFilerError_GetIStVideoFiler_t)(const PStApiHandle_t pIStCallbackParamBaseHandle, PStApiHandle_t pIStVideoFilerHandle);
	
	/*!
		@~english	@brief	Acquire reference of GenericException.
		@~english	@details	Acquire reference of GenericException.
		@~english	@param[in] pIStCallbackParamBaseHandle	IStCallbackParamBase interface handle.
		@~english	@param[out] peValue	EStApiCError_t error code.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	発生したエラーの例外情報を取得します。
		@~japanese	@details	発生したエラーの例外情報を取得します。
		@~japanese	@param[in]	pIStCallbackParamBaseHandle	IStCallbackParamBase インターフェースハンドル
		@~japanese	@param[out] peValue	EStApiCError_t エラーコード
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStCallbackParamStApiIPVideoFilerError_GetException_t)(const PStApiHandle_t pIStCallbackParamBaseHandle, EStApiCError_t *peValue);
	
	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStCallbackParamStApiIPVideoFilerError_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IStCallbackParamStApiIPVideoFilerError.
		@~english	@details	This structure holds the address of the C language wrapper function of IStCallbackParamStApiIPVideoFilerError.
		@~japanese	@brief	この構造体は IStCallbackParamStApiIPVideoFilerError のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IStCallbackParamStApiIPVideoFilerError のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_IStCallbackParamStApiIPVideoFilerError_Functions_t
	{
		/*!
			@copydoc PStApiIP_IStCallbackParamStApiIPVideoFilerError_GetIStVideoFiler_t()
		*/
		PStApiIP_IStCallbackParamStApiIPVideoFilerError_GetIStVideoFiler_t		GetIStVideoFiler;
		/*!
			@copydoc PStApiIP_IStCallbackParamStApiIPVideoFilerError_GetException_t()
		*/
		PStApiIP_IStCallbackParamStApiIPVideoFilerError_GetException_t		GetException;

	}StApi_IStCallbackParamStApiIPVideoFilerError_Functions_t, *PStApi_IStCallbackParamStApiIPVideoFilerError_Functions_t;

	/*************************************************************************/
	/* StApi::IStWnd */
	/*************************************************************************/
	/*!
		@ingroup	StApiGUI_PublicImpl
		@~english	@brief	Acquire IStWnd handle.
		@~english	@details	Acquire IStWnd handle. This pointer can be used for either displaying image, nodemap, or device selection.
		@~english	@param[in] eWnd	Type of Window.
		@~english	@param[in,out] pIStWndHandle	IStWnd interface handle.
		@~english	@attention	If the acquired IStWnd handle is no longer needed, call IStWnd->Release(pIStWndHandle) to release it. 
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStWnd インターフェースハンドルを取得します。
		@~japanese	@details	IStWnd インターフェースハンドルを取得します。
		@~japanese	@param[in] eWnd	使用するウィンドウのタイプ
		@~japanese	@param[in,out] pIStWndHandle	IStWnd インターフェースハンドル
		@~japanese	@attention	取得された IStWnd インターフェースが不要になったら、 IStWnd->Release(pIStWndHandle) を呼び出して解放してください。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStWnd_CreateIStWnd_t)(EStWindowType_t eWnd, PStApiHandle_t pIStWndHandle);
	
	/*!
		@~english	@brief	Get IStWnd handle.
		@~english	@details	Get IStWnd handle.
		@~english	@param[in] pSourceHandle	Interface handle that is enable to convert to IStWnd interface handle.
		@~english	@param[in,out] pIStWndHandle	IStWnd interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStWnd ハンドルを取得します。
		@~japanese	@details	IStWnd ハンドルを取得します。
		@~japanese	@param[in] pSourceHandle	IStWnd インターフェースハンドルに変換可能なインターフェースハンドル
		@~japanese	@param[in,out] pIStWndHandle	IStWnd インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStWnd_GetIStWnd_t)(const PStApiHandle_t pSourceHandle, PStApiHandle_t pIStWndHandle);

	/*!
		@~english	@brief	Release object.
		@~english	@details	Release object.
		@~english	@param[in] pIStWndHandle	IStWnd interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	解放します。
		@~japanese	@details	解放します。
		@~japanese	@param[in] pIStWndHandle	IStWnd インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStWnd_Release_t)(PStApiHandle_t pIStWndHandle);

	/*!
		@~english	@brief	Register a callback function.
		@~english	@details	Register a callback function.
		@~english	@param[in] pIStWndHandle	IStWnd interface handle.
		@~english	@param[in]	pFunc	Callback function pointer.
		@~english	@param[in]	pContext	Argument for the callback function.
		@~english	@param[in,out] pIStRegisteredCallbackHandle	IStRegisteredCallback Interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	コールバック関数を登録します。
		@~japanese	@details	コールバック関数を登録します。
		@~japanese	@param[in] pIStWndHandle	IStWnd インターフェースハンドル
		@~japanese	@param[in]	pFunc	コールバック関数として使用する関数
		@~japanese	@param[in]	pContext	コールバック関数に渡されるユーザー用パラメータ
		@~japanese	@param[in,out] pIStRegisteredCallbackHandle	IStRegisteredCallback インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStWnd_RegisterCallback_t)(const PStApiHandle_t pIStWndHandle, fStCallbackFunc_t *pFunc, void* pContext, PStApiHandle_t pIStRegisteredCallbackHandle);

	/*!
		@~english	@brief	Get the IStWndInfo handle.
		@~english	@details	Get the IStWndInfo handle.
		@~english	@param[in] pIStWndHandle	IStWnd interface handle.
		@~english	@param[in,out] pIStWndInfoHandle	IStWndInfo handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStWndInfo インターフェースハンドルを取得します。
		@~japanese	@details	IStWndInfo インターフェースハンドルを取得します。
		@~japanese	@param[in,out] pIStWndHandle	IStWnd インターフェースハンドル
		@~japanese	@param[in] pIStWndHandle	IStWnd インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStWnd_GetIStWndInfo_t)(const PStApiHandle_t pIStWndHandle, PStApiHandle_t pIStWndInfoHandle);

	/*!
		@~english	@brief	Get the INodeMap handle.
		@~english	@details	Get the INodeMap handle.
		@~english	@param[in] pIStWndHandle	IStWnd interface handle.
		@~english	@return	INodeMap handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	INodeMap インターフェースハンドルを取得します。
		@~japanese	@details	INodeMap インターフェースハンドルを取得します。
		@~japanese	@param[in] pIStWndHandle	IStWnd インターフェースハンドル
		@~japanese	@return	INodeMap インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStWnd_GetINodeMap_t)(const PStApiHandle_t pIStWndHandle, PStApiHandle_t pINodeMapHandle);

	/*!
		@~english	@brief	Get the Window handle. 
		@~english	@details	Get the Window handle.
		@~english	@param[in] pIStWndHandle	IStWnd interface handle.
		@~english	@return	Window handle. 
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ウィンドウハンドルを取得します。
		@~japanese	@details	ウィンドウハンドルを取得します。
		@~japanese	@param[in] pIStWndHandle	IStWnd インターフェースハンドル
		@~japanese	@return	ウィンドウハンドル。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStWnd_GetWindowHandle_t)(const PStApiHandle_t pIStWndHandle, HWND *phWnd);

	/*!
		@~english	@brief	Get the title of the Window.
		@~english	@details	Get the title of the Window.
		@~english	@param[in] pIStWndHandle	IStWnd interface handle.
		@~english	@param[in,out] szText		Title of the Window.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ウィンドウタイトルを取得します。
		@~japanese	@details	ウィンドウタイトルを取得します。
		@~japanese	@param[in] pIStWndHandle	IStWnd インターフェースハンドル
		@~japanese	@param[in,out] szText	ウィンドウタイトル
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStWnd_GetTitleW_t)(const PStApiHandle_t pIStWndHandle, wchar_t *szText, size_t *pnLen);

	/*!
		@~english	@brief	Get the title of the Window.
		@~english	@details	Get the title of the Window.
		@~english	@param[in] pIStWndHandle	IStWnd interface handle.
		@~english	@param[in,out] szText		Title of the Window.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ウィンドウタイトルを取得します。
		@~japanese	@details	ウィンドウタイトルを取得します。
		@~japanese	@param[in] pIStWndHandle	IStWnd インターフェースハンドル
		@~japanese	@param[in,out] szText	ウィンドウタイトル
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStWnd_GetTitleA_t)(const PStApiHandle_t pIStWndHandle, char *szText, size_t *pnLen);

	/*!
		@~english	@brief	Set the title of the Window.
		@~english	@details	Set the title of the Window.
		@~english	@param[in] pIStWndHandle	IStWnd interface handle.
		@~english	@param[in]	strTitle	Title of the Window.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ウィンドウタイトルを設定します。
		@~japanese	@details	ウィンドウタイトルを設定します。
		@~japanese	@param[in] pIStWndHandle	IStWnd インターフェースハンドル
		@~japanese	@param[in]	strTitle	ウィンドウタイトル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStWnd_SetTitleW_t)(const PStApiHandle_t pIStWndHandle, const wchar_t *szText);

	/*!
		@~english	@brief	Set the title of the Window.
		@~english	@details	Set the title of the Window.
		@~english	@param[in] pIStWndHandle	IStWnd interface handle.
		@~english	@param[in]	strTitle	Title of the Window.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ウィンドウタイトルを設定します。
		@~japanese	@details	ウィンドウタイトルを設定します。
		@~japanese	@param[in] pIStWndHandle	IStWnd インターフェースハンドル
		@~japanese	@param[in]	strTitle	ウィンドウタイトル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStWnd_SetTitleA_t)(const PStApiHandle_t pIStWndHandle, const char *szText);

	/*!
		@~english	@brief	Get the position and size of the Window.
		@~english	@details	Get the position and size of the Window.
		@~english	@param[in] pIStWndHandle	IStWnd interface handle.
		@~english	@param[out]	pnX	Horizontal position.
		@~english	@param[out]	pnY	Vertical position.
		@~english	@param[out]	pnWidth	Horizontal size.
		@~english	@param[out]	pnHeight	Vertical size.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ウィンドウの位置とサイズを取得します。
		@~japanese	@details	ウィンドウの位置とサイズを取得します。
		@~japanese	@param[in] pIStWndHandle	IStWnd インターフェースハンドル
		@~japanese	@param[out]	pnX	ウィンドウの横方向の位置
		@~japanese	@param[out]	pnY	ウィンドウの縦方向の位置
		@~japanese	@param[out]	pnWidth	ウィンドウの横方向のサイズ
		@~japanese	@param[out]	pnHeight	ウィンドウの縦方向のサイズ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStWnd_GetPosition_t)(const PStApiHandle_t pIStWndHandle, int32_t *pnX, int32_t *pnY, int32_t *pnWidth, int32_t *pnHeight);

	/*!
		@~english	@brief	Set the position and size of the Window.
		@~english	@details	Set the position and size of the Window.
		@~english	@param[in] pIStWndHandle	IStWnd interface handle.
		@~english	@param[in]	nX	Horizontal position.
		@~english	@param[in]	nY	Vertical position.
		@~english	@param[in]	nWidth	Horizontal size.
		@~english	@param[in]	nHeight	Vertical size.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ウィンドウの位置とサイズを設定します。
		@~japanese	@details	ウィンドウの位置とサイズを設定します。
		@~japanese	@param[in] pIStWndHandle	IStWnd インターフェースハンドル
		@~japanese	@param[in]	nX	ウィンドウの横方向の位置
		@~japanese	@param[in]	nY	ウィンドウの縦方向の位置
		@~japanese	@param[in]	nWidth	ウィンドウの横方向のサイズ
		@~japanese	@param[in]	nHeight	ウィンドウの縦方向のサイズ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStWnd_SetPosition_t)(const PStApiHandle_t pIStWndHandle, int32_t nX, int32_t nY, int32_t nWidth, int32_t nHeight);

	/*!
		@~english	@brief	Check the visibility of the Window.
		@~english	@details	Check the visibility of the Window.
		@~english	@param[in] pIStWndHandle	IStWnd interface handle.
		@~english	@param[out] pbValue	 True if the Window is visible; false otherwise.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ウィンドウが表示されているか確認します。
		@~japanese	@details	ウィンドウが表示されているか確認します。
		@~japanese	@param[in] pIStWndHandle	IStWnd インターフェースハンドル
		@~japanese	@param[out] pbValue	 ウィンドウが表示されている場合、 true が返されます。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStWnd_IsVisible_t)(const PStApiHandle_t pIStWndHandle, bool8_t *pbValue);

	/*!
		@~english	@brief	Check the visibility of menu.
		@~english	@details	Check the visibility of menu.
		@~english	@param[in] pIStWndHandle	IStWnd interface handle.
		@~english	@param[out] pbValue	 True if the menu is visible; false otherwise.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ウィンドウメニューの表示/非表示設定を確認します。
		@~japanese	@details	ウィンドウメニューの表示/非表示設定を確認します。
		@~japanese	@param[in] pIStWndHandle	IStWnd インターフェースハンドル
		@~japanese	@param[out] pbValue	 ウィンドウメニューが表示されている場合、 true が返されます。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStWnd_GetVisibleMenu_t)(const PStApiHandle_t pIStWndHandle, bool8_t *pbValue);
		
	/*!
		@~english	@brief	Set the visibility of menu.
		@~english	@details	Set the visibility of menu.
		@~english	@param[in] pIStWndHandle	IStWnd interface handle.
		@~english	@param[in]	value	True to display menu; false to hide menu.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ウィンドウメニューの表示/非表示を設定します。
		@~japanese	@details	ウィンドウメニューの表示/非表示を設定します。
		@~japanese	@param[in] pIStWndHandle	IStWnd インターフェースハンドル
		@~japanese	@param[in]	value	ウィンドウメニューを表示する場合、 true を指定します。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStWnd_SetVisibleMenu_t)(const PStApiHandle_t pIStWndHandle, bool8_t value);

	/*!
		@~english	@brief	Check the visibility of status bar.
		@~english	@details	Check the visibility of status bar.
		@~english	@param[in] pIStWndHandle	IStWnd interface handle.
		@~english	@param[out] pbValue	True if status bar is visible; false otherwise.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ステータスバーの表示/非表示設定を確認します。
		@~japanese	@details	ステータスバーの表示/非表示設定を確認します。
		@~japanese	@param[in] pIStWndHandle	IStWnd インターフェースハンドル
		@~japanese	@param[out] pbValue	ステータスバーが表示されている場合、 true が返されます。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStWnd_GetVisibleStatusBar_t)(const PStApiHandle_t pIStWndHandle, bool8_t *pbValue);

	/*!
		@~english	@brief	Set the visibility of status bar.
		@~english	@details	Set the visibility of status bar.
		@~english	@param[in] pIStWndHandle	IStWnd interface handle.
		@~english	@param[in]	value	True to display status bar; false to hide status bar.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ステータスバーの表示/非表示を設定します。
		@~japanese	@details	ステータスバーの表示/非表示を設定します。
		@~japanese	@param[in] pIStWndHandle	IStWnd インターフェースハンドル
		@~japanese	@param[in]	value	ステータスバーを表示する場合、 true を指定します。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStWnd_SetVisibleStatusBar_t)(const PStApiHandle_t pIStWndHandle, bool8_t value);
		
	/*!
		@~english	@brief	Set the displayed text on status bar.
		@~english	@details	Set the displayed text on status bar.
		@~english	@param[in] pIStWndHandle	IStWnd interface handle.
		@~english	@param[in]	strText	The text to be displayed on the status bar.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ステータスバーに表示するユーザー文字列を設定します。
		@~japanese	@details	ステータスバーに表示するユーザー文字列を設定します。
		@~japanese	@param[in] pIStWndHandle	IStWnd インターフェースハンドル
		@~japanese	@param[in]	strText	ステータスバーに表示するユーザー文字列
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStWnd_SetUserStatusBarTextW_t)(const PStApiHandle_t pIStWndHandle, const wchar_t *szText);
		
	/*!
		@~english	@brief	Set the displayed text on status bar.
		@~english	@details	Set the displayed text on status bar.
		@~english	@param[in] pIStWndHandle	IStWnd interface handle.
		@~english	@param[in]	strText	The text to be displayed on the status bar.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ステータスバーに表示するユーザー文字列を設定します。
		@~japanese	@details	ステータスバーに表示するユーザー文字列を設定します。
		@~japanese	@param[in] pIStWndHandle	IStWnd インターフェースハンドル
		@~japanese	@param[in]	strText	ステータスバーに表示するユーザー文字列
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStWnd_SetUserStatusBarTextA_t)(const PStApiHandle_t pIStWndHandle, const char *szText);

	/*!
		@~english	@brief	Show the Window.
		@~english	@details	Show the Window.
		@~english	@param[in] pIStWndHandle	IStWnd interface handle.
		@~english	@param[in]	hParentWnd	Parent window handle.
		@~english	@param[in]	eWM	Window mode. In Mac/Linux (Qt-based), StWindowMode_ModalessOnNewThread is not supported (treated as StWindowMode_Modaless).
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ウィンドウを表示します。
		@~japanese	@details	ウィンドウを表示します。
		@~japanese	@param[in] pIStWndHandle	IStWnd インターフェースハンドル
		@~japanese	@param[in]	hParentWnd	親ウィンドウハンドル
		@~japanese	@param[in]	eWM	ウィンドウモード。Mac/Linux Qt上に、StWindowMode_ModalessOnNewThreadを対応していません。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStWnd_Show_t)(const PStApiHandle_t pIStWndHandle, HWND hParentWnd, EStWindowMode_t eWM);
	/*!
		@~english	@brief	Close the Window.
		@~english	@details	Close the Window.
		@~english	@param[in] pIStWndHandle	IStWnd interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ウィンドウを閉じます。
		@~japanese	@details	ウィンドウを閉じます。
		@~japanese	@param[in] pIStWndHandle	IStWnd インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStWnd_Close_t)(const PStApiHandle_t pIStWndHandle);

#ifndef _WIN32
	/*!
		@~english	@brief	Process GUI event for Qt (Only for Mac/Linux)
		@~english	@details	Process GUI event for Qt (Only for Mac/Linux)
        @~english	@param[in]	runExec True to execute Qt's QApplication::exec(); false to execute Qt's QApplication::instance()->processEvents()
        @~english	@param[in]	maxtime Applicable only if runExec is false. Max time for processEvents() in ms (set to zero to process all events without time limit). 
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	GUIイベントを処理するための関数 （Mac/Linuxのみ）。
		@~japanese	@details	GUIイベントを処理するための関数 （Mac/Linuxのみ）。
        @~japanese  @param[in]	runExec True場合はQtのQApplication::exec()を実行します。False場合はQtのQApplication::instance()->processEvents()を実行します。
        @~japanese  @param[in]	maxtime runExecがFalseのときに適用されます. processEvents()の最大の処理時間 [ms]。ゼロを設定する場合は処理時間制限が解放します。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStWnd_ProcessEventGUI_t)(bool8_t runExec, unsigned int maxtime);
#endif
		
	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStWnd_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IStWnd.
		@~english	@details	This structure holds the address of the C language wrapper function of IStWnd.
		@~japanese	@brief	この構造体は IStWnd のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IStWnd のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_IStWnd_Functions_t
	{
		/*!
			@copydoc PStApiGUI_IStWnd_CreateIStWnd_t()
		*/
		PStApiGUI_IStWnd_CreateIStWnd_t		CreateIStWnd;

		/*!
			@copydoc PStApiGUI_IStWnd_GetIStWnd_t()
		*/
		PStApiGUI_IStWnd_GetIStWnd_t		GetIStWnd;

		/*!
			@copydoc PStApiGUI_IStWnd_Release_t()
		*/
		PStApiGUI_IStWnd_Release_t		Release;

		/*!
			@copydoc PStApiGUI_IStWnd_RegisterCallback_t()
		*/
		PStApiGUI_IStWnd_RegisterCallback_t		RegisterCallback;

		/*!
			@copydoc PStApiGUI_IStWnd_GetIStWndInfo_t()
		*/
		PStApiGUI_IStWnd_GetIStWndInfo_t		GetIStWndInfo;

		/*!
			@copydoc PStApiGUI_IStWnd_GetINodeMap_t()
		*/
		PStApiGUI_IStWnd_GetINodeMap_t		GetINodeMap;

		/*!
			@copydoc PStApiGUI_IStWnd_GetWindowHandle_t()
		*/
		PStApiGUI_IStWnd_GetWindowHandle_t		GetWindowHandle;

		/*!
			@copydoc PStApiGUI_IStWnd_GetTitleW_t()
		*/
		PStApiGUI_IStWnd_GetTitleW_t		GetTitleW;
		/*!
			@copydoc PStApiGUI_IStWnd_GetTitleA_t()
		*/
		PStApiGUI_IStWnd_GetTitleA_t		GetTitleA;

		/*!
			@copydoc PStApiGUI_IStWnd_SetTitleW_t()
		*/
		PStApiGUI_IStWnd_SetTitleW_t		SetTitleW;

		/*!
			@copydoc PStApiGUI_IStWnd_SetTitleA_t()
		*/
		PStApiGUI_IStWnd_SetTitleA_t		SetTitleA;
		/*!
			@copydoc PStApiGUI_IStWnd_GetPosition_t()
		*/
		PStApiGUI_IStWnd_GetPosition_t		GetPosition;

		/*!
			@copydoc PStApiGUI_IStWnd_SetPosition_t()
		*/
		PStApiGUI_IStWnd_SetPosition_t		SetPosition;

		/*!
			@copydoc PStApiGUI_IStWnd_IsVisible_t()
		*/
		PStApiGUI_IStWnd_IsVisible_t		IsVisible;

		/*!
			@copydoc PStApiGUI_IStWnd_GetVisibleMenu_t()
		*/
		PStApiGUI_IStWnd_GetVisibleMenu_t		GetVisibleMenu;


		/*!
			@copydoc PStApiGUI_IStWnd_SetVisibleMenu_t()
		*/
		PStApiGUI_IStWnd_SetVisibleMenu_t		SetVisibleMenu;

		/*!
			@copydoc PStApiGUI_IStWnd_GetVisibleStatusBar_t()
		*/
		PStApiGUI_IStWnd_GetVisibleStatusBar_t		GetVisibleStatusBar;

		/*!
			@copydoc PStApiGUI_IStWnd_SetVisibleStatusBar_t()
		*/
		PStApiGUI_IStWnd_SetVisibleStatusBar_t		SetVisibleStatusBar;

		/*!
			@copydoc PStApiGUI_IStWnd_SetUserStatusBarTextW_t()
		*/
		PStApiGUI_IStWnd_SetUserStatusBarTextW_t		SetUserStatusBarTextW;

		/*!
			@copydoc PStApiGUI_IStWnd_SetUserStatusBarTextA_t()
		*/
		PStApiGUI_IStWnd_SetUserStatusBarTextA_t		SetUserStatusBarTextA;

		/*!
			@copydoc PStApiGUI_IStWnd_Show_t()
		*/
		PStApiGUI_IStWnd_Show_t		Show;

		/*!
			@copydoc PStApiGUI_IStWnd_Close_t()
		*/
		PStApiGUI_IStWnd_Close_t		Close;

#ifndef _WIN32
		/*!
			@copydoc PStApiGUI_IStWnd_ProcessEventGUI_t()
		*/
		PStApiGUI_IStWnd_ProcessEventGUI_t ProcessEventGUI;
#endif
	}StApi_IStWnd_Functions_t, *PStApi_IStWnd_Functions_t;

	/*************************************************************************/
	/* StApi::IStWndInfo */
	/*************************************************************************/
	/*!
		@~english	@brief	Get the Window type.
		@~english	@details	Get the Window type.
		@~english	@param[in] pIStWndInfoHandle	IStWndInfo interface handle.
		@~english	@param[out] peValue	Window type.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ウィンドウタイプを取得します。
		@~japanese	@details	ウィンドウタイプを取得します。
		@~japanese	@param[in] pIStWndInfoHandle	IStWndInfo インターフェースハンドル
		@~japanese	@param[out] peValue	ウィンドウタイプ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStWndInfo_GetWndType_t)(const PStApiHandle_t pIStWndInfoHandle, EStWindowType_t *peValue);

	/*!
		@~english	@brief	Get the Window name.
		@~english	@details	Get the Window name.
		@~english	@param[in] pIStWndInfoHandle	IStWndInfo interface handle.
		@~english	@param[in,out] szText	Window name.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ウィンドウ名を取得します。
		@~japanese	@details	ウィンドウ名を取得します。
		@~japanese	@param[in] pIStWndInfoHandle	IStWndInfo インターフェースハンドル
		@~japanese	@param[in,out] szText	ウィンドウ名
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStWndInfo_GetWndNameW_t)(const PStApiHandle_t pIStWndInfoHandle, wchar_t *szText, size_t *pnLen);

	/*!
		@~english	@brief	Get the Window name.
		@~english	@details	Get the Window name.
		@~english	@param[in] pIStWndInfoHandle	IStWndInfo interface handle.
		@~english	@param[in,out] szText	Window name.
		@~english	@param[in,out] pnLen	Buffer/String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ウィンドウ名を取得します。
		@~japanese	@details	ウィンドウ名を取得します。
		@~japanese	@param[in] pIStWndInfoHandle	IStWndInfo インターフェースハンドル
		@~japanese	@param[in,out] szText	ウィンドウ名
		@~japanese	@param[in,out] pnLen	バッファ/文字列長
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStWndInfo_GetWndNameA_t)(const PStApiHandle_t pIStWndInfoHandle, char *szText, size_t *pnLen);

	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStWndInfo_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IStWndInfo.
		@~english	@details	This structure holds the address of the C language wrapper function of IStWndInfo.
		@~japanese	@brief	この構造体は IStWndInfo のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IStWndInfo のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_IStWndInfo_Functions_t
	{
		/*!
			@copydoc PStApiGUI_IStWndInfo_GetWndType_t()
		*/
		PStApiGUI_IStWndInfo_GetWndType_t		GetWndType;

		/*!
			@copydoc PStApiGUI_IStWndInfo_GetWndNameW_t()
		*/
		PStApiGUI_IStWndInfo_GetWndNameW_t		GetWndNameW;

		/*!
			@copydoc PStApiGUI_IStWndInfo_GetWndNameA_t()
		*/
		PStApiGUI_IStWndInfo_GetWndNameA_t		GetWndNameA;

	}StApi_IStWndInfo_Functions_t, *PStApi_IStWndInfo_Functions_t;

	/*************************************************************************/
	/* StApi::IStDeviceSelectionWnd */
	/*************************************************************************/
	/*!
		@~english	@brief	Get IStDeviceSelectionWnd handle.
		@~english	@details	Get IStDeviceSelectionWnd handle.
		@~english	@param[in] pSourceHandle	Interface handle that is enable to convert to IStDeviceSelectionWnd interface handle.
		@~english	@param[in,out] pIStDeviceSelectionWndHandle	IStDeviceSelectionWnd interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStDeviceSelectionWnd ハンドルを取得します。
		@~japanese	@details	IStDeviceSelectionWnd ハンドルを取得します。
		@~japanese	@param[in] pSourceHandle	IStDeviceSelectionWnd インターフェースハンドルに変換可能なインターフェースハンドル
		@~japanese	@param[in,out] pIStDeviceSelectionWndHandle	IStDeviceSelectionWnd インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStDeviceSelectionWnd_GetIStDeviceSelectionWnd_t)(const PStApiHandle_t pSourceHandle, PStApiHandle_t pIStDeviceSelectionWndHandle);

	/*!
		@~english	@brief	Register IStSystem interface handle for device selection.
		@~english	@details	Register IStSystem interface handle for device selection.
		@~english	@param[in] pIStDeviceSelectionWndHandle	IStDeviceSelectionWnd interface handle.
		@~english	@param[in]	pIStSystemHandle	IStSystem handle for device selection.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	デバイス選択に使用する IStSystem インターフェースハンドルを登録します。
		@~japanese	@details	デバイス選択に使用する IStSystem インターフェースハンドルを登録します。
		@~japanese	@param[in] pIStDeviceSelectionWndHandle	IStDeviceSelectionWnd インターフェースハンドル
		@~japanese	@param[in]	pIStSystemHandle	デバイス選択に使用する IStSystem インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStDeviceSelectionWnd_RegisterTargetIStSystem_t)(const PStApiHandle_t pIStDeviceSelectionWndHandle, PStApiHandle_t pIStSystemHandle);

	/*!
		@~english	@brief	Register all IStSystem handles in the list for device selection.
		@~english	@details	Register all IStSystem handles in the list for device selection.
		@~english	@param[in] pIStDeviceSelectionWndHandle	IStDeviceSelectionWnd interface handle.
		@~english	@param[in]	pIStSystemHandleArray	A List of IStSystem interface handles for device selection.
		@~english	@param[in]	nCount	Count of IStSystem interface handles for device selection.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	デバイス選択に使用する IStSystem インターフェースハンドルを登録します。
		@~japanese	@details	デバイス選択に使用する IStSystem インターフェースハンドルを登録します。
		@~japanese	@param[in] pIStDeviceSelectionWndHandle	IStDeviceSelectionWnd インターフェースハンドル
		@~japanese	@param[in]	pIStSystemHandleArray	デバイス選択に使用する IStSystem インターフェースハンドルのリスト
		@~japanese	@param[in]	nCount	デバイス選択に使用する IStSystem インターフェースハンドルの数
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStDeviceSelectionWnd_RegisterTargetIStSystemList_t)(const PStApiHandle_t pIStDeviceSelectionWndHandle, PStApiHandle_t pIStSystemHandleArray, size_t nCount);

	/*!
		@~english	@brief	Acquire the selected IStInterface interface pointer and its related IStDeviceInfo interface pointer.
		@~english	@details	Acquire the selected IStInterface interface pointer and its related IStDeviceInfo interface pointer.
		@~english	@param[in] pIStDeviceSelectionWndHandle	IStDeviceSelectionWnd interface handle.
		@~english	@param[in]	pIStInterfaceHandle	Pointer to the acquired IStInterface interface handle.
		@~english	@param[in]	pIStDeviceInfoHandle	Pointer to the acquired IStDeviceInfo interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	選択されたデバイスの情報を取得します。
		@~japanese	@details	選択されたデバイスの情報を取得します。
		@~japanese	@param[in] pIStDeviceSelectionWndHandle	IStDeviceSelectionWnd インターフェースハンドル
		@~japanese	@param[in]	pIStInterfaceHandle	選択されたデバイスの IStInterface インターフェースハンドル
		@~japanese	@param[in]	pIStDeviceInfoHandle	選択されたデバイスの IStDeviceInfo インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStDeviceSelectionWnd_GetSelectedDeviceInfo_t)(const PStApiHandle_t pIStDeviceSelectionWndHandle, PStApiHandle_t pIStInterfaceHandle, PStApiHandle_t pIStDeviceInfoHandle);

	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStDeviceSelectionWnd_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IStDeviceSelectionWnd.
		@~english	@details	This structure holds the address of the C language wrapper function of IStDeviceSelectionWnd.
		@~japanese	@brief	この構造体は IStDeviceSelectionWnd のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IStDeviceSelectionWnd のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_IStDeviceSelectionWnd_Functions_t
	{
		/*!
			@copydoc PStApiGUI_IStDeviceSelectionWnd_GetIStDeviceSelectionWnd_t()
		*/
		PStApiGUI_IStDeviceSelectionWnd_GetIStDeviceSelectionWnd_t		GetIStDeviceSelectionWnd;

		/*!
			@copydoc PStApiGUI_IStDeviceSelectionWnd_RegisterTargetIStSystem_t()
		*/
		PStApiGUI_IStDeviceSelectionWnd_RegisterTargetIStSystem_t		RegisterTargetIStSystem;

		/*!
			@copydoc PStApiGUI_IStDeviceSelectionWnd_RegisterTargetIStSystemList_t()
		*/
		PStApiGUI_IStDeviceSelectionWnd_RegisterTargetIStSystemList_t		RegisterTargetIStSystemList;

		/*!
			@copydoc PStApiGUI_IStDeviceSelectionWnd_GetSelectedDeviceInfo_t()
		*/
		PStApiGUI_IStDeviceSelectionWnd_GetSelectedDeviceInfo_t		GetSelectedDeviceInfo;

	}StApi_IStDeviceSelectionWnd_Functions_t, *PStApi_IStDeviceSelectionWnd_Functions_t;

	/*************************************************************************/
	/* StApi::IStImageDisplayWnd */
	/*************************************************************************/
	/*!
		@~english	@brief	Get IStImageDisplayWnd handle.
		@~english	@details	Get IStImageDisplayWnd handle.
		@~english	@param[in] pSourceHandle	Interface handle that is enable to convert to IStImageDisplayWnd interface handle.
		@~english	@param[in,out] pIStImageDisplayWndHandle	IStImageDisplayWnd interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStImageDisplayWnd ハンドルを取得します。
		@~japanese	@details	IStImageDisplayWnd ハンドルを取得します。
		@~japanese	@param[in] pSourceHandle	IStImageDisplayWnd インターフェースハンドルに変換可能なインターフェースハンドル
		@~japanese	@param[in,out] pIStImageDisplayWndHandle	IStImageDisplayWnd インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStImageDisplayWnd_GetIStImageDisplayWnd_t)(const PStApiHandle_t pSourceHandle, PStApiHandle_t pIStImageDisplayWndHandle);

	/*!
		@~english	@brief	Register an image for preview.
		@~english	@details	Register an image for preview. The image data will be copied.
		@~english	@param[in] pIStImageDisplayWndHandle	IStImageDisplayWnd interface handle.
		@~english	@param[in]	pIStImageHandle	The image data for preview.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	表示する画像データを登録します。
		@~japanese	@details	表示する画像データを登録します。画像データはSDK内部のバッファへコピーされます。
		@~japanese	@param[in] pIStImageDisplayWndHandle	IStImageDisplayWnd インターフェースハンドル
		@~japanese	@param[in]	pIStImageHandle	表示する画像の IStImage インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStImageDisplayWnd_RegisterIStImage_t)(const PStApiHandle_t pIStImageDisplayWndHandle, PStApiHandle_t pIStImageHandle);

	/*!
		@~english	@brief	Check if any image for preview has been registered.
		@~english	@details	Check if any image for preview has been registered.
		@~english	@param[in] pIStImageDisplayWndHandle	IStImageDisplayWnd interface handle.
		@~english	@param[out] pbValue	Return true if an image has already registered; otherwise false.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	登録された画像があるかどうか確認します。
		@~japanese	@details	登録された画像があるかどうか確認します。
		@~japanese	@param[in] pIStImageDisplayWndHandle	IStImageDisplayWnd インターフェースハンドル
		@~japanese	@param[out] pbValue		登録された画像がある場合、 true が返されます。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStImageDisplayWnd_HasImage_t)(const PStApiHandle_t pIStImageDisplayWndHandle, bool8_t *pbValue);

	/*!
		@~english	@brief	Get registered image for preview.
		@~english	@details	Get registered image for preview.
		@~english	@param[in] pIStImageDisplayWndHandle	IStImageDisplayWnd interface handle.
		@~english	@param[out] pIStImageHandle		IStImage handle to the image.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	最後に登録された画像用の IStImage インターフェースハンドルを取得します。
		@~japanese	@details	最後に登録された画像用の IStImage インターフェースハンドルを取得します。
		@~japanese	@param[in] pIStImageDisplayWndHandle	IStImageDisplayWnd インターフェースハンドル
		@~japanese	@param[out] pIStImageHandle	IStImage インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStImageDisplayWnd_GetRegisteredIStImage_t)(const PStApiHandle_t pIStImageDisplayWndHandle, PStApiHandle_t pIStImageHandle);

	/*!
		@~english	@brief	Get a converted image for preview.
		@~english	@details	Get a converted image for preview. If conversion is not needed for preview, a registered image is returned.
		@~english	@param[in] pIStImageDisplayWndHandle	IStImageDisplayWnd interface handle.
		@~english	@param[out] pIStImageHandle	IStImage handle to the image.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	最後に登録された画像を表示用のピクセルフォーマットへ変換した画像の IStImage インターフェースハンドルを取得します。
		@~japanese	@details	最後に登録された画像を表示用のピクセルフォーマットへ変換した画像の IStImage インターフェースハンドルを取得します。変換が不要な画像が登録された場合は、登録された画像が返されます。
		@~japanese	@param[in] pIStImageDisplayWndHandle	IStImageDisplayWnd インターフェースハンドル
		@~japanese	@param[out] pIStImageHandle	IStImage インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStImageDisplayWnd_GetConvertedIStImage_t)(const PStApiHandle_t pIStImageDisplayWndHandle, PStApiHandle_t pIStImageHandle);
		
	/*!
		@~english	@brief	Convert screen coordinate to image coordinate.
		@~english	@details      Convert screen coordinate to image coordinate.
		@~english	@param[in] pIStImageDisplayWndHandle	IStImageDisplayWnd interface handle.
		@~english	@param[in,out]	pX	X coordinate.
		@~english	@param[in,out]	pY	Y coordinate.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	スクリーン上の座標を画像上の座標へ変換します。
		@~japanese	@details	スクリーン上の座標を画像上の座標へ変換します。
		@~japanese	@param[in] pIStImageDisplayWndHandle	IStImageDisplayWnd インターフェースハンドル
		@~japanese	@param[in,out]	pX	スクリーン上のX座標を入力すると、画像上のX座標が返されます。
		@~japanese	@param[in,out]	pY	スクリーン上のY座標を入力すると、画像上のY座標が返されます。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStImageDisplayWnd_ScreenToImage_t)(const PStApiHandle_t pIStImageDisplayWndHandle, int32_t *pX, int32_t *pY);

	/*!
		@~english	@brief	Get IStPixelFormatConverter pointer for converting a registered image to a preview image.
		@~english	@details	Get IStPixelFormatConverter pointer for converting a registered image to a preview image.
		@~english	@param[in] pIStImageDisplayWndHandle	IStImageDisplayWnd interface handle.
		@~english	@param[out] pIStPixelFormatConverterHandle	IStPixelFormatConverter handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	登録された画像の変換に使用される IStPixelFormatConverter インターフェースハンドルを取得します。
		@~japanese	@details	登録された画像の変換に使用される IStPixelFormatConverter インターフェースハンドルを取得します。
		@~japanese	@param[in] pIStImageDisplayWndHandle	IStImageDisplayWnd インターフェースハンドル
		@~japanese	@param[out] pIStPixelFormatConverterHandle	IStPixelFormatConverter インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStImageDisplayWnd_GetIStPixelFormatConverter_t)(const PStApiHandle_t pIStImageDisplayWndHandle, PStApiHandle_t pIStPixelFormatConverterHandle);

	/*!
		@~english	@brief	Get current mode of preview pixel format.
		@~english	@details	Get current mode of preview pixel format.
		@~english	@param[in] pIStImageDisplayWndHandle	IStImageDisplayWnd interface handle.
		@~english	@param[out] peValue	Preview pixel format mode.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	プレビューピクセルフォーマットモードを取得します。
		@~japanese	@details	プレビューピクセルフォーマットモードを取得します。
		@~japanese	@param[in] pIStImageDisplayWndHandle	IStImageDisplayWnd インターフェースハンドル
		@~japanese	@param[out] peValue	プレビューピクセルフォーマットモード
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStImageDisplayWnd_GetPreviewPixelFormatMode_t)(const PStApiHandle_t pIStImageDisplayWndHandle, EStPreviewPixelFormatMode_t *peValue);

	/*!
		@~english	@brief	Set preview pixel format mode.
		@~english	@details	Set preview pixel format mode.
		@~english	@param[in] pIStImageDisplayWndHandle	IStImageDisplayWnd interface handle.
		@~english	@param[in]	ePPFM	Preview pixel format mode.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	プレビューピクセルフォーマットモードを設定します。
		@~japanese	@details	プレビューピクセルフォーマットモードを設定します。
		@~japanese	@param[in] pIStImageDisplayWndHandle	IStImageDisplayWnd インターフェースハンドル
		@~japanese	@param[in]	ePPFM	プレビューピクセルフォーマットモード
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStImageDisplayWnd_SetPreviewPixelFormatMode_t)(const PStApiHandle_t pIStImageDisplayWndHandle, EStPreviewPixelFormatMode_t ePPFM);

	/*!
		@~english	@brief	Get maximum position of horizontal scroll bar.
		@~english	@details	Get maximum position of horizontal scroll bar.
		@~english	@param[in] pIStImageDisplayWndHandle	IStImageDisplayWnd interface handle.
		@~english	@param[out] pnValue	Horizontal scroll position value.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	水平スクロールバー位置の最大値を取得します。
		@~japanese	@details	水平スクロールバー位置の最大値を取得します。
		@~japanese	@param[in] pIStImageDisplayWndHandle	IStImageDisplayWnd インターフェースハンドル
		@~japanese	@param[out] pnValue	水平スクロールバー位置の最大値
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStImageDisplayWnd_GetScrollHMax_t)(const PStApiHandle_t pIStImageDisplayWndHandle, int32_t *pnValue);

	/*!
		@~english	@brief	Get current position of horizontal scroll bar.
		@~english	@details	Get current position of horizontal scroll bar.
		@~english	@param[in] pIStImageDisplayWndHandle	IStImageDisplayWnd interface handle.
		@~english	@param[out] pnValue	Horizontal scroll position value.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	水平スクロールバー位置を取得します。
		@~japanese	@details	水平スクロールバー位置を取得します。
		@~japanese	@param[in] pIStImageDisplayWndHandle	IStImageDisplayWnd インターフェースハンドル
		@~japanese	@param[out] pnValue	水平スクロールバー位置
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStImageDisplayWnd_GetScrollHPosition_t)(const PStApiHandle_t pIStImageDisplayWndHandle, int32_t *pnValue);

	/*!
		@~english	@brief	Set the position of horizontal scroll bar. The value will set as maximum if it exceeds the maximum value.
		@~english	@details	Set the position of horizontal scroll bar. The value will set as maximum if it exceeds the maximum value.
		@~english	@param[in] pIStImageDisplayWndHandle	IStImageDisplayWnd interface handle.
		@~english	@param[in]	value	Horizontal scroll position value.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	水平スクロールバー位置を設定します。
		@~japanese	@details	水平スクロールバー位置を設定します。
		@~japanese	@param[in] pIStImageDisplayWndHandle	IStImageDisplayWnd インターフェースハンドル
		@~japanese	@param[in]	value	水平スクロールバー位置
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStImageDisplayWnd_SetScrollHPosition_t)(const PStApiHandle_t pIStImageDisplayWndHandle, int32_t value);

	/*!
		@~english	@brief	Get the maximum position of vertical scroll bar.
		@~english	@details	Get the maximum position of vertical scroll bar.
		@~english	@param[in] pIStImageDisplayWndHandle	IStImageDisplayWnd interface handle.
		@~english	@param[out] pnValue	Vertical scroll position value.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	垂直スクロールバー位置の最大値を取得します。
		@~japanese	@details	垂直スクロールバー位置の最大値を取得します。
		@~japanese	@param[in] pIStImageDisplayWndHandle	IStImageDisplayWnd インターフェースハンドル
		@~japanese	@param[out] pnValue	垂直スクロールバー位置の最大値
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStImageDisplayWnd_GetScrollVMax_t)(const PStApiHandle_t pIStImageDisplayWndHandle, int32_t *pnValue);

	/*!
		@~english	@brief	Get current position of vertical scroll bar.
		@~english	@details	Get current position of vertical scroll bar.
		@~english	@param[in] pIStImageDisplayWndHandle	IStImageDisplayWnd interface handle.
		@~english	@param[out] pnValue	Vertical scroll position value.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	垂直スクロールバー位置を取得します。
		@~japanese	@details	垂直スクロールバー位置を取得します。
		@~japanese	@param[in] pIStImageDisplayWndHandle	IStImageDisplayWnd インターフェースハンドル
		@~japanese	@param[out] pnValue	垂直スクロールバー位置
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStImageDisplayWnd_GetScrollVPosition_t)(const PStApiHandle_t pIStImageDisplayWndHandle, int32_t *pnValue);

	/*!
		@~english	@brief	Set the position of vertical scroll bar. The value will set as maximum if it exceeds the maximum value.
		@~english	@details	Set the position of vertical scroll bar. The value will set as maximum if it exceeds the maximum value.
		@~english	@param[in] pIStImageDisplayWndHandle	IStImageDisplayWnd interface handle.
		@~english	@param[in]	value	Vertical scroll position value.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	垂直スクロールバー位置を設定します。
		@~japanese	@details	垂直スクロールバー位置を設定します。
		@~japanese	@param[in] pIStImageDisplayWndHandle	IStImageDisplayWnd インターフェースハンドル
		@~japanese	@param[in]	value	垂直スクロールバー位置
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStImageDisplayWnd_SetScrollVPosition_t)(const PStApiHandle_t pIStImageDisplayWndHandle, int32_t value);

	/*!
		@~english	@brief	Get image refreshing interval.
		@~english	@details	Get image refreshing interval.
		@~english	@attention With small refreshing interval value, the display latency time decreases while the CPU utilization increases. On the other hand, with large refreshing interval value, the display latency time increases while the CPU utilization decreases.
		@~english	@param[in] pIStImageDisplayWndHandle	IStImageDisplayWnd interface handle.
		@~english	@param[out] pnValue	Refresh interval value [ms].
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	表示画像のリフレッシュ間隔を取得します。
		@~japanese	@details	表示画像のリフレッシュ間隔を取得します。
		@~japanese	@attention	値を小さくすると遅延時間が短くなりますが、CPU負荷が増加します。逆に値を大きくすると遅延時間が長くなりますが、CPU負荷は軽減されます。
		@~japanese	@param[in] pIStImageDisplayWndHandle	IStImageDisplayWnd インターフェースハンドル
		@~japanese	@param[out] pnValue	描画間隔[ms]。0を設定されていると画像データを登録したタイミングで、再描画がかかるようになります。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStImageDisplayWnd_GetRefreshInterval_t)(const PStApiHandle_t pIStImageDisplayWndHandle, uint32_t *pnValue);

	/*!
		@~english	@brief	Set image refreshing interval.
		@~english	@details	Set image refreshing interval.
		@~english	@attention With small refreshing interval value, the display latency time decreases while the CPU utilization increases. On the other hand, with large refreshing interval value, the display latency time increases while the CPU utilization decreases.
		@~english	@param[in] pIStImageDisplayWndHandle	IStImageDisplayWnd interface handle.
		@~english	@param[in]	value	Refresh interval value [ms].
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	表示画像のリフレッシュ間隔を設定します。
		@~japanese	@details	表示画像のリフレッシュ間隔を設定します。
		@~japanese	@attention	値を小さくすると遅延時間が短くなりますが、CPU負荷が増加します。逆に値を大きくすると遅延時間が長くなりますが、CPU負荷は軽減されます。
		@~japanese	@param[in] pIStImageDisplayWndHandle	IStImageDisplayWnd インターフェースハンドル
		@~japanese	@param[in]	value	描画間隔[ms]。0を指定すると画像データを登録したタイミングで、再描画がかかるようになります。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStImageDisplayWnd_SetRefreshInterval_t)(const PStApiHandle_t pIStImageDisplayWndHandle, uint32_t value);

	/*!
		@~english	@brief	Get zoom mode value.
		@~english	@details	Get zoom mode value.
		@~english	@param[in] pIStImageDisplayWndHandle	IStImageDisplayWnd interface handle.
		@~english	@param[out] peValue	Zoom mode value.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ズームモードを取得します。
		@~japanese	@details	ズームモードを取得します。
		@~japanese	@param[in] pIStImageDisplayWndHandle	IStImageDisplayWnd インターフェースハンドル
		@~japanese	@param[out] peValue	ズームモード
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStImageDisplayWnd_GetZoomMode_t)(const PStApiHandle_t pIStImageDisplayWndHandle, EStZoomMode_t *peValue);

	/*!
		@~english	@brief	Set zoom mode.
		@~english	@details	Set zoom mode.
		@~english	@param[in] pIStImageDisplayWndHandle	IStImageDisplayWnd interface handle.
		@~english	@param[in]	eZM	Zoom mode value.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ズームモードを設定します。
		@~japanese	@details	ズームモードを設定します。
		@~japanese	@param[in] pIStImageDisplayWndHandle	IStImageDisplayWnd インターフェースハンドル
		@~japanese	@param[in]	eZM	ズームモード
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStImageDisplayWnd_SetZoomMode_t)(const PStApiHandle_t pIStImageDisplayWndHandle, EStZoomMode_t eZM);

	/*!
		@~english	@brief	Get manual zoom maginification.
		@~english	@details	Get manual zoom maginification.
		@~english	@param[in] pIStImageDisplayWndHandle	IStImageDisplayWnd interface handle.
		@~english	@param[out] pdblValue	Manual zoom maginification.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	マニュアルズーム時の倍率を取得します。
		@~japanese	@details	マニュアルズーム時の倍率を取得します。
		@~japanese	@param[in] pIStImageDisplayWndHandle	IStImageDisplayWnd インターフェースハンドル
		@~japanese	@param[out] pdblValue	マニュアルズーム時の倍率
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStImageDisplayWnd_GetManualZoomMagnification_t)(const PStApiHandle_t pIStImageDisplayWndHandle, double *pdblValue);
		
	/*!
		@~english	@brief	Set manual zoom maginification.
		@~english	@details	Set manual zoom maginification.
		@~english	@param[in] pIStImageDisplayWndHandle	IStImageDisplayWnd interface handle.
		@~english	@param[in]	value	Manual zoom maginification.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	マニュアルズーム時の倍率を設定します。
		@~japanese	@details	マニュアルズーム時の倍率を設定します。
		@~japanese	@param[in] pIStImageDisplayWndHandle	IStImageDisplayWnd インターフェースハンドル
		@~japanese	@param[in]	value	マニュアルズーム時の倍率
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStImageDisplayWnd_SetManualZoomMagnification_t)(const PStApiHandle_t pIStImageDisplayWndHandle, double value);

	/*!
		@~english	@brief	Get background style.
		@~english	@details	Get background style.
		@~english	@param[in] pIStImageDisplayWndHandle	IStImageDisplayWnd interface handle.
		@~english	@param[out] peValue	Background style value.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	背景スタイルを取得します。
		@~japanese	@details	背景スタイルを取得します。
		@~japanese	@param[in] pIStImageDisplayWndHandle	IStImageDisplayWnd インターフェースハンドル
		@~japanese	@param[out] peValue	背景スタイル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStImageDisplayWnd_GetBackgroundStyle_t)(const PStApiHandle_t pIStImageDisplayWndHandle, EStBackgroundStyle_t *peValue);

	/*!
		@~english	@brief	Set background style.
		@~english	@details	Set background style.
		@~english	@param[in] pIStImageDisplayWndHandle	IStImageDisplayWnd interface handle.
		@~english	@param[in]	eBS	Background style value.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	背景スタイルを設定します。
		@~japanese	@details	背景スタイルを設定します。
		@~japanese	@param[in] pIStImageDisplayWndHandle	IStImageDisplayWnd インターフェースハンドル
		@~japanese	@param[in]	eBS	背景スタイル 
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStImageDisplayWnd_SetBackgroundStyle_t)(const PStApiHandle_t pIStImageDisplayWndHandle, EStBackgroundStyle_t eBS);

	/*!
		@~english	@brief	Get foreground color.
		@~english	@details	Get foreground color.
		@~english	@param[in] pIStImageDisplayWndHandle	IStImageDisplayWnd interface handle.
		@~english	@param[out] pnValue	Foreground color value in 32bits. Blue(bit23-16), Green(bit15-bit8), Red(bit7-bit0).
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	前景色を取得します。
		@~japanese	@details	前景色を取得します。
		@~japanese	@param[in] pIStImageDisplayWndHandle	IStImageDisplayWnd インターフェースハンドル
		@~japanese	@param[out] pnValue	前景色 bit23-16:青, bit15-8:緑, bit7-0:赤
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStImageDisplayWnd_GetForegroundColor_t)(const PStApiHandle_t pIStImageDisplayWndHandle, uint32_t *pnValue);

	/*!
		@~english	@brief	Set foreground color.
		@~english	@details	Set foreground color.
		@~english	@param[in] pIStImageDisplayWndHandle	IStImageDisplayWnd interface handle.
		@~english	@param[in]	value	Foreground color value in 32bits. Blue(bit23-16), Green(bit15-bit8), Red(bit7-bit0).
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	前景色を設定します。
		@~japanese	@details	前景色を設定します。
		@~japanese	@param[in] pIStImageDisplayWndHandle	IStImageDisplayWnd インターフェースハンドル
		@~japanese	@param[in]	value	前景色 bit23-16:青, bit15-8:緑, bit7-0:赤
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStImageDisplayWnd_SetForegroundColor_t)(const PStApiHandle_t pIStImageDisplayWndHandle, uint32_t value);

	/*!
		@~english	@brief	Get background color.
		@~english	@details	Get background color.
		@~english	@param[in] pIStImageDisplayWndHandle	IStImageDisplayWnd interface handle.
		@~english	@param[out] pnValue	24bits color value as Blue(bit23-16), Green(bit15-bit8), Red(bit7-bit0).
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	背景色を取得します。
		@~japanese	@details	背景色を取得します。
		@~japanese	@param[in] pIStImageDisplayWndHandle	IStImageDisplayWnd インターフェースハンドル
		@~japanese	@param[out] pnValue	背景色 bit23-16:青, bit15-8:緑, bit7-0:赤
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStImageDisplayWnd_GetBackgroundColor_t)(const PStApiHandle_t pIStImageDisplayWndHandle, uint32_t *pnValue);

	/*!
		@~english	@brief	Set background color.
		@~english	@details	Set background color.
		@~english	@param[in] pIStImageDisplayWndHandle	IStImageDisplayWnd interface handle.
		@~english	@param[in]	value	24bits color value as Blue(bit23-16), Green(bit15-bit8), Red(bit7-bit0).
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	背景色を設定します。
		@~japanese	@details	背景色を設定します。
		@~japanese	@param[in] pIStImageDisplayWndHandle	IStImageDisplayWnd インターフェースハンドル
		@~japanese	@param[in]	value	背景色 bit23-16:青, bit15-8:緑, bit7-0:赤
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStImageDisplayWnd_SetBackgroundColor_t)(const PStApiHandle_t pIStImageDisplayWndHandle, uint32_t value);


	/* v1.1.1 */
	/*!
		@~english	@brief	Enable the built in drawing toolbar.
		@~english	@details	Enable the built in drawing toolbar.
		@~english	@param[in] pIStImageDisplayWndHandle	IStImageDisplayWnd interface handle.
		@~english	@param[in]	bValue	true:Enable, false:Disable.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	内蔵の描画用ツールバーを有効化(無効化)します。
		@~japanese	@details	内蔵の描画用ツールバーを有効化(無効化)します。
		@~japanese	@param[in] pIStImageDisplayWndHandle	IStImageDisplayWnd インターフェースハンドル
		@~japanese	@param[in]	bValue	true:有効, false:無効
		@~japanese	@return	EStApiCError_t エラーコード
		@since StApi v1.1.1
	*/
	STAPI_PCALL(PStApiGUI_IStImageDisplayWnd_SetBuiltInDrawingToolbar_t)(const PStApiHandle_t pIStImageDisplayWndHandle, bool8_t bValue);
		
	/*!
		@~english	@brief	Check if the built in drawing toolbar is enable or not.
		@~english	@details	Check if the built in drawing toolbar is enable or not.
		@~english	@param[in] pIStImageDisplayWndHandle	IStImageDisplayWnd interface handle.
		@~english	@param[out] pbValue	true:Enable, false:Disable.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	内蔵の描画用ツールバーが有効になっているかどうかを確認します。
		@~japanese	@details	内蔵の描画用ツールバーが有効になっているかどうかを確認します。
		@~japanese	@param[in] pIStImageDisplayWndHandle	IStImageDisplayWnd インターフェースハンドル
		@~japanese	@param[out] pbValue	true:有効, false:無効
		@~japanese	@return	EStApiCError_t エラーコード
		@since StApi v1.1.1
	*/
	STAPI_PCALL(PStApiGUI_IStImageDisplayWnd_GetBuiltInDrawingToolbar_t)(const PStApiHandle_t pIStImageDisplayWndHandle, bool8_t *pbValue);

	/*!
		@~english	@brief	Enable the drawing on the saving image.
		@~english	@details	Enable the drawing on the saving image.
		@~english	@param[in] pIStImageDisplayWndHandle	IStImageDisplayWnd interface handle.
		@~english	@param[in]	bValue	true:Enable, false:Disable.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	保存画像への描画を有効化(無効化)します。
		@~japanese	@details	保存画像への描画を有効化(無効化)します。
		@~japanese	@param[in] pIStImageDisplayWndHandle	IStImageDisplayWnd インターフェースハンドル
		@~japanese	@param[in]	bValue	true:有効, false:無効
		@~japanese	@return	EStApiCError_t エラーコード
		@since StApi v1.1.1
	*/
	STAPI_PCALL(PStApiGUI_IStImageDisplayWnd_SetEnableDrawingOnSavingImage_t)(const PStApiHandle_t pIStImageDisplayWndHandle, bool8_t bValue);
		
	/*!
		@~english	@brief	Check if the drawing on the saving image is enable or not.
		@~english	@details	Check if the drawing on the saving image is enable or not.
		@~english	@param[in] pIStImageDisplayWndHandle	IStImageDisplayWnd interface handle.
		@~english	@param[out] pbValue	true:Enable, false:Disable.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	保存画像への描画が有効になっているかどうかを確認します。
		@~japanese	@details	保存画像への描画が有効になっているかどうかを確認します。
		@~japanese	@param[in] pIStImageDisplayWndHandle	IStImageDisplayWnd インターフェースハンドル
		@~japanese	@param[out] pbValue	true:有効, false:無効
		@~japanese	@return	EStApiCError_t エラーコード
		@since StApi v1.1.1
	*/
	STAPI_PCALL(PStApiGUI_IStImageDisplayWnd_GetEnableDrawingOnSavingImage_t)(const PStApiHandle_t pIStImageDisplayWndHandle, bool8_t *pbValue);

	/*!
		@~english	@brief	Get IStDrawingTool interface pointer.
		@~english	@details	Get IStDrawingTool interface pointer.
		@~english	@param[in] pIStImageDisplayWndHandle	IStImageDisplayWnd interface handle.
		@~english	@param[in, out] pIStDrawingToolHandle	IStDrawingTool interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStDrawingTool インターフェースポインターを取得します。
		@~japanese	@details	IStDrawingTool インターフェースポインターを取得します。
		@~japanese	@param[in] pIStImageDisplayWndHandle	IStImageDisplayWnd インターフェースハンドル
		@~japanese	@param[in, out] pIStDrawingToolHandle インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
		@since StApi v1.1.1
	*/
	STAPI_PCALL(PStApiGUI_IStImageDisplayWnd_GetIStDrawingTool_t)(const PStApiHandle_t pIStImageDisplayWndHandle, PStApiHandle_t pIStDrawingToolHandle);



	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStImageDisplayWnd_Functions_t
		@~english	@param[in] pIStImageDisplayWndHandle	IStImageDisplayWnd interface handle.
		@~english	@brief	This structure holds the address of the C language wrapper function of IStImageDisplayWnd.
		@~english	@details	This structure holds the address of the C language wrapper function of IStImageDisplayWnd.
		@~japanese	@brief	この構造体は IStImageDisplayWnd のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IStImageDisplayWnd のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_IStImageDisplayWnd_Functions_t
	{
		/*!
			@copydoc PStApiGUI_IStImageDisplayWnd_GetIStImageDisplayWnd_t()
		*/
		PStApiGUI_IStImageDisplayWnd_GetIStImageDisplayWnd_t		GetIStImageDisplayWnd;

		/*!
			@copydoc PStApiGUI_IStImageDisplayWnd_RegisterIStImage_t()
		*/
		PStApiGUI_IStImageDisplayWnd_RegisterIStImage_t		RegisterIStImage;

		/*!
			@copydoc PStApiGUI_IStImageDisplayWnd_HasImage_t()
		*/
		PStApiGUI_IStImageDisplayWnd_HasImage_t		HasImage;

		/*!
			@copydoc PStApiGUI_IStImageDisplayWnd_GetRegisteredIStImage_t()
		*/
		PStApiGUI_IStImageDisplayWnd_GetRegisteredIStImage_t		GetRegisteredIStImage;

		/*!
			@copydoc PStApiGUI_IStImageDisplayWnd_GetConvertedIStImage_t()
		*/
		PStApiGUI_IStImageDisplayWnd_GetConvertedIStImage_t		GetConvertedIStImage;

		/*!
			@copydoc PStApiGUI_IStImageDisplayWnd_ScreenToImage_t()
		*/
		PStApiGUI_IStImageDisplayWnd_ScreenToImage_t		ScreenToImage;

		/*!
			@copydoc PStApiGUI_IStImageDisplayWnd_GetIStPixelFormatConverter_t()
		*/
		PStApiGUI_IStImageDisplayWnd_GetIStPixelFormatConverter_t		GetIStPixelFormatConverter;

		/*!
			@copydoc PStApiGUI_IStImageDisplayWnd_GetPreviewPixelFormatMode_t()
		*/
		PStApiGUI_IStImageDisplayWnd_GetPreviewPixelFormatMode_t		GetPreviewPixelFormatMode;

		/*!
			@copydoc PStApiGUI_IStImageDisplayWnd_SetPreviewPixelFormatMode_t()
		*/
		PStApiGUI_IStImageDisplayWnd_SetPreviewPixelFormatMode_t		SetPreviewPixelFormatMode;

		/*!
			@copydoc PStApiGUI_IStImageDisplayWnd_GetScrollHMax_t()
		*/
		PStApiGUI_IStImageDisplayWnd_GetScrollHMax_t		GetScrollHMax;

		/*!
			@copydoc PStApiGUI_IStImageDisplayWnd_GetScrollHPosition_t()
		*/
		PStApiGUI_IStImageDisplayWnd_GetScrollHPosition_t		GetScrollHPosition;

		/*!
			@copydoc PStApiGUI_IStImageDisplayWnd_SetScrollHPosition_t()
		*/
		PStApiGUI_IStImageDisplayWnd_SetScrollHPosition_t		SetScrollHPosition;

		/*!
			@copydoc PStApiGUI_IStImageDisplayWnd_GetScrollVMax_t()
		*/
		PStApiGUI_IStImageDisplayWnd_GetScrollVMax_t		GetScrollVMax;

		/*!
			@copydoc PStApiGUI_IStImageDisplayWnd_GetScrollVPosition_t()
		*/
		PStApiGUI_IStImageDisplayWnd_GetScrollVPosition_t		GetScrollVPosition;

		/*!
			@copydoc PStApiGUI_IStImageDisplayWnd_SetScrollVPosition_t()
		*/
		PStApiGUI_IStImageDisplayWnd_SetScrollVPosition_t		SetScrollVPosition;

		/*!
			@copydoc PStApiGUI_IStImageDisplayWnd_GetRefreshInterval_t()
		*/
		PStApiGUI_IStImageDisplayWnd_GetRefreshInterval_t		GetRefreshInterval;

		/*!
			@copydoc PStApiGUI_IStImageDisplayWnd_SetRefreshInterval_t()
		*/
		PStApiGUI_IStImageDisplayWnd_SetRefreshInterval_t		SetRefreshInterval;

		/*!
			@copydoc PStApiGUI_IStImageDisplayWnd_GetZoomMode_t()
		*/
		PStApiGUI_IStImageDisplayWnd_GetZoomMode_t		GetZoomMode;

		/*!
			@copydoc PStApiGUI_IStImageDisplayWnd_SetZoomMode_t()
		*/
		PStApiGUI_IStImageDisplayWnd_SetZoomMode_t		SetZoomMode;

		/*!
			@copydoc PStApiGUI_IStImageDisplayWnd_GetManualZoomMagnification_t()
		*/
		PStApiGUI_IStImageDisplayWnd_GetManualZoomMagnification_t		GetManualZoomMagnification;

		/*!
			@copydoc PStApiGUI_IStImageDisplayWnd_SetManualZoomMagnification_t()
		*/
		PStApiGUI_IStImageDisplayWnd_SetManualZoomMagnification_t		SetManualZoomMagnification;

		/*!
			@copydoc PStApiGUI_IStImageDisplayWnd_GetBackgroundStyle_t()
		*/
		PStApiGUI_IStImageDisplayWnd_GetBackgroundStyle_t		GetBackgroundStyle;

		/*!
			@copydoc PStApiGUI_IStImageDisplayWnd_SetBackgroundStyle_t()
		*/
		PStApiGUI_IStImageDisplayWnd_SetBackgroundStyle_t		SetBackgroundStyle;

		/*!
			@copydoc PStApiGUI_IStImageDisplayWnd_GetForegroundColor_t()
		*/
		PStApiGUI_IStImageDisplayWnd_GetForegroundColor_t		GetForegroundColor;

		/*!
			@copydoc PStApiGUI_IStImageDisplayWnd_SetForegroundColor_t()
		*/
		PStApiGUI_IStImageDisplayWnd_SetForegroundColor_t		SetForegroundColor;

		/*!
			@copydoc PStApiGUI_IStImageDisplayWnd_GetBackgroundColor_t()
		*/
		PStApiGUI_IStImageDisplayWnd_GetBackgroundColor_t		GetBackgroundColor;

		/*!
			@copydoc PStApiGUI_IStImageDisplayWnd_SetBackgroundColor_t()
		*/
		PStApiGUI_IStImageDisplayWnd_SetBackgroundColor_t		SetBackgroundColor;	

		/* v1.1.1 */
		/*!
			@copydoc PStApiGUI_IStImageDisplayWnd_GetBuiltInDrawingToolbar_t()
		*/
		PStApiGUI_IStImageDisplayWnd_GetBuiltInDrawingToolbar_t		GetBuiltInDrawingToolbar;

		/*!
			@copydoc PStApiGUI_IStImageDisplayWnd_SetBuiltInDrawingToolbar_t()
		*/
		PStApiGUI_IStImageDisplayWnd_SetBuiltInDrawingToolbar_t		SetBuiltInDrawingToolbar;

		/*!
			@copydoc PStApiGUI_IStImageDisplayWnd_GetEnableDrawingOnSavingImage_t()
		*/
		PStApiGUI_IStImageDisplayWnd_GetEnableDrawingOnSavingImage_t		GetEnableDrawingOnSavingImage;

		/*!
			@copydoc PStApiGUI_IStImageDisplayWnd_SetEnableDrawingOnSavingImage_t()
		*/
		PStApiGUI_IStImageDisplayWnd_SetEnableDrawingOnSavingImage_t		SetEnableDrawingOnSavingImage;


		/*!
			@copydoc PStApiGUI_IStImageDisplayWnd_GetIStDrawingTool_t()
		*/
		PStApiGUI_IStImageDisplayWnd_GetIStDrawingTool_t		GetIStDrawingTool;
	}StApi_IStImageDisplayWnd_Functions_t, *PStApi_IStImageDisplayWnd_Functions_t;

	/*************************************************************************/
	/* StApi::IStNodeMapDisplayWnd */
	/*************************************************************************/
	/*!
		@~english	@brief	Get IStNodeMapDisplayWnd handle.
		@~english	@details	Get IStNodeMapDisplayWnd handle.
		@~english	@param[in] pSourceHandle	Interface handle that is enable to convert to IStNodeMapDisplayWnd interface handle.
		@~english	@param[in,out] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStNodeMapDisplayWnd ハンドルを取得します。
		@~japanese	@details	IStNodeMapDisplayWnd ハンドルを取得します。
		@~japanese	@param[in] pSourceHandle	IStNodeMapDisplayWnd インターフェースハンドルに変換可能なインターフェースハンドル
		@~japanese	@param[in,out] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStNodeMapDisplayWnd_GetIStNodeMapDisplayWnd_t)(const PStApiHandle_t pSourceHandle, PStApiHandle_t pIStNodeMapDisplayWndHandle);

	/*!
		@~english	@brief	Register the node to be displayed in the Nodemap settings window.
		@~english	@details	Register the node to be displayed in the Nodemap settings window.
		@~english	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd interface handle.
		@~english	@param[in]	pIStNodeMapDisplayWndHandle	Root node handle.
		@~english	@param[in]	szName	Caption for root node.
		@~english	@param[in,out] PStApiHandle_t	Identifier of registered node.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ノードマップ設定画面に表示するノードを登録します。
		@~japanese	@details	ノードマップ設定画面に表示するノードを登録します。
		@~japanese	@param[in]	pIStNodeMapDisplayWndHandle	ノード
		@~japanese	@param[in]	szName	ノードに対するタイトル
		@~japanese	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd インターフェースハンドル
		@~japanese	@param[in,out] PStApiHandle_t	登録ノード識別ハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStNodeMapDisplayWnd_RegisterINodeW_t)(const PStApiHandle_t pIStNodeMapDisplayWndHandle, const PStApiHandle_t pINodeHandle, const wchar_t *szName, PStApiHandle_t pRegisteredINodeHandle);
		
	/*!
		@~english	@brief	Register the node to be displayed in the Nodemap settings window.
		@~english	@details	Register the node to be displayed in the Nodemap settings window.
		@~english	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd interface handle.
		@~english	@param[in]	pIStNodeMapDisplayWndHandle	Root node handle.
		@~english	@param[in]	szName	Caption for root node.
		@~english	@param[in,out] PStApiHandle_t	Identifier of registered node.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ノードマップ設定画面に表示するノードを登録します。
		@~japanese	@details	ノードマップ設定画面に表示するノードを登録します。
		@~japanese	@param[in]	pIStNodeMapDisplayWndHandle	ノード
		@~japanese	@param[in]	szName	ノードに対するタイトル
		@~japanese	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd インターフェースハンドル
		@~japanese	@param[in,out] PStApiHandle_t	登録ノード識別ハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStNodeMapDisplayWnd_RegisterINodeA_t)(const PStApiHandle_t pIStNodeMapDisplayWndHandle, const PStApiHandle_t pINodeHandle, const char *szName, PStApiHandle_t pRegisteredINodeHandle);
		
	/*!
		@~english	@brief	Deregister the node to be displayed in the Nodemap settings window.
		@~english	@details	Deregister the node to be displayed in the Nodemap settings window.
		@~english	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd interface handle.
		@~english	@param[in]	pRegisteredINodeHandle	Identifier of registered node.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ノードの登録を解除します。
		@~japanese	@details	ノードの登録を解除します。
		@~japanese	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd インターフェースハンドル
		@~japanese	@param[in]	pRegisteredINodeHandle	登録ノード識別ハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStNodeMapDisplayWnd_DeregisterINode_t)(const PStApiHandle_t pIStNodeMapDisplayWndHandle, PStApiHandle_t pRegisteredINodeHandle);

	/*!
		@~english	@brief	Check if the list is displayed in alphabetical order (alphabetic mode).
		@~english	@details	Check if the list is displayed in alphabetical order (alphabetic mode).
		@~english	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd interface handle.
		@~english	@param[out] pbValue	True if the list is displayed in alphabetical order (alphabetic mode); false otherwise.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	アルファベットモードかどうかを確認します。
		@~japanese	@details	アルファベットモードかどうかを確認します。
		@~japanese	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd インターフェースハンドル
		@~japanese	@param[out] pbValue	アルファベットモードになっている場合、 true が返されます。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStNodeMapDisplayWnd_GetAlphabeticMode_t)(const PStApiHandle_t pIStNodeMapDisplayWndHandle, bool8_t *pbValue);
		
	/*!
		@~english	@brief	Set alphabetic mode.
		@~english	@details	Set alphabetic mode.
		@~english	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd interface handle.
		@~english	@param[in]	value	If true, the list will be in alphabetical order (alpabetic mode).
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	アルファベットモードを設定します。
		@~japanese	@details	アルファベットモードを設定します。
		@~japanese	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd インターフェースハンドル
		@~japanese	@param[in]	value	アルファベットモードにする場合は、 true を指定します。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStNodeMapDisplayWnd_SetAlphabeticMode_t)(const PStApiHandle_t pIStNodeMapDisplayWndHandle, bool8_t value);

	/*!
		@~english	@brief	Get visibility.
		@~english	@details	Get visibility.
		@~english	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd interface handle.
		@~english	@param[out] peValue	Visibility.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	表示対象項目の Visibility を取得します。
		@~japanese	@details	表示対象項目の Visibility を取得します。
		@~japanese	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd インターフェースハンドル
		@~japanese	@param[out] peValue	Visibility
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStNodeMapDisplayWnd_GetVisibility_t)(const PStApiHandle_t pIStNodeMapDisplayWndHandle, EVisibility *peValue);

	/*!
		@~english	@brief	Set visibility.
		@~english	@details	Set visibility.
		@~english	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd interface handle.
		@~english	@param[in]	eVisibility	Visibility.
		@~english	@return	EStApiCError_t error code. 
		@~japanese	@brief	表示対象項目の Visibility を設定します。
		@~japanese	@details	表示対象項目の Visibility を設定します。 Beginner へ設定すると Beginner 項目のみが表示されます。 Expert へ設定すると Beginner および Expert 項目が表示されます。 Guru へ設定すると Guru, Expert および Beginner 項目が表示されます。
		@~japanese	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd インターフェースハンドル
		@~japanese	@param[in]	eVisibility	Visibility
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStNodeMapDisplayWnd_SetVisibility_t)(const PStApiHandle_t pIStNodeMapDisplayWndHandle, EVisibility eVisibility);

	/*!
		@~english	@brief	Expand the list.
		@~english	@details	Expand the list.
		@~english	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	リストを展開します。
		@~japanese	@details	リストを展開します。
		@~japanese	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStNodeMapDisplayWnd_Expand_t)(const PStApiHandle_t pIStNodeMapDisplayWndHandle);
		
	/*!
		@~english	@brief	Collapse the list.
		@~english	@details	Collapse the list.
		@~english	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	リストを折りたたみます。
		@~japanese	@details	リストを折りたたみます。
		@~japanese	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStNodeMapDisplayWnd_Collapse_t)(const PStApiHandle_t pIStNodeMapDisplayWndHandle);

	/*!
		@~english	@brief	Refresh the list.
		@~english	@details	Refresh the list.
		@~english	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	リストを再描画します。
		@~japanese	@details	リストを再描画します。
		@~japanese	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStNodeMapDisplayWnd_Refresh_t)(const PStApiHandle_t pIStNodeMapDisplayWndHandle);

	/*!
		@~english	@brief	Check if polling is enabled.
		@~english	@details	Check if polling is enabled.
		@~english	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd interface handle.
		@~english	@param[out] pbValue	True if polling is enabled; false otherwise.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ポーリングの有効/無効を確認します。
		@~japanese	@details	ポーリングの有効/無効を確認します。
		@~japanese	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd インターフェースハンドル
		@~japanese	@param[out] pbValue	ポーリングが有効な場合、 true が返されます。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStNodeMapDisplayWnd_GetEnablePolling_t)(const PStApiHandle_t pIStNodeMapDisplayWndHandle, bool8_t *pbValue);
		
	/*!
		@~english	@brief	Enable or disable polling.
		@~english	@details	Enable or disable polling.
		@~english	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd interface handle.
		@~english	@param[in]	value	True to enable polling; false to disable polling.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ポーリングの有効/無効を設定します。
		@~japanese	@details	ポーリングの有効/無効を設定します。ポーリングを有効にすると定期的にポーリング対象の値が確認されるようになります。
		@~japanese	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd インターフェースハンドル
		@~japanese	@param[in]	value	ポーリングを有効にする場合、 true を指定します。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStNodeMapDisplayWnd_SetEnablePolling_t)(const PStApiHandle_t pIStNodeMapDisplayWndHandle, bool8_t value);

	/*!
		@~english	@brief	Check the visibility of the alphabetic mode button.
		@~english	@details	Check the visibility of the alphabetic mode button.
		@~english	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd interface handle.
		@~english	@param[out] pbValue	True if the button is visible; false otherwise.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	アルファベットモード設定ボタンの表示/非表示を確認します。
		@~japanese	@details	アルファベットモード設定ボタンの表示/非表示を確認します。
		@~japanese	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd インターフェースハンドル
		@~japanese	@param[out] pbValue	アルファベットモード設定ボタンが表示されている場合、 true が返されます。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStNodeMapDisplayWnd_GetVisibleAlphabeticMode_t)(const PStApiHandle_t pIStNodeMapDisplayWndHandle, bool8_t *pbValue);
		
	/*!
		@~english	@brief	Set the visibility of the alphabetic mode button.
		@~english	@details	Set the visibility of the alphabetic mode button.
		@~english	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd interface handle.
		@~english	@param[in]	value	True to display the alphabetic mode button; false to hide the alphabetic mode button.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	アルファベットモード設定ボタンの表示/非表示を設定します。
		@~japanese	@details	アルファベットモード設定ボタンの表示/非表示を設定します。
		@~japanese	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd インターフェースハンドル
		@~japanese	@param[in]	value	アルファベットモード設定ボタンを表示する場合、 true を指定します。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStNodeMapDisplayWnd_SetVisibleAlphabeticMode_t)(const PStApiHandle_t pIStNodeMapDisplayWndHandle, bool8_t value);

	/*!
		@~english	@brief	Check the visibility of the expand button.
		@~english	@details	Check the visibility of the expand button.
		@~english	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd interface handle.
		@~english	@param[out] pbValue	True if the button is visible; false otherwise.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	展開ボタンの表示/非表示を確認します。
		@~japanese	@details	展開ボタンの表示/非表示を確認します。
		@~japanese	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd インターフェースハンドル
		@~japanese	@param[out] pbValue	展開ボタンが表示されている場合、 true が返されます。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStNodeMapDisplayWnd_GetVisibleExpand_t)(const PStApiHandle_t pIStNodeMapDisplayWndHandle, bool8_t *pbValue);
		
	/*!
		@~english	@brief	Set the visibility of the expand button.
		@~english	@details	Set the visibility of the expand button.
		@~english	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd interface handle.
		@~english	@param[in]	value	True to display the expand button; false to hide the expand button.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	展開ボタンの表示/非表示を設定します。
		@~japanese	@details	展開ボタンの表示/非表示を設定します。
		@~japanese	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd インターフェースハンドル
		@~japanese	@param[in]	value	展開ボタンを表示する場合、 true を指定します。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStNodeMapDisplayWnd_SetVisibleExpand_t)(const PStApiHandle_t pIStNodeMapDisplayWndHandle, bool8_t value);

	/*!
		@~english	@brief	Check the visibility of the collapse button.
		@~english	@details	Check the visibility of the collapse button.
		@~english	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd interface handle.
		@~english	@param[out] pbValue	True if the button is visible; false otherwise.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	折りたたみボタンの表示/非表示を確認します。
		@~japanese	@details	折りたたみボタンの表示/非表示を確認します。
		@~japanese	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd インターフェースハンドル
		@~japanese	@param[out] pbValue	折りたたみボタンが表示されている場合、 true が返されます。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStNodeMapDisplayWnd_GetVisibleCollapse_t)(const PStApiHandle_t pIStNodeMapDisplayWndHandle, bool8_t *pbValue);

	/*!
		@~english	@brief	Set the visibility of the collapse button.
		@~english	@details	Set the visibility of the collapse button.
		@~english	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd interface handle.
		@~english	@param[in]	value	True to display the collapse button; false to hide the collapse button.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	折りたたみボタンの表示/非表示を設定します。
		@~japanese	@details	折りたたみボタンの表示/非表示を設定します。
		@~japanese	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd インターフェースハンドル
		@~japanese	@param[in]	value	折りたたみボタンを表示する場合、 true を指定します。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStNodeMapDisplayWnd_SetVisibleCollapse_t)(const PStApiHandle_t pIStNodeMapDisplayWndHandle, bool8_t value);

	/*!
		@~english	@brief	Check the visibility of the refresh button.
		@~english	@details	Check the visibility of the refresh button.
		@~english	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd interface handle.
		@~english	@param[out] pbValue	True if the button is visible; false otherwise.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	リフレッシュボタンの表示/非表示を確認します。
		@~japanese	@details	リフレッシュボタンの表示/非表示を確認します。
		@~japanese	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd インターフェースハンドル
		@~japanese	@param[out] pbValue	リフレッシュボタンが表示されている場合、 true が返されます。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStNodeMapDisplayWnd_GetVisibleRefresh_t)(const PStApiHandle_t pIStNodeMapDisplayWndHandle, bool8_t *pbValue);

	/*!
		@~english	@brief	Set the visibility of the refresh button.
		@~english	@details	Set the visibility of the refresh button.
		@~english	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd interface handle.
		@~english	@param[in]	value	True to display the refresh button; false to hide the refresh button.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	リフレッシュボタンの表示/非表示を設定します。
		@~japanese	@details	リフレッシュボタンの表示/非表示を設定します。
		@~japanese	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd インターフェースハンドル
		@~japanese	@param[in]	value	リフレッシュボタンを表示する場合、 true を指定します。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStNodeMapDisplayWnd_SetVisibleRefresh_t)(const PStApiHandle_t pIStNodeMapDisplayWndHandle, bool8_t value);

	/*!
		@~english	@brief	Check the visibility of the polling check box.
		@~english	@details	Check the visibility of the polling check box.
		@~english	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd interface handle.
		@~english	@param[out] pbValue	True if the check box is visible; false otherwise.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ポーリングチェックボックスの表示/非表示を確認します。
		@~japanese	@details	ポーリングチェックボックスの表示/非表示を確認します。
		@~japanese	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd インターフェースハンドル
		@~japanese	@param[out] pbValue	ポーリングチェックボックスが表示されている場合、 true が返されます。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStNodeMapDisplayWnd_GetVisiblePolling_t)(const PStApiHandle_t pIStNodeMapDisplayWndHandle, bool8_t *pbValue);

	/*!
		@~english	@brief	Set the visibility of the polling check box.
		@~english	@details	Set the visibility of the polling check box.
		@~english	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd interface handle.
		@~english	@param[in]	value	True to display the polling check box; false to hide the polling check box.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ポーリングチェックボックスの表示/非表示を設定します。
		@~japanese	@details	ポーリングチェックボックスの表示/非表示を設定します。
		@~japanese	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd インターフェースハンドル
		@~japanese	@param[in]	value	ポーリングチェックボックスを表示する場合、 true を指定します。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStNodeMapDisplayWnd_SetVisiblePolling_t)(const PStApiHandle_t pIStNodeMapDisplayWndHandle, bool8_t value);

	/*!
		@~english	@brief	Check the visibility of the node visibility combo box.
		@~english	@details	Check the visibility of the node visibility combo box.
		@~english	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd interface handle.
		@~english	@param[out] pbValue	True if the combo box is visible; false otherwise.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	Visibilityコンボボックスの表示/非表示を確認します。
		@~japanese	@details	Visibilityコンボボックスの表示/非表示を確認します。
		@~japanese	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd インターフェースハンドル
		@~japanese	@param[out] pbValue	Visibilityコンボボックスが表示されている場合、 true が返されます。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStNodeMapDisplayWnd_GetVisibleVisibility_t)(const PStApiHandle_t pIStNodeMapDisplayWndHandle, bool8_t *pbValue);

	/*!
		@~english	@brief	Set the visibility of the node visibility combo box.
		@~english	@details	Set the visibility of the node visibility combo box.
		@~english	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd interface handle.
		@~english	@param[in]	value	True to display the node visibility combo box; false to hide the node visibility combo box.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	Visibilityコンボボックスの表示/非表示を設定します。
		@~japanese	@details	Visibilityコンボボックスの表示/非表示を設定します。
		@~japanese	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd インターフェースハンドル
		@~japanese	@param[in]	value	Visibilityコンボボックスを表示する場合、 true を指定します。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStNodeMapDisplayWnd_SetVisibleVisibility_t)(const PStApiHandle_t pIStNodeMapDisplayWndHandle, bool8_t value);

	/*!
		@~english	@brief	Check the visibility of the node description.
		@~english	@details	Check the visibility of the node description.
		@~english	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd interface handle.
		@~english	@param[out] pbValue	True if the description is visible; false otherwise.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	説明文の表示/非表示を確認します。
		@~japanese	@details	説明文の表示/非表示を確認します。
		@~japanese	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd インターフェースハンドル
		@~japanese	@param[out] pbValue	説明文が表示されている場合、 true が返されます。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStNodeMapDisplayWnd_GetVisibleDescription_t)(const PStApiHandle_t pIStNodeMapDisplayWndHandle, bool8_t *pbValue);

	/*!
		@~english	@brief	Set the visibility of the node description.
		@~english	@details	Set the visibility of the node description.
		@~english	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd interface handle.
		@~english	@param[in]	value	True to display the node description; false to hide the node description.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	説明文の表示/非表示を設定します。
		@~japanese	@details	説明文の表示/非表示を設定します。
		@~japanese	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd インターフェースハンドル
		@~japanese	@param[in]	value	説明文を表示する場合、 true を指定します。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStNodeMapDisplayWnd_SetVisibleDescription_t)(const PStApiHandle_t pIStNodeMapDisplayWndHandle, bool8_t value);
		
	/*!
		@~english	@brief	Check the visibility of the sample code in the node description.
		@~english	@details	Check the visibility of the sample code in the node description.
		@~english	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd interface handle.
		@~english	@param[out] pbValue	True if a sample code is visible; false otherwise.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	説明文内のサンプルプログラムの表示/非表示を確認します。
		@~japanese	@details	説明文内のサンプルプログラムの表示/非表示を確認します。
		@~japanese	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd インターフェースハンドル
		@~japanese	@param[out] pbValue	説明文内のサンプルプログラムが表示されている場合、 true が返されます。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStNodeMapDisplayWnd_GetVisibleDescriptionSampleCode_t)(const PStApiHandle_t pIStNodeMapDisplayWndHandle, bool8_t *pbValue);

	/*!
		@~english	@brief	Set the visibility of the sample code in the node description.
		@~english	@details	Set the visibility of the sample code in the node description.
		@~english	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd interface handle.
		@~english	@param[in]	value	True to display the sample code in the node description; false to hide the sample code in the node description.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	説明文内のサンプルプログラムの表示/非表示を設定します。
		@~japanese	@details	説明文内のサンプルプログラムの表示/非表示を設定します。
		@~japanese	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd インターフェースハンドル
		@~japanese	@param[in]	value	説明文内のサンプルプログラムを表示する場合、 true を指定します。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStNodeMapDisplayWnd_SetVisibleDescriptionSampleCode_t)(const PStApiHandle_t pIStNodeMapDisplayWndHandle, bool8_t value);

	/* v1.1.1 */
	/*!
		@~english	@brief	Check the visibility of the node filter check box and text box.
		@~english	@details	Check the visibility of the node filter check box and text box.
		@~english	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd interface handle.
		@~english	@param[out] pbValue	True if the combo box is visible; false otherwise.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	Filterチェックボックスおよびテキストボックスの表示/非表示を確認します。
		@~japanese	@details	Filterチェックボックスおよびテキストボックスの表示/非表示を確認します。
		@~japanese	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd インターフェースハンドル
		@~japanese	@param[out] pbValue	Filterチェックボックスおよびテキストボックスが表示されている場合、 true が返されます。
		@~japanese	@return	EStApiCError_t エラーコード
		@since	StApi v1.1.1
	*/
	STAPI_PCALL(PStApiGUI_IStNodeMapDisplayWnd_GetVisibleFilter_t)(const PStApiHandle_t pIStNodeMapDisplayWndHandle, bool8_t *pbValue);

	/*!
		@~english	@brief	Set the visibility of the node filter check box and text box.
		@~english	@details	Set the visibility of the node filter check box and text box.
		@~english	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd interface handle.
		@~english	@param[in]	value	True to display the node filter check box and text box; false to hide the node filter check box and text box.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	Filterチェックボックスおよびテキストボックスの表示/非表示を設定します。
		@~japanese	@details	Filterチェックボックスおよびテキストボックスの表示/非表示を設定します。
		@~japanese	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd インターフェースハンドル
		@~japanese	@param[in]	value	Filterチェックボックスおよびテキストボックスを表示する場合、 true を指定します。
		@~japanese	@return	EStApiCError_t エラーコード
		@since	StApi v1.1.1
	*/
	STAPI_PCALL(PStApiGUI_IStNodeMapDisplayWnd_SetVisibleFilter_t)(const PStApiHandle_t pIStNodeMapDisplayWndHandle, bool8_t value);
		
	/*!
		@~english	@brief	Get filter string.
		@~english	@details	Get filter string.
		@~english	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd interface handle.
		@~english	@param[in, out] szText	Filter string.
		@~english	@param[in, out] pnLen	Buffer / String length.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	フィルター文字列を取得します。
		@~japanese	@details	フィルター文字列を取得します。
		@~japanese	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd インターフェースハンドル
		@~japanese	@param[in, out] szText	フィルター文字列
		@~japanese	@param[in, out] pnLen	バッファ / 文字列長
		@~japanese	@return	EStApiCError_t エラーコード
		@since	StApi v1.1.1
	*/
	STAPI_PCALL(PStApiGUI_IStNodeMapDisplayWnd_GetFilterTextA_t)(const PStApiHandle_t pIStNodeMapDisplayWndHandle, char *szText, size_t *pnLen);

	/*!
		@~english	@brief	Set filter string.
		@~english	@details	Set filter string.
		@~english	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd interface handle.
		@~english	@param[in]	szText	Filter string.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	フィルター文字列を設定します。
		@~japanese	@details	フィルター文字列を設定します。
		@~japanese	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd インターフェースハンドル
		@~japanese	@param[in]	szText	フィルター文字列
		@~japanese	@return	EStApiCError_t エラーコード
		@since	StApi v1.1.1
	*/
	STAPI_PCALL(PStApiGUI_IStNodeMapDisplayWnd_SetFilterTextA_t)(const PStApiHandle_t pIStNodeMapDisplayWndHandle, const char *szText);

	/*!
		@~english	@brief	Check the filter is enabled or not.
		@~english	@details	Check the filter is enabled or not.
		@~english	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd interface handle.
		@~english	@param[out] pbValue	True if the filter is enabled; false otherwise.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	Filterが有効化否かを確認します。
		@~japanese	@details	Filterが有効化否かを確認します。
		@~japanese	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd インターフェースハンドル
		@~japanese	@param[out] pbValue	Filterが有効な場合、 true が返されます。
		@~japanese	@return	EStApiCError_t エラーコード
		@since	StApi v1.1.1
	*/
	STAPI_PCALL(PStApiGUI_IStNodeMapDisplayWnd_GetEnableFilter_t)(const PStApiHandle_t pIStNodeMapDisplayWndHandle, bool8_t *pbValue);

	/*!
		@~english	@brief	Activate or deactivate the filter.
		@~english	@details	Activate or deactivate the filter.
		@~english	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd interface handle.
		@~english	@param[in]	value	True to activate the filter check; false to deactivate the filter.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	Filterを有効化または無効化します。
		@~japanese	@details	Filterを有効化または無効化します。
		@~japanese	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd インターフェースハンドル
		@~japanese	@param[in]	value	Filterを有効化する場合、 true を指定します。
		@~japanese	@return	EStApiCError_t エラーコード
		@since	StApi v1.1.1
	*/
	STAPI_PCALL(PStApiGUI_IStNodeMapDisplayWnd_SetEnableFilter_t)(const PStApiHandle_t pIStNodeMapDisplayWndHandle, bool8_t value);

	/*!
		@~english	@brief	Check the regular expression filter is enabled or not.
		@~english	@details	Check the regular expression filter is enabled or not.
		@~english	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd interface handle.
		@~english	@param[out] pbValue	True if the regular expression filter is enabled; false otherwise.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	正規表現フィルターが有効化否かを確認します。
		@~japanese	@details	正規表現フィルターが有効化否かを確認します。
		@~japanese	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd インターフェースハンドル
		@~japanese	@param[out] pbValue	正規表現フィルターが有効な場合、 true が返されます。
		@~japanese	@return	EStApiCError_t エラーコード
		@since	StApi v1.1.1
	*/
	STAPI_PCALL(PStApiGUI_IStNodeMapDisplayWnd_GetEnableRegularExpression_t)(const PStApiHandle_t pIStNodeMapDisplayWndHandle, bool8_t *pbValue);

	/*!
		@~english	@brief	Activate or deactivate the regular expression filter.
		@~english	@details	Activate or deactivate the regular expression filter.
		@~english	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd interface handle.
		@~english	@param[in]	value	True to activate the regular expression filter check; false to deactivate the regular expression filter.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	正規表現フィルターを有効化または無効化します。
		@~japanese	@details	正規表現フィルターを有効化または無効化します。
		@~japanese	@param[in] pIStNodeMapDisplayWndHandle	IStNodeMapDisplayWnd インターフェースハンドル
		@~japanese	@param[in]	value	正規表現フィルターを有効化する場合、 true を指定します。
		@~japanese	@return	EStApiCError_t エラーコード
		@since	StApi v1.1.1
	*/
	STAPI_PCALL(PStApiGUI_IStNodeMapDisplayWnd_SetEnableRegularExpression_t)(const PStApiHandle_t pIStNodeMapDisplayWndHandle, bool8_t value);

	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStNodeMapDisplayWnd_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IStNodeMapDisplayWnd.
		@~english	@details	This structure holds the address of the C language wrapper function of IStNodeMapDisplayWnd.
		@~japanese	@brief	この構造体は IStNodeMapDisplayWnd のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IStNodeMapDisplayWnd のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_IStNodeMapDisplayWnd_Functions_t
	{
		/*!
			@copydoc PStApiGUI_IStNodeMapDisplayWnd_GetIStNodeMapDisplayWnd_t()
		*/
		PStApiGUI_IStNodeMapDisplayWnd_GetIStNodeMapDisplayWnd_t		GetIStNodeMapDisplayWnd;

		/*!
			@copydoc PStApiGUI_IStNodeMapDisplayWnd_RegisterINodeW_t()
		*/
		PStApiGUI_IStNodeMapDisplayWnd_RegisterINodeW_t		RegisterINodeW;

		/*!
			@copydoc PStApiGUI_IStNodeMapDisplayWnd_RegisterINodeA_t()
		*/
		PStApiGUI_IStNodeMapDisplayWnd_RegisterINodeA_t		RegisterINodeA;

		/*!
			@copydoc PStApiGUI_IStNodeMapDisplayWnd_DeregisterINode_t()
		*/
		PStApiGUI_IStNodeMapDisplayWnd_DeregisterINode_t		DeregisterINode;

		/*!
			@copydoc PStApiGUI_IStNodeMapDisplayWnd_GetAlphabeticMode_t()
		*/
		PStApiGUI_IStNodeMapDisplayWnd_GetAlphabeticMode_t		GetAlphabeticMode;

		/*!
			@copydoc PStApiGUI_IStNodeMapDisplayWnd_SetAlphabeticMode_t()
		*/
		PStApiGUI_IStNodeMapDisplayWnd_SetAlphabeticMode_t		SetAlphabeticMode;

		/*!
			@copydoc PStApiGUI_IStNodeMapDisplayWnd_GetVisibility_t()
		*/
		PStApiGUI_IStNodeMapDisplayWnd_GetVisibility_t		GetVisibility;

		/*!
			@copydoc PStApiGUI_IStNodeMapDisplayWnd_SetVisibility_t()
		*/
		PStApiGUI_IStNodeMapDisplayWnd_SetVisibility_t		SetVisibility;
		
		/*!
			@copydoc PStApiGUI_IStNodeMapDisplayWnd_Expand_t()
		*/
		PStApiGUI_IStNodeMapDisplayWnd_Expand_t		Expand;

		/*!
			@copydoc PStApiGUI_IStNodeMapDisplayWnd_Collapse_t()
		*/
		PStApiGUI_IStNodeMapDisplayWnd_Collapse_t		Collapse;

		/*!
			@copydoc PStApiGUI_IStNodeMapDisplayWnd_Refresh_t()
		*/
		PStApiGUI_IStNodeMapDisplayWnd_Refresh_t		Refresh;

		/*!
			@copydoc PStApiGUI_IStNodeMapDisplayWnd_GetEnablePolling_t()
		*/
		PStApiGUI_IStNodeMapDisplayWnd_GetEnablePolling_t		GetEnablePolling;

		/*!
			@copydoc PStApiGUI_IStNodeMapDisplayWnd_SetEnablePolling_t()
		*/
		PStApiGUI_IStNodeMapDisplayWnd_SetEnablePolling_t		SetEnablePolling;

		/*!
			@copydoc PStApiGUI_IStNodeMapDisplayWnd_GetVisibleAlphabeticMode_t()
		*/
		PStApiGUI_IStNodeMapDisplayWnd_GetVisibleAlphabeticMode_t		GetVisibleAlphabeticMode;

		/*!
			@copydoc PStApiGUI_IStNodeMapDisplayWnd_SetVisibleAlphabeticMode_t()
		*/
		PStApiGUI_IStNodeMapDisplayWnd_SetVisibleAlphabeticMode_t		SetVisibleAlphabeticMode;

		/*!
			@copydoc PStApiGUI_IStNodeMapDisplayWnd_GetVisibleExpand_t()
		*/
		PStApiGUI_IStNodeMapDisplayWnd_GetVisibleExpand_t		GetVisibleExpand;

		/*!
			@copydoc PStApiGUI_IStNodeMapDisplayWnd_SetVisibleExpand_t()
		*/
		PStApiGUI_IStNodeMapDisplayWnd_SetVisibleExpand_t		SetVisibleExpand;

		/*!
			@copydoc PStApiGUI_IStNodeMapDisplayWnd_GetVisibleCollapse_t()
		*/
		PStApiGUI_IStNodeMapDisplayWnd_GetVisibleCollapse_t		GetVisibleCollapse;

		/*!
			@copydoc PStApiGUI_IStNodeMapDisplayWnd_SetVisibleCollapse_t()
		*/
		PStApiGUI_IStNodeMapDisplayWnd_SetVisibleCollapse_t		SetVisibleCollapse;

		/*!
			@copydoc PStApiGUI_IStNodeMapDisplayWnd_GetVisibleRefresh_t()
		*/
		PStApiGUI_IStNodeMapDisplayWnd_GetVisibleRefresh_t		GetVisibleRefresh;

		/*!
			@copydoc PStApiGUI_IStNodeMapDisplayWnd_SetVisibleRefresh_t()
		*/
		PStApiGUI_IStNodeMapDisplayWnd_SetVisibleRefresh_t		SetVisibleRefresh;

		/*!
			@copydoc PStApiGUI_IStNodeMapDisplayWnd_GetVisiblePolling_t()
		*/
		PStApiGUI_IStNodeMapDisplayWnd_GetVisiblePolling_t		GetVisiblePolling;
				
		/*!
			@copydoc PStApiGUI_IStNodeMapDisplayWnd_SetVisiblePolling_t()
		*/
		PStApiGUI_IStNodeMapDisplayWnd_SetVisiblePolling_t		SetVisiblePolling;

		/*!
			@copydoc PStApiGUI_IStNodeMapDisplayWnd_GetVisibleVisibility_t()
		*/
		PStApiGUI_IStNodeMapDisplayWnd_GetVisibleVisibility_t		GetVisibleVisibility;

		/*!
			@copydoc PStApiGUI_IStNodeMapDisplayWnd_SetVisibleVisibility_t()
		*/
		PStApiGUI_IStNodeMapDisplayWnd_SetVisibleVisibility_t		SetVisibleVisibility;

		/*!
			@copydoc PStApiGUI_IStNodeMapDisplayWnd_GetVisibleDescription_t()
		*/
		PStApiGUI_IStNodeMapDisplayWnd_GetVisibleDescription_t		GetVisibleDescription;

		/*!
			@copydoc PStApiGUI_IStNodeMapDisplayWnd_SetVisibleDescription_t()
		*/
		PStApiGUI_IStNodeMapDisplayWnd_SetVisibleDescription_t		SetVisibleDescription;

		/*!
			@copydoc PStApiGUI_IStNodeMapDisplayWnd_GetVisibleDescriptionSampleCode_t()
		*/
		PStApiGUI_IStNodeMapDisplayWnd_GetVisibleDescriptionSampleCode_t		GetVisibleDescriptionSampleCode;

		/*!
			@copydoc PStApiGUI_IStNodeMapDisplayWnd_SetVisibleDescriptionSampleCode_t()
		*/
		PStApiGUI_IStNodeMapDisplayWnd_SetVisibleDescriptionSampleCode_t		SetVisibleDescriptionSampleCode;

		/*!
			@copydoc PStApiGUI_IStNodeMapDisplayWnd_GetVisibleFilter_t()
		*/
			PStApiGUI_IStNodeMapDisplayWnd_GetVisibleFilter_t		GetVisibleFilter;

		/*!
			@copydoc PStApiGUI_IStNodeMapDisplayWnd_SetVisibleFilter_t()
		*/
		PStApiGUI_IStNodeMapDisplayWnd_SetVisibleFilter_t		SetVisibleFilter;

		/*!
			@copydoc PStApiGUI_IStNodeMapDisplayWnd_GetFilterTextA_t()
		*/
		PStApiGUI_IStNodeMapDisplayWnd_GetFilterTextA_t		GetFilterTextA;

		/*!
			@copydoc PStApiGUI_IStNodeMapDisplayWnd_SetFilterTextA_t()
		*/
		PStApiGUI_IStNodeMapDisplayWnd_SetFilterTextA_t		SetFilterTextA;

		/*!
			@copydoc PStApiGUI_IStNodeMapDisplayWnd_GetEnableFilter_t()
		*/
		PStApiGUI_IStNodeMapDisplayWnd_GetEnableFilter_t		GetEnableFilter;

		/*!
			@copydoc PStApiGUI_IStNodeMapDisplayWnd_SetEnableFilter_t()
		*/
		PStApiGUI_IStNodeMapDisplayWnd_SetEnableFilter_t		SetEnableFilter;

		/*!
			@copydoc PStApiGUI_IStNodeMapDisplayWnd_GetEnableRegularExpression_t()
		*/
		PStApiGUI_IStNodeMapDisplayWnd_GetEnableRegularExpression_t		GetEnableRegularExpression;

		/*!
			@copydoc PStApiGUI_IStNodeMapDisplayWnd_SetEnableRegularExpression_t()
		*/
		PStApiGUI_IStNodeMapDisplayWnd_SetEnableRegularExpression_t		SetEnableRegularExpression;
	}StApi_IStNodeMapDisplayWnd_Functions_t, *PStApi_IStNodeMapDisplayWnd_Functions_t;

	/*************************************************************************/
	/* StApi::IStCallbackParamStApiGUIEventBaseWnd */
	/*************************************************************************/
	/*!
		@~english	@brief	Acquire IStWnd interface handle.
		@~english	@details	Acquire IStWnd interface handle.
		@~english	@param[in] pIStCallbackParamBaseHandle	IStCallbackParamBase interface handle.
		@~english	@param[in,out] pIStWndHandle	IStWnd interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStWnd インターフェースハンドルを取得します。
		@~japanese	@details	IStWnd インターフェースハンドルを取得します。
		@~japanese	@param[in]	pIStCallbackParamBaseHandle	IStCallbackParamBase インターフェースハンドル
		@~japanese	@param[in,out] pIStWndHandle	IStWnd インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStCallbackParamStApiGUIEventBaseWnd_GetIStWnd_t)(const PStApiHandle_t pIStCallbackParamBaseHandle, PStApiHandle_t pIStWndHandle);
	
	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStCallbackParamStApiGUIEventBaseWnd_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IStCallbackParamStApiGUIEventBaseWnd.
		@~english	@details	This structure holds the address of the C language wrapper function of IStCallbackParamStApiGUIEventBaseWnd.
		@~japanese	@brief	この構造体は IStCallbackParamStApiGUIEventBaseWnd のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IStCallbackParamStApiGUIEventBaseWnd のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_IStCallbackParamStApiGUIEventBaseWnd_Functions_t
	{
		/*!
			@copydoc PStApiGUI_IStCallbackParamStApiGUIEventBaseWnd_GetIStWnd_t()
		*/
		PStApiGUI_IStCallbackParamStApiGUIEventBaseWnd_GetIStWnd_t		GetIStWnd;
	}StApi_IStCallbackParamStApiGUIEventBaseWnd_Functions_t, *PStApi_IStCallbackParamStApiGUIEventBaseWnd_Functions_t;

	/*************************************************************************/
	/* StApi::IStCallbackParamStApiGUIEventBaseWndClose */
	/*************************************************************************/
	/*!
		@~english	@brief	Call if you want to cancel close.
		@~english	@details	Call if you want to cancel close.
		@~english	@param[in] pIStCallbackParamBaseHandle	IStCallbackParamBase interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	クローズ処理をキャンセルさせます。
		@~japanese	@details	クローズ処理をキャンセルさせます。
		@~japanese	@param[in]	pIStCallbackParamBaseHandle	IStCallbackParamBase インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStCallbackParamStApiGUIEventBaseWndClose_CancelClose_t)(const PStApiHandle_t pIStCallbackParamBaseHandle);
	
	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStCallbackParamStApiGUIEventBaseWndClose_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IStCallbackParamStApiGUIEventBaseWndClose.
		@~english	@details	This structure holds the address of the C language wrapper function of IStCallbackParamStApiGUIEventBaseWndClose.
		@~japanese	@brief	この構造体は IStCallbackParamStApiGUIEventBaseWndClose のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IStCallbackParamStApiGUIEventBaseWndClose のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_IStCallbackParamStApiGUIEventBaseWndClose_Functions_t
	{
		/*!
			@copydoc PStApiGUI_IStCallbackParamStApiGUIEventBaseWndClose_CancelClose_t()
		*/
		PStApiGUI_IStCallbackParamStApiGUIEventBaseWndClose_CancelClose_t		CancelClose;
	}StApi_IStCallbackParamStApiGUIEventBaseWndClose_Functions_t, *PStApi_IStCallbackParamStApiGUIEventBaseWndClose_Functions_t;

	/*************************************************************************/
	/* StApi::IStCallbackParamStApiGUIEventBaseWndError */
	/*************************************************************************/
	/*!
		@~english	@brief	Acquire reference of GenericException.
		@~english	@details	Acquire reference of GenericException.
		@~english	@param[in] pIStCallbackParamBaseHandle	IStCallbackParamBase interface handle.
		@~english	@param[out] peValue	EStApiCError_t error code.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	例外情報を取得します。
		@~japanese	@details	例外情報を取得します。
		@~japanese	@param[in]	pIStCallbackParamBaseHandle	IStCallbackParamBase インターフェースハンドル
		@~japanese	@param[out] peValue	EStApiCError_t エラーコード
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStCallbackParamStApiGUIEventBaseWndError_GetException_t)(const PStApiHandle_t pIStCallbackParamBaseHandle, EStApiCError_t *peValue);
	
	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStCallbackParamStApiGUIEventBaseWndError_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IStCallbackParamStApiGUIEventBaseWndError.
		@~english	@details	This structure holds the address of the C language wrapper function of IStCallbackParamStApiGUIEventBaseWndError.
		@~japanese	@brief	この構造体は IStCallbackParamStApiGUIEventBaseWndError のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IStCallbackParamStApiGUIEventBaseWndError のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_IStCallbackParamStApiGUIEventBaseWndError_Functions_t
	{
		/*!
			@copydoc PStApiGUI_IStCallbackParamStApiGUIEventBaseWndError_GetException_t()
		*/
		PStApiGUI_IStCallbackParamStApiGUIEventBaseWndError_GetException_t		GetException;
	}StApi_IStCallbackParamStApiGUIEventBaseWndError_Functions_t, *PStApi_IStCallbackParamStApiGUIEventBaseWndError_Functions_t;

	/*************************************************************************/
	/* StApi::IStCallbackParamStApiGUIEventDrawing */
	/*************************************************************************/
	/*!
		@~english	@brief	Get IStImage handle for the preview image.
		@~english	@details	Get IStImage handle for the preview image.
		@~english	@param[in] pIStCallbackParamBaseHandle	IStCallbackParamBase interface handle.
		@~english	@param[in,out] pIStImageHandle	IStImage pointer to the image.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	描画される画像用の IStImage インターフェースハンドルを取得します。
		@~japanese	@details	描画される画像用の IStImage インターフェースハンドルを取得します。
		@~japanese	@param[in]	pIStCallbackParamBaseHandle	IStCallbackParamBase インターフェースハンドル
		@~japanese	@param[in,out] pIStImageHandle	IStImage インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStCallbackParamStApiGUIEventDrawing_GetIStImage_t)(const PStApiHandle_t pIStCallbackParamBaseHandle, PStApiHandle_t pIStImageHandle);

	/*!
		@~english	@brief	Get ROI horizontal offset on the preview image.
		@~english	@details	Get ROI horizontal offset on the preview image.
		@~english	@param[in] pIStCallbackParamBaseHandle	IStCallbackParamBase interface handle.
		@~english	@param[in,out] pnValue	Offset value.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	描画の対象とする画像上のエリアの横方向のオフセット値を取得します。
		@~japanese	@details	描画の対象とする画像上のエリアの横方向のオフセット値を取得します。画像全体を描画の対象とする場合は、0が返されます。
		@~japanese	@param[in]	pIStCallbackParamBaseHandle	IStCallbackParamBase インターフェースハンドル
		@~japanese	@param[in,out] pnValue	横方向のオフセット値
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStCallbackParamStApiGUIEventDrawing_GetROIOffsetX_t)(const PStApiHandle_t pIStCallbackParamBaseHandle, size_t *pnValue);

	/*!
		@~english	@brief	Get ROI vertical offset on the preview image.
		@~english	@details	Get ROI vertical offset on the preview image.
		@~english	@param[in] pIStCallbackParamBaseHandle	IStCallbackParamBase interface handle.
		@~english	@param[in,out] pnValue	Offset value.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	描画の対象とする画像上のエリアの縦方向のオフセット値を取得します。
		@~japanese	@details	描画の対象とする画像上の位置の縦方向のオフセット値を取得します。画像全体を描画の対象とする場合は、0が返されます。
		@~japanese	@param[in]	pIStCallbackParamBaseHandle	IStCallbackParamBase インターフェースハンドル
		@~japanese	@param[in,out] pnValue	縦方向のオフセット値
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStCallbackParamStApiGUIEventDrawing_GetROIOffsetY_t)(const PStApiHandle_t pIStCallbackParamBaseHandle, size_t *pnValue);

	/*!
		@~english	@brief	Get ROI horizontal size on the preview image.
		@~english	@details	Get ROI horizontal size on the preview image.
		@~english	@param[in] pIStCallbackParamBaseHandle	IStCallbackParamBase interface handle.
		@~english	@param[in,out] pnValue	Width size value.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	描画の対象とする画像上のエリアの横サイズを取得します。
		@~japanese	@details	描画の対象とする画像上のエリアの横サイズを取得します。画像全体を描画の対象とする場合は、画像の横サイズが返されます。
		@~japanese	@param[in]	pIStCallbackParamBaseHandle	IStCallbackParamBase インターフェースハンドル
		@~japanese	@param[in,out] pnValue	横サイズ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStCallbackParamStApiGUIEventDrawing_GetROIWidth_t)(const PStApiHandle_t pIStCallbackParamBaseHandle, size_t *pnValue);

	/*!
		@~english	@brief	Get ROI vertical size on the preview image.
		@~english	@details	Get ROI vertical size on the preview image.
		@~english	@param[in] pIStCallbackParamBaseHandle	IStCallbackParamBase interface handle.
		@~english	@param[in,out] pnValue	Height size value.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	描画の対象とする画像上のエリアの縦サイズを取得します。
		@~japanese	@details	描画の対象とする画像上のエリアの縦サイズを取得します。画像全体を描画の対象とする場合は、画像の縦サイズが返されます。
		@~japanese	@param[in]	pIStCallbackParamBaseHandle	IStCallbackParamBase インターフェースハンドル
		@~japanese	@param[in,out] pnValue	縦サイズ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStCallbackParamStApiGUIEventDrawing_GetROIHeight_t)(const PStApiHandle_t pIStCallbackParamBaseHandle, size_t *pnValue);
		
	/*!
		@~english	@brief	Get horizontal size of the image displaying area.
		@~english	@details	Get horizontal size of the image displaying area.
		@~english	@param[in] pIStCallbackParamBaseHandle	IStCallbackParamBase interface handle.
		@~english	@param[in,out] pnValue	Width of displaying area.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	表示エリアの横方向のサイズを取得します。
		@~japanese	@details	表示エリアの横方向のサイズを取得します。
		@~japanese	@param[in]	pIStCallbackParamBaseHandle	IStCallbackParamBase インターフェースハンドル
		@~japanese	@param[in,out] pnValue	横サイズ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStCallbackParamStApiGUIEventDrawing_GetDisplayWidth_t)(const PStApiHandle_t pIStCallbackParamBaseHandle, size_t *pnValue);
		
	/*!
		@~english	@brief	Get vertical size of the image displaying area.
		@~english	@details	Get vertical size of the image displaying area.
		@~english	@param[in] pIStCallbackParamBaseHandle	IStCallbackParamBase interface handle.
		@~english	@param[in,out] pnValue	Height of displaying area.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	表示エリアの縦方向のサイズを取得します。
		@~japanese	@details	表示エリアの縦方向のサイズを取得します。
		@~japanese	@param[in]	pIStCallbackParamBaseHandle	IStCallbackParamBase インターフェースハンドル
		@~japanese	@param[in,out] pnValue	縦サイズ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStCallbackParamStApiGUIEventDrawing_GetDisplayHeight_t)(const PStApiHandle_t pIStCallbackParamBaseHandle, size_t *pnValue);
		
	/*!
		@~english	@brief	Get device context handle.
		@~english	@details	Get device context handle.
		@~english	@param[in] pIStCallbackParamBaseHandle	IStCallbackParamBase interface handle.
		@~english	@param[in,out] pnValue	Device context handle. In Mac/Linux (Qt-based), HDC (void*) is a QPainter*.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	文字や図形の描画に使用するデバイスコンテキストを取得します。
		@~japanese	@details	文字や図形の描画に使用するデバイスコンテキストを取得します。
		@~japanese	@param[in]	pIStCallbackParamBaseHandle	IStCallbackParamBase インターフェースハンドル
		@~japanese	@param[in,out] pnValue	デバイスコンテキスト。Mac/Linux Qtの場合はHDC (void*)はQPainter*です。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStCallbackParamStApiGUIEventDrawing_GetDC_t)(const PStApiHandle_t pIStCallbackParamBaseHandle, HDC *phDC);
	
	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStCallbackParamStApiGUIEventDrawing_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IStCallbackParamStApiGUIEventDrawing.
		@~english	@details	This structure holds the address of the C language wrapper function of IStCallbackParamStApiGUIEventDrawing.
		@~japanese	@brief	この構造体は IStCallbackParamStApiGUIEventDrawing のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IStCallbackParamStApiGUIEventDrawing のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_IStCallbackParamStApiGUIEventDrawing_Functions_t
	{
		/*!
			@copydoc PStApiGUI_IStCallbackParamStApiGUIEventDrawing_GetIStImage_t()
		*/
		PStApiGUI_IStCallbackParamStApiGUIEventDrawing_GetIStImage_t		GetIStImage;
				
		/*!
			@copydoc PStApiGUI_IStCallbackParamStApiGUIEventDrawing_GetROIOffsetX_t()
		*/
		PStApiGUI_IStCallbackParamStApiGUIEventDrawing_GetROIOffsetX_t		GetROIOffsetX;

		/*!
			@copydoc PStApiGUI_IStCallbackParamStApiGUIEventDrawing_GetROIOffsetY_t()
		*/
		PStApiGUI_IStCallbackParamStApiGUIEventDrawing_GetROIOffsetY_t		GetROIOffsetY;

		/*!
			@copydoc PStApiGUI_IStCallbackParamStApiGUIEventDrawing_GetROIWidth_t()
		*/
		PStApiGUI_IStCallbackParamStApiGUIEventDrawing_GetROIWidth_t		GetROIWidth;
	
		/*!
			@copydoc PStApiGUI_IStCallbackParamStApiGUIEventDrawing_GetROIHeight_t()
		*/
		PStApiGUI_IStCallbackParamStApiGUIEventDrawing_GetROIHeight_t		GetROIHeight;

		/*!
			@copydoc PStApiGUI_IStCallbackParamStApiGUIEventDrawing_GetDisplayWidth_t()
		*/
		PStApiGUI_IStCallbackParamStApiGUIEventDrawing_GetDisplayWidth_t		GetDisplayWidth;

		/*!
			@copydoc PStApiGUI_IStCallbackParamStApiGUIEventDrawing_GetDisplayHeight_t()
		*/
		PStApiGUI_IStCallbackParamStApiGUIEventDrawing_GetDisplayHeight_t		GetDisplayHeight;

		/*!
			@copydoc PStApiGUI_IStCallbackParamStApiGUIEventDrawing_GetDC_t()
		*/
		PStApiGUI_IStCallbackParamStApiGUIEventDrawing_GetDC_t		GetDC;
	}StApi_IStCallbackParamStApiGUIEventDrawing_Functions_t, *PStApi_IStCallbackParamStApiGUIEventDrawing_Functions_t;


	/*************************************************************************/
	/* StApi::IStSpecificTypeAllocator */
	/*************************************************************************/

	/*!
		@~english
		@brief	It is called when memory allocation is required.
		@details	It is called when memory allocation is required.
		@param[out]	ppBuffer	The pointer to the pointer of the allocated memory.
		@param[in]	eDataType	Type of the data.
		@param[in]	nSize	Count of the data.
		@param[out]	ppContext	The pointer to the pointer of the private data.
		@~japanese
		@brief	メモリーの割り当てが必要になったときに呼び出されます。
		@details	メモリーの割り当てが必要になったときに呼び出されます。
		@param[out]	ppBuffer	割り当てられたメモリーへのポインター
		@param[in] eDataType 割り当てるデータの型
		@param[in]	nCount	割り当てるデータの数
		@param[out]	ppContext	メモリーと関連付けするユーザー用ポインター
	*/
	typedef void (STAPI_CALLTYPE fSpecificTypeAllocateCallbackFunc_t)(void **  ppBuffer, EStNumberDataType_t eDataType, size_t nCount, void **  ppContext);

	/*!
		@~english
		@brief	It is called when memory needs to be released.
		@details	It is called when memory needs to be released.
		@param[in]	pBuffer	The pointer to the allocated memory.
		@param[in]	eDataType	Type of the data.
		@param[in]	nSize	Count of the data.
		@param[in]	pContext	The pointer to the private data.
		@~japanese
		@brief	メモリーの解放が必要になったときに呼び出されます。
		@details	メモリーの解放が必要になったときに呼び出されます。
		@param[in]	pBuffer	解放するメモリーへのポインター
		@param[in] eDataType 割り当てるデータの型
		@param[in]	nCount	割り当てるデータの数
		@param[in]	pContext	メモリーと関連付けされているユーザー用ポインター
	*/
	typedef void (STAPI_CALLTYPE fSpecificTypeDeallocateCallbackFunc_t)(void *  pBuffer, EStNumberDataType_t eDataType, size_t nCount, void *  pContext);

	/*!
		@~english
		@brief	Called when the allocator is no longer needed.
		@details	Called when the allocator is no longer needed.
		@~japanese
		@brief	割り当てられたメモリーが不要になった際に呼び出されます。
		@details	割り当てられたメモリーが不要になった際に呼び出されます。
	*/
	typedef void (STAPI_CALLTYPE fSpecificTypeOnDeregisterCallbackFunc_t)(void);

	/*!
		@~english	@brief	Create IStSpecificTypeAllocator object.
		@~english	@details	Create IStSpecificTypeAllocator object.
		@~english	@param[in] pFuncAllocate	Function to allocate memory.
		@~english	@param[in] pFuncDeallocate	Function to deallocate memory.
		@~english	@param[in] pFuncOnDeregister	Function called when the allocator was no longer needed.
		@~english	@param[in,out] pIStSpecificTypeAllocatorHandle	IStSpecificTypeAllocator interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStSpecificTypeAllocator を生成します。
		@~japanese	@details	IStSpecificTypeAllocator を生成します。
		@~english	@param[in] pFuncAllocate	メモリー割り当て時に使用される関数
		@~english	@param[in] pFuncDeallocate	メモリー解放時に使用される関数
		@~english	@param[in] pFuncOnDeregister	アロケーターが不要になった時に呼び出される関数
		@~japanese	@param[in,out] pIStSpecificTypeAllocatorHandle	IStSpecificTypeAllocator インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStSpecificTypeAllocator_CreateIStSpecificTypeAllocator_t)(fSpecificTypeAllocateCallbackFunc_t *pFuncAllocate, fSpecificTypeDeallocateCallbackFunc_t *pFuncDeallocate, fSpecificTypeOnDeregisterCallbackFunc_t *pFuncOnDeregister, PStApiHandle_t pIStSpecificTypeAllocatorHandle);

	/*!
		@~english	@brief	Release object.
		@~english	@details	Release object.
		@~english	@param[in] pIStSpecificTypeAllocatorHandle	IStSpecificTypeAllocator interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	解放します。
		@~japanese	@details	解放します。
		@~japanese	@param[in] pIStSpecificTypeAllocatorHandle	IStSpecificTypeAllocator インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStSpecificTypeAllocator_Release_t)(PStApiHandle_t pIStSpecificTypeAllocatorHandle);
	/*!
		@~english	@brief	Allocate memory with requested size.
		@~english	@details	Allocate memory with requested size.
		@~english	@param[in] pIStSpecificTypeAllocatorHandle	IStSpecificTypeAllocator interface handle.
		@~english	@param[out]	ppBuffer	The pointer to the pointer of the allocated memory.
		@~english	@param[in]	nSize	The size of memory to allocate.
		@~english	@param[out]	ppContext	The pointer to the pointer of the private data.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	指定されたサイズのメモリーを割り当てます。
		@~japanese	@details	指定されたサイズのメモリーを割り当てます。
		@~japanese	@param[in] pIStSpecificTypeAllocatorHandle	IStSpecificTypeAllocator インターフェースハンドル
		@~japanese	@param[out]	ppBuffer	割り当てられたメモリーへのポインター
		@~japanese	@param[in] eDataType 割り当てるデータの型
		@~japanese	@param[in]	nCount	割り当てるデータの数
		@~japanese	@param[out]	ppContext	メモリーと関連付けするユーザー用ポインター
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStSpecificTypeAllocator_Allocate_t)(const PStApiHandle_t pIStSpecificTypeAllocatorHandle, void **ppBuffer, EStNumberDataType_t eDataType, size_t nCount, void **ppContext);

	/*!
		@~english	@brief	Free the memory.
		@~english	@details	Free the memory.
		@~english	@param[in] pIStSpecificTypeAllocatorHandle	IStSpecificTypeAllocator interface handle.
		@~english	@param[in]	pBuffer	The pointer to the allocated memory.
		@~english	@param[in]	nSize	The size of the allocated memory.
		@~english	@param[in]	pContext	The pointer to the private data.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	メモリーを解放します。
		@~japanese	@details	メモリーを解放します。
		@~japanese	@param[in] pIStSpecificTypeAllocatorHandle	IStSpecificTypeAllocator インターフェースハンドル
		@~japanese	@param[in]	pBuffer	解放するメモリーへのポインター
		@~japanese	@param[in] eDataType 割り当てるデータの型
		@~japanese	@param[in]	nCount	割り当てるデータの数
		@~japanese	@param[in]	pContext	メモリーと関連付けされているユーザー用ポインター
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStSpecificTypeAllocator_Deallocate_t)(const PStApiHandle_t pIStSpecificTypeAllocatorHandle, void *pBuffer, EStNumberDataType_t eDataType, size_t nCount, void *pContext);

	/*!
		@~english	@brief	Called when the allocator is no longer needed.
		@~english	@details	Called when the allocator is no longer needed.
		@~english	@param[in] pIStSpecificTypeAllocatorHandle	IStSpecificTypeAllocator interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	割り当てられたメモリーが不要になった際に呼び出されます。
		@~japanese	@details	割り当てられたメモリーが不要になった際に呼び出されます。
		@~japanese	@param[in] pIStSpecificTypeAllocatorHandle	IStSpecificTypeAllocator インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiTL_IStSpecificTypeAllocator_OnDeregister_t)(const PStApiHandle_t pIStSpecificTypeAllocatorHandle);

	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStSpecificTypeAllocator_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IStSpecificTypeAllocator.
		@~english	@details	This structure holds the address of the C language wrapper function of IStSpecificTypeAllocator.
		@~japanese	@brief	この構造体は IStSpecificTypeAllocator のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IStSpecificTypeAllocator のC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_IStSpecificTypeAllocator_Functions_t
	{
		/*!
		@copydoc PStApiTL_IStSpecificTypeAllocator_CreateIStSpecificTypeAllocator_t()
		*/
		PStApiTL_IStSpecificTypeAllocator_CreateIStSpecificTypeAllocator_t	CreateIStSpecificTypeAllocator;

		/*!
		@copydoc PStApiTL_IStSpecificTypeAllocator_Release_t()
		*/
		PStApiTL_IStSpecificTypeAllocator_Release_t	Release;

		/*!
		@copydoc PStApiTL_IStSpecificTypeAllocator_Allocate_t()
		*/
		PStApiTL_IStSpecificTypeAllocator_Allocate_t	Allocate;

		/*!
		@copydoc PStApiTL_IStSpecificTypeAllocator_Deallocate_t()
		*/
		PStApiTL_IStSpecificTypeAllocator_Deallocate_t	Deallocate;

		/*!
		@copydoc PStApiTL_IStSpecificTypeAllocator_OnDeregister_t()
		*/
		PStApiTL_IStSpecificTypeAllocator_OnDeregister_t	OnDeregister;
	}StApi_IStSpecificTypeAllocator_Functions_t, *PStApi_IStSpecificTypeAllocator_Functions_t;


	/*************************************************************************/
	/* StApi::IStGraphData */
	/*************************************************************************/
	/*!
	@~english	@brief	Acquire the type of the graph data.
	@~english	@details	Acquire the type of the graph data.
	@~english	@param[in] pIStGraphDataHandle	IStGraphData interface handle.
	@~english	@param[out] peValue Type of the graph data.
	@~english	@return	EStApiCError_t error code.
	@~japanese	@brief	データのタイプを取得します。
	@~japanese	@details	データのタイプを取得します。
	@~japanese	@param[in] pIStGraphDataHandle	IStGraphData インターフェースハンドル
	@~japanese	@param[out] peValue データのタイプ
	@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStGraphData_GetGraphDataType_t)(const PStApiHandle_t pIStGraphDataHandle, EStGraphDataType_t *peValue);

	/*!
	@~english	@brief	Acquire the type of the data.
	@~english	@details	Acquire the type of the data.
	@~english	@param[in] pIStGraphDataHandle	IStGraphData interface handle.
	@~english	@param[out] peValue 	Type of the data.
	@~english	@return	EStApiCError_t error code.
	@~japanese	@brief	データの型を取得します。
	@~japanese	@details	データの型を取得します。
	@~japanese	@param[in] pIStGraphDataHandle	IStGraphData インターフェースハンドル
	@~japanese	@param[out] peValue 	データの型
	@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStGraphData_GetNumberDataType_t)(const PStApiHandle_t pIStGraphDataHandle, EStNumberDataType_t *peValue);

	/*!
	@~english	@brief	Acquire the count of the data.
	@~english	@details	Acquire the count of the data.
	@~english	@param[in] pIStGraphDataHandle	IStGraphData interface handle.
	@~english	@param[out] pnValue	Count of the data.
	@~english	@return	EStApiCError_t error code.
	@~japanese	@brief	データの数を取得します。
	@~japanese	@details	データの数を取得します。
	@~japanese	@param[in] pIStGraphDataHandle	IStGraphData インターフェースハンドル
	@~japanese	@param[out] pnValue	データの数
	@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStGraphData_GetDataCount_t)(const PStApiHandle_t pIStGraphDataHandle, size_t *pnValue);

	/*!
	@~english	@brief	Acquire the pointer of the data.
	@~english	@details	Acquire the pointer of the data.
	@~english	@param[in] pIStGraphDataHandle	IStGraphData interface handle.
	@~english	@param[out] ppBuffer	Pointer of the data.
	@~english	@return	EStApiCError_t error code.
	@~japanese	@brief	データへのポインターを取得します。
	@~japanese	@details	データへのポインターを取得します。
	@~japanese	@param[in] pIStGraphDataHandle	IStGraphData インターフェースハンドル
	@~japanese	@param[out] ppBuffer	データへのポインター
	@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStGraphData_GetDataPtr_t)(const PStApiHandle_t pIStGraphDataHandle, void **ppBuffer);


	/*!
	@~english	@brief	Get user context.
	@~english	@details	Get user context.
	@~english	@param[in] pIStGraphDataHandle	IStGraphData interface handle.
	@~english	@param[out] ppContext	Return user context pointer. If there is no user context data, return NULL.
	@~english	@return	EStApiCError_t error code.
	@~japanese	@brief	ユーザー用データポインターを取得します。
	@~japanese	@details	ユーザー用データポインターを取得します。
	@~japanese	@param[in] pIStGraphDataHandle	IStGraphData インターフェースハンドル
	@~japanese	@param[out] ppContext	ユーザー用データポインター。指定されていない場合は、NULLが返されます。
	@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStGraphData_GetUserContext_t)(const PStApiHandle_t pIStGraphDataHandle, void **ppContext);

	/*!
		@~english	@brief	Acquire the graph data information of type uint32_t.
		@~english	@details	Acquire the graph data information of type uint32_t.
		@~english	@param[in] pIStGraphDataHandle	IStGraphData interface handle.
		@~english	@param[in] eGDIU	Type of graph data info.
		@~english	@param[out] pnValue 	Graph data information.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	グラフデータ情報(uint32_t型)を取得します。
		@~japanese	@details	グラフデータ情報(uint32_t型)を取得します。
		@~japanese	@param[in] pIStGraphDataHandle	IStGraphData インターフェースハンドル
		@~japanese	@param[in] eGDIU	グラフデータ情報のタイプ。
		@~japanese	@param[out] pnValue グラフデータ情報
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStGraphData_GetGraphDataInfoUint32_t)(const PStApiHandle_t pIStGraphDataHandle, EStGraphDataInfoUint32_t  eGDIU, uint32_t *pnValue);

	/*!
		@~english	@brief	Acquire the graph data information of type double.
		@~english	@details	Acquire the graph data information of type double.
		@~english	@param[in] pIStGraphDataHandle	IStGraphData interface handle.
		@~english	@param[in] eGDIF	Type of graph data info.
		@~english	@param[out] pdblValue 	Graph data information.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	グラフデータ情報(double型)を取得します。
		@~japanese	@details	グラフデータ情報(double型)を取得します。
		@~japanese	@param[in] pIStGraphDataHandle	IStGraphData インターフェースハンドル
		@~japanese	@param[in] eGDIF	グラフデータ情報のタイプ。
		@~japanese	@param[out] pdblValue グラフデータ情報
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStGraphData_GetGraphDataInfoFloat64_t)(const PStApiHandle_t pIStGraphDataHandle, EStGraphDataInfoFloat64_t  eGDIF, double *pdblValue);





	/*!
	@ingroup StApiC_PublicImpl
	@interface StApi_IStGraphData_Functions_t
	@~english	@brief	This structure holds the address of the C language wrapper function of IStGraphData.
	@~english	@details	This structure holds the address of the C language wrapper function of IStGraphData.
	@~japanese	@brief	この構造体は IStGraphData のC言語用ラッパー関数のアドレスを保持します。
	@~japanese	@details	この構造体は IStGraphData のC言語用ラッパー関数のアドレスを保持します。
	@since StApi v1.1.1
	*/
	typedef struct _StApi_IStGraphData_Functions_t
	{
		/*!
		@copydoc PStApiIP_IStGraphData_GetGraphDataType_t()
		*/
		PStApiIP_IStGraphData_GetGraphDataType_t	GetGraphDataType;

		/*!
		@copydoc PStApiIP_IStGraphData_GetNumberDataType_t()
		*/
		PStApiIP_IStGraphData_GetNumberDataType_t	GetNumberDataType;

		/*!
		@copydoc PStApiIP_IStGraphData_GetDataCount_t()
		*/
		PStApiIP_IStGraphData_GetDataCount_t	GetDataCount;

		/*!
		@copydoc PStApiIP_IStGraphData_GetDataPtr_t()
		*/
		PStApiIP_IStGraphData_GetDataPtr_t	GetDataPtr;

		/*!
		@copydoc PStApiIP_IStGraphData_GetUserContext_t()
		*/
		PStApiIP_IStGraphData_GetUserContext_t	GetUserContext;

		/*!
		@copydoc PStApiIP_IStGraphData_GetGraphDataInfoUint32_t()
		*/
		PStApiIP_IStGraphData_GetGraphDataInfoUint32_t	GetGraphDataInfoUint32;

		/*!
		@copydoc PStApiIP_IStGraphData_GetGraphDataInfoFloat64_t()
		*/
		PStApiIP_IStGraphData_GetGraphDataInfoFloat64_t	GetGraphDataInfoFloat64;
	}StApi_IStGraphData_Functions_t, *PStApi_IStGraphData_Functions_t;

	/*************************************************************************/
	/* StApi::IStGraphDataBuffer */
	/*************************************************************************/
	/*!
		@~english	@brief	Get IStGraphDataBuffer handle.
		@~english	@details	Get IStGraphDataBuffer handle.
		@~english	@param[in] pSourceHandle	Interface handle that is enable to convert to IStGraphDataBuffer interface handle.
		@~english	@param[in,out] pIStGraphDataBufferHandle	IStGraphDataBuffer interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStGraphDataBufferハンドルを取得します。
		@~japanese	@details	IStGraphDataBufferハンドルを取得します。
		@~japanese	@param[in] pSourceHandle	IStGraphDataBuffer インターフェースハンドルに変換可能なインターフェースハンドル
		@~japanese	@param[in,out] pIStGraphDataBufferHandle	IStGraphDataBuffer インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStGraphDataBuffer_GetIStGraphDataBuffer_t)(const PStApiHandle_t pSourceHandle, PStApiHandle_t pIStGraphDataBufferHandle);

	/*!
		@~english	@brief	Acquire IStGraphData interface pointer.
		@~english	@details	Acquire IStGraphData interface pointer.
		@~english	@param[in] pIStGraphDataBufferHandle	IStGraphDataBuffer interface handle.
		@~english	@param[out] pIStGraphDataHandle	IStGraphData interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStGraphData インターフェースポインターを取得します。
		@~japanese	@details	IStGraphData インターフェースポインターを取得します。
		@~japanese	@param[in] pIStGraphDataBufferHandle	IStGraphDataBuffer インターフェースハンドル
		@~japanese	@param[out] pIStGraphDataHandle	IStGraphData インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStGraphDataBuffer_GetIStGraphData_t)(const PStApiHandle_t pIStGraphDataBufferHandle, PStApiHandle_t pIStGraphDataHandle);

	/*!
		@~english	@brief	Acquire the size of the buffer.
		@~english	@details	Acquire the size of the buffer.
		@~english	@param[in] pIStGraphDataBufferHandle	IStGraphDataBuffer interface handle.
		@~english	@param[out] pnValue	Size of the buffer.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	バッファーサイズを取得します。
		@~japanese	@details	バッファーサイズを取得します。
		@~japanese	@param[in] pIStGraphDataBufferHandle	IStGraphDataBuffer インターフェースハンドル
		@~japanese	@param[out] pnValue	バッファーサイズ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStGraphDataBuffer_GetBufferSize_t)(const PStApiHandle_t pIStGraphDataBufferHandle, size_t *pnValue);

	/*!
		@~english	@brief	Acquire the pointer of the buffer.
		@~english	@details	Acquire the pointer of the buffer.
		@~english	@param[in] pIStGraphDataBufferHandle	IStGraphDataBuffer interface handle.
		@~english	@param[out] pBuffer	Pointer of the buffer.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	バッファへのポインターを取得します。
		@~japanese	@details	バッファへのポインターを取得します。
		@~japanese	@param[in] pIStGraphDataBufferHandle	IStGraphDataBuffer インターフェースハンドル
		@~japanese	@param[out] pBuffer	バッファへのポインター
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStGraphDataBuffer_GetBufferPtr_t)(const PStApiHandle_t pIStGraphDataBufferHandle, void **pBuffer);


	/*!
		@ingroup StApiIP_PublicInterface
		@interface IStGraphDataBuffer
		@~english	@brief	Interface for Graph Data Buffer object.
		@~english	@details	Interface for Graph Data Buffer object.
		@~japanese	@brief	グラフデータバッファ用インターフェース
		@~japanese	@details	グラフデータバッファ用インターフェース
		@since StApi v1.1.1
	*/
	typedef struct _StApi_IStGraphDataBuffer_Functions_t
	{
		/*!
			@copydoc PStApiIP_IStGraphDataBuffer_GetIStGraphDataBuffer_t()
		*/
		PStApiIP_IStGraphDataBuffer_GetIStGraphDataBuffer_t	GetIStGraphDataBuffer;

		/*!
		@copydoc PStApiIP_IStGraphDataBuffer_GetIStGraphData_t()
		*/
		PStApiIP_IStGraphDataBuffer_GetIStGraphData_t	GetIStGraphData;

		/*!
		@copydoc PStApiIP_IStGraphDataBuffer_GetBufferSize_t()
		*/
		PStApiIP_IStGraphDataBuffer_GetBufferSize_t	GetBufferSize;

		/*!
		@copydoc PStApiIP_IStGraphDataBuffer_GetBufferPtr_t()
		*/
		PStApiIP_IStGraphDataBuffer_GetBufferPtr_t	GetBufferPtr;
	}StApi_IStGraphDataBuffer_Functions_t, *PStApi_IStGraphDataBuffer_Functions_t;


	/*************************************************************************/
	/* StApi::IStGraphDataBufferResizable */
	/*************************************************************************/
	/*!
		@~english	@brief	Acquire IStGraphDataBufferResizable interface handle.
		@~english	@details	Acquire IStGraphDataBufferResizable interface handle.
		@~english	@param[in] pIStSpecificTypeAllocatorHandle	IStSpecificTypeAllocator interface handle for allocating and releasing memory. If NULL, the buffer memory allocation and deallocation are handled inside the StApi.
		@~english	@param[in,out] pIStGraphDataBufferResizableHandle	IStFilter interface handle.
		@~english	@attention	If the acquired interface handle of IStGraphDataBufferResizable does not needed anymore, call IStGraphDataBufferResizable->Release(pIStGraphDataBufferResizableHandle) to release it. 
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	pIStConverterHandle IStGraphDataBufferResizable インターフェースハンドルを取得します。
		@~japanese	@details	IStGraphDataBufferResizable インターフェースハンドルを取得します。
		@~japanese	@param[in] pIStSpecificTypeAllocatorHandle	IStSpecificTypeAllocator インターフェースハンドル。画像保持用メモリーの確保および解放をカスタマイズする際に指定します。NULLが指定された場合は、StApi内部でメモリーの割り当ておよび解放を行います。
		@~japanese	@param[in,out] pIStGraphDataBufferResizableHandle	IStGraphDataBufferResizable インターフェースハンドル
		@~japanese	@attention	 IStGraphDataBufferResizable インターフェースハンドル が不要になったら、 IStGraphDataBufferResizable->Release(pIStGraphDataBufferResizableHandle) を呼び出して解放してください。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	//STAPI_PCALL(PStApiIP_IStGraphDataBufferResizable_CreateIStGraphDataBufferResizable_t)(const PStApiHandle_t pIStSpecificTypeAllocatorHandle, PStApiHandle_t pIStGraphDataBufferResizableHandle);
	

	/*!
		@~english	@brief	Release object.
		@~english	@details	Release object.
		@~english	@param[in] pIStGraphDataBufferResizableHandle	IStGraphDataBufferResizable interface handle.
		@~english	@param[in] pIStFilterHandle	IStFilter interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	解放します。
		@~japanese	@details	解放します。
		@~japanese	@param[in] pIStGraphDataBufferResizableHandle	IStGraphDataBufferResizable インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	//STAPI_PCALL(PStApiIP_IStGraphDataBufferResizable_Release_t)(PStApiHandle_t pIStGraphDataBufferResizableHandle);

	/*!
		@~english	@brief	Copy Graph Data.
		@~english	@details	Copy Graph Data.
		@~english	@param[in] pIStGraphDataBufferResizableHandle	IStGraphDataBufferResizable interface handle.
		@~english	@param[in] pIStGraphData	Source of the IStGraphDataBuffer interface pointer to be copied.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	グラフデータをコピーします。
		@~japanese	@details	グラフデータをコピーします。
		@~japanese	@param[in] pIStGraphDataBufferResizableHandle	IStGraphDataBufferResizable インターフェースハンドル
		@~japanese	@param[in] pIStGraphData	コピーしたいグラフデータデータの IStGraphDataBuffer インターフェースポインター
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStGraphDataBufferResizable_CopyGraphData_t)(const PStApiHandle_t pDestIStGraphDataBufferResizableHandle, const PStApiHandle_t pSrcIStGraphDataBufferHandle);

	/*!
		@~english	@brief	Resize Graph Data Buffer.
		@~english	@details	Resize Graph Data Buffer.
		@~english	@param[in] pIStGraphDataBufferResizableHandle	IStGraphDataBufferResizable interface handle.
		@~english	@param[in] eDataType Type of the data.
		@~english	@param[in] nDataCount	Count of the data.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	グラフデータバッファをリサイズします。
		@~japanese	@details	グラフデータバッファをリサイズします。
		@~japanese	@param[in] pIStGraphDataBufferResizableHandle	IStGraphDataBufferResizable インターフェースハンドル
		@~japanese	@param[in] eDataType データの型
		@~japanese	@param[in] nDataCount	グラフデータの数
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStGraphDataBufferResizable_Resize_t)(const PStApiHandle_t pIStGraphDataBufferResizableHandle, EStNumberDataType_t eDataType, size_t nDataCount);
	

	/*!
		@~english	@brief	Set the graph data information of type uint32_t.
		@~english	@details	Set the graph data information of type uint32_t.
		@~english	@param[in] pIStGraphDataBufferResizableHandle	IStGraphDataBufferResizable interface handle.
		@~english	@param[in] eGDIU	Type of graph data info.
		@~english	@param[in] nValue 	Graph data information.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	グラフデータ情報(uint32_t型)を設定します。
		@~japanese	@details	グラフデータ情報(uint32_t型)を設定します。
		@~japanese	@param[in] pIStGraphDataBufferResizableHandle	IStGraphDataBufferResizable インターフェースハンドル
		@~japanese	@param[in] eGDIU	グラフデータ情報のタイプ。
		@~japanese	@param[in] nValue グラフデータ情報
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStGraphDataBufferResizable_SetGraphDataInfoUint32_t)(const PStApiHandle_t pIStGraphDataBufferResizableHandle, EStGraphDataInfoUint32_t  eGDIU, uint32_t nValue);

	/*!
		@~english	@brief	Set the graph data information of type double.
		@~english	@details	Set the graph data information of type double.
		@~english	@param[in] eGDIF	Type of graph data info.
		@~english	@param[in] pIStGraphDataBufferResizableHandle	IStGraphDataBufferResizable interface handle.
		@~english	@param[in] dblValue 	Graph data information.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	グラフデータ情報(double型)を設定します。
		@~japanese	@details	グラフデータ情報(double型)を設定します。
		@~japanese	@param[in] pIStGraphDataBufferResizableHandle	IStGraphDataBufferResizable インターフェースハンドル
		@~japanese	@param[in] eGDIF	グラフデータ情報のタイプ。
		@~japanese	@param[in] dblValue グラフデータ情報
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStGraphDataBufferResizable_SetGraphDataInfoFloat64_t)(const PStApiHandle_t pIStGraphDataBufferResizableHandle, EStGraphDataInfoFloat64_t  eGDIF, double dblValue);


	/*!
		@ingroup StApiIP_PublicInterface
		@interface IStGraphDataBuffer
		@~english	@brief	Interface for Graph Data Buffer object.
		@~english	@details	Interface for Graph Data Buffer object.
		@~japanese	@brief	グラフデータバッファ用インターフェース
		@~japanese	@details	グラフデータバッファ用インターフェース
		@since StApi v1.1.1
	*/
	typedef struct _StApi_IStGraphDataBufferResizable_Functions_t
	{
		/*!
			@copydoc PStApiIP_IStGraphDataBufferResizable_CreateIStGraphDataBufferResizable_t()
		*/
		//PStApiIP_IStGraphDataBufferResizable_CreateIStGraphDataBufferResizable_t	CreateIStGraphDataBufferResizable;

		/*!
			@copydoc PStApiIP_IStGraphDataBufferResizable_Release_t()
		*/
		//PStApiIP_IStGraphDataBufferResizable_Release_t	Release;

		/*!
			@copydoc PStApiIP_IStGraphDataBufferResizable_CopyGraphData_t()
		*/
		PStApiIP_IStGraphDataBufferResizable_CopyGraphData_t	CopyGraphData;

		/*!
			@copydoc PStApiIP_IStGraphDataBufferResizable_Resize_t()
		*/
		PStApiIP_IStGraphDataBufferResizable_Resize_t	Resize;

		/*!
			@copydoc PStApiIP_IStGraphDataBufferResizable_SetGraphDataInfoUint32_t()
		*/
		PStApiIP_IStGraphDataBufferResizable_SetGraphDataInfoUint32_t	SetGraphDataInfoUint32;

		/*!
			@copydoc PStApiIP_IStGraphDataBufferResizable_SetGraphDataInfoFloat64_t()
		*/
		PStApiIP_IStGraphDataBufferResizable_SetGraphDataInfoFloat64_t	SetGraphDataInfoFloat64;
	}StApi_IStGraphDataBufferResizable_Functions_t, *PStApi_IStGraphDataBufferResizable_Functions_t;



	/*************************************************************************/
	/* StApi::IStGraphDataBufferList */
	/*************************************************************************/
	
	/*!
		@~english	@brief	Get IStGraphDataBufferList handle.
		@~english	@details	Get IStGraphDataBufferList handle.
		@~english	@param[in] pSourceHandle	Interface handle that is enable to convert to IStGraphDataBufferList interface handle.
		@~english	@param[in,out] pIStGraphDataBufferListHandle	IStGraphDataBufferList interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStGraphDataBufferListハンドルを取得します。
		@~japanese	@details	IStGraphDataBufferListハンドルを取得します。
		@~japanese	@param[in] pSourceHandle	IStGraphDataBufferList インターフェースハンドルに変換可能なインターフェースハンドル
		@~japanese	@param[in,out] pIStGraphDataBufferListHandle	IStGraphDataBufferList インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStGraphDataBufferList_GetIStGraphDataBufferList_t)(const PStApiHandle_t pSourceHandle, PStApiHandle_t pIStGraphDataBufferListHandle);

	/*!
		@~english	@brief	Acquire count of the Graph Data.
		@~english	@details	Acquire count of the Graph Data.
		@~english	@param[in] pIStGraphDataBufferListHandle	IStGraphDataBufferList interface handle.
		@~english	@param[out] pnValue	Count of the Graph Data.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	グラフデータの数を取得します。
		@~japanese	@details	グラフデータの数を取得します。
		@~japanese	@param[in] pIStGraphDataBufferListHandle	IStGraphDataBufferList インターフェースハンドル
		@~japanese	@param[out] pnValue	グラフデータの数
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStGraphDataBufferList_GetGraphDataBufferCount_t)(const PStApiHandle_t pIStGraphDataBufferListHandle, size_t *pnValue);


	/*!
		@~english	@brief	Acquire IStGraphDataBuffer interface pointer.
		@~english	@details	Acquire IStGraphDataBuffer interface pointer.
		@~english	@param[in] pIStGraphDataBufferListHandle	IStGraphDataBufferList interface handle.
		@~english	@param[in] nIndex	Index of the component.
		@~english	@param[out] pIStGraphDataBufferHandle	IStGraphDataBuffer interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStGraphDataBuffer インターフェースポインターを取得します。
		@~japanese	@details	IStGraphDataBuffer インターフェースポインターを取得します。
		@~japanese	@param[in] pIStGraphDataBufferListHandle	IStGraphDataBufferList インターフェースハンドル
		@~japanese	@param[in] nIndex	取得するグラフデータを指定するインディックス値
		@~japanese	@param[out] pIStGraphDataBufferHandle	IStGraphDataBuffer インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStGraphDataBufferList_GetIStGraphDataBuffer_t)(const PStApiHandle_t pIStGraphDataBufferListHandle, size_t nIndex, PStApiHandle_t pIStGraphDataBufferHandle);
		
	/*!
		@~english	@brief	Check if the current graph data can be saved as the graph data file format.
		@~english	@details	Check if the current graph data can be saved as the graph data file format.
		@~english	@param[in] pIStGraphDataBufferListHandle	IStGraphDataBufferList interface handle.
		@~english	@param[in]	eSGDF	Graph data file format.
		@~english	@param[out] pbValue	True if save is supported.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	指定したフォーマットが現在のグラフデータの保存に対応しているかを確認します。
		@~japanese	@details	指定したフォーマットが現在のグラフデータの保存に対応しているかを確認します。
		@~japanese	@param[in] pIStGraphDataBufferListHandle	IStGraphDataBufferList インターフェースハンドル
		@~japanese	@param[in]	eSGDF	グラフデータファイルフォーマット
		@~japanese	@param[out] pbValue	対応している場合、 true が返されます。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStGraphDataBufferList_IsSaveSupported_t)(const PStApiHandle_t pIStGraphDataBufferListHandle, EStGraphDataFileFormat_t eSGDF, bool8_t *pbValue);

	/*!
		@~english	@brief	Save graph data to file.
		@~english	@details	Save graph data to file.
		@~english	@param[in] pIStGraphDataBufferListHandle	IStGraphDataBufferList interface handle.
		@~english	@param[in]	eSGDF	Graph data file format.
		@~english	@param[in]	szFileName	File name.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	グラフデータをファイルへ保存します。
		@~japanese	@details	グラフデータをファイルへ保存します。
		@~japanese	@param[in] pIStGraphDataBufferListHandle	IStGraphDataBufferList インターフェースハンドル
		@~japanese	@param[in]	eSGDF	グラフデータファイルフォーマット
		@~japanese	@param[in]	szFileName	ファイル名
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStGraphDataBufferList_SaveW_t)(const PStApiHandle_t pIStGraphDataBufferListHandle, EStGraphDataFileFormat_t eSGDF, const wchar_t *szFileName);

	/*!
		@~english	@brief	Save graph data to file.
		@~english	@details	Save graph data to file.
		@~english	@param[in] pIStGraphDataBufferListHandle	IStGraphDataBufferList interface handle.
		@~english	@param[in]	eSGDF	Graph data file format.
		@~english	@param[in]	szFileName	File name.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	グラフデータをファイルへ保存します。
		@~japanese	@details	グラフデータをファイルへ保存します。
		@~japanese	@param[in] pIStGraphDataBufferListHandle	IStGraphDataBufferList インターフェースハンドル
		@~japanese	@param[in]	eSGDF	グラフデータファイルフォーマット
		@~japanese	@param[in]	szFileName	ファイル名
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStGraphDataBufferList_SaveA_t)(const PStApiHandle_t pIStGraphDataBufferListHandle, EStGraphDataFileFormat_t eSGDF, const char *szFileName);


	/*!
		@ingroup StApiIP_PublicInterface
		@interface IStGraphDataBufferList
		@~english	@brief	Interface for Graph Data Buffer List object.
		@~english	@details	Interface for Graph Data Buffer List object.
		@~japanese	@brief	グラフデータバッファリスト用インターフェース
		@~japanese	@details	グラフデータバッファリスト用インターフェース
		@since StApi v1.1.1
	*/
	typedef struct _StApi_IStGraphDataBufferList_Functions_t
	{
		/*!
			@copydoc PStApiIP_IStGraphDataBufferList_GetIStGraphDataBufferList_t()
		*/
		PStApiIP_IStGraphDataBufferList_GetIStGraphDataBufferList_t	GetIStGraphDataBufferList;

		/*!
			@copydoc PStApiIP_IStGraphDataBufferList_GetGraphDataBufferCount_t()
		*/
		PStApiIP_IStGraphDataBufferList_GetGraphDataBufferCount_t	GetGraphDataBufferCount;

		/*!
			@copydoc PStApiIP_IStGraphDataBufferList_GetIStGraphDataBuffer_t()
		*/
		PStApiIP_IStGraphDataBufferList_GetIStGraphDataBuffer_t	GetIStGraphDataBuffer;

		/*!
			@copydoc PStApiIP_IStGraphDataBufferList_IsSaveSupported_t()
		*/
		PStApiIP_IStGraphDataBufferList_IsSaveSupported_t	IsSaveSupported;

		/*!
			@copydoc PStApiIP_IStGraphDataBufferList_SaveW_t()
		*/
		PStApiIP_IStGraphDataBufferList_SaveW_t	SaveW;

		/*!
			@copydoc PStApiIP_IStGraphDataBufferList_SaveA_t()
		*/
		PStApiIP_IStGraphDataBufferList_SaveA_t	SaveA;
	}StApi_IStGraphDataBufferList_Functions_t, *PStApi_IStGraphDataBufferList_Functions_t;


	/*************************************************************************/
	/* StApi::IStGraphDataBufferListResizable */
	/*************************************************************************/

	/*!
		@ingroup	StApiIP_PublicImpl
		@~english	@brief	Create object for keeping graph data buffer list and acquire IStGraphDataBufferListResizable interface handle.
		@~english	@details	Create object for keeping graph data buffer list and acquire IStGraphDataBufferListResizable interface handle. Call Release() to release IStGraphDataBufferListResizableReleasable interface handle if it is no longer necessary.
		@~english	@param[in] pIStSpecificTypeAllocatorHandle	IStSpecificTypeAllocator interface handle for allocating and releasing memory. If NULL, the buffer memory allocation and deallocation are handled inside the StApi.
		@~english	@param[in, out] pIStGraphDataBufferListResizableHandle	IStGraphDataBufferListResizable interface handle.
		@~english	@return	EStApiCError_t error code.
		@~english	@sa	 StApi_IStSpecificTypeAllocator_Functions_t
		@~japanese	@brief	グラフデータバッファリストを保持するためのオブジェクトを生成し、 IStGraphDataBufferListResizable インターフェースハンドルを取得します。
		@~japanese	@details	グラフデータバッファリストを保持するためのオブジェクトを生成し、 IStGraphDataBufferListResizable インターフェースハンドルを取得します。オブジェクトが不要になったら Release() を呼び出して解放してください。
		@~japanese	@param[in] pIStSpecificTypeAllocatorHandle	IStSpecificTypeAllocator インターフェースハンドル。画像保持用メモリーの確保および解放をカスタマイズする際に指定します。NULLが指定された場合は、StApi内部でメモリーの割り当ておよび解放を行います。
		@~japanese	@param[in, out] pIStGraphDataBufferListResizableHandle	IStGraphDataBufferListResizable インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
		@~japanese	@sa	 StApi_IStSpecificTypeAllocator_Functions_t
	*/
	STAPI_PCALL(PStApiIP_IStGraphDataBufferListResizable_CreateIStGraphDataBufferListResizable_t)(PStApiHandle_t pIStSpecificTypeAllocatorHandle, PStApiHandle_t pIStGraphDataBufferListResizableHandle);
	
	/*!
		@~english	@brief	Release object.
		@~english	@details	Release object.
		@~english	@param[in] pIStGraphDataBufferListResizableHandle	IStGraphDataBufferListResizable interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	解放します。
		@~japanese	@details	解放します。
		@~japanese	@param[in] pIStGraphDataBufferListResizableHandle	IStGraphDataBufferListResizable インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStGraphDataBufferListResizable_Release_t)(PStApiHandle_t pIStGraphDataBufferListResizableHandle);

	/*!
		@~english	@brief	Check if the current graph data can be loaded as the graph data file format.
		@~english	@details	Check if the current graph data can be loaded as the graph data file format.
		@~english	@attention	Currently this only supports StGraphDataFileFormat_StApiRaw.
		@~english	@param[in] pIStGraphDataBufferListHandle	IStGraphDataBufferList interface handle.
		@~english	@param[in]	eSGDF	Graph data file format.
		@~english	@param[out] pbValue	True if load is supported.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	指定したフォーマットの読み込みに対応しているかを確認します。
		@~japanese	@details	指定したフォーマットの読み込みに対応しているかを確認します。
		@~japanese	@attention	現在、読み込みに対応しているのは StGraphDataFileFormat_StApiRaw フォーマットのみとなります。
		@~japanese	@param[in] pIStGraphDataBufferListResizableHandle	IStGraphDataBufferList インターフェースハンドル
		@~japanese	@param[in]	eSGDF	静止画ファイルフォーマット
		@~japanese	@param[out] pbValue	対応している場合、 true が返されます。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStGraphDataBufferListResizable_IsLoadSupported_t)(const PStApiHandle_t pIStGraphDataBufferListResizableHandle, EStGraphDataFileFormat_t eSGDF, bool8_t *pbValue);

	/*!
		@~english	@brief	Read graph data from file.
		@~english	@details	Read graph data from file.
		@~english	@attention	Currently this only supports StGraphDataFileFormat_StApiRaw.
		@~english	@param[in] pIStGraphDataBufferListHandle	IStGraphDataBufferList interface handle.
		@~english	@param[in]	szFileName	File name.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	グラフデータファイルをバッファへ読み込みます。
		@~japanese	@details	グラフデータファイルをバッファへ読み込みます。
		@~japanese	@attention	現在、読み込みに対応しているのは StGraphDataFileFormat_StApiRaw フォーマットのみとなります。
		@~japanese	@param[in] pIStGraphDataBufferListResizableHandle	IStGraphDataBufferList インターフェースハンドル
		@~japanese	@param[in]	szFileName	ファイル名
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStGraphDataBufferListResizable_LoadW_t)(const PStApiHandle_t pIStGraphDataBufferListResizableHandle, const wchar_t *szFileName);

	/*!
		@~english	@brief	Read graph data from file.
		@~english	@details	Read graph data from file.
		@~english	@attention	Currently this only supports StGraphDataFileFormat_StApiRaw.
		@~english	@param[in] pIStGraphDataBufferListHandle	IStGraphDataBufferList interface handle.
		@~english	@param[in]	szFileName	File name.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	グラフデータファイルをバッファへ読み込みます。
		@~japanese	@details	グラフデータファイルをバッファへ読み込みます。
		@~japanese	@attention	現在、読み込みに対応しているのは StGraphDataFileFormat_StApiRaw フォーマットのみとなります。
		@~japanese	@param[in] pIStGraphDataBufferListResizableHandle	IStGraphDataBufferList インターフェースハンドル
		@~japanese	@param[in]	szFileName	ファイル名
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStGraphDataBufferListResizable_LoadA_t)(const PStApiHandle_t pIStGraphDataBufferListResizableHandle, const char *szFileName);

	/*!
		@~english	@brief	Create an Graph Data buffer based on the given parameters.
		@~english	@details      Create an Graph Data buffer based on the given parameters.
		@~english	@attention Buffers generated here are deleted automatically when you create the buffers again or when you release the Graph Data Buffer object.
		@~english	@param[in] pIStGraphDataBufferListHandle	IStGraphDataBufferList interface handle.
		@~english	@param[in] nComponentCount	Count of the components.
		@~english	@param[in] eValue	Type of the data.
		@~english	@param[in] nDataCount	Count of the data.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	指定されたパラメータに従ってバッファを作成します。
		@~japanese	@details	指定されたパラメータに従ってバッファを作成します。
		@~japanese	@attention ここで生成されたバッファは、再度バッファを作成した際や IStGraphDataBufferList インターフェースハンドルのRelease時に自動的に削除されます。
		@~japanese	@param[in] pIStGraphDataBufferListResizableHandle	IStGraphDataBufferList インターフェースハンドル
		@~japanese	@param[in] nComponentCount	構成要素の数
		@~japanese	@param[in] eValue	データのタイプ
		@~japanese	@param[in] nDataCount	データ数
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStGraphDataBufferListResizable_CreateBufferList_t)(const PStApiHandle_t pIStGraphDataBufferListResizableHandle, size_t nComponentCount);

	/*!
		@~english	@brief	Copy Graph Data.
		@~english	@details	Copy Graph Data.
		@~english	@param[in] pIStGraphDataBufferListHandle	IStGraphDataBufferList interface handle.
		@~english	@param[in] pIStGraphDataBufferListHandle	Source of the IStGraphDataBufferList interface pointer to be copied.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	グラフデータをコピーします。
		@~japanese	@details	グラフデータをコピーします。
		@~japanese	@param[in] pIStGraphDataBufferListResizableHandle	IStGraphDataBufferList インターフェースハンドル
		@~japanese	@param[in] pIStGraphDataBufferListHandle	コピーしたいグラフデータデータの IStGraphDataBufferList インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStGraphDataBufferListResizable_CopyGraphDataBufferList_t)(const PStApiHandle_t pIStGraphDataBufferListResizableHandle, const PStApiHandle_t pIStGraphDataBufferListHandle);



	/*!
		@~english	@brief	Acquire IStGraphDataBufferResizable interface handle.
		@~english	@details	Acquire IStGraphDataBufferResizable interface handle.
		@~english	@param[in] pIStGraphDataBufferListHandle	IStGraphDataBufferList interface handle.
		@~english	@param[in] nIndex	Index of the component.
		@~english	@param[in,out] pIStGraphDataBufferResizableHandle	IStGraphDataBufferResizable interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStGraphDataBufferResizable インターフェースハンドルを取得します。
		@~japanese	@details	IStGraphDataBufferResizable インターフェースハンドルを取得します。
		@~japanese	@param[in] pIStGraphDataBufferListResizableHandle	IStGraphDataBufferList インターフェースハンドル
		@~japanese	@param[in] nIndex	取得するグラフデータを指定するインディックス値
		@~japanese	@param[in,out] pIStGraphDataBufferResizableHandle	IStGraphDataBufferResizable インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStGraphDataBufferListResizable_GetIStGraphDataBufferResizable_t)(const PStApiHandle_t pIStGraphDataBufferListResizableHandle, size_t nIndex, PStApiHandle_t pIStGraphDataBufferResizableHandle);


	/*!
		@ingroup StApiIP_PublicInterface
		@interface IStGraphDataBufferListResizable
		@~english	@brief	Interface for Graph Data List object.
		@~english	@details	Interface for Graph Data List object.
		@~japanese	@brief	グラフデータリスト用インターフェース
		@~japanese	@details	グラフデータリスト用インターフェース
		@since StApi v1.1.1
	*/
	typedef struct _StApi_IStGraphDataBufferListResizable_Functions_t
	{
		/*!
			@copydoc PStApiIP_IStGraphDataBufferListResizable_CreateIStGraphDataBufferListResizable_t()
		*/
		PStApiIP_IStGraphDataBufferListResizable_CreateIStGraphDataBufferListResizable_t	CreateIStGraphDataBufferListResizable;

		/*!
			@copydoc PStApiIP_IStGraphDataBufferListResizable_Release_t()
		*/
		PStApiIP_IStGraphDataBufferListResizable_Release_t	Release;

		/*!
			@copydoc PStApiIP_IStGraphDataBufferListResizable_IsLoadSupported_t()
		*/
		PStApiIP_IStGraphDataBufferListResizable_IsLoadSupported_t	IsLoadSupported;

		/*!
			@copydoc PStApiIP_IStGraphDataBufferListResizable_LoadW_t()
		*/
		PStApiIP_IStGraphDataBufferListResizable_LoadW_t	LoadW;

		/*!
			@copydoc PStApiIP_IStGraphDataBufferListResizable_LoadA_t()
		*/
		PStApiIP_IStGraphDataBufferListResizable_LoadA_t	LoadA;

		/*!
			@copydoc PStApiIP_IStGraphDataBufferListResizable_CreateBufferList_t()
		*/
		PStApiIP_IStGraphDataBufferListResizable_CreateBufferList_t	CreateBufferList;

		/*!
			@copydoc PStApiIP_IStGraphDataBufferListResizable_CopyGraphDataBufferList_t()
		*/
		PStApiIP_IStGraphDataBufferListResizable_CopyGraphDataBufferList_t	CopyGraphDataBufferList;

		/*!
			@copydoc PStApiIP_IStGraphDataBufferListResizable_GetIStGraphDataBufferResizable_t()
		*/
		PStApiIP_IStGraphDataBufferListResizable_GetIStGraphDataBufferResizable_t	GetIStGraphDataBufferResizable;
	}StApi_IStGraphDataBufferListResizable_Functions_t, *PStApi_IStGraphDataBufferListResizable_Functions_t;


	/*************************************************************************/
	/* StApi::IStGraphDataFilter */
	/*************************************************************************/

	/*!
		@~english	@brief	Get IStGraphDataFilter handle.
		@~english	@details	Get IStGraphDataFilter handle.
		@~english	@param[in] pSourceHandle	Interface handle that is enable to convert to IStGraphDataFilter interface handle.
		@~english	@param[in,out] pIStGraphDataFilterHandle	IStGraphDataFilter interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStGraphDataFilterハンドルを取得します。
		@~japanese	@details	IStGraphDataFilterハンドルを取得します。
		@~japanese	@param[in] pSourceHandle	IStGraphDataFilter インターフェースハンドルに変換可能なインターフェースハンドル
		@~japanese	@param[in,out] pIStGraphDataFilterHandle	IStGraphDataFilter インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStGraphDataFilter_GetIStGraphDataFilter_t)(const PStApiHandle_t pSourceHandle, PStApiHandle_t pIStGraphDataFilterHandle);


	/*!
		@~english	@brief	Acquire current ROI mode.
		@~english	@details	Acquire current ROI mode.
		@~english	@param[in] pIStGraphDataFilterHandle	IStGraphDataFilter interface handle.
		@~english	@param[out] peRM	ROI mode.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ROIモードを取得します。
		@~japanese	@details	ROIモードを取得します。
		@~japanese	@param[in] pIStGraphDataFilterHandle	IStGraphDataFilter インターフェースハンドル
		@~japanese	@param[out] peRM	ROIモード
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStGraphDataFilter_GetROIMode_t)(const PStApiHandle_t pIStGraphDataFilterHandle, EStROIMode_t *peRM);

	/*!
		@~english	@brief	Set ROI mode.
		@~english	@details	Set ROI mode.
		@~english	@param[in] pIStGraphDataFilterHandle	IStGraphDataFilter interface handle.
		@~english	@param[in] eRM	ROI mode.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	ROIモードを設定します。
		@~japanese	@details	ROIモードを設定します。
		@~japanese	@param[in] pIStGraphDataFilterHandle	IStGraphDataFilter インターフェースハンドル
		@~japanese	@param[in] eRM	ROIモード
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStGraphDataFilter_SetROIMode_t)(const PStApiHandle_t pIStGraphDataFilterHandle, EStROIMode_t eRM);

	/*!
		@~english	@brief	Get X-axis offset value of ROI.
		@~english	@details	Get X-axis offset value of ROI.
		@~english	@param[in] pIStGraphDataFilterHandle	IStGraphDataFilter interface handle.
		@~english	@param[out] pnValue	X-axis offset value.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	横方向のオフセット値を取得します。
		@~japanese	@details	横方向のオフセット値を取得します。
		@~japanese	@param[in] pIStGraphDataFilterHandle	IStGraphDataFilter インターフェースハンドル
		@~japanese	@param[out] pnValue	横方向のオフセット値
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStGraphDataFilter_GetOffsetX_t)(const PStApiHandle_t pIStGraphDataFilterHandle, size_t *pnValue);

	/*!
		@~english	@brief	Set X-axis offset value of ROI.
		@~english	@details	Set X-axis offset value of ROI.
		@~english	@param[in] pIStGraphDataFilterHandle	IStGraphDataFilter interface handle.
		@~english	@param[in]	value	X-axis offset value.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	横方向のオフセット値を設定します。
		@~japanese	@details	横方向のオフセット値を設定します。
		@~japanese	@param[in] pIStGraphDataFilterHandle	IStGraphDataFilter インターフェースハンドル
		@~japanese	@param[in]	value	横方向のオフセット値
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStGraphDataFilter_SetOffsetX_t)(const PStApiHandle_t pIStGraphDataFilterHandle, size_t value);

	/*!
		@~english	@brief	Get Y-axis offset value of ROI.
		@~english	@details	Get Y-axis offset value of ROI.
		@~english	@param[in] pIStGraphDataFilterHandle	IStGraphDataFilter interface handle.
		@~english	@param[out] pnValue	Y-axis offset value.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	縦方向のオフセット値を取得します。
		@~japanese	@details	縦方向のオフセット値を取得します。
		@~japanese	@param[in] pIStGraphDataFilterHandle	IStGraphDataFilter インターフェースハンドル
		@~japanese	@param[out] pnValue	縦方向のオフセット値
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStGraphDataFilter_GetOffsetY_t)(const PStApiHandle_t pIStGraphDataFilterHandle, size_t *pnValue);

	/*!
		@~english	@brief	Set Y-axis offset value of ROI.
		@~english	@details	Set Y-axis offset value of ROI.
		@~english	@param[in] pIStGraphDataFilterHandle	IStGraphDataFilter interface handle.
		@~english	@param[in]	value	Y-axis offset value.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	縦方向のオフセット値を設定します。
		@~japanese	@details	縦方向のオフセット値を設定します。
		@~japanese	@param[in] pIStGraphDataFilterHandle	IStGraphDataFilter インターフェースハンドル
		@~japanese	@param[in]	value	縦方向のオフセット値
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStGraphDataFilter_SetOffsetY_t)(const PStApiHandle_t pIStGraphDataFilterHandle, size_t value);

	/*!
		@~english	@brief	Get width of ROI.
		@~english	@details	Get width of ROI.
		@~english	@param[in] pIStGraphDataFilterHandle	IStGraphDataFilter interface handle.
		@~english	@param[out] pnValue	Width of ROI.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	横方向のサイズを取得します。
		@~japanese	@details	横方向のサイズを取得します。
		@~japanese	@param[in] pIStGraphDataFilterHandle	IStGraphDataFilter インターフェースハンドル
		@~japanese	@param[out] pnValue	横方向のサイズ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStGraphDataFilter_GetWidth_t)(const PStApiHandle_t pIStGraphDataFilterHandle, size_t *pnValue);

	/*!
		@~english	@brief	Set width of ROI.
		@~english	@details	Set width of ROI.
		@~english	@param[in] pIStGraphDataFilterHandle	IStGraphDataFilter interface handle.
		@~english	@param[in]	value	Width of ROI.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	横方向のサイズを設定します。
		@~japanese	@details	横方向のサイズを設定します。
		@~japanese	@param[in] pIStGraphDataFilterHandle	IStGraphDataFilter インターフェースハンドル
		@~japanese	@param[in]	value	横方向のサイズ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStGraphDataFilter_SetWidth_t)(const PStApiHandle_t pIStGraphDataFilterHandle, size_t value);

	/*!
		@~english	@brief	Get height of ROI.
		@~english	@details	Get height of ROI.
		@~english	@param[in] pIStGraphDataFilterHandle	IStGraphDataFilter interface handle.
		@~english	@param[out] pnValue	Height of ROI.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	縦方向のサイズを取得します。
		@~japanese	@details	縦方向のサイズを取得します。
		@~japanese	@param[in] pIStGraphDataFilterHandle	IStGraphDataFilter インターフェースハンドル
		@~japanese	@param[out] pnValue	縦方向のサイズ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStGraphDataFilter_GetHeight_t)(const PStApiHandle_t pIStGraphDataFilterHandle, size_t *pnValue);
		
	/*!
		@~english	@brief	Set height of ROI.
		@~english	@details	Set height of ROI.
		@~english	@param[in] pIStGraphDataFilterHandle	IStGraphDataFilter interface handle.
		@~english	@param[in]	value	Height of ROI.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	縦方向のサイズを設定します。
		@~japanese	@details	縦方向のサイズを設定します。
		@~japanese	@param[in] pIStGraphDataFilterHandle	IStGraphDataFilter インターフェースハンドル
		@~japanese	@param[in]	value	縦方向のサイズ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStGraphDataFilter_SetHeight_t)(const PStApiHandle_t pIStGraphDataFilterHandle, size_t value);
	/*!
		@~english	@brief	Acquire the type of the data.
		@~english	@details	Acquire the type of the data.
		@~english	@param[in] pIStGraphDataFilterHandle	IStGraphDataFilter interface handle.
		@~english	@param[out] peValue	Type of the data.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	データのタイプを取得します。
		@~japanese	@details	データのタイプを取得します。
		@~japanese	@param[in] pIStGraphDataFilterHandle	IStGraphDataFilter インターフェースハンドル
		@~japanese	@param[out] peValue	データのタイプ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStGraphDataFilter_GetGraphDataType_t)(const PStApiHandle_t pIStGraphDataFilterHandle, EStGraphDataType_t *peValue);

	/*!
		@~english	@brief	Set the type of the data.
		@~english	@details	Set the type of the data.
		@~english	@param[in] pIStGraphDataFilterHandle	IStGraphDataFilter interface handle.
		@~english	@param[in] eValue	Type of the data.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	データのタイプを設定します。
		@~japanese	@details	データのタイプを設定します。
		@~japanese	@param[in] pIStGraphDataFilterHandle	IStGraphDataFilter インターフェースハンドル
		@~japanese	@param[in] eValue	データのタイプ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStGraphDataFilter_SetGraphDataType_t)(const PStApiHandle_t pIStGraphDataFilterHandle, EStGraphDataType_t eValue);

	/*!
		@~english	@brief	Acquire the list of the graph data.
		@~english	@details	Acquire the list of the graph datadata.
		@~english	@param[in] pIStGraphDataFilterHandle	IStGraphDataFilter interface handle.
		@~english	@param[int, out] pIStGraphDataBufferListHandle	IStGraphDataBufferList interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	グラフデータのバッファリストを取得します。
		@~japanese	@details	グラフデータのバッファリストを取得します。
		@~japanese	@param[in] pIStGraphDataFilterHandle	IStGraphDataFilter インターフェースハンドル
		@~japanese	@param[int, out] pIStGraphDataBufferListHandle	IStGraphDataBufferList インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStGraphDataFilter_GetIStGraphDataBufferList_t)(const PStApiHandle_t pIStGraphDataFilterHandle, PStApiHandle_t pIStGraphDataBufferListHandle);




	/*!
		@ingroup StApiIP_PublicInterface
		@interface IStGraphDataFilter
		@~english	@brief	Interface for Graph Data Filter.
		@~english	@details	Interface for Graph Data Filter.
		@sa	PStApiIP_IStFilter_CreateIStFilter_t(), PStApiIP_IStFilter_GetIStFilterInfo()
		@~japanese	@brief	グラフデータフィルター用インターフェース
		@~japanese	@details	グラフデータフィルター用インターフェース
		@sa	PStApiIP_IStFilter_CreateIStFilter_t(), PStApiIP_IStFilter_GetIStFilterInfo()
		@since StApi v1.1.1
	*/
	typedef struct _StApi_IStGraphDataFilter_Functions_t
	{
		/*!
			@copydoc PStApiIP_IStGraphDataFilter_GetIStGraphDataFilter_t()
		*/
		PStApiIP_IStGraphDataFilter_GetIStGraphDataFilter_t	GetIStGraphDataFilter;

		/*!
			@copydoc PStApiIP_IStGraphDataFilter_GetROIMode_t()
		*/
		PStApiIP_IStGraphDataFilter_GetROIMode_t	GetROIMode;

		/*!
			@copydoc PStApiIP_IStGraphDataFilter_SetROIMode_t()
		*/
		PStApiIP_IStGraphDataFilter_SetROIMode_t	SetROIMode;

		/*!
			@copydoc PStApiIP_IStGraphDataFilter_GetOffsetX_t()
		*/
		PStApiIP_IStGraphDataFilter_GetOffsetX_t	GetOffsetX;

		/*!
			@copydoc PStApiIP_IStGraphDataFilter_SetOffsetX_t()
		*/
		PStApiIP_IStGraphDataFilter_SetOffsetX_t	SetOffsetX;

		/*!
			@copydoc PStApiIP_IStGraphDataFilter_GetOffsetY_t()
		*/
		PStApiIP_IStGraphDataFilter_GetOffsetY_t	GetOffsetY;

		/*!
			@copydoc PStApiIP_IStGraphDataFilter_SetOffsetY_t()
		*/
		PStApiIP_IStGraphDataFilter_SetOffsetY_t	SetOffsetY;

		/*!
			@copydoc PStApiIP_IStGraphDataFilter_GetWidth_t()
		*/
		PStApiIP_IStGraphDataFilter_GetWidth_t	GetWidth;

		/*!
			@copydoc PStApiIP_IStGraphDataFilter_SetWidth_t()
		*/
		PStApiIP_IStGraphDataFilter_SetWidth_t	SetWidth;

		/*!
			@copydoc PStApiIP_IStGraphDataFilter_GetHeight_t()
		*/
		PStApiIP_IStGraphDataFilter_GetHeight_t	GetHeight;

		/*!
			@copydoc PStApiIP_IStGraphDataFilter_SetHeight_t()
		*/
		PStApiIP_IStGraphDataFilter_SetHeight_t	SetHeight;

		/*!
			@copydoc PStApiIP_IStGraphDataFilter_GetGraphDataType_t()
		*/
		PStApiIP_IStGraphDataFilter_GetGraphDataType_t	GetGraphDataType;

		/*!
			@copydoc PStApiIP_IStGraphDataFilter_SetGraphDataType_t()
		*/
		PStApiIP_IStGraphDataFilter_SetGraphDataType_t	SetGraphDataType;

		/*!
			@copydoc PStApiIP_IStGraphDataFilter_GetIStGraphDataBufferList_t()
		*/
		PStApiIP_IStGraphDataFilter_GetIStGraphDataBufferList_t	GetIStGraphDataBufferList;
	}StApi_IStGraphDataFilter_Functions_t, *PStApi_IStGraphDataFilter_Functions_t;


	/*************************************************************************/
	/* StApi::IStGraphDisplayWnd */
	/*************************************************************************/
	/*!
		@~english	@brief	Get IStGraphDisplayWnd handle.
		@~english	@details	Get IStGraphDisplayWnd handle.
		@~english	@param[in] pSourceHandle	Interface handle that is enable to convert to IStGraphDisplayWnd interface handle.
		@~english	@param[in,out] pIStGraphDisplayWndHandle	IStGraphDisplayWnd interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStGraphDisplayWnd ハンドルを取得します。
		@~japanese	@details	IStGraphDisplayWnd ハンドルを取得します。
		@~japanese	@param[in] pSourceHandle	IStGraphDisplayWnd インターフェースハンドルに変換可能なインターフェースハンドル
		@~japanese	@param[in,out] pIStGraphDisplayWndHandle	IStGraphDisplayWnd インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStGraphDisplayWnd_GetIStGraphDisplayWnd_t)(const PStApiHandle_t pSourceHandle, PStApiHandle_t pIStGraphDisplayWndHandle);

	/*!
		@~english	@brief	Register Graph Data Buffer List to display.
		@~english	@details	Register Graph Data Buffer List to display. The data will be copied.
		@~english	@param[in] pIStGraphDisplayWndHandle	IStGraphDisplayWnd interface handle.
		@~english	@param[in]	pIStGraphDataBufferList	IStGraphDataBufferList interface handlr to the graph data to display.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	表示するグラフデータを登録します。
		@~japanese	@details	表示するグラフデータをを登録します。グラフデータをはSDK内部のバッファへコピーされます。
		@~japanese	@param[in] pIStGraphDisplayWndHandle	IStGraphDisplayWnd インターフェースハンドル
		@~japanese	@param[in]	pIStGraphDataBufferList	表示するグラフデータの IStGraphDataBufferList インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStGraphDisplayWnd_RegisterIStGraphDataBufferList_t)(const PStApiHandle_t pIStGraphDisplayWndHandle, const PStApiHandle_t pIStGraphDataBufferListHandle);

	/*!
		@~english	@brief	Draw graph.
		@~english	@details	Draw graph.
		@~english	@param[in] pIStGraphDisplayWndHandle	IStGraphDisplayWnd interface handle.
		@~english	@param[in]	hDC Device context handle. In Mac/Linux (Qt-based), HDC (void*) is a QPainter*.
		@~english	@param[in]	nWidth Width of the graph.
		@~english	@param[in]	nHeight Height of the graph.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	グラフを描画します。
		@~japanese	@details	グラフを描画します。
		@~japanese	@param[in] pIStGraphDisplayWndHandle	IStGraphDisplayWnd インターフェースハンドル
		@~japanese	@param[in]	hDC	デバイスコンテキスト。Mac/Linux Qtの場合はHDC (void*)はQPainter*です。
		@~japanese	@param[in]	nWidth グラフの横サイズ
		@~japanese	@param[in]	nHeight グラフの縦サイズ
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStGraphDisplayWnd_Draw_t)(const PStApiHandle_t pIStGraphDisplayWndHandle, HDC hDC, uint32_t nWidth, uint32_t nHeight);

	/*!
		@~english	@brief	Get graph image.
		@~english	@details	Get graph image.
		@~english	@param[in] pIStGraphDisplayWndHandle	IStGraphDisplayWnd interface handle.
		@~english	@param[in,out]	pIStImageBuffer	Image buffer for graph image.
		@~english	@param[in]	nImageWidth Width of the image. If the value is equal to 0, the image width is same as the width of displayed graph.
		@~english	@param[in]	nImageHeight Height of the image. If the value is equal to 0, the image height is same as the height of displayed graph.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	グラフの画像データを取得します。
		@~japanese	@details	グラフの画像データを取得します。
		@~japanese	@param[in] pIStGraphDisplayWndHandle	IStGraphDisplayWnd インターフェースハンドル
		@~japanese	@param[in,out]	pIStImageBuffer	strFileName	グラフの画像データを取得するバッファを指定します。
		@~japanese	@param[in]	nImageWidth 画像の横サイズ(0指定時は表示サイズ)
		@~japanese	@param[in]	nImageHeight 画像の縦サイズ(0指定時は表示サイズ)
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiGUI_IStGraphDisplayWnd_GetIStImage_t)(const PStApiHandle_t pIStGraphDisplayWndHandle, const PStApiHandle_t pIStImageBufferHandle, size_t nImageWidth, size_t nImageHeight);

	/*!
		@ingroup StApiGUI_PublicInterface
		@interface IStGraphDisplayWnd
		@~english	@brief	Interface for Display Graph Window.
		@~english	@details	Interface for Display Graph Window.
		@~japanese	@brief	グラフ表示ウィンドウ用インターフェース
		@~japanese	@details	グラフ表示ウィンドウ用インターフェース
		@since StApi v1.1.1
	*/
	typedef struct _StApi_IStGraphDisplayWnd_Functions_t
	{
		/*!
			@copydoc PStApiGUI_IStGraphDisplayWnd_GetIStGraphDisplayWnd_t()
		*/
		PStApiGUI_IStGraphDisplayWnd_GetIStGraphDisplayWnd_t	GetIStGraphDisplayWnd;

		/*!
			@copydoc PStApiGUI_IStGraphDisplayWnd_RegisterIStGraphDataBufferList_t()
		*/
		PStApiGUI_IStGraphDisplayWnd_RegisterIStGraphDataBufferList_t	RegisterIStGraphDataBufferList;
		
		/*!
			@copydoc PStApiGUI_IStGraphDisplayWnd_Draw_t()
		*/
		PStApiGUI_IStGraphDisplayWnd_Draw_t	Draw;

		/*!
			@copydoc PStApiGUI_IStGraphDisplayWnd_GetIStImage_t()
		*/
		PStApiGUI_IStGraphDisplayWnd_GetIStImage_t	GetIStImage;


	}StApi_IStGraphDisplayWnd_Functions_t, *PStApi_IStGraphDisplayWnd_Functions_t;


	/*************************************************************************/
	/* StApi::IStDrawingTool */
	/*************************************************************************/
	/*!
		@~english	@brief	Draw on the specific image buffer.
		@~english	@details	Draw on the specific image buffer.
		@~english	@param[in]  pIStDrawingToolHandle	IStDrawingTool interface handle.
		@~english	@param[in,out]	pIStImageBuffer	Image buffer on which figures will be drawn.
		@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument.
		@~japanese	@brief	指定された画像バッファに描画を行います。
		@~japanese	@details	指定された画像バッファに描画を行います。
		@~japanese	@param[in] pIStDrawingToolHandle	IStDrawingTool インターフェースハンドル
		@~japanese	@param[in,out]	pIStImageBuffer	描画先の画像バッファ
		@~japanese	@exception	不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
	*/
	STAPI_PCALL(PStApiGUI_IStDrawingTool_DrawOnIStImageBuffer_t)(const PStApiHandle_t pIStDrawingToolHandle, const PStApiHandle_t pIStImageBufferHandle);


	/*!
		@ingroup StApiGUI_PublicInterface
		@interface IStDrawingTool
		@~english	@brief	Interface for tool to draw on a image.
		@~english	@details	Interface for tool to draw on a image.
		@~japanese	@brief	画像上への描画用ツールウィンドウインターフェース
		@~japanese	@details	画像上への描画用ツールウィンドウインターフェース
		@since StApi v1.1.1
	*/
	typedef struct _StApi_IStDrawingTool_Functions_t
	{
		/*!
			@copydoc PStApiGUI_IStDrawingTool_DrawOnIStImageBuffer_t()
		*/
		PStApiGUI_IStDrawingTool_DrawOnIStImageBuffer_t	DrawOnIStImageBuffer;
	}StApi_IStDrawingTool_Functions_t, *PStApi_IStDrawingTool_Functions_t;



	/*************************************************************************/
	/* StApi::IStImageAveragingFilter */
	/*************************************************************************/
	/*!
		@~english	@brief	Get IStImageAveragingFilter handle.
		@~english	@details	Get IStImageAveragingFilter handle.
		@~english	@param[in] pSourceHandle	Interface handle that is enable to convert to IStImageAveragingFilter interface handle.
		@~english	@param[in,out] pIStImageAveragingFilterHandle	IStImageAveragingFilter interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStImageAveragingFilterハンドルを取得します。
		@~japanese	@details	IStImageAveragingFilterハンドルを取得します。
		@~japanese	@param[in] pSourceHandle	IStImageAveragingFilter インターフェースハンドルに変換可能なインターフェースハンドル
		@~japanese	@param[in,out] pIStImageAveragingFilterHandle	IStImageAveragingFilter インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStImageAveragingFilter_GetIStImageAveragingFilter_t)(const PStApiHandle_t pSourceHandle, PStApiHandle_t pIStImageAveragingFilterHandle);

	/*!
		@~english	@brief	Get averaged image data.
		@~english	@details	Get averaged image data.
		@~english	@param[in] pIStImageAveragingFilterHandle	IStImageAveragingFilter interface handle.
		@~english	@param[in, out]	pIStImageBuffer	IStImageBuffer handle pointer for averaged image.
		@~english	@param[in]	nEachComponentBitsCount	Bits count of each component of the averaged image. If 0 is specified and the count of bits of the original image is bigger than or equals to 8, the same count of bits as the original image is used.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	 平均化された画像データを取得します。
		@~japanese	@details	平均化された画像データを取得します。
		@~japanese	@param[in] pIStImageAveragingFilterHandle	IStImageAveragingFilter インターフェースハンドル
		@~japanese	@param[in, out]	pIStImageBuffer	平均化された画像用の IStImageBuffer インターフェースハンドル
		@~japanese	@param[in]	nEachComponentBitsCount	平均化された画像の個々の構成要素のビット数を指定します。0が指定されかつ入力画像のビット数が8以上の場合は、入力画像と同じビット数が使用されます。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStImageAveragingFilter_GetAveragedImage_t)(const PStApiHandle_t pIStImageAveragingFilterHandle, const PStApiHandle_t pIStImageBufferHandle, size_t nEachComponentBitsCount);

	/*!
		@~english	@brief	Clear accumulated image data.
		@~english	@details	Clear accumulated image data.
		@~english	@param[in] pIStImageAveragingFilterHandle	IStImageAveragingFilter interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	 積算された画像データを消去します。
		@~japanese	@details	積算された画像データを消去します。
		@~japanese	@param[in] pIStImageAveragingFilterHandle	IStImageAveragingFilter インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStImageAveragingFilter_ClearImageData_t)(const PStApiHandle_t pIStImageAveragingFilterHandle);

	/*!
		@~english	@brief	Get a count of the images.
		@~english	@details	Get a count of the images.
		@~english	@param[in] pIStImageAveragingFilterHandle	IStImageAveragingFilter interface handle.
		@~english	@param[out] pnValue		Count of the images.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	 積算された画像の数を取得します。
		@~japanese	@details	積算された画像の数を取得します。
		@~japanese	@param[in] pIStImageAveragingFilterHandle	IStImageAveragingFilter インターフェースハンドル
		@~japanese	@param[out] pnValue		積算された画像の数
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStImageAveragingFilter_GetFrameCount_t)(const PStApiHandle_t pIStImageAveragingFilterHandle, size_t *pnValue);

	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStImageAveragingFilter_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IStImageAveragingFilter.
		@~english	@details	This structure holds the address of the C language wrapper function of IStImageAveragingFilter.
		@~japanese	@brief	この構造体は IStImageAveragingFilter のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IStImageAveragingFilter のC言語用ラッパー関数のアドレスを保持します。
		@since StApi v1.1.1
	*/
	typedef struct _StApi_IStImageAveragingFilter_Functions_t
	{
		/*!
			@copydoc PStApiIP_IStImageAveragingFilter_GetIStImageAveragingFilter_t()
		*/
		PStApiIP_IStImageAveragingFilter_GetIStImageAveragingFilter_t				GetIStImageAveragingFilter;

		/*!
			@copydoc PStApiIP_IStImageAveragingFilter_GetAveragedImage_t()
		*/
		PStApiIP_IStImageAveragingFilter_GetAveragedImage_t				GetAveragedImage;

		/*!
			@copydoc PStApiIP_IStImageAveragingFilter_ClearImageData_t()
		*/
		PStApiIP_IStImageAveragingFilter_ClearImageData_t				ClearImageData;

		/*!
			@copydoc PStApiIP_IStImageAveragingFilter_GetFrameCount_t()
		*/
		PStApiIP_IStImageAveragingFilter_GetFrameCount_t				GetFrameCount;

	}StApi_IStImageAveragingFilter_Functions_t, *PStApi_IStImageAveragingFilter_Functions_t;

	/*************************************************************************/
	/* StApi::IStDefectivePixelDetectionFilter */
	/*************************************************************************/
	/*!
		@~english	@brief	Get IStDefectivePixelDetectionFilter handle.
		@~english	@details	Get IStDefectivePixelDetectionFilter handle.
		@~english	@param[in] pSourceHandle	Interface handle that is enable to convert to IStDefectivePixelDetectionFilter interface handle.
		@~english	@param[in,out] pIStIStDefectivePixelDetectionFilterHandle	IStDefectivePixelDetectionFilter interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	IStDefectivePixelDetectionFilterハンドルを取得します。
		@~japanese	@details	IStDefectivePixelDetectionFilterハンドルを取得します。
		@~japanese	@param[in] pSourceHandle	IStDefectivePixelDetectionFilter インターフェースハンドルに変換可能なインターフェースハンドル
		@~japanese	@param[in,out] pIStDefectivePixelDetectionFilterHandle	IStDefectivePixelDetectionFilter インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStDefectivePixelDetectionFilter_GetIStDefectivePixelDetectionFilter_t)(const PStApiHandle_t pSourceHandle, PStApiHandle_t pIStDefectivePixelDetectionFilterHandle);

	/*!
		@~english	@brief	Acquire the defect pixel detection result.
		@~english	@details	Acquire the defect pixel detection result.
		@~english	@param[in] pIStDefectivePixelDetectionFilterHandle	IStDefectivePixelDetectionFilter interface handle.
		@~english	@param[out] peStatus	Get the status of detection.
		@~english	@param[in,out] pnCount	Input the buffer size and output the number of detected defective pixels.
		@~english	@param[out] pDefectivePixelInfoList	Get the information of the defective pixels.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	 欠陥画素検出結果を取得します。
		@~japanese	@details	欠陥画素検出結果を取得します。
		@~japanese	@param[in] pIStDefectivePixelDetectionFilterHandle	IStDefectivePixelDetectionFilter インターフェースハンドル
		@~japanese	@param[out] peStatus	検出の状態を取得します。
		@~japanese	@param[in,out] pnCount	バッファのサイズを入力し、検出された欠陥画素の数を取得します。
		@~japanese	@param[out] pDefectivePixelInfoList	検出された欠陥画素の情報を取得します。
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStDefectivePixelDetectionFilter_GetDetectionResult_t)(const PStApiHandle_t pIStDefectivePixelDetectionFilterHandle, EStDefectivePixelDetectionStatus_t *peStatus, size_t *pnCount, PSStDefectivePixelInformation_t pDefectivePixelInfoList);

	/*!
		@~english	@brief	Clear detected defective pixel information.
		@~english	@details	Clear detected defective pixel information.
		@~english	@param[in] pIStDefectivePixelDetectionFilterHandle	IStDefectivePixelDetectionFilter interface handle.
		@~english	@return	EStApiCError_t error code.
		@~japanese	@brief	 検出された欠陥画素情報を消去します。
		@~japanese	@details	検出された欠陥画素情報を消去します。
		@~japanese	@param[in] pIStDefectivePixelDetectionFilterHandle	IStDefectivePixelDetectionFilter インターフェースハンドル
		@~japanese	@return	EStApiCError_t エラーコード
	*/
	STAPI_PCALL(PStApiIP_IStDefectivePixelDetectionFilter_ClearDetectionResult_t)(const PStApiHandle_t pIStDefectivePixelDetectionFilterHandle);

	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_IStDefectivePixelDetectionFilter_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of IStDefectivePixelDetectionFilter.
		@~english	@details	This structure holds the address of the C language wrapper function of IStDefectivePixelDetectionFilter.
		@~japanese	@brief	この構造体は IStDefectivePixelDetectionFilter のC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体は IStDefectivePixelDetectionFilter のC言語用ラッパー関数のアドレスを保持します。
		@since StApi v1.1.1
	*/
	typedef struct _StApi_IStDefectivePixelDetectionFilter_Functions_t
	{
		/*!
			@copydoc PStApiIP_IStDefectivePixelDetectionFilter_GetIStDefectivePixelDetectionFilter_t()
		*/
		PStApiIP_IStDefectivePixelDetectionFilter_GetIStDefectivePixelDetectionFilter_t				GetIStDefectivePixelDetectionFilter;

		/*!
			@copydoc PStApiIP_IStDefectivePixelDetectionFilter_GetDetectionResult_t()
		*/
		PStApiIP_IStDefectivePixelDetectionFilter_GetDetectionResult_t				GetDetectionResult;

		/*!
			@copydoc PStApiIP_IStDefectivePixelDetectionFilter_ClearDetectionResult_t()
		*/
		PStApiIP_IStDefectivePixelDetectionFilter_ClearDetectionResult_t				ClearDetectionResult;

	}StApi_IStDefectivePixelDetectionFilter_Functions_t, *PStApi_IStDefectivePixelDetectionFilter_Functions_t;



	/*************************************************************************/
	/* StApi */
	/*************************************************************************/
	/*!
		@ingroup StApiC_PublicImpl
		@struct StApi_Functions_t
		@~english	@brief	This structure holds the address of the C language wrapper function of StApi.
		@~english	@details	This structure holds the address of the C language wrapper function of StApi.
		@~japanese	@brief	この構造体はStApiのC言語用ラッパー関数のアドレスを保持します。
		@~japanese	@details	この構造体はStApiのC言語用ラッパー関数のアドレスを保持します。
	*/
	typedef struct _StApi_Functions_t
	{
		/* StApi */
		/*!
			@copydoc PStApi_StApiCTerminate_t()
		*/
		PStApi_StApiCTerminate_t								StApiCTerminate;

		/*!
			@copydoc PStApi_GetStApiVersion_t()
		*/
		PStApi_GetStApiVersion_t								GetStApiVersion;

		/*!
			@copydoc PStApi_GetStApiVersionTextA_t()
		*/
		PStApi_GetStApiVersionTextA_t							GetStApiVersionTextA;

		/*!
			@copydoc PStApi_GetLastErrorDescriptionA_t()
		*/
		PStApi_GetLastErrorDescriptionA_t						GetLastErrorDescriptionA;

		/*!
			@copydoc StApi_IStPort_Functions_t
		*/
		StApi_IStPort_Functions_t								*IStPort;

		/*!
			@copydoc StApi_IStPortURLInfo_Functions_t
		*/
		StApi_IStPortURLInfo_Functions_t						*IStPortURLInfo;

		/*!
			@copydoc StApi_IStPortInfo_Functions_t
		*/
		StApi_IStPortInfo_Functions_t							*IStPortInfo;
		
		/*!
			@copydoc StApi_IStSystem_Functions_t
		*/
		StApi_IStSystem_Functions_t								*IStSystem;
		
		/*!
			@copydoc StApi_IStSystemArray_Functions_t
		*/
		StApi_IStSystemArray_Functions_t								*IStSystemArray;

		/*!
			@copydoc StApi_IStSystemInfo_Functions_t
		*/
		StApi_IStSystemInfo_Functions_t							*IStSystemInfo;

		/*!
			@copydoc StApi_IStInterface_Functions_t
		*/
		StApi_IStInterface_Functions_t							*IStInterface;

		/*!
			@copydoc StApi_IStInterfaceInfo_Functions_t
		*/
		StApi_IStInterfaceInfo_Functions_t						*IStInterfaceInfo;

		/*!
			@copydoc StApi_IStDevice_Functions_t
		*/
		StApi_IStDevice_Functions_t								*IStDevice;

		/*!
			@copydoc StApi_IStDeviceArray_Functions_t
		*/
		StApi_IStDeviceArray_Functions_t						*IStDeviceArray;

		/*!
			@copydoc StApi_IStDeviceInfo_Functions_t
		*/
		StApi_IStDeviceInfo_Functions_t							*IStDeviceInfo;

		/*!
			@copydoc StApi_IStDataStream_Functions_t
		*/
		StApi_IStDataStream_Functions_t							*IStDataStream;

		/*!
			@copydoc StApi_IStDataStreamArray_Functions_t
		*/
		StApi_IStDataStreamArray_Functions_t					*IStDataStreamArray;

		/*!
			@copydoc StApi_IStDataStreamInfo_Functions_t
		*/
		StApi_IStDataStreamInfo_Functions_t						*IStDataStreamInfo;

		/*!
			@copydoc StApi_IStStreamBuffer_Functions_t
		*/
		StApi_IStStreamBuffer_Functions_t						*IStStreamBuffer;

		/*!
			@copydoc StApi_IStStreamBufferInfo_Functions_t
		*/
		StApi_IStStreamBufferInfo_Functions_t					*IStStreamBufferInfo;

		/*!
			@copydoc StApi_IStImage_Functions_t
		*/
		StApi_IStImage_Functions_t								*IStImage;

		/*!
			@copydoc StApi_IStImageBuffer_Functions_t
		*/
		StApi_IStImageBuffer_Functions_t						*IStImageBuffer;

		/*!
			@copydoc StApi_IStPixelFormatInfo_Functions_t
		*/
		StApi_IStPixelFormatInfo_Functions_t					*IStPixelFormatInfo;

		/*!
			@copydoc StApi_IStPixelComponentInfo_Functions_t
		*/
		StApi_IStPixelComponentInfo_Functions_t					*IStPixelComponentInfo;

		/*!
			@copydoc StApi_IStPixelComponentValue_Functions_t
		*/
		StApi_IStPixelComponentValue_Functions_t				*IStPixelComponentValue;
		
		/*!
			@copydoc StApi_IStFeatureBag_Functions_t
		*/
		StApi_IStFeatureBag_Functions_t							*IStFeatureBag;

		/*!
			@copydoc StApi_IStAllocator_Functions_t
		*/
		StApi_IStAllocator_Functions_t							*IStAllocator;
		
		/*!
			@copydoc StApi_IStRegisteredCallback_Functions_t
		*/
		StApi_IStRegisteredCallback_Functions_t					*IStRegisteredCallback;

		/*!
			@copydoc StApi_IStCallbackParamBase_Functions_t
		*/
		StApi_IStCallbackParamBase_Functions_t					*IStCallbackParamBase;

		/*!
			@copydoc StApi_IStCallbackParamGenTLEventError_Functions_t
		*/
		StApi_IStCallbackParamGenTLEventError_Functions_t					*IStCallbackParamGenTLEventError;

		/*!
			@copydoc StApi_IStCallbackParamGenTLEventErrorTL_Functions_t
		*/
		StApi_IStCallbackParamGenTLEventErrorTL_Functions_t		*IStCallbackParamGenTLEventErrorTL;

		/*!
			@copydoc StApi_IStCallbackParamGenTLEventErrorIF_Functions_t
		*/
		StApi_IStCallbackParamGenTLEventErrorIF_Functions_t		*IStCallbackParamGenTLEventErrorIF;

		/*!
			@copydoc StApi_IStCallbackParamGenTLEventErrorDEV_Functions_t
		*/
		StApi_IStCallbackParamGenTLEventErrorDEV_Functions_t	*IStCallbackParamGenTLEventErrorDEV;

		/*!
			@copydoc StApi_IStCallbackParamGenTLEventErrorDS_Functions_t
		*/
		StApi_IStCallbackParamGenTLEventErrorDS_Functions_t		*IStCallbackParamGenTLEventErrorDS;

		/*!
			@copydoc StApi_IStCallbackParamGenTLEventErrorSB_Functions_t
		*/
		StApi_IStCallbackParamGenTLEventErrorSB_Functions_t		*IStCallbackParamGenTLEventErrorSB;

		/*!
			@copydoc StApi_IStCallbackParamGenTLEventNewBuffer_Functions_t
		*/
		StApi_IStCallbackParamGenTLEventNewBuffer_Functions_t	*IStCallbackParamGenTLEventNewBuffer;

		/* StApi(IP) */
		/*!
			@copydoc StApi_IStFilter_Functions_t
		*/
		StApi_IStFilter_Functions_t								*IStFilter;
		
		/*!
			@copydoc StApi_IStFilterArray_Functions_t
		*/
		StApi_IStFilterArray_Functions_t						*IStFilterArray;

		/*!
			@copydoc StApi_IStFilterInfo_Functions_t
		*/
		StApi_IStFilterInfo_Functions_t							*IStFilterInfo;

		/*!
			@copydoc StApi_IStGammaCorrectionFilter_Functions_t
		*/
		StApi_IStGammaCorrectionFilter_Functions_t					*IStGammaCorrectionFilter;

		/*!
			@copydoc StApi_IStColorTransformationFilter_Functions_t
		*/
		StApi_IStColorTransformationFilter_Functions_t				*IStColorTransformationFilter;

		/*!
			@copydoc StApi_IStEdgeEnhancementFilter_Functions_t
		*/
		StApi_IStEdgeEnhancementFilter_Functions_t					*IStEdgeEnhancementFilter;

		/*!
			@copydoc StApi_IStBalanceRatioFilter_Functions_t
		*/
		StApi_IStBalanceRatioFilter_Functions_t					*IStBalanceRatioFilter;

		/*!
			@copydoc StApi_IStNoiseReductionFilter_Functions_t
		*/
		StApi_IStNoiseReductionFilter_Functions_t					*IStNoiseReductionFilter;

		/*!
			@copydoc StApi_IStFlatFieldCorrectionFilter_Functions_t
		*/
		StApi_IStFlatFieldCorrectionFilter_Functions_t				*IStFlatFieldCorrectionFilter;

		/*!
			@copydoc StApi_IStChromaSuppressionFilter_Functions_t
		*/
		StApi_IStChromaSuppressionFilter_Functions_t				*IStChromaSuppressionFilter;

		/*!
			@copydoc StApi_IStSNMeasurementFilter_Functions_t
		*/
		StApi_IStSNMeasurementFilter_Functions_t					*IStSNMeasurementFilter;

		/*!
			@copydoc StApi_IStSNMeasurementResult_Functions_t
		*/
		StApi_IStSNMeasurementResult_Functions_t					*IStSNMeasurementResult;

		/*!
			@copydoc StApi_IStConverter_Functions_t
		*/
		StApi_IStConverter_Functions_t							*IStConverter;

		/*!
			@copydoc StApi_IStConverterInfo_Functions_t
		*/
		StApi_IStConverterInfo_Functions_t						*IStConverterInfo;

		/*!
			@copydoc StApi_IStPixelFormatConverter_Functions_t
		*/
		StApi_IStPixelFormatConverter_Functions_t				*IStPixelFormatConverter;

		/*!
			@copydoc StApi_IStReverseConverter_Functions_t
		*/
		StApi_IStReverseConverter_Functions_t					*IStReverseConverter;
		

		/*!
			@copydoc StApi_IStFiler_Functions_t
		*/
		StApi_IStFiler_Functions_t								*IStFiler;

		/*!
			@copydoc StApi_IStFilerInfo_Functions_t
		*/
		StApi_IStFilerInfo_Functions_t							*IStFilerInfo;

		/*!
			@copydoc StApi_IStStillImageFiler_Functions_t
		*/
		StApi_IStStillImageFiler_Functions_t					*IStStillImageFiler;

		/*!
			@copydoc StApi_IStVideoFiler_Functions_t
		*/
		StApi_IStVideoFiler_Functions_t						*IStVideoFiler;

		/*!
			@copydoc StApi_IStCallbackParamStApiIPVideoFilerOpen_Functions_t
		*/
		StApi_IStCallbackParamStApiIPVideoFilerOpen_Functions_t	*IStCallbackParamStApiIPVideoFilerOpen;

		/*!
			@copydoc StApi_IStCallbackParamStApiIPVideoFilerClose_Functions_t
		*/
		StApi_IStCallbackParamStApiIPVideoFilerClose_Functions_t	*IStCallbackParamStApiIPVideoFilerClose;

		/*!
			@copydoc StApi_IStCallbackParamStApiIPVideoFilerError_Functions_t
		*/
		StApi_IStCallbackParamStApiIPVideoFilerError_Functions_t	*IStCallbackParamStApiIPVideoFilerError;

		/* StApi(GUI) */

		/*!
			@copydoc StApi_IStWnd_Functions_t
		*/
		StApi_IStWnd_Functions_t								*IStWnd;

		/*!
			@copydoc StApi_IStWndInfo_Functions_t
		*/
		StApi_IStWndInfo_Functions_t							*IStWndInfo;

		/*!
			@copydoc StApi_IStDeviceSelectionWnd_Functions_t
		*/
		StApi_IStDeviceSelectionWnd_Functions_t				*IStDeviceSelectionWnd;

		/*!
			@copydoc StApi_IStImageDisplayWnd_Functions_t
		*/
		StApi_IStImageDisplayWnd_Functions_t					*IStImageDisplayWnd;

		/*!
			@copydoc StApi_IStNodeMapDisplayWnd_Functions_t
		*/
		StApi_IStNodeMapDisplayWnd_Functions_t					*IStNodeMapDisplayWnd;

		/*!
			@copydoc StApi_IStCallbackParamStApiGUIEventBaseWnd_Functions_t
		*/
		StApi_IStCallbackParamStApiGUIEventBaseWnd_Functions_t	*IStCallbackParamStApiGUIEventBaseWnd;

		/*!
			@copydoc StApi_IStCallbackParamStApiGUIEventBaseWndClose_Functions_t
		*/
		StApi_IStCallbackParamStApiGUIEventBaseWndClose_Functions_t	*IStCallbackParamStApiGUIEventBaseWndClose;

		/*!
			@copydoc StApi_IStCallbackParamStApiGUIEventBaseWndError_Functions_t
		*/
		StApi_IStCallbackParamStApiGUIEventBaseWndError_Functions_t	*IStCallbackParamStApiGUIEventBaseWndError;

		/*!
			@copydoc StApi_IStCallbackParamStApiGUIEventDrawing_Functions_t
		*/
		StApi_IStCallbackParamStApiGUIEventDrawing_Functions_t	*IStCallbackParamStApiGUIEventDrawing;

		//-----------------------------------------------------------------------------
		//v1.1.1
		//-----------------------------------------------------------------------------
		/*!
			@copydoc PStApi_GetLastErrorDescriptionW_t()
		*/
		PStApi_GetLastErrorDescriptionW_t						GetLastErrorDescriptionW;

		/*!
			@copydoc StApi_IStSpecificTypeAllocator_Functions_t
		*/
		StApi_IStSpecificTypeAllocator_Functions_t	*IStSpecificTypeAllocator;

		/* StApi(IP) */
		/*!
			@copydoc StApi_IStGraphData_Functions_t
		*/
		StApi_IStGraphData_Functions_t								*IStGraphData;

		/*!
			@copydoc StApi_IStGraphData_Functions_t
		*/
		StApi_IStGraphDataBuffer_Functions_t								*IStGraphDataBuffer;

		/*!
			@copydoc StApi_IStGraphDataBufferResizable_Functions_t
		*/
		StApi_IStGraphDataBufferResizable_Functions_t								*IStGraphDataBufferResizable;

		/*!
			@copydoc StApi_IStGraphDataBufferList_Functions_t
		*/
		StApi_IStGraphDataBufferList_Functions_t								*IStGraphDataBufferList;

		/*!
			@copydoc StApi_IStGraphDataBufferListResizable_Functions_t
		*/
		StApi_IStGraphDataBufferListResizable_Functions_t								*IStGraphDataBufferListResizable;

		/*!
			@copydoc StApi_IStGraphDataFilter_Functions_t
		*/
		StApi_IStGraphDataFilter_Functions_t								*IStGraphDataFilter;

		/*!
			@copydoc StApi_IStGraphDisplayWnd_Functions_t
		*/
		StApi_IStGraphDisplayWnd_Functions_t								*IStGraphDisplayWnd;

		/*!
			@copydoc StApi_IStDrawingTool_Functions_t
		*/
		StApi_IStDrawingTool_Functions_t								*IStDrawingTool;

		/*!
			@copydoc StApi_IStImageAveragingFilter_Functions_t
		*/
		StApi_IStImageAveragingFilter_Functions_t								*IStImageAveragingFilter;

		/*!
			@copydoc StApi_IStDefectivePixelDetectionFilter_Functions_t
		*/
		StApi_IStDefectivePixelDetectionFilter_Functions_t								*IStDefectivePixelDetectionFilter;

	}StApi_Functions_t, *PStApi_Functions_t;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STAPI_C_STAPI_H__ */
