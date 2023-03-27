#include "test_framework.h"

#include "my_clock.h"
#include "parse_data.h"
#include "response.h"

#include <algorithm>

using namespace std;

namespace my_clock {

namespace test {

void Tests() {
    TestRunner tr;
    RUN_TEST(tr, Constructor);
    RUN_TEST(tr, GetHour);
    RUN_TEST(tr, GetMinute);
    RUN_TEST(tr, GetSecond);
    RUN_TEST(tr, OpeartorPlusEqual);
    RUN_TEST(tr, OpeartorMinusEqual);
    RUN_TEST(tr, OperatorLess);
}

void Constructor() {
    {
        my_clock::Clock time;
        AssertEqual(time.GetHour(), 0, "Error setup defualt value hour");
        AssertEqual(time.GetMinute(), 0, "Error setup defualt value minute");
        AssertEqual(time.GetSecond(), 0, "Error setup defualt value second");
    }
    {
        my_clock::Clock time(10, 12, 5);
        AssertEqual(time.GetHour(), 10, "Error setup value hour");
        AssertEqual(time.GetMinute(), 12, "Error setup value minute");
        AssertEqual(time.GetSecond(), 5, "Error setup value second");
    }
}

void GetHour() {
    my_clock::Clock time;
    AssertEqual(time.GetHour(), 0, "Error get hour");
    time.GetHour() = 5;
    AssertEqual(time.GetHour(), 5, "Error set hour");
}

void GetMinute() {
    my_clock::Clock time;
    AssertEqual(time.GetMinute(), 0, "Error get minute");
    time.GetMinute() = 10;
    AssertEqual(time.GetMinute(), 10, "Error set minute");
}

void GetSecond() {
    my_clock::Clock time;
    AssertEqual(time.GetSecond(), 0, "Error get second");
    time.GetSecond() = 10;
    AssertEqual(time.GetSecond(), 10, "Error set second");

}

void OpeartorPlusEqual() {
    my_clock::Clock time(0, 0, 1);
    time += my_clock::Clock(0, 0, 59);
    AssertEqual(time, my_clock::Clock(0, 1, 0), "Error add time(0, 0, 1) with time(0, 0, 59)");
    time += my_clock::Clock(0, 59, 0);
    AssertEqual(time, my_clock::Clock(1, 0, 0), "Error add time(0, 1, 0) with time(0, 59, 0)");
    time += my_clock::Clock(2, 55, 35);
    AssertEqual(time, my_clock::Clock(3, 55, 35), "Error add time(1, 0, 0) with time(3, 55, 35)");
}

void OpeartorMinusEqual() {
    my_clock::Clock time(12, 0, 0);
    time -= my_clock::Clock(0, 0, 59);
    AssertEqual(time, my_clock::Clock(11, 59, 1), "Error sub time(12, 0, 0) with time(0, 0, 59)");
    time -= my_clock::Clock(1, 0, 0);
    AssertEqual(time, my_clock::Clock(10, 59, 1), "Error sub time(11, 59, 1) with time(1, 0, 0)");
    time -= my_clock::Clock(3, 59, 12);
    AssertEqual(time, my_clock::Clock(6, 59, 49), "Error sub time(10, 59, 1) with time(3, 59, 12)");
    time -= my_clock::Clock(1, 1, 1);
    AssertEqual(time, my_clock::Clock(5, 58, 48), "Error sub time(6, 59, 49) with time(1, 1, 1)");
}

void OperatorLess() {
    {
        my_clock::Clock lhs(0, 0, 59);
        my_clock::Clock rhs(0, 1, 0);
        Assert(lhs < rhs, "Error time(0, 0, 59) not less time(0, 1, 0)");
    }
    {
        my_clock::Clock lhs(0, 59, 59);
        my_clock::Clock rhs(1, 0, 0);
        Assert(lhs < rhs, "Error time(0, 59, 59) not less time(1, 0, 0)");
    }
    {
        my_clock::Clock lhs(2, 58, 58);
        my_clock::Clock rhs(2, 59, 58);
        Assert(lhs < rhs, "Error time(2, 58, 59) not less time(2, 58, 58)");
    }
    {
        my_clock::Clock lhs(2, 58, 58);
        my_clock::Clock rhs(3, 58, 58);
        Assert(lhs < rhs, "Error time(2, 58, 58) not less time(3, 58, 58)");
    }
}

} // namespace test

} // namespace my clock


