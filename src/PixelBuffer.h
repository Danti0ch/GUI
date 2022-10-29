#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <stdexcept>
// TODO: перенести

// TODO: верификатор чтобы n_loc_rows было меньше n_rows
class PixelBuffer{
public:

    // TODO: copypaste fix possible?
    Matrix(uint n_rows, uint n_cols):
        n_rows_(n_rows), n_cols_(n_cols),
        n_loc_row_init_(0), n_loc_col_init_(0),
        n_loc_rows_(n_rows), n_loc_cols_(n_cols), data_(n_rows * n_cols){}

    Matrix(uint n_rows, uint n_cols, const T& val):
        n_rows_(n_rows), n_cols_(n_cols),
        n_loc_row_init_(0), n_loc_col_init_(0),
        n_loc_rows_(n_rows), n_loc_cols_(n_cols), data_(n_rows * n_cols, val){}

    Matrix(const Matrix& other):
        n_rows_(other.n_rows_), n_cols_(other.n_cols_),
        n_loc_row_init_(other.n_loc_row_init_), n_loc_col_init_(other.n_loc_col_init_),
        n_loc_rows_(other.n_loc_rows_), n_loc_cols_(other.n_loc_cols_), data_(other.data_){}

    ~Matrix(){}

    /*
    Matrix submatrix(uint n_row1, uint n_row2, uint n_col1, uint n_col2) const{
        if(n_row1 > n_row2) std::swap(n_row1, n_row2);
        if(n_col1 > n_col2) std::swap(n_col1, n_col2);

        if(n_row2 >= n_rows_ || n_col2 >= n_cols) throw std::out_of_range("");

        uint sn_rows = n_row2 - n_row1 + 1;
        uint sn_cols = n_col2 - n_col1 + 1;

        Matrix submatrix(sn_rows, sn_cols);

        for(uint n_row = 0; n_row < sn_rows; n_row++){
            for(uint n_col = 0; n_col < sn_cols; n_col++){
                submatrix[n_row * sn_cols + n_col] = submatrix.data_[(n_row1 + n_row) * n_cols + n_col + n_col1];
            }
        }

        return submatrix;
    }*/

    T& access(uint n_row, uint n_col){
        if(n_row + n_loc_row_init_ >= n_loc_rows_) throw std::out_of_range("try to access %u out of %u row in pix_buffer", n_row, n_loc_rows_);
        if(n_col + n_loc_col_init_ >= n_loc_cols_) throw std::out_of_range("try to access %u out of %u col in pix_buffer", n_col, n_loc_cols_);
        return const_cast<T*>(data_.data()) + (n_row  + n_loc_row_init_) * n_cols_ + n_col + n_loc_col_init_;
    }

    const T& access(uint n_row, uint n_col) const{
        return const_cast<const T&>(const_cast<Matrix<T>*> (this)->access(n_row, n_col);
    }

    constexpr uint n_rows() const { return n_loc_rows_; }
    constexpr uint n_cols() const { return n_loc_cols_; }
    
private:
    std::vector<Color> data_;
    uint n_rows_, n_cols_;
    
    uint n_loc_row_init_, n_loc_col_init_;
    uint n_loc_rows_, n_loc_cols_;
};

#endif // MATRIX_H
