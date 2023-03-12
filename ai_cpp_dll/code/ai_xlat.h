#ifndef AI_XLAT_H
#define AI_XLAT_H

/// в разработке ...
///----------------------------------------------------------------------------|
/// "ai_xlat.h"
///----------------------------------------------------------------------------:

struct  Cell
{       Cell()
        {

        }

    char* data{nullptr};
    Plot  plot{stp::NOT_INIT};

};


struct  AI_xlat
{       AI_xlat()
        {
            const auto a = field.get_all_str();

            for(size_t i = 0; i < a.size();   ++i)
            {   q.push_back(std::vector<Cell>(a[i].size()));
            }


            get_all_str();

            debug();
        }

    Field field;

    void debug()
    {
        for    (const auto& row : q )
        {
            for(const auto& e   : row)
            {
                if(e.data != nullptr) std::cout << *e.data;
                else                  std::cout << '$';
            }   std::cout << '\n';
        }       std::cout << '\n';
    }


    #define TESTMODE false
    ///---------------------------|
    /// Разворачиваем строки!     |
    ///---------------------------:
    std::vector<std::string> get_all_str()
    {   std::vector<std::string> r;

        const auto H = cfg.HEIGHT;
        const auto W = cfg.WIDTH;

        auto& m = field.m;

        size_t cnt = 0;

        for    (size_t h = 0; h < H; ++h)
        {   r.push_back(std::string());
            for(size_t w = 0; w < W;  ++w)
            {   r.back().push_back(m[h][w]);

                q[cnt][w].plot =   {h, w};
                q[cnt][w].data = &m[h][w];
            }
            cnt++;
        }

        for    (size_t w = 0; w < W; ++w)
        {   r.push_back(std::string());
            for(size_t h = 0; h < H; ++h)
            {   r.back().push_back(m[h][w]);

                q[cnt][h].plot =   {h, w};
                q[cnt][h].data = &m[h][w];
            }
            cnt++;
        }


        ///---------------------------|
        /// Повернуть на -45 градусов.|
        ///---------------------------:
        for    (size_t h = 0; h < H; ++h)
        {   std::string s;

            std::vector<Cell> t;

            for(size_t w = 0, y = h; w < W && y < H; ++w, ++y)
            {   s.push_back(m[y][w]);

                t.push_back(Cell());

                t.back().data = &m[y][w];
                t.back().plot =   {y, w};

            }
            if(s.size() >= cfg.FWIN || TESTMODE)
            {   r.push_back(s);

                q[cnt] = t;
            }
            cnt++;
        }

        for    (size_t w = 1; w < W; ++w)
        {   std::string s;
            std::vector<Cell> t;
            for(size_t x = w, h = 0; x < W && h < H; ++x, ++h)
            {   s.push_back(m[h][x]);

                t.push_back(Cell());
                t.back().data = &m[h][x];
                t.back().plot =   {h, x};
            }
            if(s.size() >= cfg.FWIN || TESTMODE)
            {   r.push_back(s);
                q[cnt] = t;
            }
            cnt++;
        }


        ///---------------------------|
        /// Повернуть на +45 градусов.|
        ///---------------------------:
        for    (size_t h = 0; h < H; ++h)
        {   std::string s;
            std::vector<Cell> t;
            for(size_t w = W - 1, y = h; w < W && y < H; --w, ++y)
            {   s.push_back(m[y][w]);

                t.push_back(Cell());
                t.back().data = &m[y][w];
                t.back().plot =   {y, w};
            }
            if(s.size() >= cfg.FWIN || TESTMODE)
            {   r.push_back(s);
                q[cnt] = t;
            }
            cnt++;
        }

        for    (size_t w = W - 2; w < W; --w)
        {   std::string s;
            std::vector<Cell> t;
            for(size_t x = w, h = 0; x < W && h < H; --x, ++h)
            {   s.push_back(m[h][x]);

                t.push_back(Cell());
                t.back().data = &m[h][x];
                t.back().plot =   {h, x};
            }
            if(s.size() >= cfg.FWIN || TESTMODE)
            {   r.push_back(s);
                q[cnt] = t;
            }
            cnt++;
        }

        return r;
    }
#undef TESTMODE

private:
    std::vector<std::vector<Cell>> q;

public:
    static void testclass();
};


///------------------------------|
/// Тест.
///------------------------------:
void AI_xlat::testclass()
{   std::wcout << L"Тест AI_xlat:\n";

    AI_xlat x;

    std::wcout << "TEST FINSHED!\n";
    std::cin.get();
}


#endif // AI_XLAT_H
