#include "../include/hw1.h"
#include <utility>
#include <random>
#include <iostream>
#include <iomanip>
#include <stdexcept>


using Matrix = std::vector<std::vector<double>>;

Matrix algebra::zeros(size_t n, size_t m){
    return std::move(Matrix(n, std::vector<double>(m, 0)));
}

Matrix algebra::ones(size_t n, size_t m){
    return std::move(Matrix(n, std::vector<double>(m, 1)));
}

Matrix algebra::random(size_t n, size_t m, double min, double max){
    if(max < min) throw std::logic_error("");
    std::mt19937_64 rd(time(0));
    std::uniform_real_distribution<double> uniform_dist(min, max);
    Matrix cur(n, std::vector<double>(m));
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            cur[i][j] = uniform_dist(rd);
        }
    }
    return std::move(cur);
}

void algebra::show(const Matrix& matrix){
    for(auto& i: matrix)
    {
        for(auto& j: i)
        {
            std::cout << std::setw(3) << j;
        }
    }
}

Matrix algebra::multiply(const Matrix& matrix, double c){
    Matrix cur = matrix;
    for(auto& i: cur)
    {
        for(auto& j: i)
        {
            j *= c;
        }
    }
    return std::move(cur);
}

Matrix algebra::multiply(const Matrix& matrix1, const Matrix& matrix2){
    if(matrix1.empty() && matrix2.empty()) return matrix1;
    if(matrix1.empty() || matrix2.empty()) throw std::logic_error("");
    int row_1 = matrix1.size();
    int colm_1 = matrix1[0].size();
    int row_2 = matrix2.size();
    int colm_2 = matrix2[0].size();
    if(colm_1 != row_2) throw std::logic_error("");
    Matrix now(row_1, std::vector<double>(colm_2, 0));
    for(int i = 0; i < row_1; i++)
    {
        for(int j = 0; j < colm_2; j++)
        {
            for(int k = 0; k < colm_1; k++)
            {
                now[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    return std::move(now);
}

Matrix algebra::sum(const Matrix& matrix, double c){
    Matrix cur = matrix;
    for(auto& i: cur)
    {
        for(auto& j: i)
        {
            j += c;
        }
    }
    return std::move(cur);
}

Matrix algebra::sum(const Matrix& matrix1, const Matrix& matrix2){
    if(matrix1.empty() && matrix2.empty()) return matrix1;
    if(matrix1.empty() || matrix2.empty()) throw std::logic_error("");
    int row_1 = matrix1.size();
    int colm_1 = matrix1[0].size();
    int row_2 = matrix2.size();
    int colm_2 = matrix2[0].size();

    if(row_1 != row_2 || colm_1 != colm_2) throw std::logic_error("");
    Matrix cur = matrix1;
    for(int i = 0; i < row_2; i++)
    {
        for(int j = 0; j < colm_2; j++)
        {
            cur[i][j] += matrix2[i][j];
        }
    }
    return std::move(cur);
}

Matrix algebra::transpose(const Matrix& matrix){
    if(matrix.empty()) return matrix;
    int row = matrix.size();
    int colm = matrix[0].size();

    Matrix cur(colm, std::vector<double>(row));
    for(int i = 0; i < colm; i++)
    {
        for(int j = 0; j < row; j++)
        {
            cur[i][j] = matrix[j][i];
        }
    }
    return std::move(cur);
}

Matrix algebra::minor(const Matrix& matrix, size_t n, size_t m){
    if(matrix.empty()) throw std::logic_error("");
    int row = matrix.size();
    int colm = matrix[0].size();

    if(row <= n || colm <= m) throw std::logic_error("");
    Matrix cur = {};
    for(int i = 0; i < row; i++)
    {
        if(i != n)
        {
            std::vector<double> now = {};
            for(int j = 0; j < colm; j ++)
            {
                if(j != m) now.push_back(matrix[i][j]);
            }
            cur.push_back(now);
        }
    }
    return std::move(cur);
}

double algebra::determinant(const Matrix& matrix){
    int row = matrix.size();
    if(row == 0) return 1;
    int colm = matrix[0].size();
    if(row != colm) throw std::logic_error("");
    double sum = 1;
    Matrix cur_matrix = upper_triangular(matrix);
    for(int i = 0; i < row; i++)
    {
        sum *= cur_matrix[i][i];
    }
    return sum;
}

Matrix algebra::inverse(const Matrix& matrix){
    int row = matrix.size();
    if(row == 0) return matrix;
    int colm = matrix[0].size();
    if(row != colm) throw std::logic_error("");
    Matrix now(row, std::vector<double>(colm, 0));
    double cur = algebra::determinant(matrix);
    if(cur == 0) throw std::logic_error("");
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < colm; j++)
        {
            now[i][j] = algebra::determinant(algebra::minor(matrix, j, i)) / cur;
            if((i + j) & 1) now[i][j] *= -1;
        }
    }
    return std::move(now);
}

Matrix algebra::concatenate(const Matrix& matrix1, const Matrix& matrix2, int axis = 0){
    if(matrix1.empty() || matrix2.empty()) throw std::logic_error("");
    int row1 = matrix1.size();
    int colm1 = matrix1[0].size();
    int row2 = matrix2.size();
    int colm2 = matrix2[0].size();
    if(axis == 0)
    {
        if(colm1 != colm2) throw std::logic_error("");
        Matrix cur = matrix1;
        Matrix now = matrix2;
        for(auto i: now)
        {
            cur.push_back(i);
        }
        return std::move(cur);
    }
    else if(axis == 1)
    {
        if(row1 != row2) throw std::logic_error("");
        Matrix cur = matrix1;
        for(int i = 0; i < row2; i++)
        {
            for(int j = 0; j < colm2; j++)
            {
                cur[i].push_back(matrix2[i][j]);
            }
        }
        return std::move(cur);
    }
}

Matrix algebra::ero_swap(const Matrix& matrix, size_t r1, size_t r2){
    int row = matrix.size();
    if(r1 >= row || r2 >= row) throw std::out_of_range("");
    Matrix cur = matrix;
    cur[r1].swap(cur[r2]);
    return std::move(cur);
}

Matrix algebra::ero_multiply(const Matrix& matrix, size_t r, double c){
    int row = matrix.size();
    if(r >= row) throw std::out_of_range("");    
    Matrix cur = matrix;
    for(auto& i: cur[r])
    {
        i *= c;
    }
    return std::move(cur);
}

Matrix algebra::ero_sum(const Matrix& matrix, size_t r1, double c, size_t r2){
    int row = matrix.size();
    if(r1 >= row || r2 >= row) throw std::out_of_range("");
    Matrix cur = matrix;
    int colm = cur[0].size();
    for(int i = 0; i < colm; i++)
    {
        cur[r2][i] += c * cur[r1][i];
    }
    return std::move(cur);
}

Matrix algebra::upper_triangular(const Matrix& matrix){
    if(matrix.empty()) return matrix;
    int row = matrix.size();
    int colm = matrix[0].size();
    if(row != colm) throw std::logic_error("");
    Matrix cur = matrix;
    for(int i = 0; i < row; i++)
    {
        if(cur[i][i] == 0)
        {
            for(int j = i + 1; j < row; j++)
            {
                if(cur[j][i] != 0)
                {
                    cur = ero_swap(cur, i, j);
                    break;
                }
            }
        }
        if(cur[i][i] != 0)
        {
            for(int j = i + 1; j < row; j++)
            {
                cur = ero_sum(cur, i, -1 * cur[j][i] / cur[i][i], j);
            }
        }
    }
    return cur;
}
