/*****************************************************************
 *  Filename     : temperature.c
 *  Description  : run
 *  Author       : Ogawa <ocmikanmgmg@gmail.com>
 *  Created      : Jun 7, 2025
 *  Compiler     : arm-none-eabi-gcc
 *  SBC          : Raspberry Pi Zero 2 W (32bit)
 *  License      : MIT License
 *  Note         : 
 *  History      : 2025/06/07 - ファイル作成
 *  　　　　　　　　　最終編集 2025/6/8
 *****************************************************************/
#include "temperature.h"

#define THREE_DIMENSION 3

void calculate_temperature(Atom *atom, Parameter *parameter){
    f8 *atomVelocity          = atom->atomVelocity;    
    u4 atomNum                = parameter->atomNum;
    f8 atomMass               = parameter->atomMass;
    f8 boltzmannVal           = parameter->boltzmannVal;
    f8 currentTemperature     = parameter->currentTemperature;
    f8 initialTemperature     = parameter->initialTemperature;
    u4 dimension              = 0;
    f8 temporaryTemperature   = 0;
    u4 i                      = 0;
    f8 temperatureCoefficient = 0;

    for (i = 0; i < atomNum; i++) {
        for(dimension = 0; dimension < THREE_DIMENSION; dimension++) {
            temporaryTemperature += atomVelocity[i * THREE_DIMENSION + dimension] 
                                    * atomVelocity[i * THREE_DIMENSION + dimension];
        }
    }
    parameter->currentTemperature 
                = temporaryTemperature * atomMass  / (3 * atomNum * boltzmannVal);
}

void control_temperature(Atom *atom, Parameter *parameter){
    printf("hello")
}
/*
    temperatureCoefficient = initialTemperature / currentTemperature;
    temperatureCoefficient *= temperatureCoefficient;
*/