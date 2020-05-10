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
/* Line 1252 of yacc.c.  */
#line 249 "y.tab.h"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE pcap_lval;



