#include "sym_expr.h"

#include <cassert>
#include <sstream>
#include <iostream>
#include <typeinfo>

namespace sym_math {

std::string AbsSymExpr::opcode_to_string(opcode op) {
  switch (op) {
    case op_scalar:   return std::string();
    case op_variable: return std::string();
    case op_add:      return std::string("+");
    case op_multiply: return std::string("*");
    default: {
        assert(false);
        return std::string();
    }
  }
}

SymExpr::SymExpr() :
    m_optype(op_undefined) {
}

SymExpr::SymExpr(opcode op) :
    m_optype(op) {
}

SymExpr::SymExpr(int64_t v) :
    m_optype(op_scalar) {
  m_data.value(v); 
}

SymExpr::SymExpr(const std::string& var) :
    m_optype(op_variable) {
  m_data.name(var); 
}

SymExpr::SymExpr(const char* var) :
    m_optype(op_variable) {
  m_data.name(var); 
}

SymExpr::~SymExpr() {
}

/* FIXME */
std::string SymExpr::to_string() const {
  /* retrieve the operator string */
  std::string operator_string(opcode_to_string(m_optype));
  std::map<operand_index, SymExpr>::const_iterator it;

  if (m_operands.size() == 0) {
    switch (m_optype) {
      case op_scalar: {
          std::stringstream ss;
          ss << m_data.value();
          return ss.str();
      }
      case op_variable: {
          return m_data.name();
      }
      default: {
          assert(false);
          return ""; 
      }
    }

  } else if (m_operands.count(operand_left) == 1) {
    if (m_operands.count(operand_right) == 1) {
      it = m_operands.find(operand_left);
      std::string op_left(it->second.to_string());

      it = m_operands.find(operand_right);
      std::string op_right(it->second.to_string());

      return
          "(" + 
          op_right + operator_string + op_left +
          ")";
    } else {
      it = m_operands.find(operand_left);
      std::string op_left(it->second.to_string());
      return "(" + operator_string + op_left + ") ";
    }
  }

  return "";
}
  
SymExpr SymExpr::operator + (const SymExpr& rhs) {
  if (m_optype == op_scalar && rhs.m_optype == op_scalar) {
    SymExpr expr(op_scalar);
    expr.m_data.value(m_data.value() + rhs.m_data.value());
    return expr;
  } else {
    SymExpr expr(op_add);
    expr.operand(operand_left,  *this);
    expr.operand(operand_right, rhs);
    return expr;
  }
}

SymExpr SymExpr::operator * (const SymExpr& rhs) {
  if (m_optype == op_scalar && rhs.m_optype == op_scalar) {
    SymExpr expr(op_scalar);
    expr.m_data.value(m_data.value() * rhs.m_data.value());
    return expr;
  } else {
    SymExpr expr(op_multiply);
    expr.operand(operand_left,  *this);
    expr.operand(operand_right, rhs);
    return expr;
  }
}

void SymExpr::operand(operand_index op_index, const SymExpr& exp) {
  if (op_index < max_operands && op_index >= operand_left) {
    m_operands[op_index] = exp;
  } else {
    std::cerr << "operand index out of range (" << op_index << ")" << std::endl;
  }
}

bool SymExpr::eval() {
}

/* FIXME: recursive. should be replaced by a iterative one */
void SymExpr::traverse_expr() {
  std::cout << "SymExpr: " << m_optype << std::endl;
  std::map<operand_index, SymExpr>::iterator it;
  for (it = m_operands.begin(); it != m_operands.end(); ++it) {
    it->second.traverse_expr();
  }
}

}; /* namespce sym_math */
