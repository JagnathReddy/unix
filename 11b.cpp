#include<iostream>
#include<pthread.h>
#include <unistd.h>
using namespace std;
void* printHello(void* item){
    int threadId=*((int*)item);
    for(int i=0;i<5;i++)
    cout<<" HELLO WORLD from "<<threadId<<endl;
    pthread_exit(NULL);
    // return NULL;
}

int main(){
    int n=5;
    pthread_t thread[5];
    for(int i=0;i<n;i++){
        int* item=new int(i);
        pthread_create(&thread[i],NULL,printHello,(void*)item);
    }
        for(int i=0;i<n;i++){
            pthread_join(thread[i],NULL);
        }
        sleep(1);
    
    return 1;
}

