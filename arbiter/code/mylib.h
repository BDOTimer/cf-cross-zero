#ifndef MYLIB_H
#define MYLIB_H
///----------------------------------------------------------------------------|
/// "mylib.h"
///----------------------------------------------------------------------------|
#include "../../common/debug.h"


namespace myl
{
    template<typename T>
    std::wstring to_wstring(T n)
    {   std::string t = std::to_string( n);
        return std::wstring(t.begin(), t.end());
    }
}

#endif // MYLIB_H
