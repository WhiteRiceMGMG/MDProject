/*****************************************************************
 *  Filename     : force.c
 *  Description  : to calcration time step
 *  Author       : Ogawa <ocmikanmgmg@gmail.com>
 *  Created      : Jun 7, 2025
 *  Compiler     : arm-none-eabi-gcc
 *  SBC          : Raspberry Pi Zero 2 W
 *  License      : MIT License
 *  Note         : 
 *  History      : 2025/06/07 - ファイル作成
 *                 力の初期化を削除．責務はatom.cに．
 *****************************************************************/
#include <stdio.h>
#include <math.h>
#include "force.h"

#define THREE_DIMENSION 3

void calculation_force(Atom *atom, Parameter *parameter) {
    u4 i                    = 0; 
    u4 j                    = 0;
    u1 dimension            = 0;
    f8 rij[THREE_DIMENSION] = 0;
    f8 r2                   = 0;
    f8 r6                   = 0;
    f8 r12                  = 0;
    f8 fij                  = 0;
    f8 fMeg                 = 0;
    f8 epsilon              = parameter -> epsilonVal;
    f8 sigma                = parameter -> sigmaVal;
    f8 cutoff               = parameter -> cutoffCoefficient * sigma;
    f8 cutoff2              = cutoff * cutoff;

    for(i = 0; i < parameter -> atomNum; i++) {
        (atom + i) -> atomId = i;
        for(dimension = 0; dimension < THREE_DIMENSION; dimension++) {
            *((atom + i) -> atomForce + dimension) = 0;
        }
    }

    for(i = 0; i < parameter -> atomNum - 1; i++) {
        for(j = i + 1; j < parameter -> atomNum; j++) {
            r2 = 0;
            for(dimension = 0; dimension < THREE_DIMENSION; dimension++) {
                rij[dimension] = atom[j].atomPosition[dimension] 
                                   - atom[i].atomPosition[dimension];
                r2 += rij[dimension] * rij[dimension];
            }
            if(r2 < cutoff2) {
                r6 = (sigma * sigma) / r2;
                r6 = r6 * r6 * r6;
                r12 = r6 * r6;
                fMeg = 24 * epsilon * (2 * r12 - r6) / r2;
                for(dimension = 0; dimension < 3; dimension++) {
                    fij = fMeg * rij[dimension];
                    atom[i].atomForce[dimension] += fij;
                    atom[j].atomForce[dimension] -= fij;
                }
            }
        }
    }
}