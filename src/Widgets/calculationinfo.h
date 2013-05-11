/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of atomic-weights program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#ifndef CALCULATIONINFO_H
#define CALCULATIONINFO_H

#include <QWidget>

#include "Core/calculationscore.h"
#include "IO/writeresults.h"
#include "data.h"

namespace Ui
{
    class CalculationInfo;
}

class CalculationInfo : public QWidget
{
        Q_OBJECT

    public:
        explicit CalculationInfo ( Data::UserInput userInputData, QWidget *parent = 0 );
        ~CalculationInfo();

    private slots:
        void stopCalculations();
        void pauseCalculations();
        void updateGUI ( uint64_t coincidences );

    signals:
        void calculationFinished ( Data::CalculationInfo info );

    private:
        Ui::CalculationInfo *ui;
        CalculationsCore *core;
};

#endif // CALCULATIONINFO_H
