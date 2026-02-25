/* This file is encoded in UTF-8,  */
/* but BOM has not been added to accommodate environments not compatible with BOM. */
/*
 StApi
*/
/*!
	@ingroup	StApiTL_PublicImpl
	@file	StApi_PixelFormat.h
	@~english	@details	
	@~japanese	@details	
*/
#ifndef STPIXELFORMAT_H__
#define STPIXELFORMAT_H__


#ifdef __cplusplus
namespace StApi
{
#endif /* __cplusplus */
	/*-------------------------------------------------------------------------*/
	/*Enumerator EStPixelFormatNamingConvention_t                              */
	/*-------------------------------------------------------------------------*/
	/*! 
		@ingroup	StApiTL_PublicImpl
		@enum EStPixelFormatNamingConvention_t
		@~english	@brief	Enumerator for pixel format.
		@~english	@details	Enumerator for pixel format.
		@~japanese	@brief	ピクセルフォーマット列挙子
		@~japanese	@details	ピクセルフォーマット列挙子
	*/
	typedef enum
	{
		StPFNC_Unknown = (int)0xFFFFFFFFL,		/*!< Invalid value */
		
		/*!
			@~english	@details	Monochrome 1-bit packed.
			@~english	@attention  8-pixel image is stored in 8-bit (1-Byte) data.
			@~japanese	@details	モノクロ1ビット(Packed)
			@~japanese	@attention	8画素が1バイト(8ビット)で表現され、下位ビットから画素ごとに1ビットずつ使用されます。
		*/
		StPFNC_Mono1p = (int)0x01010037L,

		/*!
			@~english	@details	Monochrome 2-bit packed.
			@~english	@attention  4-pixel image is stored in 8-bit (1-Byte) data.
			@~japanese	@details	モノクロ2ビット(Packed)
			@~japanese	@attention	4画素が1バイト(8ビット)で表現され、下位ビットから画素ごとに2ビットずつ使用されます。
		*/
		StPFNC_Mono2p = (int)0x01020038L,
		
		/*!
			@~english	@details	Monochrome 4-bit packed.
			@~english	@attention  2-pixel image is stored in 8-bit (1-Byte) data.	
			@~japanese	@details	モノクロ4ビット(Packed)
			@~japanese	@attention	2画素が1バイト(8ビット)で表現され、下位ビットから画素ごとに4ビットずつ使用されます。
		*/
		StPFNC_Mono4p = (int)0x01040039L,
		
		/*!
			@~english	@details	Monochrome 8-bit.
			@~japanese	@details	モノクロ8ビット
		*/
		StPFNC_Mono8 = (int)0x01080001L,
		
		/*!
			@~english	@details	Monochrome 10-bit unpacked.
			@~english	@attention	The upper 6 bits are fixed to 0.
			@~japanese	@details	モノクロ10ビット
			@~japanese	@attention	各画素ごとに16ビット(2バイト)使用され、上位6ビットは常に0になります。
		*/
		StPFNC_Mono10 = (int)0x01100003L,
		
		/*!
			@~english	@details	Monochrome 10-bit packed.
			@~english	@attention 4-pixel image is stored in 40-bit (5-Byte) data.	
			@~japanese	@details	モノクロ10ビット(Packed)
			@~japanese	@attention	4画素が5バイト(40ビット)で表現され、下位ビットから画素ごとに10ビットずつ使用されます。
		*/
		StPFNC_Mono10p = (int)0x010A0046L,

		/*!
			@~english	@details	Monochrome 12-bit unpacked.
			@~english	@attention	The upper 4 bits are fixed to 0.
			@~japanese	@details	モノクロ12ビット
			@~japanese	@attention	各画素ごとに16ビット(2バイト)使用され、上位4ビットは常に0になります。
		*/
		StPFNC_Mono12 = (int)0x01100005L,
		
		/*!
			@~english	@details	Monochrome 12-bit packed.
			@~english	@attention	2-pixel image is stored in 24-bit (3-Byte) data.
			@~japanese	@details	モノクロ12ビット(Packed)
			@~japanese	@attention	2画素が3バイト(24ビット)で表現され、下位ビットから画素ごとに12ビットずつ使用されます。
		*/
		StPFNC_Mono12p = (int)0x010C0047L,
		
		/*!
			@~english	@details	Monochrome 14-bit unpacked.
			@~english	@attention	The upper 2 bits are fixed to 0.
			@~japanese	@details	モノクロ14ビット
			@~japanese	@attention	各画素ごとに16ビット(2バイト)使用され、上位2ビットは常に0になります。
		*/
		StPFNC_Mono14 = (int)0x01100025L,

		/*!
			@~english	@details	Monochrome 14-bit packed.
			@~english	@attention	8-pixel image is stored in 112-bit (14-Byte) data.
			@~japanese	@details	モノクロ14ビット(Packed)
			@~japanese	@attention	8画素が14バイト(112ビット)で表現され、下位ビットから画素ごとに14ビットずつ使用されます。
		*/
		StPFNC_Mono14p = (int)0x010E0104L,

		/*!
			@~english	@details	Monochrome 16-bit.
			@~japanese	@details	モノクロ16ビット
		*/
		StPFNC_Mono16 = (int)0x01100007L,

		/*!
			@~english	@details	Monochrome 32-bit.
			@~japanese	@details	モノクロ32ビット
		*/
		StPFNC_Mono32 = (int)0x01200111L,

		/*!
		@~english	@details	Bayer Blue-Green 4-bit packed.
		@~english	@attention  2-pixel image is stored in 8-bit (1-Byte) data.
		@~japanese	@details	ベイヤー青緑4ビット(Packed)
		@~japanese	@attention	2画素が1バイト(8ビット)で表現され、下位ビットから画素ごとに4ビットずつ使用されます。
		*/

		StPFNC_BayerBG4p = (int)0x01040110L,

		/*!
			@~english	@details	Bayer Blue-Green 8-bit.
			@~japanese	@details	ベイヤー青緑8ビット
		*/
		StPFNC_BayerBG8 = (int)0x0108000BL,
		
		/*!
			@~english	@details	Bayer Blue-Green 10-bit unpacked.
			@~english	@attention	The upper 6 bits are fixed to 0.
			@~japanese	@details	ベイヤー青緑10ビット
			@~japanese	@attention	各画素ごとに16ビット(2バイト)使用され、上位6ビットは常に0になります。
		*/
		StPFNC_BayerBG10 = (int)0x0110000FL,
		
		/*!
			@~english	@details	Bayer Blue-Green 10-bit packed.
			@~english	@attention	4-pixel image is stored in 40-bit (5-Byte) data.
			@~japanese	@details	ベイヤー青緑10ビット(Packed)
			@~japanese	@attention	4画素が5バイト(40ビット)で表現され、下位ビットから画素ごとに10ビットずつ使用されます。
		*/
		StPFNC_BayerBG10p = (int)0x010A0052L,
		
		/*!
			@~english	@details	Bayer Blue-Green 12-bit unpacked.
			@~english	@attention	The upper 4 bits are fixed to 0.
			@~japanese	@details	ベイヤー青緑12ビット
			@~japanese	@attention	各画素ごとに16ビット(2バイト)使用され、上位4ビットは常に0になります。
		*/
		StPFNC_BayerBG12 = (int)0x01100013L,
		
		/*!
			@~english	@details	Bayer Blue-Green 12-bit packed.
			@~english	@attention	2-pixel image is stored in 24-bit (3-Byte) data.
			@~japanese	@details	ベイヤー青緑12ビット(Packed)
			@~japanese	@attention	2画素が3バイト(24ビット)で表現され、下位ビットから画素ごとに12ビットずつ使用されます。
		*/
		StPFNC_BayerBG12p = (int)0x010C0053L,

		/*!
			@~english	@details	Bayer Blue-Green 14-bit unpacked.
			@~english	@attention	The upper 2 bits are fixed to 0.
			@~japanese	@details	ベイヤー青緑14ビット
			@~japanese	@attention	各画素ごとに16ビット(2バイト)使用され、上位2ビットは常に0になります。
		*/
		StPFNC_BayerBG14 = (int)0x0110010CL,
		
		/*!
			@~english	@details	Bayer Blue-Green 14-bit packed.
			@~english	@attention	8-pixel image is stored in 112-bit (14-Byte) data.
			@~japanese	@details	ベイヤー青緑14ビット(Packed)
			@~japanese	@attention	8画素が14バイト(112ビット)で表現され、下位ビットから画素ごとに14ビットずつ使用されます。
		*/
		StPFNC_BayerBG14p = (int)0x010E0108L,

		/*!
			@~english	@details	Bayer Blue-Green 16-bit.
			@~japanese	@details	ベイヤー青緑16ビット
		*/
		StPFNC_BayerBG16 = (int)0x01100031L,

		/*!
		@~english	@details	Bayer Green-Blue 4-bit packed.
		@~english	@attention  2-pixel image is stored in 8-bit (1-Byte) data.
		@~japanese	@details	ベイヤー緑青4ビット(Packed)
		@~japanese	@attention	2画素が1バイト(8ビット)で表現され、下位ビットから画素ごとに4ビットずつ使用されます。
		*/

		StPFNC_BayerGB4p = (int)0x0104010FL,

		/*!
			@~english	@details	Bayer Green-Blue 8-bit.
			@~japanese	@details	ベイヤー緑青8ビット
		*/
		StPFNC_BayerGB8 = (int)0x0108000AL,
		
		/*!
			@~english	@details	Bayer Green-Blue 10-bit unpacked.
			@~english	@attention	The upper 6 bits are fixed to 0.
			@~japanese	@details	ベイヤー緑青10ビット
			@~japanese	@attention	各画素ごとに16ビット(2バイト)使用され、上位6ビットは常に0になります。
		*/
		StPFNC_BayerGB10 = (int)0x0110000EL,
		
		/*!
			@~english	@details	Bayer Green-Blue 10-bit packed.
			@~english	@attention  4-pixel image is stored in 40-bit (5-Byte) data.
			@~japanese	@details	ベイヤー緑青10ビット(Packed)
			@~japanese	@attention	4画素が5バイト(40ビット)で表現され、下位ビットから画素ごとに10ビットずつ使用されます。
		*/
		StPFNC_BayerGB10p = (int)0x010A0054L,
		
		/*!
			@~english	@details	Bayer Green-Blue 12-bit unpacked.
			@~english	@attention	The upper 4 bits are fixed to 0.
			@~japanese	@details	ベイヤー緑青12ビット
			@~japanese	@attention	各画素ごとに16ビット(2バイト)使用され、上位4ビットは常に0になります。
		*/
		StPFNC_BayerGB12 = (int)0x01100012L,
		
		/*!
			@~english	@details	Bayer Green-Blue 12-bit packed.
			@~english	@attention	2-pixel image is stored in 24-bit (3-Byte) data.
			@~japanese	@details	ベイヤー緑青12ビット(Packed)
			@~japanese	@attention	2画素が3バイト(24ビット)で表現され、下位ビットから画素ごとに12ビットずつ使用されます。
		*/
		StPFNC_BayerGB12p = (int)0x010C0055L,

		/*!
			@~english	@details	Bayer Green-Blue 14-bit unpacked.
			@~english	@attention	The upper 2 bits are fixed to 0.
			@~japanese	@details	ベイヤー緑青14ビット
			@~japanese	@attention	各画素ごとに16ビット(2バイト)使用され、上位2ビットは常に0になります。
		*/
		StPFNC_BayerGB14 = (int)0x0110010BL,

		/*!
			@~english	@details	Bayer Green-Blue 14-bit packed.
			@~english	@attention	8-pixel image is stored in 112-bit (14-Byte) data.
			@~japanese	@details	ベイヤー緑青14ビット(Packed)
			@~japanese	@attention	8画素が14バイト(112ビット)で表現され、下位ビットから画素ごとに14ビットずつ使用されます。
		*/
		StPFNC_BayerGB14p = (int)0x010E0107L,

		/*!
			@~english	@details	Bayer Green-Blue 16-bit.
			@~japanese	@details	ベイヤー緑青16ビット
		*/
		StPFNC_BayerGB16 = (int)0x01100030L,

		/*!
		@~english	@details	Bayer Green-Red 4-bit packed.
		@~english	@attention  2-pixel image is stored in 8-bit (1-Byte) data.
		@~japanese	@details	ベイヤー緑赤4ビット(Packed)
		@~japanese	@attention	2画素が1バイト(8ビット)で表現され、下位ビットから画素ごとに4ビットずつ使用されます。
		*/
		StPFNC_BayerGR4p = (int)0x0104010DL,

		/*!
			@~english	@details	Bayer Green-Red 8-bit.
			@~japanese	@details	ベイヤー緑赤8ビット
		*/
		StPFNC_BayerGR8 = (int)0x01080008L,
		
		/*!
			@~english	@details	Bayer Green-Red 10-bit unpacked.
			@~english	@attention	The upper 6 bits are fixed to 0.
			@~japanese	@details	ベイヤー緑赤10ビット
			@~japanese	@attention	各画素ごとに16ビット(2バイト)使用され、上位6ビットは常に0になります。
		*/
		StPFNC_BayerGR10 = (int)0x0110000CL,
		
		/*!
			@~english	@details	Bayer Green-Red 10-bit packed.
			@~english	@attention	4-pixel image is stored in 40-bit (5-Byte) data.
			@~japanese	@details	ベイヤー緑赤10ビット(Packed)
			@~japanese	@attention	4画素が5バイト(40ビット)で表現され、下位ビットから画素ごとに10ビットずつ使用されます。
		*/
		StPFNC_BayerGR10p = (int)0x010A0056L,
		
		/*!
			@~english	@details	Bayer Green-Red 12-bit unpacked.
			@~english	@attention	The upper 4 bits are fixed to 0.
			@~japanese	@details	ベイヤー緑赤12ビット
			@~japanese	@attention	各画素ごとに16ビット(2バイト)使用され、上位4ビットは常に0になります。
		*/
		StPFNC_BayerGR12 = (int)0x01100010L,
		
		/*!
			@~english	@details	Bayer Green-Red 12-bit packed.
			@~english	@attention	2-pixel image is stored in 24-bit (3-Byte) data.
			@~japanese	@details	ベイヤー緑赤12ビット(Packed)
			@~japanese	@attention	2画素が3バイト(24ビット)で表現され、下位ビットから画素ごとに12ビットずつ使用されます。
		*/
		StPFNC_BayerGR12p = (int)0x010C0057L,

		/*!
			@~english	@details	Bayer Green-Red 14-bit unpacked.
			@~english	@attention	The upper 2 bits are fixed to 0.
			@~japanese	@details	ベイヤー緑赤14ビット
			@~japanese	@attention	各画素ごとに16ビット(2バイト)使用され、上位2ビットは常に0になります。
		*/
		StPFNC_BayerGR14 = (int)0x01100109L,
		
		/*!
			@~english	@details	Bayer Green-Red 14-bit packed.
			@~english	@attention	8-pixel image is stored in 112-bit (14-Byte) data.
			@~japanese	@details	ベイヤー緑赤14ビット(Packed)
			@~japanese	@attention	8画素が14バイト(112ビット)で表現され、下位ビットから画素ごとに14ビットずつ使用されます。
		*/
		StPFNC_BayerGR14p = (int)0x010E0105L,

		/*!
			@~english	@details	Bayer Green-Red 16-bit.
			@~japanese	@details	ベイヤー緑赤16ビット
		*/
		StPFNC_BayerGR16 = (int)0x0110002EL,

		/*!
		@~english	@details	Bayer Red-Green 4-bit packed.
		@~english	@attention  2-pixel image is stored in 8-bit (1-Byte) data.
		@~japanese	@details	ベイヤー赤緑4ビット(Packed)
		@~japanese	@attention	2画素が1バイト(8ビット)で表現され、下位ビットから画素ごとに4ビットずつ使用されます。
		*/
		StPFNC_BayerRG4p = (int)0x0104010EL,

		/*!
			@~english	@details	Bayer Red-Green 8-bit.
			@~japanese	@details	ベイヤー赤緑8ビット
		*/
		StPFNC_BayerRG8 = (int)0x01080009L,
		
		/*!
			@~english	@details	Bayer Red-Green 10-bit unpacked.
			@~english	@attention	The upper 6 bits are fixed to 0.
			@~japanese	@details	ベイヤー赤緑10ビット
			@~japanese	@attention	各画素ごとに16ビット(2バイト)使用され、上位6ビットは常に0になります。
		*/
		StPFNC_BayerRG10 = (int)0x0110000DL,
		
		/*!
			@~english	@details	Bayer Red-Green 10-bit packed.
			@~english	@attention	4-pixel image is stored in 40-bit (5-Byte) data.
			@~japanese	@details	ベイヤー赤緑10ビット(Packed)
			@~japanese	@attention	4画素が5バイト(40ビット)で表現され、下位ビットから画素ごとに10ビットずつ使用されます。
		*/
		StPFNC_BayerRG10p = (int)0x010A0058L,
		
		/*!
			@~english	@details	Bayer Red-Green 12-bit unpacked.
			@~english	@attention	The upper 4 bits are fixed to 0.
			@~japanese	@details	ベイヤー赤緑12ビット
			@~japanese	@attention	各画素ごとに16ビット(2バイト)使用され、上位4ビットは常に0になります。
		*/
		StPFNC_BayerRG12 = (int)0x01100011L,
		
		/*!
			@~english	@details	Bayer Red-Green 12-bit packed.
			@~english	@attention	2-pixel image is stored in 24-bit (3-Byte) data.
			@~japanese	@details	ベイヤー赤緑12ビット(Packed)
			@~japanese	@attention	2画素が3バイト(24ビット)で表現され、下位ビットから画素ごとに12ビットずつ使用されます。
		*/
		StPFNC_BayerRG12p = (int)0x010C0059L,

		/*!
			@~english	@details	Bayer Red-Green 14-bit unpacked.
			@~english	@attention	The upper 2 bits are fixed to 0.
			@~japanese	@details	ベイヤー赤緑14ビット
			@~japanese	@attention	各画素ごとに16ビット(2バイト)使用され、上位2ビットは常に0になります。
		*/
		StPFNC_BayerRG14 = (int)0x0110010AL,

		/*!
			@~english	@details	Bayer Red-Green 14-bit packed.
			@~english	@attention	8-pixel image is stored in 112-bit (14-Byte) data.
			@~japanese	@details	ベイヤー赤緑14ビット(Packed)
			@~japanese	@attention	8画素が14バイト(112ビット)で表現され、下位ビットから画素ごとに14ビットずつ使用されます。
		*/
		StPFNC_BayerRG14p = (int)0x010E0106L,

		/*!
			@~english	@details	Bayer Red-Green 16-bit.
			@~japanese	@details	ベイヤー赤緑16ビット
		*/
		StPFNC_BayerRG16 = (int)0x0110002FL,

		/*!
			@~english	@details	Red-Green-Blue-alpha 8-bit.
			@~english	@attention	In StApi, alpha channel is not used (undefined value).
			@~japanese	@details	赤-緑-青-α 8ビット
			@~japanese	@attention	StApiではαチャンネルは使用しておらず、値は不定になります。
		*/
		StPFNC_RGBa8 = (int)0x02200016L,

		/*!
			@~english	@details	Red-Green-Blue 8-bit.
			@~japanese	@details	赤-緑-青 8ビット
		*/
		StPFNC_RGB8 = (int)0x02180014L,

		/*!
			@~english	@details	Red-Green-Blue 10-bit packed into 32-bit.
			@~english	@attention	The upper 2 bits are fixed to 0.
			@~japanese	@details	赤-緑-青 10ビット(32ビットPacked)
			@~japanese	@attention	各チャンネルごとに10ビット使用され、各画素32ビットの上位2ビットは常に0になります。
		*/
		StPFNC_RGB10p32 = (int)0x0220001DL,
		
		/*!
			@~english	@details	Blue-Green-Red-alpha 8-bit.
			@~english	@attention	In StApi, alpha channel is not used (undefined value).
			@~japanese	@details	青-緑-赤-α 8ビット
			@~japanese	@attention	StApiではαチャンネルは使用しておらず、値は不定になります。
		*/
		StPFNC_BGRa8 = (int)0x02200017L,
		
		/*!
			@~english	@details	Blue-Green-Red-alpha 10-bit unpacked.
			@~english	@attention	The upper 6 bits are fixed to 0. In StApi, alpha channel is not used (undefined value).
			@~japanese	@details	青-緑-赤-α 10ビット
			@~japanese	@attention	各チャンネルごとに16ビット(2バイト)使用され、上位6ビットは常に0になります。StApiではαチャンネルは使用しておらず、値は不定になります。
		*/
		StPFNC_BGRa10 = (int)0x0240004CL,

		/*!
			@~english	@details	Blue-Green-Red-alpha 12-bit unpacked.
			@~english	@attention	The upper 4 bits are fixed to 0. In StApi, alpha channel is not used (undefined value).
			@~japanese	@details	青-緑-赤-α 12ビット
			@~japanese	@attention	各チャンネルごとに16ビット(2バイト)使用され、上位4ビットは常に0になります。StApiではαチャンネルは使用しておらず、値は不定になります。
		*/
		StPFNC_BGRa12 = (int)0x0240004EL,

		/*!
			@~english	@details	Blue-Green-Red-alpha 14-bit unpacked.
			@~english	@attention	The upper 2 bits are fixed to 0. In StApi, alpha channel is not used (undefined value).
			@~japanese	@details	青-緑-赤-α 14ビット
			@~japanese	@attention	各チャンネルごとに16ビット(2バイト)使用され、上位2ビットは常に0になります。StApiではαチャンネルは使用しておらず、値は不定になります。
		*/
		StPFNC_BGRa14 = (int)0x02400050L,

		/*!
			@~english	@details	Blue-Green-Red-alpha 16-bit.
			@~english	@attention	In StApi, alpha channel is not used (undefined value).
			@~japanese	@details	青-緑-赤-α 16ビット
			@~japanese	@attention	StApiではαチャンネルは使用しておらず、値は不定になります。
		*/
		StPFNC_BGRa16 = (int)0x02400051L,
		
		/*!
			@~english	@details	Blue-Green-Red 8-bit.
			@~japanese	@details	青-緑-赤 8ビット
		*/
		StPFNC_BGR8 = (int)0x02180015L,

		/*!
			@~english	@details	Blue-Green-Red 10-bit unpacked.
			@~english	@attention	The upper 6 bits are fixed to 0.
			@~japanese	@details	青-緑-赤 10ビット
			@~japanese	@attention	各チャンネルごとに16ビット(2バイト)使用され、上位6ビットは常に0になります。
		*/
		StPFNC_BGR10 = (int)0x02300019L,

		/*!
			@~english	@details	Blue-Green-Red 12-bit unpacked.
			@~english	@attention	The upper 4 bits are fixed to 0.
			@~japanese	@details	青-緑-赤 12ビット
			@~japanese	@attention	各チャンネルごとに16ビット(2バイト)使用され、上位4ビットは常に0になります。
		*/
		StPFNC_BGR12 = (int)0x0230001BL,

		/*!
			@~english	@details	Blue-Green-Red 14-bit unpacked.
			@~english	@attention	The upper 2 bits are fixed to 0.
			@~japanese	@details	青-緑-赤 14ビット
			@~japanese	@attention	各チャンネルごとに16ビット(2バイト)使用され、上位2ビットは常に0になります。
		*/
		StPFNC_BGR14 = (int)0x0230004AL,

		/*!
			@~english	@details	Blue-Green-Red 16-bit.
			@~japanese	@details	青-緑-赤 16ビット
		*/
		StPFNC_BGR16 = (int)0x0230004BL,

		/*!
		@~english	@details	Red - Green - Blue 8 - bit planar.
		@~japanese	@details	赤-緑-青 8ビット プラナー
		*/
		StPFNC_RGB8_Planar = (int)0x02180021L,

		/*!
		@~english	@details	Red - Green - Blue 10 - bit unpacked planar.
		@~japanese	@details	赤-緑-青 10ビット プラナー
		*/
		StPFNC_RGB10_Planar = (int)0x02300022L,

		/*!
		@~english	@details	Red - Green - Blue 12 - bit unpacked planar.
		@~japanese	@details	赤-緑-青 12ビット プラナー
		*/
		StPFNC_RGB12_Planar = (int)0x02300023L,

		/*!
		@~english	@details	Red - Green - Blue 16 - bit planar.
		@~japanese	@details	赤-緑-青 16ビット プラナー
		*/
		StPFNC_RGB16_Planar = (int)0x02300024L,

		/*!
			@~english	@details	Blue - Green - Red 10 - bit packed.
			@~english	@attention	4-pixel image is stored in 120-bit (15-Byte) data.
			@~japanese	@details	青-緑-赤 10ビット パックド(Packed)
			@~japanese	@attention	4画素が15バイト(120ビット)で表現され、下位ビットから画素ごとに30ビットずつ使用されます。
		*/
		StPFNC_BGR10p = (int)0x021E0048L,

		/*!
			@~english	@details	Blue - Green - Red 12 - bit packed.
			@~english	@attention	2-pixel image is stored in 72-bit (9-Byte) data.
			@~japanese	@details	青-緑-赤 12ビット パックド(Packed)
			@~japanese	@attention	2画素が9バイト(72ビット)で表現され、下位ビットから画素ごとに36ビットずつ使用されます。
		*/
		StPFNC_BGR12p = (int)0x02240049L,

		/*!
			@~english	@details	Red - Green - Blue 10 - bit packed.
			@~english	@attention	4-pixel image is stored in 120-bit (15-Byte) data.
			@~japanese	@details	赤-緑-青 10ビット パックド(Packed)
			@~japanese	@attention	4画素が15バイト(120ビット)で表現され、下位ビットから画素ごとに30ビットずつ使用されます。
		*/
		StPFNC_RGB10p = (int)0x021E005CL,

		/*!
			@~english	@details	Red - Green - Blue 12 - bit packed.
			@~english	@attention	2-pixel image is stored in 72-bit (9-Byte) data.
			@~japanese	@details	赤-緑-青 12ビット パックド(Packed)
			@~japanese	@attention	2画素が9バイト(72ビット)で表現され、下位ビットから画素ごとに36ビットずつ使用されます。
		*/
		StPFNC_RGB12p = (int)0x0224005DL,

		/*!
			@~english	@details	Red-Green-Blue 16-bit.
			@~japanese	@details	赤-緑-青 16ビット
		*/
		StPFNC_RGB16 = (int)0x02300033L,


		/*!
			@~english	@details	Blue-Green-Red 10-bit packed into 32-bit.
			@~english	@attention	The upper 2 bits are fixed to 0.
			@~japanese	@details	青-緑-赤 10ビット(32ビットPacked)
			@~japanese	@attention	各チャンネルごとに10ビット使用され、各画素32ビットの上位2ビットは常に0になります。
		*/
		StPFNC_CBGR10p32 = (int)0x82200001L,
		
		/*!
			@~english	@details	YCbCr 4:4:4 8-bit.
			@~english	@attention	YCbCrYCbCrYCbCrYCbCr.
			@~japanese	@details	YCbCr 4:4:4 8ビット
			@~japanese	@attention	画素値はYCbCrYCbCrYCbCrYCbCrのような並びになります。Yの範囲は0～255、CbおよびCrの範囲は128シフトされた状態で0から255になります。RGBとの変換式は下記のとおりです。

						Y = 0.299 x R + 0.587 x G + 0.114 x B
						Cb = -0.16874 x R - 0.33126 x G + 0.5000 x B + 128
						Cr = 0.5000 x R - 0.41869 x G - 0.08131 x B + 128
						
						R = Y + 1.40200 x (Cr - 128)
						G = Y - 0.34414 x (Cb - 128) - 0.71414 x (Cr - 128)
						B = Y + 1.77200 x (Cb - 128)
		*/
		StPFNC_YCbCr8 = (int)0x0218005BL,
		
		/*!
			@~english	@details	YCbCr 4:1:1 8-bit.
			@~english	@attention	YYCbYYCr.
			@~japanese	@details	YCbCr 4:1:1 8ビット
			@~japanese	@attention	画素値はYYCbYYCrのような並びになります。Yの範囲は0～255、CbおよびCrの範囲は128シフトされた状態で0から255になります。RGBとの変換式は下記のとおりです。

						Y = 0.299 x R + 0.587 x G + 0.114 x B
						Cb = -0.16874 x R - 0.33126 x G + 0.5000 x B + 128
						Cr = 0.5000 x R - 0.41869 x G - 0.08131 x B + 128
						
						R = Y + 1.40200 x (Cr - 128)
						G = Y - 0.34414 x (Cb - 128) - 0.71414 x (Cr - 128)
						B = Y + 1.77200 x (Cb - 128)
		*/
		StPFNC_YCbCr411_8 = (int)0x020C005AL,

		/*!
			@~english	@details	YCbCr 4:2:2 8-bit.
			@~english	@attention	YCbYCrYCbYCr.
			@~japanese	@details	YCbCr 4:2:2 8ビット
			@~japanese	@attention	画素値はYCbYCrYCbYCrのような並びになります。Yの範囲は0～255、CbおよびCrの範囲は128シフトされた状態で0から255になります。RGBとの変換式は下記のとおりです。

						Y = 0.299 x R + 0.587 x G + 0.114 x B
						Cb = -0.16874 x R - 0.33126 x G + 0.5000 x B + 128
						Cr = 0.5000 x R - 0.41869 x G - 0.08131 x B + 128
						
						R = Y + 1.40200 x (Cr - 128)
						G = Y - 0.34414 x (Cb - 128) - 0.71414 x (Cr - 128)
						B = Y + 1.77200 x (Cb - 128)
		*/
		StPFNC_YCbCr422_8 = (int)0x0210003BL,

		/*!
			@~english	@details	YCbCr 4:2:2 8-bit BT.709.
			@~english	@attention	YCbYCrYCbYCr.
			@~japanese	@details	YCbCr 4:2:2 8ビット BT.709
			@~japanese	@attention	画素値はYCbYCrYCbYCrのような並びになります。Yの範囲は16～235、CbおよびCrの範囲は128シフトされた状態で16から240になります。RGBとの変換式は下記のとおりです。
									Y = 0.18259 x R + 0.61423 x G + 0.06201 x B + 16
									Cb = -0.10064 x R - 0.33857 x G + 0.43922 x B + 128
									Cr = 0.43922 x R - 0.39894 x G - 0.04027 x B + 128

									R = 1.16438 x (Y - 16) + 1.79274 x (Cr - 128)
									G = 1.16438 x (Y - 16) - 0.21325 x (Cb - 128) - 0.53291 x (Cr - 128)
									B = 1.16438 x (Y - 16) + 2.11240 x (Cb - 128)
		*/
		StPFNC_YCbCr709_422_8 = (int)0x02100041L,
		
		/*!
			@~english	@details	YCbCr 4:2:2 8-bit BT.601.
			@~english	@attention	YCbYCrYCbYCr.
			@~japanese	@details	YCbCr 4:2:2 8ビット BT.601
			@~japanese	@attention	画素値はYCbYCrYCbYCrのような並びになります。Yの範囲は16～235、CbおよびCrの範囲は128シフトされた状態で16から240になります。RGBとの変換式は下記のとおりです。
									Y = 0.25679 x R + 0.50413 x G + 0.09791 x B + 16
									Cb = -0.14822 x R - 0.29099 x G + 0.43922 x B + 128
									Cr = 0.43922 x R - 0.36779 x G - 0.07143 x B + 128

									R = 1.16438 x (Y - 16) + 1.59603 x (Cr - 128)
									G = 1.16438 x (Y - 16) - 0.39176 x (Cb - 128) - 0.81297 x (Cr - 128)
									B = 1.16438 x (Y - 16) + 2.01723 x (Cb - 128)
		*/
		StPFNC_YCbCr601_422_8 = (int)0x0210003EL,

		/*!
			@~english	@details	YCbCr 4:1:1 8-bit.
			@~english	@attention	CbYYCrYY.
			@~japanese	@details	YCbCr 4:1:1 8ビット
			@~japanese	@attention	画素値はCbYYCrYYのような並びになります。Yの範囲は0～255、CbおよびCrの範囲は128シフトされた状態で0から255になります。RGBとの変換式は下記のとおりです。

			Y = 0.299 x R + 0.587 x G + 0.114 x B
			Cb = -0.16874 x R - 0.33126 x G + 0.5000 x B + 128
			Cr = 0.5000 x R - 0.41869 x G - 0.08131 x B + 128

			R = Y + 1.40200 x (Cr - 128)
			G = Y - 0.34414 x (Cb - 128) - 0.71414 x (Cr - 128)
			B = Y + 1.77200 x (Cb - 128)
		*/
		StPFNC_YCbCr411_8_CbYYCrYY = (int)0x020C003CL,

		/*!
			@~english	@details	YCbCr 4:1:1 8-bit BT.601.
			@~english	@attention	CbYYCrYY.
			@~japanese	@details	YCbCr 4:1:1 8ビット BT.601
			@~japanese	@attention	画素値はCbYYCrYYのような並びになります。Yの範囲は16～235、CbおよびCrの範囲は128シフトされた状態で16から240になります。RGBとの変換式は下記のとおりです。
			Y = 0.25679 x R + 0.50413 x G + 0.09791 x B + 16
			Cb = -0.14822 x R - 0.29099 x G + 0.43922 x B + 128
			Cr = 0.43922 x R - 0.36779 x G - 0.07143 x B + 128

			R = 1.16438 x (Y - 16) + 1.59603 x (Cr - 128)
			G = 1.16438 x (Y - 16) - 0.39176 x (Cb - 128) - 0.81297 x (Cr - 128)
			B = 1.16438 x (Y - 16) + 2.01723 x (Cb - 128)
		*/
		StPFNC_YCbCr601_411_8_CbYYCrYY = (int)0x020C003FL,

		/*!
			@~english	@details	YCbCr 4:1:1 8-bit BT.709.
			@~english	@attention	CbYYCrYY.
			@~japanese	@details	YCbCr 4:1:1 8ビット BT.709
			@~japanese	@attention	画素値はCbYYCrYYのような並びになります。Yの範囲は16～235、CbおよびCrの範囲は128シフトされた状態で16から240になります。RGBとの変換式は下記のとおりです。
			Y = 0.18259 x R + 0.61423 x G + 0.06201 x B + 16
			Cb = -0.10064 x R - 0.33857 x G + 0.43922 x B + 128
			Cr = 0.43922 x R - 0.39894 x G - 0.04027 x B + 128

			R = 1.16438 x (Y - 16) + 1.79274 x (Cr - 128)
			G = 1.16438 x (Y - 16) - 0.21325 x (Cb - 128) - 0.53291 x (Cr - 128)
			B = 1.16438 x (Y - 16) + 2.11240 x (Cb - 128)
		*/
		StPFNC_YCbCr709_411_8_CbYYCrYY = (int)0x020C0042L,

		/*!
			@~english	@details	YCbCr 4:2:2 8-bit.
			@~english	@attention	CbYCrYCbYCrY.
			@~japanese	@details	YCbCr 4:2:2 8ビット
			@~japanese	@attention	画素値はCbYCrYCbYCrYのような並びになります。Yの範囲は0～255、CbおよびCrの範囲は128シフトされた状態で0から255になります。RGBとの変換式は下記のとおりです。

			Y = 0.299 x R + 0.587 x G + 0.114 x B
			Cb = -0.16874 x R - 0.33126 x G + 0.5000 x B + 128
			Cr = 0.5000 x R - 0.41869 x G - 0.08131 x B + 128

			R = Y + 1.40200 x (Cr - 128)
			G = Y - 0.34414 x (Cb - 128) - 0.71414 x (Cr - 128)
			B = Y + 1.77200 x (Cb - 128)
		*/
		StPFNC_YCbCr422_8_CbYCrY = (int)0x02100043L,

		/*!
			@~english	@details	YCbCr 4:2:2 8-bit BT.601.
			@~english	@attention	CbYCrYCbYCrY.
			@~japanese	@details	YCbCr 4:2:2 8ビット BT.601
			@~japanese	@attention	画素値はCbYCrYCbYCrYのような並びになります。Yの範囲は16～235、CbおよびCrの範囲は128シフトされた状態で16から240になります。RGBとの変換式は下記のとおりです。
			Y = 0.25679 x R + 0.50413 x G + 0.09791 x B + 16
			Cb = -0.14822 x R - 0.29099 x G + 0.43922 x B + 128
			Cr = 0.43922 x R - 0.36779 x G - 0.07143 x B + 128

			R = 1.16438 x (Y - 16) + 1.59603 x (Cr - 128)
			G = 1.16438 x (Y - 16) - 0.39176 x (Cb - 128) - 0.81297 x (Cr - 128)
			B = 1.16438 x (Y - 16) + 2.01723 x (Cb - 128)
		*/
		StPFNC_YCbCr601_422_8_CbYCrY = (int)0x02100044L,

		/*!
			@~english	@details	YCbCr 4:2:2 8-bit BT.709.
			@~english	@attention	CbYCrYCbYCrY.
			@~japanese	@details	YCbCr 4:2:2 8ビット BT.709
			@~japanese	@attention	画素値はCbYCrYCbYCrYのような並びになります。Yの範囲は16～235、CbおよびCrの範囲は128シフトされた状態で16から240になります。RGBとの変換式は下記のとおりです。
			Y = 0.18259 x R + 0.61423 x G + 0.06201 x B + 16
			Cb = -0.10064 x R - 0.33857 x G + 0.43922 x B + 128
			Cr = 0.43922 x R - 0.39894 x G - 0.04027 x B + 128

			R = 1.16438 x (Y - 16) + 1.79274 x (Cr - 128)
			G = 1.16438 x (Y - 16) - 0.21325 x (Cb - 128) - 0.53291 x (Cr - 128)
			B = 1.16438 x (Y - 16) + 2.11240 x (Cb - 128)
		*/
		StPFNC_YCbCr709_422_8_CbYCrY = (int)0x02100045L,

		/*!
			@~english	@details	YCbCr 4:4:4 8-bit.
			@~english	@attention	CbYCrCbYCrCbYCrCbYCr.
			@~japanese	@details	YCbCr 4:4:4 8ビット
			@~japanese	@attention	画素値はCbYCrCbYCrCbYCrCbYCrのような並びになります。Yの範囲は0～255、CbおよびCrの範囲は128シフトされた状態で0から255になります。RGBとの変換式は下記のとおりです。

			Y = 0.299 x R + 0.587 x G + 0.114 x B
			Cb = -0.16874 x R - 0.33126 x G + 0.5000 x B + 128
			Cr = 0.5000 x R - 0.41869 x G - 0.08131 x B + 128

			R = Y + 1.40200 x (Cr - 128)
			G = Y - 0.34414 x (Cb - 128) - 0.71414 x (Cr - 128)
			B = Y + 1.77200 x (Cb - 128)
		*/
		StPFNC_YCbCr8_CbYCr = (int)0x0218003AL,

		/*!
			@~english	@details	YCbCr 4:4:4 8-bit BT.601.
			@~english	@attention	CbYCrCbYCrCbYCrCbYCr.
			@~japanese	@details	YCbCr 4:4:4 8ビット BT.601
			@~japanese	@attention	画素値はCbYCrCbYCrCbYCrCbYCrのような並びになります。Yの範囲は16～235、CbおよびCrの範囲は128シフトされた状態で16から240になります。RGBとの変換式は下記のとおりです。
			Y = 0.25679 x R + 0.50413 x G + 0.09791 x B + 16
			Cb = -0.14822 x R - 0.29099 x G + 0.43922 x B + 128
			Cr = 0.43922 x R - 0.36779 x G - 0.07143 x B + 128

			R = 1.16438 x (Y - 16) + 1.59603 x (Cr - 128)
			G = 1.16438 x (Y - 16) - 0.39176 x (Cb - 128) - 0.81297 x (Cr - 128)
			B = 1.16438 x (Y - 16) + 2.01723 x (Cb - 128)
		*/
		StPFNC_YCbCr601_8_CbYCr = (int)0x0218003DL,

		/*!
			@~english	@details	YCbCr 4:4:4 8-bit BT.709.
			@~english	@attention	CbYCrCbYCrCbYCrCbYCr.
			@~japanese	@details	YCbCr 4:4:4 8ビット BT.709
			@~japanese	@attention	画素値はCbYCrCbYCrCbYCrCbYCrのような並びになります。Yの範囲は16～235、CbおよびCrの範囲は128シフトされた状態で16から240になります。RGBとの変換式は下記のとおりです。
			Y = 0.18259 x R + 0.61423 x G + 0.06201 x B + 16
			Cb = -0.10064 x R - 0.33857 x G + 0.43922 x B + 128
			Cr = 0.43922 x R - 0.39894 x G - 0.04027 x B + 128

			R = 1.16438 x (Y - 16) + 1.79274 x (Cr - 128)
			G = 1.16438 x (Y - 16) - 0.21325 x (Cb - 128) - 0.53291 x (Cr - 128)
			B = 1.16438 x (Y - 16) + 2.11240 x (Cb - 128)
		*/
		StPFNC_YCbCr709_8_CbYCr = (int)0x02180040L,

		/*!
			@~english	@details	YUV 4:1:1 8-bit.
			@~english	@attention	UYYVYY.
			@~japanese	@details	YUV 4:1:1 8ビット
			@~japanese	@attention	画素値はUYYVYYのような並びになります。Yの範囲は0～255、UおよびVの範囲は128シフトされた状態で0から255になります。RGBとの変換式は下記のとおりです。

			Y = 0.299 x R + 0.587 x G + 0.114 x B
			U = -0.16874 x R - 0.33126 x G + 0.5000 x B + 128
			V = 0.5000 x R - 0.41869 x G - 0.08131 x B + 128

			R = Y + 1.40200 x (V - 128)
			G = Y - 0.34414 x (U - 128) - 0.71414 x (V - 128)
			B = Y + 1.77200 x (U - 128)
		*/
		StPFNC_YUV411_8_UYYVYY = (int)0x020C001EL,

		/*!
			@~english	@details	YUV 4:2:2 8-bit.
			@~english	@attention	UYVYUYVY.
			@~japanese	@details	YUV 4:2:2 8ビット
			@~japanese	@attention	画素値はUYVYUYVYのような並びになります。Yの範囲は0～255、UおよびVの範囲は128シフトされた状態で0から255になります。RGBとの変換式は下記のとおりです。

			Y = 0.299 x R + 0.587 x G + 0.114 x B
			U = -0.16874 x R - 0.33126 x G + 0.5000 x B + 128
			V = 0.5000 x R - 0.41869 x G - 0.08131 x B + 128

			R = Y + 1.40200 x (V - 128)
			G = Y - 0.34414 x (U - 128) - 0.71414 x (V - 128)
			B = Y + 1.77200 x (U - 128)
		*/
		StPFNC_YUV422_8_UYVY = (int)0x0210001FL,

		/*!
			@~english	@details	YUV 4:4:4 8-bit.
			@~english	@attention	UYVUYVUYVUYV.
			@~japanese	@details	YUV 4:4:4 8ビット
			@~japanese	@attention	画素値はUYVUYVUYVUYVのような並びになります。Yの範囲は0～255、UおよびVの範囲は128シフトされた状態で0から255になります。RGBとの変換式は下記のとおりです。

			Y = 0.299 x R + 0.587 x G + 0.114 x B
			U = -0.16874 x R - 0.33126 x G + 0.5000 x B + 128
			V = 0.5000 x R - 0.41869 x G - 0.08131 x B + 128

			R = Y + 1.40200 x (V - 128)
			G = Y - 0.34414 x (U - 128) - 0.71414 x (V - 128)
			B = Y + 1.77200 x (U - 128)
		*/
		StPFNC_YUV8_UYV = (int)0x02180020L,

		/*!
			@~english	@details	YUV 4:2:2 8-bit.
			@~english	@attention	YUYVYUYV.
			@~japanese	@details	YUV 4:2:2 8ビット
			@~japanese	@attention	画素値はYUYVYUYVのような並びになります。Yの範囲は0～255、UおよびVの範囲は128シフトされた状態で0から255になります。RGBとの変換式は下記のとおりです。

			Y = 0.299 x R + 0.587 x G + 0.114 x B
			U = -0.16874 x R - 0.33126 x G + 0.5000 x B + 128
			V = 0.5000 x R - 0.41869 x G - 0.08131 x B + 128

			R = Y + 1.40200 x (V - 128)
			G = Y - 0.34414 x (U - 128) - 0.71414 x (V - 128)
			B = Y + 1.77200 x (U - 128)
		*/
		StPFNC_YUV422_8 = (int)0x02100032L,


		/*!
			@~english	@details	GigE Vision specific format, Monochrome 10-bit packed.
			@~english	@attention	2-pixel image is stored in 24-bit (3-Byte) data.
			@~japanese	@details	GigEVision モノクロ10ビット(Packed)
			@~japanese	@attention	2画素が3バイト(24ビット)で表現されます。1バイト目が1画素目の上位8ビットに、3バイト目が2画素目の上位8ビットになります。2バイト目のbit1,0が1画素目の下位2ビットに、2バイト目のbit5,4が2画素目の下位2ビットになります。
		*/
		StPFNC_Mono10Packed = (int)0x010C0004L,
		StPFNC_GVSP_Mono10Packed = StPFNC_Mono10Packed,
		
		/*!
			@~english	@details	GigE Vision specific format, Monochrome 12-bit packed.
			@~english	@attention 2-pixel image is stored in 24-bit (3-Byte) data.
			@~japanese	@details	GigEVision モノクロ12ビット(Packed)
			@~japanese	@attention	2画素が3バイト(24ビット)で表現されます。1バイト目が1画素目の上位8ビットに、3バイト目が2画素目の上位8ビットになります。2バイト目のbit3,2,1,0が1画素目の下位4ビットに、2バイト目のbit7,6,5,4が2画素目の下位4ビットになります。
		*/
		StPFNC_Mono12Packed = (int)0x010C0006L,
		StPFNC_GVSP_Mono12Packed = StPFNC_Mono12Packed,
		
		/*!
			@~english	@details	GigE Vision specific format, Bayer Blue-Green 10-bit packed.
			@~english	@attention 2-pixel image is stored in 24-bit (3-Byte) data.	
			@~japanese	@details	GigEVision ベイヤー青緑10ビット(Packed)
			@~japanese	@attention	2画素が3バイト(24ビット)で表現されます。1バイト目が1画素目の上位8ビットに、3バイト目が2画素目の上位8ビットになります。2バイト目のbit1,0が1画素目の下位2ビットに、2バイト目のbit5,4が2画素目の下位2ビットになります。
		*/
		StPFNC_BayerBG10Packed = (int)0x010C0029L,
		StPFNC_GVSP_BayerBG10Packed = StPFNC_BayerBG10Packed,
		
		/*!
			@~english	@details	GigE Vision specific format, Bayer Blue-Green 12-bit packed.
			@~english	@attention 2-pixel image is stored in 24-bit (3-Byte) data.
			@~japanese	@details	GigEVision ベイヤー青緑12ビット(Packed)
			@~japanese	@attention	2画素が3バイト(24ビット)で表現されます。1バイト目が1画素目の上位8ビットに、3バイト目が2画素目の上位8ビットになります。2バイト目のbit3,2,1,0が1画素目の下位4ビットに、2バイト目のbit7,6,5,4が2画素目の下位4ビットになります。
		*/
		StPFNC_BayerBG12Packed = (int)0x010C002DL,
		StPFNC_GVSP_BayerBG12Packed = StPFNC_BayerBG12Packed,
		
		/*!
			@~english	@details	GigE Vision specific format, Bayer Green-Blue 10-bit packed.
			@~english	@attention 2-pixel image is stored in 24-bit (3-Byte) data.
			@~japanese	@details	GigEVision ベイヤー緑青10ビット(Packed)
			@~japanese	@attention	2画素が3バイト(24ビット)で表現されます。1バイト目が1画素目の上位8ビットに、3バイト目が2画素目の上位8ビットになります。2バイト目のbit1,0が1画素目の下位2ビットに、2バイト目のbit5,4が2画素目の下位2ビットになります。
		*/
		StPFNC_BayerGB10Packed = (int)0x010C0028L,
		StPFNC_GVSP_BayerGB10Packed = StPFNC_BayerGB10Packed,
		
		/*!
			@~english	@details	GigE Vision specific format, Bayer Green-Blue 12-bit packed.
			@~english	@attention 2-pixel image is stored in 24-bit (3-Byte) data.
			@~japanese	@details	GigEVision ベイヤー緑青12ビット(Packed)
			@~japanese	@attention	2画素が3バイト(24ビット)で表現されます。1バイト目が1画素目の上位8ビットに、3バイト目が2画素目の上位8ビットになります。2バイト目のbit3,2,1,0が1画素目の下位4ビットに、2バイト目のbit7,6,5,4が2画素目の下位4ビットになります。
		*/
		StPFNC_BayerGB12Packed = (int)0x010C002CL,
		StPFNC_GVSP_BayerGB12Packed = StPFNC_BayerGB12Packed,
		
		/*!
			@~english	@details	GigE Vision specific format, Bayer Green-Red 10-bit packed.
			@~english	@attention 2-pixel image is stored in 24-bit (3-Byte) data.
			@~japanese	@details	GigEVision ベイヤー緑赤10ビット(Packed)
			@~japanese	@attention	2画素が3バイト(24ビット)で表現されます。1バイト目が1画素目の上位8ビットに、3バイト目が2画素目の上位8ビットになります。2バイト目のbit1,0が1画素目の下位2ビットに、2バイト目のbit5,4が2画素目の下位2ビットになります。
		*/
		StPFNC_BayerGR10Packed = (int)0x010C0026L,
		StPFNC_GVSP_BayerGR10Packed = StPFNC_BayerGR10Packed,
		
		/*!
			@~english	@details	GigE Vision specific format, Bayer Green-Red 12-bit packed.
			@~english	@attention 2-pixel image is stored in 24-bit (3-Byte) data.
			@~japanese	@details	GigEVision ベイヤー緑赤12ビット(Packed)
			@~japanese	@attention	2画素が3バイト(24ビット)で表現されます。1バイト目が1画素目の上位8ビットに、3バイト目が2画素目の上位8ビットになります。2バイト目のbit3,2,1,0が1画素目の下位4ビットに、2バイト目のbit7,6,5,4が2画素目の下位4ビットになります。
		*/
		StPFNC_BayerGR12Packed = (int)0x010C002AL,
		StPFNC_GVSP_BayerGR12Packed = StPFNC_BayerGR12Packed,
		
		/*!
			@~english	@details	GigE Vision specific format, Bayer Red-Green 10-bit packed.
			@~english	@attention 2-pixel image is stored in 24-bit (3-Byte) data.
			@~japanese	@details	GigEVision ベイヤー赤緑10ビット(Packed)
			@~japanese	@attention	2画素が3バイト(24ビット)で表現されます。1バイト目が1画素目の上位8ビットに、3バイト目が2画素目の上位8ビットになります。2バイト目のbit1,0が1画素目の下位2ビットに、2バイト目のbit5,4が2画素目の下位2ビットになります。
		*/
		StPFNC_BayerRG10Packed = (int)0x010C0027L,
		StPFNC_GVSP_BayerRG10Packed = StPFNC_BayerRG10Packed,
		
		/*!
			@~english	@details	GigE Vision specific format, Bayer Red-Green 12-bit packed.
			@~english	@attention 2-pixel image is stored in 24-bit (3-Byte) data.
			@~japanese	@details	GigEVision ベイヤー赤緑12ビット(Packed)
			@~japanese	@attention	2画素が3バイト(24ビット)で表現されます。1バイト目が1画素目の上位8ビットに、3バイト目が2画素目の上位8ビットになります。2バイト目のbit3,2,1,0が1画素目の下位4ビットに、2バイト目のbit7,6,5,4が2画素目の下位4ビットになります。
		*/
		StPFNC_BayerRG12Packed = (int)0x010C002BL,
		StPFNC_GVSP_BayerRG12Packed = StPFNC_BayerRG12Packed,


		/*!
			@~english	@details	Data 8 - bit
		*/
		StPFNC_Data8 = (int)0x01080116L,


		/*!
			@~english	@details	Data 8 - bit signed
		*/
		StPFNC_Data8s = (int)0x01080117L,

		/*!
			@~english	@details	Data 16 - bit
		*/
		StPFNC_Data16 = (int)0x01100118L,

		/*!
			@~english	@details	Data 16 - bit signed
		*/
		StPFNC_Data16s = (int)0x01100119L,


		/*!
			@~english	@details	Data 32 - bit
		*/
		StPFNC_Data32 = (int)0x0120011AL,

		/*!
			@~english	@details	Data 32 - bit floating point
		*/
		StPFNC_Data32f = (int)0x0120011CL,

		/*!
			@~english	@details	Data 32 - bit signed
		*/
		StPFNC_Data32s = (int)0x0120011BL,


		/*!
			@~english	@details	Data 64 - bit
		*/
		StPFNC_Data64 = (int)0x0140011DL,

		/*!
			@~english	@details	Data 64 - bit floating point
		*/
		StPFNC_Data64f = (int)0x0140011FL,
		

		/*!
			@~english	@details	Data 64 - bit signed
		*/
		StPFNC_Data64s = (int)0x0140011EL,

		/*!
			@~english	@details	Monochrome 8-bit with polarization filters(90, 45, 135, 0).
			@~japanese	@details	モノクロ8ビット(偏光フィルタ角度 90, 45, 135, 0)
		*/
		StPFNC_Pol1Mono8 = (int)0x81080002L,

		/*!
			@~english	@details	Monochrome 8-bit with polarization filters(45, 90, 0, 135).
			@~japanese	@details	モノクロ8ビット(偏光フィルタ角度 45, 90, 0, 135)
			@since StApi v1.1.2
		*/
		StPFNC_Pol1MonoX8 = (int)0x81080003L,

		/*!
			@~english	@details	Monochrome 8-bit with polarization filters(135, 0, 90, 45).
			@~japanese	@details	モノクロ8ビット(偏光フィルタ角度 135, 0, 90, 45)
			@since StApi v1.1.2
		*/
		StPFNC_Pol1MonoY8 = (int)0x81080004L,

		/*!
			@~english	@details	Monochrome 8-bit with polarization filters(0, 135, 45, 90).
			@~japanese	@details	モノクロ8ビット(偏光フィルタ角度 0, 135, 45, 90)
			@since StApi v1.1.2
		*/
		StPFNC_Pol1MonoXY8 = (int)0x81080005L,

		/*!
			@~english	@details	Monochrome 10-bit unpacked with polarization filters(90, 45, 135, 0).
			@~english	@attention	The upper 6 bits are fixed to 0.
			@~japanese	@details	モノクロ12ビット(偏光フィルタ角度 90, 45, 135, 0)
			@~japanese	@attention	各画素ごとに16ビット(2バイト)使用され、上位6ビットは常に0になります。
			@since StApi v1.1.2
		*/
		StPFNC_Pol1Mono10 = (int)0x81100006L,

		/*!
			@~english	@details	Monochrome 10-bit unpacked with polarization filters(45, 90, 0, 135).
			@~english	@attention	The upper 6 bits are fixed to 0.
			@~japanese	@details	モノクロ12ビット(偏光フィルタ角度 45, 90, 0, 135)
			@~japanese	@attention	各画素ごとに16ビット(2バイト)使用され、上位6ビットは常に0になります。
			@since StApi v1.1.2
		*/
		StPFNC_Pol1MonoX10 = (int)0x81100007L,

		/*!
			@~english	@details	Monochrome 10-bit unpacked with polarization filters(135, 0, 90, 45).
			@~english	@attention	The upper 6 bits are fixed to 0.
			@~japanese	@details	モノクロ12ビット(偏光フィルタ角度 135, 0, 90, 45)
			@~japanese	@attention	各画素ごとに16ビット(2バイト)使用され、上位6ビットは常に0になります。
			@since StApi v1.1.2
		*/
		StPFNC_Pol1MonoY10 = (int)0x81100008L,

		/*!
			@~english	@details	Monochrome 10-bit unpacked with polarization filters(0, 135, 45, 90).
			@~english	@attention	The upper 6 bits are fixed to 0.
			@~japanese	@details	モノクロ12ビット(偏光フィルタ角度 0, 135, 45, 90)
			@~japanese	@attention	各画素ごとに16ビット(2バイト)使用され、上位6ビットは常に0になります。
			@since StApi v1.1.2
		*/
		StPFNC_Pol1MonoXY10 = (int)0x81100009L,

		/*!
			@~english	@details	Monochrome 12-bit unpacked with polarization filters(90, 45, 135, 0).
			@~english	@attention	The upper 4 bits are fixed to 0.
			@~japanese	@details	モノクロ12ビット(偏光フィルタ角度 90, 45, 135, 0)
			@~japanese	@attention	各画素ごとに12ビット(2バイト)使用され、上位4ビットは常に0になります。
			@since StApi v1.1.2
		*/
		StPFNC_Pol1Mono12 = (int)0x8110000AL,

		/*!
			@~english	@details	Monochrome 12-bit unpacked with polarization filters(45, 90, 0, 135).
			@~english	@attention	The upper 4 bits are fixed to 0.
			@~japanese	@details	モノクロ12ビット(偏光フィルタ角度 45, 90, 0, 135)
			@~japanese	@attention	各画素ごとに12ビット(2バイト)使用され、上位4ビットは常に0になります。
			@since StApi v1.1.2
		*/
		StPFNC_Pol1MonoX12 = (int)0x8110000BL,

		/*!
			@~english	@details	Monochrome 12-bit unpacked with polarization filters(135, 0, 90, 45).
			@~english	@attention	The upper 4 bits are fixed to 0.
			@~japanese	@details	モノクロ12ビット(偏光フィルタ角度 135, 0, 90, 45)
			@~japanese	@attention	各画素ごとに12ビット(2バイト)使用され、上位4ビットは常に0になります。
			@since StApi v1.1.2
		*/
		StPFNC_Pol1MonoY12 = (int)0x8110000CL,

		/*!
			@~english	@details	Monochrome 12-bit unpacked with polarization filters(0, 135, 45, 90).
			@~english	@attention	The upper 4 bits are fixed to 0.
			@~japanese	@details	モノクロ12ビット(偏光フィルタ角度 0, 135, 45, 90)
			@~japanese	@attention	各画素ごとに12ビット(2バイト)使用され、上位4ビットは常に0になります。
			@since StApi v1.1.2
		*/
		StPFNC_Pol1MonoXY12 = (int)0x8110000DL,

		/*!
			@~english	@details	Bayer Red-Green 8-bit with polarization filters(90, 45, 135, 0).
			@~japanese	@details	ベイヤー赤緑8ビット(偏光フィルタ角度 90, 45, 135, 0)
			@since StApi v1.1.2
		*/
		StPFNC_Pol1BayerRG8 = (int)0x8108000EL,

		/*!
			@~english	@details	Bayer Green-Red 8-bit with polarization filters(45, 90, 0, 135).
			@~japanese	@details	ベイヤー緑赤8ビット(偏光フィルタ角度 45, 90, 0, 135)
			@since StApi v1.1.2
		*/
		StPFNC_Pol1BayerRGX8 = (int)0x8108000FL,

		/*!
			@~english	@details	Bayer Green-Blue 8-bit with polarization filters(135, 0, 90, 45).
			@~japanese	@details	ベイヤー緑青8ビット(偏光フィルタ角度 135, 0, 90, 45)
			@since StApi v1.1.2
		*/
		StPFNC_Pol1BayerRGY8 = (int)0x81080010L,

		/*!
			@~english	@details	Bayer Blue-Green 8-bit with polarization filters(0, 135, 45, 90).
			@~japanese	@details	ベイヤー青緑8ビット(偏光フィルタ角度 0, 135, 45, 90)
			@since StApi v1.1.2
		*/
		StPFNC_Pol1BayerRGXY8 = (int)0x81080011L,
		
		/*!
			@~english	@details	Bayer Red-Green 10-bit unpacked with polarization filters(90, 45, 135, 0).
			@~english	@attention	The upper 6 bits are fixed to 0.
			@~japanese	@details	ベイヤー赤緑10ビット(偏光フィルタ角度 90, 45, 135, 0)
			@~japanese	@attention	各画素ごとに16ビット(2バイト)使用され、上位6ビットは常に0になります。
			@since StApi v1.1.2
		*/
		StPFNC_Pol1BayerRG10 = (int)0x81100012L,
		
		/*!
			@~english	@details	Bayer Green-Red 10-bit unpacked with polarization filters(45, 90, 0, 135).
			@~english	@attention	The upper 6 bits are fixed to 0.
			@~japanese	@details	ベイヤー緑赤10ビット(偏光フィルタ角度 45, 90, 0, 135)
			@~japanese	@attention	各画素ごとに16ビット(2バイト)使用され、上位6ビットは常に0になります。
			@since StApi v1.1.2
		*/
		StPFNC_Pol1BayerRGX10 = (int)0x81100013L,
		
		/*!
			@~english	@details	Bayer Green-Blue 10-bit unpacked with polarization filters(135, 0, 90, 45).
			@~english	@attention	The upper 6 bits are fixed to 0.
			@~japanese	@details	ベイヤー緑青10ビット(偏光フィルタ角度 135, 0, 90, 45)
			@~japanese	@attention	各画素ごとに16ビット(2バイト)使用され、上位6ビットは常に0になります。
			@since StApi v1.1.2
		*/
		StPFNC_Pol1BayerRGY10 = (int)0x81100014L,
		
		/*!
			@~english	@details	Bayer Blue-Green 10-bit unpacked with polarization filters(0, 135, 45, 90).
			@~english	@attention	The upper 6 bits are fixed to 0.
			@~japanese	@details	ベイヤー青緑10ビット(偏光フィルタ角度 0, 135, 45, 90)
			@~japanese	@attention	各画素ごとに16ビット(2バイト)使用され、上位6ビットは常に0になります。
			@since StApi v1.1.2
		*/
		StPFNC_Pol1BayerRGXY10 = (int)0x81100015L,
		
		/*!
			@~english	@details	Bayer Red-Green 12-bit unpacked with polarization filters(90, 45, 135, 0).
			@~english	@attention	The upper 4 bits are fixed to 0.
			@~japanese	@details	ベイヤー赤緑12ビット(偏光フィルタ角度 90, 45, 135, 0)
			@~japanese	@attention	各画素ごとに16ビット(2バイト)使用され、上位4ビットは常に0になります。
			@since StApi v1.1.2
		*/
		StPFNC_Pol1BayerRG12 = (int)0x81100016L,
		
		/*!
			@~english	@details	Bayer Green-Red 12-bit unpacked with polarization filters(45, 90, 0, 135).
			@~english	@attention	The upper 4 bits are fixed to 0.
			@~japanese	@details	ベイヤー緑赤12ビット(偏光フィルタ角度 45, 90, 0, 135)
			@~japanese	@attention	各画素ごとに16ビット(2バイト)使用され、上位4ビットは常に0になります。
			@since StApi v1.1.2
		*/
		StPFNC_Pol1BayerRGX12 = (int)0x81100017L,
		
		/*!
			@~english	@details	Bayer Green-Blue 12-bit unpacked with polarization filters(135, 0, 90, 45).
			@~english	@attention	The upper 4 bits are fixed to 0.
			@~japanese	@details	ベイヤー緑青12ビット(偏光フィルタ角度 135, 0, 90, 45)
			@~japanese	@attention	各画素ごとに16ビット(2バイト)使用され、上位4ビットは常に0になります。
			@since StApi v1.1.2
		*/
		StPFNC_Pol1BayerRGY12 = (int)0x81100018L,
		
		/*!
			@~english	@details	Bayer Blue-Green 12-bit unpacked with polarization filters(0, 135, 45, 90).
			@~english	@attention	The upper 4 bits are fixed to 0.
			@~japanese	@details	ベイヤー青緑12ビット(偏光フィルタ角度 0, 135, 45, 90)
			@~japanese	@attention	各画素ごとに16ビット(2バイト)使用され、上位4ビットは常に0になります。
			@since StApi v1.1.2
		*/
		StPFNC_Pol1BayerRGXY12 = (int)0x81100019L,

		/*!
			@~english	@details	Monochrome 10-bit packed with polarization filters(90, 45, 135, 0).
			@~english	@attention 4-pixel image is stored in 40-bit (5-Byte) data.	
			@~japanese	@details	モノクロ10ビット(Packed)(偏光フィルタ角度 90, 45, 135, 0)
			@~japanese	@attention	4画素が5バイト(40ビット)で表現され、下位ビットから画素ごとに10ビットずつ使用されます。
			@since StApi v1.1.2
		*/
		StPFNC_Pol1Mono10p = (int)0x810A001AL,

		/*!
			@~english	@details	Monochrome 10-bit packed with polarization filters(45, 90, 0, 135).
			@~english	@attention 4-pixel image is stored in 40-bit (5-Byte) data.	
			@~japanese	@details	モノクロ10ビット(Packed)(偏光フィルタ角度 45, 90, 0, 135)
			@~japanese	@attention	4画素が5バイト(40ビット)で表現され、下位ビットから画素ごとに10ビットずつ使用されます。
			@since StApi v1.1.2
		*/
		StPFNC_Pol1MonoX10p = (int)0x810A001BL,

		/*!
			@~english	@details	Monochrome 10-bit packed with polarization filters(135, 0, 90, 45).
			@~english	@attention 4-pixel image is stored in 40-bit (5-Byte) data.	
			@~japanese	@details	モノクロ10ビット(Packed)(偏光フィルタ角度 135, 0, 90, 45)
			@~japanese	@attention	4画素が5バイト(40ビット)で表現され、下位ビットから画素ごとに10ビットずつ使用されます。
			@since StApi v1.1.2
		*/
		StPFNC_Pol1MonoY10p = (int)0x810A001CL,

		/*!
			@~english	@details	Monochrome 10-bit packed with polarization filters(0, 135, 45, 90).
			@~english	@attention 4-pixel image is stored in 40-bit (5-Byte) data.	
			@~japanese	@details	モノクロ10ビット(Packed)(偏光フィルタ角度 0, 135, 45, 90)
			@~japanese	@attention	4画素が5バイト(40ビット)で表現され、下位ビットから画素ごとに10ビットずつ使用されます。
			@since StApi v1.1.2
		*/
		StPFNC_Pol1MonoXY10p = (int)0x810A001DL,
			
		/*!
			@~english	@details	Monochrome 12-bit packed with polarization filters(90, 45, 135, 0).
			@~english	@attention	2-pixel image is stored in 24-bit (3-Byte) data.
			@~japanese	@details	モノクロ12ビット(Packed)(偏光フィルタ角度 90, 45, 135, 0)
			@~japanese	@attention	2画素が3バイト(24ビット)で表現され、下位ビットから画素ごとに12ビットずつ使用されます。
			@since StApi v1.1.2
		*/
		StPFNC_Pol1Mono12p = (int)0x810C001EL,
			
		/*!
			@~english	@details	Monochrome 12-bit packed with polarization filters(45, 90, 0, 135).
			@~english	@attention	2-pixel image is stored in 24-bit (3-Byte) data.
			@~japanese	@details	モノクロ12ビット(Packed)(偏光フィルタ角度 45, 90, 0, 135)
			@~japanese	@attention	2画素が3バイト(24ビット)で表現され、下位ビットから画素ごとに12ビットずつ使用されます。
			@since StApi v1.1.2
		*/
		StPFNC_Pol1MonoX12p = (int)0x810C001FL,
			
		/*!
			@~english	@details	Monochrome 12-bit packed with polarization filters(135, 0, 90, 45).
			@~english	@attention	2-pixel image is stored in 24-bit (3-Byte) data.
			@~japanese	@details	モノクロ12ビット(Packed)(偏光フィルタ角度 135, 0, 90, 45)
			@~japanese	@attention	2画素が3バイト(24ビット)で表現され、下位ビットから画素ごとに12ビットずつ使用されます。
			@since StApi v1.1.2
		*/
		StPFNC_Pol1MonoY12p = (int)0x810C0020L,
			
		/*!
			@~english	@details	Monochrome 12-bit packed with polarization filters(0, 135, 45, 90).
			@~english	@attention	2-pixel image is stored in 24-bit (3-Byte) data.
			@~japanese	@details	モノクロ12ビット(Packed)(偏光フィルタ角度 0, 135, 45, 90)
			@~japanese	@attention	2画素が3バイト(24ビット)で表現され、下位ビットから画素ごとに12ビットずつ使用されます。
			@since StApi v1.1.2
		*/
		StPFNC_Pol1MonoXY12p = (int)0x810C0021L,
		
		/*!
			@~english	@details	Bayer Red-Green 10-bit packed with polarization filters(90, 45, 135, 0).
			@~english	@attention	4-pixel image is stored in 40-bit (5-Byte) data.
			@~japanese	@details	ベイヤー赤緑10ビット(Packed)(偏光フィルタ角度 90, 45, 135, 0)
			@~japanese	@attention	4画素が5バイト(40ビット)で表現され、下位ビットから画素ごとに10ビットずつ使用されます。
			@since StApi v1.1.2
		*/
		StPFNC_Pol1BayerRG10p = (int)0x810A0022L,
		
		/*!
			@~english	@details	Bayer Green-Red 10-bit packed with polarization filters(45, 90, 0, 135).
			@~english	@attention	4-pixel image is stored in 40-bit (5-Byte) data.
			@~japanese	@details	ベイヤー緑赤10ビット(Packed)(偏光フィルタ角度 45, 90, 0, 135)
			@~japanese	@attention	4画素が5バイト(40ビット)で表現され、下位ビットから画素ごとに10ビットずつ使用されます。
			@since StApi v1.1.2
		*/
		StPFNC_Pol1BayerRGX10p = (int)0x810A0023L,
		
		/*!
			@~english	@details	Bayer Green-Blue 10-bit packed with polarization filters(135, 0, 90, 45).
			@~english	@attention  4-pixel image is stored in 40-bit (5-Byte) data.
			@~japanese	@details	ベイヤー緑青10ビット(Packed)(偏光フィルタ角度 135, 0, 90, 45)
			@~japanese	@attention	4画素が5バイト(40ビット)で表現され、下位ビットから画素ごとに10ビットずつ使用されます。
			@since StApi v1.1.2
		*/
		StPFNC_Pol1BayerRGY10p = (int)0x810A0024L,
		
		/*!
			@~english	@details	Bayer Blue-Green 10-bit packed with polarization filters(0, 135, 45, 90).
			@~english	@attention	4-pixel image is stored in 40-bit (5-Byte) data.
			@~japanese	@details	ベイヤー青緑10ビット(Packed)(偏光フィルタ角度 0, 135, 45, 90)
			@~japanese	@attention	4画素が5バイト(40ビット)で表現され、下位ビットから画素ごとに10ビットずつ使用されます。
			@since StApi v1.1.2
		*/
		StPFNC_Pol1BayerRGXY10p = (int)0x810A0025L,
		
		/*!
			@~english	@details	Bayer Red-Green 12-bit packed with polarization filters(90, 45, 135, 0).
			@~english	@attention	2-pixel image is stored in 24-bit (3-Byte) data.
			@~japanese	@details	ベイヤー赤緑12ビット(Packed)(偏光フィルタ角度 90, 45, 135, 0)
			@~japanese	@attention	2画素が3バイト(24ビット)で表現され、下位ビットから画素ごとに12ビットずつ使用されます。
			@since StApi v1.1.2
		*/
		StPFNC_Pol1BayerRG12p = (int)0x810C0026L,
		
		/*!
			@~english	@details	Bayer Green-Red 12-bit packed with polarization filters(45, 90, 0, 135).
			@~english	@attention	2-pixel image is stored in 24-bit (3-Byte) data.
			@~japanese	@details	ベイヤー緑赤12ビット(Packed)(偏光フィルタ角度 45, 90, 0, 135)
			@~japanese	@attention	2画素が3バイト(24ビット)で表現され、下位ビットから画素ごとに12ビットずつ使用されます。
			@since StApi v1.1.2
		*/
		StPFNC_Pol1BayerRGX12p = (int)0x810C0027L,
		
		/*!
			@~english	@details	Bayer Green-Blue 12-bit packed with polarization filters(135, 0, 90, 45).
			@~english	@attention	2-pixel image is stored in 24-bit (3-Byte) data.
			@~japanese	@details	ベイヤー緑青12ビット(Packed)(偏光フィルタ角度 135, 0, 90, 45)
			@~japanese	@attention	2画素が3バイト(24ビット)で表現され、下位ビットから画素ごとに12ビットずつ使用されます。
			@since StApi v1.1.2
		*/
		StPFNC_Pol1BayerRGY12p = (int)0x810C0028L,
		
		/*!
			@~english	@details	Bayer Blue-Green 12-bit packed with polarization filters(0, 135, 45, 90).
			@~english	@attention	2-pixel image is stored in 24-bit (3-Byte) data.
			@~japanese	@details	ベイヤー青緑12ビット(Packed)(偏光フィルタ角度 0, 135, 45, 90)
			@~japanese	@attention	2画素が3バイト(24ビット)で表現され、下位ビットから画素ごとに12ビットずつ使用されます。
			@since StApi v1.1.2
		*/
		StPFNC_Pol1BayerRGXY12p = (int)0x810C0029L,

		/*!
			@~english	@details	Monochrome 8-bit with polarization filters(135, 90, 0, 45).
			@~japanese	@details	モノクロ8ビット(偏光フィルタ角度 135, 90, 0, 45)
		*/
		StPFNC_Pol1MonoC8 = (int)0x8108002AL,

		/*!
			@~english	@details	Monochrome 8-bit with polarization filters(0, 45, 135, 90).
			@~japanese	@details	モノクロ8ビット(偏光フィルタ角度 0, 45, 135, 90)
			@since StApi v1.1.2
		*/
		StPFNC_Pol1MonoXC8 = (int)0x8108002BL,

		/*!
			@~english	@details	Monochrome 8-bit with polarization filters(90, 135, 45, 0).
			@~japanese	@details	モノクロ8ビット(偏光フィルタ角度 90, 135, 45, 0)
			@since StApi v1.1.2
		*/
		StPFNC_Pol1MonoYC8 = (int)0x8108002CL,

		/*!
			@~english	@details	Monochrome 8-bit with polarization filters(45, 0, 90, 135).
			@~japanese	@details	モノクロ8ビット(偏光フィルタ角度 45, 0, 90, 135)
			@since StApi v1.1.2
		*/
		StPFNC_Pol1MonoXYC8 = (int)0x8108002DL,

		/*!
			@~english	@details	Monochrome 10-bit unpacked with polarization filters(135, 90, 0, 45).
			@~english	@attention	The upper 6 bits are fixed to 0.
			@~japanese	@details	モノクロ12ビット(偏光フィルタ角度 135, 90, 0, 45)
			@~japanese	@attention	各画素ごとに16ビット(2バイト)使用され、上位6ビットは常に0になります。
			@since StApi v1.1.2
		*/
		StPFNC_Pol1MonoC10 = (int)0x8110002EL,

		/*!
			@~english	@details	Monochrome 10-bit unpacked with polarization filters(0, 45, 135, 90).
			@~english	@attention	The upper 6 bits are fixed to 0.
			@~japanese	@details	モノクロ12ビット(偏光フィルタ角度 0, 45, 135, 90)
			@~japanese	@attention	各画素ごとに16ビット(2バイト)使用され、上位6ビットは常に0になります。
			@since StApi v1.1.2
		*/
		StPFNC_Pol1MonoXC10 = (int)0x8110002FL,

		/*!
			@~english	@details	Monochrome 10-bit unpacked with polarization filters(90, 135, 45, 0).
			@~english	@attention	The upper 6 bits are fixed to 0.
			@~japanese	@details	モノクロ12ビット(偏光フィルタ角度 90, 135, 45, 0)
			@~japanese	@attention	各画素ごとに16ビット(2バイト)使用され、上位6ビットは常に0になります。
			@since StApi v1.1.2
		*/
		StPFNC_Pol1MonoYC10 = (int)0x81100030L,

		/*!
			@~english	@details	Monochrome 10-bit unpacked with polarization filters(45, 0, 90, 135).
			@~english	@attention	The upper 6 bits are fixed to 0.
			@~japanese	@details	モノクロ12ビット(偏光フィルタ角度 45, 0, 90, 135)
			@~japanese	@attention	各画素ごとに16ビット(2バイト)使用され、上位6ビットは常に0になります。
			@since StApi v1.1.2
		*/
		StPFNC_Pol1MonoXYC10 = (int)0x81100031L,

		/*!
			@~english	@details	Monochrome 12-bit unpacked with polarization filters(135, 90, 0, 45).
			@~english	@attention	The upper 4 bits are fixed to 0.
			@~japanese	@details	モノクロ12ビット(偏光フィルタ角度 135, 90, 0, 45)
			@~japanese	@attention	各画素ごとに12ビット(2バイト)使用され、上位4ビットは常に0になります。
			@since StApi v1.1.2
		*/
		StPFNC_Pol1MonoC12 = (int)0x81100032L,

		/*!
			@~english	@details	Monochrome 12-bit unpacked with polarization filters(0, 45, 135, 90).
			@~english	@attention	The upper 4 bits are fixed to 0.
			@~japanese	@details	モノクロ12ビット(偏光フィルタ角度 0, 45, 135, 90)
			@~japanese	@attention	各画素ごとに12ビット(2バイト)使用され、上位4ビットは常に0になります。
			@since StApi v1.1.2
		*/
		StPFNC_Pol1MonoXC12 = (int)0x81100033L,

		/*!
			@~english	@details	Monochrome 12-bit unpacked with polarization filters(90, 135, 45, 0).
			@~english	@attention	The upper 4 bits are fixed to 0.
			@~japanese	@details	モノクロ12ビット(偏光フィルタ角度 90, 135, 45, 0)
			@~japanese	@attention	各画素ごとに12ビット(2バイト)使用され、上位4ビットは常に0になります。
			@since StApi v1.1.2
		*/
		StPFNC_Pol1MonoYC12 = (int)0x81100034L,

		/*!
			@~english	@details	Monochrome 12-bit unpacked with polarization filters(45, 0, 90, 135).
			@~english	@attention	The upper 4 bits are fixed to 0.
			@~japanese	@details	モノクロ12ビット(偏光フィルタ角度 45, 0, 90, 135)
			@~japanese	@attention	各画素ごとに12ビット(2バイト)使用され、上位4ビットは常に0になります。
			@since StApi v1.1.2
		*/
		StPFNC_Pol1MonoXYC12 = (int)0x81100035L,

		/*!
			@~english	@details	Bayer Red-Green 8-bit with polarization filters(135, 90, 0, 45).
			@~japanese	@details	ベイヤー赤緑8ビット(偏光フィルタ角度 135, 90, 0, 45)
			@since StApi v1.1.2
		*/
		StPFNC_Pol1BayerRGC8 = (int)0x81080036L,

		/*!
			@~english	@details	Bayer Green-Red 8-bit with polarization filters(0, 45, 135, 90).
			@~japanese	@details	ベイヤー緑赤8ビット(偏光フィルタ角度 0, 45, 135, 90)
			@since StApi v1.1.2
		*/
		StPFNC_Pol1BayerRGXC8 = (int)0x81080037L,

		/*!
			@~english	@details	Bayer Green-Blue 8-bit with polarization filters(90, 135, 45, 0).
			@~japanese	@details	ベイヤー緑青8ビット(偏光フィルタ角度 90, 135, 45, 0)
			@since StApi v1.1.2
		*/
		StPFNC_Pol1BayerRGYC8 = (int)0x81080038L,

		/*!
			@~english	@details	Bayer Blue-Green 8-bit with polarization filters(45, 0, 90, 135).
			@~japanese	@details	ベイヤー青緑8ビット(偏光フィルタ角度 45, 0, 90, 135)
			@since StApi v1.1.2
		*/
		StPFNC_Pol1BayerRGXYC8 = (int)0x81080039L,

		/*!
			@~english	@details	Bayer Red-Green 10-bit unpacked with polarization filters(135, 90, 0, 45).
			@~english	@attention	The upper 6 bits are fixed to 0.
			@~japanese	@details	ベイヤー赤緑10ビット(偏光フィルタ角度 135, 90, 0, 45)
			@~japanese	@attention	各画素ごとに16ビット(2バイト)使用され、上位6ビットは常に0になります。
			@since StApi v1.1.2
		*/
		StPFNC_Pol1BayerRGC10 = (int)0x8110003AL,

		/*!
			@~english	@details	Bayer Green-Red 10-bit unpacked with polarization filters(0, 45, 135, 90).
			@~english	@attention	The upper 6 bits are fixed to 0.
			@~japanese	@details	ベイヤー緑赤10ビット(偏光フィルタ角度 0, 45, 135, 90)
			@~japanese	@attention	各画素ごとに16ビット(2バイト)使用され、上位6ビットは常に0になります。
			@since StApi v1.1.2
		*/
		StPFNC_Pol1BayerRGXC10 = (int)0x8110003BL,

		/*!
			@~english	@details	Bayer Green-Blue 10-bit unpacked with polarization filters(90, 135, 45, 0).
			@~english	@attention	The upper 6 bits are fixed to 0.
			@~japanese	@details	ベイヤー緑青10ビット(偏光フィルタ角度 90, 135, 45, 0)
			@~japanese	@attention	各画素ごとに16ビット(2バイト)使用され、上位6ビットは常に0になります。
			@since StApi v1.1.2
		*/
		StPFNC_Pol1BayerRGYC10 = (int)0x8110003CL,

		/*!
			@~english	@details	Bayer Blue-Green 10-bit unpacked with polarization filters(45, 0, 90, 135).
			@~english	@attention	The upper 6 bits are fixed to 0.
			@~japanese	@details	ベイヤー青緑10ビット(偏光フィルタ角度 45, 0, 90, 135)
			@~japanese	@attention	各画素ごとに16ビット(2バイト)使用され、上位6ビットは常に0になります。
			@since StApi v1.1.2
		*/
		StPFNC_Pol1BayerRGXYC10 = (int)0x8110003DL,

		/*!
			@~english	@details	Bayer Red-Green 12-bit unpacked with polarization filters(135, 90, 0, 45).
			@~english	@attention	The upper 4 bits are fixed to 0.
			@~japanese	@details	ベイヤー赤緑12ビット(偏光フィルタ角度 135, 90, 0, 45)
			@~japanese	@attention	各画素ごとに16ビット(2バイト)使用され、上位4ビットは常に0になります。
			@since StApi v1.1.2
		*/
		StPFNC_Pol1BayerRGC12 = (int)0x8110003EL,

		/*!
			@~english	@details	Bayer Green-Red 12-bit unpacked with polarization filters(0, 45, 135, 90).
			@~english	@attention	The upper 4 bits are fixed to 0.
			@~japanese	@details	ベイヤー緑赤12ビット(偏光フィルタ角度 0, 45, 135, 90)
			@~japanese	@attention	各画素ごとに16ビット(2バイト)使用され、上位4ビットは常に0になります。
			@since StApi v1.1.2
		*/
		StPFNC_Pol1BayerRGXC12 = (int)0x8110003FL,

		/*!
			@~english	@details	Bayer Green-Blue 12-bit unpacked with polarization filters(90, 135, 45, 0).
			@~english	@attention	The upper 4 bits are fixed to 0.
			@~japanese	@details	ベイヤー緑青12ビット(偏光フィルタ角度 90, 135, 45, 0)
			@~japanese	@attention	各画素ごとに16ビット(2バイト)使用され、上位4ビットは常に0になります。
			@since StApi v1.1.2
		*/
		StPFNC_Pol1BayerRGYC12 = (int)0x81100040L,

		/*!
			@~english	@details	Bayer Blue-Green 12-bit unpacked with polarization filters(45, 0, 90, 135).
			@~english	@attention	The upper 4 bits are fixed to 0.
			@~japanese	@details	ベイヤー青緑12ビット(偏光フィルタ角度 45, 0, 90, 135)
			@~japanese	@attention	各画素ごとに16ビット(2バイト)使用され、上位4ビットは常に0になります。
			@since StApi v1.1.2
		*/
		StPFNC_Pol1BayerRGXYC12 = (int)0x81100041L,

		/*!
			@~english	@details	Monochrome 10-bit packed with polarization filters(135, 90, 0, 45).
			@~english	@attention 4-pixel image is stored in 40-bit (5-Byte) data.
			@~japanese	@details	モノクロ10ビット(Packed)(偏光フィルタ角度 135, 90, 0, 45)
			@~japanese	@attention	4画素が5バイト(40ビット)で表現され、下位ビットから画素ごとに10ビットずつ使用されます。
			@since StApi v1.1.2
		*/
		StPFNC_Pol1MonoC10p = (int)0x810A0042L,

		/*!
			@~english	@details	Monochrome 10-bit packed with polarization filters(0, 45, 135, 90).
			@~english	@attention 4-pixel image is stored in 40-bit (5-Byte) data.
			@~japanese	@details	モノクロ10ビット(Packed)(偏光フィルタ角度 0, 45, 135, 90)
			@~japanese	@attention	4画素が5バイト(40ビット)で表現され、下位ビットから画素ごとに10ビットずつ使用されます。
			@since StApi v1.1.2
		*/
		StPFNC_Pol1MonoXC10p = (int)0x810A0043L,

		/*!
			@~english	@details	Monochrome 10-bit packed with polarization filters(90, 135, 45, 0).
			@~english	@attention 4-pixel image is stored in 40-bit (5-Byte) data.
			@~japanese	@details	モノクロ10ビット(Packed)(偏光フィルタ角度 90, 135, 45, 0)
			@~japanese	@attention	4画素が5バイト(40ビット)で表現され、下位ビットから画素ごとに10ビットずつ使用されます。
			@since StApi v1.1.2
		*/
		StPFNC_Pol1MonoYC10p = (int)0x810A0044L,

		/*!
			@~english	@details	Monochrome 10-bit packed with polarization filters(45, 0, 90, 135).
			@~english	@attention 4-pixel image is stored in 40-bit (5-Byte) data.
			@~japanese	@details	モノクロ10ビット(Packed)(偏光フィルタ角度 45, 0, 90, 135)
			@~japanese	@attention	4画素が5バイト(40ビット)で表現され、下位ビットから画素ごとに10ビットずつ使用されます。
			@since StApi v1.1.2
		*/
		StPFNC_Pol1MonoXYC10p = (int)0x810A0045L,

		/*!
			@~english	@details	Monochrome 12-bit packed with polarization filters(135, 90, 0, 45).
			@~english	@attention	2-pixel image is stored in 24-bit (3-Byte) data.
			@~japanese	@details	モノクロ12ビット(Packed)(偏光フィルタ角度 135, 90, 0, 45)
			@~japanese	@attention	2画素が3バイト(24ビット)で表現され、下位ビットから画素ごとに12ビットずつ使用されます。
			@since StApi v1.1.2
		*/
		StPFNC_Pol1MonoC12p = (int)0x810C0046L,

		/*!
			@~english	@details	Monochrome 12-bit packed with polarization filters(0, 45, 135, 90).
			@~english	@attention	2-pixel image is stored in 24-bit (3-Byte) data.
			@~japanese	@details	モノクロ12ビット(Packed)(偏光フィルタ角度 0, 45, 135, 90)
			@~japanese	@attention	2画素が3バイト(24ビット)で表現され、下位ビットから画素ごとに12ビットずつ使用されます。
			@since StApi v1.1.2
		*/
		StPFNC_Pol1MonoXC12p = (int)0x810C0047L,

		/*!
			@~english	@details	Monochrome 12-bit packed with polarization filters(90, 135, 45, 0).
			@~english	@attention	2-pixel image is stored in 24-bit (3-Byte) data.
			@~japanese	@details	モノクロ12ビット(Packed)(偏光フィルタ角度 90, 135, 45, 0)
			@~japanese	@attention	2画素が3バイト(24ビット)で表現され、下位ビットから画素ごとに12ビットずつ使用されます。
			@since StApi v1.1.2
		*/
		StPFNC_Pol1MonoYC12p = (int)0x810C0048L,

		/*!
			@~english	@details	Monochrome 12-bit packed with polarization filters(45, 0, 90, 135).
			@~english	@attention	2-pixel image is stored in 24-bit (3-Byte) data.
			@~japanese	@details	モノクロ12ビット(Packed)(偏光フィルタ角度 45, 0, 90, 135)
			@~japanese	@attention	2画素が3バイト(24ビット)で表現され、下位ビットから画素ごとに12ビットずつ使用されます。
			@since StApi v1.1.2
		*/
		StPFNC_Pol1MonoXYC12p = (int)0x810C0049L,

		/*!
			@~english	@details	Bayer Red-Green 10-bit packed with polarization filters(135, 90, 0, 45).
			@~english	@attention	4-pixel image is stored in 40-bit (5-Byte) data.
			@~japanese	@details	ベイヤー赤緑10ビット(Packed)(偏光フィルタ角度 135, 90, 0, 45)
			@~japanese	@attention	4画素が5バイト(40ビット)で表現され、下位ビットから画素ごとに10ビットずつ使用されます。
			@since StApi v1.1.2
		*/
		StPFNC_Pol1BayerRGC10p = (int)0x810A004AL,

		/*!
			@~english	@details	Bayer Green-Red 10-bit packed with polarization filters(0, 45, 135, 90).
			@~english	@attention	4-pixel image is stored in 40-bit (5-Byte) data.
			@~japanese	@details	ベイヤー緑赤10ビット(Packed)(偏光フィルタ角度 0, 45, 135, 90)
			@~japanese	@attention	4画素が5バイト(40ビット)で表現され、下位ビットから画素ごとに10ビットずつ使用されます。
			@since StApi v1.1.2
		*/
		StPFNC_Pol1BayerRGXC10p = (int)0x810A004BL,

		/*!
			@~english	@details	Bayer Green-Blue 10-bit packed with polarization filters(90, 135, 45, 0).
			@~english	@attention  4-pixel image is stored in 40-bit (5-Byte) data.
			@~japanese	@details	ベイヤー緑青10ビット(Packed)(偏光フィルタ角度 90, 135, 45, 0)
			@~japanese	@attention	4画素が5バイト(40ビット)で表現され、下位ビットから画素ごとに10ビットずつ使用されます。
			@since StApi v1.1.2
		*/
		StPFNC_Pol1BayerRGYC10p = (int)0x810A004CL,

		/*!
			@~english	@details	Bayer Blue-Green 10-bit packed with polarization filters(45, 0, 90, 135).
			@~english	@attention	4-pixel image is stored in 40-bit (5-Byte) data.
			@~japanese	@details	ベイヤー青緑10ビット(Packed)(偏光フィルタ角度 45, 0, 90, 135)
			@~japanese	@attention	4画素が5バイト(40ビット)で表現され、下位ビットから画素ごとに10ビットずつ使用されます。
			@since StApi v1.1.2
		*/
		StPFNC_Pol1BayerRGXYC10p = (int)0x810A004DL,

		/*!
			@~english	@details	Bayer Red-Green 12-bit packed with polarization filters(135, 90, 0, 45).
			@~english	@attention	2-pixel image is stored in 24-bit (3-Byte) data.
			@~japanese	@details	ベイヤー赤緑12ビット(Packed)(偏光フィルタ角度 135, 90, 0, 45)
			@~japanese	@attention	2画素が3バイト(24ビット)で表現され、下位ビットから画素ごとに12ビットずつ使用されます。
			@since StApi v1.1.2
		*/
		StPFNC_Pol1BayerRGC12p = (int)0x810C004EL,

		/*!
			@~english	@details	Bayer Green-Red 12-bit packed with polarization filters(0, 45, 135, 90).
			@~english	@attention	2-pixel image is stored in 24-bit (3-Byte) data.
			@~japanese	@details	ベイヤー緑赤12ビット(Packed)(偏光フィルタ角度 0, 45, 135, 90)
			@~japanese	@attention	2画素が3バイト(24ビット)で表現され、下位ビットから画素ごとに12ビットずつ使用されます。
			@since StApi v1.1.2
		*/
		StPFNC_Pol1BayerRGXC12p = (int)0x810C004FL,

		/*!
			@~english	@details	Bayer Green-Blue 12-bit packed with polarization filters(90, 135, 45, 0).
			@~english	@attention	2-pixel image is stored in 24-bit (3-Byte) data.
			@~japanese	@details	ベイヤー緑青12ビット(Packed)(偏光フィルタ角度 90, 135, 45, 0)
			@~japanese	@attention	2画素が3バイト(24ビット)で表現され、下位ビットから画素ごとに12ビットずつ使用されます。
			@since StApi v1.1.2
		*/
		StPFNC_Pol1BayerRGYC12p = (int)0x810C0050L,

		/*!
			@~english	@details	Bayer Blue-Green 12-bit packed with polarization filters(45, 0, 90, 135).
			@~english	@attention	2-pixel image is stored in 24-bit (3-Byte) data.
			@~japanese	@details	ベイヤー青緑12ビット(Packed)(偏光フィルタ角度 45, 0, 90, 135)
			@~japanese	@attention	2画素が3バイト(24ビット)で表現され、下位ビットから画素ごとに12ビットずつ使用されます。
			@since StApi v1.1.2
		*/
		StPFNC_Pol1BayerRGXYC12p = (int)0x810C0051L,


		/*!
			@~english	@details	YCbCr 4:2:0 8-bit.
			@~english	@attention	The Y plane is followed by the Cb plane and then the Cr plane, which are half the height and width. The SDK does not support planes of different sizes, so getting the number of planes returns 1.
			@~japanese	@details	YCbCr 4:2:0 8ビット
			@~japanese	@attention	Yプレーンの後、縦横サイズが半分のCbプレーン、Crプレーンが続きます。サイズの異なるプレーンにSDKが対応していないため、プレーン数を取得すると1が返されます。RGBとの変換式は下記のとおりです。

			Y = 0.299 x R + 0.587 x G + 0.114 x B
			Cb = -0.16874 x R - 0.33126 x G + 0.5000 x B + 128
			Cr = 0.5000 x R - 0.41869 x G - 0.08131 x B + 128

			R = Y + 1.40200 x (Cr - 128)
			G = Y - 0.34414 x (Cb - 128) - 0.71414 x (Cr - 128)
			B = Y + 1.77200 x (Cb - 128)
			
			@since StApi v1.1.2
		*/
		StPFNC_CYCbCr420_8_YY_Cb_Cr_Planar = (int)0x820C0152L,

	}EStPixelFormatNamingConvention_t, *PEStPixelFormatNamingConvention_t;


/*!
	@ingroup	StApiTL_PublicImpl
	@~english	@details	Definition statement for compatibility with misspelled version 1.0.1.
	@~japanese	@details	バージョン1.0.1のスペルミスと互換性を保つための定義文
*/
#define EStPixelFormatNamingConverntion_t EStPixelFormatNamingConvention_t

/*!
	@ingroup	StApiTL_PublicImpl
	@~english	@details	Definition statement for compatibility with misspelled version 1.0.1.
	@~japanese	@details	バージョン1.0.1のスペルミスと互換性を保つための定義文
*/
#define PEStPixelFormatNamingConverntion_t PEStPixelFormatNamingConvention_t

