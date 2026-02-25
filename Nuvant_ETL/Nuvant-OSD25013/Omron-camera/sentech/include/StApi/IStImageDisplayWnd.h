//------------------------------------------------------------------------------
//  StApi
//------------------------------------------------------------------------------
/*!
	@ingroup	StApiGUI_PublicInterface
	@file
	@~english	@details	Definition of interface IStImageDisplayWnd
	@~japanese	@details	IStImageDisplayWnd インターフェースの定義
*/
#ifndef STDISPLAYIMAGEWND_H
#define STDISPLAYIMAGEWND_H

#include "IStWnd.h"

#ifdef ENABLE_DRAWING_TOOLS
#include "IStDrawingTool.h"
#endif //ENABLE_DRAWING_TOOLS

namespace StApi
{
	// ---------------------------------------------------------------------
	// interface IStImageDisplayWnd
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiGUI_PublicInterface
		@interface IStImageDisplayWnd
		@~english	@brief	Interface for Display Image Window.
		@~english	@details	Interface for Display Image Window.
		@~japanese	@brief	画像表示ウィンドウ用インターフェース
		@~japanese	@details	画像表示ウィンドウ用インターフェース
	*/
	interface PUBLIC_INTERFACE IStImageDisplayWnd :public IStWnd
	{
		/*!
			@~english	@brief	Register an image for preview.
			@~english	@details	Register an image for preview. The image data will be copied.
			@~english	@param[in]	pIStImage	The image data for preview.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed.
			@~japanese	@brief	表示する画像データを登録します。
			@~japanese	@details	表示する画像データを登録します。画像データはSDK内部のバッファへコピーされます。
			@~japanese	@param[in]	pIStImage	表示する画像の IStImage インターフェースポインター
			@~japanese	@exception	メモリー確保に失敗した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void RegisterIStImage(IStImage *pIStImage) = 0;

		/*!
			@~english	@brief	Check if any image for preview has been registered.
			@~english	@details	Check if any image for preview has been registered.
			@~english	@return	Return true if an image has already registered; otherwise false.
			@~english	@exception	None.
			@~japanese	@brief	登録された画像があるかどうか確認します。
			@~japanese	@details	登録された画像があるかどうか確認します。
			@~japanese	@return	登録された画像がある場合、 true が返されます。
			@~japanese	@exception	なし
		*/
		virtual bool HasImage() const = 0;

		/*!
			@~english	@brief	Get registered image for preview.
			@~english	@details	Get registered image for preview.
			@~english	@return	IStImage pointer to the image.
			@~english	@exception	Throw out a GenICam::GenericException if there is no image registered.
			@~japanese	@brief	最後に登録された画像用の IStImage インターフェースポインターを取得します。
			@~japanese	@details	最後に登録された画像用の IStImage インターフェースポインターを取得します。
			@~japanese	@return	IStImage インターフェースポインター
			@~japanese	@exception	画像が登録されていない場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual IStImage * GetRegisteredIStImage() = 0;

		/*!
			@~english	@brief	Get a converted image for preview.
			@~english	@details	Get a converted image for preview. If conversion is not needed for preview, a registered image is returned.
			@~english	@return	IStImage pointer to the image.
			@~english	@exception	Throw out a GenICam::GenericException if there is no image registered.
			@~japanese	@brief	最後に登録された画像を表示用のピクセルフォーマットへ変換した画像の IStImage インターフェースポインターを取得します。
			@~japanese	@details	最後に登録された画像を表示用のピクセルフォーマットへ変換した画像の IStImage インターフェースポインターを取得します。変換が不要な画像が登録された場合は、登録された画像が返されます。
			@~japanese	@return	IStImage インターフェースポインター
			@~japanese	@exception	画像が登録されていない場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual IStImage * GetConvertedIStImage() = 0;
		
		/*!
			@~english	@brief	Convert screen coordinate to image coordinate.
			@~english	@details      Convert screen coordinate to image coordinate.
			@~english	@param[in,out]	pX	X coordinate.
			@~english	@param[in,out]	pY	Y coordinate.
			@~english	@exception	None.
			@~japanese	@brief	スクリーン上の座標を画像上の座標へ変換します。
			@~japanese	@details	スクリーン上の座標を画像上の座標へ変換します。
			@~japanese	@param[in,out]	pX	スクリーン上のX座標を入力すると、画像上のX座標が返されます。
			@~japanese	@param[in,out]	pY	スクリーン上のY座標を入力すると、画像上のY座標が返されます。
			@~japanese	@exception	なし
		*/
		virtual void ScreenToImage(int32_t *pX, int32_t *pY) = 0;

