/*
* �ۼ��� : ����ȣ
* �ۼ��� : 2015-11-12
* ���� ���� :
* ���� ������ :
*/

#pragma once
/* Type 1

	Baisically follow 'Implement in term of'

*/
class Uncopyable
{
protected:
	Uncopyable( ) {};
	~Uncopyable( ) {};

private:
	Uncopyable( const Uncopyable& ) = delete;
	Uncopyable& operator=( const Uncopyable& ) = delete;
};

/* Type 2
	
	bad way ( code bloat issue & I hate preprocessor )  

*/
#define Implement_Uncopyable( T )			\
private:											\
	T( const T& ) = delete;						\
	T& operator=( const T& ) = delete;
