namespace tool
{
	partial class postControl
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
			this.checkBox_Bloom = new System.Windows.Forms.CheckBox();
			this.label1 = new System.Windows.Forms.Label();
			this.textBox_BrightnessBias = new System.Windows.Forms.TextBox();
			this.trackBar_BrightnessBias = new System.Windows.Forms.TrackBar();
			this.groupBox2 = new System.Windows.Forms.GroupBox();
			this.checkBox_Dof = new System.Windows.Forms.CheckBox();
			this.label2 = new System.Windows.Forms.Label();
			this.textBox_FocusRange = new System.Windows.Forms.TextBox();
			this.trackBar_FocusRange = new System.Windows.Forms.TrackBar();
			this.label5 = new System.Windows.Forms.Label();
			this.textBox_FocusDistance = new System.Windows.Forms.TextBox();
			this.trackBar_FocusDistance = new System.Windows.Forms.TrackBar();
			this.groupBox1.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.trackBar_BrightnessBias)).BeginInit();
			this.groupBox2.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.trackBar_FocusRange)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.trackBar_FocusDistance)).BeginInit();
			this.SuspendLayout();
			// 
			// groupBox1
			// 
			this.groupBox1.Controls.Add(this.checkBox_Bloom);
			this.groupBox1.Controls.Add(this.label1);
			this.groupBox1.Controls.Add(this.textBox_BrightnessBias);
			this.groupBox1.Controls.Add(this.trackBar_BrightnessBias);
			this.groupBox1.Location = new System.Drawing.Point(6, 3);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size(344, 69);
			this.groupBox1.TabIndex = 5;
			this.groupBox1.TabStop = false;
			this.groupBox1.Text = "ブルーﾑ";
			// 
			// checkBox_Bloom
			// 
			this.checkBox_Bloom.AutoSize = true;
			this.checkBox_Bloom.Location = new System.Drawing.Point(6, 18);
			this.checkBox_Bloom.Name = "checkBox_Bloom";
			this.checkBox_Bloom.Size = new System.Drawing.Size(68, 16);
			this.checkBox_Bloom.TabIndex = 7;
			this.checkBox_Bloom.Text = "ON/OFF";
			this.checkBox_Bloom.UseVisualStyleBackColor = true;
			this.checkBox_Bloom.CheckedChanged += new System.EventHandler(this.checkBox_Bloom_CheckedChanged);
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(6, 37);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(29, 12);
			this.label1.TabIndex = 6;
			this.label1.Text = "輝度";
			// 
			// textBox_BrightnessBias
			// 
			this.textBox_BrightnessBias.Enabled = false;
			this.textBox_BrightnessBias.Location = new System.Drawing.Point(104, 34);
			this.textBox_BrightnessBias.Name = "textBox_BrightnessBias";
			this.textBox_BrightnessBias.Size = new System.Drawing.Size(70, 19);
			this.textBox_BrightnessBias.TabIndex = 5;
			// 
			// trackBar_BrightnessBias
			// 
			this.trackBar_BrightnessBias.AutoSize = false;
			this.trackBar_BrightnessBias.BackColor = System.Drawing.SystemColors.Window;
			this.trackBar_BrightnessBias.LargeChange = 10;
			this.trackBar_BrightnessBias.Location = new System.Drawing.Point(180, 34);
			this.trackBar_BrightnessBias.Maximum = 100;
			this.trackBar_BrightnessBias.Name = "trackBar_BrightnessBias";
			this.trackBar_BrightnessBias.Size = new System.Drawing.Size(153, 24);
			this.trackBar_BrightnessBias.TabIndex = 4;
			this.trackBar_BrightnessBias.TickFrequency = 0;
			this.trackBar_BrightnessBias.TickStyle = System.Windows.Forms.TickStyle.None;
			this.trackBar_BrightnessBias.Scroll += new System.EventHandler(this.trackBar_BrightnessBias_Scroll);
			// 
			// groupBox2
			// 
			this.groupBox2.Controls.Add(this.checkBox_Dof);
			this.groupBox2.Controls.Add(this.label2);
			this.groupBox2.Controls.Add(this.textBox_FocusRange);
			this.groupBox2.Controls.Add(this.trackBar_FocusRange);
			this.groupBox2.Controls.Add(this.label5);
			this.groupBox2.Controls.Add(this.textBox_FocusDistance);
			this.groupBox2.Controls.Add(this.trackBar_FocusDistance);
			this.groupBox2.Location = new System.Drawing.Point(6, 78);
			this.groupBox2.Name = "groupBox2";
			this.groupBox2.Size = new System.Drawing.Size(344, 95);
			this.groupBox2.TabIndex = 6;
			this.groupBox2.TabStop = false;
			this.groupBox2.Text = "被写界深度";
			// 
			// checkBox_Dof
			// 
			this.checkBox_Dof.AutoSize = true;
			this.checkBox_Dof.Location = new System.Drawing.Point(6, 18);
			this.checkBox_Dof.Name = "checkBox_Dof";
			this.checkBox_Dof.Size = new System.Drawing.Size(68, 16);
			this.checkBox_Dof.TabIndex = 8;
			this.checkBox_Dof.Text = "ON/OFF";
			this.checkBox_Dof.UseVisualStyleBackColor = true;
			this.checkBox_Dof.CheckedChanged += new System.EventHandler(this.checkBox_Dof_CheckedChanged);
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Location = new System.Drawing.Point(4, 67);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(73, 12);
			this.label2.TabIndex = 9;
			this.label2.Text = "フォーカス範囲";
			// 
			// textBox_FocusRange
			// 
			this.textBox_FocusRange.Enabled = false;
			this.textBox_FocusRange.Location = new System.Drawing.Point(102, 64);
			this.textBox_FocusRange.Name = "textBox_FocusRange";
			this.textBox_FocusRange.Size = new System.Drawing.Size(70, 19);
			this.textBox_FocusRange.TabIndex = 8;
			// 
			// trackBar_FocusRange
			// 
			this.trackBar_FocusRange.AutoSize = false;
			this.trackBar_FocusRange.BackColor = System.Drawing.SystemColors.Window;
			this.trackBar_FocusRange.LargeChange = 10;
			this.trackBar_FocusRange.Location = new System.Drawing.Point(178, 64);
			this.trackBar_FocusRange.Maximum = 100;
			this.trackBar_FocusRange.Name = "trackBar_FocusRange";
			this.trackBar_FocusRange.Size = new System.Drawing.Size(153, 24);
			this.trackBar_FocusRange.TabIndex = 7;
			this.trackBar_FocusRange.TickFrequency = 0;
			this.trackBar_FocusRange.TickStyle = System.Windows.Forms.TickStyle.None;
			this.trackBar_FocusRange.Scroll += new System.EventHandler(this.trackBar_FocusRange_Scroll);
			// 
			// label5
			// 
			this.label5.AutoSize = true;
			this.label5.Location = new System.Drawing.Point(4, 37);
			this.label5.Name = "label5";
			this.label5.Size = new System.Drawing.Size(73, 12);
			this.label5.TabIndex = 6;
			this.label5.Text = "フォーカス距離";
			// 
			// textBox_FocusDistance
			// 
			this.textBox_FocusDistance.Enabled = false;
			this.textBox_FocusDistance.Location = new System.Drawing.Point(102, 34);
			this.textBox_FocusDistance.Name = "textBox_FocusDistance";
			this.textBox_FocusDistance.Size = new System.Drawing.Size(70, 19);
			this.textBox_FocusDistance.TabIndex = 5;
			// 
			// trackBar_FocusDistance
			// 
			this.trackBar_FocusDistance.AutoSize = false;
			this.trackBar_FocusDistance.BackColor = System.Drawing.SystemColors.Window;
			this.trackBar_FocusDistance.LargeChange = 10;
			this.trackBar_FocusDistance.Location = new System.Drawing.Point(178, 34);
			this.trackBar_FocusDistance.Maximum = 100;
			this.trackBar_FocusDistance.Name = "trackBar_FocusDistance";
			this.trackBar_FocusDistance.Size = new System.Drawing.Size(153, 24);
			this.trackBar_FocusDistance.TabIndex = 4;
			this.trackBar_FocusDistance.TickFrequency = 0;
			this.trackBar_FocusDistance.TickStyle = System.Windows.Forms.TickStyle.None;
			this.trackBar_FocusDistance.Scroll += new System.EventHandler(this.trackBar_FocusDistance_Scroll);
			// 
			// postControl
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.Controls.Add(this.groupBox2);
			this.Controls.Add(this.groupBox1);
			this.Name = "postControl";
			this.Size = new System.Drawing.Size(353, 580);
			this.groupBox1.ResumeLayout(false);
			this.groupBox1.PerformLayout();
			((System.ComponentModel.ISupportInitialize)(this.trackBar_BrightnessBias)).EndInit();
			this.groupBox2.ResumeLayout(false);
			this.groupBox2.PerformLayout();
			((System.ComponentModel.ISupportInitialize)(this.trackBar_FocusRange)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.trackBar_FocusDistance)).EndInit();
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.GroupBox groupBox1;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.TextBox textBox_BrightnessBias;
		private System.Windows.Forms.TrackBar trackBar_BrightnessBias;
		private System.Windows.Forms.GroupBox groupBox2;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.TextBox textBox_FocusRange;
		private System.Windows.Forms.TrackBar trackBar_FocusRange;
		private System.Windows.Forms.Label label5;
		private System.Windows.Forms.TextBox textBox_FocusDistance;
		private System.Windows.Forms.TrackBar trackBar_FocusDistance;
		private System.Windows.Forms.CheckBox checkBox_Bloom;
		private System.Windows.Forms.CheckBox checkBox_Dof;
	}
}
