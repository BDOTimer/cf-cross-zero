/// SmallEvil
#include "ai.dll.h"
 
#define DLLEXP __declspec (dllexport)
 
static AI* ai = nullptr;
///--------------------------------------------------|
/// Внешний интерфейс AI.                            |
///--------------------------------------------------:
extern "C"
{
    DLLEXP void init(){
       ai   = new AI();
    }
    DLLEXP void release(){
        delete ai;
    }
    DLLEXP void new_game(int width, int height, int chain, bool color){
        
    }
    DLLEXP void set_point(int x, int y, bool color){
        
    }
    // op_x, op_y - ход оппонента если он есть (доступен)
    // в теории можно выбросить, но наверное лучше пока оставить
    // {-1,-1} в случае отсутствия
    DLLEXP void step(int* x, int* y, int op_x, int op_y){
        // что в функции уже никого не касается,
        // кроме как создателя DLL
        
        // проверки не нужны мы безоговорочно верим Арбитру XD
        // но никто не запрещает их сделать
        auto p = ai->step({op_x, op_y});
        *x = p.x;
        *y = p.y;
    }
 
    DLLEXP const wchar_t* _name(){
        return ai->name();
    }
}