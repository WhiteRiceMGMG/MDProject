/*****************************************************************
 *  Filename     : atom.c
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
#include <stdlib.h>
#include "atom.h"
#include "parameter.h"

#define THREE_DIMENSION 3

void initialize_atom(Atom *atom, Parameter *parameter) {
    u4 i = 0;
    u1 dimension = 0;
    for (i = 0; i < parameter->atomNum; i++) {
        (atom + i) -> atomId = i;
        for(dimension = 0; dimension < THREE_DIMENSION; dimension++) {
            *((atom + i)->atomPosition + dimension) = 0;
            *((atom + i)->atomVelocity + dimension) = 0;
            *((atom + i)->atomForce + dimension) = 0;
        }
    }
}
