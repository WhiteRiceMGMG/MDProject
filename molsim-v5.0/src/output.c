/*****************************************************************
 *  Filename     : output.c
 *  Description  : run
 *  Author       : Ogawa <ocmikanmgmg@gmail.com>
 *  Created      : Jun 7, 2025
 *  Compiler     : arm-none-eabi-gcc
 *  SBC          : Raspberry Pi Zero 2 W (32bit)
 *  License      : MIT License
 *  Note         : 現在のステップ　atom id atom position
 *                 
 *  History      : 2025/06/10 - ファイル作成
 *                 最終編集 2025/6/10
 *****************************************************************/

 #include <stdio.h>
 #include "output.h"

void write_file(Atom *atom, Parameter *parameter, u4 step) {
    


    u4 i = 100;
    FILE *file;
    file = fopen("test.txt", "a");
    if (file == NULL) {
        perror("ファイルオープンに失敗");
        return;
    }

    fprintf(file,"%lu\n",parameter->atomNum);
    fprintf(file, "timestep %lu  \n", step);
    for(i = 0; i < parameter->atomNum;i++) {
        //fprintf(file, "atom:%lu  ", atom[i].atomId);
        fprintf(file,"A ");
        for(u4 dimension = 0; dimension < 3; dimension++) {
            fprintf(file, "%f ", atom[i].atomPosition[dimension]);
        }
        fprintf(file, "\n");
    }
    //fprintf(file, "--------------------------------------------------------------------------\n");
    fclose(file);
    return;



}