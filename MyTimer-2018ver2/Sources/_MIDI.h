#include <mmsystem.h>
#pragma comment(lib, "WinMM.Lib")

#define ONCE {static bool once = false;if(once)return 99;once = true;}

///ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
/// Играем MIDI.                                                               |
///ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
class cMIDI
{
public:
    cMIDI() : bIsPlaing(false)
    {   
    }

    DWORD open(HWND _hWnd, LPCSTR lpszMIDIFileName)//-------------------------->
    {   ONCE
        
        hWndNotify = _hWnd;
        mciOpenParms.lpstrDeviceType  = "sequencer";
        mciOpenParms.lpstrElementName = lpszMIDIFileName;

        // Open the device by specifying the device and filename.
        // MCI will attempt to choose the MIDI mapper as the output port.
        if (error_status = mciSendCommand(NULL, MCI_OPEN,
            MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)(LPVOID)&mciOpenParms))
        {   // Failed to open device.
            goto m0;
        }

        wDeviceID = mciOpenParms.wDeviceID;

        // Check if the output port is the MIDI mapper.
        mciStatusParms.dwItem = MCI_SEQ_STATUS_PORT;
        if (error_status = mciSendCommand(wDeviceID, MCI_STATUS,
            MCI_STATUS_ITEM, (DWORD)(LPVOID)&mciStatusParms))
        {
m0:         mciSendCommand(wDeviceID, MCI_CLOSE, 0, NULL);
            return (error_status);
        }
        return error_status;
    }

    void play()//-------------------------------------------------------------->
    {   if(error_status)
        {   startsignal(); // std::cout << rus("\a\a\a\a\a\a");
            return;
        }
        
        // Begin playback. The window procedure function for the parent 
        // window will be notified with an MM_MCINOTIFY message when 
        // playback is complete. At this time, the window procedure closes 
        // the device.
        mciPlayParms.dwCallback = (DWORD)hWndNotify;
        // Позиционирование в начало:
        mciSendCommand(wDeviceID, MCI_SEEK, MCI_WAIT | MCI_SEEK_TO_START, NULL);
        if (error_status = mciSendCommand(wDeviceID, MCI_PLAY, MCI_NOTIFY,
            (DWORD)(LPVOID)&mciPlayParms))
        {   mciSendCommand(wDeviceID, MCI_CLOSE, 0, NULL);
            return;
        }
        bIsPlaing = true;
    }

    void stop()//-------------------------------------------------------------->
    {   if(error_status||!bIsPlaing) return;
        mciSendCommand(wDeviceID, MCI_STOP, MCI_NOTIFY, (DWORD)&mciPlayParms);
        bIsPlaing = false;
    }

private:
    bool bIsPlaing;

    HWND              hWndNotify;
    UINT              wDeviceID;
    DWORD             error_status;
    MCI_OPEN_PARMS    mciOpenParms;
    MCI_PLAY_PARMS    mciPlayParms;
    MCI_STATUS_PARMS  mciStatusParms;
    MCI_SEQ_SET_PARMS mciSeqSetParms;

    void startsignal() 
    {   // Если ты музыкант, то правь этот файл))---------------------------------->
        /*
        Beep(1480,200);
        Beep(1568,200);
        Beep(1568,200);
        Beep(1568,200);
        Beep(739,200);
        Beep(783,200);
        Beep(783,200);
        Beep(783,200);
        Beep(369,200);
        Beep(392,200);
        Beep(369,200);
        Beep(392,200);
        Beep(392,400);
        Beep(196,400);*/

        // Еще один простой вариант:----------------------------------------------->
        std::cout << rus("\a\a\a\a\a\a");
    }
};