//------------------------------------------------------------------------------
//  StApi
//------------------------------------------------------------------------------
/*!
	@ingroup	StApiTL_PublicInterface
	@file
	@~english	@details	Definition of interface IStFeatureBag
	@~japanese	@details	IStFeatureBag インターフェースの定義
*/
#ifndef ISTFEATUREBAG_H__
#define ISTFEATUREBAG_H__

#include "CStAutoPtr.h"
#include "IStReleasable.h"

namespace StApi
{
	//---------------------------------------------------------------------
	// interface IStFeatureBag
	//---------------------------------------------------------------------
	/*!
		@ingroup StApiTL_PublicInterface
		@interface IStFeatureBag
		@~english	@brief	Interface for the StFeatureBag module.
		@~english	@details	Interface for the StFeatureBag module.
		@~english	@sa CreateIStFeatureBag()
		@~japanese	@brief	設定情報保持モジュール用インターフェース
		@~japanese	@details	設定情報保持モジュール用インターフェース
		@~japanese	@sa CreateIStFeatureBag()
	*/
	interface PUBLIC_INTERFACE IStFeatureBag
	{
		/*!
			@~english	@brief	Store streamable nodes to the feature bag.
			@~english	@details	Store streamable nodes to the feature bag.
			@~english	@param[in] pINodeMap	The node map to store.
			@~english	@param[in] MaxNumPersistScriptEntries	The max numbers of entries in the container; -1 means unlimited.
			@~english	@return	Number of entries in the bag
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or there is an invalid argument.
			@~japanese	@brief	指定したノードマップの設定情報をメモリーへ退避します。
			@~japanese	@details	指定したノードマップの設定情報をメモリーへ退避します。
			@~japanese	@param[in] pINodeMap	ノードマップ
			@~japanese	@param[in] MaxNumPersistScriptEntries	メモリーへ退避する項目数の最大値を指定します。-1を指定すると無制限になります。
			@~japanese	@return	退避された項目数
			@~japanese	@exception	メモリー確保に失敗した場合や不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual int64_t StoreNodeMapToBag(GenApi::INodeMap *pINodeMap, const int32_t MaxNumPersistScriptEntries = -1) = 0;

		/*!
			@~english	@brief	Store string to the FeatureBag.
			@~english	@details	Store string to the FeatureBag.
			@~english	@param[in] strFeatures	The string contents of setting and its value.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or there is an invalid argument.
			@~japanese	@brief	文字列で指定された設定情報をメモリーへ登録します。
			@~japanese	@details	文字列で指定された設定情報をメモリーへ登録します。
			@~japanese	@param[in] strFeatures	設定名と設定値を含んだ文字列
			@~japanese	@exception	メモリー確保に失敗した場合や不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void StoreStringToBag(const GenICam::gcstring &strFeatures) = 0;

		/*!
			@~english	@brief	Read data from saved file to the FeatureBag.
			@~english	@details	Read data from saved file to the FeatureBag.
			@~english	@param[in] strFileName	The setting file to read. This file must be created using SaveToFile() function.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or there is an invalid argument.
			@~japanese	@brief	ファイルへ保存された設定情報をメモリーへ登録します。
			@~japanese	@details	ファイルへ保存された設定情報をメモリーへ登録します。
			@~japanese	@param[in] strFileName	設定ファイル名
			@~japanese	@exception	メモリー確保に失敗した場合や不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void StoreFileToBag(const GenICam::gcstring &strFileName) = 0;

		/*!
			@~english	@brief	Loads features from the feature bag to the node tree.
			@~english	@details	Loads features from the feature bag to the node tree. If verify is set to true, the list of names in the feature bag will be re-read. If a node is a selector, its value is set to the value from the feature bag; otherwise, the value is read from the camera and compared with the value from the feature bag.
			@~english	@param[in] pNodeMap	The node map.
			@~english	@param[in] verify	If true, all streamable features will be re-read.
			@~english	@param[in] pstrErrorList	If an error occurs during loading, the error message is stored in the list and the loading continues
			@~english	@return	Return false if an error occurs during loading.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or there is an invalid argument.
			@~japanese	@brief	メモリーへ保存された設定情報をノードマップへ反映します。
			@~japanese	@details	メモリーへ保存された設定情報をノードマップへ反映します。
			@~japanese	@param[in] pNodeMap	反映先のノードマップ
			@~japanese	@param[in] verify	設定反映後に読み込み確認(ベリファイ)を行う場合は true を指定します。
			@~japanese	@param[in] pstrErrorList	設定反映時のエラーリスト
			@~japanese	@return	エラーが発生した場合、 false が返されます。
			@~japanese	@exception	メモリー確保に失敗した場合や不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual bool Load(GenApi::INodeMap *pNodeMap, bool verify = true, GenICam::gcstring_vector *pstrErrorList = NULL) = 0;

		/*!
			@~english	@brief	Acquire data from the FeatureBag.
			@~english	@details	Acquire data from the FeatureBag.
			@~english	@param[out] strFeatures	Data (String) containing the name and value of the settings stored in the feature bag.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or there is an invalid argument.
			@~japanese	@brief	メモリーへ保存された設定情報を文字列として取得します。
			@~japanese	@details	メモリーへ保存された設定情報を文字列として取得します。
			@~japanese	@param[out] strFeatures	設定名と設定値を含んだ文字列
			@~japanese	@exception	メモリー確保に失敗した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void SaveToString(GenICam::gcstring &strFeatures) = 0;

		/*!
			@~english	@brief	Save setting in the FeatureBag to a file.
			@~english	@details	Save setting in the FeatureBag to a file.
			@~english	@param[in] strFileName	File name.
			@~english	@exception	Throw out a GenICam::GenericException if file creation failed.
			@~japanese	@brief	メモリーへ保存された設定情報をファイルへ保存します。
			@~japanese	@details	メモリーへ保存された設定情報をファイルへ保存します。
			@~japanese	@param[in] strFileName	ファイル名。
			@~japanese	@exception	ファイル作成に失敗した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void SaveToFile(const GenICam::gcstring &strFileName) = 0;
	};
	
	//---------------------------------------------------------------------
	// interface IStFeatureBagReleasable
	//---------------------------------------------------------------------
	/*!
		@ingroup StApiTL_PublicInterface
		@interface IStFeatureBagReleasable
		@~english	@brief	Interface for the Feature Bag Releasable module.
		@~english	@details	Interface for the Feature Bag Releasable module.
		@~english	@sa CreateIStFeatureBag()
		@~japanese	@brief	解放可能な設定情報保持モジュール用インターフェース
		@~japanese	@details	解放可能な設定情報保持モジュール用インターフェース
		@~japanese	@sa CreateIStFeatureBag()
	*/
	interface PUBLIC_INTERFACE IStFeatureBagReleasable : public IStFeatureBag, public IStReleasable
	{

	};
	
	// ---------------------------------------------------------------------
	// typedef CIStFeatureBagPtr
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiTL_PublicImpl
		@typedef CIStFeatureBagPtr
		@~english	@brief	The auto management class of IStFeatureBagReleasable class for feature saving/loading with feature bag.
		@~english	@details	The auto management class of IStFeatureBagReleasable class for feature saving/loading with feature bag. Use this class instead of managing the initial/release of IStFeatureBagReleasable class yourself. The destructor of this class will automatically call IStFeatureBagReleasable::Release().
		@~japanese	@brief	IStFeatureBagReleasable インターフェースポインターの自動管理用クラスです。
		@~japanese	@details	IStFeatureBagReleasable インターフェースポインターの自動管理用クラスです。このクラスのデストラクタから IStFeatureBagReleasable::Release() が自動的に呼び出されます。
	*/
	typedef CStAutoPtr<IStFeatureBagReleasable, IStFeatureBag> CIStFeatureBagPtr;
}
#endif //ISTFEATUREBAG_H__




