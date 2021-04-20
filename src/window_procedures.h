#pragma once

#include "resource.h"
#include "gdi_plus_from_resource.h"

#include <Windows.h>
#include <gdiplus.h>


#pragma comment (lib, "Gdiplus.lib")


constexpr size_t BUTTON1_ID = 2222;
constexpr COLORREF DEFAULT_COLOR = RGB(0, 0, 255);



LRESULT CALLBACK CustomWndProc( HWND hWindow, UINT message, WPARAM wParam, LPARAM lParam )
{
   switch( message )
   {
      case WM_CREATE:
      {

         break;
      }
      case WM_COMMAND:
      {
         switch( LOWORD( wParam ) )
         {
            case BUTTON1_ID:
            {
               switch( HIWORD( wParam ) )
               {
                  case BN_DOUBLECLICKED:
                  {
                     MessageBox( hWindow, L"Second Procedure!", 0, 0 );
                     break;
                  }
               }
               break;
            }
         }
         break;
      }
      case WM_PAINT:
      {
         using namespace Gdiplus;
      
         PAINTSTRUCT ps;
         HDC hdc = BeginPaint( hWindow, &ps );

         Graphics graphics( hdc ); 

         graphics.DrawImage( P_IMG, 10, 10 );

         EndPaint( hWindow, &ps );
         break;
      }
      case WM_DESTROY:
      {
            PostQuitMessage( EXIT_SUCCESS );
            return 0;
      }
      default:
      {
         return DefWindowProc( hWindow, message, wParam, lParam );
      }
   }
}


LRESULT CALLBACK WndProc( HWND hWindow, UINT message, WPARAM wParam, LPARAM lParam)
{
   switch( message )
   {
      case WM_CREATE:
      {
         HWND hButton = CreateWindow( L"BUTTON",
                                       L"Double click handler",
                                       WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | CS_DBLCLKS | BS_NOTIFY,
                                       0,
                                       0,
                                       350,
                                       50,
                                       hWindow,
                                       reinterpret_cast<HMENU>( BUTTON1_ID ),
                                       nullptr,
                                       nullptr );

         break;
      }
      case WM_COMMAND:
      {
         switch( LOWORD( wParam ) )
         {
            case BUTTON1_ID:
            {
               switch( HIWORD( wParam ) )
               {
                  case BN_DOUBLECLICKED:
                  {
                     MessageBox( hWindow, L"First Procedure!", 0, 0 );
                     SetWindowLongPtr( hWindow, GWLP_WNDPROC, ( LONG_PTR ) &CustomWndProc );
                     break;
                  }
               }
               break;
            }
         }
         break;
      }
      case WM_PAINT:
      {
         PAINTSTRUCT paintStruct;
         RECT rectangle;
         HDC hdc = BeginPaint( hWindow, &paintStruct );
         GetClientRect( hWindow, &rectangle );
         SetDCBrushColor( hdc, DEFAULT_COLOR );
         FillRect( hdc, &rectangle, reinterpret_cast<HBRUSH>( GetStockObject( DC_BRUSH ) ) );
         EndPaint( hWindow, &paintStruct );
         break; 
      }
      case WM_DESTROY:
      {
         PostQuitMessage( EXIT_SUCCESS );
         return 0;
      }
      default:
      {
         return DefWindowProc( hWindow, message, wParam, lParam );
      }
   }
}
