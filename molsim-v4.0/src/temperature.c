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

//現在の温度を指定されたステップごとに計算する．
void control_thermostat(Atom *atom, Parameter *parameter){
    u4 atomNum = parameter->atomNum;
    f8 *atomVelocity = atom->atomVelocity;
    f8 atomMass = parameter->atomMass;


    printf("hello,world");
}

