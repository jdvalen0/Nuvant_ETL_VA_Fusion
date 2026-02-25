//------------------------------------------------------------------------------
//  StApi
//------------------------------------------------------------------------------
/*!
@file
@~english	@details	Definition of interface IStDeviceInfo and IStDevice.
@~japanese	@details	IStDeviceInfo インターフェースおよび IStDevice インターフェースの定義
@ingroup	StApiTL_PublicInterface
*/
#ifndef ISTDEVICE_H__
#define ISTDEVICE_H__

#include "IStDataStream.h"

namespace StApi
{
	interface IStInterface;
	interface IStAllocator;

	// ---------------------------------------------------------------------
	// interface IStDeviceInfo
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiTL_PublicInterface
		@interface IStDeviceInfo
		@~english	@brief	Interface  for information about the Device module.
		@~english	@details	Interface  for information about the Device module.
		@~japanese	@brief	デバイス情報用インターフェース
		@~japanese	@details	デバイス情報用インターフェース
	*/
	interface PUBLIC_INTERFACE IStDeviceInfo
	{
		/*!
			@~english	@brief	GenTL::DevGetInfo() is used to get GenTL::DEVICE_INFO_ID data.
			@~english	@details	GenTL::DevGetInfo() is used to get GenTL::DEVICE_INFO_ID data.
			@~english	@return	DEVICE_INFO_ID data.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or GenTL::DevGetInfo() is failed.
			@~japanese	@brief	GenTL::DevGetInfo() を使用して GenTL::DEVICE_INFO_ID の情報を取得します。
			@~japanese	@details	GenTL::DevGetInfo() を使用して GenTL::DEVICE_INFO_ID の情報を取得します。
			@~japanese	@return	DEVICE_INFO_ID データ
			@~japanese	@exception	メモリー確保に失敗した場合や GenTL::DevGetInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual GenICam::gcstring GetID() const = 0;

		/*!
			@~english	@brief	GenTL::DevGetInfo() is used to get GenTL::DEVICE_INFO_VENDOR data.
			@~english	@details	GenTL::DevGetInfo() is used to get GenTL::DEVICE_INFO_VENDOR data.
			@~english	@return	DEVICE_INFO_VENDOR data.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or GenTL::DevGetInfo() is failed.
			@~japanese	@brief	GenTL::DevGetInfo() を使用して GenTL::DEVICE_INFO_VENDOR の情報を取得します。
			@~japanese	@details	GenTL::DevGetInfo() を使用して GenTL::DEVICE_INFO_VENDOR の情報を取得します。
			@~japanese	@return	DEVICE_INFO_VENDOR データ
			@~japanese	@exception	メモリー確保に失敗した場合や GenTL::DevGetInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual GenICam::gcstring GetVendor() const = 0;

		/*!
			@~english	@brief	GenTL::DevGetInfo() is used to get GenTL::DEVICE_INFO_MODEL data.
			@~english	@details	GenTL::DevGetInfo() is used to get GenTL::DEVICE_INFO_MODEL data.
			@~english	@return	DEVICE_INFO_MODEL data.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or GenTL::DevGetInfo() is failed.
			@~japanese	@brief	GenTL::DevGetInfo() を使用して GenTL::DEVICE_INFO_MODEL の情報を取得します。
			@~japanese	@details	GenTL::DevGetInfo() を使用して GenTL::DEVICE_INFO_MODEL の情報を取得します。
			@~japanese	@return	DEVICE_INFO_MODEL データ
			@~japanese	@exception	メモリー確保に失敗した場合や GenTL::DevGetInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual GenICam::gcstring GetModel() const = 0;

		/*!
			@~english	@brief	GenTL::DevGetInfo() is used to get GenTL::DEVICE_INFO_TLTYPE data.
			@~english	@details	GenTL::DevGetInfo() is used to get GenTL::DEVICE_INFO_TLTYPE data.
			@~english	@return	DEVICE_INFO_TLTYPE data.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or GenTL::DevGetInfo() is failed.
			@~japanese	@brief	GenTL::DevGetInfo() を使用して GenTL::DEVICE_INFO_TLTYPE の情報を取得します。
			@~japanese	@details	GenTL::DevGetInfo() を使用して GenTL::DEVICE_INFO_TLTYPE の情報を取得します。
			@~japanese	@return	DEVICE_INFO_TLTYPE データ
			@~japanese	@exception	メモリー確保に失敗した場合や GenTL::DevGetInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual GenICam::gcstring GetTLType() const = 0;

		/*!
			@~english	@brief	GenTL::DevGetInfo() is used to get GenTL::DEVICE_INFO_DISPLAYNAME data.
			@~english	@details	GenTL::DevGetInfo() is used to get GenTL::DEVICE_INFO_DISPLAYNAME data.
			@~english	@return	DEVICE_INFO_DISPLAYNAME data.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or GenTL::DevGetInfo() is failed.
			@~japanese	@brief	GenTL::DevGetInfo() を使用して GenTL::DEVICE_INFO_DISPLAYNAME の情報を取得します。
			@~japanese	@details	GenTL::DevGetInfo() を使用して GenTL::DEVICE_INFO_DISPLAYNAME の情報を取得します。
			@~japanese	@return	DEVICE_INFO_DISPLAYNAME データ
			@~japanese	@exception	メモリー確保に失敗した場合や GenTL::DevGetInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual GenICam::gcstring GetDisplayName() const = 0;

		/*!
			@~english	@brief	GenTL::DevGetInfo() is used to get GenTL::DEVICE_INFO_ACCESS_STATUS data.
			@~english	@details	GenTL::DevGetInfo() is used to get GenTL::DEVICE_INFO_ACCESS_STATUS data.
			@~english	@return	DEVICE_INFO_ACCESS_STATUS data.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or GenTL::DevGetInfo() is failed.
			@~japanese	@brief	GenTL::DevGetInfo() を使用して GenTL::DEVICE_INFO_ACCESS_STATUS の情報を取得します。
			@~japanese	@details	GenTL::DevGetInfo() を使用して GenTL::DEVICE_INFO_ACCESS_STATUS の情報を取得します。
			@~japanese	@return	DEVICE_INFO_ACCESS_STATUS データ
			@~japanese	@exception	メモリー確保に失敗した場合や GenTL::DevGetInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual GenTL::DEVICE_ACCESS_STATUS GetAccessStatus() const = 0;

		/*!
			@~english	@brief	GenTL::DevGetInfo() is used to get GenTL::DEVICE_INFO_USER_DEFINED_NAME data.
			@~english	@details	GenTL::DevGetInfo() is used to get GenTL::DEVICE_INFO_USER_DEFINED_NAME data.
			@~english	@return	DEVICE_INFO_USER_DEFINED_NAME data.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or GenTL::DevGetInfo() is failed.
			@~japanese	@brief	GenTL::DevGetInfo() を使用して GenTL::DEVICE_INFO_USER_DEFINED_NAME の情報を取得します。
			@~japanese	@details	GenTL::DevGetInfo() を使用して GenTL::DEVICE_INFO_USER_DEFINED_NAME の情報を取得します。
			@~japanese	@return	DEVICE_INFO_USER_DEFINED_NAME データ
			@~japanese	@exception	メモリー確保に失敗した場合や GenTL::DevGetInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual GenICam::gcstring GetUserDefinedName() const = 0;

		/*!
			@~english	@brief	GenTL::DevGetInfo() is used to get GenTL::DEVICE_INFO_SERIAL_NUMBER data.
			@~english	@details	GenTL::DevGetInfo() is used to get GenTL::DEVICE_INFO_SERIAL_NUMBER data.
			@~english	@return	DEVICE_INFO_SERIAL_NUMBER data.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or GenTL::DevGetInfo() is failed.
			@~japanese	@brief	GenTL::DevGetInfo() を使用して GenTL::DEVICE_INFO_SERIAL_NUMBER の情報を取得します。
			@~japanese	@details	GenTL::DevGetInfo() を使用して GenTL::DEVICE_INFO_SERIAL_NUMBER の情報を取得します。
			@~japanese	@return	DEVICE_INFO_SERIAL_NUMBER データ
			@~japanese	@exception	メモリー確保に失敗した場合や GenTL::DevGetInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual GenICam::gcstring GetSerialNumber() const = 0;

		/*!
			@~english	@brief	GenTL::DevGetInfo() is used to get GenTL::DEVICE_INFO_VERSION data.
			@~english	@details	GenTL::DevGetInfo() is used to get GenTL::DEVICE_INFO_VERSION data.
			@~english	@return	DEVICE_INFO_VERSION data.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or GenTL::DevGetInfo() is failed.
			@~japanese	@brief	GenTL::DevGetInfo() を使用して GenTL::DEVICE_INFO_VERSION の情報を取得します。
			@~japanese	@details	GenTL::DevGetInfo() を使用して GenTL::DEVICE_INFO_VERSION の情報を取得します。
			@~japanese	@return	DEVICE_INFO_VERSION データ
			@~japanese	@exception	メモリー確保に失敗した場合や GenTL::DevGetInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual GenICam::gcstring GetVersion() const = 0;

		/*!
			@~english	@brief	GenTL::DevGetInfo() is used to get GenTL::DEVICE_INFO_TIMESTAMP_FREQUENCY data.
			@~english	@details	GenTL::DevGetInfo() is used to get GenTL::DEVICE_INFO_TIMESTAMP_FREQUENCY data.
			@~english	@return	DEVICE_INFO_TIMESTAMP_FREQUENCY data.
			@~english	@exception	Throw out a GenICam::GenericException if GenTL::DevGetInfo() is failed.
			@~japanese	@brief	GenTL::DevGetInfo() を使用して GenTL::DEVICE_INFO_TIMESTAMP_FREQUENCY の情報を取得します。
			@~japanese	@details	GenTL::DevGetInfo() を使用して GenTL::DEVICE_INFO_TIMESTAMP_FREQUENCY の情報を取得します。
			@~japanese	@return	DEVICE_INFO_TIMESTAMP_FREQUENCY データ
			@~japanese	@exception	GenTL::DevGetInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual uint64_t GetTimestampFrequency() const = 0;
	};

	// ---------------------------------------------------------------------
	// interface IStDevice
	// ---------------------------------------------------------------------
	/*!
			@ingroup StApiTL_PublicInterface
			@interface IStDevice
			@~english	@brief	Interface for Device control.
			@~english	@details	Interface for Device control.
			@~japanese	@brief	デバイス用インターフェース
			@~japanese	@details	デバイス用インターフェース
	*/
	interface PUBLIC_INTERFACE IStDevice : public IStRegisterCallback, public IStEventCtrl
	{
		/*!
			@~english	@brief	Acquire IStInterface pointer.
			@~english	@details	Acquire IStInterface pointer.
			@~english	@return	IStInterface Interface pointer.
			@~english	@exception	None.
			@~japanese	@brief	IStInterface インターフェースポインターを取得します。
			@~japanese	@details	IStInterface インターフェースポインターを取得します。
			@~japanese	@return	IStInterface インターフェースポインター
			@~japanese	@exception	なし
		*/
		virtual IStInterface *GetIStInterface() = 0;

