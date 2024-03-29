﻿#ifndef GAME_H
#define GAME_H
///----------------------------------------------------------------------------|
/// "game.h"
///----------------------------------------------------------------------------|
#include "../../common/debug.h"
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
        field.config_load.fishki2ai(a->ai);
        field.config_load.fishki2ai(b->ai);
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
        field.config_load.fishki2ai(a->ai);
        field.config_load.fishki2ai(b->ai);
        set_names    ();
        go           ();
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
        myl::wcout << L"Игра ...\n";

        getchar();

        Plot last_step{stp::START_STEP};

        while(field.is_step())
        {
            if(go_step(last_step)) return;

            std::swap(a, b);

            ++steps;
        }

        myl::wcout << L"НИЧЬЯ\n";

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
    {   mode.PAUSE_PRESS_ENTER_STEP();

        std::system ("cls");
        myl::wcout << names;
        myl::wcout << "STEPS: "
                   << std::to_wstring(steps) << '\n';
        myl::wcout << field     << myl::endl;
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
            myl::wcout  << a->ai->who()
                        << L" сфейлил ...\n" << myl::endl;

            a->ai->stat.add_def();
            b->win_info        ();

            return true;
        }

        field.set_FISHKA(last_step, a->ai->get_FISHKA());


        if(!mode.SILENCE) show();


        if(field.is_win(a->ai->get_FISHKA()))
        {   b->ai->stat.add_def();
            a->win_info        ();
            return true;
        }

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
