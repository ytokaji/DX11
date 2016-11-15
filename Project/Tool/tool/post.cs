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
	public partial class postControl : UserControl
	{
		public postControl()
		{
			InitializeComponent();
		}

		/// <summary>
		/// CSendMsg.SShaderParamの値ですべてを更新します。
		/// </summary>
		public void initParam()
		{
			CSendMsg.SPostParam param = CSendMsg.getInstance().m_shaderData.m_Post;

			setParamData(ref trackBar_BrightnessBias, ref textBox_BrightnessBias, param.m_fBrightness, FLOAT_RATIO_NORMAL);
			setParamData(ref trackBar_FocusRange, ref textBox_FocusRange, param.m_fFocusRange, FLOAT_RATIO_DISTANCE);
			setParamData(ref trackBar_FocusDistance, ref textBox_FocusDistance, param.m_fFocusDistance, FLOAT_RATIO_DISTANCE);

			checkBox_Bloom.Checked = param.m_bBloomUse==0 ? false : true;
			checkBox_Dof.Checked = param.m_bDofUse == 0 ? false : true;

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
		const int FLOAT_RATIO_DISTANCE = 2;
		#endregion
		#region GUIコントロール
		private void trackBar_BrightnessBias_Scroll(object sender, EventArgs e)
		{
			CSendMsg.getInstance().m_shaderData.m_Post.m_fBrightness = (float)trackBar_BrightnessBias.Value / (float)FLOAT_RATIO_NORMAL;
			initParam();
		}

		private void trackBar_FocusDistance_Scroll(object sender, EventArgs e)
		{
			CSendMsg.getInstance().m_shaderData.m_Post.m_fFocusDistance = (float)trackBar_FocusDistance.Value / (float)FLOAT_RATIO_DISTANCE;
			initParam();
		}

		private void trackBar_FocusRange_Scroll(object sender, EventArgs e)
		{
			CSendMsg.getInstance().m_shaderData.m_Post.m_fFocusRange = (float)trackBar_FocusRange.Value / (float)FLOAT_RATIO_DISTANCE;
			initParam();
		}

		private void checkBox_Bloom_CheckedChanged(object sender, EventArgs e)
		{
			CSendMsg.getInstance().m_shaderData.m_Post.m_bBloomUse = checkBox_Bloom.Checked == false ? (byte)0 : (byte)1;
			initParam();
		}

		private void checkBox_Dof_CheckedChanged(object sender, EventArgs e)
		{
			CSendMsg.getInstance().m_shaderData.m_Post.m_bDofUse = checkBox_Dof.Checked == false ? (byte)0 : (byte)1;
			initParam();
		}
		#endregion
	}
}
