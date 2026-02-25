/* This file is encoded in UTF-8,  */
/* but BOM has not been added to accommodate environments not compatible with BOM. */
/*
 StApi
*/
/*!
	@ingroup	StApiGUI_PublicImpl
	@file	StApi_GUIDef.h
	@~english	@details	
	@~japanese	@details	
*/
#ifndef STAPI_GUIDEF_H__
#define STAPI_GUIDEF_H__

#define ENABLE_DRAWING_TOOLS

#ifdef __cplusplus
namespace StApi
{
#endif /* __cplusplus */
	//-------------------------------------------------------------------------
	//Enumerator
	//-------------------------------------------------------------------------
	/*! 
		@ingroup	StApiGUI_PublicImpl
		@enum EStWindowType_t
		@~english	@brief	Enumerator for Window type.
		@~english	@details	Enumerator for Window type.
		@~japanese	@brief	ウィンドウタイプ列挙子
		@~japanese	@details	ウィンドウタイプ列挙子
	*/
	typedef enum _EStWindowType_t
	{
		/*!
			@~english	@details	Device selection Window
			@~japanese	@details	デバイス選択ウィンドウ
		*/
		StWindowType_DeviceSelection,

		/*!
			@~english	@details	Image display Window
			@~japanese	@details	画像表示ウィンドウ
		*/
		StWindowType_ImageDisplay,

		/*!
			@~english	@details	Node map display Window
			@~japanese	@details	ノードマップウィンドウ
		*/
		StWindowType_NodeMapDisplay,

		/*!
			@~english	@details	Graph display Window
			@~japanese	@details	グラフ表示ウィンドウ
			@since StApi v1.1.1
		*/
		StWindowType_GraphDisplay,

		/*!
			@~english	@details	Count of Window type.
			@~japanese	@details	定義済ウィンドウタイプ数
		*/
		StWindowType_Count					
	}EStWindowType_t, *PEStWindowType_t;

	/*!
		@ingroup	StApiGUI_PublicImpl
		@enum EStWindowMode_t
		@~english	@brief	Enumerator for Window mode.
		@~english	@details	Enumerator for Window mode.
		@~japanese	@brief	ウィンドウモード列挙子
		@~japanese	@details	ウィンドウモード列挙子
	*/
	typedef enum _EStWindowMode_t
	{
		/*!
			@~english	@details	Modal Window
			@~japanese	@details	モーダルウィンドウ
		*/
		StWindowMode_Modal,

		/*!
			@~english	@details	Modaless Window (On current thread)
			@~japanese	@details	モーダレスウィンドウ(現在のスレッドを使用)
		*/
		StWindowMode_Modaless,

		/*!
			@~english	@details	Modaless Window (On new thread): Windows OS only
			@~japanese	@details	モーダレスウィンドウ(新しいスレッドを生成): Windows OSのみ
		*/
		StWindowMode_ModalessOnNewThread,

		/*!
			@~english	@details	Child Window
			@~english	@attention	If you display a child Window with desktop Window as its parent, some functions will have limitations. For example, combo box may not work properly.
			@~japanese	@details	子ウィンドウ
			@~japanese	@attention	デスクトップウィンドウを親として子ウィンドウ表示した場合、コンボボックスが機能しないなどの制限があります。
		*/
		StWindowMode_Child,						

		/*!
			@~english	@details	Count of Window mode.
			@~japanese	@details	定義済ウィンドウモード数
		*/
		StWindowMode_Count	
	}EStWindowMode_t, *PEStWindowMode_t;

	/*!
		@ingroup	StApiGUI_PublicImpl
		@enum EStZoomMode_t
		@~english	@brief	Enumerator for image zoom mode.
		@~english	@details	Enumerator for image zoom mode.
		@~japanese	@brief	ズームモード列挙子
		@~japanese	@details	ズームモード列挙子
	*/
	typedef enum _EStZoomMode_t
	{
		/*!
			@~english	@details	Manual.
			@~japanese	@details	倍率指定
		*/
		StZoomMode_Manual,

		/*!
			@~english	@details	Fit to the windows size.
			@~japanese	@details	ウィンドウサイズに合わせる
		*/
		StZoomMode_FitToTheWindowSize,

		/*!
			@~english	@details	Count of zoom mode.
			@~japanese	@details	ズームモードの数
		*/
		StZoomMode_Count
	}EStZoomMode_t, *PEStZoomMode_t;