		/*!
			@~english	@brief	Get IStPixelFormatConverter pointer for converting a registered image to a preview image.
			@~english	@details	Get IStPixelFormatConverter pointer for converting a registered image to a preview image.
			@~english	@return	IStPixelFormatConverter pointer.
			@~english	@exception	None.
			@~japanese	@brief	登録された画像の変換に使用される IStPixelFormatConverter インターフェースポインターを取得します。
			@~japanese	@details	登録された画像の変換に使用される IStPixelFormatConverter インターフェースポインターを取得します。
			@~japanese	@return	IStPixelFormatConverter インターフェースポインター
			@~japanese	@exception	なし
		*/
		virtual IStPixelFormatConverter * GetIStPixelFormatConverter() const = 0;

		/*!
			@~english	@brief	Get current mode of preview pixel format.
			@~english	@details	Get current mode of preview pixel format.
			@~english	@return	Preview pixel format mode.
			@~english	@exception	None.
			@~japanese	@brief	プレビューピクセルフォーマットモードを取得します。
			@~japanese	@details	プレビューピクセルフォーマットモードを取得します。
			@~japanese	@return	プレビューピクセルフォーマットモード
			@~japanese	@exception	なし
		*/
		virtual EStPreviewPixelFormatMode_t GetPreviewPixelFormatMode() const = 0;

		/*!
			@~english	@brief	Set preview pixel format mode.
			@~english	@details	Set preview pixel format mode.
			@~english	@param[in]	ePPFM	Preview pixel format mode.
			@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument. 
			@~japanese	@brief	プレビューピクセルフォーマットモードを設定します。
			@~japanese	@details	プレビューピクセルフォーマットモードを設定します。
			@~japanese	@param[in]	ePPFM	プレビューピクセルフォーマットモード
			@~japanese	@exception	不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void SetPreviewPixelFormatMode(EStPreviewPixelFormatMode_t ePPFM) = 0;

		/*!
			@~english	@brief	Get maximum position of horizontal scroll bar.
			@~english	@details	Get maximum position of horizontal scroll bar.
			@~english	@return	Horizontal scroll position value.
			@~english	@exception	None.
			@~japanese	@brief	水平スクロールバー位置の最大値を取得します。
			@~japanese	@details	水平スクロールバー位置の最大値を取得します。
			@~japanese	@return	水平スクロールバー位置の最大値
			@~japanese	@exception	なし
		*/
		virtual int32_t GetScrollHMax() const = 0;

		/*!
			@~english	@brief	Get current position of horizontal scroll bar.
			@~english	@details	Get current position of horizontal scroll bar.
			@~english	@return	Horizontal scroll position value.
			@~english	@exception	None.
			@~japanese	@brief	水平スクロールバー位置を取得します。
			@~japanese	@details	水平スクロールバー位置を取得します。
			@~japanese	@return	水平スクロールバー位置
			@~japanese	@exception	なし
		*/
		virtual int32_t GetScrollHPosition() const = 0;

