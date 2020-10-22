#include <iostream>
#include <cstdlib>
#include <cstring>
#include "OutputTest.h"
#include "TestMode.h"

enum {
  ERROR = -1, OUTPUT_TEST
};

static int sample_size;
static TestMode test_mode;

int parse_options(int argc, const char *argv[]);

void print_usage(const char *exe_name);

int main(int argc, const char *argv[]) {
  int mode = parse_options(argc, argv);

  switch (mode) {
    case OUTPUT_TEST: {
      double result = OutputTest::output_test(test_mode, sample_size);
      if (result == -1.) {
        std::cerr << "Test Error\n";
        return -1;
      }
      std::cout << "Test Result: " << result << " ms\n";
      break;
    }
    case ERROR:
    default:
      print_usage(argv[0]);
      return -1;
  }
  return 0;
}

int parse_options(int argc, const char *argv[]) {
  int i = 1;
  int result = OUTPUT_TEST;
  while (i < argc) {
    if (argv[i][0] != '-') {
      return ERROR;
    }
    size_t len = strlen(argv[i]);
    if (len != 2) {
      return ERROR;
    }
    switch (argv[i++][1]) {
      case 's':
        sample_size = atoi(argv[i++]);
        break;
      case 'm': {
        int parse_int = atoi(argv[i++]);
        if (parse_int < PRINTF || parse_int > COUT_SYNC_WITH_STDIO_FALSE_TIE_NULLPTR) {
          return ERROR;
        }
        test_mode = static_cast<TestMode>(parse_int);
        break;
      }
      default:
        return ERROR;
    }
  }
  if (!test_mode && sample_size == 0) {
    result = ERROR;
  }
  return result;
}

void print_usage(const char *exe_name) {
  std::cerr << "Usage: " << exe_name << " [OPTION]...\n"
                                        "\t-s sample size\tOutput Line Size\n"
                                        "\t-m MODE\t\tTest Mode\n"
                                        "\t\t\t1  printf\n"
                                        "\t\t\t2  cout, sync_with_stdio(true)\n"
                                        "\t\t\t3  cout, sync_with_stdio(false)\n"
                                        "\t\t\t4  cout, sync_with_stdio(false), cin.tie(nullptr)\n";
}
