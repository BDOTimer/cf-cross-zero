#ifndef PLAYER_H
#define PLAYER_H
///----------------------------------------------------------------------------|
/// "player.h"
///----------------------------------------------------------------------------|
#include "aishell.h"

///----------------------------------------------------------------------------|
/// Игрок.
///----------------------------------------------------------------------------:
struct  Player
{       Player(std::wstring_view nm) : name(nm)
        {   /// Играет человек.
        }
        Player(AI* ai_) : ai(ai_)
        {   /// Играет ИИ.

            name = ai->who();
        }
       ~Player()
        {
        }

    std::wstring name;

    void win_info   ()
    {   ai->stat.add_win();
        std::wcout << L"Игрок " << name << L" ВЫИГРАЛ!\n";
    }

    Plot step(const Plot last_step)
    {   if(ai != nullptr)
        {
            auto   plot = ai->step(last_step);
            return plot;
        }

        /// TODO ...
        /// Играет человек.

        return {size_t(-1), 0};
    }

private:
    AI* ai = nullptr;

    friend struct  Game;
};

#endif // PLAYER_H
