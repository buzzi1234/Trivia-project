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
    /// Interaction logic for PersonalStatisticsWindow.xaml
    /// </summary>
    public partial class PersonalStatisticsWindow : Window
    {
        public string PlayerName { get; set; }
        public int GamesPlayed { get; set; }
        public int GamesWon { get; set; }
        public int GamesLost { get; set; }
        public double AverageScore { get; set; }
        public int BestScore { get; set; }
        public int TotalCorrectAnswers { get; set; }
        public int TotalWrongAnswers { get; set; }
        public int TotalQuestionsAnswered { get; set; }
        public double AverageAnswerTime { get; set; }
        public int CurrentRanking { get; set; }
        public PersonalStatisticsWindow()
        {
            InitializeComponent();

        }

        private void CloseButton_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }

        private void BackButton_Click(object sender, RoutedEventArgs e)
        {
            LobbyWindow lobbyWindow = new LobbyWindow();
            lobbyWindow.Show();
            this.Close();
        }


    }
}
