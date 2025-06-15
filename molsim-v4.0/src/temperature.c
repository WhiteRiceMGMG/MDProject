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

void control_thermostat(Atom *atom, Parameter *parameter){
    f8 *atomVelocity        = atom->atomVelocity;    
    u4 atomNum              = parameter->atomNum;
    f8 atomMass             = parameter->atomMass;
    f8 boltzmannVal         = parameter->boltzmannVal;
    u4 dimension            = 0;
    f8 temporaryTemperature = 0;
    u4 i                    = 0;


    for (i = 0; i < atomNum; i++) {
        for(dimension = 0; dimension < THREE_DIMENSION; dimension++) {
            temporaryTemperature += atomMass * atomVelocity[dimension] * atomVelocity[dimension]; 
        }
    }
    parameter->currentTemperature = temporaryTemperature / 3 * atomNum * boltzmannVal;


    printf("hello,world");
}

