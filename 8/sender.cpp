#include <iostream>
#include <cstring>
#include <sys/msg.h>

using namespace std;

// Define a structure for the message data
struct Message {
    long mtype;
    char mtext[100];
};

int main() {
    Message message;

    // Step 1: Create a key for the message queue
    key_t key = ftok("message_queue_key", 'A');

    // Step 2: Create or open the message queue
    int msgid = msgget(key, 0666 | IPC_CREAT);

    // Sender: Send data to the message queue
    message.mtype = 1; // Message type (you can use different types for different purposes)
    strcpy(message.mtext, "Hello, this is a message from the sender!");

    // Step 3: Send the message to the queue
    msgsnd(msgid, &message, sizeof(message.mtext), 0);

    strcpy(message.mtext, "2nd message");
    msgsnd(msgid, &message, sizeof(message.mtext), 0);
    
    cout << "Data sent to message queue." << endl;

    return 0;
}

