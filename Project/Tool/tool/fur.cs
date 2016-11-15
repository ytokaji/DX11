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
	public partial class furControl : UserControl
	{
		public furControl()
		{
			InitializeComponent();
		}

		/// <summary>
		/// CSendMsg.SShaderParamの値ですべてを更新します。
		/// </summary>
		public void initParam()
		{
			CSendMsg.SFurParam param = CSendMsg.getInstance().m_shaderData.m_Fur;

			setParamData(ref trackBar_ColorR, ref textBox_ColorR, param.m_f3Color.x, FLOAT_RATIO_NORMAL);
			setParamData(ref trackBar_ColorG, ref textBox_ColorG, param.m_f3Color.y, FLOAT_RATIO_NORMAL);
			setParamData(ref trackBar_ColorB, ref textBox_ColorB, param.m_f3Color.z, FLOAT_RATIO_NORMAL);

			setParamData(ref trackBar_FurDistance, ref textBox_FurDistance, param.m_fDistance, FLOAT_RATIO_DISTANCE);
			setParamData(ref trackBar_FurNum, ref textBox_FurNum, param.m_fNum, FLOAT_RATIO_NUM);

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
		const int FLOAT_RATIO_DISTANCE = 5000;
		const int FLOAT_RATIO_NUM = 1;
		#endregion
		#region GUIコントロール
		private void trackBar_ColorR_Scroll(object sender, EventArgs e)
		{
			CSendMsg.getInstance().m_shaderData.m_Fur.m_f3Color.x = (float)trackBar_ColorR.Value / (float)FLOAT_RATIO_NORMAL;
			initParam();
		}

		private void trackBar_ColorG_Scroll(object sender, EventArgs e)
		{
			CSendMsg.getInstance().m_shaderData.m_Fur.m_f3Color.y = (float)trackBar_ColorG.Value / (float)FLOAT_RATIO_NORMAL;
			initParam();
		}

		private void trackBar_ColorB_Scroll(object sender, EventArgs e)
		{
			CSendMsg.getInstance().m_shaderData.m_Fur.m_f3Color.z = (float)trackBar_ColorB.Value / (float)FLOAT_RATIO_NORMAL;
			initParam();
		}

		private void trackBarFurDistance_Scroll(object sender, EventArgs e)
		{
			CSendMsg.getInstance().m_shaderData.m_Fur.m_fDistance = (float)trackBar_FurDistance.Value / (float)FLOAT_RATIO_DISTANCE;
			initParam();
		}

		private void trackBar_FurNum_Scroll(object sender, EventArgs e)
		{
			CSendMsg.getInstance().m_shaderData.m_Fur.m_fNum = (float)trackBar_FurNum.Value / (float)FLOAT_RATIO_NUM;
			initParam();
		}
		#endregion
	}
}
