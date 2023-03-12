#ifndef DLL_MANEGER_H
#define DLL_MANEGER_H
///----------------------------------------------------------------------------|
/// "dll_maneger.h"
///----------------------------------------------------------------------------|
#include <filesystem>
#include "aishell.h"

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

    const      std::pair<AI*, AI*> get_pair  (size_t i )
    {   return std::pair<AI*, AI*>(aibots[tab[i].first ],
                                   aibots[tab[i].second]);
    }

    void info()
    {   std::wcout << L"УЧАСТНИКИ ЗАБЕГА:\n";
        int cnt = 0;
        for(const auto& ai : aibots)
        {   std::wcout << L"  "
                       << std::setw( 3) << ++cnt << ".  "
                       << ai->who()     << '\n';
        }   std::wcout << std::endl;
    }

    const std::vector<AI*>& get_aibots() const
    {   return aibots;
    }

    size_t amount_games() const { return tab.size(); }


private:
    FindDLL findDLL;

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
/// Тест.
///------------------------------:
inline void DLL_manager::testclass()
{   std::wcout << L"TEST DLL_manager:\n";

    DLL_manager DLL_man;

    std::wcout << "\nTEST FINISHED!\n" << std::endl;;
    std::cin.get();
}




#endif // DLL_MANEGER_H
