using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Runtime.InteropServices;


namespace tool
{
	public partial class mainForm1 : Form
	{
		/// <summary>
		/// 作成
		/// </summary>
		public mainForm1()
		{
			InitializeComponent();
			tabWater.Controls.Add(m_Water);
			tabPost.Controls.Add(m_Post);
			tabFur.Controls.Add(m_Fur);
			tabBump.Controls.Add(m_Bump);
			tabOther.Controls.Add(m_other);
		}

		/// <summary>
		/// 起動時
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void mainForm1_Load(object sender, EventArgs e)
		{
			initParam();
		}
		#region メニューコマンド
		private void newCreateNToolStripMenuItem_Click(object sender, EventArgs e)
		{
			initParam();
		}

		private void fileOpenOToolStripMenuItem_Click(object sender, EventArgs e)
		{
			m_sFileName = loadFileDialog();
			CSendMsg.getInstance().load(ref m_sFileName);

			if (m_sFileName != null && m_sFileName.Length > 0)
			{
				m_Water.initParam();
				m_Post.initParam();
				m_Fur.initParam();
				m_Bump.initParam();
				m_other.initParam();
			}
		}

		private void seveSToolStripMenuItem_Click(object sender, EventArgs e)
		{
			if (m_sFileName.Length == 0)
			{
				m_sFileName = saveFileDialog();
			}

			CSendMsg.getInstance().save(ref m_sFileName);
		}

		private void seveAsAToolStripMenuItem_Click(object sender, EventArgs e)
		{
			m_sFileName = saveFileDialog();
			CSendMsg.getInstance().save(ref m_sFileName);
		}

		private void exportStripMenuItem_Click(object sender, EventArgs e)
		{
			m_sExportFileName = exportDialog();
			CSendMsg.getInstance().export(ref m_sExportFileName);			
		}

		private void exitXToolStripMenuItem_Click(object sender, EventArgs e)
		{
			Environment.Exit(0);
		}
		#endregion
		#region privetメソッド
		/// <summary>
		/// パラメータ初期化
		/// </summary>
		private void initParam()
		{
			// パラメータ初期化
			CSendMsg msg = CSendMsg.getInstance();
			msg.m_shaderData = new CSendMsg.SShaderParam(CSendMsg.SHADER_PARAM_ID);

			m_Water.initParam();
			m_Post.initParam();
			m_Fur.initParam();
			m_Bump.initParam();
			m_other.initParam();
		}

		/// <summary>
		/// ファイルロードダイアログを表示
		/// </summary>
		/// <returns>選択されたファイル。キャンセルされた場合は文字数０</returns>
		private string loadFileDialog()
		{
			string sName = "";

			openFileDialog1.FileName = "";
			openFileDialog1.Filter = "シェーダーパラメータXML(*.spxm;)|*.spxm";
			openFileDialog1.Title = "開くファイルを選択してください";

			//ダイアログを表示する
			if (openFileDialog1.ShowDialog() == DialogResult.OK)
			{
				sName = openFileDialog1.FileName;
			}

			return sName;
		}

		/// <summary>
		/// ファイルセーブダイアログを表示
		/// </summary>
		/// <returns>選択されたファイル。キャンセルされた場合は文字数０</returns>
		private string saveFileDialog()
		{
			string sName = "";

			saveFileDialog1.FileName = "";
			saveFileDialog1.Filter = "シェーダーパラメータXML(*.spxm;)|*.spxm";
			saveFileDialog1.Title = "保存先のファイルを選択してください";

			//ダイアログを表示する
			if (saveFileDialog1.ShowDialog() == DialogResult.OK)
			{
				sName = saveFileDialog1.FileName;
			}

			return sName;
		}

		/// <summary>
		/// ファイルエクスポートダイアログを表示
		/// </summary>
		/// <returns>選択されたファイル。キャンセルされた場合は文字数０</returns>
		private string exportDialog()
		{
			string sName = "";

			saveFileDialog1.FileName = "";
			saveFileDialog1.Filter = "シェーダーパラメータ(*.sdpt;)|*.sdpt";
			saveFileDialog1.Title = "保存先のファイルを選択してください";

			//ダイアログを表示する
			if (saveFileDialog1.ShowDialog() == DialogResult.OK)
			{
				sName = saveFileDialog1.FileName;
			}

			return sName;
		}

		#endregion
		#region メンバ変数
		private string m_sFileName = "";
		private string m_sExportFileName = "";
		private other m_other = new other();
		private waterControl m_Water = new waterControl();
		private postControl m_Post = new postControl();
		private furControl m_Fur = new furControl();
		private bumpControl m_Bump = new bumpControl();
		#endregion
	}
}
