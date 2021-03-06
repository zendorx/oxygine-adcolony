#include "adcolony.h"

#ifdef __ANDROID__
    #include "android/AndroidAdcolony.h"
#elif __APPLE__
    #include <TargetConditionals.h>
    #include "ios/iosAdcolony.h"
#else
    #include "sim/AdcolonySimulator.h"
#endif



#define ADCOLONY_EXT_ENABLED 1

namespace adcolony
{

    spEventDispatcher _dispatcher;

    spEventDispatcher dispatcher()
    {
        return _dispatcher;
    }


	bool isLoaded()
	{
#if !ADCOLONY_EXT_ENABLED
		return false;
#endif

#ifdef __ANDROID__
		return jniAdcolonyIsLoaded();
#endif

		return false;
	}

	void load()
	{
#if !ADCOLONY_EXT_ENABLED
		return;
#endif

		log::messageln("adcolony::load");
#ifdef __ANDROID__
		jniAdcolonyLoad();
#endif
	}

	void show()
	{
#if !ADCOLONY_EXT_ENABLED
		return;
#endif
		
		log::messageln("adcolony::show");
#ifdef __ANDROID__
		jniAdcolonyShow();
#endif
	}

    void init()
    {
#if !ADCOLONY_EXT_ENABLED
        return;
#endif

        log::messageln("adcolony::init");
        OX_ASSERT(_dispatcher == 0);
        _dispatcher = new EventDispatcher;

#ifdef __ANDROID__
        jniAdcolonyInit();
#elif TARGET_OS_IPHONE

#else
        adcolonySimulatorInit();
#endif
        log::messageln("adcolony::init done");
    }

    void free()
    {
#if !ADCOLONY_EXT_ENABLED
        return;
#endif

        log::messageln("adcolony::free");

        OX_ASSERT(_dispatcher);

#ifdef __ANDROID__
        jniAdcolonyFree();
#endif
        _dispatcher->removeAllEventListeners();
        _dispatcher = 0;
        log::messageln("adcolony::free done");
    }


    namespace internal
    {
        void onChange(int status)
        {
            OnChangeEvent ev(status);
            _dispatcher->dispatchEvent(&ev);
        }
    }
}

