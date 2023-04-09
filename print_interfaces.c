/*
 * author: jseroczy
 *
 * description: program uisng libpcap to print all
 * comunication interfaces located on the system
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <pcap.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void print_interfaces(pcap_if_t *inter)
{
        printf("Interfaces on the system:\n");

        while(inter)
        {
                printf("\t %s\n", inter->name);
                inter = inter->next;
        }

}


int main(int argc, char **argv)
{
        char errbuf[PCAP_ERRBUF_SIZE];
        char *dev;

        /* ask pcap to find a valid device for use to sniff on */
        pcap_if_t *interfaces;
        if(pcap_findalldevs(&interfaces, errbuf) == -1)
        {
                printf("%s\n",errbuf);
                exit(EXIT_FAILURE);
        }

        print_interfaces(interfaces);
        return 0;
}
