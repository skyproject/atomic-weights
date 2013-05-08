/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of atomic-weights program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#ifndef MTRANDOM_H
#define MTRANDOM_H

#include <random>

class MTRandom
{
    public:
        MTRandom();
        int getRandomInt ( int minValue, int maxValue );

    private:
        std::mt19937 mtwister_engine;
};

#endif // MTRANDOM_H
