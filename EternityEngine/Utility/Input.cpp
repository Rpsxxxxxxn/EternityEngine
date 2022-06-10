#include "Input.h"

namespace Eternity
{
	namespace Utility
	{
		// コンストラクタ
		CInput::CInput()
		{
			ZeroMemory(m_keys, sizeof(m_keys));
			ZeroMemory(m_olds, sizeof(m_olds));
		}

		// デストラクタ
		CInput::~CInput()
		{
			SafeRelease(m_pInputDevice);
			SafeRelease(m_pInput);
		}

		// 初期化処理
		void CInput::Initialize(HWND hwnd)
		{
			// IDirectInput8の作成
			DirectInput8Create(
				GetModuleHandle(NULL),
				DIRECTINPUT_VERSION,
				IID_IDirectInput8,
				(LPVOID*)&m_pInput,
				NULL);

			// IDirectInputDevice8の取得
			m_pInput->CreateDevice(
				GUID_SysKeyboard,
				&m_pInputDevice,
				NULL);

			if (m_pInputDevice == nullptr)
				return;

			// 入力データ形式のセット
			m_pInputDevice->SetDataFormat(&c_dfDIKeyboard);

			// 排他制御のセット
			m_pInputDevice->SetCooperativeLevel(
				hwnd,
				DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);

			// 動作開始
			m_pInputDevice->Acquire();
		}

		// 更新処理
		void CInput::Update()
		{
			if (m_pInputDevice == nullptr)
				return;

			// メモリコピー
			memcpy(&m_olds, &m_keys, sizeof(m_keys));

			// 現在の入力値を配列に入れる
			auto hr = m_pInputDevice->GetDeviceState(sizeof(m_keys), m_keys);

			if (FAILED(hr))
			{
				m_pInputDevice->Acquire();
				m_pInputDevice->GetDeviceState(sizeof(m_keys), m_keys);
			}
		}

		// 一度のみ
		bool CInput::IsPressed(const BYTE keyCode)
		{
			return ((m_keys[keyCode] & 0x80) && !(m_olds[keyCode] & 0x80));
		}

		// 入力キーおしっぱ
		bool CInput::IsDown(const BYTE keyCode)
		{
			return (m_keys[keyCode] & 0x80);
		}

		// キーを離した時
		bool CInput::IsUp(const BYTE keyCode)
		{
			return (!(m_keys[keyCode] & 0x80) && (m_olds[keyCode] & 0x80));
		}
	}
}