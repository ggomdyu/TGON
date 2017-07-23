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

namespace
{

AndroidApplication* g_androidApplication;

} /* namespace */

AndroidApplication::AndroidApplication(ANativeActivity* nativeActivity, void* saveState, std::size_t savedStateSize) :
    m_nativeActivity(nativeActivity),
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
    m_sensorEventQueue(nullptr)
{
	// Initialize application event callback.
    this->InitializeCallback();

    this->InitializeMessagePipe();

	::pthread_mutex_init(&m_mutex, nullptr);
	::pthread_cond_init(&m_condition, nullptr);

	bool isRunning = false;

    m_backgroundThread = std::thread([&]()
    {
        this->InitializeConfigurationn();
        this->InitializePollSource();
        this->InitializeLooper();

		pthread_mutex_lock(&m_mutex);
		{
			isRunning = true;
			pthread_cond_broadcast(&m_condition);
		}
		pthread_mutex_unlock(&m_mutex);

        this->InitializeSensor();
		this->RunLooper();

		//free_saved_state(android_app);
		pthread_mutex_lock(&m_mutex);
		if (m_inputQueue != NULL)
		{
			AInputQueue_detachLooper(m_inputQueue);
		}
		AConfiguration_delete(m_config);
		m_isDestroyed = true;

		pthread_cond_broadcast(&m_condition);
		pthread_mutex_unlock(&m_mutex);
    });

    while (isRunning == false);
}

AndroidApplication::~AndroidApplication()
{
	::pthread_mutex_lock(&m_mutex);
	{
		this->WriteCommand(APP_CMD_DESTROY);
		while (!m_isDestroyed)
		{
			::pthread_cond_wait(&m_condition, &m_mutex);
		}
	}
	::pthread_mutex_unlock(&m_mutex);

	::close(m_readMsgPipe);
	::close(m_writeMsgPipe);
	::pthread_cond_destroy(&m_condition);
	::pthread_mutex_destroy(&m_mutex);
}

AndroidApplication* AndroidApplication::Get()
{
    return g_androidApplication;
}

void AndroidApplication::SetActivityState(CommandType commandType)
{
	::pthread_mutex_lock(&m_mutex);
    {
        this->WriteCommand(commandType);
        while (m_activityState != commandType)
        {
			::pthread_cond_wait(&m_condition, &m_mutex);
        }
    }
    ::pthread_mutex_unlock(&m_mutex);
}

