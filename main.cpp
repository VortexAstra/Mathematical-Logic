#include <iostream>
#include "bdd.h"
#include "utils.hpp"
#include "limit.hpp"

int main()
{
//  память для строк в таблице, кэш хранения
  bdd_init(10000000, 10000000);
//  Динамический Хэш
  bdd_setcacheratio(1000);
//  Число булевых пер
  bdd_setvarnum(N_VAR);
  bdd p[propertyNumbers][objectNumbers][objectNumbers];
  init(p);

  bdd tree = bddtrue;
// 5 6 3 1 1 1 1
  limitation_1(tree, p, 0, 0, 0);
  limitation_1(tree, p, 0, 1, 1);
  limitation_1(tree, p, 3, 2, 1);
  limitation_1(tree, p, 2, 6, 7);
  limitation_1(tree, p, 2, 4, 5);
//extra
  limitation_1(tree, p, 1, 8, 6);
  limitation_1(tree, p, 3, 5, 3);
  limitation_1(tree, p, 0, 5, 8);
  limitation_1(tree, p, 1, 0, 4);
  limitation_1(tree, p, 0, 3, 6);
  limitation_1(tree, p, 1, 6, 2);
  limitation_1(tree, p, 2, 2, 0);
  limitation_1(tree, p, 2, 5, 2);
  limitation_1(tree, p, 3, 6, 5);
  limitation_1(tree, p, 1, 1, 1);
  limitation_1(tree, p, 3, 7, 4);
  limitation_1(tree, p, 1, 2, 0);

//если одно то другое ипликация
  limitation_2(tree, p, 2, 6, 1, 5);
  limitation_2(tree, p, 0, 3, 2, 6);
  limitation_2(tree, p, 1, 8, 2, 4);
  limitation_2(tree, p, 2, 7, 0, 7);
  limitation_2(tree, p, 2, 8, 0, 2);
  limitation_2(tree, p, 2, 1, 3, 6);

  limitation_2(tree, p, 0, 6, 3, 8);
  limitation_2(tree, p, 0, 4, 1, 7);

//сверху снизу в зависимости о тусловия
  limitation_3(tree, p, NeighbourRelations::Right, 0, 5, 2, 1);
  limitation_3(tree, p, NeighbourRelations::Right, 0, 0, 3, 2);
  limitation_3(tree, p, NeighbourRelations::DOWN, 1, 4, 1, 8);
//стоит рядом
  limitation_4(tree, p, 1, 5, 3, 7);

//  ПО УМОЛЧАНИЕ знаечние параметров не совпадает
  limitation_5(tree, p);
//  (prop numbers )значение должно быть меньше < N
  limitation_6(tree, p);
//сумма свойств объектов-соседей не должна быть больше K
  limitation_7(tree, p);

  int satcount = bdd_satcount(tree);
  std::cout << satcount << " solutions:" << std::endl;
  if (satcount)
    bdd_allsat(tree, fun);

  bdd_done();

}

