//------------------------------------------------------------------------------
// StApi
//------------------------------------------------------------------------------
/*!
	@ingroup	StApiTL_PublicInterface
	@file
	@~english	@details	Definition of interface IStSystemInfo and IStSystem
	@~japanese	@details	IStSystemInfo インターフェースおよび IStSystem インターフェースの定義
*/
#ifndef ISTSYSTEM_H__
#define ISTSYSTEM_H__

#include "IStInterface.h"

namespace StApi
{
	interface IStRegisterCallback;

	// ---------------------------------------------------------------------
	// interface IStSystemInfo
	// ---------------------------------------------------------------------
	/*!
	 	@ingroup StApiTL_PublicInterface
		@interface IStSystemInfo
		@~english	@brief	Interface for accessing the System module information.
		@~english	@details	Interface for accessing the System module information.
		@~japanese	@brief	システム情報用インターフェース
		@~japanese	@details	システム情報用インターフェース
	*/
	interface PUBLIC_INTERFACE IStSystemInfo
	{
		/*!
			@~english	@brief	GenTL::TLInfo() is used to get the information of GenTL::TL_INFO_ID.
			@~english	@details	GenTL::TLInfo() is used to get the information of GenTL::TL_INFO_ID.
			@~english	@return	TL_INFO_ID data.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or GenTL::TLInfo() is failed.
			@~japanese	@brief	GenTL::TLInfo() を使用して GenTL::TL_INFO_ID の情報を取得します。
			@~japanese	@details	GenTL::TLInfo() を使用して GenTL::TL_INFO_ID の情報を取得します。
			@~japanese	@return	TL_INFO_ID データ
			@~japanese	@exception	メモリー確保に失敗した場合や GenTL::TLInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual GenICam::gcstring GetID() const = 0;

		/*!
			@~english	@brief	GenTL::TLInfo() is used to get the information of GenTL::TL_INFO_VENDOR.
			@~english	@details	GenTL::TLInfo() is used to get the information of GenTL::TL_INFO_VENDOR.
			@~english	@return	TL_INFO_VENDOR data.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or GenTL::TLInfo() is failed.
			@~japanese	@brief	GenTL::TLInfo() を使用して GenTL::TL_INFO_VENDOR の情報を取得します。
			@~japanese	@details	GenTL::TLInfo() を使用して GenTL::TL_INFO_VENDOR の情報を取得します。
			@~japanese	@return	TL_INFO_VENDOR データ
			@~japanese	@exception	メモリー確保に失敗した場合や GenTL::TLInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual GenICam::gcstring GetVendor() const = 0;

		/*!
			@~english	@brief	GenTL::TLInfo() is used to get the information of GenTL::TL_INFO_MODEL.
			@~english	@details	GenTL::TLInfo() is used to get the information of GenTL::TL_INFO_MODEL.
			@~english	@return	TL_INFO_MODEL data.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or GenTL::TLInfo() is failed.
			@~japanese	@brief	GenTL::TLInfo() を使用して GenTL::TL_INFO_MODEL の情報を取得します。
			@~japanese	@details	GenTL::TLInfo() を使用して GenTL::TL_INFO_MODEL の情報を取得します。
			@~japanese	@return	TL_INFO_MODEL データ
			@~japanese	@exception	メモリー確保に失敗した場合や GenTL::TLInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual GenICam::gcstring GetModel() const = 0;

		/*!
			@~english	@brief	GenTL::TLInfo() is used to get the information of GenTL::TL_INFO_VERSION.
			@~english	@details	GenTL::TLInfo() is used to get the information of GenTL::TL_INFO_VERSION.
			@~english	@return	TL_INFO_VERSION data.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or GenTL::TLInfo() is failed.
			@~japanese	@brief	GenTL::TLInfo() を使用して GenTL::TL_INFO_VERSION の情報を取得します。
			@~japanese	@details	GenTL::TLInfo() を使用して GenTL::TL_INFO_VERSION の情報を取得します。
			@~japanese	@return	TL_INFO_VERSION データ
			@~japanese	@exception	メモリー確保に失敗した場合や GenTL::TLInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual GenICam::gcstring GetVersion() const = 0;

		/*!
			@~english	@brief	GenTL::TLInfo() is used to get the information of GenTL::TL_INFO_TLTYPE.
			@~english	@details	GenTL::TLInfo() is used to get the information of GenTL::TL_INFO_TLTYPE.
			@~english	@return	TL_INFO_TLTYPE data.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or GenTL::TLInfo() is failed.
			@~japanese	@brief	GenTL::TLInfo() を使用して GenTL::TL_INFO_TLTYPE の情報を取得します。
			@~japanese	@details	GenTL::TLInfo() を使用して GenTL::TL_INFO_TLTYPE の情報を取得します。
			@~japanese	@return	TL_INFO_TLTYPE データ
			@~japanese	@exception	メモリー確保に失敗した場合や GenTL::TLInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual GenICam::gcstring GetTLType() const = 0;

		/*!
			@~english	@brief	GenTL::TLInfo() is used to get the information of GenTL::TL_INFO_NAME.
			@~english	@details	GenTL::TLInfo() is used to get the information of GenTL::TL_INFO_NAME.
			@~english	@return	TL_INFO_NAME data.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or GenTL::TLInfo() is failed.
			@~japanese	@brief	GenTL::TLInfo() を使用して GenTL::TL_INFO_NAME の情報を取得します。
			@~japanese	@details	GenTL::TLInfo() を使用して GenTL::TL_INFO_NAME の情報を取得します。
			@~japanese	@return	TL_INFO_NAME データ
			@~japanese	@exception	メモリー確保に失敗した場合や GenTL::TLInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual GenICam::gcstring GetName() const = 0;

		/*!
			@~english	@brief	GenTL::TLInfo() is used to get the information of GenTL::TL_INFO_PATHNAME.
			@~english	@details	GenTL::TLInfo() is used to get the information of GenTL::TL_INFO_PATHNAME.
			@~english	@return	TL_INFO_PATHNAME data.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or GenTL::TLInfo() is failed.
			@~japanese	@brief	GenTL::TLInfo() を使用して GenTL::TL_INFO_PATHNAME の情報を取得します。
			@~japanese	@details	GenTL::TLInfo() を使用して GenTL::TL_INFO_PATHNAME の情報を取得します。
			@~japanese	@return	TL_INFO_PATHNAME データ
			@~japanese	@exception	メモリー確保に失敗した場合や GenTL::TLInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual GenICam::gcstring GetPathName() const = 0;

		/*!
			@~english	@brief	GenTL::TLInfo() is used to get the information of GenTL::TL_INFO_DISPLAYNAME.
			@~english	@details	GenTL::TLInfo() is used to get the information of GenTL::TL_INFO_DISPLAYNAME.
			@~english	@return	TL_INFO_DISPLAYNAME data.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or GenTL::TLInfo() is failed.
			@~japanese	@brief	GenTL::TLInfo() を使用して GenTL::TL_INFO_DISPLAYNAME の情報を取得します。
			@~japanese	@details	GenTL::TLInfo() を使用して GenTL::TL_INFO_DISPLAYNAME の情報を取得します。
			@~japanese	@return	TL_INFO_DISPLAYNAME データ
			@~japanese	@exception	メモリー確保に失敗した場合や GenTL::TLInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual GenICam::gcstring GetDisplayName() const = 0;

		/*!
			@~english	@brief	GenTL::TLInfo() is used to get the information of GenTL::TL_INFO_CHAR_ENCODING.
			@~english	@details	GenTL::TLInfo() is used to get the information of GenTL::TL_INFO_CHAR_ENCODING.
			@~english	@return	TL_INFO_CHAR_ENCODING data.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or GenTL::TLInfo() is failed.
			@~japanese	@brief	GenTL::TLInfo() を使用して GenTL::TL_INFO_CHAR_ENCODING の情報を取得します。
			@~japanese	@details	GenTL::TLInfo() を使用して GenTL::TL_INFO_CHAR_ENCODING の情報を取得します。
			@~japanese	@return	TL_INFO_CHAR_ENCODING データ
			@~japanese	@exception	メモリー確保に失敗した場合や GenTL::TLInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual int32_t GetCharEncoding() const = 0;

		/*!
			@~english	@brief	GenTL::TLInfo() is used to get the information of GenTL::TL_INFO_GENTL_VER_MAJOR.
			@~english	@details	GenTL::TLInfo() is used to get the information of GenTL::TL_INFO_GENTL_VER_MAJOR.
			@~english	@return	TL_INFO_GENTL_VER_MAJOR data.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or GenTL::TLInfo() is failed.
			@~japanese	@brief	GenTL::TLInfo() を使用して GenTL::TL_INFO_GENTL_VER_MAJOR の情報を取得します。
			@~japanese	@details	GenTL::TLInfo() を使用して GenTL::TL_INFO_GENTL_VER_MAJOR の情報を取得します。
			@~japanese	@return	TL_INFO_GENTL_VER_MAJOR データ
			@~japanese	@exception	メモリー確保に失敗した場合や GenTL::TLInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual uint32_t GetGenTLVersionMajor() const = 0;

		/*!
			@~english	@brief	GenTL::TLInfo() is used to get the information of GenTL::TL_INFO_GENTL_VER_MINOR.
			@~english	@details	GenTL::TLInfo() is used to get the information of GenTL::TL_INFO_GENTL_VER_MINOR.
			@~english	@return	TL_INFO_GENTL_VER_MINOR data.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or GenTL::TLInfo() is failed.
			@~japanese	@brief	GenTL::TLInfo() を使用して GenTL::TL_INFO_GENTL_VER_MINOR の情報を取得します。
			@~japanese	@details	GenTL::TLInfo() を使用して GenTL::TL_INFO_GENTL_VER_MINOR の情報を取得します。
			@~japanese	@return	TL_INFO_GENTL_VER_MINOR データ
			@~japanese	@exception	メモリー確保に失敗した場合や GenTL::TLInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual uint32_t GetGenTLVersionMinor() const = 0;
	};

	// ---------------------------------------------------------------------
	// interface IStSystem
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiTL_PublicInterface
		@interface IStSystem
		@~english	@brief	Interface for the System module.
		@~english	@details	Interface for the System module.
		@~english	@sa	CreateIStSystem()
		@~japanese	@brief	システムモジュール用インターフェース
		@~japanese	@details	システムモジュール用インターフェース
		@~japanese	@sa	CreateIStSystem()
	*/
	interface PUBLIC_INTERFACE IStSystem : public IStRegisterCallback, public IStEventCtrl
	{
		/*!
			@~english	@brief	Acquire the value of EStSystemVendor_t when calling CreateIStSystem.
			@~english	@details	Acquire the value of EStSystemVendor_t when calling CreateIStSystem.
			@~english	@return	EStSystemVendor_t
			@~english	@exception	None.
			@~japanese	@brief	CreateIStSystem() 呼び出し時に指定された EStSystemVendor_t の値を取得します。
			@~japanese	@details	CreateIStSystem() 呼び出し時に指定された EStSystemVendor_t の値を取得します。
			@~japanese	@return	EStSystemVendor_t
			@~japanese	@exception	なし
		*/
		virtual EStSystemVendor_t GetStSystemVendor() = 0;

