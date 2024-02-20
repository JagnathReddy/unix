#include <iostream>
#include <sys/msg.h>

using namespace std;

// Define a structure for the message data
struct Message {
    long mtype;
    char mtext[100];
};

int main() {
    Message message;

    // Step 1: Create a key for the message queue (use the same key as in the sender)
    key_t key = ftok("message_queue_key", 'A');

    // Step 2: Create or open the message queue
    int msgid = msgget(key, 0666 | IPC_CREAT);

    // Receiver: Read data from the message queue
    // Step 3: Receive a message from the queue with message type 1
    msgrcv(msgid, &message, sizeof(message.mtext), 1, 0) ;
    cout << "Data received from message queue: " << message.mtext << endl;

    msgrcv(msgid, &message, sizeof(message.mtext), 1, 0);
    cout << "Data received from message queue: " << message.mtext << endl;

    return 1;
}
