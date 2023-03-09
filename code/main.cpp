/// https://www.cyberforum.ru/cpp-beginners/thread3086648.html
/// Крестики-нолики(с любым размером поля!)
/// C++17
/// Исходник в UTF-8
#include <iostream>
#include <string>
#include <vector>
#include <map>

#pragma pack(push, 1)

#define  l(v)  std::wcout << #v << L" : " << v << std::endl;

#include <chrono>
#include <thread>
inline void sleep(size_t ms)
{   std::this_thread::sleep_for(std::chrono::milliseconds(ms) );
}

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

Cfg cfg;


///---------------------------|
/// Системное.                |
///---------------------------:
struct  Sys
{       Sys()
        {   setlocale(0, "");
        }
}sys;


struct Plot
{   size_t x, y;
};

std::wostream& operator<<(std::wostream& o, const Plot p)
{   o << "{ " << p.x << ", " << p.y << " }";
    return o;
}


///----------------------------------------------------------------------------|
/// Поле.
///----------------------------------------------------------------------------:
struct  Field
{   Field() : m(nullptr)
    {   create();
        clear ();
    }

    const char EMPTY = '.';

    size_t W = cfg.WIDTH ,
           H = cfg.HEIGHT;

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

    bool verification(const Plot& p)
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


///----------------------------------------------------------------------------|
/// Статистика.
///----------------------------------------------------------------------------:
struct  Statistics
{
    int rating  = 0;
    int victory = 0; // rating += 2
    int defeat  = 0;
    int nobody  = 0; // rating += 1

    void add_win(){ victory++; rating +=2; }
    void add_def(){ defeat ++;             }
    void add_nob(){ nobody ++; rating +=1; }

    std::wstring get_str()
    {   return  std::wstring(  L"РЕЙТИНГ: " ) + std::to_wstring(rating ) +
                std::wstring(L", ПОБЕДЫ: "  ) + std::to_wstring(victory) +
                std::wstring(L", ПРОИГРЫШ: ") + std::to_wstring(defeat ) +
                std::wstring(L", НИЧЬИ: "   ) + std::to_wstring(nobody );
    }
};


///----------------------------------------------------------------------------|
/// ИИ.
///----------------------------------------------------------------------------:
#include <windows.h>
#include <thread>
#include <future>

typedef const wchar_t*(__stdcall * _name_t  )(                        );
typedef Plot          (__stdcall * _step_t  )(const Field&       field);
typedef void          (__stdcall * _create_t)(const Cfg* p            );
typedef void          (__stdcall * _delete_t)(                        );
typedef void          (__stdcall * _stfish_t)(char FISHKA             );


struct  AI
{       AI (const char* dllnm) : dllname(dllnm)
        {   try
            {   load_dll(dllnm);

                /*
                 *  std::wcout << L"DLL load GOOD!\n";
                 *  std::wcout << L"_name() returned: "
                 *             << _name() << std::endl;
                 */

                _create(&cfg);
            }
            catch(int err)
            {   error = true;
            }

            dllnamew = std::wstring(dllname.begin(), dllname.end());
        }
       ~AI()
        {   /// TODO: выгрузить DLL.
        }

    Plot stepxxx(const Field& field) const
    {   if(!error)
        {
            ///---------------------------|
            /// Оъявляем.                 |
            ///---------------------------:
            Plot plot{size_t(-1), 0};

            std::chrono::microseconds timeout{3000000};
            using result_type = std::pair<Plot, std::chrono::microseconds>;
{
            std::future<result_type> res = std::async(std::launch::async
            , [](const Field& f, const AI& ai)
            {
                using namespace std::chrono;

                auto beg = high_resolution_clock::now();
                Plot plt = ai._step(f); ///<---------------------------------|
                auto end = high_resolution_clock::now();

                return std::make_pair(plt, duration_cast<microseconds>(end - beg));
            }
            , field, *this
            );

            std::future_status status;

            ///---------------------------|
            /// Крутим.                   |
            ///---------------------------:
            do
            {
                status = res.wait_for(timeout);
                if(status == std::future_status::timeout)
                {
                    std::cout << "Time Limit Exceeded\n";

                    //break;
                }
                else if(status == std::future_status::ready)
                {
                    result_type v = res.get();
                    std::wcout << "Execution time "
                               << (v.second.count() / 1000000.)
                               << " sec, with code " << v.first << '\n';

                    plot = v.first;
                }
            }
            while(status == std::future_status::deferred);
}
            std::cout  << "1=============\n" << std::endl;
            std::wcout << plot;
            std::cin.get();

            return plot;
        }

        return {size_t(-1), 0};
    }


