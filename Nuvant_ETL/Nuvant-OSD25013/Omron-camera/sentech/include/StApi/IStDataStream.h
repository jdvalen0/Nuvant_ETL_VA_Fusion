//------------------------------------------------------------------------------
//  StApi
//------------------------------------------------------------------------------
/*!
@ingroup	StApiTL_PublicInterface
@file
@~english	@details	Definition of interface IStDataStreamInfo and IStDataStream.
@~japanese	@details	IStDataStreamInfo インターフェースおよび IStDataStream インターフェースの定義
*/
#ifndef ISTDATASTREAM_H__
#define ISTDATASTREAM_H__

#include "IStAllocator.h"
#include "IStStreamBuffer.h"

namespace StApi
{
	interface IStDevice;

	// ---------------------------------------------------------------------
	// interface IStDataStreamInfo
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiTL_PublicInterface
		@interface IStDataStreamInfo
		@~english	@brief	Interface for accessing Data Stream module information.
		@~english	@details	Interface for accessing Data Stream module information.
		@~japanese	@brief	データストリーム情報用インターフェース
		@~japanese	@details	データストリーム情報用インターフェース
	*/
	interface PUBLIC_INTERFACE IStDataStreamInfo
	{
		/*!
			@~english	@brief	GenTL::DSGetInfo() is used to get the value of GenTL::STREAM_INFO_ID.
			@~english	@details	GenTL::DSGetInfo() is used to get the value of GenTL::STREAM_INFO_ID.
			@~english	@return	STREAM_INFO_ID
			@~english	@exception	Throw out a GenICam::GenericException if memory allocation is failed or GenTL::DSGetInfo() is failed.
			@~japanese	@brief	GenTL::DSGetInfo() を使用して GenTL::STREAM_INFO_ID の情報を取得します。
			@~japanese	@details	GenTL::DSGetInfo() を使用して GenTL::STREAM_INFO_ID の情報を取得します。
			@~japanese	@return	STREAM_INFO_ID
			@~japanese	@exception	メモリー確保に失敗した場合や GenTL::DSGetInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual GenICam::gcstring GetID() const = 0;

		/*!
			@~english	@brief	GenTL::DSGetInfo() is used to get the value of GenTL::STREAM_INFO_NUM_DELIVERED.
			@~english	@details	GenTL::DSGetInfo() is used to get the value of GenTL::STREAM_INFO_NUM_DELIVERED.
			@~english	@return	STREAM_INFO_NUM_DELIVERED
			@~english	@exception	Throw out a GenICam::GenericException if GenTL::DSGetInfo() is failed.
			@~japanese	@brief	GenTL::DSGetInfo() を使用して GenTL::STREAM_INFO_NUM_DELIVERED の情報を取得します。
			@~japanese	@details	GenTL::DSGetInfo() を使用して GenTL::STREAM_INFO_NUM_DELIVERED の情報を取得します。
			@~japanese	@return	STREAM_INFO_NUM_DELIVERED
			@~japanese	@exception	GenTL::DSGetInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual uint64_t GetNumDelivered() const = 0;

		/*!
			@~english	@brief	GenTL::DSGetInfo() is used to get the value of GenTL::STREAM_INFO_NUM_UNDERRUN.
			@~english	@details	GenTL::DSGetInfo() is used to get the value of GenTL::STREAM_INFO_NUM_UNDERRUN.
			@~english	@return	STREAM_INFO_NUM_UNDERRUN
			@~english	@exception	Throw out a GenICam::GenericException if GenTL::DSGetInfo() is failed.
			@~japanese	@brief	GenTL::DSGetInfo() を使用して GenTL::STREAM_INFO_NUM_UNDERRUN の情報を取得します。
			@~japanese	@details	GenTL::DSGetInfo() を使用して GenTL::STREAM_INFO_NUM_UNDERRUN の情報を取得します。
			@~japanese	@return	STREAM_INFO_NUM_UNDERRUN
			@~japanese	@exception	GenTL::DSGetInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual uint64_t GetNumUnderrun() const = 0;

		/*!
			@~english	@brief	GenTL::DSGetInfo() is used to get the value of GenTL::STREAM_INFO_NUM_ANNOUNCED.
			@~english	@details	GenTL::DSGetInfo() is used to get the value of GenTL::STREAM_INFO_NUM_ANNOUNCED.
			@~english	@return	STREAM_INFO_NUM_ANNOUNCED
			@~english	@exception	Throw out a GenICam::GenericException if GenTL::DSGetInfo() is failed.
			@~japanese	@brief	GenTL::DSGetInfo() を使用して GenTL::STREAM_INFO_NUM_ANNOUNCED の情報を取得します。
			@~japanese	@details	GenTL::DSGetInfo() を使用して GenTL::STREAM_INFO_NUM_ANNOUNCED の情報を取得します。
			@~japanese	@return	STREAM_INFO_NUM_ANNOUNCED
			@~japanese	@exception	GenTL::DSGetInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual size_t GetNumAnnounced() const = 0;

		/*!
			@~english	@brief	GenTL::DSGetInfo() is used to get the value of GenTL::STREAM_INFO_NUM_QUEUED.
			@~english	@details	GenTL::DSGetInfo() is used to get the value of GenTL::STREAM_INFO_NUM_QUEUED.
			@~english	@return	STREAM_INFO_NUM_QUEUED
			@~english	@exception	Throw out a GenICam::GenericException if GenTL::DSGetInfo() is failed.
			@~japanese	@brief	GenTL::DSGetInfo() を使用して GenTL::STREAM_INFO_NUM_QUEUED の情報を取得します。
			@~japanese	@details	GenTL::DSGetInfo() を使用して GenTL::STREAM_INFO_NUM_QUEUED の情報を取得します。
			@~japanese	@return	STREAM_INFO_NUM_QUEUED
			@~japanese	@exception	GenTL::DSGetInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual size_t GetNumQueued() const = 0;

		/*!
			@~english	@brief	GenTL::DSGetInfo() is used to get the value of GenTL::STREAM_INFO_NUM_AWAIT_DELIVERY.
			@~english	@details	GenTL::DSGetInfo() is used to get the value of GenTL::STREAM_INFO_NUM_AWAIT_DELIVERY.
			@~english	@return	STREAM_INFO_NUM_AWAIT_DELIVERY
			@~english	@exception	Throw out a GenICam::GenericException if GenTL::DSGetInfo() is failed.
			@~japanese	@brief	GenTL::DSGetInfo() を使用して GenTL::STREAM_INFO_NUM_AWAIT_DELIVERY の情報を取得します。
			@~japanese	@details	GenTL::DSGetInfo() を使用して GenTL::STREAM_INFO_NUM_AWAIT_DELIVERY の情報を取得します。
			@~japanese	@return	STREAM_INFO_NUM_AWAIT_DELIVERY
			@~japanese	@exception	GenTL::DSGetInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual size_t GetNumAwaitDelivery() const = 0;

		/*!
			@~english	@brief	GenTL::DSGetInfo() is used to get the value of GenTL::STREAM_INFO_NUM_STARTED.
			@~english	@details	GenTL::DSGetInfo() is used to get the value of GenTL::STREAM_INFO_NUM_STARTED.
			@~english	@return	STREAM_INFO_NUM_STARTED
			@~english	@exception	Throw out a GenICam::GenericException if GenTL::DSGetInfo() is failed.
			@~japanese	@brief	GenTL::DSGetInfo() を使用して GenTL::STREAM_INFO_NUM_STARTED の情報を取得します。
			@~japanese	@details	GenTL::DSGetInfo() を使用して GenTL::STREAM_INFO_NUM_STARTED の情報を取得します。
			@~japanese	@return	STREAM_INFO_NUM_STARTED
			@~japanese	@exception	GenTL::DSGetInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual uint64_t GetNumStarted() const = 0;

		/*!
			@~english	@brief	GenTL::DSGetInfo() is used to get the value of GenTL::STREAM_INFO_PAYLOAD_SIZE.
			@~english	@details	GenTL::DSGetInfo() is used to get the value of GenTL::STREAM_INFO_PAYLOAD_SIZE.
			@~english	@return	STREAM_INFO_PAYLOAD_SIZE
			@~english	@exception	Throw out a GenICam::GenericException if GenTL::DSGetInfo() is failed.
			@~japanese	@brief	GenTL::DSGetInfo() を使用して GenTL::STREAM_INFO_PAYLOAD_SIZE の情報を取得します。
			@~japanese	@details	GenTL::DSGetInfo() を使用して GenTL::STREAM_INFO_PAYLOAD_SIZE の情報を取得します。
			@~japanese	@return	STREAM_INFO_PAYLOAD_SIZE
			@~japanese	@exception	GenTL::DSGetInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual size_t GetPayloadSize() const = 0;

		/*!
			@~english	@brief	GenTL::DSGetInfo() is used to get the value of GenTL::STREAM_INFO_IS_GRABBING.
			@~english	@details	GenTL::DSGetInfo() is used to get the value of GenTL::STREAM_INFO_IS_GRABBING.
			@~english	@return	STREAM_INFO_IS_GRABBING
			@~english	@exception	Throw out a GenICam::GenericException if GenTL::DSGetInfo() is failed.
			@~japanese	@brief	GenTL::DSGetInfo() を使用して GenTL::STREAM_INFO_IS_GRABBING の情報を取得します。
			@~japanese	@details	GenTL::DSGetInfo() を使用して GenTL::STREAM_INFO_IS_GRABBING の情報を取得します。
			@~japanese	@return	STREAM_INFO_IS_GRABBING
			@~japanese	@exception	GenTL::DSGetInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual bool8_t IsGrabbing() const = 0;

		/*!
			@~english	@brief	GenTL::DSGetInfo() is used to get the value of GenTL::STREAM_INFO_DEFINES_PAYLOADSIZE.
			@~english	@details	GenTL::DSGetInfo() is used to get the value of GenTL::STREAM_INFO_DEFINES_PAYLOADSIZE.
			@~english	@return	STREAM_INFO_DEFINES_PAYLOADSIZE
			@~english	@exception	Throw out a GenICam::GenericException if GenTL::DSGetInfo() is failed.
			@~japanese	@brief	GenTL::DSGetInfo() を使用して GenTL::STREAM_INFO_DEFINES_PAYLOADSIZE の情報を取得します。
			@~japanese	@details	GenTL::DSGetInfo() を使用して GenTL::STREAM_INFO_DEFINES_PAYLOADSIZE の情報を取得します。
			@~japanese	@return	STREAM_INFO_DEFINES_PAYLOADSIZE
			@~japanese	@exception	GenTL::DSGetInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual bool8_t GetDefinesPayloadSize() const = 0;

		/*!
			@~english	@brief	GenTL::DSGetInfo() is used to get the value of GenTL::STREAM_INFO_TLTYPE.
			@~english	@details	GenTL::DSGetInfo() is used to get the value of GenTL::STREAM_INFO_TLTYPE.
			@~english	@return	STREAM_INFO_TLTYPE
			@~english	@exception	Throw out a GenICam::GenericException if GenTL::DSGetInfo() is failed.
			@~japanese	@brief	GenTL::DSGetInfo() を使用して GenTL::STREAM_INFO_TLTYPE の情報を取得します。
			@~japanese	@details	GenTL::DSGetInfo() を使用して GenTL::STREAM_INFO_TLTYPE の情報を取得します。
			@~japanese	@return	STREAM_INFO_TLTYPE
			@~japanese	@exception	GenTL::DSGetInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual GenICam::gcstring GetTLType() const = 0;

		/*!
			@~english	@brief	GenTL::DSGetInfo() is used to get the value of GenTL::STREAM_INFO_NUM_CHUNKS_MAX.
			@~english	@details	GenTL::DSGetInfo() is used to get the value of GenTL::STREAM_INFO_NUM_CHUNKS_MAX.
			@~english	@return	STREAM_INFO_NUM_CHUNKS_MAX
			@~english	@exception	Throw out a GenICam::GenericException if GenTL::DSGetInfo() is failed.
			@~japanese	@brief	GenTL::DSGetInfo() を使用して GenTL::STREAM_INFO_NUM_CHUNKS_MAX の情報を取得します。
			@~japanese	@details	GenTL::DSGetInfo() を使用して GenTL::STREAM_INFO_NUM_CHUNKS_MAX の情報を取得します。
			@~japanese	@return	STREAM_INFO_NUM_CHUNKS_MAX
			@~japanese	@exception	GenTL::DSGetInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual size_t GetNumChunksMax() const = 0;

		/*!
			@~english	@brief	GenTL::DSGetInfo() is used to get the value of GenTL::STREAM_INFO_BUF_ANNOUNCE_MIN.
			@~english	@details	GenTL::DSGetInfo() is used to get the value of GenTL::STREAM_INFO_BUF_ANNOUNCE_MIN.
			@~english	@return	STREAM_INFO_BUF_ANNOUNCE_MIN
			@~english	@exception	Throw out a GenICam::GenericException if GenTL::DSGetInfo() is failed.
			@~japanese	@brief	GenTL::DSGetInfo() を使用して GenTL::STREAM_INFO_BUF_ANNOUNCE_MIN の情報を取得します。
			@~japanese	@details	GenTL::DSGetInfo() を使用して GenTL::STREAM_INFO_BUF_ANNOUNCE_MIN の情報を取得します。
			@~japanese	@return	STREAM_INFO_BUF_ANNOUNCE_MIN
			@~japanese	@exception	GenTL::DSGetInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual size_t GetBufAnnounceMin() const = 0;

		/*!
			@~english	@brief	GenTL::DSGetInfo() is used to get the value of GenTL::STREAM_INFO_BUF_ALIGNMENT.
			@~english	@details	GenTL::DSGetInfo() is used to get the value of GenTL::STREAM_INFO_BUF_ALIGNMENT.
			@~english	@return	STREAM_INFO_BUF_ALIGNMENT
			@~english	@exception	Throw out a GenICam::GenericException if GenTL::DSGetInfo() is failed.
			@~japanese	@brief	GenTL::DSGetInfo() を使用して GenTL::STREAM_INFO_BUF_ALIGNMENT の情報を取得します。
			@~japanese	@details	GenTL::DSGetInfo() を使用して GenTL::STREAM_INFO_BUF_ALIGNMENT の情報を取得します。
			@~japanese	@return	STREAM_INFO_BUF_ALIGNMENT
			@~japanese	@exception	GenTL::DSGetInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual size_t GetBufAlignment() const = 0;
	};
	
	// ---------------------------------------------------------------------
	// interface IStDataStream
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiTL_PublicInterface
		@interface IStDataStream
		@~english	@brief	Interface for the Data Straem module.
		@~english	@details	Interface for the Data Straem module.
		@~japanese	@brief	データストリーム用インターフェース
		@~japanese	@details	データストリーム用インターフェース
	*/
	interface PUBLIC_INTERFACE IStDataStream : public IStRegisterCallback, public IStEventCtrl
	{
		/*!
			@~english	@brief	Acquire IStDevice pointer.
			@~english	@details	Acquire IStDevice pointer.
			@~english	@return	IStDevice Interface pointer.
			@~english	@exception	None.
			@~japanese	@brief	IStDevice インターフェースポインターを取得します。
			@~japanese	@details	IStDevice インターフェースポインターを取得します。
			@~japanese	@return	IStDevice インターフェースポインター
			@~japanese	@exception	なし
		*/
		virtual IStDevice* GetIStDevice() = 0;

