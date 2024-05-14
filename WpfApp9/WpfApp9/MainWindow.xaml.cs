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
using MyTools;

namespace WpfApp9
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

        private void bthAdd_Click(object sender, RoutedEventArgs e)
        {
            
        }

        private void bthSub_Click(object sender, RoutedEventArgs e)
        {
           
        }

        private void bthMul_Click(object sender, RoutedEventArgs e)
        {
            double data1 = Convert.ToDouble(tbData1.Text);
            double data2 = Convert.ToDouble(tbData2.Text);
            double result = Calculator.Mul(data1, data2);
            MessageBox.Show("计算结果是" + result.ToString(), "提示");
        }

        private void bthDiv_Click(object sender, RoutedEventArgs e)
        {
            double data1 = Convert.ToDouble(tbData1.Text);
            double data2 = Convert.ToDouble(tbData2.Text);
            if (data2 != 0)
            {
                double result = Calculator.Div(data1, data2);
                MessageBox.Show("计算结果是: " + result.ToString(), "提示");
            }
            else
            {
                MessageBox.Show("除数不能为零", "错误");
            }
        }
    }
}