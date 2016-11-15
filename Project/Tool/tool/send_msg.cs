using System;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using System.IO;


namespace tool
{
	/// <summary>
	/// メッセージ送信、データ管理クラス
	/// シングルトンクラス
	/// </summary>
	public class CSendMsg
	{
		#region publicメソッド
		/// <summary>
		/// インスタンスの取得
		/// </summary>
		public static CSendMsg getInstance()
		{
			return m_pInstance;
		}

		/// <summary>
		/// メッセージの送信
		/// </summary>
		/// <param name="i_rData"></param>
		public void SendMessage()
		{
			// ポインタ取得
			IntPtr pDataPtr = Marshal.AllocCoTaskMem(Marshal.SizeOf(m_shaderData));
			Marshal.StructureToPtr(m_shaderData, pDataPtr, true);

			COPYDATASTRUCT data = new COPYDATASTRUCT();
			data.dwData = IntPtr.Zero;
			data.cbData = (uint)(Marshal.SizeOf(m_shaderData));
			data.lpData = pDataPtr;

			IntPtr hWnd = FindWindow(null, "application");
			SendMessage(hWnd, WM_COPYDATA, IntPtr.Zero, ref data);

			Marshal.FreeCoTaskMem(pDataPtr);
		}

		/// <summary>
		/// 自身の保存
		/// </summary>
		/// <param name="i_sFileName">ファイル名</param>
		public void save(ref string i_sFileName)
		{
			if (i_sFileName == null | i_sFileName.Length == 0)
				return;
			try
			{
				System.Xml.Serialization.XmlSerializer serializer = new System.Xml.Serialization.XmlSerializer(typeof(CSendMsg));
				System.IO.FileStream fs = new System.IO.FileStream( i_sFileName, System.IO.FileMode.Create);
				serializer.Serialize(fs, m_pInstance);
				fs.Close();
			}
			catch (System.SystemException e)
			{
				// ファイル操作エラー
				MessageBox.Show(e.Message,
					"ファイルエラー",
					MessageBoxButtons.OK,
					MessageBoxIcon.Error);
			}
		}

		/// <summary>
		/// 自身のロード
		/// </summary>
		/// <param name="i_sFileName">ファイル名</param>
		public void load(ref string i_sFileName)
		{
			if (i_sFileName == null | i_sFileName.Length == 0)
				return;
			try
			{
				//XmlSerializerオブジェクトの作成
				System.Xml.Serialization.XmlSerializer serializer = new System.Xml.Serialization.XmlSerializer(typeof(CSendMsg));
				//ファイルを開く
				System.IO.FileStream fs = new System.IO.FileStream(i_sFileName, System.IO.FileMode.Open);
				//XMLファイルから読み込み、逆シリアル化する
				m_pInstance = (CSendMsg)serializer.Deserialize(fs);
				//閉じる
				fs.Close();

			}
			catch (System.SystemException e)
			{
				// ファイル操作エラー
				MessageBox.Show(e.Message,
					"ファイルエラー",
					MessageBoxButtons.OK,
					MessageBoxIcon.Error);
			}
		}

		/// <summary>
		/// バイナリデータでの出力
		/// </summary>
		/// <param name="i_sFileName">ファイル名</param>
		public void export(ref string i_sFileName)
		{
			if (i_sFileName == null | i_sFileName.Length == 0)
				return;

			// byteデータに構造体データを格納
			int nSize = Marshal.SizeOf(typeof(CSendMsg.SShaderParam));
			IntPtr ptr = Marshal.AllocHGlobal(nSize);
			byte[] data = null;

			try
			{
				Marshal.StructureToPtr(m_shaderData, ptr, false);
				data = new byte[nSize];
				Marshal.Copy(ptr, data, 0, nSize);
			}
			finally
			{
				if (IntPtr.Zero != ptr) { Marshal.FreeHGlobal(ptr); }
			}

			// バイトデータの書き込み
			try
			{
				if (data != null)
				{
					using (BinaryWriter w = new BinaryWriter(File.OpenWrite(i_sFileName)))
					{
						w.Write(data);
					}
				}
			}
			catch (System.SystemException e)
			{
				// ファイル操作エラー
				MessageBox.Show(e.Message,
					"ファイルエラー",
					MessageBoxButtons.OK,
					MessageBoxIcon.Error);
			}

		}

