/* This file is encoded in UTF-8,  */
/* but BOM has not been added to accommodate environments not compatible with BOM. */
/*
 StApi
*/
/*!
	@ingroup	GenTL_PublicImple
	@file	StGenTL_Function.h
	@~english	@details	
	@~japanese	@details
*/

#ifndef GC_API_NAME
#define GC_API_NAME(name) GC_ERROR  name
#define GC_API_LIST(params)			params;
#define GC_API_DEF
#endif

#ifdef GC_API_DEF
#ifdef __cplusplus
namespace GenTL
{
#endif /* __cplusplus */
#endif /* GC_API_DEF */


	/*!
		@ingroup	GenTL_PublicImple
		@brief	This function must be called after no function of the GenTL library is needed anymore to clean up the resources from the GCInitLib function call. Each call to GCCloseLib has to be accompanied by a preceding call to GCInitLib.
		@details		This function must be called after no function of the GenTL library is needed anymore to clean up the resources from the GCInitLib function call. Each call to GCCloseLib has to be accompanied by a preceding call to GCInitLib.
		@return		GC_ERROR value.
	*/
	GC_API_NAME(GCCloseLib) GC_API_LIST((void))


	/*!
		\ingroup	GenTL_PublicImple
		\brief Inquire information about a GenTL implementation without instantiating a System module.
		\details Inquire information about a GenTL implementation without instantiating a System module.
		\param[in] iInfoCmd	Information to be retrieved as defined in TL_INFO_CMD.
		\param[out] piType	Data type of the pBuffer content as defined in the TL_INFO_CMD and INFO_DATATYPE.
		\param[in,out] pBuffer	Pointer to a user allocated buffer to receive the requested	information. If this parameter is NULL, piSize will contain the	minimal size of pBuffer in bytes. If the iType is a string the size includes the terminating 0.
		\param[in,out] piSize	pBuffer equal NULL:	out: minimal size of pBuffer in bytes to hold all information pBuffer unequal NULL: in: size of the provided pBuffer in bytes out: number of bytes filled by the function
		@return		GC_ERROR value.
	*/
	GC_API_NAME(GCGetInfo) GC_API_LIST((TL_INFO_CMD iInfoCmd, INFO_DATATYPE *piType, void *pBuffer, size_t *piSize))

	/*!
		\ingroup	GenTL_PublicImple
		\brief Returns a readable text description of the last error occurred in the local thread context.
		\details Returns a readable text description of the last error occurred in the local thread context.
		\param[out] piErrorCode	Error code of the last error.
		\param[in,out] sErrorText	Pointer to a user allocated C string buffer to receive the last error text. If this parameter is NULL, piSize will contain the needed size of sErrorText in bytes. The size includes the terminating 0.
		\param[in,out] piSize	sErrorText equal NULL: out: minimal size of sErrorText in bytes to hold all information. sErrorText unequal NULL: in: size of the provided sErrorText in bytes out: number of bytes filled by the function.
		@return		GC_ERROR value.
	*/
	GC_API_NAME(GCGetLastError) GC_API_LIST((GC_ERROR *piErrorCode, char *sErrorText, size_t *piSize))

	/*!
		\ingroup	GenTL_PublicImple
		\brief This function must be called prior to any other function call to allow global initialization of	the GenTL Producer driver.
		\details This function must be called prior to any other function call to allow global initialization of	the GenTL Producer driver.
		@return		GC_ERROR value.
	*/
	GC_API_NAME(GCInitLib)
	GC_API_LIST((void))

	/*!
		\ingroup	GenTL_PublicImple
		\brief Closes the System module associated with the given hSystem handle. This closes the whole GenTL Producer driver and frees all resources.
		\details Closes the System module associated with the given hSystem handle. This closes the whole GenTL Producer driver and frees all resources.
		\param[in] hSystem	System module handle to close.
		@return		GC_ERROR value.
	*/
	GC_API_NAME(TLClose)
	GC_API_LIST((TL_HANDLE hSystem))

	/*!
		\ingroup	GenTL_PublicImple
		\brief Inquire information about the System module as defined in TL_INFO_CMD.
		\details Inquire information about the System module as defined in TL_INFO_CMD.
		\param[in] hSystem	System module to work on.
		\param[in] iInfoCmd	Information to be retrieved as defined in TL_INFO_CMD.
		\param[out] piType	Data type of the pBuffer content as defined in the TL_INFO_CMD and INFO_DATATYPE.
		\param[in,out] pBuffer	Pointer to a user allocated buffer to receive the requested information. If this parameter is NULL, piSize will contain the minimal size of pBuffer in bytes. If the piType is a string the size includes the terminating 0.
		\param[in,out] piSize	pBuffer equal NULL:
				out: minimal size of pBuffer in bytes to hold all information
			pBuffer unequal NULL:
				in: size of the provided pBuffer in bytes
				out: number of bytes filled by the function.
		@return		GC_ERROR value.
	*/
	GC_API_NAME(TLGetInfo)
	GC_API_LIST((TL_HANDLE hSystem, TL_INFO_CMD iInfoCmd, INFO_DATATYPE *piType, void *pBuffer, size_t *piSize))

	/*!
		\ingroup	GenTL_PublicImple
		\brief Queries the unique ID of the interface at iIndex in the internal interface list.
		\details Queries the unique ID of the interface at iIndex in the internal interface list.
		\param[in] hSystem	System module to work on.
		\param[in] iIndex	Zero-based index of the interface on this system.
		\param[in,out] sIfaceID	Pointer to a user allocated C string buffer to receive the Interface module ID at the given iIndex. If this parameter is NULL, piSize will contain the needed size of sIfaceID in bytes. The size includes the terminating 0.
		\param[in,out] piSize	sIfaceID equal NULL:
	out: minimal size of sIfaceID in bytes to hold all information
	sIfaceID unequal NULL:
	in: size of the provided sIfaceID in bytes
	out: number of bytes filled by the function
		@return		GC_ERROR value.
	*/
	GC_API_NAME(TLGetInterfaceID)
	GC_API_LIST((TL_HANDLE hSystem, uint32_t iIndex, char *sIfaceID, size_t *piSize))

