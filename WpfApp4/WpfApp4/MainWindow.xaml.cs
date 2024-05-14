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

namespace WpfApp4
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

        private void ComboBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {

        }

        private void TextBox_TextChanged(object sender, TextChangedEventArgs e)
        {

        }

        private void RadioButton_Checked(object sender, RoutedEventArgs e)
        {

        }

      

   





        private void TextBox_DragEnter(object sender, DragEventArgs e)
        {

        }

        private void TextBox_TextChanged_1(object sender, TextChangedEventArgs e)
        {

        }

        private void comboBox_ContextMenuOpening(object sender, ContextMenuEventArgs e)
        {
           
        }

        private void comboBox_DropDownOpened(object sender, EventArgs e)
        {
            comboBox.Items.Add("大学生");
            comboBox.Items.Add("研究生");
            comboBox.Items.Add("博士生");
        }

        private void comboBox_DropDownClosed(object sender, EventArgs e)
        {
            comboBox.Items.Remove("大学生");
            comboBox.Items.Remove("研究生");
            comboBox.Items.Remove("博士生");
        }
    }
}