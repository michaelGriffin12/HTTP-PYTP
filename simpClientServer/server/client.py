import socket

def main():
	sHOST = "127.0.0.1"
	iPORT = 1337
	sfd = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	sfd.connect((sHOST, iPORT))
	sfd.send(b"Hello world!\n\n")
	sIbuf = sfd.recv(1024)
	print(sIbuf)
	sfd.shutdown(socket.SHUT_RDWR)
	sfd.close()

main()
