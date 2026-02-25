/* This file is encoded in UTF-8,  */
/* but BOM has not been added to accommodate environments not compatible with BOM. */
/*
 StApi
*/
/*!
	@ingroup	StApiIP_PublicImpl
	@file	StApi_IPDef.h
	@~english	@details
	@~japanese	@details
*/
#ifndef STAPI_IPDEF_H__
#define STAPI_IPDEF_H__

#ifdef __cplusplus
namespace StApi
{
#endif /* __cplusplus */
	//-------------------------------------------------------------------------
	//Definition
	//-------------------------------------------------------------------------

	//-------------------------------------------------------------------------
	//struct
	//-------------------------------------------------------------------------
	/*! 
		@ingroup	StApiIP_PublicImpl
		@~english	@brief	Struct for Defective pixel information.
		@~english	@details	Struct for Defective pixel information.
		@~japanese	@brief	欠陥画素位置情報
		@~japanese	@details	欠陥画素位置情報
		@since StApi v1.1.1
	*/
	typedef struct _SStDefectivePixelInformation_t
	{
		/*!
			@~english	@details	Horizontal position.
			@~japanese	@details	横方向の位置
		*/
		size_t x;

		/*!
			@~english	@details	Vertical position.
			@~japanese	@details	縦方向の位置
		*/
		size_t y;

		/*!
			@~english	@details	Evaluation value of the pixel.
			@~japanese	@details	評価値
		*/
		double dblEvaluationValue;

		/*!
			@~english	@details	Reference value for evaluation.
			@~japanese	@details	参照値(周辺画素の評価値)
		*/
		double dblReferenceValue;

		/*!
			@~english	@details	Delta Ratio.
			@~japanese	@details	評価値の周辺画素との変化の割合
		*/
		double dblDeltaRatio;
	}SStDefectivePixelInformation_t, *PSStDefectivePixelInformation_t;


	//-------------------------------------------------------------------------
	//Enumerator
	//-------------------------------------------------------------------------
	/*! 
		@ingroup	StApiIP_PublicImpl
		@enum EStFilterType_t
		@~english	@brief	Enumerator for type of image filter.
		@~english	@details	Enumerator for type of image filter.
		@~japanese	@brief	フィルタータイプ列挙子
		@~japanese	@details	フィルタータイプ列挙子
	*/
	typedef enum
	{
		/*!
			@~english	@details	Gamma correction filter.
			@~japanese	@details	ガンマ補正フィルター
		*/
		StFilterType_GammaCorrection,

		/*!
			@~english	@details	Color transformation filter.
			@~japanese	@details	色変換フィルター
		*/
		StFilterType_ColorTransformation,

		/*!
			@~english	@details	Edge enhancement filter.
			@~japanese	@details	輪郭強調フィルター
		*/
		StFilterType_EdgeEnhancement,

		/*!
			@~english	@details	Balance ratio filter.
			@~japanese	@details	バランスレートフィルター
		*/
		StFilterType_BalanceRatio,

		/*!
			@~english	@details	Noise reduction filter.
			@~japanese	@details	ノイズ軽減フィルター
		*/
		StFilterType_NoiseReduction,

		/*!
			@~english	@details	Field flat correction filter.
			@~japanese	@details	FFC(フィールドフラットコレクション)フィルター
		*/
		StFilterType_FlatFieldCorrection,

		/*!
			@~english	@details	Chroma suppression filter.
			@~japanese	@details	クロマサプレスフィルター
		*/
		StFilterType_ChromaSuppression,

		/*!
			@~english	@details	SN measurement filter.
			@~japanese	@details	SN測定フィルター
		*/
		StFilterType_SNMeasurement,

		/*!
			@~english	@details	Graph Data filter.
			@~japanese	@details	グラフデータフィルター
			@since StApi v1.1.1
		*/
		StFilterType_GraphData,

		/*!
			@~english	@details	Image averaging filter.
			@~japanese	@details	画像平均化フィルター
			@since StApi v1.1.1
		*/
		StFilterType_ImageAveraging,

		/*!
			@~english	@details	Defective Pixel Detection filter.
			@~japanese	@details	欠陥画素検出フィルター
			@since StApi v1.1.1
		*/
		StFilterType_DefectivePixelDetection,

		/*!
			@~english	@details	Count of filter.
			@~japanese	@details	対応フィルター数
		*/
		StFilterType_Count						
	}EStFilterType_t, *PEStFilterType_t;