namespace parse_data {

namespace test {

void Tests() {
    TestRunner tr;
    RUN_TEST(tr, ParseTime);
    RUN_TEST(tr, ParseLine);
    RUN_TEST(tr, ParseLines);
}

void ParseTime() {
    {
        string_view line = "00:17:26";
        my_clock::Clock time = parse_data::Time(line);
        AssertEqual(time.GetHour(), 0, "Error parse hour");
        AssertEqual(time.GetMinute(), 17, "Error parse minute");
        AssertEqual(time.GetSecond(), 26, "Error parse second");
    }
    {
        string_view line = "12:54:00";
        my_clock::Clock time = parse_data::Time(line);
        AssertEqual(time.GetHour(), 12, "Error parse hour");
        AssertEqual(time.GetMinute(), 54, "Error parse minute");
        AssertEqual(time.GetSecond(), 0, "Error parse second");
    }
    {
        string_view line = "12:00:55";
        my_clock::Clock time = parse_data::Time(line);
        AssertEqual(time.GetHour(), 12, "Error parse hour");
        AssertEqual(time.GetMinute(), 0, "Error parse minute");
        AssertEqual(time.GetSecond(), 55, "Error parse second");
    }
}

void ParseLine() {
    {
        string_view line = "\"2014-09-01 00:17:26\",3907574550806754,0";
        Data data = parse_data::Line(line);
        AssertEqual(data, Data{my_clock::Clock(0, 17, 26), 3907574550806754, 0}, "Error parse data \"2014-09-01 00:17:26\",3907574550806754,0");
    }
    {
        string_view line = "\"2014-09-01 02:18:42\",3907574550780629,0";
        Data data = parse_data::Line(line);
        AssertEqual(data, Data{my_clock::Clock(2, 18, 42), 3907574550780629, 0}, "Error parse data \"2014-09-01 02:18:42\",3907574550780629,0");
    }
}

void ParseLines() {
    vector<string> lines = {{"\"2014-09-01 00:17:26\",3907574550806754,0"},
                            {"\"2014-09-01 02:18:42\",3907574550780629,0"},
                            {"\"2014-09-01 02:39:16\",3907574550780629,25"}};
    vector<Data> result;
    mutex result_mutex;
    parse_data::Lines(result, std::move(lines), result_mutex);
    vector<Data> ans = {{my_clock::Clock(0, 17, 26), 3907574550806754, 0},
                        {my_clock::Clock(2, 18, 42), 3907574550780629, 0},
                        {my_clock::Clock(2, 39, 16), 3907574550780629, 25}};
    AssertEqual(result, ans, "Error parse lines from 3 line");
}

} // namespace test

} // namespace parse data


