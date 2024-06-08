using System.Text;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System;
using System.Data;
using System.Data.OleDb;
using LiveCharts;
using LiveCharts.Wpf;
using System.Windows;

namespace _11
{
    public partial class MainWindow : Window
    {
        private string connectionString = @"Provider=Microsoft.ACE.OLEDB.12.0;Data Source=""C:\Users\90932\Documents\Database1.accdb""";
        public SeriesCollection PieSeriesCollection { get; set; }

        public MainWindow()
        {
            InitializeComponent();
            InitializePieChart();
            LoadProducts(); // 启动时加载所有产品列表
        }

        // 初始化饼状图
        private void InitializePieChart()
        {
            PieSeriesCollection = new SeriesCollection();
            PieChart.Series = PieSeriesCollection;
        }

        // 更新饼状图数据
        private void UpdatePieChart()
        {
            using (OleDbConnection connection = new OleDbConnection(connectionString))
            {
                try
                {
                    connection.Open();
                    string query = "SELECT 种类, SUM(数量) AS Total FROM Products GROUP BY 种类";
                    using (OleDbCommand command = new OleDbCommand(query, connection))
                    {
                        using (OleDbDataReader reader = command.ExecuteReader())
                        {
                            PieSeriesCollection.Clear();
                            while (reader.Read())
                            {
                                PieSeriesCollection.Add(new PieSeries
                                {
                                    Title = reader["种类"].ToString(),
                                    Values = new ChartValues<double> { Convert.ToDouble(reader["Total"]) },
                                    DataLabels = true
                                });
                            }
                        }
                    }
                }
                catch (Exception ex)
                {
                    MessageBox.Show($"更新饼状图失败: {ex.Message}", "错误", MessageBoxButton.OK, MessageBoxImage.Error);
                }
            }
        }

        // 加载所有产品到 DataGrid
        private void LoadProducts()
        {
            using (OleDbConnection connection = new OleDbConnection(connectionString))
            {
                try
                {
                    connection.Open();
                    string query = "SELECT ID, 名字, 数量, 种类 FROM Products";
                    using (OleDbDataAdapter adapter = new OleDbDataAdapter(query, connection))
                    {
                        DataTable productsTable = new DataTable();
                        adapter.Fill(productsTable);
                        ProductsDataGrid.ItemsSource = productsTable.DefaultView;
                    }

                    UpdatePieChart(); // 加载产品后更新饼状图
                }
                catch (Exception ex)
                {
                    MessageBox.Show($"加载产品失败: {ex.Message}", "错误", MessageBoxButton.OK, MessageBoxImage.Error);
                }
            }
        }

        // 查询按钮点击事件处理
        private void QueryButton_Click(object sender, RoutedEventArgs e)
        {
            string queryText = QueryTextBox.Text.Trim();

            using (OleDbConnection connection = new OleDbConnection(connectionString))
            {
                try
                {
                    connection.Open();
                    string query;

                    // 检查查询文本是否为数字，以确定是按编号查询还是按名字或种类查询
                    if (int.TryParse(queryText, out int productId))
                    {
                        // 按编号查询
                        query = "SELECT ID, 名字, 数量, 种类 FROM Products WHERE ID = ?";
                    }
                    else
                    {
                        // 按名字或种类查询
                        query = "SELECT ID, 名字, 数量, 种类 FROM Products WHERE 名字 LIKE ? OR 种类 LIKE ?";
                        queryText = "%" + queryText + "%"; // 为名字和种类查询添加通配符
                    }

                    using (OleDbDataAdapter adapter = new OleDbDataAdapter(query, connection))
                    {
                        adapter.SelectCommand.Parameters.AddWithValue("?", queryText);

                        if (!int.TryParse(queryText, out _)) // 如果不是按编号查询，第二个参数是同一个查询文本
                        {
                            adapter.SelectCommand.Parameters.AddWithValue("?", queryText);
                        }

                        DataTable productsTable = new DataTable();
                        adapter.Fill(productsTable);
                        ProductsDataGrid.ItemsSource = productsTable.DefaultView;
                    }

                    UpdatePieChart(); // 查询产品后更新饼状图
                }
                catch (Exception ex)
                {
                    MessageBox.Show($"查询产品失败: {ex.Message}", "错误", MessageBoxButton.OK, MessageBoxImage.Error);
                }
            }
        }

