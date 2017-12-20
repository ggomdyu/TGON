/*
 * Copyright (C) 2010 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
//
//#include "../../../Source/TGON/Core/Platform/Generic/GenericWindow.h"
//
//namespace tgon {
//namespace platform {
//namespace android {
//
//class TGON_API AndroidWindow :
//    public GenericWindow
//{
//public:
//    AndroidWindow();
//    AndroidWindow(ANativeWindow* nativeWindow);
//
//    virtual void GetExtent() 
//
//private:
//    ANativeWindow* m_nativeWindow;
//};
//
//}
//}
//}

// Set of data for application maintaing, destroyed when OnDestroy invoked.
AndroidApp* g_androidApp;

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "threaded_app", __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "threaded_app", __VA_ARGS__))

/* For debug builds, always enable the debug traces in this library */
#ifndef NDEBUG
#  define LOGV(...)  ((void)__android_log_print(ANDROID_LOG_VERBOSE, "threaded_app", __VA_ARGS__))
#else
#  define LOGV(...)  ((void)0)
#endif

static void FreeSavedState(AndroidApp* android_app)
{
    pthread_mutex_lock(&android_app->mutex);
    {
        if (android_app->savedState != nullptr)
        {
            free(android_app->savedState);
            android_app->savedState = nullptr;
            android_app->savedStateSize = 0;
        }
    }
    pthread_mutex_unlock(&android_app->mutex);
}

int8_t ReadCommand(AndroidApp* android_app)
{
    int8_t cmd;
    if (read(android_app->msgread, &cmd, sizeof(cmd)) == sizeof(cmd)) {
        switch (cmd) {
            case APP_CMD_SAVE_STATE:
                FreeSavedState(android_app);
                break;
        }
        return cmd;
    } else {
        LOGE("No data on command pipe!");
    }
    return -1;
}

static void print_cur_config(AndroidApp* android_app)
{
    char lang[2], country[2];
    AConfiguration_getLanguage(android_app->config, lang);
    AConfiguration_getCountry(android_app->config, country);

    LOGV("Config: mcc=%d mnc=%d lang=%c%c cnt=%c%c orien=%d touch=%d dens=%d "
            "keys=%d nav=%d keysHid=%d navHid=%d sdk=%d size=%d long=%d "
            "modetype=%d modenight=%d",
            AConfiguration_getMcc(android_app->config),
            AConfiguration_getMnc(android_app->config),
            lang[0], lang[1], country[0], country[1],
            AConfiguration_getOrientation(android_app->config),
            AConfiguration_getTouchscreen(android_app->config),
            AConfiguration_getDensity(android_app->config),
            AConfiguration_getKeyboard(android_app->config),
            AConfiguration_getNavigation(android_app->config),
            AConfiguration_getKeysHidden(android_app->config),
            AConfiguration_getNavHidden(android_app->config),
            AConfiguration_getSdkVersion(android_app->config),
            AConfiguration_getScreenSize(android_app->config),
            AConfiguration_getScreenLong(android_app->config),
            AConfiguration_getUiModeType(android_app->config),
            AConfiguration_getUiModeNight(android_app->config));
}

static void android_app_destroy(AndroidApp* android_app)
{
    LOGV("android_app_destroy!");
    FreeSavedState(android_app);
    pthread_mutex_lock(&android_app->mutex);
    if (android_app->inputQueue != nullptr) {
        AInputQueue_detachLooper(android_app->inputQueue);
    }
    AConfiguration_delete(android_app->config);
    android_app->destroyed = 1;
    pthread_cond_broadcast(&android_app->cond);
    pthread_mutex_unlock(&android_app->mutex);
    // Can't touch android_app object after this.
}

static void ProcessInput(AndroidApp* app, android_poll_source* source)
{
    AInputEvent* event = nullptr;
    while (AInputQueue_getEvent(app->inputQueue, &event) >= 0)
    {
        LOGV("New input event: type=%d\n", AInputEvent_getType(event));
        if (AInputQueue_preDispatchEvent(app->inputQueue, event))
        {
            continue;
        }
        
        int32_t handled = 0;
        if (app->onHandleInput != nullptr)
        {
            handled = app->onHandleInput(app, event);
        }
        AInputQueue_finishEvent(app->inputQueue, event, handled);
    }
}