		/*!
			@~english	@brief	Acquire interface pointer of IStPort.
			@~english	@details	Acquire interface pointer of IStPort.
			@~english	@return	IStPort Interface pointer.
			@~english	@exception	None.
			@~japanese	@brief	IStPort インターフェースポインターを取得します。
			@~japanese	@details	IStPort インターフェースポインターを取得します。
			@~japanese	@return	IStPort インターフェースポインター
			@~japanese	@exception	なし
		*/
		virtual IStPort *GetIStPort() = 0;

		/*!
			@~english	@brief	Acquire interface pointer of IStDataStreamInfo.
			@~english	@details	Acquire interface pointer of IStDataStreamInfo.
			@~english	@return	IStDataStreamInfo Interface pointer.
			@~english	@exception	None.
			@~japanese	@brief	IStDataStreamInfo インターフェースポインターを取得します。
			@~japanese	@details	IStDataStreamInfo インターフェースポインターを取得します。
			@~japanese	@return	IStDataStreamInfo インターフェースポインター
			@~japanese	@exception	なし
		*/
		virtual const IStDataStreamInfo * GetIStDataStreamInfo() const = 0;

		/*!
			@~english	@brief	Acquire the counts of stream buffer.
			@~english	@details	Acquire the counts of stream buffer.
			@~english	@return	The counts of stream buffer.
			@~english	@exception	None.
			@~japanese	@brief	ストリーミング時に作成されるバッファの数を取得します。
			@~japanese	@details	ストリーミング時に作成されるバッファの数を取得します。
			@~japanese	@return	ストリーミング時に作成されるバッファの数
			@~japanese	@exception	なし
		*/
		virtual size_t GetStreamBufferCount() const = 0;

