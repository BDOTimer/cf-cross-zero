#ifndef MYLIB_H
#define MYLIB_H
///----------------------------------------------------------------------------|
/// "mylib.h"
///----------------------------------------------------------------------------|
#include <chrono>
#include <thread>
#include "debug.h"


inline void sleep(size_t ms)
{   if(mode.SILENCE) return;
    std::this_thread::sleep_for(std::chrono::milliseconds(ms) );
}

///---------------------------|
/// Системное.                |
///---------------------------:
struct  Sys
{       Sys()
        {   std::setlocale(0, "");
            std::system("mode 60,30");
        }
};


#endif // MYLIB_H