	/*!
		\ingroup	GenTL_PublicImple
		\brief Inquire information about an interface on the given System module hSystem as defined in	INTERFACE_INFO_CMD without opening the interface.
		\details Inquire information about an interface on the given System module hSystem as defined in	INTERFACE_INFO_CMD without opening the interface.
		\param[in] hSystem	System module to work on.
		\param[in] sIfaceID	Unique ID of the interface to inquire information from. Like with the TLOpenInterface function it is also possible to feed an alternative ID as long as the GenTL Producer knows how to interpret it.
		\param[in] iInfoCmd	Information to be retrieved as defined in INTERFACE_INFO_CMD.
		\param[out] piType	Data type of the pBuffer content as defined in the INTERFACE_INFO_CMD and INFO_DATATYPE.
		\param[in,out] pBuffer	Pointer to a user allocated buffer to receive the requested information. If this parameter is NULL, piSize will contain the minimal size of pBuffer in bytes. If the piType is a string the size includes the terminating 0.
		\param[in,out] piSize	pBuffer equal NULL:
	out: minimal size of pBuffer in bytes to hold all information
	pBuffer unequal NULL:
	in: size of the provided pBuffer in bytes
	out: number of bytes filled by the function
		@return		GC_ERROR value.
	*/
	GC_API_NAME(TLGetInterfaceInfo)
	GC_API_LIST((TL_HANDLE hSystem, const char *sIfaceID, INTERFACE_INFO_CMD iInfoCmd, INFO_DATATYPE *piType, void *pBuffer, size_t *piSize))

	/*!
		\ingroup	GenTL_PublicImple
		\brief Queries the number of available interfaces on this System module.
		\details Queries the number of available interfaces on this System module.
		\param[in] hSystem	System module to work on.
		\param[out] piNumIfaces	Number of interfaces on this System module.
		@return		GC_ERROR value.
	*/
	GC_API_NAME(TLGetNumInterfaces)
	GC_API_LIST((TL_HANDLE hSystem, uint32_t *piNumIfaces))

	/*!
		\ingroup	GenTL_PublicImple
		\brief Opens the System module and puts the instance in the phSystem handle.
		\details Opens the System module and puts the instance in the phSystem handle.
		\param[out] phSystem	System module handle of the newly opened system. It is recommended to initialize *phSystem to GENTL_INVALID_HANDLE before calling TLOpen to indicate an invalid handle.
		@return		GC_ERROR value.
	*/
	GC_API_NAME(TLOpen)
	GC_API_LIST((TL_HANDLE *phSystem))

	/*!
		\ingroup	GenTL_PublicImple
		\brief Opens the given sIfaceID on the given hSystem.
		\details Opens the given sIfaceID on the given hSystem.
		\param[in] hSystem	System module to work on.
		\param[in] sIfaceID	Unique interface ID to open as a 0-terminated C string.
		\param[out] phIface	Interface handle of the newly created interface. It is recommended to initialize *phIface to GENTL_INVALID_HANDLE before calling TLOpenInterface to indicate an invalid handle.
		@return		GC_ERROR value.
	*/
	GC_API_NAME(TLOpenInterface)
	GC_API_LIST((TL_HANDLE hSystem, const char *sIfaceID, IF_HANDLE *phIface))

	/*!
		\ingroup	GenTL_PublicImple
		\brief Updates the internal list of available interfaces. This may change the connection between a list index and an interface ID.
		\details Updates the internal list of available interfaces. This may change the connection between a list index and an interface ID.
		\param[in] hSystem	System module to work on.
		\param[out] pbChanged	Contains true if the internal list was changed and false otherwise. If set to NULL nothing is written to this parameter.
		\param[in] iTimeout	Timeout in ms. If set to GENTL_INFINITE the timeout is infinite and the function will only return after the operation is completed. In any case the GenTL Producer must make sure that this operation is completed in a reasonable amount of time depending on the underlying technology. Please be aware that there is no defined way of terminating such an update operation. On the other hand it is the GenTL Consumer's responsibility to call this function with a reasonable timeout.
		@return		GC_ERROR value.
	*/
	GC_API_NAME(TLUpdateInterfaceList)
	GC_API_LIST((TL_HANDLE hSystem, bool8_t *pbChanged, uint64_t iTimeout))

	/*!
		\ingroup	GenTL_PublicImple
		\brief Closes the Interface module associated with the given hIface handle.
		\details Closes the Interface module associated with the given hIface handle.
		\param[in] hIface	Interface module to work on.
		@return		GC_ERROR value.
	*/
	GC_API_NAME(IFClose)
	GC_API_LIST((IF_HANDLE hIface))

	/*!
		\ingroup	GenTL_PublicImple
		\brief Inquires information about the Interface module as defined in INTERFACE_INFO_CMD.
		\details Inquires information about the Interface module as defined in INTERFACE_INFO_CMD.
		\param[in] hIface	Interface module to work on.
		\param[in] iInfoCmd	Information to be retrieved as defined in INTERFACE_INFO_CMD.
		\param[out] piType	Data type of the pBuffer content as defined in the INTERFACE_INFO_CMD and INFO_DATATYPE.
		\param[in,out] pBuffer	Pointer to a user allocated buffer to receive the requested information. If this parameter is NULL, piSize will contain the minimal size of pBuffer in bytes. If the piType is a string the size includes the terminating 0.
		\param[in,out] piSize	pBuffer equal NULL:
	out: minimal size of pBuffer in bytes to hold all information
	pBuffer unequal NULL:
	in: size of the provided pBuffer in bytes
	out: number of bytes filled by the function
		@return		GC_ERROR value.
	*/
	GC_API_NAME(IFGetInfo)
	GC_API_LIST((IF_HANDLE hIface, INTERFACE_INFO_CMD iInfoCmd, INFO_DATATYPE *piType, void *pBuffer, size_t *piSize))

