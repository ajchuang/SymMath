#include "sym_expr.h"

#include <sstream>

namespace sym_math {
ConstIntExpr::ConstIntExpr(int64_t val) :
    m_value(val) {
}

ConstIntExpr::ConstIntExpr() :
    m_value(0) {
}
    
ConstIntExpr::~ConstIntExpr() {
}

std::string ConstIntExpr::to_string() const {
  std::stringstream ss;
  ss << m_value;
  return ss.str();
}

int64_t ConstIntExpr::value() const {
  return m_value;
}

void ConstIntExpr::value(int64_t v) {
  m_value = v;
}
  
VarExpr::VarExpr(const std::string& name) :
  m_var(name) {
}

VarExpr::~VarExpr() {
}

std::string VarExpr::to_string() const {
  return m_var;
}
  
SymExpr::SymExpr(opcode op) :
    m_optype(op) {
}

SymExpr::~SymExpr() {
}

/* FIXME */
std::string SymExpr::to_string() const {
  if (m_operands.size() == 2) {
    return m_operands[0].to_string() + "+" + m_operands[1].to_stirng();
  } else if (m_operands.size() == 1) {
    return "?" + m_operands[0];
  }
 
  return "":
}

/* FIXME */ 
void SymExpr::operand(operands operand_index, const AbsSymExpr& exp) {
  m_operands.push_back(exp);
  (void)operand_index;
}

}; /* namespce sym_math */
