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

#include "Widgets/wizardsettingspage.h"
#include "Widgets/wizardipsearchpage.h"
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
        void stepNext();
        void stepBack();

    signals:
        void userInputCompleted ( Data::UserInput userInputData );

    private:
        Ui::CalculationWizard *ui;
        WizardSettingsPage *wsp;
        WizardIpSearchPage *wisp;
        void switchPage();
        short currentPage = 0;
};

#endif // CALCULATIONWIZARD_H
