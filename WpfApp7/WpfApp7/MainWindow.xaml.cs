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
using Tools;

namespace WpfApp7
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }
        private void CalculateButton_Click(object sender, RoutedEventArgs e)
        {
            int number1 = 0;
            int number2 = 0;
          
            if (int.TryParse(textBox1.Text, out number1) && int.TryParse(textBox2.Text, out number2))
            {
              
                int sum = (int)Calculator.Add(number1, number2);
               
                resultBox.Text = sum.ToString();
            }
            
        }
    }
}