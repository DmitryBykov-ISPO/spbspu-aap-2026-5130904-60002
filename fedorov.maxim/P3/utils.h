#ifndef UTILS_H
#define UTILS_H

namespace utils {
  int min(int a, int b);
  int** allocate_matrix(int r, int c);
  void free_matrix(int** matrix, int r);
  int min_diag_sum(int* matrix, int r, int c);
  int min_diag_sum(int** matrix, int r, int c);
}

#endif
