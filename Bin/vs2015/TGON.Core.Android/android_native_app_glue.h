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

#ifndef _ANDROID_NATIVE_APP_GLUE_H
#define _ANDROID_NATIVE_APP_GLUE_H

#include <poll.h>
#include <pthread.h>
#include <sched.h>

#include <android/configuration.h>
#include <android/looper.h>
#include <android/native_activity.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <android/native_activity.h>에서 제공하는 Native Activity 인터페이스는
 * 특정 이벤트가 발생할 때 활동의 주 스레드가 호출하는
 * 응용 프로그램 제공 콜백 집합을 기반으로 합니다.
 *
 * 이는 각각의 콜백 중 하나를 차단해서는 안 되고 
 * 시스템이 응용 프로그램을 강제로 종료하는 위험이 있음을 의미합니다.
 * 이 프로그래밍 모델은 직접적이고 가볍지만 제한적입니다.
 *
 * 'threaded_native_app' 정적 라이브러리는 응용 프로그램이 다른 스레드에서
 * 대신 주 이벤트 루프를 구현할 수 있는
 * 다른 실행 모델을 제공하는 데 사용됩니다. 사용 방법은 다음과 같습니다.
 *
 * 1/ 응용 프로그램은 "android_main()"이라는 함수를 제공해야 합니다.
 * 이 함수는 활동의 주 스레드로부터
 *  고유한 새 스레드에서 활동을 만들었을 때 호출됩니다.
 *
 * 2/ android_main()은 응용 프로그램이 실행되는
 * ANativeActivity 개체와 같이 다른 중요한 개체로의 참조를 포함하는
 * 유효한 "android_app" 구조에 대한 포인터를 받습니다.
 *
 * 3/ "android_app" 개체는 이미 중요한 두 가지를 수신하는
 * ALooper 인스턴스를 유지합니다.
 *
 * - 활동 수명 주기 이벤트(예: "일시 중지", "다시 시작"). 아래 APP_CMD_XXX
 * 선언을 참조하세요.
 *
 * - 활동에 첨부된 AInputQueue에서 오는 이벤트를 입력합니다.
 *
 * 각각 LOOPER_ID_MAIN 및 LOOPER_ID_INPUT 값을 가진
 * ALooper_pollOnce가 반환하는 ALooper 식별자에
 * 해당합니다.
 *
 * 응용 프로그램이 추가 파일 설명자를 수신하는 데 동일한 ALooper를
 * 사용할 수 있습니다. 콜백을 기반으로 하거나 LOOPER_ID_USER로 시작하는
 * 반환 식별자를 사용할 수 있습니다.
 *
 * 4/ LOOPER_ID_MAIN 또는 LOOPER_ID_INPUT 이벤트를 받을 때마다
 * 반환된 값은 android_poll_source 구조를 가리킵니다.
 * process() 함수를 호출하여 이벤트를 자체적으로 처리하기 위해 호출하는
 * android_app->onAppCmd 및 android_app->onInputEvent에
 * 채울 수 있습니다.
 *
 * 또한 데이터를 직접 읽고 처리하기 위해
 * 낮은 수준의 함수를 호출할 수 있습니다. 호출하는 방법에 대해 알아보려면
 * process_cmd() 및 process_input() 구현을 확인하세요.
 *
 * 전체 사용 예제는 NDK에 포함되어 있는 "native-activity"
 * 샘플을 참조하세요. 또한 NativeActivity의 JavaDoc도 참조하세요.
 */

struct android_app;

/**
 * 소스에 준비된 데이터가 있을 때 ALooper fd에 연결된 데이터는
 * "outData"로 반환됩니다.
 */
struct android_poll_source {
    // 이 소스의 식별자입니다. LOOPER_ID_MAIN 또는
    // LOOPER_ID_INPUT.
    int32_t id;

    // 이 android_app ID가 연결되어 있습니다.
    struct android_app* app;

    // 이 소스에서 데이터의 표준 처리를 수행하기 위해 호출되는
    // 함수입니다.
    void (*process)(struct android_app* app, struct android_poll_source* source);
};

/**
 * 스레드 응용 프로그램의 표준 붙이기 코드에 대한
 * 인터페이스입니다. 이 모델에서 응용 프로그램의 코드는
 * 프로세스의 주 스레드에서 분리된 자체 스레드에서 실행됩니다.
 * 스레드가 Java VM과 연결될 필요는 없지만
 * Java 개체를 호출하는 JNI를 만들려면 연결해야 할 수
 * 있습니다.
*/
struct android_app {
    // 응용 프로그램은 필요한 경우 여기에 상태 개체를 가리키는 포인터를
    // 배치할 수 있습니다.
    void* userData;

