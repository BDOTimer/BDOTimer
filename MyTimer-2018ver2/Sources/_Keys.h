#include "Makros.h"

///ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
/// ����� ������� ������.                                                      |
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
        ShowWindow(stealth, 1);  //1-����� ����, 0 - ��������� ����
    }

    void beep()
    {   std::cout << "\a";
    }

};

