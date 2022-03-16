#include <stdio.h>

int main(void)
{
  int height;
  int mode = 1;
  
  printf("Enter a height:");
  scanf("%d", &height);
  
  for(int i=1;i<=height;i++){
      if (i % 2 == 1) mode = 1;
      else mode = -1;
    for(int j=1;j<=height;j++){
      if(j>i){
        printf(" ");
      }
      else{
        if(mode == 1){
          printf("1 ");
        }
        else if (mode == -1){
          printf("0 ");
        }
        mode *= -1;
      }
    }
    printf("\n");
  }
  return 0;
}