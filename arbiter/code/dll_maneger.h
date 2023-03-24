#ifndef DLL_MANEGER_H
#define DLL_MANEGER_H
///----------------------------------------------------------------------------|
/// "dll_maneger.h"
///----------------------------------------------------------------------------|
#include <filesystem>
#include "aishell.h"
#include "vers/aishell_SmallEvil.h"

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
    {   myl::wcout << L"\nНайдены DLL: " << dllnames.size() << '\n';
        for(const auto& name : dllnames)
        {   myl::wcout << L"  " << name << '\n';
        }   myl::wcout                  << '\n';
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

        for(auto &file : std::filesystem::directory_iterator("./"))
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

    const      std::pair<AI_wrap*, AI_wrap*> get_pair  (size_t i )
    {   return std::pair<AI_wrap*, AI_wrap*>(aibots[tab[i].first ],
                                             aibots[tab[i].second]);
    }

    void info()
    {   myl::wcout << L"УЧАСТНИКИ ЗАБЕГА:\n";
        int cnt = 0;
        for(const auto& ai : aibots)
        {   myl::wcout << L"  "
                       << ++cnt << ".  "
                       << ai->who()     << ",  "
                       << ai->v_get_interface_version()
                       << '\n';
        }   myl::wcout << myl::endl;
    }

    const std::vector<AI_wrap*>& get_aibots() const
    {   return aibots;
    }

    size_t amount_games() const { return tab.size(); }


private:
    FindDLL findDLL;

    ///----------------------------------|
    /// Готовим мозги.                   |
    ///----------------------------------:
    std::vector<AI_wrap*> aibots;

    void load()
    {
        std::string version ;
        HINSTANCE   hProcDLL;

        for(const auto&   name : findDLL.get())
        {   

            std::string s = myl::to_string(name);

            try
            {   hProcDLL = AI_wrap::get_hinst  (s.c_str());
                version  = AI_wrap::get_version(hProcDLL );
            }
            catch(...)
            {
                continue;
            }


            if(version == "interface_version:xlat")
            {
                aibots.push_back(new AI(name.c_str(), hProcDLL));
            }
            else if(version == "interface_version:se")
            {
                aibots.push_back(new AI_SmallEvil(name.c_str(),hProcDLL));
            }

            if(aibots.back()->error)
            {   delete aibots.back    ();
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
        myl::wcout << L"Ожидается всего спарингов: "
                   << tab.size() * 2 << myl::endl;
    }

public:
    static void testclass();
};


///------------------------------|
/// Тест.                        |
///------------------------------:
inline void DLL_manager::testclass()
{   TEST_START(DLL_manager);

    DLL_manager DLL_man;

    TEST_FINISHED;
}


#endif // DLL_MANEGER_H
