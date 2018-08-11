///ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
/// Консольный ввод собственной выпечки.                                       |
///ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
#include <iostream>
#include <windows.h>
#include <conio.h>

using std::wcout;

inline bool checkkey(int MYKEY)
{   if(GetAsyncKeyState(MYKEY) == -32767)
    {   //cout << "\a";
        return true;
    }
    return false;
}

inline SHORT checkkey_ALT(int MYKEY)
{   SHORT k = GetAsyncKeyState(MYKEY);
    if( k == -32767)
    {   //cout << "\a";
        return k;
    }
    else if( k == -32768)
            if(_kbhit())
                _getch();
    return k;
}

///ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
/// class cmyGetLine;                                                          |
///ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
class cmyGetLine
{
public:
    cmyGetLine()//---------------------------------------------------Конструктор
    {   
    }

    connector* hook;

    inline  void get(char* _b, int _n)//-----------------------------------get()
    {   itterator = 0;
        
        int  code;

        while(true)
        {   
            if(!checkkey_ALT(VK_LMENU))
            {   
                if(_kbhit())
                {   code = _getch();
                
                    switch(code)//---------------------------------------------v
                    {   
                        case VK_LMENU:
                            break;

                        case VK_BACK:
                        {   if(itterator)
                            {     itterator--;
                               _b[itterator] = 0;
                                cout << "\b \b";
                            }
                            break;
                        }
                        case VK_RETURN:
                        {   _b[itterator] = 0;
                            return;
                        }
                        case VK_ESCAPE:
                            break;

                        default:
                        {   if(_n > itterator)
                            {   char symb = static_cast<char>(code);
                                OemToCharA(&symb, &symb);
                                _b[itterator++] = symb;
                                _b[itterator]   = 0;
                                cout << symb;
                            }
                        }
                    }//--------------------------------------------------------^
                }
            }
            else
            {   (*hook)();
                Sleep(200);
            }
            Sleep(20);
        }
    }

    inline void showbuffer()
    {   //cout << "\n" << _b << "\n";
    }

private://--------------------------------------------------------------------->
    int  itterator;

};

///ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
/// Процедуры с глобальным временем.                                           |
///ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
#include <ctime> 
class cGlobalTime
{
public:
    int    allseconds;
    int    hour;
    int    minutes;

    // Колво минут обратного осчета в часы.------------------------------------>
    void converter_minutes_in_clock(int _minutes)
    {   get_nowtime();
        allseconds = _minutes * 60;
        time_t globalsec_future  = time(0) + _minutes * 60;
        globaltime_future = localtime(&globalsec_future);
        hour    = globaltime_future->tm_hour;
        minutes = globaltime_future->tm_min;
        show();
    }
    // Часы в минуты обратного осчета.----------------------------------------->
    void converter_clock_in_minutes(int _h, int _m)
    {       get_nowtime();
        int timesec    = (globaltime->tm_hour * 60 +
                          globaltime->tm_min) * 60 +
                          globaltime->tm_sec;

            allseconds    = (60 * _h + _m)*60 - timesec;// От начала суток.
            if(allseconds < 0) allseconds += SECINDAY;
            hour          = _h;
            minutes       = _m;

        show();
    }

private:
    time_t globalsec;
    tm*    globaltime;
    tm*    globaltime_future;

    static const int SECINDAY = 86400; // Кол-во секунд в сутках.

    inline void get_nowtime()
    {       globalsec  = time(0);
            globaltime = localtime(&globalsec);
    }

    void show()
    {   cout << rus("Текущее время:       ")
             << COLOR(globaltime->tm_hour, 15) << rus(" ч") << " : " 
             << COLOR(globaltime->tm_min,  15) << rus(" м") << "\n";
        cout << rus("Установленное время: ")
             << COLOR(hour,    15)    << rus(" ч") << " : " 
             << COLOR(minutes, 15)    << rus(" м") << "\n";
        cout << rus("Осталось всего секунд: ")
             << COLOR(allseconds, 15) << "\n";
    }
}GlobalTime;

#include "_Conwin.h"
///ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
/// "Интеллектуальный" ввод времени.                                           |
///ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
class cGetUserTime///----------------------------------------------------cMyLine
{
public://---------------------------------------------------------------------->
    enum E_TYPEINPUT
    {   T_ERROR = 0,
        T_MINUTE,
        T_CLOCK
    }TYPEINPUT;

    cmyGetLine myGetLine;
    cConwin* pConwin;
    void init(cConwin* _pConwin)
    {   pConwin = _pConwin;
    }
    
    cGetUserTime()
    {   
    }
    
    struct sTime
    {   sTime() : h(0), m(0), allsecond(0)
        {   
        }
        int h, m;
        int reverse; // В минутах обратный отсчет.
        int allsecond;
    }Time;

    inline void propt()
    {   cout << COLOR(rus("Введите время в одном из форматов:\n"), 15);
        cout << rus("1. Количество минут до сигнала.\n");
        cout << rus("2. Или в формате: Часы, Минуты\n   время сигнала.\n\n");
    }

