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
    /// Interaction logic for LobbyWindow.xaml
    /// </summary>
    public partial class LobbyWindow : Window
    {
        public LobbyWindow()
        {
            InitializeComponent();
        }
<<<<<<< HEAD

        private void CloseButton_Click(object sender, RoutedEventArgs e)
        {
            Application.Current.Shutdown(); // Close the application
        }
=======
>>>>>>> 7bb1dbf3a813ccb0e7945ba7e1b3f227031a4e49
        private void CreateARoomButton_Click(object sender, RoutedEventArgs e)
        {
            LobbyWindow signupWindow = new LobbyWindow();
            signupWindow.Show();
            this.Hide(); // Hide the main window if needed
            this.Close(); // Close the main window if needed
        }
        private void JoinARoomButton_Click(object sender, RoutedEventArgs e)
        {
            LobbyWindow signupWindow = new LobbyWindow();
            signupWindow.Show();
            this.Hide(); // Hide the main window if needed
            this.Close(); // Close the main window if needed
        }
        private void StatisticsButton_Click(object sender, RoutedEventArgs e)
        {
            LobbyWindow signupWindow = new LobbyWindow();
            signupWindow.Show();
            this.Hide(); // Hide the main window if needed
            this.Close(); // Close the main window if needed
        }
        private void LogoutButton_Click(object sender, RoutedEventArgs e)
        {
            TcpClient client = (TcpClient)(Application.Current.Properties["client"]);
            NetworkStream stream = (NetworkStream)(Application.Current.Properties["stream"]);

            //send message
            byte[] data = MessageBuilder.BuildLengthMessage(9, "{}");
            stream.Write(data, 0, data.Length);

            data = MessageBuilder.BuildJsonMessage("{}");
            stream.Write(data, 0, data.Length);

            byte[] buffer = new byte[1024];
            int bytesRead = stream.Read(buffer, 0, buffer.Length);
            string res = Encoding.UTF8.GetString(buffer, 5, bytesRead - 5);
            int status = MessageBuilder.GetStatus(res);
            
            if (status == 9)
            {
                MessageBox.Show($"GoodBye!"); 
                var loginPage = new MainWindow();
                loginPage.Show();
                this.Hide();
            }
            else
            {
                // Here you would typically validate the credentials against a server or database
                HideError();
            }

            
        }
        private void HideError()
        {
            ErrorMessageTextBlock.Visibility = Visibility.Collapsed;
        }
    }
}
