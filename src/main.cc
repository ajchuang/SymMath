#include "sym_expr.h"

#include <iostream>
#include <string>

using namespace sym_math;

int main() {

  SymExpr a(5);
  SymExpr b("b");

  SymExpr sum = a + b * SymExpr(13);
  std::cout << sum.to_string() << std::endl;

  return 0;
}