		/*!
			@~english	@brief	Set the position of horizontal scroll bar. The value will set as maximum if it exceeds the maximum value.
			@~english	@details	Set the position of horizontal scroll bar. The value will set as maximum if it exceeds the maximum value.
			@~english	@param[in]	value	Horizontal scroll position value.
			@~english	@exception	None.
			@~japanese	@brief	水平スクロールバー位置を設定します。
			@~japanese	@details	水平スクロールバー位置を設定します。
			@~japanese	@param[in]	value	水平スクロールバー位置
			@~japanese	@exception	なし
		*/
		virtual void SetScrollHPosition(int32_t value) = 0;

		/*!
			@~english	@brief	Get the maximum position of vertical scroll bar.
			@~english	@details	Get the maximum position of vertical scroll bar.
			@~english	@return	Vertical scroll position value.
			@~english	@exception	None.
			@~japanese	@brief	垂直スクロールバー位置の最大値を取得します。
			@~japanese	@details	垂直スクロールバー位置の最大値を取得します。
			@~japanese	@return	垂直スクロールバー位置の最大値
			@~japanese	@exception	なし
		*/
		virtual int32_t GetScrollVMax() const = 0;

		/*!
			@~english	@brief	Get current position of vertical scroll bar.
			@~english	@details	Get current position of vertical scroll bar.
			@~english	@return	Vertical scroll position value.
			@~english	@exception	None.
			@~japanese	@brief	垂直スクロールバー位置を取得します。
			@~japanese	@details	垂直スクロールバー位置を取得します。
			@~japanese	@return	垂直スクロールバー位置
			@~japanese	@exception	なし
		*/
		virtual int32_t GetScrollVPosition() const = 0;

		/*!
			@~english	@brief	Set the position of vertical scroll bar. The value will set as maximum if it exceeds the maximum value.
			@~english	@details	Set the position of vertical scroll bar. The value will set as maximum if it exceeds the maximum value.
			@~english	@param[in]	value	Vertical scroll position value.
			@~english	@exception	None.
			@~japanese	@brief	垂直スクロールバー位置を設定します。
			@~japanese	@details	垂直スクロールバー位置を設定します。
			@~japanese	@param[in]	value	垂直スクロールバー位置
			@~japanese	@exception	なし
		*/
		virtual void SetScrollVPosition(int32_t value) = 0;

		/*!
			@~english	@brief	Get image refreshing interval.
			@~english	@details	Get image refreshing interval.
			@~english	@attention With small refreshing interval value, the display latency time decreases while the CPU utilization increases. On the other hand, with large refreshing interval value, the display latency time increases while the CPU utilization decreases.
			@~english	@return	Refresh interval value [ms].
			@~english	@exception	None.
			@~japanese	@brief	表示画像のリフレッシュ間隔を取得します。
			@~japanese	@details	表示画像のリフレッシュ間隔を取得します。
			@~japanese	@attention	値を小さくすると遅延時間が短くなりますが、CPU負荷が増加します。逆に値を大きくすると遅延時間が長くなりますが、CPU負荷は軽減されます。
			@~japanese	@return	描画間隔[ms]。0を設定されていると画像データを登録したタイミングで、再描画がかかるようになります。
			@~japanese	@exception	なし
		*/
		virtual uint32_t GetRefreshInterval() const = 0;

		/*!
			@~english	@brief	Set image refreshing interval.
			@~english	@details	Set image refreshing interval.
			@~english	@attention With small refreshing interval value, the display latency time decreases while the CPU utilization increases. On the other hand, with large refreshing interval value, the display latency time increases while the CPU utilization decreases.
			@~english	@param[in]	value	Refresh interval value [ms].
			@~english	@exception	None.
			@~japanese	@brief	表示画像のリフレッシュ間隔を設定します。
			@~japanese	@details	表示画像のリフレッシュ間隔を設定します。
			@~japanese	@attention	値を小さくすると遅延時間が短くなりますが、CPU負荷が増加します。逆に値を大きくすると遅延時間が長くなりますが、CPU負荷は軽減されます。
			@~japanese	@param[in]	value	描画間隔[ms]。0を指定すると画像データを登録したタイミングで、再描画がかかるようになります。
			@~japanese	@exception	なし
		*/
		virtual void SetRefreshInterval(uint32_t value) = 0;

