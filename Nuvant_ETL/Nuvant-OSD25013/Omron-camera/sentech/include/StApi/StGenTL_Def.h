/* This file is encoded in UTF-8,  */
/* but BOM has not been added to accommodate environments not compatible with BOM. */
/*
 StApi
*/
/*!
	\ingroup	GenTL_PublicImple
	\file StGenTL_Def.h
	\brief 
*/
#ifndef STGENTL_DEF_H__
#define STGENTL_DEF_H__

#ifdef __cplusplus
	typedef bool bool8_t;
#else
	typedef uint8_t bool8_t;
	#define false 0
	#define true 1
#endif

#ifdef __cplusplus
namespace GenTL
{
#endif /* __cplusplus */

	/* --------------------------------------------------------------------- */
	/* typedef                                                               */
	/* --------------------------------------------------------------------- */
	/*!
		@ingroup GenTL_PublicImple
		@typedef TL_HANDLE
		@~english	@details	System module handle, obtained through the TLOpen() .
		@~japanese	@details	TLOpen() 関数で取得されるシステムモジュールハンドル
	*/
	typedef void*	TL_HANDLE;

	/*!
		@ingroup GenTL_PublicImple
		@typedef IF_HANDLE
		@~english	@details	Interface module handle, obtained through TLOpenInterface() .
		@~japanese	@details	TLOpenInterface() 関数で取得されるインターフェースモジュールハンドル
	*/
	typedef void*	IF_HANDLE;

	/*!
		@ingroup GenTL_PublicImple
		@typedef DEV_HANDLE
		@~english	@details	Device module handle, obtained through the IFOpenDevice() .
		@~japanese	@details	IFOpenDevice() 関数で取得されるデバイスモジュールハンドル
	*/
	typedef void*	DEV_HANDLE;

	/*!
		@ingroup GenTL_PublicImple
		@typedef DS_HANDLE
		@~english	@details	Data stream module handle, obtained through DevOpenDataStream() .
		@~japanese	@details	DevOpenDataStream() 関数で取得されるデータストリームモジュールハンドル
	*/
	typedef void*	DS_HANDLE;

	/*!
		@ingroup GenTL_PublicImple
		@typedef PORT_HANDLE
		@~english	@details	A Port handle is used to access the register of a port. A PORT_HANDLE is one of the following: TL_HANDLE, IF_HANDLE, DEV_HANDLE, handle to a device port obtained through DevGetPort(), DS_HANDLE, BUFFER_HANDLE.
		@~japanese	@details	ポートのレジスタ空間へアクセスするために使用されるポートハンドル。 PORT_HANDLE は、 TL_HANDLE 、 IF_HANDLE 、 DEV_HANDLE、 DS_HANDLE 、 BUFFER_HANDLE のいずれかになります。
	*/
	typedef void*	PORT_HANDLE;
	

	/*!
		@ingroup GenTL_PublicImple
		@typedef BUFFER_HANDLE
		@~english	@details	Buffer module handle, obtained through the DSAnnounceBuffer() function.
		@~japanese	@details	DSAnnounceBuffer() 関数で取得されるバッファモジュールハンドル
	*/
	typedef void*	BUFFER_HANDLE;

	/*!
		@ingroup GenTL_PublicImple
		@typedef EVENTSRC_HANDLE
		@~english	@details	An Event source handle is used to register a module event. EVENTSRC_HANDLE is one of the following: TL_HANDLE, IF_HANDLE, DEV_HANDLE, A handle to a device port obtained through DevGetPort(), DS_HANDLE, BUFFER_HANDLE.
		@~japanese	@details	イベントの登録に使用されるイベントソースハンドル。 EVENTSRC_HANDLE は、 TL_HANDLE 、 IF_HANDLE 、 DEV_HANDLE、 DS_HANDLE 、 BUFFER_HANDLE のいずれかになります。
	*/
	typedef void*	EVENTSRC_HANDLE;

	/*!
		@ingroup GenTL_PublicImple
		@typedef EVENT_HANDLE
		@~english	@details	Event handle.
		@~japanese	@details	イベントハンドル
	*/
	typedef void*	EVENT_HANDLE;

	
	/*-------------------------------------------------------------------------*/
	/*Enumerator                                                               */
	/*-------------------------------------------------------------------------*/
	/*! 
		@ingroup	GenTL_PublicImple
		@enum GC_ERROR
		@~english	@brief	GenTL Errors
		@~english	@details	GenTL Errors
		@~japanese	@brief	GenTLエラー列挙子
		@~japanese	@details	GenTLエラー列挙子
	*/
	typedef	enum GC_ERROR_LIST
	{
		/*!
			@~english	@details	Operation was successful. No error occurred.
			@~japanese	@details	操作は成功しました。エラーは発生しませんでした。
		*/
		GC_ERR_SUCCESS				= 0,

		/*!
			@~english	@details	Unspecified runtime error.
			@~japanese	@details	不特定のランタイムエラー。
		*/
		GC_ERR_ERROR				= -1001,

		/*!
			@~english	@details	Module or resource not initialized. e.g., GCInitLib() was not called.
			@~japanese	@details	モジュールやリソースが初期化されていません。 例: GCInitLib() が呼び出されていない。
		*/
		GC_ERR_NOT_INITIALIZED		= -1002,

		/*!
			@~english	@details	Requested operation not implemented. e.g.,no Port functions on a Buffer module.
			@~japanese	@details	要求された動作が実装されていません。 例: バッファモジュールに対してオプションのポート関数が実装されていない。
		*/
		GC_ERR_NOT_IMPLEMENTED		= -1003,

		/*!
			@~english	@details	Requested resource is already in use.
			@~japanese	@details	要求されたリソースが既に使用されています。
		*/
		GC_ERR_RESOURCE_IN_USE		= -1004,

		/*!
			@~english	@details	Requested operation is not allowed. e.g.,a remote device is opened by another client.
			@~japanese	@details	アクセスが拒否されました。 例: (リモート)デバイスが他のクライアントにオープンされている。 
		*/
		GC_ERR_ACCESS_DENIED		= -1005,

		/*!
			@~english	@details	Given handle does not support the operation. e.g.,function call on wrong handle or NULL pointer.
			@~japanese	@details	渡されたハンドルはこの操作をサポートしていません。 例: 不正なハンドルやNULLポインターに対する関数呼び出し。
		*/
		GC_ERR_INVALID_HANDLE		= -1006,

		/*!
			@~english	@details	ID could not be connected to a resource. e.g.,a device with the given ID is currently not available.
			@~japanese	@details	IDがリソースに結び付けられていません。 例: 与えられたIDのデバイスが現在は利用できない。
		*/
		GC_ERR_INVALID_ID			= -1007,
		
		/*!
			@~english	@details	The function has no data to work on.
			@~japanese	@details	関数が動作に必要とするデータがありません。
		*/
		GC_ERR_NO_DATA				= -1008,
		
		/*!
			@~english	@details	One of the parameter given was not valid or out of range.
			@~japanese	@details	与えられたパラメータが無効または範囲外です。
		*/
		GC_ERR_INVALID_PARAMETER	= -1009,
		
		/*!
			@~english	@details	Communication error has occurred. e.g.,a read or write operation to a remote device failed.
			@~japanese	@details	通信エラーが発生しました。 例: (リモート)デバイスに対する読書き操作が失敗した。
		*/
		GC_ERR_IO					= -1010,
		
		/*!
			@~english	@details	 An operation's timeout time expired before it could be completed.
			@~japanese	@details	操作が指定された時間内に完了しませんでした。
		*/
		GC_ERR_TIMEOUT				= -1011,	
		
		/*!
			@~english	@details	An operation has been aborted before it could be completed. For example a wait operation through EventGetData() has been terminated via a call to EventKill().
			@since GenTL v1.1
			@~japanese	@details	操作が完了する前に中止されました。 例: EventGetData() 関数が完了する前に EventKill() 関数の呼び出しにより中止された。
			@since GenTL v1.1
		*/
		GC_ERR_ABORT				= -1012,
		
		/*!
			@~english	@details	The GenTL Consumer has not announced enough buffers to start the acquisition in the currently active acquisition mode.
			@since GenTL v1.1
			@~japanese	@details	現在の取り込みモードでの取り込みを開始するのに十分なバッファがGenTLコンシュマーによって登録されていません。
			@since GenTL v1.1
		*/
		GC_ERR_INVALID_BUFFER		= -1013,
		
		/*!
			@~english	@details	Resource or information is not available at a given time in a current state.
			@since GenTL v1.2
			@~japanese	@details	リソースや情報が現時点では利用できません。
			@since GenTL v1.2
		*/
		GC_ERR_NOT_AVAILABLE		= -1014,
		
		/*!
			@~english	@details	A given address is out of range or invalid for internal reasons.
			@since GenTL v1.3
			@~japanese	@details	与えられたアドレスが範囲外または不正です。
			@since GenTL v1.3
		*/
		GC_ERR_INVALID_ADDRESS		= -1015,
		
		/*!
			@~english	@details	A provided buffer is too small to receive the expected amount of data. This may affect acquisition buffers in the Data Stream module if the buffers are smaller than the expected payloadsize but also buffers passed to any other function of the GenTL Producer interface to retrieve information or IDs.
			@since GenTL v1.4
			@~japanese	@details	予想される量のデータを受け取るには提供されたバッファが小さすぎます。予想されるペイロードサイズよりもバッファが小さい場合、データストリームの取り込みに影響が出る可能性があります。また、情報やIDを取得するためにGenTLプロデューサーへ渡されるバッファも同様です。
			@since GenTL v1.4
		*/
		GC_ERR_BUFFER_TOO_SMALL		= -1016,
		
		/*!
			@~english	@details	A provided index referencing a Producer internal object is out of bounds.
			@since GenTL v1.4
			@~japanese	@details	プロデューサーの内部オブジェクトを参照する提供されたインディックスが範囲外です。
			@since GenTL v1.4
		*/
		GC_ERR_INVALID_INDEX		= -1017,
		
		/*!
			@~english	@details	An error occurred parsing a buffer containing chunk data.
			@since GenTL v1.4
			@~japanese	@details	チャンクデータを含んだバッファの解釈中にエラーが発生しました。
			@since GenTL v1.4
		*/
		GC_ERR_PARSING_CHUNK_DATA	= -1018,
		
		/*!
			@~english	@details	A register write function was trying to write an invalid value.
			@since GenTL v1.4
			@~japanese	@details	レジスタ書き込み関数によって、不正な値の書き込みが要求されました。
			@since GenTL v1.4
		*/
		GC_ERR_INVALID_VALUE		= -1019,
		
		/*!
			@~english	@details	 A requested resource is exhausted. This is a rather general error which might for example refer to a limited number of available handles being available.
			@since GenTL v1.4
			@~japanese	@details	要求されたリソースが使い果たされました。これは一般的なエラーで、例えば利用可能なハンドルの数が限られていることを示している可能性があります。
			@since GenTL v1.4
		*/
		GC_ERR_RESOURCE_EXHAUSTED	= -1020,
		
		/*!
			@~english	@details	The system and/or other hardware in the system (frame grabber) ran out of memory.
			@since GenTL v1.4
			@~japanese	@details	システムおよび/またはシステム(フレームグラバー)内のその他のハードウェアのメモリーが不足しています。
			@since GenTL v1.4
		*/
		GC_ERR_OUT_OF_MEMORY		= -1021,
		
		/*!
			@~english	@details	The required operation cannot be executed because the responsible module/entity is busy executing actions that cannot be performed concurrently with the requested operation.
			@since GenTL v1.5
			@~japanese	@details	モジュールが要求された操作とは同時に行うことができない処理を実行しています。
			@since GenTL v1.5
		*/
		GC_ERR_BUSY					= -1022,
		
		/*!
			@~english	@details	Any error smaller or equal than -10000 is implementation specific. If a GenTL Consumer receives such an error number it should react as if it would be a generic runtime error.
			@~japanese	@details	-10000以下のエラーは実装によって異なります。もし、GenTLコンシュマーがこのエラーを受け取った場合、一般的なランタイムエラーとして応答すべきです。
		*/
		GC_ERR_CUSTOM_ID			= -10000
	} GC_ERROR, *PGC_ERROR;

	/*! 
		@ingroup	GenTL_PublicImple
		@enum INFO_DATATYPE
		@~english	@brief	Defines the data type possible for the various Info functions.
		@~english	@details	Defines the data type possible for the various Info functions.
		@~japanese	@brief	情報関数用データタイプ列挙子
		@~japanese	@details	情報関数用データタイプ列挙子
	*/
	typedef enum INFO_DATATYPE_LIST
	{
		/*!
			@~english	@details	Unknown data type. This value is never returned from a function but can be used to initialize the variable to inquire the type.
			@~japanese	@details	不明。この値は関数から返されることはありません。タイプを問い合わせるための変数の初期値として使用されます。
		*/
		INFO_DATATYPE_UNKNOWN		= 0,

		/*!
			@~english	@details	0-terminated C string (encoding according to the TL_INFO_CHAR_ENCODING info command).
			@~japanese	@details	0終端C文字列型。 エンコードは TL_INFO_CHAR_ENCODING 情報に従います。
		*/
		INFO_DATATYPE_STRING		= 1,

		/*!
			@~english	@details	Concatenated INFO_DATATYPE_STRING list.End of list is signaled with an additional 0.
			@~japanese	@details	連結された INFO_DATATYPE_STRING リスト型。 リストの終端には0が追加されます。
		*/
		INFO_DATATYPE_STRINGLIST	= 2,

		/*!
			@~english	@details	Signed 16 bit integer.
			@~japanese	@details	符号付16ビット整数型
		*/
		INFO_DATATYPE_INT16			= 3,

		/*!
			@~english	@details	Unsigned 16 bit integer.
			@~japanese	@details	符号なし16ビット整数型
		*/
		INFO_DATATYPE_UINT16		= 4,

		/*!
			@~english	@details	Signed 32 bit integer.
			@~japanese	@details	符号付32ビット整数型
		*/
		INFO_DATATYPE_INT32			= 5,

		/*!
			@~english	@details	Unsigned 32 bit integer.
			@~japanese	@details	符号なし32ビット整数型
		*/
		INFO_DATATYPE_UINT32		= 6,

		/*!
			@~english	@details	Signed 64 bit integer.
			@~japanese	@details	符号付64ビット整数型
		*/
		INFO_DATATYPE_INT64			= 7,

		/*!
			@~english	@details	Unsigned 64 bit integer.
			@~japanese	@details	符号なし64ビット整数型
		*/
		INFO_DATATYPE_UINT64		= 8,

		/*!
			@~english	@details	Signed 64 bit floating point number.
			@~japanese	@details	符号付64ビット浮動小数点型
		*/
		INFO_DATATYPE_FLOAT64		= 9,

		/*!
			@~english	@details	Pointer type (void*). Size is platform dependent (32 bit on 32 bit platforms).
			@~japanese	@details	ポインター型(void*)。サイズは環境依存(32bit環境では32ビット)。
		*/
		INFO_DATATYPE_PTR			= 10,

		/*!
			@~english	@details	Boolean value occupying 8 bit. 0 for false and anything for true.
			@~japanese	@details	8ビットbool型。0はfalse、その他はtrueを表します。
		*/
		INFO_DATATYPE_BOOL8			= 11,

		/*!
			@~english	@details	Platform dependent unsigned integer (32 bit on 32 bit platforms).
			@~japanese	@details	環境依存の符号なし整数型。サイズは環境依存(32bit環境では32ビット)。
		*/
		INFO_DATATYPE_SIZET			= 12,

		/*!
			@~english	@details	Like a INFO_DATATYPE_STRING but with arbitrary data and no 0 termination.
			@~japanese	@details	INFO_DATATYPE_STRING に似ているが0終端ではない任意のデータに使用される型。
		*/
		INFO_DATATYPE_BUFFER		= 13,

		/*!
			@~english	@details	The type ptrdiff_t is a type that can hold the result of subtracting two pointers.
			@~japanese	@details	2つのポインターの差を保持する型( ptrdiff_t )
			@since GenTL v1.3
		*/
		INFO_DATATYPE_PTRDIFF		= 14,

		/*!
			@~english	@details	Starting value for Custom IDs which are implementation specific.
			@~japanese	@details	実装依存の型を表す最初の値
		*/
		INFO_DATATYPE_CUSTOM_ID		= 1000
	}INFO_DATATYPE, *PINFO_DATATYPE;
	
