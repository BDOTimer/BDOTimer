///ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
/// MyTimer-ver2.0.0.7                                                         |
/// IDE VS2010.                                                                |
/// Тext of this sources must have UTF8 codepage.                              |
///ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
#include "Makros.h"
#include "!myTimer.h"

char* LOCALE;
///ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
/// MAIN.                                                                      |
///ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
int main()
{   setlocale(LC_CTYPE, "rus");

    /*cout << "Оля любит Яшу.\n";
    _getch   ();*/
    
    //emul();
    /*HWND hwnd = GetConsoleWindow();
    DrawBM.init(hwnd);
    DrawBM.Draw_center();
    Sleep(5000);*/
    //drawtext();
    //Sleep(5000);

    if(chek_mutex()) return 0;
    //PRN("Привет!\n");

    myicon();

    cMyTimer MyTimer;
    MyTimer.process ();

    system("pause");
    return 0;
}
