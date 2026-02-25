//------------------------------------------------------------------------------
// StApi
//------------------------------------------------------------------------------
/*!
	@ingroup	StApiTL_PublicImpl
	@file	StApi_Utilities.h
	@~english	@details	
	@~japanese	@details	
*/
#ifndef STAPI_UTILITIES_H__
#define STAPI_UTILITIES_H__


namespace StApi
{
#ifdef _UNICODE
#define _GCSTRING_2_LPCTSTR(str)		((str).w_str().c_str())
#else
#define _GCSTRING_2_LPCTSTR(str)		((str).c_str())
#endif
	/*!
		@ingroup	StApiTL_PublicImpl
		@def GCSTRING_2_LPCTSTR(str)
		@~english	@details	Convert GenICam::gcstring type to LPCTSTR.
		@~japanese	@details	GenICam::gcstring 文字列を LPCTSTR へ変換します。
	*/
#define GCSTRING_2_LPCTSTR(str)		_GCSTRING_2_LPCTSTR(str)
}

#endif //STAPI_UTILITIES_H__

