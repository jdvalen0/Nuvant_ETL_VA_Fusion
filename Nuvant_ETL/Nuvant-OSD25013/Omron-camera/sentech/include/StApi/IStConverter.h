//------------------------------------------------------------------------------
//  StApi
//------------------------------------------------------------------------------
/*!
	@ingroup	StApiIP_PublicInterface
	@file	
	@~english	@details	Definition of interface IStConverter
	@~japanese	@details	IStConverter インターフェースの定義
*/
#ifndef ISTCONVERTER_H
#define ISTCONVERTER_H

#include "StApi_TL.h"

#ifdef _MSC_VER
#pragma warning(push)	
#pragma warning(disable : 4819)	
#include "StApi_IPDef.h"
#pragma warning(pop)	
#else
#include "StApi_IPDef.h"
#endif

namespace StApi
{
	// ---------------------------------------------------------------------
	// interface IStConverterInfo
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiIP_PublicInterface
		@interface IStConverterInfo
		@~english	@brief	Interface for ConverterInfo.
		@~english	@details	Interface for ConverterInfo.
		@~japanese	@brief	コンバーター情報用インターフェース
		@~japanese	@details	コンバーター情報用インターフェース
	*/
	interface PUBLIC_INTERFACE IStConverterInfo
	{
		/*!
			@~english	@brief	Acquire the converter type.
			@~english	@details	Acquire the converter type.
			@~english	@return	Type of converter.
			@~english	@exception	None.
			@~japanese	@brief	変換タイプを取得します。
			@~japanese	@details	変換タイプを取得します。
			@~japanese	@return	変換タイプ
			@~japanese	@exception	なし
		*/
		virtual EStConverterType_t GetConverterType() const = 0;

		/*!
			@~english	@brief	Acquire converter name.
			@~english	@details	Acquire converter name.
			@~english	@return	Converter name.
			@~english	@exception	None.
			@~japanese	@brief	変換名を取得します。
			@~japanese	@details	変換名を取得します。
			@~japanese	@return	変換名
			@~japanese	@exception	なし
		*/
		virtual GenICam::gcstring GetConverterName() const = 0;

		/*!
			@~english	@brief	Check if the pixel format is supported.
			@~english	@details	Check if the pixel format is supported.
			@~english	@param[in] ePFNC	The pixel format.
			@~english	@return	True if supported.
			@~english	@exception	None.
			@~japanese	@brief	指定したピクセルフォーマットの変換に対応しているか確認します。
			@~japanese	@details	指定したピクセルフォーマットの変換に対応しているか確認します。
			@~japanese	@param[in] ePFNC	ピクセルフォーマット値
			@~japanese	@return	対応している場合、 true が返されます。
			@~japanese	@exception	なし
		*/
		virtual bool IsSupported(EStPixelFormatNamingConvention_t ePFNC) const = 0;
	};

	interface IStImage;

	// ---------------------------------------------------------------------
	// interface IStConverter
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiIP_PublicInterface
		@interface IStConverter
		@~english	@brief	Interface for Converter.
		@~english	@details	Interface for Converter.
		@sa	CreateIStConverter()
		@~japanese	@brief	コンバーター用インターフェース
		@~japanese	@details	コンバーター用インターフェース
		@sa	CreateIStConverter()
	*/
	interface PUBLIC_INTERFACE IStConverter : public IStRegisterCallback
	{
		/*!
			@~english	@brief	Acquire the interface pointer of IStConverterInfo.
			@~english	@details	Acquire the interface pointer of IStConverterInfo.
			@~english	@return	IStConverterInfo interface pointer.
			@~english	@exception	None.
			@~japanese	@brief	IStConverterInfo インターフェースポインターを取得します。
			@~japanese	@details	IStConverterInfo インターフェースポインターを取得します。
			@~japanese	@return	IStConverterInfo インターフェースポインター。
			@~japanese	@exception	なし
		*/
		virtual const IStConverterInfo *GetIStConverterInfo() const = 0;

