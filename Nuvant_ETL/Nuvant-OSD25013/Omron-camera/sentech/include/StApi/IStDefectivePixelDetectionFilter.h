//------------------------------------------------------------------------------
//  StApi
//------------------------------------------------------------------------------
/*!
	@ingroup	StApiIP_PublicInterface
	@file
	@~english	@details	Definition of interface IStDefectivePixelDetectionFilter
	@~japanese	@details	IStDefectivePixelDetectionFilter インターフェースの定義
*/
#ifndef ST_DEFECTIVE_PIXEL_DETECTION_FILTER_H
#define ST_DEFECTIVE_PIXEL_DETECTION_FILTER_H

#include "IStFilter.h"

namespace StApi
{
	// ---------------------------------------------------------------------
	// interface IStDefectivePixelDetectionFilter
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiIP_PublicInterface
		@interface IStDefectivePixelDetectionFilter
		@~english	@brief	Interface for Defective Pixel Detection Filter.
		@~english	@details	Interface for Defective Pixel Detection Filter.
		@~japanese	@brief	欠陥画素検出フィルター用インターフェース
		@~japanese	@details	欠陥画素検出フィルター用インターフェース
		@sa	CreateIStFilter(), GetIStFilterInfo()
	*/

	interface PUBLIC_INTERFACE IStDefectivePixelDetectionFilter : public IStFilter
	{
		/*!
			@~english	@brief	Acquire the defect pixel detection result.
			@~english	@details	Acquire the defect pixel detection result.
			@~english	@param[out] peStatus	Get the status of detection.
			@~english	@param[in,out] pnCount	Input the buffer size and output the number of detected defective pixels.
			@~english	@param[out] pDefectivePixelInfoList	Get the information of the defective pixels.
			@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument. 
			@~japanese	@brief	 欠陥画素検出結果を取得します。
			@~japanese	@details	欠陥画素検出結果を取得します。
			@~japanese	@param[out] peStatus	検出の状態を取得します。
			@~japanese	@param[in,out] pnCount	バッファのサイズを入力し、検出された欠陥画素の数を取得します。
			@~japanese	@param[out] pDefectivePixelInfoList	検出された欠陥画素の情報を取得します。
			@~japanese	@exception	不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void GetDetectionResult(EStDefectivePixelDetectionStatus_t *peStatus, size_t *pnCount, PSStDefectivePixelInformation_t pDefectivePixelInfoList) = 0;

		/*!
			@~english	@brief	Clear detected defective pixel information.
			@~english	@details	Clear detected defective pixel information.
			@~english	@exception	None.
			@~japanese	@brief	 検出された欠陥画素情報を消去します。
			@~japanese	@details	検出された欠陥画素情報を消去します。
			@~japanese	@exception	なし
		*/
		virtual void ClearDetectionResult() = 0;
	};


	// ---------------------------------------------------------------------
	// interface IStDefectivePixelDetectionFilterReleasable
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiIP_PublicInterface
		@interface IStDefectivePixelDetectionFilterReleasable
		@~english	@brief	Interface for Defective Pixel Detection(Releasable).
		@~english	@details	Interface for Defective Pixel Detection(Releasable).
		@~japanese	@brief	解放可能な欠陥画素検出インターフェース
		@~japanese	@details	解放可能な欠陥画素検出インターフェース
		@sa	CreateIStFilter()
	*/
	interface PUBLIC_INTERFACE IStDefectivePixelDetectionFilterReleasable : public IStDefectivePixelDetectionFilter, public IStReleasable
	{

	};

	//---------------------------------------------------------------------
	// typedef CIStDefectivePixelDetectionFilterPtr
	//---------------------------------------------------------------------
	/*!
		@ingroup StApiIP_PublicImpl
		@typedef CIStEdgeEnhancementFilterPtr
		@~english	@brief	The auto management class of IStDefectivePixelDetectionFilter class.
		@~english	@details	The auto management class of IStDefectivePixelDetectionFilter class.Use this class instead of managing the initial/release of IStDefectivePixelDetectionFilter class yourself. The destructor of this class will automatically call IStFilterReleasable::Release().
		@sa	CreateIStFilter(), GetIStFilterInfo()
		@~japanese	@brief	IStDefectivePixelDetectionFilter インターフェースポインターの自動管理用クラスです。
		@~japanese	@details	IStDefectivePixelDetectionFilter インターフェースポインターの自動管理用クラスです。このクラスのデストラクタから IStFilterReleasable::Release() が自動的に呼び出されます。
		@sa	CreateIStFilter(), GetIStFilterInfo()
	*/
	typedef CStAutoPtr<IStFilterReleasable, IStDefectivePixelDetectionFilter> CIStDefectivePixelDetectionFilterPtr;
}

#endif //ST_DEFECTIVE_PIXEL_DETECTION_FILTER_H