	/*! 
		@ingroup	StApiIP_PublicImpl
		@enum EStColorTransformationValueSelector_t
		@~english	@brief	Enumerator for component of the color correction matrix.
		@~english	@details	Enumerator for component of the color correction matrix.
		@~japanese	@brief	色変換行列構成要素列挙子
		@~japanese	@details	色変換行列構成要素列挙子
	*/
	typedef enum
	{
		/*!
			@~english	@details	The red contribution to the red pixel (multiplicative factor). 
			@~japanese	@details	赤算出用赤乗数 Rout = Rin x Gain00 + Gin x Gain01 + Bin x Gain02 + Offset0
		*/
		StColorTransformationValueSelector_Gain_00,

		/*!
			@~english	@details	The green contribution to the red pixel (multiplicative factor).
			@~japanese	@details	赤算出用緑乗数 Rout = Rin x Gain00 + Gin x Gain01 + Bin x Gain02 + Offset0
		*/
		StColorTransformationValueSelector_Gain_01,

		/*!
			@~english	@details	The blue contribution to the red pixel (multiplicative factor).
			@~japanese	@details	赤算出用青乗数 Rout = Rin x Gain00 + Gin x Gain01 + Bin x Gain02 + Offset0
		*/
		StColorTransformationValueSelector_Gain_02,

		/*!
			@~english	@details	The red offset.
			@~japanese	@details	赤算出用オフセット Rout = Rin x Gain00 + Gin x Gain01 + Bin x Gain02 + Offset0
		*/
		StColorTransformationValueSelector_Offset_0,
		
		/*!
			@~english	@details	The red contribution to the green pixel (multiplicative factor).
			@~japanese	@details	緑算出用赤乗数 Gout = Rin x Gain00 + Gin x Gain01 + Bin x Gain02 + Offset0
		*/
		StColorTransformationValueSelector_Gain_10,

		/*!
			@~english	@details	The green contribution to the green pixel (multiplicative factor).
			@~japanese	@details	緑算出用緑乗数 Gout = Rin x Gain00 + Gin x Gain01 + Bin x Gain02 + Offset0
		*/
		StColorTransformationValueSelector_Gain_11,

		/*!
			@~english	@details	The blue contribution to the green pixel (multiplicative factor).
			@~japanese	@details	緑算出用青乗数 Gout = Rin x Gain00 + Gin x Gain01 + Bin x Gain02 + Offset0
		*/
		StColorTransformationValueSelector_Gain_12,

		/*!
			@~english	@details	The green offset.
			@~japanese	@details	緑算出用オフセット Gout = Rin x Gain00 + Gin x Gain01 + Bin x Gain02 + Offset0
		*/
		StColorTransformationValueSelector_Offset_1,
		
		/*!
			@~english	@details	The red contribution to the blue pixel (multiplicative factor).
			@~japanese	@details	青算出用赤乗数 Bout = Rin x Gain00 + Gin x Gain01 + Bin x Gain02 + Offset0
		*/
		StColorTransformationValueSelector_Gain_20,

		/*!
			@~english	@details	The green contribution to the blue pixel (multiplicative factor).
			@~japanese	@details	青算出用緑乗数 Bout = Rin x Gain00 + Gin x Gain01 + Bin x Gain02 + Offset0
		*/
		StColorTransformationValueSelector_Gain_21,

		/*!
			@~english	@details	The blue contribution to the blue pixel (multiplicative factor).
			@~japanese	@details	青算出用青乗数 Bout = Rin x Gain00 + Gin x Gain01 + Bin x Gain02 + Offset0
		*/
		StColorTransformationValueSelector_Gain_22,

		/*!
			@~english	@details	The blue offset.
			@~japanese	@details	青算出用オフセット Bout = Rin x Gain00 + Gin x Gain01 + Bin x Gain02 + Offset0
		*/
		StColorTransformationValueSelector_Offset_2,

		/*!
			@~english	@details	Count of enumerator.
			@~japanese	@details	列挙子数
		*/
		StColorTransformationValueSelector_Count
	}EStColorTransformationValueSelector_t, *PEStColorTransformationValueSelector_t;

