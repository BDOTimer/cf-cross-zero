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
        Player(AI_wrap* ai_) : ai(ai_)
        {   /// Играет ИИ.

            name = ai->who();
        }
       ~Player()
        {
        }

    std::wstring name;

    void win_info()
    {   ai->stat.add_win();
        myl::wcout << L"Игрок " << name << L" ВЫИГРАЛ!\n";
    }

    Plot step(const Plot last_step)
    {   if(ai != nullptr)
        {
            Plot   plot = ai->v_step(last_step);
            return plot;
        }

        /// TODO ...
        /// Играет человек.

        return {size_t(-1), 0};
    }

    AI_wrap* get_ai() { return ai; }

private:
    AI_wrap* ai = nullptr;

    friend struct  Game;
};

#endif // PLAYER_H
