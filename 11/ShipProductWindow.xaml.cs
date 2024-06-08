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
    public partial class ShipProductWindow : Window
    {
        private string connectionString = @"Provider=Microsoft.ACE.OLEDB.12.0;Data Source=""C:\Users\90932\Documents\Database1.accdb""";

        public ShipProductWindow()
        {
            InitializeComponent();
        }

        private void ShipButton_Click(object sender, RoutedEventArgs e)
        {
            string productName = ProductNameTextBox.Text.Trim();
            if (int.TryParse(ShipQuantityTextBox.Text.Trim(), out int shipQuantity) && shipQuantity > 0)
            {
                using (OleDbConnection connection = new OleDbConnection(connectionString))
                {
                    try
                    {
                        connection.Open();
                        // 检查库存是否足够
                        string checkQuery = "SELECT 数量 FROM Products WHERE 名字 = ?";
                        using (OleDbCommand checkCommand = new OleDbCommand(checkQuery, connection))
                        {
                            checkCommand.Parameters.AddWithValue("?", productName);
                            object result = checkCommand.ExecuteScalar();

                            if (result != null && int.TryParse(result.ToString(), out int currentQuantity))
                            {
                                if (currentQuantity >= shipQuantity)
                                {
                                    // 更新库存
                                    string updateQuery = "UPDATE Products SET 数量 = 数量 - ? WHERE 名字 = ?";
                                    using (OleDbCommand updateCommand = new OleDbCommand(updateQuery, connection))
                                    {
                                        updateCommand.Parameters.AddWithValue("?", shipQuantity);
                                        updateCommand.Parameters.AddWithValue("?", productName);
                                        updateCommand.ExecuteNonQuery();
                                        MessageBox.Show("出货成功", "信息", MessageBoxButton.OK, MessageBoxImage.Information);
                                        this.DialogResult = true; // 设置对话框结果为 true，表示成功
                                    }
                                }
                                else
                                {
                                    MessageBox.Show("库存不足", "错误", MessageBoxButton.OK, MessageBoxImage.Error);
                                }
                            }
                            else
                            {
                                MessageBox.Show("未找到该产品", "错误", MessageBoxButton.OK, MessageBoxImage.Error);
                            }
                        }
                    }
                    catch (Exception ex)
                    {
                        MessageBox.Show($"出货失败: {ex.Message}", "错误", MessageBoxButton.OK, MessageBoxImage.Error);
                    }
                }
            }
            else
            {
                MessageBox.Show("请输入有效的出货数量", "错误", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }
    }
}
