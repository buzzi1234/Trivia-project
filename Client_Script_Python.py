import socket
import json
import struct

SERVER_IP = "127.0.0.1"
SERVER_PORT = 8826

# Request codes
LOGIN_CODE = 1
SIGNUP_CODE = 2

# Response codes
SUCCESS_LOGIN = 1
SUCCESS_SIGNUP = 2
ERROR_CODE = 3


def build_json_message(code, payload):
    json_bytes = json.dumps(payload).encode('utf-8')
    msg_length = len(json_bytes)
    header = struct.pack('!BI', code, msg_length)
    return header + json_bytes


def connect_to_server(ip, port):
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect((ip, port))
    print(f"You have connected to the server {ip}:{port}")
    return sock


def send_json_message(sock, code, data):
    message = build_json_message(code, data)
    sock.sendall(message)
    print(f"[CLIENT] Sent request with code {code} and data {data}")

    header = sock.recv(5)
    if len(header) < 5:
        print("Error: Incomplete header received")
        return None

    _, msg_length = struct.unpack('!BI', header)
    response = sock.recv(msg_length)

    try:
        decoded = response.decode('utf-8')
        parsed = json.loads(decoded)
        print("Server response:")
        print(json.dumps(parsed, indent=2, ensure_ascii=False))
        return parsed.get("status")
    except Exception as e:
        print("Error parsing server response:", e)
        print("Raw response:", response)
        return None


def assert_result(status, expected, test_name):
    if status == expected:
        print(f"{test_name}: Passed\n")
    else:
        print(f"{test_name}: Failed (Expected {expected}, got {status})\n")


def run_tests():
    print("== Test 1 - Proper registration ==\n")
    sock1 = connect_to_server(SERVER_IP, SERVER_PORT)
    status = send_json_message(sock1, SIGNUP_CODE, {
        "username": "user_test",
        "password": "1234",
        "mail": "test@gmail.com"
    })
    assert_result(status, SUCCESS_SIGNUP, "Test 1 - Proper registration")
    sock1.close()

    print("== Test 2 - Double registration (same user) should fail ==\n")
    sock2 = connect_to_server(SERVER_IP, SERVER_PORT)
    status = send_json_message(sock2, SIGNUP_CODE, {
        "username": "user_test",
        "password": "1234",
        "mail": "test@gmail.com"
    })
    assert_result(status, ERROR_CODE, "Test 2 - Double registration should fail")
    sock2.close()

    print("== Test 3 - Login with non-existent user should fail ==\n")
    sock3 = connect_to_server(SERVER_IP, SERVER_PORT)
    status = send_json_message(sock3, LOGIN_CODE, {
        "username": "not_exists",
        "password": "1234"
    })
    assert_result(status, ERROR_CODE, "Test 3 - Login non-existent user should fail")
    sock3.close()

    print("== Test 4 - Proper login ==\n")
    sock4 = connect_to_server(SERVER_IP, SERVER_PORT)
    status = send_json_message(sock4, LOGIN_CODE, {
        "username": "user_test",
        "password": "1234"
    })
    assert_result(status, SUCCESS_LOGIN, "Test 4 - Proper login")

    print("== Test 5 - Double login (same user again) should fail ==\n")
    sock5 = connect_to_server(SERVER_IP, SERVER_PORT)
    status = send_json_message(sock5, LOGIN_CODE, {
        "username": "user_test",
        "password": "1234"
    })
    assert_result(status, ERROR_CODE, "Test 5 - Double login should fail")
    sock5.close()
    sock4.close()

    #print("== Test 6 - Login again after disconnecting should work ==\n")
    #sock6 = connect_to_server(SERVER_IP, SERVER_PORT)
    #status = send_json_message(sock6, LOGIN_CODE, {
    #    "username": "user_test",
    #    "password": "1234"
    #})
    #assert_result(status, SUCCESS_LOGIN, "Test 6 - Login after disconnecting should work")
    #sock6.close()

    #print("== Test 6 - Invalid usernames should fail ==\n")
    #invalid_usernames = ["", "a" * 300, "us!@#", " "]
    #for uname in invalid_usernames:
     #   print(f"-- Testing invalid username: '{uname}' --")
      #  sock = connect_to_server(SERVER_IP, SERVER_PORT)
       # status = send_json_message(sock, SIGNUP_CODE, {
        #    "username": uname,
         #   "password": "1234",
          #  "mail": "bad@mail.com"
      #  })
       # assert_result(status, ERROR_CODE, "Test 6 - Invalid username should fail")
        #sock.close()


def main():
    run_tests()


if __name__ == "__main__":
    main()
