/* A Bison parser, made by GNU Bison 1.875b.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Written by Richard Stallman by simplifying the original so called
   ``semantic'' parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0

/* If NAME_PREFIX is specified substitute the variables and functions
   names.  */
#define yyparse pcap_parse
#define yylex   pcap_lex
#define yyerror pcap_error
#define yylval  pcap_lval
#define yychar  pcap_char
#define yydebug pcap_debug
#define yynerrs pcap_nerrs


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     DST = 258,
     SRC = 259,
     HOST = 260,
     GATEWAY = 261,
     NET = 262,
     NETMASK = 263,
     PORT = 264,
     PORTRANGE = 265,
     LESS = 266,
     GREATER = 267,
     PROTO = 268,
     PROTOCHAIN = 269,
     CBYTE = 270,
     ARP = 271,
     RARP = 272,
     IP = 273,
     SCTP = 274,
     TCP = 275,
     UDP = 276,
     ICMP = 277,
     IGMP = 278,
     IGRP = 279,
     PIM = 280,
     VRRP = 281,
     ATALK = 282,
     AARP = 283,
     DECNET = 284,
     LAT = 285,
     SCA = 286,
     MOPRC = 287,
     MOPDL = 288,
     TK_BROADCAST = 289,
     TK_MULTICAST = 290,
     NUM = 291,
     INBOUND = 292,
     OUTBOUND = 293,
     PF_IFNAME = 294,
     PF_RSET = 295,
     PF_RNR = 296,
     PF_SRNR = 297,
     PF_REASON = 298,
     PF_ACTION = 299,
     LINK = 300,
     GEQ = 301,
     LEQ = 302,
     NEQ = 303,
     ID = 304,
     EID = 305,
     HID = 306,
     HID6 = 307,
     AID = 308,
     LSH = 309,
     RSH = 310,
     LEN = 311,
     IPV6 = 312,
     ICMPV6 = 313,
     AH = 314,
     ESP = 315,
     VLAN = 316,
     MPLS = 317,
     ISO = 318,
     ESIS = 319,
     CLNP = 320,
     ISIS = 321,
     L1 = 322,
     L2 = 323,
     IIH = 324,
     LSP = 325,
     SNP = 326,
     CSNP = 327,
     PSNP = 328,
     STP = 329,
     IPX = 330,
     NETBEUI = 331,
     LANE = 332,
     LLC = 333,
     METAC = 334,
     BCC = 335,
     SC = 336,
     ILMIC = 337,
     OAMF4EC = 338,
     OAMF4SC = 339,
     OAM = 340,
     OAMF4 = 341,
     CONNECTMSG = 342,
     METACONNECT = 343,
     VPI = 344,
     VCI = 345,
     RADIO = 346,
     SIO = 347,
     OPC = 348,
     DPC = 349,
     SLS = 350,
     AND = 351,
     OR = 352,
     UMINUS = 353
   };
#endif
#define DST 258
#define SRC 259
#define HOST 260
#define GATEWAY 261
#define NET 262
#define NETMASK 263
#define PORT 264
#define PORTRANGE 265
#define LESS 266
#define GREATER 267
#define PROTO 268
#define PROTOCHAIN 269
#define CBYTE 270
#define ARP 271
#define RARP 272
#define IP 273
#define SCTP 274
#define TCP 275
#define UDP 276
#define ICMP 277
#define IGMP 278
#define IGRP 279
#define PIM 280
#define VRRP 281
#define ATALK 282
#define AARP 283
#define DECNET 284
#define LAT 285
#define SCA 286
#define MOPRC 287
#define MOPDL 288
#define TK_BROADCAST 289
#define TK_MULTICAST 290
#define NUM 291
#define INBOUND 292
#define OUTBOUND 293
#define PF_IFNAME 294
#define PF_RSET 295
#define PF_RNR 296
#define PF_SRNR 297
#define PF_REASON 298
#define PF_ACTION 299
#define LINK 300
#define GEQ 301
#define LEQ 302
#define NEQ 303
#define ID 304
#define EID 305
#define HID 306
#define HID6 307
#define AID 308
#define LSH 309
#define RSH 310
#define LEN 311
#define IPV6 312
#define ICMPV6 313
#define AH 314
#define ESP 315
#define VLAN 316
#define MPLS 317
#define ISO 318
#define ESIS 319
#define CLNP 320
#define ISIS 321
#define L1 322
#define L2 323
#define IIH 324
#define LSP 325
#define SNP 326
#define CSNP 327
#define PSNP 328
#define STP 329
#define IPX 330
#define NETBEUI 331
#define LANE 332
#define LLC 333
#define METAC 334
#define BCC 335
#define SC 336
#define ILMIC 337
#define OAMF4EC 338
#define OAMF4SC 339
#define OAM 340
#define OAMF4 341
#define CONNECTMSG 342
#define METACONNECT 343
#define VPI 344
#define VCI 345
#define RADIO 346
#define SIO 347
#define OPC 348
#define DPC 349
#define SLS 350
#define AND 351
#define OR 352
#define UMINUS 353




/* Copy the first part of user declarations.  */
#line 1 "../libpcap/grammar.y"

/*
 * Copyright (c) 1988, 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that: (1) source code distributions
 * retain the above copyright notice and this paragraph in its entirety, (2)
 * distributions including binary code include the above copyright notice and
 * this paragraph in its entirety in the documentation or other materials
 * provided with the distribution, and (3) all advertising materials mentioning
 * features or use of this software display the following acknowledgement:
 * ``This product includes software developed by the University of California,
 * Lawrence Berkeley Laboratory and its contributors.'' Neither the name of
 * the University nor the names of its contributors may be used to endorse
 * or promote products derived from this software without specific prior
 * written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 */
#ifndef lint
static const char rcsid[] _U_ =
    "@(#) $Header: /tcpdump/master/libpcap/grammar.y,v 1.86.2.4 2005/06/20 21:30:17 guy Exp $ (LBL)";
#endif

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef WIN32
#include <pcap-stdinc.h>
#else /* WIN32 */
#include <sys/types.h>
#include <sys/socket.h>
#endif /* WIN32 */

#include <stdlib.h>

#ifndef WIN32
#if __STDC__
struct mbuf;
struct rtentry;
#endif

#include <netinet/in.h>
#endif /* WIN32 */

#include <stdio.h>

#include "pcap-int.h"

#include "gencode.h"
#include "pf.h"
#include <pcap-namedb.h>

#ifdef HAVE_OS_PROTO_H
#include "os-proto.h"
#endif

#define QSET(q, p, d, a) (q).proto = (p),\
			 (q).dir = (d),\
			 (q).addr = (a)

int n_errors = 0;

static struct qual qerr = { Q_UNDEF, Q_UNDEF, Q_UNDEF, Q_UNDEF };

static void
yyerror(char *msg)
{
	++n_errors;
	bpf_error("%s", msg);
	/* NOTREACHED */
}

#ifndef YYBISON
int yyparse(void);

int
pcap_parse()
{
	return (yyparse());
}
#endif



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 90 "../libpcap/grammar.y"
typedef union YYSTYPE {
	int i;
	bpf_u_int32 h;
	u_char *e;
	char *s;
	struct stmt *stmt;
	struct arth *a;
	struct {
		struct qual q;
		int atmfieldtype;
		int mtp3fieldtype;
		struct block *b;
	} blk;
	struct block *rblk;
} YYSTYPE;
/* Line 191 of yacc.c.  */
#line 386 "y.tab.c"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 214 of yacc.c.  */
#line 398 "y.tab.c"

