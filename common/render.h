#ifndef RENDER_H
#define RENDER_H

#include <stdio.h>


/// "render.h"
///----------------------------------------------------------------------------|
/// Render.
///----------------------------------------------------------------------------:
namespace myl
{
    struct Wcout
    {

        Wcout& operator<<(size_t n)
        {   printf ("%d", n);
            return *this;
        }

        Wcout& operator<<(int n)
        {   printf ("%d", n);
            return *this;
        }

        Wcout& operator<<(char c)
        {   printf ("%c", c);
            return *this;
        }

        Wcout& operator<<(wchar_t c)
        {   //wprintf (c);
            return *this;
        }

        Wcout& operator<<(std::string_view s)
        {   printf (s.data());
            return *this;
        }

        Wcout& operator<<(std::wstring_view s)
        {   wprintf (s.data());
            return *this;
        }

        static void testclass();
    };

    struct Cin
    {
        void get(){ getchar(); }
    };

    const char endl = '\n';

    extern Wcout wcout;
    extern Cin   cin  ;
}


namespace  wnd
{
    extern myl::Wcout err  ;
    extern myl::Wcout warn ;
    extern myl::Wcout field;
    extern myl::Wcout mess ;
}

#endif // RENDER_H
