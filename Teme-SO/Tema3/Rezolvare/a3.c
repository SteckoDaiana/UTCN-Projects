#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

int get_command_num(char *s) {
    if (s == strstr(s, "PING")) {
        return 1;
    }
    if (s == strstr(s, "CREATE_SHM")) {

        return 2;
    }
    if (s == strstr(s, "WRITE_TO_SHM")) {

        return 3;
    }
    if (s == strstr(s, "MAP_FILE")) {

        return 4;
    }
    return 0;
}

void write_message(int fd, char message[]) {
    unsigned char len = strlen(message);
    write(fd, &len, 1);
    write(fd, message, len);
}

int main() {
    unsigned int shm_length, mapped_file_length;
    char command[100];
    char fname[100];
    unsigned int aa, bb;
    unsigned char command_len, *shm, *mapped_file;
    int fd1;
    if (mkfifo("RESP_PIPE_20111", 0600) == -1) {
        exit(-1);
    }
    int fd[2];
    fd[0] = open("REQ_PIPE_20111", O_RDONLY);
    fd[1] = open("RESP_PIPE_20111", O_WRONLY);
    write_message(fd[1], "CONNECT");
    for (;;) {
        memset(command, 0, 100);
        read(fd[0], &command_len, 1);
        read(fd[0], command, command_len);
        int command_num = get_command_num(command);
        switch (command_num) {
            default:
                if (mapped_file > 0)
                    munmap(mapped_file, mapped_file_length);
                if (shm>0)
                    munmap(shm, shm_length);
                unlink("RESP_PIPE_77519");
                goto finish;
            case 1:
                write_message(fd[1], "PING");
                write_message(fd[1], "PONG");
                aa = 20111;
                write(fd[1], &aa, 4);
                break;
            case 2:
                read(fd[0], &shm_length, 4);
                fd1 = shm_open("/mWHQCNa", O_CREAT | O_RDWR, 0664);
                if (fd1 == -1) {
                    write_message(fd[1], "ERROR");
                    break;
                }
                ftruncate(fd1, shm_length);
                shm = mmap(0, shm_length, PROT_READ | PROT_WRITE, MAP_SHARED, fd1, 0);
                if (shm == 0) {
                    write_message(fd[1], "ERROR");
                    break;
                }
                write_message(fd[1], "CREATE_SHM");
                write_message(fd[1], "SUCCESS");
                break;
            case 3:;
                read(fd[0], &aa, 4);
                read(fd[0], &bb, 4);
                write_message(fd[1], "WRITE_TO_SHM");
                if (aa + sizeof(int) < shm_length && aa >= 0) {
                    memcpy(shm + aa, &bb, 4);
                    write_message(fd[1], "SUCCESS");
                } else {
                    write_message(fd[1], "ERROR");
                }
                break;
            case 4:;
                read(fd[0], &command_len, 1);
                read(fd[0], fname, command_len);
                fname[command_len] = '\0';
                fd1 = open(fname, O_RDONLY);
                write_message(fd[1], "MAP_FILE");
                if (fd1 == -1) {
                    write_message(fd[1], "ERROR");
                    break;
                }
                mapped_file_length = lseek(fd1, 0, SEEK_END);
                lseek(fd1, 0, SEEK_SET);
                mapped_file = mmap(0, mapped_file_length, PROT_READ, MAP_PRIVATE, fd1, 0);
                write_message(fd[1], "SUCCESS");
                break;
        }
    }
    finish:;
}