		/*!
			@~english	@brief	Acquire interface pointer of IStPort for local port. This is for GenTL device module to apply setting to host side.
			@~english	@details	Acquire interface pointer of IStPort for local port. This is for GenTL device module to apply setting to host side.
			@~english	@return	IStPort Interface pointer.
			@~english	@exception	None.
			@~japanese	@brief	ローカルポート用の IStPort インターフェースポインターを取得します。このポートはGenTLデバイスモジュールのホスト側の設定に使用されます。
			@~japanese	@details	ローカルポート用の IStPort インターフェースポインターを取得します。このポートはGenTLデバイスモジュールのホスト側の設定に使用されます。
			@~japanese	@return	IStPort インターフェースポインター
			@~japanese	@exception	なし
		*/
		virtual IStPort *GetLocalIStPort() = 0;

		/*!
			@~english	@brief	Acquire IStDeviceInfo interface pointer.
			@~english	@details	Acquire IStDeviceInfo interface pointer.
			@~english	@return	IStDeviceInfo Interface pointer.
			@~english	@exception	None.
			@~japanese	@brief	IStDeviceInfo インターフェースポインターを取得します。
			@~japanese	@details	IStDeviceInfo インターフェースポインターを取得します。
			@~japanese	@return	IStDeviceInfo インターフェースポインター
			@~japanese	@exception	なし
		*/
		virtual const IStDeviceInfo * GetIStDeviceInfo() const = 0;

