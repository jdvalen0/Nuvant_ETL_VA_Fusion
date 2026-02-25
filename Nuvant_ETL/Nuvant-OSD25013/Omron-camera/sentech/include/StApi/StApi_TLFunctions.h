//------------------------------------------------------------------------------
// StApi
//------------------------------------------------------------------------------
/*!
	@ingroup	StApiTL_PublicImpl
	@file	StApi_TLFunctions.h
	@~english	@details	
	@~japanese	@details	
*/
#ifndef STAPI_TL_FUNCTIONS_H__
#define STAPI_TL_FUNCTIONS_H__

#ifdef _MSC_VER
#pragma warning(push)	
#pragma warning(disable : 4819)	
#include "StApi_PixelFormat.h"
#pragma warning(pop)	
#else
#include "StApi_PixelFormat.h"
#endif

#include "IStSystem.h"
#include "IStImageBuffer.h"
#include "IStFeatureBag.h"

namespace StApi
{
	//interface IStSystemReleasable;
	//interface IStImageBufferReleasable;
	//interface IStAllocator;
	//interface IStPixelFormatInfo;
	//interface IStPixelComponentInfo;
	//interface IStFeatureBagReleasable;

	//-------------------------------------------------------------------------
	// C Functions
	//-------------------------------------------------------------------------	
	/*!
		@ingroup	StApiTL_PublicImpl
		@~english	@brief	Initialize StApi.
		@~english	@details	Initialize StApi. This function must be called before using other StApi functions. 
		@~english	@attention	Call StApiTerminate() to release the resource of StApi when it is no longer needed. You can use CStApiAutoInit for automatically calling StApiInitialize() and StApiTerminate().
		@~english	@param[in]	nStApiVersion	StApi build time version.
		@~english	@exception	Throw out GenICam::GenericException when the major or minor version is differ from building.
		@~english	@sa	 StApiTerminate() , CStApiAutoInit
		@~japanese	@brief	StApiライブラリを初期化します。
		@~japanese	@details	StApiライブラリを初期化します。他のStApi関数を呼び出す前にこの関数を呼び出して、StApiライブラリを初期化してください。
		@~japanese	@attention	StApiライブラリが不要になったら StApiTerminate() を呼び出してリソースを解放してください。 CStApiAutoInit を使用することで、初期化および終了処理を自動化できます。
		@~japanese	@param[in]	nStApiVersion	ビルド時StApiバージョン
		@~japanese	@exception	StApiの実行時のメジャーバージョンまたはマイナーバージョンが、ビルド時の値と異なる場合は、例外 GenICam::GenericException が発生します。
		@~japanese	@sa	 StApiTerminate() , CStApiAutoInit
	*/
	ST_API_TL void ST_API_CALL_TYPE StApiInitialize(uint32_t nStApiVersion = STAPI_VERSION);

	/*!
		@ingroup	StApiTL_PublicImpl
		@~english	@brief	Uninitialize StApi.
		@~english	@details	Uninitialize StApi. Call this function to release resources and deinitialize the StApi. 
		@~english	@attention	If you called StApiInitialize() N times, you need to call this function N times as well.
		@~english	@exception	Throw out a GenICam::GenericException when StApi is not initialized.
		@~english	@sa	 StApiInitialize()
		@~japanese	@brief	StApiライブラリの終了処理を行います。
		@~japanese	@details	StApiライブラリの終了処理を行います。
		@~japanese	@attention	StApiInitialize() を複数回呼び出した場合は、同じ回数だけこの関数を呼び出してください。
		@~japanese	@exception	初期化されていない場合は、例外 GenICam::GenericException が発生します。
		@~japanese	@sa	 StApiInitialize()
	*/
	ST_API_TL void ST_API_CALL_TYPE StApiTerminate();
	