	/*! 
		@ingroup	StApiIP_PublicImpl
		@enum EStBalanceRatioSelector_t
		@~english	@brief	Enumerator for elements of a balance ratio.
		@~english	@details	Enumerator for elements of a balance ratio.
		@~japanese	@brief	バランスレート要素列挙子
		@~japanese	@details	バランスレート要素列挙子
	*/
	typedef enum
	{
		/*!
			@~english	@details	Red.
			@~japanese	@details	赤
		*/
		StBalanceRatioSelector_Red,

		/*!
			@~english	@details	Green.
			@~japanese	@details	緑
		*/
		StBalanceRatioSelector_Green,

		/*!
			@~english	@details	Blue.
			@~japanese	@details	青
		*/
		StBalanceRatioSelector_Blue,

		/*!
			@~english	@details	Y.
			@~japanese	@details	Y
		*/
		StBalanceRatioSelector_Y,

		/*!
			@~english	@details	Cb.
			@~japanese	@details	Cb
		*/
		StBalanceRatioSelector_Cb,

		/*!
			@~english	@details	Cr.
			@~japanese	@details	Cr
		*/
		StBalanceRatioSelector_Cr,
		
		/*!
			@~english	@details	Count of enumerator.
			@~japanese	@details	列挙子数
		*/
		StBalanceRatioSelector_Count
	}EStBalanceRatioSelector_t, *PEStBalanceRatioSelector_t;

	/*! 
		@ingroup	StApiIP_PublicImpl
		@enum EStBalanceWhiteAuto_t
		@~english	@brief	Enumerator for balance white auto.
		@~english	@details	Enumerator for balance white auto.
		@~japanese	@brief	オートホワイトバランス列挙子
		@~japanese	@details	オートホワイトバランス列挙子
	*/
	typedef enum
	{
		/*!
			@~english	@details	OFF(Manual).
			@~japanese	@details	OFF(手動/固定)
		*/
		StBalanceWhiteAuto_Off,
		
		/*!
			@~english	@details	Once.
			@~japanese	@details	1回のみ(一旦収束したらOFFになります)
		*/
		StBalanceWhiteAuto_Once,
		
		/*!
			@~english	@details	Continuous.
			@~japanese	@details	連続
		*/
		StBalanceWhiteAuto_Continuous,
		
		/*!
			@~english	@details	Count of enumerator.
			@~japanese	@details	列挙子数
		*/
		StBalanceWhiteAuto_Count
	}EStBalanceWhiteAuto_t, *PEStBalanceWhiteAuto_t;

	/*! 
		@ingroup	StApiIP_PublicImpl
		@enum EStNoiseReductionMode_t
		@~english	@brief	Enumerator for noise reduction mode.
		@~english	@details	Enumerator for noise reduction mode.
		@~japanese	@brief	ノイズリダクションモード列挙子
		@~japanese	@details	ノイズリダクションモード列挙子
	*/
	typedef enum
	{
		/*!
			@~english	@details	Off.
			@~japanese	@details	OFF
		*/
		StNoiseReductionMode_Off,

		/*!
			@~english	@details	Simple (calibration is unnecessary).
			@~japanese	@details	簡単(キャリブレーション不要)
		*/
		StNoiseReductionMode_Simple,

		/*!
			@~english	@details	Subtracting light shielding image (Calibration is necessary).
			@~japanese	@details	遮光時の画像を減算(要キャリブレーション)
		*/
		StNoiseReductionMode_SubtractingLightShieldingImage,
		
		/*!
			@~english	@details	Count of enumerator.
			@~japanese	@details	列挙子数
		*/
		StNoiseReductionMode_Count
	}EStNoiseReductionMode_t, *PEStNoiseReductionMode_t;