		/*!
			@~english	@brief	Acquire interface pointer of IStPort for remote port. This is for GenTL device module to apply setting to camera side.
			@~english	@details	Acquire interface pointer of IStPort for remote port. This is for GenTL device module to apply setting to camera side.
			@~english	@return	IStPort Interface pointer.
			@~english	@exception	None.
			@~japanese	@brief	リモートポート用の IStPort インターフェースポインターを取得します。このポートはGenTLデバイスモジュールのデバイス(カメラ)側の設定に使用されます。
			@~japanese	@details	リモートポート用の IStPort インターフェースポインターを取得します。このポートはGenTLデバイスモジュールのデバイス(カメラ)側の設定に使用されます。
			@~japanese	@return	IStPort インターフェースポインター
			@~japanese	@exception	なし
		*/
		virtual IStPort *GetRemoteIStPort()  = 0;

		/*!
			@~english	@brief	Get the counts of DataStream.
			@~english	@details	Get the counts of DataStream.
			@~english	@return	Counts of DataStream.
			@~english	@exception	None.
			@~japanese	@brief	データストリームの数を取得します。
			@~japanese	@details	データストリームの数を取得します。
			@~japanese	@return	データストリームの数
			@~japanese	@exception	なし
		*/
		virtual uint32_t GetDataStreamCount() const = 0;

