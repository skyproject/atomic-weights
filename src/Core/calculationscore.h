/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of atomic-weights program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#ifndef CALCULATIONSCORE_H
#define CALCULATIONSCORE_H

#include <QWaitCondition>
#include <QObject>
#include <QThread>
#include <QString>
#include <QMutex>

#include "IO/writeresults.h"
#include "mtrandom.h"
#include "data.h"

class CalculationsCore : public QThread
{
        Q_OBJECT

    public:
        CalculationsCore ( Data::UserInput userInputData );
        ~CalculationsCore();
        std::vector<uint64_t> cancelCalculations();
        void pauseCalculations();
        void resumeCalculations();

    signals:
        void ipFound ( uint64_t coincidences );

    private:
        void run();
        std::vector<int> getRandomIp();
        std::vector< std::vector<int> > getIpVolume ( std::vector<int> input );
        std::vector< std::vector<double> > writeIp ( std::vector<int> input,
                std::vector< std::vector<int> > );
        bool searchIp ( double inputIp[3] );
        int maximumValue;
        int ipComparison;
        std::vector<double> ipSearch;
        bool extendedIpSearch;
        short roundDecimals;
        Data::Logarithm logarithm;
        QMutex sync;
        QWaitCondition pauseCond;
        bool pause = false;
        bool cancel = false;
        uint64_t calculations = 0;
        uint64_t coincidences = 0;
        uint64_t maxCalculations = 0;
        uint64_t maxCoincidences = 0;
        MTRandom rnd;
        WriteResults *wr;
};

#endif // CALCULATIONSCORE_H
