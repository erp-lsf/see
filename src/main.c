#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <assert.h>

#define PORTNUM 2300
#define BUF_SIZE 1024
#define STARTING_AR_SIZE 2
#define AR_INCREASE_COEF 2

int split_string(char *string, char *delimiters, char ***splits) {
    int splits_pos = 0;
    int splits_size = STARTING_AR_SIZE;

    *splits = realloc(*splits, sizeof(*splits) * splits_size);
    char *capture;
    capture = strtok(string, delimiters);

    if (capture != NULL) {
        (*splits)[splits_pos] = strdup(capture);
        splits_pos++;

        capture = strtok(NULL, delimiters);
        while (capture != NULL) {
            if (splits_pos == splits_size) {
                //printf("Grow array up\n");
                *splits = realloc(*splits, sizeof(*splits) * splits_size * AR_INCREASE_COEF);
                splits_size = splits_size * AR_INCREASE_COEF;
                //printf("Size after: %d\n", splits_size);
            }

            //printf("Splits pos at start of cycle: %d\n", splits_pos);
            (*splits)[splits_pos] = strdup(capture);
            splits_pos++;
            //printf("Splits pos at end of cycle: %d\n", splits_pos);
            //printf("Size at the end of the cycle: %d\n", splits_size);

            capture = strtok(NULL, delimiters);
        }
    }

    *splits = realloc(*splits, sizeof(*splits) * splits_pos);

    return splits_pos;
}


int main(int argc, char *argv[]) {
    char **splits = NULL;
    char string[] = "1 string\n2 string\n3 string\n4 string\n5 string\n6 string\n7 string\n8 string";
    char *delimiters = "\n";
    int count = split_string(string, delimiters, &splits);

    printf("Count %d\n", count);
//  assert(count == 3);
    for (int i = 0; i < count; i++) {
        printf("String %d: \"%s\"\n", i, splits[i]);
        free(splits[i]);
    }
    free(splits);
}

/*
int main(int argc, char *argv[])
{
    char* msg = "Hello World !\n";
  
    struct sockaddr_in dest; // socket info about the machine connecting to us
    struct sockaddr_in serv; // socket info about our server
    int mysocket;            // socket used to listen for incoming connections
    socklen_t socksize = sizeof(struct sockaddr_in);

    memset(&serv, 0, sizeof(serv));           // zero the struct before filling the fields
    serv.sin_family = AF_INET;                // set the type of connection to TCP/IP
    serv.sin_addr.s_addr = htonl(INADDR_ANY); // set our address to any interface
    serv.sin_port = htons(PORTNUM);           // set the server port number 

    mysocket = socket(AF_INET, SOCK_STREAM, 0);
  
    // bind serv information to mysocket
    bind(mysocket, (struct sockaddr *)&serv, sizeof(struct sockaddr));

    // start listening, allowing a queue of up to 1 pending connection
    listen(mysocket, 1);
    int consocket = accept(mysocket, (struct sockaddr *)&dest, &socksize);
  
    while(consocket)
    {
        printf("Incoming connection from %s - sending welcome\n", inet_ntoa(dest.sin_addr));

        int size;
        char read_str[256] = {0};
        size = read(consocket, read_str, BUF_SIZE);

        send(consocket, read_str, strlen(read_str), 0); 
        close(consocket);
        consocket = accept(mysocket, (struct sockaddr *)&dest, &socksize);
    }

    close(mysocket);
    return EXIT_SUCCESS;
}
*/
