#include "Makros.h"

#ifndef CONWIN_H//ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo|
#define CONWIN_H

const char* MODE_MONITOR = "mode con cols=15 lines=1";
const char* MODE_INPUT3  = "mode con cols=35 lines=3";
const char* MODE_INPUT24 = "mode con cols=35 lines=20";

char* rus(const char*);

///ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
/// Операции с окном консоли.                                                  |
///ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
class cConwin
{
public:
    HANDLE hCon_OUTPUT;
    HANDLE hCon_INPUT;
    HWND   hwnd;
    bool   bVisible; // Индикатор видимости.

    enum   MODE
    {   M_INPUT,
        M_MONITOR
    }mode;

    // Конструктор:------------------------------------------------------------>
    cConwin() : bVisible(true), mode(M_INPUT)
    {   hCon_OUTPUT = GetStdHandle(STD_OUTPUT_HANDLE);
        if( hCon_OUTPUT == INVALID_HANDLE_VALUE )
        {   //syserror();
        }
        hCon_INPUT = GetStdHandle(STD_INPUT_HANDLE);
        if( hCon_OUTPUT == INVALID_HANDLE_VALUE )
        {   //syserror();
        }
        hwnd = GetConsoleWindow();
    }

    bool check_active_visible()
    {   if(bVisible && check_active()) return true;
        return false;
    }

    inline void show()
    {   ShowWindow(hwnd,SW_NORMAL);
        SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_SHOWWINDOW);
        bVisible = true;

        switch(mode)
        {   case M_MONITOR:
                system (MODE_MONITOR);
                break;
            case M_INPUT:
                system (MODE_INPUT24);
                break;
        }
    }

    inline void noshow()
    {   ShowWindow(hwnd,SW_MINIMIZE);//SW_NORMAL
        SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_HIDEWINDOW);
        bVisible = false;
    }

    ///^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    void setmode_input()
    {   mode = M_INPUT;
        system (MODE_INPUT24);
        SetConsoleTitle(rus("My Timer 2018"));
    }
    void setmode_monitor()
    {   mode = M_MONITOR;
        system (MODE_MONITOR);
        SetConsoleTitleW(L"Ждём...");
    }
    void inverse_visible()
    {   bVisible = !bVisible;
    
        if(bVisible)show  ();
        else        noshow();
    }
    inline HWND get_HWND(){return hwnd;}

    void set_active()
    {   if(bVisible)
        {   //ShowWindow (hwnd, SW_RESTORE);
            //SetActiveWindow(hwnd);
            //SetForegroundWindow(hwnd);

            SetForegroundWindow(hwnd);
            //SetActiveWindow(hwnd);
            //SetFocus(hwnd);

            SetWindowPos(hwnd, HWND_TOP, 0, 0, 0, 0,SWP_NOMOVE | 
                SWP_NOSIZE | SWP_SHOWWINDOW);
            SetForegroundWindow(hwnd);
        }
        
    }
    ///vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

private:
    // Просерка активности нашего окна:---------------------------------------->
    bool check_active()
    {   HWND a = GetForegroundWindow();
        if(a == hwnd) return true;
        return false;

        //SetForegroundWindow(hwnd);
    }

};

#endif//ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo|
