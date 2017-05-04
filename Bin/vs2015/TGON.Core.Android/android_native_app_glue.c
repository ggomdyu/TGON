#include "android_native_app_glue.h"
/*
 * Copyright (C) 2010 The Android Open Source Project
 *
 * Apache 라이선스 2.0 버전(이하 "라이선스")에 따라 라이선스가 부여됩니다.
 * 라이선스를 준수하지 않으면 이 파일을 사용할 수 없습니다.
 * 라이선스의 사본은
 *
 *      http://www.apache.org/licenses/LICENSE-2.0에서 얻을 수 있습니다.
 *
 * 적용 가능한 법률에 따라 필요하거나 서면으로 동의하지 않는 이상
 * 라이선스에 따라 배포되는 소프트웨어는 "있는 그대로",
 * 명시적 또는 묵시적이든 어떠한 유형의 보증이나 조건 없이 배포됩니다.
 * 라이선스에 따른 특정 언어의 권한 및 제한에 대한 내용은
 * 라이선스를 참조하세요.
 *
*/

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "threaded_app", __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "threaded_app", __VA_ARGS__))

/* 디버그 빌드의 경우 이 라이브러리에서 항상 디버그 추적을 사용하도록 설정하세요.*/
#ifndef NDEBUG
#  define LOGV(...)  ((void)__android_log_print(ANDROID_LOG_VERBOSE, "threaded_app", __VA_ARGS__))
#else
#  define LOGV(...)  ((void)0)
#endif

static void free_saved_state(struct android_app* android_app) {
    pthread_mutex_lock(&android_app->mutex);
    if (android_app->savedState != NULL) {
        free(android_app->savedState);
        android_app->savedState = NULL;
        android_app->savedStateSize = 0;
    }
    pthread_mutex_unlock(&android_app->mutex);
}

int8_t android_app_read_cmd(struct android_app* android_app) {
    int8_t cmd;
    if (read(android_app->msgread, &cmd, sizeof(cmd)) == sizeof(cmd)) {
        switch (cmd) {
            case APP_CMD_SAVE_STATE:
                free_saved_state(android_app);
                break;
        }
        return cmd;
    } else {
        LOGE("No data on command pipe!");
    }
    return -1;
}

