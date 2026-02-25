//------------------------------------------------------------------------------
// StApi
//------------------------------------------------------------------------------
/*!
	@ingroup	StApiGUI_PublicInterface
	@file
	@~english	@details	Definition of interface IStWnd
	@~japanese	@details	IStWnd インターフェースの定義
*/
#ifndef ISTWND_H__
#define ISTWND_H__


#include "StApi_IP.h"

#ifdef _MSC_VER
#pragma warning(push)	
#pragma warning(disable : 4819)	
#include "StApi_GUIDef.h"
#pragma warning(pop)	
#else
#include "StApi_GUIDef.h"
#endif

namespace StApi
{
	// ---------------------------------------------------------------------
	// interface IStWndInfo
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiGUI_PublicInterface
		@interface IStWndInfo
		@~english	@brief	Interface for Window information.
		@~english	@details	Interface for Window information.
		@~japanese	@brief	ウィンドウ情報用インターフェース
		@~japanese	@details	ウィンドウ情報用インターフェース
	*/
	interface PUBLIC_INTERFACE IStWndInfo
	{
		/*!
			@~english	@brief	Get the Window type.
			@~english	@details	Get the Window type.
			@~english	@return	Window type.
			@~english	@exception	None.
			@~japanese	@brief	ウィンドウタイプを取得します。
			@~japanese	@details	ウィンドウタイプを取得します。
			@~japanese	@return	ウィンドウタイプ
			@~japanese	@exception	なし
		*/
		virtual EStWindowType_t GetWndType() const = 0;

		/*!
			@~english	@brief	Get the Window name.
			@~english	@details	Get the Window name.
			@~english	@return	Window name.
			@~english	@exception	None.
			@~japanese	@brief	ウィンドウ名を取得します。
			@~japanese	@details	ウィンドウ名を取得します。
			@~japanese	@return	ウィンドウ名
			@~japanese	@exception	なし
		*/
		virtual GenICam::gcstring GetWndName() const = 0;
	};

	// ---------------------------------------------------------------------
	// interface IStWnd
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiGUI_PublicInterface
		@interface IStWnd
		@~english	@brief	Interface for Window.
		@~english	@details	Interface for Window.
		@~japanese	@brief	ウィンドウ用インターフェース
		@~japanese	@details	ウィンドウ用インターフェース
	*/
	interface PUBLIC_INTERFACE IStWnd : public IStRegisterCallback
	{
		/*!
			@~english	@brief	Get the IStWndInfo pointer.
			@~english	@details	Get the IStWndInfo pointer.
			@~english	@return	IStWndInfo pointer.
			@~english	@exception	None.
			@~japanese	@brief	IStWndInfo インターフェースポインターを取得します。
			@~japanese	@details	IStWndInfo インターフェースポインターを取得します。
			@~japanese	@return	IStWndInfo インターフェースポインター
			@~japanese	@exception	なし
		*/
		virtual IStWndInfo *GetIStWndInfo() const = 0;

		/*!
			@~english	@brief	Get the INodeMap pointer.
			@~english	@details	Get the INodeMap pointer.
			@~english	@return	INodeMap pointer.
			@~english	@exception	None.
			@~japanese	@brief	INodeMap インターフェースポインターを取得します。
			@~japanese	@details	INodeMap インターフェースポインターを取得します。
			@~japanese	@return	INodeMap インターフェースポインター
			@~japanese	@exception	なし
		*/
		virtual GenApi::INodeMap *GetINodeMap() = 0;

		/*!
			@~english	@brief	Get the Window handle. 
			@~english	@details	Get the Window handle.
			@~english	@return	Window handle. In Mac/Linux (Qt-based), HWND (void*) is a QWidget*.
			@~english	@exception	None.
			@~japanese	@brief	ウィンドウハンドルを取得します。
			@~japanese	@details	ウィンドウハンドルを取得します。
			@~japanese	@return	ウィンドウハンドル。Mac/Linux Qtの場合はHWND (void*)はQWidget*です。
			@~japanese	@exception	なし
		*/
		virtual HWND GetWindowHandle() = 0;

		/*!
			@~english	@brief	Get the title of the Window.
			@~english	@details	Get the title of the Window.
			@~english	@return	Title of the Window.
			@~english	@exception	None.
			@~japanese	@brief	ウィンドウタイトルを取得します。
			@~japanese	@details	ウィンドウタイトルを取得します。
			@~japanese	@return	ウィンドウタイトル
			@~japanese	@exception	なし
		*/
		virtual GenICam::gcstring GetTitle() = 0; 

