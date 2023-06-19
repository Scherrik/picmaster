#pragma once

namespace CppCLR
{
    public partial class _2DArray_To_DataGridView : Form
    {
        public _2DArray_To_DataGridView()
        {
            InitializeComponent();
        }

        private void _2DArray_To_DataGridView_Load(object sender, EventArgs e)
        {
            string[, ] rows = new string[, ]{ // 1   2     3     4 
                                             {"1","AAA","BBB","10"},//1
                                             {"2","CCC","DDD","20"},//2
                                             {"3","ZZZ","YYY","30"},//3
                                             {"4","LLL","MMM","40"},
                                             {"5","NNN","TTT","50"},
                                             {"6","WWW","RRR","60"},
                                             {"7","GGG","PPP","70"}//7
            };

            // rows.GetLength(0) return length of the first D (7)
            // rows.GetLength(1) return length of the second D
            for (int i = 0; i < rows.GetLength(0); i++)// array rows
            {
                string[] row = new string[rows.GetLength(1)];

                for (int j = 0; j < rows.GetLength(1); j++)
                {
                    row[j] = rows[i, j];
                }

                dataGridView1.Rows.Add(row);
            }
        }
    }
}