		/*!
			@~english	@brief	Set the counts of stream buffer.
			@~english	@details	Set the counts of stream buffer.
			@~english	@param[in]	nCount	Counts of stream buffer.
			@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument. 
			@~japanese	@brief	ストリーミング時に作成されるバッファの数を設定します。
			@~japanese	@details	ストリーミング時に作成されるバッファの数を設定します。
			@~japanese	@param[in]	nCount	ストリーミング時に作成されるバッファの数
			@~japanese	@exception	不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void SetStreamBufferCount(size_t nCount) = 0;

		/*!
			@~english	@brief	Acquire a buffer pointer of IStStreamBufferReleasable from a completed transfer buffer.
			@~english	@details	Acquire a buffer pointer of IStStreamBufferReleasable from a completed transfer buffer.
			@~english	@attention	Call IStStreamBufferReleasable::Release() when acquired buffer is no longer needed. This will release the acquired buffer back to receive buffer list.
			@~english	@param[in]	nTimeoutTime	Indicate the timeout of waiting for transfer finish (0xFFFFFFFF:Infinity).
			@~english	@param[in]	eHandlingOfTimeout	Indicate the operation when timeout occurred.
			@~english	@return	IStStreamBuffer Buffer pointer. NULL if timeout occurred.
			@~english	@exception	If disconnection of a device is detected, a GenICam::GenericException will be threw out.
			@~japanese	@brief	転送が完了したバッファ用の IStStreamBufferReleasable インターフェースポインターを取得します。
			@~japanese	@details	転送が完了したバッファ用の IStStreamBufferReleasable インターフェースポインターを取得します。
			@~japanese	@attention	取得したバッファが不要になったらバッファが転送バッファとして再利用されるように IStStreamBufferReleasable::Release() を呼び出してください。
			@~japanese	@param[in]	nTimeoutTime	転送の完了を待機する時間[ms]を指定します。0xFFFFFFFFを指定すると無限に待機します。
			@~japanese	@param[in]	eHandlingOfTimeout	タイムアウトが発生した際の動作を指定します。
			@~japanese	@return	IStStreamBuffer インターフェースポインター。引数に StTimeoutHandling_Return が指定されタイムアウトが発生した場合は、 NULL が返されます。
			@~japanese	@exception	デバイスが切断された場合や、引数に StTimeoutHandling_ThrowException が指定されタイムアウトが発生した場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual IStStreamBufferReleasable *RetrieveBuffer(uint32_t nTimeoutTime, EStTimeoutHandling_t eHandlingOfTimeout = StTimeoutHandling_ThrowException) = 0;

		/*!
			@~english	@brief	Start the data acquisition from host side.
			@~english	@details	Start the data acquisition from host side.
			@~english	@attention	Additional IStDevice::AcquisitionStart() call is required for the device to send the data out. To stop data acquisition, call StopAcquisition().
			@~english	@param[in]	nNumToAcquire	Number of acquisition (set to GenTL::GENTL_INFINITE for infinity acquisition). The acquisition will stop after reaching this number. Nevertheless, StopAcquisition() is still needed to end the image acquisition.
			@~english	@param[in]	eAcqStartFlags	A start flags for the acquisition engine.
			@~english	@exception	Throw out a GenICam::GenericException if disconnection of a device is detected or any error occurred in DSStartAcquisition().
			@~english	@sa IStDevice::AcquisitionStart()
			@~japanese	@brief	ホスト側のデータ取得を開始します。
			@~japanese	@details	ホスト側のデータ取得を開始します。
			@~japanese	@attention	別途 IStDevice::AcquisitionStart() を呼び出してデバイス(カメラ)側のデータ送信を開始する必要があります。停止する場合は StopAcquisition() を呼び出します。
			@~japanese	@param[in]	nNumToAcquire	取得するバッファの数を指定します( GenTL::GENTL_INFINITE を指定すると無限)。指定した数のバッファを取得した場合も別途 StopAcquisition() の呼び出しが必要になります。
			@~japanese	@param[in]	eAcqStartFlags	取り込み開始フラグ
			@~japanese	@exception	デバイスが切断された場合や GenTL::DSStartAcquisition() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
			@~japanese	@sa IStDevice::AcquisitionStart()
		*/
		virtual void StartAcquisition(uint64_t nNumToAcquire = GENTL_INFINITE, GenTL::ACQ_START_FLAGS eAcqStartFlags = GenTL::ACQ_START_FLAGS_DEFAULT) = 0;