	/*!
		\ingroup	GenTL_PublicImple
		\brief Queries the unique ID of the device at iIndex in the internal device list.
		\details Queries the unique ID of the device at iIndex in the internal device list.
		\param[in] hIface	Interface module to work on.
		\param[in] iIndex	Zero-based index of the device on this interface.
		\param[in,out] sDeviceID	Pointer to a user allocated C string buffer to receive the Device module ID at the given iIndex. If this parameter is NULL, piSize will contain the needed size of sDeviceID in bytes. The size includes the terminating 0.
		\param[in,out] piSize	sDeviceID equal NULL:
	out: minimal size of sDeviceID in bytes to hold all information
	sDeviceID unequal NULL:
	in: size of the provided sDeviceID in bytes
	out: number of bytes filled by the function
		@return		GC_ERROR value.
	*/
	GC_API_NAME(IFGetDeviceID)
	GC_API_LIST((IF_HANDLE hIface, uint32_t iIndex, char *sDeviceID, size_t *piSize))

	/*!
		\ingroup	GenTL_PublicImple
		\brief Inquires information about a device on the given Interface module hIface as defined in DEVICE_INFO_CMD without the need to open the device.
		\details Inquires information about a device on the given Interface module hIface as defined in DEVICE_INFO_CMD without the need to open the device.
		\param[in] hIface	Interface module to work on.
		\param[in] sDeviceID	Unique ID of the device to inquire information about. Like with the IFOpenDevice function it is also possible to feed an alternative ID as long as the GenTL Producer knows how to interpret it.
		\param[in] iInfoCmd	Information to be retrieved as defined in DEVICE_INFO_CMD.
		\param[out]	piType	Data type of the pBuffer content as defined in the DEVICE_INFO_CMD and INFO_DATATYPE.
		\param[in,out] pBuffer	Pointer to a user allocated buffer to receive the requested information. If this parameter is NULL, piSize will contain the minimal size of pBuffer in bytes. If the piType is a string the size includes the terminating 0.
		\param[in,out] piSize	pBuffer equal NULL:
out: minimal size of pBuffer in bytes to hold all information
pBuffer unequal NULL:
in: size of the provided pBuffer in bytes
out: number of bytes filled by the function
		@return		GC_ERROR value.
	*/
	GC_API_NAME(IFGetDeviceInfo)
	GC_API_LIST((IF_HANDLE hIface, const char *sDeviceID, DEVICE_INFO_CMD iInfoCmd, INFO_DATATYPE *piType, void *pBuffer, size_t *piSize))

	/*!
		\ingroup	GenTL_PublicImple
		\brief Queries the number of available devices on this Interface module.
		\details Queries the number of available devices on this Interface module.
		\param[in] hIface	Interface module to work on.
		\param[out]	piNumDevices	Number of devices on this Interface module.
		@return		GC_ERROR value.
	*/
	GC_API_NAME(IFGetNumDevices)
	GC_API_LIST((IF_HANDLE hIface, uint32_t *piNumDevices))

	/*!
		\ingroup	GenTL_PublicImple
		\brief Opens the given sDeviceID with the given iOpenFlags on the given hIface.
		\details Opens the given sDeviceID with the given iOpenFlags on the given hIface.
		\param[in] hIface	Interface module to work on.
		\param[in] sDeviceID	Unique device ID to open as a 0-terminated C string.
		\param[in] iOpenFlags	Configures the open process as defined in the DEVICE_ACCESS_FLAGS.
		\param[out]	phDevice	Device handle of the newly created Device module. It is recommended to initialize *phDevice to GENTL_INVALID_HANDLE before calling IFOpenDevice to indicate an invalid handle.
		@return		GC_ERROR value.
	*/
	GC_API_NAME(IFOpenDevice)
	GC_API_LIST((IF_HANDLE hIface, const char *sDeviceID, DEVICE_ACCESS_FLAGS iOpenFlags, DEV_HANDLE *phDevice))

	/*!
		\ingroup	GenTL_PublicImple
		\brief Updates the internal list of available devices.
		\details Updates the internal list of available devices.
		\param[in] hIface	Interface module to work on.
		\param[out] pbChanged	Contains true if the internal list was changed and false otherwise. If set to NULL nothing is written to this parameter.
		\param[in] iTimeout	Timeout in ms. If set to GENTL_INFINITE the timeout is infinite and the function will only return if the operation is completed. In any case the GenTL Producer must make sure that this operation is completed in a reasonable amount of time depending on the underlying technology. Please be aware that there is no defined way of terminating such an update operation. On the other hand it is the GenTL Consumer's responsibility to call this function with a reasonable timeout.
		@return		GC_ERROR value.
	*/
	GC_API_NAME(IFUpdateDeviceList)
	GC_API_LIST((IF_HANDLE hIface, bool8_t *pbChanged, uint64_t iTimeout))

	/*!
		\ingroup	GenTL_PublicImple
		\brief Retrieves a handle to the parent TL module.
		\details Retrieves a handle to the parent TL module.
		\param[in] hIface	Interface module to work on.
		\param[out] phSystem	Handle to the parent System module.
		\since GenTL v1.4
		@return		GC_ERROR value.
	*/
	GC_API_NAME(IFGetParentTL)
	GC_API_LIST((IF_HANDLE hIface, TL_HANDLE *phSystem))

	/*!
		\ingroup	GenTL_PublicImple
		\brief Closes the Device module associated with the given hDevice handle.
		\details Closes the Device module associated with the given hDevice handle.
		\param[in] hDevice	Device module handle to close.
		@return		GC_ERROR value.
	*/
	GC_API_NAME(DevClose)
	GC_API_LIST((DEV_HANDLE hDevice))

	/*!
		\ingroup	GenTL_PublicImple
		\brief Inquire information about the Device module as defined in DEVICE_INFO_CMD.
		\details Inquire information about the Device module as defined in DEVICE_INFO_CMD.
		\param[in] hDevice	Device module to work on.
		\param[in] iInfoCmd	Information to be retrieved as defined in DEVICE_INFO_CMD.
		\param[out] piType	Data type of the pBuffer content as defined in the DEVICE_INFO_CMD and INFO_DATATYPE.
		\param[in,out] pBuffer	Pointer to a user allocated buffer to receive the requested information. If this parameter is NULL, piSize will contain the minimal size of pBuffer in bytes. If the piType is a string the size includes the terminating 0.
		\param[in,out] piSize	pBuffer equal NULL:
out: minimal size of pBuffer in bytes to hold all information
pBuffer unequal NULL:
in: size of the provided pBuffer in bytes
out: number of bytes filled by the function
		@return		GC_ERROR value.
	*/
	GC_API_NAME(DevGetInfo)
	GC_API_LIST((DEV_HANDLE hDevice, DEVICE_INFO_CMD iInfoCmd, INFO_DATATYPE *piType, void *pBuffer, size_t *piSize))

