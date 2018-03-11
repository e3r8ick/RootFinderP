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

#ifndef ANPI_ROOT_BISECTION_HPP
#define ANPI_ROOT_BISECTION_HPP

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
  T rootBisection(const std::function<T(T)>& funct,T xl,T xu,const T eps) {

    // TODO: Put your code in here!

	  T xr=xl; //iniciarlo 
	  T fl =funct(xl);
	  //T maxi = log2((std::abs(xu-xl))/eps); //falla si xl>xu
	  const int maxi=std::numeric_limits<T>::digits;
	  T es = sqrt(eps);


	  T ea=T();

	  for(int i=maxi; i >0;--i){
  	  T xrold(xr);
  	  xr=(xl+xu)/T(2);
  	  T fr=funct(xr);

  	  if(std::abs(xr) > eps){
  		  ea=std::abs((xr-xrold)/xr)*T(100); //nuevo error
  	  }
  	  T cond= fl*fr;
  	  if(cond < T(0)){
  		  xu=xr;
  	  }else if(cond > T(0)){
  		  xl=xr;
  		  fl=fr;
  	  }else{
  		  ea=T(0);//No hay error 
  		  xr=(std::abs(fl) < eps) ? xl:xr;
  	  }
	  if(xr<xl or xr>xu){
		  //error, raiz fuera del rango
	  }
  	  if(ea<es) {
			return xr;
		}
	  }

    // Return NaN if no root was found
    return std::numeric_limits<T>::quiet_NaN();
  }

}

#endif
