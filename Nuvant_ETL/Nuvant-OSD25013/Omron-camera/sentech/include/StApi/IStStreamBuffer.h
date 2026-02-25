//------------------------------------------------------------------------------
// StApi
//------------------------------------------------------------------------------
/*!
	@ingroup	StApiTL_PublicInterface
	@file
	@~english	@details	Definition of interface IStStreamBufferInfo and IStStreamBuffer.
	@~japanese	@details	IStStreamBufferInfo インターフェースおよび IStStreamBuffer インターフェースの定義
*/
#ifndef ISTSTREAMBUFFER_H__
#define ISTSTREAMBUFFER_H__

#include "CStAutoPtr.h"
#include "CStAutoPtrArray.h"
#include "IStReleasable.h"
#include "IStEventCtrl.h"
#include "IStImage.h"
#include "IStPort.h"

namespace StApi
{
	interface IStDataStream;

	// ---------------------------------------------------------------------
	// interface IStStreamBufferInfo
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiTL_PublicInterface
		@interface IStStreamBufferInfo
		@~english	@brief	Interface for accessing Data Stream Buffer module information.
		@~english	@details	Interface for accessing Data Stream Buffer module information.
		@~japanese	@brief	ストリームバッファ情報用インターフェース
		@~japanese	@details	ストリームバッファ情報用インターフェース
	*/
	interface PUBLIC_INTERFACE IStStreamBufferInfo
	{
		/*!
			@~english	@brief	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_BASE.
			@~english	@details	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_BASE.
			@~english	@return	BUFFER_INFO_BASE data.
			@~english	@exception	Throw out a GenICam::GenericException if GenTL::DSGetBufferInfo() is failed.
			@~japanese	@brief	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_BASE の情報を取得します。
			@~japanese	@details	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_BASE の情報を取得します。
			@~japanese	@return	BUFFER_INFO_BASE データ
			@~japanese	@exception	GenTL::DSGetBufferInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void*	GetBaseAddress() const = 0;

		/*!
			@~english	@brief	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_SIZE.
			@~english	@details	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_SIZE.
			@~english	@return	BUFFER_INFO_SIZE data.
			@~english	@exception	Throw out a GenICam::GenericException if GenTL::DSGetBufferInfo() is failed.
			@~japanese	@brief	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_SIZE の情報を取得します。
			@~japanese	@details	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_SIZE の情報を取得します。
			@~japanese	@return	BUFFER_INFO_SIZE データ
			@~japanese	@exception	GenTL::DSGetBufferInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual size_t	GetBufferSize() const = 0;

		/*!
			@~english	@brief	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_USER_PTR.
			@~english	@details	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_USER_PTR.
			@~english	@return	BUFFER_INFO_USER_PTR data.
			@~english	@exception	Throw out a GenICam::GenericException if GenTL::DSGetBufferInfo() is failed.
			@~japanese	@brief	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_USER_PTR の情報を取得します。
			@~japanese	@details	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_USER_PTR の情報を取得します。
			@~japanese	@return	BUFFER_INFO_USER_PTR データ
			@~japanese	@exception	GenTL::DSGetBufferInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void*	GetUserPtr() const = 0;

		/*!
			@~english	@brief	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_TIMESTAMP.
			@~english	@details	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_TIMESTAMP.
			@~english	@return	BUFFER_INFO_TIMESTAMP data.
			@~english	@exception	Throw out a GenICam::GenericException if GenTL::DSGetBufferInfo() is failed.
			@~japanese	@brief	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_TIMESTAMP の情報を取得します。
			@~japanese	@details	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_TIMESTAMP の情報を取得します。
			@~japanese	@return	BUFFER_INFO_TIMESTAMP データ
			@~japanese	@exception	GenTL::DSGetBufferInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual uint64_t	GetTimestamp() const = 0;

		/*!
			@~english	@brief	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_NEW_DATA.
			@~english	@details	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_NEW_DATA.
			@~english	@return	BUFFER_INFO_NEW_DATA data.
			@~english	@exception	Throw out a GenICam::GenericException if GenTL::DSGetBufferInfo() is failed.
			@~japanese	@brief	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_NEW_DATA の情報を取得します。
			@~japanese	@details	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_NEW_DATA の情報を取得します。
			@~japanese	@return	BUFFER_INFO_NEW_DATA データ
			@~japanese	@exception	GenTL::DSGetBufferInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual bool8_t		IsNewData() const = 0;

		/*!
			@~english	@brief	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_IS_QUEUED.
			@~english	@details	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_IS_QUEUED.
			@~english	@return	BUFFER_INFO_IS_QUEUED data.
			@~english	@exception	Throw out a GenICam::GenericException if GenTL::DSGetBufferInfo() is failed.
			@~japanese	@brief	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_IS_QUEUED の情報を取得します。
			@~japanese	@details	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_IS_QUEUED の情報を取得します。
			@~japanese	@return	BUFFER_INFO_IS_QUEUED データ
			@~japanese	@exception	GenTL::DSGetBufferInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual bool8_t		IsQueued() const = 0;

		/*!
			@~english	@brief	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_IS_ACQUIRING.
			@~english	@details	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_IS_ACQUIRING.
			@~english	@return	BUFFER_INFO_IS_ACQUIRING data.
			@~english	@exception	Throw out a GenICam::GenericException if GenTL::DSGetBufferInfo() is failed.
			@~japanese	@brief	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_IS_ACQUIRING の情報を取得します。
			@~japanese	@details	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_IS_ACQUIRING の情報を取得します。
			@~japanese	@return	BUFFER_INFO_IS_ACQUIRING データ
			@~japanese	@exception	GenTL::DSGetBufferInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual bool8_t		IsAcquiring() const = 0;

		/*!
			@~english	@brief	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_IS_INCOMPLETE.
			@~english	@details	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_IS_INCOMPLETE.
			@~english	@return	BUFFER_INFO_IS_INCOMPLETE data.
			@~english	@exception	Throw out a GenICam::GenericException if GenTL::DSGetBufferInfo() is failed.
			@~japanese	@brief	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_IS_INCOMPLETE の情報を取得します。
			@~japanese	@details	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_IS_INCOMPLETE の情報を取得します。
			@~japanese	@return	BUFFER_INFO_IS_INCOMPLETE データ
			@~japanese	@exception	GenTL::DSGetBufferInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual bool8_t		IsIncomplete() const = 0;

		/*!
			@~english	@brief	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_TLTYPE.
			@~english	@details	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_TLTYPE.
			@~english	@return	BUFFER_INFO_TLTYPE data.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or GenTL::DSGetBufferInfo() is failed.
			@~japanese	@brief	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_TLTYPE の情報を取得します。
			@~japanese	@details	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_TLTYPE の情報を取得します。
			@~japanese	@return	BUFFER_INFO_TLTYPE データ
			@~japanese	@exception	メモリー確保に失敗した場合や GenTL::DSGetBufferInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual GenICam::gcstring GetTLType() const = 0;

		/*!
			@~english	@brief	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_SIZE_FILLED.
			@~english	@details	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_SIZE_FILLED.
			@~english	@return	BUFFER_INFO_SIZE_FILLED data.
			@~english	@exception	Throw out a GenICam::GenericException if GenTL::DSGetBufferInfo() is failed.
			@~japanese	@brief	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_SIZE_FILLED の情報を取得します。
			@~japanese	@details	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_SIZE_FILLED の情報を取得します。
			@~japanese	@return	BUFFER_INFO_SIZE_FILLED データ
			@~japanese	@exception	GenTL::DSGetBufferInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual size_t GetSizeFilled() const = 0;

		/*!
			@~english	@brief	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_WIDTH.
			@~english	@details	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_WIDTH.
			@~english	@return	BUFFER_INFO_WIDTH data.
			@~english	@exception	Throw out a GenICam::GenericException if GenTL::DSGetBufferInfo() is failed.
			@~japanese	@brief	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_WIDTH の情報を取得します。
			@~japanese	@details	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_WIDTH の情報を取得します。
			@~japanese	@return	BUFFER_INFO_WIDTH データ
			@~japanese	@exception	GenTL::DSGetBufferInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual size_t GetWidth() const = 0;

		/*!
			@~english	@brief	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_HEIGHT.
			@~english	@details	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_HEIGHT.
			@~english	@return	BUFFER_INFO_HEIGHT data.
			@~english	@exception	Throw out a GenICam::GenericException if GenTL::DSGetBufferInfo() is failed.
			@~japanese	@brief	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_HEIGHT の情報を取得します。
			@~japanese	@details	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_HEIGHT の情報を取得します。
			@~japanese	@return	BUFFER_INFO_HEIGHT データ
			@~japanese	@exception	GenTL::DSGetBufferInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual size_t GetHeight() const = 0;

		/*!
			@~english	@brief	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_XOFFSET.
			@~english	@details	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_XOFFSET.
			@~english	@return	BUFFER_INFO_XOFFSET data.
			@~english	@exception	Throw out a GenICam::GenericException if GenTL::DSGetBufferInfo() is failed.
			@~japanese	@brief	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_XOFFSET の情報を取得します。
			@~japanese	@details	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_XOFFSET の情報を取得します。
			@~japanese	@return	BUFFER_INFO_XOFFSET データ
			@~japanese	@exception	GenTL::DSGetBufferInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual size_t GetXOffset() const = 0;

		/*!
			@~english	@brief	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_YOFFSET.
			@~english	@details	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_YOFFSET.
			@~english	@return	BUFFER_INFO_YOFFSET data.
			@~english	@exception	Throw out a GenICam::GenericException if GenTL::DSGetBufferInfo() is failed.
			@~japanese	@brief	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_YOFFSET の情報を取得します。
			@~japanese	@details	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_YOFFSET の情報を取得します。
			@~japanese	@return	BUFFER_INFO_YOFFSET データ
			@~japanese	@exception	GenTL::DSGetBufferInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual size_t GetYOffset() const = 0;

		/*!
			@~english	@brief	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_XPADDING.
			@~english	@details	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_XPADDING.
			@~english	@return	BUFFER_INFO_XPADDING data.
			@~english	@exception	Throw out a GenICam::GenericException if GenTL::DSGetBufferInfo() is failed.
			@~japanese	@brief	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_XPADDING の情報を取得します。
			@~japanese	@details	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_XPADDING の情報を取得します。
			@~japanese	@return	BUFFER_INFO_XPADDING データ
			@~japanese	@exception	GenTL::DSGetBufferInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual size_t GetXPadding() const = 0;

		/*!
			@~english	@brief	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_YPADDING.
			@~english	@details	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_YPADDING.
			@~english	@return	BUFFER_INFO_YPADDING data.
			@~english	@exception	Throw out a GenICam::GenericException if GenTL::DSGetBufferInfo() is failed.
			@~japanese	@brief	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_YPADDING の情報を取得します。
			@~japanese	@details	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_YPADDING の情報を取得します。
			@~japanese	@return	BUFFER_INFO_YPADDING データ
			@~japanese	@exception	GenTL::DSGetBufferInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual size_t GetYPadding() const = 0;

		/*!
			@~english	@brief	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_FRAMEID.
			@~english	@details	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_FRAMEID.
			@~english	@return	BUFFER_INFO_FRAMEID data.
			@~english	@exception	Throw out a GenICam::GenericException if GenTL::DSGetBufferInfo() is failed.
			@~japanese	@brief	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_FRAMEID の情報を取得します。
			@~japanese	@details	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_FRAMEID の情報を取得します。
			@~japanese	@return	BUFFER_INFO_FRAMEID データ
			@~japanese	@exception	GenTL::DSGetBufferInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual uint64_t GetFrameID() const = 0;

		/*!
			@~english	@brief	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_IMAGEPRESENT.
			@~english	@details	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_IMAGEPRESENT.
			@~english	@return	BUFFER_INFO_IMAGEPRESENT data.
			@~english	@exception	Throw out a GenICam::GenericException if GenTL::DSGetBufferInfo() is failed.
			@~japanese	@brief	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_IMAGEPRESENT の情報を取得します。
			@~japanese	@details	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_IMAGEPRESENT の情報を取得します。
			@~japanese	@return	BUFFER_INFO_IMAGEPRESENT データ
			@~japanese	@exception	GenTL::DSGetBufferInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual bool8_t IsImagePresent() const = 0;

		/*!
			@~english	@brief	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_IMAGEOFFSET.
			@~english	@details	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_IMAGEOFFSET.
			@~english	@return	BUFFER_INFO_IMAGEOFFSET data.
			@~english	@exception	Throw out a GenICam::GenericException if GenTL::DSGetBufferInfo() is failed.
			@~japanese	@brief	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_IMAGEOFFSET の情報を取得します。
			@~japanese	@details	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_IMAGEOFFSET の情報を取得します。
			@~japanese	@return	BUFFER_INFO_IMAGEOFFSET データ
			@~japanese	@exception	GenTL::DSGetBufferInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual size_t GetImageOffset() const = 0;

		/*!
			@~english	@brief	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_PAYLOADTYPE.
			@~english	@details	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_PAYLOADTYPE.
			@~english	@return	BUFFER_INFO_PAYLOADTYPE data.
			@~english	@exception	Throw out a GenICam::GenericException if GenTL::DSGetBufferInfo() is failed.
			@~japanese	@brief	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_PAYLOADTYPE の情報を取得します。
			@~japanese	@details	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_PAYLOADTYPE の情報を取得します。
			@~japanese	@return	BUFFER_INFO_PAYLOADTYPE データ
			@~japanese	@exception	GenTL::DSGetBufferInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual size_t GetPayloadType() const = 0;

		/*!
			@~english	@brief	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_PIXELFORMAT.
			@~english	@details	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_PIXELFORMAT.
			@~english	@return	BUFFER_INFO_PIXELFORMAT data.
			@~english	@exception	Throw out a GenICam::GenericException if GenTL::DSGetBufferInfo() is failed.
			@~japanese	@brief	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_PIXELFORMAT の情報を取得します。
			@~japanese	@details	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_PIXELFORMAT の情報を取得します。
			@~japanese	@return	BUFFER_INFO_PIXELFORMAT データ
			@~japanese	@exception	GenTL::DSGetBufferInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual uint64_t GetPixelFormat() const = 0;

		/*!
			@~english	@brief	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_PIXELFORMAT_NAMESPACE.
			@~english	@details	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_PIXELFORMAT_NAMESPACE.
			@~english	@return	BUFFER_INFO_PIXELFORMAT_NAMESPACE data.
			@~english	@exception	Throw out a GenICam::GenericException if GenTL::DSGetBufferInfo() is failed.
			@~japanese	@brief	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_PIXELFORMAT_NAMESPACE の情報を取得します。
			@~japanese	@details	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_PIXELFORMAT_NAMESPACE の情報を取得します。
			@~japanese	@return	BUFFER_INFO_PIXELFORMAT_NAMESPACE データ
			@~japanese	@exception	GenTL::DSGetBufferInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual uint64_t GetPixelFormatNameSpace() const = 0;

		/*!
			@~english	@brief	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_DELIVERED_IMAGEHEIGHT.
			@~english	@details	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_DELIVERED_IMAGEHEIGHT.
			@~english	@return	BUFFER_INFO_DELIVERED_IMAGEHEIGHT data.
			@~english	@exception	Throw out a GenICam::GenericException if GenTL::DSGetBufferInfo() is failed.
			@~japanese	@brief	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_DELIVERED_IMAGEHEIGHT の情報を取得します。
			@~japanese	@details	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_DELIVERED_IMAGEHEIGHT の情報を取得します。
			@~japanese	@return	BUFFER_INFO_DELIVERED_IMAGEHEIGHT データ
			@~japanese	@exception	GenTL::DSGetBufferInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual size_t GetDeliverdImageHeight() const = 0;

		/*!
			@~english	@brief	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_DELIVERED_CHUNKPAYLOADSIZE.
			@~english	@details	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_DELIVERED_CHUNKPAYLOADSIZE.
			@~english	@return	BUFFER_INFO_DELIVERED_CHUNKPAYLOADSIZE data.
			@~english	@exception	Throw out a GenICam::GenericException if GenTL::DSGetBufferInfo() is failed.
			@~japanese	@brief	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_DELIVERED_CHUNKPAYLOADSIZE の情報を取得します。
			@~japanese	@details	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_DELIVERED_CHUNKPAYLOADSIZE の情報を取得します。
			@~japanese	@return	BUFFER_INFO_DELIVERED_CHUNKPAYLOADSIZE データ
			@~japanese	@exception	GenTL::DSGetBufferInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual size_t GetDeliverdChunkPayloadSize() const = 0;

		/*!
			@~english	@brief	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_CHUNKLAYOUTID.
			@~english	@details	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_CHUNKLAYOUTID.
			@~english	@return	BUFFER_INFO_CHUNKLAYOUTID data.
			@~english	@exception	Throw out a GenICam::GenericException if GenTL::DSGetBufferInfo() is failed.
			@~japanese	@brief	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_CHUNKLAYOUTID の情報を取得します。
			@~japanese	@details	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_CHUNKLAYOUTID の情報を取得します。
			@~japanese	@return	BUFFER_INFO_CHUNKLAYOUTID データ
			@~japanese	@exception	GenTL::DSGetBufferInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual uint64_t GetChunkLayoutID() const = 0;

		/*!
			@~english	@brief	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_FILENAME.
			@~english	@details	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_FILENAME.
			@~english	@return	BUFFER_INFO_FILENAME data.
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or GenTL::DSGetBufferInfo() is failed.
			@~japanese	@brief	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_FILENAME の情報を取得します。
			@~japanese	@details	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_FILENAME の情報を取得します。
			@~japanese	@return	BUFFER_INFO_FILENAME データ
			@~japanese	@exception	メモリー確保に失敗した場合や GenTL::DSGetBufferInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual GenICam::gcstring GetFileName() const = 0;

		/*!
			@~english	@brief	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_PIXEL_ENDIANNESS.
			@~english	@details	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_PIXEL_ENDIANNESS.
			@~english	@return	BUFFER_INFO_PIXEL_ENDIANNESS data.
			@~english	@exception	Throw out a GenICam::GenericException if GenTL::DSGetBufferInfo() is failed.
			@~japanese	@brief	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_PIXEL_ENDIANNESS の情報を取得します。
			@~japanese	@details	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_PIXEL_ENDIANNESS の情報を取得します。
			@~japanese	@return	BUFFER_INFO_PIXEL_ENDIANNESS データ
			@~japanese	@exception	GenTL::DSGetBufferInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual int32_t GetPixelEndianness() const = 0;

		/*!
			@~english	@brief	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_DATA_SIZE.
			@~english	@details	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_DATA_SIZE.
			@~english	@return	BUFFER_INFO_DATA_SIZE data.
			@~english	@exception	Throw out a GenICam::GenericException if GenTL::DSGetBufferInfo() is failed.
			@~japanese	@brief	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_DATA_SIZE の情報を取得します。
			@~japanese	@details	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_DATA_SIZE の情報を取得します。
			@~japanese	@return	BUFFER_INFO_DATA_SIZE データ
			@~japanese	@exception	GenTL::DSGetBufferInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual size_t GetDataSize() const = 0;

		/*!
			@~english	@brief	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_TIMESTAMP_NS.
			@~english	@details	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_TIMESTAMP_NS.
			@~english	@return	BUFFER_INFO_TIMESTAMP_NS data.
			@~english	@exception	Throw out a GenICam::GenericException if GenTL::DSGetBufferInfo() is failed.
			@~japanese	@brief	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_TIMESTAMP_NS の情報を取得します。
			@~japanese	@details	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_TIMESTAMP_NS の情報を取得します。
			@~japanese	@return	BUFFER_INFO_TIMESTAMP_NS データ
			@~japanese	@exception	GenTL::DSGetBufferInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual uint64_t GetTimestampNS() const = 0;

		/*!
			@~english	@brief	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_DATA_LARGER_THAN_BUFFER.
			@~english	@details	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_DATA_LARGER_THAN_BUFFER.
			@~english	@return	BUFFER_INFO_DATA_LARGER_THAN_BUFFER data.
			@~english	@exception	Throw out a GenICam::GenericException if GenTL::DSGetBufferInfo() is failed.
			@~japanese	@brief	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_DATA_LARGER_THAN_BUFFER の情報を取得します。
			@~japanese	@details	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_DATA_LARGER_THAN_BUFFER の情報を取得します。
			@~japanese	@return	BUFFER_INFO_DATA_LARGER_THAN_BUFFER データ
			@~japanese	@exception	GenTL::DSGetBufferInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual bool8_t IsDataLargerThanBuffer() const = 0;

		/*!
			@~english	@brief	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_CONTAINS_CHUNKDATA.
			@~english	@details	GenTL::DSGetBufferInfo() is used to get the information of GenTL::BUFFER_INFO_CONTAINS_CHUNKDATA.
			@~english	@return	BUFFER_INFO_CONTAINS_CHUNKDATA data.
			@~english	@exception	Throw out a GenICam::GenericException if GenTL::DSGetBufferInfo() is failed.
			@~japanese	@brief	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_CONTAINS_CHUNKDATA の情報を取得します。
			@~japanese	@details	GenTL::DSGetBufferInfo() を使用して GenTL::BUFFER_INFO_CONTAINS_CHUNKDATA の情報を取得します。
			@~japanese	@return	BUFFER_INFO_CONTAINS_CHUNKDATA データ
			@~japanese	@exception	GenTL::DSGetBufferInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual bool8_t HasChunkData() const = 0;
	};

	// ---------------------------------------------------------------------
	// interface IStStreamBuffer
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiTL_PublicInterface
		@interface IStStreamBuffer
		@~english	@brief	Interface for Stream Buffer
		@~english	@details	Interface for Stream Buffer
		@~japanese	@brief	ストリームバッファ用インターフェース
		@~japanese	@details	ストリームバッファ用インターフェース
	*/
	interface PUBLIC_INTERFACE IStStreamBuffer : public IStRegisterCallback, public IStEventCtrl
	{
		/*!
			@~english	@brief	Acquire IStDataStream pointer.
			@~english	@details	Acquire IStDataStream pointer.
			@~english	@return	IStDataStream Interface pointer.
			@~english	@exception	None.
			@~japanese	@brief	IStDataStream インターフェースポインターを取得します。
			@~japanese	@details	IStDataStream インターフェースポインターを取得します。
			@~japanese	@return	IStDataStream インターフェースポインター
			@~japanese	@exception	なし
		*/
		virtual IStDataStream* GetIStDataStream() const = 0;

