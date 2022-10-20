﻿// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz == 0)
      throw out_of_range("Vector size should be greater than zero");
    if(size > MAX_VECTOR_SIZE)
        throw out_of_range("over then max size");
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v)
  {
      sz = v.sz;
      pMem = new T[sz];
      std::copy(v.pMem, v.pMem + sz, pMem);
  }
  TDynamicVector(TDynamicVector&& v) noexcept
  {
      pMem = nullptr;
      swap(*this, v);
  }
  ~TDynamicVector()
  {
      delete[] pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if(this == &v)
          return *this;
      TDynamicVector tmp(v);
      swap(*this, tmp);
      return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      swap(*this, v);
      return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
      if(ind < 0 || ind >= sz)
          throw "Index is invalid";
      return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
      if(ind < 0 || ind >= sz)
          throw "Index is invalid";
      return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if(ind < 0 || ind >= sz)
          throw "Index is invalid";
      return pMem[ind];
  }
  const T& at(size_t ind) const
  {
      if(ind < 0 || ind >= sz)
          throw "Index is invalid";
      return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if(this == &v)
          return true;
      if(sz != v.sz)
          return false;
      for (int i = 0; i < sz; i++) {
          if(pMem[i] != v.pMem[i])
              return false;
      }
      return true;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      if(this == &v)
          return false;
      if(sz != v.sz)
          return true;
      for (int i = 0; i < sz; i++) {
          if(pMem[i] != v.pMem[i])
              return true;
      }
      return false;
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      TDynamicVector tmp(sz);
      for(size_t i = 0; i < sz; i++)
          tmp.pMem[i] = pMem[i] + val;
      return tmp;
  }
  TDynamicVector operator-(double val)
  {
      TDynamicVector tmp(sz);
      for(size_t i = 0; i < sz; i++)
          tmp.pMem[i] = pMem[i] - val;
      return tmp;
  }
  TDynamicVector operator*(double val)
  {
      TDynamicVector tmp(sz);
      for(size_t i = 0; i < sz; i++)
          tmp.pMem[i] = pMem[i] * val;
      return tmp;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      int maxLen = sz > v.sz ? sz : v.sz;
      TDynamicVector tmp(maxLen);
      int i = 0;
      for (; i < sz && i < v.sz; i++)
          tmp.pMem[i] = pMem[i] + v.pMem[i];
      for (; i < sz; i++)
          tmp.pMem[i] = pMem[i];
      for (; i < v.sz; i++)
          tmp.pMem[i] = v.pMem[i];
      return tmp;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      int maxLen = sz > v.sz ? sz : v.sz;
      TDynamicVector tmp(maxLen);
      int i = 0;
      for (; i < sz && i < v.sz; i++)
          tmp.pMem[i] = pMem[i] - v.pMem[i];
      for (; i < sz; i++)
          tmp.pMem[i] = pMem[i];
      for (; i < v.sz; i++)
          tmp.pMem[i] = -v.pMem[i];
      return tmp;
  }
  T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
  {
      int res = 0;
      for(size_t i = 0; i < sz && i < v.sz; i++)
          res += pMem[i] * v.pMem[i];
      return res;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица -
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;

  TDynamicMatrix transpose(const TDynamicMatrix& m){
      TDynamicMatrix tmp(m.sz);
      for (int i = 0; i < m.sz; i++)
          for (int j = 0; j < m.sz; j++)
              tmp[i][j] = m[j][i];
      return tmp;
  }
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
    if(s > MAX_MATRIX_SIZE)
      throw out_of_range("s is under MAX_MATRIX_SIZE");
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::size;
  using TDynamicVector<TDynamicVector<T>>::operator[];
  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      if(sz != m.sz)
          return false;
      for (int i = 0; i < sz; i++) {
          if(pMem[i] != m.pMem[i])
              return false;
      }
      return true;
  }

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val)
  {
      TDynamicMatrix tmp(sz);
      for (int i = 0; i < sz; i++)
          tmp.pMem[i] = pMem[i] * val;
      return tmp;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      TDynamicVector<T> tmp(sz);
      for (int i = 0; i < sz; i++)
          tmp[i] = pMem[i] * v;
      return tmp;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      int maxSize = sz > m.sz ? sz : m.sz;
      TDynamicMatrix tmp(maxSize);
      int i = 0;
      for (; i < sz && i < m.sz; i++)
          tmp.pMem[i] = pMem[i] + m.pMem[i];
      for (; i < sz; i++)
          tmp.pMem[i] = pMem[i];
      for (; i < m.sz; i++)
          tmp.pMem[i] = m.pMem[i];
      return tmp;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      int maxSize = sz > m.sz ? sz : m.sz;
      TDynamicMatrix tmp(maxSize);
      int i = 0;
      for (; i < sz && i < m.sz; i++)
          tmp.pMem[i] = pMem[i] - m.pMem[i];
      for (; i < sz; i++)
          tmp.pMem[i] = pMem[i];
      for (; i < m.sz; i++)
          tmp.pMem[i] = m.pMem[i] * (-1);
      return tmp;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      int minSz = sz > m.sz ? m.sz : sz;
      TDynamicMatrix res(minSz);
      TDynamicMatrix tmp = transpose(m);
      for (int i = 0; i < minSz; i++)
          for (int j = 0; j < minSz; j++)
              res[i][j] = pMem[i] * tmp[j];
      return res;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; i++)
          istr >> v.pMem[i]; // требуется оператор>> для типа T
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; i++)
          ostr << v.pMem[i] << endl; // требуется оператор<< для типа T
      return ostr;
  }
};

#endif
