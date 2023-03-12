#ifndef COMMON_H
#define COMMON_H
///----------------------------------------------------------------------------|
/// "ai_cpp_dll/code/common.h"
///
/// Общий хедер для Arbiter и aiDLL.
///----------------------------------------------------------------------------|

#ifndef l
    #define l(v) std::wcout << #v << " = " << (v) << '\n' ;
#endif // l


///----------|
/// Конфиг.  |
///----------:
struct  Cfg
{
    ///-----------------------------|
    /// Количество фишек для победы.|
    ///-----------------------------:
    size_t FWIN   =  3;
    size_t WIDTH  =  30; /// Размер поля по горизонтали.
    size_t HEIGHT =  20; /// Размер поля по вертикали.
    ///-----------------------------.

    char FISHKI[2]{'X', 'O'};
};

const char EMPTY = '.';

std::wostream& operator<<(std::wostream& o, const Cfg& c)
{   std::wcout << L"КОНФИГ --------------:\n";
    l(c.FWIN)
    l(c.WIDTH)
    l(c.HEIGHT)
    l(c.FISHKI[0])
    l(c.FISHKI[1])
    std::wcout << std::endl;
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
{   o << "{ " << p.x << ", " << p.y << " }";
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
{       Field() : std::vector<std::string>
                   (cfg.HEIGHT, std::string(cfg.WIDTH, EMPTY)), m(*this)
        {
        }

    size_t W = cfg.WIDTH ,
           H = cfg.HEIGHT;

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


    void clear()
    {   for    (size_t h = 0; h < H; ++h)
        {   for(size_t w = 0; w < W; ++w)
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