		/*!
			@~english	@brief	Get zoom mode value.
			@~english	@details	Get zoom mode value.
			@~english	@return	Zoom mode value.
			@~english	@exception	None.
			@~japanese	@brief	ズームモードを取得します。
			@~japanese	@details	ズームモードを取得します。
			@~japanese	@return	ズームモード
			@~japanese	@exception	なし
		*/
		virtual EStZoomMode_t GetZoomMode() const = 0;

		/*!
			@~english	@brief	Set zoom mode.
			@~english	@details	Set zoom mode.
			@~english	@param[in]	eZM	Zoom mode value.
			@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument. 
			@~japanese	@brief	ズームモードを設定します。
			@~japanese	@details	ズームモードを設定します。
			@~japanese	@param[in]	eZM	ズームモード
			@~japanese	@exception	不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void SetZoomMode(EStZoomMode_t eZM) = 0;

		/*!
			@~english	@brief	Get manual zoom maginification.
			@~english	@details	Get manual zoom maginification.
			@~english	@return	Manual zoom maginification.
			@~english	@exception	None.
			@~japanese	@brief	マニュアルズーム時の倍率を取得します。
			@~japanese	@details	マニュアルズーム時の倍率を取得します。
			@~japanese	@return	マニュアルズーム時の倍率
			@~japanese	@exception	なし
		*/
		virtual double GetManualZoomMagnification() const = 0;
		
		/*!
			@~english	@brief	Set manual zoom maginification.
			@~english	@details	Set manual zoom maginification.
			@~english	@param[in]	value	Manual zoom maginification.
			@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument. 
			@~japanese	@brief	マニュアルズーム時の倍率を設定します。
			@~japanese	@details	マニュアルズーム時の倍率を設定します。
			@~japanese	@param[in]	value	マニュアルズーム時の倍率
			@~japanese	@exception	不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void SetManualZoomMagnification(double value) = 0;

		/*!
			@~english	@brief	Get background style.
			@~english	@details	Get background style.
			@~english	@return	Background style value.
			@~english	@exception	None.
			@~japanese	@brief	背景スタイルを取得します。
			@~japanese	@details	背景スタイルを取得します。
			@~japanese	@return	背景スタイル
			@~japanese	@exception	なし
		*/
		virtual StApi::EStBackgroundStyle_t GetBackgroundStyle() const = 0;

		/*!
			@~english	@brief	Set background style.
			@~english	@details	Set background style.
			@~english	@param[in]	eBS	Background style value.
			@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument.
			@~japanese	@brief	背景スタイルを設定します。
			@~japanese	@details	背景スタイルを設定します。
			@~japanese	@param[in]	eBS	背景スタイル 
			@~japanese	@exception	不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void SetBackgroundStyle(StApi::EStBackgroundStyle_t eBS) = 0;

		/*!
			@~english	@brief	Get foreground color.
			@~english	@details	Get foreground color.
			@~english	@return	Foreground color value in 32bits. Blue(bit23-16), Green(bit15-bit8), Red(bit7-bit0).
			@~english	@exception	None.
			@~japanese	@brief	前景色を取得します。
			@~japanese	@details	前景色を取得します。
			@~japanese	@return	前景色 bit23-16:青, bit15-8:緑, bit7-0:赤
			@~japanese	@exception	なし
		*/
		virtual uint32_t GetForegroundColor() const = 0;

