#ifndef AI_DLL_H
#define AI_DLL_H

///----------------------------------------------------------------------------|
/// ИИ.
///     Всё что нужно сделать это ПРИНЯТЬ РЕШЕНИЕ,
///     в какую координату поставить фишку.
///----------------------------------------------------------------------------:


///------------------------------------|
/// ...                                |
///------------------------------------:
//const wchar_t* name = L"Глупыш";
const wchar_t* name = L"Дебил";
//const wchar_t* name = L"АфторРэнд";


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

        /// TODO ...
        ///--------------------...
        /// пример простейшего решения ...
        ///--------------------...
        while(true)
        {
            Plot p;
                 p.x = rrand(0, field.W);
                 p.y = rrand(0, field.H);

            if( field.verification_no_info(p))
            {   field[p.y][p.x] = FISHKA;
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

        if (field.verification(last_step, name))
        {   field[last_step.y][last_step.x] = FISHKA_ENEMY;
        }
        else
        {
            ///------------------------|
            /// Арбитер прислал НЕ ход.|
            ///------------------------:
            if(last_step == stp::START_STEP)
            {   //wprintf(L"%s %s", name, L"ходит первым.");
                std::wcout << name << L" ходит первым.\n" << std::endl;
            }
            else
            {   printf("ERROR in dll ...");
                std::cin.get();
            }
        }
    }
};
#endif // AI_DLL_H