		/*!
			@~english	@brief	Acquire IStPort interface pointer.
			@~english	@details	Acquire IStPort interface pointer.
			@~english	@return	IStPort interface pointer.
			@~english	@exception	None.
			@~japanese	@brief	IStPort インターフェースポインターを取得します。
			@~japanese	@details	IStPort インターフェースポインターを取得します。
			@~japanese	@return	IStPort インターフェースポインター
			@~japanese	@exception	なし
		*/
		virtual IStPort *GetIStPort() = 0;

		/*!
			@~english	@brief	Acquire IStSystemInfo interface pointer.
			@~english	@details	Acquire IStSystemInfo interface pointer.
			@~english	@return	IStSystemInfo interface pointer.
			@~english	@exception	None.
			@~japanese	@brief	IStSystemInfo インターフェースポインターを取得します。
			@~japanese	@details	IStSystemInfo インターフェースポインターを取得します。
			@~japanese	@return	IStSystemInfo インターフェースポインター
			@~japanese	@exception	なし
		*/
		virtual const IStSystemInfo * GetIStSystemInfo() const = 0;
		
		/*!
			@~english	@brief	Check the currently available interfaces on this system and update the interface list.
			@~english	@details	Check the currently available interfaces on this system and update the interface list.
			@~english	@return	True if the interface list was changed and false otherwise.
			@~english	@exception	None.
			@~japanese	@brief	このシステムで現在利用可能なインターフェースを検出し、インターフェースリストを更新します。
			@~japanese	@details	このシステムで現在利用可能なインターフェースを検出し、インターフェースリストを更新します。
			@~japanese	@return	インターフェースリストが更新された場合、 true が返されます。
			@~japanese	@exception	なし
		*/
		virtual bool UpdateInterfaceList() = 0;

