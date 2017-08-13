#ifndef __SYM_EXPR_H__
#define __SYM_EXPR_H__

#include <map>
#include <string>

namespace sym_math {

enum operands {
  operand_00,
  operand_01,
  operand_02,

  max_operands
};

enum opcode {
  op_add,
  op_multiply,

  max_operators
};

class ConstIntExpr : public AbsSymExpr {
public:
  ConstIntExpr(int64_t val);
  ConstIntExpr();
  virtual ~ConstIntExpr();
  virtual std::string to_string() const;

  int64_t value() const;
  void value(int64_t);

protected:
  int64_t m_value;
};

class VarExpr : public AbsSymExpr {
public:
  VarExpr(const std::string& name);
  virtual ~VarExpr();
  virtual std::string to_string() const;

protected:
  std::string m_name;
};

class SymExpr : public AbsSymExpr {
public:
  SymExpr(opcode);
  virtual ~SymExpr();
  virtual std::string to_string() const;
  
  void operand(uint32_t, AbsSymExpr);

protected:
  opcode m_optype;
  std::vector<AbsSymExpr> m_operands;
};

class AbsSymExpr {
public:
  SymExpr();
  virtual ~SymExpr();
  
  virtual AbsSymExpr operator + (const AbsSymExpr&) = 0;    
  virtual AbsSymExpr operator * (const AbsSymExpr&) = 0;

  virtual std::string to_string() = 0;

protected:
  void traverse_expr();
};
}; /* sym_math */

#endif /* __SYM_EXPR_H__ */