	/*! 
		@ingroup	StApiIP_PublicImpl
		@enum EStFlatFieldCorrectionMode_t
		@~english	@brief	Enumerator for field flat correction mode.
		@~english	@details	Enumerator for field flat correction mode.
		@~japanese	@brief	FFCモード列挙子
		@~japanese	@details	FFCモード列挙子
	*/
	typedef enum
	{
		/*!
			@~english	@details	Off.
			@~japanese	@details	OFF
		*/
		StFlatFieldCorrectionMode_Off,

		/*!
			@~english	@details	Multiplication.
			@~japanese	@details	乗算
		*/
		StFlatFieldCorrectionMode_Multiplication,

		/*!
			@~english	@details	Addition.
			@~japanese	@details	加算
		*/
		StFlatFieldCorrectionMode_Addition,
		
		/*!
			@~english	@details	Count of enumerator.
			@~japanese	@details	列挙子数
		*/
		StFlatFieldCorrectionMode_Count
	}EStFlatFieldCorrectionMode_t, *PEStFlatFieldCorrectionMode_t;

	/*! 
		@ingroup	StApiIP_PublicImpl
		@enum EStChromaSuppressionPartSelector_t
		@~english	@brief	Enumerator for target of the chroma suppression.
		@~english	@details	Enumerator for target of the chroma suppression.
		@~japanese	@brief	クロマサプレス対象列挙子
		@~japanese	@details	クロマサプレス対象列挙子
	*/
	typedef enum
	{	
		/*!
			@~english	@details	Low luminance part.
			@~japanese	@details	低輝度部
		*/
		StChromaSuppressionPartSelector_LowLuminancePart,
		
		/*!
			@~english	@details	High luminance part.
			@~japanese	@details	高輝度部
		*/
		StChromaSuppressionPartSelector_HighLuminancePart,
		
		/*!
			@~english	@details	Count of enumerator.
			@~japanese	@details	列挙子数
		*/
		StChromaSuppressionPartSelector_Count					
	}EStChromaSuppressionPartSelector_t, *PEStChromaSuppressionPartSelector_t;

	/*! 
		@ingroup	StApiIP_PublicImpl
		@enum EStROIMode_t
		@~english	@brief	Enumerator for ROI mode.
		@~english	@details	Enumerator for ROI mode.
		@~japanese	@brief	ROIモード列挙子
		@~japanese	@details	ROIモード列挙子
	*/
	typedef enum
	{
		/*!
			@~english	@details	Whole image (ROI disabled).
			@~japanese	@details	画像全体
		*/
		StROIMode_WholeImage,
		
		/*!
			@~english	@details	Manual (Sets size and offset).
			@~japanese	@details	手動(オフセットとサイズを設定する)
		*/
		StROIMode_Manual,
		
		/*!
			@~english	@details	Center of image (Sets size only)
			@~japanese	@details	画像の中央(サイズのみ設定する)
		*/
		StROIMode_CenterOfImage,
		
		/*!
			@~english	@details	Count of enumerator.
			@~japanese	@details	列挙子数
		*/
		StROIMode_Count
	}EStROIMode_t, *PEStROIMode_t;

	/*! 
		@ingroup	StApiIP_PublicImpl
		@enum EStConverterType_t
		@~english	@brief	Enumerator for type of converter.
		@~english	@details	Enumerator for type of converter.
		@~japanese	@brief	コンバータータイプ列挙子
		@~japanese	@details	コンバータータイプ列挙子
	*/
	typedef enum
	{
		/*!
			@~english	@details	Pixel format converter
			@~japanese	@details	ピクセルフォーマットコンバーター
		*/
		StConverterType_PixelFormat,
		
		/*!
			@~english	@details	Reverse converter
			@~japanese	@details	反転コンバーター
		*/
		StConverterType_Reverse,
		
		/*!
			@~english	@details	Count of enumerator.
			@~japanese	@details	列挙子数
		*/
		StConverterType_Count
	}EStConverterType_t, *PEStConverterType_t;

