#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080
#define BUFFER_SIZE 1024

void *sendMessage(void *vargp);
void *recvMessage(void *client_fd_ptr);

pthread_mutex_t close_exit_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t close_client_mutex = PTHREAD_MUTEX_INITIALIZER;
int close_client = 0;
int close_exit = 0;

void close_client_signal() {
  close_client = 1;
  pthread_mutex_lock(&close_client_mutex);
}

void open_client_signal() {
  close_client = 0;
  pthread_mutex_unlock(&close_client_mutex);
}

void close_exit_signal() {
  close_exit = 1;
  pthread_mutex_lock(&close_exit_mutex);
}

int main() {

  int server_fd, client_fd, addr_len;
  struct sockaddr_in server_addr, client_addr;
  char recv_buffer[BUFFER_SIZE];

  /***************************************************************************/
  /*                               Start socket */
  /***************************************************************************/
  server_fd = socket(AF_INET, SOCK_STREAM, 0);

  if (server_fd == -1) {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(PORT);

  if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) ==
      -1) {
    perror("bind");
    exit(EXIT_FAILURE);
  }

  while (1) {
    if (listen(server_fd, 1) == -1) {
      perror("listen");
      exit(EXIT_FAILURE);
    }
    addr_len = sizeof(client_addr);

    printf("Server listening for connection...\n");

    /***************************************************************************/
    /*                      Create client file descriptor */
    /***************************************************************************/
    client_fd = accept(server_fd, (struct sockaddr *)&client_addr,
                      (socklen_t *)&addr_len);

    printf("Server connected to client\n");
    open_client_signal();

    if (client_fd == -1) {
      perror("accept");
      exit(EXIT_FAILURE);
    }

    pthread_t send_thread;
    pthread_t recv_thread;

    pthread_create(&send_thread, NULL, &sendMessage, (void *)&client_fd);
    pthread_create(&recv_thread, NULL, &recvMessage, (void *)&client_fd);

    while (1) {
      if (close_exit == 1 | close_client == 1) {
        break;
      }
    }

    close(client_fd);
    pthread_cancel(send_thread);
    pthread_cancel(recv_thread);

    if (close_exit == 1) {
      break;
    }
  }

  close(server_fd);
  printf("Closed connection.\n");

  return 0;
}

void *recvMessage(void *client_fd_ptr) {
  int client_fd = *((int *)client_fd_ptr);
  char recv_buffer[BUFFER_SIZE];

  while (1) {
    /*************************************************************************/
    /*       Read new content from client file descriptor into a buffer */
    /*************************************************************************/

    if (close_exit) {
      break;
    }

    // Check for data or disconnection from the client
    int bytes_received = recv(client_fd, recv_buffer, BUFFER_SIZE, 0);
    /* read(client_fd, recv_buffer, BUFFER_SIZE); */

    if (bytes_received == 0) {
      printf("Client disconnected.\n");
      close(client_fd);
      close_client_signal();
      break; // Close the server
    } else {
      printf("Client: %s", recv_buffer);
      memset(recv_buffer, 0, BUFFER_SIZE);
    }
  }

  pthread_exit(NULL);
}

void *sendMessage(void *server_fd_ptr) {
  int server_fd = *((int *)server_fd_ptr);
  char send_buffer[BUFFER_SIZE];

  while (1) {
    /*************************************************************************/
    /*           Get message from standard input and send to server */
    /*************************************************************************/

    if (strcmp(send_buffer, "exit") == 0 ||
        strcmp(send_buffer, "exit\n") == 0) {
      close_exit_signal();
      break;
    }

    // Send a message to the server
    fgets(send_buffer, BUFFER_SIZE, stdin);
    int res = send(server_fd, send_buffer, strlen(send_buffer), 0);

    if (res == -1) {
      perror("send");
      exit(EXIT_FAILURE);
    }

    memset(send_buffer, 0, BUFFER_SIZE);
  }

  pthread_exit(NULL);
}