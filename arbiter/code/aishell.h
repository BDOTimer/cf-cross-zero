#ifndef AISHELL_H
#define AISHELL_H
///----------------------------------------------------------------------------|
/// "aishell.h"
///----------------------------------------------------------------------------|
#include "../../common/common.h"
#include "statistics.h"
#include <windows.h>

///----------------------------------------------------------------------------|
/// ИИ.
///----------------------------------------------------------------------------:
typedef const wchar_t*(__stdcall * _name_t  )(                        );
typedef Plot          (__stdcall * _step_t  )(const Plot last_step    );
typedef void          (__stdcall * _create_t)(const Cfg  cfg          );
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

                _create(cfg);
            }
            catch(int err)
            {   error = true;
            }

            std::string s{dllname};
            dllnamew = std::wstring(s.begin(), s.end());

            nm_dllname  = std::wstring(_name());
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
        {   /// TODO: выгрузить DLL.
        }

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
                Plot plt = ai._step(f); ///<---------------------------------|
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


    Plot step(const Plot last_step) const
    {   if(!error)
        {   return _step(last_step);
        }

        return stp::BAD_RETURN;
    }

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
    std::string     dllname;
    std::wstring   dllnamew;

public:

    Statistics       stat;

    _name_t       _name  ;
    _step_t       _step  ;
    _create_t     _create;
    _delete_t     _delete;
    _stfish_t     _stfish;

    HINSTANCE hGetProcIDDLL = nullptr;

    bool error = false;

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


///------------------------------|
/// Тест.                        |
///------------------------------:
inline void AI::testclass()
{   std::wcout << L"TEST AI:\n";

    Field f;
    AI   ai("0.dll");

    Plot plt{1, 1};

        std::wcout << ai._step(plt) << '\n';
        std::wcout << ai._step(plt) << '\n';
        std::wcout << ai._step(plt) << '\n';
        std::wcout << ai._step(plt) << '\n';

    std::wcout << "\nTEST FINISHED!\n" << std::endl;
    std::cin.get();
}



#endif // AISHELL_H
