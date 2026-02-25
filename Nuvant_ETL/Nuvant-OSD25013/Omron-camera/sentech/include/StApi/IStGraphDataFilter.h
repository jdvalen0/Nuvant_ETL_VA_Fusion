//------------------------------------------------------------------------------
//  StApi
//------------------------------------------------------------------------------
/*!
	@ingroup	StApiIP_PublicInterface
	@file
	@~english	@details	Definition of interface IStGraphDataFilter
	@~japanese	@details	IStGraphDataFilter インターフェースの定義
*/
#ifndef ISTGRAPHDATAFILTER_H__
#define ISTGRAPHDATAFILTER_H__
#include "IStFilter.h"
#include "IStGraphDataBufferList.h"

namespace StApi
{
	// ---------------------------------------------------------------------
	// interface IStGraphDataFilter
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiIP_PublicInterface
		@interface IStGraphDataFilter
		@~english	@brief	Interface for Graph Data Filter.
		@~english	@details	Interface for Graph Data Filter.
		@sa	CreateIStFilter(), GetIStFilterInfo()
		@~japanese	@brief	グラフデータフィルター用インターフェース
		@~japanese	@details	グラフデータフィルター用インターフェース
		@sa	CreateIStFilter(), GetIStFilterInfo()
		@since StApi v1.1.1
	*/
	interface PUBLIC_INTERFACE IStGraphDataFilter : public IStFilter
	{

		/*!
			@~english	@brief	Acquire current ROI mode.
			@~english	@details	Acquire current ROI mode.
			@~english	@return	ROI mode.
			@~english	@exception	None.
			@~japanese	@brief	ROIモードを取得します。
			@~japanese	@details	ROIモードを取得します。
			@~japanese	@return	ROIモード
			@~japanese	@exception	なし
		*/
		virtual EStROIMode_t GetROIMode() const = 0;

		/*!
			@~english	@brief	Set ROI mode.
			@~english	@details	Set ROI mode.
			@~english	@param[in] eRM	ROI mode.
			@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument. 
			@~japanese	@brief	ROIモードを設定します。
			@~japanese	@details	ROIモードを設定します。
			@~japanese	@param[in] eRM	ROIモード
			@~japanese	@exception	不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void SetROIMode(EStROIMode_t eRM) = 0;

		/*!
			@~english	@brief	Get X-axis offset value of ROI.
			@~english	@details	Get X-axis offset value of ROI.
			@~english	@return	X-axis offset value.
			@~english	@exception	None.
			@~japanese	@brief	横方向のオフセット値を取得します。
			@~japanese	@details	横方向のオフセット値を取得します。
			@~japanese	@return	横方向のオフセット値
			@~japanese	@exception	なし
		*/
		virtual size_t GetOffsetX() const = 0;

		/*!
			@~english	@brief	Set X-axis offset value of ROI.
			@~english	@details	Set X-axis offset value of ROI.
			@~english	@param[in]	value	X-axis offset value.
			@~english	@exception	None.
			@~japanese	@brief	横方向のオフセット値を設定します。
			@~japanese	@details	横方向のオフセット値を設定します。
			@~japanese	@param[in]	value	横方向のオフセット値
			@~japanese	@exception	なし
		*/
		virtual void SetOffsetX(size_t value) = 0;

		/*!
			@~english	@brief	Get Y-axis offset value of ROI.
			@~english	@details	Get Y-axis offset value of ROI.
			@~english	@return	Y-axis offset value.
			@~english	@exception	None.
			@~japanese	@brief	縦方向のオフセット値を取得します。
			@~japanese	@details	縦方向のオフセット値を取得します。
			@~japanese	@return	縦方向のオフセット値
			@~japanese	@exception	なし
		*/
		virtual size_t GetOffsetY() const = 0;

		/*!
			@~english	@brief	Set Y-axis offset value of ROI.
			@~english	@details	Set Y-axis offset value of ROI.
			@~english	@param[in]	value	Y-axis offset value.
			@~english	@exception	None.
			@~japanese	@brief	縦方向のオフセット値を設定します。
			@~japanese	@details	縦方向のオフセット値を設定します。
			@~japanese	@param[in]	value	縦方向のオフセット値
			@~japanese	@exception	なし
		*/
		virtual void SetOffsetY(size_t value) = 0;

