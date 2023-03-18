#include <locale>
#include <string>
#include <vector>
#include "render.h"


namespace myl
{   myl::Wcout wcout;
    myl::Cin   cin  ;
}


namespace wnd
{
    myl::Wcout err   ;
    myl::Wcout warn  ;
    myl::Wcout field ;
    myl::Wcout mess  ;
    myl::Wcout banner;
}

///----------------------------------------------------------------------------|
/// Тест.
///----------------------------------------------------------------------------:
struct Plot{ size_t x, y; };


myl::Wcout& operator<<(myl::Wcout& o, const Plot& plot)
{   o << "Plot:" << '{' << plot.x << ", " << plot.y << '}';
    return o;
}

using field_t = std::vector<std::string>;

struct PlotC{ Plot p; char c; };

field_t& operator<<(field_t& f, const PlotC& plotc)
{   f[plotc.p.y][plotc.p.x] = plotc.c;
    return f;
}


myl::Wcout& operator<<(myl::Wcout& o, const field_t& f)
{   for    (const auto& r : f)
    {   for(const auto& e : r)
        {
            o <<   e;
        }   o << '\n';
    }       o << '\n';
    return  o;
}

///------------------------------|
/// Тест.                        |
///------------------------------:
void myl::Wcout::testclass()
{
    std::setlocale(0, "");

    int  n = -333;
    char c =  'Z';

    Plot p = {123, 321};

    std:: string  str =  "std:: string";
    std::wstring wstr = L"std::wstring";

    myl::wcout  <<  "Hello, world!\n"
                << 2023       << "\n"
                << n          << "\n"
                << c          << "\n"
                << L"Привет,  Мир!\n";
    wnd::err    << p          << '\n'
                << str        << '\n'
                << wstr       << '\n';

    auto m = std::vector(10, std::string(7, '.'));

    m << PlotC{{2,2}, 'S'};

    Plot pp{3, 3};

    m << PlotC{pp, 'F'};

    myl::wcout << m;

    getchar();
}



