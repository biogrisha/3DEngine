#define _USE_MATH_DEFINES
#include<math.h>
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include "ThreeDObject.h"
#include "Observer.h"
using namespace Gdiplus;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void UpdateImage();

Observer* observer;
Gdiplus::Graphics *graphics;
Color* white = new Color(255, 255, 255);

HDC hdc;
HWND                hWnd;
MSG                 msg;
BOOL                bRet;
WNDCLASS            wndClass;
GdiplusStartupInput gdiplusStartupInput;
ULONG_PTR           gdiplusToken;

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow)
{



    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    wndClass.style = CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc = WndProc;
    wndClass.cbClsExtra = 0;
    wndClass.cbWndExtra = 0;
    wndClass.hInstance = GetModuleHandle(NULL);
    wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndClass.hCursor = LoadCursor(NULL, IDC_HAND);
    wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndClass.lpszMenuName = NULL;
    wndClass.lpszClassName = TEXT("GettingStarted");

    RegisterClass(&wndClass);

    hWnd = CreateWindow(
        TEXT("GettingStarted"),   // window class name
        TEXT("Getting Started"),  // window caption
        WS_OVERLAPPEDWINDOW,      // window style
        CW_USEDEFAULT,            // initial x position
        CW_USEDEFAULT,            // initial y position
        CW_USEDEFAULT,            // initial x size
        CW_USEDEFAULT,            // initial y size
        NULL,                     // parent window handle
        NULL,                     // window menu handle
        hInstance,                // program instance handle
        NULL);                    // creation parameters

    
    

    hdc = GetDC(hWnd);
    graphics = new Gdiplus::Graphics(hdc);

    Bitmap masterpieceBitmap(L"Masterpiece.bmp");
    Bitmap helloBitmap(L"Hello.bmp");
    Color black(0, 0, 0);
    //Create box
    ThreeDObject* box = new ThreeDObject();
    float j = 0;
    for (int x = 0; x < masterpieceBitmap.GetWidth();x++)
    {
        j += 0.1;
        for (int y = 0; y < masterpieceBitmap.GetHeight(); y++)
        {
            masterpieceBitmap.GetPixel(x, y, &black);
            if (black.GetR() == 0 && black.GetG() == 0 && black.GetB() == 0)
            {
                ThreeDObject::ThreeDPixel pix;
                    pix.X = (-x*4)+300;
                    pix.Y = (-y*4) + 100;
                    pix.Z = 300;
                    pix.Brightness = 10;
                    box->AddPixel(pix);
                
            }


        }
    }
    observer = new Observer(400, box);

    ShowWindow(hWnd, 10);
    UpdateWindow(hWnd);
    

    graphics->Clear(*white);
    graphics->DrawImage(&helloBitmap, 60, 10);
   

    while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0)
    {

        if (bRet == -1)
        {
            // handle the error and possibly exit
        }
        else
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        
    }
    
    delete box;
    delete observer;
    DeleteObject(white);
    GdiplusShutdown(gdiplusToken);
    return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
        WPARAM wParam, LPARAM lParam)
    {
        HDC          hdc;
        PAINTSTRUCT  ps;

        switch (message)
        {
        case WM_PAINT:
           
            return 0;
        case WM_KEYDOWN: //Command from Child windows and menus are under this message
            switch (wParam) //the ID is is wParam
            {
                case VK_LEFT: //check for our button ID
                {
                    observer->Rotate(true);
                    UpdateImage();
                    return 0;
                }
                case VK_RIGHT: //check for our button ID
                {
                    observer->Rotate(false);
                    UpdateImage();
                    return 0;
                }
                case VK_UP: //check for our button ID
                {
                    observer->Move(true);
                    UpdateImage();
                    return 0;
                }
                case VK_DOWN: //check for our button ID
                {
                    observer->Move(false);
                    UpdateImage();
                    return 0;
                }
            }
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    } // WndProc

    void UpdateImage()
    {
        
        graphics->Clear(*white);
        graphics->DrawImage(observer->GetImage(), 60, 10);
    }

