#include<iostream>
#include<pthread.h>
#include <unistd.h>
using namespace std;
void* count100(void* item){
    int threadId=*((int*)item);
    for(int i=0;i<100;i++){
        sleep(1);
        cout<<i<<" from threadId: "<<threadId<<endl;
    }
    return NULL;
}

int main(){
    int n=2;
    pthread_t thread[2];
    for(int i=0;i<n;i++){
        int* item=new int(i);
        pthread_create(&thread[i],NULL,count100,(void*)item);
    }
    for(int i=0;i<n;i++){
        pthread_join(thread[i],NULL);
    }
    return 1;
}

