#ifndef ARBITER_H
#define ARBITER_H
///----------------------------------------------------------------------------|
/// "arbiter.h"
///----------------------------------------------------------------------------|
#include "dll_maneger.h"
#include "game.h"

///----------------------------------------------------------------------------|
/// Арбитер.
///----------------------------------------------------------------------------:
struct  Arbiter
{       Arbiter()
        {
            loop();
        }
       ~Arbiter()
        {
        }

private:

    DLL_manager DLL_man;

    ///------------------------------|
    /// Турнир гоу!                  |
    ///------------------------------:
    void loop()
    {
        for(size_t N = DLL_man.amount_games(), ipair = 0; ipair < N; ++ipair)
        {
            Game        game( ipair);
            set_players(game, ipair);

            game.run_first ();
            game.run_second();
        }

        std::wcout << L"ТУРНИР ЗАВЕРШЕН!\n\n";

        show_raiting();
    }

    ///------------------------------|
    /// Вставляем игрокам мозги.     |
    ///------------------------------:
    void set_players(Game& game, const size_t ipair)
    {
        const auto&[ai1, ai2] = DLL_man.get_pair(ipair);

        ai1->set_FISHKA(cfg.FISHKI[0]);
        ai2->set_FISHKA(cfg.FISHKI[1]);

        ASSERT(nullptr == game.a && nullptr == game.b);

        game.a = new Player(ai1);
        game.b = new Player(ai2);
    }

    ///------------------------------|
    /// Показать рейтинг.            |
    ///------------------------------:
    void show_raiting()
    {   std::wcout << L"ИТОГОВАЯ ТАБЛИЦА РЕЙТИНГОВ!\n";

        std::multimap<int, AI*, std::greater<>> m;

        for(const auto& e : DLL_man.get_aibots())
        {   m.insert(std::make_pair(e->stat.rating, e));
        }

        int cnt = 0;
        for(const auto&[r,  ai] : m)
        {   std::wcout << ++cnt              << ". "
                       << ai->stat.get_str() << L" -> "
                       << ai->who         () << '\n';
        }

        mode.PAUSE_PRESS_ENTER_STRONG();
    }
};



#endif // ARBITER_H
