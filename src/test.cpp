#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

void printMatrix(S21Matrix& matrix) {
  for (size_t i = 0; i < (size_t)matrix.GetRows(); ++i) {
    for (size_t j = 0; j < (size_t)matrix.GetCols(); ++j) {
      std::cout << matrix.GetNumberMatrix(i, j) << ' ';
    }
    std::cout << std::endl;
  }
}

// S21Matrix matrix1(3, 3);
// matrix1.SetNumberMatrix(0, 0, 1);
// matrix1.SetNumberMatrix(0, 1, 2);
// matrix1.SetNumberMatrix(0, 2, 3);
// matrix1.SetNumberMatrix(1, 0, 0);
// matrix1.SetNumberMatrix(1, 1, 4);
// matrix1.SetNumberMatrix(1, 2, 2);
// matrix1.SetNumberMatrix(2, 0, 5);
// matrix1.SetNumberMatrix(2, 1, 2);
// matrix1.SetNumberMatrix(2, 2, 1);
// S21Matrix matrix2(3, 3);
// matrix2.SetNumberMatrix(0, 0, 1);
// matrix2.SetNumberMatrix(0, 1, 2);
// matrix2.SetNumberMatrix(0, 2, 3);
// matrix2.SetNumberMatrix(1, 0, 1);
// matrix2.SetNumberMatrix(1, 1, 2);
// matrix2.SetNumberMatrix(1, 2, 3);
// matrix2.SetNumberMatrix(2, 0, 1);
// matrix2.SetNumberMatrix(2, 1, 2);
// matrix2.SetNumberMatrix(2, 2, 3);
//
//  S21Matrix matrix4(0, 0);
//  S21Matrix matrix5(0, 0);
//  EXPECT_EQ(result, 1);
S21Matrix matrixForTest1() {
  S21Matrix matrix1(3, 3);
  matrix1.SetNumberMatrix(0, 0, 1);
  matrix1.SetNumberMatrix(0, 1, 2);
  matrix1.SetNumberMatrix(0, 2, 3);
  matrix1.SetNumberMatrix(1, 0, 0);
  matrix1.SetNumberMatrix(1, 1, 4);
  matrix1.SetNumberMatrix(1, 2, 2);
  matrix1.SetNumberMatrix(2, 0, 5);
  matrix1.SetNumberMatrix(2, 1, 2);
  matrix1.SetNumberMatrix(2, 2, 1);
  return matrix1;
}

S21Matrix matrixForTest2() {
  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 1.0;
  matrix2(0, 1) = 2.0;
  matrix2(1, 0) = 1.0;
  matrix2(1, 1) = 2.0;
  return matrix2;
}

TEST(s21_matrix, EqMatrix) {
  S21Matrix matrix1 = matrixForTest2();
  S21Matrix matrix2 = matrixForTest2();
  bool result = matrix1.EqMatrix(matrix2);
  EXPECT_EQ(result, 1);

  S21Matrix matrix3 = matrixForTest1();
  result = matrix1.EqMatrix(matrix3);
  EXPECT_EQ(result, 0);
}

TEST(s21_matrix, SumMatrix) {
  S21Matrix matrix1 = matrixForTest2();
  S21Matrix matrix2 = matrixForTest2();
  matrix1.SumMatrix(matrix2);
  EXPECT_EQ(matrix1(0, 0), 2);
  EXPECT_EQ(matrix1(0, 1), 4);
  EXPECT_EQ(matrix1(1, 0), 2);
  EXPECT_EQ(matrix1(1, 1), 4);

  S21Matrix matrix3 = matrixForTest1();
  EXPECT_THROW(matrix1.SumMatrix(matrix3), std::invalid_argument);
}

TEST(s21_matrix, SubMatrix) {
  S21Matrix matrix1 = matrixForTest2();
  S21Matrix matrix2 = matrixForTest2();
  matrix1.SubMatrix(matrix2);
  EXPECT_EQ(matrix1(0, 0), 0);
  EXPECT_EQ(matrix1(0, 1), 0);
  EXPECT_EQ(matrix1(1, 0), 0);
  EXPECT_EQ(matrix1(1, 1), 0);

  S21Matrix matrix3 = matrixForTest1();
  EXPECT_THROW(matrix1.SubMatrix(matrix3), std::invalid_argument);
}

TEST(s21_matrix, MulNumber) {
  S21Matrix matrix1 = matrixForTest2();
  matrix1.MulNumber(2);
  EXPECT_EQ(matrix1(0, 0), 2);
  EXPECT_EQ(matrix1(0, 1), 4);
  EXPECT_EQ(matrix1(1, 0), 2);
  EXPECT_EQ(matrix1(1, 1), 4);
}