		/*!
			@~english	@brief	Perform image conversion.
			@~english	@details	Perform image conversion.
			@~english	@param[in]	pSourceIStImage	Input image buffer.
			@~english	@param[in,out]	pDestIStImageBuffer	Output image buffer.
			@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument. 
			@~japanese	@brief	画像の変換処理を行います。
			@~japanese	@details	画像の変換処理を行います。
			@~japanese	@param[in]	pSourceIStImage	入力画像
			@~japanese	@param[in,out]	pDestIStImageBuffer	出力画像バッファー
			@~japanese	@exception	不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void Convert(IStImage *pSourceIStImage, IStImageBuffer *pDestIStImageBuffer) = 0;

		/*!
			@~english	@brief	Acquire interface pointer of INodeMap.
			@~english	@details	Acquire interface pointer of INodeMap.
			@~english	@return	INodeMap interface pointer.
			@~english	@exception	None.
			@~japanese	@brief	INodeMap インターフェースポインターを取得します。
			@~japanese	@details	INodeMap インターフェースポインターを取得します。
			@~japanese	@return	INodeMap インターフェースポインター。
			@~japanese	@exception	なし
		*/
		virtual GenApi::INodeMap *GetINodeMap() = 0;

		/*!
			@~english	@brief	Get the line pitch alignment value of the converted image.
			@~english	@details	Get the line pitch alignment value of the converted image.
			@~english	@return	Line pitch alignment value.
			@~english	@exception	None.
			@~japanese	@brief	変換後の画像のラインピッチの最小単位を取得します。
			@~japanese	@details	変換後の画像のラインピッチの最小単位を取得します。
			@~japanese	@return	変換後の画像のラインピッチの最小単位
			@~japanese	@exception	なし
		*/
		virtual size_t GetLinePitchAlignment() const = 0;

		/*!
			@~english	@brief	Set the line pitch alignment value of the converted image.
			@~english	@details	Set the line pitch alignment value of the converted image.
			@~english	@param[in]	nLinePitchAlignment	Line pitch alignment value.
			@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument. 
			@~japanese	@brief	変換後の画像のラインピッチの最小単位を設定します。
			@~japanese	@details	変換後の画像のラインピッチの最小単位を設定します。
			@~japanese	@param[in]	nLinePitchAlignment	変換後の画像のラインピッチの最小単位
			@~japanese	@exception	不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void SetLinePitchAlignment(size_t nLinePitchAlignment) = 0;
	};

	// ---------------------------------------------------------------------
	// interface IStConverterReleasable
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiIP_PublicInterface
		@interface IStConverterReleasable
		@~english	@brief	Interface for Converter(Releasable).
		@~english	@details	Interface for Converter(Releasable).
		@sa	CreateIStConverter()
		@~japanese	@brief	解放可能なコンバーター用インターフェース
		@~japanese	@details	解放可能なコンバーター用インターフェース
		@sa	CreateIStConverter()
	*/
	interface PUBLIC_INTERFACE IStConverterReleasable : public IStConverter, public IStReleasable
	{

	};

	//---------------------------------------------------------------------
	// typedef CIStConverterPtr
	//---------------------------------------------------------------------
	/*!
		@ingroup StApiIP_PublicImpl
		@typedef CIStConverterPtr
		@~english	@brief	The auto management class of IStConverter class for image conversion.
		@~english	@details	The auto management class of IStConverter class for image conversion. Use this class instead of managing the initial/release of IStConverter class yourself. The destructor of this class will automatically call IStConverterReleasable::Release().
		@sa	CreateIStConverter()
		@~japanese	@brief	IStConverterReleasable インターフェースポインターの自動管理用クラスです。
		@~japanese	@details	IStConverterReleasable インターフェースポインターの自動管理用クラスです。このクラスのデストラクタから IStConverterReleasable::Release() が自動的に呼び出されます。
		@sa	CreateIStConverter()
	*/
	typedef CStAutoPtr<IStConverterReleasable, IStConverter> CIStConverterPtr;
}
#endif //ISTCONVERTER_H



