/**
 * @file testMain.cpp
 * @author csl (3079625093@qq.com)
 * @version 0.1
 * @date 2022-01-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "testPoint.h"
#include "testKdtree.h"
#include "testLine.h"
#include "testUtility.h"
#include "testLinestring.h"
#include "testPolygon.h"
#include "testRectangle.h"

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
