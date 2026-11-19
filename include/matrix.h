#ifndef MATRIX_H
#define MATRIX_H

/**
 * @file matrix.h
 * @brief Basic dynamically allocated matrix operations.
 */

/**
 * @brief Matrix represented as an array of dynamically allocated rows.
 *
 * Memory owned by a Matrix must be released with free_matrix.
 */
struct Matrix {
    double** data;  ///< Pointer to the matrix rows.
    int rows;       ///< Number of rows.
    int cols;       ///< Number of columns.
};

/**
 * @brief Create a zero-initialized matrix.
 * @param rows Number of rows; must be positive.
 * @param cols Number of columns; must be positive.
 * @return A newly allocated matrix.
 * @throws std::invalid_argument If a dimension is not positive.
 * @throws std::bad_alloc If memory cannot be allocated.
 */
Matrix create_matrix(int rows, int cols);

/**
 * @brief Release all memory owned by a matrix.
 * @param m Matrix to release. An empty matrix is safe to pass.
 */
void free_matrix(Matrix m);

/**
 * @brief Add two matrices element by element.
 * @param a First matrix.
 * @param b Second matrix.
 * @return A newly allocated matrix containing a + b.
 * @throws std::invalid_argument If a matrix is invalid or dimensions differ.
 */
Matrix matrix_add(Matrix a, Matrix b);

/**
 * @brief Multiply two matrices using the standard matrix product.
 * @param a Left matrix with dimensions M x N.
 * @param b Right matrix with dimensions N x K.
 * @return A newly allocated M x K matrix.
 * @throws std::invalid_argument If a matrix is invalid or dimensions differ.
 */
Matrix matrix_multiply(Matrix a, Matrix b);

/**
 * @brief Add a scalar to every matrix element.
 * @param m Source matrix.
 * @param value Value added to each element.
 * @return A newly allocated result matrix.
 * @throws std::invalid_argument If the source matrix is invalid.
 */
Matrix matrix_add_scalar(Matrix m, double value);

/**
 * @brief Print a matrix with fixed two-decimal formatting.
 * @param m Matrix to print.
 *
 * Empty or invalid matrices are printed as [Empty matrix]. Large matrices are
 * printed in abbreviated form.
 */
void print_matrix(Matrix m);

/**
 * @brief Copy row-major array data into a newly allocated matrix.
 * @param data Source array containing rows * cols elements.
 * @param rows Number of rows; must be positive.
 * @param cols Number of columns; must be positive.
 * @return A newly allocated matrix containing a copy of data.
 * @throws std::invalid_argument If data is null or a dimension is invalid.
 */
Matrix matrix_from_array(double* data, int rows, int cols);

#endif // MATRIX_H
