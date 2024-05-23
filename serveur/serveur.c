#include "pse.h"

#define CMD "serveur"
#define VRAI 1
#define BUFFER_SIZE 1024

int variable = 0;  // Variable à mettre à jour

int main(int argc, char *argv[]) {
  short port;
  int ecoute, canal, ret;
  struct sockaddr_in adrEcoute, adrClient;
  unsigned int lgAdrClient;
  char buffer[BUFFER_SIZE] = {0};

  if (argc != 2) {
    fprintf(stderr, "usage: %s port\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  port = (short)atoi(argv[1]);

  printf("%s: creating a socket\n", CMD);
  ecoute = socket(AF_INET, SOCK_STREAM, 0);
  if (ecoute < 0)
    erreur_IO("socket");

  adrEcoute.sin_family = AF_INET;
  adrEcoute.sin_addr.s_addr = INADDR_ANY;
  adrEcoute.sin_port = htons(port);
  printf("%s: binding to INADDR_ANY address on port %d\n", CMD, port);
  ret = bind(ecoute, (struct sockaddr *)&adrEcoute, sizeof(adrEcoute));
  if (ret < 0)
    erreur_IO("bind");

  printf("%s: listening to socket\n", CMD);
  ret = listen(ecoute, 5);
  if (ret < 0)
    erreur_IO("listen");

  while (VRAI) {
    printf("%s: accepting a connection\n", CMD);
    lgAdrClient = sizeof(adrClient);
    canal = accept(ecoute, (struct sockaddr *)&adrClient, &lgAdrClient);
    if (canal < 0)
      erreur_IO("accept");

    printf("%s: adr %s, port %hu\n", CMD,
           stringIP(ntohl(adrClient.sin_addr.s_addr)), ntohs(adrClient.sin_port));

    while (read(canal, buffer, BUFFER_SIZE) > 0) {
      variable = atoi(buffer);
      printf("Variable mise à jour : %d\n", variable);
      memset(buffer, 0, BUFFER_SIZE);
    }

    if (close(canal) == -1)
      erreur_IO("fermeture canal");
  }

  if (close(ecoute) == -1)
    erreur_IO("fermeture ecoute");

  exit(EXIT_SUCCESS);
}