	/*! 
		@ingroup	StApiIP_PublicImpl
		@enum EStBayerInterpolationMethod_t
		@~english	@brief	Enumerator for Bayer interpolation method.
		@~english	@details	Enumerator for Bayer interpolation method.
		@~japanese	@brief	ベイヤー色補間列挙子
		@~japanese	@details	ベイヤー色補間列挙子
	*/
	typedef enum
	{
		/*!
			@~english	@details	Off.
			@~japanese	@details	OFF
		*/
		StBayerInterpolationMethod_Off,
		
		/*!
			@~english	@details	Nearest neighbor 1. Copies neighboring pixel values. The position of the copied pixel is different from that of the Nearest neighbor 2.
			@~japanese	@details	ニアレストネイバー1 近隣の画素値をコピーします。ニアレストネイバー2とはコピーされる画素の位置が異なります。
		*/
		StBayerInterpolationMethod_NearestNeighbor,
		
		/*!
			@~english	@details	Nearest neighbor 2. Copies neighboring pixel values. The position of the copied pixel is different from that of the Nearest neighbor 1.
			@~japanese	@details	ニアレストネイバー2 近隣の画素値をコピーします。ニアレストネイバー1とはコピーされる画素の位置が異なります。
		*/
		StBayerInterpolationMethod_NearestNeighbor2,
		
		/*!
			@~english	@details	BiLinear 1. Uses the average of neighboring pixel values. The processing load is lower than BiLinear 1 and 2, but the false color is conspicuous.
			@~japanese	@details	バイリニア1 近隣の画素値の平均値を使用します。バイリニア1,2よりも処理にかかる負荷は低めですが、偽色が目立ちます。
		*/
		StBayerInterpolationMethod_BiLinear,
		
		/*!
			@~english	@details	BiLinear 2. Uses the average of neighboring pixel values. Fake edge coloring is less than BiLinear 1, but the processing load is higher.
			@~japanese	@details	バイリニア2 近隣の画素値の平均値を使用します。バイリニア1よりもエッジ部の偽着色が軽減されていますが、処理にかかる負荷は高めになります。
		*/
		StBayerInterpolationMethod_BiLinear2,
		
		/*!
			@~english	@details	BiCubic. Uses the surrounding 4x4 pixels.
			@~japanese	@details	バイキュービック 周辺の4x4画素を使用します。
		*/
		StBayerInterpolationMethod_BiCubic,
		
		/*!
			@~english	@brief		Mono.
			@~english	@details	Convert bayer image to monochrome image without performing color interpolation processing.
			@~japanese	@brief		モノクロ
			@~japanese	@details	色補間処理を行わずに、ベイヤー画像をモノクロ画像へ変換します。
			@since v1.0.6
		*/
		StBayerInterpolationMethod_Mono,

		/*!
			@~english	@details	BiLinear 3. Uses the average of neighboring pixel values. Fake edge coloring is less than BiLinear 2, but the processing load is higher.
			@~japanese	@details	バイリニア3 近隣の画素値の平均値を使用します。バイリニア2よりもエッジ部の偽着色が軽減されていますが、処理にかかる負荷は高めになります。
		*/
		StBayerInterpolationMethod_BiLinear3,

		/*!
			@~english	@details	Count of enumerator.
			@~japanese	@details	列挙子数
		*/
		StBayerInterpolationMethod_Count	
	}EStBayerInterpolationMethod_t, *PEStBayerInterpolationMethod_t;

	/*! 
		@ingroup	StApiIP_PublicImpl
		@enum EStRotationMode_t
		@~english	@brief	Enumerator for rotation mode.
		@~english	@details	Enumerator for rotation mode.
		@~japanese	@brief	回転モード列挙子
		@~japanese	@details	回転モード列挙子
	*/
	typedef enum
	{
		/*!
			@~english	@details	Off.
			@~japanese	@details	OFF
		*/
		StRotationMode_Off,					//!< Off
		
		/*!
			@~english	@details	90 degrees clockwise.
			@~japanese	@details	90度時計回り
		*/
		StRotationMode_Clockwise90,
		
		/*!
			@~english	@details	90 degrees counterclockwise.
			@~japanese	@details	90度反時計回り
		*/
		StRotationMode_Counterclockwise90,
		
		/*!
			@~english	@details	Count of enumerator.
			@~japanese	@details	列挙子数
		*/
		StRotationMode_Count
	}EStRotationMode_t, *PEStRotationMode_t;

