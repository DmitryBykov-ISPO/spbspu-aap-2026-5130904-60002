#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include "utils.h"

int main(int argc, char* argv[])
{
  if (argc != 4 || (std::strcmp(argv[1], "1") && std::strcmp(argv[1], "2"))) {
    std::cerr << "Invalid args\n";
    return 1;
  }

  int mode = std::stoi(argv[1]);
  char* input_path = argv[2];
  char* output_path = argv[3];

  std::ifstream input(input_path);

  if (!input.is_open()) {
    std::cerr << "Input file cannot open\n";
    return 2;
  }

  int r = 0;
  int c = 0;
  input >> r >> c;
  if (r<=0 || c<=0) {
    std::cerr << "Invalid args\n";
    return 1;
  }

  int temp = 0;
  int res = 0;


  if (mode == 1) {
    int matrix[10000];
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        if (!(input >> temp)) {
          std::cerr << "Invalid matrix\n";
          return 2;
        }
        matrix[i * c + j] = temp;
      }
    }

    res = utils::min_diag_sum(matrix, r, c);
  }
  else {
    int ** matrix = utils::allocate_matrix(r, c);
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        if (!(input >> temp)) {
          std::cerr << "Invalid matrix\n";
          return 2;
        }
        matrix[i][j] = temp;
      }
    }

    res = utils::min_diag_sum(matrix, r, c);
    utils::free_matrix(matrix, r, c);
  }
  input.close();

  std::ofstream output(output_path);

  if (!output.is_open()) {
    std::cerr << "Output file cannot open\n";
    return 2;
  }

  output << res;

  output.close();

  return 0;
}
