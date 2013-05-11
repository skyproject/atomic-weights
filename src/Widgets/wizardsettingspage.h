/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of atomic-weights program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#ifndef WIZARDSETTINGSPAGE_H
#define WIZARDSETTINGSPAGE_H

#include <QWidget>

#include "data.h"

namespace Ui
{
    class WizardSettingsPage;
}

class WizardSettingsPage : public QWidget
{
        Q_OBJECT

    public:
        explicit WizardSettingsPage ( QWidget *parent = 0 );
        ~WizardSettingsPage();
        int getMaximumValue();
        int getIpComparison();
        uint64_t getMaximumCalculations();
        uint64_t getMaximumCoincidences();
        Data::Logarithm getLogarithmicBase();

    private slots:
        void checkRadioButtons();

    private:
        Ui::WizardSettingsPage *ui;
};

#endif // WIZARDSETTINGSPAGE_H
