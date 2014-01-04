#pragma once
#ifndef GLOBAL_DEFINES_H_
#define GLOBAL_DEFINES_H_

#ifdef _DEBUG
#include <Windows.h>
#define LOG(exp) OutputDebugString(TEXT(exp)) 

#else
#define LOG(exp)
#endif//_DEBUG

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK,__FILE__,__LINE__)
#endif//_DEBUG


#endif//GLOBAL_DEFINES_H_