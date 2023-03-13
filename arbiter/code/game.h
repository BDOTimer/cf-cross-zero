#ifndef GAME_H
#define GAME_H
///----------------------------------------------------------------------------|
/// "game.h"
///----------------------------------------------------------------------------|
#include "mode.h"
#include "player.h"

///----------------------------------------------------------------------------|
/// Вся ИГРА.
///----------------------------------------------------------------------------:
struct  Game
{       Game(Field& f, int Cnt) : field(f), cntg(Cnt * 2 + 1)
        {
        }
       ~Game()
        {   if(nullptr != a) delete a;
            if(nullptr != b) delete b;
        }

    Player* a = nullptr;
    Player* b = nullptr;

    ///------------------------------|
    /// Первая игра.                 |
    ///------------------------------:
    void run_first  ()
    {   steps      = 1;
        field.fclear();
        set_names   ();
        go          ();
        mode.PAUSE_PRESS_ENTER_INFO();
    }

    ///------------------------------|
    /// Вторая игра.                 |
    ///------------------------------:
    void run_second  ()
    {   cntg++         ;
        steps       = 1;
        field.fclear ();
        change_fishki();
        set_names    ();
        go();
        mode.PAUSE_PRESS_ENTER_INFO();
    }

private:
    Field& field;
    int     cntg;
    int    steps;

    ///------------------------------|
    /// Процесс игры.                |
    ///------------------------------:
    void go()
    {
        std::wcout << L"Игра ...\n";

        Plot last_step{stp::START_STEP};

        while(field.is_step())
        {
            if(go_step(last_step)) return;

            std::swap(a, b);

            ++steps;
        }

        std::wcout << L"НИЧЬЯ\n";

        a->ai->stat.add_nob();
        b->ai->stat.add_nob();
    }

    void change_fishki()
    {
        ///------------------------------|
        /// Первый ходит всегда игрок A  |
        /// у него должна быть фишка  X  |
        ///------------------------------:

        if(a->ai->get_FISHKA() == cfg.FISHKI[0])
        {
            a->ai->set_FISHKA (cfg.FISHKI[1]);
            b->ai->set_FISHKA (cfg.FISHKI[0]);

            std::swap(a, b);
        }
        else
        {
            a->ai->set_FISHKA (cfg.FISHKI[0]);
            b->ai->set_FISHKA (cfg.FISHKI[1]);
        }
    }

    ///------------------------------|
    /// Показать текущее Поле.       |
    ///------------------------------:
    void show()
    {   std::system ("cls");
        std::wcout << names;
        std::wcout << "STEPS: " << std::setw(5) << myl::to_wstring(steps) << '\n';
        std::cout  << field << std::endl;
        sleep(mode.TIME_PAUSE_STEPS);
    }

    ///------------------------------|
    /// Вызов мозга.                 |
    ///------------------------------:
    bool go_step(Plot& last_step)
    {
        last_step = a->step(last_step);
        bool good = field.verification(last_step, a->ai->who().c_str());
        if (!good)
        {   /// TODO ...
            std::wcout  << a->ai->who()
                        << L" сфейлил ...\n" << std::endl;

            a->ai->stat.add_def();
            b->win_info        ();

            mode.PAUSE_PRESS_ENTER_STRONG(L".");
            return true;
        }

        field.set_FISHKA(last_step, a->ai->get_FISHKA());


        if(!mode.SILENCE) show();


        if(field.is_win(a->ai->get_FISHKA()))
        {   b->ai->stat.add_def();
            a->win_info        ();
            return true;
        }

        mode.PAUSE_PRESS_ENTER_STEP();
        return false;

    }

    ///------------------------------|
    /// Кешируем баннер.             |
    ///------------------------------:
    std::wstring names;
    void     set_names()
    {
        std::wstring A(1, a->ai->get_FISHKA());
        std::wstring B(1, b->ai->get_FISHKA());

        names  = L"Игра:";
        names += myl::to_wstring(cntg) + L'\n';
        names += a->ai->who()                 ;
        names += L"\"" + A + L"\"" + L" <=> " ;
        names += b->ai->who()                 ;
        names += L"\"" + B + L"\"" + L'\n'    ;
    }
};

#endif // GAME_H
