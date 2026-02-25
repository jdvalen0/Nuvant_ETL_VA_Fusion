/*
 StApi
*/
/*!
	@file
	@~english	@details	Defines platform specific parameter
	@~japanese	@details		
*/
#ifndef STAPI_PLATFORM_H__
#define STAPI_PLATFORM_H__


#if defined (_MSC_VER) && defined (_WIN32)

/* Windows */
#define ST_BUILD_WINDOWS
#define APIEXPORT __declspec(dllexport)
#define APIIMPORT __declspec(dllimport)
#define PUBLIC_INTERFACE
#define ST_API_CALL_TYPE	__stdcall

#elif defined(__GNUC__) && (defined(__linux__) || defined(__APPLE__))

/* Linux */
#ifdef __APPLE__
#   define ST_BUILD_APPLE
#else
#   define ST_BUILD_LINUX
#endif
#define APIEXPORT __attribute__((visibility("default")))
#define APIIMPORT __attribute__((visibility("default")))
#define PUBLIC_INTERFACE __attribute__((visibility("default")))
#define ST_API_CALL_TYPE 
typedef void* HWND;
typedef void* HDC;
#else
#error Unknown platform
#endif


#ifdef STSDK_TL_EXPORTS
#define ST_API_TL APIEXPORT
#define ST_API_BASE APIEXPORT
#else
#define ST_API_TL APIIMPORT
#endif

#ifdef STSDK_IP_EXPORTS
#define ST_API_IP APIEXPORT
#define ST_API_BASE APIEXPORT
#else
#define ST_API_IP APIIMPORT
#endif

#ifdef STSDK_GUI_EXPORTS
#define ST_API_GUI APIEXPORT
#define ST_API_BASE APIEXPORT
#else
#define ST_API_GUI APIIMPORT
#endif

#ifndef ST_API_BASE
#define ST_API_BASE APIIMPORT
#endif /* ST_API_BASE */


#endif /* STAPI_PLATFORM_H__ */

