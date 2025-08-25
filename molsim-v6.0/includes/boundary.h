/*****************************************************************
 *  Filename     : boundary.h
 *  Description  : boudry  file
 *  Author       : Ogawa <ocmikanmgmg@gmail.com>
 *  Created      : Aug 25, 2025
 *  Compiler     : gcc
 *  SBC          : Raspberry Pi Zero 2 W (32bit)
 *  License      : OGW License
 *  Note         : no windows
 *  History      : 2025/08/25 - ファイル作成
 *  最終編集 2025/08/25
 *****************************************************************/
#include <includes.h>
#ifndef BOUNDARY_H
#define BOUNDARY_H

f8 apply_period(f8 pos, Parameter *param, f8 celMax);
f8 calculation_minimam(f8 rij, f8 celMax);

#endif

