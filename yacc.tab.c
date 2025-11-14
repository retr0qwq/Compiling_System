// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.

// "%code top" blocks.
#line 31 "frontend/parser/yacc.y"

    #include <iostream>

    #include <frontend/parser/parser.h>
    #include <frontend/parser/location.hh>
    #include <frontend/parser/scanner.h>
    #include <frontend/parser/yacc.h>

    using namespace FE;
    using namespace FE::AST;

    static YaccParser::symbol_type yylex(Scanner& scanner, Parser &parser)
    {
        (void)parser;
        return scanner.nextToken(); 
    }

    extern size_t errCnt;

#line 59 "yacc.tab.c"




#include "yacc.tab.h"




#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 4 "frontend/parser/yacc.y"
namespace  FE  {
#line 159 "yacc.tab.c"

  /// Build a parser object.
   YaccParser :: YaccParser  (FE::Scanner& scanner_yyarg, FE::Parser& parser_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      scanner (scanner_yyarg),
      parser (parser_yyarg)
  {}

   YaccParser ::~ YaccParser  ()
  {}

   YaccParser ::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/



  // by_state.
   YaccParser ::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

   YaccParser ::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
   YaccParser ::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
   YaccParser ::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

   YaccParser ::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

   YaccParser ::symbol_kind_type
   YaccParser ::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

   YaccParser ::stack_symbol_type::stack_symbol_type ()
  {}

   YaccParser ::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_ASSIGN_EXPR: // ASSIGN_EXPR
      case symbol_kind::S_EXPR: // EXPR
      case symbol_kind::S_NOCOMMA_EXPR: // NOCOMMA_EXPR
      case symbol_kind::S_LOGICAL_OR_EXPR: // LOGICAL_OR_EXPR
      case symbol_kind::S_LOGICAL_AND_EXPR: // LOGICAL_AND_EXPR
      case symbol_kind::S_EQUALITY_EXPR: // EQUALITY_EXPR
      case symbol_kind::S_RELATIONAL_EXPR: // RELATIONAL_EXPR
      case symbol_kind::S_ADDSUB_EXPR: // ADDSUB_EXPR
      case symbol_kind::S_MULDIV_EXPR: // MULDIV_EXPR
      case symbol_kind::S_UNARY_EXPR: // UNARY_EXPR
      case symbol_kind::S_BASIC_EXPR: // BASIC_EXPR
      case symbol_kind::S_FUNC_CALL_EXPR: // FUNC_CALL_EXPR
      case symbol_kind::S_ARRAY_DIMENSION_EXPR: // ARRAY_DIMENSION_EXPR
      case symbol_kind::S_LEFT_VAL_EXPR: // LEFT_VAL_EXPR
      case symbol_kind::S_LITERAL_EXPR: // LITERAL_EXPR
        value.YY_MOVE_OR_COPY< FE::AST::ExprNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INITIALIZER: // INITIALIZER
        value.YY_MOVE_OR_COPY< FE::AST::InitDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_UNARY_OP: // UNARY_OP
        value.YY_MOVE_OR_COPY< FE::AST::Operator > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_PARAM_DECLARATOR: // PARAM_DECLARATOR
        value.YY_MOVE_OR_COPY< FE::AST::ParamDeclarator* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_PROGRAM: // PROGRAM
        value.YY_MOVE_OR_COPY< FE::AST::Root* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_STMT: // STMT
      case symbol_kind::S_CONTINUE_STMT: // CONTINUE_STMT
      case symbol_kind::S_EXPR_STMT: // EXPR_STMT
      case symbol_kind::S_VAR_DECL_STMT: // VAR_DECL_STMT
      case symbol_kind::S_FUNC_BODY: // FUNC_BODY
      case symbol_kind::S_FUNC_DECL_STMT: // FUNC_DECL_STMT
      case symbol_kind::S_FOR_STMT: // FOR_STMT
      case symbol_kind::S_IF_STMT: // IF_STMT
      case symbol_kind::S_BLOCK_STMT: // BLOCK_STMT
      case symbol_kind::S_RETURN_STMT: // RETURN_STMT
      case symbol_kind::S_BREAK_STMT: // BREAK_STMT
      case symbol_kind::S_WHILE_STMT: // WHILE_STMT
        value.YY_MOVE_OR_COPY< FE::AST::StmtNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TYPE: // TYPE
        value.YY_MOVE_OR_COPY< FE::AST::Type* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_VAR_DECLARATION: // VAR_DECLARATION
        value.YY_MOVE_OR_COPY< FE::AST::VarDeclaration* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_VAR_DECLARATOR: // VAR_DECLARATOR
        value.YY_MOVE_OR_COPY< FE::AST::VarDeclarator* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FLOAT_CONST: // FLOAT_CONST
        value.YY_MOVE_OR_COPY< float > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INT_CONST: // INT_CONST
        value.YY_MOVE_OR_COPY< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_LL_CONST: // LL_CONST
        value.YY_MOVE_OR_COPY< long long > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_STR_CONST: // STR_CONST
      case symbol_kind::S_ERR_TOKEN: // ERR_TOKEN
      case symbol_kind::S_SLASH_COMMENT: // SLASH_COMMENT
      case symbol_kind::S_IDENT: // IDENT
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_EXPR_LIST: // EXPR_LIST
      case symbol_kind::S_ARRAY_DIMENSION_EXPR_LIST: // ARRAY_DIMENSION_EXPR_LIST
        value.YY_MOVE_OR_COPY< std::vector<FE::AST::ExprNode*>* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INITIALIZER_LIST: // INITIALIZER_LIST
        value.YY_MOVE_OR_COPY< std::vector<FE::AST::InitDecl*>* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_PARAM_DECLARATOR_LIST: // PARAM_DECLARATOR_LIST
        value.YY_MOVE_OR_COPY< std::vector<FE::AST::ParamDeclarator*>* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_STMT_LIST: // STMT_LIST
        value.YY_MOVE_OR_COPY< std::vector<FE::AST::StmtNode*>* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_VAR_DECLARATOR_LIST: // VAR_DECLARATOR_LIST
        value.YY_MOVE_OR_COPY< std::vector<FE::AST::VarDeclarator*>* > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

   YaccParser ::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_ASSIGN_EXPR: // ASSIGN_EXPR
      case symbol_kind::S_EXPR: // EXPR
      case symbol_kind::S_NOCOMMA_EXPR: // NOCOMMA_EXPR
      case symbol_kind::S_LOGICAL_OR_EXPR: // LOGICAL_OR_EXPR
      case symbol_kind::S_LOGICAL_AND_EXPR: // LOGICAL_AND_EXPR
      case symbol_kind::S_EQUALITY_EXPR: // EQUALITY_EXPR
      case symbol_kind::S_RELATIONAL_EXPR: // RELATIONAL_EXPR
      case symbol_kind::S_ADDSUB_EXPR: // ADDSUB_EXPR
      case symbol_kind::S_MULDIV_EXPR: // MULDIV_EXPR
      case symbol_kind::S_UNARY_EXPR: // UNARY_EXPR
      case symbol_kind::S_BASIC_EXPR: // BASIC_EXPR
      case symbol_kind::S_FUNC_CALL_EXPR: // FUNC_CALL_EXPR
      case symbol_kind::S_ARRAY_DIMENSION_EXPR: // ARRAY_DIMENSION_EXPR
      case symbol_kind::S_LEFT_VAL_EXPR: // LEFT_VAL_EXPR
      case symbol_kind::S_LITERAL_EXPR: // LITERAL_EXPR
        value.move< FE::AST::ExprNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INITIALIZER: // INITIALIZER
        value.move< FE::AST::InitDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_UNARY_OP: // UNARY_OP
        value.move< FE::AST::Operator > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_PARAM_DECLARATOR: // PARAM_DECLARATOR
        value.move< FE::AST::ParamDeclarator* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_PROGRAM: // PROGRAM
        value.move< FE::AST::Root* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_STMT: // STMT
      case symbol_kind::S_CONTINUE_STMT: // CONTINUE_STMT
      case symbol_kind::S_EXPR_STMT: // EXPR_STMT
      case symbol_kind::S_VAR_DECL_STMT: // VAR_DECL_STMT
      case symbol_kind::S_FUNC_BODY: // FUNC_BODY
      case symbol_kind::S_FUNC_DECL_STMT: // FUNC_DECL_STMT
      case symbol_kind::S_FOR_STMT: // FOR_STMT
      case symbol_kind::S_IF_STMT: // IF_STMT
      case symbol_kind::S_BLOCK_STMT: // BLOCK_STMT
      case symbol_kind::S_RETURN_STMT: // RETURN_STMT
      case symbol_kind::S_BREAK_STMT: // BREAK_STMT
      case symbol_kind::S_WHILE_STMT: // WHILE_STMT
        value.move< FE::AST::StmtNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TYPE: // TYPE
        value.move< FE::AST::Type* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_VAR_DECLARATION: // VAR_DECLARATION
        value.move< FE::AST::VarDeclaration* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_VAR_DECLARATOR: // VAR_DECLARATOR
        value.move< FE::AST::VarDeclarator* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FLOAT_CONST: // FLOAT_CONST
        value.move< float > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INT_CONST: // INT_CONST
        value.move< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_LL_CONST: // LL_CONST
        value.move< long long > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_STR_CONST: // STR_CONST
      case symbol_kind::S_ERR_TOKEN: // ERR_TOKEN
      case symbol_kind::S_SLASH_COMMENT: // SLASH_COMMENT
      case symbol_kind::S_IDENT: // IDENT
        value.move< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_EXPR_LIST: // EXPR_LIST
      case symbol_kind::S_ARRAY_DIMENSION_EXPR_LIST: // ARRAY_DIMENSION_EXPR_LIST
        value.move< std::vector<FE::AST::ExprNode*>* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INITIALIZER_LIST: // INITIALIZER_LIST
        value.move< std::vector<FE::AST::InitDecl*>* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_PARAM_DECLARATOR_LIST: // PARAM_DECLARATOR_LIST
        value.move< std::vector<FE::AST::ParamDeclarator*>* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_STMT_LIST: // STMT_LIST
        value.move< std::vector<FE::AST::StmtNode*>* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_VAR_DECLARATOR_LIST: // VAR_DECLARATOR_LIST
        value.move< std::vector<FE::AST::VarDeclarator*>* > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
   YaccParser ::stack_symbol_type&
   YaccParser ::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_ASSIGN_EXPR: // ASSIGN_EXPR
      case symbol_kind::S_EXPR: // EXPR
      case symbol_kind::S_NOCOMMA_EXPR: // NOCOMMA_EXPR
      case symbol_kind::S_LOGICAL_OR_EXPR: // LOGICAL_OR_EXPR
      case symbol_kind::S_LOGICAL_AND_EXPR: // LOGICAL_AND_EXPR
      case symbol_kind::S_EQUALITY_EXPR: // EQUALITY_EXPR
      case symbol_kind::S_RELATIONAL_EXPR: // RELATIONAL_EXPR
      case symbol_kind::S_ADDSUB_EXPR: // ADDSUB_EXPR
      case symbol_kind::S_MULDIV_EXPR: // MULDIV_EXPR
      case symbol_kind::S_UNARY_EXPR: // UNARY_EXPR
      case symbol_kind::S_BASIC_EXPR: // BASIC_EXPR
      case symbol_kind::S_FUNC_CALL_EXPR: // FUNC_CALL_EXPR
      case symbol_kind::S_ARRAY_DIMENSION_EXPR: // ARRAY_DIMENSION_EXPR
      case symbol_kind::S_LEFT_VAL_EXPR: // LEFT_VAL_EXPR
      case symbol_kind::S_LITERAL_EXPR: // LITERAL_EXPR
        value.copy< FE::AST::ExprNode* > (that.value);
        break;

      case symbol_kind::S_INITIALIZER: // INITIALIZER
        value.copy< FE::AST::InitDecl* > (that.value);
        break;

      case symbol_kind::S_UNARY_OP: // UNARY_OP
        value.copy< FE::AST::Operator > (that.value);
        break;

      case symbol_kind::S_PARAM_DECLARATOR: // PARAM_DECLARATOR
        value.copy< FE::AST::ParamDeclarator* > (that.value);
        break;

      case symbol_kind::S_PROGRAM: // PROGRAM
        value.copy< FE::AST::Root* > (that.value);
        break;

      case symbol_kind::S_STMT: // STMT
      case symbol_kind::S_CONTINUE_STMT: // CONTINUE_STMT
      case symbol_kind::S_EXPR_STMT: // EXPR_STMT
      case symbol_kind::S_VAR_DECL_STMT: // VAR_DECL_STMT
      case symbol_kind::S_FUNC_BODY: // FUNC_BODY
      case symbol_kind::S_FUNC_DECL_STMT: // FUNC_DECL_STMT
      case symbol_kind::S_FOR_STMT: // FOR_STMT
      case symbol_kind::S_IF_STMT: // IF_STMT
      case symbol_kind::S_BLOCK_STMT: // BLOCK_STMT
      case symbol_kind::S_RETURN_STMT: // RETURN_STMT
      case symbol_kind::S_BREAK_STMT: // BREAK_STMT
      case symbol_kind::S_WHILE_STMT: // WHILE_STMT
        value.copy< FE::AST::StmtNode* > (that.value);
        break;

      case symbol_kind::S_TYPE: // TYPE
        value.copy< FE::AST::Type* > (that.value);
        break;

      case symbol_kind::S_VAR_DECLARATION: // VAR_DECLARATION
        value.copy< FE::AST::VarDeclaration* > (that.value);
        break;

      case symbol_kind::S_VAR_DECLARATOR: // VAR_DECLARATOR
        value.copy< FE::AST::VarDeclarator* > (that.value);
        break;

      case symbol_kind::S_FLOAT_CONST: // FLOAT_CONST
        value.copy< float > (that.value);
        break;

      case symbol_kind::S_INT_CONST: // INT_CONST
        value.copy< int > (that.value);
        break;

      case symbol_kind::S_LL_CONST: // LL_CONST
        value.copy< long long > (that.value);
        break;

      case symbol_kind::S_STR_CONST: // STR_CONST
      case symbol_kind::S_ERR_TOKEN: // ERR_TOKEN
      case symbol_kind::S_SLASH_COMMENT: // SLASH_COMMENT
      case symbol_kind::S_IDENT: // IDENT
        value.copy< std::string > (that.value);
        break;

      case symbol_kind::S_EXPR_LIST: // EXPR_LIST
      case symbol_kind::S_ARRAY_DIMENSION_EXPR_LIST: // ARRAY_DIMENSION_EXPR_LIST
        value.copy< std::vector<FE::AST::ExprNode*>* > (that.value);
        break;

      case symbol_kind::S_INITIALIZER_LIST: // INITIALIZER_LIST
        value.copy< std::vector<FE::AST::InitDecl*>* > (that.value);
        break;

      case symbol_kind::S_PARAM_DECLARATOR_LIST: // PARAM_DECLARATOR_LIST
        value.copy< std::vector<FE::AST::ParamDeclarator*>* > (that.value);
        break;

      case symbol_kind::S_STMT_LIST: // STMT_LIST
        value.copy< std::vector<FE::AST::StmtNode*>* > (that.value);
        break;

      case symbol_kind::S_VAR_DECLARATOR_LIST: // VAR_DECLARATOR_LIST
        value.copy< std::vector<FE::AST::VarDeclarator*>* > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

   YaccParser ::stack_symbol_type&
   YaccParser ::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_ASSIGN_EXPR: // ASSIGN_EXPR
      case symbol_kind::S_EXPR: // EXPR
      case symbol_kind::S_NOCOMMA_EXPR: // NOCOMMA_EXPR
      case symbol_kind::S_LOGICAL_OR_EXPR: // LOGICAL_OR_EXPR
      case symbol_kind::S_LOGICAL_AND_EXPR: // LOGICAL_AND_EXPR
      case symbol_kind::S_EQUALITY_EXPR: // EQUALITY_EXPR
      case symbol_kind::S_RELATIONAL_EXPR: // RELATIONAL_EXPR
      case symbol_kind::S_ADDSUB_EXPR: // ADDSUB_EXPR
      case symbol_kind::S_MULDIV_EXPR: // MULDIV_EXPR
      case symbol_kind::S_UNARY_EXPR: // UNARY_EXPR
      case symbol_kind::S_BASIC_EXPR: // BASIC_EXPR
      case symbol_kind::S_FUNC_CALL_EXPR: // FUNC_CALL_EXPR
      case symbol_kind::S_ARRAY_DIMENSION_EXPR: // ARRAY_DIMENSION_EXPR
      case symbol_kind::S_LEFT_VAL_EXPR: // LEFT_VAL_EXPR
      case symbol_kind::S_LITERAL_EXPR: // LITERAL_EXPR
        value.move< FE::AST::ExprNode* > (that.value);
        break;

      case symbol_kind::S_INITIALIZER: // INITIALIZER
        value.move< FE::AST::InitDecl* > (that.value);
        break;

      case symbol_kind::S_UNARY_OP: // UNARY_OP
        value.move< FE::AST::Operator > (that.value);
        break;

      case symbol_kind::S_PARAM_DECLARATOR: // PARAM_DECLARATOR
        value.move< FE::AST::ParamDeclarator* > (that.value);
        break;

      case symbol_kind::S_PROGRAM: // PROGRAM
        value.move< FE::AST::Root* > (that.value);
        break;

      case symbol_kind::S_STMT: // STMT
      case symbol_kind::S_CONTINUE_STMT: // CONTINUE_STMT
      case symbol_kind::S_EXPR_STMT: // EXPR_STMT
      case symbol_kind::S_VAR_DECL_STMT: // VAR_DECL_STMT
      case symbol_kind::S_FUNC_BODY: // FUNC_BODY
      case symbol_kind::S_FUNC_DECL_STMT: // FUNC_DECL_STMT
      case symbol_kind::S_FOR_STMT: // FOR_STMT
      case symbol_kind::S_IF_STMT: // IF_STMT
      case symbol_kind::S_BLOCK_STMT: // BLOCK_STMT
      case symbol_kind::S_RETURN_STMT: // RETURN_STMT
      case symbol_kind::S_BREAK_STMT: // BREAK_STMT
      case symbol_kind::S_WHILE_STMT: // WHILE_STMT
        value.move< FE::AST::StmtNode* > (that.value);
        break;

      case symbol_kind::S_TYPE: // TYPE
        value.move< FE::AST::Type* > (that.value);
        break;

      case symbol_kind::S_VAR_DECLARATION: // VAR_DECLARATION
        value.move< FE::AST::VarDeclaration* > (that.value);
        break;

      case symbol_kind::S_VAR_DECLARATOR: // VAR_DECLARATOR
        value.move< FE::AST::VarDeclarator* > (that.value);
        break;

      case symbol_kind::S_FLOAT_CONST: // FLOAT_CONST
        value.move< float > (that.value);
        break;

      case symbol_kind::S_INT_CONST: // INT_CONST
        value.move< int > (that.value);
        break;

      case symbol_kind::S_LL_CONST: // LL_CONST
        value.move< long long > (that.value);
        break;

      case symbol_kind::S_STR_CONST: // STR_CONST
      case symbol_kind::S_ERR_TOKEN: // ERR_TOKEN
      case symbol_kind::S_SLASH_COMMENT: // SLASH_COMMENT
      case symbol_kind::S_IDENT: // IDENT
        value.move< std::string > (that.value);
        break;

      case symbol_kind::S_EXPR_LIST: // EXPR_LIST
      case symbol_kind::S_ARRAY_DIMENSION_EXPR_LIST: // ARRAY_DIMENSION_EXPR_LIST
        value.move< std::vector<FE::AST::ExprNode*>* > (that.value);
        break;

      case symbol_kind::S_INITIALIZER_LIST: // INITIALIZER_LIST
        value.move< std::vector<FE::AST::InitDecl*>* > (that.value);
        break;

      case symbol_kind::S_PARAM_DECLARATOR_LIST: // PARAM_DECLARATOR_LIST
        value.move< std::vector<FE::AST::ParamDeclarator*>* > (that.value);
        break;

      case symbol_kind::S_STMT_LIST: // STMT_LIST
        value.move< std::vector<FE::AST::StmtNode*>* > (that.value);
        break;

      case symbol_kind::S_VAR_DECLARATOR_LIST: // VAR_DECLARATOR_LIST
        value.move< std::vector<FE::AST::VarDeclarator*>* > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
   YaccParser ::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
   YaccParser ::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
   YaccParser ::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
   YaccParser ::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
   YaccParser ::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
   YaccParser ::debug_stream () const
  {
    return *yycdebug_;
  }

  void
   YaccParser ::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


   YaccParser ::debug_level_type
   YaccParser ::debug_level () const
  {
    return yydebug_;
  }

  void
   YaccParser ::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

   YaccParser ::state_type
   YaccParser ::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
   YaccParser ::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
   YaccParser ::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
   YaccParser ::operator() ()
  {
    return parse ();
  }

  int
   YaccParser ::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex (scanner, parser));
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_ASSIGN_EXPR: // ASSIGN_EXPR
      case symbol_kind::S_EXPR: // EXPR
      case symbol_kind::S_NOCOMMA_EXPR: // NOCOMMA_EXPR
      case symbol_kind::S_LOGICAL_OR_EXPR: // LOGICAL_OR_EXPR
      case symbol_kind::S_LOGICAL_AND_EXPR: // LOGICAL_AND_EXPR
      case symbol_kind::S_EQUALITY_EXPR: // EQUALITY_EXPR
      case symbol_kind::S_RELATIONAL_EXPR: // RELATIONAL_EXPR
      case symbol_kind::S_ADDSUB_EXPR: // ADDSUB_EXPR
      case symbol_kind::S_MULDIV_EXPR: // MULDIV_EXPR
      case symbol_kind::S_UNARY_EXPR: // UNARY_EXPR
      case symbol_kind::S_BASIC_EXPR: // BASIC_EXPR
      case symbol_kind::S_FUNC_CALL_EXPR: // FUNC_CALL_EXPR
      case symbol_kind::S_ARRAY_DIMENSION_EXPR: // ARRAY_DIMENSION_EXPR
      case symbol_kind::S_LEFT_VAL_EXPR: // LEFT_VAL_EXPR
      case symbol_kind::S_LITERAL_EXPR: // LITERAL_EXPR
        yylhs.value.emplace< FE::AST::ExprNode* > ();
        break;

