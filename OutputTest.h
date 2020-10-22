#ifndef OUTPUT_TEST__OUTPUTTEST_H_
#define OUTPUT_TEST__OUTPUTTEST_H_
#include "TestMode.h"
#include <string>
#include <vector>

class OutputTest {
 public:
  static double output_test(TestMode test_mode, int sample_size);
 private:
  static const int OUTPUT_STR_LENGTH = 32;
  static void generate_print_data(std::vector<std::string> &data, int sample_size);
  static std::string generate_random_string(int string_length);
  static void printf_test(const std::vector<std::string> &data);
  static void cout_test(const std::vector<std::string> &data);
};

#endif //OUTPUT_TEST__OUTPUTTEST_H_
