//------------------------------------------------------------------------------
//  StApi
//------------------------------------------------------------------------------
/*!
	@ingroup	StApiTL_PublicInterface
	@file
	@~english	@details	Definition of interface IStInterfaceInfo and IStInterface
	@~japanese	@details	IStInterfaceInfo インターフェースおよび IStInterface インターフェースの定義
*/
#ifndef ISTINTERFACE_H__
#define ISTINTERFACE_H__

#include "IStDevice.h"
namespace StApi
{
	// ---------------------------------------------------------------------
	// interface IStInterfaceInfo
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiTL_PublicInterface
		@interface IStInterfaceInfo
		@~english	@brief	Interface for accessing Interface module information.
		@~english	@details	Interface for accessing Interface module information.
		@~japanese	@brief	インターフェース情報用インターフェース
		@~japanese	@details	インターフェース情報用インターフェース
	*/
	interface PUBLIC_INTERFACE IStInterfaceInfo
	{
		/*!
			@~english	@brief	GenTL::IFInfo() is used to get information of GenTL::INTERFACE_INFO_ID.
			@~english	@details	GenTL::IFInfo() is used to get information of GenTL::INTERFACE_INFO_ID.
			@~english	@return	INTERFACE_INFO_ID data.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or GenTL::IFInfo() is failed.
			@~japanese	@brief	GenTL::IFInfo() を使用して GenTL::INTERFACE_INFO_ID の情報を取得します。
			@~japanese	@details	GenTL::IFInfo() を使用して GenTL::INTERFACE_INFO_ID の情報を取得します。
			@~japanese	@return	INTERFACE_INFO_ID データ
			@~japanese	@exception	メモリー確保に失敗した場合や GenTL::IFInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual GenICam::gcstring GetID() const = 0;

		/*!
			@~english	@brief	GenTL::IFInfo() is used to get information of GenTL::INTERFACE_INFO_DISPLAYNAME.
			@~english	@details	GenTL::IFInfo() is used to get information of GenTL::INTERFACE_INFO_DISPLAYNAME.
			@~english	@return	INTERFACE_INFO_DISPLAYNAME data.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or GenTL::IFInfo() is failed.
			@~japanese	@brief	GenTL::IFInfo() を使用して GenTL::INTERFACE_INFO_DISPLAYNAME の情報を取得します。
			@~japanese	@details	GenTL::IFInfo() を使用して GenTL::INTERFACE_INFO_DISPLAYNAME の情報を取得します。
			@~japanese	@return	INTERFACE_INFO_DISPLAYNAME データ
			@~japanese	@exception	メモリー確保に失敗した場合や GenTL::IFInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual GenICam::gcstring GetDisplayName() const = 0;

		/*!
			@~english	@brief	GenTL::IFInfo() is used to get information of GenTL::INTERFACE_INFO_TLTYPE.
			@~english	@details	GenTL::IFInfo() is used to get information of GenTL::INTERFACE_INFO_TLTYPE.
			@~english	@return	INTERFACE_INFO_TLTYPE data.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or GenTL::IFInfo() is failed.
			@~japanese	@brief	GenTL::IFInfo() を使用して GenTL::INTERFACE_INFO_TLTYPE の情報を取得します。
			@~japanese	@details	GenTL::IFInfo() を使用して GenTL::INTERFACE_INFO_TLTYPE の情報を取得します。
			@~japanese	@return	INTERFACE_INFO_TLTYPE データ
			@~japanese	@exception	メモリー確保に失敗した場合や GenTL::IFInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual GenICam::gcstring GetTLType() const = 0;
	};

	// ---------------------------------------------------------------------
	// interface IStInterface
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiTL_PublicInterface
		@interface IStInterface
		@~english	@brief	Interface for the Interface module.
		@~english	@details	Interface for the Interface module.
		@~japanese	@brief	インターフェース用インターフェース
		@~japanese	@details	インターフェース用インターフェース
	*/
	interface IStSystem;
	interface PUBLIC_INTERFACE IStInterface : public IStRegisterCallback, public IStEventCtrl
	{
		/*!
			@~english	@brief	Acquire IStSystem interface pointer.
			@~english	@details	Acquire IStSystem interface pointer.
			@~english	@return	IStSystem Interface pointer.
			@~english	@exception	None.
			@~japanese	@brief	IStSystem インターフェースポインターを取得します。
			@~japanese	@details	IStSystem インターフェースポインターを取得します。
			@~japanese	@return	IStSystem インターフェースポインター
			@~japanese	@exception	なし
		*/
		virtual IStSystem*	GetIStSystem() = 0;

