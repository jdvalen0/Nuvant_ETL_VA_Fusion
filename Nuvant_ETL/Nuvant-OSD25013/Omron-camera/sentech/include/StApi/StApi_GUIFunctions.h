//------------------------------------------------------------------------------
// StApi
//------------------------------------------------------------------------------
/*!
	@ingroup	StApiGUI_PublicImpl
	@file	StApi_GUIFunctions.h
	@~english	@details	
	@~japanese	@details	
*/
#ifndef ISTAPI_GUIFUNCTIONS_H__
#define ISTAPI_GUIFUNCTIONS_H__

namespace StApi
{
	//-------------------------------------------------------------------------
	// C Functions
	//-------------------------------------------------------------------------	
	/*!
		@ingroup	StApiGUI_PublicImpl
		@~english	@brief	Acquire IStWndReleasable pointer.
		@~english	@details	Acquire IStWndReleasable pointer. This pointer can be used for either displaying image, nodemap, or device selection.
		@~english	@param[in] eWnd	Type of Window.
		@~english	@return	IStWndReleasable pointer.
		@~english	@attention	If the acquired IStWndReleasable pointer is no longer needed, call IStWndReleasable::Release() to release it. 
		@~english	@exception	Throw out a GenICam::GenericException if StApi is not initialized or memory allocation is failed.
		@~japanese	@brief	IStWndReleasable インターフェースポインターを取得します。
		@~japanese	@details	IStWndReleasable インターフェースポインターを取得します。
		@~japanese	@param[in] eWnd	使用するウィンドウのタイプ
		@~japanese	@return	IStWndReleasable インターフェースポインター
		@~japanese	@attention	取得された IStWndReleasable インターフェースが不要になったら、 IStWndReleasable::Release() を呼び出して解放してください。
		@~japanese	@exception	初期化されていない場合、メモリーの割り当てに失敗した場合や引数が不正な場合は、例外 GenICam::GenericException が発生します。
	*/
	ST_API_GUI StApi::IStWndReleasable* ST_API_CALL_TYPE CreateIStWnd(StApi::EStWindowType_t eWnd);


	/*!
		@ingroup	StApiGUI_PublicImpl
		@~english	@brief	Acquire IStWndReleasable pointer.
		@~english	@details	Acquire IStWndReleasable pointer. This pointer can be used for displaying image.
		@~english	@param[in]	pIStAllocator	IStAllocator pointer.
		@~english	@return	IStWndReleasable pointer.
		@~english	@attention	If the acquired IStWndReleasable pointer is no longer needed, call IStWndReleasable::Release() to release it. 
		@~english	@exception	Throw out a GenICam::GenericException if StApi is not initialized or memory allocation is failed.
		@~japanese	@brief	IStWndReleasable インターフェースポインターを取得します。
		@~japanese	@details	IStWndReleasable インターフェースポインターを取得します。
		@~japanese	@param[in]	pIStAllocator	IStAllocator インターフェースポインター
		@~japanese	@return	IStWndReleasable インターフェースポインター
		@~japanese	@attention	取得された IStWndReleasable インターフェースが不要になったら、 IStWndReleasable::Release() を呼び出して解放してください。
		@~japanese	@exception	初期化されていない場合、メモリーの割り当てに失敗した場合や引数が不正な場合は、例外 GenICam::GenericException が発生します。
	*/
	ST_API_GUI StApi::IStWndReleasable* ST_API_CALL_TYPE CreateIStImageDisplayWnd(StApi::IStAllocator *pIStAllocator);

