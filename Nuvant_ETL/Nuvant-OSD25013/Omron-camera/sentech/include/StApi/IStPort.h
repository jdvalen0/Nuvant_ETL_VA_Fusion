//------------------------------------------------------------------------------
// StApi
//------------------------------------------------------------------------------
/*!
	@ingroup	StApiTL_PublicInterface
	@file
	@~english	@details	Definition of interfaces IStPortInfo and IStPort
	@~japanese	@details	IStPortURLInfo, IStPortInfo,  IStPortインターフェースの定義
*/
#ifndef ISTPORT_H__
#define ISTPORT_H__

#include "StApi_Platform.h"

namespace StApi
{
	//---------------------------------------------------------------------
	// interface IStPortURLInfo
	//---------------------------------------------------------------------
	/*!
		@ingroup StApiTL_PublicInterface
		@interface IStPortURLInfo
		@~english	@brief	Interface  for accessing Port URL information.
		@~english	@details	Interface  for accessing Port URL information.
		@~japanese	@brief	ポートURL情報用インターフェース
		@~japanese	@details	ポートURL情報用インターフェース
	*/
	interface PUBLIC_INTERFACE IStPortURLInfo
	{
		/*!
			@~english	@brief	GenTL::GCGetPortURLInfo() is used to acquire data of GenTL::URL_INFO_URL.
			@~english	@details	GenTL::GCGetPortURLInfo() is used to acquire data of GenTL::URL_INFO_URL.
			@~english	@return	URL_INFO_URL data.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or GenTL::GCGetPortURLInfo() is failed.
			@~japanese	@brief	GenTL::GCGetPortURLInfo() を使用して GenTL::URL_INFO_URL の情報を取得します。
			@~japanese	@details	GenTL::GCGetPortURLInfo() を使用して GenTL::URL_INFO_URL の情報を取得します。
			@~japanese	@return	URL_INFO_URL データ
			@~japanese	@exception	メモリー確保に失敗した場合や GenTL::GCGetPortURLInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual GenICam::gcstring GetURL() const = 0;

		/*!
			@~english	@brief	GenTL::GCGetPortURLInfo() is used to acquire data of GenTL::URL_INFO_SCHEMA_VER_MAJOR.
			@~english	@details	GenTL::GCGetPortURLInfo() is used to acquire data of GenTL::URL_INFO_SCHEMA_VER_MAJOR.
			@~english	@return	URL_INFO_SCHEMA_VER_MAJOR data.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or GenTL::GCGetPortURLInfo() is failed.
			@~japanese	@brief	GenTL::GCGetPortURLInfo() を使用して GenTL::URL_INFO_SCHEMA_VER_MAJOR の情報を取得します。
			@~japanese	@details	GenTL::GCGetPortURLInfo() を使用して GenTL::URL_INFO_SCHEMA_VER_MAJOR の情報を取得します。
			@~japanese	@return	URL_INFO_SCHEMA_VER_MAJOR データ
			@~japanese	@exception	GenTL::GCGetPortURLInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual int32_t GetSchemaVerMajor() const = 0;

		/*!
			@~english	@brief	GenTL::GCGetPortURLInfo() is used to acquire data of GenTL::URL_INFO_SCHEMA_VER_MINOR.
			@~english	@details	GenTL::GCGetPortURLInfo() is used to acquire data of GenTL::URL_INFO_SCHEMA_VER_MINOR.
			@~english	@return	URL_INFO_SCHEMA_VER_MINOR data.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or GenTL::GCGetPortURLInfo() is failed.
			@~japanese	@brief	GenTL::GCGetPortURLInfo() を使用して GenTL::URL_INFO_SCHEMA_VER_MINOR の情報を取得します。
			@~japanese	@details	GenTL::GCGetPortURLInfo() を使用して GenTL::URL_INFO_SCHEMA_VER_MINOR の情報を取得します。
			@~japanese	@return	URL_INFO_SCHEMA_VER_MINOR データ
			@~japanese	@exception	GenTL::GCGetPortURLInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual int32_t GetSchemaVerMinor() const = 0;

		/*!
			@~english	@brief	GenTL::GCGetPortURLInfo() is used to acquire data of GenTL::URL_INFO_FILE_VER_MAJOR.
			@~english	@details	GenTL::GCGetPortURLInfo() is used to acquire data of GenTL::URL_INFO_FILE_VER_MAJOR.
			@~english	@return	URL_INFO_FILE_VER_MAJOR data.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or GenTL::GCGetPortURLInfo() is failed.
			@~japanese	@brief	GenTL::GCGetPortURLInfo() を使用して GenTL::URL_INFO_FILE_VER_MAJOR の情報を取得します。
			@~japanese	@details	GenTL::GCGetPortURLInfo() を使用して GenTL::URL_INFO_FILE_VER_MAJOR の情報を取得します。
			@~japanese	@return	URL_INFO_FILE_VER_MAJOR データ
			@~japanese	@exception	GenTL::GCGetPortURLInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual int32_t GetFileVerMajor() const = 0;

		/*!
			@~english	@brief	GenTL::GCGetPortURLInfo() is used to acquire data of GenTL::URL_INFO_FILE_VER_MINOR.
			@~english	@details	GenTL::GCGetPortURLInfo() is used to acquire data of GenTL::URL_INFO_FILE_VER_MINOR.
			@~english	@return	URL_INFO_FILE_VER_MINOR data.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or GenTL::GCGetPortURLInfo() is failed.
			@~japanese	@brief	GenTL::GCGetPortURLInfo() を使用して GenTL::URL_INFO_FILE_VER_MINOR の情報を取得します。
			@~japanese	@details	GenTL::GCGetPortURLInfo() を使用して GenTL::URL_INFO_FILE_VER_MINOR の情報を取得します。
			@~japanese	@return	URL_INFO_FILE_VER_MINOR データ
			@~japanese	@exception	GenTL::GCGetPortURLInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual int32_t GetFileVerMinor() const = 0;

		/*!
			@~english	@brief	GenTL::GCGetPortURLInfo() is used to acquire data of GenTL::URL_INFO_FILE_VER_SUBMINOR.
			@~english	@details	GenTL::GCGetPortURLInfo() is used to acquire data of GenTL::URL_INFO_FILE_VER_SUBMINOR.
			@~english	@return	URL_INFO_FILE_VER_SUBMINOR data.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or GenTL::GCGetPortURLInfo() is failed.
			@~japanese	@brief	GenTL::GCGetPortURLInfo() を使用して GenTL::URL_INFO_FILE_VER_SUBMINOR の情報を取得します。
			@~japanese	@details	GenTL::GCGetPortURLInfo() を使用して GenTL::URL_INFO_FILE_VER_SUBMINOR の情報を取得します。
			@~japanese	@return	URL_INFO_FILE_VER_SUBMINOR データ
			@~japanese	@exception	GenTL::GCGetPortURLInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual int32_t GetFileVerSubMinor() const = 0;

		/*!
			@~english	@brief	GenTL::GCGetPortURLInfo() is used to acquire data of GenTL::URL_INFO_FILE_SHA1_HASH.
			@~english	@details	GenTL::GCGetPortURLInfo() is used to acquire data of GenTL::URL_INFO_FILE_SHA1_HASH.
			@~english	@param[out]	pBuffer	Set a pointer of buffer to receive data.
			@~english	@param[in,out]	pnSize	Set the size of buffer and get the size of data.
			@~english	@return	URL_INFO_FILE_SHA1_HASH data.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or GenTL::GCGetPortURLInfo() is failed.
			@~japanese	@brief	GenTL::GCGetPortURLInfo() を使用して GenTL::URL_INFO_FILE_SHA1_HASH の情報を取得します。
			@~japanese	@details	GenTL::GCGetPortURLInfo() を使用して GenTL::URL_INFO_FILE_SHA1_HASH の情報を取得します。
			@~japanese	@param[out]	pBuffer	データを受け取るバッファを指定します。
			@~japanese	@param[in,out]	pnSize	バッファがNULL以外の時は指定するバッファのサイズを渡し、データのサイズを受け取ります。
			@~japanese	@return	URL_INFO_FILE_SHA1_HASH データ
			@~japanese	@exception	GenTL::GCGetPortURLInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void GetSha1HashBuffer(void *pBuffer, size_t *pnSize) const = 0;

		/*!
			@~english	@brief	GenTL::GCGetPortURLInfo() is used to acquire data of GenTL::URL_INFO_FILE_REGISTER_ADDRESS.
			@~english	@details	GenTL::GCGetPortURLInfo() is used to acquire data of GenTL::URL_INFO_FILE_REGISTER_ADDRESS.
			@~english	@return	URL_INFO_FILE_REGISTER_ADDRESS data.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or GenTL::GCGetPortURLInfo() is failed.
			@~japanese	@brief	GenTL::GCGetPortURLInfo() を使用して GenTL::URL_INFO_FILE_REGISTER_ADDRESS の情報を取得します。
			@~japanese	@details	GenTL::GCGetPortURLInfo() を使用して GenTL::URL_INFO_FILE_REGISTER_ADDRESS の情報を取得します。
			@~japanese	@return	URL_INFO_FILE_REGISTER_ADDRESS データ
			@~japanese	@exception	GenTL::GCGetPortURLInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual uint64_t GetFileRegisterAddress() const = 0;

		/*!
			@~english	@brief	GenTL::GCGetPortURLInfo() is used to acquire data of GenTL::URL_INFO_FILE_SIZE.
			@~english	@details	GenTL::GCGetPortURLInfo() is used to acquire data of GenTL::URL_INFO_FILE_SIZE.
			@~english	@return	URL_INFO_FILE_SIZE data.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or GenTL::GCGetPortURLInfo() is failed.
			@~japanese	@brief	GenTL::GCGetPortURLInfo() を使用して GenTL::URL_INFO_FILE_SIZE の情報を取得します。
			@~japanese	@details	GenTL::GCGetPortURLInfo() を使用して GenTL::URL_INFO_FILE_SIZE の情報を取得します。
			@~japanese	@return	URL_INFO_FILE_SIZE データ
			@~japanese	@exception	GenTL::GCGetPortURLInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual uint64_t GetFileSize() const = 0;

		/*!
			@~english	@brief	GenTL::GCGetPortURLInfo() is used to acquire data of GenTL::URL_INFO_SCHEME.
			@~english	@details	GenTL::GCGetPortURLInfo() is used to acquire data of GenTL::URL_INFO_SCHEME.
			@~english	@return	URL_INFO_SCHEME data.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or GenTL::GCGetPortURLInfo() is failed.
			@~japanese	@brief	GenTL::GCGetPortURLInfo() を使用して GenTL::URL_INFO_SCHEME の情報を取得します。
			@~japanese	@details	GenTL::GCGetPortURLInfo() を使用して GenTL::URL_INFO_SCHEME の情報を取得します。
			@~japanese	@return	URL_INFO_SCHEME データ
			@~japanese	@exception	GenTL::GCGetPortURLInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual int32_t GetScheme() const = 0;

		/*!
			@~english	@brief	GenTL::GCGetPortURLInfo() is used to acquire data of GenTL::URL_INFO_FILENAME.
			@~english	@details	GenTL::GCGetPortURLInfo() is used to acquire data of GenTL::URL_INFO_FILENAME.
			@~english	@return	URL_INFO_FILENAME data.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or GenTL::GCGetPortURLInfo() is failed.
			@~japanese	@brief	GenTL::GCGetPortURLInfo() を使用して GenTL::URL_INFO_FILENAME の情報を取得します。
			@~japanese	@details	GenTL::GCGetPortURLInfo() を使用して GenTL::URL_INFO_FILENAME の情報を取得します。
			@~japanese	@return	URL_INFO_FILENAME データ
			@~japanese	@exception	メモリー確保に失敗した場合や GenTL::GCGetPortURLInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual GenICam::gcstring GetFileName() const = 0;
	};

	//---------------------------------------------------------------------
	// interface IStPortInfo
	//---------------------------------------------------------------------
	/*!
		@ingroup StApiTL_PublicInterface
		@interface IStPortInfo
		@~english	@brief	Interface  for information about the Port.
		@~english	@details	Interface  for information about the Port.
		@~japanese	@brief	ポート情報用インターフェース
		@~japanese	@details	ポート情報用インターフェース
	*/
	interface PUBLIC_INTERFACE IStPortInfo
	{
		/*!
			@~english	@brief	Use GenTL::GCGetPortInfo() to acquire data of GenTL::PORT_INFO_ID.
			@~english	@details	Use GenTL::GCGetPortInfo() to acquire data of GenTL::PORT_INFO_ID.
			@~english	@return	PORT_INFO_ID data.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or GenTL::GCGetPortInfo() is failed.
			@~japanese	@brief	GenTL::GCGetPortInfo() を使用して GenTL::PORT_INFO_ID の情報を取得します。
			@~japanese	@details	GenTL::GCGetPortInfo() を使用して GenTL::PORT_INFO_ID の情報を取得します。
			@~japanese	@return	PORT_INFO_ID データ
			@~japanese	@exception	メモリー確保に失敗した場合や GenTL::GCGetPortInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual GenICam::gcstring GetID() const = 0;

		/*!
			@~english	@brief	Use GenTL::GCGetPortInfo() to acquire data of GenTL::PORT_INFO_VENDOR.
			@~english	@details	Use GenTL::GCGetPortInfo() to acquire data of GenTL::PORT_INFO_VENDOR.
			@~english	@return	PORT_INFO_VENDOR data.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or GenTL::GCGetPortInfo() is failed.
			@~japanese	@brief	GenTL::GCGetPortInfo() を使用して GenTL::PORT_INFO_VENDOR の情報を取得します。
			@~japanese	@details	GenTL::GCGetPortInfo() を使用して GenTL::PORT_INFO_VENDOR の情報を取得します。
			@~japanese	@return	PORT_INFO_VENDOR データ
			@~japanese	@exception	メモリー確保に失敗した場合や GenTL::GCGetPortInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual GenICam::gcstring GetVendor() const = 0;

		/*!
			@~english	@brief	Use GenTL::GCGetPortInfo() to acquire data of GenTL::PORT_INFO_MODEL.
			@~english	@details	Use GenTL::GCGetPortInfo() to acquire data of GenTL::PORT_INFO_MODEL.
			@~english	@return	PORT_INFO_MODEL data.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or GenTL::GCGetPortInfo() is failed.
			@~japanese	@brief	GenTL::GCGetPortInfo() を使用して GenTL::PORT_INFO_MODEL の情報を取得します。
			@~japanese	@details	GenTL::GCGetPortInfo() を使用して GenTL::PORT_INFO_MODEL の情報を取得します。
			@~japanese	@return	PORT_INFO_MODEL データ
			@~japanese	@exception	メモリー確保に失敗した場合や GenTL::GCGetPortInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual GenICam::gcstring GetModel() const = 0;

		/*!
			@~english	@brief	Use GenTL::GCGetPortInfo() to acquire data of GenTL::PORT_INFO_TLTYPE.
			@~english	@details	Use GenTL::GCGetPortInfo() to acquire data of GenTL::PORT_INFO_TLTYPE.
			@~english	@return	PORT_INFO_TLTYPE data.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or GenTL::GCGetPortInfo() is failed.
			@~japanese	@brief	GenTL::GCGetPortInfo() を使用して GenTL::PORT_INFO_TLTYPE の情報を取得します。
			@~japanese	@details	GenTL::GCGetPortInfo() を使用して GenTL::PORT_INFO_TLTYPE の情報を取得します。
			@~japanese	@return	PORT_INFO_TLTYPE データ
			@~japanese	@exception	メモリー確保に失敗した場合や GenTL::GCGetPortInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual GenICam::gcstring GetTLType() const = 0;

		/*!
			@~english	@brief	Use GenTL::GCGetPortInfo() to acquire data of GenTL::PORT_INFO_MODULE.
			@~english	@details	Use GenTL::GCGetPortInfo() to acquire data of GenTL::PORT_INFO_MODULE.
			@~english	@return	PORT_INFO_MODULE data.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or GenTL::GCGetPortInfo() is failed.
			@~japanese	@brief	GenTL::GCGetPortInfo() を使用して GenTL::PORT_INFO_MODULE の情報を取得します。
			@~japanese	@details	GenTL::GCGetPortInfo() を使用して GenTL::PORT_INFO_MODULE の情報を取得します。
			@~japanese	@return	PORT_INFO_MODULE データ
			@~japanese	@exception	メモリー確保に失敗した場合や GenTL::GCGetPortInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual GenICam::gcstring GetModule() const = 0;

		/*!
			@~english	@brief	Use GenTL::GCGetPortInfo() to acquire data of GenTL::PORT_INFO_LITTLE_ENDIAN.
			@~english	@details	Use GenTL::GCGetPortInfo() to acquire data of GenTL::PORT_INFO_LITTLE_ENDIAN.
			@~english	@return	PORT_INFO_LITTLE_ENDIAN data.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or GenTL::GCGetPortInfo() is failed.
			@~japanese	@brief	GenTL::GCGetPortInfo() を使用して GenTL::PORT_INFO_LITTLE_ENDIAN の情報を取得します。
			@~japanese	@details	GenTL::GCGetPortInfo() を使用して GenTL::PORT_INFO_LITTLE_ENDIAN の情報を取得します。
			@~japanese	@return	PORT_INFO_LITTLE_ENDIAN データ
			@~japanese	@exception	GenTL::GCGetPortInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual bool8_t IsLittleEndian() const = 0;

		/*!
			@~english	@brief	Use GenTL::GCGetPortInfo() to acquire data of GenTL::PORT_INFO_BIG_ENDIAN.
			@~english	@details	Use GenTL::GCGetPortInfo() to acquire data of GenTL::PORT_INFO_BIG_ENDIAN.
			@~english	@return	PORT_INFO_BIG_ENDIAN data.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or GenTL::GCGetPortInfo() is failed.
			@~japanese	@brief	GenTL::GCGetPortInfo() を使用して GenTL::PORT_INFO_BIG_ENDIAN の情報を取得します。
			@~japanese	@details	GenTL::GCGetPortInfo() を使用して GenTL::PORT_INFO_BIG_ENDIAN の情報を取得します。
			@~japanese	@return	PORT_INFO_BIG_ENDIAN データ
			@~japanese	@exception	GenTL::GCGetPortInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual bool8_t IsBigEndian() const = 0;

		/*!
			@~english	@brief	Use GenTL::GCGetPortInfo() to acquire data of GenTL::PORT_INFO_ACCESS_READ.
			@~english	@details	Use GenTL::GCGetPortInfo() to acquire data of GenTL::PORT_INFO_ACCESS_READ.
			@~english	@return	PORT_INFO_ACCESS_READ data.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or GenTL::GCGetPortInfo() is failed.
			@~japanese	@brief	GenTL::GCGetPortInfo() を使用して GenTL::PORT_INFO_ACCESS_READ の情報を取得します。
			@~japanese	@details	GenTL::GCGetPortInfo() を使用して GenTL::PORT_INFO_ACCESS_READ の情報を取得します。
			@~japanese	@return	PORT_INFO_ACCESS_READ データ
			@~japanese	@exception	GenTL::GCGetPortInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual bool8_t IsAccessRead() const = 0;

		/*!
			@~english	@brief	Use GenTL::GCGetPortInfo() to acquire data of GenTL::PORT_INFO_ACCESS_WRITE.
			@~english	@details	Use GenTL::GCGetPortInfo() to acquire data of GenTL::PORT_INFO_ACCESS_WRITE.
			@~english	@return	PORT_INFO_ACCESS_WRITE data.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or GenTL::GCGetPortInfo() is failed.
			@~japanese	@brief	GenTL::GCGetPortInfo() を使用して GenTL::PORT_INFO_ACCESS_WRITE の情報を取得します。
			@~japanese	@details	GenTL::GCGetPortInfo() を使用して GenTL::PORT_INFO_ACCESS_WRITE の情報を取得します。
			@~japanese	@return	PORT_INFO_ACCESS_WRITE データ
			@~japanese	@exception	GenTL::GCGetPortInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual bool8_t IsAccessWrite() const = 0;

		/*!
			@~english	@brief	Use GenTL::GCGetPortInfo() to acquire data of GenTL::PORT_INFO_ACCESS_NA.
			@~english	@details	Use GenTL::GCGetPortInfo() to acquire data of GenTL::PORT_INFO_ACCESS_NA.
			@~english	@return	PORT_INFO_ACCESS_NA data.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or GenTL::GCGetPortInfo() is failed.
			@~japanese	@brief	GenTL::GCGetPortInfo() を使用して GenTL::PORT_INFO_ACCESS_NA の情報を取得します。
			@~japanese	@details	GenTL::GCGetPortInfo() を使用して GenTL::PORT_INFO_ACCESS_NA の情報を取得します。
			@~japanese	@return	PORT_INFO_ACCESS_NA データ
			@~japanese	@exception	GenTL::GCGetPortInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual bool8_t IsAccessNA() const = 0;

		/*!
			@~english	@brief	Use GenTL::GCGetPortInfo() to acquire data of GenTL::PORT_INFO_ACCESS_NI.
			@~english	@details	Use GenTL::GCGetPortInfo() to acquire data of GenTL::PORT_INFO_ACCESS_NI.
			@~english	@return	PORT_INFO_ACCESS_NI data.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or GenTL::GCGetPortInfo() is failed.
			@~japanese	@brief	GenTL::GCGetPortInfo() を使用して GenTL::PORT_INFO_ACCESS_NI の情報を取得します。
			@~japanese	@details	GenTL::GCGetPortInfo() を使用して GenTL::PORT_INFO_ACCESS_NI の情報を取得します。
			@~japanese	@return	PORT_INFO_ACCESS_NI データ
			@~japanese	@exception	GenTL::GCGetPortInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual bool8_t IsAccessNI() const = 0;

		/*!
			@~english	@brief	Use GenTL::GCGetPortInfo() to acquire data of GenTL::PORT_INFO_VERSION.
			@~english	@details	Use GenTL::GCGetPortInfo() to acquire data of GenTL::PORT_INFO_VERSION.
			@~english	@return	PORT_INFO_VERSION data.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or GenTL::GCGetPortInfo() is failed.
			@~japanese	@brief	GenTL::GCGetPortInfo() を使用して GenTL::PORT_INFO_VERSION の情報を取得します。
			@~japanese	@details	GenTL::GCGetPortInfo() を使用して GenTL::PORT_INFO_VERSION の情報を取得します。
			@~japanese	@return	PORT_INFO_VERSION データ
			@~japanese	@exception	メモリー確保に失敗した場合や GenTL::GCGetPortInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual GenICam::gcstring GetVersion() const = 0;

		/*!
			@~english	@brief	Use GenTL::GCGetPortInfo() to acquire data of GenTL::PORT_INFO_PORTNAME.
			@~english	@details	Use GenTL::GCGetPortInfo() to acquire data of GenTL::PORT_INFO_PORTNAME.
			@~english	@return	PORT_INFO_PORTNAME data.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or GenTL::GCGetPortInfo() is failed.
			@~japanese	@brief	GenTL::GCGetPortInfo() を使用して GenTL::PORT_INFO_PORTNAME の情報を取得します。
			@~japanese	@details	GenTL::GCGetPortInfo() を使用して GenTL::PORT_INFO_PORTNAME の情報を取得します。
			@~japanese	@return	PORT_INFO_PORTNAME データ
			@~japanese	@exception	メモリー確保に失敗した場合や GenTL::GCGetPortInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual GenICam::gcstring GetPortName() const = 0;
	};

	//---------------------------------------------------------------------
	// interface IStPort
	//---------------------------------------------------------------------
	/*!
		@ingroup StApiTL_PublicInterface
		@interface IStPort
		@~english	@brief	Interface for Port.
		@~english	@details	Interface for Port.
		@~japanese	@brief	ポート用インターフェース
		@~japanese	@details	ポート用インターフェース
	*/
	interface PUBLIC_INTERFACE IStPort
	{
		/*!
			@~english	@brief	Acquire the number of available URLs of this port.
			@~english	@details	Acquire the number of available URLs of this port.
			@~english	@return	Number of avaliable URLs of this port.
			@~english	@exception	Throw out a GenICam::GenericException if there is an error when calling GenTL Api.
			@~japanese	@brief	このポートの利用可能なURLの数を取得します。
			@~japanese	@details	このポートの利用可能なURLの数を取得します。
			@~japanese	@return	このポートの利用可能なURLの数
			@~japanese	@exception	GenTL 関数がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual uint32_t GetPortURLCount() const = 0;

		/*!
			@~english	@brief	Acquire the index of the Port URL.
			@~english	@details	Acquire the index of the Port URL.
			@~english	@return	Index of the Port URL.
			@~english	@exception	None.
			@~japanese	@brief	ポートURLインディックスの設定値を取得します。
			@~japanese	@details	ポートURLインディックスの設定値を取得します。
			@~japanese	@return	ポートURLインディックス
			@~japanese	@exception	なし
		*/
		virtual uint32_t GetPortURLIndex() const = 0;