	/*!
		@ingroup	StApiGUI_PublicImpl
		@enum EStBackgroundStyle_t
		@~english	@brief	Enumerator for background style of image display Window.
		@~english	@details	Enumerator for background style of image display Window.
		@~japanese	@brief	背景スタイル列挙子
		@~japanese	@details	背景スタイル列挙子
	*/
	typedef enum _EStBackgroundStyle_t
	{
		/*!
			@~english	@details	The solid color.
			@~japanese	@details	単一色
		*/
		StBackgroundStyle_None,

		/*!
			@~english	@details	Horizontal hatch.
			@~japanese	@details	水平ハッチ
		*/
		StBackgroundStyle_HorizontalHatch,

		/*!
			@~english	@details	Vertical hatch.
			@~japanese	@details	垂直ハッチ
		*/
		StBackgroundStyle_VerticalHatch,

		/*!
			@~english	@details	45-degree downward left-to-right hatch.
			@~japanese	@details	45 度右上がりのハッチ（右上から左下への対角線)
		*/
		StBackgroundStyle_FDiagonalHatch,

		/*!
			@~english	@details	45 - degree upward left - to - right hatch.
			@~japanese	@details	45 度右下がりのハッチ（左上から右下への対角線）
		*/
		StBackgroundStyle_BDiagonalHatch,

		/*!
			@~english	@details	Horizontal and vertical crosshatch.
			@~japanese	@details	水平と垂直のクロスハッチ
		*/
		StBackgroundStyle_Crosshatch,

		/*!
			@~english	@details	45-degree crosshatch.
			@~japanese	@details	45 度のクロスハッチ（左上から右下と、右上から左下への対角線）
		*/
		StBackgroundStyle_DiagCrosshatch,

		/*!
			@~english	@details	Count of background style.
			@~japanese	@details	背景スタイルの数
		*/
		StBackgroundStyle_Count
	}EStBackgroundStyle_t, *PEStBackgroundStyle_t;

	/*!
		@ingroup	StApiGUI_PublicImpl
		@enum EStPreviewPixelFormatMode_t
		@~english	@brief	Enumerator for pixel format of the preview image.
		@~english	@details	Enumerator for pixel format of the preview image.
		@~japanese	@brief	プレビューピクセルフォーマットモード列挙子
		@~japanese	@details	プレビューピクセルフォーマットモード列挙子
	*/
	typedef enum _EStPreviewPixelFormatMode_t
	{
		/*!
			@~english	@details	Auto(Color:BGRa8 / Black and White:mono8)
			@~japanese	@details	自動(カラー:BGRa8 / モノクロ:mono8)
		*/
		StPreviewPixelFormatMode_Auto,
		/*!
			@~english	@details	Manual
			@~japanese	@details	手動(指定したピクセルフォーマットを使用)
		*/
		StPreviewPixelFormatMode_Manual,
		/*!
			@~english	@details	Count of preview pixel format mode.
			@~japanese	@details	プレビューピクセルフォーマットモードの数
		*/
		StPreviewPixelFormatMode_Count
	}EStPreviewPixelFormatMode_t, *PEStPreviewPixelFormatMode_t;

#ifdef ENABLE_DRAWING_TOOLS
	/*!
		@ingroup	StApiGUI_PublicImpl
		@enum EStDrawingItemType_t
		@~english	@brief	Enumerator for drawing item.
		@~english	@details	Enumerator for drawing item.
		@~japanese	@brief	描画アイテム列挙子
		@~japanese	@details	描画アイテム列挙子
		@since StApi v1.1.1
	*/
	typedef enum _EStDrawingItemType_t
	{
		StDrawingItemType_None,
		StDrawingItemType_Select,
		StDrawingItemType_Line,
		StDrawingItemType_Rectangle,
		StDrawingItemType_Ellipse,
		StDrawingItemType_Text,
		StDrawingItemType_Angle,
		StDrawingItemType_Polygon,
		StDrawingItemType_Perpendicular,
		StDrawingItemType_Arc,
		StDrawingItemType_Bezier,
		StDrawingItemType_FreeHand,
		StDrawingItemType_Cross,
		//StDrawingItemType_RoundRect,
		/*!
			@~english	@details	Count of drawing item.
			@~japanese	@details	描画アイテムの数
			@since StApi v1.1.1
		*/
		StDrawingItemType_Count

	}EStDrawingItemType_t;
#endif //ENABLE_DRAWING_TOOLS

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif //STAPI_GUIDEF_H__
