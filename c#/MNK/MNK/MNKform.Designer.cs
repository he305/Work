namespace MNK
{
    partial class MNKform
    {
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.label1 = new System.Windows.Forms.Label();
            this.EditCount = new System.Windows.Forms.TextBox();
            this.XLayoutPanel = new System.Windows.Forms.TableLayoutPanel();
            this.XLabel = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.MNK_button = new System.Windows.Forms.Button();
            this.answerLayout = new System.Windows.Forms.TableLayoutPanel();
            this.tableLayoutPanel2 = new System.Windows.Forms.TableLayoutPanel();
            this.YLayoutPanel = new System.Windows.Forms.TableLayoutPanel();
            this.ZLayoutPanel = new System.Windows.Forms.TableLayoutPanel();
            this.WLayoutPanel = new System.Windows.Forms.TableLayoutPanel();
            this.polynomeSizeBox = new System.Windows.Forms.ComboBox();
            this.drawGraphButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(72, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Кол-во точек";
            // 
            // EditCount
            // 
            this.EditCount.Location = new System.Drawing.Point(90, 6);
            this.EditCount.Name = "EditCount";
            this.EditCount.Size = new System.Drawing.Size(47, 20);
            this.EditCount.TabIndex = 1;
            this.EditCount.TextChanged += new System.EventHandler(this.EditCount_TextChanged);
            // 
            // XLayoutPanel
            // 
            this.XLayoutPanel.ColumnCount = 1;
            this.XLayoutPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.XLayoutPanel.ImeMode = System.Windows.Forms.ImeMode.Off;
            this.XLayoutPanel.Location = new System.Drawing.Point(25, 53);
            this.XLayoutPanel.Name = "XLayoutPanel";
            this.XLayoutPanel.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.XLayoutPanel.RowCount = 1;
            this.XLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.XLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 263F));
            this.XLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 263F));
            this.XLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 263F));
            this.XLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 263F));
            this.XLayoutPanel.Size = new System.Drawing.Size(59, 263);
            this.XLayoutPanel.TabIndex = 2;
            // 
            // XLabel
            // 
            this.XLabel.AutoSize = true;
            this.XLabel.Location = new System.Drawing.Point(46, 37);
            this.XLabel.Name = "XLabel";
            this.XLabel.Size = new System.Drawing.Size(14, 13);
            this.XLabel.TabIndex = 6;
            this.XLabel.Text = "X";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(123, 37);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(14, 13);
            this.label2.TabIndex = 7;
            this.label2.Text = "Y";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(214, 37);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(14, 13);
            this.label3.TabIndex = 8;
            this.label3.Text = "Z";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(300, 37);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(18, 13);
            this.label4.TabIndex = 9;
            this.label4.Text = "W";
            // 
            // MNK_button
            // 
            this.MNK_button.Location = new System.Drawing.Point(396, 12);
            this.MNK_button.Name = "MNK_button";
            this.MNK_button.Size = new System.Drawing.Size(75, 23);
            this.MNK_button.TabIndex = 10;
            this.MNK_button.Text = "Найти значения";
            this.MNK_button.UseVisualStyleBackColor = true;
            this.MNK_button.Click += new System.EventHandler(this.MNK_button_Click);
            // 
            // answerLayout
            // 
            this.answerLayout.ColumnCount = 1;
            this.answerLayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.answerLayout.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.answerLayout.Location = new System.Drawing.Point(396, 53);
            this.answerLayout.Name = "answerLayout";
            this.answerLayout.RowCount = 1;
            this.answerLayout.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.answerLayout.Size = new System.Drawing.Size(75, 96);
            this.answerLayout.TabIndex = 11;
            // 
            // tableLayoutPanel2
            // 
            this.tableLayoutPanel2.ColumnCount = 1;
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel2.Location = new System.Drawing.Point(396, 165);
            this.tableLayoutPanel2.Name = "tableLayoutPanel2";
            this.tableLayoutPanel2.RowCount = 5;
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel2.Size = new System.Drawing.Size(97, 97);
            this.tableLayoutPanel2.TabIndex = 12;
            // 
            // YLayoutPanel
            // 
            this.YLayoutPanel.ColumnCount = 1;
            this.YLayoutPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.YLayoutPanel.ImeMode = System.Windows.Forms.ImeMode.Off;
            this.YLayoutPanel.Location = new System.Drawing.Point(102, 53);
            this.YLayoutPanel.Name = "YLayoutPanel";
            this.YLayoutPanel.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.YLayoutPanel.RowCount = 1;
            this.YLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.YLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 263F));
            this.YLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 263F));
            this.YLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 263F));
            this.YLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 263F));
            this.YLayoutPanel.Size = new System.Drawing.Size(59, 263);
            this.YLayoutPanel.TabIndex = 13;
            // 
            // ZLayoutPanel
            // 
            this.ZLayoutPanel.ColumnCount = 1;
            this.ZLayoutPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.ZLayoutPanel.ImeMode = System.Windows.Forms.ImeMode.Off;
            this.ZLayoutPanel.Location = new System.Drawing.Point(192, 53);
            this.ZLayoutPanel.Name = "ZLayoutPanel";
            this.ZLayoutPanel.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.ZLayoutPanel.RowCount = 1;
            this.ZLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.ZLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 263F));
            this.ZLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 263F));
            this.ZLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 263F));
            this.ZLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 263F));
            this.ZLayoutPanel.Size = new System.Drawing.Size(59, 263);
            this.ZLayoutPanel.TabIndex = 14;
            // 
            // WLayoutPanel
            // 
            this.WLayoutPanel.ColumnCount = 1;
            this.WLayoutPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.WLayoutPanel.ImeMode = System.Windows.Forms.ImeMode.Off;
            this.WLayoutPanel.Location = new System.Drawing.Point(279, 53);
            this.WLayoutPanel.Name = "WLayoutPanel";
            this.WLayoutPanel.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.WLayoutPanel.RowCount = 1;
            this.WLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.WLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 263F));
            this.WLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 263F));
            this.WLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 263F));
            this.WLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 263F));
            this.WLayoutPanel.Size = new System.Drawing.Size(59, 263);
            this.WLayoutPanel.TabIndex = 15;
            // 
            // polynomeSizeBox
            // 
            this.polynomeSizeBox.FormattingEnabled = true;
            this.polynomeSizeBox.Items.AddRange(new object[] {
            "x + y",
            "x^2 + y",
            "x + y^2",
            "x^2 + y^2"});
            this.polynomeSizeBox.Location = new System.Drawing.Point(246, 6);
            this.polynomeSizeBox.Name = "polynomeSizeBox";
            this.polynomeSizeBox.Size = new System.Drawing.Size(121, 21);
            this.polynomeSizeBox.TabIndex = 16;
            // 
            // drawGraphButton
            // 
            this.drawGraphButton.Location = new System.Drawing.Point(396, 292);
            this.drawGraphButton.Name = "drawGraphButton";
            this.drawGraphButton.Size = new System.Drawing.Size(97, 23);
            this.drawGraphButton.TabIndex = 17;
            this.drawGraphButton.Text = "График";
            this.drawGraphButton.UseVisualStyleBackColor = true;
            this.drawGraphButton.Click += new System.EventHandler(this.drawGraphButton_Click);
            // 
            // MNKform
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(505, 338);
            this.Controls.Add(this.drawGraphButton);
            this.Controls.Add(this.polynomeSizeBox);
            this.Controls.Add(this.WLayoutPanel);
            this.Controls.Add(this.ZLayoutPanel);
            this.Controls.Add(this.YLayoutPanel);
            this.Controls.Add(this.tableLayoutPanel2);
            this.Controls.Add(this.answerLayout);
            this.Controls.Add(this.MNK_button);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.XLabel);
            this.Controls.Add(this.XLayoutPanel);
            this.Controls.Add(this.EditCount);
            this.Controls.Add(this.label1);
            this.Name = "MNKform";
            this.Text = "MNK";
            this.Load += new System.EventHandler(this.MNKform_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox EditCount;
        private System.Windows.Forms.TableLayoutPanel XLayoutPanel;
        private System.Windows.Forms.Label XLabel;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button MNK_button;
        private System.Windows.Forms.TableLayoutPanel answerLayout;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2;
        private System.Windows.Forms.TableLayoutPanel YLayoutPanel;
        private System.Windows.Forms.TableLayoutPanel ZLayoutPanel;
        private System.Windows.Forms.TableLayoutPanel WLayoutPanel;
        private System.Windows.Forms.ComboBox polynomeSizeBox;
        private System.Windows.Forms.Button drawGraphButton;
    }
}