	/*! 
		@ingroup	StApiIP_PublicImpl
		@enum EStFilerType_t
		@~english	@brief	Enumerator for type of filer.
		@~english	@details	Enumerator for type of filer.
		@~japanese	@brief	ファイラータイプ列挙子
		@~japanese	@details	ファイラータイプ列挙子
	*/
	typedef enum
	{
		/*!
			@~english	@details	Still image filer.
			@~japanese	@details	静止画ファイル
		*/
		StFilerType_StillImage,	

		/*!
			@~english	@details	Video filer.
			@~japanese	@details	ビデオファイル
		*/
		StFilerType_Video,

		/*!
			@~english	@details	Count of enumerator.
			@~japanese	@details	列挙子数
		*/
		StFilerType_Count
	}EStFilerType_t, *PEStFilerType_t;

	/*! 
		@ingroup	StApiIP_PublicImpl
		@enum EStStillImageFileFormat_t
		@~english	@brief	Enumerator still image file format.
		@~english	@details	Enumerator for still image file format.
		@~japanese	@brief	静止画ファイルフォーマット列挙子
		@~japanese	@details	静止画ファイルフォーマット列挙子
	*/
	typedef enum
	{
		/*!
			@~english	@details	StApi original format.
			@~japanese	@details	StApi 独自フォーマット
		*/
		StStillImageFileFormat_StApiRaw,
		
		/*!
			@~english	@details	Bitmap.
			@~japanese	@details	ビットマップ
		*/
		StStillImageFileFormat_Bitmap,
		
		/*!
			@~english	@details	JPEG.
			@~japanese	@details	JPEG
		*/
		StStillImageFileFormat_JPEG,
		
		/*!
			@~english	@details	Tiff.
			@~japanese	@details	Tiff
		*/
		StStillImageFileFormat_TIFF,
		
		/*!
			@~english	@details	PNG.
			@~japanese	@details	PNG
		*/
		StStillImageFileFormat_PNG,
		
		/*!
			@~english	@details	Comma separated values text.
			@~japanese	@details	カンマ区切りテキスト
		*/
		StStillImageFileFormat_CSV,
		
		/*!
			@~english	@details	Count of enumerator.
			@~japanese	@details	列挙子数
		*/
		StStillImageFileFormat_Count
	}EStStillImageFileFormat_t, *PEStStillImageFileFormat_t;

#ifdef _WIN32
#define ENABLED_VPX_VIDEO_FILE
//#define ENABLED_VP9
#endif
	/*! 
		@ingroup	StApiIP_PublicImpl
		@enum EStVideoFileFormat_t
		@~english	@brief	Enumerator for video file format.
		@~english	@details	Enumerator for video file format.
		@~japanese	@brief	動画ファイルフォーマット列挙子
		@~japanese	@details	動画ファイルフォーマット列挙子
	*/
	typedef enum
	{
		/*!
			@~english	@details	AVI 1.0.
			@~english	@attention  Maximum file size is 2 GB.
			@~japanese	@details	AVI 1.0
			@~japanese	@attention	ファイルサイズは最大2Gバイトになります。
		*/
		StVideoFileFormat_AVI1,

		/*!
			@~english	@details	AVI 2.0.
			@~english	@attention  Maximum file size is 1 TB.
			@~japanese	@details	AVI 2.0(OpenDML)
			@~japanese	@attention	ファイルサイズは最大1Tバイトになります。
		*/
		StVideoFileFormat_AVI2,
		
#ifdef ENABLED_VPX_VIDEO_FILE
		/*!
			@~english	@details	WebM
			@~japanese	@details	WebM
		*/
		StVideoFileFormat_WebM,
#endif

		/*!
			@~english	@details	Count of enumerator.
			@~japanese	@details	列挙子数
		*/
		StVideoFileFormat_Count	 
	}EStVideoFileFormat_t, *PEStVideoFileFormat_t;

	/*! 
		@ingroup	StApiIP_PublicImpl
		@enum EStVideoFileCompression_t
		@~english	@brief	Enumerator for video file compression type.
		@~english	@details	Enumerator for video file compression type.
		@~japanese	@brief	動画ファイル圧縮タイプ列挙子
		@~japanese	@details	動画ファイル圧縮タイプ列挙子
	*/
	typedef enum
	{
		/*!
			@~english	@details	Uncompressed.
			@~japanese	@details	非圧縮
		*/
		StVideoFileCompression_Uncompressed,
		/*!
			@~english	@details	Motion JPEG.
			@~japanese	@details	モーションJPEG
		*/
		StVideoFileCompression_MotionJPEG,

#ifdef ENABLED_VPX_VIDEO_FILE
		/*!
			@~english	@details	VP8.
			@~japanese	@details	VP8
		*/
		StVideoFileCompression_VP8,

#ifdef ENABLED_VP9
		/*!
			@~english	@details	VP9.
			@~japanese	@details	VP9
		*/
		StVideoFileCompression_VP9,
#endif //ENABLED_VP9
#endif
		/*!
			@~english	@details	Count of enumerator.
			@~japanese	@details	列挙子数
		*/
		StVideoFileCompression_Count
	}EStVideoFileCompression_t, *PEStVideoFileCompression_t;
	//-------------------------------------------------------------------------

