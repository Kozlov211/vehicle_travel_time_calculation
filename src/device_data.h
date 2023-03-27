#pragma once

#include "my_clock.h"

#include <stdint.h>

namespace device_data {

class DeviceData {
public:
    DeviceData(size_t id);

    size_t GetId() const;

    my_clock::Clock& GetCurrentTime() const;

    my_clock::Clock& GetParkingTime() const;

    my_clock::Clock& GetCurrParkingTime() const;

private:
    mutable my_clock::Clock current_time_;
    mutable my_clock::Clock parking_time_;
    mutable my_clock::Clock curr_parking_time_;
    size_t id_;
};

bool operator<(const DeviceData& lhs, const DeviceData& rhs);

} // namespace device data