static void ProcessCommand(AndroidApp* app, struct android_poll_source* source)
{
    int8_t cmd = ReadCommand(app);
    
    /**
     * Call with the command returned by android_app_read_cmd() to do the
     * initial pre-processing of the given command.  You can perform your own
     * actions for the command after calling this function.
     */
    //void android_app_pre_exec_cmd(struct android_app* android_app, int8_t cmd);

    if (app->onHandleCommand != nullptr)
    {
        app->onHandleCommand(app, cmd);
    }

    /**
     * Call with the command returned by android_app_read_cmd() to do the
     * final post-processing of the given command.  You must have done your own
     * actions for the command before calling this function.
     */
    //void android_app_post_exec_cmd(struct android_app* android_app, int8_t cmd);
}

static void* BackgroundThreadEntry(void* param)
{
    AndroidApp* app = reinterpret_cast<AndroidApp*>(param);

    app->config = AConfiguration_new();
    AConfiguration_fromAssetManager(app->config, app->activity->assetManager);

    print_cur_config(app);

    app->cmdPollSource.id = LOOPER_ID_MAIN;
    app->cmdPollSource.app = app;
    app->cmdPollSource.process = ProcessCommand;
    app->inputPollSource.id = LOOPER_ID_INPUT;
    app->inputPollSource.app = app;
    app->inputPollSource.process = ProcessInput;

    ALooper* looper = ALooper_prepare(ALOOPER_PREPARE_ALLOW_NON_CALLBACKS);
    app->looper = looper;

    ALooper_addFd(looper, app->msgread, LOOPER_ID_MAIN, ALOOPER_EVENT_INPUT, nullptr, &app->cmdPollSource);

    pthread_mutex_lock(&app->mutex);
    {
        app->running = 1;
        pthread_cond_broadcast(&app->cond);
    }
    pthread_mutex_unlock(&app->mutex);

    android_main(app);

    android_app_destroy(app);
    return nullptr;
}

// --------------------------------------------------------------------
// Native activity interaction (called from main thread)
// --------------------------------------------------------------------

static void WriteCommand(AndroidApp* android_app, int8_t cmd)
{
    if (write(android_app->msgwrite, &cmd, sizeof(cmd)) != sizeof(cmd))
    {
        LOGE("Failure writing android_app cmd: %s\n", strerror(errno));
    }
}

static void SetInputQueue(AndroidApp* android_app, AInputQueue* inputQueue)
{
    pthread_mutex_lock(&android_app->mutex);
    {
        android_app->pendingInputQueue = inputQueue;
        WriteCommand(android_app, APP_CMD_INPUT_CHANGED);
        while (android_app->inputQueue != android_app->pendingInputQueue)
        {
            pthread_cond_wait(&android_app->cond, &android_app->mutex);
        }
    }
    pthread_mutex_unlock(&android_app->mutex);
}

static void SetNativeWindow(AndroidApp* android_app, ANativeWindow* window)
{
    pthread_mutex_lock(&android_app->mutex);
    {
        if (android_app->pendingWindow != nullptr)
        {
            WriteCommand(android_app, APP_CMD_TERM_WINDOW);
        }
        android_app->pendingWindow = window;
        if (window != nullptr)
        {
            WriteCommand(android_app, APP_CMD_INIT_WINDOW);
        }
        while (android_app->window != android_app->pendingWindow)
        {
            pthread_cond_wait(&android_app->cond, &android_app->mutex);
        }
    }
    pthread_mutex_unlock(&android_app->mutex);
}

class LockGuard
{
public:
};

static void SetActivityState(AndroidApp* app, int8_t cmd)
{
    pthread_mutex_lock(&app->mutex);
    {
        WriteCommand(app, cmd);
        while (app->activityState != cmd)
        {
            pthread_cond_wait(&app->cond, &app->mutex);
        }
    }
    pthread_mutex_unlock(&app->mutex);
}