	/*! 
		@ingroup	GenTL_PublicImple
		@enum	TL_CHAR_ENCODING
		@~english	@brief	Char encoding schemata.
		@~english	@details	Char encoding schemata.
		@~japanese	@brief	文字エンコーディング列挙子
		@~japanese	@details	文字エンコーディング列挙子
		@since GenTL v1.4
	*/
	typedef enum TL_CHAR_ENCODING_LIST
	{
		/*!
			@~english	@details	Char encoding of the GenTL Producer is ASCII.
			@~japanese	@details	GenTLプロデューサーの文字コードはアスキー
		*/
		TL_CHAR_ENCODING_ASCII	= 0,

		/*!
			@~english	@details	Char encoding of the GenTL Producer is UTF8.
			@~japanese	@details	GenTLプロデューサーの文字コードはUTF-8
		*/
		TL_CHAR_ENCODING_UTF8	= 1
	}TL_CHAR_ENCODING, *PTL_CHAR_ENCODING;
	
	/*! 
		@ingroup	GenTL_PublicImple
		@enum	TL_INFO_CMD
		@~english	@brief	System module information commands for the TLGetInfo() and GCGetInfo() functions.
		@~english	@details	System module information commands for the TLGetInfo() and GCGetInfo() functions.
		@~japanese	@brief	TLGetInfo() および GCGetInfo() 関数用システムモジュール情報コマンド
		@~japanese	@details	TLGetInfo() および GCGetInfo() 関数用システムモジュール情報コマンド
	*/
	typedef enum TL_INFO_CMD_LIST
	{

		/*!
			@~english	@details	STRING	Unique ID identifying a GenTL Producer.For example the filename of the GenTL Producer implementation including its path.
			@~japanese	@details	STRING	GenTLプロデューサーを特定するID。 例: パスを含むGenTLプロデューサーのファイル名。
		*/
		TL_INFO_ID				= 0,

		/*!
			@~english	@details	STRING	GenTL Producer vendor name.
			@~japanese	@details	STRING	GenTLプロデューサーベンダー名。
		*/
		TL_INFO_VENDOR			= 1,

		/*!
			@~english	@details	STRING	GenTL Producer model name. For example : A vendor produces more than one GenTL Producer for different device classes or different technologies. The TL_INFO_MODEL references a single GenTL Producer implementation.The combination of Vendor and Model provides a unique reference of ONE GenTL Producer implementation.
			@~japanese	@details	STRING	GenTLプロデューサーモデル名。 例: ベンダーはデバイスクラスや異なる技術に対して1つ以上のGenTLプロデューサーを提供します。 TL_INFO_MODEL はGenTLプロデューサーの1つの実装を表します。「ベンダー」と「モデル」を指定することで、一つのGenTLプロデューサーが特定されます。
		*/
		TL_INFO_MODEL			= 2,

		/*!
			@~english	@details	STRING	GenTL Producer version.
			@~japanese	@details	STRING	GenTLプロデューサーバージョン。
		*/
		TL_INFO_VERSION			= 3,

		/*!
			@~english	@details	STRING	Transport layer technology that is supported.
			@~japanese	@details	STRING	サポートされるトランスポート層タイプ。
		*/
		TL_INFO_TLTYPE			= 4,

		/*!
			@~english	@details	STRING	File name including extension of the library.
			@~japanese	@details	STRING	このライブラリの拡張子を含んだファイル名。
		*/
		TL_INFO_NAME			= 5,

		/*!
			@~english	@details	STRING	Full path including file name and extension of the library.
			@~japanese	@details	STRING	このライブラリの拡張子とファイル名を含む完全パス。
		*/
		TL_INFO_PATHNAME		= 6,

		/*!
			@~english	@details	STRING	User readable name of the GenTL	Producer.
			@~japanese	@details	STRING	GenTLプロデューサーのユーザーが読み込み可能な名前。
		*/
		TL_INFO_DISPLAYNAME		= 7,

		/*!
			@~english	@details	INT32(TL_CHAR_ENCODING_LIST)	The char encoding of the GenTL Producer.
			@since GenTL v1.4
			@~japanese	@details	INT32(TL_CHAR_ENCODING_LIST)	GenTLプロデューサーの文字エンコード。
			@since GenTL v1.4
		*/
		TL_INFO_CHAR_ENCODING	= 8,

		/*!
			@~english	@details	UINT32	Major version number of GenTL Standard Version this Producer complies with.
			@since GenTL v1.5
			@~japanese	@details	UINT32	このプロデューサーが準拠するGenTL規格のメジャーバージョン。
			@since GenTL v1.5
		*/
		TL_INFO_GENTL_VER_MAJOR	= 9,

		/*!
			@~english	@details	UINT32	Minor version number of GenTL Standard Version this Producer complies with.
			@since GenTL v1.5
			@~japanese	@details	UINT32	このプロデューサーが準拠するGenTL規格のマイナーバージョン。
			@since GenTL v1.5
		*/
		TL_INFO_GENTL_VER_MINOR	= 10,

		/*!
			@~english	@details	Starting value for GenTL Producer custom IDs which are implementation specific.
			@~japanese	@details	実装依存のGenTLプロデューサー独自IDの最初の値
		*/
		TL_INFO_CUSTOM_ID		= 1000
	}TL_INFO_CMD, *PTL_INFO_CMD;
	
	/*! 
		@ingroup	GenTL_PublicImple
		@enum	INTERFACE_INFO_CMD
		@~english	@brief	This enumeration defines commands to retrieve information with the IFGetInfo() function from the Interface module or through TLGetInterfaceInfo() .
		@~english	@details	This enumeration defines commands to retrieve information with the IFGetInfo() function from the Interface module or through TLGetInterfaceInfo() .
		@~japanese	@brief	IFGetInfo() および TLGetInterfaceInfo() 関数用インターフェースモジュール情報コマンド
		@~japanese	@details	IFGetInfo() および TLGetInterfaceInfo() 関数用インターフェースモジュール情報コマンド
	*/
	typedef enum INTERFACE_INFO_CMD_LIST
	{

		/*!
			@~english	@details	STRING	Unique ID of the interface.
			@~japanese	@details	STRING	インターフェース固有のID。
		*/
		INTERFACE_INFO_ID			= 0,

		/*!
			@~english	@details	STRING	User readable name of the interface.
			@~japanese	@details	STRING	このインターフェースのユーザーが読み込み可能な名前
		*/
		INTERFACE_INFO_DISPLAYNAME	= 1,

		/*!
			@~english	@details	STRING	Transport layer technology that is supported.
			@~japanese	@details	STRING	このインターフェースがサポートするトランスポート層タイプ。
		*/
		INTERFACE_INFO_TLTYPE		= 2,

		/*!
			@~english	@details	STRING	Starting value for GenTL Producer custom IDs which are implementation specific.
			@~japanese	@details	STRING	実装依存のGenTLプロデューサー独自IDの最初の値
		*/
		INTERFACE_INFO_CUSTOM_ID	= 1000
	}INTERFACE_INFO_CMD, *PINTERFACE_INFO_CMD;
	
	/*! 
		@ingroup	GenTL_PublicImple
		@enum	DEVICE_ACCESS_FLAGS
		@~english	@brief	This enumeration defines flags how a device is to be opened with the IFOpenDevice() function.
		@~english	@details	This enumeration defines flags how a device is to be opened with the IFOpenDevice() function.
		@~japanese	@brief	IFOpenDevice() 関数でデバイス(カメラ)をオープンする際に指定されるアクセスタイプ列挙子
		@~japanese	@details	IFOpenDevice() 関数でデバイス(カメラ)をオープンする際に指定されるアクセスタイプ列挙子
	*/
	typedef enum DEVICE_ACCESS_FLAGS /*DEVICE_ACCESS_FLAGS_LIST*/
	{

		/*!
			@~english	@details	Not used in a command. Can be used to initialize a variable to query that information.
			@~japanese	@details	コマンドでは使用されません。情報問い合わせ時の変数の初期化に使用されます。
		*/
		DEVICE_ACCESS_UNKNOWN	= 0,

		/*!
			@~english	@details	This either means that the device is not open because it was not opened before or the access to it was denied.
			@~japanese	@details	まだオープンされていないか、アクセスが拒否されたことを意味します。
		*/
		DEVICE_ACCESS_NONE		= 1,

		/*!
			@~english	@details	Open the device read only. All Port functions can only read from the device.
			@~japanese	@details	読み込み専用で開きます。すべてのポート関数はデバイスからの読み込みのみ可能です。
		*/
		DEVICE_ACCESS_READONLY	= 2,

		/*!
			@~english	@details	Open the device in a way that other hosts/processes can have read only access to the device. Device access level is read/write for this process.
			@~japanese	@details	他のホスト/プロセスが読み込みのみ可能なようにデバイスを開きます。このプロセスは読み書き可能です。
		*/
		DEVICE_ACCESS_CONTROL	= 3,

		/*!
			@~english	@details	Open the device in a way that only this host/process can have access to the device. Device access level is read/write for this process.
			@~japanese	@details	このホスト/プロセスのみがデバイスにアクセスできるように開きます。このプロセスは読み書き可能です。
		*/
		DEVICE_ACCESS_EXCLUSIVE	= 4,

		/*!
			@~english	@details	Starting value for GenTL Producer custom IDs which are implementation specific.
			@~japanese	@details	実装依存のGenTLプロデューサー独自IDの最初の値
		*/
		DEVICE_ACCESS_CUSTOM_ID	= 1000
	}DEVICE_ACCESS_FLAGS, *PDEVICE_ACCESS_FLAGS;
	
	/*! 
		@ingroup	GenTL_PublicImple
		@enum	DEVICE_ACCESS_STATUS
		@~english	@brief	This enumeration defines values for the accessibility of the device to be returned in the DevGetInfo() function on a device handle.
		@~english	@details	This enumeration defines values for the accessibility of the device to be returned in the DevGetInfo() function on a device handle.
		@~japanese	@brief	DevGetInfo() 関数で取得されるデバイス(カメラ)のアクセス権列挙子
		@~japanese	@details	DevGetInfo() 関数で取得されるデバイス(カメラ)のアクセス権列挙子
	*/
	typedef enum DEVICE_ACCESS_STATUS_LIST
	{
		/*!
			@~english	@details	The current availability of the device is unknown.
			@~japanese	@details	現在のデバイスの使用の可否は不明です。
		*/
		DEVICE_ACCESS_STATUS_UNKNOWN		= 0,

		/*!
			@~english	@details	The device is available to be opened for Read/Write access but it is currently not opened.
			@~english	@attention	This value will only be returned through IFGetDeviceInfo() function because as soon as the device is open DEVICE_ACCESS_STATUS_OPEN_READWRITE will be returned.
			@~japanese	@details	デバイスは読み書きオープン可能ですが、現在はオープンされていません。
			@~japanese	@attention	この値は IFGetDeviceInfo() 関数からのみ返されます。デバイスがオープンされると、 DEVICE_ACCESS_STATUS_OPEN_READWRITE が返されるようになります。
		*/
		DEVICE_ACCESS_STATUS_READWRITE		= 1,

		/*!
			@~english	@details	The device is available to be opened for Read access.
			@~english	@attention	In case the device allows both read and write access the value DEVICE_ACCESS_STATUS_READWRITE has a higher priority. This value will only be returned through IFGetDeviceInfo() function because as soon as the device is open DEVICE_ACCESS_STATUS_OPEN_READONLY will be returned.
			@~japanese	@details	デバイスは読み取りオープン可能です。
			@~japanese	@attention	デバイスの読み書きの両方が可能な場合は、 DEVICE_ACCESS_STATUS_READWRITE が優先されます。この値は IFGetDeviceInfo() 関数からのみ返されます。デバイスがオープンされると、 DEVICE_ACCESS_STATUS_OPEN_READWRITE が返されるようになります。
		*/
		DEVICE_ACCESS_STATUS_READONLY		= 2,

		/*!
			@~english	@details	The device is seen be the producer but is not available for access because it is not reachable.
			@~japanese	@details	デバイスはプロデューサーから見えますが、到達できないため使用できません。
		*/
		DEVICE_ACCESS_STATUS_NOACCESS		= 3,

		/*!
			@~english	@details	The device is already owned/opened by another entity.
			@since GenTL v1.5
			@~japanese	@details	デバイスは既に他で所有/使用されています。
			@since GenTL v1.5
		*/
		DEVICE_ACCESS_STATUS_BUSY			= 4,

		/*!
			@~english	@details	The device is already owned/opened by this GenTL Producer with RW access. A further call to IFOpenDevice() will return GC_ERR_RESOURCE_IN_USE.
			@since GenTL v1.5
			@~japanese	@details	デバイスは既にこのプロデューサーで読み書きアクセスで所有/使用されています。 IFOpenDevice() を再度呼び出すと GC_ERR_RESOURCE_IN_USE が返されます。
			@since GenTL v1.5
		*/
		DEVICE_ACCESS_STATUS_OPEN_READWRITE	= 5,

		/*!
			@~english	@details	The device is already owned/opened by this GenTL Producer with RO access. A further call to IFOpenDevice() will return GC_ERR_RESOURCE_IN_USE.
			@since GenTL v1.5
			@~japanese	@details	デバイスは既にこのプロデューサーで読み取りのみアクセスで所有/使用されています。 IFOpenDevice() を再度呼び出すと GC_ERR_RESOURCE_IN_USE が返されます。
			@since GenTL v1.5
		*/
		DEVICE_ACCESS_STATUS_OPEN_READ		= 6,

		/*!
			@~english	@details	Starting value for custom IDs which are implementation specific.
			@since GenTL v1.5
			@~japanese	@details	実装に依存した独自IDの最初の値です。
			@since GenTL v1.5
		*/
		DEVICE_ACCESS_STATUS_CUSTOM_ID		= 1000
	}DEVICE_ACCESS_STATUS, *PDEVICE_ACCESS_STATUS;

