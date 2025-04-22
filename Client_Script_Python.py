import socket

SERVER_IP = "127.0.0.1"
SERVER_PORT = 8826


def is_valid_port(port):
    return 1024 <= port <= 65535


if not is_valid_port(SERVER_PORT):
    print("Error: Invalid port number (must be between 1024 and 65535)")
    exit(1)

try:
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect((SERVER_IP, SERVER_PORT))
    print(f"You have connected to the server {SERVER_IP}:{SERVER_PORT}")

    server_msg = sock.recv(1024).decode()
    print("The server sent:", server_msg[:5])

    if server_msg[:5] == "Hello":
        msg = "Hello"
        sock.sendall(msg.encode())
        print("Hello response was sent to the server")

    sock.close()

except Exception as e:
    print("Error connecting or communicating with the server:", e)
