	#include <stdio.h>
	#include <netdb.h>
	#include <arpa/inet.h>

	#define MAX 128
	/* Function prototypes */
	void dotted_decimal();

	int main (int argc, char *argv[])
	{
		if(argc != 3)
		{
			printf("Usage: %s Subnet_Mask Network_Addr", argv[0]);		
			return -1;
		}
		
		uint32_t net_ip;				//network/IP address in 32-bit long
		uint32_t subnet_mask;			//subnet mask in 32-bit long
		char *octet1;					//First octet of the subnet_mask
		char *octet2	;				//Second octet of the subnet_mask
		char *octet3;					//Third octet of the subnet_mask
		char *octet4;					//Fourth octet of the subnet_mask
		const char *valid_subnet[8];	//Array of valid subnet values
		valid_subnet[0] = 
		subnet_mask = inet_addr(argv[1]); //Convert dotted decimal subnet mask to binary
		net_ip = inet_addr(argv[2]); //Convert dotted decimal network/IP addr to binary
		
		//Split the subnet mask into 4 octets(tokens) and compare to valid subnet values
		octet1 = strtok(argv[1], ".");
		octet2 = strtok(argv[1], ".");
		octet3 = strtok(argv[1], ".");
		octet4 = strtok(argv[1], NULL);
		
				
		
		
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
		struct in_addr* ip;			//Pointer to the in_addr structure
		uint32_t bin_ip;
		bin_ip = (addr & subnet);	//Bitwise AND operation of network addr and subnet mask
		ip = (struct in_addr *)&bin_ip;
		printf("The network address in dotted decimal: %s\n", inet_ntoa(*ip));
	}
