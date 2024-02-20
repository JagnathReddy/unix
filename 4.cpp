#include <iostream>
#include <cstring>
#include <sys/wait.h>
#include <sys/shm.h>
#include <unistd.h>

using namespace std;
#define size 1280    //in bytes , must be a megabyte multiple 
int main(){
    key_t key=ftok("file1.txt",1243);      //make sure the file must exist or error:"segmentation fault (core dumped)"
    int shmid=shmget(key,size,IPC_CREAT|0666);    //IPC_CREAT: available in sys/ipc , 0666: sets the permission to read and write to all processes
    char *shm_ptr=(char*)shmat(shmid,NULL,0);    //attach and //this points to the location of sharedMemory
    string msg="Hello from the shared memory";
    strcpy(shm_ptr,msg.c_str());                  // copies the msg on pointer location
    
    //fork to make a child
    pid_t pid=fork();
    if(pid==0){
        cout<<"Child process reads : "<<shm_ptr<<"from the shared Memory"<<endl;
    }else{
        wait(NULL);  //wait for child to finish
        shmdt(shm_ptr);                 //detach
        shmctl(shmid,IPC_RMID,NULL);   //removes the shared memory //IPC_RMID: remove id
    }
    return 0;
}