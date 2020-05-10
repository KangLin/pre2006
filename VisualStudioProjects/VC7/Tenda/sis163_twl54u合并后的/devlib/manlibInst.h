/*
 *  Copyright © 2001 Atheros Communications, Inc.,  All Rights Reserved.
 */
/* manlibInst.h - Exported functions and defines for mInst.c */

#ifndef	__INCmanlibinsth
#define	__INCmanlibinsth
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ident  "ACI $Id: //depot/sw/src/dk/mdk/manlib/manlibInst.h#1 $, $Header: //depot/sw/src/dk/mdk/manlib/manlibInst.h#1 $"

// temperature control models
#define TMP_LB300                       0x01

// spectrum analyzer models
#define SPA_E4404B                      0x01
#define SPA_E4405B                      SPA_E4404B  // define them to be same for now
#define SPA_8595E                       0x02
#define SPA_R3162                       0x03

#define SPA_DET_NEG                     0x01
#define SPA_DET_POS                     0x02
#define SPA_DET_SAMPLE                  0x03

#define SPA_E4404B_MAX_SWEEP_POINTS     401
#define SPA_E4405B_MAX_SWEEP_POINTS     401
#define SPA_8595E_MAX_SWEEP_POINTS      401
#define SPA_R3162_MAX_SWEEP_POINTS      1001
#define SPA_MAX_SWEEP_POINTS            SPA_R3162_MAX_SWEEP_POINTS

// power meter models
#define PM_436A                         0x01
#define PM_E4416A                       0x02
#define PM_4531                         0X03
#define NRP_Z11                         0x04

// attenuator models
#define ATT_11713A                      0x01
#define ATT_11713A_110                  0x02

// power supply models
#define PS_E3631A                       0x01
#define PS_P6V                          0x01
#define PS_P25V                         0x02
#define PS_N25V                         0x03

#ifndef SWIG



// Spectrum Analyzer Functions
int spaInit(const int adr, const int model); 
double spaMeasChannelPower(const int ud, const double center, const double span,const int reset);


int spaMeasSpectralMask (const int ud, const double center, const double span, 
							const int reset, const int verbose, const int output);
int spaMeasSpectralMask11b (const int ud, const double center, const double span, 
							const int reset, const int verbose, const int output);
#endif // #ifndef SWIG

#ifdef __cplusplus
}
#endif

#endif // __INCmanlibinsth
