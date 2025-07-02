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
            Loaded += PersonalStatisticsWindow_Loaded;
        }

        private async void PersonalStatisticsWindow_Loaded(object sender, RoutedEventArgs e)
        {
            TcpClient client = (TcpClient)(Application.Current.Properties["client"]);
            NetworkStream stream = (NetworkStream)(Application.Current.Properties["stream"]);

            byte[] data = MessageBuilder.buildMessage(11, "{}");
            await stream.WriteAsync(data, 0, data.Length); // ✅ Non-blocking

            byte[] buffer = new byte[1024];
            int bytesRead = await stream.ReadAsync(buffer, 0, buffer.Length); // ✅ Non-blocking

            string res = Encoding.UTF8.GetString(buffer, 5, bytesRead - 5);
            int status = MessageBuilder.GetStatus(res);

            if (status == 11)
            {
                string room = "room";
                var jsonDoc = JsonDocument.Parse(res);
                for (int i = 1; i < 11; i++)
                {
                    try
                    {
                        var roomValue = JsonDocument.Parse(jsonDoc.RootElement.GetProperty(room + i.ToString()).ToString());
                        switch (i)
                        {
                            case 1: room1.Text = roomValue.RootElement.GetProperty("name").ToString(); break;
                            case 2: room2.Text = roomValue.RootElement.GetProperty("name").ToString(); break;
                            case 3: room3.Text = roomValue.RootElement.GetProperty("name").ToString(); break;
                            case 4: room4.Text = roomValue.RootElement.GetProperty("name").ToString(); break;
                            case 5: room5.Text = roomValue.RootElement.GetProperty("name").ToString(); break;
                            case 6: room6.Text = roomValue.RootElement.GetProperty("name").ToString(); break;
                            case 7: room7.Text = roomValue.RootElement.GetProperty("name").ToString(); break;
                            case 8: room8.Text = roomValue.RootElement.GetProperty("name").ToString(); break;
                            case 9: room9.Text = roomValue.RootElement.GetProperty("name").ToString(); break;
                            case 10: room10.Text = roomValue.RootElement.GetProperty("name").ToString(); break;
                        }
                        
                    }

                    catch { 
                        
                    }
                }
            }
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
                var inRoom = new PlayerLobbyWindow();
                inRoom.Show();
                this.Close();
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

                string room = "room";
                var jsonDoc = JsonDocument.Parse(res);
                for (int i = 1; i < 11; i++)
                {

                    var roomValue = JsonDocument.Parse(jsonDoc.RootElement.GetProperty(room + i.ToString()).ToString());
                    if(roomValue.RootElement.GetProperty("name").ToString() == roomName)
                    {
                        return roomValue.RootElement.GetProperty("id").GetInt32();
                    }    
                }
            }
            return -1;
        }
        
    }
    
    public class JoinRoomRequest
    { 
        public int roomId { get; set; }
    }

}
