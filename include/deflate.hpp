/**
 * Copyright (C) 2018
 * Área Académica de Ingeniería en Computadoras, ITCR, Costa Rica
 *
 * This file is part of the numerical analysis lecture CE3102 at TEC
 *
 * @Author: Pablo Alvarado
 * @Date  : 10.02.2018
 */

#include <cmath>
#include <limits>
#include <functional>

#include "Exception.hpp"
#include <boost/math/tools/polynomial.hpp>
#ifndef ANPI_DEFLATE_HPP
#define ANPI_DEFLATE_HPP
using namespace boost::math::tools;
namespace anpi {
  
  /**
   * Find the roots of the function funct looking for it in the
   * interval [xl,xu], using the bisection method.
   *
   * @param funct a std::function of the form "T funct(T x)"
   * @param xl lower interval limit
   * @param xu upper interval limit
   *
   * @return root found, or NaN if none could be found.
   *
   * @throws anpi::Exception if inteval is reversed or both extremes
   *         have same sign.
   */
  template<typename T>
  polynomial<T> deflate(const polynomial<T>& poly,const T& root, polynomial<T>& residuo) {
   int n = poly.size()-1;
   residuo[0] = poly[n];
   polynomial<T> a = poly;
   a[n] = 0;
   T s =  T(0); 
   for (int i = n-1; i>=0; --i){
     s = a[i];
     a[i] = residuo[0];
     residuo[0] = s + residuo[0]*root;
   }
   return a;
   //return std::numeric_limits<T>::quiet_NaN();    
  }
}
  
#endif

