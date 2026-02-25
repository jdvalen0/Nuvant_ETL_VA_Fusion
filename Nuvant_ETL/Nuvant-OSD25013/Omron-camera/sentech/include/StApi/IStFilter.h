//------------------------------------------------------------------------------
//  StApi
//------------------------------------------------------------------------------
/*!
	@ingroup	StApiIP_PublicInterface
	@file	
	@~english	@details	Definition of interface IStFilter
	@~japanese	@details	IStFilter インターフェースの定義
*/
#ifndef ISTFILTER_H
#define ISTFILTER_H

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
	// interface IStFilterInfo
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiIP_PublicInterface
		@interface IStFilterInfo
		@~english	@brief	Interface for FilterInfo.
		@~english	@details	Interface for FilterInfo.
		@sa	GetIStFilterInfo()
		@~japanese	@brief	フィルター情報用インターフェース
		@~japanese	@details	フィルター情報用インターフェース
		@sa	GetIStFilterInfo()
	*/
	interface PUBLIC_INTERFACE IStFilterInfo
	{
		/*!
			@~english	@brief	Acquire filter type.
			@~english	@details	Acquire filter type.
			@~english	@return	Filter type.
			@~english	@exception	None.
			@~japanese	@brief	フィルタータイプを取得します。
			@~japanese	@details	フィルタータイプを取得します。
			@~japanese	@return	フィルタータイプ
			@~japanese	@exception	なし
		*/
		virtual EStFilterType_t GetFilterType() const = 0;

		/*!
			@~english	@brief	Acquire filter name.
			@~english	@details	Acquire filter name.
			@~english	@return	Filter name.
			@~english	@exception	None.
			@~japanese	@brief	フィルター名を取得します。
			@~japanese	@details	フィルター名を取得します。
			@~japanese	@return	フィルター名
			@~japanese	@exception	なし
		*/
		virtual GenICam::gcstring GetFilterName() const = 0;

		/*!
			@~english	@brief	Check if the pixel format is supported.
			@~english	@details	    Check if the pixel format is supported.
			@~english	@param[in]	nValue	Pixel format.
			@~english	@return	Return true if the pixel format is supported.
			@~english	@exception	None.
			@~japanese	@brief	指定したピクセルフォーマットに対応しているかどうか確認します。
			@~japanese	@details	指定したピクセルフォーマットに対応しているかどうか確認します。
			@~japanese	@param[in]	nValue	ピクセルフォーマット
			@~japanese	@return	対応している場合、 true が返されます。
			@~japanese	@exception	なし
		*/
		virtual bool IsSupported(EStPixelFormatNamingConvention_t nValue) const = 0;
	};

	interface IStImage;

	// ---------------------------------------------------------------------
	// interface IStFilter
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiIP_PublicInterface
		@interface IStFilter
		@~english	@brief	Interface for Filter.
		@~english	@details	Interface for Filter.
		@sa	CreateIStFilter(), GetIStFilterInfo()
		@~japanese	@brief	フィルター用インターフェース
		@~japanese	@details	フィルター用インターフェース
		@sa	CreateIStFilter(), GetIStFilterInfo()
	*/
	interface PUBLIC_INTERFACE IStFilter : public IStRegisterCallback
	{
		/*!
			@~english	@brief	Acquire IStFilterInfo interface pointer.
			@~english	@details	Acquire IStFilterInfo interface pointer.
			@~english	@return	IStFilterInfo interface pointer.
			@~english	@exception	None.
			@~japanese	@brief	IStFilterInfo インターフェースポインターを取得します。
			@~japanese	@details	IStFilterInfo インターフェースポインターを取得します。
			@~japanese	@return	IStFilterInfo インターフェースポインター
			@~japanese	@exception	なし
		*/
		virtual IStFilterInfo *GetIStFilterInfo() const = 0;

		/*!
			@~english	@brief	Apply filter to the input image data. The result will overwrite the input buffer.
			@~english	@details      Apply filter to the input image data. The result will overwrite the input buffer.
			@~english	@param[in]	pImage	Input image buffer.
			@~english	@return	IStImage output image buffer (the same as the input data).
			@~english	@exception	None.
			@~japanese	@brief	フィルター処理を実行します。入力した画像は処理後の画像で上書きされます。
			@~japanese	@details	フィルター処理を実行します。入力した画像は処理後の画像で上書きされます。
			@~japanese	@param[in]	pImage	入力画像の IStImage インターフェースポインター
			@~japanese	@return	処理後の画像の IStImage インターフェースポインター(入力されたものと同じ)
			@~japanese	@exception	なし
		*/
		virtual IStImage *Filter(IStImage *pImage) = 0;

		/*!
			@~english	@brief	Acquire INodeMap interface pointer.
			@~english	@details	Acquire INodeMap interface pointer.
			@~english	@return	INodeMap interface pointer.
			@~english	@exception	None.
			@~japanese	@brief	INodeMap インターフェースポインターを取得します。
			@~japanese	@details	INodeMap インターフェースポインターを取得します。
			@~japanese	@return	INodeMap インターフェースポインター
			@~japanese	@exception	なし
		*/
		virtual GenApi::INodeMap *GetINodeMap() = 0;
	};

	// ---------------------------------------------------------------------
	// interface IStFilterReleasable
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiIP_PublicInterface
		@interface IStFilterReleasable
		@~english	@brief	Interface for FilterReleasable.
		@~english	@details	Interface for FilterReleasable.
		@sa	CreateIStFilter(), GetIStFilterInfo()
		@~japanese	@brief	解放可能なフィルター用インターフェース
		@~japanese	@details	解放可能なフィルター用インターフェース
		@sa	CreateIStFilter(), GetIStFilterInfo()
	*/
	interface PUBLIC_INTERFACE IStFilterReleasable : public IStFilter, public IStReleasable
	{

	};

	//---------------------------------------------------------------------
	// typedef CIStFilterPtr
	//---------------------------------------------------------------------
	/*!
		@ingroup StApiIP_PublicImpl
		@typedef CIStFilterPtr
		@~english	@brief	The auto management class of IStFilter class.
		@~english	@details	The auto management class of IStFilter class.Use this class instead of managing the initial/release of IStFilter class yourself. The destructor of this class will automatically call IStFilterReleasable::Release().
		@sa	CreateIStFilter(), GetIStFilterInfo()
		@~japanese	@brief	IStFilterReleasable インターフェースポインターの自動管理用クラスです。
		@~japanese	@details	IStFilterReleasable インターフェースポインターの自動管理用クラスです。このクラスのデストラクタから IStFilterReleasable::Release() が自動的に呼び出されます。
		@sa	CreateIStFilter(), GetIStFilterInfo()
	*/
	typedef CStAutoPtr<IStFilterReleasable, IStFilter> CIStFilterPtr;

	// ---------------------------------------------------------------------
	// class CIStFilterPtrArray
	// ---------------------------------------------------------------------
	/*!
		@ingroup StApiIP_PublicImpl
		@class CIStFilterPtrArray
		@~english	@brief	The auto management class for the classes that inheritance the IStFilter class.
		@~english	@details	The auto management class for the classes that inheritance the IStFilter class. The destructor of this class will automatically call IStFilterReleasable::Release().
		@sa	CreateIStFilter(), GetIStFilterInfo()
		@~japanese	@brief	IStFilterReleasable インターフェースポインターリストの自動管理用クラスです。
		@~japanese	@details	IStFilterReleasable インターフェースポインターリストの自動管理用クラスです。このクラスのデストラクタから IStDeviceReleasable::Release() が自動的に呼び出されます。
		@sa	CreateIStFilter(), GetIStFilterInfo()
	*/
	class ST_API_IP CIStFilterPtrArray : public CStAutoPtrArray<IStFilterReleasable, IStFilter>
	{
	public:
		CIStFilterPtrArray();
		virtual ~CIStFilterPtrArray();
		
		/*!
			@copydoc IStFilter::Filter
		*/
		IStImage *Filter(IStImage *pImage);

		/*!
			@copydoc IStReleasable::Release
		*/
		void Release();
	private:
		// Copy is prohibited.
		CIStFilterPtrArray(CIStFilterPtrArray &rhs);

		// Copy is prohibited.
		CIStFilterPtrArray & operator= (CIStFilterPtrArray &rhs);

	};
}
#endif //ISTFILTER_H



