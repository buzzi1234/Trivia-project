using System;
using System.Collections.Generic;
using System.Linq;
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
            LobbyWindow signupWindow = new LobbyWindow();
            signupWindow.Show();
            this.Hide(); // Hide the main window if needed
            this.Close(); // Close the main window if needed
        }
    }
}
