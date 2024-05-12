#ifndef EVENTMANAGER_HH
#define EVENTMANAGER_HH

#include <unordered_map>
#include "types/Event.hpp"
#include <list>
#include <functional>


#include <bitset>
#include <cstdint>

namespace ecs {
    class EventManager {
    private:
        std::unordered_map<EventId, std::list<std::function<void(Event&)>>> listeners;
    public:
        void addListener(EventId id, std::function<void(Event&)> const& listener) {
            listeners[id].push_back(listener);
        }

        void sendEvent(Event& event) {
            uint32_t type = event.getType();

            for (auto const& listener : listeners[type]) {
                listener(event);
            }
        }

        void sendEvent(EventId eventId) {
            Event event(eventId);

            for (auto const& listener : listeners[eventId]) {
                listener(event);
            }
        }
    };
}

#endif