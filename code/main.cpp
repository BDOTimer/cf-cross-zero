///----------------------------------------------------------------------------|
/// https://www.cyberforum.ru/cpp-beginners/thread3086648.html
/// Крестики-нолики(с любым размером поля!)
/// C++17
/// Исходник в UTF-8
///----------------------------------------------------------------------------|
#include <iostream>
#include <iomanip>
#include <sstream>
#include <future>
#include <string>
#include <vector>
#include <map>

#include "file.h" /// НОВОЕ ...

#pragma pack(push, 1)

const wchar_t* NAME_ARBITER = L"ARBITER";

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

}mode;


#include "mylib.h"
#include "arbiter.h"


Sys sys;


/// TODO ...
///-----------------------------------|
/// Новейший моск.                    |
///-----------------------------------:
#include "../ai_cpp_dll/code/ai_xlat.h"

inline void tests()
{
  //Field      ::testclass();
  //AI         ::testclass();
  //DLL_manager::testclass();

  //AI_xlat     ::testclass();

  //Blacklist  ::testclass();
  //Config_load::testclass<Cfg, Field>(cfg);
}

int main()
{
    tests();

    try
    {
        Arbiter run;
    }
    catch(...)
    {   std::wcout << L"EEE..." << std::endl;
    }

    mode.PAUSE_PRESS_ENTER_STRONG(L"Arbiter FINISHED.");
}

#pragma pack(pop)
