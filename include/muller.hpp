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
*/

  
template <typename T, typename U >
U muller(const polynomial<T> &poly, U xi, U h, bool pulir, U roots[], int tama ){
    //definir variables del método
    polynomial<T> reducedPoly = poly;
    int degree =(int) poly.degree();
    int n = 0; //cantidad de raíces encontradas
    bool puliendo = false;
    while (n < degree-1){
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
        //U ea = 100; //aproximate error
        do{
            //pulir la raíz
            if (pulir && puliendo){
                fi = poly.evaluate(xi);
                fimin1 = poly.evaluate(ximin1);
                fimin2 = poly.evaluate(ximin2);

            }else{ //no pulir la raiz
                fi = reducedPoly.evaluate(xi);
                fimin1 = reducedPoly.evaluate(ximin1);
                fimin2 = reducedPoly.evaluate(ximin2);
            }
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
            //ea = abs((xiplus1 - xi) / xiplus1) * 100;            
            ximin2 = ximin1;
            ximin1 = xi;
            xi = xiplus1;
            ++i;
            if (pulir && !puliendo){
                puliendo = true;
                break;
            }//end pulir
            else if (abs(dxi) < abs(eps*xiplus1)){
                roots[n] = xiplus1; 
                n+=1;
                polynomial<T> residuo {{0}};
                reducedPoly = anpi::deflate(reducedPoly, xiplus1, residuo);                
                xi = 0.0;
                puliendo = false;
                break;
            }//end found root
        }while (i < maxi);//end do .. while
        if (i >= maxi){
            return 0;
        }
    } // FIN WHILE N < DEGREE
    roots[n] = -reducedPoly[0];
    return 1;
    }
}
#endif