#include "pse.h"

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "usage: %s hostname port\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  int sock = 0;
  struct sockaddr_in serv_addr;
  char buffer[BUFFER_SIZE] = {0};
  int port = atoi(argv[2]);

  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(port);

  if (inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) <= 0) {
    perror("Invalid address/ Address not supported");
    close(sock);
    exit(EXIT_FAILURE);
  }

  if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    perror("Connection Failed");
    close(sock);
    exit(EXIT_FAILURE);
  }

  printf("Connecté au serveur %s sur le port %d.\n", argv[1], port);
  printf("Entrez un entier : ");
  while (fgets(buffer, BUFFER_SIZE, stdin) != NULL) {
    send(sock, buffer, strlen(buffer), 0);
    printf("Entrez un entier : ");
    memset(buffer, 0, BUFFER_SIZE);
  }

  close(sock);
  return 0;
}

