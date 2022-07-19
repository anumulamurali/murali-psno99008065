#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <unistd.h>
#include <arpa/inet.h>
int main()
{
printf("displaying all wife devices:\n");
  FILE *pf,*cf;

 char command[1500];
 char data[1024];
 char essid[400];
 char pass[500];
 char ip[150];
 int port;
 int e;
sprintf(command,"iwlist wlp2s0 scan | grep ESSID");
pf=popen(command,"r");
while(fgets(data,1024,pf)!=NULL)
{
printf("%s",data);

}
if(pclose(pf)!=0)
{
  fprintf(stderr,"Error:Failed to close\n");
}
// connection part
printf("connecting to specified wife:\n");
 printf("eneter essid:");
 scanf("%s",essid);
 printf("enter password:");
 scanf("%s",pass);
sprintf(command,"nmcli dev wifi connect %s password %s",essid,pass);
pf=popen(command,"r");
while(fgets(data,1024,pf)!=NULL)
{
printf("%s",data);

}
if(pclose(pf)!=0)
{
  fprintf(stderr,"Error:Failed to close\n");
}
// find wlp name
printf("finding network interface name:\n");
sprintf(command,"ifconfig | grep ^wl | grep -o -E '\\w+' | grep ^w");
pf=popen(command,"r");
while(fgets(data,1024,pf)!=NULL)
{
printf("%s",data);

}
if(pclose(pf)!=0)
{
  fprintf(stderr,"Error:Failed to close\n");
}
// ipaddr part
printf("getting ip addr of system:\n");
 int n;
    struct ifreq ifr;
    char array[50];
    printf("enter the network interface name:");
    scanf("%s",array);
    n = socket(AF_INET, SOCK_DGRAM, 0);
    //Type of address to retrieve - IPv4 IP address
    ifr.ifr_addr.sa_family = AF_INET;
    //Copy the interface name in the ifreq structure
    strncpy(ifr.ifr_name , array , IFNAMSIZ - 1);
    ioctl(n, SIOCGIFADDR, &ifr);
    close(n);
    //display result
    printf("IP Address is %s - %s\n" , array , inet_ntoa(( (struct sockaddr_in *)&ifr.ifr_addr )->sin_addr) );
   
// scanning part for live host
printf("finding all live host:\n");
printf("enter ip address:");
scanf("%s",ip);
sprintf(command,"nmap -sn %s | grep 192",ip);
pf=popen(command,"r");
while(fgets(data,1024,pf)!=NULL)
{
printf("%s",data);

}
if(pclose(pf)!=0)
{
  fprintf(stderr,"Error:Failed to close\n");
}
// port scanning
printf("performing port scanning on selected network:\n");
printf("enter ip:");
 scanf("%s",ip);
sprintf(command,"nmap %s | grep open",ip);
pf=popen(command,"r");
while(fgets(data,1024,pf)!=NULL)
{
printf("%s",data);

}
if(pclose(pf)!=0)
{
  fprintf(stderr,"Error:Failed to close\n");
}
// making port active 
printf("making access to protected or closed port :\n");
 printf("enter ip:");
 scanf("%s",ip);
 printf("enter port:");
 scanf("%d",&port);
sprintf(command,"sudo ufw allow from %s to any port %d",ip,port);
pf=popen(command,"r");
while(fgets(data,1024,pf)!=NULL)
{
printf("%s",data);
}
if(pclose(pf)!=0)
{
  fprintf(stderr,"Error:Failed to close\n");
}
}
