///
/// C++17
/// Исходник(DLL) в UTF-8
///----------------------------------------------------------------------------|
/// AI для игры в крестонолики. (это dll проект.)
///----------------------------------------------------------------------------:
#include <iostream> /// c 150 кб до 1000 Kb DLL жиреет!
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>

#define  l(v)  std::wcout << #v << L" = " << v << L"\n";
#define ll(v)  std::cout  << #v <<  " = " << v << "\n";

#pragma pack(push, 1)

///----------|
/// Конфиг.  |
///----------:
struct  Cfg
{
    ///-----------------------------|
    /// Количество фишек для победы.|
    ///-----------------------------:
    size_t FWIN   =  5;
    size_t WIDTH  = 10; /// Размер поля по горизонтали.
    size_t HEIGHT =  5; /// Размер поля по вертикали.
    ///-----------------------------.

    char FISHKI[2]{'X', 'O'};

};

Cfg* cfg;


struct Plot
{   size_t x, y;
};

std::wostream& operator<<(std::wostream& o, const Plot& p)
{   //o << "Plot:{ " << p.x << ", " << p.y << " }";
    return o;
}

///----------------------------------------------------------------------------|
/// Поле.
///----------------------------------------------------------------------------:
struct  Field
{       Field() : m(nullptr)
        {   create();
        }

    const char EMPTY = '.';

    size_t W = 0,
           H = 0;

    ///---------------------------|
    /// Проверка фишки на выигрыш.|
    ///---------------------------:
    bool is_win(const char FISHKA) const
    {
        std::string fishka(cfg->FWIN, FISHKA);

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

    bool verification(const Plot& p) const
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
    {
        std::vector<std::string> r;

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
            if(s.size() >= cfg->FWIN || TESTMODE)
            {   r.push_back(s);
            }
        }

        for    (size_t w = 1; w < W; ++w)
        {   std::string s;
            for(size_t x = w, h = 0; x < W && h < H; ++x, ++h)
            {   s.push_back(m[h][x]);
            }
            if(s.size() >= cfg->FWIN || TESTMODE)
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
            if(s.size() >= cfg->FWIN || TESTMODE)
            {   r.push_back(s);
            }
        }

        for    (size_t w = W - 2; w < W; --w)
        {   std::string s;
            for(size_t x = w, h = 0; x < W && h < H; --x, ++h)
            {   s.push_back(m[h][x]);
            }
            if(s.size() >= cfg->FWIN || TESTMODE)
            {   r.push_back(s);
            }
        }

        return r;
    }
    #undef TESTMODE
};

struct Rand
{   Rand(            ){   srand((unsigned)time(0));}
    Rand(unsigned sid){   srand(sid);              }
    int operator()(int range_min, int range_max) const
    {   return rand() % (range_max - range_min) + range_min;
    }
}rrand;

///-----------|
/// AI        |
///-----------:
#include "ai.dll.h"

#define DLLEXP __declspec (dllexport)

static AI* ai = nullptr;
///--------------------------------------------------|
/// Интерфейс AI.                                    |
///--------------------------------------------------:
extern "C"
{
    DLLEXP void         _create(Cfg* pcfg         ){       cfg = pcfg      ;
                                                            ai = new AI()  ; }
    DLLEXP Plot           _step(const Field& field){ return ai->step(field); }
    DLLEXP const wchar_t* _name(                  ){ return name           ; }
    DLLEXP void         _delete(                  ){ delete ai             ; }
    DLLEXP void         _stfish(const char FISHKA ){ ai->FISHKA = FISHKA   ; }
}

#undef DLLEXP

