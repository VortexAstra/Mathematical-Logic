//
// Created by Артем Устинов
//

#ifndef MAT_LOG_LIMIT_HPP
#define MAT_LOG_LIMIT_HPP

#include <bdd.h>
#include "utils.hpp"

void init(bdd p[propertyNumbers][objectNumbers][objectNumbers])
{
  int I = 0;
  for (int i = 0; i < objectNumbers; ++i) {
    for (int j = 0; j < objectNumbers; ++j) {
      for (int z = 0; z < propertyNumbers; ++z) {
        p[z][i][j] = bddtrue;
        for (int k = 0; k < LOG_N; ++k) {
//          bdd_ithvar - обращение к (*) переменной и к не
          p[z][i][j] &= ((j >> k) & 1) ? bdd_ithvar(I + LOG_N * z + k) : bdd_nithvar(I + LOG_N * z + k);
        }
      }
    }
    I += LOG_N * propertyNumbers;
  }
}

void limitation_1(bdd& tree, bdd p[propertyNumbers][objectNumbers][objectNumbers], int propertyNumber, int objectNumber, int propertyValue)
{
  tree &= p[propertyNumber][objectNumber][propertyValue];
}

void limitation_2(bdd& tree, bdd p[propertyNumbers][objectNumbers][objectNumbers], int propertyNumber1, int propertyValue1, int propertyNumber2, int propertyValue2)
{
  bdd treeTemp = bddtrue;

  for (int i = 0; i < objectNumbers; ++i) {
    treeTemp &= !(p[propertyNumber1][i][propertyValue1] ^ p[propertyNumber2][i][propertyValue2]);
  }
  tree &= treeTemp;
}

bdd lim3(bdd p[propertyNumbers][objectNumbers][objectNumbers], NeighbourRelations neighbour, int propertyNumber1, int propertyValue1, int propertyNumber2, int propertyValue2)
{
  bdd treeTemp = bddtrue;

  if (neighbour == Right) {//RIGHT
    for (int i = 0; i < objectNumbers; ++i) {
      if ((i + 1) % 3 != 0) {
        treeTemp &= !(p[propertyNumber1][i][propertyValue1] ^ p[propertyNumber2][i + 1][propertyValue2]);
      }
    }
  }
  else { //DOWN
    for (int i = 0; i < objectNumbers - N_SQRT; ++i) {
      treeTemp &= !(p[propertyNumber1][i][propertyValue1] ^ p[propertyNumber2][i + N_SQRT][propertyValue2]);
    }
  }
  return treeTemp;
}

void limitation_3(bdd& tree, bdd p[propertyNumbers][objectNumbers][objectNumbers], NeighbourRelations neighbour, int propertyNumber1, int propertyValue1, int propertyNumber2, int propertyValue2)
{
  tree &= lim3(p, neighbour, propertyNumber1, propertyValue1, propertyNumber2, propertyValue2);
}

void limitation_4(bdd& tree, bdd p[propertyNumbers][objectNumbers][objectNumbers], int propertyNumber1, int propertyValue1, int propertyNumber2, int propertyValue2)
{
  bdd treeTmp = bddfalse;

  treeTmp |= lim3(p, NeighbourRelations::Right, propertyNumber1, propertyValue1, propertyNumber2, propertyValue2);
  treeTmp |= lim3(p, NeighbourRelations::DOWN, propertyNumber1, propertyValue1, propertyNumber2, propertyValue2);

  tree &= treeTmp;
}

void limitation_5(bdd& tree, bdd p[propertyNumbers][objectNumbers][objectNumbers])  //property values are different
{
  for (int m = 0; m < propertyNumbers; ++m) {
    for (int i = 0; i < objectNumbers - 1; ++i) {
      for (int j = i + 1; j < objectNumbers; ++j) {
        for (int k = 0; k < objectNumbers; ++k) {
          tree &= p[m][i][k] >> !p[m][j][k];
        }
      }
    }
  }
}

void limitation_6(bdd& tree, bdd p[propertyNumbers][objectNumbers][objectNumbers])	//property values are < objectNumbers
{
  bdd treeTemp = bddtrue;

  for (int i = 0; i < objectNumbers; ++i) {
    for (int k = 0; k < propertyNumbers; ++k) {
      bdd temp = bddfalse;
      for (int j = 0; j < objectNumbers; ++j) {
        temp |= p[k][i][j];
      }

      treeTemp &= temp;
    }
  }

  tree &= treeTemp;
}

void limitation_7(bdd& tree, bdd p[propertyNumbers][objectNumbers][objectNumbers])
{
  for (int i = 0; i < objectNumbers - 1; i++)
    for (int j = 0; j < objectNumbers; j++)
      for (int k = 0; k < objectNumbers; k++)
        for (int x = 0; x < objectNumbers; x++)
          for (int y = 0; y < objectNumbers; y++)
            if (j + k + x + y > K)
              tree &= !(p[0][i][j] & p[1][i][k] & p[2][i][x] & p[3][i][y]);
}


void print()
{
  for (int i = 0; i < objectNumbers; i++) {
    std::cout << i << ": ";
    for (int j = 0; j < propertyNumbers; j++) {
      int J = i * propertyNumbers * LOG_N + j * LOG_N;
      int num = 0;
      for (int k = 0; k < LOG_N; k++) num += var[J + k] << k;
      std::cout << num << ' ';
    }
    std::cout << "\n";
  }
  std::cout << "\n";
}

void build(char* varset, unsigned n, unsigned I)
{
  if (I == n - 1) {
    if (varset[I] >= 0) {
      var[I] = varset[I];
      print();
      return;
    }

    var[I] = 0;
    print();
    var[I] = 1;
    print();
    return;
  }

  if (varset[I] >= 0) {
    var[I] = varset[I];
    build(varset, n, I + 1);
    return;
  }

  var[I] = 0;
  build(varset, n, I + 1);
  var[I] = 1;
  build(varset, n, I + 1);
}

void fun(char* varset, int size)
{
  build(varset, size, 0);
}

void fun(char* varset, int size);

#endif //MAT_LOG_LIMIT_HPP
