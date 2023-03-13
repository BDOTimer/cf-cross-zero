#ifndef DEBUG_H
#define DEBUG_H
///----------------------------------------------------------------------------|
/// "debug.h"
///----------------------------------------------------------------------------:
#define MYDEBUG

#ifdef MYDEBUG
#define ASSERT(U) if(!(U)) std::cout << "\aASSERT: FILE: "      \
                                         << cutpath(__FILE__)   \
                                         << ", LINE: "          \
                                         << __LINE__  << '\n' ; ll
#define l(v)      std::wcout << #v << " = " << (v) << '\n' ;
#define ls(v)     std::cout  << #v << " = " << (v) << '\n' ;
#define ll        std::cin.get();
#define sssg       std::cout << "SIGNAL\n";ll
#else
#define ASSERT(U)
#define l(v)
#define ll
#define sss
#endif

inline std::string cutpath  (std::string s)
{   auto p = s.find  ("code");
    return   s.substr(p , s.size() - p);
}

struct  CustomException : public std::exception
{       CustomException(int line, const char* filename)
        {   reason = std::string("ERROR_EXCEPTION: File: "  ) +
                                               sub(filename ) +
                            ", Line: " + std::to_string(line) ;
        }

    std::string LEFT = "sources";
    std::string reason;

    virtual const char* what() const throw()
    {   return  reason.c_str();
    }

    std::string sub(std::string s)
    {   const auto pos = s.find  (LEFT) + LEFT.size() + 1;
        return           s.substr(pos, s.size() - pos);
    }
};


#define ERROR_EXCEPTION CustomException(__LINE__, __FILE__)

#define TEST_START(N) std::wcout << "\nTEST "   << #N              \
                                 << " START:\n" << std::endl;
#define TEST_FINISHED std::wcout << "\nTEST "      << __FUNCTION__ \
                                 << " FINISHED!\n" << std::endl;   \
                      std::cin.get();

#endif // DEBUG_H