		/*!
			@~english	@brief	Set the index of the Port URL.
			@~english	@details	Set the index of the Port URL.
			@~english	@param[in] nIndex	Index of the Port URL.
			@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument. 
			@~japanese	@brief	ポートURLインディックスの値を設定します。
			@~japanese	@details	ポートURLインディックスの値を設定します。
			@~japanese	@param[in] nIndex	ポートURLインディックス
			@~japanese	@exception	不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void SetPortURLIndex(uint32_t nIndex) = 0;

		/*!
			@~english	@brief	Acquire IStPortURLInfo interface pointer of the Port URL.
			@~english	@details	Acquire IStPortURLInfo interface pointer of the Port URL.
			@~english	@return	IStPortURLInfo interface pointer.
			@~english	@exception	None.
			@~japanese	@brief	IStPortURLInfo インターフェースポインターを取得します。
			@~japanese	@details	IStPortURLInfo インターフェースポインターを取得します。
			@~japanese	@return	IStPortURLInfo インターフェースポインター
			@~japanese	@exception	なし
		*/
		virtual const IStPortURLInfo *GetIStPortURLInfo() const = 0;

		/*!
			@~english	@brief	Acquire INodeMap interface pointer of this port.
			@~english	@details	Acquire INodeMap interface pointer of this port.
			@~english	@return	INodeMap interface pointer.
			@~english	@exception	Throw out a GenICam::GenericException if a memory allocation is failed or GenTL function is failed.
			@~japanese	@brief	INodeMap インターフェースポインターを取得します。
			@~japanese	@details	INodeMap インターフェースポインターを取得します。
			@~japanese	@return	INodeMap インターフェースポインター
			@~japanese	@exception	メモリー確保に失敗した場合や GenTL 関数がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual GenApi::INodeMap *GetINodeMap() = 0;

		/*!
			@~english	@brief	Acquire IStPortInfo interface pointer of this port.
			@~english	@details	Acquire IStPortInfo interface pointer of this port.
			@~english	@return	IStPortInfo interface pointer.
			@~english	@exception	None.
			@~japanese	@brief	IStPortInfo インターフェースポインターを取得します。
			@~japanese	@details	IStPortInfo インターフェースポインターを取得します。
			@~japanese	@return	IStPortInfo インターフェースポインター
			@~japanese	@exception	なし
		*/
		virtual const IStPortInfo *GetIStPortInfo() const = 0;

		/*!
			@~english	@brief	Acquire the XML file name.
			@~english	@details	Acquire the XML file name.
			@~english	@return	XML file name.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or GenTL function is failed.
			@~japanese	@brief	XMLファイルのファイル名を取得します。
			@~japanese	@details	XMLファイルのファイル名を取得します。
			@~japanese	@return	XMLファイルのファイル名
			@~japanese	@exception	メモリー確保に失敗した場合や GenTL 関数がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual GenICam::gcstring GetXMLFileName() = 0;

		/*!
			@~english	@brief	Save the Port XML data a file.
			@~english	@details	Save the Port XML data to a file.
			@~english	@param[in] strFileName	File name.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or GenTL function is failed.
			@~japanese	@brief	このポートで使用されているXMLファイルを保存します。
			@~japanese	@details	このポートで使用されているXMLファイルを保存します。
			@~japanese	@param[in] strFileName	ファイル名
			@~japanese	@exception	メモリー確保に失敗した場合や GenTL 関数がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void SaveXMLFile(const GenICam::gcstring &strFileName) = 0;
	};
}
#endif //ISTPORT_H__

