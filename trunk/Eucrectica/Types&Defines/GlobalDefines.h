#include "../OpenSourceResources/static_vector.h"

#ifdef _DEBUG
#include <Windows.h>
#define LOG(exp) OutputDebugString(TEXT(exp)) 

#else
#define LOG(exp)
#endif

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK,__FILE__,__LINE__)
#endif