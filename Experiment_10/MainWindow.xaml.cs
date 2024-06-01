using System;
using System.Data;
using System.Data.OleDb;
using System.Windows;
using System.Windows.Controls;

namespace YourNamespace
{
    public partial class MainWindow : Window
    {
        private OleDbConnection oleDbConnection;

        public MainWindow()
        {
            InitializeComponent();
            // Initialize the database connection
            oleDbConnection = new OleDbConnection(@"Provider=Microsoft.ACE.OLEDB.12.0;Data Source=C:\Users\90932\Downloads\Database1.accdb");
        }

        private void 查询_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                oleDbConnection.Open();
                string sql = "SELECT * FROM stu1 WHERE StudentName='" + NameTextBox.Text + "'";
                OleDbCommand sqlcmd = new OleDbCommand(sql, oleDbConnection);
                OleDbDataReader reader = sqlcmd.ExecuteReader();
                if (reader.Read())
                {
                    NameTextBox.Text = reader["StudentNo"].ToString();
                }
                else
                {
                    MessageBox.Show("No record found.");
                }
                oleDbConnection.Close();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void 报表查询_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                oleDbConnection.Open();
                string sql = "SELECT * FROM stu1";
                OleDbDataAdapter dbDataAdapter = new OleDbDataAdapter(sql, oleDbConnection);
                DataSet myds = new DataSet();
                dbDataAdapter.Fill(myds, "stu1");
                DataGrid.ItemsSource = myds.Tables["stu1"].DefaultView;
                oleDbConnection.Close();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void 增加_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                oleDbConnection.Open();
                string sql = "INSERT INTO stu1 (StudentNo, StudentName) VALUES (21204, '" + NameTextBox.Text + "')";
                OleDbCommand oleDbCommand = new OleDbCommand(sql, oleDbConnection);
                int i = oleDbCommand.ExecuteNonQuery();
                MessageBox.Show("成功增加" + i.ToString() + "行", "信息提示", MessageBoxButton.OK, MessageBoxImage.Information);
                oleDbConnection.Close();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void 删除_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                oleDbConnection.Open();
                string sql = "DELETE FROM stu1 WHERE StudentNo=21204";
                OleDbCommand oleDbCommand = new OleDbCommand(sql, oleDbConnection);
                int i = oleDbCommand.ExecuteNonQuery();
                MessageBox.Show("成功删除" + i.ToString() + "行", "信息提示", MessageBoxButton.OK, MessageBoxImage.Information);
                oleDbConnection.Close();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void 修改_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                oleDbConnection.Open();
                string sql = "UPDATE stu1 SET StudentNo=21204 WHERE StudentName='" + NameTextBox.Text + "'";
                OleDbCommand oleDbCommand = new OleDbCommand(sql, oleDbConnection);
                int i = oleDbCommand.ExecuteNonQuery();
                MessageBox.Show("成功修改" + i.ToString() + "行", "信息提示", MessageBoxButton.OK, MessageBoxImage.Information);
                oleDbConnection.Close();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void Window_Closed(object sender, EventArgs e)
        {
            Environment.Exit(0); // 关闭所有进程
        }
    }
}