		/*!
			@~english	@brief	Acquire IStPort interface pointer.
			@~english	@details	Acquire IStPort interface pointer.
			@~english	@return	IStPort Interface pointer.
			@~english	@exception	None.
			@~japanese	@brief	IStPort インターフェースポインターを取得します。
			@~japanese	@details	IStPort インターフェースポインターを取得します。
			@~japanese	@return	IStPort インターフェースポインター
			@~japanese	@exception	なし
		*/
		virtual IStPort *GetIStPort() = 0;

		/*!
			@~english	@brief	Acquire IStInterfaceInfo interface pointer.
			@~english	@details	Acquire IStInterfaceInfo interface pointer.
			@~english	@return	IStInterfaceInfo Interface pointer.
			@~english	@exception	None.
			@~japanese	@brief	IStInterfaceInfo インターフェースポインターを取得します。
			@~japanese	@details	IStInterfaceInfo インターフェースポインターを取得します。
			@~japanese	@return	IStInterfaceInfo インターフェースポインター
			@~japanese	@exception	なし
		*/
		virtual const IStInterfaceInfo * GetIStInterfaceInfo() const = 0;

		/*!
			@~english	@brief	Scan for connected devices and update the device list.
			@~english	@details      Scan for connected devices and update the device list.
			@~english	@return	Return true if device list is updated.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or GenTL function is failed.
			@~japanese	@brief	接続されているデバイス(カメラ)を検出し、デバイス(カメラ)リストを更新します。
			@~japanese	@details	接続されているデバイス(カメラ)を検出し、デバイス(カメラ)リストを更新します。
			@~japanese	@return	デバイス(カメラ)リストが変更された場合 true が返されます。
			@~japanese	@exception	メモリー確保に失敗した場合や GenTL::IFUpdateDeviceList() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual bool UpdateDeviceList() = 0;

		/*!
			@~english	@brief	Acquire the timeout value for device scanning.
			@~english	@details	Acquire the timeout value for device scanning.
			@~english	@return	The timeout value for device scanning [ms].
			@~english	@exception	None.
			@~japanese	@brief	デバイス(カメラ)リスト更新時のタイムアウト時間を取得します。
			@~japanese	@details	デバイス(カメラ)リスト更新時のタイムアウト時間を取得します。
			@~japanese	@return	デバイス(カメラ)リスト更新時のタイムアウト時間[ms]
			@~japanese	@exception	なし
		*/
		virtual uint64_t GetUpdateDeviceListTimeout() const = 0;
		
		/*!
			@~english	@brief	Set the timeout value for device scanning.
			@~english	@details	Set the timeout value for device scanning.
			@~english	@param[in] iTimeout Set the timeout value for device scanning [ms].
			@~english	@exception	None.
			@~japanese	@brief	デバイス(カメラ)リスト更新時のタイムアウト時間を設定します。
			@~japanese	@details	デバイス(カメラ)リスト更新時のタイムアウト時間を設定します。
			@~japanese	@param[in] iTimeout デバイス(カメラ)リスト更新時のタイムアウト時間[ms]
			@~japanese	@exception	なし
		*/
		virtual void SetUpdateDeviceListTimeout(uint64_t iTimeout) = 0;

