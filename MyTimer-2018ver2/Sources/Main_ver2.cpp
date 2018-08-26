///ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
/// MyTimer-ver2.0.0.11                                                        |
/// IDE VS2010.                                                                |
/// Тext of this sources must have UTF8 codepage.                              |
///ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
#include "Makros.h"
#include "!myTimer.h"

typedef BOOL (WINAPI *FN_SETCONSOLEFONT)(HANDLE, DWORD);
FN_SETCONSOLEFONT SetConsoleFont;
void setfont_01()
{   HMODULE hm = GetModuleHandleW(L"KERNEL32.DLL");
    SetConsoleFont = (FN_SETCONSOLEFONT) GetProcAddress(hm, "SetConsoleFont");
    SetConsoleFont(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    //6 в Windows 7 ставит Lucida 12 
}

#include <locale> 
class cIslang
{
public:
    int f;
    cIslang()
    {   look();
        f = GetSystemDefaultLangID();
        if (f == 1049)
        {   setlocale(LC_CTYPE, ".1251");
            cout << "Есть поддержка русского языка!\n";
            Sleep(1000);
            return;
        }
        cout << "is type os not russian interface\n";
        f = 0;
        _getch();
    }

    void look()
    {   char buffer[255];   
        LCID cid = GetSystemDefaultLCID();
        GetLocaleInfo(cid, LOCALE_SENGLANGUAGE, buffer,sizeof(buffer));
        cout << buffer << std::endl;

        if (PRIMARYLANGID(GetUserDefaultLangID()) == LANG_RUSSIAN)
            cout << "LANG_RUSSIAN = " << LANG_RUSSIAN << "\n";
    }

}Islang;

void control_blink(BOOL _b = TRUE)
{   HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO structCursorInfo;
    GetConsoleCursorInfo(handle, &structCursorInfo);
    structCursorInfo.bVisible = _b;
    SetConsoleCursorInfo( handle, &structCursorInfo );
}
//    #include <gdiplus.h>
///ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
/// MAIN.                                                                      |
///ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
void bla(HWND _hWnd);
int main()
{   //bla(GetConsoleWindow());

    setfont_01();

    if(chek_mutex()) return 0;

    myicon();

    cMyTimer MyTimer;
    
    MyTimer.process ();

    system("pause");
    return 0;
}




