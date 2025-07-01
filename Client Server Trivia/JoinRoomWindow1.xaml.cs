using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace Client_Server_Trivia
{
    /// <summary>
    /// Interaction logic for JoinRoomWindow1.xaml
    /// </summary>
    public partial class JoinRoomWindow1 : Window
    {
        public object ErrorMessageTextBlock { get; private set; }

        public JoinRoomWindow1()
        {
            InitializeComponent();
        }

        private void JoinRoom_Click(object sender, RoutedEventArgs e)
        {
            string roomName = RoomNameTextBox.Text.Trim();
            JoinRoomRequest joinRoomRequest = new JoinRoomRequest();
            joinRoomRequest.roomId = GetId(roomName);

            TcpClient client = (TcpClient)(Application.Current.Properties["client"]);
            NetworkStream stream = (NetworkStream)(Application.Current.Properties["stream"]);

            string json = JsonSerializer.Serialize<JoinRoomRequest>(joinRoomRequest);

            byte[] data = MessageBuilder.buildMessage(15, json);
            stream.Write(data, 0, data.Length);

            byte[] buffer = new byte[1024];
            int bytesRead = stream.Read(buffer, 0, buffer.Length);

            string res = Encoding.UTF8.GetString(buffer, 5, bytesRead - 5);
            int status = MessageBuilder.GetStatus(res);

            if (status == 15)
            {
                MessageBox.Show($"You had joined the Room {roomName}");
            }
            


        }
        private void CloseButton_Click(object sender, RoutedEventArgs e)
        {
            Application.Current.Shutdown(); // Close the application
        }
        private void BackButton_Click(object sender, RoutedEventArgs e)
        {
            LobbyWindow lobbyWindow = new LobbyWindow();
            lobbyWindow.Show();
            this.Close();
        }

        private int GetId(string roomName)
        {
            TcpClient client = (TcpClient)(Application.Current.Properties["client"]);
            NetworkStream stream = (NetworkStream)(Application.Current.Properties["stream"]);

            //send message
            byte[] data = MessageBuilder.buildMessage(11, "{}");
            stream.Write(data, 0, data.Length);

            byte[] buffer = new byte[1024];
            int bytesRead = stream.Read(buffer, 0, buffer.Length);

            string res = Encoding.UTF8.GetString(buffer, 5, bytesRead - 5);
            int status = MessageBuilder.GetStatus(res);
            if (status == 11)
            {
                int i = 1;
                var jsonDoc = JsonDocument.Parse(res);
                var jsonRoomData = JsonDocument.Parse(jsonDoc.RootElement.GetProperty("room1").GetString());
                return jsonRoomData.RootElement.GetProperty("id").GetInt32();
            }
            return 1;
        }
        
    }
    
    public class JoinRoomRequest
    { 
        public int roomId { get; set; }
    }

}
