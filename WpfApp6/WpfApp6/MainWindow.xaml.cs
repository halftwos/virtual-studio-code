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

namespace WpfApp6
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
        
    

        private void int1_TextChanged(object sender, TextChangedEventArgs e)
        {
            int sum = Convert.ToInt16(int1.Text) + Convert.ToInt16(int2.Text);
            put.Text = (sum).ToString();
        }

        private void int2_TextChanged(object sender, TextChangedEventArgs e)
        {
            int sum = Convert.ToInt16(int1.Text) + Convert.ToInt16(int2.Text);
            put.Text = (sum).ToString();
        }
    }
}