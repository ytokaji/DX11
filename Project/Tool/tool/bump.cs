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
	public partial class bumpControl : UserControl
	{
		public bumpControl()
		{
			InitializeComponent();
		}

		/// <summary>
		/// CSendMsg.SShaderParamの値ですべてを更新します。
		/// </summary>
		public void initParam()
		{
			CSendMsg.SBumpParam param = CSendMsg.getInstance().m_shaderData.m_Bump;

			setParamData(ref trackBar_SpecularPower, ref textBox_SpecularPower, param.m_fSpecularPower, FLOAT_RATIO_POWERL);
			setParamData(ref trackBar_SpecularRange, ref textBox_SpecularRange, param.m_fSpecularRange, FLOAT_RATIO_RANGE);

			CSendMsg.getInstance().SendMessage();
		}
		#region privateメソッド
		/// <summary>
		/// i_fValをGUIに反映
		/// </summary>
		/// <param name="i_rBar"></param>
		/// <param name="i_rText"></param>
		/// <param name="i_fVal"></param>
		private void setParamData(ref TrackBar i_rBar, ref TextBox i_rText, float i_fVal, float i_fRatio)
		{
			int nVal = (int)(i_fVal * i_fRatio);
			nVal = Math.Max(nVal, i_rBar.Minimum);
			nVal = Math.Min(nVal, i_rBar.Maximum);
			i_rBar.Value = nVal;
			i_rText.Text = ((float)nVal / i_fRatio).ToString();
		}
		#endregion
		#region 定義
		/// <summary>
		/// トラックバーの1をfloat値のいくつとして扱うか
		/// </summary>
		const int FLOAT_RATIO_NORMAL = 100;
		const int FLOAT_RATIO_POWERL = 50;
		const int FLOAT_RATIO_RANGE = 20;
		#endregion
		#region GUIコントロール
		private void trackBar_SpecularPower_Scroll(object sender, EventArgs e)
		{
			CSendMsg.getInstance().m_shaderData.m_Bump.m_fSpecularPower = (float)trackBar_SpecularPower.Value / (float)FLOAT_RATIO_POWERL;
			initParam();
		}

		private void trackBar_SpecularRange_Scroll(object sender, EventArgs e)
		{
			CSendMsg.getInstance().m_shaderData.m_Bump.m_fSpecularRange = (float)trackBar_SpecularRange.Value / (float)FLOAT_RATIO_RANGE;
			initParam();
		}
		#endregion
	}
}
