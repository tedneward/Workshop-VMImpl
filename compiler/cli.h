#ifndef _CLI_H_
#define _CLI_H_

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cerrno>
#include <string>
#include <vector>

struct Cli {
    std::string input;
    std::string output;

    void print_debug() {
        printf("Cli {\n");
        printf("\tinput: %s\n", this->input.c_str());
        printf("\toutput: %s\n", this->output.c_str());
        printf("}\n");
    }

    static void help() {
        printf("Usage: Cli [OPTIONS]\n"
        "\n"
        "Options:\n"
        "    -h, --help\n"
        "    -i, --input <INPUT>\n"
        "    -o, --output <OUTPUT>\n"
    );
    exit(0);
}

    static bool is_option(char* arg) {
        static const char* valid_options[] = {
            "-i",
            "--input",
            "-o",
            "--output",
        };

        for (size_t i = 0; i != 4; ++i) {
            if (strcmp(arg, valid_options[i]) == 0) {
                return true;
            }
        }

        return false;
    }

    static Cli parse (int argc, char *args[]) {
        --argc;
        ++args;

        const char* mandatory_field_names[] = { "input", "output", };
        bool mandatory_fields_seen[sizeof(mandatory_field_names)/sizeof(mandatory_field_names[0])] = { false };

        Cli res = {};
        for (int i = 0; i != argc; ++i, ++args) {
            char *arg = args[0];
            if (strcmp("-h", arg) == 0 || strcmp("--help", arg) == 0) {
                Cli::help();
            } else if (strcmp(arg, "-i") == 0 || strcmp(arg, "--input") == 0) {
                ++args;
                ++i;
                if (i == argc) {
                    printf("Expected value for option '%s' but no value was provided", arg);
                    exit(1);
                }
                std::string arg_res = args[0];
                res.input = arg_res;
                mandatory_fields_seen[0] = true;
            } else if (strcmp(arg, "-o") == 0 || strcmp(arg, "--output") == 0) {
                ++args;
                ++i;
                if (i == argc) {
                    printf("Expected value for option '%s' but no value was provided", arg);
                    exit(1);
                }
                std::string arg_res = args[0];
                res.output = arg_res;
                mandatory_fields_seen[1] = true;
            } else {
                printf("Unknown option '%s'\n", arg);
                exit(1);
            }
        }

        bool not_seen_any = false;
        for (size_t i = 0; i != sizeof(mandatory_field_names)/sizeof(mandatory_field_names[0]); ++i) {
            if (!mandatory_fields_seen[i]) {
                printf("--%s was required but it was not provided\n", mandatory_field_names[i]);
                not_seen_any = true;
            }
        }
        if (not_seen_any) {
            exit(1);
        }
        return res;
    }
};

#endif // _CLI_H_
