/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of atomic-weights program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#ifndef DATA_H
#define DATA_H

#include <QString>

class Data
{
    public:
        enum class Logarithm
        {
            natural,
            decimal
        };
        struct UserInput
        {
            int maximumValue;
            int ipComparison;
            std::vector<double> search;
            bool extendedIpSearch;
            Logarithm log;
            QString resultsFilePath;
        };
        struct CalculationInfo
        {
            QString resultsFilePath;
            long long calculationsNumber;
            long long coincidencesNumber;
        };
        struct CalculationResult
        {
            long long calculations;
            long long coincidences;
            std::vector< std::vector<int> > ipVolume;
            std::vector< std::vector<double> > r_input;
        };
};

#endif // DATA_H
