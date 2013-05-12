/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of atomic-weights program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#ifndef WRITERESULTS_H
#define WRITERESULTS_H

#include <QObject>
#include <map>

#include "data.h"

class WriteResults : public QObject
{
        Q_OBJECT

    public:
        WriteResults ( Data::UserInput userInputData );
        void saveResult ( Data::CalculationResult result );
        void writeEndingToFile();

    private:
        void writeInitialDataToFile ( Data::UserInput userInputData );
        std::map<double, uint64_t> ipValues;
        QString resultsFile;
};

#endif // WRITERESULTS_H