		/*!
			@~english	@brief	Set foreground color.
			@~english	@details	Set foreground color.
			@~english	@param[in]	value	Foreground color value in 32bits. Blue(bit23-16), Green(bit15-bit8), Red(bit7-bit0).
			@~english	@exception	None.
			@~japanese	@brief	前景色を設定します。
			@~japanese	@details	前景色を設定します。
			@~japanese	@param[in]	value	前景色 bit23-16:青, bit15-8:緑, bit7-0:赤
			@~japanese	@exception	なし
		*/
		virtual void SetForegroundColor(uint32_t value) = 0;

		/*!
			@~english	@brief	Get background color.
			@~english	@details	Get background color.
			@~english	@return	24bits color value as Blue(bit23-16), Green(bit15-bit8), Red(bit7-bit0).
			@~english	@exception	None.
			@~japanese	@brief	背景色を取得します。
			@~japanese	@details	背景色を取得します。
			@~japanese	@return	背景色 bit23-16:青, bit15-8:緑, bit7-0:赤
			@~japanese	@exception	なし
		*/
		virtual uint32_t GetBackgroundColor() const = 0;

		/*!
			@~english	@brief	Set background color.
			@~english	@details	Set background color.
			@~english	@param[in]	value	24bits color value as Blue(bit23-16), Green(bit15-bit8), Red(bit7-bit0).
			@~english	@exception	None.
			@~japanese	@brief	背景色を設定します。
			@~japanese	@details	背景色を設定します。
			@~japanese	@param[in]	value	背景色 bit23-16:青, bit15-8:緑, bit7-0:赤
			@~japanese	@exception	なし
		*/
		virtual void SetBackgroundColor(uint32_t value) = 0;

		//v1.1.1
		
		/*!
			@~english	@brief	Check if the built in drawing toolbar is enable or not.
			@~english	@details	Check if the built in drawing toolbar is enable or not.
			@~english	@return	true:Enable, false:Disable.
			@~english	@exception	None.
			@~japanese	@brief	内蔵の描画用ツールバーが有効になっているかどうかを確認します。
			@~japanese	@details	内蔵の描画用ツールバーが有効になっているかどうかを確認します。
			@~japanese	@return	true:有効, false:無効
			@~japanese	@exception	なし
		*/
		virtual bool GetBuiltInDrawingToolbar() const = 0;

		/*!
			@~english	@brief	Enable the built in drawing toolbar.
			@~english	@details	Enable the built in drawing toolbar.
			@~english	@param[in]	bValue	true:Enable, false:Disable.
			@~english	@exception	None.
			@~japanese	@brief	内蔵の描画用ツールバーを有効化(無効化)します。
			@~japanese	@details	内蔵の描画用ツールバーを有効化(無効化)します。
			@~japanese	@param[in]	bValue	true:有効, false:無効
			@~japanese	@exception	なし
		*/
		virtual void SetBuiltInDrawingToolbar(bool bValue) = 0;

		
		/*!
			@~english	@brief	Check if the drawing on the saving image is enable or not.
			@~english	@details	Check if the drawing on the saving image is enable or not.
			@~english	@return	true:Enable, false:Disable.
			@~english	@exception	None.
			@~japanese	@brief	保存画像への描画が有効になっているかどうかを確認します。
			@~japanese	@details	保存画像への描画が有効になっているかどうかを確認します。
			@~japanese	@return	true:有効, false:無効
			@~japanese	@exception	なし
		*/
		virtual bool GetEnableDrawingOnSavingImage() const = 0;

		/*!
			@~english	@brief	Enable the drawing on the saving image.
			@~english	@details	Enable the drawing on the saving image.
			@~english	@param[in]	bValue	true:Enable, false:Disable.
			@~english	@exception	None.
			@~japanese	@brief	保存画像への描画を有効化(無効化)します。
			@~japanese	@details	保存画像への描画を有効化(無効化)します。
			@~japanese	@param[in]	bValue	true:有効, false:無効
			@~japanese	@exception	なし
		*/
		virtual void SetEnableDrawingOnSavingImage(bool bValue) = 0;

