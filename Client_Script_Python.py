import socket
import json
import struct


SERVER_IP = "127.0.0.1"
SERVER_PORT = 8826


def is_valid_port(port):
    return 1024 <= port <= 65535


def build_json_message(code, payload):
    """
     [1 byte code][4 bytes length][JSON payload]
    """
    json_bytes = json.dumps(payload).encode('utf-8')
    msg_length = len(json_bytes)
    header = struct.pack('!BI', code, msg_length)
    return header + json_bytes


def connect_to_server(ip, port):
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect((ip, port))
    print(f"You have connected to the server{ip}:{port}")
    return sock


def send_json_message(sock, code, data):
    message = build_json_message(code, data)
    sock.sendall(message)
    print(f"send with code{code}")

    response = sock.recv(4096)
    try:
        decoded = response.decode('utf-8')
        parsed = json.loads(decoded)
        print("Server response:")
        print(json.dumps(parsed, indent=2, ensure_ascii=False))
    except Exception as e:
        print("Error parsing server response", e)
        print("Raw text from the server", response)


def main():
    if not is_valid_port(SERVER_PORT):
        print("Error")
        return

    try:
        sock = connect_to_server(SERVER_IP, SERVER_PORT)

        login_info = {"username": "user1", "password": "1234"}
        send_json_message(sock, 1, login_info)
        signup_info = {"username": "user1", "password": "1234", "mail": "user1@gmail.com"}
        send_json_message(sock, 2, signup_info)

        sock.close()

    except Exception as e:
        print("Error while communicating with the server ", e)


if __name__ == "__main__":
    main()
