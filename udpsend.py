import socket, argparse
from datetime import datetime

parser = argparse.ArgumentParser()
parser.add_argument('-a', '--address', type=str,
                    default="0.0.0.0",
                    help='IP Address to connect to')
parser.add_argument('-p', '--port', type=int, default=12345,
			help='UDP port to send on')
args = parser.parse_args()

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

print(f"Sending to {args.address} on port {args.port}....")

try:
	while True:
		msg = input("$ ")
		msg = bytes(msg, "utf-8")
	
		now = datetime.now()
		current_time = now.strftime("%H:%M:%S")
	
		s.sendto(msg, (args.address, args.port))
		print(f"Message sent successfully at {current_time}.")
except:
	s.close()
