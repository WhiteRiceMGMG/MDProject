/*****************************************************************
 *  Filename     : output.h
 *  Description  : run
 *  Author       : Ogawa <ocmikanmgmg@gmail.com>
 *  Created      : Jun 7, 2025
 *  Compiler     : arm-none-eabi-gcc
 *  SBC          : Raspberry Pi Zero 2 W (32bit)
 *  License      : MIT License
 *  Note         : 
 *  History      : 2025/06/07 - ファイル作成
 *  最終編集 2025/6/8
 *****************************************************************/
#ifndef OUTPUT_H
#define OUTPUT_H
#include <stdio.h>
#include "sysdef.h"
#include "atom.h"
#include "parameter.h"

void write_file(Atom *atom, Parameter *parameter, u4 step);


#endif