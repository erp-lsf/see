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
#define STARTING_AR_SIZE 1
#define AR_INCREASE_COEF 2

int split_string(char* string, char* delimiters, char** splits) {
  int splits_pos = 0;
  int splits_size = STARTING_AR_SIZE;
  int capture_length = 0;

  // splits = realloc(splits, sizeof(char*) * splits_size);
  char *capture;
  capture = strtok(string, delimiters);

  if(capture != NULL) {
    capture_length = strlen(capture);
    splits[splits_pos] = malloc((capture_length + 1) * sizeof(char));
    strncpy(splits[splits_pos], capture, capture_length + 1);
    splits_pos++;

    while((capture = strtok(NULL, delimiters)) != NULL) {
      capture_length = strlen(capture);
      splits[splits_pos] = malloc((capture_length + 1) * sizeof(char));
      strncpy(splits[splits_pos], capture, capture_length + 1);
      splits_pos++;

      if(splits_pos == splits_size) {
        printf("Grow array up\n");
        *splits = realloc(*splits, sizeof(char*) * splits_size * AR_INCREASE_COEF);
        splits_size = splits_size * AR_INCREASE_COEF;
        printf("Splits pos: %d\n", splits_pos);
        printf("Splits size after: %d\n", splits_size);
      }
    }
  }

  *splits = realloc(*splits, sizeof(char*) * splits_pos);

  return splits_pos;
}

int main(int argc, char *argv[]) {
  char** splits = malloc(sizeof(char*) * STARTING_AR_SIZE);
  char string[] = "Hello!\nI want to see the beautiful world\nthree strings";

  int count = split_string(string, "\n", splits);
  //printf("Count %d\n", count);
//  assert(count == 3);
 for(int i=0; i<count; i++) {
    printf("String %d: ", i);
    printf(splits[i]);
    printf("\n");
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