        // 添加按钮点击事件处理
        private void AddButton_Click(object sender, RoutedEventArgs e)
        {
            AddProductWindow addProductWindow = new AddProductWindow();
            if (addProductWindow.ShowDialog() == true)
            {
                LoadProducts(); // 重新加载产品列表
                UpdatePieChart(); // 添加产品后更新饼状图
            }
        }

        // 显示所有数据按钮点击事件处理
        private void ShowAllButton_Click(object sender, RoutedEventArgs e)
        {
            LoadProducts(); // 重新加载所有产品数据
        }

        // 删除按钮点击事件处理
        private void DeleteButton_Click(object sender, RoutedEventArgs e)
        {
            if (ProductsDataGrid.SelectedItem is DataRowView selectedRow)
            {
                int id = Convert.ToInt32(selectedRow["ID"]);

                using (OleDbConnection connection = new OleDbConnection(connectionString))
                {
                    try
                    {
                        connection.Open();

                        // 删除产品
                        string deleteQuery = "DELETE FROM Products WHERE ID = ?";
                        using (OleDbCommand deleteCommand = new OleDbCommand(deleteQuery, connection))
                        {
                            deleteCommand.Parameters.AddWithValue("?", id);
                            deleteCommand.ExecuteNonQuery();
                        }

                        // 调整编号
                        AdjustProductIds(connection);

                        MessageBox.Show("产品已删除", "信息", MessageBoxButton.OK, MessageBoxImage.Information);
                        LoadProducts(); // 删除成功后重新加载产品列表
                        UpdatePieChart(); // 删除产品后更新饼状图
                    }
                    catch (Exception ex)
                    {
                        MessageBox.Show($"删除产品失败: {ex.Message}", "错误", MessageBoxButton.OK, MessageBoxImage.Error);
                    }
                }
            }
            else
            {
                MessageBox.Show("请先选择要删除的产品", "错误", MessageBoxButton.OK, MessageBoxImage.Warning);
            }
        }

        // 管理员按钮点击事件处理
        private void AdminButton_Click(object sender, RoutedEventArgs e)
        {
            AddUserWindow addUserWindow = new AddUserWindow();
            addUserWindow.ShowDialog();
        }

        // 出货按钮点击事件处理
        private void ShipButton_Click(object sender, RoutedEventArgs e)
        {
            ShipProductWindow shipProductWindow = new ShipProductWindow();
            if (shipProductWindow.ShowDialog() == true)
            {
                LoadProducts(); // 重新加载产品列表
                UpdatePieChart(); // 出货后更新饼状图
            }
        }

        // 调整产品编号
        private void AdjustProductIds(OleDbConnection connection)
        {
            try
            {
                // 获取所有产品按原编号排序
                string selectQuery = "SELECT ID FROM Products ORDER BY ID";
                using (OleDbCommand selectCommand = new OleDbCommand(selectQuery, connection))
                {
                    using (OleDbDataReader reader = selectCommand.ExecuteReader())
                    {
                        List<int> ids = new List<int>();
                        while (reader.Read())
                        {
                            ids.Add(reader.GetInt32(0));
                        }

                        // 更新编号为连续的
                        for (int i = 0; i < ids.Count; i++)
                        {
                            int currentId = ids[i];
                            int newId = i + 1; // 新的连续编号从 1 开始

                            // 如果当前编号与新的连续编号不一致，则更新
                            if (currentId != newId)
                            {
                                string updateQuery = "UPDATE Products SET ID = ? WHERE ID = ?";
                                using (OleDbCommand updateCommand = new OleDbCommand(updateQuery, connection))
                                {
                                    updateCommand.Parameters.AddWithValue("?", newId);
                                    updateCommand.Parameters.AddWithValue("?", currentId);
                                    updateCommand.ExecuteNonQuery();
                                }
                            }
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show($"调整产品编号失败: {ex.Message}", "错误", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }
    }
}