		/*!
			@~english	@brief	Set the title of the Window.
			@~english	@details	Set the title of the Window.
			@~english	@param[in]	strTitle	Title of the Window.
			@~english	@exception	None.
			@~japanese	@brief	ウィンドウタイトルを設定します。
			@~japanese	@details	ウィンドウタイトルを設定します。
			@~japanese	@param[in]	strTitle	ウィンドウタイトル
			@~japanese	@exception	なし
		*/
		virtual void SetTitle(const GenICam::gcstring &strTitle) = 0;

		/*!
			@~english	@brief	Get the position and size of the Window.
			@~english	@details	Get the position and size of the Window.
			@~english	@param[out]	pnX	Horizontal position.
			@~english	@param[out]	pnY	Vertical position.
			@~english	@param[out]	pnWidth	Horizontal size.
			@~english	@param[out]	pnHeight	Vertical size.
			@~english	@exception	Throw out GenICam::GenericException when error occurred.
			@~japanese	@brief	ウィンドウの位置とサイズを取得します。
			@~japanese	@details	ウィンドウの位置とサイズを取得します。
			@~japanese	@param[out]	pnX	ウィンドウの横方向の位置
			@~japanese	@param[out]	pnY	ウィンドウの縦方向の位置
			@~japanese	@param[out]	pnWidth	ウィンドウの横方向のサイズ
			@~japanese	@param[out]	pnHeight	ウィンドウの縦方向のサイズ
			@~japanese	@exception	エラーが発生した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void GetPosition(int32_t *pnX, int32_t *pnY, int32_t *pnWidth, int32_t *pnHeight) = 0;

		/*!
			@~english	@brief	Set the position and size of the Window.
			@~english	@details	Set the position and size of the Window.
			@~english	@param[in]	nX	Horizontal position.
			@~english	@param[in]	nY	Vertical position.
			@~english	@param[in]	nWidth	Horizontal size.
			@~english	@param[in]	nHeight	Vertical size.
			@~english	@exception	Throw out GenICam::GenericException when error occurred.
			@~japanese	@brief	ウィンドウの位置とサイズを設定します。
			@~japanese	@details	ウィンドウの位置とサイズを設定します。
			@~japanese	@param[in]	nX	ウィンドウの横方向の位置
			@~japanese	@param[in]	nY	ウィンドウの縦方向の位置
			@~japanese	@param[in]	nWidth	ウィンドウの横方向のサイズ
			@~japanese	@param[in]	nHeight	ウィンドウの縦方向のサイズ
			@~japanese	@exception	エラーが発生した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void SetPosition(int32_t nX, int32_t nY, int32_t nWidth, int32_t nHeight) = 0;

		/*!
			@~english	@brief	Check the visibility of the Window.
			@~english	@details	Check the visibility of the Window.
			@~english	@return	 True if the Window is visible; false otherwise.
			@~english	@exception	None.
			@~japanese	@brief	ウィンドウが表示されているか確認します。
			@~japanese	@details	ウィンドウが表示されているか確認します。
			@~japanese	@return	 ウィンドウが表示されている場合、 true が返されます。
			@~japanese	@exception	なし
		*/
		virtual bool IsVisible() = 0;

		/*!
			@~english	@brief	Check the visibility of menu.
			@~english	@details	Check the visibility of menu.
			@~english	@return	 True if the menu is visible; false otherwise.
			@~english	@exception	None.
			@~japanese	@brief	ウィンドウメニューの表示/非表示設定を確認します。
			@~japanese	@details	ウィンドウメニューの表示/非表示設定を確認します。
			@~japanese	@return	 ウィンドウメニューが表示されている場合、 true が返されます。
			@~japanese	@exception	なし
		*/
		virtual bool GetVisibleMenu() const = 0;
		
		/*!
			@~english	@brief	Set the visibility of menu.
			@~english	@details	Set the visibility of menu.
			@~english	@param[in]	value	True to display menu; false to hide menu.
			@~english	@exception	None.
			@~japanese	@brief	ウィンドウメニューの表示/非表示を設定します。
			@~japanese	@details	ウィンドウメニューの表示/非表示を設定します。
			@~japanese	@param[in]	value	ウィンドウメニューを表示する場合、 true を指定します。
			@~japanese	@exception	なし
		*/
		virtual void SetVisibleMenu(bool value) = 0;

