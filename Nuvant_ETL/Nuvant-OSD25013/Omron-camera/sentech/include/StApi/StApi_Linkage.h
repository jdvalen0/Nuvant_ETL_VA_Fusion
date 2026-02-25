/* This file is encoded in UTF-8,  */
/* but BOM has not been added to accommodate environments not compatible with BOM. */
/*
 StApi
*/
/*!
	@file	StApi_Linkage.h
	@~english	@details	
	@~japanese	@details	
*/
#ifndef STAPI_LINKAGE_H__
#define STAPI_LINKAGE_H__

#   if (defined (_WIN32) && defined (_MT )) || defined (__MINGW32__) || defined (__MINGW64__)
#     if (defined(_DEBUG) || defined(DEBUG)) && defined(STAPI_DEBUG_BUILD)
#           define ST_CONFIGURATION "MDd"
#       else
#           define ST_CONFIGURATION "MD"
#     endif
#   elif defined(__linux__) || defined(__APPLE__)
#   else
#       pragma message("Invalid Configuration")
#   endif

#   ifdef _WIN32
#       define ST_FULL_FILE_NAME(MOD, CON, COM, MAJOR, MINOR, EXT) MOD "_" CON "_" COM "_v" MAJOR "_" MINOR  EXT
#       define ST_FILE_NAME(module, extension) ST_FULL_FILE_NAME(module, ST_CONFIGURATION, STAPI_COMPILER_STR, STAPI_VERSION_MAJOR_STR, STAPI_VERSION_MINOR_STR, extension)
#   endif
#endif //STAPI_LINKAGE_H__

