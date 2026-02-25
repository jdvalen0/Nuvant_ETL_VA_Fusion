//------------------------------------------------------------------------------
// StApi
//------------------------------------------------------------------------------
/*!
	@ingroup	StApiIP_PublicInterface
	@file
	@~english	@details	Definition of interface IStVideoFiler
	@~japanese	@details	IStVideoFiler インターフェースの定義
*/
#ifndef ISTVIDEOFILER_H__
#define ISTVIDEOFILER_H__

#include "IStFiler.h"

namespace StApi
{
	interface IStImage;
	interface IStStreamBuffer;

	//---------------------------------------------------------------------
	// interface IStVideoFiler
	//---------------------------------------------------------------------
	/*!
		@ingroup StApiIP_PublicInterface
		@interface IStVideoFiler
		@~english	@brief	Interface for Video Filer.
		@~english	@details	Interface for Video Filer.
		@sa	CreateIStFiler()
		@~japanese	@brief	動画ファイラー用インターフェース
		@~japanese	@details	動画ファイラー用インターフェース
		@sa	CreateIStFiler()
	*/
	interface PUBLIC_INTERFACE IStVideoFiler : public IStFiler
	{
		/*!
			@~english	@brief	Acquire current video file format setting.
			@~english	@details	Acquire current video file format setting.
			@~english	@return	Video file format.
			@~english	@exception	None.
			@~japanese	@brief	動画ファイルフォーマット設定を取得します。
			@~japanese	@details	動画ファイルフォーマット設定を取得します。
			@~japanese	@return	動画ファイルフォーマット
			@~japanese	@exception	なし
		*/
		virtual EStVideoFileFormat_t GetVideoFileFormat() const = 0;

		/*!
			@~english	@brief	Set video file format. The video file format must be set before adding any image frame.
			@~english	@details	Set video file format. The video file format must be set before adding any image frame.
			@~english	@param[in]	eVFF	Video file format.
			@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument. 
			@~japanese	@brief	動画ファイルフォーマットを設定します。
			@~japanese	@details	動画ファイルフォーマットを設定します。
			@~japanese	@param[in]	eVFF	動画ファイルフォーマット
			@~japanese	@exception	不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void SetVideoFileFormat(EStVideoFileFormat_t eVFF) = 0;

		/*!
			@~english	@brief	Acquire current video file compression format.
			@~english	@details	Acquire current video file compression format.
			@~english	@return	Video file compression format.
			@~english	@exception	None.
			@~japanese	@brief	動画ファイルの圧縮形式設定を取得します。
			@~japanese	@details	動画ファイルの圧縮形式設定を取得します。
			@~japanese	@return	動画ファイルの圧縮形式
			@~japanese	@exception	なし
		*/
		virtual EStVideoFileCompression_t GetVideoFileCompression() const = 0;

		/*!
			@~english	@brief	Set video file compression format. The video file compression format must be set before adding any image frame.
			@~english	@details	Set video file compression format. The video file compression format must be set before adding any image frame.
			@~english	@param[in]	eVFC	Video file compression format.
			@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument. 
			@~japanese	@brief	動画ファイルの圧縮形式を設定します。
			@~japanese	@details	動画ファイルの圧縮形式を設定します。
			@~japanese	@param[in]	eVFC	動画ファイルの圧縮形式
			@~japanese	@exception	不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void SetVideoFileCompression(EStVideoFileCompression_t eVFC) = 0;

		/*!
			@~english	@brief	Get the current video compression rate.
			@~english	@details	Get the current video compression rate.
			@~english	@return	Video compression rate (0: high compression rate ~ 100: low compression rate).
			@~english	@exception	None.
			@~japanese	@brief	動画ファイルの品質設定を取得します。
			@~japanese	@details	動画ファイルの品質設定を取得します。
			@~japanese	@return	品質(0:低品質～100:高品質)
			@~japanese	@exception	なし
		*/
		virtual uint32_t GetQuality() const = 0;

		/*!
			@~english	@brief	Set video compression rate.
			@~english	@details	Set video compression rate.
			@~english	@param[in]	value	Video compression rate (0: high compression rate ~ 100: low compression rate).
			@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument. 
			@~japanese	動画ファイルの品質を設定します。
			@~japanese	@details	動画ファイルの品質を設定します。
			@~japanese	@param[in]	value	品質(0:低品質～100:高品質)
			@~japanese	@exception	不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void SetQuality(uint32_t value) = 0;

		/*!
			@~english	@brief	Get current Y-axis reversion setting.
			@~english	@details	Get current Y-axis reversion setting.
			@~english	@return	True if Y-axis reversion is enabled.
			@~english	@exception	None.
			@~japanese	@brief	上下反転設定を取得します。
			@~japanese	@details	上下反転設定を取得します。
			@~japanese	@return	上下反転が有効な場合、 true が返されます。
			@~japanese	@exception	なし
		*/
		virtual bool GetReverseY() const = 0;

