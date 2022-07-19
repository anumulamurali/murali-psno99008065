#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#define SIZE 1024

void send_file(FILE *fp, int sockfd){
  int n;
  char data[SIZE] = {0};
 
  while(fgets(data, SIZE, fp) != NULL) {
    if (send(sockfd, data, sizeof(data), 0) == -1) {
      perror("[-]Error in sending file.");
      exit(1);
    }
    bzero(data, SIZE);
  }
}
 
int main(){
FILE *pf,*cf;
printf(" display all available files:\n");
 char command[50];
 char data[1024];
sprintf(command,"ls");
pf=popen(command,"r");
while(fgets(data,1024,pf)!=NULL)
{
printf("%s",data);

}
if(pclose(pf)!=0)
{
  fprintf(stderr,"Error:Failed to close\n");
}
printf("sending file to host:\n");
  char ip[150];
  int port;
  int e;
  printf("enter ip:");
  scanf("%s",ip);
  printf("enter port:");
  scanf("%d",&port);
  
 
  int sockfd;
  struct sockaddr_in server_addr;
  FILE *fp;
  char filename[150];
  printf("enter file name:");
  scanf("%s",filename);
 
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0) {
    perror("[-]Error in socket");
    exit(1);
  }
  printf("[+]Server socket created successfully.\n");
 
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = port;
  server_addr.sin_addr.s_addr = inet_addr(ip);
 
  e = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if(e == -1) {
    perror("[-]Error in socket");
    exit(1);
  }
 printf("[+]Connected to Server.\n");
 
  fp = fopen(filename, "r");
  if (fp == NULL) {
    perror("[-]Error in reading file.");
    exit(1);
  }
  send_file(fp, sockfd);
  printf("[+]File data sent successfully.\n");
 
  printf("[+]Closing the connection.\n");
  close(sockfd);
 
  return 0;
}
