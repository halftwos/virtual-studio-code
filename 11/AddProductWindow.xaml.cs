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
using ISO15693DLL;
using System.Data.OleDb;
using System.Data;
using System.IO.Ports;
using System.Collections.ObjectModel;


namespace _11
{
    public partial class AddProductWindow : Window
    {
        private string connectionString = @"Provider=Microsoft.ACE.OLEDB.12.0;Data Source=""C:\Users\90932\Documents\Database1.accdb""";
        private ObservableCollection<string> _categories; // ObservableCollection for ComboBox

        public AddProductWindow()
        {
            InitializeComponent();
            _categories = new ObservableCollection<string>();
            ProductCategoryComboBox.ItemsSource = _categories;
            LoadCategories();
        }

        private void LoadCategories()
        {
            using (OleDbConnection connection = new OleDbConnection(connectionString))
            {
                try
                {
                    connection.Open();
                    string query = "SELECT DISTINCT 种类 FROM Products";
                    using (OleDbCommand command = new OleDbCommand(query, connection))
                    {
                        using (OleDbDataReader reader = command.ExecuteReader())
                        {
                            while (reader.Read())
                            {
                                _categories.Add(reader["种类"].ToString());
                            }
                        }
                    }
                }
                catch (Exception ex)
                {
                    MessageBox.Show($"加载种类失败: {ex.Message}", "错误", MessageBoxButton.OK, MessageBoxImage.Error);
                }
            }
        }

        private void AddButton_Click(object sender, RoutedEventArgs e)
        {
            string productName = ProductNameTextBox.Text.Trim();
            string productCategory = ProductCategoryComboBox.Text.Trim();
            if (int.TryParse(ProductQuantityTextBox.Text.Trim(), out int productQuantity))
            {
                int newId = GetNewProductId();

                using (OleDbConnection connection = new OleDbConnection(connectionString))
                {
                    try
                    {
                        connection.Open();
                        string query = "INSERT INTO Products (ID, 名字, 数量, 种类) VALUES (?, ?, ?, ?)";
                        using (OleDbCommand command = new OleDbCommand(query, connection))
                        {
                            command.Parameters.AddWithValue("?", newId);
                            command.Parameters.AddWithValue("?", productName);
                            command.Parameters.AddWithValue("?", productQuantity);
                            command.Parameters.AddWithValue("?", productCategory);

                            command.ExecuteNonQuery();
                            MessageBox.Show("产品添加成功", "信息", MessageBoxButton.OK, MessageBoxImage.Information);
                            this.DialogResult = true; // 设置对话框结果为 true，表示成功
                        }
                    }
                    catch (Exception ex)
                    {
                        MessageBox.Show($"添加产品失败: {ex.Message}", "错误", MessageBoxButton.OK, MessageBoxImage.Error);
                    }
                }
            }
            else
            {
                MessageBox.Show("数量必须是一个有效的数字", "错误", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        private void AddCategoryButton_Click(object sender, RoutedEventArgs e)
        {
            string newCategory = Microsoft.VisualBasic.Interaction.InputBox("请输入新的种类:", "添加新种类", "");
            if (!string.IsNullOrWhiteSpace(newCategory) && !_categories.Contains(newCategory))
            {
                _categories.Add(newCategory);
                ProductCategoryComboBox.SelectedItem = newCategory;
            }
        }

        private void DeleteCategoryButton_Click(object sender, RoutedEventArgs e)
        {
            string selectedCategory = ProductCategoryComboBox.SelectedItem as string;
            if (!string.IsNullOrWhiteSpace(selectedCategory))
            {
                // 提示用户确认删除
                MessageBoxResult result = MessageBox.Show($"确定要删除种类 '{selectedCategory}' 吗？", "确认删除", MessageBoxButton.YesNo, MessageBoxImage.Warning);
                if (result == MessageBoxResult.Yes)
                {
                    _categories.Remove(selectedCategory);
                    ProductCategoryComboBox.SelectedItem = null;
                }
            }
        }

      

        private int GetNewProductId()
        {
            int newId = 1;
            using (OleDbConnection connection = new OleDbConnection(connectionString))
            {
                try
                {
                    connection.Open();
                    string query = "SELECT MAX(ID) FROM Products";
                    using (OleDbCommand command = new OleDbCommand(query, connection))
                    {
                        object result = command.ExecuteScalar();
                        if (result != DBNull.Value && result != null)
                        {
                            newId = Convert.ToInt32(result) + 1;
                        }
                    }
                }
                catch (Exception ex)
                {
                    MessageBox.Show($"无法获取新产品 ID: {ex.Message}", "错误", MessageBoxButton.OK, MessageBoxImage.Error);
                }
            }
            return newId;
        }
    }
}






