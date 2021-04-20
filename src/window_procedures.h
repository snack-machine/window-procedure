#pragma once

#include <Windows.h>

#include "resource.h"
#include "gdi_plus_from_resource.h"




#pragma comment (lib, "Gdiplus.lib")


constexpr size_t BUTTON1_ID = 2222;
constexpr COLORREF DEFAULT_COLOR = RGB(0, 0, 255);



LRESULT CALLBACK WndProc( HWND hWindow, UINT message, WPARAM wParam, LPARAM lParam );

LRESULT CALLBACK CustomWndProc( HWND hWindow, UINT message, WPARAM wParam, LPARAM lParam );

