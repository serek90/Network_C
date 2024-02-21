#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void
ip_int_to_string(char *ip_str, int ip_int)
{
        int ip_arr[4];
        ip_arr[0] = ((ip_int & (0xFF000000)) >> 24);
        ip_arr[1] = ((ip_int & (0x00FF0000)) >> 16);
        ip_arr[2] = ((ip_int & (0x0000FF00)) >> 8);
        ip_arr[3] = ip_int & (0x000000FF);
        sprintf(ip_str,"%d.%d.%d.%d", ip_arr[0], ip_arr[1], ip_arr[2], ip_arr[3]);
}

int
ip_string_to_int(char *ip_str)
{
        int ip_arr[4];
        sscanf(ip_str,"%d.%d.%d.%d", &ip_arr[0], &ip_arr[1], &ip_arr[2], &ip_arr[3]);
        return (ip_arr[0] << 24) + (ip_arr[1] << 16)+ (ip_arr[2] << 8) + ip_arr[3];
}

void
get_broadcast_address(char * ip_addr, int mask, char *b_addr)
{
        /* validate input */

        int num = ip_string_to_int(ip_addr);

        /* create mask bit representation as int */
        int res = 0;
        for(int i = 0; i < 32 - mask; i++)
                res |= (1 << i);

        num |= res;
        ip_int_to_string(b_addr, num);
}

void
get_network_address(char * ip_addr, int mask, char *n_addr)
{
        /* validate input */

        int num = ip_string_to_int(ip_addr);

        /* create mask bit representation as int */
        int res = 0;
        for(int i = 31; i > mask; i--)
                res |= (1 << i);

        num &= res;
	ip_int_to_string(n_addr, num);
}


int main(int argc, char **argv)
{

	if(argc != 2)
	{
		printf("Wrong argument should be ip/net_mask f.e 192.168.100.2/24\n");
		return 1;
	}
	char ip_addr[20];
	int mask;

	sscanf(argv[1],"%s/%d", ip_addr, &mask);
	char b_addr[20];
	get_broadcast_address(ip_addr, 24, b_addr);
	char n_addr[20];
	get_network_address(ip_addr, 24, n_addr);

	printf("\nIP address is: %s/\%d\n", ip_addr, mask);
	printf("Broadcast address is: %s\n", b_addr);
	printf("Network address is: %s\n\n", n_addr);

	return 0;
}