		/*!
			@~english	@brief	Get IStDrawingTool interface pointer.
			@~english	@details	Get IStDrawingTool interface pointer.
			@~english	@return	IStDrawingTool interface pointer.
			@~english	@exception	None.
			@~japanese	@brief	IStDrawingTool インターフェースポインターを取得します。
			@~japanese	@details	IStDrawingTool インターフェースポインターを取得します。
			@~japanese	@return	IStDrawingTool インターフェースポインター
			@~japanese	@exception	なし
		*/
		virtual IStDrawingTool *GetIStDrawingTool() = 0;
	};

	//---------------------------------------------------------------------
	// typedef CIStImageDisplayWndPtr
	//---------------------------------------------------------------------
	/*!
		@ingroup StApiGUI_PublicImpl
		@typedef CIStImageDisplayWndPtr
		@~english	@brief	This class is for lifetime management of IStImageDisplayWnd.
		@~english	@details	This class is for lifetime management of IStImageDisplayWnd. The destructor of this class will automatically call IStWndReleasable::Release().
		@~japanese	@brief	IStImageDisplayWnd インターフェースポインターの自動管理用クラスです。
		@~japanese	@details	IStImageDisplayWnd インターフェースポインターの自動管理用クラスです。このクラスのデストラクタから IStWndReleasable::Release() が自動的に呼び出されます。
	*/
	typedef CStAutoPtr<IStWndReleasable, IStImageDisplayWnd> CIStImageDisplayWndPtr;

	//---------------------------------------------------------------------
	// typedef CIStImageDisplayWndPtrArray
	//---------------------------------------------------------------------
	/*!
		@ingroup StApiGUI_PublicImpl
		@typedef CIStImageDisplayWndPtrArray
		@~english	@brief	This class is for lifetime management of multiple objects of IStImageDisplayWnd.
		@~english	@details	This class is for lifetime management of multiple objects of IStImageDisplayWnd. The destructor of this class will automatically call IStWndReleasable::Release().
		@~japanese	@brief	IStImageDisplayWnd インターフェースポインターの自動管理用クラスです。
		@~japanese	@details	IStImageDisplayWnd インターフェースポインターの自動管理用クラスです。このクラスのデストラクタから IStWndReleasable::Release() が自動的に呼び出されます。
	*/
	typedef CIStWndPtrArrayT<IStImageDisplayWnd> CIStImageDisplayWndPtrArray;

	// ---------------------------------------------------------------------
	// interface IStCallbackParamStApiGUIEventDrawing
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiGUI_PublicInterface
		@interface IStCallbackParamStApiGUIEventDrawing
		@~english	@brief	Interface for GUI Event (Draw Image).
		@~english	@details	Interface for GUI Event (Draw Image).
		@~japanese	@brief	IStCallbackParamStApiGUIEventDrawing インターフェース
		@~japanese	@details	IStCallbackParamStApiGUIEventDrawing インターフェース
	*/
	interface PUBLIC_INTERFACE IStCallbackParamStApiGUIEventDrawing : public IStCallbackParamStApiGUIEventBaseWnd
	{
		/*!
			@~english	@brief	Get IStImage pointer for the preview image.
			@~english	@details	Get IStImage pointer for the preview image.
			@~english	@return	IStImage pointer to the image.
			@~english	@exception	None.
			@~japanese	@brief	描画される画像用の IStImage インターフェースポインターを取得します。
			@~japanese	@details	描画される画像用の IStImage インターフェースポインターを取得します。
			@~japanese	@return	IStImage インターフェースポインター
			@~japanese	@exception	なし
		*/
		virtual IStImage *GetIStImage() const = 0;

