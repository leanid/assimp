/*
---------------------------------------------------------------------------
Open Asset Import Library (ASSIMP)
---------------------------------------------------------------------------

Copyright (c) 2006-2008, ASSIMP Development Team

All rights reserved.

Redistribution and use of this software in source and binary forms, 
with or without modification, are permitted provided that the following 
conditions are met:

* Redistributions of source code must retain the above
  copyright notice, this list of conditions and the
  following disclaimer.

* Redistributions in binary form must reproduce the above
  copyright notice, this list of conditions and the
  following disclaimer in the documentation and/or other
  materials provided with the distribution.

* Neither the name of the ASSIMP team, nor the names of its
  contributors may be used to endorse or promote products
  derived from this software without specific prior
  written permission of the ASSIMP Development Team.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
---------------------------------------------------------------------------
*/

#ifndef AI_DEFINES_H_INC
#define AI_DEFINES_H_INC

// compiler specific includes and definitions
#if (defined _MSC_VER)

	// include stdint.h from the C98 standard
#	include "Compiler/VisualStudio/stdint.h"

#	undef ASSIMP_API

	// ************************************************************
	// Define ASSIMP_BUILD_DLL_EXPORT to build a DLL of the library
	// ************************************************************
#	if (defined ASSIMP_BUILD_DLL_EXPORT)
#		define ASSIMP_API __declspec(dllexport)

	// ************************************************************
	// Define ASSIMP_DLL before including Assimp to use ASSIMP in
	// an external DLL (otherwise a static library is used)
	// ************************************************************
#	elif (defined ASSIMP_DLL)
#		define ASSIMP_API __declspec(dllimport)
#	else
#		define ASSIMP_API 
#	endif

#endif // (defined _MSC_VER)

#ifdef __cplusplus
#	define C_STRUCT
#else
	// ************************************************************
	// To build the documentation, make sure ASSIMP_DOXYGEN_BUILD
	// is defined by Doxygen's preprocessor. The corresponding
	// entries in the DoxyFile look like this:
#if 0
	ENABLE_PREPROCESSING   = YES
	MACRO_EXPANSION        = YES
	EXPAND_ONLY_PREDEF     = YES
	SEARCH_INCLUDES        = YES
	INCLUDE_PATH           = 
	INCLUDE_FILE_PATTERNS  = 
	PREDEFINED             = ASSIMP_DOXYGEN_BUILD=1
	EXPAND_AS_DEFINED      = C_STRUCT
	SKIP_FUNCTION_MACROS   = YES
#endif
	// ************************************************************
#	if (defined ASSIMP_DOXYGEN_BUILD)
#		define C_STRUCT
#	else
#		define C_STRUCT struct
#	endif
#endif

#ifdef _DEBUG
#	define AI_DEBUG_INVALIDATE_PTR(ptr) ptr = 0;
#else
#	define AI_DEBUG_INVALIDATE_PTR(ptr)
#endif

#endif // !! AI_DEFINES_H_INC
