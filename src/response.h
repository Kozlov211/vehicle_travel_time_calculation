#pragma once

#include "parse_data.h"
#include "device_data.h"

#include <vector>
#include <set>
#include <string>

namespace response {

std::string CSVFile(const std::vector<parse_data::Data>& data);

std::string AnswerAsString(const std::set<device_data::DeviceData>& devices);

namespace test {

void Tests();

void CSVFile();

} // namespace test

} // namespace response

