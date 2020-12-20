/*
 *  Copyright (C) 2019 ~ 2020 Uniontech Software Technology Co.,Ltd
 *
 * Author:     wangliang <wangliang@uniontech.com>
 *
 * Maintainer: wangliang <wangliang@uniontech.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "ut_Vt102Emulation_test.h"

#include "Vt102Emulation.h"

//Qt单元测试相关头文件
#include <QTest>
#include <QtGui>
#include <QDebug>

using namespace Konsole;

#define TY_CONSTRUCT(T,A,N) ( (((static_cast<int>(N)) & 0xffff) << 16) | (((static_cast<int>(A)) & 0xff) << 8) | ((static_cast<int>(T)) & 0xff) )

#define TY_CHR(   )     TY_CONSTRUCT(0,0,0)
#define TY_CTL(A  )     TY_CONSTRUCT(1,A,0)
#define TY_ESC(A  )     TY_CONSTRUCT(2,A,0)
#define TY_ESC_CS(A,B)  TY_CONSTRUCT(3,A,B)
#define TY_ESC_DE(A  )  TY_CONSTRUCT(4,A,0)
#define TY_CSI_PS(A,N)  TY_CONSTRUCT(5,A,N)
#define TY_CSI_PN(A  )  TY_CONSTRUCT(6,A,0)
#define TY_CSI_PR(A,N)  TY_CONSTRUCT(7,A,N)
#define TY_CSI_PS_SP(A,N)  TY_CONSTRUCT(11,A,N)

#define TY_VT52(A)    TY_CONSTRUCT(8,A,0)
#define TY_CSI_PG(A)  TY_CONSTRUCT(9,A,0)
#define TY_CSI_PE(A)  TY_CONSTRUCT(10,A,0)

UT_Vt102Emulation_Test::UT_Vt102Emulation_Test()
{
}

void UT_Vt102Emulation_Test::SetUp()
{
}

void UT_Vt102Emulation_Test::TearDown()
{
}

#ifdef UT_VT102EMULATION_TEST

/*******************************************************************************
 1. @函数:    Vt102Emulation类的函数
 2. @作者:    ut000438 王亮
 3. @日期:    2020-12-28
 4. @说明:    reset单元测试
*******************************************************************************/
TEST_F(UT_Vt102Emulation_Test, reset)
{
    Vt102Emulation emulation;
    emulation.reset();
}

/*******************************************************************************
 1. @函数:    Vt102Emulation类的函数
 2. @作者:    ut000438 王亮
 3. @日期:    2020-12-28
 4. @说明:    clearEntireScreen单元测试
*******************************************************************************/
TEST_F(UT_Vt102Emulation_Test, clearEntireScreen)
{
    Vt102Emulation emulation;
    emulation.clearEntireScreen();
}

/*******************************************************************************
 1. @函数:    Vt102Emulation类的函数
 2. @作者:    ut000438 王亮
 3. @日期:    2020-12-28
 4. @说明:    processToken单元测试
*******************************************************************************/
TEST_F(UT_Vt102Emulation_Test, processToken)
{
    Vt102Emulation emulation;

    for (int i = 0; i < 110; i++) {
        emulation.processToken(TY_CHR(), 'a', 0);
        emulation.processToken(TY_CTL('a' + i), 'a', 0);
        emulation.processToken(TY_CTL('A' + i), 'a', 0);
        emulation.processToken(TY_ESC('a' + i), 0, 0);
        emulation.processToken(TY_ESC_CS('a' + i, ' ' + i), 0, 0);
        emulation.processToken(TY_ESC_DE('0' + i), 0, 0);
        emulation.processToken(TY_ESC_DE('a' + i), 0, 0);
        emulation.processToken(TY_CSI_PN('a' + i), 1, 0);
        emulation.processToken(TY_CSI_PN('A' + i), 1, 0);
        emulation.processToken(TY_CSI_PS_SP('a' + i, 1), 1, 0);
        emulation.processToken(TY_CSI_PS('m', i), 0, 1);
        emulation.processToken(TY_CSI_PS('a' + i, i), 0, 1);
        emulation.processToken(TY_CSI_PS('A' + i, i), 0, 1);
        emulation.processToken(TY_CSI_PE('a' + i), 0, 0);
        emulation.processToken(TY_CSI_PR('a' + i, i), 0, 0);
        emulation.processToken(TY_CSI_PR('a' + i, i * 10), 0, 0);
        emulation.processToken(TY_CSI_PG('a' + i), 0, 0);
        emulation.processToken(TY_CSI_PS('a' + i, 0), COLOR_SPACE_RGB, 236);
        emulation.processToken(TY_CSI_PS('a' + i, 1), COLOR_SPACE_256, 1);
        emulation.processToken(TY_CSI_PS('a' + i, 2), 0, 0);
        emulation.processToken(TY_CHR(), 'a' + i, 0);
        emulation.processToken(TY_VT52('a' + i), 0, 0);
        emulation.processToken(TY_VT52('A' + i), 0, 0);
        emulation.processToken(TY_VT52('a' + i), 'm', 'l');
    }
}

#endif