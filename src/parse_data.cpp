#include "parse_data.h"

#include <charconv>
#include <fstream>
#include <iostream>
#include <string_view>
#include <thread>

using namespace std;

namespace parse_data {

bool operator==(const Data& lhs, const Data& rhs) {
    return make_tuple(lhs.id_, lhs.speed_, lhs.time_) == make_tuple(rhs.id_, rhs.speed_, rhs.time_);
}

std::ostream& operator<<(std::ostream& os, const Data& data) {
    os << "time: " << data.time_ << ", ";
    os << "id: " << data.id_ << ", ";
    os << "speed: " << data.speed_ << ", ";
    return os;
}

my_clock::Clock Time(string_view line) {
    my_clock::Clock time;
    size_t pos_sep = line.find(':');
    string_view hour = line.substr(0, pos_sep);
    line.remove_prefix(pos_sep + 1);
    pos_sep = line.find(':');
    string_view minute = line.substr(0, pos_sep);
    line.remove_prefix(pos_sep + 1);
    string_view second = line;
    from_chars(hour.data(), hour.data() + hour.size(), time.GetHour());
    from_chars(minute.data(), minute.data() + minute.size(), time.GetMinute());
    from_chars(second.data(), second.data() + second.size(), time.GetSecond());
    return time;
}

Data Line(string_view line) {
    Data data;
    size_t pos_sep = line.find(',');
    my_clock::Clock time = Time(line.substr(12, 8));
    line.remove_prefix(pos_sep + 1);
    from_chars(line.data(), line.data() + line.size(), data.id_);
    pos_sep = line.find(',');
    line.remove_prefix(pos_sep + 1);
    from_chars(line.data(), line.data() + line.size(), data.speed_);
    data.time_ = time;
    return data;
}

void Lines(vector<Data>& result, vector<std::string>&& lines, mutex& result_mutex) {
    for (const auto& line : lines) {
        Data data = Line(line);
        typename std::vector<Data>::value_type* destination;
        {
            std::lock_guard guard(result_mutex);
             destination = &result.emplace_back();
        }
        *destination = std::move(data);
    }
}

std::vector<parse_data::Data> CSVFile(istream& input) {
    std::mutex result_mutex;
    std::vector<parse_data::Data> result;
    const size_t MAX_BATCH_SIZE = 5'000;
    std::vector<std::string> lines;
    lines.reserve(MAX_BATCH_SIZE);
    std::vector<std::thread> threads;
    std::string line;
    while(getline(input, line)) {
        lines.push_back(move(line));
        if (lines.size() >= MAX_BATCH_SIZE) {
            threads.push_back(std::thread(parse_data::Lines, ref(result), move(lines), ref(result_mutex)));
            lines.reserve(MAX_BATCH_SIZE);
        }
    }
    if (!lines.empty()) {
        threads.push_back(std::thread(parse_data::Lines, ref(result), move(lines), ref(result_mutex)));
    }
    for (auto& thread : threads) {
        thread.join();
    }
    return result;
}

} // namespace parse data

