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
    /// Interaction logic for RoomPlayersWindow.xaml
    /// </summary>
    public partial class RoomPlayersWindow : Window
    {
        public RoomPlayersWindow()
        {
            InitializeComponent();
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
    }
}
