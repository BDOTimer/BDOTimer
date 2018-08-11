﻿///ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
/// Главный класс.                                                             |
///ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
#include "Makros.h"

#include "_GetUserTime.h"
#include "_Conwin.h"
#include "_Keys.h"
#include "_MIDI.h"
#include "ShowBMP.h"

class cMyTimer
{
public:
    enum eMODECONSOLWIN
    {   e_START,
        e_INPUT,
        e_CHECK,
        e_MONITOR,
        e_SiGNAL,
        e_END
    }MODECONSOLWIN;

    cMyTimer() : MODECONSOLWIN(e_START)//--Конструктор:----------------------->
    {   static connector conn_extHook(*this, &cMyTimer::extHook);
        UserTime.myGetLine.hook = &conn_extHook;
    }

    /// Данная функция вызывается внутри cmyGetLine::get()--------------------->
    /// при нажатой клавиши ALT.
    inline void extHook()
    {   while(true)
        {
            if(Keys.key_Visible()) 
            {   Conwin.inverse_visible();
                Conwin.set_active     ();
                if(Conwin.bVisible)
                {   UserTime.propt();

                /*cout << ">>> ";
                cout << myLine.getstr();
                cout << "\n";*/

                    cout << ">>> ";
                    cout << UserTime.getstr();
                    //FlushConsoleInputBuffer(Conwin.hCon_INPUT);
                    
                }
                else Sleep(200);
            }
            if(Conwin.bVisible) return;
            Sleep(200);
        }
    }

    void process()
    {   while (true)
        {
            switch(MODECONSOLWIN)
            {   case e_START:
                    MODECONSOLWIN = start();
                    break;

                case e_INPUT:
                    MODECONSOLWIN = input();
                    break;

                case e_CHECK:
                    MODECONSOLWIN = check();
                    break;

                case e_MONITOR:
                    MODECONSOLWIN = monitor();
                    break;

                case e_SiGNAL:
                    MODECONSOLWIN = signal();
                    break;

                case e_END:
                    return;
                    //break;

                default:
                    PRNERR("parametr MODECONSOLWIN");
                    exit(0);
            }
        }
   
    }

private:
    ///------------------------------------------------------------------------>
    cKeys   Keys;
    cConwin Conwin;
    cGetUserTime UserTime;
    cMIDI   MIDI;

    int     user_input_time; // в секундах.
    
    void cursor(int _v = TRUE)
    {   CONSOLE_CURSOR_INFO C;
        C.bVisible = 0;
        C.dwSize   = 100;
        SetConsoleCursorInfo(Conwin.hwnd, &C);
    }

    eMODECONSOLWIN start()//---------------------------------------------start()
    {   while(true)
        {   
            SetWindowLongPtr(Conwin.hwnd, GWL_STYLE, 
                                          WS_OVERLAPPED |
                                          WS_CAPTION    |
                                          WS_SYSMENU
            );
            cursor(FALSE);

            UserTime.init(&Conwin);
            Conwin.show();
            Conwin.setmode_input();
            PRN("Подготовка к работе...");
        
            MIDI.open(Conwin.get_HWND(), "signal.mid");

            return e_INPUT;
        }
    }

    eMODECONSOLWIN input()//---------------------------------------------input()
    {   while(true)
        {   user_input_time = UserTime.get();
            //while(!Keys.checkkey(VK_ESCAPE)) Sleep(100);
            return e_CHECK;
        }
    }

    eMODECONSOLWIN check()//---------------------------------------------check()
    {   while(true)
        {   cout << COLOR(rus("\nТаймер был запущен!"), 10);
            cout << COLOR(rus("\nБыстро спрятать Таймер:[Пробел]!"), 10);
            cout << COLOR(rus("\nДля отмены жми:        [Escape]"), 8);
            cout << COLOR(rus("\nДля контроля времени:  [ALT+1]\n"), 8);
            //_getch();

            int pause = 9000;//--------------------------Ожидание проверки ввода:
            while(!Keys.checkkey(VK_SPACE))
            {   if(Keys.checkkey(VK_ESCAPE))
                {   return e_INPUT;
                }
                std::cout << rus("\rСкрытие окна через: ")
                          << COLOR(pause/1000, 14) << rus(" секунд.");
                Sleep(500);
                pause -= 500;
                user_input_time -= 500;
                if(pause == 0) return e_MONITOR;
            }

            //----------------------------------------------------------------->
            MIDI.stop();
            
            return e_MONITOR;
        }
    }

    eMODECONSOLWIN monitor()//-----------------------------------------monitor()
    {   system("cls");
        int t = user_input_time;
        Conwin.noshow();
        Conwin.setmode_monitor();
        for(int i = t; i > 0; i -= 500)
        {   if(Conwin.bVisible)
                std::cout << "\r " << COLOR(i/1000, 14) << rus(" секунд.");

            Sleep(500);

            if(Conwin.check_active_visible() && Keys.key_Stop()) 
            {   system("cls");
                Conwin.setmode_input();
                std::cout << rus("\n Период удален!\a\n");
                Sleep(2000);
                system("cls");

                return e_INPUT;
            }

            if(Keys.key_Visible()) 
            {   Conwin.inverse_visible();
            }

            if(Conwin.bVisible)
                std::cout << "\r                                         ";
        }

        system("cls");
        Conwin.show();
        Conwin.setmode_input();
    
        cout << COLOR(rus("\n ПОРА ДЕЙСТВОВАТЬ!\n\n"), 14);
        cout << " " << COLOR(UserTime.getstr(), 12) << "\n";
        MIDI.play();
DrawBM.init();
DrawBM.Draw_center();
//Sleep(5000);
        
        TimeToAct();
        return e_INPUT;
    }

    eMODECONSOLWIN signal()//-------------------------------------------signal()
    {   
        while(true)
        {   return e_END;
        }
    }

    void TimeToAct()
    {   Conwin.set_active();

        RECT* rect = nullptr;
        GetWindowRect(Conwin.hwnd, rect);
        //mouseclick(rect->left-30, rect->top-30);

        //OpenIcon(Conwin.hwnd);

        // If it is minimized, show the window
    /*
        if (IsIconic(Conwin.hwnd))
        {   //ShowWindowAsync(Conwin.hwnd, SW_SHOW);
            OpenIcon(Conwin.hwnd);
            system("cls");
            SetWindowPos(Conwin.hwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
            Conwin.setmode_input();
        
    
            cout << COLOR(rus("\n ПОРА ДЕЙСТВОВАТЬ!\n"), 14);
        }*/

        while(true)
        {   if(Conwin.check_active_visible() && Keys.key_Stop()) 
            {   MIDI.stop();
                Conwin.inverse_visible();
                return;
            }
            Sleep(200);
        }
    }
};

inline void HandleInstanceMessage(HWND AppWnd)
{
    HWND H;
    DWORD CurID, ThrID;
    BOOL R;
    LPDWORD lpdwProcessId;

    H = GetForegroundWindow();
    ThrID = GetWindowThreadProcessId(H, lpdwProcessId);
    CurID = GetCurrentThreadId();
    R = AttachThreadInput(CurID, ThrID, true);
    SetForegroundWindow(AppWnd);
    if(R)
        AttachThreadInput(CurID, ThrID, false);
}
