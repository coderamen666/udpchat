all: udpsend udprecv
udpsend: udpsend.c
	cc -o udpsend udpsend.c
udprecv: udprecv.c
	cc -o udprecv udprecv.c

