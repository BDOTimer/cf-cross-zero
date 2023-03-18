#ifndef MODE_H
#define MODE_H
///----------------------------------------------------------------------------|
/// "mode.h"
///----------------------------------------------------------------------------|
#include <chrono>
#include <thread>
#include "mylib.h"

const bool ONN = true ;
const bool OFF = false;

///----------------------------------------------------------------------------|
/// Режимы лога.
///----------------------------------------------------------------------------:
struct Mode
{
    int  TIME_PAUSE_STEPS = 500; /// Автопауза между шагами.
    bool SILENCE          = OFF; /// true -> Без лога процесса игры.
    bool KEYTRACER        = OFF; /// true -> Остановка на каждом ходу.

    void PAUSE_PRESS_ENTER_INFO()
    {   if(SILENCE) return;
        myl::wcout  << L"\nPAUSE_PRESS_ENTER\n" << myl::endl;
        myl::cin.get();
    }

    void PAUSE_PRESS_ENTER_ERROR()
    {   myl::wcout  << '\a';
        myl::cin.get();
    }

    void PAUSE_PRESS_ENTER_STEP()
    {   if(!KEYTRACER) return;
        myl::wcout  << L"\nPAUSE_PRESS_ENTER_STEP\n" << myl::endl;
        myl::cin.get();
    }

    void PAUSE_PRESS_ENTER_STRONG(std::wstring mess = L"")
    {   myl::wcout  << mess << "\a\n"           << myl::endl;
        myl::wcout  << L"\nPAUSE_PRESS_ENTER\n" << myl::endl;
        myl::cin.get();
    }
};

extern Mode mode;

inline void sleep(size_t ms)
{   if(mode.SILENCE) return;
    std::this_thread::sleep_for(std::chrono::milliseconds(ms) );
}

#endif // MODE_H