#if ! defined (yyoverflow) || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# if YYSTACK_USE_ALLOCA
#  define YYSTACK_ALLOC alloca
# else
#  ifndef YYSTACK_USE_ALLOCA
#   if defined (alloca) || defined (_ALLOCA_H)
#    define YYSTACK_ALLOC alloca
#   else
#    ifdef __GNUC__
#     define YYSTACK_ALLOC __builtin_alloca
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC malloc
#  define YYSTACK_FREE free
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif

#if defined (__STDC__) || defined (__cplusplus)
   typedef signed char yysigned_char;
#else
   typedef short yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   583

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  114
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  40
/* YYNRULES -- Number of rules. */
#define YYNRULES  180
/* YYNRULES -- Number of states. */
#define YYNSTATES  248

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   353

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    98,     2,     2,     2,     2,   100,     2,
     107,   106,   103,   101,     2,   102,     2,   104,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   113,     2,
     110,   109,   108,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   111,     2,   112,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    99,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,   105
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short yyprhs[] =
{
       0,     0,     3,     6,     8,     9,    11,    15,    19,    23,
      27,    29,    31,    33,    35,    39,    41,    45,    49,    51,
      55,    57,    59,    61,    64,    66,    68,    70,    74,    78,
      80,    82,    84,    87,    91,    94,    97,   100,   103,   106,
     109,   113,   115,   119,   123,   125,   127,   129,   132,   135,
     137,   138,   140,   142,   146,   150,   154,   158,   160,   162,
     164,   166,   168,   170,   172,   174,   176,   178,   180,   182,
     184,   186,   188,   190,   192,   194,   196,   198,   200,   202,
     204,   206,   208,   210,   212,   214,   216,   218,   220,   222,
     224,   226,   228,   230,   232,   234,   236,   238,   240,   242,
     244,   247,   250,   253,   256,   261,   263,   265,   268,   270,
     273,   275,   277,   280,   283,   286,   289,   292,   295,   297,
     299,   301,   303,   305,   307,   309,   311,   313,   315,   317,
     322,   329,   333,   337,   341,   345,   349,   353,   357,   361,
     364,   368,   370,   372,   374,   376,   378,   380,   382,   386,
     388,   390,   392,   394,   396,   398,   400,   402,   404,   406,
     408,   410,   412,   414,   416,   419,   422,   426,   428,   430,
     434,   436,   438,   440,   442,   444,   447,   450,   454,   456,
     458
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const short yyrhs[] =
{
     115,     0,    -1,   116,   117,    -1,   116,    -1,    -1,   126,
      -1,   117,   118,   126,    -1,   117,   118,   120,    -1,   117,
     119,   126,    -1,   117,   119,   120,    -1,    96,    -1,    97,
      -1,   121,    -1,   143,    -1,   123,   124,   106,    -1,    49,
      -1,    51,   104,    36,    -1,    51,     8,    51,    -1,    51,
      -1,    52,   104,    36,    -1,    52,    -1,    50,    -1,    53,
      -1,   122,   120,    -1,    98,    -1,   107,    -1,   121,    -1,
     125,   118,   120,    -1,   125,   119,   120,    -1,   143,    -1,
     124,    -1,   128,    -1,   122,   126,    -1,   129,   130,   131,
      -1,   129,   130,    -1,   129,   131,    -1,   129,    13,    -1,
     129,    14,    -1,   129,   132,    -1,   127,   120,    -1,   123,
     117,   106,    -1,   133,    -1,   140,   138,   140,    -1,   140,
     139,   140,    -1,   134,    -1,   144,    -1,   145,    -1,   146,
     147,    -1,   150,   151,    -1,   133,    -1,    -1,     4,    -1,
       3,    -1,     4,    97,     3,    -1,     3,    97,     4,    -1,
       4,    96,     3,    -1,     3,    96,     4,    -1,     5,    -1,
       7,    -1,     9,    -1,    10,    -1,     6,    -1,    45,    -1,
      18,    -1,    16,    -1,    17,    -1,    19,    -1,    20,    -1,
      21,    -1,    22,    -1,    23,    -1,    24,    -1,    25,    -1,
      26,    -1,    27,    -1,    28,    -1,    29,    -1,    30,    -1,
      31,    -1,    33,    -1,    32,    -1,    57,    -1,    58,    -1,
      59,    -1,    60,    -1,    63,    -1,    64,    -1,    66,    -1,
      67,    -1,    68,    -1,    69,    -1,    70,    -1,    71,    -1,
      73,    -1,    72,    -1,    65,    -1,    74,    -1,    75,    -1,
      76,    -1,    91,    -1,   129,    34,    -1,   129,    35,    -1,
      11,    36,    -1,    12,    36,    -1,    15,    36,   142,    36,
      -1,    37,    -1,    38,    -1,    61,   143,    -1,    61,    -1,
      62,   143,    -1,    62,    -1,   135,    -1,    39,    49,    -1,
      40,    49,    -1,    41,    36,    -1,    42,    36,    -1,    43,
     136,    -1,    44,   137,    -1,    36,    -1,    49,    -1,    49,
      -1,   108,    -1,    46,    -1,   109,    -1,    47,    -1,   110,
      -1,    48,    -1,   143,    -1,   141,    -1,   133,   111,   140,
     112,    -1,   133,   111,   140,   113,    36,   112,    -1,   140,
     101,   140,    -1,   140,   102,   140,    -1,   140,   103,   140,
      -1,   140,   104,   140,    -1,   140,   100,   140,    -1,   140,
      99,   140,    -1,   140,    54,   140,    -1,   140,    55,   140,
      -1,   102,   140,    -1,   123,   141,   106,    -1,    56,    -1,
     100,    -1,    99,    -1,   110,    -1,   108,    -1,   109,    -1,
      36,    -1,   123,   143,   106,    -1,    77,    -1,    78,    -1,
      79,    -1,    80,    -1,    83,    -1,    84,    -1,    81,    -1,
      82,    -1,    85,    -1,    86,    -1,    87,    -1,    88,    -1,
      89,    -1,    90,    -1,   148,    -1,   138,    36,    -1,   139,
      36,    -1,   123,   149,   106,    -1,    36,    -1,   148,    -1,
     149,   119,   148,    -1,    92,    -1,    93,    -1,    94,    -1,
      95,    -1,   152,    -1,   138,    36,    -1,   139,    36,    -1,
     123,   153,   106,    -1,    36,    -1,   152,    -1,   153,   119,
     152,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short yyrline[] =
{
       0,   159,   159,   163,   165,   167,   168,   169,   170,   171,
     173,   175,   177,   178,   180,   182,   183,   185,   187,   192,
     201,   210,   219,   228,   230,   232,   234,   235,   236,   238,
     240,   242,   243,   245,   246,   247,   248,   249,   250,   252,
     253,   254,   255,   257,   259,   260,   261,   262,   263,   266,
     267,   270,   271,   272,   273,   274,   275,   278,   279,   280,
     281,   284,   286,   287,   288,   289,   290,   291,   292,   293,
     294,   295,   296,   297,   298,   299,   300,   301,   302,   303,
     304,   305,   306,   307,   308,   309,   310,   311,   312,   313,
     314,   315,   316,   317,   318,   319,   320,   321,   322,   323,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   339,   340,   341,   342,   343,   344,   347,   348,
     361,   372,   373,   374,   376,   377,   378,   380,   381,   383,
     384,   385,   386,   387,   388,   389,   390,   391,   392,   393,
     394,   395,   397,   398,   399,   400,   401,   403,   404,   406,
     407,   408,   409,   410,   411,   412,   413,   415,   416,   417,
     418,   421,   422,   424,   425,   426,   427,   429,   436,   437,
     440,   441,   442,   443,   445,   446,   447,   448,   450,   459,
     460
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "DST", "SRC", "HOST", "GATEWAY", "NET", 
  "NETMASK", "PORT", "PORTRANGE", "LESS", "GREATER", "PROTO", 
  "PROTOCHAIN", "CBYTE", "ARP", "RARP", "IP", "SCTP", "TCP", "UDP", 
  "ICMP", "IGMP", "IGRP", "PIM", "VRRP", "ATALK", "AARP", "DECNET", "LAT", 
  "SCA", "MOPRC", "MOPDL", "TK_BROADCAST", "TK_MULTICAST", "NUM", 
  "INBOUND", "OUTBOUND", "PF_IFNAME", "PF_RSET", "PF_RNR", "PF_SRNR", 
  "PF_REASON", "PF_ACTION", "LINK", "GEQ", "LEQ", "NEQ", "ID", "EID", 
  "HID", "HID6", "AID", "LSH", "RSH", "LEN", "IPV6", "ICMPV6", "AH", 
  "ESP", "VLAN", "MPLS", "ISO", "ESIS", "CLNP", "ISIS", "L1", "L2", "IIH", 
  "LSP", "SNP", "CSNP", "PSNP", "STP", "IPX", "NETBEUI", "LANE", "LLC", 
  "METAC", "BCC", "SC", "ILMIC", "OAMF4EC", "OAMF4SC", "OAM", "OAMF4", 
  "CONNECTMSG", "METACONNECT", "VPI", "VCI", "RADIO", "SIO", "OPC", "DPC", 
  "SLS", "AND", "OR", "'!'", "'|'", "'&'", "'+'", "'-'", "'*'", "'/'", 
  "UMINUS", "')'", "'('", "'>'", "'='", "'<'", "'['", "']'", "':'", 
  "$accept", "prog", "null", "expr", "and", "or", "id", "nid", "not", 
  "paren", "pid", "qid", "term", "head", "rterm", "pqual", "dqual", 
  "aqual", "ndaqual", "pname", "other", "pfvar", "reason", "action", 
  "relop", "irelop", "arth", "narth", "byteop", "pnum", "atmtype", 
  "atmmultitype", "atmfield", "atmvalue", "atmfieldvalue", "atmlistvalue", 
  "mtp3field", "mtp3value", "mtp3fieldvalue", "mtp3listvalue", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,    33,   124,
      38,    43,    45,    42,    47,   353,    41,    40,    62,    61,
      60,    91,    93,    58
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,   114,   115,   115,   116,   117,   117,   117,   117,   117,
     118,   119,   120,   120,   120,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   122,   123,   124,   124,   124,   125,
     125,   126,   126,   127,   127,   127,   127,   127,   127,   128,
     128,   128,   128,   128,   128,   128,   128,   128,   128,   129,
     129,   130,   130,   130,   130,   130,   130,   131,   131,   131,
     131,   132,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     134,   134,   134,   134,   134,   134,   134,   134,   134,   134,
     134,   134,   135,   135,   135,   135,   135,   135,   136,   136,
     137,   138,   138,   138,   139,   139,   139,   140,   140,   141,
     141,   141,   141,   141,   141,   141,   141,   141,   141,   141,
     141,   141,   142,   142,   142,   142,   142,   143,   143,   144,
     144,   144,   144,   144,   144,   144,   144,   145,   145,   145,
     145,   146,   146,   147,   147,   147,   147,   148,   149,   149,
     150,   150,   150,   150,   151,   151,   151,   151,   152,   153,
     153
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     2,     1,     0,     1,     3,     3,     3,     3,
       1,     1,     1,     1,     3,     1,     3,     3,     1,     3,
       1,     1,     1,     2,     1,     1,     1,     3,     3,     1,
       1,     1,     2,     3,     2,     2,     2,     2,     2,     2,
       3,     1,     3,     3,     1,     1,     1,     2,     2,     1,
       0,     1,     1,     3,     3,     3,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     2,     2,     2,     4,     1,     1,     2,     1,     2,
       1,     1,     2,     2,     2,     2,     2,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     4,
       6,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       3,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     3,     1,     1,     3,
       1,     1,     1,     1,     1,     2,     2,     3,     1,     1,
       3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       4,     0,    50,     1,     0,     0,     0,    64,    65,    63,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    80,    79,   147,   105,   106,     0,     0,
       0,     0,     0,     0,    62,   141,    81,    82,    83,    84,
     108,   110,    85,    86,    95,    87,    88,    89,    90,    91,
      92,    94,    93,    96,    97,    98,   149,   150,   151,   152,
     155,   156,   153,   154,   157,   158,   159,   160,   161,   162,
      99,   170,   171,   172,   173,    24,     0,    25,     2,    50,
      50,     5,     0,    31,     0,    49,    44,   111,     0,   128,
     127,    45,    46,     0,     0,   102,   103,     0,   112,   113,
     114,   115,   118,   119,   116,   120,   117,     0,   107,   109,
       0,     0,   139,    10,    11,    50,    50,    32,     0,   128,
     127,    15,    21,    18,    20,    22,    39,    12,     0,     0,
      13,    52,    51,    57,    61,    58,    59,    60,    36,    37,
     100,   101,    34,    35,    38,     0,   122,   124,   126,     0,
       0,     0,     0,     0,     0,     0,     0,   121,   123,   125,
       0,     0,   167,     0,     0,     0,    47,   163,   178,     0,
       0,     0,    48,   174,   143,   142,   145,   146,   144,     0,
       0,     0,     7,    50,    50,     6,   127,     9,     8,    40,
     140,   148,     0,     0,     0,    23,    26,    30,     0,    29,
       0,     0,     0,     0,    33,     0,   137,   138,   136,   135,
     131,   132,   133,   134,    42,    43,   168,     0,   164,   165,
     179,     0,   175,   176,   104,   127,    17,    16,    19,    14,
       0,     0,    56,    54,    55,    53,   129,     0,   166,     0,
     177,     0,    27,    28,     0,   169,   180,   130
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short yydefgoto[] =
{
      -1,     1,     2,   118,   115,   116,   195,   127,   128,   110,
     197,   198,    81,    82,    83,    84,   142,   143,   144,   111,
      86,    87,   104,   106,   160,   161,    88,    89,   179,    90,
      91,    92,    93,   166,   167,   217,    94,   172,   173,   221
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -178
static const short yypact[] =
{
    -178,     9,   194,  -178,   -22,    -8,    -1,  -178,  -178,  -178,
    -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,
    -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,    -4,    19,
      11,    15,   -18,    35,  -178,  -178,  -178,  -178,  -178,  -178,
     -14,   -14,  -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,
    -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,
    -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,
    -178,  -178,  -178,  -178,  -178,  -178,   472,  -178,   -77,   380,
     380,  -178,    67,  -178,    20,     1,  -178,  -178,   468,  -178,
    -178,  -178,  -178,   137,   473,  -178,  -178,   -50,  -178,  -178,
    -178,  -178,  -178,  -178,  -178,  -178,  -178,   -14,  -178,  -178,
     472,   -58,  -178,  -178,  -178,   287,   287,  -178,   -27,   -49,
     -10,  -178,  -178,     7,     0,  -178,  -178,  -178,    67,    67,
    -178,   -25,    65,  -178,  -178,  -178,  -178,  -178,  -178,  -178,
    -178,  -178,   150,  -178,  -178,   472,  -178,  -178,  -178,   472,
     472,   472,   472,   472,   472,   472,   472,  -178,  -178,  -178,
     472,   472,  -178,    66,    79,    92,  -178,  -178,  -178,   103,
     106,   112,  -178,  -178,  -178,  -178,  -178,  -178,  -178,   120,
     -10,    99,  -178,   287,   287,  -178,     4,  -178,  -178,  -178,
    -178,  -178,   107,   134,   135,  -178,  -178,    69,   -77,   -10,
     168,   172,   174,   175,  -178,   -38,    42,    42,   329,   452,
      60,    60,  -178,  -178,    99,    99,  -178,   -54,  -178,  -178,
    -178,     2,  -178,  -178,  -178,    41,  -178,  -178,  -178,  -178,
      67,    67,  -178,  -178,  -178,  -178,  -178,   143,  -178,    66,
    -178,   103,  -178,  -178,    68,  -178,  -178,  -178
};

/* YYPGOTO[NTERM-NUM].  */
static const short yypgoto[] =
{
    -178,  -178,  -178,   184,   -11,  -177,   -79,  -117,     6,    -2,
    -178,  -178,   -74,  -178,  -178,  -178,  -178,    46,  -178,     8,
    -178,  -178,  -178,  -178,    73,    75,   -20,   -78,  -178,   -34,
    -178,  -178,  -178,  -178,  -150,  -178,  -178,  -178,  -158,  -178
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -42
static const short yytable[] =
{
      80,   -41,   119,   126,   -13,   117,   108,   109,    79,     3,
      85,   220,   196,   216,    95,   192,   149,   150,   102,   113,
     114,   231,    25,   131,   132,   133,   134,   135,    96,   136,
     137,   103,   119,   138,   139,    97,   182,   187,   107,   107,
     239,   185,   188,   114,   241,    98,   120,   100,   130,   174,
     175,   101,   238,   145,   140,   141,   112,   190,   176,   177,
     178,   151,   152,   153,   154,   155,   156,   196,    99,   113,
     114,   200,   201,   180,   236,   237,   120,    80,    80,   189,
     129,   186,   186,   246,   105,    79,    79,    85,    85,   245,
     181,   163,   169,    77,   130,   199,   191,   -41,   -41,   114,
     -13,   -13,   162,    25,   194,   107,   119,   -41,   240,   117,
     -13,   193,   145,   184,   184,   218,   121,   122,   123,   124,
     125,   183,   183,    85,    85,   205,   129,   107,   219,   206,
     207,   208,   209,   210,   211,   212,   213,   -29,   -29,   168,
     214,   215,   222,   153,   154,   155,   156,   191,   223,   186,
     225,   242,   243,   149,   150,   133,   224,   135,   226,   136,
     137,   202,   203,   155,   156,    75,   164,   170,   165,   171,
     227,   228,   232,   162,    77,   229,   233,   234,   235,   244,
     247,   184,    80,   146,   147,   148,    78,   230,   204,   183,
     183,    85,    85,     0,    -3,     0,   130,   130,   151,   152,
     153,   154,   155,   156,     0,     4,     5,     0,     0,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,   129,   129,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
       0,     0,     0,     0,    77,   157,   158,   159,     0,     0,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
       0,     0,    75,     0,     0,     0,    76,     0,     4,     5,
       0,    77,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,     0,     0,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,     0,     0,     0,   121,   122,   123,   124,
     125,     0,     0,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,   149,   150,    75,     0,     0,     0,    76,
       0,     4,     5,     0,    77,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,     0,     0,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,     0,     0,     0,   152,
     153,   154,   155,   156,     0,     0,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,     0,     0,    75,     0,
       0,     0,    76,     0,     0,     0,     0,    77,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,   149,   150,    25,   168,
       0,     0,     0,     0,   146,   147,   148,    34,     0,   146,
     147,   148,   149,   150,     0,     0,     0,     0,    35,    36,
      37,    38,    39,     0,     0,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,     0,
       0,     0,     0,   153,   154,   155,   156,     0,     0,     0,
       0,     0,     0,    70,     0,     0,     0,   151,   152,   153,
     154,   155,   156,     0,    76,     0,   157,   158,   159,    77,
      77,   157,   158,   159
};

static const short yycheck[] =
{
       2,     0,    80,    82,     0,    79,    40,    41,     2,     0,
       2,   169,   129,   163,    36,     8,    54,    55,    36,    96,
      97,   198,    36,     3,     4,     5,     6,     7,    36,     9,
      10,    49,   110,    13,    14,    36,   115,   116,    40,    41,
     217,   115,   116,    97,   221,    49,    80,    36,    82,    99,
     100,    36,   106,   111,    34,    35,    76,   106,   108,   109,
     110,    99,   100,   101,   102,   103,   104,   184,    49,    96,
      97,    96,    97,   107,   112,   113,   110,    79,    80,   106,
      82,   115,   116,   241,    49,    79,    80,    79,    80,   239,
     110,    93,    94,   107,   128,   129,   106,    96,    97,    97,
      96,    97,    36,    36,   104,   107,   184,   106,   106,   183,
     106,   104,   111,   115,   116,    36,    49,    50,    51,    52,
      53,   115,   116,   115,   116,   145,   128,   129,    36,   149,
     150,   151,   152,   153,   154,   155,   156,    96,    97,    36,
     160,   161,    36,   101,   102,   103,   104,   106,    36,   183,
     184,   230,   231,    54,    55,     5,    36,     7,    51,     9,
      10,    96,    97,   103,   104,    98,    93,    94,    93,    94,
      36,    36,     4,    36,   107,   106,     4,     3,     3,    36,
     112,   183,   184,    46,    47,    48,     2,   198,   142,   183,
     184,   183,   184,    -1,     0,    -1,   230,   231,    99,   100,
     101,   102,   103,   104,    -1,    11,    12,    -1,    -1,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,   230,   231,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      -1,    -1,    -1,    -1,   107,   108,   109,   110,    -1,    -1,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      -1,    -1,    98,    -1,    -1,    -1,   102,    -1,    11,    12,
      -1,   107,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    -1,    -1,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    -1,    -1,    -1,    49,    50,    51,    52,
      53,    -1,    -1,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    54,    55,    98,    -1,    -1,    -1,   102,
      -1,    11,    12,    -1,   107,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    -1,    -1,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    -1,    -1,    -1,   100,
     101,   102,   103,   104,    -1,    -1,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    -1,    -1,    98,    -1,
      -1,    -1,   102,    -1,    -1,    -1,    -1,   107,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    54,    55,    36,    36,
      -1,    -1,    -1,    -1,    46,    47,    48,    45,    -1,    46,
      47,    48,    54,    55,    -1,    -1,    -1,    -1,    56,    57,
      58,    59,    60,    -1,    -1,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    -1,
      -1,    -1,    -1,   101,   102,   103,   104,    -1,    -1,    -1,
      -1,    -1,    -1,    91,    -1,    -1,    -1,    99,   100,   101,
     102,   103,   104,    -1,   102,    -1,   108,   109,   110,   107,
     107,   108,   109,   110
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,   115,   116,     0,    11,    12,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    98,   102,   107,   117,   122,
     123,   126,   127,   128,   129,   133,   134,   135,   140,   141,
     143,   144,   145,   146,   150,    36,    36,    36,    49,    49,
      36,    36,    36,    49,   136,    49,   137,   123,   143,   143,
     123,   133,   140,    96,    97,   118,   119,   126,   117,   141,
     143,    49,    50,    51,    52,    53,   120,   121,   122,   123,
     143,     3,     4,     5,     6,     7,     9,    10,    13,    14,
      34,    35,   130,   131,   132,   111,    46,    47,    48,    54,
      55,    99,   100,   101,   102,   103,   104,   108,   109,   110,
     138,   139,    36,   123,   138,   139,   147,   148,    36,   123,
     138,   139,   151,   152,    99,   100,   108,   109,   110,   142,
     143,   140,   120,   122,   123,   126,   143,   120,   126,   106,
     106,   106,     8,   104,   104,   120,   121,   124,   125,   143,
      96,    97,    96,    97,   131,   140,   140,   140,   140,   140,
     140,   140,   140,   140,   140,   140,   148,   149,    36,    36,
     152,   153,    36,    36,    36,   143,    51,    36,    36,   106,
     118,   119,     4,     4,     3,     3,   112,   113,   106,   119,
     106,   119,   120,   120,    36,   148,   152,   112
};

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrlab1


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)         \
  Current.first_line   = Rhs[1].first_line;      \
  Current.first_column = Rhs[1].first_column;    \
  Current.last_line    = Rhs[N].last_line;       \
  Current.last_column  = Rhs[N].last_column;
#endif

/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (0)

# define YYDSYMPRINT(Args)			\
do {						\
  if (yydebug)					\
    yysymprint Args;				\
} while (0)

# define YYDSYMPRINTF(Title, Token, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr, 					\
                  Token, Value);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (cinluded).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short *bottom, short *top)
#else
static void
yy_stack_print (bottom, top)
    short *bottom;
    short *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (/* Nothing. */; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_reduce_print (int yyrule)
#else
static void
yy_reduce_print (yyrule)
    int yyrule;
#endif
{
  int yyi;
  unsigned int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %u), ",
             yyrule - 1, yylno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname [yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname [yyr1[yyrule]]);
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (Rule);		\
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YYDSYMPRINT(Args)
# define YYDSYMPRINTF(Title, Token, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

#endif /* !YYERROR_VERBOSE */



#if YYDEBUG
/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep)
#else
static void
yysymprint (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  if (yytype < YYNTOKENS)
    {
      YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
# ifdef YYPRINT
      YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
    }
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyoutput, ")");
}

#endif /* ! YYDEBUG */
/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yydestruct (int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yytype, yyvaluep)
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  switch (yytype)
    {

      default:
        break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM);
# else
int yyparse ();
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM)
# else
int yyparse (YYPARSE_PARAM)
  void *YYPARSE_PARAM;
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;



