#ifndef COMMON_H
#define COMMON_H
///----------------------------------------------------------------------------|
/// "ai_cpp_dll/code/common.h"
///
/// Общий хедер для Arbiter и aiDLL.
///----------------------------------------------------------------------------|

extern bool TYPE_IS_SERVER_OR_CLIENT;

#ifndef l
    #define l(v) std::wcout << #v << " = " << (v) << '\n' ;
#endif // l

#include "configload.h"

///----------|
/// Конфиг.  |
///----------:
struct  Cfg
{
    ///-----------------------------|
    /// Количество фишек для победы.|
    ///-----------------------------:
    size_t FWIN   =   5;
    size_t WIDTH  =  30; /// Размер поля по горизонтали.
    size_t HEIGHT =  20; /// Размер поля по вертикали.
    ///-----------------------------.

    char FISHKI[2]{'X', 'O'};
};

const char EMPTY = '.';

std::wostream& operator<<(std::wostream& o, const Cfg& c)
{   o   << L"КОНФИГ ---------------------------:\n"
        << "   FWIN      = " << c.FWIN      << '\n'
        << "   WIDTH     = " << c.WIDTH     << '\n'
        << "   HEIGHT    = " << c.HEIGHT    << '\n'
        << "   FISHKI[0] = " << c.FISHKI[0] << '\n'
        << "   FISHKI[1] = " << c.FISHKI[1] << '\n'
        << std::endl;
    return o;
}

///----------|
/// Конфиг.  |
///----------:
Cfg   cfg;
Cfg* pcfg = nullptr;


struct Plot
{   size_t x, y;
    bool operator==(const Plot& p) const { return x == p.x && y == p.y; }
};


std::wostream& operator<<(std::wostream& o, const Plot& p)
{          o << "{ " << p.x << ", " << p.y << " }";
    return o;
}


namespace stp
{
    ///-------------------------------------------------|
    /// Когда нужно понять кто первый сделал ход.       |
    ///-------------------------------------------------:
    const Plot START_STEP = {size_t(-111), size_t(-111)};
    const Plot   NOT_INIT = {size_t(-1  ),         0   };
    const Plot BAD_RETURN = {size_t(-112),         0   };
}


///----------------------------------------------------------------------------|
/// Поле.
///----------------------------------------------------------------------------:
struct  Field   : std::vector<std::string>
{       Field() : m(*this)
        {
            if(TYPE_IS_SERVER_OR_CLIENT && !config_load.get_config(cfg))
            {
                {   amount_fish_2_config = config_load.get_field(cfg, *this);
                }
            }
            else
            {   m = std::vector<std::string>
                                    (cfg.HEIGHT, std::string(cfg.WIDTH, EMPTY));
            }
        }

    ConfigLoad config_load;

    size_t W = cfg.WIDTH ,
           H = cfg.HEIGHT;


    size_t amount_fish_2_config = 0;


    char who_step()
    {   return amount_fish_2_config % 2 == 0 ? cfg.FISHKI[0] : cfg.FISHKI[1];
    }


    void set_FISHKA(const Plot& p, char fishka)
    {   m[p.y][p.x] = fishka;
    }

    ///---------------------------|
    /// Проверка фишки на выигрыш.|
    ///---------------------------:
    bool is_win(const char FISHKA) const
    {   std::string fishka(cfg.FWIN, FISHKA);

        for(const auto& str : get_all_str())
        {   if(str.find(fishka) != str.npos) return true;
        }
        return false;
    }

    ///---------------------------|
    /// Есть ли ходы?             |
    ///---------------------------:
    bool is_step() const
    {   for    (size_t h = 0; h < H; ++h)
        {   for(size_t w = 0; w < W; ++w)
            {   if(m[h][w] == EMPTY) return true;
            }
        }
        return false;
    }

    void fclear()
    {
        if(!config_load.error)
        {
            m = config_load.get_data();

            if(0 != amount_fish_2_config)
            {
                /// ...
            }
        }
        else for(size_t h = 0; h < H; ++h)
        {    for(size_t w = 0; w < W; ++w)
             {   m[h][w] = EMPTY;
             }
        }
    }

    void fill_for_test()
    {   char cnt = 'A';
        for    (size_t h = 0; h < H; ++h)
        {   for(size_t w = 0; w < W; ++w)
            {   m[h][w] = cnt++;
            }
        }
    }