		/*!
			@~english	@brief	Stop the data acquisition from host side.
			@~english	@details	Stop the data acquisition from host side.
			@~english	@attention	Additional IStDevice::AcquisitionStop() call is required for the device to stop sending the data out.
			@~english	@param[in]	eAcqStopFlags	A stop flags for the acquisition engine.
			@~english	@exception	Throw out a GenICam::GenericException if any error occurred in DSStopAcquisition().
			@~english	@sa IStDevice::AcquisitionStop()
			@~japanese	@brief	ホスト側のデータ取得を停止します。
			@~japanese	@details	ホスト側のデータ取得を停止します。
			@~japanese	@attention	予め IStDevice::AcquisitionStop() を呼び出してデバイス(カメラ)側のデータ送信を停止する必要があります。
			@~japanese	@param[in]	eAcqStopFlags	取り込み停止フラグ
			@~japanese	@exception	GenTL::DSStopAcquisition() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
			@~japanese	@sa IStDevice::AcquisitionStop()
		*/
		virtual void StopAcquisition(GenTL::ACQ_STOP_FLAGS eAcqStopFlags = GenTL::ACQ_STOP_FLAGS_DEFAULT) = 0;

		/*!
			@~english	@brief	Check if data acquisition is on going.
			@~english	@details	    Check if data acquisition is on going.
			@~english	@attention	Note that even if IStDataStreamInfo::IsGrabbing() is false, if IStDataStreamInfo::GetNumAwaitDelivery() is larger than 0 this will still return true.
			@~english	@return		Return true if data acquisition from the device(camera) is on going.
			@~english	@exception	Throw out a GenICam::GenericException if any error occured when calling GenTL::DSGetInfo().
			@~english	@sa IStDataStreamInfo::IsGrabbing(), IStDataStreamInfo::GetNumAwaitDelivery()
			@~japanese	@brief	デバイス(カメラ)からデータを取得中か否かを確認します。
			@~japanese	@details	デバイス(カメラ)からデータを取得中か否かを確認します。
			@~japanese	@attention	IStDataStreamInfo::IsGrabbing() が false でも、IStDataStreamInfo::GetNumAwaitDelivery() が0より大きい場合は true が返されます。
			@~japanese	@return		デバイス(カメラ)からデータを取得中の場合 true が返されます。
			@~japanese	@exception	GenTL::DSGetInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
			@~japanese	@sa IStDataStreamInfo::IsGrabbing(), IStDataStreamInfo::GetNumAwaitDelivery()
		*/
		virtual bool IsGrabbing() = 0;