		#endregion
		#region privateメソッド
		/// <summary>
		/// コンストラクタ
		/// </summary>
		private CSendMsg()
		{
		}
		#endregion
		#region 構造体
		/// <summary>
		/// 転送パラメータ
		/// </summary>
		[StructLayout(LayoutKind.Sequential)]
		public struct SShaderParam
		{
			public SShaderParam(char[] i_pchID)
			{
				m_chID = i_pchID;
				m_Water = new SWaterParam();
				m_Others = new SOtherParam();
				m_Post = new SPostParam();
				m_Fur = new SFurParam();
				m_Bump = new SBumpParam();
			}
			[MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
			public char[] m_chID;		//!< 識別子

			public SOtherParam m_Others;
			public SWaterParam m_Water;
			public SPostParam m_Post;
			public SFurParam m_Fur;
			public SBumpParam m_Bump;
		};
		
		/// <summary>
		/// 浮動少数2要素
		/// </summary>
		[StructLayout(LayoutKind.Sequential)]
		public struct SVector2
		{
			public float x { get; set; }
			public float y { get; set; }
			
		}

		/// <summary>
		/// 浮動少数3要素
		/// </summary>
		[StructLayout(LayoutKind.Sequential)]
		public struct SVector3
		{
			public float x { get; set; }
			public float y { get; set; }
			public float z { get; set; }

		}

		/// <summary>
		/// 浮動少数4要素
		/// </summary>
		[StructLayout(LayoutKind.Sequential)]
		public struct SVector4
		{
			public float x { get; set; }
			public float y { get; set; }
			public float z { get; set; }
			public float w { get; set; }
		}

		/// <summary>
		/// その他パラメータ
		/// </summary>
		[StructLayout(LayoutKind.Sequential)]
		public unsafe struct SOtherParam
		{
			public SVector3 m_f3LightDir;				//!< ライト方向
			public bool m_bShaderReLoadReq;				//!< シェーダリロード要求
		};

		/// <summary>
		/// 水面シェーダパラメータ
		/// </summary>
		[StructLayout(LayoutKind.Sequential)]
		public unsafe struct SWaterParam
		{
			public SVector4 m_f4Color;					//!< 基本色味RGB
			public SVector3 m_f3SpecularColor;			//!< スペキュラ色味RGB
			public SVector2 m_f2RefrParams;				//!< 屈折のゆらぎの強さU,V(RefrScale)
			public SVector2 m_f2ReflParams;				//!< 反射のゆらぎの強さU,V(ReflScale)
			public SVector2 m_f2SpecularPower;			//!< スペキュラの強さ,絞り
			public float m_fReflBias { get; set; }		//!< 反射効果のバイアス0～1(Fresnel.x)
			public float m_fFresnelPower { get; set; }	//!< フレネルの強さ(Fresnel.y)
		};

		/// <summary>
		/// ポストシェーダパラメータ
		/// </summary>
		[StructLayout(LayoutKind.Sequential)]
		public unsafe struct SPostParam
		{
			public float m_fBrightness;					//!< 輝度
			public float m_fFocusDistance;				//!< フォーカス距離
			public float m_fFocusRange;					//!< フォーカス範囲
			public byte m_bBloomUse;					//!< ブルームのON/OFF
			public byte m_bDofUse;						//!< dofのON/OFF
			public byte m_reserve1;
			public byte m_reserve2;
		};

		/// <summary>
		/// ファーシェーダパラメータ
		/// </summary>
		[StructLayout(LayoutKind.Sequential)]
		public unsafe struct SFurParam
		{
			public SVector3 m_f3Color;					//!< 基本色味RGB
			public float m_fDistance;					//!< 距離
			public float m_fNum;						//!< 数
		};

		/// <summary>
		/// バンプシェーダパラメータ
		/// </summary>
		[StructLayout(LayoutKind.Sequential)]
		public unsafe struct SBumpParam
		{
			public float m_fSpecularPower;				//!< スペキュラの範囲
			public float m_fSpecularRange;				//!< スペキュラの距離
		};

		private struct COPYDATASTRUCT
		{
			public IntPtr dwData;
			public UInt32 cbData;
			public IntPtr lpData;
		}
		#endregion
		#region メンバ変数
		private static CSendMsg m_pInstance = new CSendMsg();
		public SShaderParam m_shaderData = new SShaderParam(SHADER_PARAM_ID);
		#endregion
		#region 定義
		private static uint WM_COPYDATA = 0x004A;
		public static char[] SHADER_PARAM_ID = { 's', 'd', 'p', 't' };	
		#endregion
		#region user32.dllメソッド
		[DllImport("user32.dll")]
		private extern static IntPtr FindWindow(string lpClassName, string lpWindowName);
		[DllImport("user32.dll")]
		private static extern IntPtr SendMessage(IntPtr hWnd, uint Msg, IntPtr wParam, ref COPYDATASTRUCT lParam);
		#endregion
	}
}
