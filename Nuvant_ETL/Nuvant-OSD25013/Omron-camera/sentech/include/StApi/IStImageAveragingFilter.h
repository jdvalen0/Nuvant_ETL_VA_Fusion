//------------------------------------------------------------------------------
//  StApi
//------------------------------------------------------------------------------
/*!
	@ingroup	StApiIP_PublicInterface
	@file
	@~english	@details	Definition of interface IStImageAveragingFilter
	@~japanese	@details	IStImageAveragingFilter インターフェースの定義
*/
#ifndef ST_IMAGE_AVERAGING_FILTER_H
#define ST_IMAGE_AVERAGING_FILTER_H

#include "IStFilter.h"

namespace StApi
{
	// ---------------------------------------------------------------------
	// interface IStImageAveragingFilter
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiIP_PublicInterface
		@interface IStImageAveragingFilter
		@~english	@brief	Interface for Image Averaging Filter.
		@~english	@details	Interface for Image Averaging Filter.
		@~japanese	@brief	画像平均化フィルター用インターフェース
		@~japanese	@details	画像平均化フィルター用インターフェース
		@sa	CreateIStFilter(), GetIStFilterInfo()
	*/

	interface PUBLIC_INTERFACE IStImageAveragingFilter : public IStFilter
	{
		/*!
			@~english	@brief	Get averaged image data.
			@~english	@details	Get averaged image data.
			@~english	@param[in, out]	pIStImageBuffer	IStImageBuffer interface pointer for averaged image.
			@~english	@param[in]	nEachComponentBitsCount	Bits count of each component of the averaged image. If 0 is specified and the count of bits of the original image is bigger than or equals to 8, the same count of bits as the original image is used.
			@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument or there is no image data. 
			@~japanese	@brief	 平均化された画像データを取得します。
			@~japanese	@details	平均化された画像データを取得します。
			@~japanese	@param[in, out]	pIStImageBuffer	平均化された画像用の IStImageBuffer インターフェースポインター
			@~japanese	@param[in]	nEachComponentBitsCount	平均化された画像の個々の構成要素のビット数を指定します。0が指定されかつ入力画像のビット数が8以上の場合は、入力画像と同じビット数が使用されます。
			@~japanese	@exception	不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void GetAveragedImage(StApi::IStImageBuffer *pIStImageBuffer, size_t nEachComponentBitsCount = 0) = 0;

		/*!
			@~english	@brief	Clear accumulated image data.
			@~english	@details	Clear accumulated image data.
			@~english	@exception	None.
			@~japanese	@brief	 積算された画像データを消去します。
			@~japanese	@details	積算された画像データを消去します。
			@~japanese	@exception	なし
		*/
		virtual void ClearImageData() = 0;

		/*!
			@~english	@brief	Get a count of the images.
			@~english	@details	Get a count of the images.
			@~english	@return		Count of the images.
			@~english	@exception	None.
			@~japanese	@brief	 積算された画像の数を取得します。
			@~japanese	@details	積算された画像の数を取得します。
			@~japanese	@return		積算された画像の数
			@~japanese	@exception	なし
		*/
		virtual size_t GetFrameCount() = 0;
	};


	// ---------------------------------------------------------------------
	// interface IStImageAveragingFilterReleasable
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiIP_PublicInterface
		@interface IStImageAveragingFilterReleasable
		@~english	@brief	Interface for Image Accumulation(Releasable).
		@~english	@details	Interface for Image Accumulation(Releasable).
		@~japanese	@brief	解放可能な画像積算用インターフェース
		@~japanese	@details	解放可能な画像積算用インターフェース
		@sa	CreateIStFilter()
	*/
	interface PUBLIC_INTERFACE IStImageAveragingFilterReleasable : public IStImageAveragingFilter, public IStReleasable
	{

	};

	//---------------------------------------------------------------------
	// typedef CIStImageAveragingFilterPtr
	//---------------------------------------------------------------------
	/*!
		@ingroup StApiIP_PublicImpl
		@typedef CIStEdgeEnhancementFilterPtr
		@~english	@brief	The auto management class of IStImageAveragingFilter class.
		@~english	@details	The auto management class of IStImageAveragingFilter class.Use this class instead of managing the initial/release of IStImageAveragingFilter class yourself. The destructor of this class will automatically call IStFilterReleasable::Release().
		@sa	CreateIStFilter(), GetIStFilterInfo()
		@~japanese	@brief	IStImageAveragingFilter インターフェースポインターの自動管理用クラスです。
		@~japanese	@details	IStImageAveragingFilter インターフェースポインターの自動管理用クラスです。このクラスのデストラクタから IStFilterReleasable::Release() が自動的に呼び出されます。
		@sa	CreateIStFilter(), GetIStFilterInfo()
	*/
	typedef CStAutoPtr<IStFilterReleasable, IStImageAveragingFilter> CIStImageAveragingFilterPtr;
}

#endif //ST_IMAGE_AVERAGING_FILTER_H