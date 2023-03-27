#include "device_data.h"

namespace device_data {

DeviceData::DeviceData(size_t id) : id_(id) {}

my_clock::Clock& DeviceData::GetParkingTime() const {
    return parking_time_;
}

my_clock::Clock& DeviceData::GetCurrentTime() const {
    return current_time_;
}

my_clock::Clock& DeviceData::GetCurrParkingTime() const {
    return curr_parking_time_;
}

size_t DeviceData::GetId() const {
    return id_;
}

bool operator<(const DeviceData& lhs, const DeviceData& rhs) {
    return lhs.GetId() < rhs.GetId();
}

} // namespace device data

