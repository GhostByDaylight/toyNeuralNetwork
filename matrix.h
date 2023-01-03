#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <functional>
#include <type_traits>

class Matrix {
public:
  Matrix(int rows = 0, int cols = 0) {
    this->rows = rows;
    this->cols = cols;
    data.resize(rows);
    for (int i = 0; i < rows; i++) {
      data[i].resize(cols);
      for (int j = 0; j < cols; j++)
        data[i][j] = 0;
    }
  }

  void set(int row, int col, int value) { data[row][col] = value; }

  int get(int row, int col) { return data[row][col]; }


  //Matrix Display
  void disp() {
    for (int count = 0; count < this->rows; count++)
      std::cout << "________";
    std::cout << std::endl;
    for (int i = 0; i < this->rows; i++) {
      std::cout << "|";
      for (int j = 0; j < this->cols; j++)
        std::cout << data[i][j] << " ";
      std::cout << "|" << std::endl;
    }
    for (int count = 0; count < this->rows; count++)
      std::cout << "__";
    std::cout << std::endl;
  }

  void randomize() {

    // Create a random number generator
    std::mt19937 generator(std::random_device{}());

    // Create a distribution to generate random numbers in the range [0, 50]
    std::uniform_real_distribution<double> distribution(-1, 1);

    for (int i = 0; i < this->rows; i++) {
      for (int j = 0; j < this->cols; j++) {
        // Generate a random number
        double randomNumber = distribution(generator);
        data[i][j] = randomNumber;
      }
    }
  }



  //Matrix Add another matrix
  void add(Matrix m) {
    if (this->rows != m.rows || this->cols != m.cols) {
      std::cout << "Error: cannot add matrices of different sizes." << std::endl;
      return;
    }

    for (int i = 0; i < this->rows; i++) {
      for (int j = 0; j < this->cols; j++)
        data[i][j] += m.data[i][j];
    }
  }

  //Matrix add a single number
  void add(double n) {
    for (int i = 0; i < this->rows; i++) {
      for (int j = 0; j < this->cols; j++) {
        data[i][j] += n;
      }
    }
  }

  //Static method for matrix add
  static Matrix add(const Matrix &m1, const Matrix &m2) {
    // Check that the matrices have the same dimensions
    if (m1.rows != m2.rows || m1.cols != m2.cols) {
      throw std::invalid_argument(
          "Matrices must have the same dimensions to be added together");
    }

    // Create a new matrix to hold the result
    Matrix result(m1.rows, m1.cols);

    // Add the corresponding elements of the two matrices together
    for (int i = 0; i < m1.rows; i++) {
      for (int j = 0; j < m1.cols; j++) {
        result.data[i][j] = m1.data[i][j] + m2.data[i][j];
      }
    }

    // Return the result
    return result;
  }

  //Matrix Subtract
  void subtract(Matrix m) {
    if (this->rows != m.rows || this->cols != m.cols) {
      std::cout << "Error: cannot subtract matrices of different sizes." << std::endl;
      return;
    }

    for (int i = 0; i < this->rows; i++) {
      for (int j = 0; j < this->cols; j++)
        data[i][j] -= m.data[i][j];
    }
  }

  // Matrix subtract a single number
  void subtract(int n) {
    for (int i = 0; i < this->rows; i++) {
      for (int j = 0; j < this->cols; j++) {
        data[i][j] -= n;
      }
    }
  }

  // Static method for matrix add
  static Matrix subtract(const Matrix &m1, const Matrix &m2) {
    // Check that the matrices have the same dimensions
    if (m1.rows != m2.rows || m1.cols != m2.cols) {
      throw std::invalid_argument(
          "Matrices must have the same dimensions to be subtraced from one another");
    }

    // Create a new matrix to hold the result
    Matrix result(m1.rows, m1.cols);

    // Add the corresponding elements of the two matrices together
    for (int i = 0; i < m1.rows; i++) {
      for (int j = 0; j < m1.cols; j++) {
        result.data[i][j] = m1.data[i][j] - m2.data[i][j];
      }
    }

    // Return the result
    return result;
  }

