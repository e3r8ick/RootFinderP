/**
 * Copyright (C) 2018
 * Área Académica de Ingeniería en Computadoras, ITCR, Costa Rica
 * @Author: Erick Cordero, Victor Montero, Cristofer Villegas
 * @Date  : 13.03.2018
 */

#include <boost/math/tools/polynomial.hpp>
#ifndef ANPI_DEFLATE2_HPP
#define ANPI_DEFLATE2_HPP
using namespace boost::math::tools;
namespace anpi
{

    /**
     * Deflate a polynomial with real coeficients with a complex root 
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
    polynomial<T> deflate2(const polynomial<T> &poly, const std::complex<T> root, polynomial<T> &residuo)
    {   T real = std::real(root);
        T imag = std::imag(root);
        //get the quadratic divident from root
        const polynomial<T> rootDiv = {{real*real + imag*imag, -2 * real, 1}}; 
        int nv = rootDiv.size() -1 ;
        int n = poly.size() - 1;
        residuo = poly; 
        polynomial<T> quotient = poly;
        for (int i = 0; i < poly.size(); ++i){
            quotient[i] = 0.;
        }
        for (int k = n - nv ; k >=0; --k){
            std::cout << "k: " << k << " nv: " << nv << std::endl;
            quotient[k] = residuo[nv+k];
            for (int j = nv + k - 1; j >= k; --j){
                std::cout << "j: " << j << std::endl;
                residuo[j] -= quotient[k]*rootDiv[j-k];
            }
        }
        //add trailing zeros to residuo
        for (int j = nv; j <= n; ++j){
            residuo[nv] = T(0.0);
        }
        return quotient;
    }
}

#endif
