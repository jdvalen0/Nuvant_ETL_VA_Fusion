//------------------------------------------------------------------------------
// StApi
//------------------------------------------------------------------------------
/*!
	@ingroup	StApiIP_PublicInterface
	@file
	@~english	@details	Definition of interface IStSNMeasurementFilter
	@~japanese	@details	IStSNMeasurementFilter インターフェースの定義
*/
#ifndef STSNMeasurementFILTER_H
#define STSNMeasurementFILTER_H

#include "IStFilter.h"

namespace StApi
{
	//---------------------------------------------------------------------
	// interface IStSNMeasurementResult
	//---------------------------------------------------------------------
	/*!
		@ingroup StApiIP_PublicInterface
		@interface IStSNMeasurementResult
		@~english	@brief	Interface for SN Measurement Result.
		@~english	@details	Interface for SN Measurement Result.
		@~japanese	@brief	SN測定結果用インターフェース
		@~japanese	@details	SN測定結果用インターフェース
	*/
	interface PUBLIC_INTERFACE IStSNMeasurementResult
	{
		/*!
			@~english	@brief	Get the component counts of pixel.
			@~english	@details	Get the component counts of pixel.
			@~english	@return	Component counts.
			@~english	@exception	None.
			@~japanese	@brief	構成要素の数を取得します。
			@~japanese	@details	構成要素の数を取得します。
			@~japanese	@return	構成要素の数
			@~japanese	@exception	なし
		*/
		virtual size_t GetComponentCount() const = 0;

		/*!
			@~english	@brief	Get the information of target component. 
			@~english	@details	Get the information of target component. 
			@~english	@param[in]	nIndex		Index of the target component. Index can be assigned from 0 to GetComponentCount() - 1.
			@~english	@param[out]	pePC		The component type.
			@~english	@param[out]	pnPixelCount	The pixel counts.
			@~english	@param[out]	pdblAverage		The average value.
			@~english	@param[out]	pdblTemporalStandardDeviation	The average of standard deviation of all pixels.
			@~english	@param[out]	pdblFrameStandardDeviation	The average of standard deviation of every frame.
			@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument. 
			@~japanese	@brief	指定した構成要素の情報を取得します。
			@~japanese	@details	指定した構成要素の情報を取得します。
			@~japanese	@param[in]	nIndex		構成要素を指定します。0から GetComponentCount() - 1 の値を指定します。
			@~japanese	@param[out]	pePC		ピクセル構成要素タイプ
			@~japanese	@param[out]	pnPixelCount		ピクセル数
			@~japanese	@param[out]	pdblAverage		平均値
			@~japanese	@param[out]	pdblTemporalStandardDeviation	同じ位置の画素の標準偏差を平均値。同じ位置の画素値が安定していると小さな値になります。
			@~japanese	@param[out]	pdblFrameStandardDeviation	1フレーム内の画素の標準偏差の平均値。均一な被写体を撮像した際に取得された画像が均一になっていると小さな値になります。
			@~japanese	@exception	不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void GetSNMeasurementValue(size_t nIndex, EStPixelComponent_t *pePC, size_t *pnPixelCount, double *pdblAverage, double *pdblTemporalStandardDeviation, double *pdblFrameStandardDeviation) const = 0;
	};
	
	interface IStImage;

	//---------------------------------------------------------------------
	// interface IStSNMeasurementFilter
	//---------------------------------------------------------------------
	/*!
		@ingroup StApiIP_PublicInterface
		@interface IStSNMeasurementFilter
		@~english	@brief	Interface for SN Measurement Filter.
		@~english	@details	Interface for SN Measurement Filter.
		@sa	CreateIStFilter(), GetIStFilterInfo()
		@~japanese	@brief	SN測定フィルター用インターフェース
		@~japanese	@details	SN測定フィルター用インターフェース
		@sa	CreateIStFilter(), GetIStFilterInfo()
	*/
	interface PUBLIC_INTERFACE IStSNMeasurementFilter : public IStFilter
	{
		/*!
			@~english	@brief	Discard the current acquired data.
			@~english	@details	Discard the current acquired data.
			@~english	@exception	None.
			@~japanese	@brief	保持している画像データを破棄します。
			@~japanese	@details	保持している画像データを破棄します。
			@~japanese	@exception	なし
		*/
		virtual void ClearGrabbedImage() = 0;