	/*! 
		@ingroup	GenTL_PublicImple
		@enum	DEVICE_INFO_CMD
		@~english	@brief	This enumeration defines commands to retrieve information with the DevGetInfo() function on a device handle.
		@~english	@details	This enumeration defines commands to retrieve information with the DevGetInfo() function on a device handle.
		@~japanese	@brief	DevGetInfo() 関数用デバイス(カメラ)モジュール情報コマンド
		@~japanese	@details	DevGetInfo() 関数用デバイス(カメラ)モジュール情報コマンド
	*/
	typedef enum DEVICE_INFO_CMD_LIST
	{

		/*!
			@~english	@details	STRING	Unique ID of the device.
			@~japanese	@details	STRING	デバイスを特定するID
		*/
		DEVICE_INFO_ID						= 0,

		/*!
			@~english	@details	STRING	Device vendor name.
			@~japanese	@details	STRING	デバイスベンダー名
		*/
		DEVICE_INFO_VENDOR					= 1,

		/*!
			@~english	@details	STRING	Device model name.
			@~japanese	@details	STRING	デバイスモデル名
		*/
		DEVICE_INFO_MODEL					= 2,

		/*!
			@~english	@details	STRING	Transport layer technology that is supported.
			@~japanese	@details	STRING	対応しているトランスポート層タイプ
		*/
		DEVICE_INFO_TLTYPE					= 3,

		/*!
			@~english	@details	STRING	User readable name of the device.
			@~japanese	STRING	デバイスのユーザーが読める名前です。
		*/
		DEVICE_INFO_DISPLAYNAME				= 4,

		/*!
			@~english	@details	INT32	Gets the access status the GenTL Producer has on the device.
			@~japanese	@details	INT32	GenTLプロデューサーのデバイスに対するアクセス権を取得します。
		*/
		DEVICE_INFO_ACCESS_STATUS			= 5,

		/*!
			@~english	@details	STRING	String containing the user defined name of the device. If the information is not available, the query should result in GC_ERR_NOT_AVAILABLE.
			@since GenTL v1.4 
			@~japanese	@details	STRING	デバイスのユーザー定義名。この情報が利用不可の場合、取得時に GC_ERR_NOT_AVAILABLE が返されます。
			@since GenTL v1.4 
		*/
		DEVICE_INFO_USER_DEFINED_NAME		= 6,

		/*!
			@~english	@details	STRING	Serial number of the device in string format. If the information is not available, the query should result in GC_ERR_NOT_AVAILABLE.
			@since GenTL v1.4 
			@~japanese	@details	STRING	デバイスのシリアル番号文字列。この情報が利用不可の場合、取得時に GC_ERR_NOT_AVAILABLE が返されます。
			@since GenTL v1.4 
		*/
		DEVICE_INFO_SERIAL_NUMBER			= 7,

		/*!
			@~english	@details	STRING	Device version in string format. If the information is not known, the query should result in GC_ERR_NOT_AVAILABLE.
			@since GenTL v1.4 
			@~japanese	@details	STRING	デバイスのバージョン文字列。この情報が利用不可の場合、取得時に GC_ERR_NOT_AVAILABLE が返されます。
			@since GenTL v1.4 
		*/
		DEVICE_INFO_VERSION					= 8,

		/*!
			@~english	@details	UINT64	Tick frequency of the device's timestamp counter in ticks per second. The counter is used for example to assign timestamps to the individual acquired buffers (BUFFER_INFO_TIMESTAMP).
			@since GenTL v1.4 
			@~japanese	@details	UINT64	デバイスのタイムスタンプ用カウンターの1秒間のカウント値。カウンターは取得された個々のバッファーのタイムスタンプ(BUFFER_INFO_TIMESTAMP)などに使用されます。
			@since GenTL v1.4 
		*/
		DEVICE_INFO_TIMESTAMP_FREQUENCY		= 9,

		/*!
			@~english	@details	Starting value for GenTL Producer custom IDs which are implementation specific.
			@~japanese	@details	実装依存の独自IDの最初の値
		*/
		DEVICE_INFO_CUSTOM_ID				= 1000
	}DEVICE_INFO_CMD, *PDEVICE_INFO_CMD;
	
	/*! 
		@ingroup	GenTL_PublicImple
		@enum	ACQ_STOP_FLAGS
		@~english	@brief	This enumeration defines special stop flags for the acquisition engine. The function used is DSStopAcquisition() .
		@~english	@details	This enumeration defines special stop flags for the acquisition engine. The function used is DSStopAcquisition() .
		@~japanese	@brief	DSStopAcquisition() 関数用取り込みエンジンストップフラグ
		@~japanese	@details	DSStopAcquisition() 関数用取り込みエンジンストップフラグ
	*/
	typedef enum ACQ_STOP_FLAGS /*ACQ_STOP_FLAGS_LIST*/
	{

		/*!
			@~english	@details	Stops the acquisition engine when the currently running tasks like filling a buffer are completed (default behavior).
			@~japanese	@details	1つのバッファへの受信完了のような現在行われているタスクが完了した時点で、取り込みを停止します(デフォルトのふるまい)。
		*/
		ACQ_STOP_FLAGS_DEFAULT				= 0,

		/*!
			@~english	@details	Stop the acquisition engine immediately. 
			@~english	@attention	In case this results in a partially filled buffer the Producer will return the buffer through the regular mechanism to the user, indicating through the info function of that buffer that this buffer is not complete.
			@~japanese	@details	取り込みを直ちに停止します。
			@~japanese	@attention	この結果として部分的に埋められたバッファがプロデューサーから通常通りユーザーへ返されます。情報取得関数によりバッファが未完了であることがわかります。
		*/
		ACQ_STOP_FLAGS_KILL					= 1,

		/*!
			@~english	@details	Starting value for GenTL Producer custom IDs which are implementation specific.
			@~japanese	@details	実装依存の独自IDの最初の値
		*/
		ACQ_STOP_FLAGS_CUSTOM_ID			= 1000
	}ACQ_STOP_FLAGS, *PACQ_STOP_FLAGS;

	/*! 
		@ingroup	GenTL_PublicImple
		@enum	ACQ_START_FLAGS
		@~english	@brief	This enumeration defines special start flags for the acquisition engine. The function used is DSStartAcquisition() .
		@~english	@details	This enumeration defines special start flags for the acquisition engine. The function used is DSStartAcquisition() .
		@~japanese	@brief	DSStartAcquisition() 関数用取り込みエンジンスタートフラグ
		@~japanese	@details	DSStartAcquisition() 関数用取り込みエンジンスタートフラグ
	*/
	typedef enum ACQ_START_FLAGS /* ACQ_START_FLAGS_LIST */
	{

		/*!
			@~english	@details	Default behavior.
			@~japanese	@details	デフォルトのふるまい
		*/
		ACQ_START_FLAGS_DEFAULT			= 0,

		/*!
			@~english	@details	Starting value for GenTL Producer custom IDs.
			@~japanese	@details	実装依存の独自IDの最初の値
		*/
		ACQ_START_FLAGS_CUSTOM_ID		= 1000
	}ACQ_START_FLAGS, *PACQ_START_FLAGS;
	
	/*! 
		@ingroup	GenTL_PublicImple
		@enum	ACQ_QUEUE_TYPE
		@~english	@brief	This enumeration commands define from which to which queue/pool buffers are flushed with the DSFlushQueue() function.
		@~english	@details	This enumeration commands define from which to which queue/pool buffers are flushed with the DSFlushQueue() function.
		@~japanese	@brief	DSFlushQueue() 関数用フラッシュバッファ指定列挙子
		@~japanese	@details	DSFlushQueue() 関数用フラッシュバッファ指定列挙子
	*/
	typedef enum ACQ_QUEUE_TYPE_LIST
	{

		/*!
			@~english	@details	Flushes the buffers from the input pool to the output buffer queue and if necessary adds entries in the "New Buffer" event data queue. The buffers currently being filled are not affected by this operation. This only applies to the mandatory default buffer handling mode. The fill state of a buffer can be inquired through the buffer info command BUFFER_INFO_NEW_DATA. This allows the GenTL Consumer to maintain all buffers without a second reference in the GenTL Consumer because all buffers are delivered through the new buffer event.
			@~japanese	@details	バッファを入力プールから出力キューへ移動し、必要に応じて「New Buffer」イベントデータキューへエントリーを追加します。まだ転送が完了しきっていないバッファもこの操作の影響をうけます。これは対応が必須のデフォルトのモードです。バッファにデータが入れられたかどうかは BUFFER_INFO_NEW_DATA で確認できます。それによりGenTLコンシュマーはすべてのバッファを 「New Buffer」イベントで受け取ることができます。
		*/
		ACQ_QUEUE_INPUT_TO_OUTPUT			= 0,

		/*!
			@~english	@details	Discards all buffers in the output buffer queue and if necessary remove the entries from the event data queue.
			@~japanese	@details	出力キューのすべてのバッファを破棄し、必要に応じてイベントデータキューのテントりーも削除します。
		*/
		ACQ_QUEUE_OUTPUT_DISCARD			= 1,

		/*!
			@~english	@details	Puts all buffers in the input pool. This is including those in the output buffer queue and the ones which are currently being filled and discard entries in the event data queue.
			@~japanese	@details	すべてのバッファを入力プールへ移動します。これには出力キューや現在データを受信中のバッファも含まれ、イベントデータキューのエントリーも削除されます。
		*/
		ACQ_QUEUE_ALL_TO_INPUT				= 2,

		/*!
			@~english	@details	Puts all buffers that are neither in the input pool nor being currently filled nor in the output buffer queue in the input pool.
			@~japanese	@details	入力プールや出力キューになく、現在受信中でもないバッファを入力プールへ移動します。
		*/
		ACQ_QUEUE_UNQUEUED_TO_INPUT			= 3,
		/*!
			@~english	@details	Discards all buffers in the input pool and the buffers in the output queue including buffers currently being filled so that no buffer is bound to any internal mechanism and all buffers may be revoked or requeued.
			@~japanese	@details	入力プールや出力キューにあるバッファおよび現在受信中のバッファを含むすべてのバッファを破棄し、内部には保持されているバッファは全くない状態にします。
		*/
		ACQ_QUEUE_ALL_DISCARD				= 4,

		/*!
			@~english	@details	Starting value for GenTL Producer custom IDs which are implementation specific.
			@~japanese	@details	実装依存の独自IDの最初の値
		*/
		ACQ_QUEUE_CUSTOM_ID					= 1000
	}ACQ_QUEUE_TYPE, *PACQ_QUEUE_TYPE;

