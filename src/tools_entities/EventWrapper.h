#ifndef EVENT_WRAPPER_H
#define EVENT_WRAPPER_H

#include "tools.hpp"
#include "Event.h"
#include "stImage.h"
booba::Event* convertToStandartEvent(const stImage* space, const Event* event);

#endif // EVENT_WRAPPER_H