		/*!
			@~english	@brief	Get the current frame rate.
			@~english	@details	Get the current frame rate
			@~english	@attention	In v1.0.1 only payload containing image data was counted. Since v1.0.2 all payload including chunk without image data is counted. 
			@~english	@return		Frame rate value [fps].
			@~english	@exception	None.
			@~japanese	@brief	現在のフレーム(ブロック)レートを取得します。
			@~japanese	@details	現在のフレーム(ブロック)レートを取得します。
			@~japanese	@attention	v1.0.1では画像データが含まれたペイロードデータ(ブロック)のみがカウントされておりましたが、v1.0.2以降ではすべてのペイロードデータ(ブロック)がカウントされます。
			@~japanese	@return		フレーム(ブロック)レート[fps]
			@~japanese	@exception	なし
		*/
		virtual double GetCurrentFPS() const = 0;

		/*!
			@~english	@brief	Get the current data rate.
			@~english	@details	Get the current data rate.
			@~english	@attention	The payload data excluding the leader, trailer, and event data is counted. Thus the value will be lower than the real data rate.
			@~english	@return		Value of data rate [bytes/s].
			@~english	@exception	None.
			@~japanese	@brief	現在のデータレートを取得します。
			@~japanese	@details	現在のデータレートを取得します。
			@~japanese	@attention	ペイロードデータのみが対象となり、リーダー、トレイラーおよびイベントデータなどはカウントされないため、実際のデータレートよりも低い値になります。
			@~japanese	@return		データレート[bytes/s]
			@~japanese	@exception	なし
		*/
		virtual double GetCurrentBPS() const = 0;
	};

