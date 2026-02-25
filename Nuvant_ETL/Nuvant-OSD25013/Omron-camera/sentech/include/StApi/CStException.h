//------------------------------------------------------------------------------
//  StApi
//------------------------------------------------------------------------------
/*!
	@ingroup	StApiTL_PublicImpl
	@file	CStException.h
	@~english	@details	Declaration of CStGenTLErrorException and other related exception classes
	@~japanese	@details	クラス CStGenTLErrorException およびクラス CStWin32ErrorException の定義
*/
#ifndef STAPI_EXCEPTION_H__
#define STAPI_EXCEPTION_H__

#include "StApi_Platform.h"
#include <GenICam.h>

#ifdef _MSC_VER
#pragma warning(push)	
#pragma warning(disable : 4819)	
#include "StGenTL_Def.h"
#pragma warning(pop)	
#else
#include "StGenTL_Def.h"
#endif

namespace StApi
{
	//---------------------------------------------------------------------
	// class CStGenTLErrorException
	//---------------------------------------------------------------------
	/*!
		@ingroup	StApiTL_PublicImpl
		@brief	@~english	This class is for exception handling when GenTL API error occurred.
					@~japanese	GenTLエラー用例外用クラス
		@details	@~english	This class is for exception handling when GenTL API error occurred.
				@~japanese	GenTLエラー用例外用クラス
	*/
	class ST_API_TL CStGenTLErrorException : public GenICam::GenericException
	{
	public:
		CStGenTLErrorException(GenTL::GC_ERROR, const char *pFunctionName, const char* pDescription, const char *pSourceFileName, int SourceLine, const char* pExceptionType);

		virtual ~CStGenTLErrorException() {};

		/*!
			@~english	@brief	Acquire the called function name of GenTL Api.
			@~english	@details	Acquire the called function name of GenTL Api.
			@~english	@return	Function name of GenTL Api.
			@~english	@exception	None.
			@~japanese	@brief	エラーが発生したGenTLの関数名を取得します。
			@~japanese	@details	エラーが発生したGenTLの関数名を取得します。
			@~japanese	@return	エラーが発生したGenTLの関数名
			@~japanese	@exception	なし
		*/
		virtual GenICam::gcstring GetFunctionName() const throw();

		/*!
			@~english	@brief	Acquire error code of GenTL.
			@~english	@details	Acquire error code of GenTL.
			@~english	@return	Error code of GenTL.
			@~english	@exception	None.
			@~japanese	@brief	GenTLのエラーコードを取得します。
			@~japanese	@details	GenTLのエラーコードを取得します。
			@~japanese	@return	GenTLのエラーコード
			@~japanese	@exception	なし
		*/
		virtual GenTL::GC_ERROR GetError() const throw();
	private:
		GenICam::gcstring m_FunctionName;
		GenTL::GC_ERROR m_GenTLError;
	};

#ifdef _WIN32
	//---------------------------------------------------------------------
	// class CStWin32ErrorException
	//---------------------------------------------------------------------
	/*!
		@ingroup	StApiTL_PublicImpl
		@~english	@brief	This class is for exception handling when Win32 API error occurred.
		@~english	@details	This class is for exception handling when Win32 API error occurred.
		@~japanese	@brief	Win32 APIエラー用例外用クラス
		@~japanese	@details	Win32 APIエラー用例外用クラス
	*/
	class ST_API_TL CStWin32ErrorException : public GenICam::GenericException
	{
	public:
		CStWin32ErrorException(HRESULT, const char *pFunctionName, const char* pDescription, const char *pSourceFileName, int SourceLine, const char* pExceptionType);

		virtual ~CStWin32ErrorException() {};

		/*!
			@copydoc	CStGenTLErrorException::GetFunctionName()
		*/
		virtual GenICam::gcstring GetFunctionName() const throw();

		/*!
			@copydoc	CStGenTLErrorException::GetError()
		*/
		virtual HRESULT GetError() const throw();
	private:
		GenICam::gcstring m_FunctionName;
		HRESULT m_Win32Error;
	};
#elif defined(__linux__)
	//---------------------------------------------------------------------
	// class CStLinuxErrorException
	//---------------------------------------------------------------------
	/*!
		@ingroup	StApiTL_PublicImpl
		@~english	@brief	This class is for exception handling when Linux related error occurred.
		@~english	@details	This class is for exception handling when Linux related error occurred.
		@~japanese	@brief	Linux関連エラー用例外用クラス
		@~japanese	@details	Linux関連エラー用例外用クラス
	*/
    class ST_API_TL CStLinuxErrorException : public GenICam::GenericException
    {
    public:
        CStLinuxErrorException(int, const char *pFunctionName, const char* pDescription, const char *pSourceFileName, int SourceLine, const char* pExceptionType);

		virtual ~CStLinuxErrorException() {};

        /*!
            @copydoc    CStGenTLErrorException::GetFunctionName()
        */
        virtual GenICam::gcstring GetFunctionName() const throw();

        /*!
            @copydoc    CStGenTLErrorException::GetError()
        */
        virtual int GetError() const throw();
    private:
		GenICam::gcstring m_FunctionName;
        int m_LinuxError;
    };
#elif defined(__APPLE__)
	//---------------------------------------------------------------------
	// class CStOSXErrorException
	//---------------------------------------------------------------------
	/*!
		@ingroup	StApiTL_PublicImpl
		@~english	@brief	This class is for exception handling when OS X related error occurred.
		@~english	@details	This class is for exception handling when OS X related error occurred.
		@~japanese	@brief	OS X関連エラー用例外用クラス
		@~japanese	@details	OS X関連エラー用例外用クラス
	*/
    class ST_API_TL CStOSXErrorException : public GenICam::GenericException
    {
    public:
        CStOSXErrorException(int, const char *pFunctionName, const char* pDescription, const char *pSourceFileName, int SourceLine, const char* pExceptionType);

		virtual ~CStOSXErrorException() {};

        /*!
            @copydoc    CStGenTLErrorException::GetFunctionName()
        */
        virtual GenICam::gcstring GetFunctionName() const throw();

        /*!
            @copydoc    CStGenTLErrorException::GetError()
        */
        virtual int GetError() const throw();
    private:
		GenICam::gcstring m_FunctionName;
        int m_OSXError;
    };
#endif
}

#endif //STAPI_EXCEPTION_H__
