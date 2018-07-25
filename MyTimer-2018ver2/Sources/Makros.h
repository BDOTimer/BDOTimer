#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>

#ifndef MAKROS_H//ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo|
#define MAKROS_H

#include "Connector.h"
#include "../resource.h"

using std::cout;

#define MYDEBUG

//--������� ��� ������ � ������:-----------------------------------------------v
#define BIT_1(  val, bit)   val |= (1<<bit)        // ��������� 1.
#define BIT_0(  val, bit)   val &= (~(1<<bit))     // ��������� 0.
#define BIT_Inv(val, bit)   val ^= (1<<bit)        // �������� ����.
#define BIT_IS1(val, bit) ((val  & (1<<bit)) != 0) // ���� 1.
#define BIT_IS0(val, bit) ((val  & (1<<bit)) == 0) // ���� 0.

///ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
/// ��������� ������� ���������.                                               |
///ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
static char  bufRus[256];
inline char* rus(const char* _text)
{   CharToOem(_text, bufRus);
    return bufRus;
}

#define    SIG cout << "SIGNAL!\n";
#define    PRN(_m_) std::cout << rus(_m_) << "\n"
#define PRNERR(_m_) std::cout << "Error: "<< _m_ << " fail!" << "\n"

///ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
/// ���� ������.                                                               |
///ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
enum ConsoleColor
{   Black         = 0,
    Blue          = 1,
    Green         = 2,
    Cyan          = 3,
    Red           = 4,
    Magenta       = 5,
    Brown         = 6,
    LightGray     = 7,
    DarkGray      = 8,
    LightBlue     = 9,
    LightGreen    = 10,
    LightCyan     = 11,
    LightRed      = 12,
    LightMagenta  = 13,
    Yellow        = 14,
    White         = 15
};
void mySetColor(UINT text = 7, UINT background = 0) // #include <Windows.h>
{   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                              (WORD)((background << 4) | text));
}
#define COLOR(N,C) "";mySetColor(C);cout<<N;mySetColor();cout

//--��������� ��������:-------------------------------------------------------->
#pragma warning(disable : 4996     )

///ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
/// ������ �� ���������� �������.                                              |
///ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
inline bool chek_mutex()
{
    HANDLE _Present = CreateMutex(NULL,false,"My_Program_Already_Present");
    if(GetLastError() == ERROR_ALREADY_EXISTS)
    {   cout << rus("������� ������� ��������� �������!\n");
        cout << rus("������ ��� �������!\n\n");
        cout << rus("[ALT+1] - ��������/�������� ������...\n");
        Sleep(2000);
        CloseHandle(_Present);
        return true;
    }
    return false;
}

///ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
/// ��������� ������� ������.                                                  |
///ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
void myicon()
{   HMODULE hmod = LoadLibrary("Kernel32.dll");
    DWORD (*SetConsoleIcon)(HICON) = (DWORD (*)(HICON))
                                       (GetProcAddress(hmod, "SetConsoleIcon"));
    SetConsoleIcon(LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1)));
    FreeLibrary(hmod); 
}

#endif//ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo|