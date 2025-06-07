/*****************************************************************
 *  Filename     : integrator.h
 *  Description  : to calcration time step
 *  Author       : Ogawa <ocmikanmgmg@gmail.com>
 *  Created      : Jun 7, 2025
 *  Compiler     : arm-none-eabi-gcc
 *  SBC          : Raspberry Pi Zero 2 W
 *  License      : MIT License
 *  Note         : 
 *  History      : 2025/06/07 - ファイル作成
 *****************************************************************/
#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include <stdio.h>
#include "parameter.h"
#include "sysdef.h"
#include "atom.h"
#include "force.h"

void velocity_verlet(Atom *atom, Parameter *parameter);


#endif