		/*!
			@~english	@brief	Enable or disable Y-axis reversion.
			@~english	@details	Enable or disable Y-axis reversion.
			@~english	@attention  Not all pixel format is supported for Y-axis reversion.
			@~english	@param[in]	value	True to enable Y-axis reversion.
			@~english	@exception	None.
			@~japanese	@brief	上下反転を設定します。
			@~japanese	@details	上下反転を設定します。
			@~japanese	@attention	IStPixelFormatConverter が上下反転をサポートしているピクセルフォーマットに対してのみ有効になります。
			@~japanese	@param[in]	value	true を指定すると上下反転が有効になります。
			@~japanese	@exception	なし
		*/
		virtual void SetReverseY(bool value) = 0;

		/*!
			@~english	@brief	Get current FPS setting for the video file.
			@~english	@details	Get current FPS setting for the video file.
			@~english	@return	FPS.
			@~english	@exception	None.
			@~japanese	@brief	動画ファイルのFPS設定を取得します。
			@~japanese	@details	動画ファイルのFPS設定を取得します。
			@~japanese	@return	FPS
			@~japanese	@exception	なし
		*/
		virtual double GetFPS() const = 0;

		/*!
			@~english	@brief	Set FPS setting for the video file.
			@~english	@details	Set FPS setting for the video file.
			@~english	@attention  This FPS setting is the FPS for playback of the video file.
			@~english	@param[in]	value	FPS (0.001 ~ 65535.0).
			@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument. 
			@~japanese	@brief	動画ファイルのFPSを設定します。
			@~japanese	@details	動画ファイルのFPSを設定します。
			@~japanese	@attention	設定したFPSが再生時の標準速度になります。保存時のFPS(カメラのFPS)よりも小さな値を設定するとスロー再生される動画ファイルが生成されます。
			@~japanese	@param[in]	value	FPS(0.001～65535.0)
			@~japanese	@exception	不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void SetFPS(double value) = 0;

		/*!
			@~english	@brief	Register video file name. 
			@~english	@details	Register video file name. 
			@~english	@attention  If multiple video file names are registered, multiple video files will be created when the file size or frame numbers exceeds the maximum limit.
			@~english	@param[in]	strFileName	Video file name.
			@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument. 
			@~japanese	@brief	動画ファイル名を登録します。 
			@~japanese	@details	動画ファイル名を登録します。
			@~japanese	@attention	複数のファイルを予め登録しておくと、ファイルサイズやフレーム数が上限に達した際、保存中の動画ファイルがクローズされた後に、次の動画ファイルがオープンされるようになります。
			@~japanese	@param[in]	strFileName	動画ファイル名
			@~japanese	@exception	不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void RegisterFileName(const GenICam::gcstring &strFileName) = 0;

		/*!
			@~english	@brief	Add image data with a specified frame number into video file.
			@~english	@details	Add image data with a specified frame number into video file.
			@~english	@attention
			@~english	@param[in]	pImage	Image data.
			@~english	@param[in]	iFrameNo	Frame number.
			@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument. 
			@~japanese	@brief	動画ファイルへ保存する画像データを登録します。
			@~japanese	@details	動画ファイルへ保存する画像データを登録します。
			@~japanese	@attention	渡された画像データはピクセルフォーマットを変換( StPFNC_Mono8 または StPFNC_BGR8 )されて、SDK内部のバッファへ退避されます。SDK内部のバッファに空きがない場合、空きができるまで待機します。登録されたファイル名が空の場合は、画像データの退避は行わずに終了します。
			@~japanese	@param[in]	pImage	動画ファイルへ保存する画像データ
			@~japanese	@param[in]	iFrameNo	フレーム番号
			@~japanese	@exception	不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void RegisterIStImage(IStImage *pImage, uint32_t iFrameNo) = 0;
		
		/*!
			@~english	@brief	Check if video recording is stopped.
			@~english	@details	Check if video recording is stopped.
			@~english	@return	True if video recording is stopped or the video file name list is empty.
			@~english	@exception	None.
			@~japanese	@brief	動画ファイルの生成が停止しているかどうかを確認します。
			@~japanese	@details	動画ファイルの生成が停止しているかどうかを確認します。
			@~japanese	@return	動画ファイルの生成が停止(登録ファイルリストが空)の場合、 true が返されます。
			@~japanese	@exception	なし
		*/
		virtual bool IsStopped() const = 0;

