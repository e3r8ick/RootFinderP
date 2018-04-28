/**
 * Copyright (C) 2018
 * Área Académica de Ingeniería en Computadoras, ITCR, Costa Rica
 *
 * This file is part of the numerical analysis lecture CE3102 at TEC
 *
 * @Author: 
 * @Date  : 03.03.2018
 */

#include <cmath>
#include <limits>
#include <functional>
#include <iostream>
#include <algorithm>
#include <vector>

#define cimg_display 0
#include "CImg.h"
#include "Exception.hpp"
#include "Matrix.hpp"
#include "Pivot.hpp"

#ifndef ANPI_ROBOTLEGENDARIO_HPP
#define ANPI_ROBOTLEGENDARIO_HPP
using namespace cimg_library;

namespace anpi
{

/**
 * 
 * 
 * 
 **/
int mapeo(int i1, int j1, int i2, int j2, int m, int n)
{
    if (i1 < 0 || i2 < 0 || j1 < 0 || j2 < 0){
        return 0;
    }
    if (i1 >= m || i2 >= m || j1 >= n || j2 >= n){
        return 0;
    }
    int iMayor, iMenor, jMenor;

    //sacamos el mayor y menor de i 
    if(i1 >= i2){
        iMayor = i1;
        iMenor = i2;
    }else{
        iMayor = i2;
        iMenor = i1;
    }

    //sacamos el menor de j
    if(j1 >= j2){
        jMenor = j2;
    }else{
        jMenor = j1;
    }


    int result = 2 * iMayor * (n-1) + jMenor + iMenor + 1;

    if(iMayor == iMenor){
        return result;

    }
    return result-(n-1);

}

/**
 * 
 * 
 * 
 * */
std::vector<int> mapeoInverso(int mapeado, int m, int n)
{
    std::vector<int> coordenadas;
    int iMayor, iMenor, jMayor, jMenor;
    int mn = 2*n-1;
    int mod = mapeado % mn;
    int divi = mapeado/mn;

    //sacamos j e i mayor y menor
    if (mod == 0){ // last column
        iMayor = divi;
        iMenor = divi - 1;
        jMayor = jMenor = n-1;
        coordenadas.push_back(iMenor);
        coordenadas.push_back(jMayor);
        coordenadas.push_back(iMayor);
        coordenadas.push_back(jMenor);
    }
    else if(mod > n-1){ //vertical
        mod -= n;
        jMenor = jMayor = mod;
        iMenor = divi;
        iMayor = divi + 1;
        coordenadas.push_back(iMenor);
        coordenadas.push_back(jMayor);
        coordenadas.push_back(iMayor);
        coordenadas.push_back(jMenor);
       
    }else{ //horizontal
        jMenor = mod -1;
        jMayor = mod;
        iMenor = iMayor = divi;
        coordenadas.push_back(iMayor);
        coordenadas.push_back(jMenor);
        coordenadas.push_back(iMenor);
        coordenadas.push_back(jMayor);
    }
    return coordenadas;
}

bool isCorner(int i, int j, int m, int n){
    if (i == 0 && j == 0){
        return true;
    }else if(i == m-1 && j == n-1){
        return true;
    }else if(i == 0 && j == n-1){
        return true;
    }else if (i == m-1 && j == 0){
        return true;
    }else{
        return false;
    }
}

template <typename T>
void nodos(int m, int n, Matrix<T> &A, int iin, int jin, 
           int ifin, int jfin, std::vector<T> b){
    bool eliminado = false;
    int index = 0;
    int m1, m2, m3, m4;
    for(int i=0; i < m; ++i){
        for(int j=0; j<n; ++j){
            if (index >= (2*m*n - m - n)){
                std::cout << "here" << std::endl;
            }
            
            m1=mapeo(i-1, j, i ,j,m, n);
            m2=mapeo(i, j, i,j+1,m,n);
            m3=mapeo(i+1, j, i,j,m,n);
            m4=mapeo(i, j-1, i ,j,m,n);
            
            if (m4 != 0){
                A[index][m4-1] = 1.0;
            }if (m1 != 0){
                A[index][m1-1] = 1.0;
            }if (m2 != 0){
                A[index][m2-1] = -1.0;    
            }if (m3 != 0){
                A[index][m3-1] = -1.0;
            }
            
            if ((i == iin) && (j == jin)){ //inicio
                std::cout << "inicio: ";
                b[index] = 1.0;
                std::cout << " /inicio" <<std::endl;
                ++index;
            }else if ((i == ifin) && (j == jfin)){ // final
                std::cout << "final: ";

                b[index] = -1.0;
                std::cout << " /final" <<std::endl;
                ++index;
                
            }else if (!eliminado && isCorner(i, j, m, n)){
                if (m4 != 0){
                A[index][m4-1] = 0;
                }if (m1 != 0){
                    A[index][m1-1] = 0;
                }if (m2 != 0){
                    A[index][m2-1] = 0;    
                }if (m3 != 0){
                    A[index][m3-1] = 0;
                }
                eliminado = true;
            }else{
                ++index;
            }
        } // end for j
    }//end for i
    std::cout << "end nodos" << std::endl;
}

template <typename T>
void mallas(int m, int n, Matrix<T> &A, const std::vector<int> &resistors){
    int index = m*n -1; //initial index to place the equations in A
    int m1, m2, m3, m4;
    for (int i = 0; i < (m-1); ++i){
        for (int j = 0; j< (n-1); ++j){
            //obtener posiciones para las resitencias
            m1 = anpi::mapeo(i, j, i, j+1, m, n); // derecha adyacente al nodo (pos)
            m2 = anpi::mapeo(i, j+1, i+1, j+1, m, n); //derecha para abajo (pos)
            m3 = anpi::mapeo(i+1, j, i+1, j+1, m ,n); // abajo acostada (neg)
            m4 = anpi::mapeo(i , j, i+1, j, m, n); //abajo adyancente al nodo (neg)

            A[index][m1-1] = (T) resistors[m1-1];
            A[index][m2-1] = (T) resistors[m2-1];
            A[index][m3-1] = (T) -resistors[m3-1];
            A[index][m4-1] = (T) -resistors[m4-1];    
            index++;       
        }
    }
}

std::vector<int> getResistors(CImg<unsigned char> image){

  int w = image.width();
  int h = image.height();
  const int oneOhm = 1;
  const int oneMega = 1000000;
  std::vector<int> resistors;
  std::vector<int> coordenadas;
  int i1,i2,j1,j2;
  int R1, R2, G1, G2, B1, B2; 
  int colorThreshold = 255; //allow option to use light-almost white colors as white if adjusted
  int rAmount = 2*w*h - (w+h);

  for (int i = 1; i <= rAmount; ++i){
      coordenadas = anpi::mapeoInverso(i, h, w);
      //valores de los terminales de la resistencia
      i1 = coordenadas[0];
      j1 = coordenadas[1];
      i2 = coordenadas[2];
      j2 = coordenadas[3];

      //colores de los nodos terminales de la resistencia
      R1 = (int)image(i1,j1,0,0);
      G1 = (int)image(i1,j1,0,1);
      B1 = (int)image(i1,j1,0,2);

      R2 = (int)image(i2,j2,0,0);
      G2 = (int)image(i2,j2,0,1);
      B2 = (int)image(i2,j2,0,2);
      if (R1 >= colorThreshold && R2 >= colorThreshold && G1 >= colorThreshold
       && G2 >= colorThreshold && B1 >= colorThreshold && B2 >= colorThreshold){
        resistors.push_back(oneOhm);
      }else{
        resistors.push_back(oneMega);
      }
  }
  return resistors;
}

} //anpi

#endif
