namespace DFT
{
    partial class Graph
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea1 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Legend legend1 = new System.Windows.Forms.DataVisualization.Charting.Legend();
            System.Windows.Forms.DataVisualization.Charting.Series series1 = new System.Windows.Forms.DataVisualization.Charting.Series();
            this.Draw = new System.Windows.Forms.Button();
            this.a_label = new System.Windows.Forms.Label();
            this.f_label = new System.Windows.Forms.Label();
            this.fi_label = new System.Windows.Forms.Label();
            this.a_textBox = new System.Windows.Forms.TextBox();
            this.f_textBox = new System.Windows.Forms.TextBox();
            this.fi_textBox = new System.Windows.Forms.TextBox();
            this.n_label = new System.Windows.Forms.Label();
            this.n_textBox = new System.Windows.Forms.TextBox();
            this.noise_label = new System.Windows.Forms.Label();
            this.noise_yes = new System.Windows.Forms.RadioButton();
            this.noise_no = new System.Windows.Forms.RadioButton();
            this.Graphic = new System.Windows.Forms.DataVisualization.Charting.Chart();
            ((System.ComponentModel.ISupportInitialize)(this.Graphic)).BeginInit();
            this.SuspendLayout();
            // 
            // Draw
            // 
            this.Draw.Location = new System.Drawing.Point(763, 30);
            this.Draw.Name = "Draw";
            this.Draw.Size = new System.Drawing.Size(75, 20);
            this.Draw.TabIndex = 0;
            this.Draw.Text = "Построить";
            this.Draw.UseVisualStyleBackColor = true;
            this.Draw.Click += new System.EventHandler(this.DrawGraph_Click);
            // 
            // a_label
            // 
            this.a_label.AutoSize = true;
            this.a_label.Location = new System.Drawing.Point(13, 12);
            this.a_label.Name = "a_label";
            this.a_label.Size = new System.Drawing.Size(62, 13);
            this.a_label.TabIndex = 1;
            this.a_label.Text = "Амплитуда";
            // 
            // f_label
            // 
            this.f_label.AutoSize = true;
            this.f_label.Location = new System.Drawing.Point(99, 12);
            this.f_label.Name = "f_label";
            this.f_label.Size = new System.Drawing.Size(49, 13);
            this.f_label.TabIndex = 2;
            this.f_label.Text = "Частота";
            // 
            // fi_label
            // 
            this.fi_label.AutoSize = true;
            this.fi_label.Location = new System.Drawing.Point(169, 12);
            this.fi_label.Name = "fi_label";
            this.fi_label.Size = new System.Drawing.Size(91, 13);
            this.fi_label.TabIndex = 3;
            this.fi_label.Text = "Начальная фаза";
            // 
            // a_textBox
            // 
            this.a_textBox.Location = new System.Drawing.Point(16, 28);
            this.a_textBox.Name = "a_textBox";
            this.a_textBox.Size = new System.Drawing.Size(59, 20);
            this.a_textBox.TabIndex = 4;
            this.a_textBox.Text = "1,5";
            this.a_textBox.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // f_textBox
            // 
            this.f_textBox.Location = new System.Drawing.Point(102, 27);
            this.f_textBox.Name = "f_textBox";
            this.f_textBox.Size = new System.Drawing.Size(46, 20);
            this.f_textBox.TabIndex = 5;
            this.f_textBox.Text = "3,4";
            this.f_textBox.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // fi_textBox
            // 
            this.fi_textBox.Location = new System.Drawing.Point(172, 27);
            this.fi_textBox.Name = "fi_textBox";
            this.fi_textBox.Size = new System.Drawing.Size(88, 20);
            this.fi_textBox.TabIndex = 6;
            this.fi_textBox.Text = "30";
            this.fi_textBox.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // n_label
            // 
            this.n_label.AutoSize = true;
            this.n_label.Location = new System.Drawing.Point(666, 15);
            this.n_label.Name = "n_label";
            this.n_label.Size = new System.Drawing.Size(91, 13);
            this.n_label.TabIndex = 7;
            this.n_label.Text = "Кол-во сигналов";
            // 
            // n_textBox
            // 
            this.n_textBox.Location = new System.Drawing.Point(669, 31);
            this.n_textBox.Name = "n_textBox";
            this.n_textBox.Size = new System.Drawing.Size(88, 20);
            this.n_textBox.TabIndex = 8;
            this.n_textBox.Text = "16";
            this.n_textBox.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // noise_label
            // 
            this.noise_label.AutoSize = true;
            this.noise_label.Location = new System.Drawing.Point(286, 27);
            this.noise_label.Name = "noise_label";
            this.noise_label.Size = new System.Drawing.Size(29, 13);
            this.noise_label.TabIndex = 10;
            this.noise_label.Text = "Шум";
            // 
            // noise_yes
            // 
            this.noise_yes.AutoSize = true;
            this.noise_yes.Location = new System.Drawing.Point(317, 15);
            this.noise_yes.Name = "noise_yes";
            this.noise_yes.Size = new System.Drawing.Size(40, 17);
            this.noise_yes.TabIndex = 11;
            this.noise_yes.Text = "Да";
            this.noise_yes.UseVisualStyleBackColor = true;
            // 
            // noise_no
            // 
            this.noise_no.AutoSize = true;
            this.noise_no.Checked = true;
            this.noise_no.Location = new System.Drawing.Point(317, 33);
            this.noise_no.Name = "noise_no";
            this.noise_no.Size = new System.Drawing.Size(44, 17);
            this.noise_no.TabIndex = 12;
            this.noise_no.TabStop = true;
            this.noise_no.Text = "Нет";
            this.noise_no.UseVisualStyleBackColor = true;
            // 
            // Graphic
            // 
            chartArea1.Name = "ChartArea1";
            this.Graphic.ChartAreas.Add(chartArea1);
            legend1.Name = "Legend1";
            this.Graphic.Legends.Add(legend1);
            this.Graphic.Location = new System.Drawing.Point(16, 55);
            this.Graphic.Name = "Graphic";
            series1.ChartArea = "ChartArea1";
            series1.IsVisibleInLegend = false;
            series1.Legend = "Legend1";
            series1.Name = "DFT";
            this.Graphic.Series.Add(series1);
            this.Graphic.Size = new System.Drawing.Size(822, 550);
            this.Graphic.TabIndex = 13;
            this.Graphic.Text = "chart1";
            // 
            // Graph
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(850, 617);
            this.Controls.Add(this.Graphic);
            this.Controls.Add(this.noise_no);
            this.Controls.Add(this.noise_yes);
            this.Controls.Add(this.noise_label);
            this.Controls.Add(this.n_textBox);
            this.Controls.Add(this.n_label);
            this.Controls.Add(this.fi_textBox);
            this.Controls.Add(this.f_textBox);
            this.Controls.Add(this.a_textBox);
            this.Controls.Add(this.fi_label);
            this.Controls.Add(this.f_label);
            this.Controls.Add(this.a_label);
            this.Controls.Add(this.Draw);
            this.Name = "Graph";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "График";
            ((System.ComponentModel.ISupportInitialize)(this.Graphic)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button Draw;
        private System.Windows.Forms.Label a_label;
        private System.Windows.Forms.Label f_label;
        private System.Windows.Forms.Label fi_label;
        private System.Windows.Forms.TextBox a_textBox;
        private System.Windows.Forms.TextBox f_textBox;
        private System.Windows.Forms.TextBox fi_textBox;
        private System.Windows.Forms.Label n_label;
        private System.Windows.Forms.TextBox n_textBox;
        private System.Windows.Forms.Label noise_label;
        private System.Windows.Forms.RadioButton noise_yes;
        private System.Windows.Forms.RadioButton noise_no;
        private System.Windows.Forms.DataVisualization.Charting.Chart Graphic;
    }
}

