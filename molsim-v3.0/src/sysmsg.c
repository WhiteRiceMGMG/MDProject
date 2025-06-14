/*****************************************************************
 *  Filename     : sysmsg.c
 *  Description  : to calcration time step
 *  Author       : Ogawa <ocmikanmgmg@gmail.com>
 *  Created      : Jun 7, 2025
 *  Compiler     : arm-none-eabi-gcc
 *  SBC          : Raspberry Pi Zero 2 W
 *  License      : MIT License
 *  Note         : 
 *  History      : 2025/06/07 - ファイル作成
 *****************************************************************/
#include "sysmsg.h"

void system_message(Parameter *parameter){

    printf("原子数 100推奨        ：");
    usleep(100000);
    scanf("%lu", &(parameter->atomNum));
    usleep(100000);

    printf("ステップ数 100推奨    ：");
    usleep(100000);
    scanf("%lu", &(parameter->simulationStep));
    usleep(100000);    

    printf("刻み幅 0.1推奨       ：");
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

    printf("カットオフ入力        :");
    usleep(100000);
    printf("2.5(自動設定)\n");
    usleep(100000);
    
    printf("セルX長さ 20推奨      :");
    usleep(100000);
    scanf("%lf", &(parameter->cellSize[0]));
    usleep(100000);

    printf("セルY長さ 20推奨      ：");
    usleep(100000);
    scanf("%lf", &(parameter->cellSize[1]));
    usleep(100000);

    printf("セルZ長さ 10推奨      ：");
    usleep(100000);
    scanf("%lf", &(parameter->cellSize[2]));
    usleep(100000);

    printf("初期配置間隔 1推奨     ：");
    usleep(100000);
    scanf("%lf", &(parameter->atomInterval));
    usleep(1);

    usleep(1);
    printf("RUN SIMULATIOM\n");
}
