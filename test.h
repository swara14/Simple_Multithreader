#include <stdio.h>
int user_main(int argc, char **argv);

void faltu_ka_function(){
    printf("kya karun \n");
}

int main(int argc, char **argv)
{
    faltu_ka_function();
    printf("SPP nhi ho rahi\n");
    int rc = user_main(argc, argv);
    return rc;
    
    return 0;
}


#define main user_main
