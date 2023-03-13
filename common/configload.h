#ifndef CONFIG_LOAD_H
#define CONFIG_LOAD_H
///----------------------------------------------------------------------------|
/// "configload.h"
///----------------------------------------------------------------------------|
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "debug.h"

///----------------------------------------------------------------------------|
/// myLib
///----------------------------------------------------------------------------|
template<typename T>
void info(const T& v)
{   for(const auto& e : v) std::cout << e << '\n'; std::cout << std::endl;
}


struct Split
{      Split   (std::string& s, char c = 'c'){ go(s, c); }
    std::vector<std::string> v;
    void go    (std::string& s, char c)
    {   size_t  p1 = 0, p2;
        for( ; (p2 = s.find(" ", p1)) != s.npos;  p1 = ++p2)
        {   v.push_back(s.substr(p1, p2      -p1));
        }   v.push_back(s.substr(p1, s.size()-p1));
    }
};


///----------------------------------------------------------------------------|
/// LoadPregame
///----------------------------------------------------------------------------|
struct  ConfigLoad
{       ConfigLoad() : file_name("config.txt")
        {
            std::wcout << L"ЗАГРУЗКА КОНФИГА ...\n";

            std::ifstream f(file_name);
            if(f.is_open())
            {
                for(std::string s ; std::getline(f, s);)
                {   if(s.find("//") == s.npos) m.push_back(s);
                }
            }
            else
            {   std::cout << "MESSAGE: CONFIG_FILE_ABSENT\n";
            }
        }

    bool error = true;

    template<typename T>
    bool get_config(T& config)
    {   if(m.empty()) return error;

        Split ready(m[0]);

        //info(ready.v);

        if   (ready.v.size() != 5)
        {   l(ready.v.size())
            throw ERROR_EXCEPTION;
        }

        size_t F;
        size_t H;
        size_t W;

        try
        {
            F = std::stoi(ready.v[0]);
            H = std::stoi(ready.v[1]);
            W = std::stoi(ready.v[2]);

            const size_t A = (size_t)ready.v[3][0];
            const size_t B = (size_t)ready.v[4][0];

            if( 32 > A && A > 128) throw ERROR_EXCEPTION;
            if( 32 > B && B > 128) throw ERROR_EXCEPTION;

            config.FWIN   = F;
            config.HEIGHT = H;
            config.WIDTH  = W;
            config.FISHKI[0] = ready.v[3][0];
            config.FISHKI[1] = ready.v[4][0];
        }
        catch(const CustomException& e)
        {   std::cout << e.what() << '\n';
            return error;
        }

        return error = false;
    }

    template<typename C, typename T>
    void get_field(const C& cfg, T& field)
    {   if(error) return;

        data.resize(cfg.HEIGHT);

        field.H = cfg.HEIGHT;
        field.W = cfg.WIDTH;

        for(size_t i = 1; i < m.size(); ++i)
        {   data [i - 1] = m[i];
        }

        for(auto& s : data)
        {   s.resize(cfg.WIDTH, '.');
        }

        for     (auto& r : data)
        {   for (auto& c : r   )
            {   if (c != '.' && c != cfg.FISHKI[0] && c != cfg.FISHKI[1])
                {   c  = '.';
                }
            }
        }

        field = data;
    }

    auto& get_data() const
    {   return data;
    }

private:
    const char* file_name;
    std::vector<std::string>    m;
    std::vector<std::string> data;
public:
    template<typename tC, typename tF> static void testclass(tC&);
};

///------------------------------|
/// Тест.                        |
///------------------------------:
template<typename tC, typename tF>
inline void ConfigLoad::testclass(tC& cfg)
{   TEST_START(ConfigLoad);

    tF f;

    ConfigLoad  pregame;
                pregame.get_config(cfg);
                pregame.get_field (cfg, f);

    std::wcout << cfg << "\n\n";

    f.debug();

    std::cout << f << '\n';

    TEST_FINISHED;
}

#endif // CONFIG_LOAD_H