	/*! 
		@ingroup	GenTL_PublicImple
		@enum	STREAM_INFO_CMD
		@~english	@brief	This enumeration defines commands to retrieve information with the DSGetInfo() function on a data stream handle.
		@~english	@details	This enumeration defines commands to retrieve information with the DSGetInfo() function on a data stream handle.
		@~japanese	@brief	DSGetInfo() 関数用データストリームモジュール情報コマンド
		@~japanese	@details	DSGetInfo() 関数用データストリームモジュール情報コマンド
	*/
	typedef enum STREAM_INFO_CMD_LIST
	{
		/*!
			@~english	@details	STRING	Unique ID of the data stream.
			@~japanese	@details	STRING	データストリームを特定するID
		*/
		STREAM_INFO_ID					= 0,

		/*!
			@~english	@details	UINT64	Number of delivered buffers since last acquisition start.
			@~japanese	@details	UINT64	最後の取り込み開始後に受け取ったバッファの数
		*/
		STREAM_INFO_NUM_DELIVERED		= 1,

		/*!
			@~english	@details	UINT64	Number of lost frames due to queue underrun. This number is initialized with zero at the time the stream is opened and incremented every time the data could not be acquired because there was no buffer in the input pool.
			@~japanese	@details	UINT64	キューのアンダーランにより失われたフレームの数。数値はストリームがオープンされたときに0に初期化され、入力プールにバッファがないためにデータを取得できなくなるたびにカウントされます。
		*/
		STREAM_INFO_NUM_UNDERRUN		= 2,

		/*!
			@~english	@details	SIZET	Number of announced buffers.
			@~japanese	@details	SIZET	データストリームに登録されたバッファの数
		*/
		STREAM_INFO_NUM_ANNOUNCED		= 3,

		/*!
			@~english	@details	SIZET	Number of buffers in the input pool plus the buffer(s) currently being filled. This does not include the buffers in the output queue.The intention of this informational value is to prevent / early detect an underrun of the acquisition buffers.
			@~japanese	@details	SIZET	入力プールおよび現在データが入れられているバッファの数。出力キューにあるバッファは含まれません。この情報は取り込みバッファのアンダーランの防止および早期検出に使用されます。
		*/
		STREAM_INFO_NUM_QUEUED			= 4,

		/*!
			@~english	@details	SIZET	Number of buffers in the output buffer queue.
			@~japanese	@details	SIZET	出力キューにあるバッファの数
		*/
		STREAM_INFO_NUM_AWAIT_DELIVERY	= 5,

		/*!
			@~english	@details	UINT64	Number of frames started in the acquisition engine. This number is incremented every time a new buffer is started to be filled(data written to) regardless if the buffer is later delivered to the user or discarded for any reason.This number is initialized with 0 at at the time of the stream is opened.It is not reset until the stream is closed.
			@~japanese	@details	UINT64	取り込みが開始されたフレームの数。この数は後でユーザーへ渡されたか、何らかの理由で破棄されたかは関係なく、バッファへの書き込みが開始されるたびにカウントされます。この数はストリームがオープンされると0に初期化されま、ストリームが閉じられるまではリセットされません。
		*/
		STREAM_INFO_NUM_STARTED			= 6,

		/*!
			@~english	@details	SIZET	Size of the expected data in bytes.
			@~japanese	@details	SIZET	予想されるデータのバイト単位のサイズ
		*/
		STREAM_INFO_PAYLOAD_SIZE		= 7,

		/*!
			@~english	@details	BOOL8	Flag indicating whether the acquisition engine is started or not.This is independent from the acquisition status of the remote device.
			@~japanese	@details	BOOL8	(ホスト側の)取り込み処理が開始されているかどうかを表します。これは(リモート)デバイスの状態には依存しません。
		*/
		STREAM_INFO_IS_GRABBING			= 8,

		/*!
			@~english	@details	BOOL8	Flag indicating that this data stream defines a payload size independent from the remote device.If false the size of the expected payload size is to be retrieved from the remote device.If true the expected payload size is to be inquired from the Data Stream module.In case the GenTL Producer does not support this command it is to interpreted as false.
			@~japanese	@details	BOOL8	ペイロードサイズがデータストリームモジュールから取得できることを表します。 false の場合、ペイロードサイズは(リモート)デバイスから取得します。
		*/
		STREAM_INFO_DEFINES_PAYLOADSIZE	= 9,

		/*!
			@~english	@details	STRING	Transport layer technology that is supported.
			@~japanese	@details	STRING	対応しているトランスポート層タイプ
		*/
		STREAM_INFO_TLTYPE				= 10,

		/*!
			@~english	@details	SIZET	Maximum number of chunks to be expected in a buffer(can be used to allocate the array for the DSGetBufferChunkData() function).In case this is not known a priori by the GenTL Producer the DSGetInfo() function returns GC_ERR_NOT_AVAILABLE.This maximum must not change during runtime.
			@since GenTL v1.3
			@~japanese	@details	SIZET	バッファに含まれると予想されるチャンクの数の最大値。この値は DSGetBufferChunkData() 関数用の配列の割り当てに使用されます。GenTLプロデューサーが事前に把握できない場合、 DSGetInfo() は GC_ERR_NOT_AVAILABLE を返します。この最大値は動作中には変化しません。
			@since GenTL v1.3
		*/
		STREAM_INFO_NUM_CHUNKS_MAX		= 11,

		/*!
			@~english	@details	SIZET	Minimum number of buffers to announce.In case this is not known a priori by the GenTL Producer the DSGetInfo() function returns a GC_ERR_NOT_AVAILABLE error. This minimum may change during runtime when changing parameters through the node map.
			@since GenTL v1.3
			@~japanese	@details	SIZET	取り込みを開始するのに必要なバッファの最小の数。GenTLプロデューサーが事前に把握できない場合、 DSGetInfo() 関数は GC_ERR_NOT_AVAILABLE エラーを返します。この最小値はノードマップを通したパラメータ変更により動的に変化する可能性があります。
			@since GenTL v1.3
		*/
		STREAM_INFO_BUF_ANNOUNCE_MIN	= 12,

		/*!
			@~english	@details	SIZET	Alignment size in bytes of the buffer passed to DSAnnounceBuffer(). If a buffer is passed to DSAnnounceBuffer() which is not aligned according to the alignment size it is up to the Producer to either reject the buffer and return the GC_ERR_INVALID_BUFFER error code or to cope with a potential overhead and use the unaligned buffer as is.In case there is no special alignment needed the GenTL Producer should report a 1.
			@since GenTL v1.3
			@~japanese	@details	SIZET	DSAnnounceBuffer() で渡されるバッファのバイト単位のアライメントサイズ。アライメントサイズに合っていないバッファが DSAnnounceBuffer() でw足された場合、GenTLプロデューサーは、拒否して GC_ERR_INVALID_BUFFER エラーを返すか、オーバーヘッドの可能性を含みつつアライメントされていないバッファに対処します。GenTLプロデューサーが特別なアライメントを必要としない場合は1が返されます。
			@since GenTL v1.3
		*/
		STREAM_INFO_BUF_ALIGNMENT		= 13,

		/*!
			@~english	@details	Starting value for GenTL Producer custom IDs which are implementation specific.
			@~japanese	@details	実装依存の独自IDの最初の値
		*/
		STREAM_INFO_CUSTOM_ID			= 1000
	}STREAM_INFO_CMD, *PSTREAM_INFO_CMD;

	/*! 
		@ingroup	GenTL_PublicImple
		@enum	BUFFER_INFO_CMD
		@~english	@brief	This enumeration defines commands to retrieve information with the DSGetBufferInfo() function on a buffer handle.
		@~english	@details	This enumeration defines commands to retrieve information with the DSGetBufferInfo() function on a buffer handle.
		@~japanese	@brief	DSGetBufferInfo() 関数用バッファモジュール情報コマンド
		@~japanese	@details	DSGetBufferInfo() 関数用バッファモジュール情報コマンド
	*/
	typedef enum BUFFER_INFO_CMD_LIST
	{

		/*!
			@~english	@details	PTR	Base address of the buffer memory as passed to the DSAnnounceBuffer() function.This is also the address where the payload within the buffer starts.
			@~japanese	@details	PTR	DSAnnounceBuffer() 関数へ渡されたバッファメモリーのベースアドレス。これはバッファ内のペイロードデータの開始するアドレスでもあります。
		*/
		BUFFER_INFO_BASE					= 0,

		/*!
			@~english	@details	SIZET	Size of the buffer in bytes.
			@~japanese	@details	SIZET	バイト単位のバッファのサイズ
		*/
		BUFFER_INFO_SIZE					= 1,

		/*!
			@~english	@details	PTR	Private data pointer casted to an integer provided at buffer announcement using DSAnnounceBuffer() or DSAllocAndAnnounceBuffer() by the GenTL Consumer.The pointer is attached to the buffer to allow attachment of user data to a buffer.
			@~japanese	@details	PTR DSAnnounceBuffer() 関数または DSAllocAndAnnounceBuffer() 関数を使ってGenTLコンシュマーから渡された整数にキャストされたプライベートデータへのポインターです。このポインターによりユーザーデータをバッファへ付随させることができます。
		*/
		BUFFER_INFO_USER_PTR				= 2,

		/*!
			@~english	@details	UINT64	Timestamp the buffer was acquired. The unit is device / implementation dependent.
			@~japanese	UINT64	バッファのタイムスタンプ値です。単位はデバイスや実装に依存します。
		*/
		BUFFER_INFO_TIMESTAMP				= 3,

		/*!
			@~english	@details	BOOL8	Flag to indicate that the buffer contains new data since the last delivery.
			@~japanese	@details	BOOL8	前の受信以後に受け取った新しいデータが含まれていることを示すフラグです。
		*/
		BUFFER_INFO_NEW_DATA				= 4,

		/*!
			@~english	@details	BOOL8	If this flag is set to true the buffer is in the input pool, the buffer is currently being filled or the buffer is in the output buffer queue.In case this value is true the buffer is owned by the GenTL Producer and it can not be revoked.
			@~japanese	@details	BOOL8	このフラグが true のとき、バッファは入力プールにあるか、バッファはデータが入れられようとしているか、出力キューにあります。この値が true の場合、バッファはGenTLプロデューサーに所有されているため破棄できません。
		*/
		BUFFER_INFO_IS_QUEUED				= 5,

		/*!
			@~english	@details	BOOL8	Flag to indicate that the buffer is currently being filled with data.
			@~japanese	@details	BOOL8	現在バッファにデータが入れられていることを表します。
		*/
		BUFFER_INFO_IS_ACQUIRING			= 6,

		/*!
			@~english	@details	BOOL8	Flag to indicate that a buffer was filled but an error occurred during that process.
			@~japanese	@details	BOOL8	バッファ入っているデータが、エラー等により不完全であることを表します。
		*/
		BUFFER_INFO_IS_INCOMPLETE			= 7,

		/*!
			@~english	@details	STRING	Transport layer technology that is supported.
			@~japanese	@details	STRING	サポートされているトランスポート層タイプ
		*/
		BUFFER_INFO_TLTYPE					= 8,

		/*!
			@~english	@details	SIZET	Number of bytes written into the buffer the last time it has been filled.This value is reset to 0 when the buffer is placed into the Input Buffer Pool. If the buffer is incomplete(such as if there are missing packets), only the number of bytes successfully written to the buffer are reported.If the buffer is complete, the number equals to the size reported through BUFFER_INFO_DATA_SIZE.
			@~japanese	@details	SIZET	最後にこのバッファへ入れられたデータのバイト単位のサイズです。この値はバッファが入力プールに入れられるとき0にリセットされます。バッファが不完全(喪失されたパケットがあるなど)の場合、バッファへ書き込みに成功したバイト単位のサイズが報告されます。バッファが完全の場合、 BUFFER_INFO_DATA_SIZE と同じ値になります。
		*/
		BUFFER_INFO_SIZE_FILLED				= 9,

		/*!
			@~english	@details	SIZET	Width of the data in the buffer in number of pixels.
			@since GenTL v1.2
			@~japanese	@details	SIZET	バッファ内のデータの横方向のピクセル数です。
			@since GenTL v1.2
		*/
		BUFFER_INFO_WIDTH					= 10,

		/*!
			@~english	@details	SIZET	Height of the data in the buffer in number of pixels as configured. For variable size images this is the maximum height of the buffer.
			@since GenTL v1.2
			@~japanese	@details	SIZET	バッファ内のデータの設定された縦方向のピクセル数です。縦サイズが変化する画像に対しては、バッファの最大縦サイズになります。
			@since GenTL v1.2
		*/
		BUFFER_INFO_HEIGHT					= 11,

		/*!
			@~english	@details	SIZET	XOffset of the data in the buffer in number of pixels from the image origin to handle areas of interest.
			@since GenTL v1.2
			@~japanese	@details	SIZET	元の画像データに対するバッファ内の画像データの横方向のオフセット値です。
			@since GenTL v1.2
		*/
		BUFFER_INFO_XOFFSET					= 12,

		/*!
			@~english	@details	SIZET	YOffset of the data in the buffer in number of lines from the image origin to handle areas of interest.
			@since GenTL v1.2
			@~japanese	@details	SIZET	元の画像データに対するバッファ内の画像データの縦方向のオフセット値です。
			@since GenTL v1.2
		*/
		BUFFER_INFO_YOFFSET					= 13,

		/*!
			@~english	@details	SIZET	XPadding of the data in the buffer in number of bytes.
			@since GenTL v1.2
			@~japanese	@details	SIZET	バッファ内のデータの横方向のバイト単位のパッディング値です。
			@since GenTL v1.2
		*/
		BUFFER_INFO_XPADDING				= 14,

		/*!
			@~english	@details	SIZET	YPadding of the data in the buffer in number of lines.
			@since GenTL v1.2
			@~japanese	@details	SIZET	バッファ内のデータの縦方向のライン単位のパッディング値です。
			@since GenTL v1.2
		*/
		BUFFER_INFO_YPADDING				= 15,

		/*!
			@~english	@details	UINT64	A sequentially incremented number of the frame.
			@since GenTL v1.2
			@~japanese	@details	UINT64	フレームの連番です。 GigEVisionやUSB3VisionではブロックIDに対応します。
			@since GenTL v1.2
		*/
		BUFFER_INFO_FRAMEID					= 16,

		/*!
			@~english	@details	BOOL8	Flag to indicate if the current data in the buffer contains image data.
			@since GenTL v1.2
			@~japanese	@details	BOOL8	バッファに画像データが含まれるかどうかを表します。
			@since GenTL v1.2
		*/
		BUFFER_INFO_IMAGEPRESENT			= 17,

		/*!
			@~english	@details	SIZET	Offset of the image data from the beginning of the delivered buffer in bytes.
			@since GenTL v1.2
			@~japanese	@details	SIZET	画像データのバッファ内の位置をバイト単位で表します。
			@since GenTL v1.2
		*/
		BUFFER_INFO_IMAGEOFFSET				= 18,

		/*!
			@~english	@details	SIZET	Payload type of the data.
			@sa	PAYLOADTYPE_INFO_IDS
			@since GenTL v1.2
			@~japanese	@details	SIZET	データのペイロードタイプです。
			@sa	PAYLOADTYPE_INFO_IDS
			@since GenTL v1.2
		*/
		BUFFER_INFO_PAYLOADTYPE				= 19,

		/*!
			@~english	@details	UINT64	Pixelformat of the data.
			@sa	BUFFER_INFO_PIXELFORMAT_NAMESPACE
			@since GenTL v1.2
			@~japanese	@details	UINT64	ピクセルフォーマット
			@sa	BUFFER_INFO_PIXELFORMAT_NAMESPACE
			@since GenTL v1.2
		*/
		BUFFER_INFO_PIXELFORMAT				= 20,

		/*!
			@~english	@details	UINT64 This information refers to the constants defined in PIXELFORMAT_NAMESPACE_IDs to allow interpretation of BUFFER_INFO_PIXELFORMAT.
			@sa	BUFFER_INFO_PIXELFORMAT, PIXELFORMAT_NAMESPACE_ID
			@since GenTL v1.2
			@~japanese	@details	UINT64	BUFFER_INFO_PIXELFORMAT の解釈に使用されるピクセルフォーマットネームスペース情報です。
			@sa	BUFFER_INFO_PIXELFORMAT, PIXELFORMAT_NAMESPACE_ID
			@since GenTL v1.2
		*/
		BUFFER_INFO_PIXELFORMAT_NAMESPACE	= 21,

		/*!
			@~english	@details	SIZET	The number of lines in the current buffer as delivered by the transport mechanism.
			@~english	@attention	For area scan type images this is usually the number of lines configured in the device.For variable size linescan images this number may be lower than the configured image height.
			@since GenTL v1.2
			@~japanese	@details	SIZET	受信した画像データの縦サイズです。
			@~japanese	@attention	エリアスキャンカメラの画像はたいてい設定されたライン数になります。ラインスキャンカメラの画像は設定されたライン数より少なくなることがあります。
			@since GenTL v1.2
		*/
		BUFFER_INFO_DELIVERED_IMAGEHEIGHT	= 22,

		/*!
			@~english	@details	SIZET	The chunk payloadsize size.
			@since GenTL v1.2
			@~japanese	@details	SIZET	チャンクを含むペイロードデータのサイズ
			@since GenTL v1.2
		*/
		BUFFER_INFO_DELIVERED_CHUNKPAYLOADSIZE	= 23,

		/*!
			@~english	@details	UINT64	The chunk layout id serves as an indicator that the chunk layout has changed and the application should reparse the chunk layout in the buffer.
			@since GenTL v1.2
			@~japanese	@details	UINT64	バッファ内のチャンクデータのレイアウト識別用のIDです。このIDが同じ場合、個々のチャンクデータの位置も変わりません。
			@since GenTL v1.2
		*/
		BUFFER_INFO_CHUNKLAYOUTID			= 24,

		/*!
			@~english	@details	STRING	Filename in case the payload contains a file. 
			@since GenTL v1.2
			@~japanese	@details	STRING	ペイロードに含まれるファイルのファイル名です。
			@since GenTL v1.2
		*/
		BUFFER_INFO_FILENAME				= 25,

		/*!
			@~english	@details	INT32	Endianness of the multi-byte pixel data in the buffer.
			@sa PIXELENDIANNESS_ID
			@since GenTL v1.4
			@~japanese	@details	INT32	バッファ内のマルチバイトピクセルデータのエンディアンを表します。
			@sa PIXELENDIANNESS_ID
			@since GenTL v1.4
		*/
		BUFFER_INFO_PIXEL_ENDIANNESS		= 26,

		/*!
			@~english	@details	SIZET	Size of the data intended to be written to the buffer last time it has been filled. This value is reset to 0 when the buffer is placed into the Input Buffer Pool. If the buffer is incomplete the number still reports the full size of the original data including the lost parts. If the buffer is complete, the number equals to the size reported through BUFFER_INFO_SIZE_FILLED.
			@sa BUFFER_INFO_SIZE_FILLED
			@since GenTL v1.4
			@~japanese	@details	SIZET	バッファに最後に書き込まれたデータのサイズです。この値はバッファを入力プールに入れた時に0へリセットされます。バッファが不完全な時も、失われた部分も含む元のサイズを返します。バッファが完全な時は BUFFER_INFO_SIZE_FILLED で返される値と等しくなります。
			@sa BUFFER_INFO_SIZE_FILLED
			@since GenTL v1.4
		*/
		BUFFER_INFO_DATA_SIZE				= 27,

		/*!
			@~english	@details	UINT64	Timestamp the buffer was acquired, in units of 1 ns (1,000,000,000 ticks per second).
			@since GenTL v1.4
			@~japanese	@details	UINT64	バッファのns単位のタイムスタンプ値です。
			@since GenTL v1.4
		*/
		BUFFER_INFO_TIMESTAMP_NS			= 28,

		/*!
			@~english	@details	BOOL8	If this values is set to true it indicates that the payload transferred would not fit into the announced buffer and that therefore only parts of the payload or no payload (depending on the implementation of the GenTL Producer) is copied into the buffer.
			@since GenTL v1.4
			@~japanese	@details	BOOL8	この値が true 場合、転送されたペイロードデータは渡されたバッファに合っていません。データの一部分のみコピーされるか、全くコピーされないかはGenTLプロデューサーの実装に依存します。
			@since GenTL v1.4
		*/
		BUFFER_INFO_DATA_LARGER_THAN_BUFFER	= 29,

		/*!
			@~english	@details	BOOL8	If this values is set to true it indicates that the payload transferred contains chunk data.
			@since GenTL v1.4
			@~japanese	@details	BOOL8	この値が true 場合、転送されたペイロードデータにチャンクデータが含まれます。
			@since GenTL v1.4
		*/
		BUFFER_INFO_CONTAINS_CHUNKDATA		= 30,

		/*!
			@~english	@details	Starting value for GenTL Producer custom IDs which are implementation specific.
			@~japanese	@details	実装依存の独自IDの最初の値
		*/
		BUFFER_INFO_CUSTOM_ID				= 1000
	}BUFFER_INFO_CMD, *PBUFFER_INFO_CMD;

