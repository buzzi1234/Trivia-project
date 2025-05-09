#include "JsonResponsePacketSerializer.h"
#include <bitset>


//destructor
JsonResponsePacketSerializer::~JsonResponsePacketSerializer()
{
	this->buffer.clear();
}

/// <summary>
/// The function serialize the ErrorResponse struct into buffer
/// </summary>
/// <param name="er"> A struct that containe error message </param>
/// <returns> Buffer ( row of bits ) to the client </returns>
std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(Structs::ErrorResponse er)
{
	std::vector<unsigned char> vec_char(er.mesagge.begin(), er.mesagge.end());

	return serializeAll(vec_char, ERROR_CODE);
	
}

/// <summary>
/// The function serialize the LoginResponse struct into buffer
/// </summary>
/// <param name="lr"> A struct that containe statue num </param>
/// <returns> Buffer ( row of bits ) to the client </returns>
std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(Structs::LoginResponse lr)
{
	std::string status = "{status: " + std::to_string(lr.status) + "}";
	std::vector<unsigned char> vec_char(status.begin(), status.end());
	
	return serializeAll(vec_char, LOG_CODE);
}

/// <summary>
/// The function serialize the SigninResponse struct into buffer
/// </summary>
/// <param name="lr"> A struct that containe statue num </param>
/// <returns> Buffer ( row of bits ) to the client </returns>
std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(Structs::SignupResponse sr)
{
	std::string status = R"({"status" : )" + std::to_string(sr.status) + "}";
	std::vector<unsigned char> vec_char(status.begin(), status.end());

	return serializeAll(vec_char, SIGN_CODE);
}

/// <summary>
/// The function create a buffer that containe the code, length, msg
/// </summary>
/// <param name="vec_char"> buffer of the message </param>
/// <param name="code"> code of the message </param>
/// <returns> the complete buffer </returns>
std::vector<unsigned char> JsonResponsePacketSerializer::serializeAll(std::vector<unsigned char> vec_char, int code)
{
	unsigned char code_byte = static_cast<unsigned char>(code); //turn code into byte

	//turn length of msg into 4 byte 
	std::vector<unsigned char> len(4);
	len[0] = (vec_char.size() >> 24) & 0xFF;
	len[1] = (vec_char.size() >> 16) & 0xFF;
	len[2] = (vec_char.size() >> 8) & 0xFF;
	len[3] = vec_char.size() & 0xFF;


	this->buffer.push_back(code_byte);

	for (unsigned char c : len) {
		this->buffer.push_back(c);
	}

	for (unsigned char c : vec_char) {
		this->buffer.push_back(c);
	}

	return this->buffer;
}
