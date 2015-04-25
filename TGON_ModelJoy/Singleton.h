#pragma once
template <typename T> class CSingleton
{
private:
	static T* m_Instance;

public:
	static T* InstancePtr()
	{
		if ( m_Instance == nullptr )
		{
			m_Instance = new T;
		}
		return m_Instance;
	}

	static void DestroyInstance()
	{
		if ( m_Instance != nullptr )
		{
			delete m_Instance;
			m_Instance = nullptr;
		}
	}
};

template <typename T> T* CSingleton<T>::m_Instance = nullptr;