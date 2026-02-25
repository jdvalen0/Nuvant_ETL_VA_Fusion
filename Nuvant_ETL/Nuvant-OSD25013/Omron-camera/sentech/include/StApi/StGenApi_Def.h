/* This file is encoded in UTF-8,  */
/* but BOM has not been added to accommodate environments not compatible with BOM. */
/*
 StApi C
*/
/*!
	@ingroup	GenApiC_PublicImpl
	@file StGenApi_Def.h
	@~english	@details
	@~japanese	@details
*/

#if !defined(STGENAPI_DEF_H__)
#define STGENAPI_DEF_H__

#if defined(__cplusplus) && ! defined(__BORLANDC__)
#include <GenApi/Types.h>
#include <GenApi/NodeCallback.h>
using namespace GenApi;
#else

	/*************************************************************************/
	/* Enumerator */
	/*************************************************************************/
	/*! 
		@ingroup	GenApi_PublicImpl
		@enum ECallbackType
		@~english	@brief	The type of callback
		@~english	@details	The type of callback
		@~japanese	@brief	コールバックタイプ列挙子
		@~japanese	@details	コールバックタイプ列挙子
	*/
	typedef enum _ECallbackType
	{
		/*!
			@~english	@details	Callback is fired on leaving the tree inside the lock-guarded area.
			@~japanese	@details	ツリーがロックにより保護されているエリア内からコールバックされます。
		*/
		cbPostInsideLock = 1,
		/*!
			@~english	@details	Callback is fired on leaving the tree outside the lock-guarded area.
			@~japanese	@details	ツリーがロックにより保護されているエリアを抜けてからコールバックされます。
		*/
		cbPostOutsideLock = 2
	} ECallbackType;

	/*!
		@ingroup	GenApi_PublicImpl
		@enum EAccessMode
		@~english	@brief	Access mode of a node.
		@~english	@details	Access mode of a node.
		@~japanese	@brief	アクセスモード列挙子
		@~japanese	@details	アクセスモード列挙子
	*/
	typedef enum _EAccessMode
	{
		/*!
			@~english	@details	Not implemented.
			@~japanese	@details	非実装
		*/
		NI,

		/*!
			@~english	@details	Not available.
			@~japanese	@details	利用不可
		*/
		NA,

		/*!
			@~english	@details	Write Only.
			@~japanese	@details	書き込みのみ可能
		*/
		WO,

		/*!
			@~english	@details	Read Only.
			@~japanese	@details	読み込みのみ可能
		*/
		RO,

		/*!
			@~english	@details	Read and Write.
			@~japanese	@details	読み書き可能
		*/
		RW,

		/*!
			@~english	@details	Object is not yet initialized.
			@~japanese	@details	未定義のアクセスモード
		*/
		_UndefinedAccesMode,

		/*!
			@~english	@details	Used internally for AccessMode cycle detection.
			@~japanese	@details	内部で使用されるサイクル検知用アクセスモード
		*/
		_CycleDetectAccesMode
	} EAccessMode;

	/*!
		@ingroup	GenApi_PublicImpl
		@~english	@brief	Recommended visibility of a node.
		@~english	@details	Recommended visibility of a node.
		@~japanese	@brief	可視性列挙子
		@~japanese	@details	可視性列挙子
	*/
	typedef enum _EVisibility
	{
		/*!
			@~english	@details	Always visible.
			@~japanese	@details	常に可視
		*/
		Beginner = 0,

		/*!
			@~english	@details	Visible for experts or Gurus.
			@~japanese	@details	ExpertまたはGuruに対して可視
		*/
		Expert = 1,

		/*!
			@~english	@details	Visible for Gurus.
			@~japanese	@details	Guruに対して可視
		*/
		Guru = 2,

		/*!
			@~english	@details	Not Visible.
			@~japanese	@details	不可視
		*/
		Invisible = 3,

		/*!
			@~english	@details	Object is not yet initialized.
			@~japanese	@details	定義されていない可視性
		*/
		_UndefinedVisibility = 99
	} EVisibility;

	/*!
		@ingroup	GenApi_PublicImpl
		@~english	@brief	Caching mode of a register.
		@~english	@details	Caching mode of a register.
		@~japanese	@brief	キャッシングモード列挙子
		@~japanese	@details	キャッシングモード列挙子
	*/
	typedef enum _ECachingMode
	{
		/*!
			@~english	@details	Do not use cache.
			@~japanese	@details	キャッシュを使用しない
		*/
		NoCache,

		/*!
			@~english	@details	Write to cache and register.
			@~japanese	@details	書き込み時にキャッシュする
		*/
		WriteThrough,

		/*!
			@~english	@details	Write to register, write to cache on read.
			@~japanese	@details	書き込み後、読み込みを行いキャッシュする
		*/
		WriteAround,

		/*!
			@~english	@details	Not yet initialized.
			@~japanese	@details	未定義のキャッシュモード
		*/
		_UndefinedCachingMode
	} ECachingMode;
	
	/*!
		@ingroup	GenApi_PublicImpl
		@~english	@brief	Recommended representation of a node value.
		@~english	@details	Recommended representation of a node value.
		@~japanese	@brief	ノード値表現方法列挙子
		@~japanese	@details	ノード値表現方法列挙子
	*/
	typedef enum _ERepresentation
	{
		/*!
			@~english	@details	Slider with linear behavior.
			@~japanese	@details	直線的な振る舞いをするスライダー
		*/
		Linear,

		/*!
			@~english	@details	Slider with logarithmic behaviour.
			@~japanese	@details	対数的な振る舞いをするスライダー
		*/
		Logarithmic,

		/*!
			@~english	@details	Check box.
			@~japanese	@details	チェックボックス
		*/
		Boolean,

		/*!
			@~english	@details	Decimal number in an edit control.
			@~japanese	@details	10進数エディットボックス
		*/
		PureNumber,

		/*!
			@~english	@details	Hex number in an edit control.
			@~japanese	@details	16進数エディットボックス
		*/
		HexNumber,

		/*!
			@~english	@details	IP-Address.
			@~japanese	@details	IPアドレス
		*/
		IPV4Address,

		/*!
			@~english	@details	MAC-Address.
			@~japanese	@details	MACアドレス
		*/
		MACAddress,
		_UndefinedRepresentation
	} ERepresentation;
	
	/*!
		@ingroup	GenApi_PublicImpl
		@~english	@brief	Defines if a node name is standard or custom.
		@~english	@details	Defines if a node name is standard or custom.
		@~japanese	@brief	ノード名ネームスペース列挙子
		@~japanese	@details	ノード名ネームスペース列挙子
	*/
	typedef enum _ENameSpace
	{
		/*!
			@~english	@details	Name resides in custom namespace.
			@~japanese	@details	カスタムネームスペース
		*/
		Custom,

		/*!
			@~english	@details	Name resides in one of the standard namespaces.
			@~japanese	@details	標準ネームスペース
		*/
		Standard,

		/*!
			@~english	@details	Object is not yet initialized.
			@~japanese	@details	定義されていないネームスペース
		*/
		_UndefinedNameSpace
	} ENameSpace;
	
	/*!
		@ingroup	GenApi_PublicImpl
		@~english	@brief	Defines the choices of a Yes/No alternaitve.
		@~english	@details	Defines the choices of a Yes/No alternaitve.
		@~japanese	@brief	Yes/No列挙子
		@~japanese	@details	Yes/No列挙子
	*/
	typedef enum _EYesNo
	{
		/*!
			@~english	@details	No.
			@~japanese	@details	No
		*/
		No = 0, 

		/*!
			@~english	@details	Yes.
			@~japanese	@details	Yes
		*/
		Yes = 1,

		/*!
			@~english	@details	Object is not yet initialized.
			@~japanese	@details	定義されていないYes/No列挙子
		*/
		_UndefinedYesNo = 2
	} EYesNo;
	
	/*!
		@ingroup	GenApi_PublicImpl
		@~english	@brief	Typedef for float notation.
		@~english	@details	Typedef for float notation.
		@~japanese	@brief	浮動小数点表記方法列挙子
		@~japanese	@details	浮動小数点表記方法列挙子
	*/
	typedef enum _EDisplayNotation
	{
		/*!
			@~english	@details	The notation if either scientific or fixed depending on what is shorter.
			@~japanese	@details	固定小数点表記または指数表記の短い表記
		*/
		fnAutomatic,

		/*!
			@~english	@details	The notation is fixed, e.g. 123.4.
			@~japanese	@details	固定小数点表記(例:123.4)
		*/
		fnFixed,

		/*!
			@~english	@details	The notation is scientific, e.g. 1.234e2.
			@~japanese	@details	指数表記(例:1.234e2)
		*/
		fnScientific,

		/*!
			@~english	@details	Object is not yet initialized.
			@~japanese	@details	定義されていない表記
		*/
		_UndefinedEDisplayNotation
	} EDisplayNotation;

	/*!
		@ingroup	GenApi_PublicImpl
		@~english	@brief	Typedef for interface type.
		@~english	@details	Typedef for interface type.
		@~japanese	@brief	インターフェースタイプ列挙子
		@~japanese	@details	インターフェースタイプ列挙子
	*/
	typedef enum _EInterfaceType
	{
		/*!
			@~english	@details	IValue interface.
			@~japanese	@details	IValue インターフェース
		*/
		intfIValue,

		/*!
			@~english	@details	IBase interface.
			@~japanese	@details	IBase インターフェース
		*/
		intfIBase,

		/*!
			@~english	@details	IInteger interface.
			@~japanese	@details	IInteger インターフェース
		*/
		intfIInteger,

		/*!
			@~english	@details	IBoolean interface.
			@~japanese	@details	IBoolean インターフェース
		*/
		intfIBoolean,

		/*!
			@~english	@details	ICommand interface.
			@~japanese	@details	ICommand インターフェース
		*/
		intfICommand,

		/*!
			@~english	@details	IFloat interface.
			@~japanese	@details	IFloat インターフェース
		*/
		intfIFloat,

		/*!
			@~english	@details	IString interface.
			@~japanese	@details	IString インターフェース
		*/
		intfIString,

		/*!
			@~english	@details	IRegister interface.
			@~japanese	@details	IRegister インターフェース
		*/
		intfIRegister,

		/*!
			@~english	@details	ICategory interface.
			@~japanese	@details	ICategory インターフェース
		*/
		intfICategory,

		/*!
			@~english	@details	IEnumeration interface.
			@~japanese	@details	IEnumeration インターフェース
		*/
		intfIEnumeration,

		/*!
			@~english	@details	IEnumEntry interface.
			@~japanese	@details	IEnumEntry インターフェース
		*/
		intfIEnumEntry,

		/*!
			@~english	@details	IPort interface.
			@~japanese	@details	IPort インターフェース
		*/
		intfIPort
	} EInterfaceType;
	
	/*!
		@ingroup	GenApi_PublicImpl
		@~english	@brief	Typedef for link type.
		@~english	@details	Typedef for link type.
		@~japanese	@brief	リンクタイプ列挙子
		@~japanese	@details	リンクタイプ列挙子
	*/
	typedef enum _ELinkType
	{
		/*!
			@~english	@details	All nodes for which this node is at least an invalidating child.
			@~japanese	@details	このノードが ctInvalidatingChildren に含んでいるすべてのノード
		*/
		ctParentNodes,

		/*!
			@~english	@details	All nodes which can be read from.
			@~japanese	@details	このノードが読み込みを行うすべてのノード
		*/
		ctReadingChildren,

		/*!
			@~english	@details	All nodes which can write a value further down the node stack.
			@~japanese	@details	このノードが書き込みを行うすべてのノード
		*/
		ctWritingChildren,

		/*!
			@~english	@details	All directly connected nodes which invalidate this node.
			@~japanese	@details	このノードのキャッシュを無効化する直接接続されたすべてのノード
		*/
		ctInvalidatingChildren,

		/*!
			@~english	@details	All directly or indirectly connected nodes which are invalidated by this nodes (i.e. which are dependent on this node).
			@~japanese	@details	このノードによりキャッシュが無効化される(このノードに依存している)すべてのノード
		*/
		ctDependingNodes,

		/*!
			@~english	@details	All indirectly connected terminal nodes.
			@~japanese	@details	接続されたすべての終端ノード
		*/
		ctTerminalNodes
	} ELinkType;
	
	/*!
		@ingroup	GenApi_PublicImpl
		@~english	@brief	Typedef for increment mode.
		@~english	@details	Typedef for increment mode.
		@~japanese	@brief	インクリメントモード列挙子
		@~japanese	@details	インクリメントモード列挙子
	*/
	typedef enum _EIncMode
	{
		/*!
			@~english	@details	The feature has no increment.
			@~japanese	@details	インクリメントなし
		*/
		noIncrement,

		/*!
			@~english	@details	The feature has a fix increment.
			@~japanese	@details	固定値インクリメント
		*/
		fixedIncrement,

		/*!
			@~english	@details	The feature has a list of valid value.
			@~japanese	@details	有効値リスト
		*/
		listIncrement
	} EIncMode;
#endif
#endif /* STGENAPI_DEF_H__ */
