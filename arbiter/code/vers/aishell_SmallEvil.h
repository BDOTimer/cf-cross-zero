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
typedef void (__cdecl * new_game_t )(int  w, int  h, int  chain , bool color);
typedef void (__cdecl * set_point_t)(int  x, int  y, bool color);
typedef void (__cdecl * step_t     )(int* x, int* y, int  op_x  , int op_y);
typedef const wchar_t * (__cdecl * name_t)();


struct  AI_SmallEvil : public AI_wrap
{       AI_SmallEvil(const wchar_t* dllnm, HINSTANCE hinst) : dllnamew(dllnm)
        {
            try
            {   hGetProcIDDLL = hinst;

                load_dll(   );
                v_create (cfg);

                nm_dllname  = std::wstring(v_name());
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
        v_stfish(fishka);
    }

    const char get_FISHKA  () const { return FISHKA    ; }
    const std::wstring& who() const { return nm_dllname; }

private:
    char       FISHKA = '-';
    std::wstring nm_dllname;
    std::wstring   dllnamew;

private:

    /// smallevel
    init_t                   _init                 ;
    release_t                _release              ;
    new_game_t               _new_game             ;
    set_point_t              _set_point            ;
    step_t                   _step                 ;
    name_t                   _name                 ;
    _get_interface_version_t _get_interface_version;


public:
    #define GET_PROC_ADDRESS(V) get_proc_address(V, #V)
    void load_dll()
    {
        GET_PROC_ADDRESS(_name     );
        GET_PROC_ADDRESS(_init     );
        GET_PROC_ADDRESS(_release  );
        GET_PROC_ADDRESS(_new_game );
        GET_PROC_ADDRESS(_set_point);
        GET_PROC_ADDRESS(_step     );
        GET_PROC_ADDRESS(_get_interface_version);
    }
    #undef GET_PROC_ADDRESS

    template<typename F>
    void get_proc_address(F& foo, const char* fooname)
    {
        foo = (F)GetProcAddress(hGetProcIDDLL, fooname);
        if (!foo)
        {   myl::wcout << "ERROR: dll load "
                       << fooname  << " of \""
                       << dllnamew << "\""
                       << myl::endl;
            throw EXIT_FAILURE;
        }
    }

    ///------------------------------------------------------------------------|
    void v_create (const Cfg& c) const
    {     _init( );
    }

    Plot v_step(const Plot& last_step)
    {   int      x,    y;
        _step   (&x,   &y,  last_step.x, last_step.y);
        return {size_t(x), size_t(y)};

    }

    const wchar_t* v_name  (                  ) const { return _name   (); }
    void           v_delete(                  ) const {        _release(); }
    void           v_stfish(const char FISHKA )
    {
        bool b = cfg.FISHKI[0] == FISHKA ?  true  : false;
        _new_game(cfg.WIDTH, cfg.HEIGHT, cfg.FWIN, b );
    }

    void v_sendplot (Plot  plot, char FISHKA) const
    {   bool b = cfg.FISHKI[0] == FISHKA ?  true  : false;
        _set_point(plot.x, plot.y, b);
    }

    const char* v_get_interface_version() const
    {   return   _get_interface_version();
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

        ai->v_create  (cfg);
        myl::wcout << L"Получен ответ: " << ai->v_step(plt) << '\n';
        ai->v_delete  (   );
        ai->v_stfish  (     cfg.FISHKI[0]);
        ai->v_sendplot(plt, cfg.FISHKI[0]);
        myl::wcout << ai->v_get_interface_version()      << '\n';

    delete ai;

    TEST_FINISHED
}


#endif // AISHELL_SE_H