		/*!
			@~english	@brief	Get ROI horizontal offset on the preview image.
			@~english	@details	Get ROI horizontal offset on the preview image.
			@~english	@return	Offset value.
			@~english	@exception	None.
			@~japanese	@brief	描画の対象とする画像上のエリアの横方向のオフセット値を取得します。
			@~japanese	@details	描画の対象とする画像上のエリアの横方向のオフセット値を取得します。画像全体を描画の対象とする場合は、0が返されます。
			@~japanese	@return	横方向のオフセット値
			@~japanese	@exception	なし
		*/
		virtual size_t GetROIOffsetX() const = 0;

		/*!
			@~english	@brief	Get ROI vertical offset on the preview image.
			@~english	@details	Get ROI vertical offset on the preview image.
			@~english	@return	Offset value.
			@~english	@exception	None.
			@~japanese	@brief	描画の対象とする画像上のエリアの縦方向のオフセット値を取得します。
			@~japanese	@details	描画の対象とする画像上の位置の縦方向のオフセット値を取得します。画像全体を描画の対象とする場合は、0が返されます。
			@~japanese	@return	縦方向のオフセット値
			@~japanese	@exception	なし
		*/
		virtual size_t GetROIOffsetY() const = 0;

		/*!
			@~english	@brief	Get ROI horizontal size on the preview image.
			@~english	@details	Get ROI horizontal size on the preview image.
			@~english	@return	Width size value.
			@~english	@exception	None.
			@~japanese	@brief	描画の対象とする画像上のエリアの横サイズを取得します。
			@~japanese	@details	描画の対象とする画像上のエリアの横サイズを取得します。画像全体を描画の対象とする場合は、画像の横サイズが返されます。
			@~japanese	@return	横サイズ
			@~japanese	@exception	なし
		*/
		virtual size_t GetROIWidth() const = 0;

		/*!
			@~english	@brief	Get ROI vertical size on the preview image.
			@~english	@details	Get ROI vertical size on the preview image.
			@~english	@return	Height size value.
			@~english	@exception	None.
			@~japanese	@brief	描画の対象とする画像上のエリアの縦サイズを取得します。
			@~japanese	@details	描画の対象とする画像上のエリアの縦サイズを取得します。画像全体を描画の対象とする場合は、画像の縦サイズが返されます。
			@~japanese	@return	縦サイズ
			@~japanese	@exception	なし
		*/
		virtual size_t GetROIHeight() const = 0;
		
		/*!
			@~english	@brief	Get horizontal size of the image displaying area.
			@~english	@details	Get horizontal size of the image displaying area.
			@~english	@return	Width of displaying area.
			@~english	@exception	None.
			@~japanese	@brief	表示エリアの横方向のサイズを取得します。
			@~japanese	@details	表示エリアの横方向のサイズを取得します。
			@~japanese	@return	横サイズ
			@~japanese	@exception	なし
		*/
		virtual size_t GetDisplayWidth() const = 0;
		
		/*!
			@~english	@brief	Get vertical size of the image displaying area.
			@~english	@details	Get vertical size of the image displaying area.
			@~english	@return	Height of displaying area.
			@~english	@exception	None.
			@~japanese	@brief	表示エリアの縦方向のサイズを取得します。
			@~japanese	@details	表示エリアの縦方向のサイズを取得します。
			@~japanese	@return	縦サイズ
			@~japanese	@exception	なし
		*/
		virtual size_t GetDisplayHeight() const = 0;
		
		/*!
			@~english	@brief	Get device context handle.
			@~english	@details	Get device context handle.
			@~english	@return	Device context handle. In Mac/Linux (Qt-based), HDC (void*) is a QPainter*.
			@~english	@exception	None.
			@~japanese	@brief	文字や図形の描画に使用するデバイスコンテキストを取得します。
			@~japanese	@details	文字や図形の描画に使用するデバイスコンテキストを取得します。
			@~japanese	@return	デバイスコンテキスト。Mac/Linux Qtの場合はHDC (void*)はQPainter*です。
			@~japanese	@exception	なし
		*/
		virtual HDC		GetDC() const = 0;
	};
}
#endif //STDISPLAYIMAGEWND_H
