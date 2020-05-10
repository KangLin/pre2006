/*******************************************************************************************************
文件名：EnumAndStructAndConst.h
功  能：象棋控件的枚举常、结构、常数的定义
作  者：康  林
版  本：1.0.0.1
日  期：2004-9-26
时  间：13:39:08
*******************************************************************************************************/
#if !defined(ENUMANDSTRUCTANDCONST_H)
#define ENUMANDSTRUCTANDCONST_H

#include "common.h"

/*typedef*/ enum ENUM_QiZi{RShuai = 1, RShi = 2, RXiang = 3, RMa = 4, RChe = 5, RPao = 6, RBing = 7,
              NoQiZi = 0, RQi = 1, BQi = -1,
              BShuai = -1, BShi = -2, BXiang = -3, BMa = -4, BChe = -5, BPao = -6, BBing = -7
} /*ENUM_QiZi*/;
/*typedef*/ enum ENUM_BianMa{BianMa, JieMa} /*ENUM_BianMa*/;
/*typedef*/ enum ENUM_ReturnValue{RETURNFALSE, BEIJIANGJUN, JIANGDUIMIAN, JIANGJUN, RETURNTRUE
} /*ENUM_ReturnValue*/;

ENUM_QiZi GetQiZiSide(ENUM_QiZi qz);

#define MAX_STRING_BUFFER 128

#endif //!defined(ENUMANDSTRUCTANDCONST_H)