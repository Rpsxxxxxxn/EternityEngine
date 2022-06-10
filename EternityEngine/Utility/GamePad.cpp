#include "GamePad.h"

namespace Eternity
{
	namespace Utility
	{
		// コンストラクタ
		CGamePad::CGamePad()
			: m_pInput(nullptr)
			, m_pInputDevice(nullptr)
		{
			ZeroMemory(&m_oldJS, sizeof(m_oldJS));
			ZeroMemory(&m_newJS, sizeof(m_newJS));
		}

		// デストラクタ
		CGamePad::~CGamePad()
		{
			SafeRelease(m_pInputDevice);
			SafeRelease(m_pInput);
		}

		// 初期化処理
		void CGamePad::Initialize(HWND hwnd)
		{
			CreateDevice();

			if (m_pInputDevice == nullptr)
				return;

			SetDataFormat();
			SetCooperativeLevel(hwnd);
			SetCapabilities();
			SetEnumObject();
			SetPooling();
		}

		// 更新処理
		void CGamePad::Update()
		{
			if (m_pInputDevice == nullptr)
				return;

			// メモリコピー
			memcpy(&m_oldJS, &m_newJS, sizeof(m_newJS));

			SetPooling();
			SetDeviceState();
		}

		// 一度のみ
		bool CGamePad::IsPressed(const BYTE keyCode)
		{
			return (
				(m_newJS.rgbButtons[keyCode] & 0x80) &&
				!(m_oldJS.rgbButtons[keyCode] & 0x80));
		}

		// 押しっぱなし
		bool CGamePad::IsDown(const BYTE keyCode)
		{
			return m_newJS.rgbButtons[keyCode] & 0x80;
		}

		// 押し上げた時
		bool CGamePad::IsUp(const BYTE keyCode)
		{
			return (
				!(m_newJS.rgbButtons[keyCode] & 0x80) &&
				(m_oldJS.rgbButtons[keyCode] & 0x80));
		}

		// デバイスの生成
		void CGamePad::CreateDevice()
		{
			DirectInput8Create(
				GetModuleHandle(NULL),
				DIRECTINPUT_VERSION,
				IID_IDirectInput8,
				(void**)&m_pInput, NULL);

			m_pInput->EnumDevices(
				DI8DEVCLASS_GAMECTRL,
				(LPDIENUMDEVICESCALLBACKA)EnumJoysticksCallback,
				(void*)this,
				DIEDFL_ATTACHEDONLY);
		}

		// フォーマットの設定
		void CGamePad::SetDataFormat()
		{
			m_pInputDevice->SetDataFormat(&c_dfDIJoystick);
		}

		// 協調レベルの設定
		void CGamePad::SetCooperativeLevel(HWND hwnd)
		{
			m_pInputDevice->SetCooperativeLevel(hwnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND);
		}

		// デバイスの能力を取得
		void CGamePad::SetCapabilities()
		{
			m_pInputDevice->GetCapabilities(&m_devCaps);
		}

		// オブジェクトの設定
		void CGamePad::SetEnumObject()
		{
			m_pInputDevice->EnumObjects(
				(LPDIENUMDEVICEOBJECTSCALLBACKA)EnumAxesCallback,
				(void*)this,
				DIDFT_AXIS);
		}

		// アクセス権の取得
		void CGamePad::SetPooling()
		{
			// デバイスからのデータを取得
			auto hr = m_pInputDevice->Poll();

			if (FAILED(hr))
			{
				// アクセス権を取得
				hr = m_pInputDevice->Acquire();

				// 繰り返し
				while (hr == DIERR_INPUTLOST)
				{
					hr = m_pInputDevice->Acquire();
				}
			}
		}

		// デバイス情報の設定
		void CGamePad::SetDeviceState()
		{
			m_pInputDevice->GetDeviceState(sizeof(DIJOYSTATE), &m_newJS);
		}

		// パッドの設定
		bool __stdcall CGamePad::EnumJoysticksCallback(
			const DIDEVICEINSTANCE* pDeviceInst,
			void* pObject)
		{
			// ゲームパッド呼び出し
			CGamePad* pMyApp = (CGamePad*)pObject;

			// デバイスの生成
			auto hr = pMyApp->m_pInput->CreateDevice(
				pDeviceInst->guidInstance,
				&pMyApp->m_pInputDevice, NULL);

			if (FAILED(hr))
				return DIENUM_CONTINUE;

			return DIENUM_STOP;
		}

		// ジョイスティックの設定
		bool __stdcall CGamePad::EnumAxesCallback(
			const DIDEVICEOBJECTINSTANCE* pDeviceObject,
			void* pObject)
		{
			// ゲームパッド呼び出し
			CGamePad* pMyApp = (CGamePad*)pObject;

			// スティックの設定
			DIPROPRANGE diprg;
			diprg.diph.dwSize = sizeof(DIPROPRANGE);
			diprg.diph.dwHeaderSize = sizeof(DIPROPHEADER);
			diprg.diph.dwHow = DIPH_BYID;
			diprg.diph.dwObj = pDeviceObject->dwType;
			diprg.lMin = 0 - 1000;
			diprg.lMax = 0 + 1000;

			// スティック情報を設定
			auto hr = pMyApp->m_pInputDevice->SetProperty(DIPROP_RANGE, &diprg.diph);

			if (FAILED(hr))
				return DIENUM_STOP;

			return DIENUM_CONTINUE;
		}
	}
}