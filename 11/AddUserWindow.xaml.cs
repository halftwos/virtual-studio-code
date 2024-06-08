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
using System.Data.OleDb;



namespace _11
{
    public partial class AddUserWindow : Window
    {
        private string connectionString = @"Provider=Microsoft.ACE.OLEDB.12.0;Data Source=""C:\Users\90932\Documents\Database1.accdb""";

        public AddUserWindow()
        {
            InitializeComponent();
        }

        private void AddUserButton_Click(object sender, RoutedEventArgs e)
        {
            string Username = UsernameTextBox.Text.Trim();
            string Password = PasswordBox.Password.Trim();

            if (!string.IsNullOrEmpty(Username) && !string.IsNullOrEmpty(Password))
            {
                using (OleDbConnection connection = new OleDbConnection(connectionString))
                {
                    try
                    {
                        connection.Open();
                        string query = "INSERT INTO [Users] ([Username], [Password]) VALUES (?, ?)";
                        using (OleDbCommand command = new OleDbCommand(query, connection))
                        {
                            command.Parameters.AddWithValue("?", Username);
                            command.Parameters.AddWithValue("?", Password);

                            command.ExecuteNonQuery();
                            MessageBox.Show("用户添加成功", "信息", MessageBoxButton.OK, MessageBoxImage.Information);
                            this.DialogResult = true; // 设置对话框结果为 true，表示成功
                        }
                    }
                    catch (Exception ex)
                    {
                        MessageBox.Show($"添加用户失败: {ex.Message}", "错误", MessageBoxButton.OK, MessageBoxImage.Error);
                    }
                }
            }
            else
            {
                MessageBox.Show("请输入用户名和密码", "错误", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }
    }
}


