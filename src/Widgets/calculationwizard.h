/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of atomic-weights program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#ifndef CALCULATIONWIZARD_H
#define CALCULATIONWIZARD_H

#include <QWidget>

#include "data.h"

namespace Ui
{
    class CalculationWizard;
}

class CalculationWizard : public QWidget
{
        Q_OBJECT

    public:
        explicit CalculationWizard ( QWidget *parent = 0 );
        ~CalculationWizard();

    private slots:
        void wizardFinished();

    signals:
        void userInputCompleted ( Data::UserInput userInputData );

    private:
        Ui::CalculationWizard *ui;
};

#endif // CALCULATIONWIZARD_H
