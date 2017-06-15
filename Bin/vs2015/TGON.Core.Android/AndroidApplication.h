#pragma once
#include <cstdint>
#include <memory>
#include <thread>

class AndroidApplication
{
/**
 * @seciton Nested class
 */
private:
    enum
    {
        /**
         * Option for ALooper_prepare: this looper will accept calls to
         * ALooper_addFd() that do not have a callback (that is provide NULL
         * for the callback).  In this case the caller of ALooper_pollOnce()
         * or ALooper_pollAll() MUST check the return from these functions to
         * discover when data is available on such fds and process it.
         */
        ALOOPER_PREPARE_ALLOW_NON_CALLBACKS = 1 << 0
    };

    struct PollSource
    {
        /* @brief   Function to call to perform the standard processing of data from this source */
        void(*process)(AndroidApplication* app, PollSource* source);

        /* @brief   The identifier of this source. May be LOOPER_ID_MAIN or LOOPER_ID_INPUT. */
        int32_t id;

        /* @brief   The AndroidApplication this ident is associated with. */
        AndroidApplication* application;
    };

/**
 * @seciton Ctor/Dtor
 */
public:
    AndroidApplication();
    virtual ~AndroidApplication() = default;

    /**
     * @brief   Called when after ....
     */
    void Initialize(ANativeActivity* nativeActivity, void* saveState, std::size_t savedStateSize);

/**
 * @seciton Private method
 */
private:
    void InitializeMessagePipe();
    void InitializeConfig();
    void InitializePollSource();
    void InitializeLooper();
    void InitializeSensor();

    static void ProcessCommand(AndroidApplication* application, PollSource* source);
    static void ProcessInput(AndroidApplication* application, PollSource* source);

/**
 * @seciton Private variable
 */
private:
    ANativeActivity* m_nativeActivity;
    
    int m_readMsgPipe;
    int m_writeMsgPipe;

    pthread_mutex_t m_mutex;
    pthread_cond_t m_condition;

    std::thread m_backgroundThread;
    
    AConfiguration* m_config;
    PollSource m_cmdPollSource;
    PollSource m_inputPollSource;
    ALooper* m_looper;
    ASensorManager* m_sensorManager;
    const ASensor* m_accelerometerSensor;
    ASensorEventQueue* m_sensorEventQueue;

    bool m_isRunning;
};