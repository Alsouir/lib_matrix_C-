#pragma once

#include <exception>
#include <iostream>
#include <vector>

class S21Matrix {
 private:
  // Attributes
  int rows_, cols_;  // Rows and columns
  double** matrix_;  // Pointer to the memory where the matrix is allocated
  void CreateMatrix(int rows, int cols);

 public:
  // Default constructor
  S21Matrix();

  // Destructor
  ~S21Matrix();

  //������������������� ����������� � ����������� ����� � ��������.
  S21Matrix(int rows, int cols);

  //����������� �����������.
  S21Matrix(const S21Matrix& other);

  //����������� ��������.
  S21Matrix(S21Matrix&& other) noexcept;

  //���������� ������ ������� � �������
  void SumMatrix(const S21Matrix& other);

  //��������� ������� �� ��������� ����� �����.
  bool EqMatrix(const S21Matrix& other);

  //�������� �� ������� ������� ������
  void SubMatrix(const S21Matrix& other);

  //�������� ������� ������� �� �����.
  void MulNumber(const double num);

  //�������� ������� ������� �� ������.
  void MulMatrix(const S21Matrix& other);

  //������� ����� ����������������� ������� �� ������� � ���������� ��.
  S21Matrix Transpose();

  //��������� ������� �������������� ���������� ������� ������� � ���������� ��.
  S21Matrix CalcComplements();

  //��������� � ���������� ������������ ������� �������.
  double Determinant();

  //��������� � ���������� �������� �������.
  S21Matrix InverseMatrix();

  // * �������� �������� ���� ������
  S21Matrix operator+(const S21Matrix& other);

  // * �������� ��������� ����� ������� �� ������.
  S21Matrix operator-(const S21Matrix& other);

  // * �������� ��������� ������� �� �����.
  S21Matrix operator*(const double& num);

  // * �������� ��������� ������ .
  S21Matrix operator*(const S21Matrix& other);

  // * �������� �������� �� ��������� ������ (EqMatrix).
  bool operator==(const S21Matrix& other);

  // * �������� ���������� ������� �������� ������ �������.
  S21Matrix operator=(const S21Matrix& other);

  S21Matrix operator=(S21Matrix&& other) noexcept;

  // * �������� ���������� �������� (SumMatrix).
  S21Matrix operator+=(S21Matrix& other);

  // * �������� ���������� �������� (SubMatrix).
  S21Matrix operator-=(S21Matrix& other);

  // * �������� ���������� ��������� (MulMatrix/MulNumber).
  S21Matrix operator*=(S21Matrix& other);

  S21Matrix operator*=(double& number);

  // �������� ���������� �� ��������� ������� (������, �������).
  double& operator()(int i, int j);
  double& operator()(int i, int j) const;

  //�������������� �������

  int GetRows();
  int GetCols();
  double** GetMatrix();
  double GetNumberMatrix(int i, int j);
  void SetNumberMatrix(int i, int j, double result);
  void SetCols(const int cols);
  void SetRows(const int rows);
};

// void printMatrix(S21Matrix& matrix);
