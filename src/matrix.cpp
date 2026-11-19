#include "matrix.h"

#include <iomanip>
#include <iostream>
#include <stdexcept>

namespace {

bool is_valid_matrix(const Matrix& matrix) {
    if (matrix.rows <= 0 || matrix.cols <= 0 || matrix.data == nullptr) {
        return false;
    }

    for (int row = 0; row < matrix.rows; ++row) {
        if (matrix.data[row] == nullptr) {
            return false;
        }
    }

    return true;
}

void check_valid_matrix(const Matrix& matrix) {
    if (!is_valid_matrix(matrix)) {
        throw std::invalid_argument("Matrix is not initialized");
    }
}

void check_same_size(const Matrix& first, const Matrix& second) {
    if (first.rows != second.rows || first.cols != second.cols) {
        throw std::invalid_argument("Matrix dimensions must match");
    }
}

} // namespace

Matrix create_matrix(int rows, int cols) {
    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument("Matrix dimensions must be positive integers");
    }

    Matrix matrix{nullptr, rows, cols};
    try {
        matrix.data = new double*[rows]{};
        for (int row = 0; row < rows; ++row) {
            matrix.data[row] = new double[cols]{};
        }
    } catch (...) {
        if (matrix.data != nullptr) {
            for (int row = 0; row < rows; ++row) {
                delete[] matrix.data[row];
            }
            delete[] matrix.data;
        }
        throw;
    }

    return matrix;
}

void free_matrix(Matrix matrix) {
    if (matrix.data == nullptr) {
        return;
    }

    for (int row = 0; row < matrix.rows; ++row) {
        delete[] matrix.data[row];
    }
    delete[] matrix.data;
}

Matrix matrix_add(Matrix first, Matrix second) {
    check_valid_matrix(first);
    check_valid_matrix(second);
    check_same_size(first, second);

    Matrix result = create_matrix(first.rows, first.cols);
    for (int row = 0; row < first.rows; ++row) {
        for (int col = 0; col < first.cols; ++col) {
            result.data[row][col] = first.data[row][col] + second.data[row][col];
        }
    }
    return result;
}

Matrix matrix_multiply(Matrix first, Matrix second) {
    check_valid_matrix(first);
    check_valid_matrix(second);
    if (first.cols != second.rows) {
        throw std::invalid_argument(
            "The number of columns in the first matrix must match the number of rows in the second");
    }

    Matrix result = create_matrix(first.rows, second.cols);
    for (int row = 0; row < first.rows; ++row) {
        for (int col = 0; col < second.cols; ++col) {
            for (int index = 0; index < first.cols; ++index) {
                result.data[row][col] += first.data[row][index] * second.data[index][col];
            }
        }
    }
    return result;
}

Matrix matrix_add_scalar(Matrix matrix, double value) {
    check_valid_matrix(matrix);

    Matrix result = create_matrix(matrix.rows, matrix.cols);
    for (int row = 0; row < matrix.rows; ++row) {
        for (int col = 0; col < matrix.cols; ++col) {
            result.data[row][col] = matrix.data[row][col] + value;
        }
    }
    return result;
}

void print_matrix(Matrix matrix) {
    if (!is_valid_matrix(matrix)) {
        std::cout << "[Empty matrix]\n";
        return;
    }

    constexpr int max_rows_to_show = 10;
    constexpr int max_cols_to_show = 8;
    const bool abbreviated_rows = matrix.rows > max_rows_to_show;
    const bool abbreviated_cols = matrix.cols > max_cols_to_show;
    const int rows_to_show = abbreviated_rows ? max_rows_to_show + 1 : matrix.rows;
    const int cols_to_show = abbreviated_cols ? max_cols_to_show + 1 : matrix.cols;

    const std::ios::fmtflags old_flags = std::cout.flags();
    const std::streamsize old_precision = std::cout.precision();
    std::cout << std::fixed << std::setprecision(2);

    for (int display_row = 0; display_row < rows_to_show; ++display_row) {
        if (abbreviated_rows && display_row == max_rows_to_show / 2) {
            std::cout << "[...]\n";
            continue;
        }

        const int row = abbreviated_rows && display_row > max_rows_to_show / 2
                            ? matrix.rows - (rows_to_show - display_row)
                            : display_row;
        std::cout << "[";
        for (int display_col = 0; display_col < cols_to_show; ++display_col) {
            if (display_col > 0) {
                std::cout << ' ';
            }
            if (abbreviated_cols && display_col == max_cols_to_show / 2) {
                std::cout << std::setw(8) << "...";
                continue;
            }

            const int col = abbreviated_cols && display_col > max_cols_to_show / 2
                                ? matrix.cols - (cols_to_show - display_col)
                                : display_col;
            std::cout << std::setw(8) << matrix.data[row][col];
        }
        std::cout << "]\n";
    }

    std::cout.flags(old_flags);
    std::cout.precision(old_precision);
}

Matrix matrix_from_array(double* data, int rows, int cols) {
    if (data == nullptr) {
        throw std::invalid_argument("Source data must not be null");
    }

    Matrix matrix = create_matrix(rows, cols);
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            matrix.data[row][col] = data[row * cols + col];
        }
    }
    return matrix;
}