      case symbol_kind::S_INITIALIZER: // INITIALIZER
        yylhs.value.emplace< FE::AST::InitDecl* > ();
        break;

      case symbol_kind::S_UNARY_OP: // UNARY_OP
        yylhs.value.emplace< FE::AST::Operator > ();
        break;

      case symbol_kind::S_PARAM_DECLARATOR: // PARAM_DECLARATOR
        yylhs.value.emplace< FE::AST::ParamDeclarator* > ();
        break;

      case symbol_kind::S_PROGRAM: // PROGRAM
        yylhs.value.emplace< FE::AST::Root* > ();
        break;

      case symbol_kind::S_STMT: // STMT
      case symbol_kind::S_CONTINUE_STMT: // CONTINUE_STMT
      case symbol_kind::S_EXPR_STMT: // EXPR_STMT
      case symbol_kind::S_VAR_DECL_STMT: // VAR_DECL_STMT
      case symbol_kind::S_FUNC_BODY: // FUNC_BODY
      case symbol_kind::S_FUNC_DECL_STMT: // FUNC_DECL_STMT
      case symbol_kind::S_FOR_STMT: // FOR_STMT
      case symbol_kind::S_IF_STMT: // IF_STMT
      case symbol_kind::S_BLOCK_STMT: // BLOCK_STMT
      case symbol_kind::S_RETURN_STMT: // RETURN_STMT
      case symbol_kind::S_BREAK_STMT: // BREAK_STMT
      case symbol_kind::S_WHILE_STMT: // WHILE_STMT
        yylhs.value.emplace< FE::AST::StmtNode* > ();
        break;

