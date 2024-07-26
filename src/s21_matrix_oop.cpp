#include "s21_matrix_oop.h"

void S21Matrix::CreateMatrix(int rows, int cols) {
  rows_ = rows;
  cols_ = cols;
  matrix_ = new double*[rows];
  for (int i = 0; i < rows; i++) {
    matrix_[i] = new double[cols];
  }
}

// Default constructor
S21Matrix::S21Matrix() { CreateMatrix(1, 1); }

// Destructor
S21Matrix::~S21Matrix() {
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}

//������������������� ����������� � ����������� ����� � ��������.
S21Matrix::S21Matrix(int rows, int cols) {
  if (rows > 0 && cols > 0) {
    CreateMatrix(rows, cols);
  } else {
    throw std::out_of_range(
        "Invalid input: number of rows or columns must be greater than 0");
  }
}

//����������� �����������.
S21Matrix::S21Matrix(const S21Matrix& other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  CreateMatrix(other.rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

//����������� ��������.
S21Matrix::S21Matrix(S21Matrix&& other) noexcept {
  matrix_ = other.matrix_;
  rows_ = other.rows_;
  cols_ = other.cols_;
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

//���������� ������ ������� � �������
void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Matrices have different sizes");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix_[i][j] + other.matrix_[i][j];
    }
  }
}

//��������� ������� �� ��������� ����� �����.
bool S21Matrix::EqMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    return false;
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (matrix_[i][j] != other.matrix_[i][j]) {
        return false;
      }
    }
  }
  return true;
}

//�������� �� ������� ������� ������
void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Matrices have different sizes");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix_[i][j] - other.matrix_[i][j];
    }
  }
}

//�������� ������� ������� �� �����.
void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix_[i][j] * num;
    }
  }
}

//�������� ������� ������� �� ������.
void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::invalid_argument("Invalid matrix sizes for multiplication");
  }
  S21Matrix resultMul(rows_, other.cols_);
  double sum_ij;
  for (int i = 0; i < resultMul.rows_; i++) {
    for (int j = 0; j < resultMul.cols_; j++) {
      sum_ij = 0;
      for (int k = 0; k < other.rows_; k++) {
        sum_ij = sum_ij + matrix_[i][k] * other.matrix_[k][j];
      }
      resultMul.matrix_[i][j] = sum_ij;
    }
  }
  *this = resultMul;
}

//������� ����� ����������������� ������� �� ������� � ���������� ��.
S21Matrix S21Matrix::Transpose() {
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result.matrix_[j][i] = matrix_[i][j];
    }
  }
  return result;
}

//��������� ������� �������������� ���������� ������� ������� � ���������� ��.
S21Matrix S21Matrix::CalcComplements() {
  if (cols_ != rows_) {
    throw std::invalid_argument("Invalid matrix size");
  }
  S21Matrix result(cols_, rows_);
  int rows_minor = 0;
  int columns_minor = 0;
  double minor_determinant = 0;
  S21Matrix minor;
  int sing = 1;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if ((i + j) % 2 == 0) {
        sing = 1;
      } else {
        sing = -1;
      }
      S21Matrix minor(cols_ - 1, rows_ - 1);
      rows_minor = 0;
      for (int k = 0; k < cols_; k++) {
        if (k == i) continue;
        columns_minor = 0;
        for (int t = 0; t < cols_; t++) {
          if (t == j) continue;
          minor.matrix_[rows_minor][columns_minor] = matrix_[k][t];
          columns_minor++;
        }
        rows_minor++;
      }
      minor_determinant = 0;
      minor_determinant = minor.Determinant();
      result.matrix_[i][j] =
          sing * minor_determinant;  // pow(-1, (i + j)) * minor_determinant;
    }
  }

  return result;
}

