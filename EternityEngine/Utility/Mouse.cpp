#include "Mouse.h"

namespace Eternity
{
	namespace Utility
	{
		// コンストラクタ
		CMouse::CMouse()
			: m_pInput(nullptr)
			, m_pInputDevice(nullptr)
		{
			ZeroMemory(&m_oldMS, sizeof(m_oldMS));
			ZeroMemory(&m_newMS, sizeof(m_newMS));
		}

		// デストラクタ
		CMouse::~CMouse()
		{
			Utility::SafeRelease(m_pInputDevice);
			Utility::SafeRelease(m_pInput);
		}

		// 初期化処理
		void CMouse::Initialize(HWND hwnd)
		{
			DirectInput8Create(
				GetModuleHandle(NULL),
				DIRECTINPUT_VERSION,
				IID_IDirectInput8,
				(void**)&m_pInput,
				nullptr);

			m_pInput->CreateDevice(GUID_SysMouse, &m_pInputDevice, NULL);

			m_pInputDevice->SetDataFormat(&c_dfDIMouse);

			m_pInputDevice->SetCooperativeLevel(hwnd,
				DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

			DIPROPDWORD diprop;
			diprop.diph.dwSize = sizeof(diprop);
			diprop.diph.dwHeaderSize = sizeof(diprop.diph);
			diprop.diph.dwObj = 0;
			diprop.diph.dwHow = DIPH_DEVICE;
			diprop.dwData = DIPROPAXISMODE_REL;

			m_pInputDevice->SetProperty(DIPROP_AXISMODE, &diprop.diph);

			m_pInputDevice->Acquire();
		}

		// 更新処理
		void CMouse::Update()
		{
			if (m_pInputDevice == nullptr)
				return;

			memcpy(&m_oldMS, &m_newMS, sizeof(m_newMS));

			// デバイスの状態を取得
			auto hr = m_pInputDevice->GetDeviceState(sizeof(DIMOUSESTATE), &m_newMS);

			if (hr == DIERR_INPUTLOST)
			{
				m_pInputDevice->Acquire();
				m_pInputDevice->GetDeviceState(sizeof(DIMOUSESTATE), &m_newMS);
			}
		}

		// 一度のみ
		bool CMouse::IsPressed(const BYTE keyCode)
		{
			return (
				(m_newMS.rgbButtons[keyCode] & 0x80) &&
				!(m_oldMS.rgbButtons[keyCode] & 0x80));
		}

		// おしっぱなし
		bool CMouse::IsDown(const BYTE keyCode)
		{
			return (m_newMS.rgbButtons[keyCode] & 0x80);
		}

		// 押し上げたとき
		bool CMouse::IsUp(const BYTE keyCode)
		{
			return (
				!(m_newMS.rgbButtons[keyCode] & 0x80) &&
				(m_oldMS.rgbButtons[keyCode] & 0x80));
		}

		// マウスが移動した距離？
		POINT CMouse::GetMouseMove()
		{
			POINT p;

			p.x = m_newMS.lX;
			p.y = m_newMS.lY;

			return p;
		}

		// マウスホイールの取得
		float CMouse::GetMouseWheel()
		{
			return m_newMS.lZ;
		}
	}
}