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

void write_file(Atom *atom, Parameter *parameter, u4 step) {
    


    int i = 100;
    FILE *file;
    file = fopen("test.txt", "a+");
    fprintf(file, "step:%d ", step);
    for(i = 0; i < atom->atomNum;i++) {
        for(u4 dimension = 0; dimension < 3; dimension++) {
            fprintf(file, "Atom %d: pos:%d", atom[i], atom[i].atomPosition[dimension]);
        }
    }
    fprintf(file, "step:%d Atom%d: pos:%d", i);
    fclose(file);
    return 0;



}