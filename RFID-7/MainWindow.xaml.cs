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
using System.IO.Ports;
using ISO15693DLL;

namespace RFID_7

{
    public partial class MainWindow : Window
    {
        ISO15693Reader reader = new ISO15693Reader(); // 创建ISO15693读卡器实例

        public MainWindow()
        {
            InitializeComponent();
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            gb_USB.Visibility = Visibility.Hidden;
            gb_Com.Visibility = Visibility.Hidden;
            gb_Card.Visibility = Visibility.Hidden;
            RBOpenCloseCom.IsChecked = true;
        }

        private void RBOpenCloseCom_Checked(object sender, RoutedEventArgs e)
        {
            gb_Com.Visibility = Visibility.Visible;
            gb_USB.Visibility = Visibility.Hidden;
            gb_Com.Margin = new Thickness(353, 46, 0, 0);
            string[] strPortName = SerialPort.GetPortNames();
            cmbPort.ItemsSource = strPortName;
        }

        private void RBOpenCloseUSB_Checked(object sender, RoutedEventArgs e)
        {
            gb_Com.Visibility = Visibility.Hidden;
            gb_USB.Visibility = Visibility.Visible;
        }

        private void bOpenCom_Click(object sender, RoutedEventArgs e)
        {
            if (cmbPort.SelectedIndex < 0)
            {
                MessageBox.Show("请选择串口");
                return;
            }
            string strPortName = cmbPort.Text.Trim();
            if (cmbBaudRate.SelectedIndex < 0)
            {
                MessageBox.Show("请选择波特率");
                return;
            }
            Int32 BaudRate = Int32.Parse(cmbBaudRate.Text.Trim());

            Byte value = reader.OpenSerialPort(strPortName, BaudRate);
            if (value == 0)
            {
                MessageBox.Show("串口打开成功");
                LBResult.Items.Add("串口打开成功");
                gb_Card.Visibility = Visibility.Visible;
            }
            else
            {
                MessageBox.Show("串口打开失败");
                LBResult.Items.Add("串口打开失败");
            }
        }

        private void bCloseCom_Click(object sender, RoutedEventArgs e)
        {
            if (reader.IsOpen == true)
            {
                Byte value = reader.CloseSerialPort();
                if (value == 0)
                {
                    MessageBox.Show("关闭串口成功");
                    LBResult.Items.Add("关闭串口成功");
                }
                else
                {
                    MessageBox.Show("关闭串口失败");
                    LBResult.Items.Add("关闭串口失败");
                }
            }
        }

        private void BInvetorySingle_Click(object sender, RoutedEventArgs e)
        {
            if (reader.IsOpen == false)
            {
                MessageBox.Show("请先打开串口");
                return;
            }

            ModulateMethod mm = ModulateMethod.ASK;
            InventoryModel im = InventoryModel.Single;
            Int32 TagCount = 0;
            String[] TagNumber = new String[1];
            Byte value = reader.Inventory(mm, im, ref TagCount, ref TagNumber);
            if (value != 0x00)
            {
                MessageBox.Show("错误：Inventory命令执行失败！");
                return;
            }
            TBCardInformation.Text = TagNumber[0];
        }

        private void BReadCardSingle_Click(object sender, RoutedEventArgs e)
        {
            String TagNum = TBCardInformation.Text.Trim();
            BlockLength bl = BlockLength.ShortBlock4Byte;
            Byte[] BlockData = new Byte[4];
            Byte value = reader.ReadSingleBlock(TagNum, bl, 0x00, ref BlockData);
            string Result = "";
            for (int i = 0; i < 4; i++)
                Result += BlockData[i].ToString("X2"); // 字符串格式控制符X为十六进制2为每次都是两位数
            LBResult.Items.Add(Result);

            // 读中文时使用以下程序
            // Encoding.RegisterProvider(CodePagesEncodingProvider.Instance);
            // string cstr = GetChsFromHex(Result);
            // LBResult.Items.Add(cstr);
        }

        private void BWriteCardSingle_Click(object sender, RoutedEventArgs e)
        {
            String TagNum = TBCardInformation.Text.Trim();
            BlockLength bl = BlockLength.ShortBlock4Byte;
            Byte[] BlockData = new Byte[4] { 0x00, 0x01, 0x02, 0x03 };

            // 写中文时使用以下程序
            // Encoding.RegisterProvider(CodePagesEncodingProvider.Instance);
            // System.Text.Encoding chs = System.Text.Encoding.GetEncoding("gb2312");
            // BlockData = chs.GetBytes("你好");

            // 写数据为文本框录入的数据
            // Byte address = Byte.Parse(TBAddress.Text.Trim());
            // string strHex = TBWriteData.Text.Trim();
            // for (int i = 0; i < 4; i++)
            //     BlockData[i] = Byte.Parse(strHex.Substring(2 * i, 2), System.Globalization.NumberStyles.HexNumber);

            Byte value = reader.WriteSingleBlock(TagNum, bl, 0x00, BlockData);
            if (value != 0x00)
                MessageBox.Show("写卡命令执行失败！");
            else
                MessageBox.Show("写卡命令执行成功！");
        }

        // 从汉字转换到16进制
        public static string GetHexFromChs(string s)
        {
            if ((s.Length % 2) != 0)
            {
                s += ""; // 空格
            }
            System.Text.Encoding chs = System.Text.Encoding.GetEncoding("gb2312");
            byte[] bytes = chs.GetBytes(s);
            string str = "";
            for (int i = 0; i < bytes.Length; i++)
            {
                str += string.Format("{0:X}", bytes[i]);
            }
            return str;
        }

        // 从16进制转换成汉字
        public static string GetChsFromHex(string hex)
        {
            if (hex == null)
                throw new ArgumentNullException("hex");
            if (hex.Length % 2 != 0)
            {
                hex += "20"; // 空格
            }

            // 需要将hex转换成byte数组。
            byte[] bytes = new byte[hex.Length / 2];
            for (int i = 0; i < bytes.Length; i++)
            {
                try
                {
                    // 每两个字符是一个byte。
                    bytes[i] = byte.Parse(hex.Substring(i * 2, 2), System.Globalization.NumberStyles.HexNumber);
                }
                catch
                {
                    // Rethrow an exception with custom message.
                    throw new ArgumentException("hex is not a valid hex number!", "hex");
                }
            }
            // 获得 GB2312, Chinese Simplified。
            System.Text.Encoding chs = System.Text.Encoding.GetEncoding("gb2312");
            return chs.GetString(bytes);
        }

       
    }
}

