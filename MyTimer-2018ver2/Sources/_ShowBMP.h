#include "Makros.h"

class cDrawBM
{
    enum eISBMP
    {   BMP_RES,
        BMP_FILE
    }ISBMP;

public:
    cDrawBM(const char* _namefie) : hwnd(0)
    {   ISBMP = BMP_FILE;
        
        bmp_widht  = 100;
        bmp_height = 100;

        hBitmap = (HBITMAP)LoadImageA(NULL, _namefie, IMAGE_BITMAP,
                                      bmp_widht, bmp_height, LR_LOADFROMFILE);
        //hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));
        if(hBitmap == 0)MessageBox(hwnd, "Error::hBitmap == 0", "", MB_OK);
    }

    cDrawBM() : hwnd(0)
    {   ISBMP = BMP_RES;
        
        bmp_widht  = 100;
        bmp_height = 100;
    }

    HWND      hwnd;
    HDC       hdc;
    HINSTANCE hInst;

    void init(HWND _hwnd = 0)
    {   if(_hwnd == 0)
        {   /*static char MyName[MAX_PATH] = {0};
            GetModuleFileNameA(NULL, MyName, sizeof(MyName));
            MessageBox(hwnd, MyName, "", MB_OK);
            //HWND hwnd = FindWindowA(NULL, MyName);
            hwnd = FindWindow(NULL, MyName);
            if(hwnd == 0)MessageBox(hwnd, "Error::hwnd == 0", "", MB_OK);*/

            /*HMENU hSysMenu = GetSystemMenu(hwnd, false);
            DeleteMenu(hSysMenu, SC_CLOSE,MF_BYCOMMAND);*/
            hwnd = GetConsoleWindow();
            hInst = (HINSTANCE)hwnd;
        }
        else
        {   hwnd = _hwnd;
            hInst = (HINSTANCE)hwnd;
            //hInst = (HINSTANCE)_hwnd;
            /*std::cout << "hwnd  = " << hwnd  << "\n";
            std::cout << "hInst = " << hInst << "\n";
            Sleep(7000);*/
        }
        hdc = GetWindowDC(hwnd);
        if (hdc == 0)MessageBox(hwnd, "Error::hdc == 0", "", MB_OK);
        
        if(ISBMP  == BMP_RES)
        {   load_bmp_from_resurces();
        }

        InvalidateRect(hwnd,NULL,TRUE);
    }
    
    void Draw()
    {   //ZeroMemory(&ps, sizeof(PAINTSTRUCT));
        conwin_size();
        hdc = BeginPaint(hwnd, &ps);
              DrawBitmap(hdc);
              EndPaint  (hwnd, &ps);
    }

    void Draw_center()
    {   conwin_size();
        hdc = BeginPaint(hwnd, &ps);
              DrawBitmap(hdc, center_widht, center_height);
              EndPaint  (hwnd, &ps);
    }

    void DrawBitmap(HDC hdc, int x = 0, int y = 0)
    {
        HBITMAP hbmp;
        HDC     hMemDC;
        BITMAP  bm;
        POINT   ptSize, ptOrg;

        hMemDC = CreateCompatibleDC(hdc);
        hbmp = (HBITMAP)SelectObject(hMemDC, hBitmap);

        if (hbmp)
        {   // ƒл¤ контекста пам¤ти:
            SetMapMode(hMemDC, GetMapMode(hdc));

            // ќпредел¤ем размеры изображени¤:
            GetObject(hBitmap, sizeof(BITMAP), (LPSTR) &bm);
 
            ptSize.x = bm.bmWidth;
            ptSize.y = bm.bmHeight;

            // ѕреобразуем координаты устройства в логические
            // дл¤ устройства вывода:
            DPtoLP(hdc, &ptSize, 1);
 
            ptOrg.x = 0;
            ptOrg.y = 0;

            DPtoLP(hMemDC, &ptOrg, 1);

            BitBlt(hdc, x, y, ptSize.x, ptSize.y,
                    hMemDC, ptOrg.x, ptOrg.y, SRCCOPY);

            SelectObject(hMemDC, hbmp);
        }
        else MessageBox(hwnd, "Error::hbmp == 0", "", MB_OK);

        DeleteDC(hMemDC);
    }

    void conwin_size()
    {   RECT rc;
        GetClientRect(hwnd, &rc);

        center_widht  = (rc.right  - rc.left - bmp_widht )/2;
        center_height = (rc.bottom - rc.top  - bmp_height)/2;

        /*std::cout << "rc.left = " << rc.left << "\n";
        std::cout << "rc.top  = " << rc.top  << "\n";
        std::cout << center_widht << "\n";
        std::cout << center_height  << "\n";
        Sleep(5000);*/
        //_getch();
    }

private:
    HBITMAP hBitmap;
    PAINTSTRUCT ps;

    int bmp_widht;
    int bmp_height;

    int center_widht;
    int center_height;

    void load_bmp_from_resurces()
    {   
        hBitmap = (HBITMAP)LoadImageA((HINSTANCE)GetModuleHandle(0),
            MAKEINTRESOURCE(IDB_BITMAP1),
            IMAGE_BITMAP, bmp_widht, bmp_height, LR_DEFAULTCOLOR);
        if(hBitmap == 0)MessageBox(hwnd, "Error::hBitmap == 0", "", MB_OK);
    }
}DrawBM;//("1.bmp");