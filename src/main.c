#include <context.h>
#include <utils.h>
#include <logic.h>
#include <render.h>
#include <list.h>


int main(){
    ProgramContext program;
    
    List* list = lst_generate(10, 1, 10);
    lst_print(list);

    init_sequence(&program);

    program_loop(&program);

    destroy_program_context(&program);
    return 0;
}
