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
    /// Interaction logic for CreateRoomWindow.xaml
    /// </summary>
    public partial class CreateRoomWindow : Window
    {
        public CreateRoomWindow()
        {
            InitializeComponent();
        }

        private void ToCreateButton_Click(object sender, RoutedEventArgs e)
        {
            string roomName = RoomnameTextBox.Text.Trim();
            string maxUsers = MaxusersTextBox.Text.Trim();
            string questionCount = QuestioncountBox.Text.Trim();
            string answerTimeOut = AnswertimeoutBox.Text.Trim();

            createRoomRequest room = new createRoomRequest();
            
            room.roomName = roomName;

            if (string.IsNullOrWhiteSpace(roomName) || string.IsNullOrWhiteSpace(maxUsers)
                || string.IsNullOrWhiteSpace(questionCount) || string.IsNullOrWhiteSpace(answerTimeOut))
            {
                ShowError("Please fill in all fields.");
                return;
            }

            try
            {
                room.maxUsers = Int32.Parse(maxUsers);
                room.questionCount = Int32.Parse(questionCount);
                room.answerTimeout = Int32.Parse(answerTimeOut);
            }
            catch (Exception ex)
            {
                ShowError(ex.Message + "Must be a number!");
                return;
            }


            

            TcpClient client = (TcpClient)(Application.Current.Properties["client"]);
            NetworkStream stream = (NetworkStream)(Application.Current.Properties["stream"]);

            string json = JsonSerializer.Serialize<createRoomRequest>(room);
            //send message
            byte[] data = MessageBuilder.buildMessage(17, json);
            stream.Write(data, 0, data.Length);

            byte[] buffer = new byte[1024];
            int bytesRead = stream.Read(buffer, 0, buffer.Length);

            string res = Encoding.UTF8.GetString(buffer, 5, bytesRead - 5);
            int status = MessageBuilder.GetStatus(res);


            if (status == 17)
            {
                MessageBox.Show($"Room created successfully for {roomName}!\n\n[TODO: Send to server for registration]");
                var inRoom = new RoomAdminWindow();
                inRoom.Show();
                this.Hide();
            }
            else
            {
                HideError();
            }

        }
        private void CloseButton_Click(object sender, RoutedEventArgs e)
        {
            //logout
            Application.Current.Shutdown();
        }

        private void ToLobbyButton_Click(object sender, EventArgs e)
        {
            var lobby = new LobbyWindow();
            lobby.Show();
            this.Hide();
        }

        private void HideError()
        {
            ErrorMessageTextBlock.Visibility = Visibility.Collapsed;
        }
        private void ShowError(string message)
        {
            ErrorMessageTextBlock.Text = message;
            ErrorMessageTextBlock.Visibility = Visibility.Visible;
        }

    }

    public class createRoomRequest
    {
        public string roomName { get; set; }
        public int maxUsers { get; set; }
        public int questionCount { get; set; }
        public int answerTimeout { get; set; }
    }
}
