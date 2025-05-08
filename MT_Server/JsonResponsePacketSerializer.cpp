#include "JsonResponsePacketSerializer.h"
#include <bitset>

//constructor
JsonResponsePacketSerializer::JsonResponsePacketSerializer()
{
}
//destructor
JsonResponsePacketSerializer::~JsonResponsePacketSerializer()
{
	this->buffer.clear();
}


std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(ErrorResponse er)
{
	std::vector<unsigned char> vec_char(er.mesagge.begin(), er.mesagge.end());

	return serializeAll(vec_char);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(LoginResponse lr)
{
	std::string status = "{status: " + std::to_string(lr.status) + "}";
	std::vector<unsigned char> vec_char(status.begin(), status.end());
	
	return serializeAll(vec_char);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(SignupResponse sr)
{
	std::string status = "{status: " + std::to_string(sr.status) + "}";
	std::vector<unsigned char> vec_char(status.begin(), status.end());

	return serializeAll(vec_char);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeAll(std::vector<unsigned char> vec_char)
{
	unsigned char code = static_cast<unsigned char>(LOG_CODE);
	std::vector<unsigned char> len(4);
	len[0] = (vec_char.size() >> 24) & 0xFF;
	len[1] = (vec_char.size() >> 16) & 0xFF;
	len[2] = (vec_char.size() >> 8) & 0xFF;
	len[3] = vec_char.size() & 0xFF;


	this->buffer.push_back(code);

	for (unsigned char c : len) {
		this->buffer.push_back(c);
	}

	for (unsigned char c : vec_char) {
		this->buffer.push_back(c);
	}

	return this->buffer;
}