	/*!
		@ingroup	StApiTL_PublicImpl
		@~english	@brief	Acquire version of the running StApi.
		@~english	@details	Acquire version of the running StApi.
		@~english	@exception	Throw out a GenICam::GenericException when StApi is not initialized.
		@~english	@return	Version of the running StApi.
		@~english	@sa	 STAPI_VERSION_MAJOR
		@~japanese	@brief	実行中のStApiのバージョンを取得します。
		@~japanese	@details	StApiのバージョンを取得します。bit31-24:メジャーバージョン, bit23-16:マイナーバージョン, bit15-0:サブマイナーバージョン。
		@~japanese	@exception	初期化されていない場合は、例外 GenICam::GenericException が発生します。
		@~japanese	@return	StApi実行時バージョン
		@~japanese	@sa	 STAPI_VERSION_MAJOR
	*/
	ST_API_TL uint32_t ST_API_CALL_TYPE GetStApiVersion();
	
	/*!
		@ingroup	StApiTL_PublicImpl
		@~english	@brief	Acquire version of the running StApi.
		@~english	@details	Acquire version of the running StApi.
		@~english	@exception	Throw out a GenICam::GenericException when StApi is not initialized.
		@~english	@return	Version of the running StApi.
		@~english	@sa	 STAPI_VERSION_MAJOR
		@~japanese	@brief	実行中のStApiのバージョンを取得します。
		@~japanese	@details	StApiのバージョンを取得します。Major.Minor.SubMinor
		@~japanese	@exception	初期化されていない場合は、例外 GenICam::GenericException が発生します。
		@~japanese	@return	StApi実行時バージョン文字列
		@~japanese	@sa	 STAPI_VERSION_MAJOR
	*/
	ST_API_TL GenICam::gcstring ST_API_CALL_TYPE GetStApiVersionText();

	/*!
		@ingroup	StApiTL_PublicImpl
		@~english	@brief	Open the system module and interface module of GenTL then acquire IStSystemReleasable interface pointer.
		@~english	@details	Open the system module and interface module of GenTL then acquire IStSystemReleasable interface pointer. If the acquired IStSystemReleasable is no longer needed, call IStSystemReleasable::Release() to release it.
		@~english	@param[in] eStSystemVendor	GenTL module to use. The StApi functionality may differ depending on the GenTL module.
		@~english	@param[in] eInterfaceMask	The interface to use. For example: StInterfaceType_USB3Vision is used for USB3Vision camera. This will reduce the scanning time because only the specified interface is scanned for devices. Use logical OR to specify more than one interface.
		@~english	@return	IStSystemReleasable pointer.
		@~english	@exception	 Throw out a GenICam::GenericException when StApi is not initialized, memory allocation is failed, GenTL function is failed, or there are any invalid argument.
		@~english	@sa	 StApi::CIStSystemPtr
		@~japanese	@brief	GenTLのシステムモージュールをオープンし、 IStSystemReleasable インターフェースポインターを取得します。
		@~japanese	@details	GenTLのシステムモージュールをオープンし、 IStSystemReleasable インターフェースポインターを取得します。 IStSystemReleasable が不要になったら、 IStSystemReleasable::Release() を呼び出して解放してください。
		@~japanese	@param[in] eStSystemVendor	使用するGenTLモジュールを指定します。使用するGenTLモジュールにより、利用可能なStApi関数が変化することがあります。
		@~japanese	@param[in] eInterfaceMask	使用するインターフェースを指定します。USB3Visionカメラのみを使用する場合、 StInterfaceType_USB3Vision を指定することでGigEVisionカメラの検索のような不要な処理を軽減できます。複数のインターフェースを使用する場合は論理和を指定します。
		@~japanese	@return	IStSystemReleasable インターフェースポインター
		@~japanese	@exception	初期化されていない場合、メモリーの割り当てに失敗した場合またはGenTL関数がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		@~japanese	@sa	 StApi::CIStSystemPtr
	*/
	ST_API_TL StApi::IStSystemReleasable* ST_API_CALL_TYPE CreateIStSystem(StApi::EStSystemVendor_t eStSystemVendor = StSystemVendor_Default, StApi::EStInterfaceType_t eInterfaceMask = StInterfaceType_All);