	//-------------------------------------------------------------------------
	//Enumerator EStGraphDataType_t
	//-------------------------------------------------------------------------
	/*!
		@ingroup	StApiIP_PublicImpl
		@enum EStGraphDataType_t
		@~english	@brief	Enumerator for graph data type.
		@~english	@details	Enumerator for graph data type.
		@~japanese	@brief	グラフデータタイプ列挙子
		@~japanese	@details	グラフデータタイプ列挙子
		@since StApi v1.1.1
	*/
	typedef enum _EStGraphDataType_t
	{
		/*!
			@~english	@details	Unknown.
			@~japanese	@details	不明
		*/
		StGraphDataType_Unknown,

		/*!
			@~english	@details	Histogram.
			@~japanese	@details	ヒストグラム。色ごとに、画素値の出現回数をカウントします。
		*/
		StGraphDataType_Histogram,

		/*!
			@~english	@details	Vertical Integration.
			@~japanese	@details	縦方向の積算値。色ごとに、縦方向に画素値を積算します。
		*/
		StGraphDataType_VerticalIntegration,

		/*!
			@~english	@details	Horizontal Integration.
			@~japanese	@details	横方向の積算値。色ごとに、横方向に画素値を積算します。
		*/
		StGraphDataType_HorizontalIntegration,

		/*!
			@~english	@details	Count of GraphDataType.
			@~japanese	@details	グラフデータタイプの数
		*/
		StGraphDataType_Count
	}EStGraphDataType_t, *PEStGraphDataType_t;
	
	/*!
		@ingroup	StApiIP_PublicImpl
		@enum EStGraphDataInfoUint32_t
		@~english	@brief	Enumerator for graph data information of type uint32_t.
		@~english	@details	Enumerator for graph data information of type uint32_t.
		@~japanese	@brief	グラフデータ情報(uint32型)列挙子
		@~japanese	@details	グラフデータ情報(uint32型)列挙子
		@since StApi v1.1.1
	*/
	typedef enum _EStGraphDataInfoUint32_t
	{
		/*!
			@~english	@details	Pixel Component Type.
			@~japanese	@details	ピクセル構成要素値(EStPixelComponent_t)。
		*/
		StGraphDataInfoUint32_PixelComponent,

		/*!
			@~english	@details	Theoretical maximum.
			@~japanese	@details	グラフデータの理論上の最大値。ヒストグラム( StGraphDataType_Histogram )の場合は、対象画素の数を表します。 縦方向の積算値( StGraphDataType_VerticalIntegration )の場合は、縦方向の対象画素の数を表します。 横方向の積算値( StGraphDataType_HorizontalIntegration )の場合は、横方向の対象画素の数を表します。
		*/
		StGraphDataInfoUint32_TheoreticalMaximum,

		/*!
			@~english	@details	Index of maximum value.
			@~japanese	@details	最大値のインディックス値。ヒストグラム( StGraphDataType_Histogram )の場合は、度数が最大となった画素値を表します。 縦方向の積算値( StGraphDataType_VerticalIntegration )の場合は、積算値が最大となった横方向の位置を表します。 横方向の積算値( StGraphDataType_HorizontalIntegration )の場合は、積算値が最大となった縦方向の位置を表します。
		*/
		StGraphDataInfoUint32_IndexOfMaximumValue,

		/*!
			@~english	@details	Maximum value.
			@~japanese	@details	最大値。ヒストグラム( StGraphDataType_Histogram )の場合は、最大度数を表します。 縦方向の積算値( StGraphDataType_VerticalIntegration )の場合は、最大となった積算値を表します。 横方向の積算値( StGraphDataType_HorizontalIntegration )の場合は、最大となった積算値を表します。
		*/
		StGraphDataInfoUint32_MaximumValue,

		/*!
			@~english	@details	Maximum value.
			@~japanese	@details	最大値。ヒストグラム( StGraphDataType_Histogram )の場合は、対応していません。 縦方向の積算値( StGraphDataType_VerticalIntegration )および横方向の積算値( StGraphDataType_HorizontalIntegration )の場合は、対象となった画素の数を表します。
		*/
		StGraphDataInfoUint32_IntegrationCount,

		/*!
			@~english	@details	Count of GraphDataInfoUint32.
			@~japanese	@details	グラフデータ情報(uint32型)の数
		*/
		StGraphDataInfoUint32_Count
	}EStGraphDataInfoUint32_t, *PEStGraphDataInfoUint32_t;
	