	/*!
		\ingroup	GenTL_PublicImple
		\brief Queries the unique ID of the data stream at iIndex in the internal data stream list.
		\details Queries the unique ID of the data stream at iIndex in the internal data stream list.
		\param[in] hDevice	Device module to work on.
		\param[in] iIndex	Zero-based index of the data stream on this device.
		\param[in,out] sDataStreamID	Pointer to a user allocated C string buffer to receive the Interface module ID at the given iIndex. If this parameter is NULL, piSize will contain the needed size of sDataStreamID in bytes. The size includes the terminating 0.
		\param[in,out] piSize	sDataStreamID equal NULL:
	out: minimal size of sDataStreamID in bytes to hold all information
	sDataStreamID unequal NULL:
	in: size of the provided sDataStreamID in bytes
	out: number of bytes filled by the function
		@return		GC_ERROR value.
	*/
	GC_API_NAME(DevGetDataStreamID)
	GC_API_LIST((DEV_HANDLE hDevice, uint32_t iIndex, char *sDataStreamID, size_t *piSize))

	/*!
		\ingroup	GenTL_PublicImple
		\brief Queries the number of available data streams on this Device module.
		\details Queries the number of available data streams on this Device module.
		\param[in] hDevice	Device module to work on.
		\param[out] piNumDataStreams	Number of data stream on this Device module.
		@return		GC_ERROR value.
	*/
	GC_API_NAME(DevGetNumDataStreams)
	GC_API_LIST((DEV_HANDLE hDevice, uint32_t *piNumDataStreams))

	/*!
		\ingroup	GenTL_PublicImple
		\brief Retrieves the port handle for the associated remote device.
		\details Retrieves the port handle for the associated remote device.
		\param[in] hDevice	Device module to work on.
		\param[out] phRemoteDevice	Port handle for the remote device. It is recommended to initialize *phRemoteDev to GENTL_INVALID_HANDLE before calling DevGetPort to indicate an invalid handle.
		@return		GC_ERROR value.
	*/
	GC_API_NAME(DevGetPort)
	GC_API_LIST((DEV_HANDLE hDevice, PORT_HANDLE *phRemoteDevice))

	/*!
		\ingroup	GenTL_PublicImple
		\brief Opens the given sDataStreamID on the given hDevice.
		\details Opens the given sDataStreamID on the given hDevice.
		\param[in] hDevice	Device module to work on.
		\param[in] sDataStreamID	Unique data stream ID to open as a 0-terminated C string.
		\param[out] phDataStream	Data Stream module handle of the newly created stream. It is recommended to initialize *phDataStream to GENTL_INVALID_HANDLE before calling DevOpenDataStream to indicate an invalid handle.
		@return		GC_ERROR value.
	*/
	GC_API_NAME(DevOpenDataStream)
	GC_API_LIST((DEV_HANDLE hDevice, const char *sDataStreamID, DS_HANDLE *phDataStream))

	/*!
		\ingroup	GenTL_PublicImple
		\brief Retrieves a handle to the parent Interface module.
		\details Retrieves a handle to the parent Interface module.
		\param[in] hDevice	Device module to work on.
		\param[out] phIface	Handle to the parent Interface module.
		\since GenTL v1.4
		@return		GC_ERROR value.
	*/
	GC_API_NAME(DevGetParentIF)
	GC_API_LIST((DEV_HANDLE hDevice, IF_HANDLE *phIface))

	/*!
		\ingroup	GenTL_PublicImple
		\brief This function allocates the memory for a single buffer and announces this buffer to the Data Stream associated with the hDataStream handle and returns a hBuffer handle which references that single buffer until the buffer is revoked.
		\details This function allocates the memory for a single buffer and announces this buffer to the Data Stream associated with the hDataStream handle and returns a hBuffer handle which references that single buffer until the buffer is revoked.
		\param[in] hDataStream	Data Stream module to work on.
		\param[in] iBufferSize	Size of the buffer in bytes.
		\param[in] pPrivate	Pointer to private data which will be passed to the GenTL Consumer on New Buffer events. This parameter may be NULL.
		\param[out] phBuffer	Buffer module handle of the newly announced buffer. It is recommended to initialize *phBuffer to GENTL_INVALID_HANDLE before calling DSAllocAndAnnounceBuffer to indicate an invalid handle.
		@return		GC_ERROR value.
	*/
	GC_API_NAME(DSAllocAndAnnounceBuffer)
	GC_API_LIST((DS_HANDLE hDataStream, size_t iBufferSize, void *pPrivate, BUFFER_HANDLE *phBuffer))

	/*!
		\ingroup	GenTL_PublicImple
		\brief This announces a GenTL Consumer allocated memory to the Data Stream associated with the hDataStream handle and returns a hBuffer handle which references that single buffer until the buffer is revoked.
		\details This announces a GenTL Consumer allocated memory to the Data Stream associated with the hDataStream handle and returns a hBuffer handle which references that single buffer until the buffer is revoked.
		\param[in] hDataStream	Data Stream module to work on.
		\param[in] pBuffer	Pointer to buffer memory to announce.
		\param[in] iSize	Size of the pBuffer in bytes.
		\param[in] pPrivate	Pointer to private data which will be passed to the GenTL Consumer on New Buffer events. This parameter may be NULL.
		\param[out] phBuffer	Buffer module handle of the newly announced buffer. It is recommended to initialize *phBuffer to GENTL_INVALID_HANDLE before calling DSAnnounceBuffer to indicate an invalid handle.
		@return		GC_ERROR value.
	*/
	GC_API_NAME(DSAnnounceBuffer)
	GC_API_LIST((DS_HANDLE hDataStream, void *pBuffer, size_t iSize, void *pPrivate, BUFFER_HANDLE *phBuffer))