		/*!
			@~english	@brief	Get width of ROI.
			@~english	@details	Get width of ROI.
			@~english	@return	Width of ROI.
			@~english	@exception	None.
			@~japanese	@brief	横方向のサイズを取得します。
			@~japanese	@details	横方向のサイズを取得します。
			@~japanese	@return	横方向のサイズ
			@~japanese	@exception	なし
		*/
		virtual size_t GetWidth() const = 0;

		/*!
			@~english	@brief	Set width of ROI.
			@~english	@details	Set width of ROI.
			@~english	@param[in]	value	Width of ROI.
			@~english	@exception	None.
			@~japanese	@brief	横方向のサイズを設定します。
			@~japanese	@details	横方向のサイズを設定します。
			@~japanese	@param[in]	value	横方向のサイズ
			@~japanese	@exception	なし
		*/
		virtual void SetWidth(size_t value) = 0;

		/*!
			@~english	@brief	Get height of ROI.
			@~english	@details	Get height of ROI.
			@~english	@return	Height of ROI.
			@~english	@exception	None.
			@~japanese	@brief	縦方向のサイズを取得します。
			@~japanese	@details	縦方向のサイズを取得します。
			@~japanese	@return	縦方向のサイズ
			@~japanese	@exception	なし
		*/
		virtual size_t GetHeight() const = 0;
		
		/*!
			@~english	@brief	Set height of ROI.
			@~english	@details	Set height of ROI.
			@~english	@param[in]	value	Height of ROI.
			@~english	@exception	None.
			@~japanese	@brief	縦方向のサイズを設定します。
			@~japanese	@details	縦方向のサイズを設定します。
			@~japanese	@param[in]	value	縦方向のサイズ
			@~japanese	@exception	なし
		*/
		virtual void SetHeight(size_t value) = 0;
		/*!
			@~english	@brief	Acquire the type of the data.
			@~english	@details	Acquire the type of the data.
			@~english	@return	Type of the data.
			@~english	@exception	None.
			@~japanese	@brief	データのタイプを取得します。
			@~japanese	@details	データのタイプを取得します。
			@~japanese	@return	データのタイプ
			@~japanese	@exception	なし
		*/
		virtual EStGraphDataType_t GetGraphDataType() const = 0;

		/*!
			@~english	@brief	Set the type of the data.
			@~english	@details	Set the type of the data.
			@~english	@param[in] eValue	Type of the data.
			@~english	@exception	None.
			@~japanese	@brief	データのタイプを設定します。
			@~japanese	@details	データのタイプを設定します。
			@~japanese	@param[in] eValue	データのタイプ
			@~japanese	@exception	なし
		*/
		virtual void SetGraphDataType(EStGraphDataType_t eValue) = 0;

		/*!
			@~english	@brief	Acquire the list of the graph data.
			@~english	@details	Acquire the list of the graph datadata.
			@~english	@return	List of the data.
			@~english	@exception	None.
			@~japanese	@brief	グラフデータのバッファリストを取得します。
			@~japanese	@details	グラフデータのバッファリストを取得します。
			@~japanese	@return	グラフデータのバッファリスト
			@~japanese	@exception	なし
		*/
		virtual const IStGraphDataBufferList* GetIStGraphDataBufferList() const = 0;

	};

	//---------------------------------------------------------------------
	// typedef CIStGraphDataFilterPtr
	//---------------------------------------------------------------------
	/*!
		@ingroup StApiIP_PublicImpl
		@typedef CIStGraphDataFilterPtr
		@~english	@brief	The auto management class of IStGraphDataFilter class.
		@~english	@details	The auto management class of IStGraphDataFilter class.Use this class instead of managing the initial/release of IStGraphDataFilter class yourself. The destructor of this class will automatically call IStFilterReleasable::Release().
		@sa	CreateIStFilter(), GetIStFilterInfo()
		@~japanese	@brief	グラフデータフィルター用インターフェースポインターの自動管理用クラスです。
		@~japanese	@details	グラフデータフィルター用インターフェースポインターの自動管理用クラスです。このクラスのデストラクタから IStGraphDataFilter::Release() が自動的に呼び出されます。
		@sa	CreateIStFilter(), GetIStFilterInfo()
		@since StApi v1.1.1
	*/
	typedef CStAutoPtr<IStFilterReleasable, IStGraphDataFilter> CIStGraphDataFilterPtr;
}


#endif //ISTGRAPHDATAFILTER_H__