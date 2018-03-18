/**
 * Copyright (C) 2018
 * Área Académica de Ingeniería en Computadoras, ITCR, Costa Rica
 * @Author: Erick Cordero, Victor Montero, Cristofer Villegas
 * @Date  : 13.03.2018
 */

#include <boost/math/tools/polynomial.hpp>
#ifndef ANPI_DEFLATE_HPP
#define ANPI_DEFLATE_HPP
using namespace boost::math::tools;
namespace anpi
{

/**
   * Deflate a polynomial with real coeficients with a real root 
   * of 1 degree.
   *
   * @param poly the polynomial to deflate"
   * @param root the root to divide it by
   * @param residuo a polynomial passed by reference to store the remainder
   *
   * @return a the deflated polynomial.
   *
   */
template <typename T>
polynomial<T> deflate(const polynomial<T> &poly, const T &root, polynomial<T> &residuo)
{
  int n = poly.size() - 1;
  residuo[0] = poly[n];
  polynomial<T> a = poly;
  a[n] = 0;
  T s = T(0);
  for (int i = n - 1; i >= 0; --i)
  {
    s = a[i];
    a[i] = residuo[0];
    residuo[0] = s + residuo[0] * root;
  }
  return a;
}
}

#endif
