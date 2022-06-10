#include "GamePad.h"

namespace Eternity
{
	namespace Utility
	{
		// �R���X�g���N�^
		CGamePad::CGamePad()
			: m_pInput(nullptr)
			, m_pInputDevice(nullptr)
		{
			ZeroMemory(&m_oldJS, sizeof(m_oldJS));
			ZeroMemory(&m_newJS, sizeof(m_newJS));
		}

		// �f�X�g���N�^
		CGamePad::~CGamePad()
		{
			SafeRelease(m_pInputDevice);
			SafeRelease(m_pInput);
		}

		// ����������
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

		// �X�V����
		void CGamePad::Update()
		{
			if (m_pInputDevice == nullptr)
				return;

			// �������R�s�[
			memcpy(&m_oldJS, &m_newJS, sizeof(m_newJS));

			SetPooling();
			SetDeviceState();
		}

		// ��x�̂�
		bool CGamePad::IsPressed(const BYTE keyCode)
		{
			return (
				(m_newJS.rgbButtons[keyCode] & 0x80) &&
				!(m_oldJS.rgbButtons[keyCode] & 0x80));
		}

		// �������ςȂ�
		bool CGamePad::IsDown(const BYTE keyCode)
		{
			return m_newJS.rgbButtons[keyCode] & 0x80;
		}

		// �����グ����
		bool CGamePad::IsUp(const BYTE keyCode)
		{
			return (
				!(m_newJS.rgbButtons[keyCode] & 0x80) &&
				(m_oldJS.rgbButtons[keyCode] & 0x80));
		}

		// �f�o�C�X�̐���
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

		// �t�H�[�}�b�g�̐ݒ�
		void CGamePad::SetDataFormat()
		{
			m_pInputDevice->SetDataFormat(&c_dfDIJoystick);
		}

		// �������x���̐ݒ�
		void CGamePad::SetCooperativeLevel(HWND hwnd)
		{
			m_pInputDevice->SetCooperativeLevel(hwnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND);
		}

		// �f�o�C�X�̔\�͂��擾
		void CGamePad::SetCapabilities()
		{
			m_pInputDevice->GetCapabilities(&m_devCaps);
		}

		// �I�u�W�F�N�g�̐ݒ�
		void CGamePad::SetEnumObject()
		{
			m_pInputDevice->EnumObjects(
				(LPDIENUMDEVICEOBJECTSCALLBACKA)EnumAxesCallback,
				(void*)this,
				DIDFT_AXIS);
		}

		// �A�N�Z�X���̎擾
		void CGamePad::SetPooling()
		{
			// �f�o�C�X����̃f�[�^���擾
			auto hr = m_pInputDevice->Poll();

			if (FAILED(hr))
			{
				// �A�N�Z�X�����擾
				hr = m_pInputDevice->Acquire();

				// �J��Ԃ�
				while (hr == DIERR_INPUTLOST)
				{
					hr = m_pInputDevice->Acquire();
				}
			}
		}

		// �f�o�C�X���̐ݒ�
		void CGamePad::SetDeviceState()
		{
			m_pInputDevice->GetDeviceState(sizeof(DIJOYSTATE), &m_newJS);
		}

		// �p�b�h�̐ݒ�
		bool __stdcall CGamePad::EnumJoysticksCallback(
			const DIDEVICEINSTANCE* pDeviceInst,
			void* pObject)
		{
			// �Q�[���p�b�h�Ăяo��
			CGamePad* pMyApp = (CGamePad*)pObject;

			// �f�o�C�X�̐���
			auto hr = pMyApp->m_pInput->CreateDevice(
				pDeviceInst->guidInstance,
				&pMyApp->m_pInputDevice, NULL);

			if (FAILED(hr))
				return DIENUM_CONTINUE;

			return DIENUM_STOP;
		}

		// �W���C�X�e�B�b�N�̐ݒ�
		bool __stdcall CGamePad::EnumAxesCallback(
			const DIDEVICEOBJECTINSTANCE* pDeviceObject,
			void* pObject)
		{
			// �Q�[���p�b�h�Ăяo��
			CGamePad* pMyApp = (CGamePad*)pObject;

			// �X�e�B�b�N�̐ݒ�
			DIPROPRANGE diprg;
			diprg.diph.dwSize = sizeof(DIPROPRANGE);
			diprg.diph.dwHeaderSize = sizeof(DIPROPHEADER);
			diprg.diph.dwHow = DIPH_BYID;
			diprg.diph.dwObj = pDeviceObject->dwType;
			diprg.lMin = 0 - 1000;
			diprg.lMax = 0 + 1000;

			// �X�e�B�b�N����ݒ�
			auto hr = pMyApp->m_pInputDevice->SetProperty(DIPROP_RANGE, &diprg.diph);

			if (FAILED(hr))
				return DIENUM_STOP;

			return DIENUM_CONTINUE;
		}
	}
}