      case symbol_kind::S_TYPE: // TYPE
        yylhs.value.emplace< FE::AST::Type* > ();
        break;

      case symbol_kind::S_VAR_DECLARATION: // VAR_DECLARATION
        yylhs.value.emplace< FE::AST::VarDeclaration* > ();
        break;

      case symbol_kind::S_VAR_DECLARATOR: // VAR_DECLARATOR
        yylhs.value.emplace< FE::AST::VarDeclarator* > ();
        break;

      case symbol_kind::S_FLOAT_CONST: // FLOAT_CONST
        yylhs.value.emplace< float > ();
        break;

      case symbol_kind::S_INT_CONST: // INT_CONST
        yylhs.value.emplace< int > ();
        break;

      case symbol_kind::S_LL_CONST: // LL_CONST
        yylhs.value.emplace< long long > ();
        break;

      case symbol_kind::S_STR_CONST: // STR_CONST
      case symbol_kind::S_ERR_TOKEN: // ERR_TOKEN
      case symbol_kind::S_SLASH_COMMENT: // SLASH_COMMENT
      case symbol_kind::S_IDENT: // IDENT
        yylhs.value.emplace< std::string > ();
        break;

      case symbol_kind::S_EXPR_LIST: // EXPR_LIST
      case symbol_kind::S_ARRAY_DIMENSION_EXPR_LIST: // ARRAY_DIMENSION_EXPR_LIST
        yylhs.value.emplace< std::vector<FE::AST::ExprNode*>* > ();
        break;

      case symbol_kind::S_INITIALIZER_LIST: // INITIALIZER_LIST
        yylhs.value.emplace< std::vector<FE::AST::InitDecl*>* > ();
        break;

      case symbol_kind::S_PARAM_DECLARATOR_LIST: // PARAM_DECLARATOR_LIST
        yylhs.value.emplace< std::vector<FE::AST::ParamDeclarator*>* > ();
        break;

      case symbol_kind::S_STMT_LIST: // STMT_LIST
        yylhs.value.emplace< std::vector<FE::AST::StmtNode*>* > ();
        break;

      case symbol_kind::S_VAR_DECLARATOR_LIST: // VAR_DECLARATOR_LIST
        yylhs.value.emplace< std::vector<FE::AST::VarDeclarator*>* > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // PROGRAM: STMT_LIST
#line 140 "frontend/parser/yacc.y"
              {
        yylhs.value.as < FE::AST::Root* > () = new Root(yystack_[0].value.as < std::vector<FE::AST::StmtNode*>* > ());
        parser.ast = yylhs.value.as < FE::AST::Root* > ();
    }
#line 1062 "yacc.tab.c"
    break;

  case 3: // PROGRAM: PROGRAM END
#line 144 "frontend/parser/yacc.y"
                  {
        YYACCEPT;
    }
#line 1070 "yacc.tab.c"
    break;

  case 4: // STMT_LIST: STMT
#line 150 "frontend/parser/yacc.y"
         {
        yylhs.value.as < std::vector<FE::AST::StmtNode*>* > () = new std::vector<StmtNode*>();
        if (yystack_[0].value.as < FE::AST::StmtNode* > ()) yylhs.value.as < std::vector<FE::AST::StmtNode*>* > ()->push_back(yystack_[0].value.as < FE::AST::StmtNode* > ());
    }
#line 1079 "yacc.tab.c"
    break;

  case 5: // STMT_LIST: STMT_LIST STMT
#line 154 "frontend/parser/yacc.y"
                     {
        yylhs.value.as < std::vector<FE::AST::StmtNode*>* > () = yystack_[1].value.as < std::vector<FE::AST::StmtNode*>* > ();
        if (yystack_[0].value.as < FE::AST::StmtNode* > ()) yylhs.value.as < std::vector<FE::AST::StmtNode*>* > ()->push_back(yystack_[0].value.as < FE::AST::StmtNode* > ());
    }
#line 1088 "yacc.tab.c"
    break;

  case 6: // STMT: EXPR_STMT
#line 161 "frontend/parser/yacc.y"
              {
        yylhs.value.as < FE::AST::StmtNode* > () = yystack_[0].value.as < FE::AST::StmtNode* > ();
    }
#line 1096 "yacc.tab.c"
    break;

  case 7: // STMT: VAR_DECL_STMT
#line 164 "frontend/parser/yacc.y"
                    {
        yylhs.value.as < FE::AST::StmtNode* > () = yystack_[0].value.as < FE::AST::StmtNode* > ();
    }
#line 1104 "yacc.tab.c"
    break;

  case 8: // STMT: FUNC_DECL_STMT
#line 167 "frontend/parser/yacc.y"
                     {
        yylhs.value.as < FE::AST::StmtNode* > () = yystack_[0].value.as < FE::AST::StmtNode* > ();
    }
#line 1112 "yacc.tab.c"
    break;

  case 9: // STMT: FOR_STMT
#line 170 "frontend/parser/yacc.y"
               {
        yylhs.value.as < FE::AST::StmtNode* > () = yystack_[0].value.as < FE::AST::StmtNode* > ();
    }
#line 1120 "yacc.tab.c"
    break;

  case 10: // STMT: IF_STMT
#line 173 "frontend/parser/yacc.y"
              {
        yylhs.value.as < FE::AST::StmtNode* > () = yystack_[0].value.as < FE::AST::StmtNode* > ();
    }
#line 1128 "yacc.tab.c"
    break;

  case 11: // STMT: CONTINUE_STMT
#line 176 "frontend/parser/yacc.y"
                    {
        yylhs.value.as < FE::AST::StmtNode* > () = yystack_[0].value.as < FE::AST::StmtNode* > ();
    }
#line 1136 "yacc.tab.c"
    break;

  case 12: // STMT: SEMICOLON
#line 179 "frontend/parser/yacc.y"
                {
        yylhs.value.as < FE::AST::StmtNode* > () = nullptr;
    }
#line 1144 "yacc.tab.c"
    break;

  case 13: // STMT: SLASH_COMMENT
#line 182 "frontend/parser/yacc.y"
                    {
        yylhs.value.as < FE::AST::StmtNode* > () = nullptr;
    }
#line 1152 "yacc.tab.c"
    break;

  case 14: // STMT: BLOCK_STMT
#line 186 "frontend/parser/yacc.y"
                 { yylhs.value.as < FE::AST::StmtNode* > () = yystack_[0].value.as < FE::AST::StmtNode* > (); }
#line 1158 "yacc.tab.c"
    break;

  case 15: // STMT: RETURN_STMT
#line 187 "frontend/parser/yacc.y"
                  { yylhs.value.as < FE::AST::StmtNode* > () = yystack_[0].value.as < FE::AST::StmtNode* > (); }
#line 1164 "yacc.tab.c"
    break;

  case 16: // STMT: WHILE_STMT
#line 188 "frontend/parser/yacc.y"
                 { yylhs.value.as < FE::AST::StmtNode* > () = yystack_[0].value.as < FE::AST::StmtNode* > (); }
#line 1170 "yacc.tab.c"
    break;

  case 17: // STMT: BREAK_STMT
#line 189 "frontend/parser/yacc.y"
                 { yylhs.value.as < FE::AST::StmtNode* > () = yystack_[0].value.as < FE::AST::StmtNode* > (); }
#line 1176 "yacc.tab.c"
    break;

  case 18: // CONTINUE_STMT: CONTINUE SEMICOLON
#line 193 "frontend/parser/yacc.y"
                       {
        yylhs.value.as < FE::AST::StmtNode* > () = new ContinueStmt(yystack_[1].location.begin.line, yystack_[1].location.begin.column);
    }
#line 1184 "yacc.tab.c"
    break;

  case 19: // EXPR_STMT: EXPR SEMICOLON
#line 199 "frontend/parser/yacc.y"
                   {
        yylhs.value.as < FE::AST::StmtNode* > () = new ExprStmt(yystack_[1].value.as < FE::AST::ExprNode* > (), yystack_[1].location.begin.line, yystack_[1].location.begin.column);
    }
#line 1192 "yacc.tab.c"
    break;

  case 20: // VAR_DECLARATION: TYPE VAR_DECLARATOR_LIST
#line 205 "frontend/parser/yacc.y"
                             {
        yylhs.value.as < FE::AST::VarDeclaration* > () = new VarDeclaration(yystack_[1].value.as < FE::AST::Type* > (), yystack_[0].value.as < std::vector<FE::AST::VarDeclarator*>* > (), false, yystack_[1].location.begin.line, yystack_[1].location.begin.column);
    }
#line 1200 "yacc.tab.c"
    break;

  case 21: // VAR_DECLARATION: CONST TYPE VAR_DECLARATOR_LIST
#line 208 "frontend/parser/yacc.y"
                                     {
        yylhs.value.as < FE::AST::VarDeclaration* > () = new VarDeclaration(yystack_[1].value.as < FE::AST::Type* > (), yystack_[0].value.as < std::vector<FE::AST::VarDeclarator*>* > (), true, yystack_[2].location.begin.line, yystack_[2].location.begin.column);
    }
#line 1208 "yacc.tab.c"
    break;

  case 22: // VAR_DECL_STMT: VAR_DECLARATION SEMICOLON
#line 215 "frontend/parser/yacc.y"
                             {
        yylhs.value.as < FE::AST::StmtNode* > () = new VarDeclStmt(yystack_[1].value.as < FE::AST::VarDeclaration* > (), yystack_[1].location.begin.line, yystack_[1].location.begin.column);

    }
#line 1217 "yacc.tab.c"
    break;

  case 23: // FUNC_BODY: LBRACE RBRACE
#line 222 "frontend/parser/yacc.y"
                  {
        yylhs.value.as < FE::AST::StmtNode* > () = nullptr;
    }
#line 1225 "yacc.tab.c"
    break;

  case 24: // FUNC_BODY: LBRACE STMT_LIST RBRACE
#line 225 "frontend/parser/yacc.y"
                              {
        if (!yystack_[1].value.as < std::vector<FE::AST::StmtNode*>* > () || yystack_[1].value.as < std::vector<FE::AST::StmtNode*>* > ()->empty())
        {
            yylhs.value.as < FE::AST::StmtNode* > () = nullptr;
            delete yystack_[1].value.as < std::vector<FE::AST::StmtNode*>* > ();
        }
        else if (yystack_[1].value.as < std::vector<FE::AST::StmtNode*>* > ()->size() == 1)
        {
            yylhs.value.as < FE::AST::StmtNode* > () = (*yystack_[1].value.as < std::vector<FE::AST::StmtNode*>* > ())[0];
            delete yystack_[1].value.as < std::vector<FE::AST::StmtNode*>* > ();
        }
        else yylhs.value.as < FE::AST::StmtNode* > () = new BlockStmt(yystack_[1].value.as < std::vector<FE::AST::StmtNode*>* > (), yystack_[2].location.begin.line, yystack_[2].location.begin.column);
    }
#line 1243 "yacc.tab.c"
    break;

