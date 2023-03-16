#ifndef AISHELL_SE_H
#define AISHELL_SE_H

const char* INTERFACE_VERSION = "interface_version:se";
///----------------------------------------------------------------------------|
/// "aishell_SmallEvil.h"
///----------------------------------------------------------------------------|
#include "../../../common/common.h"
#include "../statistics.h"
#include <windows.h>

#include "../ai_wrap.h"

///----------------------------------------------------------------------------|
/// ИИ.
///----------------------------------------------------------------------------:

typedef void (__cdecl * init_t     )();
typedef void (__cdecl * release_t  )();
typedef void (__cdecl * new_game_t )(int w, int h, int chain, bool color);
typedef void (__cdecl * set_point_t)(int x, int y, bool color);
typedef void (__cdecl * step_t     )(int* x, int* y, int op_x, int op_y);
typedef const wchar_t* (__cdecl * name_t                )();


struct  AI_SmallEvil : public AI_wrap
{       AI_SmallEvil(const wchar_t* dllnm, HINSTANCE hinst) : dllnamew(dllnm)
        {
            try
            {   hGetProcIDDLL = hinst;

                load_dll(   );
                _create (cfg);

                nm_dllname  = std::wstring(_name());
            }
            catch(...)
            {   error = true; return;
            }

            nm_dllname += L". \"" ;
            nm_dllname += dllnamew;
            nm_dllname += L"\" "  ;
        }
       ~AI_SmallEvil()
        {   /// TODO: выгрузить DLL.
        }

/*
    Plot stepxxx(const Plot last_step) const
    {   if(!error)
        {
            ///---------------------------|
            /// Оъявляем.                 |
            ///---------------------------:
            Plot plot{stp::NOT_INIT};

            std::chrono::microseconds timeout{3000000};
            using result_type = std::pair<Plot, std::chrono::microseconds>;
{
            std::future<result_type> res = std::async(std::launch::async
            , [](const Plot& f, const AI& ai)
            {
                using namespace std::chrono;

                auto beg = high_resolution_clock::now();
                Plot plt = ai._step(f);   ///<---------------------------------|
                auto end = high_resolution_clock::now();

                return std::make_pair(plt, duration_cast<microseconds>(end - beg));
            }
            , last_step, *this
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

        return stp::BAD_RETURN;
    }
*/

    void set_FISHKA(const char fishka)
    {
        FISHKA = fishka;
        _stfish(fishka);
    }

    const char get_FISHKA  () const { return FISHKA    ; }
    const std::wstring& who() const { return nm_dllname; }

private:
    char       FISHKA = '-';
    std::wstring nm_dllname;
    std::wstring   dllnamew;

private:

    /// smallevel
    init_t                  init                 ;
    release_t               release              ;
    new_game_t              new_game             ;
    set_point_t             set_point            ;
    step_t                  step                 ;
    name_t                  name                 ;
    get_interface_version_t get_interface_version;


public:
    #define GET_PROC_ADDRESS(V) get_proc_address(V, #V)
    void load_dll()
    {
        GET_PROC_ADDRESS(name     );
        GET_PROC_ADDRESS(init     );
        GET_PROC_ADDRESS(release  );
        GET_PROC_ADDRESS(new_game );
        GET_PROC_ADDRESS(set_point);
        GET_PROC_ADDRESS(step     );
        GET_PROC_ADDRESS(get_interface_version);
    }
    #undef GET_PROC_ADDRESS

    template<typename F>
    void get_proc_address(F& foo, const char* fooname)
    {
        foo = (F)GetProcAddress(hGetProcIDDLL, fooname);
        if (!foo)
        {   std::wcout << "ERROR: dll load "
                       << fooname  << " of \""
                       << dllnamew << "\""
                       << std::endl;
            throw EXIT_FAILURE;
        }
    }

    ///------------------------------------------------------------------------|
    void _create (const Cfg& c) const
    {     init( );
    }

    Plot _step(const Plot& last_step)
    {   int      x,    y;
        step   (&x,   &y,  last_step.x, last_step.y);
        return {size_t(x), size_t(y)};

    }

    const wchar_t* _name  (                  ) const { return name   (); }
    void           _delete(                  ) const {        release(); }
    void           _stfish(const char FISHKA )
    {
        bool b = cfg.FISHKI[0] == FISHKA ?  true  : false;
        new_game(cfg.WIDTH, cfg.HEIGHT, cfg.FWIN, b );
    }

    void _sendplot (Plot  plot, char FISHKA) const
    {   bool b = cfg.FISHKI[0] == FISHKA ?  true  : false;
        set_point(plot.x, plot.y, b);
    }

    const char* _get_interface_version() const
    {   return   get_interface_version();
    }

public:
    static void testclass();
};

///------------------------------|
/// Тест.                        |
///------------------------------:
inline void AI_SmallEvil::testclass()
{   TEST_START(AI_SmallEvil)

    Field  f;
    auto   hinst = AI::get_hinst   ( "smallevil.dll");
    AI_wrap*  ai = new AI_SmallEvil(L"smallevil.dll", hinst);

    Plot plt{11, 22};

        ai->_create  (cfg);
        std::wcout << L"Получен ответ: " << ai->_step(plt) << '\n';
        ai->_delete  (   );
        ai->_stfish  (     cfg.FISHKI[0]);
        ai->_sendplot(plt, cfg.FISHKI[0]);
        std::wcout << ai->_get_interface_version()      << '\n';

    delete ai;

    TEST_FINISHED
}


#endif // AISHELL_SE_H
