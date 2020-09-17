#include "pch.h"
#include "ConsoleTetris.h" 

int main(int argc, char* argv[])
{
    ConsoleTetris ct(10, 20);
    ct.Init();
    ct.Run();
    
    return 0;
}
