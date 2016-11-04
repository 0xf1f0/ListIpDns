	#include <stdio.h>
	#include <netdb.h>
	#include <arpa/inet.h>

	#define MAX 128

	/* Function prototypes */
	void dotted_decimal();

	int main (int argc, char *argv[])
	{
		//struct hostent *hostPtr;
		
		//Check if the user entered the right number of input
		if(argc != 3)
		{
			printf("Usage: %s Subnet_Mask Network_Addr", argv[0]);		
			return -1;
		}
		
		uint32_t net_ip;			//network/IP address in 32-bit binary
		uint32_t subnet_mask;		//subnet mask in 32-bit binary
		uint32_t x;
		uint32_t y;
		
		char *addr_ptr;		
		
		subnet_mask = inet_addr(argv[1]); //Convert dotted decimal subnet mask to binary
		net_ip = inet_addr(argv[2]); //Convert dotted decimal network/IP addr to binary
		
		/* 
		Validate the subnet_mask by doing a bitwise NOR of the subnet mask; call it x
		Add 1 to x; call it y
		Do bitwise AND of x and y;
		If TRUE, this will return 32-bit 0's
		else FALSE	
		*/
		x = ~ subnet_mask; 		//bitwise NOR of the subnet mask
		printf("%d\n", x);
		y = x + 1;				//2's complement of x
		printf("%d\n", y);
		if(x & y != 00000000000000000000000000000000)
			printf("Subnet mask '%s' is invalid, try a valid subnet mask/n", subnet_mask);
		dotted_decimal(subnet_mask, net_ip);	
		return 0;
	}

	/*Do a bitwise AND of the subnet mask and network/IP address to find the network address.
	This may seems redundant at first, but user cant't be trusted to input a valid network address.
	Thus, we calcualte the network address and work with the result.
	*/

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
