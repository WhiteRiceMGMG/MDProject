/*****************************************************************
 *  Filename     : main.c
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
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include "parameter.h"
#include "atom.h"
#include "force.h"
#include "integrator.h"
#include "sysmsg.h"
#include "output.h"
#include "temperature.h"

// 標準正規分布を生成する関数（Box-Muller法）
double rand_normal(double mean, double stddev) {
    double u1 = ((double)rand() + 1.0) / ((double)RAND_MAX + 2.0);
    double u2 = ((double)rand() + 1.0) / ((double)RAND_MAX + 2.0);
    return mean + stddev * sqrt(-2.0 * log(u1)) * cos(2.0 * M_PI * u2);
}

int main(void) {
    Parameter *parameter = (Parameter *)malloc(sizeof(Parameter));
    
    parameter->atomNum            = 100;    /*原子の数*/
    parameter->simulationStep     = 100;    /*シミュレーションステップ*/
    parameter->timeStep           = 0.1;    /*1ステップあたりの時間*/
    parameter->epsilonVal         = 1.0;  /*原子間の引力*/
    parameter->sigmaVal           = 1.0;  /*ポテンシャルエネルギー最小位置*/
    parameter->atomMass           = 1.0;  /*原子質量*/
    parameter->cutoffCoefficient  = 2.5;  /*カットオフ距離*/
    parameter->cellSize[0]        = 20;    /*X方向のセルの長さ*/
    parameter->cellSize[1]        = 20;    /*Y方向のセルの長さ*/
    parameter->cellSize[2]        = 20;    /*Z方向のセルの長さ*/
    parameter->atomInterval       = 1;    /*初期原子間距離*/
    parameter->initialTemperature = 300;    /*初期温度*/
    parameter->currentTemperature = 1;    /*現在の温度*/
    parameter->boltzmannVal       = 1;    /*ボルツマン定数*/

    system_message(parameter);
    

    Atom *atom = (Atom *)malloc(sizeof(Atom) * parameter->atomNum);
    initialize_atom(atom, parameter);
//-----------------------------------------------------------
    double kT_over_m = parameter->boltzmannVal * parameter->initialTemperature / parameter->atomMass;
    double stddev = sqrt(kT_over_m); 

    for (u4 i = 0; i < parameter->atomNum; i++) {
        for (u4 d = 0; d < 3; d++) {
            atom[i].atomVelocity[d] = rand_normal(0.0, stddev); 
        }
    }

    double vcm[3] = {0.0, 0.0, 0.0};
    for (u4 i = 0; i < parameter->atomNum; i++) {
        for (u4 d = 0; d < 3; d++) {
            vcm[d] += atom[i].atomVelocity[d];
        }
    }
    for (u4 d = 0; d < 3; d++) {
        vcm[d] /= parameter->atomNum;
    }
    for (u4 i = 0; i < parameter->atomNum; i++) {
        for (u4 d = 0; d < 3; d++) {
            atom[i].atomVelocity[d] -= vcm[d]; 
        }
    }    
//-----------------------------------------------------------
    // ランダム配置（最小距離を考慮）
    double minDistance = 1.0; // 原子間の最小距離
    srand(time(NULL)); // ランダムシードを設定

    for (u4 i = 0; i < parameter->atomNum; i++) {
        int valid = 0;
        while (!valid) {
            valid = 1; // 配置が有効か仮定
            for (u4 dimension = 0; dimension < 3; dimension++) {
                atom[i].atomPosition[dimension] =
                    ((double)rand() / RAND_MAX) * parameter->cellSize[dimension];
            }
            for (u4 j = 0; j < i; j++) {
                double distanceSquared = 0.0;
                for (u4 dimension = 0; dimension < 3; dimension++) {
                    double diff = atom[i].atomPosition[dimension] - atom[j].atomPosition[dimension];
                    distanceSquared += diff * diff;
                }
                if (sqrt(distanceSquared) < minDistance) {
                    valid = 0; // 配置をやり直す
                    break;
                }
            }
        }
    }

/*
    atom[0].atomPosition[0] = 0.0;
    atom[1].atomPosition[0] = 9.0;
    atom[2].atomPosition[0] = 5.0;
*/

    calculation_force(atom, parameter);

    for(u4 step = 0; step < parameter->simulationStep; step++) {
        velocity_verlet(atom, parameter);
        //printf("Step %lu: Atom0 Pos = %f, Atom1 Pos = %f \n",
        //       step, atom[0].atomPosition[0], atom[1].atomPosition[0]);
        printf("Step:%lu  ", step);
        //if (step % 5 == 0) {
            calculate_temperature(atom, parameter);
            printf("Temperature:%f\n",parameter->currentTemperature);
            control_temperature(atom, parameter);
        //}
        
           write_file(atom,parameter,step);


        //for(u4 atomId = 0; atomId < atom->atomId; atomId++) {
        //↑これはoutputで書くべきかも
    }
  

    free(atom);
    return 0;

}



