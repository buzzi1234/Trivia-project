import socket
import json
import struct

SERVER_IP = "127.0.0.1"
SERVER_PORT = 8826
LOGIN_CODE = 1
SIGNUP_CODE = 2


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
        decoded = response[5:].decode('utf-8')
        parsed = json.loads(decoded)
        print("Server response:")
        print(json.dumps(parsed, indent=2, ensure_ascii=False))
        return parsed
    except Exception as e:
        print("Error parsing server response", e)
        print("Raw text from the server", response)
        return None


def run_tests():
    print("== test proper registration ==\n")
    sock1 = connect_to_server(SERVER_IP, SERVER_PORT)
    send_json_message(sock1, SIGNUP_CODE, {"username": "user_test", "password": "1234", "mail": "test@gmail.com"})
    sock1.close()

    print("== test double registration (same user) ==\n")
    sock2 = connect_to_server(SERVER_IP, SERVER_PORT)
    send_json_message(sock2, SIGNUP_CODE, {"username": "user_test", "password": "1234", "mail": "test@gmail.com"})
    sock2.close()

    print("== test connecting with a non-existent user ==\n")
    sock3 = connect_to_server(SERVER_IP, SERVER_PORT)
    send_json_message(sock3, LOGIN_CODE, {"username": "not_exists", "password": "1234"})
    sock3.close()

    print("== test proper connection ==\n")
    sock4 = connect_to_server(SERVER_IP, SERVER_PORT)
    send_json_message(sock3, LOGIN_CODE, {"username": "user_test", "password": "1234"})

    print("== test double login (same user again) ==\n")
    sock5 = connect_to_server(SERVER_IP, SERVER_PORT)
    send_json_message(sock5, LOGIN_CODE, {"username": "user_test", "password": "1234"})
    sock5.close()
    sock4.close()

    print("== test invalid usernames ==\n")
    invalid_username = ["", "a" * 300, "us!@#", " "]
    for uname in invalid_username:
        print(f"\n--testing with invalid username'{uname}'--")
        sock = connect_to_server(SERVER_IP, SERVER_PORT)
        send_json_message(sock, SIGNUP_CODE, {
            "username": uname,
            "password": "1234",
            "mail": "bad@mail.com"
        })
        sock.close()


def main():
    run_tests()


if __name__ == "__main__":
    main()