	// ---------------------------------------------------------------------
	// interface IStDataStreamReleasable
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiTL_PublicInterface
		@interface IStDataStreamReleasable
		@~english	@brief	Interface for the Data Stream Releasable module.
		@~english	@details	Interface for the Data Stream Releasable module.
		@~japanese	@brief	解放可能なデータストリーム用インターフェース
		@~japanese	@details	解放可能なデータストリーム用インターフェース
	*/
	interface PUBLIC_INTERFACE IStDataStreamReleasable : public IStDataStream, public IStReleasable
	{

	};

	// ---------------------------------------------------------------------
	// typedef CIStDataStreamPtr
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiTL_PublicImpl
		@typedef CIStDataStreamPtr
		@~english	@brief	The auto management class of IStDataStreamReleasable for interface of the data stream module.
		@~english	@details	The auto management class of IStDataStreamReleasable for interface of the data stream module. The destructor of this class will automatically call IStDataStreamReleasable::Release().
		@~japanese	@brief	IStDataStreamReleasable インターフェースポインターの自動管理用クラスです。
		@~japanese	@details	IStDataStreamReleasable インターフェースポインターの自動管理用クラスです。このクラスのデストラクタから IStDataStreamReleasable::Release() が自動的に呼び出されます。
	*/
	typedef CStAutoPtr<IStDataStreamReleasable, IStDataStream> CIStDataStreamPtr;

