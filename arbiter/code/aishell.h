#ifndef AISHELL_H
#define AISHELL_H
///----------------------------------------------------------------------------|
/// "aishell.h"
///----------------------------------------------------------------------------|
#include "../../common/common.h"
#include "statistics.h"
#include <windows.h>

#include "ai_wrap.h"

///----------------------------------------------------------------------------|
/// ИИ.
///----------------------------------------------------------------------------:
///  __cdecl  для VS
/// __stdcall ???
typedef const wchar_t*(__cdecl * _name_t    )(                        );
typedef Plot          (__cdecl * _step_t    )(const Plot last_step    );
typedef void          (__cdecl * _create_t  )(const Cfg  cfg          );
typedef void          (__cdecl * _delete_t  )(                        );
typedef void          (__cdecl * _stfish_t  )(char  FISHKA            );
typedef void          (__cdecl * _sendplot_t)(Plot  plot, char color  );
//typedef const char *(__cdecl * _get_interface_version_t)(           );


struct  AI : public AI_wrap
{       AI ( const wchar_t* dllnm, HINSTANCE hinst)
           : dllnamew      (dllnm)
        {
            try
            {   hGetProcIDDLL = hinst;
                load_dll(   );
                v_create (cfg);

                /*
                 *  std::wcout << L"DLL load GOOD!\n";
                 *  std::wcout << L"_name() returned: "
                 *             << _name() << std::endl;
                 */

                nm_dllname  = std::wstring(v_name());
            }
            catch(const std::exception& e)
            {   myl::wcout << e.what() << myl::endl;
                error = true; return;
            }
            catch(...)
            {   error = true; return;
            }

            nm_dllname += L". \"" ;
            nm_dllname += dllnamew;
            nm_dllname += L"\" "  ;
/*
            std::wostringstream oss;
            oss.setf(std::ios::left);
            oss<< std::setw(14) << std::wstring(_name());
            oss << L" [" << dllnamew << L"]";
            nm_dllname = oss.str();
*/
        }
       ~AI()
        {
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
    _name_t                               _name    ;
    _step_t                               _step    ;
    _create_t                             _create  ;
    _delete_t                             _delete  ;
    _stfish_t                             _stfish  ;
    _sendplot_t                           _sendplot;
    _get_interface_version_t _get_interface_version;


public:
    #define GET_PROC_ADDRESS(V) get_proc_address(V, #V)
    void load_dll()
    {
        GET_PROC_ADDRESS(_name    );
        GET_PROC_ADDRESS(_step    );
        GET_PROC_ADDRESS(_create  );
        GET_PROC_ADDRESS(_delete  );
        GET_PROC_ADDRESS(_stfish  );
        GET_PROC_ADDRESS(_sendplot);
        GET_PROC_ADDRESS(_get_interface_version);
    }
    #undef GET_PROC_ADDRESS

    template<typename F>
    void get_proc_address(F& foo, const char*  fooname)
    {
             foo = (F)GetProcAddress(hGetProcIDDLL, fooname);
        if (!foo)
        {   myl::wcout << "ERROR: dll load "
                       << fooname  << " of \""
                       << dllnamew << "\""
                       << myl::endl;
            throw ERROR_EXCEPTION_MESS(" qwerty");
        }
    }

    ///------------------------------------------------------------------------|
    void v_create(const Cfg& _cfg) const
    {     _create(           _cfg);
    }

    Plot v_step(const Plot&  last_step)
    {   Plot   pzzz = _step(last_step);/////////////////////////////////////////
        return pzzz;
    }

    const wchar_t* v_name  (                  ) const { return _name  (); }
    void           v_delete(                  ) const {        _delete(); }
    void           v_stfish(const char FISHKA )
    {      _stfish(FISHKA);
    }

    void v_sendplot (Plot  plot, char color) const
    {     _sendplot(plot, color);
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
inline    void AI::testclass()
{   TEST_START(AI)

    Field f;

    HINSTANCE hinst = AI_wrap::get_hinst("0.dll");
    AI_wrap*  ai    = new AI(L"0.dll", hinst);

    Plot plt{1, 1};

        myl::wcout << ai->v_step(plt) << '\n';
        myl::wcout << ai->v_step(plt) << '\n';
        myl::wcout << ai->v_step(plt) << '\n';
        myl::wcout << ai->v_step(plt) << '\n';

    delete ai;

    TEST_FINISHED
}



#endif // AISHELL_H
