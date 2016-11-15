namespace tool
{
	partial class bumpControl
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
			this.label2 = new System.Windows.Forms.Label();
			this.textBox_SpecularPower = new System.Windows.Forms.TextBox();
			this.trackBar_SpecularPower = new System.Windows.Forms.TrackBar();
			this.label1 = new System.Windows.Forms.Label();
			this.textBox_SpecularRange = new System.Windows.Forms.TextBox();
			this.trackBar_SpecularRange = new System.Windows.Forms.TrackBar();
			this.groupBox1.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.trackBar_SpecularPower)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.trackBar_SpecularRange)).BeginInit();
			this.SuspendLayout();
			// 
			// groupBox1
			// 
			this.groupBox1.Controls.Add(this.label2);
			this.groupBox1.Controls.Add(this.textBox_SpecularPower);
			this.groupBox1.Controls.Add(this.trackBar_SpecularPower);
			this.groupBox1.Controls.Add(this.label1);
			this.groupBox1.Controls.Add(this.textBox_SpecularRange);
			this.groupBox1.Controls.Add(this.trackBar_SpecularRange);
			this.groupBox1.Location = new System.Drawing.Point(6, 3);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size(344, 79);
			this.groupBox1.TabIndex = 7;
			this.groupBox1.TabStop = false;
			this.groupBox1.Text = "スペキュラ";
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Location = new System.Drawing.Point(6, 51);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(84, 12);
			this.label2.TabIndex = 9;
			this.label2.Text = "スペキュラの強度";
			// 
			// textBox_SpecularPower
			// 
			this.textBox_SpecularPower.Enabled = false;
			this.textBox_SpecularPower.Location = new System.Drawing.Point(104, 48);
			this.textBox_SpecularPower.Name = "textBox_SpecularPower";
			this.textBox_SpecularPower.Size = new System.Drawing.Size(70, 19);
			this.textBox_SpecularPower.TabIndex = 8;
			// 
			// trackBar_SpecularPower
			// 
			this.trackBar_SpecularPower.AutoSize = false;
			this.trackBar_SpecularPower.BackColor = System.Drawing.SystemColors.Window;
			this.trackBar_SpecularPower.LargeChange = 10;
			this.trackBar_SpecularPower.Location = new System.Drawing.Point(180, 48);
			this.trackBar_SpecularPower.Maximum = 100;
			this.trackBar_SpecularPower.Name = "trackBar_SpecularPower";
			this.trackBar_SpecularPower.Size = new System.Drawing.Size(153, 24);
			this.trackBar_SpecularPower.TabIndex = 7;
			this.trackBar_SpecularPower.TickFrequency = 0;
			this.trackBar_SpecularPower.TickStyle = System.Windows.Forms.TickStyle.None;
			this.trackBar_SpecularPower.Scroll += new System.EventHandler(this.trackBar_SpecularPower_Scroll);
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(6, 21);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(84, 12);
			this.label1.TabIndex = 6;
			this.label1.Text = "スペキュラの範囲";
			// 
			// textBox_SpecularRange
			// 
			this.textBox_SpecularRange.Enabled = false;
			this.textBox_SpecularRange.Location = new System.Drawing.Point(104, 18);
			this.textBox_SpecularRange.Name = "textBox_SpecularRange";
			this.textBox_SpecularRange.Size = new System.Drawing.Size(70, 19);
			this.textBox_SpecularRange.TabIndex = 5;
			// 
			// trackBar_SpecularRange
			// 
			this.trackBar_SpecularRange.AutoSize = false;
			this.trackBar_SpecularRange.BackColor = System.Drawing.SystemColors.Window;
			this.trackBar_SpecularRange.LargeChange = 10;
			this.trackBar_SpecularRange.Location = new System.Drawing.Point(180, 18);
			this.trackBar_SpecularRange.Maximum = 100;
			this.trackBar_SpecularRange.Name = "trackBar_SpecularRange";
			this.trackBar_SpecularRange.Size = new System.Drawing.Size(153, 24);
			this.trackBar_SpecularRange.TabIndex = 4;
			this.trackBar_SpecularRange.TickFrequency = 0;
			this.trackBar_SpecularRange.TickStyle = System.Windows.Forms.TickStyle.None;
			this.trackBar_SpecularRange.Scroll += new System.EventHandler(this.trackBar_SpecularRange_Scroll);
			// 
			// bumpControl
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.Controls.Add(this.groupBox1);
			this.Name = "bumpControl";
			this.Size = new System.Drawing.Size(353, 580);
			this.groupBox1.ResumeLayout(false);
			this.groupBox1.PerformLayout();
			((System.ComponentModel.ISupportInitialize)(this.trackBar_SpecularPower)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.trackBar_SpecularRange)).EndInit();
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.GroupBox groupBox1;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.TextBox textBox_SpecularPower;
		private System.Windows.Forms.TrackBar trackBar_SpecularPower;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.TextBox textBox_SpecularRange;
		private System.Windows.Forms.TrackBar trackBar_SpecularRange;
	}
}