		/*!
			@~english	@brief	Open DataStream module of GenTL and acquire IStDataStreamReleasable interface pointer.
			@~english	@details	Open DataStream module of GenTL and acquire IStDataStreamReleasable interface pointer.
			@~english	@attention	If the acquired interface pointer of IStDataStreamReleasable does not needed anymore, call IStDataStreamReleasable::Release() to release it. 
			@~english	@param[in] nIndex	Index of the DataStream to open. It can be set as 0 to (GetDataStreamCount() - 1) .
			@~english	@param[in] pIStAllocator	IStAllocator interface pointer for allocating and releasing memory. If NULL, the buffer memory allocation and deallocation are managed by StApi.
			@~english	@return	IStDataStreamReleasable Interface pointer.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or there is an invalid argument or GenTL function is failed.
			@~english	@sa StApi::CIStDataStreamPtr
			@~japanese	@brief	データストリームをオープンし IStDataStreamReleasable インターフェースポインターを取得します。
			@~japanese	@details	データストリームをオープンし IStDataStreamReleasable インターフェースポインターを取得します。
			@~japanese	@attention	取得された IStDataStreamReleasable インターフェースが不要になったら、 IStDataStreamReleasable::Release() を呼び出して解放してください。
			@~japanese	@param[in] nIndex	0から GetDataStreamCount() 未満の値でデータストリームを指定します。
			@~japanese	@param[in] pIStAllocator	ストリーミングに使用されるバッファの割り当ておよび解放に使用される IStAllocator インターフェースポインターを指定します。NULLが指定された場合は、StApi内部でバッファの割り当ておよび解放が行われます。
			@~japanese	@return	IStDataStreamReleasable インターフェースポインター
			@~japanese	@exception	メモリー確保に失敗した場合、不正な引数が指定された場合や GenTL 関数がエラーを返した場合は、例外 GenICam::GenericException が発生します。
			@~japanese	@sa StApi::CIStDataStreamPtr
		*/
		virtual IStDataStreamReleasable* CreateIStDataStream(size_t nIndex = 0, IStAllocator *pIStAllocator = NULL) = 0;

