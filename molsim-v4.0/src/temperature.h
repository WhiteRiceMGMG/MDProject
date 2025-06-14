/*****************************************************************
 *  Filename     : temperature.h
 *  Description  : run
 *  Author       : Ogawa <ocmikanmgmg@gmail.com>
 *  Created      : Jun 7, 2025
 *  Compiler     : arm-none-eabi-gcc
 *  SBC          : Raspberry Pi Zero 2 W (32bit)
 *  License      : MIT License
 *  Note         : サーモスタット機能は50stepに一回くらい．
 *                 Atom構造体にtemperature追加．
 * 　　　　　　　　　 parameter構造体にボルツマン定数追加
 *  History      : 2025/06/14 - ファイル作成
 *  　　　　　　　　　最終編集 2025/6/8
 * 　　　　　　　　　　
 *****************************************************************/
#include <stdio.h>
#include <math.h>
#include "sysdef.h"
#include "parameter.h"
#include "atom.h"

void control_thermostat(Atom *atom, Parameter *parameter);