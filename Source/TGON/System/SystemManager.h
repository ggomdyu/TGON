/*
* �ۼ��� : ����ȣ
* �ۼ��� : 2016-04-02
* ���� ���� :
* ���� ������ :
* Description :
*/


#pragma once
#include <iostream>
#include <string>
#include <map>
#include "../Object/TObject.h"


namespace tgon
{


class SystemManager
{
public:
	// Singleton
	static SystemManager* Get( )
	{
		static SystemManager inst;
		return &inst;
	}


	void AddSubSystem( TObject* object )
	{
		
	}

	
	template <class T> T* GetSubSystem( )
	{
		
	}

private:
	std::map<TObject*, uint32_t> m_sysRepo;
	
};


}