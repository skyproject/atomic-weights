/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of atomic-weights program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#ifndef CALCULATIONRESULTS_H
#define CALCULATIONRESULTS_H

#include <QWidget>

#include "data.h"

namespace Ui
{
    class CalculationResults;
}

class CalculationResults : public QWidget
{
        Q_OBJECT

    public:
        explicit CalculationResults ( Data::CalculationInfo calculation, QWidget *parent = 0 );
        ~CalculationResults();

    private slots:
        void openResultsFile();
        void closeResultsInfo();

    signals:
        void resultsClosed();

    private:
        Ui::CalculationResults *ui;
};

#endif // CALCULATIONRESULTS_H
