#include "OutputTest.h"
#include "TestMode.h"
#include <iostream>
#include <functional>
#include <chrono>
#include <random>
#include <string>

double OutputTest::output_test(TestMode test_mode, int sample_size) {
  std::vector<std::string> data;
  generate_print_data(data, sample_size);

  std::function<void(const std::vector<std::string> &)> test_function;
  switch (test_mode) {
    case PRINTF:
      test_function = printf_test;
      break;
    case COUT_SYNC_WITH_STDIO_TRUE:
      std::ios_base::sync_with_stdio(true);
      test_function = cout_test;
      break;
    case COUT_SYNC_WITH_STDIO_FALSE:
      std::ios_base::sync_with_stdio(false);
      test_function = cout_test;
      break;
    case COUT_SYNC_WITH_STDIO_FALSE_TIE_NULLPTR:
      std::ios_base::sync_with_stdio(false);
      std::cout.tie(nullptr);
      test_function = cout_test;
      break;
    default:
      return -1.;
  }

  auto start = std::chrono::system_clock::now();
  test_function(data);
  auto end = std::chrono::system_clock::now();
  std::chrono::duration<double> result = end - start;

  return result.count() * 1000;
}

void OutputTest::generate_print_data(std::vector<std::string> &data, int sample_size) {
  for (int i = 0; i < sample_size; i++) {
    data.push_back(generate_random_string(OUTPUT_STR_LENGTH));
  }
}

/**
 * string_length 만큼 A-Z로 구성된 random string을 반환한다.
 * @param string_length 생성 문자열 길이
 * @return 생성된 random string
 */
std::string OutputTest::generate_random_string(int string_length) {
  std::string random_string;
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_int_distribution<int> range('A', 'Z');
  for (int i = 0; i < string_length; ++i) {
    random_string.push_back(range(mt));
  }
  return random_string;
}

void OutputTest::printf_test(const std::vector<std::string> &data) {
  int data_size = data.size();
  for (int i = 0; i < data_size; i++) {
    printf("%s\n", data[i].c_str());
  }
}

void OutputTest::cout_test(const std::vector<std::string> &data) {
  int data_size = data.size();
  for (int i = 0; i < data_size; i++) {
    std::cout << data[i] << '\n';
  }
}
