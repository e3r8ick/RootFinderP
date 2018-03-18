/**
 * Copyright (C) 2018
 * Área Académica de Ingeniería en Computadoras, ITCR, Costa Rica
 * @Author: Erick Cordero, Victor Montero, Cristofer Villegas
 * @Date  : 16.03.2018
 */

#include <boost/math/tools/polynomial.hpp>
#include "deflate.hpp"
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
template <typename T, typename U>
U muller(const polynomial<T> &poly, U xi, U h, bool pulir){
    //definir variables del método
    polynomial<T> reducedPoly = poly;
    int degree =(int) poly.size();
    int n = 0; //cantidad de raíces encontradas
    T roots[degree];  //raíces
    while (n <= degree){
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
            if (n == 3){
                return 0;
            }
            fi = reducedPoly.evaluate(xi);
            fimin1 = reducedPoly.evaluate(ximin1);
            fimin2 = reducedPoly.evaluate(ximin2);
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
            ximin2 = ximin1;
            ximin1 = xi;
            xi = xiplus1;
            ++i;
            if (abs(dxi) < abs(eps*xiplus1)){
                std::cout << xiplus1 << std::endl;
                roots[n] = xiplus1; 
                n+=1;
                polynomial<T> residuo {{0}};
                std::cout << "Inicio" << std::endl;
                reducedPoly = anpi::deflate(poly, xiplus1, residuo);
                for (int i = 0; i < reducedPoly.size(); ++i){
                    std::cout << reducedPoly[i] << std::endl;
                }
                std::cout << "FIn" << std::endl; 
                i = 0;
                xi = 0.0;
            }
        }while (i < maxi);//end do .. while
    } // FIN WHILE N < DEGREE
    return std::numeric_limits<U>::quiet_NaN();
    }
}
#endif