    // 주 앱 명령(APP_CMD_*)을 처리하는 함수로 채웁니다.
    void (*onAppCmd)(struct android_app* app, int32_t cmd);

    // 입력 이벤트를 처리하는 함수로 채웁니다. 여기서는
    // 이벤트가 이미 사전에 디스패치되었으며, 반환 시 종료됩니다.
    // 이벤트를 처리하면 1을 반환하고 기본 디스패치의 경우 0을
    // 반환합니다.
    int32_t (*onInputEvent)(struct android_app* app, AInputEvent* event);

    // 이 앱은 ANativeActivity 개체 인스턴스에서 실행됩니다.
    ANativeActivity* activity;

    // 앱은 현재 구성에서 실행됩니다.
    AConfiguration* config;

    // 생성 시 제공된 인스턴스의 마지막 저장 상태입니다.
    // 상태가 없으면 NULL이 되고, 필요한 경우 사용할 수 있습니다.
    // 메모리는 APP_CMD_RESUME에 대해 android_app_exec_cmd()를 호출할 때까지 남아있습니다.
    // 호출되면 메모리가 해제되고 savedState는 NULL로 설정됩니다.
    // 이 변수는 APP_CMD_SAVE_STATE를 처리할 때만 변경해야 합니다.
    // 이 때 NULL로 초기화되므로 상태를 malloc하여
    // 정보를 여기에 배치할 수 있습니다. 이런 경우 메모리는
    // 나중에 해제됩니다.
    void* savedState;
    size_t savedStateSize;

    // Alooper는 앱의 스레드와 연결됩니다.
    ALooper* looper;

    // NULL이 아닐 때 사용자 입력 이벤트를 받는 앱의
    // 입력 큐가 됩니다.
    AInputQueue* inputQueue;

    // NULL이 아닐 때 앱이 그릴 수 있는 창 표면이 됩니다.
    ANativeWindow* window;

    // 창의 현재 콘텐츠 사각형입니다. 이 곳은 사용자에게 표시되는
    // 창 콘텐츠를 배치해야 하는 영역입니다.
    ARect contentRect;

    // 앱 활동의 현재 상태입니다. APP_CMD_START,
    // APP_CMD_RESUME, APP_CMD_PAUSE 또는 APP_CMD_STOP이 될 수 있으며 자세한 내용은 아래를 참조하세요.
    int activityState;

    // 응용 프로그램의 NativeActivity가 제거되었거나
    // 앱 스레드가 완료되기를 기다리는 동안은 0이 아닙니다.
    int destroyRequested;

    // -------------------------------------------------
    // 아래는 붙이기 코드의 "private" 구현입니다.

    pthread_mutex_t mutex;
    pthread_cond_t cond;

    int msgread;
    int msgwrite;

    pthread_t thread;

    struct android_poll_source cmdPollSource;
    struct android_poll_source inputPollSource;

    int running;
    int stateSaved;
    int destroyed;
    int redrawNeeded;
    AInputQueue* pendingInputQueue;
    ANativeWindow* pendingWindow;
    ARect pendingContentRect;
};

enum {
    /**
     * 앱의 주 스레드에서 오는 명령의 Looper 데이터 ID로
     * ALooper_pollOnce()의 식별자로 반환됩니다. 이 식별자에
     * 대한 데이터는 android_poll_source 구조에 대한 포인터입니다.
     * android_app_read_cmd()
     * 및 android_app_exec_cmd()로 검색하고 처리할 수 있습니다.
     */
    LOOPER_ID_MAIN = 1,

    /**
     * 응용 프로그램 창의 AInputQueue에서 오는 이벤트의 Looper 데이터 ID로
     * ALooper_pollOnce()에서 식별자로 반환됩니다.
     * 이 식별자에 대한 데이터는
     * android_poll_source 구조의 포인터입니다. android_app용 inputQueue
     * 개체를 통해 읽을 수 있습니다.
     */
    LOOPER_ID_INPUT = 2,

    /**
     * 사용자 정의된 ALooper 식별자의 시작입니다.
     */
    LOOPER_ID_USER = 3,
};

enum {
    /**
     * 주 스레드의 명령: AInputQueue가 변경되었습니다. 이 명령을
     * 처리 시 android_app->inputQueue는 새 큐
     * (또는 NULL)로 업데이트됩니다.
     */
    APP_CMD_INPUT_CHANGED,

