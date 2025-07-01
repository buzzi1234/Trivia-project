using System;
using System.Net.Sockets;
using System.Text;
using System.Text.Json;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Client_Server_Trivia
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private readonly string usersFilePath = "Users.txt";
        private bool isPasswordVisible = false;
        
        public MainWindow()
        {
            InitializeComponent();
        }
        private void CloseButton_Click(object sender, RoutedEventArgs e)
        {
            Application.Current.Shutdown(); // Close the application
        }
        private void LoginButton_Click(object sender, RoutedEventArgs e)
        {
            string username = UsernameTextBox.Text.Trim();
            string password = GetPassword().Trim();
            loginRequest log = new loginRequest();
            log.username = username;
            log.password = password;
            

            if (string.IsNullOrEmpty(username) || string.IsNullOrEmpty(password))
            {
                MessageBox.Show("Please enter both username and password.");
                return;
            }

            // TODO: Send to server - login request
            /*
            * here need to send request to the server with
            * - username
            * - password
            * 
            * request should be of type LOGIN REQUEST
            * and get back
            * - SUCCESS/FAILURE
            * - If SUCCESS - user details
            * - If FAILURE - reason for failure
            */

            TcpClient client = new TcpClient("127.0.0.1", 8826);
            NetworkStream stream = client.GetStream();

            Application.Current.Properties["client"] = client;
            Application.Current.Properties["stream"] = stream;

            string json = JsonSerializer.Serialize<loginRequest>(log);
            //send message
            byte[] data = MessageBuilder.buildMessage(1, json);
            stream.Write(data, 0, data.Length);


            byte[] buffer = new byte[1024];
            int bytesRead = stream.Read(buffer, 0, buffer.Length);
            string res = Encoding.UTF8.GetString(buffer, 5, bytesRead - 5);
            int status = MessageBuilder.GetStatus(res);
            
            if(status == 1)
            {
                MessageBox.Show($"Welcome, {username}!"); //go to the lobby page
                var lobbyWin = new LobbyWindow();
                lobbyWin.Show();
                this.Hide();
            }
            else
            {
                // Here you would typically validate the credentials against a server or database
                HideError();
            }
            
        }
        private void SignupButton_Click(object sender, RoutedEventArgs e)
        {
            SignupWindow signupWindow = new SignupWindow();
            signupWindow.Show();
            this.Hide(); // Hide the main window if needed
            this.Close(); // Close the main window if needed
        }
        private void ShowError(string message)
        {
            ErrorMessageTextBlock.Text = message;
            ErrorMessageTextBlock.Visibility = Visibility.Visible;
        }
        private string GetPassword()
        {
            if (isPasswordVisible)
            {
                return PasswordTextBox.Text;
            }
            else
            {
                return PasswordBox.Password;
            }
        }
        private void HideError()
        {
            ErrorMessageTextBlock.Visibility = Visibility.Collapsed;
        }

        private void UsernameTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
        }
        
    }

    public class loginRequest
    {
        public string username { get; set; }
        public string password { get; set; }

    }
}