static void android_app_free(struct AndroidApp* android_app)
{
    pthread_mutex_lock(&android_app->mutex);
    WriteCommand(android_app, APP_CMD_DESTROY);
    while (!android_app->destroyed) {
        pthread_cond_wait(&android_app->cond, &android_app->mutex);
    }
    pthread_mutex_unlock(&android_app->mutex);

    close(android_app->msgread);
    close(android_app->msgwrite);
    pthread_cond_destroy(&android_app->cond);
    pthread_mutex_destroy(&android_app->mutex);
    free(android_app);
}

static void OnDestroy(ANativeActivity* activity)
{
    LOGV("Destroy: %p\n", activity);
    android_app_free((struct AndroidApp*)activity->instance);
}

static void OnStart(ANativeActivity* activity)
{
    LOGV("Start: %p\n", activity);
    SetActivityState((struct AndroidApp*)activity->instance, APP_CMD_START);
}

static void OnResume(ANativeActivity* activity)
{
    LOGV("Resume: %p\n", activity);
    SetActivityState((struct AndroidApp*)activity->instance, APP_CMD_RESUME);
}

static void* OnSaveInstanceState(ANativeActivity* activity, size_t* outLen)
{
    struct AndroidApp* android_app = (struct AndroidApp*)activity->instance;
    void* savedState = nullptr;

    LOGV("SaveInstanceState: %p\n", activity);
    pthread_mutex_lock(&android_app->mutex);
    {
        android_app->stateSaved = 0;
        WriteCommand(android_app, APP_CMD_SAVE_STATE);
        while (!android_app->stateSaved)
        {
            pthread_cond_wait(&android_app->cond, &android_app->mutex);
        }

        if (android_app->savedState != nullptr)
        {
            savedState = android_app->savedState;
            *outLen = android_app->savedStateSize;
            android_app->savedState = nullptr;
            android_app->savedStateSize = 0;
        }
    }
    pthread_mutex_unlock(&android_app->mutex);

    return savedState;
}

static void OnPause(ANativeActivity* activity)
{
    LOGV("Pause: %p\n", activity);
    SetActivityState((struct AndroidApp*)activity->instance, APP_CMD_PAUSE);
}

static void OnStop(ANativeActivity* activity)
{
    LOGV("Stop: %p\n", activity);
    SetActivityState((struct AndroidApp*)activity->instance, APP_CMD_STOP);
}

static void OnConfigurationChanged(ANativeActivity* activity)
{
    struct AndroidApp* android_app = (struct AndroidApp*)activity->instance;
    LOGV("ConfigurationChanged: %p\n", activity);
    WriteCommand(android_app, APP_CMD_CONFIG_CHANGED);
}

static void OnLowMemory(ANativeActivity* activity)
{
    struct AndroidApp* android_app = (struct AndroidApp*)activity->instance;
    LOGV("LowMemory: %p\n", activity);
    WriteCommand(android_app, APP_CMD_LOW_MEMORY);
}

static void OnWindowFocusChanged(ANativeActivity* activity, int focused) {
    LOGV("WindowFocusChanged: %p -- %d\n", activity, focused);
    WriteCommand((struct AndroidApp*)activity->instance, focused ? APP_CMD_GAINED_FOCUS : APP_CMD_LOST_FOCUS);
}

static void OnNativeWindowCreated(ANativeActivity* activity, ANativeWindow* window) {
    LOGV("NativeWindowCreated: %p -- %p\n", activity, window);
    SetNativeWindow((struct AndroidApp*)activity->instance, window);
}

static void OnNativeWindowDestroyed(ANativeActivity* activity, ANativeWindow* window) {
    LOGV("NativeWindowDestroyed: %p -- %p\n", activity, window);
    SetNativeWindow((struct AndroidApp*)activity->instance, nullptr);
}

static void OnInputQueueCreated(ANativeActivity* activity, AInputQueue* queue) {
    LOGV("InputQueueCreated: %p -- %p\n", activity, queue);
    SetInputQueue((struct AndroidApp*)activity->instance, queue);
}

static void OnInputQueueDestroyed(ANativeActivity* activity, AInputQueue* queue) {
    LOGV("InputQueueDestroyed: %p -- %p\n", activity, queue);
    SetInputQueue((struct AndroidApp*)activity->instance, nullptr);
}

void ANativeActivity_onCreate(ANativeActivity* activity, void* savedState, size_t savedStateSize)
{
    LOGV("Creating: %p\n", activity);
    activity->callbacks->onDestroy = OnDestroy;
    activity->callbacks->onStart = OnStart;
    activity->callbacks->onResume = OnResume;
    activity->callbacks->onSaveInstanceState = OnSaveInstanceState;
    activity->callbacks->onPause = OnPause;
    activity->callbacks->onStop = OnStop;
    activity->callbacks->onConfigurationChanged = OnConfigurationChanged;
    activity->callbacks->onLowMemory = OnLowMemory;
    activity->callbacks->onWindowFocusChanged = OnWindowFocusChanged;
    activity->callbacks->onNativeWindowCreated = OnNativeWindowCreated;
    activity->callbacks->onNativeWindowDestroyed = OnNativeWindowDestroyed;
    activity->callbacks->onInputQueueCreated = OnInputQueueCreated;
    activity->callbacks->onInputQueueDestroyed = OnInputQueueDestroyed;

    g_androidApp = new AndroidApp{};
    g_androidApp->activity = activity;

    pthread_mutex_init(&g_androidApp->mutex, nullptr);
    pthread_cond_init(&g_androidApp->cond, nullptr);

    int msgpipe[2];
    if (::pipe(msgpipe))
    {
        LOGE("could not create pipe: %s", strerror(errno));
        return;
    }
    g_androidApp->msgread = msgpipe[0];
    g_androidApp->msgwrite = msgpipe[1];

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_create(&g_androidApp->thread, &attr, BackgroundThreadEntry, g_androidApp);

    // Wait for thread to start.
    while (!g_androidApp->running);
}


#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "AndroidProject1.NativeActivity", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "AndroidProject1.NativeActivity", __VA_ARGS__))

/**
* Our saved state data.
*/
struct saved_state {
	float angle;
	int32_t x;
	int32_t y;
};

/**
* Shared state for our app.
*/
struct engine
{
	AndroidApp* app;

	int animating;
	EGLDisplay display;
	EGLSurface surface;
	EGLContext context;
	int32_t width;
	int32_t height;
	struct saved_state state;
};

/**
* Initialize an EGL context for the current display.
*/
static int engine_init_display(engine* engine) {
	// initialize OpenGL ES and EGL

	/*
	* Here specify the attributes of the desired configuration.
	* Below, we select an EGLConfig with at least 8 bits per color
	* component compatible with on-screen windows
	*/
	const EGLint attribs[] = {
		EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
		EGL_BLUE_SIZE, 8,
		EGL_GREEN_SIZE, 8,
		EGL_RED_SIZE, 8,
		EGL_NONE
	};
	EGLint w, h, format;
	EGLint numConfigs;
	EGLConfig config;
	EGLSurface surface;
	EGLContext context;

	EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

	eglInitialize(display, 0, 0);

	/* Here, the application chooses the configuration it desires. In this
	* sample, we have a very simplified selection process, where we pick
	* the first EGLConfig that matches our criteria */
	eglChooseConfig(display, attribs, &config, 1, &numConfigs);

	/* EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
	* guaranteed to be accepted by ANativeWindow_setBuffersGeometry().
	* As soon as we picked a EGLConfig, we can safely reconfigure the
	* ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID. */
	eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);

	ANativeWindow_setBuffersGeometry(engine->app->window, 0, 0, format);

	surface = eglCreateWindowSurface(display, config, engine->app->window, nullptr);
	context = eglCreateContext(display, config, nullptr, nullptr);

	if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE) {
		LOGW("Unable to eglMakeCurrent");
		return -1;
	}

	eglQuerySurface(display, surface, EGL_WIDTH, &w);
	eglQuerySurface(display, surface, EGL_HEIGHT, &h);

	engine->display = display;
	engine->context = context;
	engine->surface = surface;
	engine->width = w;
	engine->height = h;
	engine->state.angle = 0;

	// Initialize GL state.
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
	glEnable(GL_CULL_FACE);
	glShadeModel(GL_SMOOTH);
	glDisable(GL_DEPTH_TEST);

	return 0;
}

