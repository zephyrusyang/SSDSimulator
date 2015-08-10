#include <stdio.h>

int g_k = 100;

void subloop(char* str){
  int i;

  for(i=0;i<g_k;i++){
    if(0 == i % 10){
      printf("Hello World[%03d],%s\n", i, str);
    }else{
      printf("Hi KIKI[%03d],%s!\n", i, str);
    }
  }

}

int main(void){
  subloop("love you!");
}
