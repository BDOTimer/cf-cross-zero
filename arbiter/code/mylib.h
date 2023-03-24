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

    std::string to_string(std::wstring_view s)
    {   std::string r;  r.reserve(s.size());
        for (const auto e : s) r.push_back(char(e)); return r;
    }
}

#endif // MYLIB_H
