//------------------------------------------------------------------------------
//  StApi
//------------------------------------------------------------------------------
/*!
	@ingroup	StApiTL_PublicInterface
	@file
	@~english	@details	Definition of interface IStImageBuffer
	@~japanese	@details	IStImageBuffer インターフェースの定義
*/
#ifndef ISTIMAGEBUFFER_H__
#define ISTIMAGEBUFFER_H__

#include "IStImage.h"

namespace StApi
{
	//---------------------------------------------------------------------
	// interface IStImageBuffer
	//---------------------------------------------------------------------
	/*!
		@ingroup StApiTL_PublicInterface
		@interface IStImageBuffer
		@~english	@brief	Interface for Image Buffer object.
		@~english	@details	Interface for Image Buffer object.
		@~english	@sa	CreateIStImageBuffer()
		@~japanese	@brief	画像バッファ用インターフェース
		@~japanese	@details	画像バッファ用インターフェース
		@~japanese	@sa	CreateIStImageBuffer()
	*/
	interface PUBLIC_INTERFACE IStImageBuffer
	{
		/*!
			@~english	@brief	Create an image buffer based on the given parameters.
			@~english	@details      Create an image buffer based on the given parameters.
			@~english	@attention Buffers generated here are deleted automatically when you create the buffers again or when you release the Image Buffer object.
			@~english	@param[in] nWidth	Width of image.
			@~english	@param[in] nHeight	Height of image.
			@~english	@param[in] nPixelFormat	The pixel format of the image.
			@~english	@param[in] eInitializeMemory	Assign the memory initialization method for this buffer.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or there is an invalid argument.
			@~japanese	@brief	指定されたサイズ・フォーマットに従ってバッファを作成します。
			@~japanese	@details	指定されたサイズ・フォーマットに従ってバッファを作成します。
			@~japanese	@attention ここで生成されたバッファは、再度バッファを作成した際や IStImageBuffer インターフェースハンドルのRelease時に自動的に削除されます。
			@~japanese	@param[in] nWidth	画像の横サイズ
			@~japanese	@param[in] nHeight	画像の縦サイズ
			@~japanese	@param[in] nPixelFormat	画像のピクセルフォーマット
			@~japanese	@param[in] eInitializeMemory	バッファの初期化方法
			@~japanese	@exception	メモリー確保に失敗した場合や不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void CreateBuffer(size_t nWidth, size_t nHeight, EStPixelFormatNamingConvention_t nPixelFormat, EStMemoryInitialization_t eInitializeMemory = StMemoryInitialization_DoNothing) = 0;

		/*!
			@~english	@brief	Acquire IStImage interface pointer.
			@~english	@details	Acquire IStImage interface pointer.
			@~english	@return	IStImage interface pointer.
			@~english	@exception	Throw out a GenICam::GenericException if the memory for image data does not been properly allocated.
			@~japanese	@brief	IStImage インターフェースポインターを取得します。
			@~japanese	@details	IStImage インターフェースポインターを取得します。
			@~japanese	@return	IStImage インターフェースポインター
			@~japanese	@exception	画像データが存在しない場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual IStImage*	GetIStImage() = 0;

		/*!
			@~english	@brief	Copy image data.
			@~english	@details	Copy image data.
			@~english	@param[in] pIStImage	IStImage interface pointer of the source iamge to be copied.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or there is an invalid argument.
			@~japanese	@brief	画像データをコピーします。
			@~japanese	@details	画像データをコピーします。
			@~japanese	@param[in] pIStImage	コピーしたい画像データ用 IStImage インターフェースポインター
			@~japanese	@exception	メモリー確保に失敗した場合や不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void CopyImage(IStImage *pIStImage) = 0;
	};
	
	//---------------------------------------------------------------------
	// interface IStImageBufferReleasable
	//---------------------------------------------------------------------
	/*!
		@ingroup StApiTL_PublicInterface
		@interface IStImageBufferReleasable
		@~english	@brief	Interface for the Image Buffer Releasable module.
		@~english	@details	Interface for the Image Buffer Releasable module.
		@~english	@sa	CreateIStImageBuffer()
		@~japanese	@brief	解放可能な画像バッファ用インターフェース
		@~japanese	@details	解放可能な画像バッファ用インターフェース
		@~japanese	@sa	CreateIStImageBuffer()
	*/
	interface PUBLIC_INTERFACE IStImageBufferReleasable : public IStImageBuffer, public IStReleasable
	{

	};
	
	// ---------------------------------------------------------------------
	// typedef CIStImageBufferPtr
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiTL_PublicImpl
		@typedef CIStImageBufferPtr
		@~english	@brief	This class is for lifetime management of IStImageBufferReleasable.
		@~english	@details	This class is for lifetime management of IStImageBufferReleasable. The destructor of this class will automatically call IStImageBufferReleasable::Release().
		@~japanese	@brief	IStImageBufferReleasable インターフェースポインターの自動管理用クラスです。
		@~japanese	@details	IStImageBufferReleasable インターフェースポインターの自動管理用クラスです。このクラスのデストラクタから IStImageBufferReleasable::Release() が自動的に呼び出されます。
	*/
	typedef CStAutoPtr<IStImageBufferReleasable, IStImageBuffer> CIStImageBufferPtr;
}

#endif //ISTIMAGEBUFFER_H__
