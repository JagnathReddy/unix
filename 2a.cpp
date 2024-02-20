 #include <iostream>
 #include <fstream>
 #include <unistd.h>
 int main() {
    int source_fd = open("copyFromHere.txt", O_RDONLY); //O_RDONLY=open read only
    if (source_fd == -1) {
        perror("Error opening source file");
        return 1;
    }
    //Create or open the destination file for writing
    //open=> "path", write_only OR Create(O_CREAT) , mode(S_IRUSR | S_IWUSR) 
    //mode only req if the file isnt already present
    int dest_fd = open("pasteHere.txt" O_WRONLY);
    
    char buffer[4096];
    ssize_t bytes_read;
    // Copy data from source to destination
    while ((bytes_read = read(source_fd, buffer, sizeof(buffer))) > 0) {
        ssize_t bytes_written = write(dest_fd, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            perror("Error writing to destination file");
            close(source_fd);
            close(dest_fd);
            return 1;
        }
    }
    // Close file descriptors
    close(source_fd);
    close(dest_fd);
    std::cout << "File copied successfully!" << std::endl;
    return 0;
 }