	/*!
		@ingroup	StApiTL_PublicImpl
		@~english	@brief	Create object for keeping image data and acquire IStImageBufferReleasable.
		@~english	@details	Create object for keeping image data and acquire IStImageBufferReleasable. The acquired IStImageBufferReleasable interface pointer can be assign for storing the image after processing. Call IStImageBufferReleasable::Release() to release IStImageBuffer interface pointer if it is no longer necessary.
		@~english	@param[in] pIStAllocator	Interface pointer for allocating and releasing memory. If NULL, the buffer memory allocation and deallocation are handled inside the StApi.
		@~english	@return	IStImageBufferReleasable pointer.
		@~english	@exception	 Throw out a GenICam::GenericException when StApi is not initialized or memory allocation is failed.
		@~english	@sa	 IStAllocator
		@~japanese	@brief	画像データを保持するためのオブジェクトを生成し、 IStImageBufferReleasable インターフェースポインターを取得します。
		@~japanese	@details	画像データを保持するためのオブジェクトを生成し、 IStImageBufferReleasable インターフェースポインターを取得します。オブジェクトが不要になったら IStImageBufferReleasable::Release() を呼び出して解放してください。
		@~japanese	@param[in] pIStAllocator	IStAllocator インターフェースポインター。画像保持用メモリーの確保および解放をカスタマイズする際に指定します。NULLが指定された場合は、StApi内部でメモリーの割り当ておよび解放を行います。
		@~japanese	@return	IStImageBufferReleasable インターフェースポインター
		@~japanese	@exception	初期化されていない場合、メモリーの割り当てに失敗した場合は、例外 GenICam::GenericException が発生します。
		@~japanese	@sa	 IStAllocator
	*/
	ST_API_TL StApi::IStImageBufferReleasable* ST_API_CALL_TYPE CreateIStImageBuffer(StApi::IStAllocator *pIStAllocator = NULL);

	/*!
		@ingroup	StApiTL_PublicImpl
		@~english	@brief	Acquire IStPixelFormatInfo interface pointer. 
		@~english	@details	Acquire IStPixelFormatInfo interface pointer. IStPixelFormatInfo interface pointer is used for obtaining information related to the pixel format.
		@~english	@param[in] ePFNC	Pixel format.
		@~english	@return	IStPixelFormatInfo pointer.
		@~english	@exception	 Throw out a GenICam::GenericException when StApi is not initialized.
		@~japanese	@brief	IStPixelFormatInfo インターフェースを取得します。
		@~japanese	@details	IStPixelFormatInfo インターフェースを取得します。 IStPixelFormatInfo インターフェースはピクセルフォーマット関連情報の取得に使用されます。
		@~japanese	@param[in] ePFNC	ピクセルフォーマット値
		@~japanese	@return	IStPixelFormatInfo インターフェースポインター
		@~japanese	@exception	初期化されていない場合は、例外 GenICam::GenericException が発生します。
	*/
	ST_API_TL StApi::IStPixelFormatInfo* ST_API_CALL_TYPE GetIStPixelFormatInfo(StApi::EStPixelFormatNamingConvention_t ePFNC);

	/*!
		@ingroup	StApiTL_PublicImpl
		@~english	@brief	Acquire IStPixelComponentInfo. 
		@~english	@details	Acquire IStPixelComponentInfo. IStPixelComponentInfo is used for obtaining information related to the pixel component.
		@~english	@param[in] ePC	Pixel component.
		@~english	@return	IStPixelComponentInfo pointer.
		@~english	@exception	 Throw out a GenICam::GenericException when StApi is not initialized.
		@~japanese	@brief	IStPixelComponentInfo インターフェースを取得します。
		@~japanese	@details	IStPixelComponentInfo インターフェースを取得します。 IStPixelComponentInfo インターフェースはピクセル構成要素関連情報の取得に使用されます。
		@~japanese	@param[in] ePC	ピクセル構成要素値
		@~japanese	@return	IStPixelFormatInfo インターフェースポインター
		@~japanese	@exception	初期化されていない場合は、例外 GenICam::GenericException が発生します。
	*/
	ST_API_TL StApi::IStPixelComponentInfo* ST_API_CALL_TYPE GetIStPixelComponentInfo(StApi::EStPixelComponent_t ePC);

