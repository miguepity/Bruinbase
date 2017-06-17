#ifndef YY_SQL_SQLPARSER_TAB_H_INCLUDED
# define YY_SQL_SQLPARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int sqldebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    SELECT = 258,
    FROM = 259,
    WHERE = 260,
    LOAD = 261,
    WITH = 262,
    INDEX = 263,
    QUIT = 264,
    COUNT = 265,
    AND = 266,
    OR = 267,
    COMMA = 268,
    STAR = 269,
    LF = 270,
    INTEGER = 271,
    STRING = 272,
    ID = 273,
    EQUAL = 274,
    NEQUAL = 275,
    LESS = 276,
    LESSEQUAL = 277,
    GREATER = 278,
    GREATEREQUAL = 279
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 33 "SqlParser.y" /* yacc.c:1909  */

  int integer;
  char* string;
  SelCond* cond;
  std::vector<SelCond>* conds;

#line 86 "SqlParser.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE sqllval;

int sqlparse (void);

#endif /* !YY_SQL_SQLPARSER_TAB_H_INCLUDED  */