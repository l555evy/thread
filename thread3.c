#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<semaphore.h>

void*thread_fun(void*arg);
sem_t bin_sem;
#define WORK_SIZE 1024
char work_area[WORK_SIZE];
int main(){
  int res;
  pthread_t thread;
  void*thread_result;

  res=sem_init(&bin_sem,0,0);
  if(res!=0){
    perror("Semaphore initialization failed\n");
    exit(EXIT_FAILURE);
  }
  res=pthread_create(&thread,NULL,thread_fun,NULL);
  if(res!=0){
    perror("Thread creation\n");
    exit(EXIT_FAILURE);
  }
  printf("Input some text(enter 'end' to end):");
  while(strncmp("end",work_area,3)!=0){
   fgets(work_area,WORK_SIZE,stdin);
   sem_post(&bin_sem);
  }
  printf("\n waiting for thread to Finsh\n");
  res=pthread_join(thread,&thread_result);
  if(res!=0){
   perror("Thread joined failed");
   exit(EXIT_FAILURE);
  }
  printf("Thread joined %s",(char*)thread_result);
  sem_destroy(&bin_sem);
  exit(EXIT_SUCCESS);
  }
  void*thread_fun(void*arg){
    sem_wait(&bin_sem);
    while(strncmp("end",work_area,3)!=0){
      printf("You input %d characters\n",strlen(work_area)-1);
      sem_wait(&bin_sem);
    }
    pthread_exit("BYE!");
  }

    