	/*!
		@ingroup	StApiTL_PublicImpl
		@~english	@brief	Acquire IStFeatureBagReleasable.
		@~english	@details	Acquire IStFeatureBagReleasable. IStFeatureBagReleasable is used for saving/loading setting of cameras to memory or file. Call IStPixelComponentInfo::Release() to release the object if it is no longer necessary.
		@~english	@return	IStFeatureBagReleasable pointer.
		@~english	@exception	 Throw out a GenICam::GenericException when StApi is not initialized or memory allocation is failed.
		@~japanese	@brief	IStFeatureBagReleasable インターフェースを取得します。
		@~japanese	@details	IStPixelComponentInfo インターフェースポインターを取得します。オブジェクトが不要になったら IStPixelComponentInfo::Release() を呼び出して解放してください。
		@~japanese	@return	IStFeatureBagReleasable インターフェースポインター
		@~japanese	@exception	初期化されていない場合、メモリーの割り当てに失敗した場合は、例外 GenICam::GenericException が発生します。
	*/
	ST_API_TL StApi::IStFeatureBagReleasable* ST_API_CALL_TYPE CreateIStFeatureBag();



	// ---------------------------------------------------------------------
	// class CStApiAutoInit
	// ---------------------------------------------------------------------
	/*!
		@ingroup	StApiTL_PublicImpl
		@~english	@brief	For automatically initialing or terminating process of the StApi library.
		@~english	@details	For automatically initialing or terminating process of the StApi library.
		@~japanese	@brief	StApiライブラリの初期化および終了処理を自動化するためのクラス
		@~japanese	@details	StApiライブラリの初期化および終了処理を自動化するためのクラス
	*/
	class CStApiAutoInit
	{
	public:
		/*!
			@~english	@brief	Call the initialization process ( StApiInitialize() ) in the constructor.
			@~english	@details	Call the initialization process ( StApiInitialize() ) in the constructor.
			@~english	@exception	Throw out a GenICam::GenericException if StApiInitialize() is failed.
			@~english	@sa	StApiInitialize()
			@~japanese	@brief	StApiInitialize() が呼び出されStApiライブラリが初期化されます。
			@~japanese	@details	StApiInitialize() が呼び出されStApiライブラリが初期化されます。
			@~japanese	@exception	StApiInitialize() が失敗した場合は、例外 GenICam::GenericException が発生します。
			@~japanese	@sa	StApiInitialize()
		*/
		CStApiAutoInit()
		{
			StApiInitialize();
		};

		/*!
			@~english	@brief	Call the termination process ( StApiTerminate() ) in the destructor.
			@~english	@details	Call the termination process ( StApiTerminate() ) in the destructor.
			@~english	@exception	None.
			@~english	@sa	StApiTerminate()
			@~japanese	@brief	StApiライブラリの終了処理 StApiTerminate() が呼び出されます。
			@~japanese	@details	StApiライブラリの終了処理 StApiTerminate() が呼び出されます。
			@~japanese	@exception	なし
			@~japanese	@sa	StApiTerminate()
		*/
		virtual ~CStApiAutoInit()
		{
			StApiTerminate();
		}
	private:
		// Copy is prohibited.
		CStApiAutoInit(CStApiAutoInit &rhs);

		// Reference is prohibited.
		CStApiAutoInit & operator= (CStApiAutoInit &rhs);

		// Prevent the creation of the heap area
		void* operator new(size_t nSize);
	};
}

#endif //STAPI_TL_FUNCTIONS_H__


