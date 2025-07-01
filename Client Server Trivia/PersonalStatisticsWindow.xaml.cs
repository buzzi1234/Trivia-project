using System;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Expressions;
using System.Net.Sockets;
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

            this.Height = SystemParameters.PrimaryScreenHeight;

            // Keep width fixed or adjust if needed
            this.Width = 850;

            // Optional: Re-center manually (since we changed size)
            this.Left = (SystemParameters.PrimaryScreenWidth - this.Width) / 2;
            this.Top = 0;

            Loaded += PersonalStatisticsWindow_Loaded;

        }

        private async void PersonalStatisticsWindow_Loaded(object sender, RoutedEventArgs e)
        {

            TcpClient client = (TcpClient)(Application.Current.Properties["client"]);
            NetworkStream stream = (NetworkStream)(Application.Current.Properties["stream"]);

            byte[] data = MessageBuilder.buildMessage(21, "{}");
            await stream.WriteAsync(data, 0, data.Length); // ✅ Non-blocking

            byte[] buffer = new byte[1024];
            int bytesRead = await stream.ReadAsync(buffer, 0, buffer.Length); // ✅ Non-blocking

            string res = Encoding.UTF8.GetString(buffer, 5, bytesRead - 5);
            int status = MessageBuilder.GetStatus(res);

            if (status == 21)
            {
                putValues(res);
                PlayerNameText.Text = PlayerName;
                GamesPlayedValue.Text = GamesPlayed.ToString();
                WinRateValue.Text = GamesWon.ToString();
                BestScoreValue.Text = BestScore.ToString();
                GamesWonValue.Text = GamesWon.ToString();
                GamesLostValue.Text = GamesLost.ToString();
                CorrectAnswersValue.Text = TotalCorrectAnswers.ToString();
                WrongAnswersValue.Text = TotalWrongAnswers.ToString();
                TotalQuestionsValue.Text = TotalQuestionsAnswered.ToString();

            }
        }

        private void putValues(string stats)
        {
            var jsonDoc = JsonDocument.Parse(stats);
            string statsName = "stats";
            for(int i = 1; i < 7; i++)
            {
                string statsValue = jsonDoc.RootElement.GetProperty(statsName + i.ToString()).ToString();
                switch (i)
                {
                    case 1: PlayerName = statsValue; break;
                    case 2: AverageAnswerTime = double.Parse(statsValue); break;
                    case 3: TotalCorrectAnswers = int.Parse(statsValue); break;
                    case 4: TotalQuestionsAnswered = int.Parse(statsValue); break;
                    case 5: GamesPlayed = int.Parse(statsValue); break;
                    case 6: BestScore = int.Parse(statsValue); break;
                }
            }
            TotalWrongAnswers = TotalQuestionsAnswered-TotalCorrectAnswers;
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
