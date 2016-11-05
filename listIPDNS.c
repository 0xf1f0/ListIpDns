#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX 128

/* Function prototypes */
bool isValidIP(char *);
bool isValidMask(char *);
void dotted_decimal();

int main (int argc, char *argv[])
{
    struct in_addr net_mask, net_ip;

    //Check if the user entered the right number of input
    if(argc != 3)
    {
        printf("Usage: %s Subnet_Mask Network_Address\n", argv[0]);
        return -1;
    }

    //Validate the Subnet mask address
    else if (isValidMask(argv[1]) == 0)
    {
        printf("Invalid Subnet Mask\n");
        return -1;
    }

    //Validate the Network/IP address
    else if (isValidIP(argv[2]) == 0)
    {
        printf("Invalid IP address\n");
        return -1;
    }

    else if (isValidMask(argv[1]) == 0 && isValidIP(argv[2]) == 0)
    {
        printf("Invalid Subnet mask and IP address\n");
        return -1;
    }
    else
        printf("Valid Input\n");

    return 0;
}

//Validate the network/IP address
/*  Convert the IP address to a decimal format "ddd.ddd.ddd.ddd"
    which checks if the "ddd" is between 0-255
*/
bool isValidIP(char *ipAddr)
{
    struct sockaddr_in sin;
    int ans = inet_pton(AF_INET, ipAddr, &(sin.sin_addr));
    return ans != 0; //1 = TRUE, 0 = FALSE
}


//Validate the subnet mask from input
/*  Convert the subnet mask to decimal format
    Generate possible valid subnet mask in decimal
    Compare with user input
    Return 1 if found
    else return 0
*/
bool isValidMask(char *pt2mask)
{
    unsigned long net_mask, mask, subnet_mask, i;
    unsigned int ans = 0;
    struct in_addr netmask;
    subnet_mask = inet_addr(pt2mask);       //Convert dotted decimal subnet mask to network byte
    mask = inet_aton(pt2mask, &netmask);
    net_mask = ntohl(netmask.s_addr);       //Network byte to long Host byte order
    printf("HEX: %x\n", net_mask );
    printf("Subnet mask in host byte/decimal: %lu\n", net_mask);

    for(i = -1; i > 0; i--)
    {
        if(-(i & -i) == i && mask == i)
        {
            ans = 1;
            break;
        }
    }
    return ans;
}


//Convert binary IP address to dotted decimal
//**This will come in handy later**
void dotted_decimal(uint32_t subnet, uint32_t addr)
{
    struct in_addr* ip;
    uint32_t bin_ip;
    bin_ip = (addr & subnet);	//Bitwise AND operation of network addr and subnet mask
    ip = (struct in_addr *)&bin_ip;
    printf("The network address in dotted decimal: %s\n", inet_ntoa(*ip));
}
