//------------------------------------------------------------------------------
//  StApi
//------------------------------------------------------------------------------
/*!
	@ingroup	StApiGUI_PublicInterface
	@file
	@~english	@details	Definition of interface IStDeviceSelectionWnd
	@~japanese	@details	IStDeviceSelectionWnd インターフェースの定義
*/
#ifndef STDEVICESELECTIONWND_H
#define STDEVICESELECTIONWND_H

#include "IStWnd.h"

namespace StApi
{
	// ---------------------------------------------------------------------
	// interface IStDeviceSelectionWnd
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiGUI_PublicInterface
		@interface IStDeviceSelectionWnd
		@~english	@brief	Interface for Device Selection Window.
		@~english	@details	Interface for Device Selection Window.
		@~japanese	@brief	デバイス選択ウィンドウ用インターフェース
		@~japanese	@details	デバイス選択ウィンドウ用インターフェース
	*/
	interface PUBLIC_INTERFACE IStDeviceSelectionWnd :public IStWnd
	{
		/*!
			@~english	@brief	Register IStSystem interface pointer for device selection.
			@~english	@details	Register IStSystem interface pointer for device selection.
			@~english	@param[in]	pIStSystem	Interface pointer of pIStSystem for device selection.
			@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument. 
			@~japanese	@brief	デバイス選択に使用する IStSystem インターフェースポインターを登録します。
			@~japanese	@details	デバイス選択に使用する IStSystem インターフェースポインターを登録します。
			@~japanese	@param[in]	pIStSystem	デバイス選択に使用する IStSystem インターフェースポインター
			@~japanese	@exception	不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void RegisterTargetIStSystem(IStSystem *pIStSystem) = 0;

		/*!
			@~english	@brief	Register all IStSystem pointers in the list for device selection.
			@~english	@details	Register all IStSystem pointers in the list for device selection.
			@~english	@param[in]	objIStSystemPtrList	A List of IStSystem interface pointers for device selection.
			@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument. 
			@~japanese	@brief	デバイス選択に使用する IStSystem インターフェースポインターを登録します。
			@~japanese	@details	デバイス選択に使用する IStSystem インターフェースポインターを登録します。
			@~japanese	@param[in]	objIStSystemPtrList	デバイス選択に使用する IStSystem インターフェースポインターのリスト
			@~japanese	@exception	不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void RegisterTargetIStSystemList(CIStSystemPtrArray &objIStSystemPtrList) = 0;

		/*!
			@~english	@brief	Acquire the selected IStInterface interface pointer and its related IStDeviceInfo interface pointer.
			@~english	@details	Acquire the selected IStInterface interface pointer and its related IStDeviceInfo interface pointer.
			@~english	@param[in]	ppIStInterface	Pointer to the acquired IStInterface interface pointer.
			@~english	@param[in]	ppIStDeviceInfo	Pointer to the acquired IStDeviceInfo interface pointer.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed.
			@~japanese	@brief	選択されたデバイスの情報を取得します。
			@~japanese	@details	選択されたデバイスの情報を取得します。
			@~japanese	@param[in]	ppIStInterface	選択されたデバイスの IStInterface インターフェースポインター
			@~japanese	@param[in]	ppIStDeviceInfo	選択されたデバイスの IStDeviceInfo インターフェースポインター
			@~japanese	@exception	メモリー確保に失敗した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void GetSelectedDeviceInfo(IStInterface **ppIStInterface, const IStDeviceInfo **ppIStDeviceInfo) = 0;
	};

	//---------------------------------------------------------------------
	// typedef CIStDeviceSelectionWndPtr
	//---------------------------------------------------------------------
	/*!
		@ingroup StApiGUI_PublicImpl
		@typedef CIStDeviceSelectionWndPtr
		@~english	@brief	This class is for lifetime management of IStDeviceSelectionWnd.
		@~english	@details	This class is for lifetime management of IStDeviceSelectionWnd. The destructor of this class will automatically call IStWndReleasable::Release().
		@~japanese	@brief	IStDeviceSelectionWnd インターフェースポインターの自動管理用クラスです。
		@~japanese	@details	IStDeviceSelectionWnd インターフェースポインターの自動管理用クラスです。このクラスのデストラクタから IStWndReleasable::Release() が自動的に呼び出されます。
	*/
	typedef CStAutoPtr<IStWndReleasable, IStDeviceSelectionWnd> CIStDeviceSelectionWndPtr;

}
#endif //STDEVICESELECTIONWND_H
