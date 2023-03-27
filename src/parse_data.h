#pragma once

#include "my_clock.h"

#include <iostream>
#include <string_view>
#include <string>
#include <vector>
#include <mutex>

namespace parse_data {

struct Data {
    my_clock::Clock time_;
    size_t id_;
    uint16_t speed_;
};

bool operator==(const Data& lhs, const Data& rhs);

std::ostream& operator<<(std::ostream& os, const Data& data);

my_clock::Clock Time(std::string_view line);

Data Line(std::string_view line);

void Lines(std::vector<Data>& result, std::vector<std::string>&& lines, std::mutex& result_mutex);

std::vector<parse_data::Data> CSVFile(std::istream& input);

namespace test {

void Tests();

void ParseTime();

void ParseLine();

void ParseLines();

} // namespace tests

} // namespace parse data

