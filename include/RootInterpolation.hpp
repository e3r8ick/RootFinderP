/**
 * Copyright (C) 2018
 * Área Académica de Ingeniería en Computadoras, ITCR, Costa Rica
 *
 * This file is part of the numerical analysis lecture CE3102 at TEC
 *
 * @Author: Pablo Alvarado
 * @Date  : 10.02.2018
 */

#include <iostream>
#include <cmath>
#include <limits>
#include <functional>

#include "Exception.hpp"

#ifndef ANPI_ROOT_INTERPOLATION_HPP
#define ANPI_ROOT_INTERPOLATION_HPP

namespace anpi {
  
  /**
   * Find the roots of the function funct looking for it in the
   * interval [xl,xu], by means of the interpolation method.
   *
   * @param funct a functor of the form "T funct(T x)"
   * @param xl lower interval limit
   * @param xu upper interval limit
   *
   * @return root found, or NaN if none could be found.
   *
   * @throws anpi::Exception if inteval is reversed or both extremes
   *         have same sign.
   */
  template<typename T>
  T rootInterpolation(const std::function<T(T)>& funct,T xl,T xu,const T eps) {

    // TODO: Put your code in here!

    T xr=xl; //inicialización
    T fl = funct(xl);
    T fu = funct(xu);
    const int maxi=std::numeric_limits<T>::digits;
    T es = sqrt(eps);

    T ea=T();

    int iu(0), il(0); //contadores

    for(int i=maxi;i>0;--i){
      T xrold(xr);
      xr=xu-fu*(xl-xu)/(fl-fu);
      T fr=funct(xr);

      if(std::abs(xr)>eps){
        ea = std::abs((xr-xrold)/xr)*T(100);
      }

      T cond=fl*fr;
      if(cond <T(0)){
        xu=xr;
        fu=fr;
        iu=0;
        il++;
        if(il>=2){
          fl/=T(2);
        }
      }else if (cond > T(0)){
        xl = xr;
        fl = fr;
        il=0;
        iu++;
        if(iu>=2){
          fu/=2;
        }
        else {
          ea = T(0);
          xr = (fl == T(0)) ? xl : xu;
        }
        if(ea < es) {
          std::cout <<"xr: " << xr << ".\n";
          return xr;
        }
      }

    }

    // Return NaN if no root was found
    return std::numeric_limits<T>::quiet_NaN();
  }

}
  
#endif

