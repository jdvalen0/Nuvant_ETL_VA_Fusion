//------------------------------------------------------------------------------
// StApi
//------------------------------------------------------------------------------
/*!
	@ingroup	StApiIP_PublicInterface
	@file
	@~english	@details	Definition of interface IStReverseConverter
	@~japanese	@details	IStReverseConverter インターフェースの定義
*/
#ifndef ISTREVERSECONVERTER_H
#define ISTREVERSECONVERTER_H

#include "IStConverter.h"

namespace StApi
{
	interface IStImage;

	// ---------------------------------------------------------------------
	// interface IStReverseConverter
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiIP_PublicInterface
		@interface IStReverseConverter
		@~english	@brief	Interface for Reverse Converter.
		@~english	@details	Interface for Reverse Converter.
		@sa	CreateIStConverter()
		@~japanese	@brief	反転回転コンバーター用インターフェース
		@~japanese	@details	反転回転コンバーター用インターフェース
		@sa	CreateIStConverter()
	*/
	interface PUBLIC_INTERFACE IStReverseConverter : public IStConverter
	{
		/*!
			@~english	@brief	Get the current setting of horizontal image mirroring.
			@~english	@details	Get the current setting of horizontal image mirroring.
			@~english	@return	True if the current setting is enabled.
			@~english	@exception	None.
			@~japanese	@brief	左右反転設定を取得します。
			@~japanese	@details	左右反転設定を取得します。
			@~japanese	@return	左右反転が有効な場合、 true を返します。
			@~japanese	@exception	なし
		*/
		virtual bool GetReverseX() const = 0;

		/*!
			@~english	@brief	Set horizontal image mirroring setting.
			@~english	@details	Set horizontal image mirroring setting.
			@~english	@param[in]	value	True to enable; false to disable.
			@~english	@exception	None.
			@~japanese	@brief	左右反転を設定します。
			@~japanese	@details	左右反転を設定します。
			@~japanese	@param[in]	value	左右反転を行う場合、 true を指定します。
			@~japanese	@exception	なし
		*/
		virtual void SetReverseX(bool value) = 0;

		/*!
			@~english	@brief	Get the current setting of vertical image mirroring.
			@~english	@details	Get the current setting of vertical image mirroring.
			@~english	@return	True if the current setting is enabled.
			@~english	@exception	None.
			@~japanese	@brief	上下反転設定を取得します。
			@~japanese	@details	上下反転設定を取得します。
			@~japanese	@return	上下反転が有効な場合、 true を返します。
			@~japanese	@exception	なし
		*/
		virtual bool GetReverseY() const = 0;

		/*!
			@~english	@brief	Set vertical image mirroring setting.
			@~english	@details	Set vertical image mirroring setting.
			@~english	@param[in]	value	True to enable; false to disable.
			@~english	@exception	None.
			@~japanese	@brief	上下反転を設定します。
			@~japanese	@details	上下反転を設定します。
			@~japanese	@param[in]	value	上下反転を行う場合、 true を指定します。
			@~japanese	@exception	なし
		*/
		virtual void SetReverseY(bool value) = 0;

		/*!
			@~english	@brief	Get current setting of image rotation.
			@~english	@details	Get current setting of image rotation.
			@~english	@return	Image rotation setting.
			@~english	@exception	None.
			@~japanese	@brief	回転モードを取得します。
			@~japanese	@details	回転モードを取得します。
			@~japanese	@return	回転モード
			@~japanese	@exception	なし
		*/
		virtual EStRotationMode_t GetRotationMode() const = 0;

		/*!
			@~english	@brief	Set current setting of image rotation.
			@~english	@details	Set current setting of image rotation.
			@~english	@param[in]	eRM	Image rotation setting.
			@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument. 
			@~japanese	@brief	回転モードを設定します。
			@~japanese	@details	回転モードを設定します。
			@~japanese	@param[in]	eRM	回転モード
			@~japanese	@exception	不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void SetRotationMode(EStRotationMode_t eRM) = 0;
	};


	//---------------------------------------------------------------------
	// typedef CIStReverseConverterPtr
	//---------------------------------------------------------------------
	/*!
		@ingroup StApiIP_PublicImpl
		@typedef CIStReverseConverterPtr
		@~english	@brief	 The auto management class of IStReverseConverter class for image reverse.
		@~english	@details	 The auto management class of IStReverseConverter class for image reverse. Use this class instead of managing the initial/release of IStReverseConverter class yourself. The destructor of this class will automatically call IStConverterReleasable::Release().
		@sa	CreateIStConverter()
		@~japanese	@brief	反転回転コンバーター用インターフェースインターフェースポインターの自動管理用クラスです。
		@~japanese	@details	反転回転コンバーター用インターフェースインターフェースポインターの自動管理用クラスです。このクラスのデストラクタから IStConverterReleasable::Release() が自動的に呼び出されます。
		@sa	CreateIStConverter()
	*/
	typedef CStAutoPtr<IStConverterReleasable, IStReverseConverter> CIStReverseConverterPtr;
}
#endif //ISTREVERSECONVERTER_H