#define YYPOPSTACK   (yyvsp--, yyssp--)

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* When reducing, the number of symbols on the RHS of the reduced
     rule.  */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	short *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YYDSYMPRINTF ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %s, ", yytname[yytoken]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;


  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 160 "../libpcap/grammar.y"
    {
	finish_parse(yyvsp[0].blk.b);
}
    break;

  case 4:
#line 165 "../libpcap/grammar.y"
    { yyval.blk.q = qerr; }
    break;

  case 6:
#line 168 "../libpcap/grammar.y"
    { gen_and(yyvsp[-2].blk.b, yyvsp[0].blk.b); yyval.blk = yyvsp[0].blk; }
    break;

  case 7:
#line 169 "../libpcap/grammar.y"
    { gen_and(yyvsp[-2].blk.b, yyvsp[0].blk.b); yyval.blk = yyvsp[0].blk; }
    break;

  case 8:
#line 170 "../libpcap/grammar.y"
    { gen_or(yyvsp[-2].blk.b, yyvsp[0].blk.b); yyval.blk = yyvsp[0].blk; }
    break;

  case 9:
#line 171 "../libpcap/grammar.y"
    { gen_or(yyvsp[-2].blk.b, yyvsp[0].blk.b); yyval.blk = yyvsp[0].blk; }
    break;

  case 10:
#line 173 "../libpcap/grammar.y"
    { yyval.blk = yyvsp[-1].blk; }
    break;

  case 11:
#line 175 "../libpcap/grammar.y"
    { yyval.blk = yyvsp[-1].blk; }
    break;

  case 13:
#line 178 "../libpcap/grammar.y"
    { yyval.blk.b = gen_ncode(NULL, (bpf_u_int32)yyvsp[0].i,
						   yyval.blk.q = yyvsp[-1].blk.q); }
    break;

  case 14:
#line 180 "../libpcap/grammar.y"
    { yyval.blk = yyvsp[-1].blk; }
    break;

  case 15:
#line 182 "../libpcap/grammar.y"
    { yyval.blk.b = gen_scode(yyvsp[0].s, yyval.blk.q = yyvsp[-1].blk.q); }
    break;

  case 16:
#line 183 "../libpcap/grammar.y"
    { yyval.blk.b = gen_mcode(yyvsp[-2].s, NULL, yyvsp[0].i,
				    yyval.blk.q = yyvsp[-3].blk.q); }
    break;

  case 17:
#line 185 "../libpcap/grammar.y"
    { yyval.blk.b = gen_mcode(yyvsp[-2].s, yyvsp[0].s, 0,
				    yyval.blk.q = yyvsp[-3].blk.q); }
    break;

  case 18:
