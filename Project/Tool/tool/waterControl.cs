using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace tool
{
	public partial class waterControl : UserControl
	{
		public waterControl()
		{
			InitializeComponent();
		}

		/// <summary>
		/// CSendMsg.SShaderParamの値ですべてを更新します。
		/// </summary>
		public void initParam()
		{
			CSendMsg.SWaterParam param = CSendMsg.getInstance().m_shaderData.m_Water;

			setParamData(ref trackBar_ColorR, ref textBox_ColorR, param.m_f4Color.x, FLOAT_RATIO_NORMAL);
			setParamData(ref trackBar_ColorG, ref textBox_ColorG, param.m_f4Color.y, FLOAT_RATIO_NORMAL);
			setParamData(ref trackBar_ColorB, ref textBox_ColorB, param.m_f4Color.z, FLOAT_RATIO_NORMAL);
			setParamData(ref trackBar_ColorA, ref textBox_ColorA, param.m_f4Color.w, FLOAT_RATIO_NORMAL);

			setParamData(ref trackBar_SpecularColorR, ref textBox_SpecularColorR, param.m_f3SpecularColor.x, FLOAT_RATIO_NORMAL);
			setParamData(ref trackBar_SpecularColorG, ref textBox_SpecularColorG, param.m_f3SpecularColor.y, FLOAT_RATIO_NORMAL);
			setParamData(ref trackBar_SpecularColorB, ref textBox_SpecularColorB, param.m_f3SpecularColor.z, FLOAT_RATIO_NORMAL);

			setParamData(ref trackBar_RefrParamsU, ref textBox_RefrParamsU, param.m_f2RefrParams.x, FLOAT_RATIO_REFR_RFLE_UV);
			setParamData(ref trackBar_RefrParamsV, ref textBox_RefrParamsV, param.m_f2RefrParams.y, FLOAT_RATIO_REFR_RFLE_UV);

			setParamData(ref trackBar_ReflParamsU, ref textBox_ReflParamsU, param.m_f2ReflParams.x, FLOAT_RATIO_REFR_RFLE_UV);
			setParamData(ref trackBar_ReflParamsV, ref textBox_ReflParamsV, param.m_f2ReflParams.y, FLOAT_RATIO_REFR_RFLE_UV);

			setParamData(ref trackBar_SpecularPowerX, ref textBox_SpecularPowerX, param.m_f2SpecularPower.x, FLOAT_RATIO_NORMAL);
			setParamData(ref trackBar_SpecularPowerY, ref textBox_SpecularPowerY, param.m_f2SpecularPower.y, FLOAT_RATIO_SPECULAR_Y);

			setParamData(ref trackBar_ReflBias, ref textBox_ReflBias, param.m_fReflBias, FLOAT_RATIO_NORMAL);

			setParamData(ref trackBar_FresnelPower, ref textBoxFresnelPower, param.m_fFresnelPower, FLOAT_RATIO_FRESNEL_POWER);

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
			i_rText.Text = ((float)nVal/i_fRatio).ToString();
		}
		#endregion
		#region 定義
		/// <summary>
		/// トラックバーの1をfloat値のいくつとして扱うか
		/// </summary>
		const int FLOAT_RATIO_NORMAL = 100;
		const int FLOAT_RATIO_REFR_RFLE_UV = 500;
		const int FLOAT_RATIO_SPECULAR_Y = 10;
		const int FLOAT_RATIO_FRESNEL_POWER = 20;
		#endregion
		#region GUIコントロール
		private void trackBar_ColorR_Scroll(object sender, EventArgs e)
		{
			CSendMsg.getInstance().m_shaderData.m_Water.m_f4Color.x = (float)trackBar_ColorR.Value / (float)FLOAT_RATIO_NORMAL;
			initParam();
		}

		private void trackBar_ColorG_Scroll(object sender, EventArgs e)
		{
			CSendMsg.getInstance().m_shaderData.m_Water.m_f4Color.y = (float)trackBar_ColorG.Value / (float)FLOAT_RATIO_NORMAL;
			initParam();
		}

		private void trackBar_ColorB_Scroll(object sender, EventArgs e)
		{
			CSendMsg.getInstance().m_shaderData.m_Water.m_f4Color.z = (float)trackBar_ColorB.Value / (float)FLOAT_RATIO_NORMAL;
			initParam();
		}

		private void trackBar_ColorA_Scroll(object sender, EventArgs e)
		{
			CSendMsg.getInstance().m_shaderData.m_Water.m_f4Color.w = (float)trackBar_ColorA.Value / (float)FLOAT_RATIO_NORMAL;
			initParam();
		}

		private void trackBar_SpecularColorR_Scroll(object sender, EventArgs e)
		{
			CSendMsg.getInstance().m_shaderData.m_Water.m_f3SpecularColor.x = (float)trackBar_SpecularColorR.Value / (float)FLOAT_RATIO_NORMAL;
			initParam();
		}

		private void trackBar_SpecularColorG_Scroll(object sender, EventArgs e)
		{
			CSendMsg.getInstance().m_shaderData.m_Water.m_f3SpecularColor.y = (float)trackBar_SpecularColorG.Value / (float)FLOAT_RATIO_NORMAL;
			initParam();
		}

		private void trackBar_SpecularColorB_Scroll(object sender, EventArgs e)
		{
			CSendMsg.getInstance().m_shaderData.m_Water.m_f3SpecularColor.z = (float)trackBar_SpecularColorB.Value / (float)FLOAT_RATIO_NORMAL;
		}

		private void trackBar_RefrParamsU_Scroll(object sender, EventArgs e)
		{
			CSendMsg.getInstance().m_shaderData.m_Water.m_f2RefrParams.x = (float)trackBar_RefrParamsU.Value / (float)FLOAT_RATIO_REFR_RFLE_UV;
			initParam();
		}

		private void trackBar_RefrParamsV_Scroll(object sender, EventArgs e)
		{
			CSendMsg.getInstance().m_shaderData.m_Water.m_f2RefrParams.y = (float)trackBar_RefrParamsV.Value / (float)FLOAT_RATIO_REFR_RFLE_UV;
			initParam();
		}

		private void trackBar_ReflParamsU_Scroll(object sender, EventArgs e)
		{
			CSendMsg.getInstance().m_shaderData.m_Water.m_f2ReflParams.x = (float)trackBar_ReflParamsU.Value / (float)FLOAT_RATIO_REFR_RFLE_UV;
			initParam();
		}

		private void trackBar_ReflParamsV_Scroll(object sender, EventArgs e)
		{
			CSendMsg.getInstance().m_shaderData.m_Water.m_f2ReflParams.y = (float)trackBar_ReflParamsV.Value / (float)FLOAT_RATIO_REFR_RFLE_UV;
			initParam();
		}

		private void trackBar_SpecularPowerX_Scroll(object sender, EventArgs e)
		{
			CSendMsg.getInstance().m_shaderData.m_Water.m_f2SpecularPower.x = (float)trackBar_SpecularPowerX.Value / (float)FLOAT_RATIO_NORMAL;
			initParam();
		}

		private void trackBar_SpecularPowerY_Scroll(object sender, EventArgs e)
		{
			CSendMsg.getInstance().m_shaderData.m_Water.m_f2SpecularPower.y = (float)trackBar_SpecularPowerY.Value / (float)FLOAT_RATIO_SPECULAR_Y;
			initParam();
		}

		private void trackBar_ReflBias_Scroll(object sender, EventArgs e)
		{
			CSendMsg.getInstance().m_shaderData.m_Water.m_fReflBias = (float)trackBar_ReflBias.Value / (float)FLOAT_RATIO_NORMAL;
			initParam();
		}

		private void trackBar_FresnelPower_Scroll(object sender, EventArgs e)
		{
			CSendMsg.getInstance().m_shaderData.m_Water.m_fFresnelPower = (float)trackBar_FresnelPower.Value / (float)FLOAT_RATIO_FRESNEL_POWER;
			initParam();
		}
		#endregion
	}
}