		/*!
			@~english	@brief	Get the number of available interfaces on this system.
			@~english	@details	Get the number of available interfaces on this system.
			@~english	@return	Number of the available interfaces on this system.
			@~english	@exception	None.
			@~japanese	@brief	このシステムで現在使用可能なインターフェースの数を取得します。
			@~japanese	@details	このシステムで現在使用可能なインターフェースの数を取得します。
			@~japanese	@return	現在使用可能なインターフェースの数
			@~japanese	@exception	なし
		*/
		virtual uint32_t GetInterfaceCount() const = 0;

		/*!
			@~english	@brief	Get IStInterface interface pointer.
			@~english	@details	Get IStInterface interface pointer.
			@~english	@param[in]	nIndex	Index of the target interface from 0 to GetInterfaceCount()-1.
			@~english	@return	IStInterface interface pointer.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or there is an invalid argument or GenTL function is failed.
			@~japanese	@brief	指定された IStInterface インターフェースポインターを取得します。
			@~japanese	@details	指定された IStInterface インターフェースポインターを取得します。
			@~japanese	@param[in]	nIndex	0から GetInterfaceCount() で取得した数未満の値でインターフェースを指定します。
			@~japanese	@return	IStInterface インターフェースポインター
			@~japanese	@exception	メモリー確保に失敗した場合、不正な引数が指定された場合や GenTL 関数がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual IStInterface* GetIStInterface(size_t nIndex) = 0;

		/*!
			@~english	@brief	Acquire IStDeviceReleasable interface for the first device found (Device index = 0). 
			@~english	@details	Acquire IStDeviceReleasable interface for the first device found (Device index = 0).
			@~english	@attention	If IStDeviceReleasable interface pointer is no longer needed, call IStDeviceReleasable::Release().
			@~english	@param[in] eDeviceAccessFlags	Device access flag.
			@~english	@return	Return IStDeviceReleasable interface pointer.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or there is an invalid argument or GenTL function is failed.
			@~japanese	@brief	このシステムで最初に見つかったデバイスを作成し、 IStDeviceReleasable インターフェースポインターを取得します。
			@~japanese	@details	このシステムで最初に見つかったデバイスを作成し、 IStDeviceReleasable インターフェースポインターを取得します。
			@~japanese	@attention	取得された IStDeviceReleasable インターフェースが不要になったら、 IStDeviceReleasable::Release() を呼び出して解放してください。
			@~japanese	@param[in] eDeviceAccessFlags	デバイスアクセスフラグを指定します。
			@~japanese	@return	IStDeviceReleasable インターフェースポインター
			@~japanese	@exception	メモリー確保に失敗した場合、不正な引数が指定された場合や GenTL 関数がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual IStDeviceReleasable* CreateFirstIStDevice(GenTL::DEVICE_ACCESS_FLAGS eDeviceAccessFlags = GenTL::DEVICE_ACCESS_CONTROL) = 0;
	};

	// ---------------------------------------------------------------------
	// interface IStSystemReleasable
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiTL_PublicInterface
		@interface IStSystemReleasable
		@~english	@brief	Interface for the System Releasable module.
		@~english	@details	Interface for the System Releasable module.
		@~english	@sa	CreateIStSystem()
		@~japanese	@brief	解放可能なシステムモジュール用インターフェース
		@~japanese	@details	解放可能なシステムモジュール用インターフェース
		@~japanese	@sa	CreateIStSystem()
	*/
	interface PUBLIC_INTERFACE IStSystemReleasable : public IStSystem, public IStReleasable
	{
	};

