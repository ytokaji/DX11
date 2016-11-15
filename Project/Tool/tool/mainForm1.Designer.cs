namespace tool
{
	partial class mainForm1
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
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(mainForm1));
			this.tabControl1 = new System.Windows.Forms.TabControl();
			this.tabWater = new System.Windows.Forms.TabPage();
			this.tabPost = new System.Windows.Forms.TabPage();
			this.tabOther = new System.Windows.Forms.TabPage();
			this.menuStrip1 = new System.Windows.Forms.MenuStrip();
			this.menuFileFToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.newCreateNToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.fileOpenOToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.toolStripSeparator = new System.Windows.Forms.ToolStripSeparator();
			this.seveSToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.seveAsAToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
			this.exportStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
			this.exitXToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.toolStripContainer1 = new System.Windows.Forms.ToolStripContainer();
			this.toolStripContainer2 = new System.Windows.Forms.ToolStripContainer();
			this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
			this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
			this.tabFur = new System.Windows.Forms.TabPage();
			this.tabBump = new System.Windows.Forms.TabPage();
			this.tabControl1.SuspendLayout();
			this.menuStrip1.SuspendLayout();
			this.toolStripContainer1.SuspendLayout();
			this.toolStripContainer2.ContentPanel.SuspendLayout();
			this.toolStripContainer2.TopToolStripPanel.SuspendLayout();
			this.toolStripContainer2.SuspendLayout();
			this.SuspendLayout();
			// 
			// tabControl1
			// 
			this.tabControl1.Controls.Add(this.tabWater);
			this.tabControl1.Controls.Add(this.tabPost);
			this.tabControl1.Controls.Add(this.tabFur);
			this.tabControl1.Controls.Add(this.tabBump);
			this.tabControl1.Controls.Add(this.tabOther);
			this.tabControl1.Location = new System.Drawing.Point(0, 3);
			this.tabControl1.Name = "tabControl1";
			this.tabControl1.SelectedIndex = 0;
			this.tabControl1.Size = new System.Drawing.Size(384, 569);
			this.tabControl1.TabIndex = 0;
			// 
			// tabWater
			// 
			this.tabWater.AutoScroll = true;
			this.tabWater.BackColor = System.Drawing.Color.White;
			this.tabWater.Location = new System.Drawing.Point(4, 21);
			this.tabWater.Name = "tabWater";
			this.tabWater.Padding = new System.Windows.Forms.Padding(3);
			this.tabWater.Size = new System.Drawing.Size(376, 544);
			this.tabWater.TabIndex = 0;
			this.tabWater.Text = "water";
			// 
			// tabPost
			// 
			this.tabPost.Location = new System.Drawing.Point(4, 21);
			this.tabPost.Name = "tabPost";
			this.tabPost.Padding = new System.Windows.Forms.Padding(3);
			this.tabPost.Size = new System.Drawing.Size(376, 544);
			this.tabPost.TabIndex = 2;
			this.tabPost.Text = "post";
			this.tabPost.UseVisualStyleBackColor = true;
			// 
			// tabOther
			// 
			this.tabOther.Location = new System.Drawing.Point(4, 21);
			this.tabOther.Name = "tabOther";
			this.tabOther.Padding = new System.Windows.Forms.Padding(3);
			this.tabOther.Size = new System.Drawing.Size(376, 544);
			this.tabOther.TabIndex = 1;
			this.tabOther.Text = "others";
			this.tabOther.UseVisualStyleBackColor = true;
			// 
			// menuStrip1
			// 
			this.menuStrip1.Dock = System.Windows.Forms.DockStyle.None;
			this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menuFileFToolStripMenuItem});
			this.menuStrip1.Location = new System.Drawing.Point(0, 0);
			this.menuStrip1.Name = "menuStrip1";
			this.menuStrip1.Size = new System.Drawing.Size(384, 24);
			this.menuStrip1.TabIndex = 1;
			this.menuStrip1.Text = "menuStrip1";
			// 
			// menuFileFToolStripMenuItem
			// 
			this.menuFileFToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.newCreateNToolStripMenuItem,
            this.fileOpenOToolStripMenuItem,
            this.toolStripSeparator,
            this.seveSToolStripMenuItem,
            this.seveAsAToolStripMenuItem,
            this.toolStripSeparator1,
            this.exportStripMenuItem,
            this.toolStripSeparator2,
            this.exitXToolStripMenuItem});
			this.menuFileFToolStripMenuItem.Name = "menuFileFToolStripMenuItem";
			this.menuFileFToolStripMenuItem.Size = new System.Drawing.Size(66, 20);
			this.menuFileFToolStripMenuItem.Text = "ファイル(&F)";
			// 
			// newCreateNToolStripMenuItem
			// 
			this.newCreateNToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("newCreateNToolStripMenuItem.Image")));
			this.newCreateNToolStripMenuItem.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.newCreateNToolStripMenuItem.Name = "newCreateNToolStripMenuItem";
			this.newCreateNToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.N)));
			this.newCreateNToolStripMenuItem.Size = new System.Drawing.Size(179, 22);
			this.newCreateNToolStripMenuItem.Text = "新規作成(&N)";
			this.newCreateNToolStripMenuItem.Click += new System.EventHandler(this.newCreateNToolStripMenuItem_Click);
			// 
			// fileOpenOToolStripMenuItem
			// 
			this.fileOpenOToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("fileOpenOToolStripMenuItem.Image")));
			this.fileOpenOToolStripMenuItem.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.fileOpenOToolStripMenuItem.Name = "fileOpenOToolStripMenuItem";
			this.fileOpenOToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.O)));
			this.fileOpenOToolStripMenuItem.Size = new System.Drawing.Size(179, 22);
			this.fileOpenOToolStripMenuItem.Text = "開く(&O)";
			this.fileOpenOToolStripMenuItem.Click += new System.EventHandler(this.fileOpenOToolStripMenuItem_Click);
			// 
			// toolStripSeparator
			// 
			this.toolStripSeparator.Name = "toolStripSeparator";
			this.toolStripSeparator.Size = new System.Drawing.Size(176, 6);
			// 
			// seveSToolStripMenuItem
			// 
			this.seveSToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("seveSToolStripMenuItem.Image")));
			this.seveSToolStripMenuItem.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.seveSToolStripMenuItem.Name = "seveSToolStripMenuItem";
			this.seveSToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.S)));
			this.seveSToolStripMenuItem.Size = new System.Drawing.Size(179, 22);
			this.seveSToolStripMenuItem.Text = "上書き保存(&S)";
			this.seveSToolStripMenuItem.Click += new System.EventHandler(this.seveSToolStripMenuItem_Click);
			// 
			// seveAsAToolStripMenuItem
			// 
			this.seveAsAToolStripMenuItem.Name = "seveAsAToolStripMenuItem";
			this.seveAsAToolStripMenuItem.Size = new System.Drawing.Size(179, 22);
			this.seveAsAToolStripMenuItem.Text = "名前を付けて保存(&A)";
			this.seveAsAToolStripMenuItem.Click += new System.EventHandler(this.seveAsAToolStripMenuItem_Click);
			// 
			// toolStripSeparator1
			// 
			this.toolStripSeparator1.Name = "toolStripSeparator1";
			this.toolStripSeparator1.Size = new System.Drawing.Size(176, 6);
			// 
			// exportStripMenuItem
			// 
			this.exportStripMenuItem.Name = "exportStripMenuItem";
			this.exportStripMenuItem.Size = new System.Drawing.Size(179, 22);
			this.exportStripMenuItem.Text = "エクスポート";
			this.exportStripMenuItem.Click += new System.EventHandler(this.exportStripMenuItem_Click);
			// 
			// toolStripSeparator2
			// 
			this.toolStripSeparator2.Name = "toolStripSeparator2";
			this.toolStripSeparator2.Size = new System.Drawing.Size(176, 6);
			// 
			// exitXToolStripMenuItem
			// 
			this.exitXToolStripMenuItem.Name = "exitXToolStripMenuItem";
			this.exitXToolStripMenuItem.Size = new System.Drawing.Size(179, 22);
			this.exitXToolStripMenuItem.Text = "終了(&X)";
			this.exitXToolStripMenuItem.Click += new System.EventHandler(this.exitXToolStripMenuItem_Click);
			// 
			// toolStripContainer1
			// 
			this.toolStripContainer1.BottomToolStripPanelVisible = false;
			// 
			// toolStripContainer1.ContentPanel
			// 
			this.toolStripContainer1.ContentPanel.Size = new System.Drawing.Size(150, 150);
			this.toolStripContainer1.LeftToolStripPanelVisible = false;
			this.toolStripContainer1.Location = new System.Drawing.Point(3, -25);
			this.toolStripContainer1.Name = "toolStripContainer1";
			this.toolStripContainer1.RightToolStripPanelVisible = false;
			this.toolStripContainer1.Size = new System.Drawing.Size(150, 175);
			this.toolStripContainer1.TabIndex = 2;
			this.toolStripContainer1.Text = "toolStripContainer1";
			// 
			// toolStripContainer2
			// 
			this.toolStripContainer2.BottomToolStripPanelVisible = false;
			// 
			// toolStripContainer2.ContentPanel
			// 
			this.toolStripContainer2.ContentPanel.Controls.Add(this.tabControl1);
			this.toolStripContainer2.ContentPanel.Controls.Add(this.toolStripContainer1);
			this.toolStripContainer2.ContentPanel.Size = new System.Drawing.Size(384, 563);
			this.toolStripContainer2.Dock = System.Windows.Forms.DockStyle.Fill;
			this.toolStripContainer2.LeftToolStripPanelVisible = false;
			this.toolStripContainer2.Location = new System.Drawing.Point(0, 0);
			this.toolStripContainer2.Name = "toolStripContainer2";
			this.toolStripContainer2.RightToolStripPanelVisible = false;
			this.toolStripContainer2.Size = new System.Drawing.Size(384, 587);
			this.toolStripContainer2.TabIndex = 3;
			this.toolStripContainer2.Text = "toolStripContainer2";
			// 
			// toolStripContainer2.TopToolStripPanel
			// 
			this.toolStripContainer2.TopToolStripPanel.Controls.Add(this.menuStrip1);
			// 
			// openFileDialog1
			// 
			this.openFileDialog1.FileName = "openFileDialog1";
			// 
			// tabFur
			// 
			this.tabFur.Location = new System.Drawing.Point(4, 21);
			this.tabFur.Name = "tabFur";
			this.tabFur.Padding = new System.Windows.Forms.Padding(3);
			this.tabFur.Size = new System.Drawing.Size(376, 544);
			this.tabFur.TabIndex = 3;
			this.tabFur.Text = "fur";
			this.tabFur.UseVisualStyleBackColor = true;
			// 
			// tabBump
			// 
			this.tabBump.Location = new System.Drawing.Point(4, 21);
			this.tabBump.Name = "tabBump";
			this.tabBump.Padding = new System.Windows.Forms.Padding(3);
			this.tabBump.Size = new System.Drawing.Size(376, 544);
			this.tabBump.TabIndex = 4;
			this.tabBump.Text = "bump";
			this.tabBump.UseVisualStyleBackColor = true;
			// 
			// mainForm1
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.AutoSize = true;
			this.ClientSize = new System.Drawing.Size(384, 587);
			this.Controls.Add(this.toolStripContainer2);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
			this.MainMenuStrip = this.menuStrip1;
			this.MaximizeBox = false;
			this.Name = "mainForm1";
			this.Text = "mainForm1";
			this.Load += new System.EventHandler(this.mainForm1_Load);
			this.tabControl1.ResumeLayout(false);
			this.menuStrip1.ResumeLayout(false);
			this.menuStrip1.PerformLayout();
			this.toolStripContainer1.ResumeLayout(false);
			this.toolStripContainer1.PerformLayout();
			this.toolStripContainer2.ContentPanel.ResumeLayout(false);
			this.toolStripContainer2.TopToolStripPanel.ResumeLayout(false);
			this.toolStripContainer2.TopToolStripPanel.PerformLayout();
			this.toolStripContainer2.ResumeLayout(false);
			this.toolStripContainer2.PerformLayout();
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.TabControl tabControl1;
		private System.Windows.Forms.TabPage tabWater;
		private System.Windows.Forms.TabPage tabOther;
		private System.Windows.Forms.MenuStrip menuStrip1;
		private System.Windows.Forms.ToolStripMenuItem menuFileFToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem newCreateNToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem fileOpenOToolStripMenuItem;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator;
		private System.Windows.Forms.ToolStripMenuItem seveSToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem seveAsAToolStripMenuItem;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
		private System.Windows.Forms.ToolStripMenuItem exitXToolStripMenuItem;
		private System.Windows.Forms.ToolStripContainer toolStripContainer1;
		private System.Windows.Forms.ToolStripContainer toolStripContainer2;
		private System.Windows.Forms.SaveFileDialog saveFileDialog1;
		private System.Windows.Forms.OpenFileDialog openFileDialog1;
		private System.Windows.Forms.ToolStripMenuItem exportStripMenuItem;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
		private System.Windows.Forms.TabPage tabPost;
		private System.Windows.Forms.TabPage tabFur;
		private System.Windows.Forms.TabPage tabBump;
	}
}