		/*!
			@~english	@brief	Acquire IStPort interface pointer.
			@~english	@details	Acquire IStPort interface pointer.
			@~english	@return	IStPort Interface pointer.
			@~english	@exception	None.
			@~japanese	@brief	IStPort インターフェースポインターを取得します。
			@~japanese	@details	IStPort インターフェースポインターを取得します。
			@~japanese	@return	IStPort インターフェースポインター
			@~japanese	@exception	なし
		*/
		virtual IStPort *GetIStPort() = 0;

		/*!
			@~english	@brief	Acquire IStStreamBufferInfo pointer.
			@~english	@details	Acquire IStStreamBufferInfo pointer.
			@~english	@return	IStStreamBufferInfo Interface pointer.
			@~english	@exception	None.
			@~japanese	@brief	IStStreamBufferInfo インターフェースポインターを取得します。
			@~japanese	@details	IStStreamBufferInfo インターフェースポインターを取得します。
			@~japanese	@return	IStStreamBufferInfo インターフェースポインター
			@~japanese	@exception	なし
		*/
		virtual const IStStreamBufferInfo *GetIStStreamBufferInfo() const = 0;

		/*!
			@~english	@brief	Acquire IStImage interface pointer.
			@~english	@details	Acquire IStImage interface pointer.
			@~english	@return	IStImage Interface pointer.
			@~english	@exception	Throw out a GenICam::GenericException if the stream buffer does not have any image data inside.
			@~japanese	@brief	IStImage インターフェースポインターを取得します。
			@~japanese	@details	IStImage インターフェースポインターを取得します。
			@~japanese	@return	IStImage インターフェースポインター
			@~japanese	@exception	ストリームバッファに画像データが含まれていない場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual IStImage*	GetIStImage() = 0;

		/*!
			@~english	@brief	Get INodeMap interface pointer for accessing chunk data.
			@~english	@details	Get INodeMap interface pointer for accessing chunk data.
			@~english	@return	GenApi::INodeMap Interface pointer.
			@~english	@exception	Throw out a GenICam::GenericException if the stream buffer does not have any chunk data inside.
			@~japanese	@brief	チャンクデータ用の GenApi::INodeMap インターフェースポインターを取得します。
			@~japanese	@details	チャンクデータ用の GenICam::INodeMap インターフェースポインターを取得します。
			@~japanese	@return	GenApi::INodeMap インターフェースポインター
			@~japanese	@exception	ストリームバッファにチャンクデータが含まれていない場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual GenApi::INodeMap* GetChunkINodeMap() = 0;
	};

	// ---------------------------------------------------------------------
	// interface IStStreamBufferReleasable
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiTL_PublicInterface
		@interface IStStreamBufferReleasable
		@~english	@brief	Interface for the Stream Buffer Releasable module.
		@~english	@details	Interface for the Stream Buffer Releasable module.
		@~japanese	@brief	解放可能なストリームバッファ用インターフェース
		@~japanese	@details	解放可能なストリームバッファ用インターフェース。解放されたバッファは受信バッファキューに挿入され、データの受信に再利用されます。
	*/
	interface PUBLIC_INTERFACE IStStreamBufferReleasable : public IStStreamBuffer, public IStReleasable
	{

	};

	// ---------------------------------------------------------------------
	// typedef CIStDataStreamPtr
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiTL_PublicImpl
		@typedef CIStDataStreamPtr
		@~english	@brief	The auto management class of IStStreamBufferReleasable for stream buffer module.
		@~english	@details	The auto management class of IStStreamBufferReleasable for stream buffer module. Use this class instead of managing the initial/release of IStStreamBufferReleasable class yourself. The destructor of this class will automatically call IStStreamBufferReleasable::Release() for re-queue the buffer into buffer list.
		@~japanese	@brief	IStStreamBufferReleasable インターフェースポインターの自動管理用クラスです。
		@~japanese	@details	IStStreamBufferReleasable インターフェースポインターの自動管理用クラスです。このクラスのデストラクタから IStStreamBufferReleasable::Release() が自動的に呼び出され、バッファが転送バッファとして再利用されるようになります。
	*/
	typedef CStAutoPtr<IStStreamBufferReleasable, IStStreamBuffer> CIStStreamBufferPtr;
}
#endif //ISTSTREAMBUFFER_H__