	/*!
		@ingroup	StApiIP_PublicImpl
		@enum EStGraphDataInfoFloat64_t
		@~english	@brief	Enumerator for graph data information of type doube.
		@~english	@details	Enumerator for graph data information of type doube.
		@~japanese	@brief	グラフデータ情報(double型)列挙子
		@~japanese	@details	グラフデータ情報(double型)列挙子
		@since StApi v1.1.1
	*/
	typedef enum _EStGraphDataInfoFloat64_t
	{
		/*!
			@~english	@details	Count of GraphDataInfoFloat64.
			@~japanese	@details	グラフデータ情報(double型)の数
		*/
		StGraphDataInfoFloat64_Count
	}EStGraphDataInfoFloat64_t, *PEStGraphDataInfoFloat64_t;

	/*! 
		@ingroup	StApiIP_PublicImpl
		@enum EStGraphDataFileFormat_t
		@~english	@brief	Enumerator for graph data file format.
		@~english	@details	Enumerator for graph data file format.
		@~japanese	@brief	グラフデータファイルフォーマット列挙子
		@~japanese	@details	グラフデータファイルフォーマット列挙子
		@since StApi v1.1.1
	*/
	typedef enum _EStGraphDataFileFormat_t
	{
		/*!
			@~english	@details	StApi original format.
			@~japanese	@details	StApi 独自フォーマット
		*/
		StGraphDataFileFormat_StApiRaw,
		
		/*!
			@~english	@details	CSV.
			@~japanese	@details	CSV
		*/
		StGraphDataFileFormat_CSV,
		
		/*!
			@~english	@details	Count of enumerator.
			@~japanese	@details	列挙子数
		*/
		StGraphDataFileFormat_Count
	}EStGraphDataFileFormat_t, *PEStGraphDataFileFormat_t;
	
	/*! 
		@ingroup	StApiIP_PublicImpl
		@enum EStDefectivePixelDetectionStatus_t
		@~english	@brief	Enumerator for Defective Pixel Detection Status.
		@~english	@details	Enumerator for Defective Pixel Detection Status.
		@~japanese	@brief	欠陥画素検出状態列挙子
		@~japanese	@details	欠陥画素検出状態列挙子
		@since StApi v1.1.1
	*/
	typedef enum _EStDefectivePixelDetectionStatus_t
	{
		/*!
			@~english	@details	Not run.
			@~japanese	@details	未実行
		*/
		StDefectivePixelDetectionStatus_NotRun,

		/*!
			@~english	@details	Succeeded.
			@~japanese	@details	成功した
		*/
		StDefectivePixelDetectionStatus_Succeeded,

		/*!
			@~english	@details	Too Many Defective Pixel Detected Failed.
			@~japanese	@details	検出された欠陥画素が多すぎて失敗しました。
		*/
		StDefectivePixelDetectionStatus_TooManyDefectivePixelDetectedFailed,

		/*!
			@~english	@details	Failed.
			@~japanese	@details	失敗しました。
		*/
		StDefectivePixelDetectionStatus_Failed,
		
		/*!
			@~english	@details	Count of enumerator.
			@~japanese	@details	列挙子数
		*/
		StDefectivePixelDetectionStatus_Count
	}EStDefectivePixelDetectionStatus_t, *PEStDefectivePixelDetectionStatus_t;
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif //STAPI_IPDEF_H__


