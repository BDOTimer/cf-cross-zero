#ifndef COMMON_H
#define COMMON_H
///----------------------------------------------------------------------------|
/// "code/common.h"
///
/// Общий хедер для Arbiter и aiDLL.
///----------------------------------------------------------------------------|
/// 
#define l(v)      std::wcout << #v << " = " << (v) << '\n' ;
#define ls(v)     std::cout  << #v << " = " << (v) << '\n' ;
#define ll        std::cin.get();
#define sssx       std::cout << "SIGNAL\n";ll


///----------|
/// Конфиг.  |
///----------:
struct  Cfg
{
    ///-----------------------------|
    /// Количество фишек для победы.|
    ///-----------------------------:
    size_t FWIN   = 5;
    size_t WIDTH  = 10; /// Размер поля по горизонтали.
    size_t HEIGHT = 5; /// Размер поля по вертикали.
    ///-----------------------------.

    char FISHKI[2]{ 'X', 'O' };

};
const Cfg cfg_default;

///----------|
/// Конфиг.  |
///----------:
extern Cfg   cfg;
extern Cfg* pcfg;

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


struct Plot
{   size_t x, y;
    bool operator==(const Plot& p) const { return x == p.x && y == p.y; }
};


std::wostream& operator<<(std::wostream& o, const Plot& p)
{   o << "{ " << p.x << ", " << p.y << " }";
    return o;
}


namespace mss
{
    ///-------------------------------------------------|
    /// Когда нужно понять кто первый сделал ход.       |
    ///-------------------------------------------------:
    const Plot START_STEP = {size_t(-111), size_t(-111)};
}


///----------------------------------------------------------------------------|
/// Поле.
///----------------------------------------------------------------------------:
struct  Field
{       Field(const Cfg& cfg_) : W(cfg_.WIDTH), H(cfg_.HEIGHT), m(nullptr)
        {
            create();
            fclear();
        }

    const char EMPTY = '.';

    size_t W, H;

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

    char* operator[](const size_t i)
    {   return  m[i];
    }

    void fclear()
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
        }   std::cout      << '\n';
    }

    bool verification(const Plot& p, const wchar_t* name) const
    {   

        bool b = p.x < W && p.y < H && m[p.y][p.x] == EMPTY;
        if (!b)
        {
            if(p == mss::START_STEP)
            {   std::wcout << L"Verification: mss::START_STEP" << std::endl;
            }
            else if(p.x >= W && p.y >= H)
            {   std::wcout << L"FAIL verification: Ход за пределами поля! "
                           << name << std::endl;
                l(p.x)
                l(p.y)
                l(W)
                l(H)
            }
            else if(m[p.y][p.x] != EMPTY)
            {   std::wcout << L"FAIL verification: Ход на занятую клетку! "
                           << name << std::endl;
                l(p)
                l((int)m[p.y][p.x])
                l((int)EMPTY)
            }
            else std::wcout << L"FAIL verification ..." << std::endl;
        }
        return b;
    }

    bool verification_no_info(const Plot& p) const
    {   return p.x < W && p.y < H && m[p.y][p.x] == EMPTY;
    }


private:
    char** m;

    void create()
    {   if(nullptr !=  m)  return;

        m = new char* [H];
        for (size_t i = 0; i < H; i++)
        {   m[i] = new char[W];
        }
    }

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
    }       o << line << std::endl;
    return  o;
}


/// Тест:
///------------------------------|
/// ABC
/// DEF
/// GHI
///------------------------------:
void Field::testclass()
{   
    std::wcout << L"Тест:\n";
    Field f(cfg);

    f.fill_for_test();
    f.debug        ();

    std::wcout << "TEST FINSHED!\n";
    std::cin.get();
}

#endif // COMMON_H