    inline int get()//-----------------------------------------------------get()
    {   system("cls");
        TYPEINPUT = T_ERROR;
        propt();

        do//------------------------------------------------------------------->
        {   
            FlushConsoleInputBuffer(pConwin->hCon_INPUT);
            cout << ">>> ";

            str[0] = '\0';
            myGetLine.get(str, cExtract::N);

            system("cls");
            
            cout << "str = " << str << std::endl;

            Extract.make(str);
            Extract.deb_show();
            
            if(detail_error())
            {   cout << "Extract.error = " << COLOR(Extract.error, 12) << "\n";
                cout << rus("\nПовторите ввод!") << "\n";
            }
            else
            {   cout << "Extract.error = " << COLOR(Extract.error, 10) << "\n";
                cout << COLOR(rus("Значение Таймера УСТАНОВЛЕННО!"), 10) << "\n";
            }
            cout << "===================================\n";
        }while(Extract.error);
        //--------------------------------------------------------------------->
        
        TYPEINPUT = (E_TYPEINPUT)Extract.i;
        //cout << rus("Отлично! - TYPEINPUT = ") << TYPEINPUT << "\n";

        switch(TYPEINPUT)
        {   case T_MINUTE:
            {   PRN("Обратный отсчет:[Минуты]");
                Time.reverse = Extract.m[0];
                GlobalTime.converter_minutes_in_clock(Time.reverse);
                cout << rus("Режим: ") << COLOR("T_MINUTE", 13) << "\n";
                cout << rus("Осталось всего секунд: ") << GlobalTime.allseconds
                     << "\n";
                return GlobalTime.allseconds*1000;
            }

            case T_CLOCK:
            {   PRN("Часы:[Час, Mинуты]");
                Time.h = Extract.m[0];
                Time.m = Extract.m[1];
                GlobalTime.converter_clock_in_minutes(Time.h, Time.m);
                cout << rus("Режим: ") << COLOR("T_CLOCK", 13) << "\n";
                return GlobalTime.allseconds*1000;
            }
            
            case T_ERROR:
            {   PRN("Режим времени не установлен!\n");
                break;
            }

            default:
                PRN("Неизвестный режим!\n");
        }

        system("pause");
        return -1;
    }
    inline char* getstr(){return str;}

private://--------------------------------------------------------------------->

    ///-----------------------------------------------------------------cExtract
    class cExtract
    {   
    public:
        static const int N = 30;
        cExtract() : error(0), pMessErr(NULL){}
        //--------------------------------------------------------------------->
        int m[3];
        int numberdigit[3];
        int i;
        int error;
        char* pMessErr;

        //----------------------------------------------------------------init()
        inline void init(){  m[0] = m[1] = m[2] = -999; i = 0; error = 0;}
        void deb_show()//---------------------------------------------deb_show()
        {   cout << m[0] << "." << m[1] << "." << m[2] << "\n"
            << "i = " << i << "\n";
        }

        inline void make(char* p)//---------------------------------------make()
        {   init();

            i = 0;
            poz_symb = 0;
            while(*p != 0)
            {   //cout << *p;
                if(isdigit(*p))
                {   if(i == 2)
                    {   error |= 2;
                        PRN("Слишком много данных!\n");
                        return;
                    }
                    m[i++] = getgigit(p);

                    if(*p == 0)
                    {   if(poz_symb == cExtract::N-1)
                        {   error |= 16;
                            PRN("Слишком много символов!\n");
                            std::cin.clear();
                            std::cin.ignore(32767, '\n');
                            return;
                        }
                        break;
                    }
                    poz_symb++;
                }
                p++;
            }
            if(0 == i) 
            {   error |=  1;
                PRN("Ввод пустой строки!\n");
            }
        }

    private:
        int poz_symb;
        int getgigit(char*& p)//--------------------------------------getgigit()
        {   
            int  i = 0;
            char s[N];
            while(isdigit(*p))
            {   s[i++] = *p++;
                poz_symb++;
            }
            s[i] = NULL;
            if(i > 4) error |= 4; // "Разряднось времени превышена!"
            if(i > 2) error |= 8; // "Разряднось времени превышена!"
            //cout << "test1 = " << atoi(s) << "\n";
            return atoi(s);
        }
    }Extract;

    bool detail_error()//-----------------------------------------detail_error()
    {   if(BIT_IS1(Extract.error, 4)) 
        {   PRN("Слишком много символов!-2");
            PRN("(не более 30 символов)\n");
            return true;
        }
        
        //if(Extract.i == 2 && BIT_IS1(Extract.error, 3) ) return true;
        if(Extract.i == 2)
             {   if(BIT_IS1(Extract.error, 3) || BIT_IS1(Extract.error, 2))
                 {   PRN("Превышен диапазон значений:");
                     PRN("Часы[0-23],Минуты[0-59].");
                     return true;
                 }

                 if(Extract.m[0] > 23) 
                 {   PRN("Значение часа превышено!");
                     PRN("(диапазон значений: [0-23])");
                     Extract.error |= 64;
                     return true;
                 }
                 else if(Extract.m[1] > 59)
                 {   PRN("Значение минут превышено!");
                     PRN("(диапазон значений: [0-59])");
                     Extract.error |= 128;
                     return true;
                 }
             }
        else if((Extract.i == 1) && Extract.m[1] > 9999)
             {   PRN("Количество минут превышено!");
                 PRN("(диапазон значений: [0-9999])");
                 Extract.error |= 4;
                 //orbit(Extract.error, 00000000100b);
                 return true;
             }

        if(Extract.error) return true;
                          return false;
    }

    void clear_input()//-------------------------------------------clear_input()
    {   FlushConsoleInputBuffer(pConwin->hCon_INPUT);
    /*
        std::cin.clear();
        std::cin.ignore(32767,'\n');*/

        /*if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(32767,'\n');
            std::cout << "Oops, that input is invalid.  Please try again.\n";
        }
        else std::cin.ignore(32767,'\n');*/
    }

    char str[cExtract::N];
};