namespace response {

namespace test {

void Tests() {
    TestRunner tr;
    RUN_TEST(tr, CSVFile);
}

void CSVFile() {
    {
        istringstream in("\"2014-09-01 00:17:26\",3907574550806754,0\n"
                         "\"2014-09-01 00:15:29\",3907574550780629,0\n"
                         "\"2014-09-01 00:25:45\",3907574550780629,0\n"
                         "\"2014-09-01 00:46:17\",3907574550780629,0\n"
                         "\"2014-09-01 01:17:05\",3907574550780629,0\n"
                         "\"2014-09-01 01:32:29\",3907574550780629,0\n"
                         "\"2014-09-01 01:47:54\",3907574550780629,0\n"
                         "\"2014-09-01 02:18:42\",3907574550780629,0\n"
                         "\"2014-09-01 02:39:16\",3907574550780629,0\n"
                         "\"2014-09-01 02:54:41\",3907574550780629,0\n"
                         "\"2014-09-01 03:04:39\",3907574550775536,0\n"
                         "\"2014-09-01 03:04:42\",3907574550775536,0\n"
                         "\"2014-09-01 03:11:31\",3907574550775536,0\n"
                         "\"2014-09-01 03:11:32\",3907574550775536,0\n"
                         "\"2014-09-01 03:11:33\",3907574550775536,0\n"
                         "\"2014-09-01 03:11:34\",3907574550775536,0\n"
                         "\"2014-09-01 03:11:35\",3907574550775536,0\n"
                         "\"2014-09-01 03:11:36\",3907574550775536,0\n"
                         "\"2014-09-01 03:11:37\",3907574550775536,0\n"
                         "\"2014-09-01 03:11:38\",3907574550775536,0\n"
                         "\"2014-09-01 03:11:39\",3907574550775536,0\n"
                         "\"2014-09-01 03:11:40\",3907574550775536,0\n"
                         "\"2014-09-01 03:11:41\",3907574550775536,0\n"
                         "\"2014-09-01 03:11:42\",3907574550775536,0\n"
                         "\"2014-09-01 03:11:43\",3907574550775536,0\n");
        std::vector<parse_data::Data> data = parse_data::CSVFile(in);
        sort(data.begin(), data.end(), [](const auto& lhs, const auto& rhs) {
            return lhs.time_ < rhs.time_;
        });
        auto result = response::CSVFile(data);
        string ans = "id: 3907574550775536\n"
                     "время в пути: 0.0h\n"
                     "время стоянки: 24.0h"
                     "\n-----\n"
                     "id: 3907574550780629\n"
                     "время в пути: 0.0h\n"
                     "время стоянки: 24.0h"
                     "\n-----\n"
                     "id: 3907574550806754\n"
                     "время в пути: 0.0h\n"
                     "время стоянки: 24.0h";
        AssertEqual(result, ans, "Error response all id parked");
    }
    {
        istringstream in("\"2014-09-01 00:15:00\",3907574550806754,10\n"
                         "\"2014-09-01 00:16:00\",3907574550806754,10\n"
                         "\"2014-09-01 00:17:00\",3907574550806754,10\n"
                         "\"2014-09-01 00:18:00\",3907574550806754,10\n"
                         "\"2014-09-01 00:19:00\",3907574550806754,10\n"
                         "\"2014-09-01 00:20:00\",3907574550806754,10\n"
                         "\"2014-09-01 00:21:00\",3907574550806754,10\n"
                         "\"2014-09-01 01:15:06\",3907574550780629,10\n"
                         "\"2014-09-01 01:16:45\",3907574550780629,10\n"
                         "\"2014-09-01 01:17:17\",3907574550780629,10\n"
                         "\"2014-09-01 01:18:05\",3907574550780629,10\n"
                         "\"2014-09-01 01:19:29\",3907574550780629,10\n"
                         "\"2014-09-01 01:20:54\",3907574550780629,10\n"
                         "\"2014-09-01 01:21:42\",3907574550780629,10\n"
                         "\"2014-09-01 01:22:16\",3907574550780629,10\n"
                         "\"2014-09-01 01:23:41\",3907574550780629,10\n"
                         "\"2014-09-01 01:24:41\",3907574550780629,10\n"
                         "\"2014-09-01 01:25:41\",3907574550780629,10\n"
                         "\"2014-09-01 01:26:41\",3907574550780629,10\n");
        std::vector<parse_data::Data> data = parse_data::CSVFile(in);
        sort(data.begin(), data.end(), [](const auto& lhs, const auto& rhs) {
            return lhs.time_ < rhs.time_;
        });
        auto result = response::CSVFile(data);
        string ans = "id: 3907574550780629\n"
                     "время в пути: 0.2h\n"
                     "время стоянки: 23.8h"
                     "\n-----\n"
                     "id: 3907574550806754\n"
                     "время в пути: 0.1h\n"
                     "время стоянки: 23.9h";
        AssertEqual(result, ans, "Error response some id in way");
    }
    {
        ostringstream query;
        my_clock::Clock time;
        while(time <= my_clock::end_day) {
            query << "\"2014-09-01 " << time << ",3907574550806754,10\n";
            query << "\"2014-09-01 " << time << ",3907574550780629,10\n";
            time += my_clock::minute;
        }
        istringstream in(query.str());
        std::vector<parse_data::Data> data = parse_data::CSVFile(in);
        sort(data.begin(), data.end(), [](const auto& lhs, const auto& rhs) {
            return lhs.time_ < rhs.time_;
        });
        auto result = response::CSVFile(data);
        string ans = "id: 3907574550780629\n"
                     "время в пути: 24.0h\n"
                     "время стоянки: 0.0h"
                     "\n-----\n"
                     "id: 3907574550806754\n"
                     "время в пути: 24.0h\n"
                     "время стоянки: 0.0h";
        AssertEqual(result, ans, "Error response all id in way");
    }
    {
        ostringstream query;
        my_clock::Clock time;
        while(time <= my_clock::Clock(12, 0, 0)) {
            query << "\"2014-09-01 " << time << ",3907574550806754,5\n";
            time += my_clock::minute;

        }
        while(time <= my_clock::end_day) {
            query << "\"2014-09-01 " << time << ",3907574550780629,10\n";
            time += my_clock::minute;
        }
        istringstream in(query.str());
        std::vector<parse_data::Data> data = parse_data::CSVFile(in);
        sort(data.begin(), data.end(), [](const auto& lhs, const auto& rhs) {
            return lhs.time_ < rhs.time_;
        });
        auto result = response::CSVFile(data);
        string ans = "id: 3907574550780629\n"
                     "время в пути: 12.0h\n"
                     "время стоянки: 12.0h"
                     "\n-----\n"
                     "id: 3907574550806754\n"
                     "время в пути: 12.0h\n"
                     "время стоянки: 12.0h";
        AssertEqual(result, ans, "Error response all id in way half a day");
    }
    {
        ostringstream query;
        my_clock::Clock time;
        while(time <= my_clock::Clock(3, 0, 0)) {
            query << "\"2014-09-01 " << time << ",3907574550806754,5\n";
            time += my_clock::minute;
        }
        time = my_clock::Clock(6, 0, 0);
        while(time <= my_clock::Clock(9, 0, 0)) {
            query << "\"2014-09-01 " << time << ",3907574550806754,5\n";
            time += my_clock::minute;
        }
        time = my_clock::Clock(15, 0, 0);
        while(time <= my_clock::Clock(18, 0, 0)) {
            query << "\"2014-09-01 " << time << ",3907574550806754,5\n";
            time += my_clock::minute;
        }
        istringstream in(query.str());
        std::vector<parse_data::Data> data = parse_data::CSVFile(in);
        sort(data.begin(), data.end(), [](const auto& lhs, const auto& rhs) {
            return lhs.time_ < rhs.time_;
        });
        auto result = response::CSVFile(data);
        string ans = "id: 3907574550806754\n"
                     "время в пути: 9.0h\n"
                     "время стоянки: 15.0h";
        AssertEqual(result, ans, "Error response in way 9 hour");
    }
    {
        ostringstream query;
        my_clock::Clock time;
        while(time <= my_clock::Clock(6, 0, 0)) {
            query << "\"2014-09-01 " << time << ",3907574550806754,5\n";
            query << "\"2014-09-01 " << time << ",3907574550780629,0\n";
            time += my_clock::minute;
        }
        time = my_clock::Clock(6, 0, 1);
        while(time <= my_clock::Clock(12, 0, 0)) {
            query << "\"2014-09-01 " << time << ",3907574550806754,0\n";
            query << "\"2014-09-01 " << time << ",3907574550780629,10\n";
            time += my_clock::minute;
        }
        time = my_clock::Clock(12, 0, 1);
        while(time <= my_clock::Clock(18, 0, 0)) {
            query << "\"2014-09-01 " << time << ",3907574550806754,5\n";
            query << "\"2014-09-01 " << time << ",3907574550780629,0\n";
            time += my_clock::minute;
        }
        time = my_clock::Clock(18, 0, 1);
        while(time <= my_clock::end_day) {
            query << "\"2014-09-01 " << time << ",3907574550806754,0\n";
            query << "\"2014-09-01 " << time << ",3907574550780629,15\n";
            time += my_clock::minute;
        }
        istringstream in(query.str());
        std::vector<parse_data::Data> data = parse_data::CSVFile(in);
        sort(data.begin(), data.end(), [](const auto& lhs, const auto& rhs) {
            return lhs.time_ < rhs.time_;
        });
        auto result = response::CSVFile(data);
        string ans = "id: 3907574550780629\n"
                     "время в пути: 12.0h\n"
                     "время стоянки: 12.0h"
                     "\n-----\n"
                     "id: 3907574550806754\n"
                     "время в пути: 12.0h\n"
                     "время стоянки: 12.0h";
        AssertEqual(result, ans, "Error response all id in way 9 hour");
    }
}

} // namespace test

} // namespace response

