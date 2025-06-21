using System.Text;
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

            // Here you would typically validate the credentials against a server or database
            HideError();
            MessageBox.Show($"Welcome, {username}!");
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
    }
}