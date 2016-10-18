#pragma once

#include "EventDispatcher.h"
#include "Event.h"
#include "json/json.h"
#include <string>
#include <list>

using namespace std;
using namespace oxygine;

namespace adcolony
{

    void init();
    void free();
    enum AdcolonyStatus{
        ON_LOADED = 1,
        ON_FAILED = 2,
        ON_OPENED = 3,
        ON_EXPIRED = 4,
    }

    class OnChangeEvent : public Event
    {
    public:
        enum { EVENT = sysEventID('A', 'D', 'C')};
        OnChangeEvent(int status) : Event(EVENT), status(AdcolonyStatus(status)) {};
        AdcolonyStatus status = 0;
    };

    spEventDispatcher dispatcher();

    bool isLoaded();
    void load();
    void show();

    namespace internal
    {
        void onChange(int status);
    }
};