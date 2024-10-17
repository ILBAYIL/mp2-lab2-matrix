#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <cassert>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

template<typename T>
class TDynamicVector
{
protected:
    size_t sz;
    T* pMem;

public:
    TDynamicVector(size_t size = 1) : sz(size) {
        if (sz == 0 || sz > MAX_VECTOR_SIZE)
            throw out_of_range("Вектор должен быть больше нуля но меньше максимального значения");
        pMem = new T[sz]();
    }

    TDynamicVector(T* arr, size_t s) : sz(s)
    {
        assert(arr != nullptr && "Конструктор TDynamicVector требует ненулевой аргумент");
        pMem = new T[sz];
        std::copy(arr, arr + sz, pMem);
    }

    TDynamicVector(const TDynamicVector& v) : sz(v.sz)
    {
        pMem = new T[sz];
        std::copy(v.pMem, v.pMem + sz, pMem);
    }

    TDynamicVector(TDynamicVector&& v) noexcept : sz(v.sz), pMem(v.pMem)
    {
        v.sz = 0;
        v.pMem = nullptr;
    }

    ~TDynamicVector()
    {
        delete[] pMem;
    }

    TDynamicVector& operator=(const TDynamicVector& v)
    {
        if (this != &v) {
            delete[] pMem;
            sz = v.sz;
            pMem = new T[sz];
            std::copy(v.pMem, v.pMem + sz, pMem);
        }
        return *this;
    }

    TDynamicVector& operator=(TDynamicVector&& v) noexcept
    {
        if (this != &v) {
            delete[] pMem;
            sz = v.sz;
            pMem = v.pMem;
            v.sz = 0;
            v.pMem = nullptr;
        }
        return *this;
    }

    size_t size() const noexcept { return sz; }

    T& operator[](size_t ind) {
        if (ind < 0 || ind >= sz) throw out_of_range("Индекс вне диапазона"); // Проверка на отрицательный и слишком большой индекс
        return pMem[ind]; // Без контроля
    }

    const T& operator[](size_t ind) const{
        if (ind >= sz) throw out_of_range("Индекс вне диапазона");
        return pMem[ind];
    }

    T& at(size_t ind)
    {
        if (ind >= sz) throw out_of_range("Индекс вне диапазона");
        return pMem[ind];
    }

    const T& at(size_t ind) const {
        if (ind >= sz) throw out_of_range("Индекс вне диапазона");
        return pMem[ind];
    }

    bool operator==(const TDynamicVector& v) const noexcept
    {
        if (sz != v.sz) return false;
        return std::equal(pMem, pMem + sz, v.pMem);
    }

    bool operator!=(const TDynamicVector& v) const noexcept
    {
        return !(*this == v);
    }

    TDynamicVector operator+(T val) const
    {
        TDynamicVector result(sz);
        std::transform(pMem, pMem + sz, result.pMem, [val](T elem) { return elem + val; });
        return result;
    }

    TDynamicVector operator-(T val) const
    {
        TDynamicVector result(sz);
        std::transform(pMem, pMem + sz, result.pMem, [val](T elem) { return elem - val; });
        return result;
    }

    TDynamicVector operator*(T val) const
    {
        TDynamicVector result(sz);
        std::transform(pMem, pMem + sz, result.pMem, [val](T elem) { return elem * val; });
        return result;
    }

    TDynamicVector operator+(const TDynamicVector& v) const
    {
        if (sz != v.sz) throw invalid_argument("Векторы должны быть одного размера");
        TDynamicVector result(sz);
        std::transform(pMem, pMem + sz, v.pMem, result.pMem, std::plus<T>());
        return result;
    }

    TDynamicVector operator-(const TDynamicVector& v) const
    {
        if (sz != v.sz) throw invalid_argument("Векторы должны быть одного размера");
        TDynamicVector result(sz);
        std::transform(pMem, pMem + sz, v.pMem, result.pMem, std::minus<T>());
        return result;
    }

    T operator*(const TDynamicVector& v) const noexcept(false) {
        // Проверка на равенство размеров векторов
        if (sz != v.sz) {
            throw std::invalid_argument("Векторы должны быть одного размера");
        }

        // Результат умножения
        T result = T(); // Предполагаем, что T поддерживает оператор сложения и имеет конструктор по умолчанию
        for (size_t i = 0; i < sz; ++i) {
            result += pMem[i] * v.pMem[i]; // Умножаем соответствующие элементы
        }
        return result; // Возвращаем результат
    }

    friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
    {
        std::swap(lhs.sz, rhs.sz);
        std::swap(lhs.pMem, rhs.pMem);
    }

    friend istream& operator>>(istream& istr, TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            istr >> v.pMem[i];
        return istr;
    }

    friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            ostr << v.pMem[i] << ' ';
        return ostr;
    }
};

template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
    using TDynamicVector<TDynamicVector<T>>::pMem;
    using TDynamicVector<TDynamicVector<T>>::sz;

public:
    size_t size() const noexcept { return sz; };
    TDynamicMatrix(size_t r = 1, size_t c = 1) : TDynamicVector<TDynamicVector<T>>(r) {
        if (r == 0 || c == 0 || r > MAX_MATRIX_SIZE || c > MAX_MATRIX_SIZE)
            throw out_of_range("Размер больше 0 и меньше максимального");
        for (size_t i = 0; i < r; i++) {
            pMem[i] = TDynamicVector<T>(c);
        }
    }

    size_t rows() const noexcept { return sz; }
    size_t cols() const noexcept { return pMem[0].size(); }



    bool operator==(const TDynamicMatrix& m) const noexcept {
        if (rows() != m.rows() || cols() != m.cols()) return false;
        return std::equal(pMem, pMem + rows(), m.pMem);
    }

    TDynamicMatrix operator*(const T& val) const {
        TDynamicMatrix res(rows(), cols());
        for (size_t i = 0; i < rows(); i++) {
            for (size_t j = 0; j < cols(); j++) {
                res[i][j] = pMem[i][j] * val;
            }
        }
        return res;
    }

    TDynamicVector<T> operator*(const TDynamicVector<T>& v) const {
        if (cols() != v.size()) throw invalid_argument("Число столбцов матрицы должно совпадать с размером вектора");
        TDynamicVector<T> res(rows());
        for (size_t i = 0; i < rows(); i++) {
            res[i] = 0;
            for (size_t j = 0; j < cols(); j++) {
                res[i] += pMem[i][j] * v[j];
            }
        }
        return res;
    }

    TDynamicMatrix operator+(const TDynamicMatrix& m) const {
        if (rows() != m.rows() || cols() != m.cols()) throw invalid_argument("Матрицы должны быть одного размера");
        TDynamicMatrix res(rows(), cols());
        for (size_t i = 0; i < rows(); i++) {
            res[i] = pMem[i] + m.pMem[i];
        }
        return res;
    }

    TDynamicMatrix operator-(const TDynamicMatrix& m) const {
        if (rows() != m.rows() || cols() != m.cols()) throw invalid_argument("Матрицы должны быть одного размера");
        TDynamicMatrix res(rows(), cols());
        for (size_t i = 0; i < rows(); i++) {
            res[i] = pMem[i] - m.pMem[i];
        }
        return res;
    }

    TDynamicMatrix operator*(const TDynamicMatrix& m) const {
        if (cols() != m.rows()) throw invalid_argument("Число столбцов первой матрицы должно совпадать с количеством строк второй матрицы");
        TDynamicMatrix res(rows(), m.cols());
        for (size_t i = 0; i < rows(); i++) {
            for (size_t j = 0; j < m.cols(); j++) {
                res[i][j] = 0;
                for (size_t k = 0; k < cols(); k++) {
                    res[i][j] += pMem[i][k] * m.pMem[k][j];
                }
            }
        }
        return res;
    }
    TDynamicVector<T>& operator[](size_t ind) {
        if (ind < 0 || ind >= sz) throw out_of_range("Row index out of range"); // Проверка на отрицательный и слишком большой индекс
        return pMem[ind];
    }
    friend istream& operator>>(istream& istr, TDynamicMatrix& m)
    {
        for (size_t i = 0; i < m.rows(); i++) {
            istr >> m.pMem[i];
        }
        return istr;
    }

    friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& m)
    {
        for (size_t i = 0; i < m.rows(); i++) {
            ostr << m.pMem[i] << endl;
        }
        return ostr;
    }
};

#endif