  case 25: // FUNC_DECL_STMT: TYPE IDENT LPAREN PARAM_DECLARATOR_LIST RPAREN FUNC_BODY
#line 241 "frontend/parser/yacc.y"
                                                             {
        Entry* entry = Entry::getEntry(yystack_[4].value.as < std::string > ());
        yylhs.value.as < FE::AST::StmtNode* > () = new FuncDeclStmt(yystack_[5].value.as < FE::AST::Type* > (), entry, yystack_[2].value.as < std::vector<FE::AST::ParamDeclarator*>* > (), yystack_[0].value.as < FE::AST::StmtNode* > (), yystack_[5].location.begin.line, yystack_[5].location.begin.column);
    }
#line 1252 "yacc.tab.c"
    break;

  case 26: // FOR_STMT: FOR LPAREN VAR_DECLARATION SEMICOLON EXPR SEMICOLON EXPR RPAREN STMT
#line 248 "frontend/parser/yacc.y"
                                                                         {
        VarDeclStmt* initStmt = new VarDeclStmt(yystack_[6].value.as < FE::AST::VarDeclaration* > (), yystack_[6].location.begin.line, yystack_[6].location.begin.column);
        yylhs.value.as < FE::AST::StmtNode* > () = new ForStmt(initStmt, yystack_[4].value.as < FE::AST::ExprNode* > (), yystack_[2].value.as < FE::AST::ExprNode* > (), yystack_[0].value.as < FE::AST::StmtNode* > (), yystack_[8].location.begin.line, yystack_[8].location.begin.column);
    }
#line 1261 "yacc.tab.c"
    break;

  case 27: // FOR_STMT: FOR LPAREN EXPR SEMICOLON EXPR SEMICOLON EXPR RPAREN STMT
#line 252 "frontend/parser/yacc.y"
                                                                {
        StmtNode* initStmt = new ExprStmt(yystack_[6].value.as < FE::AST::ExprNode* > (), yystack_[6].value.as < FE::AST::ExprNode* > ()->line_num, yystack_[6].value.as < FE::AST::ExprNode* > ()->col_num);
        yylhs.value.as < FE::AST::StmtNode* > () = new ForStmt(initStmt, yystack_[4].value.as < FE::AST::ExprNode* > (), yystack_[2].value.as < FE::AST::ExprNode* > (), yystack_[0].value.as < FE::AST::StmtNode* > (), yystack_[8].location.begin.line, yystack_[8].location.begin.column);
    }
#line 1270 "yacc.tab.c"
    break;

  case 28: // IF_STMT: IF LPAREN EXPR RPAREN STMT
#line 261 "frontend/parser/yacc.y"
    {
        yylhs.value.as < FE::AST::StmtNode* > () = new IfStmt(yystack_[2].value.as < FE::AST::ExprNode* > (), yystack_[0].value.as < FE::AST::StmtNode* > (), nullptr, yystack_[4].location.begin.line, yystack_[4].location.begin.column);
    }
#line 1278 "yacc.tab.c"
    break;

  case 29: // IF_STMT: IF LPAREN EXPR RPAREN STMT ELSE STMT
#line 265 "frontend/parser/yacc.y"
    {
        yylhs.value.as < FE::AST::StmtNode* > () = new IfStmt(yystack_[4].value.as < FE::AST::ExprNode* > (), yystack_[2].value.as < FE::AST::StmtNode* > (), yystack_[0].value.as < FE::AST::StmtNode* > (), yystack_[6].location.begin.line, yystack_[6].location.begin.column);
    }
#line 1286 "yacc.tab.c"
    break;

  case 30: // BLOCK_STMT: LBRACE RBRACE
#line 273 "frontend/parser/yacc.y"
                  {
        yylhs.value.as < FE::AST::StmtNode* > () = nullptr;
    }
#line 1294 "yacc.tab.c"
    break;

  case 31: // BLOCK_STMT: LBRACE STMT_LIST RBRACE
#line 276 "frontend/parser/yacc.y"
                              {
        if (!yystack_[1].value.as < std::vector<FE::AST::StmtNode*>* > () || yystack_[1].value.as < std::vector<FE::AST::StmtNode*>* > ()->empty())
        {
            yylhs.value.as < FE::AST::StmtNode* > () = nullptr;
            delete yystack_[1].value.as < std::vector<FE::AST::StmtNode*>* > ();
        }
        else if (yystack_[1].value.as < std::vector<FE::AST::StmtNode*>* > ()->size() == 1)
        {
            yylhs.value.as < FE::AST::StmtNode* > () = (*yystack_[1].value.as < std::vector<FE::AST::StmtNode*>* > ())[0];
            delete yystack_[1].value.as < std::vector<FE::AST::StmtNode*>* > ();
        }
        else yylhs.value.as < FE::AST::StmtNode* > () = new BlockStmt(yystack_[1].value.as < std::vector<FE::AST::StmtNode*>* > (), yystack_[2].location.begin.line, yystack_[2].location.begin.column);
    }
#line 1312 "yacc.tab.c"
    break;

  case 32: // RETURN_STMT: RETURN SEMICOLON
#line 292 "frontend/parser/yacc.y"
                     {
        yylhs.value.as < FE::AST::StmtNode* > () = new ReturnStmt(nullptr, yystack_[1].location.begin.line, yystack_[1].location.begin.column);
    }
#line 1320 "yacc.tab.c"
    break;

  case 33: // RETURN_STMT: RETURN EXPR SEMICOLON
#line 295 "frontend/parser/yacc.y"
                            {
        yylhs.value.as < FE::AST::StmtNode* > () = new ReturnStmt(yystack_[1].value.as < FE::AST::ExprNode* > (), yystack_[2].location.begin.line, yystack_[2].location.begin.column);
    }
#line 1328 "yacc.tab.c"
    break;

  case 34: // BREAK_STMT: BREAK SEMICOLON
#line 301 "frontend/parser/yacc.y"
                    {
        yylhs.value.as < FE::AST::StmtNode* > () = new BreakStmt(yystack_[1].location.begin.line, yystack_[1].location.begin.column);
    }
#line 1336 "yacc.tab.c"
    break;

  case 35: // WHILE_STMT: WHILE LPAREN EXPR RPAREN STMT
#line 307 "frontend/parser/yacc.y"
                                  {
        yylhs.value.as < FE::AST::StmtNode* > () = new WhileStmt(yystack_[2].value.as < FE::AST::ExprNode* > (), yystack_[0].value.as < FE::AST::StmtNode* > (), yystack_[4].location.begin.line, yystack_[4].location.begin.column);
    }
#line 1344 "yacc.tab.c"
    break;

  case 36: // PARAM_DECLARATOR: TYPE IDENT
#line 313 "frontend/parser/yacc.y"
               {
        Entry* entry = Entry::getEntry(yystack_[0].value.as < std::string > ());
        yylhs.value.as < FE::AST::ParamDeclarator* > () = new ParamDeclarator(yystack_[1].value.as < FE::AST::Type* > (), entry, nullptr, yystack_[1].location.begin.line, yystack_[1].location.begin.column);
    }
#line 1353 "yacc.tab.c"
    break;

  case 37: // PARAM_DECLARATOR: TYPE IDENT LBRACKET RBRACKET
#line 317 "frontend/parser/yacc.y"
                                   {
        std::vector<ExprNode*>* dim = new std::vector<ExprNode*>();
        dim->emplace_back(new LiteralExpr(-1, yystack_[1].location.begin.line, yystack_[1].location.begin.column));
        Entry* entry = Entry::getEntry(yystack_[2].value.as < std::string > ());
        yylhs.value.as < FE::AST::ParamDeclarator* > () = new ParamDeclarator(yystack_[3].value.as < FE::AST::Type* > (), entry, dim, yystack_[3].location.begin.line, yystack_[3].location.begin.column);
    }
#line 1364 "yacc.tab.c"
    break;

  case 38: // PARAM_DECLARATOR: TYPE IDENT LBRACKET RBRACKET ARRAY_DIMENSION_EXPR_LIST
#line 324 "frontend/parser/yacc.y"
                                                             {
        std::vector<ExprNode*>* dim = yystack_[0].value.as < std::vector<FE::AST::ExprNode*>* > ();
        dim->insert(dim->begin(), new LiteralExpr(-1, yystack_[2].location.begin.line, yystack_[2].location.begin.column)); // 首维省略
        Entry* entry = Entry::getEntry(yystack_[3].value.as < std::string > ());
        yylhs.value.as < FE::AST::ParamDeclarator* > () = new ParamDeclarator(yystack_[4].value.as < FE::AST::Type* > (), entry, dim, yystack_[4].location.begin.line, yystack_[4].location.begin.column);
    }
#line 1375 "yacc.tab.c"
    break;

  case 39: // PARAM_DECLARATOR: TYPE IDENT ARRAY_DIMENSION_EXPR_LIST
#line 330 "frontend/parser/yacc.y"
                                           {
        Entry* entry = Entry::getEntry(yystack_[1].value.as < std::string > ());
        yylhs.value.as < FE::AST::ParamDeclarator* > () = new ParamDeclarator(yystack_[2].value.as < FE::AST::Type* > (), entry, yystack_[0].value.as < std::vector<FE::AST::ExprNode*>* > (), yystack_[2].location.begin.line, yystack_[2].location.begin.column);
    }
#line 1384 "yacc.tab.c"
    break;

  case 40: // PARAM_DECLARATOR_LIST: %empty
#line 337 "frontend/parser/yacc.y"
                    {
            yylhs.value.as < std::vector<FE::AST::ParamDeclarator*>* > () = new std::vector<ParamDeclarator*>();
        }
#line 1392 "yacc.tab.c"
    break;

  case 41: // PARAM_DECLARATOR_LIST: PARAM_DECLARATOR
#line 340 "frontend/parser/yacc.y"
                       {
        yylhs.value.as < std::vector<FE::AST::ParamDeclarator*>* > () = new std::vector<FE::AST::ParamDeclarator*>();
        yylhs.value.as < std::vector<FE::AST::ParamDeclarator*>* > ()->push_back(yystack_[0].value.as < FE::AST::ParamDeclarator* > ());
    }
#line 1401 "yacc.tab.c"
    break;

  case 42: // PARAM_DECLARATOR_LIST: PARAM_DECLARATOR_LIST COMMA PARAM_DECLARATOR
#line 344 "frontend/parser/yacc.y"
                                                   {
        yylhs.value.as < std::vector<FE::AST::ParamDeclarator*>* > () = yystack_[2].value.as < std::vector<FE::AST::ParamDeclarator*>* > ();
        yylhs.value.as < std::vector<FE::AST::ParamDeclarator*>* > ()->push_back(yystack_[0].value.as < FE::AST::ParamDeclarator* > ());
    }
#line 1410 "yacc.tab.c"
    break;

  case 43: // VAR_DECLARATOR: IDENT
#line 353 "frontend/parser/yacc.y"
          {
        Entry* entry = Entry::getEntry(yystack_[0].value.as < std::string > ());
        yylhs.value.as < FE::AST::VarDeclarator* > () = new VarDeclarator(new LeftValExpr(entry), nullptr, yystack_[0].location.begin.line, yystack_[0].location.begin.column);
    }
#line 1419 "yacc.tab.c"
    break;

