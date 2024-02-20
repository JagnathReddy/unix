#include<iostream>
#include<unistd.h>
using namespace std;
int main(){
    int t=0;
    pid_t pid = fork();     //pid_t=> Process IDentifier _ type
    if(pid==-1){
        cout<<"fork error"<<endl;
        return 1;
    }
    for(int i=0;i<5;i++){
        if(pid==0){
            cout<<"child process : "<<i<<endl;
        }else{
            cout<<"parent process : "<<i<<endl;
        }
        sleep(1); 
    }
    return 0;
}
