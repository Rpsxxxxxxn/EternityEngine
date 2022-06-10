#include "Input.h"

namespace Eternity
{
	namespace Utility
	{
		// �R���X�g���N�^
		CInput::CInput()
		{
			ZeroMemory(m_keys, sizeof(m_keys));
			ZeroMemory(m_olds, sizeof(m_olds));
		}

		// �f�X�g���N�^
		CInput::~CInput()
		{
			SafeRelease(m_pInputDevice);
			SafeRelease(m_pInput);
		}

		// ����������
		void CInput::Initialize(HWND hwnd)
		{
			// IDirectInput8�̍쐬
			DirectInput8Create(
				GetModuleHandle(NULL),
				DIRECTINPUT_VERSION,
				IID_IDirectInput8,
				(LPVOID*)&m_pInput,
				NULL);

			// IDirectInputDevice8�̎擾
			m_pInput->CreateDevice(
				GUID_SysKeyboard,
				&m_pInputDevice,
				NULL);

			if (m_pInputDevice == nullptr)
				return;

			// ���̓f�[�^�`���̃Z�b�g
			m_pInputDevice->SetDataFormat(&c_dfDIKeyboard);

			// �r������̃Z�b�g
			m_pInputDevice->SetCooperativeLevel(
				hwnd,
				DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);

			// ����J�n
			m_pInputDevice->Acquire();
		}

		// �X�V����
		void CInput::Update()
		{
			if (m_pInputDevice == nullptr)
				return;

			// �������R�s�[
			memcpy(&m_olds, &m_keys, sizeof(m_keys));

			// ���݂̓��͒l��z��ɓ����
			auto hr = m_pInputDevice->GetDeviceState(sizeof(m_keys), m_keys);

			if (FAILED(hr))
			{
				m_pInputDevice->Acquire();
				m_pInputDevice->GetDeviceState(sizeof(m_keys), m_keys);
			}
		}

		// ��x�̂�
		bool CInput::IsPressed(const BYTE keyCode)
		{
			return ((m_keys[keyCode] & 0x80) && !(m_olds[keyCode] & 0x80));
		}

		// ���̓L�[��������
		bool CInput::IsDown(const BYTE keyCode)
		{
			return (m_keys[keyCode] & 0x80);
		}

		// �L�[�𗣂�����
		bool CInput::IsUp(const BYTE keyCode)
		{
			return (!(m_keys[keyCode] & 0x80) && (m_olds[keyCode] & 0x80));
		}
	}
}