    Plot step(const Field& field) const
    {   if(!error)
        {   return _step(field);
        }

        return {size_t(-1), 0};
    }

    std::string   dllname;
    char           FISHKA;
    std::wstring dllnamew;
    Statistics       stat;

    _name_t       _name  ;
    _step_t       _step  ;
    _create_t     _create;
    _delete_t     _delete;
    _stfish_t     _stfish;

    HINSTANCE hGetProcIDDLL = nullptr;

    bool error = false;

    std::wstring get_name()
    {   std::wstring s(_name())   ;
                     s += L"[ "   ;
                     s += dllnamew;
                     s += L"]";
        return       s;
    }

    #define GET_PROC_ADDRESS(V) get_proc_address(V, #V)

    void load_dll(const char*        dllname)
    {   hGetProcIDDLL = LoadLibrary( dllname);

        if (!hGetProcIDDLL)
        {   std::cout << "ERROR: Could not DLL ..." << std::endl;
            throw EXIT_FAILURE;
        }

        GET_PROC_ADDRESS(_name  );
        GET_PROC_ADDRESS(_step  );
        GET_PROC_ADDRESS(_create);
        GET_PROC_ADDRESS(_delete);
        GET_PROC_ADDRESS(_stfish);
    }

    #undef GET_PROC_ADDRESS

    template<typename F>
    void get_proc_address(F& foo, const char* fooname)
    {
        foo = (F)GetProcAddress(hGetProcIDDLL, fooname);
        if (!foo)
        {   std::cout << "ERROR: dll load " << fooname << std::endl;
            throw EXIT_FAILURE;
        }
    }

public:
    static void testclass();
};
/// Тест:
///------------------------------|
/// ...
///------------------------------:
void AI::testclass()
{   std::wcout << L"TEST AI:\n";

    Field f;
    AI   ai("0.dll");

        std::wcout << ai._step(f) << '\n';
        std::wcout << ai._step(f) << '\n';
        std::wcout << ai._step(f) << '\n';
        std::wcout << ai._step(f) << '\n';

    std::wcout << "\nTEST FINISHED!\n" << std::endl;;
    std::cin.get();
}


#include <filesystem>
///----------------------------------------------------------------------------|
/// Получаем имена всех dll.
///----------------------------------------------------------------------------:
struct  FindDLL
{       FindDLL()
        {
            find();
            info();
        }

    void info()
    {   std::wcout << L"\nНайдены DLL: " << dllnames.size() << '\n';
        for(const auto& name : dllnames)
        {   std::wcout << L"  " << name << '\n';
        }   std::wcout                  << '\n';
    }

    const std::vector<std::wstring>& get(){ return dllnames; }

private:
    std::vector<std::wstring> dllnames;

    void find()
    {
        ///----------------------------------|
        /// Расширение которое буду искать.  |
        ///----------------------------------:
        std::wstring ext = L".dll";

        for(auto &file : std::filesystem::recursive_directory_iterator("./"))
        {   if(file.path().extension() == ext)
            {   dllnames.push_back(file.path().filename());
            }
        }
    }
};


///----------------------------------------------------------------------------|
/// Участники забега (или коллекция мозгов).
///----------------------------------------------------------------------------:
struct  DLL_manager
{       DLL_manager()
        {
            load   ();
            info   ();
            int_tab();
        }
       ~DLL_manager()
        {
            for(auto& ai : aibots) delete ai;
        }

    FindDLL findDLL;

