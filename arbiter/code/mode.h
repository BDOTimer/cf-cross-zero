#ifndef MODE_H
#define MODE_H
///----------------------------------------------------------------------------|
/// "mode.h"
///----------------------------------------------------------------------------|
#include <chrono>
#include <thread>
#include "mylib.h"


///----------------------------------------------------------------------------|
/// Режимы лога.
///----------------------------------------------------------------------------:
struct Mode
{
    int  TIME_PAUSE_STEPS = 500;   /// Автопауза между шагами.
    bool SILENCE          = false; /// true -> Без лога процесса игры.
    bool KEYTRACER        = false; /// true -> Остановка на каждом ходу.

    void PAUSE_PRESS_ENTER_INFO()
    {   if(SILENCE) return;
        std::cin.get();
    }

    void PAUSE_PRESS_ENTER_ERROR()
    {   std::wcout << '\a';
        std::cin.get();
    }

    void PAUSE_PRESS_ENTER_STEP()
    {   if(!KEYTRACER) return;
        std::cin.get();
    }

    void PAUSE_PRESS_ENTER_STRONG(std::wstring mess = L"")
    {   std::wcout << mess << "\a\n" << std::endl;
        std::cin.get();
    }
};

inline Mode mode;

inline void sleep(size_t ms)
{   if(mode.SILENCE) return;
    std::this_thread::sleep_for(std::chrono::milliseconds(ms) );
}

#endif // MODE_H