/**
* Just the current frame in the display.
*/
static void engine_draw_frame(engine* engine) {
	if (engine->display == nullptr) {
		// No display.
		return;
	}

	// Just fill the screen with a color.
	glClearColor(((float)engine->state.x) / engine->width, engine->state.angle,
		((float)engine->state.y) / engine->height, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	eglSwapBuffers(engine->display, engine->surface);
}

/**
* Tear down the EGL context currently associated with the display.
*/
static void engine_term_display(engine* engine) {
	if (engine->display != EGL_NO_DISPLAY) {
		eglMakeCurrent(engine->display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
		if (engine->context != EGL_NO_CONTEXT) {
			eglDestroyContext(engine->display, engine->context);
		}
		if (engine->surface != EGL_NO_SURFACE) {
			eglDestroySurface(engine->display, engine->surface);
		}
		eglTerminate(engine->display);
	}
	engine->animating = 0;
	engine->display = EGL_NO_DISPLAY;
	engine->context = EGL_NO_CONTEXT;
	engine->surface = EGL_NO_SURFACE;
}

/**
* Process the next input event.
*/
static int32_t OnHandleInput(AndroidApp* app, AInputEvent* event)
{
	if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION)
    {
		//app->state.x = AMotionEvent_getX(event, 0);
		//app->state.y = AMotionEvent_getY(event, 0);
		return 1;
	}
	return 0;
}

/**
* Process the next main command.
*/
static void OnHandleCommand(AndroidApp* app, int32_t cmd)
{
	switch (cmd)
    {
    case APP_CMD_INPUT_CHANGED:
        LOGV("APP_CMD_INPUT_CHANGED\n");
        pthread_mutex_lock(&app->mutex);
        if (app->inputQueue != nullptr)
        {
            AInputQueue_detachLooper(app->inputQueue);
        }
        app->inputQueue = app->pendingInputQueue;
        if (app->inputQueue != nullptr)
        {
            LOGV("Attaching input queue to looper");
            AInputQueue_attachLooper(app->inputQueue, app->looper, LOOPER_ID_INPUT, nullptr, &app->inputPollSource);
        }
        pthread_cond_broadcast(&app->cond);
        pthread_mutex_unlock(&app->mutex);
        break;

    case APP_CMD_INIT_WINDOW:
        LOGV("APP_CMD_INIT_WINDOW\n");
        pthread_mutex_lock(&app->mutex);
        app->window = app->pendingWindow;
        pthread_cond_broadcast(&app->cond);
        pthread_mutex_unlock(&app->mutex);

        // The window is being shown, get it ready.
        if (app->window != nullptr) {
            //engine_init_display(engine);
            //engine_draw_frame(engine);
        }
        break;

    case APP_CMD_TERM_WINDOW:
        LOGV("APP_CMD_TERM_WINDOW\n");
        pthread_cond_broadcast(&app->cond);

        pthread_mutex_lock(&app->mutex);
        app->window = nullptr;
        pthread_cond_broadcast(&app->cond);
        pthread_mutex_unlock(&app->mutex);

        // The window is being hidden or closed, clean it up.
        //engine_term_display(engine);
        break;

    case APP_CMD_RESUME:
        LOGV("activityState=%d\n", cmd);
        pthread_mutex_lock(&app->mutex);
        app->activityState = cmd;
        pthread_cond_broadcast(&app->cond);
        pthread_mutex_unlock(&app->mutex);

        FreeSavedState(app);
        break;

    case APP_CMD_START:
    case APP_CMD_PAUSE:
    case APP_CMD_STOP:
        LOGV("activityState=%d\n", cmd);
        pthread_mutex_lock(&app->mutex);
        app->activityState = cmd;
        pthread_cond_broadcast(&app->cond);
        pthread_mutex_unlock(&app->mutex);


        FreeSavedState(app);
        break;

    case APP_CMD_CONFIG_CHANGED:
        LOGV("APP_CMD_CONFIG_CHANGED\n");
        AConfiguration_fromAssetManager(app->config,
            app->activity->assetManager);
        print_cur_config(app);
        break;

    case APP_CMD_DESTROY:
        LOGV("APP_CMD_DESTROY\n");
        app->destroyRequested = 1;
        break;
	case APP_CMD_SAVE_STATE:
		// The system has asked us to save our current state.  Do so.
		/*app->savedState = malloc(sizeof(struct saved_state));
		*((struct saved_state*)app->savedState) = engine->state;
		app->savedStateSize = sizeof(struct saved_state);*/

        LOGV("APP_CMD_SAVE_STATE\n");
        pthread_mutex_lock(&app->mutex);
        app->stateSaved = 1;
        pthread_cond_broadcast(&app->cond);
        pthread_mutex_unlock(&app->mutex);
		break;

	case APP_CMD_GAINED_FOCUS:
		// When our app gains focus, we start monitoring the accelerometer.
		if (app->accelerometerSensor != nullptr) {
			ASensorEventQueue_enableSensor(app->sensorEventQueue,
                app->accelerometerSensor);
			// We'd like to get 60 events per second (in us).
			ASensorEventQueue_setEventRate(app->sensorEventQueue,
                app->accelerometerSensor, (1000L / 60) * 1000);
		}
		break;
	case APP_CMD_LOST_FOCUS:
		// When our app loses focus, we stop monitoring the accelerometer.
		// This is to avoid consuming battery while not being used.
		if (app->accelerometerSensor != nullptr) {
			ASensorEventQueue_disableSensor(app->sensorEventQueue,
                app->accelerometerSensor);
		}
		// Also stop animating.
		//engine->animating = 0;
		//engine_draw_frame(engine);
		break;
	}
}

/**
 * This is the main entry point of a native application that is using
 * android_native_app_glue.  It runs in its own thread, with its own
 * event loop for receiving input events and doing other things.
 */
void android_main(AndroidApp* app)
{
	engine engine;

	memset(&engine, 0, sizeof(engine));
	app->userData = &engine;
	app->onHandleCommand = OnHandleCommand;
	app->onHandleInput = OnHandleInput;
	engine.app = app;

	// Prepare to monitor accelerometer
    app->sensorManager = ASensorManager_getInstance();
	app->accelerometerSensor = ASensorManager_getDefaultSensor(app->sensorManager, ASENSOR_TYPE_ACCELEROMETER);
	app->sensorEventQueue = ASensorManager_createEventQueue(app->sensorManager, app->looper, LOOPER_ID_USER, nullptr, nullptr);

	if (app->savedState != nullptr)
    {
		// We are starting with a previous saved state; restore from it.
		engine.state = *(struct saved_state*)app->savedState;
	}

	engine.animating = 1;

	// loop waiting for stuff to do.
	while (true)
    {
		// Read all pending events.
		int ident;
		int events;
		struct android_poll_source* source;

		// If not animating, we will block forever waiting for events.
		// If animating, we loop until all events are read, then continue
		// to draw the next frame of animation.
		while ((ident = ALooper_pollAll(engine.animating ? 0 : -1, nullptr, &events, (void**)&source)) >= 0)
        {
			// Process this event.
			if (source != nullptr) {
				source->process(app, source);
			}

			// If a sensor has data, process it now.
			if (ident == LOOPER_ID_USER) {
				if (app->accelerometerSensor != nullptr) {
					ASensorEvent event;
					while (ASensorEventQueue_getEvents(app->sensorEventQueue,
						&event, 1) > 0) {
						LOGI("accelerometer: x=%f y=%f z=%f",
							event.acceleration.x, event.acceleration.y,
							event.acceleration.z);
					}
				}
			}

			// Check if we are exiting.
			if (app->destroyRequested != 0) {
				//engine_term_display(&engine);
				return;
			}
		}

		if (engine.animating) {
			// Done with events; draw next animation frame.
			engine.state.angle += .01f;
			if (engine.state.angle > 1) {
				engine.state.angle = 0;
			}

			// Drawing is throttled to the screen update rate, so there
			// is no need to do timing here.
			//engine_draw_frame(&engine);
		}
	}
}
