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
#include "output.h"

int main(void) {
    Parameter *parameter = (Parameter *)malloc(sizeof(Parameter));
    parameter->atomNum           = 0;    /*原子の数*/
    parameter->simulationStep    = 0;    /*シミュレーションステップ*/
    parameter->timeStep          = 0;    /*1ステップあたりの時間*/
    parameter->epsilonVal        = 1.0;  /*原子間の引力*/
    parameter->sigmaVal          = 1.0;  /*ポテンシャルエネルギー最小位置*/
    parameter->atomMass          = 1.0;  /*原子質量*/
    parameter->cutoffCoefficient = 2.5;  /*カットオフ距離*/
    parameter->cellSize[0]       = 0;    /*X方向のセルの長さ*/
    parameter->cellSize[1]       = 0;    /*Y方向のセルの長さ*/
    parameter->cellSize[2]       = 0;    /*Z方向のセルの長さ*/
    parameter->atomInterval      = 0;     /*初期原子間距離*/
    printf("原子数 100推奨    ：");
    usleep(100000);
    scanf("%lu", &(parameter->atomNum));
    usleep(100000);

    printf("ステップ数 100推奨：");
    usleep(100000);
    scanf("%lu", &(parameter->simulationStep));
    usleep(100000);    

    printf("刻み幅 0.1推奨    ：");
    usleep(100000);
    scanf("%lf", &(parameter->timeStep));
    usleep(100000);

    printf("σ                  ：");
    usleep(100000);
    printf("1.0(自動設定)\n");
    usleep(100000);

    printf("ε                  ：");
    usleep(100000);
    printf("1.0(自動設定)\n");
    usleep(100000);

    printf("カットオフ入力     :");
    usleep(100000);
    printf("2.5(自動設定)\n");
    usleep(100000);
    
    printf("セルX長さ 20推奨   :");
    usleep(100000);
    scanf("%lf", &(parameter->cellSize[0]));
    usleep(100000);

    printf("セルY長さ 20推奨  ：");
    usleep(100000);
    scanf("%lf", &(parameter->cellSize[1]));
    usleep(100000);

    printf("セルZ長さ 10推奨  ：");
    usleep(100000);
    scanf("%lf", &(parameter->cellSize[2]));
    usleep(100000);

    printf("初期配置間隔 1推奨 ：");
    usleep(100000);
    scanf("%lf", &(parameter->atomInterval));
    usleep(1);

    usleep(1);
    printf("RUN SIMULATIOM\n");

    Atom *atom = (Atom *)malloc(sizeof(Atom) * parameter->atomNum);
    initialize_atom(atom, parameter);

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
        printf("Step %lu: Atom0 Pos = %f, Atom1 Pos = %f\n",
               step, atom[0].atomPosition[0], atom[1].atomPosition[0]);
        if(step == (parameter->simulationStep / 100)) {
            printf("◻️");
        }
            write_file(atom,parameter,step);
        //for(u4 atomId = 0; atomId < atom->atomId; atomId++) {
        //↑これはoutputで書くべきかも
    }
  

    free(atom);
    return 0;

}



