/*
* Author : Taewoo-Kim
* Date : 04/25/2015
* Latest author : Junho-Cha
* Latest date : 05/22/2016
*/


#pragma once


/*
	Preprocessor version
*/
#define TGON_SINGLETON( typeName )\
	static typeName* Get( )\
	{\
		static typeName instance;\
		return &instance;\
	}

#define TGON_SINGLETON_DYNAMIC( typeName )\
	static const std::unique_ptr<typeName>& Get( )\
	{\
		static std::unique_ptr<typeName> instance( new typeName );\
		return instance;\
	}


/*
	Inherit version
*/
class ISingleton
{
	friend class TSingletonGuard;

private:
	virtual void Release( ) {};
};

template <class _Ty>
class TSingleton : public ISingleton
{
private:
	class SingletonInhProxy : public _Ty {};

public:
	static _Ty* Get( )
	{
		static SingletonInhProxy spInst;
		return &spInst;
	}

protected:
	TSingleton( )
	{
		TSingletonGuard::Get()->Push( this );
	}
	virtual ~TSingleton( ) {}
};

class TSingletonGuard
{
public:
	static TSingletonGuard* Get( )
	{
		static TSingletonGuard myInstance;
		return &myInstance;
	}

	void Push( ISingleton* singleton )
	{
		auto iter = std::find(
			m_singletonRepo.begin( ),
			m_singletonRepo.end( ),
			singleton
		);

		// Does not exist?
		if ( iter != m_singletonRepo.end( ))
		{
			m_singletonRepo.push_back( singleton );
		}
	}

private:
	~TSingletonGuard( )
	{
		for ( auto& singletonElem : m_singletonRepo )
		{
			singletonElem->Release( );
		}
	}

private:
	std::vector<ISingleton*> m_singletonRepo;
};


//template <class _Ty>
//class TSingletonDynamic : public ISingleton
//{
//private:
//	class SingletonInhProxy : public _Ty 
//	{
//		friend std::default_delete<_Ty>;
//	};
//
//public:
//	static _Ty* Get( )
//	{
//		// TODO : Induce this code to inline
//		static std::unique_ptr<SingletonInhProxy> 
//			spInstPtr( new SingletonInhProxy );
//		return spInstPtr.get();
//	}
//
//	virtual void Release( ) override {}
//
//protected:
//	TSingletonDynamic( ) {}
//	virtual ~TSingletonDynamic( ) {}
//};


// Deprecated...
/*
#define DECLARE_DYNAMIC_SINGLETON( )\
private:\
	template<typename base_t>\
	inline static base_t owner_tag( void( base_t::* )( ));\
\
	void internal_tag( );\
	typedef decltype( owner_tag( &internal_tag )) this_t;\
\
public:\
	static const std::unique_ptr<this_t>& Get( )\
	{\
	}
*/