#include "parse_data.h"
#include "response.h"

#include <algorithm>
#include <fstream>

using namespace std;

int main(int argc, char **argv)
{
    string file_input = "log.csv";
    string file_output = "ans.txt";
    if (argc > 1) {
        file_input = argv[1];
        file_output = argv[2];
    }
    ifstream input(file_input);
    if (!input.is_open()) {
        throw invalid_argument("file input is not opened");
    }

    ofstream output(file_output);
    if (!output.is_open()) {
        throw invalid_argument("file output is not opened");
    }
    auto lambda_sort = [](const parse_data::Data& lhs, const parse_data::Data& rhs) {
        return lhs.time_ < rhs.time_;
    };
    auto data = parse_data::CSVFile(input);
    sort(data.begin(), data.end(), lambda_sort);
    output << response::CSVFile(data);
    input.close();
    output.close();
    return 0;
}