    void operator=(const std::vector<std::string>& _m){ m = _m; }

    void debug() const
    {   size_t cnt = 0;
        std::wcout << L" ... сначала горизонтали:\n";
        for(const auto& s : get_all_str())
        {   if(    H == cnt  ) std::wcout << L" ... теперь вертикали:\n";
            if(W + H == cnt++) std::wcout << L" ... теперь диагонали:\n";

            std::cout << s << '\n';
        }
        std::cout      << '\n';
    }

    bool verification(const Plot& p, const wchar_t* name) const
    {   bool b = p.x < W && p.y < H && m[p.y][p.x] == EMPTY;
        if (!b)
        {
            if(p == stp::START_STEP)
            {   /// std::wcout << "mss::START_STEP" << endl;
            }
            else if(p.x >= W && p.y >= H)
            {   std::wcout << L"FAIL: Ход за пределами поля! "
                           << name << std::endl;
                l(p.x)
                l(p.y)
                l(W)
                l(H)
            }
            else if(m[p.y][p.x] != EMPTY)
            {   std::wcout << L"FAIL: Ход на занятую клетку! "
                           << name << std::endl;
                l(p.x)
                l(p.y)
            }
        }
        return b;
    }

    bool verification_no_info(const Plot& p) const
    {   return p.x < W && p.y < H && m[p.y][p.x] == EMPTY;
    }


    std::vector<std::string>& m;


#define TESTMODE false
    ///---------------------------|
    /// Разворачиваем строки!     |
    ///---------------------------:
    std::vector<std::string> get_all_str() const
    {   std::vector<std::string> r;

        for    (size_t h = 0; h < H; ++h)
        {   r.push_back(std::string());
            for(size_t w = 0; w < W;  ++w)
            {   r.back().push_back(m[h][w]);
            }
        }

        for    (size_t w = 0; w < W;  ++w)
        {   r.push_back(std::string());
            for(size_t h = 0; h < H; ++h)
            {   r.back().push_back(m[h][w]);
            }
        }

        ///---------------------------|
        /// Повернуть на -45 градусов.|
        ///---------------------------:
        for    (size_t h = 0; h < H; ++h)
        {   std::string s;
            for(size_t w = 0, y = h; w < W && y < H; ++w, ++y)
            {   s.push_back(m[y][w]);
            }
            if(s.size() >= cfg.FWIN || TESTMODE)
            {   r.push_back(s);
            }
        }

        for    (size_t w = 1; w < W; ++w)
        {   std::string s;
            for(size_t x = w, h = 0; x < W && h < H; ++x, ++h)
            {   s.push_back(m[h][x]);
            }
            if(s.size() >= cfg.FWIN || TESTMODE)
            {   r.push_back(s);
            }
        }

        ///---------------------------|
        /// Повернуть на +45 градусов.|
        ///---------------------------:
        for    (size_t h = 0; h < H; ++h)
        {   std::string s;
            for(size_t w = W - 1, y = h; w < W && y < H; --w, ++y)
            {   s.push_back(m[y][w]);
            }
            if(s.size() >= cfg.FWIN || TESTMODE)
            {   r.push_back(s);
            }
        }

        for    (size_t w = W - 2; w < W; --w)
        {   std::string s;
            for(size_t x = w, h = 0; x < W && h < H; --x, ++h)
            {   s.push_back(m[h][x]);
            }
            if(s.size() >= cfg.FWIN || TESTMODE)
            {   r.push_back(s);
            }
        }

        return r;
    }
#undef TESTMODE

public:
    static void testclass();
};

std::ostream& operator<<(std::ostream& o, Field& f)
{
    std::string line(f.W+2, '-');
    o << line << '\n';
    for    (size_t h = 0; h < f.H; ++h)
    {   o << "|";
        for(size_t w = 0; w < f.W; ++w)
        {   o << f[h][w];
        }   o << "|\n";
    }       o << line << '\n';
    return  o;
}


/// Тест:
///------------------------------|
/// ABC
/// DEF
/// GHI
///------------------------------:
void Field::testclass()
{   std::wcout << L"Тест:\n";
    Field f;

    f.fill_for_test();
    f.debug        ();

    std::wcout << "TEST FINSHED!\n";
    std::cin.get();
}

#endif // COMMON_H

