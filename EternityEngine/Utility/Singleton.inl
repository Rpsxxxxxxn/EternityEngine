#include "Singleton.h"

namespace Eternity
{
	namespace Utility
	{
		template<class Type> std::once_flag CSingleton<Type>::m_onceFlg;
		template<class Type> Type* CSingleton<Type>::m_pInstance = nullptr;

		template<class Type>
		inline Type& CSingleton<Type>::GetInstance()
		{
			std::call_once(m_onceFlg, Create);
			return *m_pInstance;
		}

		template<class Type>
		inline void CSingleton<Type>::Create()
		{
			m_pInstance = new Type;
			CSingletonFinalizer::AddFinalizer(&CSingleton<Type>::Destroy);
		}

		template<class Type>
		inline void CSingleton<Type>::Destroy()
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
}