using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;

namespace Client_Server_Trivia
{
    class MessageBuilder
    {
        public static byte[] BuildJsonMessage(int code, string payload)
        {
            // 1. Encode the payload string to UTF-8
            byte[] jsonBytes = Encoding.UTF8.GetBytes(payload);

            // 2. Get length of payload
            int msgLength = jsonBytes.Length;

            // 3. Build header: 1 byte for code, 4 bytes for length (big-endian)
            byte[] header = new byte[5];
            header[0] = (byte)(code & 0xFF); // use only lowest byte of int

            header[1] = (byte)((msgLength >> 24) & 0xFF);
            header[2] = (byte)((msgLength >> 16) & 0xFF);
            header[3] = (byte)((msgLength >> 8) & 0xFF);
            header[4] = (byte)(msgLength & 0xFF);

            // 4. Combine header + payload
            byte[] message = new byte[header.Length + jsonBytes.Length];
            Buffer.BlockCopy(header, 0, message, 0, header.Length);
            Buffer.BlockCopy(jsonBytes, 0, message, header.Length, jsonBytes.Length);

            return message;
        }

        public static int GetStatus(string json)
        {
            var jsonDoc = JsonDocument.Parse(json);

            return jsonDoc.RootElement.GetProperty("status").GetInt32();
        }
    }
}
