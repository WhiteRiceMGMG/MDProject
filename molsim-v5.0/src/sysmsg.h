/*****************************************************************
 *  Filename     : sysmsg.h
 *  Description  : to calcration time step
 *  Author       : Ogawa <ocmikanmgmg@gmail.com>
 *  Created      : Jun 7, 2025
 *  Compiler     : arm-none-eabi-gcc
 *  SBC          : Raspberry Pi Zero 2 W
 *  License      : MIT License
 *  Note         : 
 *  History      : 2025/06/07 - ファイル作成
 *****************************************************************/
#ifndef SYSMSG_H
#define SYSMSG_H

#include <stdio.h>
#include <unistd.h>
#include "parameter.h"
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>


void system_message(Parameter *parameter);

void initialize_log(void);

void simulation_log(void);

void end_log(void);

void error_log(void);

#endif
