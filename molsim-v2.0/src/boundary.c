/*****************************************************************
 *  Filename     : boundary.c
 *  Description  : to calcration time step
 *  Author       : Ogawa <ocmikanmgmg@gmail.com>
 *  Created      : Jun 7, 2025
 *  Compiler     : arm-none-eabi-gcc
 *  SBC          : Raspberry Pi Zero 2 W
 *  License      : MIT License
 *  Note         : 
 *  History      : 2025/06/08 - ファイル作成
 *****************************************************************/
#include <stdio.h>
#include <math.h>
#include "boundary.h"

f8 apply_period(f8 position, Parameter *parameter, f8 cellMax) {
    
    while (position >= cellMax) {
        position -= cellMax;
    }
    while (position < 0) {
        position += cellMax;
    }
    return position;
}

f8 calculation_minimam(f8 rij, f8 cellMax) {

    if(rij < 0.5 * cellMax) {
        rij -= cellMax;
    } else if(rij < -0.5 * cellMax) {
        rij += cellMax;
    } else {
        ;
    }
    

    return rij;
}



