#pragma once
#ifndef _APPLICATION_WIN32_H_
#define _APPLICATION_WIN32_H_
#ifdef WIN32
#include <windows.h>    // include the basic windows header file
#include <windowsx.h>

class Application
{
public:
	static Application* Singleton(){return &m_Singleton;}
	HWND& GetHWND(){return m_HWND;}
	void Init();
private:
	static Application m_Singleton;
	Application(){};
	HWND m_HWND;
};

#endif//WIN32
#endif//_APPLICATION_WIN32_H_