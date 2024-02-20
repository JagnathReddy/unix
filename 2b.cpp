 #include <iostream>
 extern char** environ;     //extern 
 int main() {
    int i=0; 
    while (environ[i] != nullptr) {
        std::cout << environ[i] << std::endl;
        i++;
    }
    return 0;
 }