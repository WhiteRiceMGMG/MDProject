/*****************************************************************
 *  Filename     : boundary.c
 *  Description  : to calcration time step
 *  Author       : Ogawa <ocmikanmgmg@gmail.com>
 *  Created      : Jun 7, 2025
 *  Compiler     : arm-none-eabi-gcc
 *  SBC          : Raspberry Pi Zero 2 W
 *  License      : MIT License
 *  Note         : 
 *  History      : 2025/06/07 - ファイル作成
 *****************************************************************/
#include <stdio.h>
#include <math.h>
#include "boundary.h"

void apply_period(Atom *atom, Parameter *parameter) {
    //rijElementがcellSizeの範囲外に出た時，境界条件適応する．
    if 
}
