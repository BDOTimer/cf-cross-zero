///
/// C++17
/// Исходник(DLL) в UTF-8
///----------------------------------------------------------------------------|
/// AI для игры в крестонолики. (это dll проект.)
///----------------------------------------------------------------------------:
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>

#include <iostream> /// c 150 кб до 1000 Kb DLL жиреет!

#pragma pack(push, 1)

#include "../../common/common.h"
//#include "ai_xlat.h"


struct Rand
{   Rand(            ){   srand((unsigned)time(0));}
    Rand(unsigned sid){   srand(sid);              }
    int operator    ()(int range_min, int range_max) const
    {   return rand () % (range_max - range_min) + range_min;
    }
}rrand;

///-----------|
/// AI        |
///-----------:
#include "ai.dll.h"

#define DLLEXP __declspec (dllexport)

static AI* ai = nullptr;
///--------------------------------------------------|
/// Внешний интерфейс AI.                            |
///--------------------------------------------------:
extern "C"
{
    DLLEXP void _create (const Cfg _cfg)
    {   cfg = _cfg;
       pcfg = &cfg;
       ai   = new AI();
    }

    DLLEXP Plot _step(const Plot enemy_step)
    {   return ai->step(enemy_step);
    }

    DLLEXP const wchar_t* _name(                  ){ return name        ; }
    DLLEXP void         _delete(                  ){ delete ai          ; }
    DLLEXP void         _stfish(const char FISHKA )
    {      ai->FISHKA  = FISHKA;
        if(ai->FISHKA == cfg.FISHKI[0]) ai->FISHKA_ENEMY = cfg.FISHKI[1];
        else                            ai->FISHKA_ENEMY = cfg.FISHKI[0];
        ai->field.fclear();
    }
}

//#pragma pack(pop, 1)

#undef DLLEXP


