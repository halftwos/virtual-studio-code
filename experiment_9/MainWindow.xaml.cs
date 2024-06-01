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
using ISO14443DLL;
using System.IO.Ports;



namespace experiment_9
{
    public partial class MainWindow : Window
    {
        private SerialPort serialPort;

        public MainWindow()
        {
            InitializeComponent();
            InitializeComPorts();
        }

        private void InitializeComPorts()
        {
            string[] ports = SerialPort.GetPortNames();
            CBport.ItemsSource = ports;
        }

        private void BtnOpenCom_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                if (CBport.SelectedItem != null && CBBaudrate.SelectedItem != null)
                {
                    string portName = CBport.SelectedItem.ToString();
                    int baudRate = int.Parse((CBBaudrate.SelectedItem as ComboBoxItem).Content.ToString());
                    serialPort = new SerialPort(portName, baudRate);
                    serialPort.Open();
                    AddLog("串口已打开: " + portName);
                }
                else
                {
                    MessageBox.Show("请选择串口和波特率");
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("打开串口失败: " + ex.Message);
            }
        }

        private void BtnCloseCom_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                if (serialPort != null && serialPort.IsOpen)
                {
                    serialPort.Close();
                    AddLog("串口已关闭");
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("关闭串口失败: " + ex.Message);
            }
        }

        private void BtnRequest_Click(object sender, RoutedEventArgs e)
        {
            // 模拟请求所有卡片的操作
            AddLog("请求所有卡片...");
            // 这里添加实际请求所有卡片的代码
        }

        private void BtnAntiColl_Click(object sender, RoutedEventArgs e)
        {
            // 模拟寻卡操作
            AddLog("寻卡...");
            // 这里添加实际寻卡的代码
        }

        private void BtnInventory_Click(object sender, RoutedEventArgs e)
        {
            // 模拟直接寻卡操作
            AddLog("直接寻卡...");
            // 这里添加实际直接寻卡的代码
        }

        private void BtnSelect_Click(object sender, RoutedEventArgs e)
        {
            // 模拟选择卡片操作
            AddLog("选择卡片...");
            // 这里添加实际选择卡片的代码
        }

        private void BtnAuthentication_Click(object sender, RoutedEventArgs e)
        {
            // 模拟密码认证操作
            string address = TBAddress.Text;
            string password = TBPassWord.Text;
            AddLog($"认证密码，地址: {address}, 密钥: {password}");
            // 这里添加实际认证密码的代码
        }

        private void BtnRead_Click(object sender, RoutedEventArgs e)
        {
            // 模拟读取数据块操作
            AddLog("读取数据块...");
            // 这里添加实际读取数据块的代码
        }

        private void BtnWrite_Click(object sender, RoutedEventArgs e)
        {
            // 模拟写入数据块操作
            string data = TBWriteData.Text;
            AddLog($"写入数据块: {data}");
            // 这里添加实际写入数据块的代码
        }

        private void BtnClear_Click(object sender, RoutedEventArgs e)
        {
            LBInformation.Items.Clear();
        }

        private void AddLog(string message)
        {
            LBInformation.Items.Add(message);
            LBInformation.ScrollIntoView(LBInformation.Items[LBInformation.Items.Count - 1]);
        }
    }
}