	/*!
		@ingroup	StApiGUI_PublicImpl
		@~english	@brief	Acquire IStWndReleasable pointer.
		@~english	@details	Acquire IStWndReleasable pointer. This pointer can be used for displaying graph.
		@~english	@param[in]	pIStSpecificTypeAllocator	IStSpecificTypeAllocator pointer.
		@~english	@return	IStWndReleasable pointer.
		@~english	@attention	If the acquired IStWndReleasable pointer is no longer needed, call IStWndReleasable::Release() to release it. 
		@~english	@exception	Throw out a GenICam::GenericException if StApi is not initialized or memory allocation is failed.
		@~japanese	@brief	IStWndReleasable インターフェースポインターを取得します。
		@~japanese	@details	IStWndReleasable インターフェースポインターを取得します。
		@~japanese	@param[in]	pIStSpecificTypeAllocator	IStSpecificTypeAllocator インターフェースポインター
		@~japanese	@return	IStWndReleasable インターフェースポインター
		@~japanese	@attention	取得された IStWndReleasable インターフェースが不要になったら、 IStWndReleasable::Release() を呼び出して解放してください。
		@~japanese	@exception	初期化されていない場合、メモリーの割り当てに失敗した場合や引数が不正な場合は、例外 GenICam::GenericException が発生します。
	*/
	ST_API_GUI StApi::IStWndReleasable* ST_API_CALL_TYPE CreateIStGraphDisplayWnd(StApi::IStSpecificTypeAllocator *pIStSpecificTypeAllocator = NULL);

	/*!
		@ingroup	StApiGUI_PublicImpl
		@~english	@brief	Copy a image to clipboard.
		@~english	@details	Copy a image to clipboard.
		@~english	@param[in]	pIStImage	IStImage interface pointer.
		@~english	@attention	Image data in formats other than StPFNC_Mono8, StPFNC_BGR8, and StPFNC_BGRa8 will be copied to the clipboard after conversion. If you want to specify the conversion method, please convert to StPFNC_Mono8, StPFNC_BGR8, StPFNC_BGRa8 using IStPixelFormatConverter beforehand.
		@~english	@exception	Throw out a GenICam::GenericException if StApi is not initialized or memory allocation is failed.
		@~japanese	@brief	画像データをクリップボードへコピーします。
		@~japanese	@details	画像データをクリップボードへコピーします。
		@~japanese	@param[in]	pIStImage	IStImage interface pointer.
		@~japanese	@attention	StPFNC_Mono8, StPFNC_BGR8, StPFNC_BGRa8 以外のフォーマットの画像データは、変換後にクリップボードへコピーされます。変換方法を指定したい場合は、あらかじめ IStPixelFormatConverter を使用して、 StPFNC_Mono8, StPFNC_BGR8, StPFNC_BGRa8 へ変換された画像データを引数に指定してください。
		@~japanese	@exception	初期化されていない場合、メモリーの割り当てに失敗した場合や引数が不正な場合は、例外 GenICam::GenericException が発生します。
	*/
	ST_API_GUI void ST_API_CALL_TYPE SetIStImageToClipboard(StApi::IStImage *pIStImage);

#ifndef _WIN32
    /*!
        @ingroup	StApiGUI_PublicImpl
        @~english	@brief	Process GUI event (Only for Mac/Linux).
        @~english	@details	Process GUI event (Only for Mac/Linux).
        @~english	@return	return value of QApplication::exec() or zero if processEvents() is executed.
        @~english	@param[in]	runExec True to execute Qt's QApplication::exec(); false to execute Qt's QApplication::instance()->processEvents()
        @~english	@param[in]	maxtime Applicable only if runExec is false. Max time for processEvents() in ms (set to zero to process all events without time limit). 
        @~japanese	@brief	GUIイベントを処理するための関数 （Mac/Linuxのみ）。
        @~japanese	@details	GUIイベントを処理するための関数 （Mac/Linuxのみ）。
        @~japanese	@return QApplication::exec()からのリターン。processEvents()を実行すれば、ゼロです。
        @~japanese  @param[in]	runExec True場合はQtのQApplication::exec()を実行します。False場合はQtのQApplication::instance()->processEvents()を実行します。
        @~japanese  @param[in]	maxtime runExecがFalseのときに適用されます. processEvents()の最大の処理時間 [ms]。ゼロを設定する場合は処理時間制限が解放します。
    */
    ST_API_GUI int ST_API_CALL_TYPE processEventGUI(bool runExec=false, unsigned int maxtime=0);
#endif
}
#endif //ISTAPI_GUIFUNCTIONS_H__
