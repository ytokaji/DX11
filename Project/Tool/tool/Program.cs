using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;

namespace tool
{
	static class Program
	{
		/// <summary>
		/// アプリケーションのメイン エントリ ポイントです。
		/// </summary>
		[STAThread]
		static void Main()
		{
			try
			{
				Application.EnableVisualStyles();
				Application.SetCompatibleTextRenderingDefault(false);
				Application.Run(new mainForm1());
			}
			catch (FormatException e)
			{
				// ここまで処理されなかった例外は回復不能として処理
				MessageBox.Show(e.Message,
					"エラー",
					MessageBoxButtons.OK,
					MessageBoxIcon.Error);
			}
		}
	}
}