    void info()
    {   std::wcout << L"УЧАСТНИКИ ЗАБЕГА:\n";
        int cnt = 0;
        for(const auto& ai : aibots)
        {   std::wcout << L"  "
                       << std::setw( 3) << ++cnt               << ".  "
                       << std::setw(16) << ai->_name()         << " [ "
                       << std::setw(12) << ai->dllname.c_str() << " ]\n";
        }   std::wcout << std::endl;
    }

    const std::vector<std::pair<size_t, size_t>>& get_tab() const
    {   return tab;
    }

    const std::vector<AI*>& get_aibots() const
    {   return aibots;
    }

private:
    ///----------------------------------|
    /// Готовим мозги.                   |
    ///----------------------------------:
    std::vector<AI*> aibots;

    void load()
    {
        for(const auto&   name : findDLL.get())
        {   std::string s(name.begin(), name.end());
            aibots.push_back(new AI(s.c_str()));

            if(aibots.back()->error)
            {
                delete aibots.back    ();
                       aibots.pop_back();
            }
        }
    }

    ///----------------------------------|
    /// Расписание игр.                  |
    ///----------------------------------:
    std::vector<std::pair<size_t, size_t>> tab;

    void int_tab()
    {
        ///------------------------------|
        /// Один против всех.            |
        ///------------------------------:
        for    (size_t i =     0, N = aibots.size() - 1; i < N; ++i)
        {   for(size_t j = i + 1; j < aibots.size();            ++j)
            {   tab.push_back(std::pair<size_t, size_t>(i, j));
            }
        }

        ///------------------------------|
        /// Каждая пара играет две игры. |
        /// (сначала ходит 1, потом 2)   |
        ///------------------------------:
        std::wcout << L"Ожидается всего спарингов: "
                   << tab.size() * 2 << std::endl;
    }

public:
    static void testclass();
};

///------------------------------|
/// ...
///------------------------------:
void DLL_manager::testclass()
{   std::wcout << L"TEST DLL_manager:\n";

    DLL_manager DLL_man;

    std::wcout << "\nTEST FINISHED!\n" << std::endl;;
    std::cin.get();
}


///----------------------------------------------------------------------------|
/// Игрок.
///----------------------------------------------------------------------------:
struct  Player
{       Player(std::wstring_view nm, const char f) : name(nm), FISHKA(f)
        {   /// Играет человек.
        }
        Player(AI* ai_, const char f) : FISHKA(f),  ai(ai_)
        {   /// Играет ИИ.

            name = ai->get_name();
        }
       ~Player()
        {
        }

    std::wstring name;
    char       FISHKA;


    void win_info   ()
    {   ai->stat.add_win();
        std::wcout << L"Игрок " << name << L" ВЫИГРАЛ!\n";
        std::cin.get();
    }

    Plot step(const Field& field)
    {   if(ai != nullptr)
        {
            auto   plot = ai->step(field);
            return plot;
        }

        /// TODO ...

        return {size_t(-1), 0};
    }

private:
    AI* ai = nullptr;

    friend struct  Game;
};

///----------------------------------------------------------------------------|
/// Вся ИГРА.
///----------------------------------------------------------------------------:
struct  Game
{       Game(Player* a_, Player* b_, int Cnt) : a(a_), b(b_), cntg(Cnt)
        {   loop();
        }

    void change_fishki()
    {   field.clear   ();
        std:: swap (a->    FISHKA,     b->FISHKA);
        std:: swap (a->ai->FISHKA, b->ai->FISHKA);

        if(a->ai->FISHKA == cfg.FISHKI[0])
        {
            a->ai->_stfish (cfg.FISHKI[0]);
            b->ai->_stfish (cfg.FISHKI[1]);
        }
        else
        {   b->ai->_stfish (cfg.FISHKI[0]);
            a->ai->_stfish (cfg.FISHKI[1]);
        }

    }

    int cnt;

    Player*   a;
    Player*   b;
    Field field;
    int    cntg;

