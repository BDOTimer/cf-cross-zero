#ifndef STAT_H
#define STAT_H
///----------------------------------------------------------------------------|
/// "statistics.h"
///----------------------------------------------------------------------------|

///----------------------------------------------------------------------------|
/// Статистика.
///----------------------------------------------------------------------------:
struct  Statistics
{
    int rating  = 0;
    int victory = 0; // rating += 2
    int defeat  = 0;
    int nobody  = 0; // rating += 1

    void add_win(){ victory++; rating +=2; }
    void add_def(){ defeat ++;             }
    void add_nob(){ nobody ++; rating +=1; }

    std::wstring get_str()
    {   return  std::wstring(  L"РЕЙТИНГ: " ) + std::to_wstring(rating ) +
                std::wstring(L", ПОБЕДЫ: "  ) + std::to_wstring(victory) +
                std::wstring(L", ПРОИГРЫШ: ") + std::to_wstring(defeat ) +
                std::wstring(L", НИЧЬИ: "   ) + std::to_wstring(nobody );
    }
};


#endif // STAT_H