	/*!
		\ingroup	GenTL_PublicImple
		\brief Closes the Data Stream module associated with the given hDataStream handle.
		\details Closes the Data Stream module associated with the given hDataStream handle.
		\param[in] hDataStream	Data Stream module handle to close.
		@return		GC_ERROR value.
	*/
	GC_API_NAME(DSClose)
	GC_API_LIST((DS_HANDLE hDataStream))

	/*!
		\ingroup	GenTL_PublicImple
		\brief Flushes the by iOperation defined internal buffer pool or queue to another one as defined in ACQ_QUEUE_TYPE.
		\details Flushes the by iOperation defined internal buffer pool or queue to another one as defined in ACQ_QUEUE_TYPE.
		\param[in] hDataStream	Data Stream module to work on.
		\param[in] iOperation	Flush operation to perform as defined in ACQ_QUEUE_TYPE.
		@return		GC_ERROR value.
	*/
	GC_API_NAME(DSFlushQueue)
	GC_API_LIST((DS_HANDLE hDataStream, ACQ_QUEUE_TYPE iOperation))

	/*!
		\ingroup	GenTL_PublicImple
		\brief DSGetBufferID queries the buffer handle for a given index iIndex.
		\details DSGetBufferID queries the buffer handle for a given index iIndex.
		\param[in] hDataStream	Data Stream module to work on.
		\param[in] iIndex	Zero-based index of the buffer on this data stream.
		\param[in,out] phBuffer	Buffer module handle of the given iIndex.
		@return		GC_ERROR value.
	*/
	GC_API_NAME(DSGetBufferID)
	GC_API_LIST((DS_HANDLE hDataStream, uint32_t iIndex, BUFFER_HANDLE *phBuffer))
	
	/*!
		\ingroup	GenTL_PublicImple
		\brief Inquire information about the Buffer module associated with hBuffer on the hDataStream instance as defined in BUFFER_INFO_CMD.
		\details Inquire information about the Buffer module associated with hBuffer on the hDataStream instance as defined in BUFFER_INFO_CMD.
		\param[in] hDataStream	Data Stream module to work on.
		\param[in] hBuffer	Buffer handle to retrieve information about.
		\param[in] iInfoCmd	Information to be retrieved as defined in BUFFER_INFO_CMD.
		\param[out] piType	Data type of the pBuffer content as defined in the BUFFER_INFO_CMD and INFO_DATATYPE.
		\param[in,out] pBuffer	Pointer to a user allocated buffer to receive the requested information. If this parameter is NULL, piSize will contain the minimal size of pBuffer in bytes. If the piType is a string the size includes the terminating 0.
		\param[in,out] piSize	pBuffer equal NULL:
	out: minimal size of pBuffer in bytes to hold all information.
	pBuffer unequal NULL:
	in: size of the provided pBuffer in bytes.
	out: number of bytes filled by the function.
		@return		GC_ERROR value.
	*/
	GC_API_NAME(DSGetBufferInfo)
	GC_API_LIST((DS_HANDLE hDataStream, BUFFER_HANDLE hBuffer, BUFFER_INFO_CMD iInfoCmd, INFO_DATATYPE *piType, void *pBuffer, size_t *piSize))

	/*!
		\ingroup	GenTL_PublicImple
		\brief Inquires information about the Data Stream module associated with hDataStream as defined in STREAM_INFO_CMD.
		\details Inquires information about the Data Stream module associated with hDataStream as defined in STREAM_INFO_CMD.
		\param[in] hDataStream	Data Stream module to work on.
		\param[in] iInfoCmd	Information to be retrieved as defined in STREAM_INFO_CMD.
		\param[out] piType	Data type of the pBuffer content as defined in the STREAM_INFO_CMD and INFO_DATATYPE.
		\param[in,out] pBuffer	Pointer to a user allocated buffer to receive the requested information. If this parameter is NULL, piSize will contain the minimal size of pBuffer in bytes. If the piType is a string the size includes the terminating 0.
		\param[in,out] piSize	pBuffer equal NULL:
	out: minimal size of pBuffer in bytes to hold all information.
	pBuffer unequal NULL:
	in: size of the provided pBuffer in bytes.
	out: number of bytes filled by the function.
		@return		GC_ERROR value.
	*/
	GC_API_NAME(DSGetInfo)
	GC_API_LIST((DS_HANDLE hDataStream, STREAM_INFO_CMD iInfoCmd, INFO_DATATYPE *piType, void *pBuffer, size_t *piSize))

	/*!
		\ingroup	GenTL_PublicImple
		\brief This function queues a particular buffer for acquisition.
		\details This function queues a particular buffer for acquisition.
		\param[in] hDataStream	Data Stream module to work on.
		\param[in] hBuffer	Buffer handle to queue.
		@return		GC_ERROR value.
	*/
	GC_API_NAME(DSQueueBuffer)
	GC_API_LIST((DS_HANDLE hDataStream, BUFFER_HANDLE hBuffer))

	/*!
		\ingroup	GenTL_PublicImple
		\brief Removes an announced buffer from the acquisition engine.
		\details Removes an announced buffer from the acquisition engine.
		\param[in] hDataStream	Data Stream module to work on.
		\param[in] hBuffer	Buffer handle to revoke.
		\param[out] ppBuffer	Pointer to the buffer memory. This is for convenience if GenTL Consumer allocated memory is used which is to be freed. If the buffer was allocated by the GenTL Producer NULL is to be returned. If the parameter is set to NULL it is ignored.
		\param[out] ppPrivate	Pointer to the user data pointer given in the announce function. If the parameter is set to NULL it is ignored.
		@return		GC_ERROR value.
	*/
	GC_API_NAME(DSRevokeBuffer)
	GC_API_LIST((DS_HANDLE hDataStream, BUFFER_HANDLE hBuffer, void **ppBuffer, void **ppPrivate))