  //Matrix Multiply
  void multiply(Matrix m) {
    if (this->rows != m.rows || this->cols != m.cols) {
      std::cerr << "Error: Matrices must have the same dimensions to compute the Hadamard product." << std::endl;
      return;
    }
    for (int i = 0; i < this->rows; i++) {
      for (int j = 0; j < this->cols; j++) {
        data[i][j] *= m.data[i][j];
      }
    }
  }

  // Matrix multiply a single number
  void multiply(int n) {
    for (int i = 0; i < this->rows; i++) {
      for (int j = 0; j < this->cols; j++) {
        data[i][j] *= n;
      }
    }
  }

  static Matrix multiply(const Matrix &matrix1, const Matrix &matrix2) {
    // Create a new matrix to store the result of the multiplication
    Matrix result(matrix1.rows, matrix2.cols);

    // Loop through the rows of the first matrix
    for (int row = 0; row < matrix1.rows; row++) {
      // Loop through the columns of the second matrix
      for (int col = 0; col < matrix2.cols; col++) {
        // Calculate the dot product of the row from the first matrix
        // and the column from the second matrix
        for (int i = 0; i < matrix1.cols; i++) {
          result.data[row][col] += matrix1.data[row][i] * matrix2.data[i][col];
        }
      }
    }
    // Return the result of the multiplication
    return result;
  }

  //Matrix Divide
  void divide(Matrix m) {
    if (this->rows != m.rows || this->cols != m.cols) {
      std::cout << "Error: cannot divide matrices of different sizes." << std::endl;
      return;
    }

    for (int i = 0; i < this->rows; i++) {
      for (int j = 0; j < this->cols; j++)
        data[i][j] /= m.data[i][j];
    }
  }

  // Matrix multiply a single number
  void divide(int n) {
    for (int i = 0; i < this->rows; i++) {
      for (int j = 0; j < this->cols; j++) {
        data[i][j] /= n;
      }
    }
  }

  static Matrix divide(const Matrix &m1, const Matrix &m2) {
    // Check that the matrices have the same size
    if (m1.rows != m2.rows || m1.cols != m2.cols) {
      throw std::invalid_argument(
          "Cannot divide matrices with different sizes");
    }

    // Create a new matrix to store the result
    Matrix result(m1.rows, m1.cols);

    // Divide each element of the first matrix by the corresponding element
    // of the second matrix and store the result in the new matrix
    for (int row = 0; row < m1.rows; row++) {
      for (int col = 0; col < m1.cols; col++) {
        result.data[row][col] = m1.data[row][col] / m2.data[row][col];
      }
    }

    return result;
  }

  void transpose() {
    std::vector<std::vector<double>> transposed(cols, std::vector<double>(rows));
    for (int i = 0; i < this->rows; i++) {
      for (int j = 0; j < this->cols; j++)
        transposed[j][i] = data[i][j];
    }
    data = transposed;
    std::swap(this->rows, this->cols);
  }

  static Matrix transpose(const Matrix &m) {
    Matrix result(m.cols, m.rows);
    for (int i = 0; i < m.rows; i++) {
      for (int j = 0; j < m.cols; j++) {
        result.data[j][i] = m.data[i][j];
      }
    }
    return result;
  }

  void map(std::function<double(double)> pFunc) {
    for (int i = 0; i < this->rows; i++) {
      for (int j = 0; j < this->cols; j++) {
        double val = data[i][j];
        data[i][j] = pFunc(val);
      }
    }
  }

  static Matrix map(Matrix m, std::function<double(double)> pFunc) {
    Matrix result = Matrix(m.rows, m.cols);
    for (int i = 0; i < m.rows; i++) {
      for (int j = 0; j < m.cols; j++) {
        double val = m.data[i][j];
        result.data[i][j] = pFunc(val);
      }
    }
    return result;
  }

  static Matrix fromArray(std::vector<double> arr) {
    
    Matrix m = Matrix(arr.size(), 1);
    for (int i = 0; i < arr.size(); i++) {
      m.data[i][0] = arr[i];
    }

    return m;
  }

  std::vector<double> toArray() {
    std::vector<double> arr;
    for (int i = 0; i < this->rows; i++) {
      for (int j = 0; j < this->cols; j++) {
        arr.push_back(data[i][j]);
      }
    }
    return arr;
  }


private:
  std::vector<std::vector<double>> data;
  int rows;
  int cols;
};