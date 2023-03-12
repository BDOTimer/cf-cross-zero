﻿#ifndef FILE_H
#define FILE_H
///----------------------------------------------------------------------------|
/// "file.h"
///----------------------------------------------------------------------------|
/// Тест.
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>


///----------------------------------------------------------------------------|
/// Blacklist
///----------------------------------------------------------------------------|
struct  Blacklist
{       Blacklist() : file_name_blist("blacklist.txt")
        {
            std::wcout << L"ЗАГРУЗКА Blacklist ...\n";

            std::ifstream f(file_name_blist);
            if(f.is_open())
            {
                for(std::string s ; std::getline(f, s);)
                {   m.push_back(s);
                }
            }

        }

    bool is_this_file_fail(std::string file_name) const
    {   for(const auto& nm : m) if(nm == file_name) return true; return false;
    }

    void add(std::string  file_name) const
    {   std::ofstream(file_name_blist, std::ios_base::app)
                   << file_name << std::endl;
    }

private:
    const char* file_name_blist;
    std::vector<std::string>  m{"xxx.dll"}; /// TODO: test

public:
    static void testclass();
};

inline void Blacklist::testclass()
{   std::wcout << L"TEST Blacklist:\n";

    Blacklist   bl;
                bl.add("aaa.dll");
                bl.add("bbb.dll");

    std::cout << (bl.is_this_file_fail("aaa.dll") ? "FAIL" : "GOOD") << '\n';

    std::wcout << "\nTEST FINISHED!\n" << std::endl;;
    std::cin.get();
}

#endif // FILE_H
