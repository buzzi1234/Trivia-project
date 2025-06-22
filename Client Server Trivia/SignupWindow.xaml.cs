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
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Client_Server_Trivia
{
    /// <summary>
    /// Interaction logic for SignupWindow.xaml
    /// </summary>
    public partial class SignupWindow : Window
    {
        public SignupWindow()
        {
            InitializeComponent();
        }

        private void SignupButton_Click(object sender, RoutedEventArgs e)
        {
            string username = UsernameTextBox.Text.Trim();
            string email = EmailTextBox.Text.Trim();
            string password = PasswordBox.Password.Trim();
            string confirmPassword = ConfirmPasswordBox.Password.Trim();

            if (string.IsNullOrWhiteSpace(username) || string.IsNullOrWhiteSpace(email)
                || string.IsNullOrWhiteSpace(password) || string.IsNullOrWhiteSpace(confirmPassword))
            {
                ShowError("Please fill in all fields.");
                return;
            }

            if (password != confirmPassword)
            {
                ShowError("Passwords do not match.");
                return;
            }

            TcpClient client = new TcpClient("127.0.0.1", 8826);
            NetworkStream stream = client.GetStream();

            string json = "{\"username\":\"" + username + "\",\"password\":\"" + password + "\",\"mail\":\"" + email + "\"}";
            //send message
            byte[] data = MessageBuilder.BuildJsonMessage(2, json);
            stream.Write(data, 0, data.Length);

            byte[] buffer = new byte[1024];
            int bytesRead = stream.Read(buffer, 0, buffer.Length);
            string res = Encoding.UTF8.GetString(buffer, 5, bytesRead - 5);
            int status = MessageBuilder.GetStatus(res);
            if(status == 2)
            {
                MessageBox.Show($"Account created successfully for {username}!\n\n[TODO: Send to server for registration]");
            }
            else
            {
                HideError();
            }
               
        }

        private void LoginButton_Click(object sender, RoutedEventArgs e)
        {
            MainWindow loginWindow = new MainWindow();
            loginWindow.Show();
            this.Close();
        }

        private void ShowError(string message)
        {
            ErrorMessageTextBlock.Text = message;
            ErrorMessageTextBlock.Visibility = Visibility.Visible;
        }

        private void HideError()
        {
            ErrorMessageTextBlock.Visibility = Visibility.Collapsed;
        }

        private void CloseButton_Click(object sender, RoutedEventArgs e)
        {
            Application.Current.Shutdown();
        }
    }
}