		/*!
			@~english	@brief	Execute AcquisitionStart command to start data transmission.
			@~english	@details	Execute AcquisitionStart command to start data transmission.
			@~english	@attention	IStDataStream::StartAcquisition() must be called beforehand to enable data acquisition in the host side. To stop acquisition, AcquisitionStop() must be called.
			@~english	@exception	Throw out a GenICam::GenericException if an error occurred.
			@~english	@sa IStDataStream::StartAcquisition()
			@~japanese	@brief	カメラのAcquisitionStartコマンドを実行し、カメラからのデータ出力を開始します。
			@~japanese	@details	カメラのAcquisitionStartコマンドを実行し、カメラからのデータ出力を開始します。
			@~japanese	@attention	予め IStDataStream::StartAcquisition() を使用してホスト側のデータ取得を開始しておく必要があります。停止する場合は AcquisitionStop() を呼び出します。
			@~japanese	@exception	コマンドの実行に失敗した場合は、例外 GenICam::GenericException が発生します。
			@~japanese	@sa IStDataStream::StartAcquisition()
		*/
		virtual void AcquisitionStart() = 0;

		/*!
			@~english	@brief	Execute AcquisitionStop command to stop data transmission.
			@~english	@details	Execute AcquisitionStop command to stop data transmission.
			@~english	@attention	IStDataStream::StopAcquisition() must be called to stop the data acquisition in the host side.
			@~english	@exception	Throw out a GenICam::GenericException if an error occurred.
			@~english	@sa IStDataStream::StopAcquisition()
			@~japanese	@brief	カメラのAcquisitionStopコマンドを実行し、カメラからのデータ出力を停止します。
			@~japanese	@details	カメラのAcquisitionStopコマンドを実行し、カメラからのデータ出力を停止します。
			@~japanese	@attention	別途 IStDataStream::StopAcquisition() を使用してホスト側のデータ取得を停止する必要があります。
			@~japanese	@exception	コマンドの実行に失敗した場合は、例外 GenICam::GenericException が発生します。
			@~japanese	@sa IStDataStream::StopAcquisition()
		*/
		virtual void AcquisitionStop() = 0;

		/*!
			@~english	@brief	Check if the camera lost its connection.
			@~english	@details	    Check if the camera lost its connection.
			@~english	@attention	This will be only workable when DeviceLost event of GenTL is supported.
			@~english	@return	Return true if disconnected.
			@~english	@exception	None.
			@~japanese	@brief	デバイス(カメラ)との接続が切断されたかどうかを確認します。
			@~japanese	@details	デバイス(カメラ)との接続が切断されたかどうかを確認します。
			@~japanese	@attention	DeviceLost イベントがサポートされているGenTLモジュール使用時のみ正常な値が返されます。
			@~japanese	@return	デバイス(カメラ)との接続が切断されている場合、 true が返されます。
			@~japanese	@exception	なし
		*/
		virtual bool IsDeviceLost() = 0;
	};

	// ---------------------------------------------------------------------
	// interface IStDeviceReleasable
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiTL_PublicInterface
		@interface IStDeviceReleasable
		@~english	@brief	Interface for the Device Releasable module.
		@~english	@details	Interface for the Device Releasable module.
		@~japanese	@brief	解放可能なデバイス用インターフェース
		@~japanese	@details	解放可能なデバイス用インターフェース
	*/
	interface PUBLIC_INTERFACE IStDeviceReleasable : public IStDevice, public IStReleasable
	{

	};

