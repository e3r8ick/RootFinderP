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
#include <iostream>
#include "Exception.hpp"
#include <iomanip>
#include <boost/math/tools/polynomial.hpp>
#ifndef ANPI_LAGUERRE_HPP
#define ANPI_LAGUERRE_HPP
using namespace boost::math::tools;
namespace anpi {

  template<typename T> 
  T laguerre(const polynomial<T>& poly, T xi){
    T n = poly.degree();
    T df=0; 
    T ddf=0;
    T xp = 1;        
    int maxi = std::numeric_limits<T>::digits;
    T eps = std::numeric_limits<T>::epsilon();
    T g, h, a;
    T fi = poly.evaluate(xi);
    for (int i = 0; i < maxi; ++i){
      if (abs(fi) < sqrt(eps)){
        return xi;
      }else{
        //primer derivada
        df = 0;
        xp = 1;
        std::cout << "Derivadas para " << xi << std::endl;
        for (int i= 1; i<(n+1); i++){
          df += i*xp*poly[i];
          xp*=xi;
        }
        std::cout << "1era: " << df << std::endl;
        xp = 1.0;
        ddf = 0;
        //segunda derivada
        for (int i = 2; i<(n+1); i++){
          ddf += (i-1)*i*xp*poly[i];
          xp*=xi;
        }
        std::cout << "2da: " << ddf << std::endl;
        g = df/fi;
        h = g*g - ddf/df;
        a = n/(g+boost::math::sign(g+0)*sqrt((n-1)*(n*h-g*g)));
        xi = xi-a;
        fi = poly.evaluate(xi);
      if (abs(a) < sqrt(eps)){
        return xi;
      }
      }//end else siguiente iteración.
    }//end for
    return xi;
  }

}
#endif