#pragma once
#include <cstdint>
#include <memory>
#include <thread>

struct AndroidPollSource
{
private:
	using HandlerFunctionType = void(*)(AndroidApplication*);

public:
	/* @brief	The identifier of this source.  May be LOOPER_ID_MAIN or LOOPER_ID_INPUT. */
	int32_t id;

	/* @brief	Function to call to perform the standard processing of data from this source. */
	HandlerFunctionType handler;
};


class AndroidApplication
{
/**
 * @section	Type definition
 */
private:
	using CommandType = std::int8_t;
	using InputEventType = std::int32_t;

	enum class EInputEventHandled : std::int32_t { kNo = 0, kYes = 1, };

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

	
/* @seciton Ctor/Dtor */
public:
    AndroidApplication(ANativeActivity* nativeActivity, void* saveState, std::size_t savedStateSize);
    virtual ~AndroidApplication();

/* @seciton Public method */
public:
    static AndroidApplication* Get();

/* @seciton Private method */
private:
    void InitializeCallback();

    /** @brief  Create pipe to send message into background thread */
    void InitializeMessagePipe();
    void InitializeConfigurationn();
    void InitializePollSource();
    void InitializeLooper();
    void InitializeSensor();

	void RunLooper();
	void OnHandleCommand(CommandType commandType);
	EInputEventHandled OnHandleInput(AInputEvent* inputEvent);

    void WriteCommand(CommandType commandType);
	CommandType ReadCommand() const;

	void SetActivityState(CommandType commandType);
	void SetNativeWindow(ANativeWindow* nativeWindow);
    void SetInputQueue(AInputQueue* inputQueue);

    static void OnDestroy(ANativeActivity* nativeActivity);
    static void OnStart(ANativeActivity* nativeActivity);
    static void OnResume(ANativeActivity* nativeActivity);
    static void* OnSaveInstanceState(ANativeActivity* nativeActivity, size_t* outLen);
    static void OnPause(ANativeActivity* nativeActivity);
    static void OnStop(ANativeActivity* nativeActivity);
    static void OnConfigurationChanged(ANativeActivity* nativeActivity);
    static void OnLowMemory(ANativeActivity* nativeActivity);
    static void OnWindowFocusChanged(ANativeActivity* nativeActivity, int focused);
    static void OnNativeWindowCreated(ANativeActivity* nativeActivity, ANativeWindow* window);
    static void OnNativeWindowDestroyed(ANativeActivity* nativeActivity, ANativeWindow* window);
    static void OnInputQueueCreated(ANativeActivity* nativeActivity, AInputQueue* queue);
    static void OnInputQueueDestroyed(ANativeActivity* nativeActivity, AInputQueue* queue);

/* @seciton Private variable */
private:
    ANativeActivity* m_nativeActivity;
    
    int m_readMsgPipe;
    int m_writeMsgPipe;

    pthread_mutex_t m_mutex;
    pthread_cond_t m_condition;

    std::thread m_backgroundThread;
    
    AConfiguration* m_config;
	AndroidPollSource m_cmdPollSource;
	AndroidPollSource m_inputPollSource;
    ALooper* m_looper;
    ASensorManager* m_sensorManager;
    const ASensor* m_accelerometerSensor;
    ASensorEventQueue* m_sensorEventQueue;

    ////////////////////////////////////
    // 이하부터 멤버이니셜라이저를 통한 초기화가 되지 않았음

    AInputQueue* m_pendingInputQueue = nullptr;
    AInputQueue* m_inputQueue = nullptr;
    ANativeWindow* m_pendingNativeWindow = nullptr;
    ANativeWindow* m_nativeWindow = nullptr;

	//void* m_savedState = nullptr;
	//int m_savedStateSize = 0;
	int m_activityState = 0;
	//int m_stateSaved = 0;
	bool m_destroyRequested = false;
	bool m_isDestroyed = false;
};