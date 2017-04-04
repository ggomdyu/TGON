//
// pch.h
// 표준 시스템 포함 파일의 헤더입니다.
//
// 빌드 시스템에서 미리 컴파일된 헤더를 생성할 때 사용합니다.
// pch.cpp가 필요하지 않으며, pch.h는 프로젝트의 일부인 모든 cpp 파일에
// 자동으로 포함됩니다.
//

#include <jni.h>
#include <errno.h>

#include <string.h>
#include <unistd.h>
#include <sys/resource.h>

#include <EGL/egl.h>
#include <GLES/gl.h>

#include <android/sensor.h>

#include <android/log.h>
#include "android_native_app_glue.h"
