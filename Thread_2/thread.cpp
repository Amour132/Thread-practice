#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h> 

using namespace std;

void* thread1(void *arg)
{
   cout<<"thread 1 is returning..."<<endl;
   int* p = new int;
   *p = 1;
   return (void*)p;
}

void* thread2(void* arg)
{
  cout<<"thread2 is exiting..."<<endl;
  int *p = new int;
  *p = 2;
  pthread_exit((void*)p);
}

void* thread3(void* arg)
{
  while(1)
  {
    cout<<"thread3 is running"<<endl;
    sleep(1);
  }
  return NULL;
}

int main()
{
  pthread_t tid;
  void* ret;

  pthread_create(&tid,NULL,thread1,NULL);
  pthread_join(tid,&ret);
  cout<<"thread return thread1 id:"<<tid<<"return code:"<<*(int *)ret<<endl;

  pthread_create(&tid,NULL,thread2,NULL);
  pthread_join(tid,&ret); 
  cout<<"thread return thread1 id:"<<tid<<"return code:"<<*(int *)ret<<endl;

  pthread_create(&tid,NULL,thread3,NULL);
  sleep(3);
  pthread_cancel(tid);
  pthread_join(tid,&ret);  
  if(ret == PTHREAD_CANCELED)
  {
     cout<<"thread return thread1 id:"<<tid<<"return code:PTHREAD_CANCELED"<<endl;

  }
  else 
  {
    cout<<"thread return thread1 id:"<<tid<<"return code: NULL"<<endl;
  }
}