	// ---------------------------------------------------------------------
	// class CIStDataStreamPtrArray
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiTL_PublicImpl
		@class CIStDataStreamPtrArray
		@~english	@brief	This class manages the lifetime of classes derived from IStDataStream.
		@~english	@details	This class manages the lifetime of classes derived from IStDataStream. The destructor of this class will automatically call IStDataStreamReleasable::Release().
		@~japanese	@brief	IStDataStreamReleasable インターフェースポインターリストの自動管理用クラスです。
		@~japanese	@details	IStDataStreamReleasable インターフェースポインターリストの自動管理用クラスです。このクラスのデストラクタから IStDataStreamReleasable::Release() が自動的に呼び出されます。
	*/
	class ST_API_TL CIStDataStreamPtrArray : public CStAutoPtrArray<IStDataStreamReleasable, IStDataStream>
	{
	public:
		CIStDataStreamPtrArray();
		virtual ~CIStDataStreamPtrArray();

		/*!
			@copydoc IStDataStreamReleasable::Release()
		*/
		void Release();

		/*!
			@copydoc IStDataStream::RetrieveBuffer()
		*/
		IStStreamBufferReleasable *RetrieveBuffer(uint32_t nTimeoutTime, EStTimeoutHandling_t eHandlingOfTimeout = StTimeoutHandling_ThrowException);