		/*!
			@~english	@brief	Acquire counts of frame for measurement.
			@~english	@details	Acquire counts of frame for measurement.
			@~english	@return	Counts of frame for measurement.
			@~english	@exception	None.
			@~japanese	@brief	統計値算出に使用するフレーム数を取得します。
			@~japanese	@details	統計値算出に使用するフレーム数を取得します。
			@~japanese	@return	統計値算出に使用するフレーム数
			@~japanese	@exception	なし
		*/
		virtual size_t GetFrameCount() const = 0;

		/*!
			@~english	@brief	Set the number of frames that will be acquired for measurement.
			@~english	@details	Set the number of frames that will be acquired for measurement.
			@~english	@param[in]	value	Number of frames. Can be set from 1 to 1024.
			@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument. 
			@~japanese	@brief	統計値算出に使用するフレーム数を設定します。
			@~japanese	@details	統計値算出に使用するフレーム数を設定します。
			@~japanese	@param[in]	value	統計値算出に使用するフレーム数(1～1024)
			@~japanese	@exception	不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void SetFrameCount(size_t value) = 0;

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
			@~english	@brief	Retrieve SN measurement result.
			@~english	@details	Retrieve SN measurement result.
			@~english	@param[in]	dwTimeout	Timeout [ms].
			@~english	@param[in]	eHandlingOfTimeout	timeout handler.
			@~english	@return	Return IStSNMeasurementResult interface pointer if success.
			@~english	@exception	Throw out GenICam::GenericException when timeout occurred and the timeout handle exists.
			@~japanese	@brief	計測結果を取得します。
			@~japanese	@details	計測結果を取得します。指定した時間内に計測が完了しない(指定したフレームを渡さなかった)場合、タイムアウトが発生します。
			@~japanese	@param[in]	dwTimeout	タイムアウト時間[ms]
			@~japanese	@param[in]	eHandlingOfTimeout	タイムアウトへの対処
			@~japanese	@return	IStSNMeasurementResult インターフェースポインター
			@~japanese	@exception	タイムアウトが発生し、その対処に例外を選択した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual IStSNMeasurementResult *RetrieveIStSNMeasurementResult(uint32_t dwTimeout, EStTimeoutHandling_t eHandlingOfTimeout = StTimeoutHandling_ThrowException) = 0;
	};

	//---------------------------------------------------------------------
	// typedef CIStSNMeasurementFilterPtr
	//---------------------------------------------------------------------
	/*!
		@ingroup StApiIP_PublicImpl
		@typedef CIStSNMeasurementFilterPtr
		@~english	@brief	 This class if for lifetime management of IStSNMeasurementFilter.
		@~english	@details	This class if for lifetime management of IStSNMeasurementFilter. The destructor of this class will automatically call IStFilterReleasable::Release().
		@sa	CreateIStFilter(), GetIStFilterInfo()
		@~japanese	@brief	SN測定フィルター用インターフェースポインターの自動管理用クラスです。
		@~japanese	@details	SN測定フィルター用インターフェースポインターの自動管理用クラスです。このクラスのデストラクタから IStFilterReleasable::Release() が自動的に呼び出されます。
		@sa	CreateIStFilter(), GetIStFilterInfo()
	*/
	typedef CStAutoPtr<IStFilterReleasable, IStSNMeasurementFilter> CIStSNMeasurementFilterPtr;
}
#endif //STSNMeasurementFILTER_H



