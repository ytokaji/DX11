using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace tool
{
	public partial class other : UserControl
	{
		public other()
		{
			InitializeComponent();
		}

		/// <summary>
		/// CSendMsg.SShaderParamの値ですべてを更新します。
		/// </summary>
		public void initParam()
		{
			CSendMsg.SOtherParam param = CSendMsg.getInstance().m_shaderData.m_Others;

			setParamData(ref trackBar_LightDir_X, ref textBox_LightDir_X, param.m_f3LightDir.x, FLOAT_RATIO_NORMAL, 1.0f);
			setParamData(ref trackBar_LightDir_Y, ref textBox_LightDir_Y, param.m_f3LightDir.y, FLOAT_RATIO_NORMAL, 1.0f);
			setParamData(ref trackBar_LightDir_Z, ref textBox_LightDir_Z, param.m_f3LightDir.z, FLOAT_RATIO_NORMAL, 1.0f);

			CSendMsg.getInstance().SendMessage();
		}
		#region privateメソッド
		/// <summary>
		/// i_fValをGUIに反映
		/// </summary>
		/// <param name="i_rBar"></param>
		/// <param name="i_rText"></param>
		/// <param name="i_fVal"></param>
		private void setParamData(ref TrackBar i_rBar, ref TextBox i_rText, float i_fVal, float i_fRatio, float i_fOffset)
		{
			int nVal = (int)((i_fVal + i_fOffset) * i_fRatio);
			nVal = Math.Max(nVal, i_rBar.Minimum);
			nVal = Math.Min(nVal, i_rBar.Maximum);
			i_rBar.Value = nVal;
			i_rText.Text = (((float)nVal / i_fRatio) - i_fOffset).ToString();
		}
		#endregion
		#region 定義
		/// <summary>
		/// トラックバーの1をfloat値のいくつとして扱うか
		/// </summary>
		const int FLOAT_RATIO_NORMAL = 50;
		#endregion
		#region GUIコントロール
		private void button_shaderReload_Click(object sender, EventArgs e)
		{
			CSendMsg.getInstance().m_shaderData.m_Others.m_bShaderReLoadReq = true;
			CSendMsg.getInstance().SendMessage();
			CSendMsg.getInstance().m_shaderData.m_Others.m_bShaderReLoadReq = false;

		}

		private void trackBar_LightDir_X_Scroll(object sender, EventArgs e)
		{
			CSendMsg.getInstance().m_shaderData.m_Others.m_f3LightDir.x = (float)trackBar_LightDir_X.Value / (float)FLOAT_RATIO_NORMAL - 1;
			initParam();
		}

		private void trackBar_LightDir_Y_Scroll(object sender, EventArgs e)
		{
			CSendMsg.getInstance().m_shaderData.m_Others.m_f3LightDir.y = (float)trackBar_LightDir_Y.Value / (float)FLOAT_RATIO_NORMAL - 1;
			initParam();
		}

		private void trackBar_LightDir_Z_Scroll(object sender, EventArgs e)
		{
			CSendMsg.getInstance().m_shaderData.m_Others.m_f3LightDir.z = (float)trackBar_LightDir_Z.Value / (float)FLOAT_RATIO_NORMAL - 1;
			initParam();
		}
		#endregion
	}
}