	/*! 
		@ingroup	GenTL_PublicImple
		@enum	BUFFER_PART_INFO_CMD
		@~english	@brief	This enumeration defines commands to retrieve information with the DSGetBufferPartInfo() function on a buffer handle.
		@~english	@details	This enumeration defines commands to retrieve information with the DSGetBufferPartInfo() function on a buffer handle.
		@~english	@attention	In case a BUFFER_PART_INFO_CMD is not available or not implemented the DSGetBufferPartInfo() function must return the appropriate error return value.
		@since GenTL v1.5
		@~japanese	@brief	DSGetBufferPartInfo() 関数用バッファーパート情報コマンド
		@~japanese	@details	DSGetBufferPartInfo() 関数用バッファーパート情報コマンド
		@~japanese	@attention	BUFFER_PART_INFO_CMD が使用できないまたは実装されていない場合、 DSGetBufferPartInfo() 関数は適切なエラー値を返す必要があります。
		@since GenTL v1.5
	*/
	typedef enum BUFFER_PART_INFO_CMD_LIST
	{
		/*!
			@~english	@details	PTR	Base address of the buffer part memory.This is the address where the valid buffer part data start, not considering any padding between data parts or buffer alignment.
			@since GenTL v1.5
			@~japanese	@details	PTR	バッファパートのベースアドレスです。有効なデータパートの開始位置で、データパート間のパッディングやアライメントは考慮されていません。
			@since GenTL v1.5
		*/
		BUFFER_PART_INFO_BASE					= 0,
		BUFFER_PART_INFO_DATA_SIZE				= 1,	/*!< SIZET	Size of the buffer part in bytes. Actual size of the data within this buffer part should be reported. Eventual padding between buffer parts is not included.In case of variable payload type only the size of valid data within the buffer part is reported. */
		BUFFER_PART_INFO_DATA_TYPE				= 2,	/*!< SIZET	Type of the data in given part. This information refers to the constants defined in PARTDATATYPE_IDs. */
		BUFFER_PART_INFO_DATA_FORMAT			= 3,	/*!< UINT64 Format of the individual items (such as pixels) in the buffer part. The interpretation of the format is specific to every data type (BUFFER_PART_INFO_DATA_TYPE), as specified in definitions of individual PARTDATATYPE_IDS. The actual meaning of the data format depends on the namespace the format belongs to which can be inquired using the BUFFER_PART_INFO_DATA_FORMAT_NAMESPACE command(although for the standard PARTDATATYPE_IDS a recommended data format namespace is always specified). */
		BUFFER_PART_INFO_DATA_FORMAT_NAMESPACE	= 4,	/*!< UINT64	This information refers to the constants defined in PIXELFORMAT_NAMESPACE_IDS to allow interpretation of BUFFER_PART_INFO_DATA_FORMAT. */
		BUFFER_PART_INFO_WIDTH					= 5,	/*!< SIZET	Width of the data in the buffer part in	number of pixels. If the information is not applicable to given data type, the query should result in GC_ERR_NOT_AVAILABLE. */
		BUFFER_PART_INFO_HEIGHT					= 6,	/*!< SIZET	Height of the data in the buffer part in number of pixels. If the information is not applicable to given data type, the query should result in GC_ERR_NOT_AVAILABLE. */
		BUFFER_PART_INFO_XOFFSET				= 7,	/*!< SIZET	XOffset of the data in the buffer part in number of pixels from the image origin to handle areas of interest. If the information is not applicable to given data type, the query should result in GC_ERR_NOT_AVAILABLE. */
		BUFFER_PART_INFO_YOFFSET				= 8,	/*!< SIZET	YOffset of the data in the buffer part in number of pixels from the image origin to handle areas of interest. If the information is not applicable to given data type, the query should result in GC_ERR_NOT_AVAILABLE. */
		BUFFER_PART_INFO_XPADDING				= 9,	/*!< SIZET	XPadding of the data in the buffer part in number of pixels. If the information is not applicable to given data type, the query should result in GC_ERR_NOT_AVAILABLE. */
		BUFFER_PART_INFO_SOURCE_ID				= 10,	/*!< UINT64	Identifier allowing to group data parts belonging to the same source(usually corresponding with the SourceSelector / ChunkSourceID features from SFNC).Parts marked with the same source_id can be pixelmapped together.Parts carrying data from different ROI's of the same source would typically be marked with the same source_id. It is not mandatory that source_id's within a given buffer make a contiguous sequence of numbers starting with zero. Note: for example with a dual - source 3D camera, the buffer can contain data parts carrying the 3D data and Confidence data corresponding to both of the two different sources.In this case the source ID helps to match the 3D and Confidence parts belonging together. This information refers for example to the information provided in the GigE Vision image stream multi - part data leader. */
		BUFFER_PART_INFO_DELIVERED_IMAGEHEIGHT	= 11,	/*!< SIZET	The number of lines in the current buffer part as delivered by the transport mechanism. For area scan type images this is usually the number of lines configured in the device. For variable size linescan images this number may be lower than the configured image height. This information refers for example to the information provided in the GigE Vision image stream data trailer. For other technologies this is to be implemented accordingly. */
		
		/*!
			@~english	@details	Starting value for GenTL Producer custom IDs which are implementation specific.
			@~japanese	@details	実装依存の独自IDの最初の値
		*/
		BUFFER_PART_INFO_CUSTOM_ID				= 1000
	}BUFFER_PART_INFO_CMD, *PBUFFER_PART_INFO_CMD;

	/*! 
		@ingroup	GenTL_PublicImple
		@enum	PAYLOADTYPE_INFO_ID
		@~english	@brief	This enumeration defines constants to give a hint on the payload type to be expected in the	buffer.
		@~english	@details	This enumeration defines constants to give a hint on the payload type to be expected in the	buffer.
		@since GenTL GenTL v1.2
		@~japanese	@brief	ペイロードタイプ列挙子
		@~japanese	@details	ペイロードタイプ列挙子
		@since GenTL GenTL v1.2
	*/
	typedef enum PAYLOADTYPE_INFO_IDS
	{
		/*!
			@~english	@details	The GenTL Producer is not aware of the	payload type of the data in the provided buffer. For the GenTL Consumer perspective this can be handled as raw data.
			@since GenTL v1.2
			@~japanese	@details	提供されたバッファ内のデータのペイロードタイプが不明です。
			@since GenTL v1.2
		*/
		PAYLOAD_TYPE_UNKNOWN			= 0,

		/*!
			@~english	@details	The buffer payload contains image data. The GenTL Consumer can check if additional chunk data is available via the BUFFER_INFO commands.
			@since GenTL v1.2
			@~japanese	@details	バッファのペイロードデータには画像データが含まれています。追加でチャンクデータがあるかどうかは BUFFER_INFO コマンドで確認できます。
			@since GenTL v1.2
		*/
		PAYLOAD_TYPE_IMAGE				= 1,

		/*!
			@~english	@details	The buffer payload contains raw and further unspecified data.This can be used to send acquisition statistics.
			@since GenTL v1.2
			@~japanese	@details	バッファのペイロードデータには生の特定できないデータが含まれています。
			@since GenTL v1.2
		*/
		PAYLOAD_TYPE_RAW_DATA			= 2,

		/*!
			@~english	@details	The buffer payload contains data of a file. It is used to transfer files such as JPEG compressed images which can be stored by the GenTL Producer directly to a hard disk.The user might get a hint how to interpret the buffer by the filename provided through a call to DSGetBufferInfo() with the command BUFFER_INFO_FILENAME.
			@since GenTL v1.2
			@~japanese	@details	バッファのペイロードデータにはファイルのデータが含まれています。これはGenTLプロデューサーによって直接ハードディスクへ保存できるJPEG圧縮画像のようなファイルの転送に使用されます。ユーザーはバッファをどのように解釈したらよいかのヒントを BUFFER_INFO_FILENAME を指定した DSGetBufferInfo() 関数の呼び出しにより得られるかもしれません。
			@since GenTL v1.2
		*/
		PAYLOAD_TYPE_FILE				= 3,

		/*!
			@~english	@details	The buffer payload contains chunk data which can be parsed.The chunk data type might be reported through SFNC or deduced from the technology the device is based on.This constant is for backward compatibility with GEV 1.2 and is deprecated since GenTL version 1.5.From now on ChunkData can be part or any other payload type.Use the BUFFER_INFO_CONTAINS_CHUNKDATA commads to query if a given buffer content contains chunk data.
			@since GenTL v1.2
			@deprecated GenTL 1.5
			@~japanese	@details	バッファのペイロードデータには解析可能なチャンクデータが含まれています。この値はGigEVison1.2の後方互換性のためにあり、GenTL 1.5では非推奨となっており、チャンクデータは他のペイロードタイプの一部となっています。バッファにチャンクデータが含まれるか否かは BUFFER_INFO_CONTAINS_CHUNKDATA で確認できます。
			@since GenTL v1.2
			@deprecated GenTL 1.5
		*/
		PAYLOAD_TYPE_CHUNK_DATA			= 4,

		/*!
			@~english	@details	The buffer payload contains JPEG data in the format described in GEV 2.0.The GenTL Producer should report additional information through the corresponding BUFFER_INFO_CMD commands.
			@since GenTL v1.4
			@~japanese	@details	バッファのペイロードデータには GigEVision 2.0 で記述されたフォーマットのJPEGデータが含まれています。GenTLプロデューサーは追加の情報を対応する BUFFER_INFO_CMD で報告する必要があります。
			@since GenTL v1.4
		*/
		PAYLOAD_TYPE_JPEG				= 5,

		/*!
			@~english	@details	The buffer payload contains JPEG 2000 data in the format described in GEV 2.0.The GenTL Producer should report additional information through the corresponding BUFFER_INFO_CMD commands.
			@since GenTL v1.4
			@~japanese	@details	バッファのペイロードデータには GigEVision 2.0 で記述されたフォーマットのJPEG2000データが含まれています。GenTLプロデューサーは追加の情報を対応する BUFFER_INFO_CMD で報告する必要があります。
			@since GenTL v1.4
		*/
		PAYLOAD_TYPE_JPEG2000			= 6,

		/*!
			@~english	@details	The buffer payload contains H264 data in the format described in GEV 2.0.The GenTL Producer should report additional information through the corresponding BUFFER_INFO_CMD commands.
			@since GenTL v1.4
			@~japanese	@details	バッファのペイロードデータには GigEVision 2.0 で記述されたフォーマットのH.264データが含まれています。GenTLプロデューサーは追加の情報を対応する BUFFER_INFO_CMD で報告する必要があります。
			@since GenTL v1.4
		*/
		PAYLOAD_TYPE_H264				= 7,

		/*!
			@~english	@details	The buffer payload contains only chunk data but no additional payload.
			@since GenTL v1.4
			@~japanese	@details	バッファのペイロードデータにはチャンクデータのみが含まれています。
			@since GenTL v1.4
		*/
		PAYLOAD_TYPE_CHUNK_ONLY			= 8,

		/*!
			@~english	@details	The buffer payload contains device specific data.The GenTL Producer should report additional information through the corresponding BUFFER_INFO_CMD commands.
			@since GenTL v1.4
			@~japanese	@details	バッファのペイロードデータにはデバイス独自のデータが含まれています。GenTLプロデューサーは追加の情報を対応する BUFFER_INFO_CMD で報告する必要があります。
			@since GenTL v1.4
		*/
		PAYLOAD_TYPE_DEVICE_SPECIFIC	= 9,

		/*!
			@~english	@details	The buffer payload contains multiple parts of different payload types. Information about the individual parts should be queried using DSGetNumBufferParts() and DSGetBufferPartInfo() functions.
			@since GenTL v1.5
			@~japanese	@details	バッファのペイロードデータには異なるペイロードタイプからなるマルチパートデータが含まれています。個々のパートの情報は DSGetNumBufferParts() および DSGetBufferPartInfo() 関数を使って取得します。
			@since GenTL v1.5
		*/
		PAYLOAD_TYPE_MULTI_PART			= 10,

		/*!
			@~english	@details	Starting value for GenTL Producer custom IDs which are implementation specific.
			@~japanese	@details	実装依存の独自IDの最初の値
		*/
		PAYLOAD_TYPE_CUSTOM_ID			= 1000
	}PAYLOADTYPE_INFO_ID, *PPAYLOADTYPE_INFO_ID;

