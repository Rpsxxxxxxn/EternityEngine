#include "Mouse.h"

namespace Eternity
{
	namespace Utility
	{
		// �R���X�g���N�^
		CMouse::CMouse()
			: m_pInput(nullptr)
			, m_pInputDevice(nullptr)
		{
			ZeroMemory(&m_oldMS, sizeof(m_oldMS));
			ZeroMemory(&m_newMS, sizeof(m_newMS));
		}

		// �f�X�g���N�^
		CMouse::~CMouse()
		{
			Utility::SafeRelease(m_pInputDevice);
			Utility::SafeRelease(m_pInput);
		}

		// ����������
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

		// �X�V����
		void CMouse::Update()
		{
			if (m_pInputDevice == nullptr)
				return;

			memcpy(&m_oldMS, &m_newMS, sizeof(m_newMS));

			// �f�o�C�X�̏�Ԃ��擾
			auto hr = m_pInputDevice->GetDeviceState(sizeof(DIMOUSESTATE), &m_newMS);

			if (hr == DIERR_INPUTLOST)
			{
				m_pInputDevice->Acquire();
				m_pInputDevice->GetDeviceState(sizeof(DIMOUSESTATE), &m_newMS);
			}
		}

		// ��x�̂�
		bool CMouse::IsPressed(const BYTE keyCode)
		{
			return (
				(m_newMS.rgbButtons[keyCode] & 0x80) &&
				!(m_oldMS.rgbButtons[keyCode] & 0x80));
		}

		// �������ςȂ�
		bool CMouse::IsDown(const BYTE keyCode)
		{
			return (m_newMS.rgbButtons[keyCode] & 0x80);
		}

		// �����グ���Ƃ�
		bool CMouse::IsUp(const BYTE keyCode)
		{
			return (
				!(m_newMS.rgbButtons[keyCode] & 0x80) &&
				(m_oldMS.rgbButtons[keyCode] & 0x80));
		}

		// �}�E�X���ړ����������H
		POINT CMouse::GetMouseMove()
		{
			POINT p;

			p.x = m_newMS.lX;
			p.y = m_newMS.lY;

			return p;
		}

		// �}�E�X�z�C�[���̎擾
		float CMouse::GetMouseWheel()
		{
			return m_newMS.lZ;
		}
	}
}