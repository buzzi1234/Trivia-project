using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Reflection.Emit;
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
    /// Interaction logic for HighScoresWindow.xaml
    /// </summary>
    public partial class HighScoresWindow : Window
    {
        public HighScoresWindow()
        {
            InitializeComponent();
            Loaded += HighScoresWindow_Loaded;
            
        }
        private async void HighScoresWindow_Loaded(object sender, RoutedEventArgs e)
        {

            TcpClient client = (TcpClient)(Application.Current.Properties["client"]);
            NetworkStream stream = (NetworkStream)(Application.Current.Properties["stream"]);

            byte[] data = MessageBuilder.buildMessage(19, "{}");
            await stream.WriteAsync(data, 0, data.Length); // ✅ Non-blocking

            byte[] buffer = new byte[1024];
            int bytesRead = await stream.ReadAsync(buffer, 0, buffer.Length); // ✅ Non-blocking

            string res = Encoding.UTF8.GetString(buffer, 5, bytesRead - 5);
            int status = MessageBuilder.GetStatus(res);

            if (status == 19)
            {
                var jsonDoc = JsonDocument.Parse(res);
                string scr = "score";
                for (int i = 1; i < 4; i++)
                {
                    // Assuming you have multiple labels like HighScore1, HighScore2, etc.
                    string scoreValue = jsonDoc.RootElement.GetProperty(scr + i.ToString()).ToString();
                    SetScoreLabel(i, scoreValue);
                }
            }
        }
        private void SetScoreLabel(int index, string score)
        {
            Dispatcher.Invoke(() =>
            {
                switch (index)
                {
                    case 3: FirstPlaceScore.Text = score; break;
                    case 2: SecondPlaceScore.Text = score; break;
                    case 1: ThirdPlaceScore.Text = score; break;
                }
            });
        }

        private void BackButton_Click(object sender, RoutedEventArgs e)
        {
            LobbyWindow lobbyWindow = new LobbyWindow();
            lobbyWindow.Show();
            this.Close();
        }
        private void CloseButton_Click(object sender, EventArgs e)
        {
            // Ensure the main window is closed when this window is closed
            Application.Current.Shutdown();
        }
    }
  
}