	/*! 
		@ingroup	GenTL_PublicImple
		@enum	PIXELFORMAT_NAMESPACE_ID
		@~english	@brief	This enumeration defines constants to interpret the pixel formats provided through BUFFER_INFO_PIXELFORMAT.
		@~english	@details	This enumeration defines constants to interpret the pixel formats provided through BUFFER_INFO_PIXELFORMAT.
		@since GenTL GenTL v1.2
		@~japanese	@brief	ピクセルフォーマット名列挙子
		@~japanese	@details	ピクセルフォーマット名列挙子
		@since GenTL GenTL v1.2
	*/
	typedef enum PIXELFORMAT_NAMESPACE_IDS
	{

		/*!
			@~english	@details	The interpretation of the pixel format values is unknown to the GenTL Producer.
			@since GenTL v1.2
			@~japanese	@details	ピクセルフォーマット値の解釈方法が不明です。
			@since GenTL v1.2
		*/
		PIXELFORMAT_NAMESPACE_UNKNOWN			= 0,

		/*!
			@~english	@details	The interpretation of the pixel format values is referencing GigE Vision 1.x.
			@since GenTL v1.2
			@~japanese	@details	ピクセルフォーマット値は GigEVision 1.xに準拠します。
			@since GenTL v1.2
		*/
		PIXELFORMAT_NAMESPACE_GEV				= 1,

		/*!
			@~english	@details	The interpretation of the pixel format values is referencing IIDC 1.x.
			@since GenTL v1.2
			@~japanese	@details	ピクセルフォーマット値は IIDC 1.xに準拠します。
			@since GenTL v1.2
		*/
		PIXELFORMAT_NAMESPACE_IIDC				= 2,

		/*!
			@~english	@details	The interpretation of the pixel format values is referencing PFNC 16Bit Values. It is recommended to use the PFNC32 namespace when ever possible or even do the translation in the GenTL Producer since the support in GenTL consumers for it is expected to be much broader.
			@since GenTL v1.4
			@~japanese	@details	ピクセルフォーマット値は PFNC 16ビット値です。可能な限り PFNC 32ビット値の使用が推奨されます。
			@since GenTL v1.4
		*/
		PIXELFORMAT_NAMESPACE_PFNC_16BIT		= 3,

		/*!
			@~english	@details	The interpretation of the pixel format values is referencing PFNC 32Bit Values.
			@since GenTL v1.4
			@~japanese	@details	ピクセルフォーマット値は PFNC 32ビット値です。
			@since GenTL v1.4
		*/
		PIXELFORMAT_NAMESPACE_PFNC_32BIT		= 4,

		/*!
			@~english	@details	The interpretation of the pixel format values is GenTL Producer specific.
			@~japanese	@details	実装依存の独自IDの最初の値
		*/
		PIXELFORMAT_NAMESPACE_CUSTOM_ID			= 1000
	}PIXELFORMAT_NAMESPACE_ID, *PPIXELFORMAT_NAMESPACE_ID;

	/*! 
		@ingroup	GenTL_PublicImple
		@enum	PIXELENDIANNESS_ID
		@~english	@brief	This enumeration defines constants describing endianness of multi-byte pixel data in a buffer. These values are returned by a call to DSGetBufferInfo() with the command BUFFER_INFO_PIXELENDIANNESS.
		@~english	@details	This enumeration defines constants describing endianness of multi-byte pixel data in a buffer. These values are returned by a call to DSGetBufferInfo() with the command BUFFER_INFO_PIXELENDIANNESS.
		@since GenTL GenTL v1.4
		@~japanese	@brief	ピクセルエンディアン列挙子
		@~japanese	@details	ピクセルエンディアン列挙子
		@since GenTL GenTL v1.4
	*/
	typedef enum PIXELENDIANNESS_IDS
	{

		/*!
			@~english	@details	Endianness of the pixel data is unknown to the GenTL Producer.
			@since GenTL GenTL v1.4
			@~japanese	@details	ピクセルデータのエンディアンが不明です。
			@since GenTL GenTL v1.4
		*/
		PIXELENDIANNESS_UNKNOWN					= 0,

		/*!
			@~english	@details	The pixel data is stored in little endian format.
			@since GenTL GenTL v1.4
			@~japanese	@details	ピクセルデータはリトルエンディアンで格納されています。
			@since GenTL GenTL v1.4
		*/
		PIXELENDIANNESS_LITTLE					= 1,

		/*!
			@~english	@details	The pixel data is stored in big endian format.
			@since GenTL GenTL v1.4
			@~japanese	@details	ピクセルデータはビッグエンディアンで格納されています。
			@since GenTL GenTL v1.4
		*/
		PIXELENDIANNESS_BIG						= 2
	}PIXELENDIANNESS_ID, *PPIXELENDIANNESS_ID;
	
	/*! 
		@ingroup	GenTL_PublicImple
		@enum	PARTDATATYPE_ID
		@~english	@brief	This enumeration defines constants to give a hint on the data type to be expected in the buffer part.
		@~english	@details	This enumeration defines constants to give a hint on the data type to be expected in the buffer part. These values are returned by a call to DSGetBufferPartInfo() with the command BUFFER_PART_INFO_DATA_TYPE. The part data type is intended to describe data in individual parts of a multi-part buffer.
		@since GenTL GenTL v1.5
		@~japanese	@brief	パートデータタイプ列挙子
		@~japanese	@details	パートデータタイプ列挙子。 引数に BUFFER_PART_INFO_DATA_TYPE を指定して DSGetBufferPartInfo() を呼び出すことで、マルチパートバッファの個々のパートのデータタイプを取得します。
		@since GenTL GenTL v1.5
	*/
	typedef enum PARTDATATYPE_IDS
	{
		PART_DATATYPE_UNKNOWN				= 0,	//!< The GenTL Producer is not aware of the data type of the data in the provided buffer part. From the GenTL Consumer perspective this can be handled as raw data.
													//!< \since GenTL v1.5
		PART_DATATYPE_2D_IMAGE				= 1,	//!< Color or monochrome (2D) image. This part carries all the pixel data of given image (even if the image is represented by a single-plane pixel format). It is recommended to use PIXELFORMAT_NAMESPACE_PFNC_32BIT data format with this data type whenever possible.
													//!< \since GenTL v1.5
		PART_DATATYPE_2D_PLANE_BIPLANAR		= 2,	//!< Single color plane of a planar (2D) image. The data should be linked with the other color planes to get the complete image. The complete image consists of 2 planes. The planes of a given planar image must be placed as consecutive parts within the buffer. It is recommended to use PIXELFORMAT_NAMESPACE_PFNC_32BIT data format with this data type whenever possible.
													//!< \since GenTL v1.5
		PART_DATATYPE_2D_PLANE_TRIPLANAR	= 3,	//!< Single color plane of a planar (2D) image. The data should be linked with the other color planes to get the complete image. The complete image consists of 3 planes. The planes of a given planar image must be placed as consecutive parts within the buffer. It is recommended to use PIXELFORMAT_NAMESPACE_PFNC_32BIT data format with this data type whenever possible.
													//!< \since GenTL v1.5
		PART_DATATYPE_2D_PLANE_QUADPLANAR	= 4,	//!< Single color plane of a planar (2D) image. The data should be linked with the other color planes to get the complete image. The complete image consists of 4 planes. The planes of a given planar image must be placed as consecutive parts within the buffer. It is recommended to use PIXELFORMAT_NAMESPACE_PFNC_32BIT data format with this data type whenever possible.
													//!< \since GenTL v1.5
		PART_DATATYPE_3D_IMAGE				= 5,	//!< 3D image (pixel coordinates). This part carries all the pixel data of given image (even if the image is represented by a single-plane pixel format, for example when transferring the depth map only). It is recommended to use PIXELFORMAT_NAMESPACE_PFNC_32BIT data format with this data type whenever possible.
													//!< \since GenTL v1.5
		PART_DATATYPE_3D_PLANE_BIPLANAR		= 6,	//!< Single plane of a planar 3D image. The data should be linked with the other coordinate planes to get the complete image. The complete image consists of 2 planes. The planes of a given planar image must be placed as consecutive parts within the buffer. It is recommended to use PIXELFORMAT_NAMESPACE_PFNC_32BIT data format with this data type whenever possible.
													//!< \since GenTL v1.5
		PART_DATATYPE_3D_PLANE_TRIPLANAR	= 7,	//!< Single plane of a planar 3D image. The data should be linked with the other coordinate planes to get the complete image. The complete image consists of 3 planes. The planes of a given planar image must be placed as consecutive parts within the buffer. It is recommended to use PIXELFORMAT_NAMESPACE_PFNC_32BIT data format with this data type whenever possible.
													//!< \since GenTL v1.5
		PART_DATATYPE_3D_PLANE_QUADPLANAR	= 8,	//!< Single plane of a planar 3D image. The data should be linked with the other coordinate planes to get the complete image. The complete image consists of 4 planes. The planes of a given planar image must be placed as consecutive parts within the buffer. It is recommended to use PIXELFORMAT_NAMESPACE_PFNC_32BIT data format with this data type whenever possible.
													//!< \since GenTL v1.5
		PART_DATATYPE_CONFIDENCE_MAP		= 9,	//!< Confidence of the individual pixel values. Expresses the level of validity of given pixel values. Confidence map is always used together with one or more additional image-based parts matching 1:1 dimension-wise. Each value in the confidence map expresses level of validity of the image pixel at matching position. The data format should be a Confidence PFNC format. It is recommended to use PIXELFORMAT_NAMESPACE_PFNC_32BIT data format with this data type whenever possible.
													//!< \since GenTL v1.5
		/*!
			@~english	@details	Starting value for GenTL Producer custom IDs which are implementation specific.
			@since GenTL v1.5
			@~japanese	@details	実装依存の独自IDの最初の値
			@since GenTL v1.5
		*/
		PART_DATATYPE_CUSTOM_ID				= 1000
	}PARTDATATYPE_ID, *PPARTDATATYPE_ID;