		/*!
			@~english	@brief	Check the visibility of status bar.
			@~english	@details	Check the visibility of status bar.
			@~english	@return	True if status bar is visible; false otherwise.
			@~english	@exception	None.
			@~japanese	@brief	ステータスバーの表示/非表示設定を確認します。
			@~japanese	@details	ステータスバーの表示/非表示設定を確認します。
			@~japanese	@return	ステータスバーが表示されている場合、 true が返されます。
			@~japanese	@exception	なし
		*/
		virtual bool GetVisibleStatusBar() const = 0;

		/*!
			@~english	@brief	Set the visibility of status bar.
			@~english	@details	Set the visibility of status bar.
			@~english	@param[in]	value	True to display status bar; false to hide status bar.
			@~english	@exception	None.
			@~japanese	@brief	ステータスバーの表示/非表示を設定します。
			@~japanese	@details	ステータスバーの表示/非表示を設定します。
			@~japanese	@param[in]	value	ステータスバーを表示する場合、 true を指定します。
			@~japanese	@exception	なし
		*/
		virtual void SetVisibleStatusBar(bool value) = 0;
		
		/*!
			@~english	@brief	Set the displayed text on status bar.
			@~english	@details	Set the displayed text on status bar.
			@~english	@param[in]	strText	The text to be displayed on the status bar.
			@~english	@exception	None.
			@~japanese	@brief	ステータスバーに表示するユーザー文字列を設定します。
			@~japanese	@details	ステータスバーに表示するユーザー文字列を設定します。
			@~japanese	@param[in]	strText	ステータスバーに表示するユーザー文字列
			@~japanese	@exception	なし
		*/
		virtual void SetUserStatusBarText(const GenICam::gcstring &strText) = 0;

		/*!
			@~english	@brief	Show the Window.
			@~english	@details	Show the Window.
			@~english	@param[in]	hParentWnd	Parent window handle.
			@~english	@param[in]	eWM	Window mode. In Mac/Linux (Qt-based), StWindowMode_ModalessOnNewThread is not supported (treated as StWindowMode_Modaless).
			@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument. 
			@~japanese	@brief	ウィンドウを表示します。
			@~japanese	@details	ウィンドウを表示します。
			@~japanese	@param[in]	hParentWnd	親ウィンドウハンドル
			@~japanese	@param[in]	eWM	ウィンドウモード。Mac/Linux Qt上に、StWindowMode_ModalessOnNewThreadを対応していません。
			@~japanese	@exception	不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void Show(HWND hParentWnd, EStWindowMode_t eWM) = 0;
		/*!
			@~english	@brief	Close the Window.
			@~english	@details	Close the Window.
			@~english	@exception	None.
			@~japanese	@brief	ウィンドウを閉じます。
			@~japanese	@details	ウィンドウを閉じます。
			@~japanese	@exception	なし
		*/
		virtual void Close() = 0;

	};

	// ---------------------------------------------------------------------
	// interface IStWndReleasable
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiGUI_PublicInterface
		@interface IStWndReleasable
		@~english	@brief	Interface for Releasable Window.
		@~english	@details	Interface for Releasable Window.
		@~japanese	@brief	解放可能なウィンドウ用インターフェース
		@~japanese	@details	解放可能なウィンドウ用インターフェース
	*/
	interface PUBLIC_INTERFACE IStWndReleasable : public IStWnd, public IStReleasable
	{

	};

	//---------------------------------------------------------------------
	// typedef CIStWndPtr
	//---------------------------------------------------------------------
	/*!
		@ingroup StApiGUI_PublicImpl
		@typedef CIStWndPtr
		@~english	@brief	The auto management class of IStWndReleasable class for window displaying.
		@~english	@details	The auto management class of IStWndReleasable class for window displaying.Use this class instead of managing the initial/release of IStWndReleasable class yourself. The destructor of this class will automatically call IStWndReleasable::Release().
		@~japanese	@brief	解放可能なウィンドウ用インターフェースポインターの自動管理用クラスです。
		@~japanese	@details	解放可能なウィンドウ用インターフェースポインターの自動管理用クラスです。このクラスのデストラクタから IStWndReleasable::Release() が自動的に呼び出されます。
	*/
	typedef CStAutoPtr<IStWndReleasable, IStWnd> CIStWndPtr;

	template<class T>
	class ST_API_GUI CIStWndPtrArrayT : public CStAutoPtrArray<IStWndReleasable, T>
	{
	public:
		CIStWndPtrArrayT();
		virtual ~CIStWndPtrArrayT();

