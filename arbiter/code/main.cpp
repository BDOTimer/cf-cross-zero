///----------------------------------------------------------------------------|
/// https://www.cyberforum.ru/cpp-beginners/thread3086648.html
/// Крестики-нолики(с любым размером поля!)
/// C++17
/// Исходник в UTF-8
///----------------------------------------------------------------------------|
//#include <iostream>
#include <iomanip>
#include <sstream>
#include <future>
#include <string>
#include <vector>
#include <map>

#include "file.h" /// НОВОЕ ...

//#pragma pack(push, 1)


const wchar_t* NAME_ARBITER             = L"ARBITER";
bool           TYPE_IS_SERVER_OR_CLIENT = true      ;

#include "mylib.h"
#include "mode.h"
#include "arbiter.h"

///---------------------------|
/// Системное.                |
///---------------------------:
struct  Sys
{       Sys()
        {   std::setlocale(0, "");
            //std::system("mode 60,30");
        }
}sys;

Mode mode;

/// TODO ...
///-----------------------------------|
/// Новейший моск.                    |
///-----------------------------------:
#include "../../ai_cpp_dll/code/ai_xlat.h"

inline void tests()
{
  //Field      ::testclass();
  //AI         ::testclass();
  //DLL_manager::testclass();

  //AI_xlat     ::testclass();

  //Blacklist  ::testclass();
  //ConfigLoad::testclass<Cfg, Field>(cfg);

  //AI_SmallEvil::testclass();

  //myl::Wcout::testclass();
}

int main()
{
    tests();

    try
    {
        Arbiter run;
    }
    catch(...)
    {   myl::wcout << L"EEE..." << myl::endl;
    }

    mode.PAUSE_PRESS_ENTER_STRONG(L"Arbiter FINISHED.");
}

//#pragma pack(pop)