		/*!
			@~english	@brief	Acquire maximum number of frames in one video file.
			@~english	@details	Acquire maximum number of frames in one video file.
			@~english	@return	Maximum number of frames in one video file.
			@~english	@exception	None.
			@~japanese	@brief	1つの動画ファイルに保存する最大フレーム数を取得します。
			@~japanese	@details	1つの動画ファイルに保存する最大フレーム数を取得します。
			@~japanese	@return	1つの動画ファイルに保存する最大フレーム数
			@~japanese	@exception	なし
		*/
		virtual size_t GetMaximumFrameCountPerFile() const = 0;

		/*!
			@~english	@brief	Set maximum number of frames in one video file.
			@~english	@details	Set maximum number of frames in one video file.
			@~english	@attention	The file will be saved and closed when it reached either the maximum number of frames or the file size limit.
			@~english	@param[in]	value	Maximum number of frames (1 ~ 100000). 
			@~english	@exception	Throw out a GenICam::GenericException if there is an invalid argument.
			@~japanese	@brief	1つの動画ファイルに保存する最大フレーム数を設定します。
			@~japanese	@details	1つの動画ファイルに保存する最大フレーム数を設定します。
			@~japanese	@attention	指定したフレーム数に達しない場合も、ファイルサイズが上限に達した場合は、動画ファイルが閉じられます。
			@~japanese	@param[in]	value	1つの動画ファイルに保存する最大フレーム数(1～100000) 
			@~japanese	@exception	不正な引数が指定された場合は、例外 GenICam::GenericException が発生します。
		*/
		virtual void SetMaximumFrameCountPerFile(size_t value) = 0;

		/*!
			@~english	@brief	Close the file if it is opened and clear file name list and image data.
			@~english	@details	Close the file if it is opened and clear file name list and image data.
			@~english	@exception	None.
			@~japanese	@brief	生成中の動画ファイルをクローズし、ファイルリストおよび保存待機中の画像データをクリアします。
			@~japanese	@details	生成中の動画ファイルをクローズし、ファイルリストおよび保存待機中の画像データをクリアします。
			@~japanese	@exception	なし
		*/
		virtual void Reset() = 0;
	};

	//---------------------------------------------------------------------
	// typedef CIStVideoFilerPtr
	//---------------------------------------------------------------------
	/*!
		@ingroup StApiIP_PublicImpl
		@typedef CIStVideoFilerPtr
		@~english	@brief	The auto management class of IStVideoFiler class for handling video file.
		@~english	@details	The auto management class of IStVideoFiler class for handling video file.Use this class instead of managing the initial/release of IStVideoFiler class yourself. The destructor of this class will automatically call IStFilerReleasable::Release().
		@sa	CreateIStFiler()
		@~japanese	@brief	動画ファイラー用インターフェースポインターの自動管理用クラスです。
		@~japanese	@details	動画ファイラー用インターフェースポインターの自動管理用クラスです。このクラスのデストラクタから IStFilerReleasable::Release() が自動的に呼び出されます。
		@sa	CreateIStFiler()
	*/
	typedef CStAutoPtr<IStFilerReleasable, IStVideoFiler> CIStVideoFilerPtr;

	//---------------------------------------------------------------------
	// interface IStCallbackParamStApiIPVideoFilerOpen
	//---------------------------------------------------------------------
	/*!
		@ingroup StApiIP_PublicInterface
		@interface IStCallbackParamStApiIPVideoFilerOpen
		@~english	@brief	IStCallbackParamStApiIPVideoFilerOpen Interface.
		@~english	@details	IStCallbackParamStApiIPVideoFilerOpen Interface.
		@~japanese	@brief	IStCallbackParamStApiIPVideoFilerOpen インターフェース
		@~japanese	@details	IStCallbackParamStApiIPVideoFilerOpen インターフェース
	*/
	interface PUBLIC_INTERFACE IStCallbackParamStApiIPVideoFilerOpen : public IStCallbackParamBase
	{
		/*!
			@~english	@brief	Acquire IStVideoFiler interface pointer.
			@~english	@details	Acquire IStVideoFiler interface pointer.
			@~english	@return	IStVideoFiler interface pointer.
			@~english	@exception	None.
			@~japanese	@brief	IStVideoFiler インターフェースポインターを取得します。
			@~japanese	@details	IStVideoFiler インターフェースポインターを取得します。
			@~japanese	@return	IStVideoFiler インターフェースポインター
			@~japanese	@exception	なし
		*/
		virtual IStVideoFiler *GetIStVideoFiler() = 0;
		
