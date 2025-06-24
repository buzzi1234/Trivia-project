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
    /// Interaction logic for HighScoresWindow.xaml
    /// </summary>
    public partial class HighScoresWindow : Window
    {
        public HighScoresWindow()
        {
            InitializeComponent();
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
