using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
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
    /// Interaction logic for RoomAdminWindow.xaml
    /// </summary>
    public partial class RoomAdminWindow : Window
    {
        public RoomAdminWindow()
        {
            InitializeComponent();
        }

        private void CloseRoomButton_Click(object sender, RoutedEventArgs e)
        {
            TcpClient client = (TcpClient)(Application.Current.Properties["client"]);
            NetworkStream stream = (NetworkStream)(Application.Current.Properties["stream"]);

            byte[] data = MessageBuilder.buildMessage(23, "{}");
            stream.Write(data, 0, data.Length); // ✅ Non-blocking

            byte[] buffer = new byte[1024];
            int bytesRead = stream.Read(buffer, 0, buffer.Length); // ✅ Non-blocking

            string res = Encoding.UTF8.GetString(buffer, 5, bytesRead - 5);
            int status = MessageBuilder.GetStatus(res);
            if (status == 23)
            {
                MessageBox.Show("Return to lobby");
                LobbyWindow lb = new LobbyWindow();
                lb.Show();
                this.Close();
            }
        }

        private void StartGameButton_Click(object sender, RoutedEventArgs e)
        {
            TcpClient client = (TcpClient)(Application.Current.Properties["client"]);
            NetworkStream stream = (NetworkStream)(Application.Current.Properties["stream"]);

            byte[] data = MessageBuilder.buildMessage(27, "{}");
            stream.Write(data, 0, data.Length); // ✅ Non-blocking

            byte[] buffer = new byte[1024];
            int bytesRead = stream.Read(buffer, 0, buffer.Length); // ✅ Non-blocking

            string res = Encoding.UTF8.GetString(buffer, 5, bytesRead - 5);
            int status = MessageBuilder.GetStatus(res);
            if (status == 27)
            {
                MessageBox.Show("Game Started");
               
            }
        }
    }
}
