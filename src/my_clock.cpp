#include "my_clock.h"
#include <tuple>
#include <cassert>

using namespace std;

namespace my_clock {

Clock::Clock(uint16_t hour, uint16_t minute, uint16_t second) : hour_(hour), minute_(minute), second_(second) {}

uint16_t Clock::GetHour() const {
    return hour_;
}

uint16_t Clock::GetMinute() const {
    return minute_;
}

uint16_t Clock::GetSecond() const {
    return second_;
}

uint16_t& Clock::GetHour() {
    return hour_;
}

uint16_t& Clock::GetMinute() {
    return minute_;
}

uint16_t& Clock::GetSecond() {
    return second_;
}

Clock& Clock::operator-=(const Clock& rhs) {
    assert(*this >= rhs);
    if (rhs.second_ > second_) {
        if (minute_ == 0) {
            --hour_;
            minute_ += 60;
        }
        --minute_;
        second_ += 60;
    }
    second_ -= rhs.second_;
    if (rhs.minute_ > minute_) {
        --hour_;
        minute_ += 60;
    }
    minute_ -= rhs.minute_;
    hour_ -= rhs.hour_;
    return *this;
}

Clock& Clock::operator+=(const Clock& rhs) {
    second_ += rhs.second_;
    if (second_ >= 60) {
        second_%= 60;
        ++minute_;
    }
    minute_ += rhs.minute_;
    if (minute_ >= 60) {
        minute_ %= 60;
        ++hour_;
    }
    hour_ += rhs.hour_;
    return *this;
}

Clock& Clock::operator++() {
    *(this) += second;
    return *this;
}

Clock Clock::operator++(int) {
    Clock tmp = *this;
    ++(*this);
    return tmp;
}

Clock operator+(const Clock& lhs, const Clock& rhs) {
    Clock copy_Clock = lhs;
    copy_Clock += rhs;
    return copy_Clock;
}

Clock operator-(const Clock& lhs, const Clock& rhs) {
    Clock copy_Clock = lhs;
    copy_Clock -= rhs;
    return copy_Clock;
}

bool operator<(const Clock& lhs, const Clock& rhs) {
    return make_tuple(lhs.GetHour(), lhs.GetMinute(), lhs.GetSecond()) < make_tuple(rhs.GetHour(), rhs.GetMinute(), rhs.GetSecond());
}

bool operator==(const Clock& lhs, const Clock& rhs) {
    return !(lhs < rhs || rhs < lhs);
}

bool operator!=(const Clock& lhs, const Clock& rhs) {
    return !(lhs == rhs);
}

bool operator>(const Clock& lhs, const Clock& rhs) {
    return rhs < lhs;
}

bool operator>=(const Clock& lhs, const Clock& rhs) {
    return lhs > rhs || lhs == rhs;
}

bool operator<=(const Clock& lhs, const Clock& rhs) {
    return lhs < rhs || lhs == rhs;
}

ostream& operator<<(ostream& os, const Clock& time) {
    if (time.GetHour() < 10) {
        os << "0";
    }
    os << time.GetHour() << ":";
    if (time.GetMinute() < 10) {
        os << "0";
    }
    os << time.GetMinute() << ":";
    if (time.GetSecond() < 10) {
        os << "0";
    }
    os << time.GetSecond();
    return os;
}

} // namespace my clock

