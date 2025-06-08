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
#include "force.h"

f8 apply_period(f8 position, Parameter *parameter, f8 cellMax);

f8 calculation_minimam(f8 rij, f8 cellMax);

#endif


