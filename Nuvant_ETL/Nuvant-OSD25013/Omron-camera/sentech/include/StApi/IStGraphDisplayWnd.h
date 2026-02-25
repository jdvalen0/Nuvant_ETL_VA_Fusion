//------------------------------------------------------------------------------
//  StApi
//------------------------------------------------------------------------------
/*!
	@ingroup	StApiGUI_PublicInterface
	@file
	@~english	@details	Definition of interface IStGraphDisplayWnd
	@~japanese	@details	IStGraphDisplayWnd インターフェースの定義
*/
#ifndef ISTGRAPHDISPLAYWND_H__
#define ISTGRAPHDISPLAYWND_H__

#include "IStWnd.h"
#include "IStGraphDataBufferList.h"

namespace StApi
{
	
	// ---------------------------------------------------------------------
	// interface IStImageDisplayWnd
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiGUI_PublicInterface
		@interface IStGraphDisplayWnd
		@~english	@brief	Interface for Display Graph Window.
		@~english	@details	Interface for Display Graph Window.
		@~japanese	@brief	グラフ表示ウィンドウ用インターフェース
		@~japanese	@details	グラフ表示ウィンドウ用インターフェース
		@since StApi v1.1.1
	*/
	interface PUBLIC_INTERFACE IStGraphDisplayWnd :public IStWnd
	{
		/*!
			@~english	@brief	Register Graph Data Buffer List to display.
			@~english	@details	Register Graph Data Buffer List to display. The data will be copied.
			@~english	@param[in]	pIStGraphDataBufferList	The graph data to display.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed.
			@~japanese	@brief	表示するグラフデータを登録します。
			@~japanese	@details	表示するグラフデータをを登録します。グラフデータをはSDK内部のバッファへコピーされます。
			@~japanese	@param[in]	pIStGraphDataBufferList	表示するグラフデータの IStGraphDataBufferList インターフェースポインター
			@~japanese	@exception	メモリー確保に失敗した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void RegisterIStGraphDataBufferList(const IStGraphDataBufferList *pIStGraphDataBufferList) = 0;

		/*!
			@~english	@brief	Draw graph.
			@~english	@details	Draw graph.
			@~english	@param[in]	hDC Device context handle. In Mac/Linux (Qt-based), HDC (void*) is a QPainter*.
			@~english	@param[in]	nWidth Width of the graph.
			@~english	@param[in]	nHeight Height of the graph.
			@~english	@exception	None.
			@~japanese	@brief	グラフを描画します。
			@~japanese	@details	グラフを描画します。
			@~japanese	@param[in]	hDC	デバイスコンテキスト。Mac/Linux Qtの場合はHDC (void*)はQPainter*です。
			@~japanese	@param[in]	nWidth グラフの横サイズ
			@~japanese	@param[in]	nHeight グラフの縦サイズ
			@~japanese	@exception	なし
		*/
		virtual void Draw(HDC hDC, uint32_t nWidth, uint32_t nHeight) = 0;
		
		/*!
			@~english	@brief	Get graph image.
			@~english	@details	Get graph image.
			@~english	@param[in,out]	pIStImageBuffer	Image buffer for graph image.
			@~english	@param[in]	nImageWidth Width of the image. If the value is equal to 0, the image width is same as the width of displayed graph.
			@~english	@param[in]	nImageHeight Height of the image. If the value is equal to 0, the image height is same as the height of displayed graph.
			@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument. 
			@~japanese	@brief	グラフの画像データを取得します。
			@~japanese	@details	グラフの画像データを取得します。
			@~japanese	@param[in,out]	pIStImageBuffer	strFileName	グラフの画像データを取得するバッファを指定します。
			@~japanese	@param[in]	nImageWidth 画像の横サイズ(0指定時は表示サイズ)
			@~japanese	@param[in]	nImageHeight 画像の縦サイズ(0指定時は表示サイズ)
			@~japanese	@exception	不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void GetIStImage(IStImageBuffer *pIStImageBuffer, size_t nImageWidth = 0, size_t nImageHeight = 0) = 0;
	};

	//---------------------------------------------------------------------
	// typedef CIStGraphDisplayWndPtr
	//---------------------------------------------------------------------
	/*!
		@ingroup StApiGUI_PublicImpl
		@typedef CIStGraphDisplayWndPtr
		@~english	@brief	This class is for lifetime management of IStGraphDisplayWnd.
		@~english	@details	This class is for lifetime management of IStGraphDisplayWnd. The destructor of this class will automatically call IStWndReleasable::Release().
		@~japanese	@brief	IStGraphDisplayWnd インターフェースポインターの自動管理用クラスです。
		@~japanese	@details	IStGraphDisplayWnd インターフェースポインターの自動管理用クラスです。このクラスのデストラクタから IStWndReleasable::Release() が自動的に呼び出されます。
		@since StApi v1.1.1
	*/
	typedef CStAutoPtr<IStWndReleasable, IStGraphDisplayWnd> CIStGraphDisplayWndPtr;

	//---------------------------------------------------------------------
	// typedef CIStGraphDisplayWndPtrArray
	//---------------------------------------------------------------------
	/*!
		@ingroup StApiGUI_PublicImpl
		@typedef CIStGraphDisplayWndPtrArray
		@~english	@brief	This class is for lifetime management of multiple objects of IStGraphDisplayWnd.
		@~english	@details	This class is for lifetime management of multiple objects of IStGraphDisplayWnd. The destructor of this class will automatically call IStWndReleasable::Release().
		@~japanese	@brief	IStGraphDisplayWnd インターフェースポインターの自動管理用クラスです。
		@~japanese	@details	IStGraphDisplayWnd インターフェースポインターの自動管理用クラスです。このクラスのデストラクタから IStWndReleasable::Release() が自動的に呼び出されます。
		@since StApi v1.1.1
	*/
	typedef CIStWndPtrArrayT<IStGraphDisplayWnd> CIStGraphDisplayWndPtrArray;
}


#endif //ISTGRAPHDISPLAYWND_H__