  case 44: // VAR_DECLARATOR: IDENT ASSIGN INITIALIZER
#line 357 "frontend/parser/yacc.y"
                              {
        Entry* entry = Entry::getEntry(yystack_[2].value.as < std::string > ());
        yylhs.value.as < FE::AST::VarDeclarator* > () = new VarDeclarator(new LeftValExpr(entry), yystack_[0].value.as < FE::AST::InitDecl* > (), yystack_[2].location.begin.line, yystack_[2].location.begin.column);
    }
#line 1428 "yacc.tab.c"
    break;

  case 45: // VAR_DECLARATOR: IDENT LBRACKET RBRACKET
#line 361 "frontend/parser/yacc.y"
                              {
        std::vector<ExprNode*>* dims = new std::vector<ExprNode*>();
        dims->emplace_back(new LiteralExpr(-1, yystack_[1].location.begin.line, yystack_[1].location.begin.column));
        Entry* entry = Entry::getEntry(yystack_[2].value.as < std::string > ());
        yylhs.value.as < FE::AST::VarDeclarator* > () = new VarDeclarator(new LeftValExpr(entry, dims), nullptr, yystack_[2].location.begin.line, yystack_[2].location.begin.column);
    }
#line 1439 "yacc.tab.c"
    break;

  case 46: // VAR_DECLARATOR: IDENT LBRACKET RBRACKET ARRAY_DIMENSION_EXPR_LIST
#line 367 "frontend/parser/yacc.y"
                                                        {
        std::vector<ExprNode*>* dims = yystack_[0].value.as < std::vector<FE::AST::ExprNode*>* > ();
        dims->insert(dims->begin(), new LiteralExpr(-1, yystack_[2].location.begin.line, yystack_[2].location.begin.column));
        Entry* entry = Entry::getEntry(yystack_[3].value.as < std::string > ());
        yylhs.value.as < FE::AST::VarDeclarator* > () = new VarDeclarator(new LeftValExpr(entry, dims), nullptr, yystack_[3].location.begin.line, yystack_[3].location.begin.column);
    }
#line 1450 "yacc.tab.c"
    break;

  case 47: // VAR_DECLARATOR: IDENT LBRACKET RBRACKET ASSIGN INITIALIZER
#line 373 "frontend/parser/yacc.y"
                                                 {
        std::vector<ExprNode*>* dims = new std::vector<ExprNode*>();
        dims->emplace_back(new LiteralExpr(-1, yystack_[3].location.begin.line, yystack_[3].location.begin.column));
        Entry* entry = Entry::getEntry(yystack_[4].value.as < std::string > ());
        yylhs.value.as < FE::AST::VarDeclarator* > () = new VarDeclarator(new LeftValExpr(entry, dims), yystack_[0].value.as < FE::AST::InitDecl* > (), yystack_[4].location.begin.line, yystack_[4].location.begin.column);
    }
#line 1461 "yacc.tab.c"
    break;

  case 48: // VAR_DECLARATOR: IDENT LBRACKET RBRACKET ARRAY_DIMENSION_EXPR_LIST ASSIGN INITIALIZER
#line 379 "frontend/parser/yacc.y"
                                                                           {
        std::vector<ExprNode*>* dims = yystack_[2].value.as < std::vector<FE::AST::ExprNode*>* > ();
        dims->insert(dims->begin(), new LiteralExpr(-1, yystack_[4].location.begin.line, yystack_[4].location.begin.column));
        Entry* entry = Entry::getEntry(yystack_[5].value.as < std::string > ());
        yylhs.value.as < FE::AST::VarDeclarator* > () = new VarDeclarator(new LeftValExpr(entry, dims), yystack_[0].value.as < FE::AST::InitDecl* > (), yystack_[5].location.begin.line, yystack_[5].location.begin.column);
    }
#line 1472 "yacc.tab.c"
    break;

  case 49: // VAR_DECLARATOR: IDENT ARRAY_DIMENSION_EXPR_LIST
#line 385 "frontend/parser/yacc.y"
                                      {
        Entry* entry = Entry::getEntry(yystack_[1].value.as < std::string > ());
        yylhs.value.as < FE::AST::VarDeclarator* > () = new VarDeclarator(new LeftValExpr(entry, yystack_[0].value.as < std::vector<FE::AST::ExprNode*>* > ()), nullptr, yystack_[1].location.begin.line, yystack_[1].location.begin.column);
    }
#line 1481 "yacc.tab.c"
    break;

  case 50: // VAR_DECLARATOR: IDENT ARRAY_DIMENSION_EXPR_LIST ASSIGN INITIALIZER
#line 389 "frontend/parser/yacc.y"
                                                         {
        Entry* entry = Entry::getEntry(yystack_[3].value.as < std::string > ());
        yylhs.value.as < FE::AST::VarDeclarator* > () = new VarDeclarator(new LeftValExpr(entry, yystack_[2].value.as < std::vector<FE::AST::ExprNode*>* > ()), yystack_[0].value.as < FE::AST::InitDecl* > (), yystack_[3].location.begin.line, yystack_[3].location.begin.column);
    }
#line 1490 "yacc.tab.c"
    break;

  case 51: // VAR_DECLARATOR_LIST: VAR_DECLARATOR
#line 396 "frontend/parser/yacc.y"
                   {
        yylhs.value.as < std::vector<FE::AST::VarDeclarator*>* > () = new std::vector<VarDeclarator*>();
        yylhs.value.as < std::vector<FE::AST::VarDeclarator*>* > ()->push_back(yystack_[0].value.as < FE::AST::VarDeclarator* > ());
    }
#line 1499 "yacc.tab.c"
    break;

  case 52: // VAR_DECLARATOR_LIST: VAR_DECLARATOR_LIST COMMA VAR_DECLARATOR
#line 400 "frontend/parser/yacc.y"
                                               {
        yylhs.value.as < std::vector<FE::AST::VarDeclarator*>* > () = yystack_[2].value.as < std::vector<FE::AST::VarDeclarator*>* > ();
        yylhs.value.as < std::vector<FE::AST::VarDeclarator*>* > ()->push_back(yystack_[0].value.as < FE::AST::VarDeclarator* > ());
    }
#line 1508 "yacc.tab.c"
    break;

  case 53: // INITIALIZER: NOCOMMA_EXPR
#line 408 "frontend/parser/yacc.y"
                 {
        // 单个初始化
        yylhs.value.as < FE::AST::InitDecl* > () = new FE::AST::Initializer(yystack_[0].value.as < FE::AST::ExprNode* > (), yystack_[0].location.begin.line, yystack_[0].location.begin.column);
    }
#line 1517 "yacc.tab.c"
    break;

  case 54: // INITIALIZER: LBRACE INITIALIZER_LIST RBRACE
#line 412 "frontend/parser/yacc.y"
                                     {
        // 初始化列表
        yylhs.value.as < FE::AST::InitDecl* > () = new FE::AST::InitializerList(yystack_[1].value.as < std::vector<FE::AST::InitDecl*>* > (), yystack_[2].location.begin.line, yystack_[2].location.begin.column);
    }
#line 1526 "yacc.tab.c"
    break;

  case 55: // INITIALIZER_LIST: INITIALIZER
#line 419 "frontend/parser/yacc.y"
                {
        yylhs.value.as < std::vector<FE::AST::InitDecl*>* > () = new std::vector<InitDecl*>();
        yylhs.value.as < std::vector<FE::AST::InitDecl*>* > ()->push_back(yystack_[0].value.as < FE::AST::InitDecl* > ());
    }
#line 1535 "yacc.tab.c"
    break;

  case 56: // INITIALIZER_LIST: INITIALIZER_LIST COMMA INITIALIZER
#line 423 "frontend/parser/yacc.y"
                                         {
        yylhs.value.as < std::vector<FE::AST::InitDecl*>* > () = yystack_[2].value.as < std::vector<FE::AST::InitDecl*>* > ();
        yylhs.value.as < std::vector<FE::AST::InitDecl*>* > ()->push_back(yystack_[0].value.as < FE::AST::InitDecl* > ());
    }
#line 1544 "yacc.tab.c"
    break;

  case 57: // ASSIGN_EXPR: LEFT_VAL_EXPR ASSIGN NOCOMMA_EXPR
#line 431 "frontend/parser/yacc.y"
                                      {
        yylhs.value.as < FE::AST::ExprNode* > () = new BinaryExpr(Operator::ASSIGN, yystack_[2].value.as < FE::AST::ExprNode* > (), yystack_[0].value.as < FE::AST::ExprNode* > (), yystack_[2].location.begin.line, yystack_[2].location.begin.column);
    }
#line 1552 "yacc.tab.c"
    break;

  case 58: // EXPR_LIST: NOCOMMA_EXPR
#line 437 "frontend/parser/yacc.y"
                 {
        yylhs.value.as < std::vector<FE::AST::ExprNode*>* > () = new std::vector<ExprNode*>();
        yylhs.value.as < std::vector<FE::AST::ExprNode*>* > ()->push_back(yystack_[0].value.as < FE::AST::ExprNode* > ());
    }
#line 1561 "yacc.tab.c"
    break;

  case 59: // EXPR_LIST: EXPR_LIST COMMA NOCOMMA_EXPR
#line 441 "frontend/parser/yacc.y"
                                   {
        yylhs.value.as < std::vector<FE::AST::ExprNode*>* > () = yystack_[2].value.as < std::vector<FE::AST::ExprNode*>* > ();
        yylhs.value.as < std::vector<FE::AST::ExprNode*>* > ()->push_back(yystack_[0].value.as < FE::AST::ExprNode* > ());
    }
#line 1570 "yacc.tab.c"
    break;

  case 60: // EXPR: NOCOMMA_EXPR
#line 448 "frontend/parser/yacc.y"
                 {
        yylhs.value.as < FE::AST::ExprNode* > () = yystack_[0].value.as < FE::AST::ExprNode* > ();
    }
#line 1578 "yacc.tab.c"
    break;

  case 61: // EXPR: EXPR COMMA NOCOMMA_EXPR
#line 451 "frontend/parser/yacc.y"
                              {
        if (yystack_[2].value.as < FE::AST::ExprNode* > ()->isCommaExpr()) {
            CommaExpr* ce = static_cast<CommaExpr*>(yystack_[2].value.as < FE::AST::ExprNode* > ());
            ce->exprs->push_back(yystack_[0].value.as < FE::AST::ExprNode* > ());
            yylhs.value.as < FE::AST::ExprNode* > () = ce;
        } else {
            auto vec = new std::vector<ExprNode*>();
            vec->push_back(yystack_[2].value.as < FE::AST::ExprNode* > ());
            vec->push_back(yystack_[0].value.as < FE::AST::ExprNode* > ());
            yylhs.value.as < FE::AST::ExprNode* > () = new CommaExpr(vec, yystack_[2].value.as < FE::AST::ExprNode* > ()->line_num, yystack_[2].value.as < FE::AST::ExprNode* > ()->col_num);
        }
    }
#line 1595 "yacc.tab.c"
    break;

  case 62: // NOCOMMA_EXPR: LOGICAL_OR_EXPR
#line 466 "frontend/parser/yacc.y"
                    {
        yylhs.value.as < FE::AST::ExprNode* > () = yystack_[0].value.as < FE::AST::ExprNode* > ();
    }
#line 1603 "yacc.tab.c"
    break;

  case 63: // NOCOMMA_EXPR: ASSIGN_EXPR
#line 469 "frontend/parser/yacc.y"
                  {
        yylhs.value.as < FE::AST::ExprNode* > () = yystack_[0].value.as < FE::AST::ExprNode* > ();
    }
#line 1611 "yacc.tab.c"
    break;