#line 187 "../libpcap/grammar.y"
    {
				  /* Decide how to parse HID based on proto */
				  yyval.blk.q = yyvsp[-1].blk.q;
				  yyval.blk.b = gen_ncode(yyvsp[0].s, 0, yyval.blk.q);
				}
    break;

  case 19:
#line 192 "../libpcap/grammar.y"
    {
#ifdef INET6
				  yyval.blk.b = gen_mcode6(yyvsp[-2].s, NULL, yyvsp[0].i,
				    yyval.blk.q = yyvsp[-3].blk.q);
#else
				  bpf_error("'ip6addr/prefixlen' not supported "
					"in this configuration");
#endif /*INET6*/
				}
    break;

  case 20:
#line 201 "../libpcap/grammar.y"
    {
#ifdef INET6
				  yyval.blk.b = gen_mcode6(yyvsp[0].s, 0, 128,
				    yyval.blk.q = yyvsp[-1].blk.q);
#else
				  bpf_error("'ip6addr' not supported "
					"in this configuration");
#endif /*INET6*/
				}
    break;

  case 21:
#line 210 "../libpcap/grammar.y"
    { 
				  yyval.blk.b = gen_ecode(yyvsp[0].e, yyval.blk.q = yyvsp[-1].blk.q);
				  /*
				   * $1 was allocated by "pcap_ether_aton()",
				   * so we must free it now that we're done
				   * with it.
				   */
				  free(yyvsp[0].e);
				}
    break;

  case 22:
#line 219 "../libpcap/grammar.y"
    {
				  yyval.blk.b = gen_acode(yyvsp[0].e, yyval.blk.q = yyvsp[-1].blk.q);
				  /*
				   * $1 was allocated by "pcap_ether_aton()",
				   * so we must free it now that we're done
				   * with it.
				   */
				  free(yyvsp[0].e);
				}
    break;

  case 23:
#line 228 "../libpcap/grammar.y"
    { gen_not(yyvsp[0].blk.b); yyval.blk = yyvsp[0].blk; }
    break;

  case 24:
#line 230 "../libpcap/grammar.y"
    { yyval.blk = yyvsp[-1].blk; }
    break;

  case 25:
#line 232 "../libpcap/grammar.y"
    { yyval.blk = yyvsp[-1].blk; }
    break;

  case 27:
#line 235 "../libpcap/grammar.y"
    { gen_and(yyvsp[-2].blk.b, yyvsp[0].blk.b); yyval.blk = yyvsp[0].blk; }
    break;

  case 28:
#line 236 "../libpcap/grammar.y"
    { gen_or(yyvsp[-2].blk.b, yyvsp[0].blk.b); yyval.blk = yyvsp[0].blk; }
    break;

  case 29:
#line 238 "../libpcap/grammar.y"
    { yyval.blk.b = gen_ncode(NULL, (bpf_u_int32)yyvsp[0].i,
						   yyval.blk.q = yyvsp[-1].blk.q); }
    break;

  case 32:
#line 243 "../libpcap/grammar.y"
    { gen_not(yyvsp[0].blk.b); yyval.blk = yyvsp[0].blk; }
    break;

  case 33:
#line 245 "../libpcap/grammar.y"
    { QSET(yyval.blk.q, yyvsp[-2].i, yyvsp[-1].i, yyvsp[0].i); }
    break;

  case 34:
#line 246 "../libpcap/grammar.y"
    { QSET(yyval.blk.q, yyvsp[-1].i, yyvsp[0].i, Q_DEFAULT); }
    break;

  case 35:
