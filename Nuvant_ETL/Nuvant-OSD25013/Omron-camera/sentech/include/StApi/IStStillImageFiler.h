//------------------------------------------------------------------------------
// StApi
//------------------------------------------------------------------------------
/*!
	@ingroup	StApiIP_PublicInterface
	@file
	@~english	@details	Definition of interface IStStillImageFiler
	@~japanese	@details	IStStillImageFiler インターフェースの定義
*/
#ifndef ST_IMAGE_PERSISTENCE_H
#define ST_IMAGE_PERSISTENCE_H

#include "IStFiler.h"

namespace StApi
{
	interface IStImage;

	//---------------------------------------------------------------------
	// interface IStStillImageFiler
	//---------------------------------------------------------------------
	/*!
		@ingroup StApiIP_PublicInterface
		@interface IStStillImageFiler
		@~english	@brief	Interface for Image Persistence.
		@~english	@details	Interface for Image Persistence.
		@sa	CreateIStFiler()
		@~japanese	@brief	静止画ファイラー用インターフェース
		@~japanese	@details	静止画ファイラー用インターフェース
		@sa	CreateIStFiler()
	*/
	interface PUBLIC_INTERFACE IStStillImageFiler : public IStFiler
	{
		/*!
			@~english	@brief	Check if the target pixel format can be saved as the still image file format.
			@~english	@details	Check if the target pixel format can be saved as the still image file format.
			@~english	@param[in]	ePFNC	Target pixel format.
			@~english	@param[in]	eSIFF	Still image file format.
			@~english	@return	True if save is supported.
			@~english	@exception	None.
			@~japanese	@brief	指定したピクセルフォーマットの保存に対応しているかを確認します。
			@~japanese	@details	指定したピクセルフォーマットの保存に対応しているかを確認します。
			@~japanese	@param[in]	ePFNC	ピクセルフォーマット
			@~japanese	@param[in]	eSIFF	静止画ファイルフォーマット
			@~japanese	@return	対応している場合、 true が返されます。
			@~japanese	@exception	なし
		*/
		virtual bool IsSaveSupported(EStPixelFormatNamingConvention_t ePFNC, EStStillImageFileFormat_t eSIFF) const = 0;

		/*!
			@~english	@brief	Check if the still image file format can be loaded as the target pixel format.
			@~english	@details	Check if the still image file format can be loaded as the target pixel format.
			@~english	@attention	Currently this only supports StStillImageFileFormat_StApiRaw.
			@~english	@param[in]	ePFNC	Target pixel format.
			@~english	@param[in]	eSIFF	Still image file format.
			@~english	@return	True if load is supported.
			@~english	@exception	None.
			@~japanese	@brief	指定したピクセルフォーマットの読み込みに対応しているかを確認します。
			@~japanese	@details	指定したピクセルフォーマットの読み込みに対応しているかを確認します。
			@~japanese	@attention	現在、読み込みに対応しているのは StStillImageFileFormat_StApiRaw フォーマットのみとなります。
			@~japanese	@param[in]	ePFNC	ピクセルフォーマット
			@~japanese	@param[in]	eSIFF	静止画ファイルフォーマット
			@~japanese	@return	対応している場合、 true が返されます。
			@~japanese	@exception	なし
		*/
		virtual bool IsLoadSupported(EStPixelFormatNamingConvention_t ePFNC, EStStillImageFileFormat_t eSIFF) const = 0;

		/*!
			@~english	@brief	Save image data to file.
			@~english	@details	Save image data to file.
			@~english	@param[in]	pImage	Image data.
			@~english	@param[in]	eSIFF	Still image file format.
			@~english	@param[in]	strFileName	File name.
			@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument. 
			@~japanese	@brief	画像データを静止画ファイルへ保存します。
			@~japanese	@details	画像データを静止画ファイルへ保存します。
			@~japanese	@param[in]	pImage	保存する画像データ
			@~japanese	@param[in]	eSIFF	静止画ファイルフォーマット
			@~japanese	@param[in]	strFileName	ファイル名
			@~japanese	@exception	不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void Save(IStImage *pImage, EStStillImageFileFormat_t eSIFF, const GenICam::gcstring &strFileName) const = 0;

		/*!
			@~english	@brief	Read image data from file.
			@~english	@details	Read image data from file.
			@~english	@attention	Currently this only supports StStillImageFileFormat_StApiRaw.
			@~english	@param[in]	pIStImageBuffer	Buffer to store image data from file.
			@~english	@param[in]	strFileName	File name.
			@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument. 
			@~japanese	@brief	静止画ファイルを画像バッファへ読み込みます。
			@~japanese	@details	静止画ファイルを画像バッファへ読み込みます。
			@~japanese	@attention	現在、読み込みに対応しているのは StStillImageFileFormat_StApiRaw フォーマットのみとなります。
			@~japanese	@param[in]	pIStImageBuffer	画像バッファ
			@~japanese	@param[in]	strFileName	ファイル名
			@~japanese	@exception	不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void Load(IStImageBuffer *pIStImageBuffer, const GenICam::gcstring &strFileName) const = 0;

		/*!
			@~english	@brief	Acquire JPEG image quality setting.
			@~english	@details	Acquire JPEG image quality setting.
			@~english	@return		Quality value. 0(Low) ~ 100(High).
			@~english	@exception	None.
			@~japanese	@brief	JPEGファイルの品質設定を取得します。
			@~japanese	@details	JPEGファイルの品質設定を取得します。
			@~japanese	@return		品質 0:低品質～100:高品質
			@~japanese	@exception	なし
		*/
		virtual uint32_t GetQuality() const = 0;
		
		/*!
			@~english	@brief	Set JPEG image quality.
			@~english	@details	Set JPEG image quality.
			@~english	@param[in]	value		Quality value. 0(Low) ~ 100(High).
			@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument. 
			@~japanese	@brief	JPEGファイルの品質を設定します。
			@~japanese	@details	JPEGファイルの品質を設定します。
			@~japanese	@param[in]	value		品質 0:低品質～100:高品質
			@~japanese	@exception	不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void SetQuality(uint32_t value) = 0;
	};
	
	//---------------------------------------------------------------------
	// typedef CIStStillImageFilerPtr
	//---------------------------------------------------------------------
	/*!
		@ingroup StApiIP_PublicImpl
		@typedef CIStStillImageFilerPtr
		@~english	@brief	The auto management class of IStStillImageFiler class for still image file handling.
		@~english	@details	The auto management class of IStStillImageFiler class for still image file handling. Use this class instead of managing the initial/release of IStStillImageFiler class yourself. The destructor of this class will automatically call IStFilerReleasable::Release().
		@sa	CreateIStFiler()
		@~japanese	@brief	静止画ファイラー用インターフェースポインターの自動管理用クラスです。
		@~japanese	@details	静止画ファイラー用インターフェースポインターの自動管理用クラスです。このクラスのデストラクタから IStFilerReleasable::Release() が自動的に呼び出されます。
		@sa	CreateIStFiler()
	*/
	typedef CStAutoPtr<IStFilerReleasable, IStStillImageFiler> CIStStillImageFilerPtr;
}
#endif //ST_IMAGE_PERSISTENCE_H



