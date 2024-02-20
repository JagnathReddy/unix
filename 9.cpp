#include <iostream>
#include <unistd.h>
using namespace std;
int main(){
    int pipe_fd[2];
    pipe(pipe_fd);
    pid_t pid=fork();
    if(pid>0){
        string s="hello";
        close(pipe_fd[0]);
        write(pipe_fd[1],s.c_str(),s.length());
        close(pipe_fd[1]);
    }else{
        char buffer[100];
        size_t Bytesread;
        close(pipe_fd[1]);
        Bytesread=read(pipe_fd[0],&buffer,sizeof(buffer));
        close(pipe_fd[0]);
        buffer[Bytesread]='\0';
        cout<<buffer<<endl;
    }
    return 1;
}