#ifndef EVENT_HH
#define EVENT_HH

#include <cstdint>
#include <any>
#include <unordered_map>

namespace ecs {
    using EventId = uint32_t;
    using ParamId = uint32_t;

    class Event {
    private:
        EventId type;
        std::unordered_map<EventId, std::any> data;
    public:
        Event() = delete;
        explicit Event(EventId type) : type {type} {};

        EventId getType() const {
            return type;
        }

        template<typename T>
        void SetParam(EventId id, T value) {
            data[id] = value;
        }

        template<typename T>
        T GetParam(EventId id) {
            return std::any_cast<T>(data[id]);
        }

    };
}

#endif