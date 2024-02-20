#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <vector>
  
//--lpthread flag MUSTTTTTTTTTTTTTTT


using namespace std;

vector<int> buffer;

sem_t mutex;
sem_t empty;
sem_t full;

void *producer(void *arg) {
  while (true) {
    sleep(1);
    int item = *((int *)arg);
    sem_wait(&empty); // will wait if buffer is full
    sem_wait(&mutex); // 1--=>0
    buffer.push_back(item);
    cout << "Produced: " << item << "size of buffer:" << sizeof(buffer) << endl;
    sem_post(&mutex); // 0++=>1
    sem_post(&full);
  }
  return NULL;
}
void *consumer(void *arg) {
  while (true) {
    sleep(1);
    sem_wait(&full);
    sem_wait(&mutex);
    int item = buffer.back(); // get last
    buffer.pop_back();        // remove last from buffer
    cout << "Consumed: " << item << "size of buffer:" << sizeof(buffer) << endl;
    sem_post(&mutex);
    sem_post(&empty);
  }
  return NULL;
}

int main() {
  pthread_t producerProcess[2];
  pthread_t consumerProcess[2];
  sem_init(&mutex,0,1);  //initial =1
  sem_init(&empty,0,10);  //initial size of buffer=5
  sem_init(&full,0,0);  
  int i;
  for (i = 0; i < 2; i++) {
    int* item=new int(i);
    pthread_create(&producerProcess[i], NULL, producer, (void *)item);
    pthread_create(&consumerProcess[i], NULL, consumer, NULL);
  }
  for (i = 0; i < 2; i++) {
    pthread_join(producerProcess[i], NULL);
    pthread_join(consumerProcess[i], NULL);
  }
  sem_destroy(&mutex);
  sem_destroy(&empty);
  sem_destroy(&full);
  return 1;
}