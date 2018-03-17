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
#ifndef ANPI_LAGUERRE_HPP
#define ANPI_LAGUERRE_HPP
using namespace boost::math::tools;
namespace anpi {

  /**
   * Find the roots of the function funct with the LAGUERRE method
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
  polynomial<T> laguerre(const polynomial<T>& poly, T x) {

    T eps = sqrt(std::numeric_limits<T>::epsilon());
    T n = poly.size()-1;
    T p=0; 
    T df=0; 
    T ddf=0;
    for(int j=n; j>=0; j--){
      ddf=ddf*x+df; //segunda derivada
      df=df*x+p; //primera derivada
      p=p*x+poly[j];//polinomio evaluado en x
    }

    T xk = 0;
    T g = 0;
    T h = 0;
    T sk = 0;
    T maxi = std::numeric_limits<T>::digits;
    for(T i=0; xk>eps || i==maxi; i++){   
      g = df/p;
      h= g*g-(ddf/df);
      sk= n/(g+sgn(g+0)*sqrt((n-1*(n*h-g*g))));
      xk = xk - sk;
    }
	

    // Return NaN if no root was found
    return std::numeric_limits<T>::quiet_NaN();
  }

  template <typename T> T sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

}

#endif
