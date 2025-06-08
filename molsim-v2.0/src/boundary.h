/*****************************************************************
 *  Filename     : boundary.h
 *  Description  : to calcration time step
 *  Author       : Ogawa <ocmikanmgmg@gmail.com>
 *  Created      : Jun 7, 2025
 *  Compiler     : arm-none-eabi-gcc
 *  SBC          : Raspberry Pi Zero 2 W
 *  License      : MIT License
 *  Note         : 
 *  History      : 2025/06/07 - ファイル作成
 *****************************************************************/
#ifndef BOUNDARY_H
#define BOUNDARY_H

#include <stdio.h>
#include "sysdef.h"
#include "parameter.h"
#include "atom.h"

void apply_period(Atom *atom, Parameter *parameter);

void calculation_minimau(Atom *atom, Parameter *parameter);

#endif


