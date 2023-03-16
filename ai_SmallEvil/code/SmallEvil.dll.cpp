
const char* INTERFACE_VERSION = "interface_version:se";

#include <stdio.h>
#include "ai.dll.h"

#define DLLEXP __declspec (dllexport)

//static AI* ai = nullptr;
///--------------------------------------------------|
/// Внешний интерфейс AI.                            |
///--------------------------------------------------:
extern "C"
{
    DLLEXP void init(){
       //ai   = new AI();
       printf("DLLEXP void init()\n");
    }
    DLLEXP void release(){
        printf("DLLEXP void release()\n");
    }
    DLLEXP void new_game(int width, int height, int chain, bool color){
        printf("DLLEXP void new_game(width = %d, ", width);
        printf("height = %d, ", height);
        printf("chain = %d, ", chain);
        printf("bool = %d)\n", (int)color);
    }
    DLLEXP void set_point(int x, int y, bool color){
        printf("DLLEXP void set_point(x = %d, ", x);
        printf("y = %d, ", y);
        printf("bool color = %d)\n", (int)color);
    }
    // op_x, op_y - ход оппонента если он есть (доступен)
    // в теории можно выбросить, но наверное лучше пока оставить
    // {-1,-1} в случае отсутствия
    DLLEXP void step(int* x, int* y, int op_x, int op_y){
        printf("DLLEXP void step(op_x = %d, ", op_x);
        printf("op_y = %d)\n", op_y);
        *x = 2023;
        *y = 2024;
    }
    DLLEXP const wchar_t* name(){
        return L"smallevil";
    }
    DLLEXP const char* get_interface_version()
    {   return INTERFACE_VERSION;
    }
}
