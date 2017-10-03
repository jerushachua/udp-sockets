#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

// UDP Client

int main(int argc, char *argv[])
{

  int sock;
  struct sockaddr_in sa;
  int bytes_sent;
  char buffer[200];
  char recbuffer[1024]; 
  ssize_t recfile; 
  socklen_t fromlen; 

  if (argc == 2){
    printf("The argument supplied is %s\n", argv[1]);
    strcpy(buffer, argv[1]);
  }else{
    printf("No filename given. ");
  }

  /* create an Internet, datagram, socket using UDP */
  sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (-1 == sock) {
      /* if socket failed to initialize, exit */
      printf("Error Creating Socket");
      exit(EXIT_FAILURE);
    }

  /* Zero out socket address */
  memset(&sa, 0, sizeof sa);

  /* The address is IPv4 */
  sa.sin_family = AF_INET;

   /* IPv4 adresses is a uint32_t, convert a string representation of the octets to the appropriate value */
  sa.sin_addr.s_addr = htonl(INADDR_ANY);

  /* sockets are unsigned shorts, htons(x) ensures x is in network byte order, set the port to 8080 */
  sa.sin_port = htons(8080);

  bytes_sent = sendto(sock, buffer, strlen(buffer), 0,(struct sockaddr*)&sa, sizeof sa);
  if (bytes_sent < 0) {
    printf("Error sending packet: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  int i; 
  while(recfile = recvfrom(sock, (void*)recbuffer, sizeof buffer, 0, (struct sockaddr*)&sa, &fromlen)){

    sprintf(recbuffer, "%s", recbuffer); 
    printf("%s", recbuffer);
    if(i%10000 == 0) printf("hullo"); i++; //not getting stuck here  
  }

  close(sock); /* close the socket */
  return 0;
}
