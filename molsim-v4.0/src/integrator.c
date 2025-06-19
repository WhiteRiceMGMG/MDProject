/*****************************************************************
 *  Filename     : integrator.c
 *  Description  : to calcration time step
 *  Author       : Ogawa <ocmikanmgmg@gmail.com>
 *  Created      : Jun 7, 2025
 *  Compiler     : arm-none-eabi-gcc
 *  SBC          : Raspberry Pi Zero 2 W
 *  License      : MIT License
 *  Note         : 
 *  History      : 2025/06/07 - ファイル作成
 *****************************************************************/
#include "integrator.h"

#define THREE_DIMENSION 3

void velocity_verlet(Atom *atom, Parameter *parameter) {
    u4 i            = 0;
    u4 dimension    = 0;
    f8 acceleration = 0;
    f8 cellSize[3]  = {0};
    u4 atomNum      = parameter -> atomNum;
    f8 mass         = parameter -> atomMass;
    f8 timeStep     = parameter -> timeStep;
    f8 halfTimeStep = timeStep * 0.5; 

    for(dimension = 0; dimension < THREE_DIMENSION; dimension++) {
        cellSize[dimension] = parameter->cellSize[dimension];
    }

    for(i = 0; i < atomNum; i++) {
        for(dimension = 0; dimension < THREE_DIMENSION; dimension++) {
            acceleration = atom[i].atomForce[dimension] / mass;
            atom[i].atomVelocity[dimension] += halfTimeStep * acceleration;
        }
    }
    
    for(i = 0; i < atomNum; i++) {
        for(dimension = 0; dimension < THREE_DIMENSION; dimension++) {
            atom[i].atomPosition[dimension] += timeStep * atom[i].atomVelocity[dimension];
            //↓ポインタ渡ししたかったけど，iとdimensionも渡すのがめんどいのと，多分渡す値自体もf8で軽いからこうした．
            //引数にparameter構造体を指定しているが，多分ここは削れると思う．
            atom[i].atomPosition[dimension] = apply_period(atom[i].atomPosition[dimension], parameter,cellSize[dimension]); 
        }
    }




    for(i = 0; i < atomNum; i++) {
        for(dimension = 0; dimension < THREE_DIMENSION; dimension++) {
            acceleration = atom[i].atomForce[dimension] / mass;
            atom[i].atomVelocity[dimension] += halfTimeStep * acceleration;
        }
    }

    /*ここら辺から速度スケーリング法適応したい． */
    void control_temperature(Atom *atom, Parameter *parameter);
    
}



