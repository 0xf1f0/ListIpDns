This program prints list all host in a given subnet and checks if the hosts are up
    Usage: ./listIPDNS subnet_mask network_address
subnet_mask is the subnet mask
network_address is the network address or IP address

The program checks if the subnet_mask and network_address are valid
	-Displays a corresponding error message for all invalid cases
	e.g Invalid subnet_mask or network_address[IP] or both

The subnet mask if validated by converting the subnet_mask to unsigned long then generate all possible valid subnet mask as unsigned long
	-Compare the result and return a boolean (1 = True, 0 = False)

The Network address is validated by converting the IP to decimat format
	-Check if octet is between 0-255 using inet_pton()

If the network_address and subnet_mask are valid:

	Network address is recalculated regardless of user input
	- DO a bitwise AND of the subnet_mask and network_address
	
	Broadcast address is calculated by doing:
		Bitwise OR of the network and NOT(subnet_mask)
	
	Convert the subnet_mask from unsigned long to a decimal and multiply the result by -1, this will give us the number of host in the given subnet
	
	Convert the network_address from dotted decimal to network byte long
	Convert the network byte to host byte long; this is the network number
	
	Iterate over the number of host and add each number to the network number
	Convert each iteration to a dotted decimal format
	Each dotted decimal is the IP of the host on that particular subnet
	Display all the IP addressess
	Check if the host is avalaible 
		-Display the official host name
		-Check and display other DNS name associated with the host's IP address
	Display an error message if the host is down

	
What works?
	Everything
		-Network Address
		-Broadcast Adress
		-Number of host in the subnet
		-A listing of all host's IP addresses and their hostname/official name