    void loop()
    {
        std::wcout << L"Игра ...\n";

        ///------------------------------|
        /// Первый ходит у кого 'X'      |
        ///------------------------------:
        if(a->FISHKA == cfg.FISHKI[1]) std::swap(a, b);

        while(field.is_step())
        {
            /// ход игрока а
            {
                auto p   = a->step(field);
                bool err = field.verification(p);
                if (!err)
                {   /// TODO ...
                    std::wcout << L"Проблема 1 ...\n" << std::endl;
                    std::cin.get();
                    break;
                }

                if(p.x == size_t(-1))
                {   std::cout << "... p.x == size_t(-1)\n" << std::endl;
                    std::cin.get();
                }

                field[p.y][p.x] = a->FISHKA;

                show();
            }


            if(field.is_win(a->FISHKA))
            {   b->ai->stat.add_def();
                a->win_info();
                return;
            }

            /// ход игрока b
            {
                auto p   = b->step(field);
                bool err = field.verification(p);
                if (!err)
                {   /// TODO ...
                    std::wcout << L"Проблема 2 ...\n" << std::endl;
                    std::cin.get();
                    break;
                }

                if(p.x == size_t(-1))
                {   std::cout << "... p.x == size_t(-1)\n" << std::endl;
                    std::cin.get();
                }

                field[p.y][p.x] = b->FISHKA;

                show();
            }

            if(field.is_win(b->FISHKA))
            {   a->ai->stat.add_def();
                b->win_info();
                return;
            }
        }
        std::wcout << L"НИЧЬЯ\n";

        a->ai->stat.add_nob();
        b->ai->stat.add_nob();
    }

private:
    void show()
    {   std::system("cls");
        std::wcout << L"Игра:" << cntg  << '\n';
        std::cout  << field    << std::endl;
        sleep(500);
    }
};


///----------------------------------------------------------------------------|
/// Арбитер.
///----------------------------------------------------------------------------:
struct  Arbiter
{       Arbiter()
        {
            std::cin.get();
            loop();
        }

private:

    DLL_manager DLL_man;

    Player* a = nullptr;
    Player* b = nullptr;

    int cnt   = 0;

    void loop()
    {

        for(const size_t N = DLL_man.get_tab().size(); ipair < N; )
        {
            set_players();
            Game go(a, b, ++cnt);

                 go.change_fishki();
                 go.cntg ++;
                 go.loop ();
        }

        std::wcout << L"ТУРНИР ЗАВЕРШЕН!\n\n";

        show_raiting();
    }

    size_t ipair = 0;

    void set_players()
    {
        const auto& tab = DLL_man.get_tab   ();
        const auto& aib = DLL_man.get_aibots();

        const auto&[iplayer1, iplayer2] = tab[ipair];

        ipair++;

        AI* ai1 = aib[iplayer1];
        AI* ai2 = aib[iplayer2];

        ai1->FISHKA = cfg.FISHKI[0];
        ai2->FISHKA = cfg.FISHKI[1];

        ai1->_stfish(cfg.FISHKI[0]);
        ai2->_stfish(cfg.FISHKI[1]);

        if(nullptr != a) delete a;
        if(nullptr != b) delete b;

        a = new Player(ai1, cfg.FISHKI[0]);
        b = new Player(ai2, cfg.FISHKI[1]);
    }

    void show_raiting()
    {   std::wcout << L"ИТОГОВАЯ ТАБЛИЦА РЕЙТИНГОВ!\n";

        std::multimap<int, AI*, std::greater<>> m;

        for(const auto& e : DLL_man.get_aibots())
        {   m.insert(std::make_pair(e->stat.rating, e));
        }

        int cnt = 0;
        for(const auto&[r,  ai] : m)
        {   std::wcout << ++cnt              << ". "
                       << ai->stat.get_str() << L" -> "
                       << ai->get_name    () << '\n';
        }

        std::cin.get();
    }
};


int main()
{
  //Field::testclass      ();
  //AI::testclass         ();
  //DLL_manager::testclass();
    try
    {
        Arbiter run;
    }
    catch(const Plot& p)
    {
        std::wcout << L"eee..." << std::endl;
    }
}
