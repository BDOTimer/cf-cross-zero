#ifndef AI_WRAP_H
#define AI_WRAP_H
///----------------------------------------------------------------------------|
/// "ai_wrap.h"
///----------------------------------------------------------------------------|
typedef const char*(__cdecl * _get_interface_version_t)();


struct  AI_wrap
{       AI_wrap(){}

    virtual ~AI_wrap()
    {
        if(NULL  != hGetProcIDDLL)
        {   auto FreeResult  = FreeLibrary(hGetProcIDDLL);
            if ( FreeResult != 0)
            {    myl::wcout  << "ERROR: FreeLibrary ...\n";
            }
        }
    }

    virtual const wchar_t* v_name                 (                      ) const= 0;
    virtual Plot           v_step                 (const Plot&           ) = 0;
    virtual void           v_create               (const Cfg&            ) const= 0;
    virtual void           v_delete               (                      ) const= 0;
    virtual void           v_stfish               (const char FISHKA     )      = 0;
    virtual void           v_sendplot             (Plot  plot, char color) const= 0;
    virtual const char*    v_get_interface_version(                      ) const= 0;

    virtual const char get_FISHKA  ()     const = 0;
    virtual const std::wstring& who()     const = 0;
    virtual void  set_FISHKA(const char fishka) = 0;


    HINSTANCE hGetProcIDDLL = NULL ;
    bool      error         = false;
    Statistics                stat ;


    static HINSTANCE get_hinst(const char* _dllname)
    {
        HINSTANCE _hGetProcIDDLL = LoadLibraryA( _dllname);
        if (!_hGetProcIDDLL)
        {   myl::wcout << "ERROR: Could not DLL ..." << myl::endl;
            throw EXIT_FAILURE;
        }
        return _hGetProcIDDLL;
    }

    static const char* get_version(HINSTANCE hinst)
    {   _get_interface_version_t foo =
       (_get_interface_version_t)GetProcAddress(hinst, "_get_interface_version");

        if (!foo)
        {   myl::wcout << "ERROR: dll load no version ,,," << myl::endl;
            throw EXIT_FAILURE;
        }
        return foo();
    }
};


#endif // AI_WRAP_H