	// ---------------------------------------------------------------------
	// typedef CIStDevicePtr
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiTL_PublicImpl
		@typedef CIStDevicePtr
		@~english	@brief	The auto management class of IStDeviceReleaseable for interface of the device module.
		@~english	@details	The auto management class of IStDeviceReleaseable for interface of the device module. Use this class instead of managing the initial/release of IStDeviceReleaseable class yourself. The destructor of this class will automatically call IStDeviceReleaseable::Release() for release the class object.
		@~japanese	@brief	IStDeviceReleasable インターフェースポインターの自動管理用クラスです。
		@~japanese	@details	IStDeviceReleasable インターフェースポインターの自動管理用クラスです。このクラスのデストラクタから IStDeviceReleasable::Release() が自動的に呼び出されます。
	*/
	typedef CStAutoPtr<IStDeviceReleasable, IStDevice> CIStDevicePtr;

	// ---------------------------------------------------------------------
	// class CIStDevicePtrArray
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiTL_PublicImpl
		@class CIStDevicePtrArray
		@~english	@brief	This class manages the lifetime of classes derived from IStDevice.
		@~english	@details	This class manages the lifetime of classes derived from IStDevice. The destructor of this class will automatically call IStDevice::Release().
		@~japanese	@brief	IStDeviceReleasable インターフェースポインターリストの自動管理用クラスです。
		@~japanese	@details	IStDeviceReleasable インターフェースポインターリストの自動管理用クラスです。このクラスのデストラクタから IStDeviceReleasable::Release() が自動的に呼び出されます。
	*/
	class ST_API_TL CIStDevicePtrArray : public CStAutoPtrArray<IStDeviceReleasable, IStDevice>
	{
	public:
		CIStDevicePtrArray();
		virtual ~CIStDevicePtrArray();

		/*!
			@~english	@brief	Call IStDeviceReleasable::Release() for all registered interfaces.
			@~english	@details	Call IStDeviceReleasable::Release() for all registered interfaces.
			@~english	@exception	None.
			@~japanese	@brief	登録されているインターフェースに対して IStDeviceReleasable::Release() を呼び出します。
			@~japanese	@details	登録されているインターフェースに対して IStDeviceReleasable::Release() を呼び出します。
			@~japanese	@exception	なし
		*/
		void Release();

		/*!
			@~english	@brief	Call IStDevice::AcquisitionStart() for all registered interfaces.
			@~english	@details	Call IStDevice::AcquisitionStart() for all registered interfaces.
			@~english	@exception	Throw out GenICam::GenericException when setting is failed.
			@~japanese	@brief	登録されているインターフェースに対して IStDevice::AcquisitionStart() を呼び出します。
			@~japanese	@details	登録されているインターフェースに対して IStDevice::AcquisitionStart() を呼び出します。
			@~japanese	@exception	コマンドの実行に失敗した場合は、例外 GenICam::GenericException が発生します。
		*/
		void AcquisitionStart();

		/*!
			@~english	@brief	Call IStDevice::AcquisitionStop() for all registered interfaces.
			@~english	@details	Call IStDevice::AcquisitionStop() for all registered interfaces.
			@~english	@exception	Throw out GenICam::GenericException when setting is failed.
			@~japanese	@brief	登録されているインターフェースに対して IStDevice::AcquisitionStop() を呼び出します。
			@~japanese	@details	登録されているインターフェースに対して IStDevice::AcquisitionStop() を呼び出します。
			@~japanese	@exception	コマンドの実行に失敗した場合は、例外 GenICam::GenericException が発生します。
		*/
		void AcquisitionStop();
	private:
		// Copy is prohibited.
		CIStDevicePtrArray(CIStDevicePtrArray &rhs);

		// Copy is prohibited.
		CIStDevicePtrArray & operator= (CIStDevicePtrArray &rhs);

	};
}
#endif //ISTDEVICE_H__