		/*!
			@copydoc IStDataStream::StartAcquisition()
		*/
		void StartAcquisition(uint64_t nNumToAcquire = GENTL_INFINITE, GenTL::ACQ_START_FLAGS eAcqStartFlags = GenTL::ACQ_START_FLAGS_DEFAULT);

		/*!
			@copydoc IStDataStream::StopAcquisition()
		*/
		void StopAcquisition(GenTL::ACQ_STOP_FLAGS eAcqStopFlags = GenTL::ACQ_STOP_FLAGS_DEFAULT);

		/*!
			@~english	@brief	Check if data acquisition is on going.
			@~english	@details	    Check if data acquisition is on going.
			@~english	@return		If all the DataStream are on working, return true; if any of DataStream stopped, return false.
			@~english	@exception	Throw out a GenICam::GenericException if GenTL::DSGetInfo() is failed.
			@~english	@sa IStDataStream::IsGrabbing()
			@~japanese	@brief	デバイス(カメラ)からデータを取得中か否かを確認します。
			@~japanese	@details	デバイス(カメラ)からデータを取得中か否かを確認します。
			@~japanese	@return		すべてのデータストリームがデータ取得中( IStDataStream::IsGrabbing() がtrue)の時に true が返されます。
			@~japanese	@exception	GenTL::DSGetInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
			@~japanese	@sa IStDataStream::IsGrabbing()
		*/
		bool IsGrabbingAll();

		/*!
			@~english	@brief	Check if data acquisition is on going.
			@~english	@details	    Check if data acquisition is on going.
			@~english	 @return		If any of DataStream is on working, return true; if all of DataStream stopped, return false.
			@~english	@exception	Throw out a GenICam::GenericException if GenTL::DSGetInfo() is failed.
			@sa IStDataStream::IsGrabbing()
			@~japanese	@brief	デバイス(カメラ)からデータを取得中か否かを確認します。
			@~japanese	@details	デバイス(カメラ)からデータを取得中か否かを確認します。
			@~japanese	@return		いずれかのデータストリームがデータ取得中( IStDataStream::IsGrabbing() がtrue)の時に true が返されます。
			@~japanese	@exception	GenTL::DSGetInfo() がエラーを返した場合は、例外 GenICam::GenericException が発生します。
			@sa IStDataStream::IsGrabbing()
		*/
		bool IsGrabbingAny();

	private:
		// Copy is prohibited.
		CIStDataStreamPtrArray(CIStDataStreamPtrArray &rhs);

		// Copy is prohibited.
		CIStDataStreamPtrArray & operator= (CIStDataStreamPtrArray &rhs);

	};
}
#endif //ISTDATASTREAM_H__