		/*!
			@~english	@brief	Get the number of the detected devices from calling UpdateDeviceList().
			@~english	@details	Get the number of the detected devices from calling UpdateDeviceList().
			@~english	@return	Number of the detected devices.
			@~english	@exception	None.
			@~japanese	@brief	認識されているデバイスの数を取得します。接続されたデバイスを認識させるには UpdateDeviceList() を呼び出します。
			@~japanese	@details	認識されているデバイスの数を取得します。接続されたデバイスを認識させるには UpdateDeviceList() を呼び出します。
			@~japanese	@return	認識されているデバイスの数
			@~japanese	@exception	なし
		*/
		virtual uint32_t GetDeviceCount() const = 0;

		/*!
			@~english	@brief	Acquire IStDeviceInfo interface pointer of a device.
			@~english	@details	Acquire IStDeviceInfo interface pointer of a device.
			@~english	@param[in] nIndex	Device index from 0 to (GetDeviceCount() - 1).
			@~english	@return	IStDeviceInfo interface pointer.
			@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument.
			@~japanese	@brief	指定したデバイスの IStDeviceInfo インターフェースポインターを取得します。
			@~japanese	@details	指定したデバイスの IStDeviceInfo インターフェースポインターを取得します。
			@~japanese	@param[in] nIndex	0から GetDeviceCount() 未満の値でデバイスを指定します。
			@~japanese	@return	IStDeviceInfo インターフェースポインター
			@~japanese	@exception	引数が不正な場合例外 GenICam::GenericException が発生します。
		*/
		virtual const IStDeviceInfo *GetIStDeviceInfo(size_t nIndex) const = 0;

		/*!
			@~english	@brief	Check if a device is accessible.
			@~english	@details  Check if a device is accessible.
			@~english	@param[in] nIndex	Device index from 0 to (GetDeviceCount() - 1).
			@~english	@param[in] eDeviceAccessFlags	Device access flag.
			@~english	@return	True if the device is accessible.
			@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument.
			@~japanese	@brief	指定したデバイス(カメラ)が利用可能かどうか確認します。
			@~japanese	@details	指定したデバイス(カメラ)が利用可能かどうか確認します。
			@~japanese	@param[in] nIndex	0から GetDeviceCount() 未満の値でデバイスを指定します。
			@~japanese	@param[in] eDeviceAccessFlags	デバイスアクセスフラグ
			@~japanese	@return	デバイス(カメラ)が利用可能な場合 true が返されます。
			@~japanese	@exception	引数が不正な場合例外 GenICam::GenericException が発生します。
		*/
		virtual bool IsDeviceAvailable(size_t nIndex, GenTL::DEVICE_ACCESS_FLAGS eDeviceAccessFlags) = 0;