	/*! 
		@ingroup	GenTL_PublicImple
		@enum	PORT_INFO_CMD
		@~english	@brief	 This enumeration defines commands to retrieve information with the GCGetPortInfo() function on a module or remote device handle.
		@~english	@details	 This enumeration defines commands to retrieve information with the GCGetPortInfo() function on a module or remote device handle.
		@~japanese	@brief	 ポート情報列挙子
		@~japanese	@details	ポート情報列挙子。モジュールやリモートデバイスの情報取得のため GCGetPortInfo() で使用されます。
	*/
	typedef enum PORT_INFO_CMD_LIST
	{
		/*!
			@~english	@details	STRING	Unique ID of the module the port references. In case of the remote device module PORT_INFO_ID returns the same ID as for the local device module. In case of a buffer PORT_INFO_ID returns the address of the buffer as hex string without the leading '0x'.
			@~japanese	@details	STRING	ポートのモジュールを特定するID。リモートデバイスの場合、 PORT_INFO_ID はローカルデバイスと同じIDを返します。バッファもウールの PORT_INFO_ID は、バッファアドレスの0xを含まない16進表記を返します。
		*/
		PORT_INFO_ID				= 0,

		/*!
			@~english	@details	STRING	Port vendor name. 
			@~japanese	@details	STRING	ポートベンダー名。
		*/
		PORT_INFO_VENDOR			= 1,

		/*!
			@~english	@details	STRING	Port model name. The port model references the model of the underlying module.
			@~japanese	@details	STRING	ポートモデル名。ポートモデルはモジュールのモデルを参照する。
		*/
		PORT_INFO_MODEL				= 2,

		/*!
			@~english	@details	STRING	Transport layer technology that is supported.
			@~japanese	@details	STRING	サポートされているトランスポート層タイプ
		*/
		PORT_INFO_TLTYPE			= 3,

		/*!
			@~english	@details	STRING	GenTL Module the port refers to: "TLSystem" for the System module. "TLInterface" for the Interface. "TLDevice" for the Device module. "TLDataStream" for the Data Stream module. "TLBuffer" for the Buffer module. "Device" for the remote device.
			@~japanese	@details	STRING	このポートに参照されるGenTLモジュール TLSystem:システムモジュール, TLInterface:インターフェースモジュール, TLDevice:(ローカル)デバイスモジュール、TLDataStream:データストリームモジュール, TLBuffer:バッファモジュール, Device:リモートデバイス
		*/
		PORT_INFO_MODULE			= 4,

		/*!
			@~english	@details	BOOL8	Flag indicating that the port's data is little endian.
			@~japanese	@details	BOOL8	ポートのデータがリトルエンディアンであることを示すフラグ
		*/
		PORT_INFO_LITTLE_ENDIAN		= 5,

		/*!
			@~english	@details	BOOL8	Flag indicating that the port's data is big endian.
			@~japanese	@details	BOOL8	ポートのデータがビッグエンディアンであることを示すフラグ
		*/
		PORT_INFO_BIG_ENDIAN		= 6,

		/*!
			@~english	@details	BOOL8	Flag indicating that read access is allowed.
			@~japanese	@details	BOOL8	ポートが読み込みアクセス可能であることを示すフラグ
		*/
		PORT_INFO_ACCESS_READ		= 7,

		/*!
			@~english	@details	BOOL8	Flag indicating that write access is allowed.
			@~japanese	@details	BOOL8	ポートが書き込みアクセス可能であることを示すフラグ
		*/
		PORT_INFO_ACCESS_WRITE		= 8,

		/*!
			@~english	@details	BOOL8	Flag indicating that the port is currently not available.
			@~japanese	@details	BOOL8	ポートが現在使用できないことを示すフラグ
		*/
		PORT_INFO_ACCESS_NA			= 9,

		/*!
			@~english	@details	BOOL8	Flag indicating that no port is implemented.This is only valid on the Buffer module since on all other modules the port is mandatory.
			@~japanese	@details	BOOL8	ポートが実装されていないことを示すフラグ。他のモジュールではポートが必須なため、この値はバッファモジュール時のみ有効です。
		*/
		PORT_INFO_ACCESS_NI			= 10,

		/*!
			@~english	@details	STRING	Version of the port.
			@~japanese	@details	STRING	このポートのバージョン
		*/
		PORT_INFO_VERSION			= 11,

		/*!
			@~english	@details	STRING	Name of the port as referenced in the XML description.This name is used to connect this port to the nodemap instance of this module.
			@~japanese	@details	STRING	XMLで参照されるこのポートの名前。このモジュールとノードマップの実体を接続する際に使用されます。
		*/
		PORT_INFO_PORTNAME			= 12,

		/*!
			@~english	@details	Starting value for GenTL Producer custom IDs which are implementation specific.
			@~japanese	@details	実装依存の独自IDの最初の値
		*/
		PORT_INFO_CUSTOM_ID			= 1000
	}PORT_INFO_CMD, *PPORT_INFO_CMD;

	/*! 
		@ingroup	GenTL_PublicImple
		@enum	URL_SCHEME_ID
		@~english	@brief	This enumeration defines the values to be retrieved through a call to GCGetPortURLInfo() with the command URL_INFO_SCHEME.
		@~english	@details	 This enumeration defines the values to be retrieved through a call to GCGetPortURLInfo() with the command URL_INFO_SCHEME.
		@since GenTL v1.5
		@~japanese	@brief	スキーマ情報列挙子
		@~japanese	@details	スキーマ情報列挙子。引数に URL_INFO_SCHEME を指定した GCGetPortURLInfo() の呼び出しで取得されます。
		@since GenTL v1.5
	*/
	typedef enum URL_SCHEME_IDS
	{

		/*!
			@~english	@details	The XML-File is to be retrieved from the local register map. The address and size where it can be read can be queried using the GCGetPortURLInfo() function with the URL_INFO_FILE_REGISTER_ADDRESS and URL_INFO_FILE_SIZE command.
			@since GenTL v1.5
			@~japanese	@details	XMLファイルはレジスタマップから取得できます。取得できる場所とサイズは GCGetPortURLInfo() 関数に URL_INFO_FILE_REGISTER_ADDRESS および URL_INFO_FILE_SIZE を指定することで取得できます。
			@since GenTL v1.5
		*/
		URL_SCHEME_LOCAL		= 0,

		/*!
			@~english	@details	The XML-file can be retrieved from a webserver using the http protocol. The URL where it can be downloaded can be queried using the GCGetPortURLInfo() function with the URL_INFO_URL command.
			@since GenTL v1.5
			@~japanese	@details	XMLファイルはHTTPプロトコルを使用してWEBサーバーから取得できます。ダウンロード元は GCGetPortURLInfo() 関数に URL_INFO_URL を指定することで取得できます。
			@since GenTL v1.5
		*/
		URL_SCHEME_HTTP			= 1,

		/*!
			@~english	@details	The XML-file can be read from the local hard disk. The filename can be queried through GCGetPortURLInfo() function using the URL_INFO_FILENAME command.
			@since GenTL v1.5
			@~japanese	@details	XMLファイルはローカルハードディスクから取得できます。ファイル名は GCGetPortURLInfo() 関数に URL_INFO_FILENAME を指定することで取得できます。
			@since GenTL v1.5
		*/
		URL_SCHEME_FILE			= 2,

		/*!
			@~english	@details	Starting value for custom IDs which are implementation specific.
			@since GenTL v1.5
			@~japanese	@details	実装依存の独自IDの最初の値
			@since GenTL v1.5
		*/
		URL_SCHEME_CUSTOM_ID	= 1000
	}URL_SCHEME_ID, *PURL_SCHEME_ID;

	/*! 
		@ingroup	GenTL_PublicImple
		@enum	URL_INFO_CMD
		@~english	@brief	This enumeration defines commands to retrieve information with the GCGetPortURLInfo() function on a module or remote device handle.
		@~english	@details	 This enumeration defines commands to retrieve information with the GCGetPortURLInfo() function on a module or remote device handle.
		@since GenTL v1.1
		@~japanese	@brief	URL情報列挙子
		@~japanese	@details	URL情報列挙子。モジュールやリモートデバイスの情報取得のため GCGetPortURLInfo() で使用されます。
		@since GenTL v1.1
	*/
	typedef enum URL_INFO_CMD_LIST
	{
		/*!
			@~english	@details	STRING	URL.
			@since GenTL v1.1
			@~japanese	@details	STRING	URL
			@since GenTL v1.1
		*/
		URL_INFO_URL					= 0,
		
		/*!
			@~english	@details	INT32 Major version of the schema this URL refers to.
			@since GenTL v1.1
			@~japanese	@details	INT32 このURL参照するスキーマのメジャーバージョン
			@since GenTL v1.1
		*/
		URL_INFO_SCHEMA_VER_MAJOR		= 1,
		
		/*!
			@~english	@details	INT32 Minor version of the schema this URL refers to.
			@since GenTL v1.1
			@~japanese	@details	INT32 このURL参照するスキーマのマイナーバージョン
			@since GenTL v1.1
		*/
		URL_INFO_SCHEMA_VER_MINOR		= 2,
		
		/*!
			@~english	@details	INT32 Major version of the XML-file this URL refers to.
			@since GenTL v1.1
			@~japanese	@details	INT32 このURL参照するXMLファイルのメジャーバージョン
			@since GenTL v1.1
		*/
		URL_INFO_FILE_VER_MAJOR			= 3,
		
		/*!
			@~english	@details	INT32 Minor version of the XML-file this URL refers to.
			@since GenTL v1.1
			@~japanese	@details	INT32 このURL参照するXMLファイルのマイナーバージョン
			@since GenTL v1.1
		*/
		URL_INFO_FILE_VER_MINOR			= 4,
		
		/*!
			@~english	@details	INT32 Subminor version of the XML-file this URL refers to.
			@since GenTL v1.1
			@~japanese	@details	INT32 このURL参照するXMLファイルのサブマイナーバージョン
			@since GenTL v1.1
		*/
		URL_INFO_FILE_VER_SUBMINOR		= 5,
		
		/*!
			@~english	@details	BUFFER	SHA1 Hash of the XML-file this URL refers to.The size of the provided buffer is 160Bit according to the SHA1 specification.
			@since GenTL v1.4
			@~japanese	@details	BUFFER	このURLが参照するXMLファイルのSHA1ハッシュ。SHA1の規格に従い、提供されるバッファのサイズは160ビット(20バイト)。
			@since GenTL v1.4
		*/
		URL_INFO_FILE_SHA1_HASH			= 6,
		
		/*!
			@~english	@details	UINT64	Register address of the XML-File in the device's register map. In case the XML is not localy stored in the device's register map the info function should return a GC_ERR_NOT_AVAILABLE.
			@since GenTL v1.5
			@~japanese	@details	UINT64	レジスターマップ上のXMLファイルのアドレス。レジスタマップにXMLファイルが格納されていない場合、情報取得関数は GC_ERR_NOT_AVAILABLE を返します。
			@since GenTL v1.5
		*/
		URL_INFO_FILE_REGISTER_ADDRESS	= 7,
		
		/*!
			@~english	@details	UINT64	File size of the XML-File in bytes.
			@since GenTL v1.5
			@~japanese	@details	UINT64	XMLファイルのバイト単位のサイズ
			@since GenTL v1.5
		*/
		URL_INFO_FILE_SIZE				= 8,
		
		/*!
			@~english	@details	INT32	Scheme of the URL.
			@sa	URL_SCHEME_IDS
			@since GenTL v1.5
			@~japanese	@details	INT32	URLのスキーマ。
			@sa	URL_SCHEME_IDS
			@since GenTL v1.5
		*/
		URL_INFO_SCHEME					= 9,
		
		/*!
			@~english	@details	STRING	Filename in case the scheme of the URL is URL_SCHEME_FILE or as a hint if the scheme is URL_SCHEME_LOCAL.
			@since GenTL v1.5
			@~japanese	@details	STRING	URLが URL_SCHEME_FILE である場合のファイル名。URLが URL_SCHEME_LOCAL であるファイル名のヒント。
			@since GenTL v1.5
		*/
		URL_INFO_FILENAME				= 10,

		/*!
			@~english	@details	Starting value for GenTL Producer custom IDs which are implementation specific.
			@~japanese	@details	実装依存の独自IDの最初の値
		*/
		URL_INFO_CUSTOM_ID				= 1000
	}URL_INFO_CMD, *PURL_INFO_CMD;

	/*! 
		@ingroup	GenTL_PublicImple
		@enum	EVENT_TYPE
		@~english	@brief	Known event types that can be registered on certain modules with the GCRegisterEvent() function.
		@~english	@details	Known event types that can be registered on certain modules with the GCRegisterEvent() function.
		@~japanese	@brief	イベントタイプ列挙子
		@~japanese	@details	イベントタイプ列挙子。 GCRegisterEvent() で登録されるイベントの指定に使用されます。
	*/
	typedef enum EVENT_TYPE_LIST
	{
		/*!
			@~english	@details	Notification on module errors. EVENT_DATA_ID:INT32 (GC_ERROR), EVENT_DATA_VALUE:STRING(Description)
			@~japanese	@details	モジュールエラーを通知します。 EVENT_DATA_ID はINT32で GC_ERROR 、 EVENT_DATA_VALUE は文字列で説明文になります。
		*/
		EVENT_ERROR						= 0,

		/*!
			@~english	@details	Notification on newly filled buffers. EVENT_DATA_ID:PTR(Buffer handle), EVENT_DATA_VALUE:PTR(Private pointer)
			@~japanese	@details	新規にデータが書き込まれたバッファを通知します。 EVENT_DATA_ID はバッファハンドルで 、 EVENT_DATA_VALUE はユーザー用データポインターになります。
		*/
		EVENT_NEW_BUFFER				= 1,

		/*!
			@~english	@details	Notification if a feature was changed by the GenTL Producer driver and thus needs to be invalidated in the GenICam GenApi instance using the module. EVENT_DATA_ID:STRING(Feature name)
			@~japanese	@details	GenTLプロデューサーにより機能が更新され、このモジュールのGenApiの実体の更新が必要であることを通知します。 EVENT_DATA_ID は設定の名称になります。
		*/
		EVENT_FEATURE_INVALIDATE		= 2,

		/*!
			@~english	@details	Notification if the GenTL Producer driver wants to manually set a feature in the GenICam GenApi instance using the module. EVENT_DATA_ID:STRING(Feature name), EVENT_DATA_VALUE:STRING(Feature value)
			@~japanese	@details	GenTLプロデューサーがこのモジュールのGenApi実体の設定を望んでいることを通知します。。 EVENT_DATA_ID は設定の名称、 EVET_DATA_VALUE は設定される値になります。
		*/
		EVENT_FEATURE_CHANGE			= 3,

		/*!
			@~english	@details	Notification if the GenTL Producer wants to inform the GenICam GenApi instance of the remote device that a GenApi compatible event	was fired.This Event is to be registered on a Local Device module. EVENT_DATA_ID:String representation of the EventID number in hexadecimal numbers with even number of digits and without the leading '0x'. STRING(Event ID), EVENT_DATA_VALUE:Corresponds to the data addressable through the remote device's nodemap event port, beginning of the buffer corresponding to address 0. BUFFER(optional data) 
			@~english	@attention	This event type used to be called EVENT_FEATURE_DEVEVENT but has been renamed for a more intuitive understanding.
			@~japanese	@details	リモートデバイスでGenApi互換のイベントが発生したことを通知します。このイベントはローカルデバイスモジュールに対して登録されます。 EVENT_DATA_ID はイベントIDの0xを除いた16進数表記、 EVENT_DATA_VALUE はバッファでイベントポートを通じてアクセス可能です。
			@~japanese	@attention	このイベントタイプは EVENT_FEATURE_DEVEVENT と呼ばれていましたが、名称が変更されました。
		*/
		EVENT_REMOTE_DEVICE				= 4,
		
		/*!
			@~english	@details	Notification that one GenTL Producer module wants to inform the GenICam GenApi instance of this module that a GenApi compatible event was fired. This Event is to be registered on any module handle except on the Remote Device. EVENT_DATA_ID:String representation of the EventID number in hexadecimal numbers with even number of digits and without the leading '0x'. Data type: STRING (Event ID), EVENT_DATA_VALUE:Corresponds to the data addressable through the module's nodemap event port, beginning of the buffer corresponding to address 0. BUFFER (optional data)
			@since GenTL v1.4
			@~japanese	@details	GenTLプロデューサーモージュールがGenApi互換のイベントの発生をGenApiモジュールの実体へ通知します。イベントはリモートデバイスを除くどのモジュールにも登録できます。 EVENT_DATA_ID は文字列でEventIDの0xを除いた16進数表記、 EVENT_DATA_VALUE はバッファでイベントポートを通じてアクセス可能です。
			@since GenTL v1.4
		*/
		EVENT_MODULE					= 5,

		/*!
			@~english	@details	Starting value for GenTL Producer custom events which are implementation specific.
			@~japanese	@details	実装依存の独自IDの最初の値
		*/
		EVENT_CUSTOM_ID					= 1000
	}EVENT_TYPE, *PEVENT_TYPE;