void AndroidApplication::InitializeCallback()
{
    m_nativeActivity->callbacks->onDestroy = AndroidApplication::OnDestroy;
    m_nativeActivity->callbacks->onStart = AndroidApplication::OnStart;
    m_nativeActivity->callbacks->onResume = AndroidApplication::OnResume;
    m_nativeActivity->callbacks->onSaveInstanceState = AndroidApplication::OnSaveInstanceState;
    m_nativeActivity->callbacks->onPause = AndroidApplication::OnPause;
    m_nativeActivity->callbacks->onStop = AndroidApplication::OnStop;
    m_nativeActivity->callbacks->onConfigurationChanged = AndroidApplication::OnConfigurationChanged;
    m_nativeActivity->callbacks->onLowMemory = AndroidApplication::OnLowMemory;
    m_nativeActivity->callbacks->onWindowFocusChanged = AndroidApplication::OnWindowFocusChanged;
    m_nativeActivity->callbacks->onNativeWindowCreated = AndroidApplication::OnNativeWindowCreated;
    m_nativeActivity->callbacks->onNativeWindowDestroyed = AndroidApplication::OnNativeWindowDestroyed;
    m_nativeActivity->callbacks->onInputQueueCreated = AndroidApplication::OnInputQueueCreated;
    m_nativeActivity->callbacks->onInputQueueDestroyed = AndroidApplication::OnInputQueueDestroyed;
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

void AndroidApplication::InitializeConfigurationn()
{
    m_config = AConfiguration_new();
	::AConfiguration_fromAssetManager(m_config, m_nativeActivity->assetManager);
}

void AndroidApplication::InitializePollSource()
{
    m_cmdPollSource.id = LOOPER_ID_MAIN;
	m_cmdPollSource.handler = [](AndroidApplication* application)
	{
		application->OnHandleCommand(application->ReadCommand());
	};
    m_inputPollSource.id = LOOPER_ID_INPUT;
	m_inputPollSource.handler = [](AndroidApplication* application)
	{
		AInputEvent* inputEvent = nullptr;
		while (::AInputQueue_getEvent(application->m_inputQueue, &inputEvent) >= 0)
		{
			LOGV("New input event: type=%d\n", ::AInputEvent_getType(inputEvent));
			if (::AInputQueue_preDispatchEvent(application->m_inputQueue, inputEvent))
			{
				continue;
			}

			auto inputEventHandled = application->OnHandleInput(inputEvent);
			::AInputQueue_finishEvent(application->m_inputQueue, inputEvent, static_cast<int>(inputEventHandled));
		}
	};
}

void AndroidApplication::InitializeLooper()
{
	ALooper* looper = ::ALooper_prepare(ALOOPER_PREPARE_ALLOW_NON_CALLBACKS);
	::ALooper_addFd(looper, m_readMsgPipe, LOOPER_ID_MAIN, ALOOPER_EVENT_INPUT, nullptr, &m_cmdPollSource);
	
	m_looper = looper;
}

void AndroidApplication::InitializeSensor()
{
    m_sensorManager = ::ASensorManager_getInstance();

    m_accelerometerSensor = ::ASensorManager_getDefaultSensor(m_sensorManager, ASENSOR_TYPE_ACCELEROMETER);
    m_sensorEventQueue = ::ASensorManager_createEventQueue(m_sensorManager, m_looper, LOOPER_ID_USER, nullptr, nullptr);
}

void AndroidApplication::RunLooper()
{
	while (true)
	{
		// Read all pending events.
		int ident;
		int events;
		AndroidPollSource* pollSource = nullptr;

		// If not animating, we will block forever waiting for events.
		// If animating, we loop until all events are read, then continue
		// to draw the next frame of animation.
		while ((ident = ALooper_pollAll(-1, nullptr, &events, reinterpret_cast<void**>(&pollSource))) >= 0)
		{
			// Process this event.
			if (pollSource != nullptr)
			{
				pollSource->handler(this);
			}

			// If a sensor has data, process it now.
			if (ident == LOOPER_ID_USER)
			{
				if (m_accelerometerSensor != nullptr)
				{
					ASensorEvent event;
					while (ASensorEventQueue_getEvents(m_sensorEventQueue, &event, 1) > 0)
					{
						LOGI("accelerometer: x=%f y=%f z=%f", event.acceleration.x, event.acceleration.y, event.acceleration.z);
					}
				}
			}

			// Check if we are exiting.
			if (m_destroyRequested == true)
			{
				//engine_term_display(&engine);
				return;
			}
		}

		//if (engine.animating) {
		//	// Done with events; draw next animation frame.
		//	engine.state.angle += .01f;
		//	if (engine.state.angle > 1) {
		//		engine.state.angle = 0;
		//	}
		//
		//	// Drawing is throttled to the screen update rate, so there
		//	// is no need to do timing here.
		//	//engine_draw_frame(&engine);
		//}
	}
}

void AndroidApplication::SetNativeWindow(ANativeWindow* nativeWindow)
{
	::pthread_mutex_lock(&m_mutex);
    {
        if (m_pendingNativeWindow != nullptr)
        {
            WriteCommand(APP_CMD_TERM_WINDOW);
        }

        m_pendingNativeWindow = nativeWindow;

        if (nativeWindow != nullptr)
        {
            WriteCommand(APP_CMD_INIT_WINDOW);
        }

        while (m_nativeWindow != m_pendingNativeWindow)
        {
            pthread_cond_wait(&m_condition, &m_mutex);
        }
    }
	::pthread_mutex_unlock(&m_mutex);
}


void AndroidApplication::SetInputQueue(AInputQueue* inputQueue)
{
	::pthread_mutex_lock(&m_mutex);
    {
        m_pendingInputQueue = inputQueue;

        this->WriteCommand(APP_CMD_INPUT_CHANGED);

        while (m_inputQueue != m_pendingInputQueue)
        {
            pthread_cond_wait(&m_condition, &m_mutex);
        }
    }
	::pthread_mutex_unlock(&m_mutex);
}

void AndroidApplication::OnDestroy(ANativeActivity* nativeActivity)
{
    LOGV("AndroidApplication::OnDestroy\n");

    delete g_androidApplication;
    g_androidApplication = nullptr;
}

void AndroidApplication::OnStart(ANativeActivity* nativeActivity)
{
    LOGV("AndroidApplication::OnStart\n");

    g_androidApplication->SetActivityState(APP_CMD_START);
}

void AndroidApplication::OnResume(ANativeActivity* nativeActivity)
{
    LOGV("AndroidApplication::OnResume\n");
    g_androidApplication->SetActivityState(APP_CMD_RESUME);
}

void* AndroidApplication::OnSaveInstanceState(ANativeActivity* nativeActivity, size_t* outLen)
{
    LOGV("AndroidApplication::OnSaveInstanceState\n");
    return nullptr;
}

void AndroidApplication::OnPause(ANativeActivity* nativeActivity)
{
    LOGV("AndroidApplication::OnPause\n");
	g_androidApplication->SetActivityState(APP_CMD_PAUSE);
}

void AndroidApplication::OnStop(ANativeActivity* nativeActivity)
{
    LOGV("AndroidApplication::OnStop\n");
	g_androidApplication->SetActivityState(APP_CMD_STOP);
}

void AndroidApplication::OnConfigurationChanged(ANativeActivity* nativeActivity)
{
    LOGV("AndroidApplication::OnConfigurationChanged\n");
	g_androidApplication->WriteCommand(APP_CMD_CONFIG_CHANGED);
}

void AndroidApplication::OnLowMemory(ANativeActivity* nativeActivity)
{
    LOGV("AndroidApplication::OnLowMemory\n");
	g_androidApplication->WriteCommand(APP_CMD_LOW_MEMORY);
}

void AndroidApplication::OnWindowFocusChanged(ANativeActivity* nativeActivity, int focused)
{
    LOGV("AndroidApplication::OnWindowFocusChanged (%d)\n", focused);
	g_androidApplication->WriteCommand(focused ? APP_CMD_GAINED_FOCUS : APP_CMD_LOST_FOCUS);
}

void AndroidApplication::OnNativeWindowCreated(ANativeActivity* nativeActivity, ANativeWindow* nativeWindow)
{
    LOGV("AndroidApplication::OnNativeWindowCreated\n");
	g_androidApplication->SetNativeWindow(nativeWindow);
}

void AndroidApplication::OnNativeWindowDestroyed(ANativeActivity* nativeActivity, ANativeWindow* nativeWindow)
{
	LOGV("AndroidApplication::OnNativeWindowDestroyed\n");
	g_androidApplication->SetNativeWindow(nullptr);
}

void AndroidApplication::OnInputQueueCreated(ANativeActivity* nativeActivity, AInputQueue* inputQueue)
{
	LOGV("AndroidApplication::OnInputQueueCreated\n");
	g_androidApplication->SetInputQueue(inputQueue);
}

void AndroidApplication::OnInputQueueDestroyed(ANativeActivity* nativeActivity, AInputQueue* queue)
{
    LOGV("AndroidApplication::OnInputQueueDestroyed\n");
	g_androidApplication->SetInputQueue(nullptr);
}

void AndroidApplication::OnHandleCommand(CommandType commandType)
{
	switch (commandType)
	{
	case APP_CMD_INPUT_CHANGED:
		LOGV("APP_CMD_INPUT_CHANGED\n");

		::pthread_mutex_lock(&m_mutex);
		{
			if (m_inputQueue != nullptr)
			{
				::AInputQueue_detachLooper(m_inputQueue);
			}
			m_inputQueue = m_pendingInputQueue;
			if (m_inputQueue != nullptr)
			{
				LOGV("Attaching input queue to looper");
				::AInputQueue_attachLooper(m_inputQueue, m_looper, LOOPER_ID_INPUT, nullptr, &m_inputPollSource);
			}
			::pthread_cond_broadcast(&m_condition);
		}
		::pthread_mutex_unlock(&m_mutex);
		break;

	case APP_CMD_INIT_WINDOW:
		LOGV("APP_CMD_INIT_WINDOW\n");

		::pthread_mutex_lock(&m_mutex);
		{
			m_nativeWindow = m_pendingNativeWindow;
			::pthread_cond_broadcast(&m_condition);
		}
		::pthread_mutex_unlock(&m_mutex);

		// The window is being shown, get it ready.
		if (m_nativeWindow != nullptr)
		{
			//engine_init_display(engine);
			//engine_draw_frame(engine);
		}
		break;

	case APP_CMD_TERM_WINDOW:
		LOGV("APP_CMD_TERM_WINDOW\n");
		::pthread_cond_broadcast(&m_condition);

		// 창을 숨기거나 닫아 정리합니다.
		//engine_term_display(engine);

		::pthread_mutex_lock(&m_mutex);
		{
			m_nativeWindow = nullptr;
			::pthread_cond_broadcast(&m_condition);
		}
		::pthread_mutex_unlock(&m_mutex);

		// The window is being hidden or closed, clean it up.
		//engine_term_display(engine);
		break;

	case APP_CMD_RESUME:
		LOGV("activityState=%d\n", commandType);
		::pthread_mutex_lock(&m_mutex);
		{
			m_activityState = commandType;
			::pthread_cond_broadcast(&m_condition);
		}
		::pthread_mutex_unlock(&m_mutex);

		//FreeSavedState(app);
		break;

	case APP_CMD_START:
	case APP_CMD_PAUSE:
	case APP_CMD_STOP:
		LOGV("activityState=%d\n", commandType);
		::pthread_mutex_lock(&m_mutex);
		{
			m_activityState = commandType;
			::pthread_cond_broadcast(&m_condition);
		}
		::pthread_mutex_unlock(&m_mutex);

		//FreeSavedState(app);
		break;

	case APP_CMD_CONFIG_CHANGED:
		LOGV("APP_CMD_CONFIG_CHANGED\n");
		::AConfiguration_fromAssetManager(m_config, m_nativeActivity->assetManager);
		//print_cur_config(app);
		break;

	case APP_CMD_DESTROY:
		LOGV("APP_CMD_DESTROY\n");
		m_destroyRequested = 1;
		break;

	case APP_CMD_SAVE_STATE:
		LOGV("APP_CMD_SAVE_STATE\n");

		//FreeSavedState();

		// The system has asked us to save our current state.  Do so.
		/*m_savedState = malloc(sizeof(struct saved_state));
		*((struct saved_state*)m_savedState) = engine->state;
		m_savedStateSize = sizeof(struct saved_state);*/

		//pthread_mutex_lock(&m_mutex);
		//{
		//	m_stateSaved = 1;
		//	pthread_cond_broadcast(&m_condition);
		//}
		//pthread_mutex_unlock(&m_mutex);
		break;

	case APP_CMD_GAINED_FOCUS:
		// When our app gains focus, we start monitoring the accelerometer.
		if (m_accelerometerSensor != nullptr)
		{
			::ASensorEventQueue_enableSensor(m_sensorEventQueue, m_accelerometerSensor);
			// We'd like to get 60 events per second (in us).
			::ASensorEventQueue_setEventRate(m_sensorEventQueue, m_accelerometerSensor, (1000L / 60) * 1000);
		}
		break;
	case APP_CMD_LOST_FOCUS:
		// When our app loses focus, we stop monitoring the accelerometer.
		// This is to avoid consuming battery while not being used.
		if (m_accelerometerSensor != nullptr)
		{
			::ASensorEventQueue_disableSensor(m_sensorEventQueue, m_accelerometerSensor);
		}
		// Also stop animating.
		//engine->animating = 0;
		//engine_draw_frame(engine);
		break;
	}
}

AndroidApplication::EInputEventHandled AndroidApplication::OnHandleInput(AInputEvent* inputEvent)
{
	auto inputEventType = ::AInputEvent_getType(inputEvent);
	if (inputEventType == AINPUT_EVENT_TYPE_MOTION)
	{
		//app->state.x = AMotionEvent_getX(event, 0);
		//app->state.y = AMotionEvent_getY(event, 0);
		return EInputEventHandled::kYes;
	}
	else if (inputEventType == AINPUT_EVENT_TYPE_KEY)
	{
		return EInputEventHandled::kYes;
	}

	return EInputEventHandled::kNo;
}

void AndroidApplication::WriteCommand(CommandType commandType)
{
    if (::write(m_writeMsgPipe, &commandType, sizeof(commandType)) != sizeof(commandType))
    {
        LOGE("Failure writing command: %s\n", strerror(errno));
    }
}

AndroidApplication::CommandType AndroidApplication::ReadCommand() const
{
	CommandType commandType;
	if (::read(m_readMsgPipe, &commandType, sizeof(commandType)) == sizeof(commandType))
	{
		return commandType;
	}
	else
	{
		LOGE("No data on command pipe!");
	}

	return -1;
}

void ANativeActivity_onCreate(ANativeActivity* nativeActivity, void* savedState, size_t savedStateSize)
{
    g_androidApplication = new AndroidApplication(nativeActivity, savedState, savedStateSize);
}