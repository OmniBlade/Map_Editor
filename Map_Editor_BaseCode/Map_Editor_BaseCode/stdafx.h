// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#ifdef _MSC_VER

#include <windows.h>
#include <tchar.h>

#else

#include <string.h>
#include <memory>

#define TCHAR		char
#define _T(x)		x
#define _tprintf	printf
#define _tmain		main
#define nullptr         NULL
#define _strcmpi        strcasecmp
#define _strdup         strdup

namespace std{

template<typename T, typename ...Args>
std::unique_ptr<T> make_unique( Args&& ...args ) {
  return std::unique_ptr<T>( new T( std::forward<Args>(args)... ) );
}

}

#endif
#include "targetver.h"
#include <stdio.h>

typedef unsigned char byte;
typedef unsigned short word;
typedef unsigned long dword;

// TODO: reference additional headers your program requires here
