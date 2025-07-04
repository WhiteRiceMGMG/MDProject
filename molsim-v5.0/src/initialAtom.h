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
#ifndef INITIALATOM_H
#define INITIALATOM_H
#include <stdio.h>
#include "atom.h"
#include "parameter.h"

void initial_atom_position_lattice(Atom *atom, Parameter *parameter);


#endif