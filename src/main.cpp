#include <shlwapi.h>

#include "window_procedures.h"
#include "gdi_plus_from_resource.h"
#include <assert.h>




int CALLBACK wWinMain( HINSTANCE hInstance, HINSTANCE, PWSTR szCmdLine, int nCmdShow )
{
   ULONG_PTR token;
   Gdiplus::GdiplusStartupInput input = { 0 };
   input.GdiplusVersion = 1;
   GdiplusStartup( &token, &input, NULL );


   HMODULE hMod = GetModuleHandle( NULL );
   HRSRC hRes = FindResource( hMod, MAKEINTRESOURCE( IDB_BITMAP1 ), L"JPG" );
   HGLOBAL hGlobal = LoadResource( hMod, hRes );
   void* pResData = LockResource( hGlobal );
   DWORD dwResData = SizeofResource( hMod, hRes );
   IStream* pStream = SHCreateMemStream( (BYTE*)pResData, dwResData );
   P_IMG = new Gdiplus::Image( pStream );
   pStream->Release();


   MSG message{ };
   HWND hWindow{ };

   WNDCLASSEX windowClass{ sizeof( WNDCLASSEX ) };
   windowClass.cbClsExtra = 0;
   windowClass.cbWndExtra = 0;
   windowClass.hbrBackground = reinterpret_cast<HBRUSH>( GetStockObject( BLACK_BRUSH ) );
   windowClass.hCursor = LoadCursor( nullptr, IDC_ARROW );
   windowClass.hIcon = LoadIcon( nullptr, IDI_APPLICATION );
   windowClass.hIconSm = LoadIcon( nullptr, IDI_APPLICATION );
   windowClass.hInstance = hInstance;
   windowClass.lpfnWndProc = WndProc;
   windowClass.lpszClassName = L"Name";
   windowClass.lpszMenuName = nullptr;
   windowClass.style = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS;

   if( !RegisterClassEx( &windowClass ) )
      return EXIT_FAILURE;

   hWindow = CreateWindow( windowClass.lpszClassName,
                            L"Title",
                            WS_OVERLAPPEDWINDOW,
                            0,
                            0,
                            600,
                            600,
                            nullptr,
                            nullptr,
                            windowClass.hInstance,
                            nullptr );

   if( hWindow == INVALID_HANDLE_VALUE )
      return EXIT_FAILURE;

   ShowWindow( hWindow, nCmdShow );
   UpdateWindow( hWindow );


   while( GetMessage( &message, nullptr, 0, 0) )
   {
      TranslateMessage( &message );
      DispatchMessage( &message );
   }

   Gdiplus::GdiplusShutdown( token );
   return static_cast<int>( message.wParam );
}
