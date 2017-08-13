#ifndef __SYM_EXPR_H__
#define __SYM_EXPR_H__

#include <cassert>
#include <map>
#include <string>

namespace sym_math {

enum operand_index {
  operand_00,
  operand_01,
  operand_02,

  max_operands,

  /* alias */
  operand_left    = operand_00,
  operand_right   = operand_01,
};

enum opcode {
  op_scalar,
  op_variable,
  op_add,
  op_multiply,

  max_operators,
  op_undefined
};

class ExprInfo {
public:
  ExprInfo() {}
  ExprInfo(int64_t v) : m_value(v) {}
  ExprInfo(const std::string& name, int64_t def = 0) : m_value(def), m_var(name) {}
  ExprInfo(const char* name, int64_t def = 0) : m_value(def), m_var(name) {}
  ~ExprInfo() {}

  void value(int64_t v) { m_value = v; }
  int64_t value() const { return m_value; }

  void name(const std::string& n) { m_var = n; }
  void name(const char* n) { m_var = n; }
  std::string name() const { return m_var; }

protected:
  std::string m_var;
  int64_t     m_value;
};

class AbsSymExpr {
public:
  virtual std::string to_string() const = 0;
  virtual bool has_children() = 0;
  virtual void traverse_expr() = 0;

  static std::string opcode_to_string(opcode);

protected:
  ExprInfo m_data;
};

class SymExpr : public AbsSymExpr {
public:
  SymExpr();
  SymExpr(opcode);

  /* create single unit */
  SymExpr(int64_t);
  SymExpr(const std::string&);
  SymExpr(const char*);

  virtual ~SymExpr();

  virtual std::string to_string() const;
  virtual bool has_children() { return true; };
  virtual void traverse_expr();
  
  /* operators */
  virtual SymExpr operator + (const SymExpr&);
  virtual SymExpr operator * (const SymExpr&);

  void operand(operand_index, const SymExpr&);
  bool eval();
protected:
  opcode m_optype;
  std::map<operand_index, SymExpr> m_operands;
};
}; /* sym_math */

#endif /* __SYM_EXPR_H__ */