		/*!
			@~english	@brief	Acquire opened file name.
			@~english	@details	Acquire opened file name.
			@~english	@return	Opened file name.
			@~english	@exception	None.
			@~japanese	@brief	オープンされた動画ファイルのファイル名を取得します。
			@~japanese	@details	オープンされた動画ファイルのファイル名を取得します。
			@~japanese	@return	オープンされた動画ファイルのファイル名
			@~japanese	@exception	なし
		*/
		virtual const GenICam::gcstring &GetFileName() = 0;
	};

	//---------------------------------------------------------------------
	// interface IStCallbackParamStApiIPVideoFilerClose
	//---------------------------------------------------------------------
	/*!
		@ingroup StApiIP_PublicInterface
		@interface IStCallbackParamStApiIPVideoFilerClose
		@~english	@brief	IStCallbackParamStApiIPVideoFilerClose Interface.
		@~english	@details	IStCallbackParamStApiIPVideoFilerClose Interface.
		@~japanese	@brief	IStCallbackParamStApiIPVideoFilerClose インターフェース
		@~japanese	@details	IStCallbackParamStApiIPVideoFilerClose インターフェース
	*/
	interface PUBLIC_INTERFACE IStCallbackParamStApiIPVideoFilerClose : public IStCallbackParamBase
	{
		/*!
			@~english	@brief	Acquire IStVideoFiler interface pointer.
			@~english	@details	Acquire IStVideoFiler interface pointer.
			@~english	@return	IStVideoFiler interface pointer.
			@~english	@exception	None.
			@~japanese	@brief	IStVideoFiler インターフェースポインターを取得します。
			@~japanese	@details	IStVideoFiler インターフェースポインターを取得します。
			@~japanese	@return	IStVideoFiler インターフェースポインター
			@~japanese	@exception	なし
		*/
		virtual IStVideoFiler *GetIStVideoFiler() = 0;
		
		/*!
			@~english	@brief	Acquire closed file name.
			@~english	@details	Acquire closed file name.
			@~english	@return	Closed file name.
			@~english	@exception	None.
			@~japanese	@brief	閉じられた動画ファイルのファイル名を取得します。
			@~japanese	@details	閉じられた動画ファイルのファイル名を取得します。
			@~japanese	@return	閉じられた動画ファイルのファイル名
			@~japanese	@exception	なし
		*/
		virtual const GenICam::gcstring &GetFileName() = 0;
	};

	//---------------------------------------------------------------------
	// interface IStCallbackParamStApiIPVideoFilerError
	//---------------------------------------------------------------------
	/*!
		@ingroup StApiIP_PublicInterface
		@interface IStCallbackParamStApiIPVideoFilerError
		@~english	@brief	IStCallbackParamStApiIPVideoFilerError Interface.
		@~english	@details	IStCallbackParamStApiIPVideoFilerError Interface.
		@~japanese	@brief	IStCallbackParamStApiIPVideoFilerError インターフェース
		@~japanese	@details	IStCallbackParamStApiIPVideoFilerError インターフェース
	*/
	interface PUBLIC_INTERFACE IStCallbackParamStApiIPVideoFilerError : public IStCallbackParamBase
	{
		/*!
			@~english	@brief	Acquire IStVideoFiler interface pointer.
			@~english	@details	Acquire IStVideoFiler interface pointer.
			@~english	@return	IStVideoFiler interface pointer.
			@~english	@exception	None.
			@~japanese	@brief	IStVideoFiler インターフェースポインターを取得します。
			@~japanese	@details	IStVideoFiler インターフェースポインターを取得します。
			@~japanese	@return	IStVideoFiler インターフェースポインター
			@~japanese	@exception	なし
		*/
		virtual IStVideoFiler *GetIStVideoFiler() = 0;
		
		/*!
			@~english	@brief	Acquire reference of GenericException.
			@~english	@details	Acquire reference of GenericException.
			@~english	@return	GenericException.
			@~english	@exception	None.
			@~japanese	@brief	発生したエラーの例外情報を取得します。
			@~japanese	@details	発生したエラーの例外情報を取得します。
			@~japanese	@return	GenericException
			@~japanese	@exception	なし
		*/
		virtual const GenICam::GenericException &GetException() = 0;
	};

}
#endif //ISTVIDEOFILER_H__