  case 64: // LOGICAL_OR_EXPR: LOGICAL_AND_EXPR
#line 476 "frontend/parser/yacc.y"
                     { yylhs.value.as < FE::AST::ExprNode* > () = yystack_[0].value.as < FE::AST::ExprNode* > (); }
#line 1617 "yacc.tab.c"
    break;

  case 65: // LOGICAL_OR_EXPR: LOGICAL_OR_EXPR OR LOGICAL_AND_EXPR
#line 477 "frontend/parser/yacc.y"
                                          {
        yylhs.value.as < FE::AST::ExprNode* > () = new BinaryExpr(Operator::OR, yystack_[2].value.as < FE::AST::ExprNode* > (), yystack_[0].value.as < FE::AST::ExprNode* > (), yystack_[2].location.begin.line, yystack_[2].location.begin.column);
    }
#line 1625 "yacc.tab.c"
    break;

  case 66: // LOGICAL_AND_EXPR: EQUALITY_EXPR
#line 484 "frontend/parser/yacc.y"
                  { yylhs.value.as < FE::AST::ExprNode* > () = yystack_[0].value.as < FE::AST::ExprNode* > (); }
#line 1631 "yacc.tab.c"
    break;

  case 67: // LOGICAL_AND_EXPR: LOGICAL_AND_EXPR AND EQUALITY_EXPR
#line 485 "frontend/parser/yacc.y"
                                         {
        yylhs.value.as < FE::AST::ExprNode* > () = new BinaryExpr(Operator::AND, yystack_[2].value.as < FE::AST::ExprNode* > (), yystack_[0].value.as < FE::AST::ExprNode* > (), yystack_[2].location.begin.line, yystack_[2].location.begin.column);
    }
#line 1639 "yacc.tab.c"
    break;

  case 68: // EQUALITY_EXPR: RELATIONAL_EXPR
#line 492 "frontend/parser/yacc.y"
                    { yylhs.value.as < FE::AST::ExprNode* > () = yystack_[0].value.as < FE::AST::ExprNode* > (); }
#line 1645 "yacc.tab.c"
    break;

  case 69: // EQUALITY_EXPR: EQUALITY_EXPR EQ RELATIONAL_EXPR
#line 493 "frontend/parser/yacc.y"
                                       {
        yylhs.value.as < FE::AST::ExprNode* > () = new BinaryExpr(Operator::EQ, yystack_[2].value.as < FE::AST::ExprNode* > (), yystack_[0].value.as < FE::AST::ExprNode* > (), yystack_[2].location.begin.line, yystack_[2].location.begin.column);
    }
#line 1653 "yacc.tab.c"
    break;

  case 70: // EQUALITY_EXPR: EQUALITY_EXPR NEQ RELATIONAL_EXPR
#line 496 "frontend/parser/yacc.y"
                                        {
        yylhs.value.as < FE::AST::ExprNode* > () = new BinaryExpr(Operator::NEQ, yystack_[2].value.as < FE::AST::ExprNode* > (), yystack_[0].value.as < FE::AST::ExprNode* > (), yystack_[2].location.begin.line, yystack_[2].location.begin.column);
    }
#line 1661 "yacc.tab.c"
    break;

  case 71: // RELATIONAL_EXPR: ADDSUB_EXPR
#line 503 "frontend/parser/yacc.y"
                { yylhs.value.as < FE::AST::ExprNode* > () = yystack_[0].value.as < FE::AST::ExprNode* > (); }
#line 1667 "yacc.tab.c"
    break;

  case 72: // RELATIONAL_EXPR: RELATIONAL_EXPR LT ADDSUB_EXPR
#line 504 "frontend/parser/yacc.y"
                                     {
        yylhs.value.as < FE::AST::ExprNode* > () = new BinaryExpr(Operator::LT, yystack_[2].value.as < FE::AST::ExprNode* > (), yystack_[0].value.as < FE::AST::ExprNode* > (), yystack_[2].location.begin.line, yystack_[2].location.begin.column);
    }
#line 1675 "yacc.tab.c"
    break;

  case 73: // RELATIONAL_EXPR: RELATIONAL_EXPR GT ADDSUB_EXPR
#line 507 "frontend/parser/yacc.y"
                                     {
        yylhs.value.as < FE::AST::ExprNode* > () = new BinaryExpr(Operator::GT, yystack_[2].value.as < FE::AST::ExprNode* > (), yystack_[0].value.as < FE::AST::ExprNode* > (), yystack_[2].location.begin.line, yystack_[2].location.begin.column);
    }
#line 1683 "yacc.tab.c"
    break;

  case 74: // RELATIONAL_EXPR: RELATIONAL_EXPR LE ADDSUB_EXPR
#line 510 "frontend/parser/yacc.y"
                                     {
        yylhs.value.as < FE::AST::ExprNode* > () = new BinaryExpr(Operator::LE, yystack_[2].value.as < FE::AST::ExprNode* > (), yystack_[0].value.as < FE::AST::ExprNode* > (), yystack_[2].location.begin.line, yystack_[2].location.begin.column);
    }
#line 1691 "yacc.tab.c"
    break;

  case 75: // RELATIONAL_EXPR: RELATIONAL_EXPR GE ADDSUB_EXPR
#line 513 "frontend/parser/yacc.y"
                                     {
        yylhs.value.as < FE::AST::ExprNode* > () = new BinaryExpr(Operator::GE, yystack_[2].value.as < FE::AST::ExprNode* > (), yystack_[0].value.as < FE::AST::ExprNode* > (), yystack_[2].location.begin.line, yystack_[2].location.begin.column);
    }
#line 1699 "yacc.tab.c"
    break;

  case 76: // ADDSUB_EXPR: MULDIV_EXPR
#line 520 "frontend/parser/yacc.y"
                { yylhs.value.as < FE::AST::ExprNode* > () = yystack_[0].value.as < FE::AST::ExprNode* > (); }
#line 1705 "yacc.tab.c"
    break;

  case 77: // ADDSUB_EXPR: ADDSUB_EXPR PLUS MULDIV_EXPR
#line 521 "frontend/parser/yacc.y"
                                   {
        yylhs.value.as < FE::AST::ExprNode* > () = new BinaryExpr(Operator::ADD, yystack_[2].value.as < FE::AST::ExprNode* > (), yystack_[0].value.as < FE::AST::ExprNode* > (), yystack_[2].location.begin.line, yystack_[2].location.begin.column);
    }
#line 1713 "yacc.tab.c"
    break;

  case 78: // ADDSUB_EXPR: ADDSUB_EXPR MINUS MULDIV_EXPR
#line 524 "frontend/parser/yacc.y"
                                    {
        yylhs.value.as < FE::AST::ExprNode* > () = new BinaryExpr(Operator::SUB, yystack_[2].value.as < FE::AST::ExprNode* > (), yystack_[0].value.as < FE::AST::ExprNode* > (), yystack_[2].location.begin.line, yystack_[2].location.begin.column);
    }
#line 1721 "yacc.tab.c"
    break;

  case 79: // MULDIV_EXPR: UNARY_EXPR
#line 531 "frontend/parser/yacc.y"
               { yylhs.value.as < FE::AST::ExprNode* > () = yystack_[0].value.as < FE::AST::ExprNode* > (); }
#line 1727 "yacc.tab.c"
    break;

  case 80: // MULDIV_EXPR: MULDIV_EXPR MUL UNARY_EXPR
#line 532 "frontend/parser/yacc.y"
                                 {
        yylhs.value.as < FE::AST::ExprNode* > () = new BinaryExpr(Operator::MUL, yystack_[2].value.as < FE::AST::ExprNode* > (), yystack_[0].value.as < FE::AST::ExprNode* > (), yystack_[2].location.begin.line, yystack_[2].location.begin.column);
    }
#line 1735 "yacc.tab.c"
    break;

  case 81: // MULDIV_EXPR: MULDIV_EXPR DIV UNARY_EXPR
#line 535 "frontend/parser/yacc.y"
                                 {
        yylhs.value.as < FE::AST::ExprNode* > () = new BinaryExpr(Operator::DIV, yystack_[2].value.as < FE::AST::ExprNode* > (), yystack_[0].value.as < FE::AST::ExprNode* > (), yystack_[2].location.begin.line, yystack_[2].location.begin.column);
    }
#line 1743 "yacc.tab.c"
    break;

  case 82: // MULDIV_EXPR: MULDIV_EXPR MOD UNARY_EXPR
#line 538 "frontend/parser/yacc.y"
                                 {
        yylhs.value.as < FE::AST::ExprNode* > () = new BinaryExpr(Operator::MOD, yystack_[2].value.as < FE::AST::ExprNode* > (), yystack_[0].value.as < FE::AST::ExprNode* > (), yystack_[2].location.begin.line, yystack_[2].location.begin.column);
    }
#line 1751 "yacc.tab.c"
    break;

  case 83: // UNARY_EXPR: BASIC_EXPR
#line 544 "frontend/parser/yacc.y"
               {
        yylhs.value.as < FE::AST::ExprNode* > () = yystack_[0].value.as < FE::AST::ExprNode* > ();
    }
#line 1759 "yacc.tab.c"
    break;

  case 84: // UNARY_EXPR: UNARY_OP UNARY_EXPR
#line 547 "frontend/parser/yacc.y"
                          {
        yylhs.value.as < FE::AST::ExprNode* > () = new UnaryExpr(yystack_[1].value.as < FE::AST::Operator > (), yystack_[0].value.as < FE::AST::ExprNode* > (), yystack_[1].location.begin.line, yystack_[1].location.begin.column);
    }
#line 1767 "yacc.tab.c"
    break;

  case 85: // BASIC_EXPR: LITERAL_EXPR
#line 553 "frontend/parser/yacc.y"
                 {
        yylhs.value.as < FE::AST::ExprNode* > () = yystack_[0].value.as < FE::AST::ExprNode* > ();
    }
#line 1775 "yacc.tab.c"
    break;

  case 86: // BASIC_EXPR: LEFT_VAL_EXPR
#line 556 "frontend/parser/yacc.y"
                    {
        yylhs.value.as < FE::AST::ExprNode* > () = yystack_[0].value.as < FE::AST::ExprNode* > ();
    }
#line 1783 "yacc.tab.c"
    break;

  case 87: // BASIC_EXPR: LPAREN EXPR RPAREN
#line 559 "frontend/parser/yacc.y"
                         {
        yylhs.value.as < FE::AST::ExprNode* > () = yystack_[1].value.as < FE::AST::ExprNode* > ();
    }
#line 1791 "yacc.tab.c"
    break;

  case 88: // BASIC_EXPR: FUNC_CALL_EXPR
#line 562 "frontend/parser/yacc.y"
                     {
        yylhs.value.as < FE::AST::ExprNode* > () = yystack_[0].value.as < FE::AST::ExprNode* > ();
    }
#line 1799 "yacc.tab.c"
    break;

  case 89: // FUNC_CALL_EXPR: IDENT LPAREN RPAREN
#line 568 "frontend/parser/yacc.y"
                        {
        std::string funcName = yystack_[2].value.as < std::string > ();
        if (funcName != "starttime" && funcName != "stoptime")
        {
            Entry* entry = Entry::getEntry(funcName);
            yylhs.value.as < FE::AST::ExprNode* > () = new CallExpr(entry, nullptr, yystack_[2].location.begin.line, yystack_[2].location.begin.column);
        }
        else
        {    
            funcName = "_sysy_" + funcName;
            std::vector<ExprNode*>* args = new std::vector<ExprNode*>();
            args->emplace_back(new LiteralExpr(static_cast<int>(yystack_[2].location.begin.line), yystack_[2].location.begin.line, yystack_[2].location.begin.column));
            yylhs.value.as < FE::AST::ExprNode* > () = new CallExpr(Entry::getEntry(funcName), args, yystack_[2].location.begin.line, yystack_[2].location.begin.column);
        }
    }
#line 1819 "yacc.tab.c"
    break;

