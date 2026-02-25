//------------------------------------------------------------------------------
//  StApi
//------------------------------------------------------------------------------
/*!
	@ingroup	StApiGUI_PublicInterface
	@file
	@~english	@details	Definition of interface IStNodeMapDisplayWnd
	@~japanese	@details	IStNodeMapDisplayWnd インターフェースの定義
*/
#ifndef STDISPLAYNODEMAPWND_H
#define STDISPLAYNODEMAPWND_H

#include "IStWnd.h"

namespace StApi
{
	// ---------------------------------------------------------------------
	// typedef RegisteredINodeHandle_t
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiGUI_PublicImpl
		@typedef RegisteredINodeHandle_t
		@~english	@brief	A type identifier of the registered node.
		@~english	@details	A type identifier of the registered node.
		@~japanese	@brief	登録されたノード識別用ハンドル型
		@~japanese	@details	登録されたノード識別用ハンドル型
	*/
	typedef void* RegisteredINodeHandle_t;

	// ---------------------------------------------------------------------
	// interface IStNodeMapDisplayWnd
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiGUI_PublicInterface
		@interface IStNodeMapDisplayWnd
		@~english	@brief	Interface for Node Map Display Window.
		@~english	@details	Interface for Node Map Display Window.
		@~japanese	@brief	ノードマップ表示ウィンドウ用インターフェース
		@~japanese	@details	ノードマップ表示ウィンドウ用インターフェース
	*/
	interface PUBLIC_INTERFACE IStNodeMapDisplayWnd :public IStWnd
	{
		/*!
			@~english	@brief	Register the node to be displayed in the Nodemap settings window.
			@~english	@details	Register the node to be displayed in the Nodemap settings window.
			@~english	@param[in]	pIRootNode	Root node.
			@~english	@param[in]	strCaption	Caption for root node.
			@~english	@return	Identifier of registered node.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed.
			@~japanese	@brief	ノードマップ設定画面に表示するノードを登録します。
			@~japanese	@details	ノードマップ設定画面に表示するノードを登録します。
			@~japanese	@param[in]	pIRootNode	ノード
			@~japanese	@param[in]	strCaption	ノードに対するタイトル
			@~japanese	@return	登録ノード識別子
			@~japanese	@exception	メモリー確保に失敗した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual RegisteredINodeHandle_t RegisterINode(GenApi::INode *pIRootNode, const GenICam::gcstring &strCaption) = 0;
		
		/*!
			@~english	@brief	Deregister the node to be displayed in the Nodemap settings window.
			@~english	@details	Deregister the node to be displayed in the Nodemap settings window.
			@~english	@param[in]	hRegistered	Identifier of registered node.
			@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument. 
			@~japanese	@brief	ノードの登録を解除します。
			@~japanese	@details	ノードの登録を解除します。
			@~japanese	@param[in]	hRegistered	登録ノード識別子
			@~japanese	@exception	不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void DeregisterINode(RegisteredINodeHandle_t hRegistered) = 0;

		/*!
			@~english	@brief	Check if the list is displayed in alphabetical order (alphabetic mode).
			@~english	@details	Check if the list is displayed in alphabetical order (alphabetic mode).
			@~english	@return	True if the list is displayed in alphabetical order (alphabetic mode); false otherwise.
			@~english	@exception	None.
			@~japanese	@brief	アルファベットモードかどうかを確認します。
			@~japanese	@details	アルファベットモードかどうかを確認します。
			@~japanese	@return	アルファベットモードになっている場合、 true が返されます。
			@~japanese	@exception	なし
		*/
		virtual bool GetAlphabeticMode() const = 0;
		
		/*!
			@~english	@brief	Set alphabetic mode.
			@~english	@details	Set alphabetic mode.
			@~english	@param[in]	value	If true, the list will be in alphabetical order (alpabetic mode).
			@~english	@exception	None.
			@~japanese	@brief	アルファベットモードを設定します。
			@~japanese	@details	アルファベットモードを設定します。
			@~japanese	@param[in]	value	アルファベットモードにする場合は、 true を指定します。
			@~japanese	@exception	なし
		*/
		virtual void SetAlphabeticMode(bool value) = 0;

		/*!
			@~english	@brief	Get visibility.
			@~english	@details	Get visibility.
			@~english	@return	Visibility.
			@~english	@exception	None.
			@~japanese	@brief	表示対象項目の Visibility を取得します。
			@~japanese	@details	表示対象項目の Visibility を取得します。
			@~japanese	@return	Visibility
			@~japanese	@exception	なし
		*/
		virtual GenApi::EVisibility GetVisibility() const = 0;

		/*!
			@~english	@brief	Set visibility.
			@~english	@details	Set visibility.
			@~english	@param[in]	eVisibility	Visibility.
			@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument. 
			@~japanese	@brief	表示対象項目の Visibility を設定します。
			@~japanese	@details	表示対象項目の Visibility を設定します。 Beginner へ設定すると Beginner 項目のみが表示されます。 Expert へ設定すると Beginner および Expert 項目が表示されます。 Guru へ設定すると Guru, Expert および Beginner 項目が表示されます。
			@~japanese	@param[in]	eVisibility	Visibility
			@~japanese	@exception	不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void SetVisibility(GenApi::EVisibility eVisibility) = 0;

		/*!
			@~english	@brief	Expand the list.
			@~english	@details	Expand the list.
			@~english	@exception	None.
			@~japanese	@brief	リストを展開します。
			@~japanese	@details	リストを展開します。
			@~japanese	@exception	なし
		*/
		virtual void Expand() = 0;
		
		/*!
			@~english	@brief	Collapse the list.
			@~english	@details	Collapse the list.
			@~english	@exception	None.
			@~japanese	@brief	リストを折りたたみます。
			@~japanese	@details	リストを折りたたみます。
			@~japanese	@exception	なし
		*/
		virtual void Collapse() = 0;

		/*!
			@~english	@brief	Refresh the list.
			@~english	@details	Refresh the list.
			@~english	@exception	None.
			@~japanese	@brief	リストを再描画します。
			@~japanese	@details	リストを再描画します。
			@~japanese	@exception	なし
		*/
		virtual void Refresh() = 0;

		/*!
			@~english	@brief	Check if polling is enabled.
			@~english	@details	Check if polling is enabled.
			@~english	@return	True if polling is enabled; false otherwise.
			@~english	@exception	None.
			@~japanese	@brief	ポーリングの有効/無効を確認します。
			@~japanese	@details	ポーリングの有効/無効を確認します。
			@~japanese	@return	ポーリングが有効な場合、 true が返されます。
			@~japanese	@exception	なし
		*/
		virtual bool GetEnablePolling() const = 0;
		
		/*!
			@~english	@brief	Enable or disable polling.
			@~english	@details	Enable or disable polling.
			@~english	@param[in]	value	True to enable polling; false to disable polling.
			@~english	@exception	None.
			@~japanese	@brief	ポーリングの有効/無効を設定します。
			@~japanese	@details	ポーリングの有効/無効を設定します。ポーリングを有効にすると定期的にポーリング対象の値が確認されるようになります。
			@~japanese	@param[in]	value	ポーリングを有効にする場合、 true を指定します。
			@~japanese	@exception	なし
		*/
		virtual void SetEnablePolling(bool value) = 0;

		/*!
			@~english	@brief	Check the visibility of the alphabetic mode button.
			@~english	@details	Check the visibility of the alphabetic mode button.
			@~english	@return	True if the button is visible; false otherwise.
			@~english	@exception	None.
			@~japanese	@brief	アルファベットモード設定ボタンの表示/非表示を確認します。
			@~japanese	@details	アルファベットモード設定ボタンの表示/非表示を確認します。
			@~japanese	@return	アルファベットモード設定ボタンが表示されている場合、 true が返されます。
			@~japanese	@exception	なし
		*/
		virtual bool GetVisibleAlphabeticMode() const = 0;
		
		/*!
			@~english	@brief	Set the visibility of the alphabetic mode button.
			@~english	@details	Set the visibility of the alphabetic mode button.
			@~english	@param[in]	value	True to display the alphabetic mode button; false to hide the alphabetic mode button.
			@~english	@exception	None.
			@~japanese	@brief	アルファベットモード設定ボタンの表示/非表示を設定します。
			@~japanese	@details	アルファベットモード設定ボタンの表示/非表示を設定します。
			@~japanese	@param[in]	value	アルファベットモード設定ボタンを表示する場合、 true を指定します。
			@~japanese	@exception	なし
		*/
		virtual void SetVisibleAlphabeticMode(bool value) = 0;

		/*!
			@~english	@brief	Check the visibility of the expand button.
			@~english	@details	Check the visibility of the expand button.
			@~english	@return	True if the button is visible; false otherwise.
			@~english	@exception	None.
			@~japanese	@brief	展開ボタンの表示/非表示を確認します。
			@~japanese	@details	展開ボタンの表示/非表示を確認します。
			@~japanese	@return	展開ボタンが表示されている場合、 true が返されます。
			@~japanese	@exception	なし
		*/
		virtual bool GetVisibleExpand() const = 0;
		
		/*!
			@~english	@brief	Set the visibility of the expand button.
			@~english	@details	Set the visibility of the expand button.
			@~english	@param[in]	value	True to display the expand button; false to hide the expand button.
			@~english	@exception	None.
			@~japanese	@brief	展開ボタンの表示/非表示を設定します。
			@~japanese	@details	展開ボタンの表示/非表示を設定します。
			@~japanese	@param[in]	value	展開ボタンを表示する場合、 true を指定します。
			@~japanese	@exception	なし
		*/
		virtual void SetVisibleExpand(bool value) = 0;

		/*!
			@~english	@brief	Check the visibility of the collapse button.
			@~english	@details	Check the visibility of the collapse button.
			@~english	@return	True if the button is visible; false otherwise.
			@~english	@exception	None.
			@~japanese	@brief	折りたたみボタンの表示/非表示を確認します。
			@~japanese	@details	折りたたみボタンの表示/非表示を確認します。
			@~japanese	@return	折りたたみボタンが表示されている場合、 true が返されます。
			@~japanese	@exception	なし
		*/
		virtual bool GetVisibleCollapse() const = 0;

		/*!
			@~english	@brief	Set the visibility of the collapse button.
			@~english	@details	Set the visibility of the collapse button.
			@~english	@param[in]	value	True to display the collapse button; false to hide the collapse button.
			@~english	@exception	None.
			@~japanese	@brief	折りたたみボタンの表示/非表示を設定します。
			@~japanese	@details	折りたたみボタンの表示/非表示を設定します。
			@~japanese	@param[in]	value	折りたたみボタンを表示する場合、 true を指定します。
			@~japanese	@exception	なし
		*/
		virtual void SetVisibleCollapse(bool value) = 0;

		/*!
			@~english	@brief	Check the visibility of the refresh button.
			@~english	@details	Check the visibility of the refresh button.
			@~english	@return	True if the button is visible; false otherwise.
			@~english	@exception	None.
			@~japanese	@brief	リフレッシュボタンの表示/非表示を確認します。
			@~japanese	@details	リフレッシュボタンの表示/非表示を確認します。
			@~japanese	@return	リフレッシュボタンが表示されている場合、 true が返されます。
			@~japanese	@exception	なし
		*/
		virtual bool GetVisibleRefresh() const = 0;

		/*!
			@~english	@brief	Set the visibility of the refresh button.
			@~english	@details	Set the visibility of the refresh button.
			@~english	@param[in]	value	True to display the refresh button; false to hide the refresh button.
			@~english	@exception	None.
			@~japanese	@brief	リフレッシュボタンの表示/非表示を設定します。
			@~japanese	@details	リフレッシュボタンの表示/非表示を設定します。
			@~japanese	@param[in]	value	リフレッシュボタンを表示する場合、 true を指定します。
			@~japanese	@exception	なし
		*/
		virtual void SetVisibleRefresh(bool value) = 0;

		/*!
			@~english	@brief	Check the visibility of the polling check box.
			@~english	@details	Check the visibility of the polling check box.
			@~english	@return	True if the check box is visible; false otherwise.
			@~english	@exception	None.
			@~japanese	@brief	ポーリングチェックボックスの表示/非表示を確認します。
			@~japanese	@details	ポーリングチェックボックスの表示/非表示を確認します。
			@~japanese	@return	ポーリングチェックボックスが表示されている場合、 true が返されます。
			@~japanese	@exception	なし
		*/
		virtual bool GetVisiblePolling() const = 0;

		/*!
			@~english	@brief	Set the visibility of the polling check box.
			@~english	@details	Set the visibility of the polling check box.
			@~english	@param[in]	value	True to display the polling check box; false to hide the polling check box.
			@~english	@exception	None.
			@~japanese	@brief	ポーリングチェックボックスの表示/非表示を設定します。
			@~japanese	@details	ポーリングチェックボックスの表示/非表示を設定します。
			@~japanese	@param[in]	value	ポーリングチェックボックスを表示する場合、 true を指定します。
			@~japanese	@exception	なし
		*/
		virtual void SetVisiblePolling(bool value) = 0;

		/*!
			@~english	@brief	Check the visibility of the node visibility combo box.
			@~english	@details	Check the visibility of the node visibility combo box.
			@~english	@return	True if the combo box is visible; false otherwise.
			@~english	@exception	None.
			@~japanese	@brief	Visibilityコンボボックスの表示/非表示を確認します。
			@~japanese	@details	Visibilityコンボボックスの表示/非表示を確認します。
			@~japanese	@return	Visibilityコンボボックスが表示されている場合、 true が返されます。
			@~japanese	@exception	なし
		*/
		virtual bool GetVisibleVisibility() const = 0;

		/*!
			@~english	@brief	Set the visibility of the node visibility combo box.
			@~english	@details	Set the visibility of the node visibility combo box.
			@~english	@param[in]	value	True to display the node visibility combo box; false to hide the node visibility combo box.
			@~english	@exception	None.
			@~japanese	@brief	Visibilityコンボボックスの表示/非表示を設定します。
			@~japanese	@details	Visibilityコンボボックスの表示/非表示を設定します。
			@~japanese	@param[in]	value	Visibilityコンボボックスを表示する場合、 true を指定します。
			@~japanese	@exception	なし
		*/
		virtual void SetVisibleVisibility(bool value) = 0;

		/*!
			@~english	@brief	Check the visibility of the node description.
			@~english	@details	Check the visibility of the node description.
			@~english	@return	True if the description is visible; false otherwise.
			@~english	@exception	None.
			@~japanese	@brief	説明文の表示/非表示を確認します。
			@~japanese	@details	説明文の表示/非表示を確認します。
			@~japanese	@return	説明文が表示されている場合、 true が返されます。
			@~japanese	@exception	なし
		*/
		virtual bool GetVisibleDescription() const = 0;

		/*!
			@~english	@brief	Set the visibility of the node description.
			@~english	@details	Set the visibility of the node description.
			@~english	@param[in]	value	True to display the node description; false to hide the node description.
			@~english	@exception	None.
			@~japanese	@brief	説明文の表示/非表示を設定します。
			@~japanese	@details	説明文の表示/非表示を設定します。
			@~japanese	@param[in]	value	説明文を表示する場合、 true を指定します。
			@~japanese	@exception	なし
		*/
		virtual void SetVisibleDescription(bool value) = 0;
		
		/*!
			@~english	@brief	Check the visibility of the sample code in the node description.
			@~english	@details	Check the visibility of the sample code in the node description.
			@~english	@return	True if a sample code is visible; false otherwise.
			@~english	@exception	None.
			@~japanese	@brief	説明文内のサンプルプログラムの表示/非表示を確認します。
			@~japanese	@details	説明文内のサンプルプログラムの表示/非表示を確認します。
			@~japanese	@return	説明文内のサンプルプログラムが表示されている場合、 true が返されます。
			@~japanese	@exception	なし
		*/
		virtual bool GetVisibleDescriptionSampleCode() const = 0;

		/*!
			@~english	@brief	Set the visibility of the sample code in the node description.
			@~english	@details	Set the visibility of the sample code in the node description.
			@~english	@param[in]	value	True to display the sample code in the node description; false to hide the sample code in the node description.
			@~english	@exception	None.
			@~japanese	@brief	説明文内のサンプルプログラムの表示/非表示を設定します。
			@~japanese	@details	説明文内のサンプルプログラムの表示/非表示を設定します。
			@~japanese	@param[in]	value	説明文内のサンプルプログラムを表示する場合、 true を指定します。
			@~japanese	@exception	なし
		*/
		virtual void SetVisibleDescriptionSampleCode(bool value) = 0;

		/*!
			@~english	@brief	Check the visibility of the node filter check box and text box.
			@~english	@details	Check the visibility of the node filter check box and text box.
			@~english	@return	True if the combo box is visible; false otherwise.
			@~english	@exception	None.
			@~japanese	@brief	Filterチェックボックスおよびテキストボックスの表示/非表示を確認します。
			@~japanese	@details	Filterチェックボックスおよびテキストボックスの表示/非表示を確認します。
			@~japanese	@return	Filterチェックボックスおよびテキストボックスが表示されている場合、 true が返されます。
			@~japanese	@exception	なし
			@since	StApi v1.1.1
		*/
		virtual bool GetVisibleFilter() const = 0;

		/*!
			@~english	@brief	Set the visibility of the node filter check box and text box.
			@~english	@details	Set the visibility of the node filter check box and text box.
			@~english	@param[in]	value	True to display the node filter check box and text box; false to hide the node filter check box and text box.
			@~english	@exception	None.
			@~japanese	@brief	Filterチェックボックスおよびテキストボックスの表示/非表示を設定します。
			@~japanese	@details	Filterチェックボックスおよびテキストボックスの表示/非表示を設定します。
			@~japanese	@param[in]	value	Filterチェックボックスおよびテキストボックスを表示する場合、 true を指定します。
			@~japanese	@exception	なし
			@since	StApi v1.1.1
		*/
		virtual void SetVisibleFilter(bool value) = 0;
		
		/*!
			@~english	@brief	Get filter string.
			@~english	@details	Get filter string.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed.
			@~japanese	@brief	フィルター文字列を取得します。
			@~japanese	@details	フィルター文字列を取得します。
			@~japanese	@exception	メモリー確保に失敗した場合は、例外 GenICam::GenericException が発生します。
			@since	StApi v1.1.1
		*/
		virtual GenICam::gcstring GetFilterText() const = 0;
		
		/*!
			@~english	@brief	Set filter string.
			@~english	@details	Set filter string.
			@~english	@param[in]	strFilter	Filter string.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed.
			@~japanese	@brief	フィルター文字列を設定します。
			@~japanese	@details	フィルター文字列を設定します。
			@~japanese	@param[in]	strFilter	フィルター文字列
			@~japanese	@exception	メモリー確保に失敗した場合は、例外 GenICam::GenericException が発生します。
			@since	StApi v1.1.1
		*/
		virtual void SetFilterText(const GenICam::gcstring &strFilter) = 0;

		/*!
			@~english	@brief	Check the filter is enabled or not.
			@~english	@details	Check the filter is enabled or not.
			@~english	@return	True if the filter is enabled; false otherwise.
			@~english	@exception	None.
			@~japanese	@brief	Filterが有効化否かを確認します。
			@~japanese	@details	Filterが有効化否かを確認します。
			@~japanese	@return	Filterが有効な場合、 true が返されます。
			@~japanese	@exception	なし
			@since	StApi v1.1.1
		*/
		virtual bool GetEnableFilter() const = 0;

