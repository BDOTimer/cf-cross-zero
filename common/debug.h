#ifndef DEBUG_H
#define DEBUG_H
///----------------------------------------------------------------------------|
/// "debug.h"
///----------------------------------------------------------------------------:
#define MYDEBUG

#include "render.h"

#ifdef MYDEBUG
#define ASSERT(U) if(!(U)) {myl::wcout << "\aASSERT: FILE: "   \
                                       << cutpath(__FILE__)    \
                                       << ", LINE: "           \
                                       << __LINE__ << '\n' ; ll}
#define l(v)      myl::wcout << #v << " = " << (v) << '\n' ;
#define ls(v)     myl::cout  << #v << " = " << (v) << '\n' ;
#define ll        myl::cin.get();
#define sss       myl::wcout << "SIGNAL\n";ll
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
{       CustomException(int line, const char* filename, const char* mess = "")
        {   reason = std::string("ERROR_EXCEPTION: File: "  ) +
                                               cut(filename ) +
                            ", Line: " + std::to_string(line)
                            + mess;
        }

    std::string LEFT = "code";
    std::string reason;

    virtual const char* what() const throw()
    {   return  reason.c_str();
    }

    std::string cut(std::string s)
    {   const auto pos = s.find  (LEFT) + LEFT.size() + 1;
        return           s.substr(pos, s.size() - pos);
    }
};


#define ERROR_EXCEPTION         CustomException(__LINE__, __FILE__)
#define ERROR_EXCEPTION_MESS(M) CustomException(__LINE__, __FILE__, M)

#define TEST_START(N) myl::wcout << "\nTEST "   << #N              \
                                 << " START:\n" << myl::endl;
#define TEST_FINISHED myl::wcout << "\nTEST "      << __FUNCTION__ \
                                 << " FINISHED!\n" << myl::endl;   \
                      myl::cin.get();

#endif // DEBUG_H