	/*-------------------------------------------------------------------------*/
	/*Enumerator EStPixelComponent_t                                           */
	/*-------------------------------------------------------------------------*/
	/*! 
		@ingroup	StApiTL_PublicImpl
		@enum EStPixelComponent_t
		@~english	@brief	Enumerator for components of the pixel.
		@~english	@details	Enumerator for components of the pixel.
		@~japanese	@brief	ピクセル構成要素列挙子
		@~japanese	@details	ピクセル構成要素列挙子
	*/
	typedef enum
	{
		/*!
			@~english   @details    Invalid value.
			@~japanese	@details	不正な値
		*/
		StPixelComponent_Unknown =	0x00000000,

		/*!
			@~english   @details    1 bit mono.
			@~japanese	@details	1ビットモノクロ
		*/
		StPixelComponent_Mono1 =	0x01010000,

		/*!
			@~english   @details    2 bits mono.
			@~japanese	@details	2ビットモノクロ
		*/
		StPixelComponent_Mono2 =	0x01020000,

		/*!
			@~english   @details    4 bits mono.
			@~japanese	@details	4ビットモノクロ
		*/
		StPixelComponent_Mono4 =	0x01040000,

		/*!
			@~english   @details    8 bits mono.
			@~japanese	@details	8ビットモノクロ
		*/
		StPixelComponent_Mono8 =	0x01080000,

		/*!
			@~english   @details    8 bits mono with 0 degree polarization filter.
			@~japanese	@details	8ビットモノクロ(0度偏光フィルター)
			@since StApi v1.1.2
		*/
		StPixelComponent_Mono8_POL_000 = 0x01080001,

		/*!
			@~english   @details    8 bits mono with 45 degree polarization filter.
			@~japanese	@details	8ビットモノクロ(45度偏光フィルター)
			@since StApi v1.1.2
		*/
		StPixelComponent_Mono8_POL_045 = 0x01080002,

		/*!
			@~english   @details    8 bits mono with 90 degree polarization filter.
			@~japanese	@details	8ビットモノクロ(90度偏光フィルター)
			@since StApi v1.1.2
		*/
		StPixelComponent_Mono8_POL_090 = 0x01080003,

		/*!
			@~english   @details    8 bits mono with 135 degree polarization filter.
			@~japanese	@details	8ビットモノクロ(135度偏光フィルター)
			@since StApi v1.1.2
		*/
		StPixelComponent_Mono8_POL_135 = 0x01080004,

		/*!
			@~english   @details    10 bits mono.
			@~japanese	@details	10ビットモノクロ
		*/
		StPixelComponent_Mono10 =	0x010A0000,

		/*!
			@~english   @details    10 bits mono with 0 degree polarization filter.
			@~japanese	@details	10ビットモノクロ(0度偏光フィルター)
			@since StApi v1.1.2
		*/
		StPixelComponent_Mono10_POL_000 = 0x010A0001,

		/*!
			@~english   @details    10 bits mono with 45 degree polarization filter.
			@~japanese	@details	10ビットモノクロ(45度偏光フィルター)
			@since StApi v1.1.2
		*/
		StPixelComponent_Mono10_POL_045 = 0x010A0002,

		/*!
			@~english   @details    10 bits mono with 90 degree polarization filter.
			@~japanese	@details	10ビットモノクロ(90度偏光フィルター)
			@since StApi v1.1.2
		*/
		StPixelComponent_Mono10_POL_090 = 0x010A0003,

		/*!
			@~english   @details    10 bits mono with 135 degree polarization filter.
			@~japanese	@details	10ビットモノクロ(135度偏光フィルター)
			@since StApi v1.1.2
		*/
		StPixelComponent_Mono10_POL_135 = 0x010A0004,

		/*!
			@~english   @details    12 bits mono.
			@~japanese	@details	12ビットモノクロ
		*/
		StPixelComponent_Mono12 = 0x010C0000,

		/*!
			@~english   @details    12 bits mono with 0 degree polarization filter.
			@~japanese	@details	12ビットモノクロ(0度偏光フィルター)
			@since StApi v1.1.2
		*/
		StPixelComponent_Mono12_POL_000 = 0x010C0001,

		/*!
			@~english   @details    12 bits mono with 45 degree polarization filter.
			@~japanese	@details	12ビットモノクロ(45度偏光フィルター)
			@since StApi v1.1.2
		*/
		StPixelComponent_Mono12_POL_045 = 0x010C0002,

		/*!
			@~english   @details    12 bits mono with 90 degree polarization filter.
			@~japanese	@details	12ビットモノクロ(90度偏光フィルター)
			@since StApi v1.1.2
		*/
		StPixelComponent_Mono12_POL_090 = 0x010C0003,

			/*!
				@~english   @details    12 bits mono with 135 degree polarization filter.
				@~japanese	@details	12ビットモノクロ(135度偏光フィルター)
				@since StApi v1.1.2
			*/
		StPixelComponent_Mono12_POL_135 = 0x010C0004,

		/*!
			@~english   @details    14 bits mono.
			@~japanese	@details	14ビットモノクロ
		*/
		StPixelComponent_Mono14 =	0x010E0000,

		/*!
			@~english   @details    16 bits mono.
			@~japanese	@details	16ビットモノクロ
		*/
		StPixelComponent_Mono16 =	0x01100000,

		/*!
			@~english   @details    32 bits mono.
			@~japanese	@details	32ビットモノクロ
		*/
		StPixelComponent_Mono32 =	0x01200000,

		/*!
			@~english   @details    4 bits red.
			@~japanese	@details	4ビット赤
		*/
		StPixelComponent_R4 =		0x02040000,

		/*!
			@~english   @details    8 bits red.
			@~japanese	@details	8ビット赤
		*/
		StPixelComponent_R8 =		0x02080000,

		/*!
			@~english   @details    8 bits red with 0 degree polarization filter.
			@~japanese	@details	8ビット赤(0度偏光フィルター)
			@since StApi v1.1.2
		*/
		StPixelComponent_R8_POL_000 = 0x02080001,

		/*!
			@~english   @details    8 bits red with 45 degree polarization filter.
			@~japanese	@details	8ビット赤(45度偏光フィルター)
			@since StApi v1.1.2
		*/
		StPixelComponent_R8_POL_045 = 0x02080002,

		/*!
			@~english   @details    8 bits red with 90 degree polarization filter.
			@~japanese	@details	8ビット赤(90度偏光フィルター)
			@since StApi v1.1.2
		*/
		StPixelComponent_R8_POL_090 = 0x02080003,

		/*!
			@~english   @details    8 bits red with 135 degree polarization filter.
			@~japanese	@details	8ビット赤(135度偏光フィルター)
			@since StApi v1.1.2
		*/
		StPixelComponent_R8_POL_135 = 0x02080004,

		/*!
			@~english   @details    10 bits red.
			@~japanese	@details	10ビット赤
		*/
		StPixelComponent_R10 =		0x020A0000,

		/*!
			@~english   @details    10 bits red with 0 degree polarization filter.
			@~japanese	@details	10ビット赤(0度偏光フィルター)
			@since StApi v1.1.2
		*/
		StPixelComponent_R10_POL_000 = 0x020A0001,

		/*!
			@~english   @details    10 bits red with 45 degree polarization filter.
			@~japanese	@details	10ビット赤(45度偏光フィルター)
			@since StApi v1.1.2
		*/
		StPixelComponent_R10_POL_045 = 0x020A0002,

		/*!
			@~english   @details    10 bits red with 90 degree polarization filter.
			@~japanese	@details	10ビット赤(90度偏光フィルター)
			@since StApi v1.1.2
		*/
		StPixelComponent_R10_POL_090 = 0x020A0003,

		/*!
			@~english   @details    10 bits red with 135 degree polarization filter.
			@~japanese	@details	10ビット赤(135度偏光フィルター)
			@since StApi v1.1.2
		*/
		StPixelComponent_R10_POL_135 = 0x020A0004,

		/*!
			@~english   @details    12 bits red.
			@~japanese	@details	12ビット赤
		*/
		StPixelComponent_R12 =		0x020C0000,

		/*!
			@~english   @details    12 bits red with 0 degree polarization filter.
			@~japanese	@details	12ビット赤(0度偏光フィルター)
			@since StApi v1.1.2
		*/
		StPixelComponent_R12_POL_000 = 0x020C0001,

		/*!
			@~english   @details    12 bits red with 45 degree polarization filter.
			@~japanese	@details	12ビット赤(45度偏光フィルター)
			@since StApi v1.1.2
		*/
		StPixelComponent_R12_POL_045 = 0x020C0002,

		/*!
			@~english   @details    12 bits red with 90 degree polarization filter.
			@~japanese	@details	12ビット赤(90度偏光フィルター)
			@since StApi v1.1.2
		*/
		StPixelComponent_R12_POL_090 = 0x020C0003,

		/*!
			@~english   @details    12 bits red with 135 degree polarization filter.
			@~japanese	@details	12ビット赤(135度偏光フィルター)
			@since StApi v1.1.2
		*/
		StPixelComponent_R12_POL_135 = 0x020C0004,

		/*!
			@~english   @details    14 bits red.
			@~japanese	@details	14ビット赤
		*/
		StPixelComponent_R14 =		0x020E0000,

		/*!
			@~english   @details    16 bits red.
			@~japanese	@details	16ビット赤
		*/
		StPixelComponent_R16 =		0x02100000,

		/*!
			@~english   @details    4 bits green.
			@~japanese	@details	4ビット緑
		*/
		StPixelComponent_G4 =		0x03040000,

		/*!
			@~english   @details    8 bits green.
			@~japanese	@details	8ビット緑
		*/
		StPixelComponent_G8 =		0x03080000,

		/*!
			@~english   @details    10 bits green.
			@~japanese	@details	10ビット緑
		*/
		StPixelComponent_G10 =		0x030A0000,

		/*!
			@~english   @details    12 bits green.
			@~japanese	@details	12ビット緑
		*/
		StPixelComponent_G12 =		0x030C0000,

		/*!
			@~english   @details    14 bits green.
			@~japanese	@details	14ビット緑
		*/
		StPixelComponent_G14 =		0x030E0000,

		/*!
			@~english   @details    16 bits green.
			@~japanese	@details	16ビット緑
		*/
		StPixelComponent_G16 =		0x03100000,

		/*!
			@~english   @details    4 bits blue.
			@~japanese	@details	4ビット青
		*/
		StPixelComponent_B4 =		0x04040000,

		/*!
			@~english   @details    8 bits blue.
			@~japanese	@details	8ビット青
		*/
		StPixelComponent_B8 =		0x04080000,

		/*!
			@~english   @details    8 bits blue with 0 degree polarization filter.
			@~japanese	@details	8ビット青(0度偏光フィルター)
			@since StApi v1.1.2
		*/
		StPixelComponent_B8_POL_000 = 0x04080001,

		/*!
			@~english   @details    8 bits blue with 45 degree polarization filter.
			@~japanese	@details	8ビット青(45度偏光フィルター)
			@since StApi v1.1.2
		*/
		StPixelComponent_B8_POL_045 = 0x04080002,

		/*!
			@~english   @details    8 bits blue with 90 degree polarization filter.
			@~japanese	@details	8ビット青(90度偏光フィルター)
			@since StApi v1.1.2
		*/
		StPixelComponent_B8_POL_090 = 0x04080003,

		/*!
			@~english   @details    8 bits blue with 135 degree polarization filter.
			@~japanese	@details	8ビット青(135度偏光フィルター)
			@since StApi v1.1.2
		*/
		StPixelComponent_B8_POL_135 = 0x04080004,

		/*!
			@~english   @details    10 bits blue.
			@~japanese	@details	10ビット青
		*/
		StPixelComponent_B10 =		0x040A0000,

		/*!
			@~english   @details    10 bits blue with 0 degree polarization filter.
			@~japanese	@details	10ビット青(0度偏光フィルター)
			@since StApi v1.1.2
		*/
		StPixelComponent_B10_POL_000 = 0x040A0001,

		/*!
			@~english   @details    10 bits blue with 45 degree polarization filter.
			@~japanese	@details	10ビット青(45度偏光フィルター)
			@since StApi v1.1.2
		*/
		StPixelComponent_B10_POL_045 = 0x040A0002,

		/*!
			@~english   @details    10 bits blue with 90 degree polarization filter.
			@~japanese	@details	10ビット青(90度偏光フィルター)
			@since StApi v1.1.2
		*/
		StPixelComponent_B10_POL_090 = 0x040A0003,

		/*!
			@~english   @details    10 bits blue with 135 degree polarization filter.
			@~japanese	@details	10ビット青(135度偏光フィルター)
			@since StApi v1.1.2
		*/
		StPixelComponent_B10_POL_135 = 0x040A0004,

		/*!
			@~english   @details    12 bits blue.
			@~japanese	@details	12ビット青
		*/
		StPixelComponent_B12 =		0x040C0000,

		/*!
			@~english   @details    12 bits blue with 0 degree polarization filter.
			@~japanese	@details	12ビット青(0度偏光フィルター)
			@since StApi v1.1.2
		*/
		StPixelComponent_B12_POL_000 = 0x040C0001,

		/*!
			@~english   @details    12 bits blue with 45 degree polarization filter.
			@~japanese	@details	12ビット青(45度偏光フィルター)
			@since StApi v1.1.2
		*/
		StPixelComponent_B12_POL_045 = 0x040C0002,

		/*!
			@~english   @details    12 bits blue with 90 degree polarization filter.
			@~japanese	@details	12ビット青(90度偏光フィルター)
			@since StApi v1.1.2
		*/
		StPixelComponent_B12_POL_090 = 0x040C0003,

		/*!
			@~english   @details    12 bits blue with 135 degree polarization filter.
			@~japanese	@details	12ビット青(135度偏光フィルター)
			@since StApi v1.1.2
		*/
		StPixelComponent_B12_POL_135 = 0x040C0004,

		/*!
			@~english   @details    14 bits blue.
			@~japanese	@details	14ビット青
		*/
		StPixelComponent_B14 =		0x040E0000,

		/*!
			@~english   @details    16 bits blue.
			@~japanese	@details	16ビット青
		*/
		StPixelComponent_B16 =		0x04100000,

		/*!
			@~english   @details    4 bits Gr.
			@~japanese	@details	4ビット緑赤
		*/
		StPixelComponent_Gr4 =		0x05040000,

		/*!
			@~english   @details    8 bits Gr.
			@~japanese	@details	8ビット緑赤
		*/
		StPixelComponent_Gr8 =		0x05080000,

		/*!
			@~english   @details    8 bits Gr with 0 degree polarization filter.
			@~japanese	@details	8ビット緑赤(0度偏光フィルター)
			@since StApi v1.1.2
		*/
		StPixelComponent_Gr8_POL_000 = 0x05080001,

		/*!
			@~english   @details    8 bits Gr with 45 degree polarization filter.
			@~japanese	@details	8ビット緑赤(45度偏光フィルター)
			@since StApi v1.1.2
		*/
		StPixelComponent_Gr8_POL_045 = 0x05080002,

		/*!
			@~english   @details    8 bits Gr with 90 degree polarization filter.
			@~japanese	@details	8ビット緑赤(90度偏光フィルター)
			@since StApi v1.1.2
		*/
		StPixelComponent_Gr8_POL_090 = 0x05080003,

		/*!
			@~english   @details    8 bits Gr with 135 degree polarization filter.
			@~japanese	@details	8ビット緑赤(135度偏光フィルター)
			@since StApi v1.1.2
		*/
		StPixelComponent_Gr8_POL_135 = 0x05080004,

		/*!
			@~english   @details    10 bits Gr.
			@~japanese	@details	10ビット緑赤
		*/
		StPixelComponent_Gr10 =		0x050A0000,

		/*!
			@~english   @details    10 bits Gr with 0 degree polarization filter.
			@~japanese	@details	10ビット緑赤(0度偏光フィルター)
			@since StApi v1.1.2
		*/
		StPixelComponent_Gr10_POL_000 = 0x050A0001,

		/*!
			@~english   @details    10 bits Gr with 45 degree polarization filter.
			@~japanese	@details	10ビット緑赤(45度偏光フィルター)
			@since StApi v1.1.2
		*/
		StPixelComponent_Gr10_POL_045 = 0x050A0002,

		/*!
			@~english   @details    10 bits Gr with 90 degree polarization filter.
			@~japanese	@details	10ビット緑赤(90度偏光フィルター)
			@since StApi v1.1.2
		*/
		StPixelComponent_Gr10_POL_090 = 0x050A0003,

		/*!
			@~english   @details    10 bits Gr with 135 degree polarization filter.
			@~japanese	@details	10ビット緑赤(135度偏光フィルター)
			@since StApi v1.1.2
		*/
		StPixelComponent_Gr10_POL_135 = 0x050A0004,

		/*!
			@~english   @details    12 bits Gr.
			@~japanese	@details	12ビット緑赤
		*/
		StPixelComponent_Gr12 =		0x050C0000,

		/*!
			@~english   @details    12 bits Gr with 0 degree polarization filter.
			@~japanese	@details	12ビット緑赤(0度偏光フィルター)
			@since StApi v1.1.2
		*/
		StPixelComponent_Gr12_POL_000 = 0x050C0001,

		/*!
			@~english   @details    12 bits Gr with 45 degree polarization filter.
			@~japanese	@details	12ビット緑赤(45度偏光フィルター)
			@since StApi v1.1.2
		*/
		StPixelComponent_Gr12_POL_045 = 0x050C0002,

		/*!
			@~english   @details    12 bits Gr with 90 degree polarization filter.
			@~japanese	@details	12ビット緑赤(90度偏光フィルター)
			@since StApi v1.1.2
		*/
		StPixelComponent_Gr12_POL_090 = 0x050C0003,

		/*!
			@~english   @details    12 bits Gr with 135 degree polarization filter.
			@~japanese	@details	12ビット緑赤(135度偏光フィルター)
			@since StApi v1.1.2
		*/
		StPixelComponent_Gr12_POL_135 = 0x050C0004,

		/*!
			@~english   @details    14 bits Gr.
			@~japanese	@details	14ビット緑赤
		*/
		StPixelComponent_Gr14 =		0x050E0000,

		/*!
			@~english   @details    16 bits Gr.
			@~japanese	@details	16ビット緑赤
		*/
		StPixelComponent_Gr16 =		0x05100000,

		/*!
			@~english   @details    4 bits Gb.
			@~japanese	@details	4ビット緑青
		*/
		StPixelComponent_Gb4 =		0x06040000,

		/*!
			@~english   @details    8 bits Gb.
			@~japanese	@details	8ビット緑青
		*/
		StPixelComponent_Gb8 =		0x06080000,

		/*!
			@~english   @details    8 bits Gb with 0 degree polarization filter.
			@~japanese	@details	8ビット緑青(0度偏光フィルター)
			@since StApi v1.1.2
		*/
		StPixelComponent_Gb8_POL_000 = 0x06080001,

		/*!
			@~english   @details    8 bits Gb with 45 degree polarization filter.
			@~japanese	@details	8ビット緑青(45度偏光フィルター)
			@since StApi v1.1.2
		*/
		StPixelComponent_Gb8_POL_045 = 0x06080002,

		/*!
			@~english   @details    8 bits Gb with 90 degree polarization filter.
			@~japanese	@details	8ビット緑青(90度偏光フィルター)
			@since StApi v1.1.2
		*/
		StPixelComponent_Gb8_POL_090 = 0x06080003,

		/*!
			@~english   @details    8 bits Gb with 135 degree polarization filter.
			@~japanese	@details	8ビット緑青(135度偏光フィルター)
			@since StApi v1.1.2
		*/
		StPixelComponent_Gb8_POL_135 = 0x06080004,

		/*!
			@~english   @details    10 bits Gb.
			@~japanese	@details	10ビット緑青
		*/
		StPixelComponent_Gb10 =		0x060A0000,

		/*!
			@~english   @details    10 bits Gb with 0 degree polarization filter.
			@~japanese	@details	10ビット緑青(0度偏光フィルター)
			@since StApi v1.1.2
		*/
		StPixelComponent_Gb10_POL_000 = 0x060A0001,

		/*!
			@~english   @details    10 bits Gb with 45 degree polarization filter.
			@~japanese	@details	10ビット緑青(45度偏光フィルター)
			@since StApi v1.1.2
		*/
		StPixelComponent_Gb10_POL_045 = 0x060A0002,

		/*!
			@~english   @details    10 bits Gb with 90 degree polarization filter.
			@~japanese	@details	10ビット緑青(90度偏光フィルター)
			@since StApi v1.1.2
		*/
		StPixelComponent_Gb10_POL_090 = 0x060A0003,

		/*!
			@~english   @details    10 bits Gb with 135 degree polarization filter.
			@~japanese	@details	10ビット緑青(135度偏光フィルター)
			@since StApi v1.1.2
		*/
		StPixelComponent_Gb10_POL_135 = 0x060A0004,

		/*!
			@~english   @details    12 bits Gb.
			@~japanese	@details	12ビット緑青
		*/
		StPixelComponent_Gb12 =		0x060C0000,

		/*!
			@~english   @details    12 bits Gb with 0 degree polarization filter.
			@~japanese	@details	12ビット緑青(0度偏光フィルター)
			@since StApi v1.1.2
		*/
		StPixelComponent_Gb12_POL_000 = 0x060C0001,

		/*!
			@~english   @details    12 bits Gb with 45 degree polarization filter.
			@~japanese	@details	12ビット緑青(45度偏光フィルター)
			@since StApi v1.1.2
		*/
		StPixelComponent_Gb12_POL_045 = 0x060C0002,

		/*!
			@~english   @details    12 bits Gb with 90 degree polarization filter.
			@~japanese	@details	12ビット緑青(90度偏光フィルター)
			@since StApi v1.1.2
		*/
		StPixelComponent_Gb12_POL_090 = 0x060C0003,

		/*!
			@~english   @details    12 bits Gb with 135 degree polarization filter.
			@~japanese	@details	12ビット緑青(135度偏光フィルター)
			@since StApi v1.1.2
		*/
		StPixelComponent_Gb12_POL_135 = 0x060C0004,

		/*!
			@~english   @details    14 bits Gb.
			@~japanese	@details	14ビット緑青
		*/
		StPixelComponent_Gb14 =		0x060E0000,

		/*!
			@~english   @details    16 bits Gb.
			@~japanese	@details	16ビット緑青
		*/
		StPixelComponent_Gb16 =		0x06100000,

		/*!
			@~english   @details    8 bits Y.
			@~japanese	@details	8ビットY
		*/
		StPixelComponent_Y8 =		0x07080000,

		/*!
			@~english   @details    8 bits Cb.
			@~japanese	@details	8ビットCb
		*/
		StPixelComponent_Cb8 =		0x08080000,

		/*!
			@~english   @details    8 bits Cr.
			@~japanese	@details	8ビットCr
		*/
		StPixelComponent_Cr8 =		0x09080000,

		/*!
			@~english   @details    8 bits U.
			@~japanese	@details	8ビットU
		*/
		StPixelComponent_U8 =		0x0A080000,

		/*!
			@~english   @details    8 bits V.
			@~japanese	@details	8ビットV
		*/
		StPixelComponent_V8 =		0x0B080000,

		StPixelComponent_Data8 =	0x0C080000,			/*!< 8bits Data */
		StPixelComponent_Data8s =	0x0C080001,			/*!< 8bits signed Data */
		StPixelComponent_Data16 =	0x0C100000,			/*!< 16bits Data */
		StPixelComponent_Data16s =	0x0C100001,			/*!< 16bits signed Data */
		StPixelComponent_Data32 =	0x0C200000,			/*!< 32bits Data */
		StPixelComponent_Data32f =	0x0C200002,			/*!< 32bits floating point Data */
		StPixelComponent_Data32s =	0x0C200001,			/*!< 32bits signed Data */
		StPixelComponent_Data64 =	0x0C400000,			/*!< 64bits Data */
		StPixelComponent_Data64f =	0x0C400002,			/*!< 64bits floating point Data */
		StPixelComponent_Data64s =	0x0C400001,			/*!< 64bits signed Data */

	}EStPixelComponent_t, *PEStPixelComponent_t;

