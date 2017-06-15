#include "pch.h"
#include "AndroidApplication.h"

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "threaded_app", __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "threaded_app", __VA_ARGS__))

/* For debug builds, always enable the debug traces in this library */
#ifndef NDEBUG
#  define LOGV(...)  ((void)__android_log_print(ANDROID_LOG_VERBOSE, "threaded_app", __VA_ARGS__))
#else
#  define LOGV(...)  ((void)0)
#endif

AndroidApplication::AndroidApplication() :
    m_nativeActivity(nullptr),
    m_readMsgPipe(0),
    m_writeMsgPipe(0),
    m_mutex{},
    m_condition{},
    m_config(nullptr),
    m_cmdPollSource{},
    m_inputPollSource{},
    m_looper(nullptr),
    m_sensorManager(nullptr),
    m_accelerometerSensor(nullptr),
    m_sensorEventQueue(nullptr),
    m_isRunning(false)
{
}

void AndroidApplication::Initialize(ANativeActivity* nativeActivity, void* saveState, std::size_t savedStateSize)
{
    this->InitializeMessagePipe();

    pthread_mutex_init(&m_mutex, nullptr);
    pthread_cond_init(&m_condition, nullptr);

    m_backgroundThread = std::thread([&]()
    {
        this->InitializeConfig();
        this->InitializePollSource();
        this->InitializeLooper();
        this->InitializeSensor();

        m_isRunning = true;
    });

    while (m_isRunning == false);
}

void AndroidApplication::InitializeMessagePipe()
{
    int msgPipe[2];
    if (::pipe(msgPipe))
    {
        LOGE("could not create pipe: %s", strerror(errno));
        return;
    }

    m_readMsgPipe = msgPipe[0];
    m_writeMsgPipe = msgPipe[1];
}

void AndroidApplication::InitializeConfig()
{
    m_config = AConfiguration_new();
    if (m_config == nullptr)
    {
        return;
    }

    AConfiguration_fromAssetManager(m_config, m_nativeActivity->assetManager);
}

void AndroidApplication::InitializePollSource()
{
    m_cmdPollSource.id = LOOPER_ID_MAIN;
    m_cmdPollSource.application = this;
    m_cmdPollSource.process = ProcessCommand;
    m_inputPollSource.id = LOOPER_ID_INPUT;
    m_inputPollSource.application = this;
    m_inputPollSource.process = ProcessInput;
}

void AndroidApplication::InitializeLooper()
{
    ALooper* looper = ALooper_prepare(ALOOPER_PREPARE_ALLOW_NON_CALLBACKS);
    m_looper = looper;

    ALooper_addFd(looper, m_readMsgPipe, LOOPER_ID_MAIN, ALOOPER_EVENT_INPUT, nullptr, &m_cmdPollSource);
}

void AndroidApplication::InitializeSensor()
{
    m_sensorManager = ASensorManager_getInstance();

    m_accelerometerSensor = ASensorManager_getDefaultSensor(m_sensorManager, ASENSOR_TYPE_ACCELEROMETER);
    m_sensorEventQueue = ASensorManager_createEventQueue(m_sensorManager, m_looper, LOOPER_ID_USER, nullptr, nullptr);
}

void AndroidApplication::ProcessCommand(AndroidApplication* application, PollSource* source)
{
}

void AndroidApplication::ProcessInput(AndroidApplication* application, PollSource* source)
{
}