#line 247 "../libpcap/grammar.y"
    { QSET(yyval.blk.q, yyvsp[-1].i, Q_DEFAULT, yyvsp[0].i); }
    break;

  case 36:
#line 248 "../libpcap/grammar.y"
    { QSET(yyval.blk.q, yyvsp[-1].i, Q_DEFAULT, Q_PROTO); }
    break;

  case 37:
#line 249 "../libpcap/grammar.y"
    { QSET(yyval.blk.q, yyvsp[-1].i, Q_DEFAULT, Q_PROTOCHAIN); }
    break;

  case 38:
#line 250 "../libpcap/grammar.y"
    { QSET(yyval.blk.q, yyvsp[-1].i, Q_DEFAULT, yyvsp[0].i); }
    break;

  case 39:
#line 252 "../libpcap/grammar.y"
    { yyval.blk = yyvsp[0].blk; }
    break;

  case 40:
#line 253 "../libpcap/grammar.y"
    { yyval.blk.b = yyvsp[-1].blk.b; yyval.blk.q = yyvsp[-2].blk.q; }
    break;

  case 41:
#line 254 "../libpcap/grammar.y"
    { yyval.blk.b = gen_proto_abbrev(yyvsp[0].i); yyval.blk.q = qerr; }
    break;

  case 42:
#line 255 "../libpcap/grammar.y"
    { yyval.blk.b = gen_relation(yyvsp[-1].i, yyvsp[-2].a, yyvsp[0].a, 0);
				  yyval.blk.q = qerr; }
    break;

  case 43:
#line 257 "../libpcap/grammar.y"
    { yyval.blk.b = gen_relation(yyvsp[-1].i, yyvsp[-2].a, yyvsp[0].a, 1);
				  yyval.blk.q = qerr; }
    break;

  case 44:
#line 259 "../libpcap/grammar.y"
    { yyval.blk.b = yyvsp[0].rblk; yyval.blk.q = qerr; }
    break;

  case 45:
#line 260 "../libpcap/grammar.y"
    { yyval.blk.b = gen_atmtype_abbrev(yyvsp[0].i); yyval.blk.q = qerr; }
    break;

  case 46:
#line 261 "../libpcap/grammar.y"
    { yyval.blk.b = gen_atmmulti_abbrev(yyvsp[0].i); yyval.blk.q = qerr; }
    break;

  case 47:
#line 262 "../libpcap/grammar.y"
    { yyval.blk.b = yyvsp[0].blk.b; yyval.blk.q = qerr; }
    break;

  case 48:
#line 263 "../libpcap/grammar.y"
    { yyval.blk.b = yyvsp[0].blk.b; yyval.blk.q = qerr; }
    break;

  case 50:
#line 267 "../libpcap/grammar.y"
    { yyval.i = Q_DEFAULT; }
    break;

  case 51:
#line 270 "../libpcap/grammar.y"
    { yyval.i = Q_SRC; }
    break;

  case 52:
#line 271 "../libpcap/grammar.y"
    { yyval.i = Q_DST; }
    break;

  case 53:
#line 272 "../libpcap/grammar.y"
    { yyval.i = Q_OR; }
    break;

  case 54:
#line 273 "../libpcap/grammar.y"
    { yyval.i = Q_OR; }
    break;

  case 55:
#line 274 "../libpcap/grammar.y"
    { yyval.i = Q_AND; }
    break;

  case 56:
#line 275 "../libpcap/grammar.y"
    { yyval.i = Q_AND; }
    break;

  case 57:
#line 278 "../libpcap/grammar.y"
    { yyval.i = Q_HOST; }
    break;

  case 58:
#line 279 "../libpcap/grammar.y"
    { yyval.i = Q_NET; }
    break;

  case 59:
#line 280 "../libpcap/grammar.y"
    { yyval.i = Q_PORT; }
    break;

  case 60:
#line 281 "../libpcap/grammar.y"
    { yyval.i = Q_PORTRANGE; }
    break;

  case 61:
#line 284 "../libpcap/grammar.y"
    { yyval.i = Q_GATEWAY; }
    break;

  case 62:
#line 286 "../libpcap/grammar.y"
    { yyval.i = Q_LINK; }
    break;

  case 63:
#line 287 "../libpcap/grammar.y"
    { yyval.i = Q_IP; }
    break;

  case 64:
#line 288 "../libpcap/grammar.y"
    { yyval.i = Q_ARP; }
    break;

  case 65:
#line 289 "../libpcap/grammar.y"
    { yyval.i = Q_RARP; }
    break;

  case 66:
#line 290 "../libpcap/grammar.y"
    { yyval.i = Q_SCTP; }
    break;

  case 67:
#line 291 "../libpcap/grammar.y"
    { yyval.i = Q_TCP; }
    break;

  case 68:
#line 292 "../libpcap/grammar.y"
    { yyval.i = Q_UDP; }
    break;

  case 69:
#line 293 "../libpcap/grammar.y"
    { yyval.i = Q_ICMP; }
    break;

  case 70:
#line 294 "../libpcap/grammar.y"
    { yyval.i = Q_IGMP; }
    break;

  case 71:
#line 295 "../libpcap/grammar.y"
    { yyval.i = Q_IGRP; }
    break;

  case 72:
#line 296 "../libpcap/grammar.y"
    { yyval.i = Q_PIM; }
    break;

  case 73:
#line 297 "../libpcap/grammar.y"
    { yyval.i = Q_VRRP; }
    break;

  case 74:
#line 298 "../libpcap/grammar.y"
    { yyval.i = Q_ATALK; }
    break;

  case 75:
#line 299 "../libpcap/grammar.y"
    { yyval.i = Q_AARP; }
    break;

  case 76:
#line 300 "../libpcap/grammar.y"
    { yyval.i = Q_DECNET; }
    break;

  case 77:
#line 301 "../libpcap/grammar.y"
    { yyval.i = Q_LAT; }
    break;

  case 78:
#line 302 "../libpcap/grammar.y"
    { yyval.i = Q_SCA; }
    break;

  case 79:
#line 303 "../libpcap/grammar.y"
    { yyval.i = Q_MOPDL; }
    break;

  case 80:
#line 304 "../libpcap/grammar.y"
    { yyval.i = Q_MOPRC; }
    break;

  case 81:
#line 305 "../libpcap/grammar.y"
    { yyval.i = Q_IPV6; }
    break;

  case 82:
#line 306 "../libpcap/grammar.y"
    { yyval.i = Q_ICMPV6; }
    break;

  case 83:
#line 307 "../libpcap/grammar.y"
    { yyval.i = Q_AH; }
    break;

  case 84:
#line 308 "../libpcap/grammar.y"
    { yyval.i = Q_ESP; }
    break;

  case 85:
#line 309 "../libpcap/grammar.y"
    { yyval.i = Q_ISO; }
    break;

  case 86:
#line 310 "../libpcap/grammar.y"
    { yyval.i = Q_ESIS; }
    break;

  case 87:
#line 311 "../libpcap/grammar.y"
    { yyval.i = Q_ISIS; }
    break;

  case 88:
#line 312 "../libpcap/grammar.y"
    { yyval.i = Q_ISIS_L1; }
    break;

  case 89:
#line 313 "../libpcap/grammar.y"
    { yyval.i = Q_ISIS_L2; }
    break;

  case 90:
#line 314 "../libpcap/grammar.y"
    { yyval.i = Q_ISIS_IIH; }
    break;

  case 91:
#line 315 "../libpcap/grammar.y"
    { yyval.i = Q_ISIS_LSP; }
    break;

  case 92:
#line 316 "../libpcap/grammar.y"
    { yyval.i = Q_ISIS_SNP; }
    break;

  case 93:
#line 317 "../libpcap/grammar.y"
    { yyval.i = Q_ISIS_PSNP; }
    break;

  case 94:
#line 318 "../libpcap/grammar.y"
    { yyval.i = Q_ISIS_CSNP; }
    break;

  case 95:
#line 319 "../libpcap/grammar.y"
    { yyval.i = Q_CLNP; }
    break;

  case 96:
#line 320 "../libpcap/grammar.y"
    { yyval.i = Q_STP; }
    break;

  case 97:
#line 321 "../libpcap/grammar.y"
    { yyval.i = Q_IPX; }
    break;

  case 98:
#line 322 "../libpcap/grammar.y"
    { yyval.i = Q_NETBEUI; }
    break;

  case 99:
#line 323 "../libpcap/grammar.y"
    { yyval.i = Q_RADIO; }
    break;

  case 100:
#line 325 "../libpcap/grammar.y"
    { yyval.rblk = gen_broadcast(yyvsp[-1].i); }
    break;

  case 101:
#line 326 "../libpcap/grammar.y"
    { yyval.rblk = gen_multicast(yyvsp[-1].i); }
    break;

  case 102:
#line 327 "../libpcap/grammar.y"
    { yyval.rblk = gen_less(yyvsp[0].i); }
    break;

  case 103:
#line 328 "../libpcap/grammar.y"
    { yyval.rblk = gen_greater(yyvsp[0].i); }
    break;

  case 104:
#line 329 "../libpcap/grammar.y"
    { yyval.rblk = gen_byteop(yyvsp[-1].i, yyvsp[-2].i, yyvsp[0].i); }
    break;

  case 105:
#line 330 "../libpcap/grammar.y"
    { yyval.rblk = gen_inbound(0); }
    break;

  case 106:
#line 331 "../libpcap/grammar.y"
    { yyval.rblk = gen_inbound(1); }
    break;

  case 107:
#line 332 "../libpcap/grammar.y"
    { yyval.rblk = gen_vlan(yyvsp[0].i); }
    break;

  case 108:
#line 333 "../libpcap/grammar.y"
    { yyval.rblk = gen_vlan(-1); }
    break;

  case 109:
#line 334 "../libpcap/grammar.y"
    { yyval.rblk = gen_mpls(yyvsp[0].i); }
    break;

  case 110:
#line 335 "../libpcap/grammar.y"
    { yyval.rblk = gen_mpls(-1); }
    break;

  case 111:
#line 336 "../libpcap/grammar.y"
    { yyval.rblk = yyvsp[0].rblk; }
    break;

  case 112:
#line 339 "../libpcap/grammar.y"
    { yyval.rblk = gen_pf_ifname(yyvsp[0].s); }
    break;

  case 113:
#line 340 "../libpcap/grammar.y"
    { yyval.rblk = gen_pf_ruleset(yyvsp[0].s); }
    break;

  case 114:
#line 341 "../libpcap/grammar.y"
    { yyval.rblk = gen_pf_rnr(yyvsp[0].i); }
    break;

  case 115:
#line 342 "../libpcap/grammar.y"
    { yyval.rblk = gen_pf_srnr(yyvsp[0].i); }
    break;

  case 116:
#line 343 "../libpcap/grammar.y"
    { yyval.rblk = gen_pf_reason(yyvsp[0].i); }
    break;

  case 117:
#line 344 "../libpcap/grammar.y"
    { yyval.rblk = gen_pf_action(yyvsp[0].i); }
    break;

  case 118:
#line 347 "../libpcap/grammar.y"
    { yyval.i = yyvsp[0].i; }
    break;

  case 119:
#line 348 "../libpcap/grammar.y"
    { const char *reasons[] = PFRES_NAMES;
				  int i;
				  for (i = 0; reasons[i]; i++) {
					  if (pcap_strcasecmp(yyvsp[0].s, reasons[i]) == 0) {
						  yyval.i = i;
						  break;
					  }
				  }
				  if (reasons[i] == NULL)
					  bpf_error("unknown PF reason");
				}
    break;

  case 120:
#line 361 "../libpcap/grammar.y"
    { if (pcap_strcasecmp(yyvsp[0].s, "pass") == 0 ||
				      pcap_strcasecmp(yyvsp[0].s, "accept") == 0)
					yyval.i = PF_PASS;
				  else if (pcap_strcasecmp(yyvsp[0].s, "drop") == 0 ||
				      pcap_strcasecmp(yyvsp[0].s, "block") == 0)
					yyval.i = PF_DROP;
				  else
					  bpf_error("unknown PF action");
				}
    break;

  case 121:
#line 372 "../libpcap/grammar.y"
    { yyval.i = BPF_JGT; }
    break;

  case 122:
#line 373 "../libpcap/grammar.y"
    { yyval.i = BPF_JGE; }
    break;

  case 123:
#line 374 "../libpcap/grammar.y"
    { yyval.i = BPF_JEQ; }
    break;

  case 124:
#line 376 "../libpcap/grammar.y"
    { yyval.i = BPF_JGT; }
    break;

  case 125:
#line 377 "../libpcap/grammar.y"
    { yyval.i = BPF_JGE; }
    break;

  case 126:
#line 378 "../libpcap/grammar.y"
    { yyval.i = BPF_JEQ; }
    break;

  case 127:
#line 380 "../libpcap/grammar.y"
    { yyval.a = gen_loadi(yyvsp[0].i); }
    break;

  case 129:
#line 383 "../libpcap/grammar.y"
    { yyval.a = gen_load(yyvsp[-3].i, yyvsp[-1].a, 1); }
    break;

  case 130:
#line 384 "../libpcap/grammar.y"
    { yyval.a = gen_load(yyvsp[-5].i, yyvsp[-3].a, yyvsp[-1].i); }
    break;

  case 131:
#line 385 "../libpcap/grammar.y"
    { yyval.a = gen_arth(BPF_ADD, yyvsp[-2].a, yyvsp[0].a); }
    break;

  case 132:
#line 386 "../libpcap/grammar.y"
    { yyval.a = gen_arth(BPF_SUB, yyvsp[-2].a, yyvsp[0].a); }
    break;

  case 133:
#line 387 "../libpcap/grammar.y"
    { yyval.a = gen_arth(BPF_MUL, yyvsp[-2].a, yyvsp[0].a); }
    break;

  case 134:
#line 388 "../libpcap/grammar.y"
    { yyval.a = gen_arth(BPF_DIV, yyvsp[-2].a, yyvsp[0].a); }
    break;

  case 135:
#line 389 "../libpcap/grammar.y"
    { yyval.a = gen_arth(BPF_AND, yyvsp[-2].a, yyvsp[0].a); }
    break;

  case 136:
#line 390 "../libpcap/grammar.y"
    { yyval.a = gen_arth(BPF_OR, yyvsp[-2].a, yyvsp[0].a); }
    break;

  case 137:
#line 391 "../libpcap/grammar.y"
    { yyval.a = gen_arth(BPF_LSH, yyvsp[-2].a, yyvsp[0].a); }
    break;

  case 138:
#line 392 "../libpcap/grammar.y"
    { yyval.a = gen_arth(BPF_RSH, yyvsp[-2].a, yyvsp[0].a); }
    break;

  case 139:
#line 393 "../libpcap/grammar.y"
    { yyval.a = gen_neg(yyvsp[0].a); }
    break;

  case 140:
#line 394 "../libpcap/grammar.y"
    { yyval.a = yyvsp[-1].a; }
    break;

  case 141:
#line 395 "../libpcap/grammar.y"
    { yyval.a = gen_loadlen(); }
    break;

  case 142:
#line 397 "../libpcap/grammar.y"
    { yyval.i = '&'; }
    break;

  case 143:
#line 398 "../libpcap/grammar.y"
    { yyval.i = '|'; }
    break;

  case 144:
