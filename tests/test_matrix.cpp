#include "matrix.h"

#include <gtest/gtest.h>

#include <stdexcept>
#include <string>

namespace {

void expect_matrix_value(const Matrix& matrix, int row, int col, double expected) {
    EXPECT_NEAR(matrix.data[row][col], expected, 1e-9);
}

} // namespace

TEST(MatrixTest, CreateMatrixInitializesElementsToZero) {
    Matrix matrix = create_matrix(2, 3);

    EXPECT_EQ(matrix.rows, 2);
    EXPECT_EQ(matrix.cols, 3);
    ASSERT_NE(matrix.data, nullptr);
    for (int row = 0; row < matrix.rows; ++row) {
        ASSERT_NE(matrix.data[row], nullptr);
        for (int col = 0; col < matrix.cols; ++col) {
            EXPECT_DOUBLE_EQ(matrix.data[row][col], 0.0);
        }
    }

    free_matrix(matrix);
}

TEST(MatrixTest, MatrixFromArrayPreservesRowMajorOrder) {
    double values[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    Matrix matrix = matrix_from_array(values, 2, 3);

    expect_matrix_value(matrix, 0, 0, 1.0);
    expect_matrix_value(matrix, 0, 2, 3.0);
    expect_matrix_value(matrix, 1, 0, 4.0);
    expect_matrix_value(matrix, 1, 2, 6.0);

    free_matrix(matrix);
}

TEST(MatrixTest, AdditionReturnsElementwiseSum) {
    double first_values[] = {1.0, 2.0, 3.0, 4.0};
    double second_values[] = {5.0, 6.0, 7.0, 8.0};
    Matrix first = matrix_from_array(first_values, 2, 2);
    Matrix second = matrix_from_array(second_values, 2, 2);

    Matrix result = matrix_add(first, second);

    expect_matrix_value(result, 0, 0, 6.0);
    expect_matrix_value(result, 0, 1, 8.0);
    expect_matrix_value(result, 1, 0, 10.0);
    expect_matrix_value(result, 1, 1, 12.0);

    free_matrix(result);
    free_matrix(second);
    free_matrix(first);
}

TEST(MatrixTest, MultiplicationReturnsMatrixProduct) {
    double first_values[] = {1.0, 2.0, 3.0, 4.0};
    double second_values[] = {5.0, 6.0, 7.0, 8.0};
    Matrix first = matrix_from_array(first_values, 2, 2);
    Matrix second = matrix_from_array(second_values, 2, 2);

    Matrix result = matrix_multiply(first, second);

    expect_matrix_value(result, 0, 0, 19.0);
    expect_matrix_value(result, 0, 1, 22.0);
    expect_matrix_value(result, 1, 0, 43.0);
    expect_matrix_value(result, 1, 1, 50.0);

    free_matrix(result);
    free_matrix(second);
    free_matrix(first);
}

TEST(MatrixTest, AddScalarReturnsIndependentResult) {
    double values[] = {1.0, 2.0, 3.0, 4.0};
    Matrix source = matrix_from_array(values, 2, 2);

    Matrix result = matrix_add_scalar(source, 2.5);

    expect_matrix_value(result, 0, 0, 3.5);
    expect_matrix_value(result, 1, 1, 6.5);
    expect_matrix_value(source, 0, 0, 1.0);

    free_matrix(result);
    free_matrix(source);
}

TEST(MatrixTest, InvalidDimensionsThrow) {
    EXPECT_THROW(create_matrix(0, 2), std::invalid_argument);
    EXPECT_THROW(create_matrix(2, -1), std::invalid_argument);
    EXPECT_THROW(matrix_from_array(nullptr, 1, 1), std::invalid_argument);
}

TEST(MatrixTest, IncompatibleOperationsThrow) {
    Matrix first = create_matrix(2, 2);
    Matrix second = create_matrix(3, 3);
    EXPECT_THROW(matrix_add(first, second), std::invalid_argument);
    free_matrix(second);
    free_matrix(first);

    Matrix left = create_matrix(2, 3);
    Matrix right = create_matrix(2, 2);
    EXPECT_THROW(matrix_multiply(left, right), std::invalid_argument);
    free_matrix(right);
    free_matrix(left);
}

TEST(MatrixTest, EmptyMatrixPrintsDefinedMessage) {
    testing::internal::CaptureStdout();
    print_matrix(Matrix{nullptr, 0, 0});
    const std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "[Empty matrix]\n");
}

TEST(MatrixTest, FreeEmptyMatrixIsSafe) {
    EXPECT_NO_THROW(free_matrix(Matrix{nullptr, 0, 0}));
}
