///**
// * @filename    FStateMachine.h
// * @author      ggomdyu
// * @since       11/12/2016
// */
//
//#pragma once
//
//namespace tgon
//{
//namespace utility
//{
//
//template <typename _StateType>
//class FStateMachine
//{
///* @section Public constructor */
//public:
//    FStateMachine() = default;
//
//    template <typename... _ArgTypes>
//    FStateMachine(_ArgTypes&&... args);
//
///* @section Public destructor */
//public:
//    virtual ~FStateMachine() = default;
//
///* @section Public method */
//public:
//    /* @brief   Change current state. */
//    void ChangeState(_StateType&& newState);
//    void ChangeState(const _StateType& newState);
//
//    /* @brief   Called when a new state is begun. */
//    virtual void OnDidEnterState(const _StateType& newState) {}
//
//    /* @brief   Called when the current state will over. */
//    virtual void OnWillExitState(const _StateType& prevState) {}
//
//    const _StateType& GetCurrentState() const noexcept;
//
///* @section Private variable */
//private:
//    _StateType m_currState;
////};
//
//template <typename _StateType>
//template <typename... _ArgTypes>
//inline FStateMachine<_StateType>::FStateMachine(_ArgTypes&&... args) :
//    m_currState(args...)
//{
//}
//
//template<typename _StateType>
//void FStateMachine<_StateType>::ChangeState(_StateType&& newState)
//{
//    this->OnWillExitState(m_currState);
//
//    m_currState = std::move(newState);
//    this->OnDidEnterState(newState);
//}
//
//template<typename _StateType>
//void FStateMachine<_StateType>::ChangeState(const _StateType& newState)
//{
//    this->OnWillExitState(m_currState);
//
//    m_currState = newState;
//    this->OnDidEnterState(newState);
//}
//
//template<typename _StateType>
//inline const _StateType& FStateMachine<_StateType>::GetCurrentState() const noexcept
//{
//    return m_currState;
//}
//
//} /* namespace utility */
//} /* namespace tgon */

