#include <stdio.h>
#include "headers.h"
int main(int argc, char* argv[])
{   
    structCases cases;
    cases = options(argc, argv);
    if(!cases.errors){
        dirContents(cases);
    }
    return 0;
}