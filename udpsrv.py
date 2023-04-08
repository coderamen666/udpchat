import socket
import argparse

# Parse command-line arguments
parser = argparse.ArgumentParser()
parser.add_argument('-l', '--listen_port', type=int, default=12345,
                    help='UDP port number to listen on')
parser.add_argument('-r', '--rebroadcast_port', type=int, default=54321,
                    help='UDP port number to rebroadcast on')
parser.add_argument('-a', '--address', type=str,
                    default="0.0.0.0",
                    help='Internal DO NOT TOUCH')
args = parser.parse_args()

# Create a UDP socket for listening
listen_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Bind the socket to the specified listen port
listen_socket.bind((args.address, args.listen_port))

# Create a UDP socket for rebroadcasting
rebroadcast_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Create a dictionary to store the IP addresses that have sent packets
ip_addresses = {}

print("Listening at IP address {} on port {}; Rebroadcasting on port {}".format(socket.gethostbyname(socket.gethostname()), args.listen_port, args.rebroadcast_port))
# Loop indefinitely
while True:
    # Receive a packet
    data, address = listen_socket.recvfrom(1024)

    print("{} : {} : {}".format(data, address, ip_addresses))
    
    # Check if the IP address has already been stored
    if not(address[0] in ip_addresses):
        ip_addresses[address[0]] = True

    # Rebroadcast Packets
    for ip_address in ip_addresses:
        rebroadcast_socket.sendto(bytes("<{}>: {}".format(address[0], data.decode("utf-8")), "utf-8"), (ip_address, args.rebroadcast_port))
