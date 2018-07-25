#include "Makros.h"

///ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
/// Отлов нажатых клавиш.                                                      |
///ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
class cKeys
{
public:
    cKeys() : bEscape(false)
    {   
    }
    
    //------------------------------------------------------------------------->
    bool   bEscape;

    ///^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    bool key_Visible()
    {   if(GetAsyncKeyState(VK_LMENU) && (GetAsyncKeyState('1') == -32767) )
        {   //Conwin.bVisible = !Conwin.bVisible;
            beep();
            return true;
        }
        return false;
    }
    bool key_Stop()
    {   if(GetAsyncKeyState(VK_ESCAPE) == -32767)
        {   beep();
            return true;
        }
        return false;
    }

    bool checkkey(int MYKEY)
    {   if(GetAsyncKeyState(MYKEY) == -32767)
        {   beep();
            return true;
        }
        return false;
    }
    ///vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

private:
    //------------------------------------------------------------------------->
/*
    void check(int key)
    {   if (GetAsyncKeyState(VK_LMENU ))
        {   Conwin.bVisible = !Conwin.bVisible;
            std::cout << "\a";
        }
    }*/

    //------------------------------------------------------------------------->
    void stealth()
    {   HWND stealth;
        AllocConsole();
        stealth = FindWindowA("consoleWindowClass", NULL);
        ShowWindow(stealth, 1);  //1-видим окно, 0 - невидмиое окно
    }

    void beep()
    {   std::cout << "\a";
    }

};

