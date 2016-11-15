namespace tool
{
	partial class other
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
			this.button_shaderReload = new System.Windows.Forms.Button();
			this.groupBox1 = new System.Windows.Forms.GroupBox();
			this.label3 = new System.Windows.Forms.Label();
			this.textBox_LightDir_Z = new System.Windows.Forms.TextBox();
			this.trackBar_LightDir_Z = new System.Windows.Forms.TrackBar();
			this.label2 = new System.Windows.Forms.Label();
			this.textBox_LightDir_Y = new System.Windows.Forms.TextBox();
			this.trackBar_LightDir_Y = new System.Windows.Forms.TrackBar();
			this.label1 = new System.Windows.Forms.Label();
			this.textBox_LightDir_X = new System.Windows.Forms.TextBox();
			this.trackBar_LightDir_X = new System.Windows.Forms.TrackBar();
			this.groupBox1.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.trackBar_LightDir_Z)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.trackBar_LightDir_Y)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.trackBar_LightDir_X)).BeginInit();
			this.SuspendLayout();
			// 
			// button_shaderReload
			// 
			this.button_shaderReload.Location = new System.Drawing.Point(31, 117);
			this.button_shaderReload.Name = "button_shaderReload";
			this.button_shaderReload.Size = new System.Drawing.Size(295, 22);
			this.button_shaderReload.TabIndex = 0;
			this.button_shaderReload.Text = "シェーダリロード要求";
			this.button_shaderReload.UseVisualStyleBackColor = true;
			this.button_shaderReload.Click += new System.EventHandler(this.button_shaderReload_Click);
			// 
			// groupBox1
			// 
			this.groupBox1.Controls.Add(this.label3);
			this.groupBox1.Controls.Add(this.textBox_LightDir_Z);
			this.groupBox1.Controls.Add(this.trackBar_LightDir_Z);
			this.groupBox1.Controls.Add(this.label2);
			this.groupBox1.Controls.Add(this.textBox_LightDir_Y);
			this.groupBox1.Controls.Add(this.trackBar_LightDir_Y);
			this.groupBox1.Controls.Add(this.label1);
			this.groupBox1.Controls.Add(this.textBox_LightDir_X);
			this.groupBox1.Controls.Add(this.trackBar_LightDir_X);
			this.groupBox1.Location = new System.Drawing.Point(3, 3);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size(344, 108);
			this.groupBox1.TabIndex = 6;
			this.groupBox1.TabStop = false;
			this.groupBox1.Text = "ディレクショナルライト方向";
			// 
			// label3
			// 
			this.label3.AutoSize = true;
			this.label3.Location = new System.Drawing.Point(6, 81);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(12, 12);
			this.label3.TabIndex = 12;
			this.label3.Text = "Z";
			// 
			// textBox_LightDir_Z
			// 
			this.textBox_LightDir_Z.Enabled = false;
			this.textBox_LightDir_Z.Location = new System.Drawing.Point(104, 78);
			this.textBox_LightDir_Z.Name = "textBox_LightDir_Z";
			this.textBox_LightDir_Z.Size = new System.Drawing.Size(70, 19);
			this.textBox_LightDir_Z.TabIndex = 11;
			// 
			// trackBar_LightDir_Z
			// 
			this.trackBar_LightDir_Z.AutoSize = false;
			this.trackBar_LightDir_Z.BackColor = System.Drawing.SystemColors.Window;
			this.trackBar_LightDir_Z.LargeChange = 10;
			this.trackBar_LightDir_Z.Location = new System.Drawing.Point(180, 78);
			this.trackBar_LightDir_Z.Maximum = 100;
			this.trackBar_LightDir_Z.Name = "trackBar_LightDir_Z";
			this.trackBar_LightDir_Z.Size = new System.Drawing.Size(153, 24);
			this.trackBar_LightDir_Z.TabIndex = 10;
			this.trackBar_LightDir_Z.TickFrequency = 0;
			this.trackBar_LightDir_Z.TickStyle = System.Windows.Forms.TickStyle.None;
			this.trackBar_LightDir_Z.Scroll += new System.EventHandler(this.trackBar_LightDir_Z_Scroll);
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Location = new System.Drawing.Point(6, 51);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(12, 12);
			this.label2.TabIndex = 9;
			this.label2.Text = "Y";
			// 
			// textBox_LightDir_Y
			// 
			this.textBox_LightDir_Y.Enabled = false;
			this.textBox_LightDir_Y.Location = new System.Drawing.Point(104, 48);
			this.textBox_LightDir_Y.Name = "textBox_LightDir_Y";
			this.textBox_LightDir_Y.Size = new System.Drawing.Size(70, 19);
			this.textBox_LightDir_Y.TabIndex = 8;
			// 
			// trackBar_LightDir_Y
			// 
			this.trackBar_LightDir_Y.AutoSize = false;
			this.trackBar_LightDir_Y.BackColor = System.Drawing.SystemColors.Window;
			this.trackBar_LightDir_Y.LargeChange = 10;
			this.trackBar_LightDir_Y.Location = new System.Drawing.Point(180, 48);
			this.trackBar_LightDir_Y.Maximum = 100;
			this.trackBar_LightDir_Y.Name = "trackBar_LightDir_Y";
			this.trackBar_LightDir_Y.Size = new System.Drawing.Size(153, 24);
			this.trackBar_LightDir_Y.TabIndex = 7;
			this.trackBar_LightDir_Y.TickFrequency = 0;
			this.trackBar_LightDir_Y.TickStyle = System.Windows.Forms.TickStyle.None;
			this.trackBar_LightDir_Y.Scroll += new System.EventHandler(this.trackBar_LightDir_Y_Scroll);
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(6, 21);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(12, 12);
			this.label1.TabIndex = 6;
			this.label1.Text = "X";
			// 
			// textBox_LightDir_X
			// 
			this.textBox_LightDir_X.Enabled = false;
			this.textBox_LightDir_X.Location = new System.Drawing.Point(104, 18);
			this.textBox_LightDir_X.Name = "textBox_LightDir_X";
			this.textBox_LightDir_X.Size = new System.Drawing.Size(70, 19);
			this.textBox_LightDir_X.TabIndex = 5;
			// 
			// trackBar_LightDir_X
			// 
			this.trackBar_LightDir_X.AutoSize = false;
			this.trackBar_LightDir_X.BackColor = System.Drawing.SystemColors.Window;
			this.trackBar_LightDir_X.LargeChange = 10;
			this.trackBar_LightDir_X.Location = new System.Drawing.Point(180, 18);
			this.trackBar_LightDir_X.Maximum = 100;
			this.trackBar_LightDir_X.Name = "trackBar_LightDir_X";
			this.trackBar_LightDir_X.Size = new System.Drawing.Size(153, 24);
			this.trackBar_LightDir_X.TabIndex = 4;
			this.trackBar_LightDir_X.TickFrequency = 0;
			this.trackBar_LightDir_X.TickStyle = System.Windows.Forms.TickStyle.None;
			this.trackBar_LightDir_X.Scroll += new System.EventHandler(this.trackBar_LightDir_X_Scroll);
			// 
			// other
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.Controls.Add(this.groupBox1);
			this.Controls.Add(this.button_shaderReload);
			this.Name = "other";
			this.Size = new System.Drawing.Size(353, 580);
			this.groupBox1.ResumeLayout(false);
			this.groupBox1.PerformLayout();
			((System.ComponentModel.ISupportInitialize)(this.trackBar_LightDir_Z)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.trackBar_LightDir_Y)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.trackBar_LightDir_X)).EndInit();
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.Button button_shaderReload;
		private System.Windows.Forms.GroupBox groupBox1;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.TextBox textBox_LightDir_Z;
		private System.Windows.Forms.TrackBar trackBar_LightDir_Z;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.TextBox textBox_LightDir_Y;
		private System.Windows.Forms.TrackBar trackBar_LightDir_Y;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.TextBox textBox_LightDir_X;
		private System.Windows.Forms.TrackBar trackBar_LightDir_X;
	}
}