    /**
     * 주 스레드의 명령: 새 ANativeWindow를 사용할 수 있습니다.
     * 이 명령을 수신 시 android_app->window는 새 창
     * 표면을 포함합니다.
     */
    APP_CMD_INIT_WINDOW,

    /**
     * 주 스레드의 명령: 기존 ANativeWindow를 종료해야
     * 합니다. 이 명령을 수신 시 android_app->window는
     * 기존 창을 계속 포함합니다.
     * android_app_exec_cmd를 호출한 후 NULL로 설정됩니다.
     */
    APP_CMD_TERM_WINDOW,

    /**
     * 주 스레드의 명령: 현재 ANativeWindow 크기가 변경되었습니다.
     * 새 크기로 다시 그리세요.
     */
    APP_CMD_WINDOW_RESIZED,

    /**
     * 주 스레드의 명령: 시스템에서 현재 ANativeWindow를
     * 다시 그려야 합니다. 일시적인 그리기 결함을 피하려면 
     * android_app_exec_cmd()로 보내기 전에 창을 다시 그려야 합니다.
     */
    APP_CMD_WINDOW_REDRAW_NEEDED,

    /**
     * 주 스레드의 명령: 소프트 입력 창이 표시되거나 숨겨진 것과 같이
     * 창의 콘텐츠 영역이 변경되었습니다. android_app::contentRect에서
     * 새 콘텐츠 사각형을 찾을 수 있습니다.
     */
    APP_CMD_CONTENT_RECT_CHANGED,

    /**
     * 주 스레드의 명령: 앱의 활동 창에 입력 포커스가
     * 위치했습니다.
     */
    APP_CMD_GAINED_FOCUS,

    /**
     * 주 스레드의 명령: 앱의 활동 창에서 입력 포커스가
     * 사라졌습니다.
     */
    APP_CMD_LOST_FOCUS,

    /**
     * 주 스레드의 명령: 현재 장치 구성이 변경되었습니다.
     */
    APP_CMD_CONFIG_CHANGED,

    /**
     * 주 스레드의 명령: 시스템에서 사용할 수 있는 메모리가 부족합니다.
     * 메모리 사용을 줄이세요.
     */
    APP_CMD_LOW_MEMORY,

    /**
     * 주 스레드의 명령: 앱의 활동이 시작되었습니다.
     */
    APP_CMD_START,

    /**
     * 주 스레드의 명령: 앱의 활동이 다시 시작되었습니다.
     */
    APP_CMD_RESUME,

    /**
     * 주 스레드의 명령: 앱은 나중에 필요할 때 복원할 수 있도록 자체적으로
     * 새로운 저장 상태를 생성해야 합니다. 저장된 상태가 있으면
     * malloc으로 할당하고 android_app.savedStateSize의 크기로
     * android_app.savedState에 배치하세요. 나중에
     * 해제됩니다.
     */
    APP_CMD_SAVE_STATE,

    /**
     * 주 스레드의 명령: 앱의 활동이 일시 중지되었습니다.
     */
    APP_CMD_PAUSE,

    /**
     * 주 스레드의 명령: 앱의 활동이 중지되었습니다.
     */
    APP_CMD_STOP,

    /**
     * 주 스레드의 명령: 앱의 활동이 제거되어,
     * 계속 진행하기 전에 앱 스레드가 정리되기를 기다리고 있습니다.
     */
    APP_CMD_DESTROY,
};

/**
 * ALooper_pollAll()이 LOOPER_ID_MAIN을 반환할 때 호출하며 다음
 * 앱 명령 메시지를 읽습니다.
 */
int8_t android_app_read_cmd(struct android_app* android_app);

/**
 * 지정한 명령을 초기에 사전 처리하기 위해 android_app_read_cmd()가
 * 반환하는 명령으로 호출합니다. 이 함수를 호출한 후
 * 명령에 대한 작업을 수행할 수 있습니다.
 */
void android_app_pre_exec_cmd(struct android_app* android_app, int8_t cmd);

/**
 * 지정한 명령을 최종적으로 사후 처리하기 위해 android_app_read_cmd()가
 * 반환하는 명령을 호출합니다. 이 함수를 호출하기 전에
 * 명령에 대한 작업을 마쳐야 합니다.
 */
void android_app_post_exec_cmd(struct android_app* android_app, int8_t cmd);

/**
 * 응용 프로그램 코드가 구현해야 하는 함수이며
 * 앱에 대한 주 입력을 나타냅니다.
 */
extern void android_main(struct android_app* app);

#ifdef __cplusplus
}
#endif

#endif /* _ANDROID_NATIVE_APP_GLUE_H */
