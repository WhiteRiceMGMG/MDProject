/*****************************************************************
 *  Filename     : parameter.h
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

#ifndef PARAMETER_H
#define PARAMETER_H

typedef struct {
    u4 atomNum;
    u4 simulationStep;
    f8 timeStep;
    f8 epsilonVal;
    f8 sigmaVal;
    f8 atomMass;
    f8 cutoffCoefficient;
    f8 cellSize[3];
    f8 atomInterval;
    f8 initialTemperature;
    f8 currentTemperature;
    f8 boltzmannVal;
} Parameter;


#endif