		/*!
			@~english	@brief	Open Device module of GenTL and acquire IStDeviceReleasable interface pointer.
			@~english	@details	Open Device module of GenTL and acquire IStDeviceReleasable interface pointer.
			@~english	@attention	If IStDeviceReleasable interface pointer is no longer needed, call DeviceReleasable::Release() for release it.
			@~english	@param[in] nIndex	Device index from 0 to (GetDeviceCount() - 1).
			@~english	@return	IStDeviceReleasable Interface pointer.
			@~english	@param[in] eDeviceAccessFlags	Device access flag.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or there is an invalid argument or GenTL function is failed.
			@~japanese	@brief	指定したデバイス(カメラ)をオープンし IStDeviceReleasable インターフェースポインターを取得します。
			@~japanese	@details	指定したデバイス(カメラ)をオープンし IStDeviceReleasable インターフェースポインターを取得します。
			@~japanese	@attention	取得された IStDeviceReleasable インターフェースが不要になったら、 IStDeviceReleasable::Release() を呼び出して解放してください。
			@~japanese	@param[in] nIndex	0から GetDeviceCount() 未満の値でデバイスを指定します。
			@~japanese	@param[in] eDeviceAccessFlags	デバイスアクセスフラグ
			@~japanese	@return	IStDeviceReleasable インターフェースポインター
			@~japanese	@exception	メモリー確保に失敗した場合、不正な引数が指定された場合や GenTL 関数がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual IStDeviceReleasable* CreateIStDevice(size_t nIndex, GenTL::DEVICE_ACCESS_FLAGS eDeviceAccessFlags = GenTL::DEVICE_ACCESS_CONTROL) = 0;

		/*!
			@~english	@brief	Open Device module of GenTL and acquire IStDeviceReleasable interface pointer.
			@~english	@details	Open Device module of GenTL and acquire IStDeviceReleasable interface pointer.
			@~english	@attention	If IStDeviceReleasable interface pointer is no longer needed, call DeviceReleasable::Release() to release it.
			@~english	@param[in] strID	Device ID.
			@~english	@param[in] eDeviceAccessFlags	The way of access.
			@~english	@return	IStDeviceReleasable Interface pointer.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or there is an invalid argument or GenTL function is failed.
			@~japanese	@brief	指定したデバイス(カメラ)をオープンし IStDeviceReleasable インターフェースポインターを取得します。
			@~japanese	@details	指定したデバイス(カメラ)をオープンし IStDeviceReleasable インターフェースポインターを取得します。
			@~japanese	@attention	取得された IStDeviceReleasable インターフェースが不要になったら、 IStDeviceReleasable::Release() を呼び出して解放してください。
			@~japanese	@param[in] strID	デバイスIDを指定します。
			@~japanese	@param[in] eDeviceAccessFlags	デバイスアクセスフラグ
			@~japanese	@return	IStDeviceReleasable インターフェースポインター
			@~japanese	@exception	メモリー確保に失敗した場合、不正な引数が指定された場合や GenTL 関数がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual IStDeviceReleasable* CreateIStDevice(const GenICam::gcstring &strID, GenTL::DEVICE_ACCESS_FLAGS eDeviceAccessFlags = GenTL::DEVICE_ACCESS_CONTROL) = 0;

		/*!
			@~english	@brief	Open the first detected device module of GenTL (Device index is 0) and acquire IStDeviceReleasable interface pointer.
			@~english	@details	Open the first detected device module of GenTL (Device index is 0) and acquire IStDeviceReleasable interface pointer.
			@~english	@attention	If IStDeviceReleasable interface pointer is no longer needed, call DeviceReleasable::Release() to release it.
			@~english	@param[in] eDeviceAccessFlags	Device access flag.
			@~english	@return	IStDeviceReleasable Interface pointer.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed, or if there is an invalid argument, or if GenTL function is failed, or there are no avaliable cameras found.
			@~japanese	@brief	最初に見つかったデバイス(カメラ)をオープンし IStDeviceReleasable インターフェースポインターを取得します。
			@~japanese	@details	最初に見つかったデバイス(カメラ)をオープンし IStDeviceReleasable インターフェースポインターを取得します。
			@~japanese	@attention	取得された IStDeviceReleasable インターフェースが不要になったら、 IStDeviceReleasable::Release() を呼び出して解放してください。
			@~japanese	@param[in] eDeviceAccessFlags	デバイスアクセスフラグ
			@~japanese	@return	IStDeviceReleasable インターフェースポインター
			@~japanese	@exception	メモリー確保に失敗した場合、不正な引数が指定された場合、GenTL 関数がエラーを返した場合や利用可能なカメラが見つからない場合には、例外 GenICam::GenericException が発生します。
		*/
		virtual IStDeviceReleasable* CreateFirstIStDevice(GenTL::DEVICE_ACCESS_FLAGS eDeviceAccessFlags = GenTL::DEVICE_ACCESS_CONTROL) = 0;
	};
}
#endif //ISTINTERFACE_H__

