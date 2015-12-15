#include "Singleton.h"

template <typename T>
decltype( typename DynamicSingleton<T>::m_instance ) DynamicSingleton<T>::m_instance;