/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of atomic-weights program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#ifndef DATA_H
#define DATA_H

#include <stdint.h>
#include <QString>

class Data
{
    public:
        enum class Logarithm
        {
            Natural,
            Decimal
        };
        struct UserInput
        {
            int maximumValue;
            int ipComparison;
            std::vector<double> search;
            bool extendedIpSearch;
            Logarithm log;
            QString resultsFilePath;
            uint64_t maximumCalculations;
            uint64_t maximumCoincidences;
        };
        struct CalculationInfo
        {
            QString resultsFilePath;
            uint64_t calculationsNumber;
            uint64_t coincidencesNumber;
        };
        struct CalculationResult
        {
            uint64_t calculations;
            uint64_t coincidences;
            std::vector< std::vector<int> > ipVolume;
            std::vector< std::vector<double> > r_input;
        };
};

#endif // DATA_H
