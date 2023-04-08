import socket, argparse
from datetime import datetime

parser = argparse.ArgumentParser()
parser.add_argument('-p', '--port', type=int, default=12345,
			help='UDP port to listen on')
args = parser.parse_args()

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.bind(("0.0.0.0", args.port))

print(f"Listening on port {args.port}....")

try:
	while True:
		data, address = s.recvfrom(1024)
		byte_count = len(data)
		txt = data.decode("utf-8")
		addr, port = address
		now = datetime.now()
		current_time = now.strftime("%H:%M:%S")
		print(f"Received {byte_count} bytes from {addr}:{port} at {current_time}: {txt}")
except:
	s.close()
