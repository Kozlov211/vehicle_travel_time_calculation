#include "response.h"

#include <iomanip>
#include <set>
#include <sstream>
#include <string>
#include <stdint.h>
#include <vector>

using namespace std;

namespace response {

string CSVFile(const vector<parse_data::Data>& data) {
    set<device_data::DeviceData> devices;
    size_t current_id = data[0].id_;
    auto device = devices.emplace(current_id).first;
    for(const auto& value : data) {
        if (current_id != value.id_) {
            current_id = value.id_;
            device = devices.find(current_id);
            if (device == devices.end()) {
                device = devices.emplace(current_id).first;
            }
        }
        my_clock::Clock time_difference(value.time_ - device->GetCurrentTime());
        if (value.speed_ != 0) {
            if (time_difference > my_clock::stop_time) {
                device->GetParkingTime() += time_difference;
             }
        } else {
            device->GetParkingTime() += time_difference;
        }
        device->GetCurrentTime() = value.time_;
    }
    for(auto& device : devices) {
        my_clock::Clock time_difference(my_clock::end_day - device.GetCurrentTime());
        if (time_difference > my_clock::stop_time) {
            device.GetParkingTime() += time_difference;
        }
    }
    return AnswerAsString(devices);
}

string AnswerAsString(const set<device_data::DeviceData>& devices) {
    ostringstream os;
    bool is_first = true;
    for (const auto& device : devices) {
        if (is_first) {
            is_first = false;
        } else {
            os <<"\n-----\n";
        }
        double parking_time = device.GetParkingTime().GetHour();
        double hour = 60;
        double day = 24;
        parking_time += device.GetParkingTime().GetMinute() / hour;
        fixed(os);
        os << "id: " << device.GetId() << endl;
        os << "время в пути: " << setprecision(1)  <<  day - parking_time << "h\n";
        os << "время стоянки: " << parking_time << "h";
    }
    return os.str();
}

} // namespace response