static void print_cur_config(struct android_app* android_app) {
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

void android_app_pre_exec_cmd(struct android_app* android_app, int8_t cmd) {
    switch (cmd) {
        case APP_CMD_INPUT_CHANGED:
            LOGV("APP_CMD_INPUT_CHANGED\n");
            pthread_mutex_lock(&android_app->mutex);
            if (android_app->inputQueue != NULL) {
                AInputQueue_detachLooper(android_app->inputQueue);
            }
            android_app->inputQueue = android_app->pendingInputQueue;
            if (android_app->inputQueue != NULL) {
                LOGV("Attaching input queue to looper");
                AInputQueue_attachLooper(android_app->inputQueue,
                        android_app->looper, LOOPER_ID_INPUT, NULL,
                        &android_app->inputPollSource);
            }
            pthread_cond_broadcast(&android_app->cond);
            pthread_mutex_unlock(&android_app->mutex);
            break;

        case APP_CMD_INIT_WINDOW:
            LOGV("APP_CMD_INIT_WINDOW\n");
            pthread_mutex_lock(&android_app->mutex);
            android_app->window = android_app->pendingWindow;
            pthread_cond_broadcast(&android_app->cond);
            pthread_mutex_unlock(&android_app->mutex);
            break;

        case APP_CMD_TERM_WINDOW:
            LOGV("APP_CMD_TERM_WINDOW\n");
            pthread_cond_broadcast(&android_app->cond);
            break;

        case APP_CMD_RESUME:
        case APP_CMD_START:
        case APP_CMD_PAUSE:
        case APP_CMD_STOP:
            LOGV("activityState=%d\n", cmd);
            pthread_mutex_lock(&android_app->mutex);
            android_app->activityState = cmd;
            pthread_cond_broadcast(&android_app->cond);
            pthread_mutex_unlock(&android_app->mutex);
            break;

        case APP_CMD_CONFIG_CHANGED:
            LOGV("APP_CMD_CONFIG_CHANGED\n");
            AConfiguration_fromAssetManager(android_app->config,
                    android_app->activity->assetManager);
            print_cur_config(android_app);
            break;

        case APP_CMD_DESTROY:
            LOGV("APP_CMD_DESTROY\n");
            android_app->destroyRequested = 1;
            break;
    }
}

void android_app_post_exec_cmd(struct android_app* android_app, int8_t cmd) {
    switch (cmd) {
        case APP_CMD_TERM_WINDOW:
            LOGV("APP_CMD_TERM_WINDOW\n");
            pthread_mutex_lock(&android_app->mutex);
            android_app->window = NULL;
            pthread_cond_broadcast(&android_app->cond);
            pthread_mutex_unlock(&android_app->mutex);
            break;

        case APP_CMD_SAVE_STATE:
            LOGV("APP_CMD_SAVE_STATE\n");
            pthread_mutex_lock(&android_app->mutex);
            android_app->stateSaved = 1;
            pthread_cond_broadcast(&android_app->cond);
            pthread_mutex_unlock(&android_app->mutex);
            break;

        case APP_CMD_RESUME:
            free_saved_state(android_app);
            break;
    }
}

static void android_app_destroy(struct android_app* android_app) {
    LOGV("android_app_destroy!");
    free_saved_state(android_app);
    pthread_mutex_lock(&android_app->mutex);
    if (android_app->inputQueue != NULL) {
        AInputQueue_detachLooper(android_app->inputQueue);
    }
    AConfiguration_delete(android_app->config);
    android_app->destroyed = 1;
    pthread_cond_broadcast(&android_app->cond);
    pthread_mutex_unlock(&android_app->mutex);
    // 이후에 android_app 개체를 터치할 수 없습니다.
}

static void process_input(struct android_app* app, struct android_poll_source* source) {
    AInputEvent* event = NULL;
    while (AInputQueue_getEvent(app->inputQueue, &event) >= 0) {
        LOGV("New input event: type=%d\n", AInputEvent_getType(event));
        if (AInputQueue_preDispatchEvent(app->inputQueue, event)) {
            continue;
        }
        int32_t handled = 0;
        if (app->onInputEvent != NULL) handled = app->onInputEvent(app, event);
        AInputQueue_finishEvent(app->inputQueue, event, handled);
    }
}

static void process_cmd(struct android_app* app, struct android_poll_source* source) {
    int8_t cmd = android_app_read_cmd(app);
    android_app_pre_exec_cmd(app, cmd);
    if (app->onAppCmd != NULL) app->onAppCmd(app, cmd);
    android_app_post_exec_cmd(app, cmd);
}

static void* android_app_entry(void* param) {
    struct android_app* android_app = (struct android_app*)param;

    android_app->config = AConfiguration_new();
    AConfiguration_fromAssetManager(android_app->config, android_app->activity->assetManager);

    print_cur_config(android_app);

    android_app->cmdPollSource.id = LOOPER_ID_MAIN;
    android_app->cmdPollSource.app = android_app;
    android_app->cmdPollSource.process = process_cmd;
    android_app->inputPollSource.id = LOOPER_ID_INPUT;
    android_app->inputPollSource.app = android_app;
    android_app->inputPollSource.process = process_input;

    ALooper* looper = ALooper_prepare(ALOOPER_PREPARE_ALLOW_NON_CALLBACKS);
    ALooper_addFd(looper, android_app->msgread, LOOPER_ID_MAIN, ALOOPER_EVENT_INPUT, NULL,
            &android_app->cmdPollSource);
    android_app->looper = looper;

    pthread_mutex_lock(&android_app->mutex);
    android_app->running = 1;
    pthread_cond_broadcast(&android_app->cond);
    pthread_mutex_unlock(&android_app->mutex);

    android_main(android_app);

    android_app_destroy(android_app);
    return NULL;
}

// --------------------------------------------------------------------
// Native Activity 상호 작용(주 스레드에서 호출됨)
// --------------------------------------------------------------------

static struct android_app* android_app_create(ANativeActivity* activity,
        void* savedState, size_t savedStateSize) {
    struct android_app* android_app = (struct android_app*)malloc(sizeof(struct android_app));
    memset(android_app, 0, sizeof(struct android_app));
    android_app->activity = activity;

    pthread_mutex_init(&android_app->mutex, NULL);
    pthread_cond_init(&android_app->cond, NULL);

    if (savedState != NULL) {
        android_app->savedState = malloc(savedStateSize);
        android_app->savedStateSize = savedStateSize;
        memcpy(android_app->savedState, savedState, savedStateSize);
    }

    int msgpipe[2];
    if (pipe(msgpipe)) {
        LOGE("could not create pipe: %s", strerror(errno));
        return NULL;
    }
    android_app->msgread = msgpipe[0];
    android_app->msgwrite = msgpipe[1];

    pthread_attr_t attr; 
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_create(&android_app->thread, &attr, android_app_entry, android_app);

    // 스레드 시작을 대기합니다.
    pthread_mutex_lock(&android_app->mutex);
    while (!android_app->running) {
        pthread_cond_wait(&android_app->cond, &android_app->mutex);
    }
    pthread_mutex_unlock(&android_app->mutex);

    return android_app;
}

static void android_app_write_cmd(struct android_app* android_app, int8_t cmd) {
    if (write(android_app->msgwrite, &cmd, sizeof(cmd)) != sizeof(cmd)) {
        LOGE("Failure writing android_app cmd: %s\n", strerror(errno));
    }
}

static void android_app_set_window(struct android_app* android_app, ANativeWindow* window) {
    pthread_mutex_lock(&android_app->mutex);
    if (android_app->pendingWindow != NULL) {
        android_app_write_cmd(android_app, APP_CMD_TERM_WINDOW);
    }
    android_app->pendingWindow = window;
    if (window != NULL) {
        android_app_write_cmd(android_app, APP_CMD_INIT_WINDOW);
    }
    while (android_app->window != android_app->pendingWindow) {
        pthread_cond_wait(&android_app->cond, &android_app->mutex);
    }
    pthread_mutex_unlock(&android_app->mutex);
}

void ANativeActivity_onCreate(ANativeActivity* activity, void* savedState, size_t savedStateSize)
{
    LOGV("Creating: %p\n", activity);
    activity->callbacks->onDestroy = AndroidApplication::OnDestroy;
    activity->callbacks->onStart = AndroidApplication::OnStart;
    activity->callbacks->onResume = AndroidApplication::OnResume;
    activity->callbacks->onSaveInstanceState = AndroidApplication::OnSaveInstanceState;
    activity->callbacks->onPause = AndroidApplication::OnPause;
    activity->callbacks->onStop = AndroidApplication::OnStop;
    activity->callbacks->onConfigurationChanged = AndroidApplication::OnConfigurationChanged;
    activity->callbacks->onLowMemory = AndroidApplication::OnLowMemory;
    activity->callbacks->onWindowFocusChanged = AndroidApplication::OnWindowFocusChanged;
    activity->callbacks->onNativeWindowCreated = AndroidApplication::OnNativeWindowCreated;
    activity->callbacks->onNativeWindowDestroyed = AndroidApplication::OnNativeWindowDestroyed;
    activity->callbacks->onInputQueueCreated = AndroidApplication::OnInputQueueCreated;
    activity->callbacks->onInputQueueDestroyed = AndroidApplication::OnInputQueueDestroyed;

    activity->instance = android_app_create(activity, savedState, savedStateSize);
}

void AndroidApplication::SetActivityState(android_app* android_app, int8_t cmd)
{
    pthread_mutex_lock(&android_app->mutex);
    {
        android_app_write_cmd(android_app, cmd);
        while (android_app->activityState != cmd)
        {
            pthread_cond_wait(&android_app->cond, &android_app->mutex);
        }
    }
    pthread_mutex_unlock(&android_app->mutex);
}

void AndroidApplication::SetInputQueue(struct android_app* android_app, AInputQueue* inputQueue)
{
    pthread_mutex_lock(&android_app->mutex);
    {
        android_app->pendingInputQueue = inputQueue;
        android_app_write_cmd(android_app, APP_CMD_INPUT_CHANGED);
        while (android_app->inputQueue != android_app->pendingInputQueue)
        {
            pthread_cond_wait(&android_app->cond, &android_app->mutex);
        }
    }
    pthread_mutex_unlock(&android_app->mutex);
}

void AndroidApplication::OnStart(ANativeActivity* activity)
{
    LOGV("Start: %p\n", activity);
    AndroidApplication::SetActivityState((struct android_app*)activity->instance, APP_CMD_START);
}

void AndroidApplication::OnResume(ANativeActivity* activity)
{
    LOGV("Resume: %p\n", activity);
    AndroidApplication::SetActivityState((struct android_app*)activity->instance, APP_CMD_RESUME);
}

void* AndroidApplication::OnSaveInstanceState(ANativeActivity* activity, size_t* outLen)
{
    android_app* app = (android_app*)activity->instance;
    void* savedState = NULL;

    LOGV("SaveInstanceState: %p\n", activity);
    pthread_mutex_lock(&app->mutex);
    {
        app->stateSaved = 0;
        android_app_write_cmd(app, APP_CMD_SAVE_STATE);
        while (!app->stateSaved)
        {
            pthread_cond_wait(&app->cond, &app->mutex);
        }

        if (app->savedState != NULL)
        {
            savedState = app->savedState;
            *outLen = app->savedStateSize;
            app->savedState = NULL;
            app->savedStateSize = 0;
        }
    }
    pthread_mutex_unlock(&app->mutex);

    return savedState;
}

void AndroidApplication::OnDestroy(ANativeActivity* activity)
{
    LOGV("Destroy: %p\n", activity);

    android_app* appInstance = (android_app*)activity->instance;

    pthread_mutex_lock(&appInstance->mutex);
    {
        android_app_write_cmd(appInstance, APP_CMD_DESTROY);
        while (!appInstance->destroyed)
        {
            pthread_cond_wait(&appInstance->cond, &appInstance->mutex);
        }
    }
    
    pthread_mutex_unlock(&appInstance->mutex);

    close(appInstance->msgread);
    close(appInstance->msgwrite);
    pthread_cond_destroy(&appInstance->cond);
    pthread_mutex_destroy(&appInstance->mutex);
    free(appInstance);
}

void AndroidApplication::OnPause(ANativeActivity* activity)
{
    LOGV("Pause: %p\n", activity);
    AndroidApplication::SetActivityState((struct android_app*)activity->instance, APP_CMD_PAUSE);
}

void AndroidApplication::OnStop(ANativeActivity* activity)
{
    LOGV("Stop: %p\n", activity);
    AndroidApplication::SetActivityState((struct android_app*)activity->instance, APP_CMD_STOP);
}

void AndroidApplication::OnConfigurationChanged(ANativeActivity* activity)
{
    struct android_app* android_app = (struct android_app*)activity->instance;
    LOGV("ConfigurationChanged: %p\n", activity);
    android_app_write_cmd(android_app, APP_CMD_CONFIG_CHANGED);
}

void AndroidApplication::OnLowMemory(ANativeActivity* activity)
{
    struct android_app* android_app = (struct android_app*)activity->instance;
    LOGV("LowMemory: %p\n", activity);
    android_app_write_cmd(android_app, APP_CMD_LOW_MEMORY);
}

void AndroidApplication::OnWindowFocusChanged(ANativeActivity* activity, int focused)
{
    LOGV("WindowFocusChanged: %p -- %d\n", activity, focused);
    android_app_write_cmd((struct android_app*)activity->instance, focused ? APP_CMD_GAINED_FOCUS : APP_CMD_LOST_FOCUS);
}

void AndroidApplication::OnNativeWindowCreated(ANativeActivity* activity, ANativeWindow* window)
{
    LOGV("NativeWindowCreated: %p -- %p\n", activity, window);
    android_app_set_window((struct android_app*)activity->instance, window);
}

void AndroidApplication::OnNativeWindowDestroyed(ANativeActivity* activity, ANativeWindow* window)
{
    LOGV("NativeWindowDestroyed: %p -- %p\n", activity, window);
    android_app_set_window((struct android_app*)activity->instance, NULL);
}

void AndroidApplication::OnInputQueueCreated(ANativeActivity* activity, AInputQueue* queue)
{
    LOGV("InputQueueCreated: %p -- %p\n", activity, queue);
    SetInputQueue((struct android_app*)activity->instance, queue);
}

void AndroidApplication::OnInputQueueDestroyed(ANativeActivity* activity, AInputQueue* queue)
{
    LOGV("InputQueueDestroyed: %p -- %p\n", activity, queue);
    SetInputQueue((struct android_app*)activity->instance, NULL);
}