//��������� � ���������� ������������ ������� �������.
double S21Matrix::Determinant() {
  if (cols_ != rows_) {
    throw std::invalid_argument("Invalid matrix size");
  }
  double result = 0.0;
  if (cols_ == 1) {
    result = matrix_[0][0];
  } else if (cols_ == 2) {
    result = matrix_[1][1] * matrix_[0][0] - matrix_[1][0] * matrix_[0][1];
  } else {
    int sing = 1;
    for (int i = 0; i < rows_; i++) {
      S21Matrix auxiliary_matrix(cols_ - 1, rows_ - 1);
      int t = 0;
      for (int j = 1; j < rows_; j++) {
        int k = 0;
        for (int l = 0; l < rows_; l++) {
          if (l != i) {
            auxiliary_matrix.matrix_[t][k] = matrix_[j][l];
            k++;
          }
        }
        t++;
      }
      double result_auxiliary_matrix = auxiliary_matrix.Determinant();
      result += matrix_[0][i] * result_auxiliary_matrix * sing;
      sing = -sing;
    }
  }
  return result;
}

//��������� � ���������� �������� �������.
S21Matrix S21Matrix::InverseMatrix() {
  double determinant = Determinant();
  if (cols_ != rows_ || determinant == 0) {
    throw std::invalid_argument("Invalid matrix size");
  }
  S21Matrix result = CalcComplements().Transpose();
  determinant = 1 / determinant;
  result.MulNumber(determinant);

  return result;
}

// * �������� �������� ���� ������
S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  S21Matrix result(*this);
  result.SumMatrix(other);
  return result;
}

// * �������� ��������� ����� ������� �� ������.
S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  S21Matrix result(*this);
  result.SubMatrix(other);
  return result;
}

// * �������� ��������� ������� �� �����.
S21Matrix S21Matrix::operator*(const double& num) {
  S21Matrix result(*this);
  result.MulNumber(num);
  return result;
}

// * �������� ��������� ������ .
S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix result(*this);
  result.MulMatrix(other);
  return result;
}

// * �������� �������� �� ��������� ������ (EqMatrix).
bool S21Matrix::operator==(const S21Matrix& other) { return EqMatrix(other); }

// * �������� ���������� ������� �������� ������ �������.
S21Matrix S21Matrix::operator=(const S21Matrix& other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
  return *this;
}

S21Matrix S21Matrix::operator=(S21Matrix&& other) noexcept {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
  return *this;
}

// * �������� ���������� �������� (SumMatrix).
S21Matrix S21Matrix::operator+=(S21Matrix& other) {
  SumMatrix(other);
  return *this;
}

// * �������� ���������� �������� (SubMatrix).
S21Matrix S21Matrix::operator-=(S21Matrix& other) {
  SubMatrix(other);
  return *this;
}

// * �������� ���������� ��������� (MulMatrix/MulNumber).
S21Matrix S21Matrix::operator*=(S21Matrix& other) {
  MulMatrix(other);
  return *this;
}
S21Matrix S21Matrix::operator*=(double& number) {
  MulNumber(number);
  return *this;
}

// �������� ���������� �� ��������� ������� (������, �������).
double& S21Matrix::operator()(int i, int j) {
  if (i >= rows_ || j >= cols_ || i < 0 || j < 0) {
    throw std::length_error("Incorrect input, index is out of range");
  }
  return matrix_[i][j];
}

double& S21Matrix::operator()(int i, int j) const {
  if (i >= rows_ || j >= cols_ || i < 0 || j < 0) {
    throw std::length_error("Incorrect input, index is out of range");
  }
  return matrix_[i][j];
}
//�������������� �������

int S21Matrix::GetRows() { return rows_; }
int S21Matrix::GetCols() { return cols_; }
double** S21Matrix::GetMatrix() { return matrix_; }
double S21Matrix::GetNumberMatrix(int i, int j) { return matrix_[i][j]; }
void S21Matrix::SetNumberMatrix(int i, int j, double result) {
  matrix_[i][j] = result;
}

void S21Matrix::SetRows(const int rows) {
  if (rows < 1) {
    throw std::invalid_argument(
        "Incorrect input, matrices should have cols and rows");
  }
  S21Matrix result(rows, cols_);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (i < rows_) {
        result.matrix_[i][j] = matrix_[i][j];
      }
    }
  }
  *this = result;
}

void S21Matrix::SetCols(const int cols) {
  if (cols <= 0) {
    throw std::invalid_argument(
        "Incorrect input, matrices should have cols and rows");
  }
  S21Matrix result(rows_, cols);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols; ++j) {
      if (j < cols_) {
        result.matrix_[i][j] = matrix_[i][j];
      }
    }
  }
  *this = result;
}
