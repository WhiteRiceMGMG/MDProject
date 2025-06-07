/*****************************************************************
 *  Filename     : atom.h
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
#include "sysdef.h"
#include "parameter.h"

#ifndef ATOM_H
#define ATOM_H

typedef struct Atom {
    u4 atomId;
    f8 atomPosition[3];
    f8 atomVelocity[3];
    f8 atomForce[3];
};

void initialize_atom(Atom *atom, Parameter *parameter);



#endif