	/*-------------------------------------------------------------------------*/
	/*Enumerator EStPixelColorFilter_t                                         */
	/*-------------------------------------------------------------------------*/
	/*! 
		@ingroup	StApiTL_PublicImpl
		@enum EStPixelColorFilter_t
		@~english	@brief	Enumerator for pixel color filter.
		@~english	@details	Enumerator for pixel color filter.
		@~japanese	@brief	カラーフィルター列挙子
		@~japanese	@details	カラーフィルター列挙子
	*/
	typedef enum
	{
		StPixelColorFilter_Unknown,		/*!< Invalid value */

		/*!
			@~english	@details	Mono.
			@~japanese	@details	なし(モノクロ)
		*/
		StPixelColorFilter_None,

		/*!
			@~english	@details	BayerRG.
			@~english	@attention	RGrGbB.
			@~japanese	@details	ベイヤー赤緑
			@~japanese	@attention	偶数ラインは左から赤緑のフィルターが交互に並び、奇数ラインは左から緑青のフィルターが交互に並びます。
		*/
		StPixelColorFilter_BayerRG,

		/*!
			@~english	@details	BayerRG.
			@~english	@attention	GrRBGb.
			@~japanese	@details	ベイヤー緑赤
			@~japanese	@attention	偶数ラインは左から緑赤のフィルターが交互に並び、奇数ラインは左から青緑のフィルターが交互に並びます。
		*/
		StPixelColorFilter_BayerGR,

		/*!
			@~english	@details	BayerGB.
			@~english	@attention	GbBRGr.
			@~japanese	@details	ベイヤー緑青
			@~japanese	@attention	偶数ラインは左から緑青のフィルターが交互に並び、奇数ラインは左から赤緑のフィルターが交互に並びます。
		*/
		StPixelColorFilter_BayerGB,

		/*!
			@~english	@details	BayerBG.
			@~english	@attention	BGbGrR.
			@~japanese	@details	ベイヤー青緑
			@~japanese	@attention	偶数ラインは左から青緑のフィルターが交互に並び、奇数ラインは左から緑赤のフィルターが交互に並びます。
		*/ 
		StPixelColorFilter_BayerBG,

		/*!
			@~english	@details	Pol1Mono.
			@~english	@attention	Pol1Mono.
			@~japanese	@details	偏光フィルタ(モノクロ)
			@~japanese	@attention	偶数ラインには90度/45度の偏光フィルタが、奇数ラインには135度/0度の偏光フィルタが交互に並びます。
			@since StApi v1.1.2
		*/
		StPixelColorFilter_Pol1Mono,

		/*!
			@~english	@details	Pol1MonoX.
			@~english	@attention	Pol1MonoX.
			@~japanese	@details	偏光フィルタ(モノクロ)
			@~japanese	@attention	偶数ラインには45度/90度の偏光フィルタが、奇数ラインには0度/135度の偏光フィルタが交互に並びます。
			@since StApi v1.1.2
		*/
		StPixelColorFilter_Pol1MonoX,

		/*!
			@~english	@details	Pol1MonoY.
			@~english	@attention	Pol1MonoY.
			@~japanese	@details	偏光フィルタ(モノクロ)
			@~japanese	@attention	偶数ラインには135度/0度の偏光フィルタが、奇数ラインには90度/45度の偏光フィルタが交互に並びます。
			@since StApi v1.1.2
		*/
		StPixelColorFilter_Pol1MonoY,

		/*!
			@~english	@details	Pol1MonoXY.
			@~english	@attention	Pol1MonoXY.
			@~japanese	@details	偏光フィルタ(モノクロ)
			@~japanese	@attention	偶数ラインには0度/135度の偏光フィルタが、奇数ラインには45度/90度の偏光フィルタが交互に並びます。
			@since StApi v1.1.2
		*/
		StPixelColorFilter_Pol1MonoXY,

		/*!
			@~english	@details	Pol1BayerRG.
			@~english	@attention	Pol1BayerRG.
			@~japanese	@details	偏光フィルタ(カラー)
			@~japanese	@attention	偶数ラインには90度/45度の偏光フィルタが、奇数ラインには135度/0度の偏光フィルタが交互に並びます。さらに2画素ごとに左から赤緑のフィルターが交互に並ぶラインと、2画素ごとに左から緑青のフィルターが交互に並ぶラインが2ライン繰り返されます。
			@since StApi v1.1.2
		*/
		StPixelColorFilter_Pol1BayerRG,

		/*!
			@~english	@details	Pol1BayerRGX.
			@~english	@attention	Pol1BayerRGX.
			@~japanese	@details	偏光フィルタ(カラー)
			@~japanese	@attention	偶数ラインには45度/90度の偏光フィルタが、奇数ラインには0度/135度の偏光フィルタが交互に並びます。さらに2画素ごとに左から緑赤のフィルターが交互に並ぶラインと、2画素ごとに左から青緑のフィルターが交互に並ぶラインが2ライン繰り返されます。
			@since StApi v1.1.2
		*/
		StPixelColorFilter_Pol1BayerRGX,

		/*!
			@~english	@details	Pol1BayerRGY.
			@~english	@attention	Pol1BayerRGY.
			@~japanese	@details	偏光フィルタ(カラー)
			@~japanese	@attention	偶数ラインには135度/0度の偏光フィルタが、奇数ラインには90度/45度の偏光フィルタが交互に並びます。さらに2画素ごとに左から緑青のフィルターが交互に並ぶラインと、2画素ごとに左から赤緑のフィルターが交互に並ぶラインが2ライン繰り返されます。
			@since StApi v1.1.2
		*/
		StPixelColorFilter_Pol1BayerRGY,

		/*!
			@~english	@details	Pol1BayerRGXY.
			@~english	@attention	Pol1BayerRGXY.
			@~japanese	@details	偏光フィルタ(カラー)
			@~japanese	@attention	偶数ラインには0度/135度の偏光フィルタが、奇数ラインには45度/90度の偏光フィルタが交互に並びます。さらに2画素ごとに左から青緑のフィルターが交互に並ぶラインと、2画素ごとに左から緑赤のフィルターが交互に並ぶラインが2ライン繰り返されます。
			@since StApi v1.1.2
		*/
		StPixelColorFilter_Pol1BayerRGXY,

			

		/*!
			@~english	@details	Pol1MonoC.
			@~english	@attention	Pol1MonoC.
			@~japanese	@details	偏光フィルタ(モノクロ)
			@~japanese	@attention	偶数ラインには135度/90度の偏光フィルタが、奇数ラインには0度/45度の偏光フィルタが交互に並びます。
			@since StApi v1.1.2
		*/
		StPixelColorFilter_Pol1MonoC,

		/*!
			@~english	@details	Pol1MonoXC.
			@~english	@attention	Pol1MonoXC.
			@~japanese	@details	偏光フィルタ(モノクロ)
			@~japanese	@attention	偶数ラインには0度/45度の偏光フィルタが、奇数ラインには135度/90度の偏光フィルタが交互に並びます。
			@since StApi v1.1.2
		*/
		StPixelColorFilter_Pol1MonoXC,

		/*!
			@~english	@details	Pol1MonoYC.
			@~english	@attention	Pol1MonoYC.
			@~japanese	@details	偏光フィルタ(モノクロ)
			@~japanese	@attention	偶数ラインには90度/135度の偏光フィルタが、奇数ラインには45度/0度の偏光フィルタが交互に並びます。
			@since StApi v1.1.2
		*/
		StPixelColorFilter_Pol1MonoYC,

		/*!
			@~english	@details	Pol1MonoXYC.
			@~english	@attention	Pol1MonoXYC.
			@~japanese	@details	偏光フィルタ(モノクロ)
			@~japanese	@attention	偶数ラインには45度/0度の偏光フィルタが、奇数ラインには90度/135度の偏光フィルタが交互に並びます。
			@since StApi v1.1.2
		*/
		StPixelColorFilter_Pol1MonoXYC,

		/*!
			@~english	@details	Pol1BayerRGC.
			@~english	@attention	Pol1BayerRGC.
			@~japanese	@details	偏光フィルタ(カラー)
			@~japanese	@attention	偶数ラインには135度/90度の偏光フィルタが、奇数ラインには0度/45度の偏光フィルタが交互に並びます。さらに2画素ごとに左から赤緑のフィルターが交互に並ぶラインと、2画素ごとに左から緑青のフィルターが交互に並ぶラインが2ライン繰り返されます。
			@since StApi v1.1.2
		*/
		StPixelColorFilter_Pol1BayerRGC,

		/*!
			@~english	@details	Pol1BayerRGXC.
			@~english	@attention	Pol1BayerRGXC.
			@~japanese	@details	偏光フィルタ(カラー)
			@~japanese	@attention	偶数ラインには0度/45度の偏光フィルタが、奇数ラインには135度/90度の偏光フィルタが交互に並びます。さらに2画素ごとに左から緑赤のフィルターが交互に並ぶラインと、2画素ごとに左から青緑のフィルターが交互に並ぶラインが2ライン繰り返されます。
			@since StApi v1.1.2
		*/
		StPixelColorFilter_Pol1BayerRGXC,

		/*!
			@~english	@details	Pol1BayerRGYC.
			@~english	@attention	Pol1BayerRGYC.
			@~japanese	@details	偏光フィルタ(カラー)
			@~japanese	@attention	偶数ラインには90度/135度の偏光フィルタが、奇数ラインには45度/0度の偏光フィルタが交互に並びます。さらに2画素ごとに左から緑青のフィルターが交互に並ぶラインと、2画素ごとに左から赤緑のフィルターが交互に並ぶラインが2ライン繰り返されます。
			@since StApi v1.1.2
		*/
		StPixelColorFilter_Pol1BayerRGYC,

		/*!
			@~english	@details	Pol1BayerRGXYC.
			@~english	@attention	Pol1BayerRGXYC.
			@~japanese	@details	偏光フィルタ(カラー)
			@~japanese	@attention	偶数ラインには45度/0度の偏光フィルタが、奇数ラインには90度/135度の偏光フィルタが交互に並びます。さらに2画素ごとに左から青緑のフィルターが交互に並ぶラインと、2画素ごとに左から緑赤のフィルターが交互に並ぶラインが2ライン繰り返されます。
			@since StApi v1.1.2
		*/
		StPixelColorFilter_Pol1BayerRGXYC,
	}EStPixelColorFilter_t, *PEStPixelColorFilter_t;

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* STPIXELFORMAT_H__ */