#line 399 "../libpcap/grammar.y"
    { yyval.i = '<'; }
    break;

  case 145:
#line 400 "../libpcap/grammar.y"
    { yyval.i = '>'; }
    break;

  case 146:
#line 401 "../libpcap/grammar.y"
    { yyval.i = '='; }
    break;

  case 148:
#line 404 "../libpcap/grammar.y"
    { yyval.i = yyvsp[-1].i; }
    break;

  case 149:
#line 406 "../libpcap/grammar.y"
    { yyval.i = A_LANE; }
    break;

  case 150:
#line 407 "../libpcap/grammar.y"
    { yyval.i = A_LLC; }
    break;

  case 151:
#line 408 "../libpcap/grammar.y"
    { yyval.i = A_METAC;	}
    break;

  case 152:
#line 409 "../libpcap/grammar.y"
    { yyval.i = A_BCC; }
    break;

  case 153:
#line 410 "../libpcap/grammar.y"
    { yyval.i = A_OAMF4EC; }
    break;

  case 154:
#line 411 "../libpcap/grammar.y"
    { yyval.i = A_OAMF4SC; }
    break;

  case 155:
#line 412 "../libpcap/grammar.y"
    { yyval.i = A_SC; }
    break;

  case 156:
#line 413 "../libpcap/grammar.y"
    { yyval.i = A_ILMIC; }
    break;

  case 157:
#line 415 "../libpcap/grammar.y"
    { yyval.i = A_OAM; }
    break;

  case 158:
#line 416 "../libpcap/grammar.y"
    { yyval.i = A_OAMF4; }
    break;

  case 159:
#line 417 "../libpcap/grammar.y"
    { yyval.i = A_CONNECTMSG; }
    break;

  case 160:
#line 418 "../libpcap/grammar.y"
    { yyval.i = A_METACONNECT; }
    break;

  case 161:
#line 421 "../libpcap/grammar.y"
    { yyval.blk.atmfieldtype = A_VPI; }
    break;

  case 162:
#line 422 "../libpcap/grammar.y"
    { yyval.blk.atmfieldtype = A_VCI; }
    break;

  case 164:
#line 425 "../libpcap/grammar.y"
    { yyval.blk.b = gen_atmfield_code(yyvsp[-2].blk.atmfieldtype, (bpf_int32)yyvsp[0].i, (bpf_u_int32)yyvsp[-1].i, 0); }
    break;

  case 165:
#line 426 "../libpcap/grammar.y"
    { yyval.blk.b = gen_atmfield_code(yyvsp[-2].blk.atmfieldtype, (bpf_int32)yyvsp[0].i, (bpf_u_int32)yyvsp[-1].i, 1); }
    break;

  case 166:
#line 427 "../libpcap/grammar.y"
    { yyval.blk.b = yyvsp[-1].blk.b; yyval.blk.q = qerr; }
    break;

  case 167:
#line 429 "../libpcap/grammar.y"
    {
	yyval.blk.atmfieldtype = yyvsp[-1].blk.atmfieldtype;
	if (yyval.blk.atmfieldtype == A_VPI ||
	    yyval.blk.atmfieldtype == A_VCI)
		yyval.blk.b = gen_atmfield_code(yyval.blk.atmfieldtype, (bpf_int32) yyvsp[0].i, BPF_JEQ, 0);
	}
    break;

  case 169:
#line 437 "../libpcap/grammar.y"
    { gen_or(yyvsp[-2].blk.b, yyvsp[0].blk.b); yyval.blk = yyvsp[0].blk; }
    break;

  case 170:
#line 440 "../libpcap/grammar.y"
    { yyval.blk.mtp3fieldtype = M_SIO; }
    break;

  case 171:
#line 441 "../libpcap/grammar.y"
    { yyval.blk.mtp3fieldtype = M_OPC; }
    break;

  case 172:
#line 442 "../libpcap/grammar.y"
    { yyval.blk.mtp3fieldtype = M_DPC; }
    break;

  case 173:
#line 443 "../libpcap/grammar.y"
    { yyval.blk.mtp3fieldtype = M_SLS; }
    break;

  case 175:
#line 446 "../libpcap/grammar.y"
    { yyval.blk.b = gen_mtp3field_code(yyvsp[-2].blk.mtp3fieldtype, (u_int)yyvsp[0].i, (u_int)yyvsp[-1].i, 0); }
    break;

  case 176:
#line 447 "../libpcap/grammar.y"
    { yyval.blk.b = gen_mtp3field_code(yyvsp[-2].blk.mtp3fieldtype, (u_int)yyvsp[0].i, (u_int)yyvsp[-1].i, 1); }
    break;

  case 177:
#line 448 "../libpcap/grammar.y"
    { yyval.blk.b = yyvsp[-1].blk.b; yyval.blk.q = qerr; }
    break;

  case 178:
#line 450 "../libpcap/grammar.y"
    {
	yyval.blk.mtp3fieldtype = yyvsp[-1].blk.mtp3fieldtype;
	if (yyval.blk.mtp3fieldtype == M_SIO ||
	    yyval.blk.mtp3fieldtype == M_OPC ||
	    yyval.blk.mtp3fieldtype == M_DPC ||
	    yyval.blk.mtp3fieldtype == M_SLS )
		yyval.blk.b = gen_mtp3field_code(yyval.blk.mtp3fieldtype, (u_int) yyvsp[0].i, BPF_JEQ, 0);
	}
    break;

  case 180:
#line 460 "../libpcap/grammar.y"
    { gen_or(yyvsp[-2].blk.b, yyvsp[0].blk.b); yyval.blk = yyvsp[0].blk; }
    break;


    }

/* Line 999 of yacc.c.  */
#line 2514 "y.tab.c"

  yyvsp -= yylen;
  yyssp -= yylen;


  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (YYPACT_NINF < yyn && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  int yytype = YYTRANSLATE (yychar);
	  const char* yyprefix;
	  char *yymsg;
	  int yyx;

	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  int yyxbegin = yyn < 0 ? -yyn : 0;

	  /* Stay within bounds of both yycheck and yytname.  */
	  int yychecklim = YYLAST - yyn;
	  int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
	  int yycount = 0;

	  yyprefix = ", expecting ";
	  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      {
		yysize += yystrlen (yyprefix) + yystrlen (yytname [yyx]);
		yycount += 1;
		if (yycount == 5)
		  {
		    yysize = 0;
		    break;
		  }
	      }
	  yysize += (sizeof ("syntax error, unexpected ")
		     + yystrlen (yytname[yytype]));
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "syntax error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[yytype]);

	      if (yycount < 5)
		{
		  yyprefix = ", expecting ";
		  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
		    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
		      {
			yyp = yystpcpy (yyp, yyprefix);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yyprefix = " or ";
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("syntax error; also virtual memory exhausted");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror ("syntax error");
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      /* Return failure if at end of input.  */
      if (yychar == YYEOF)
        {
	  /* Pop the error token.  */
          YYPOPSTACK;
	  /* Pop the rest of the stack.  */
	  while (yyss < yyssp)
	    {
	      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
	      yydestruct (yystos[*yyssp], yyvsp);
	      YYPOPSTACK;
	    }
	  YYABORT;
        }

      YYDSYMPRINTF ("Error: discarding", yytoken, &yylval, &yylloc);
      yydestruct (yytoken, &yylval);
      yychar = YYEMPTY;

    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*----------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action.  |
`----------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
      yydestruct (yystos[yystate], yyvsp);
      yyvsp--;
      yystate = *--yyssp;

      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;


  yystate = yyn;
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

#ifndef yyoverflow
/*----------------------------------------------.
| yyoverflowlab -- parser overflow comes here.  |
`----------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 462 "../libpcap/grammar.y"