	/*!
		\ingroup	GenTL_PublicImple
		\brief Starts the acquisition engine on the host.
		\details Starts the acquisition engine on the host.
		\param[in]	hDataStream	Data Stream module to work on.
		\param[in]	iStartFlags	As defined in ACQ_START_FLAGS.
		\param[in]	iNumToAcquire	Sets the number of filled/delivered buffers after which the acquisition engine stops automatically. Buffers which are internally discarded or missed are not counted. If set to GENTL_INFINITE the acquisition continues until a call to DSStopAcquisition is issued. If set to 0 a GC_ERR_INVALID_PARAMETER is returned.
		@return		GC_ERROR value.
	*/
	GC_API_NAME(DSStartAcquisition)
	GC_API_LIST((DS_HANDLE hDataStream, ACQ_START_FLAGS iStartFlags, uint64_t iNumToAcquire))

	/*!
		\ingroup	GenTL_PublicImple
		\brief Stops the acquisition engine on the host.
		\details Stops the acquisition engine on the host.
		\param[in] hDataStream	Data Stream module to work on.
		\param[in]	iStopFlags	Stops the acquisition as defined in ACQ_STOP_FLAGS.
		@return		GC_ERROR value.
	*/
	GC_API_NAME(DSStopAcquisition)
	GC_API_LIST((DS_HANDLE hDataStream, ACQ_STOP_FLAGS iStopFlags))

	/*!
		\ingroup	GenTL_PublicImple
		\brief DSGetBufferChunkData parses the transport layer technology dependent chunk data info in the buffer.
		\details DSGetBufferChunkData parses the transport layer technology dependent chunk data info in the buffer.
		\param[in] hDataStream	Data Stream module to work on.
		\param[in]	hBuffer	Buffer handle to parse.
		\param[out]	pChunkData	User allocated array of structures to receive the chunk layout information. If this parameter is NULL, piNumChunks will contain the number of chunks in the buffer, e.g., the minimal number of entries in the pChunkData array.
		\param[in,out]	piNumChunks	pChunkData equal NULL: out: number of chunks in the buffer (minimal number of entries in the pChunkData array to hold all information). pChunkData unequal NULL: in: number of entries in the provided pChunkData array. out: number of entries successfully written to the pChunkData array.
		@return		GC_ERROR value.
		\since GenTL v1.3
	*/
	GC_API_NAME(DSGetBufferChunkData)
	GC_API_LIST((DS_HANDLE hDataStream, BUFFER_HANDLE hBuffer, SINGLE_CHUNK_DATA *pChunkData, size_t *piNumChunks))

	/*!
		\ingroup	GenTL_PublicImple
		\brief Retrieves a handle to the parent Device module.
		\details Retrieves a handle to the parent Device module.
		\param[in] hDataStream	Data Stream module to work on.
		\param[in]	phDevice	Handle to the parent Device module.
		@return		GC_ERROR value.
		\since GenTL v1.4
	*/
	GC_API_NAME(DSGetParentDev)
	GC_API_LIST((DS_HANDLE hDataStream, DEV_HANDLE *phDevice))

	/*!
		\ingroup	GenTL_PublicImple
		\brief Inquires the number of independent data parts in the buffer.
		\details Inquires the number of independent data parts in the buffer.
		\param[in] hDataStream	Data Stream module to work on.
		\param[in]	hBuffer	Buffer handle to retrieve information about.
		\param[out]	piNumParts	Number of independent data parts in the buffer. The reported number may be 0 in case the referenced buffer carries a multipart buffer payload but for some reason the number of parts is buffer is 0.
		@return		GC_ERROR value.
		\since GenTL v1.5
	*/
	GC_API_NAME(DSGetNumBufferParts)
	GC_API_LIST((DS_HANDLE hDataStream, BUFFER_HANDLE hBuffer, uint32_t *piNumParts))

	/*!
		\ingroup	GenTL_PublicImple
		\brief Inquires information about individual data parts of the buffer encapsulated in the Buffer module associated with hBuffer on the hDataStream instance as defined in BUFFER_PART_INFO_CMD.
		\details Inquires information about individual data parts of the buffer encapsulated in the Buffer module associated with hBuffer on the hDataStream instance as defined in BUFFER_PART_INFO_CMD.
		\param[in] hDataStream	Data Stream module to work on.
		\param[in]	hBuffer	Buffer handle to retrieve information about.
		\param[in]	iPartIndex	Zero based index of the buffer part to query.
		\param[in]	iInfoCmd	Information to be retrieved as defined in BUFFER_PART_INFO_CMD.
		\param[out]	piType	Data type of the pBuffer content as defined in the BUFFER_PART_INFO_CMD and INFO_DATATYPE.
		\param[in,out]	pBuffer	Pointer to a user allocated buffer to receive the requested information. If this parameter is NULL, piSize will contain the minimal size of pBuffer in bytes. If the piType is a string the size includes the terminating 0.
		\param[in,out]	piSize	pBuffer equal NULL: out: minimal size of pBuffer in bytes to hold all information. pBuffer unequal NULL: in: size of the provided pBuffer in bytes. out: number of bytes filled by the function.
		@return		GC_ERROR value.
		\since GenTL v1.5
	*/
	GC_API_NAME(DSGetBufferPartInfo)
	GC_API_LIST((DS_HANDLE hDataStream, BUFFER_HANDLE hBuffer, uint32_t iPartIndex, BUFFER_PART_INFO_CMD iInfoCmd, INFO_DATATYPE *piType, void *pBuffer, size_t *piSize))

	/*!
		\ingroup	GenTL_PublicImple
		\brief Queries detailed port information as defined in PORT_INFO_CMD.
		\details Queries detailed port information as defined in PORT_INFO_CMD.
		\param[in]	hPort	Module or remote device port handle to access Port from.
		\param[in]	iInfoCmd	Information to be retrieved as defined in PORT_INFO_CMD.
		\param[out]	piType	Data type of the pBuffer content as defined in the PORT_INFO_CMD and INFO_DATATYPE.
		\param[in,out]	pBuffer	Pointer to a user allocated buffer to receive the requested information. If this parameter is NULL, piSize will contain the minimal size of pBuffer in bytes. If the piType is a string the size includes the terminating 0.
		\param[in,out]	piSize	pBuffer equal NULL:
	out: minimal size of pBuffer in bytes to hold all information.
	pBuffer unequal NULL:
	in: size of the provided pBuffer in bytes.
	out: number of bytes filled by the function.
		@return		GC_ERROR value.
	*/
	GC_API_NAME(GCGetPortInfo)
	GC_API_LIST((PORT_HANDLE hPort, PORT_INFO_CMD iInfoCmd, INFO_DATATYPE *piType, void *pBuffer, size_t *piSize))

	/*!
		\ingroup	GenTL_PublicImple
		\brief GCGetPortURL retrieves a URL list with the XML description for the given hPort.
		\details GCGetPortURL retrieves a URL list with the XML description for the given hPort.
		\param[in]	hPort	Module or remote device port handle to access Port from.
		\param[in,out]	sURL	Pointer to a user allocated string buffer to receive the list of URLs If this parameter is NULL, piSize will contain the needed size of sURL in bytes. Each entry in the list is 0 terminated. After the last entry there is an additional 0. The size includes the terminating 0 characters.
		\param[in,out]	piSize	sURL equal NULL:
	out: minimal size of sURL in bytes to hold all information.
	sURL unequal NULL:
	in: size of the provided sURL in bytes.
	out: number of bytes filled by the function.
		@return		GC_ERROR value.
	*/
	GC_API_NAME(GCGetPortURL)
	GC_API_LIST((PORT_HANDLE hPort, char *sURL, size_t *piSize))

	/*!
		\ingroup	GenTL_PublicImple
		\brief Inquires the number of available URLs for this port.
		\details Inquires the number of available URLs for this port.
		\param[in]	hPort	Module or remote device port handle to access Port from.
		\param[out]	piNumURLs	Number of available URL entries.
		@return		GC_ERROR value.
		\since GenTL v1.1
	*/
	GC_API_NAME(GCGetNumPortURLs)
	GC_API_LIST((PORT_HANDLE hPort, uint32_t *piNumURLs))

	/*!
		\ingroup	GenTL_PublicImple
		\brief Queries detailed port information as defined in URL_INFO_CMD.
		\details Queries detailed port information as defined in URL_INFO_CMD.
		\param[in]	hPort	Module or remote device port handle to access Port from.
		\param[in]	iURLIndex	Zero based index of the URL to query.
		\param[in]	iInfoCmd	Information to be retrieved as defined in URL_INFO_CMD.
		\param[out]	piType	Data type of the pBuffer content as defined in the URL URL_INFO_CMD and INFO_DATATYPE.
		\param[in,out]	pBuffer	Pointer to a user allocated buffer to receive the requested information. If this parameter is NULL, piSize will contain the minimal size of pBuffer in bytes. If the piType is a string the size includes the terminating 0.
		\param[in,out]	piSize equal NULL: out: minimal size of pBuffer in bytes to hold all information. pBuffer unequal NULL: in: size of the provided pBuffer in bytes. out: number of bytes filled by the function.
		@return		GC_ERROR value.
		\since GenTL v1.1
	*/
	GC_API_NAME(GCGetPortURLInfo)
	GC_API_LIST((PORT_HANDLE hPort, uint32_t iURLIndex, URL_INFO_CMD iInfoCmd, INFO_DATATYPE *piType, void *pBuffer, size_t *piSize))

	/*!
		\ingroup	GenTL_PublicImple
		\brief Reads a number of bytes from a given iAddress from the specified hPort.
		\details Reads a number of bytes from a given iAddress from the specified hPort.
		\param[in]	hPort	Module or remote device port handle to access Port from.
		\param[in]	iAddress	Byte address to read from.
		\param[out]	pBuffer	Pointer to a user allocated byte buffer to receive data.
		\param[in,out]	piSize	Size of the provided pBuffer and thus the amount of bytes to read from the register map; after the read operation this parameter holds the information about the bytes actually read.
		@return		GC_ERROR value.
	*/
	GC_API_NAME(GCReadPort)
	GC_API_LIST((PORT_HANDLE hPort, uint64_t iAddress, void *pBuffer, size_t *piSize))

	/*!
		\ingroup	GenTL_PublicImple
		\brief Writes a number of bytes at the given iAddress to the specified hPort.
		\details Writes a number of bytes at the given iAddress to the specified hPort.
		\param[in]	hPort	Module or remote device port handle to access Port from.
		\param[in]	iAddress	Byte address to write to.
		\param[in]	pBuffer	Pointer to a user allocated byte buffer containing the data to write.
		\param[in,out]	piSize	Size of the provided pBuffer and thus the amount of bytes to write to the register map; after the write operation this parameter holds the information about the bytes actually written.
		@return		GC_ERROR value.
	*/
	GC_API_NAME(GCWritePort)
	GC_API_LIST((PORT_HANDLE hPort, uint64_t iAddress, const void *pBuffer, size_t *piSize))

	/*!
		\ingroup	GenTL_PublicImple
		\brief Writes a number of bytes to the given address on the specified hPort for every element in the pEntries array.
		\details Writes a number of bytes to the given address on the specified hPort for every element in the pEntries array.
		\param[in]	hPort	Module or remote device port handle to access Port from.
		\param[in]	pEntries	Array of structures containing write address and data to write.
		\param[in,out]	piNumEntries	In: Number of entries in the array, Out: Number of successful executed writes according to the entries in the pEntries array.
		@return		GC_ERROR value.
		\since GenTL v1.1
	*/
	GC_API_NAME(GCWritePortStacked)
	GC_API_LIST((PORT_HANDLE hPort, PORT_REGISTER_STACK_ENTRY *pEntries, size_t *piNumEntries))

	/*!
		\ingroup	GenTL_PublicImple
		\brief Reads a number of bytes from the given address on the specified hPort for every element in the pEntries array.
		\details Reads a number of bytes from the given address on the specified hPort for every element in the pEntries array.
		\param[in]	hPort	Module or remote device port handle to access Port from.
		\param[in]	pEntries	Array of structures containing read address and data to read.
		\param[in,out]	piNumEntries	In: Number of entries in the array, Out: Number of successful executed reads according to the entries in the pEntries array.
		@return		GC_ERROR value.
		\since GenTL v1.1
	*/
	GC_API_NAME(GCReadPortStacked)
	GC_API_LIST((PORT_HANDLE hPort, PORT_REGISTER_STACK_ENTRY *pEntries, size_t *piNumEntries))

	/*!
		\ingroup	GenTL_PublicImple
		\brief Flushes all events in the given hEvent object.
		\details Flushes all events in the given hEvent object.
		\param[in]	hEvent	Event handle to flush queue on.
		@return		GC_ERROR value.
	*/
	GC_API_NAME(EventFlush)
	GC_API_LIST((EVENT_HANDLE hEvent))

	/*!
		\ingroup	GenTL_PublicImple
		\brief Retrieves the next event data entry from the event data queue associated with the hEvent.
		\details Retrieves the next event data entry from the event data queue associated with the hEvent.
		\param[in]	hEvent	Event handle to wait for.
		\param[out]	pBuffer	Pointer to a user allocated buffer to receive the event data. The data type of the buffer is dependent on the event ID of the hEvent. If this value is NULL the data is removed from the queue without being delivered. In case of a New Buffer Event being retrieved with pBuffer equals NULL the buffer is removed from the output queue and not requeued.
		\param[in,out]	piSize	Size of the provided pBuffer in bytes; after the write operation this parameter holds the information about the bytes actually written.
		\param[in]	iTimeout	Timeout for the wait in ms. If set to GENTL_INFINITE the timeout is infinite and the function will only return if the operation is completed or if EventKill is called on this event object. A value of 0 checks the state of the event object and returns immediately either with a timeout or with event data.
		@return		GC_ERROR value.
	*/
	GC_API_NAME(EventGetData)
	GC_API_LIST((EVENT_HANDLE hEvent, void *pBuffer, size_t *piSize, uint64_t iTimeout))

	/*!
		\ingroup	GenTL_PublicImple
		\brief Parses the transport layer technology dependent event info.
		\details Parses the transport layer technology dependent event info.
		\param[in]	hEvent	Event handle to parse data from.
		\param[in]	pInBuffer	Pointer to a buffer containing event data. This value must not be NULL.
		\param[in]	iInSize	Size of the provided pInBuffer in bytes.
		\param[in]	iInfoCmd	Information to be retrieved as defined in EVENT_DATA_INFO_CMD and EVENT_TYPE.
		\param[out]	piType	Data type of the pOutBuffer content as defined in the EVENT_DATA_INFO_CMD, EVENT_TYPE and INFO_DATATYPE.
		\param[in,out]	pOutBuffer	Pointer to a user allocated buffer to receive the requested information. If this parameter is NULL, piOutSize will contain the minimal size of pOutBuffer in bytes. If the piType is a string the size includes the terminating 0.
		\param[in,out]	piOutSize	pOutBuffer equal NULL:
	out: minimal size of pOutBuffer in bytes to hold all
	information.
	pOutBuffer unequal NULL:
	in: size of the provided pOutBuffer in bytes.
	out: number of bytes filled by the function.
		@return		GC_ERROR value.
	*/
	GC_API_NAME(EventGetDataInfo)
	GC_API_LIST((EVENT_HANDLE hEvent, const void *pInBuffer, size_t iInSize, EVENT_DATA_INFO_CMD iInfoCmd, INFO_DATATYPE *piType, void *pOutBuffer, size_t *piOutSize))

	/*!
		\ingroup	GenTL_PublicImple
		\brief Retrieves information about the given hEvent object as defined in EVENT_INFO_CMD.
		\details Retrieves information about the given hEvent object as defined in EVENT_INFO_CMD.
		\param[in]	hEvent	Event handle to retrieve info from.
		\param[in]	iInfoCmd	Information to be retrieved as defined in EVENT_INFO_CMD.
		\param[out]	piType	Data type of the pBuffer content as defined in the EVENT_INFO_CMD and INFO_DATATYPE.
		\param[in,out]	pBuffer	Pointer to a user allocated buffer to receive the requested information. If this parameter is NULL, piSize will contain the minimal size of pBuffer in bytes. If the piType is a string the size includes the terminating 0.
		\param[in,out]	piSize	pBuffer equal NULL:
	out: minimal size of pBuffer in bytes to hold all information
	pBuffer unequal NULL:
	in: size of the provided pBuffer in bytes
	out: number of bytes filled by the function
		@return		GC_ERROR value.
	*/
	GC_API_NAME(EventGetInfo)
	GC_API_LIST((EVENT_HANDLE hEvent, EVENT_INFO_CMD iInfoCmd, INFO_DATATYPE *piType, void *pBuffer, size_t *piSize))

	/*!
		\ingroup	GenTL_PublicImple
		\brief Terminates a waiting operation on a previously registered event object.
		\details Terminates a waiting operation on a previously registered event object.
		\param[in]	hEvent	Handle to event object.
		@return		GC_ERROR value.
	*/
	GC_API_NAME(EventKill)
	GC_API_LIST((EVENT_HANDLE hEvent))

	/*!
		\ingroup	GenTL_PublicImple
		\brief Registers an event object to a certain iEventID.
		\details Registers an event object to a certain iEventID.
		\param[in]	hModule	Module handle to access to register event to.
		\param[in]	iEventID	Event type to register as defined in EVENT_TYPE.
		\param[out]	phEvent	New handle to an event object to work with. It is recommended to initialize *phEvent to GENTL_INVALID_HANDLE before calling GCRegisterEvent to indicate an invalid handle.
		@return		GC_ERROR value.
	*/
	GC_API_NAME(GCRegisterEvent)
	GC_API_LIST((EVENTSRC_HANDLE hModule, EVENT_TYPE iEventID, EVENT_HANDLE *phEvent))

	/*!
		\ingroup	GenTL_PublicImple
        \brief A call to this function will unregister the given iEventID from the given hModule.
		\details A call to this function will unregister the given iEventID from the given hModule.
		\param[in]	hModule	Module handle to unregister event with.
		\param[in]	iEventID	Event type to unregister as defined in EVENT_TYPE.
		@return		GC_ERROR value.
	*/
	GC_API_NAME(GCUnregisterEvent)
	GC_API_LIST((EVENTSRC_HANDLE hModule, EVENT_TYPE iEventID))

#ifdef GC_API_DEF
#ifdef __cplusplus

}
#endif /* __cplusplus */
#undef GC_API_DEF
#endif /* GC_API_DEF */

#undef GC_API_LIST
#undef GC_API_NAME




