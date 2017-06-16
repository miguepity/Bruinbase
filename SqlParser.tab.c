/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         sqlparse
#define yylex           sqllex
#define yyerror         sqlerror
#define yydebug         sqldebug
#define yynerrs         sqlnerrs

#define yylval          sqllval
#define yychar          sqlchar

/* Copy the first part of user declarations.  */
#line 1 "SqlParser.y" /* yacc.c:339  */

#include <cstdio>
#include <cstring>
#include <sys/times.h>
#include <unistd.h>
#include <climits>
#include <string>
#include "Bruinbase.h"
#include "SqlEngine.h" 
#include "PageFile.h"

int  sqllex(void);  
void sqlerror(const char *str) { fprintf(stderr, "Error: %s\n", str); }
extern "C" { int  sqlwrap() { return 1; } }

static void runSelect(int attr, const char* table, const std::vector<SelCond>& conds)
{
  struct tms tmsbuf;
  clock_t btime, etime;
  int     bpagecnt, epagecnt;

  btime = times(&tmsbuf);
  bpagecnt = PageFile::getPageReadCount();
  SqlEngine::select(attr, table, conds);
  etime = times(&tmsbuf);
  epagecnt = PageFile::getPageReadCount();

  fprintf(stderr, "  -- %.3f seconds to run the select command. Read %d pages\n", ((float)(etime - btime))/sysconf(_SC_CLK_TCK), epagecnt - bpagecnt);
}


#line 106 "SqlParser.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "SqlParser.tab.h".  */
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
#line 33 "SqlParser.y" /* yacc.c:355  */

  int integer;
  char* string;
  SelCond* cond;
  std::vector<SelCond>* conds;

#line 178 "SqlParser.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE sqllval;

int sqlparse (void);

#endif /* !YY_SQL_SQLPARSER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 195 "SqlParser.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif