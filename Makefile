all: udpsend.c udprecv.c
	cc -o udpsend udpsend.c
	cc -o udprecv udprecv.c