		/*!
			@~english	@brief	Activate or deactivate the filter.
			@~english	@details	Activate or deactivate the filter.
			@~english	@param[in]	value	True to activate the filter check; false to deactivate the filter.
			@~english	@exception	None.
			@~japanese	@brief	Filterを有効化または無効化します。
			@~japanese	@details	Filterを有効化または無効化します。
			@~japanese	@param[in]	value	Filterを有効化する場合、 true を指定します。
			@~japanese	@exception	なし
			@since	StApi v1.1.1
		*/
		virtual void SetEnableFilter(bool value) = 0;

		/*!
			@~english	@brief	Check the regular expression filter is enabled or not.
			@~english	@details	Check the regular expression filter is enabled or not.
			@~english	@return	True if the regular expression filter is enabled; false otherwise.
			@~english	@exception	None.
			@~japanese	@brief	正規表現フィルターが有効化否かを確認します。
			@~japanese	@details	正規表現フィルターが有効化否かを確認します。
			@~japanese	@return	正規表現フィルターが有効な場合、 true が返されます。
			@~japanese	@exception	なし
			@since	StApi v1.1.1
		*/
		virtual bool GetEnableRegularExpression() const = 0;

		/*!
			@~english	@brief	Activate or deactivate the regular expression filter.
			@~english	@details	Activate or deactivate the regular expression filter.
			@~english	@param[in]	value	True to activate the regular expression filter check; false to deactivate the regular expression filter.
			@~english	@exception	None.
			@~japanese	@brief	正規表現フィルターを有効化または無効化します。
			@~japanese	@details	正規表現フィルターを有効化または無効化します。
			@~japanese	@param[in]	value	正規表現フィルターを有効化する場合、 true を指定します。
			@~japanese	@exception	なし
			@since	StApi v1.1.1
		*/
		virtual void SetEnableRegularExpression(bool value) = 0;


	};
	
	//---------------------------------------------------------------------
	// typedef CIStNodeMapDisplayWndPtr
	//---------------------------------------------------------------------
	/*!
		@ingroup StApiGUI_PublicImpl
		@typedef CIStNodeMapDisplayWndPtr
		@~english	@brief	The auto management class of IStNodeMapDisplayWnd class for displaying node map.
		@~english	@details	The auto management class of IStNodeMapDisplayWnd class for displaying node map.Use this class instead of managing the initial/release of IStNodeMapDisplayWnd class yourself. The destructor of this class will automatically call IStWndReleasable::Release().
		@~japanese	@brief	IStNodeMapDisplayWnd インターフェースポインターの自動管理用クラスです。
		@~japanese	@details	IStNodeMapDisplayWnd インターフェースポインターの自動管理用クラスです。このクラスのデストラクタから IStWndReleasable::Release() が自動的に呼び出されます。
	*/
	typedef CStAutoPtr<IStWndReleasable, IStNodeMapDisplayWnd> CIStNodeMapDisplayWndPtr;

	//---------------------------------------------------------------------
	// typedef CIStNodeMapDisplayWndPtrArray
	//---------------------------------------------------------------------
	/*!
		@ingroup StApiGUI_PublicImpl
		@typedef CIStNodeMapDisplayWndPtrArray
		@~english	@brief	This class is for lifetime management of multiple object of IStNodeMapDisplayWnd.
		@~english	@details	This class is for lifetime management of multiple object of IStNodeMapDisplayWnd. The destructor of this class will automatically call IStWndReleasable::Release().
		@~japanese	@brief	IStNodeMapDisplayWnd インターフェースポインターの自動管理用クラスです。
		@~japanese	@details	IStNodeMapDisplayWnd インターフェースポインターの自動管理用クラスです。このクラスのデストラクタから IStWndReleasable::Release() が自動的に呼び出されます。
	*/
	typedef CIStWndPtrArrayT<IStNodeMapDisplayWnd> CIStNodeMapDisplayWndPtrArray;
}
#endif //STDISPLAYNODEMAPWND_H