	// ---------------------------------------------------------------------
	// typedef CIStSystemPtr
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiTL_PublicImpl
		@typedef CIStSystemPtr
		@~english	@brief	The auto management class of IStSystemReleasable class for acquiring information about the System module.
		@~english	@details	The auto management class of IStSystemReleasable class for acquiring information about the System module. Use this class instead of managing the initial/release of IStSystemReleasable class yourself. The destructor of this class will automatically call IStSystemReleasable::Release() for release the class object.
		@~japanese	@brief	IStSystemReleasable インターフェースポインターの自動管理用クラスです。
		@~japanese	@details	IStSystemReleasable インターフェースポインターの自動管理用クラスです。このクラスのデストラクタから IStSystemReleasable::Release() が自動的に呼び出されます。
	*/
	typedef CStAutoPtr<IStSystemReleasable, IStSystem> CIStSystemPtr;

	// ---------------------------------------------------------------------
	// class CIStSystemPtrArray
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiTL_PublicImpl
		@class CIStSystemPtrArray
		@~english	@brief	This class manages the lifetime of classes derived from IStSystemReleasable.
		@~english	@details	This class manages the lifetime of classes derived from IStSystemReleasable. The destructor of this class will automatically call IStSystemReleasable::Release().
		@~japanese	@brief	IStSystemReleasable インターフェースポインターリストの自動管理用クラスです。
		@~japanese	@details	IStSystemReleasable インターフェースポインターリストの自動管理用クラスです。このクラスのデストラクタから IStSystemReleasable::Release() が自動的に呼び出されます。
	*/
	class ST_API_TL CIStSystemPtrArray : public CStAutoPtrArray<IStSystemReleasable, IStSystem>
	{
	public:
		CIStSystemPtrArray();
		virtual ~CIStSystemPtrArray();

