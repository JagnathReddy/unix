#include <climits>
#include <iostream>
#include <unistd.h>
using namespace std;
int main() {
    //SysConf=> _SC_
  cout << No. of clock ticks:  << sysconf(_SC_CLK_TCK) << endl;
  cout << Max. no. of child processes:  << sysconf(_SC_CHILD_MAX)<< endl;
  cout << Max. no. of open files/process:  << sysconf(_SC_OPEN_MAX)<< endl;
  
    //PathConf=>_PC_ 
  cout << Max. path length:  << pathconf(/, _PC_PATH_MAX) << endl;
  cout << Max. no. of characters in a file name: << pathconf(/, _PC_NAME_MAX) << endl;
  return 0;
}