	/*! 
		@ingroup	GenTL_PublicImple
		@enum	EVENT_INFO_CMD
		@~english	@brief	This enumeration defines command to retrieve information with the EventGetInfo() function on an event handle.
		@~english	@details	This enumeration defines command to retrieve information with the EventGetInfo() function on an event handle.
		@~japanese	@brief	イベント情報列挙子
		@~japanese	@details	イベント情報列挙子。 EventGetInfo() で取得する情報の指定に使用されます。
	*/
	typedef enum EVENT_INFO_CMD_LIST
	{
		/*!
			@~english	@details	INT32(EVENT_TYPE)	The event type of the event handle.
			@~japanese	@details	INT32(EVENT_TYPE)	指定されたイベントハンドルのイベントタイプ
		*/
		EVENT_EVENT_TYPE				= 0,
		
		/*!
			@~english	@details	SIZET	Number of events in the event data queue.
			@~japanese	@details	SIZET	イベントデータキュー内のイベント数
		*/
		EVENT_NUM_IN_QUEUE				= 1,
		
		/*!
			@~english	@details	UINT64	Number of events that were fired since the registration of the event through a call to GCRegisterEvent(). A fired event is either still in the internal queue or already delivered to the user or discarded through EventFlush().
			@~japanese	@details	UINT64	GCRegisterEvent() を呼び出してイベントの登録をしてから発生したイベントの数。発生したイベントには、内部のキューにあるイベント、ユーザーに渡されたイベント、 EventFlush() で破棄されたイベントが含まれます。
		*/
		EVENT_NUM_FIRED					= 2,
		
		/*!
			@~english	@details	SIZET	Maximum size in bytes of the event data provided by the event. In case this is not known a priori by the GenTL Producer the EventGetInfo() function returns GC_ERR_NOT_AVAILABLE. This maximum size must not change during runtime.
			@since GenTL v1.2
			@~japanese	@details	SIZET	このイベントで提供されるイベントデータのバイト単位の最大サイズです。GenTLプロデューサーにより事前に把握できない場合、 EventGetInfo() 関数は GC_ERR_NOT_AVAILABLE を返します。実行中に最大サイズは変化しません。
			@since GenTL v1.2
		*/
		EVENT_SIZE_MAX					= 3,
		
		/*!
			@~english	@details	SIZET	Maximum size in bytes of the information output buffer of EventGetDataInfo() function for EVENT_DATA_VALUE. In case this is not known a priori by the GenTL Producer the EventGetDataInfo() function returns the GC_ERR_NOT_AVAILABLE error. This maximum size must not change during runtime.
			@since GenTL v1.2
			@~japanese	@details	SIZET	EVENT_DATA_VALUE を指定した EventGetDataInfo() 関数ので出力される情報の最大サイズです。GenTLプロデューサーにより事前に把握できない場合、 EventGetDataInfo() 関数は GC_ERR_NOT_AVAILABLE を返します。実行中に最大サイズは変化しません。
			@since GenTL v1.2
		*/
		EVENT_INFO_DATA_SIZE_MAX		= 4,

		/*!
			@~english	@details	Starting value for GenTL Producer custom IDs which are implementation specific. 
			@~japanese	@details	実装依存の独自IDの最初の値
		*/
		EVENT_INFO_CUSTOM_ID			= 1000
	}EVENT_INFO_CMD, *PEVENT_INFO_CMD;

	/*! 
		@ingroup	GenTL_PublicImple
		@enum	EVENT_DATA_INFO_CMD
		@~english	@brief	This enumeration defines commands to retrieve information with the EventGetDataInfo() function on delivered event data.
		@~english	@details	This enumeration defines commands to retrieve information with the EventGetDataInfo() function on delivered event data.
		@~japanese	@brief	イベントデータ列挙子
		@~japanese	@details	イベントデータ列挙子。 EventGetDataInfo() で取得する情報の指定に使用されます。
	*/
	typedef enum EVENT_DATA_INFO_CMD_LIST
	{
		/*!
			@~english	@details	Attribute in the event data to identify the object or feature the event refers to.
			@~japanese	@details	イベントが参照するオブジェクトや機能の特定に使用されるイベントデータの属性です。
		*/
		EVENT_DATA_ID					= 0,

		/*!
			@~english	@details	Defines additional data to an ID.
			@~japanese	@details	IDに対する追加データの定義です。
		*/
		EVENT_DATA_VALUE				= 1,

		/*!
			@~english	@details	UINT64	Attribute in the event data to identify the object or feature the event refers to. It is the numeric representation of EVENT_DATA_ID if applicable. In case it is not possible to map EVENT_DATA_ID to a number the EventGetDataInfo() function returns GC_ERR_NOT_AVAILABLE.
			@since GenTL v1.3
			@~japanese	@details	UINT64	イベントが参照するオブジェクトや機能の特定に使用されるイベントデータの属性です。 EVENT_DATA_ID が数値表現可能であれば、数値化してものになります。もし無理な場合は、 EventGetDataInfo() は GC_ERR_NOT_AVAILABLE を返します。
			@since GenTL v1.3
		*/
		EVENT_DATA_NUMID				= 2,

		/*!
			@~english	@details	Starting value for GenTL Producer custom IDs which are implementation specific.
			@~japanese	@details	実装依存の独自IDの最初の値
		*/
		EVENT_DATA_CUSTOM_ID			= 1000
	}EVENT_DATA_INFO_CMD, *PEVENT_DATA_INFO_CMD;



	//-------------------------------------------------------------------------
	//Structs
	//-------------------------------------------------------------------------
	//! \ingroup	GenTL_PublicImple
	//! Structure of the data returned from a signaled "New Buffer" event.
	#   pragma pack (push, 1)
	typedef struct S_EVENT_NEW_BUFFER
	{
		//! Buffer handle which contains new data.
		BUFFER_HANDLE	BufferHandle;

		//! User pointer provided at announcement of the buffer.
		void*	pUserPointer;
	}EVENT_NEW_BUFFER_DATA, *PEVENT_NEW_BUFFER_DATA;
	#   pragma pack (pop)

	//! \ingroup	GenTL_PublicImple
	//! Layout of the array elements being used in the function GCWritePortStacked and GCReadPortStacked to accomplish a stacked register read / write operations.
	#   pragma pack (push, 1)
	typedef struct S_PORT_REGISTER_STACK_ENTRY
	{
		//! Register address.
		uint64_t	Address;
		
		//! Pointer to the buffer receiving the data being read / containing the data to write.
		void*	pBuffer;
		
		//! Number of bytes to read / write. The provided Buffer must be at least that size.
		size_t Size;
	}PORT_REGISTER_STACK_ENTRY, *PPORT_REGISTER_STACK_ENTRY;
	#   pragma pack (pop)

	#   pragma pack (push, 1)
	//! \ingroup	GenTL_PublicImple
	//! Layout of the array elements being used in the function DSGetBufferChunkData to carry information about individual chunks present in the buffer.
	typedef struct S_SINGLE_CHUNK_DATA
	{
		//! Numeric representation of the chunk's ChunkID.
		uint64_t	ChunkID;
		
		//! Offset of the chunk's data from the start of the buffer(in bytes).
		ptrdiff_t	ChunkOffset;

		//! Size of the given chunk data (in bytes).
		size_t	ChunkLength;
	}SINGLE_CHUNK_DATA, *PSINGLE_CHUNK_DATA;
	#   pragma pack (pop)

	//-------------------------------------------------------------------------
	//String Constants
	//-------------------------------------------------------------------------
	/*! 
		@ingroup	GenTL_PublicImple
		@~english	@details	Type to use for GigE Vision technology.
		@~japanese	@details	GigE Visionタイプ
	*/
#define TLTypeGEVName			"GEV"	//"GigEVision"
	
	/*! 
		@ingroup	GenTL_PublicImple
		@~english	@details	Type to use for Camera Link technology.
		@~japanese	@details	Camera Linkタイプ
	*/
#define TLTypeCLName			"CL"	//"CameraLink"

	/*! 
		@ingroup	GenTL_PublicImple
		@~english	@details	Type to use for Camera Link HS.
		@since GenTL v1.3
		@~japanese	@details	Camera Link HSタイプ
		@since GenTL v1.3
	*/
#define TLTypeCLHSName			"CLHS"	//"CameraLinkHS"

	/*! 
		@ingroup	GenTL_PublicImple
		@~english	@details	Type to use for CoaXPress.
		@since GenTL v1.3
		@~japanese	@details	CoaXPressタイプ
		@since GenTL v1.3
	*/
#define TLTypeCXPName			"CXP"	//"CoaXPress"

	/*! 
		@ingroup	GenTL_PublicImple
		@~english	@details	Type to use for USB3 Vision Standard.
		@since GenTL v1.4
		@~japanese	@details	USB3 Visionタイプ
		@since GenTL v1.4
	*/
#define TLTypeU3VName			"U3V"	//"USB3Vision"

	/*! 
		@ingroup	GenTL_PublicImple
		@~english	@details	Type to use for several supported technologies.
		@since GenTL v1.3
		@~japanese	@details	混合タイプ
		@since GenTL v1.3
	*/
#define TLTypeMixedName			"Mixed"

	/*! 
		@ingroup	GenTL_PublicImple
		@~english	@details	Type to use for custom technologies.
		@since GenTL v1.3
		@~japanese	@details	独自タイプ
		@since GenTL v1.3
	*/
#define TLTypeCustomName		"Custom"

	/*! 
		@ingroup	GenTL_PublicImple
		@~english	@details	Name to identify a system module.
		@~japanese	@details	システムモジュールの識別子
	*/
#define TLSystemModuleName        "TLSystem"
	
	/*! 
		@ingroup	GenTL_PublicImple
		@~english	@details	Name to identify a interface module.
		@~japanese	@details	インタフェースモジュールの識別子
	*/
#define TLInterfaceModuleName     "TLInterface"

	/*! 
		@ingroup	GenTL_PublicImple
		@~english	@details	Name to identify a device module.
		@~japanese	@details	(ローカル)デバイスモジュールの識別子
	*/
#define TLDeviceModuleName        "TLDevice"

	/*! 
		@ingroup	GenTL_PublicImple
		@~english	@details	Name to identify a data stream module.
		@~japanese	@details	データストリームモジュールの識別子
	*/
#define TLDataStreamModuleName    "TLDataStream"

	/*! 
		@ingroup	GenTL_PublicImple
		@~english	@details	Name to identify a buffer module.
		@~japanese	@details	バッファモジュールの識別子
	*/
#define TLBufferModuleName        "TLBuffer"

	/*! 
		@ingroup	GenTL_PublicImple
		@~english	@details	Name to identify a remote device module
		@~japanese	@details	リモートデバイスモジュールの識別子
	*/
#define TLRemoteDeviceModuleName  "Device" 

	//-------------------------------------------------------------------------
	// Numeric Constants
	//-------------------------------------------------------------------------

	/*! 
		@ingroup	GenTL_PublicImple
		@~english	@details	This value is indicating an invalid handle for any handle type used within GenTL Producer API.
		@since GenTL v1.4
		@~japanese	@details	GenTLプロデューサーAPIないで不正なハンドルの値として使用されます。
		@since GenTL v1.4
	*/
#define GENTL_INVALID_HANDLE	NULL

	/*! 
		@ingroup	GenTL_PublicImple
		@~english	@details	Value indicating an infinite number(e.g., timeout or number of buffers) to be used with API functions.
		@since GenTL v1.4
		@~japanese	@details	API関数で無限を表す数値として使用されます(例えば、タイムアウト時間やバッファの数など)。
		@since GenTL v1.4
	*/

#if defined(_MSC_VER) && (_MSC_VER < 1600)
#define GENTL_INFINITE	0xFFFFFFFFFFFFFFFFUL
#elif defined(__BORLANDC__) && (__BORLANDC__ < 0x600)
#define GENTL_INFINITE	0xFFFFFFFFFFFFFFFFUL
#else
#define GENTL_INFINITE	0xFFFFFFFFFFFFFFFFULL
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */


	//-------------------------------------------------------------------------
	//Functions
	//-------------------------------------------------------------------------
/// @cond
#if defined(_WIN32) 
#  ifndef GC_IMPORT_EXPORT
#    define GC_IMPORT_EXPORT    __declspec(dllimport)
#  endif
#  ifndef GC_CALLTYPE
#    define GC_CALLTYPE __stdcall
#  endif
#elif defined (__GNUC__) && (__GNUC__ >= 4) && (defined (__linux__) || defined (__APPLE__))
#  define GC_IMPORT_EXPORT __attribute__((visibility("default")))
#  if defined (__i386__)
#    define GC_CALLTYPE __attribute__((stdcall))
#  else
#    define GC_CALLTYPE /* default */
#  endif
#  ifndef EXTERN_C
#    define EXTERN_C extern "C"
#  endif
#endif

#ifdef __cplusplus
namespace GenTL
{
#endif /* __cplusplus */

#define GC_API_NAME(name) GC_IMPORT_EXPORT GC_ERROR GC_CALLTYPE name
#define GC_API_LIST(params)			params;
#include "StGenTL_Function.h"


#define GC_API_NAME(name) typedef GC_ERROR(GC_CALLTYPE *P##name)
#define GC_API_LIST(params)	params;
#include "StGenTL_Function.h"

#ifdef __cplusplus
}
#endif /* __cplusplus */
/// @endcond

#endif //STGENTL_DEF_H__


