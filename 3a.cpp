#include<iostream>
#include<unistd.h>
// to get error number
#include<errno.h>
// to get error message form error number
#include<string.h>

using namespace std;
int main(){
    int status=link("file1.txt","file2.txt");
    if(status==0){
        cout<<"linked successfully"<<endl;
    }else{
        cout<<strerror(errno)<<endl;   //error message
        cout<<"error linking files"<<endl;
    }
}
