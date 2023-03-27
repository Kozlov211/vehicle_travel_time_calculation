#pragma once

#include <iostream>
#include <stdint.h>

namespace my_clock {

class Clock {
public:
    explicit Clock(uint16_t hour = 0, uint16_t minute = 0, uint16_t second = 0);

    uint16_t GetHour() const;

    uint16_t GetMinute() const;

    uint16_t GetSecond() const;

    uint16_t& GetHour();

    uint16_t& GetMinute();

    uint16_t& GetSecond();

    Clock& operator+=(const Clock& rhs);

    Clock& operator-=(const Clock& rhs);

    Clock& operator++();

    Clock operator++(int);

private:
    uint16_t hour_;
    uint16_t minute_;
    uint16_t second_;
};

static Clock stop_time(0, 2, 0);

static Clock end_day(23, 59, 59);

static Clock zero(0, 0, 0);

static Clock second(0, 0, 1);

static Clock minute(0, 1, 0);

static Clock hour(1, 0, 0);

Clock operator+(const Clock& lhs, const Clock& rhs);

Clock operator-(const Clock& lhs, const Clock& rhs);

bool operator<(const Clock& lhs, const Clock& rhs);

bool operator==(const Clock& lhs, const Clock& rhs);

bool operator!=(const Clock& lhs, const Clock& rhs);

bool operator>(const Clock& lhs, const Clock& rhs);

bool operator>=(const Clock& lhs, const Clock& rhs);

bool operator<=(const Clock& lhs, const Clock& rhs);

std::ostream& operator<<(std::ostream& os, const Clock& time);

namespace test {

void Tests();

void Constructor();

void GetHour();

void GetMinute();

void GetSecond();

void OpeartorPlusEqual();

void OpeartorMinusEqual();

void OperatorLess();

} // namespace test;

} // namespace my clock


