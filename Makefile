
all: listIPDNS.c
	gcc -o listIPDNS listIPDNS.c

clean: 
	$(RM) listIPDNS
