namespace tool
{
	partial class furControl
	{
		/// <summary> 
		/// 必要なデザイナー変数です。
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary> 
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
		/// <param name="disposing">マネージ リソースが破棄される場合 true、破棄されない場合は false です。</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region コンポーネント デザイナーで生成されたコード

		/// <summary> 
		/// デザイナー サポートに必要なメソッドです。このメソッドの内容を 
		/// コード エディターで変更しないでください。
		/// </summary>
		private void InitializeComponent()
		{
			this.groupBox1 = new System.Windows.Forms.GroupBox();
			this.label3 = new System.Windows.Forms.Label();
			this.textBox_ColorB = new System.Windows.Forms.TextBox();
			this.trackBar_ColorB = new System.Windows.Forms.TrackBar();
			this.label2 = new System.Windows.Forms.Label();
			this.textBox_ColorG = new System.Windows.Forms.TextBox();
			this.trackBar_ColorG = new System.Windows.Forms.TrackBar();
			this.label1 = new System.Windows.Forms.Label();
			this.textBox_ColorR = new System.Windows.Forms.TextBox();
			this.trackBar_ColorR = new System.Windows.Forms.TrackBar();
			this.label4 = new System.Windows.Forms.Label();
			this.textBox_FurDistance = new System.Windows.Forms.TextBox();
			this.trackBar_FurDistance = new System.Windows.Forms.TrackBar();
			this.label5 = new System.Windows.Forms.Label();
			this.textBox_FurNum = new System.Windows.Forms.TextBox();
			this.trackBar_FurNum = new System.Windows.Forms.TrackBar();
			this.groupBox1.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.trackBar_ColorB)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.trackBar_ColorG)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.trackBar_ColorR)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.trackBar_FurDistance)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.trackBar_FurNum)).BeginInit();
			this.SuspendLayout();
			// 
			// groupBox1
			// 
			this.groupBox1.Controls.Add(this.label3);
			this.groupBox1.Controls.Add(this.textBox_ColorB);
			this.groupBox1.Controls.Add(this.trackBar_ColorB);
			this.groupBox1.Controls.Add(this.label2);
			this.groupBox1.Controls.Add(this.textBox_ColorG);
			this.groupBox1.Controls.Add(this.trackBar_ColorG);
			this.groupBox1.Controls.Add(this.label1);
			this.groupBox1.Controls.Add(this.textBox_ColorR);
			this.groupBox1.Controls.Add(this.trackBar_ColorR);
			this.groupBox1.Location = new System.Drawing.Point(3, 3);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size(344, 111);
			this.groupBox1.TabIndex = 5;
			this.groupBox1.TabStop = false;
			this.groupBox1.Text = "基本色味";
			// 
			// label3
			// 
			this.label3.AutoSize = true;
			this.label3.Location = new System.Drawing.Point(6, 81);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(13, 12);
			this.label3.TabIndex = 12;
			this.label3.Text = "B";
			// 
			// textBox_ColorB
			// 
			this.textBox_ColorB.Enabled = false;
			this.textBox_ColorB.Location = new System.Drawing.Point(104, 78);
			this.textBox_ColorB.Name = "textBox_ColorB";
			this.textBox_ColorB.Size = new System.Drawing.Size(70, 19);
			this.textBox_ColorB.TabIndex = 11;
			// 
			// trackBar_ColorB
			// 
			this.trackBar_ColorB.AutoSize = false;
			this.trackBar_ColorB.BackColor = System.Drawing.SystemColors.Window;
			this.trackBar_ColorB.LargeChange = 10;
			this.trackBar_ColorB.Location = new System.Drawing.Point(180, 78);
			this.trackBar_ColorB.Maximum = 100;
			this.trackBar_ColorB.Name = "trackBar_ColorB";
			this.trackBar_ColorB.Size = new System.Drawing.Size(153, 24);
			this.trackBar_ColorB.TabIndex = 10;
			this.trackBar_ColorB.TickFrequency = 0;
			this.trackBar_ColorB.TickStyle = System.Windows.Forms.TickStyle.None;
			this.trackBar_ColorB.Scroll += new System.EventHandler(this.trackBar_ColorB_Scroll);
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Location = new System.Drawing.Point(6, 51);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(13, 12);
			this.label2.TabIndex = 9;
			this.label2.Text = "G";
			// 
			// textBox_ColorG
			// 
			this.textBox_ColorG.Enabled = false;
			this.textBox_ColorG.Location = new System.Drawing.Point(104, 48);
			this.textBox_ColorG.Name = "textBox_ColorG";
			this.textBox_ColorG.Size = new System.Drawing.Size(70, 19);
			this.textBox_ColorG.TabIndex = 8;
			// 
			// trackBar_ColorG
			// 
			this.trackBar_ColorG.AutoSize = false;
			this.trackBar_ColorG.BackColor = System.Drawing.SystemColors.Window;
			this.trackBar_ColorG.LargeChange = 10;
			this.trackBar_ColorG.Location = new System.Drawing.Point(180, 48);
			this.trackBar_ColorG.Maximum = 100;
			this.trackBar_ColorG.Name = "trackBar_ColorG";
			this.trackBar_ColorG.Size = new System.Drawing.Size(153, 24);
			this.trackBar_ColorG.TabIndex = 7;
			this.trackBar_ColorG.TickFrequency = 0;
			this.trackBar_ColorG.TickStyle = System.Windows.Forms.TickStyle.None;
			this.trackBar_ColorG.Scroll += new System.EventHandler(this.trackBar_ColorG_Scroll);
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(6, 21);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(13, 12);
			this.label1.TabIndex = 6;
			this.label1.Text = "R";
			// 
			// textBox_ColorR
			// 
			this.textBox_ColorR.Enabled = false;
			this.textBox_ColorR.Location = new System.Drawing.Point(104, 18);
			this.textBox_ColorR.Name = "textBox_ColorR";
			this.textBox_ColorR.Size = new System.Drawing.Size(70, 19);
			this.textBox_ColorR.TabIndex = 5;
			// 
			// trackBar_ColorR
			// 
			this.trackBar_ColorR.AutoSize = false;
			this.trackBar_ColorR.BackColor = System.Drawing.SystemColors.Window;
			this.trackBar_ColorR.LargeChange = 10;
			this.trackBar_ColorR.Location = new System.Drawing.Point(180, 18);
			this.trackBar_ColorR.Maximum = 100;
			this.trackBar_ColorR.Name = "trackBar_ColorR";
			this.trackBar_ColorR.Size = new System.Drawing.Size(153, 24);
			this.trackBar_ColorR.TabIndex = 4;
			this.trackBar_ColorR.TickFrequency = 0;
			this.trackBar_ColorR.TickStyle = System.Windows.Forms.TickStyle.None;
			this.trackBar_ColorR.Scroll += new System.EventHandler(this.trackBar_ColorR_Scroll);
			// 
			// label4
			// 
			this.label4.AutoSize = true;
			this.label4.Location = new System.Drawing.Point(9, 127);
			this.label4.Name = "label4";
			this.label4.Size = new System.Drawing.Size(29, 12);
			this.label4.TabIndex = 15;
			this.label4.Text = "距離";
			// 
			// textBox_FurDistance
			// 
			this.textBox_FurDistance.Enabled = false;
			this.textBox_FurDistance.Location = new System.Drawing.Point(107, 124);
			this.textBox_FurDistance.Name = "textBox_FurDistance";
			this.textBox_FurDistance.Size = new System.Drawing.Size(70, 19);
			this.textBox_FurDistance.TabIndex = 14;
			// 
			// trackBar_FurDistance
			// 
			this.trackBar_FurDistance.AutoSize = false;
			this.trackBar_FurDistance.BackColor = System.Drawing.SystemColors.Window;
			this.trackBar_FurDistance.LargeChange = 10;
			this.trackBar_FurDistance.Location = new System.Drawing.Point(183, 124);
			this.trackBar_FurDistance.Maximum = 100;
			this.trackBar_FurDistance.Name = "trackBar_FurDistance";
			this.trackBar_FurDistance.Size = new System.Drawing.Size(153, 24);
			this.trackBar_FurDistance.TabIndex = 13;
			this.trackBar_FurDistance.TickFrequency = 0;
			this.trackBar_FurDistance.TickStyle = System.Windows.Forms.TickStyle.None;
			this.trackBar_FurDistance.Scroll += new System.EventHandler(this.trackBarFurDistance_Scroll);
			// 
			// label5
			// 
			this.label5.AutoSize = true;
			this.label5.Location = new System.Drawing.Point(9, 157);
			this.label5.Name = "label5";
			this.label5.Size = new System.Drawing.Size(17, 12);
			this.label5.TabIndex = 18;
			this.label5.Text = "数";
			// 
			// textBox_FurNum
			// 
			this.textBox_FurNum.Enabled = false;
			this.textBox_FurNum.Location = new System.Drawing.Point(107, 154);
			this.textBox_FurNum.Name = "textBox_FurNum";
			this.textBox_FurNum.Size = new System.Drawing.Size(70, 19);
			this.textBox_FurNum.TabIndex = 17;
			// 
			// trackBar_FurNum
			// 
			this.trackBar_FurNum.AutoSize = false;
			this.trackBar_FurNum.BackColor = System.Drawing.SystemColors.Window;
			this.trackBar_FurNum.LargeChange = 10;
			this.trackBar_FurNum.Location = new System.Drawing.Point(183, 154);
			this.trackBar_FurNum.Maximum = 100;
			this.trackBar_FurNum.Name = "trackBar_FurNum";
			this.trackBar_FurNum.Size = new System.Drawing.Size(153, 24);
			this.trackBar_FurNum.TabIndex = 16;
			this.trackBar_FurNum.TickFrequency = 0;
			this.trackBar_FurNum.TickStyle = System.Windows.Forms.TickStyle.None;
			this.trackBar_FurNum.Scroll += new System.EventHandler(this.trackBar_FurNum_Scroll);
			// 
			// furControl
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.Controls.Add(this.label5);
			this.Controls.Add(this.textBox_FurNum);
			this.Controls.Add(this.trackBar_FurNum);
			this.Controls.Add(this.label4);
			this.Controls.Add(this.textBox_FurDistance);
			this.Controls.Add(this.groupBox1);
			this.Controls.Add(this.trackBar_FurDistance);
			this.Name = "furControl";
			this.Size = new System.Drawing.Size(353, 580);
			this.groupBox1.ResumeLayout(false);
			this.groupBox1.PerformLayout();
			((System.ComponentModel.ISupportInitialize)(this.trackBar_ColorB)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.trackBar_ColorG)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.trackBar_ColorR)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.trackBar_FurDistance)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.trackBar_FurNum)).EndInit();
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.GroupBox groupBox1;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.TextBox textBox_ColorB;
		private System.Windows.Forms.TrackBar trackBar_ColorB;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.TextBox textBox_ColorG;
		private System.Windows.Forms.TrackBar trackBar_ColorG;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.TextBox textBox_ColorR;
		private System.Windows.Forms.TrackBar trackBar_ColorR;
		private System.Windows.Forms.Label label4;
		private System.Windows.Forms.TextBox textBox_FurDistance;
		private System.Windows.Forms.TrackBar trackBar_FurDistance;
		private System.Windows.Forms.Label label5;
		private System.Windows.Forms.TextBox textBox_FurNum;
		private System.Windows.Forms.TrackBar trackBar_FurNum;
	}
}
