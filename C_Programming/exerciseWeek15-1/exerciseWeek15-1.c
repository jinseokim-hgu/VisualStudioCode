#include <stdio.h>

int main()
{
    int a=17;

    for(int i=7;i>=0;--i){
        printf("%d", (a>>i)&1);
    }

    return 0;
}