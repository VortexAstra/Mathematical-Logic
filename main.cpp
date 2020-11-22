#include <iostream>
#include "bdd.h"
#include "utils.hpp"
#include "limit.hpp"
#include "NeighbourRelations.hpp"

int main()
{
//  память для строк в таблице, кэш хранения
  bdd_init(10000000, 10000000);
//  Динамический Хэш
  bdd_setcacheratio(1000);
//  Число булевых пер
  bdd_setvarnum(N_VAR);
  bdd bddArrayWithSource[propertyNumbers][objectNumbers][objectNumbers];
  init(bddArrayWithSource);

  bdd bddTree = bddtrue;
// 5 6 3 1 1 1 1
  limitation1(bddTree, bddArrayWithSource, 0, 0, 0);
  limitation1(bddTree, bddArrayWithSource, 0, 1, 1);
  limitation1(bddTree, bddArrayWithSource, 3, 2, 1);
  limitation1(bddTree, bddArrayWithSource, 2, 6, 7);
  limitation1(bddTree, bddArrayWithSource, 2, 4, 5);
//extra
  limitation1(bddTree, bddArrayWithSource, 1, 8, 6);
  limitation1(bddTree, bddArrayWithSource, 3, 5, 3);
  limitation1(bddTree, bddArrayWithSource, 0, 5, 8);
  limitation1(bddTree, bddArrayWithSource, 1, 0, 4);
  limitation1(bddTree, bddArrayWithSource, 0, 3, 6);
  limitation1(bddTree, bddArrayWithSource, 1, 6, 2);
  limitation1(bddTree, bddArrayWithSource, 2, 2, 0);
  limitation1(bddTree, bddArrayWithSource, 2, 5, 2);
  limitation1(bddTree, bddArrayWithSource, 3, 6, 5);
  limitation1(bddTree, bddArrayWithSource, 1, 1, 1);
  limitation1(bddTree, bddArrayWithSource, 3, 7, 4);
  limitation1(bddTree, bddArrayWithSource, 1, 2, 0);

//если одно то другое ипликация
  limitation2(bddTree, bddArrayWithSource, 2, 6, 1, 5);
  limitation2(bddTree, bddArrayWithSource, 0, 3, 2, 6);
  limitation2(bddTree, bddArrayWithSource, 1, 8, 2, 4);
  limitation2(bddTree, bddArrayWithSource, 2, 7, 0, 7);
  limitation2(bddTree, bddArrayWithSource, 2, 8, 0, 2);
  limitation2(bddTree, bddArrayWithSource, 2, 1, 3, 6);

  limitation2(bddTree, bddArrayWithSource, 0, 6, 3, 8);
  limitation2(bddTree, bddArrayWithSource, 0, 4, 1, 7);

//сверху снизу в зависимости о тусловия
  limitation3(bddTree, bddArrayWithSource, NeighbourRelations::Right, 0, 5, 2, 1);
  limitation3(bddTree, bddArrayWithSource, NeighbourRelations::Right, 0, 0, 3, 2);
  limitation3(bddTree, bddArrayWithSource, NeighbourRelations::DOWN, 1, 4, 1, 8);
//стоит рядом
  limitation4(bddTree, bddArrayWithSource, 1, 5, 3, 7);

//  ПО УМОЛЧАНИЕ знаечние параметров не совпадает
  limitation5(bddTree, bddArrayWithSource);
//  (prop numbers )значение должно быть меньше < N
  limitation6(bddTree, bddArrayWithSource);
//сумма свойств объектов-соседей не должна быть больше K
  limitation7(bddTree, bddArrayWithSource);

  int satcount = bdd_satcount(bddTree);
  std::cout << satcount << " solutions:" << std::endl;
  if (satcount)
    bdd_allsat(bddTree, fun);

  bdd_done();

}