TEST(s21_matrix, MulMatrix) {
  S21Matrix matrix1(2, 3);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(0, 2) = 3.0;
  matrix1(1, 0) = 4.0;
  matrix1(1, 1) = 5.0;
  matrix1(1, 2) = 6.0;
  S21Matrix matrix2(3, 2);
  matrix2(0, 0) = 7.0;
  matrix2(0, 1) = 8.0;
  matrix2(1, 0) = 9.0;
  matrix2(1, 1) = 10.0;
  matrix2(2, 0) = 11.0;
  matrix2(2, 1) = 12.0;

  matrix1.MulMatrix(matrix2);
  EXPECT_EQ(matrix1(0, 0), 58.0);
  EXPECT_EQ(matrix1(0, 1), 64.0);
  EXPECT_EQ(matrix1(1, 0), 139.0);
  EXPECT_EQ(matrix1(1, 1), 154.0);

  S21Matrix matrix3 = matrixForTest1();
  EXPECT_THROW(matrix1.MulMatrix(matrix3), std::invalid_argument);
}

TEST(s21_matrix, Transpose) {
  S21Matrix matrix1(2, 3);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(0, 2) = 3.0;
  matrix1(1, 0) = 4.0;
  matrix1(1, 1) = 5.0;
  matrix1(1, 2) = 6.0;

  S21Matrix result = matrix1.Transpose();

  EXPECT_EQ(result(0, 0), 1.0);
  EXPECT_EQ(result(0, 1), 4.0);
  EXPECT_EQ(result(1, 0), 2.0);
  EXPECT_EQ(result(1, 1), 5.0);
  EXPECT_EQ(result(2, 0), 3.0);
  EXPECT_EQ(result(2, 1), 6.0);
}

TEST(s21_matrix, CalcComplements) {
  S21Matrix matrix1(3, 3);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(0, 2) = 3.0;
  matrix1(1, 0) = 4.0;
  matrix1(1, 1) = 5.0;
  matrix1(1, 2) = 6.0;
  matrix1(2, 0) = 7.0;
  matrix1(2, 1) = 8.0;
  matrix1(2, 2) = 9.0;

  S21Matrix result = matrix1.CalcComplements();

  EXPECT_EQ(result(0, 0), -3.0);
  EXPECT_EQ(result(0, 1), 6.0);
  EXPECT_EQ(result(0, 2), -3.0);
  EXPECT_EQ(result(1, 0), 6.0);
  EXPECT_EQ(result(1, 1), -12.0);
  EXPECT_EQ(result(1, 2), 6.0);
  EXPECT_EQ(result(2, 0), -3.0);
  EXPECT_EQ(result(2, 1), 6.0);
  EXPECT_EQ(result(2, 2), -3.0);
  S21Matrix matrix2(2, 3);
  EXPECT_THROW(matrix2.CalcComplements(), std::invalid_argument);
}

TEST(s21_matrix, Determinant) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  EXPECT_DOUBLE_EQ(matrix1.Determinant(), -2.0);
  S21Matrix matrix2(2, 3);
  EXPECT_THROW(matrix2.CalcComplements(), std::invalid_argument);
}

TEST(s21_matrix, InverseMatrix) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  S21Matrix result = matrix1.InverseMatrix();

  EXPECT_EQ(result(0, 0), -2);
  EXPECT_EQ(result(0, 1), 1);
  EXPECT_EQ(result(1, 0), 1.5);
  EXPECT_EQ(result(1, 1), -0.5);

  S21Matrix matrix2(3, 3);
  matrix2(0, 0) = 1.0;
  matrix2(0, 1) = 2.0;
  matrix2(0, 2) = 3.0;
  matrix2(1, 0) = 4.0;
  matrix2(1, 1) = 5.0;
  matrix2(1, 2) = 6.0;
  matrix2(2, 0) = 7.0;
  matrix2(2, 1) = 8.0;
  matrix2(2, 2) = 9.0;

  EXPECT_THROW(matrix2.InverseMatrix(), std::invalid_argument);

  S21Matrix matrix3(2, 3);
  EXPECT_THROW(matrix3.InverseMatrix(), std::invalid_argument);
}

TEST(s21_matrix, SetColsAndSetRows) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  S21Matrix matrix2(3, 3);
  matrix2(0, 0) = 1.0;
  matrix2(0, 1) = 2.0;
  matrix2(0, 2) = 3.0;
  matrix2(1, 0) = 3.0;
  matrix2(1, 1) = 4.0;
  matrix2(1, 2) = 6.0;
  matrix2(2, 0) = 7.0;
  matrix2(2, 1) = 8.0;
  matrix2(2, 2) = 9.0;
  matrix2.SetCols(2);
  matrix2.SetRows(2);
  EXPECT_TRUE(matrix1 == matrix2);

  EXPECT_THROW(matrix2.SetRows(-2);, std::invalid_argument);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}