		/*!
			@~english	@brief	Acquire IStDeviceReleasable interface for the first device found (Device index = 0) in the system module. 
			@~english	@details	Acquire IStDeviceReleasable interface for the first device found (Device index = 0) in the system module. 
			@~english	@attention	If the IStDeviceReleasable interface pointer is no longer needed, call IStDeviceReleasable::Release().
			@~english	@param[in] eDeviceAccessFlags	Device access flag.
			@~english	@return	Return IStDeviceReleasable interface pointer.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or there is an invalid argument or GenTL function is failed.
			@~japanese	@brief	システムで最初に見つかったデバイスを作成し、 IStDeviceReleasable インターフェースポインターを取得します。
			@~japanese	@details	システムで最初に見つかったデバイスを作成し、 IStDeviceReleasable インターフェースポインターを取得します。
			@~japanese	@attention	取得された IStDeviceReleasable インターフェースが不要になったら、 IStDeviceReleasable::Release() を呼び出して解放してください。
			@~japanese	@param[in] eDeviceAccessFlags	デバイスアクセスフラグを指定します。
			@~japanese	@return	IStDeviceReleasable インターフェースポインター
			@~japanese	@exception	メモリー確保に失敗した場合、不正な引数が指定された場合や GenTL 関数がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		IStDeviceReleasable* CreateFirstIStDevice(GenTL::DEVICE_ACCESS_FLAGS eDeviceAccessFlags = GenTL::DEVICE_ACCESS_CONTROL);

		/*!
			@~english	@brief	IStSystemReleasable::Release() is called for each registered system module.
			@~english	@details	IStSystemReleasable::Release() is called for each registered system module.
			@~english	@exception	None.
			@~japanese	@brief	登録されているインターフェースに対して IStSystemReleasable::Release() を呼び出します。
			@~japanese	@details	登録されているインターフェースに対して IStSystemReleasable::Release() を呼び出します。
			@~japanese	@exception	なし
		*/
		void Release();
	private:
		// Copy is prohibited.
		CIStSystemPtrArray(CIStSystemPtrArray &rhs);

		// Copy is prohibited.
		CIStSystemPtrArray & operator= (CIStSystemPtrArray &rhs);
	};
}
#endif //ISTSYSTEM_H__
