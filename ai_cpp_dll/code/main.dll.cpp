﻿
const char* INTERFACE_VERSION = "interface_version:xlat";

///----------------------------------------------------------------------------|
/// C++17
/// Исходник(DLL) в UTF-8
///----------------------------------------------------------------------------|
/// AI для игры в крестонолики. (это dll проект.)
///----------------------------------------------------------------------------:
#include <cstdlib>
#include <vector>
#include <string>
#include <ctime>

///------------------------------------|
/// ...                                |
///------------------------------------:
//const wchar_t* authorname = L"Глупыш";
//const wchar_t* authorname = L"Дебил";
const wchar_t* authorname = L"АфторРэнд";

//#include <iostream> /// c 150 кб до 1000 Kb DLL жиреет!

//#pragma pack(push, 1)


bool TYPE_IS_SERVER_OR_CLIENT = false;


///-----------|
/// AI        |
///-----------:
#include "ai.dll.h"
//#include "ai_xlat.h"


#define DLLEXP __declspec (dllexport)


static AI* ai = nullptr;
///----------------------------------------------------------------------------|
/// Внешний интерфейс AI.
///----------------------------------------------------------------------------:
extern "C"
{
    DLLEXP void _create(const Cfg _cfg)
    {   cfg = _cfg;
        ai  = new AI();
    }

    DLLEXP Plot _step(const Plot enemy_step)
    {   return ai->step(enemy_step);
    }

    DLLEXP const wchar_t* _name(                  ){ return authorname  ; }
    DLLEXP void         _delete(                  ){ delete ai          ; }
    DLLEXP void         _stfish(const char FISHKA )
    {      ai->FISHKA  = FISHKA;
        if(ai->FISHKA == cfg.FISHKI[0]) ai->FISHKA_ENEMY = cfg.FISHKI[1];
        else                            ai->FISHKA_ENEMY = cfg.FISHKI[0];
        ai->field.fclear();
    }

    DLLEXP void _sendplot(Plot plot, char color)
    {   ai->field[plot.y][plot.x] = color;

        if(DEBUG_DLL_RUNTIME)
        {   myl::wcout << L"sendplot_:\n";
            l(plot)
            l(color)
        }
    }

    DLLEXP const char* _get_interface_version()
    {   return INTERFACE_VERSION;
    }
}

///----------------------------------------------------------------------------|
/// ENTER POINT TO DLL.
///----------------------------------------------------------------------------:
//#define UNICODE
#include <windows.h>

void DLLEXP SomeFunction(const std::wstring& text)
{   MessageBox(0, text.c_str(), L"DLL Message", MB_OK | MB_ICONINFORMATION);
}

extern "C" DLLEXP BOOL APIENTRY
DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    std::wstring auth(authorname);

    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        // attach to process
        // return FALSE to fail DLL load
        // SomeFunction(auth + L" DLL_PROCESS_ATTACH");
        ///-------|
        /// ...   |
        ///-------:
        /// ...

        break;

    case DLL_PROCESS_DETACH:
        // detach from process
        // SomeFunction(auth + L" DLL_PROCESS_DETACH");
        break;

    case DLL_THREAD_ATTACH:
        // attach to thread
        // SomeFunction(auth + L" DLL_THREAD_ATTACH");;
        break;

    case DLL_THREAD_DETACH:
        // detach from thread
        // SomeFunction(auth + L" + DLL_THREAD_DETACH");
        break;
    }
    return TRUE; // succesful
}

//#pragma pack(pop, 1)

#undef DLLEXP




