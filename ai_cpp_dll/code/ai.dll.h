#ifndef AI_DLL_H
#define AI_DLL_H

#include "../../common/render.h"
#include "../../common/common.h"

///----------------------------------------------------------------------------|
/// ИИ.
///     Всё что нужно сделать это ПРИНЯТЬ РЕШЕНИЕ,
///     в какую координату поставить фишку.
///----------------------------------------------------------------------------:

const bool DEBUG_DLL_RUNTIME = false;

///------------------------------------|
/// ...                                |
///------------------------------------:
const wchar_t* authorname = L"Глупыш";
//const wchar_t* authorname = L"Дебил";
//const wchar_t* authorname = L"АфторРэнд";


struct Rand
{   Rand(            ){   srand((unsigned)time(0));}
    Rand(unsigned sid){   srand(sid);              }
    int  operator   ()(int range_min, int range_max)   const
    {   ASSERT(range_min < range_max)
        return rand () %  (range_max -    range_min) + range_min;
    }
}rrand;


struct  AI
{       AI()
        {
        }

    ///---------------------|
    /// Конфиг игры.        |
    ///---------------------:
    /// Cfg* pcfg; /// Глобально.

    ///---------------------|
    /// Ваша фишка.         |
    ///---------------------:
    char FISHKA       = 0; /// Устанавливается Арбитром
    char FISHKA_ENEMY = 0; /// непосредственно перед матчем.

    ///---------------------|
    /// Послединй ход врага.|
    ///---------------------:
    Plot last_step{stp::NOT_INIT};

    ///---------------------|
    /// Это ваше поле.      |
    ///---------------------:
    Field field;

    ///-------------------------------|
    /// Это основной метод.           |
    /// его будет дёргать Арбитер,    |
    /// чтоб узнать ваше решение.     |
    ///-------------------------------:
    Plot step(const Plot& enemy_step)
    {
        set_step(enemy_step);

        Plot p;

        /// TODO ...
        ///--------------------...
        /// пример простейшего решения ...
        ///--------------------...
        while(true)
        {
            p.x = rrand(0, field.W);
            p.y = rrand(0, field.H);

            if( field.verification_no_info(p))
            {   field[p.y][p.x] = FISHKA;

                if(DEBUG_DLL_RUNTIME)
                {   myl::wcout << authorname << L" сделал ход: " << p << ":\n";
                    myl::wcout  << field      << myl::endl;
                    myl::cin.get();
                }

                return p;
            }
        }

        return {size_t(-1), 0};
    }

    ///--------------------...
    /// пример обхода поля ...
    ///--------------------...
    /*
    void debug(const Field& field) const
    {
        for    (size_t h = 0; h < field.H; ++ h)
        {   for(size_t w = 0; w < field.W; ++ w)
            {
                std::cout << field[h][w];
            }   std::cout << '\n';
        }       std::cout << '\n';
    }
    */

private:
    void set_step(const Plot& enemy_step)
    {   last_step = enemy_step;

        if (field.verification(last_step, authorname))
        {   field[last_step.y][last_step.x] = FISHKA_ENEMY;

            if(DEBUG_DLL_RUNTIME)
            {   myl::wcout  << authorname  << L" состояние доски до хода:\n";
                myl::wcout   << field       << myl::endl;
            }
        }
        else
        {
            ///------------------------|
            /// Арбитер прислал НЕ ход.|
            ///------------------------:
            if(last_step == stp::START_STEP)
            {   //wprintf(L"%s %s", authorname, L"ходит первым.");

                if(DEBUG_DLL_RUNTIME)
                {   myl::wcout  << authorname  << L" ходит первым.\n";
                    myl::wcout  << L"Состояние доски:\n";
                    myl::wcout   << field      << myl::endl;
                }
            }
            else
            {   printf("ERROR in dll ...");
                myl::cin.get();
            }
        }
    }
};
#endif // AI_DLL_H

