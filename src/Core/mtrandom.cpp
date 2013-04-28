/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of atomic-weights program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#include <time.h>

#include "Core/mtrandom.h"

MTRandom::MTRandom()
{
    mtwister_engine.seed((unsigned)time(NULL));
}

int MTRandom::getRandomInt(int minValue, int maxValue)
{
    int number = (int)mtwister_engine();
    if (minValue != maxValue)
    {
        return (std::abs(number % (maxValue - minValue)) + minValue);
    }
    else
    {
        return minValue;
    }
}
