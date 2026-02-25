//------------------------------------------------------------------------------
//  StApi
//------------------------------------------------------------------------------
/*!
	@ingroup	StApiGUI_PublicInterface
	@file
	@~english	@details	Definition of interface IStDrawingTool
	@~japanese	@details	IStDrawingTool インターフェースの定義
*/
#ifndef ISTDRAWINGTOOL_H__
#define ISTDRAWINGTOOL_H__

#include "IStWnd.h"

namespace StApi
{
	
	// ---------------------------------------------------------------------
	// interface IStDrawingTool
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiGUI_PublicInterface
		@interface IStDrawingTool
		@~english	@brief	Interface for tool to draw on a image.
		@~english	@details	Interface for tool to draw on a image.
		@~japanese	@brief	画像上への描画用ツールウィンドウインターフェース
		@~japanese	@details	画像上への描画用ツールウィンドウインターフェース
		@since StApi v1.1.1
	*/
	interface PUBLIC_INTERFACE IStDrawingTool
	{

		/*!
			@~english	@brief	Draw on the specific image buffer.
			@~english	@details	Draw on the specific image buffer.
			@~english	@param[in]	pIStImageBuffer	Image buffer on which figures will be drawn.
			@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument. 
			@~japanese	@brief	指定された画像バッファに描画を行います。
			@~japanese	@details	指定された画像バッファに描画を行います。
			@~japanese	@param[in]	pIStImageBuffer	描画先の画像バッファ
			@~japanese	@exception	不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void DrawOnIStImageBuffer(StApi::IStImageBuffer *pIStImageBuffer) = 0;
		
	};

}


#endif //ISTDRAWINGTOOL_H__
