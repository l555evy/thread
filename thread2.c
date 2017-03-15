#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>

void*thread_fun(void*arg);
//char message[]="hello levy";
int run_now=1;
int main(){
  int res;
  pthread_t thread;
  void*thread_result;
  int print_number=0;
  res=pthread_create(&thread,NULL,thread_fun,NULL);
  if(res!=0){
    perror("Thread creation failed");
    exit(EXIT_FAILURE);
  }
  while(print_number++<20){
    if(run_now==1){
      printf("1");
      run_now=2;
    }else{
      sleep(1);
     }
  }
    
  printf("Waiting for thread to finish..\n");
  res=pthread_join(thread,&thread_result);
  if(res!=0){
    perror("Thread join failed");
    exit(EXIT_FAILURE);
  }
  printf("Thread join %s\n",(char*)thread_result);
  exit(EXIT_SUCCESS);
}
void*thread_fun(void*arg){
  int print_number2=0;
  while(print_number2++<20){
    if(run_now==2){
    printf("2");
    run_now=1;
    }else{
    sleep(2);
    }
  }
pthread_exit("Thank you ~~");
}

