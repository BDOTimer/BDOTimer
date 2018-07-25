///ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
/// MyTimer-ver2.0.0.6                                                         |
///ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
#include "Makros.h"
#include "!myTimer.h"

void simulateKeyPress(BYTE key)
{
    // Simulate a key press
    keybd_event( key, 0, 0, 0 );
    // Simulate a key release
    Sleep(1000);
    keybd_event( key, 0, KEYEVENTF_KEYUP, 0);
}

void emul()
{   Sleep(5000);
    while(true)
    {   simulateKeyPress(VK_SHIFT);
        Sleep(1000);
    }
    system("pause");
}

#include <conio.h>
void drawtext()
{
    HWND hwnd = GetConsoleWindow();
    HDC dc = GetDC(hwnd);
    TextOut(dc,10,10,"hi world",8);
    TextOut(dc,10,10,"hi world",8);
}

///ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
/// MAIN.                                                                      |
///ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
int main()
{   //emul();
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