  case 90: // FUNC_CALL_EXPR: IDENT LPAREN EXPR_LIST RPAREN
#line 583 "frontend/parser/yacc.y"
                                    {
        Entry* entry = Entry::getEntry(yystack_[3].value.as < std::string > ());
        yylhs.value.as < FE::AST::ExprNode* > () = new CallExpr(entry, yystack_[1].value.as < std::vector<FE::AST::ExprNode*>* > (), yystack_[3].location.begin.line, yystack_[3].location.begin.column);
    }
#line 1828 "yacc.tab.c"
    break;

  case 91: // ARRAY_DIMENSION_EXPR: LBRACKET NOCOMMA_EXPR RBRACKET
#line 590 "frontend/parser/yacc.y"
                                   {
        yylhs.value.as < FE::AST::ExprNode* > () = yystack_[1].value.as < FE::AST::ExprNode* > ();
    }
#line 1836 "yacc.tab.c"
    break;

  case 92: // ARRAY_DIMENSION_EXPR_LIST: ARRAY_DIMENSION_EXPR
#line 597 "frontend/parser/yacc.y"
                         {
        yylhs.value.as < std::vector<FE::AST::ExprNode*>* > () = new std::vector<FE::AST::ExprNode*>();
        yylhs.value.as < std::vector<FE::AST::ExprNode*>* > ()->push_back(yystack_[0].value.as < FE::AST::ExprNode* > ());
    }
#line 1845 "yacc.tab.c"
    break;

  case 93: // ARRAY_DIMENSION_EXPR_LIST: ARRAY_DIMENSION_EXPR_LIST ARRAY_DIMENSION_EXPR
#line 601 "frontend/parser/yacc.y"
                                                     {
        yylhs.value.as < std::vector<FE::AST::ExprNode*>* > () = yystack_[1].value.as < std::vector<FE::AST::ExprNode*>* > ();
        yylhs.value.as < std::vector<FE::AST::ExprNode*>* > ()->push_back(yystack_[0].value.as < FE::AST::ExprNode* > ());
    }
#line 1854 "yacc.tab.c"
    break;

  case 94: // LEFT_VAL_EXPR: IDENT
#line 609 "frontend/parser/yacc.y"
          {
        Entry* entry = Entry::getEntry(yystack_[0].value.as < std::string > ());
        yylhs.value.as < FE::AST::ExprNode* > () = new LeftValExpr(entry, nullptr, yystack_[0].location.begin.line, yystack_[0].location.begin.column);
    }
#line 1863 "yacc.tab.c"
    break;

  case 95: // LEFT_VAL_EXPR: IDENT ARRAY_DIMENSION_EXPR_LIST
#line 613 "frontend/parser/yacc.y"
                                      {
        Entry* entry = Entry::getEntry(yystack_[1].value.as < std::string > ());
        yylhs.value.as < FE::AST::ExprNode* > () = new LeftValExpr(entry, yystack_[0].value.as < std::vector<FE::AST::ExprNode*>* > (), yystack_[1].location.begin.line, yystack_[1].location.begin.column);
    }
#line 1872 "yacc.tab.c"
    break;

  case 96: // LITERAL_EXPR: INT_CONST
#line 620 "frontend/parser/yacc.y"
              {
        yylhs.value.as < FE::AST::ExprNode* > () = new LiteralExpr(yystack_[0].value.as < int > (), yystack_[0].location.begin.line, yystack_[0].location.begin.column);
    }
#line 1880 "yacc.tab.c"
    break;

  case 97: // LITERAL_EXPR: FLOAT_CONST
#line 624 "frontend/parser/yacc.y"
                  {
        yylhs.value.as < FE::AST::ExprNode* > () = new LiteralExpr(yystack_[0].value.as < float > (), yystack_[0].location.begin.line, yystack_[0].location.begin.column);
    }
#line 1888 "yacc.tab.c"
    break;

  case 98: // LITERAL_EXPR: LL_CONST
#line 627 "frontend/parser/yacc.y"
               {
        yylhs.value.as < FE::AST::ExprNode* > () = new LiteralExpr(yystack_[0].value.as < long long > (), yystack_[0].location.begin.line, yystack_[0].location.begin.column);
    }
#line 1896 "yacc.tab.c"
    break;

  case 99: // TYPE: INT
#line 634 "frontend/parser/yacc.y"
        { yylhs.value.as < FE::AST::Type* > () = intType; }
#line 1902 "yacc.tab.c"
    break;

  case 100: // TYPE: FLOAT
#line 635 "frontend/parser/yacc.y"
            { yylhs.value.as < FE::AST::Type* > () = floatType; }
#line 1908 "yacc.tab.c"
    break;

  case 101: // TYPE: VOID
#line 636 "frontend/parser/yacc.y"
           { yylhs.value.as < FE::AST::Type* > () = voidType; }
#line 1914 "yacc.tab.c"
    break;

  case 102: // UNARY_OP: PLUS
#line 641 "frontend/parser/yacc.y"
         { yylhs.value.as < FE::AST::Operator > () = Operator::ADD; }
#line 1920 "yacc.tab.c"
    break;

  case 103: // UNARY_OP: MINUS
#line 642 "frontend/parser/yacc.y"
            { yylhs.value.as < FE::AST::Operator > () = Operator::SUB; }
#line 1926 "yacc.tab.c"
    break;

  case 104: // UNARY_OP: NOT
#line 643 "frontend/parser/yacc.y"
          { yylhs.value.as < FE::AST::Operator > () = Operator::NOT; }
#line 1932 "yacc.tab.c"
    break;


#line 1936 "yacc.tab.c"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (yyla.location, YY_MOVE (msg));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yyerror_range[1].location = yystack_[0].location;
        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
   YaccParser ::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
   YaccParser ::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

  std::string
   YaccParser ::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  //  YaccParser ::context.
   YaccParser ::context::context (const  YaccParser & yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
   YaccParser ::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

    const int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        const int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        const int yychecklim = yylast_ - yyn + 1;
        const int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
        for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
          if (yycheck_[yyx + yyn] == yyx && yyx != symbol_kind::S_YYerror
              && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
            {
              if (!yyarg)
                ++yycount;
              else if (yycount == yyargn)
                return 0;
              else
                yyarg[yycount++] = YY_CAST (symbol_kind_type, yyx);
            }
      }

    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }






  int
   YaccParser ::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
   YaccParser ::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const short  YaccParser ::yypact_ninf_ = -129;

  const signed char  YaccParser ::yytable_ninf_ = -1;

  const short
   YaccParser ::yypact_[] =
  {
     245,  -129,  -129,  -129,  -129,    77,  -129,  -129,  -129,    -9,
       4,    12,    23,    29,   291,    66,  -129,   343,    48,  -129,
    -129,  -129,     5,   245,  -129,  -129,  -129,    37,  -129,  -129,
    -129,  -129,  -129,  -129,  -129,  -129,  -129,     2,  -129,    58,
      69,   -19,    28,   -12,   101,  -129,  -129,  -129,    63,  -129,
     115,   343,    89,   343,  -129,   119,   343,   277,   343,  -129,
    -129,  -129,     9,   154,    81,  -129,   149,  -129,  -129,  -129,
    -129,  -129,   343,   343,   343,   343,   343,   343,   343,   343,
     343,   343,   343,   343,   343,   343,   343,   -18,  -129,   144,
    -129,  -129,  -129,    99,  -129,   145,  -129,   105,   153,    64,
     154,   113,  -129,   -17,   144,  -129,  -129,  -129,    69,   -19,
      28,    28,   -12,   -12,   -12,   -12,   101,   101,  -129,  -129,
    -129,  -129,    66,   299,   327,   -15,   154,   343,  -129,  -129,
     245,   343,   343,   245,  -129,   123,   177,   -14,   327,  -129,
    -129,   327,  -129,  -129,   173,    70,    74,  -129,    66,   169,
     172,   327,    -4,  -129,    -6,  -129,   245,   343,   343,  -129,
     181,  -129,   335,   119,  -129,   327,   327,  -129,  -129,   143,
     151,  -129,   213,   119,  -129,  -129,   245,   245,  -129,   119,
    -129,  -129
  };

  const signed char
   YaccParser ::yydefact_[] =
  {
       0,    96,    98,    13,    97,    94,    99,   100,   101,     0,
       0,     0,     0,     0,     0,     0,    12,     0,     0,   102,
     103,   104,     0,     2,     4,    11,     6,     0,     7,     8,
       9,    10,    14,    15,    17,    16,    63,     0,    60,    62,
      64,    66,    68,    71,    76,    79,    83,    88,    86,    85,
       0,     0,     0,     0,    92,    95,     0,     0,     0,    18,
      34,    32,     0,     0,     0,    30,     0,     1,     3,     5,
      22,    19,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    43,    51,    20,
      84,    86,    89,     0,    58,     0,    93,     0,     0,     0,
       0,     0,    33,    43,    21,    87,    31,    61,    65,    67,
      69,    70,    73,    72,    75,    74,    77,    78,    80,    81,
      82,    57,    40,     0,     0,    49,     0,     0,    90,    91,
       0,     0,     0,     0,    41,     0,     0,    45,     0,    44,
      53,     0,    52,    59,    28,     0,     0,    35,     0,     0,
      36,     0,    46,    55,     0,    50,     0,     0,     0,    42,
       0,    25,     0,    39,    47,     0,     0,    54,    29,     0,
       0,    23,     0,    37,    48,    56,     0,     0,    24,    38,
      26,    27
  };

  const short
   YaccParser ::yypgoto_[] =
  {
    -129,  -129,   -16,   -22,  -129,  -129,   146,  -129,  -129,  -129,
    -129,  -129,  -129,  -129,  -129,  -129,    54,  -129,    83,   147,
    -128,  -129,  -129,  -129,   -11,   -36,  -129,   134,   137,    43,
       6,    61,   -43,  -129,  -129,   -51,    -5,   320,  -129,    -8,
    -129
  };

  const unsigned char
   YaccParser ::yydefgoto_[] =
  {
       0,    22,    23,    24,    25,    26,    27,    28,   161,    29,
      30,    31,    32,    33,    34,    35,   134,   135,    88,    89,
     139,   154,    36,    93,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    54,   125,    48,    49,    50,
      51
  };

