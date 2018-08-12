///ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
/// MyTimer-ver2.0.0.8                                                         |
/// IDE VS2010.                                                                |
/// Тext of this sources must have UTF8 codepage.                              |
///ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
#include "Makros.h"
#include "!myTimer.h"

//#include <fcntl.h>
//#include <io.h>
//_setmode(_fileno(stdout), _O_U16TEXT);

typedef BOOL (WINAPI *FN_SETCONSOLEFONT)(HANDLE, DWORD);
FN_SETCONSOLEFONT SetConsoleFont;
void setfont_01()
{   HMODULE hm = GetModuleHandleW(L"KERNEL32.DLL");
    SetConsoleFont = (FN_SETCONSOLEFONT) GetProcAddress(hm, "SetConsoleFont");
    SetConsoleFont(GetStdHandle(STD_OUTPUT_HANDLE), 9);
}


///ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
/// MAIN.                                                                      |
///ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
int main()
{   /*SetConsoleCP(1251);
    SetConsoleOutputCP(1251);*/
    setlocale(LC_CTYPE, ".1251");
    //setlocale(LC_CTYPE, "");
    setfont_01();

    /*cout << "Оля любит Яшу.\n";
    _getch   ();*/

    if(chek_mutex()) return 0;
    //PRN("Привет!\n");

    myicon();

    cMyTimer MyTimer;
    MyTimer.process ();

    system("pause");
    return 0;
}
