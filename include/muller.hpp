/**
 * Copyright (C) 2018
 * Área Académica de Ingeniería en Computadoras, ITCR, Costa Rica
 * @Author: Erick Cordero, Victor Montero, Cristofer Villegas
 * @Date  : 16.03.2018
 */

#include <boost/math/tools/polynomial.hpp>
#include "Exception.hpp"
#ifndef ANPI_MULLER_HPP
#define ANPI_MULLER_HPP
using namespace boost::math::tools; //polynomial
using namespace boost::math; //sign
namespace anpi
{

/**
   * Calculates the roots of a polynomial using Muller's method
   * given the 3 starting points.
   *
   * @param poly the polynomial 
   * @param xi the highest starting point
   * @param ximin1 the middle starting point
   * @param ximin2 the lowest starting point.
   *
   * @return root the calculated root of the polynomial.
   */
template <std::size_t N, typename T, typename U>
U muller(const std::array<T,N> &poly, U xi, U h, bool pulir){
    U ximin1, ximin2;
    if (xi == 0){
        ximin1 = xi + h;
        ximin2 = xi - h;
    }else{
        ximin1 = xi + h*xi;
        ximin2 = xi - h*xi;
    }
    U dxi, xiplus1; //next estimate
    U fi, fimin1, fimin2; //evaluated values;
    U h0, h1, d0, d1; //intermediate steps
    U a, b; //quadratic coeficients
    U eps = sqrt(std::numeric_limits<U>::epsilon()); //threshold
    U disc; 
    int maxi = std::numeric_limits<U>::digits;
    int i = 0; 
    U ea = 100; //aproximate error
    do{
        /*fi = poly.evaluate(xi);*/
        /*fimin1 = poly.evaluate(ximin1);*/
        /*fimin2 = poly.evaluate(ximin2);*/
        
        fi = tools::evaluate_polynomial(poly, xi, 4);
        fimin1 = tools::evaluate_polynomial(poly, ximin1, 4);
        fimin2 = tools::evaluate_polynomial(poly, ximin2, 4);
        h0 = ximin1 - ximin2;
        h1 = xi - ximin1;
        d0 = (fimin1 - fimin2) / h0;
        d1 = (fi - fimin1) / h1;
        a = (d1 - d0) / (h1 + h0);
        b = a * h1 + d1;
        disc = b*b -4*a*fi;
        if (disc < 0){
            if (!std::is_same<U, std::complex<double>>::value && !std::is_same<U, std::complex<float>>::value){
                throw anpi::Exception("Attempt to calculate complex root while using real values");
            }
        }//end if discriminante < 0
        dxi = - 2 * fi / (b + sign(b)*sqrt(disc));
        xiplus1 = xi + dxi;
        ea = abs((xiplus1 - xi) / xiplus1) * 100;
        if (abs(dxi) < abs(eps*xiplus1)){
            if (pulir){
                return anpi::muller(poly, xiplus1, h, false);
            }
            std::cout << xiplus1 << std::endl;
            return xiplus1; //FIN de iteración
        }
        ximin2 = ximin1;
        ximin1 = xi;
        xi = xiplus1;
        ++i;
    }while (i < maxi);//end do .. while
    std::cout << xiplus1 <<std::endl;
    return std::numeric_limits<U>::quiet_NaN();
}
}

#endif
