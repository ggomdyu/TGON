/*
* Author : Cha Junho
* Date : 11/12/2016
* Latest author :
* Latest date :
*/

#pragma once


namespace tgon
{


template <typename StateTy>
class StateMachine
{
	/**
	 * Ctor/Dtor
	 */
public:
	FStateMachine( const StateTy& initialState );
	virtual ~FStateMachine( ) = default;
	
	/**
	 * Methods
	 */
public:
	/**
	 * @param newState	The State you want to change to
	 */
	void ChangeState( const StateTy& newState );

	/** 
	 * Event handlers
	 */ 
	virtual void OnStateEnd( const StateTy& prevState ) {};
	virtual void OnStateChanged( const StateTy& newState ) {};

	/**
	 * Private members
	 */
private:
	StateTy m_state;
	StateTy m_prevState;
};

template<typename StateTy>
FStateMachine<StateTy>::FStateMachine( const StateTy& initialState ) :
	m_state( initialState ),
	m_prevState{ initialState }
{
}

template<typename StateTy>
void FStateMachine<StateTy>::ChangeState( const StateTy& newState )
{
	m_prevState = m_state;
	m_state = newState;
	
	this->OnStateEnd( m_prevState );
	this->OnStateChanged( newState );
}


}