		/*!
			@copydoc IStReleasable::Release
		*/
		void Release();
	private:
		// Copy is prohibited.
		CIStWndPtrArrayT(CIStWndPtrArrayT &rhs);

		// Copy is prohibited.
		CIStWndPtrArrayT & operator= (CIStWndPtrArrayT &rhs);

	};
	
	//---------------------------------------------------------------------
	// typedef CIStWndPtrArray
	//---------------------------------------------------------------------
	/*!
		@ingroup StApiGUI_PublicImpl
		@typedef CIStWndPtrArray
		@~english	@brief	This class manages the lifetime of classes derived from IStWndReleasable.
		@~english	@details	This class manages the lifetime of classes derived from IStWndReleasable. The destructor of this class will automatically call IStWndReleasable::Release().
		@~japanese	@brief	IStWndReleasable インターフェースポインターの自動管理用クラスです。
		@~japanese	@details	IStWndReleasable インターフェースポインターの自動管理用クラスです。このクラスのデストラクタから IStWndReleasable::Release() が自動的に呼び出されます。
	*/
	typedef CIStWndPtrArrayT<IStWnd> CIStWndPtrArray;

	// ---------------------------------------------------------------------
	// interface IStCallbackParamStApiGUIEventBaseWnd
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiGUI_PublicInterface
		@interface IStCallbackParamStApiGUIEventBaseWnd
		@~english	@brief	Interface for GUI Event.
		@~english	@details	Interface for GUI Event.
		@~japanese	@brief	IStCallbackParamStApiGUIEventBaseWnd インターフェース
		@~japanese	@details	IStCallbackParamStApiGUIEventBaseWnd インターフェース
	*/
	interface PUBLIC_INTERFACE IStCallbackParamStApiGUIEventBaseWnd : public IStCallbackParamBase
	{
		/*!
			@~english	@brief	Acquire IStWnd interface pointer.
			@~english	@details	Acquire IStWnd interface pointer.
			@~english	@return	IStWnd interface pointer.
			@~english	@exception	None.
			@~japanese	@brief	IStWnd インターフェースポインターを取得します。
			@~japanese	@details	IStWnd インターフェースポインターを取得します。
			@~japanese	@return	IStWnd インターフェースポインター
			@~japanese	@exception	なし
		*/
		virtual IStWnd *GetIStWnd() const = 0;
	};

	// ---------------------------------------------------------------------
	// interface IStCallbackParamStApiGUIEventBaseWndClose
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiGUI_PublicInterface
		@interface IStCallbackParamStApiGUIEventBaseWndClose
		@~english	@brief	Interface for GUI close event.
		@~english	@details	Interface for GUI close event.
		@~japanese	@brief	IStCallbackParamStApiGUIEventBaseWndClose インターフェース
		@~japanese	@details	IStCallbackParamStApiGUIEventBaseWndClose インターフェース
	*/
	interface PUBLIC_INTERFACE IStCallbackParamStApiGUIEventBaseWndClose : public IStCallbackParamStApiGUIEventBaseWnd
	{
		/*!
			@~english	@brief	Call if you want to cancel close.
			@~english	@details	Call if you want to cancel close.
			@~english	@exception	None.
			@~japanese	@brief	クローズ処理をキャンセルさせます。
			@~japanese	@details	クローズ処理をキャンセルさせます。
			@~japanese	@exception	なし
		*/
		virtual void CancelClose() = 0;
	};
	
	// ---------------------------------------------------------------------
	// interface IStCallbackParamStApiGUIEventBaseWndError
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiGUI_PublicInterface
		@interface IStCallbackParamStApiGUIEventBaseWndError
		@~english	@brief	Interface for GUI error event.
		@~english	@details	Interface for GUI error event.
		@~japanese	@brief	IStCallbackParamStApiGUIEventBaseWndError インターフェース
		@~japanese	@details	IStCallbackParamStApiGUIEventBaseWndError インターフェース
	*/
	interface PUBLIC_INTERFACE IStCallbackParamStApiGUIEventBaseWndError : public IStCallbackParamStApiGUIEventBaseWnd
	{
		/*!
			@~english	@brief	Acquire reference of GenericException.
			@~english	@details	Acquire reference of GenericException.
			@~english	@return	GenericException
			@~english	@exception	None.
			@~japanese	@brief	例外情報を取得します。
			@~japanese	@details	例外情報を取得します。
			@~japanese	@return	例外情報
			@~japanese	@exception	なし
		*/
		virtual const GenICam::GenericException &GetException() = 0;
	};


}

#endif //ISTWND_H__