  const unsigned char
   YaccParser ::yytable_[] =
  {
      55,    69,    66,    62,    96,    67,    64,    63,    90,   122,
     153,   123,   123,   155,    53,    53,    94,    95,    56,    75,
     166,    81,    82,   164,    76,    53,   167,    71,    72,   124,
     124,    57,   141,   151,   102,    72,   107,   174,   175,    58,
     118,   119,   120,   165,    69,    97,    99,   101,    59,   100,
     121,     1,     2,    68,    60,     3,     4,     5,     6,     7,
       8,     9,    70,    10,    11,    12,    13,    77,    78,    79,
      80,    14,    15,    16,    96,    17,     6,     7,     8,    18,
      65,    19,    20,   112,   113,   114,   115,    95,   140,   132,
      72,   143,     1,     2,    21,   157,    72,     4,     5,   158,
      72,    96,   140,    73,    52,   140,    53,    72,   144,   105,
      86,   147,    96,    74,   136,   140,    17,    92,   110,   111,
     145,   146,    19,    20,    87,   127,    95,   128,    96,   140,
     140,    72,   152,   130,   168,    21,    83,    84,    85,    72,
     136,   133,   116,   117,   172,   163,   169,   170,    53,   148,
      69,   149,     1,     2,   180,   181,     3,     4,     5,     6,
       7,     8,     9,   103,    10,    11,    12,    13,   179,    72,
     126,   176,    14,    15,    16,   129,    17,    72,   131,   177,
      18,   106,    19,    20,     1,     2,   150,   156,     3,     4,
       5,     6,     7,     8,     9,    21,    10,    11,    12,    13,
     160,   162,   159,    98,    14,    15,    16,   108,    17,   142,
     104,   109,    18,   171,    19,    20,     1,     2,     0,     0,
       3,     4,     5,     6,     7,     8,     9,    21,    10,    11,
      12,    13,     0,     0,     0,     0,    14,    15,    16,     0,
      17,     0,     0,     0,    18,   178,    19,    20,     1,     2,
       0,     0,     3,     4,     5,     6,     7,     8,     9,    21,
      10,    11,    12,    13,     0,     0,     0,     0,    14,    15,
      16,     0,    17,     0,     0,     0,    18,     0,    19,    20,
       1,     2,     0,     0,     0,     4,     5,     6,     7,     8,
       0,    21,     0,     0,     1,     2,     0,     0,     0,     4,
       5,    15,     1,     2,    17,     0,     0,     4,     5,     0,
      19,    20,     0,     0,     0,     0,    61,     0,    17,     0,
       0,     0,     0,    21,    19,    20,    17,     0,     0,   137,
       1,     2,    19,    20,     0,     4,     5,    21,     1,     2,
       0,     0,     0,     4,     5,    21,     1,     2,     0,     0,
       0,     4,     5,     0,    17,     0,     0,     0,   138,     0,
      19,    20,    17,     0,     0,   173,     0,     0,    19,    20,
      17,    91,     0,    21,     0,     0,    19,    20,     0,     0,
       0,    21,     0,     0,     0,     0,     0,     0,     0,    21,
       0,     0,     0,    91,    91,    91,    91,    91,    91,    91,
      91,    91,    91,    91,    91,    91
  };

  const short
   YaccParser ::yycheck_[] =
  {
       5,    23,    18,    14,    55,     0,    17,    15,    51,    27,
     138,    29,    29,   141,    29,    29,    52,    53,    27,    38,
      26,    33,    34,   151,    43,    29,    32,    25,    26,    47,
      47,    27,    47,    47,    25,    26,    72,   165,   166,    27,
      83,    84,    85,    47,    66,    56,    57,    58,    25,    57,
      86,     3,     4,    48,    25,     7,     8,     9,    10,    11,
      12,    13,    25,    15,    16,    17,    18,    39,    40,    41,
      42,    23,    24,    25,   125,    27,    10,    11,    12,    31,
      32,    33,    34,    77,    78,    79,    80,   123,   124,    25,
      26,   127,     3,     4,    46,    25,    26,     8,     9,    25,
      26,   152,   138,    45,    27,   141,    29,    26,   130,    28,
      47,   133,   163,    44,   122,   151,    27,    28,    75,    76,
     131,   132,    33,    34,     9,    26,   162,    28,   179,   165,
     166,    26,   137,    28,   156,    46,    35,    36,    37,    26,
     148,    28,    81,    82,   160,   150,   157,   158,    29,    26,
     172,    28,     3,     4,   176,   177,     7,     8,     9,    10,
      11,    12,    13,     9,    15,    16,    17,    18,   173,    26,
      26,    28,    23,    24,    25,    30,    27,    26,    25,    28,
      31,    32,    33,    34,     3,     4,     9,    14,     7,     8,
       9,    10,    11,    12,    13,    46,    15,    16,    17,    18,
      31,    29,   148,    57,    23,    24,    25,    73,    27,   126,
      63,    74,    31,    32,    33,    34,     3,     4,    -1,    -1,
       7,     8,     9,    10,    11,    12,    13,    46,    15,    16,
      17,    18,    -1,    -1,    -1,    -1,    23,    24,    25,    -1,
      27,    -1,    -1,    -1,    31,    32,    33,    34,     3,     4,
      -1,    -1,     7,     8,     9,    10,    11,    12,    13,    46,
      15,    16,    17,    18,    -1,    -1,    -1,    -1,    23,    24,
      25,    -1,    27,    -1,    -1,    -1,    31,    -1,    33,    34,
       3,     4,    -1,    -1,    -1,     8,     9,    10,    11,    12,
      -1,    46,    -1,    -1,     3,     4,    -1,    -1,    -1,     8,
       9,    24,     3,     4,    27,    -1,    -1,     8,     9,    -1,
      33,    34,    -1,    -1,    -1,    -1,    25,    -1,    27,    -1,
      -1,    -1,    -1,    46,    33,    34,    27,    -1,    -1,    30,
       3,     4,    33,    34,    -1,     8,     9,    46,     3,     4,
      -1,    -1,    -1,     8,     9,    46,     3,     4,    -1,    -1,
      -1,     8,     9,    -1,    27,    -1,    -1,    -1,    31,    -1,
      33,    34,    27,    -1,    -1,    30,    -1,    -1,    33,    34,
      27,    51,    -1,    46,    -1,    -1,    33,    34,    -1,    -1,
      -1,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    46,
      -1,    -1,    -1,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85
  };

  const signed char
   YaccParser ::yystos_[] =
  {
       0,     3,     4,     7,     8,     9,    10,    11,    12,    13,
      15,    16,    17,    18,    23,    24,    25,    27,    31,    33,
      34,    46,    51,    52,    53,    54,    55,    56,    57,    59,
      60,    61,    62,    63,    64,    65,    72,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    87,    88,
      89,    90,    27,    29,    85,    86,    27,    27,    27,    25,
      25,    25,    74,    89,    74,    32,    52,     0,    48,    53,
      25,    25,    26,    45,    44,    38,    43,    39,    40,    41,
      42,    33,    34,    35,    36,    37,    47,     9,    68,    69,
      82,    87,    28,    73,    75,    75,    85,    74,    56,    74,
      89,    74,    25,     9,    69,    28,    32,    75,    77,    78,
      79,    79,    80,    80,    80,    80,    81,    81,    82,    82,
      82,    75,    27,    29,    47,    86,    26,    26,    28,    30,
      28,    25,    25,    28,    66,    67,    89,    30,    31,    70,
      75,    47,    68,    75,    53,    74,    74,    53,    26,    28,
       9,    47,    86,    70,    71,    70,    14,    25,    25,    66,
      31,    58,    29,    86,    70,    47,    26,    32,    53,    74,
      74,    32,    52,    30,    70,    70,    28,    28,    32,    86,
      53,    53
  };

  const signed char
   YaccParser ::yyr1_[] =
  {
       0,    50,    51,    51,    52,    52,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    54,    55,
      56,    56,    57,    58,    58,    59,    60,    60,    61,    61,
      62,    62,    63,    63,    64,    65,    66,    66,    66,    66,
      67,    67,    67,    68,    68,    68,    68,    68,    68,    68,
      68,    69,    69,    70,    70,    71,    71,    72,    73,    73,
      74,    74,    75,    75,    76,    76,    77,    77,    78,    78,
      78,    79,    79,    79,    79,    79,    80,    80,    80,    81,
      81,    81,    81,    82,    82,    83,    83,    83,    83,    84,
      84,    85,    86,    86,    87,    87,    88,    88,    88,    89,
      89,    89,    90,    90,    90
  };

  const signed char
   YaccParser ::yyr2_[] =
  {
       0,     2,     1,     2,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     2,
       2,     3,     2,     2,     3,     6,     9,     9,     5,     7,
       2,     3,     2,     3,     2,     5,     2,     4,     5,     3,
       0,     1,     3,     1,     3,     3,     4,     5,     6,     2,
       4,     1,     3,     1,     3,     1,     3,     3,     1,     3,
       1,     3,     1,     1,     1,     3,     1,     3,     1,     3,
       3,     1,     3,     3,     3,     3,     1,     3,     3,     1,
       3,     3,     3,     1,     2,     1,     1,     3,     1,     3,
       4,     3,     1,     2,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const  YaccParser ::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "INT_CONST",
  "LL_CONST", "STR_CONST", "ERR_TOKEN", "SLASH_COMMENT", "FLOAT_CONST",
  "IDENT", "INT", "FLOAT", "VOID", "IF", "ELSE", "FOR", "WHILE",
  "CONTINUE", "BREAK", "SWITCH", "CASE", "GOTO", "DO", "RETURN", "CONST",
  "SEMICOLON", "COMMA", "LPAREN", "RPAREN", "LBRACKET", "RBRACKET",
  "LBRACE", "RBRACE", "PLUS", "MINUS", "MUL", "DIV", "MOD", "EQ", "GT",
  "LT", "GE", "LE", "NEQ", "AND", "OR", "NOT", "ASSIGN", "END", "THEN",
  "$accept", "PROGRAM", "STMT_LIST", "STMT", "CONTINUE_STMT", "EXPR_STMT",
  "VAR_DECLARATION", "VAR_DECL_STMT", "FUNC_BODY", "FUNC_DECL_STMT",
  "FOR_STMT", "IF_STMT", "BLOCK_STMT", "RETURN_STMT", "BREAK_STMT",
  "WHILE_STMT", "PARAM_DECLARATOR", "PARAM_DECLARATOR_LIST",
  "VAR_DECLARATOR", "VAR_DECLARATOR_LIST", "INITIALIZER",
  "INITIALIZER_LIST", "ASSIGN_EXPR", "EXPR_LIST", "EXPR", "NOCOMMA_EXPR",
  "LOGICAL_OR_EXPR", "LOGICAL_AND_EXPR", "EQUALITY_EXPR",
  "RELATIONAL_EXPR", "ADDSUB_EXPR", "MULDIV_EXPR", "UNARY_EXPR",
  "BASIC_EXPR", "FUNC_CALL_EXPR", "ARRAY_DIMENSION_EXPR",
  "ARRAY_DIMENSION_EXPR_LIST", "LEFT_VAL_EXPR", "LITERAL_EXPR", "TYPE",
  "UNARY_OP", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
   YaccParser ::yyrline_[] =
  {
       0,   140,   140,   144,   150,   154,   161,   164,   167,   170,
     173,   176,   179,   182,   186,   187,   188,   189,   193,   199,
     205,   208,   215,   222,   225,   241,   248,   252,   260,   264,
     273,   276,   292,   295,   301,   307,   313,   317,   324,   330,
     337,   340,   344,   353,   357,   361,   367,   373,   379,   385,
     389,   396,   400,   408,   412,   419,   423,   431,   437,   441,
     448,   451,   466,   469,   476,   477,   484,   485,   492,   493,
     496,   503,   504,   507,   510,   513,   520,   521,   524,   531,
     532,   535,   538,   544,   547,   553,   556,   559,   562,   568,
     583,   590,   597,   601,   609,   613,   620,   624,   627,   634,
     635,   636,   641,   642,   643
  };

  void
   YaccParser ::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
   YaccParser ::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


#line 4 "frontend/parser/yacc.y"
} //  FE 
#line 2584 "yacc.tab.c"

#line 646 "frontend/parser/yacc.y"


void FE::YaccParser::error(const FE::location& location, const std::string& message)
{
    std::cerr << "msg: " << message << ", error happened at: " << location << std::endl;
}
