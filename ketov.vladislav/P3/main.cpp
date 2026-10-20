#include <iostream>
#include <fstream>

const int invalid_argument = 1;
const int invalid_data = 2;

int main(int argc, char * argv[]) {

  if (argc != 4) {
    std::cerr << "Not enough arguments\n";
    return invalid_argument;
  }

  std::string_view s = argv[1];
  for (char c:s) {
    if (c < '0' || c > '9') {
      std::cerr << "First parametr is not a number\n";
      return invalid_argument;
    }
  }

  if ((std::stoi(argv[1]) != 1) && (std::stoi(argv[1]) != 2)) {
    std::cerr << "First parametr is out of range\n";
    return invalid_argument;
  }

  std::ifstream fileIn(argv[2]);
  if (!fileIn) {
    std::cerr << "Can not open file\n";
    return invalid_data;
  }

  std::ofstream fileOut(argv[3]);
  if (!fileOut) {
    std::cerr << "Can not open file\n";
    return invalid_data;
  }

  int rows = 0;
  int cols = 0;

  if (std::stoi(argv[1]) == 1) {
    if (!(fileIn >> rows >> cols)) {
      std::cerr << "Not correct data\n";
      return invalid_data;
    }

    int arr[rows][cols];

    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        if (!(fileIn >> arr[i][j])) {
          std::cerr << "Not correct data\n";
          return invalid_data;
        }
      }
    }

    int addValue = 1;
    int allCount = rows * cols;
    int top = 0;
    int bottom = rows - 1;
    int left = 0;
    int right = cols - 1;
    while (addValue <= allCount) {
      for (int i = left; i <= right && addValue <= allCount; i++) {
        arr[bottom][i] += addValue;
        addValue++;
      }
      bottom--;

      for (int i = bottom; i >= top && addValue <= allCount; i--) {
        arr[i][right] += addValue;
        addValue++;
      }
      right--;

      for (int i = right; i >= left && addValue <= allCount; i--) {
        arr[top][i] += addValue;
        addValue++;
      }
      top++;

      for (int i = top; i <= bottom && addValue <= allCount; i++) {
        arr[i][left] += addValue;
        addValue++;
      }
      left++;
    }

    fileOut << rows << " " << cols << " ";
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        fileOut << arr[i][j] << " ";
      }
    }
  }





  if (std::stoi(argv[1]) == 2) {
    if (!(fileIn >> rows >> cols)) {
      std::cerr << "Not correct data\n";
      return invalid_data;
    }

    int ** arr = new int * [rows]{};

    try {
      for (int i = 0; i < rows; i++) {
        arr[i] = new int [cols]{};
      }
    }
    catch (...) {
      for (int i = 0; i < rows; i++) {
        delete[] arr[i];
      }
      delete[] arr;
      std::cerr << "no memory";
      return invalid_argument;
    }

    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        if (!(fileIn >> arr[i][j])) {
          std::cerr << "Not correct data\n";
          return invalid_data;
        }
      }
    }

    int addValue = 1;
    int allCount = rows * cols;
    int top = 0;
    int bottom = rows - 1;
    int left = 0;
    int right = cols - 1;
    while (addValue <= allCount) {
      for (int i = left; i <= right && addValue <= allCount; i++) {
        arr[bottom][i] += addValue;
        addValue++;
      }
      bottom--;

      for (int i = bottom; i >= top && addValue <= allCount; i--) {
        arr[i][right] += addValue;
        addValue++;
      }
      right--;

      for (int i = right; i >= left && addValue <= allCount; i--) {
        arr[top][i] += addValue;
        addValue++;
      }
      top++;

      for (int i = top; i <= bottom && addValue <= allCount; i++) {
        arr[i][left] += addValue;
        addValue++;
      }
      left++;
    }

    fileOut << rows << " " << cols << " ";
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        fileOut << arr[i][j] << " ";
      }
    }

    for (int i = 0; i < rows; i++) {
      delete[] arr[i];
    }
    delete[] arr;
  }

  fileIn.close();
  fileOut.close();
  return 0;
}
