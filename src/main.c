#include <context.h>
#include <utils.h>
#include <logic.h>
#include <render.h>


int main(){
    ProgramContext program;
    init_sequence(&program);

    program_loop(&program);

    destroy_program_context(&program);
    return 0;
}
