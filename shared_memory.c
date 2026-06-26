#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int main() {
    int shmid;
    char *shared_memory;

    // Create shared memory segment
    shmid = shmget(IPC_PRIVATE, 1024, IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }

    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        shared_memory = (char *)shmat(shmid, NULL, 0);
        printf("Child received: %s\n", shared_memory);
        shmdt(shared_memory);
    } else {
        // Parent process
        shared_memory = (char *)shmat(shmid, NULL, 0);
        strcpy(shared_memory, "Hello from Parent Process!");
        wait(NULL);
        shmdt(shared_memory);

        // Remove shared memory
        shmctl(shmid, IPC_RMID, NULL);
    }

    return 0;
}
