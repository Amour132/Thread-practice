#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

using namespace std;

pthread_cond_t cond;
pthread_mutex_t mutex;

void* v1(void *arg)
{
  while(1)
  {
    pthread_cond_wait(&cond,&mutex);
    cout << "活动" <<endl;
  }
}

void* v2(void *arg) 
{
  while(1)
  {
    pthread_cond_signal(&cond);
    sleep(1);
  }
}

int main()
{
  pthread_t t1;
  pthread_t t2;
  
  pthread_cond_init(&cond,NULL);
  pthread_mutex_init(&mutex,NULL);

  pthread_create(&t1,NULL,v1,NULL);
  pthread_create(&t2,NULL,v2,NULL);

  pthread_join(t1,NULL);
  pthread_join(t2,NULL);

  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&cond);

}
