/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of atomic-weights program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#ifndef MATH_H
#define MATH_H

#include "data.h"

class Math
{
    public:
        static double ip ( std::vector<int> input, Data::Logarithm log );
        static double roundDouble ( double source, short decimals );
};

#endif // MATH_H
