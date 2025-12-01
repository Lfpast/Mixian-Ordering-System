#include <iostream>
#include <string>

#include "SmartPtr.h"
#include "SmartPtr-impl.h"
#include "test.h"
#include "HashTable.h"
#include "GenerateSuite.h"
#include "interactive-main.h"
#include "CLI11.hpp"

using namespace std;

enum Mode {
    TEST = 0,
    MAIN,
    GENERATE,
    CANNOT_FIND
};

Mode convert(string mode) {
    std::transform(mode.begin(), mode.end(), mode.begin(), ::tolower);
    if (mode == "test") {
        return TEST;
    } else if (mode == "main") {
        return MAIN;
    } else if (mode == "generate") {
        return GENERATE;
    } else {
        return CANNOT_FIND;
    }
}

int main(int argc, char* argv[]) {
    CLI::App app("Tmajai Mixian Order System");
    string mode = "main";
    string path = "";
    std::pair<string,int> output_path_config = std::pair<string,int>("",0);
    int test_case = 0;
    app.add_option("--mode, -m", mode, "Choose the mode to run the program")->required()->default_str("main");
    CLI::Option* test_case_option = app.add_option("--testcase, -t", test_case, "Choose the test case to run the program");
    CLI::Option* path_option = app.add_option("--source, --src, -s", path, "Choose the source txt to run the program");
    CLI::Option* output_option = app.add_option("--output, -o", output_path_config, "Choose the output txt and number of record to store the generated result");
    path_option->check(CLI::ExistingFile);
    test_case_option = test_case_option->check(CLI::Range(1,24));
    output_option->check(CLI::NonexistentPath);
    
    CLI11_PARSE(app, argc, argv);
    if (convert(mode) == TEST) {
        TestSuite ts;
        ts.run(test_case);
    } else if (convert(mode) == MAIN) {
        if (path == "") {
            cout << "Please specify the source txt" << endl;
            return 0;
        }
        InteractiveMain im = InteractiveMain(path);
        im.run();
    } else if (convert(mode) == GENERATE) {
        if (output_path_config.first == "") {
            cout << "Please specify the output txt" << endl;
            return 0;
        }
        if (output_path_config.second == 0) {
            cout << "Please specify the number of record to store" << endl;
            return 0;
        }

        ofstream output_file = ofstream(output_path_config.first);
        GenerateSuite::generateRandomData(output_file, output_path_config.second);
    } else {
        cout << "Invalid mode" << endl;
    }
}
