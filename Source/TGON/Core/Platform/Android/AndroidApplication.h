/**
 * filename AndroidApplication.h
 * author   ggomdyu
 * since    04/05/2017
 */

#pragma once
#include "../Generic/GenericApplication.h"

////#include "AndroidApplicationFwd.h"

#include <boost/config.hpp>
#include <boost/config/suffix.hpp>

namespace tgon
{

typedef GenericApplication<class AndroidApplication> TApplication;

class TGON_API AndroidApplication :
    public GenericApplication<AndroidApplication>
{
/** 
 * @section Ctor/Dtor
 */
public:
    AndroidApplication() = delete;
	~AndroidApplication() = delete;

/**
 * @section Public command methods
 */
public:
	/**
	 * @brief   Pull out the message from all queue and dispatch it.
	 * @return  False if there is no message to pull out
	 */
	static bool PumpMessage();

    static void free_saved_state(struct android_app* android_app)
    {
        pthread_mutex_lock(&android_app->mutex);
        if (android_app->savedState != NULL) {
            free(android_app->savedState);
            android_app->savedState = NULL;
            android_app->savedStateSize = 0;
        }
        pthread_mutex_unlock(&android_app->mutex);
    }


private:
};

} /* namespace tgon */