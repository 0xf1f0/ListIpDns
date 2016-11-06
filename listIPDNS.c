#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


/* Function prototypes */
bool isValidIP(const char *);
bool isValidMask(const char *);
const char *networkAddr(unsigned long, unsigned long);
const char *broadcastAddr(unsigned long, unsigned long);
int hostCount(const char *);


int main (int argc, char *argv[])
{
    unsigned long net_mask, net_ip;
    int count = 0; //How many host?

    //Check if the user entered the right number of input
    if(argc != 3)
    {
        printf("Usage: %s Subnet_Mask Network_Address\n", argv[0]);
        exit(1);
    }

    int validMask = isValidMask(argv[1]);
    int validIP = isValidIP(argv[2]);

    if(validMask == 0 && validIP == 0)
    {
        fprintf(stderr, "Invalid subnet mask and IP\n");
        return -1;
    }
    else if(validMask == 0 && validIP == 1)
    {
        fprintf(stderr, "Invalid subnet mask\n");
        return -1;
    }
    else if(validMask == 1 && validIP == 0)
    {
        fprintf(stderr, "Invalid IP\n");
        return -1;
    }
    printf("Valid Input... MASK: %d IP: %d\n", validMask, validIP);

    net_mask= inet_addr(argv[1]);       //Convert dotted decimal subnet mask to binary
    net_ip = inet_addr(argv[2]);        //Convert dotted decimal network/IP addr to binary
    count = hostCount(argv[1]);
    printf("Network Address: %s\n", networkAddr(net_mask, net_ip));
    printf("Broadcast Address: %s\n", broadcastAddr(net_mask, net_ip));
    printf("Number of Host: %d\n", count);

    return 0;
}

//Validate the network/IP address
/*  Convert the IP address to a decimal format "ddd.ddd.ddd.ddd"
    which checks if the "ddd" is between 0-255
*/
bool isValidIP(const char *ipAddr)
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
bool isValidMask(const char *ptr2mask)
{
    unsigned long net_mask, mask, subnet_mask;
    unsigned int i, ans = 0;
    struct in_addr netmask;
    subnet_mask = inet_addr(ptr2mask);       //Convert dotted decimal subnet mask to network byte
    mask = inet_aton(ptr2mask, &netmask);
    net_mask = ntohl(netmask.s_addr);       //Network byte to long Host byte order
    //printf("DEC: %d\n", -(net_mask));
    printf("Subnet mask in host byte/decimal: %lu\n", net_mask);
    for(i = -1; i > 0; i--)
    {
        if(-(i & -i) == i && net_mask == i)
        {
            ans = 1;
            break;
        }
    }
    return ans;
}

/*Do a bitwise AND of the subnet mask and network/IP address to find the network address.
This may seems redundant at first, but user cant't be trusted to input a valid network address.
Thus, we calcualte the network address and work with the result.
*/

//Convert binary IP address to dotted decimal
//**This will come in handy later**
const char *networkAddr(unsigned long subnet, unsigned long addr)
{
    struct in_addr* ip;
    unsigned long bin_ip;
    bin_ip = (addr & subnet);	//Bitwise AND operation of network addr and subnet mask
    ip = (struct in_addr *)&bin_ip;
    printf("The network address in dotted decimal: %s\n", inet_ntoa(*ip));
    return (inet_ntoa(*ip));
}

/*Do a bitwise OR of the NOT(subnet mask) and network/IP address to find the network address.
Thus, we calculate the broadcast address.
*/
const char *broadcastAddr(unsigned long subnet, unsigned long addr)
{
    struct in_addr* ip;
    unsigned long bin_ip;
    bin_ip = (addr | ~subnet);	            //Bitwise OR operation of network addr and subnet mask
    ip = (struct in_addr *)&bin_ip;
    printf("The broadcast address in dotted decimal: %s\n", inet_ntoa(*ip));
    return (inet_ntoa(*ip));
}

//Calculate the number of host using the subnet mask
int hostCount(const char *ptr2mask)
{
    unsigned long net_mask, mask, subnet_mask;
    unsigned int i, ans = 0;
    struct in_addr netmask;
    subnet_mask = inet_addr(ptr2mask);       //Convert dotted decimal subnet mask to network byte
    mask = inet_aton(ptr2mask, &netmask);
    net_mask = ntohl(netmask.s_addr);       //Network byte to long Host byte order
    return (-(net_mask));
}
