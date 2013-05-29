/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of atomic-weights program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#include <QValidator>
#include <QString>

#include "Widgets/wizardsettingspage.h"
#include "ui_wizardsettingspage.h"

WizardSettingsPage::WizardSettingsPage ( QWidget *parent ) :
    QWidget ( parent ),
    ui ( new Ui::WizardSettingsPage )
{
    ui->setupUi ( this );
}

WizardSettingsPage::~WizardSettingsPage()
{
    delete ui;
}

int WizardSettingsPage::getMaximumValue()
{
    return ui->boxMaximumValue->currentText().toInt();
}

int WizardSettingsPage::getIpComparison()
{
    return ui->boxComparison->currentText().toInt();
}

Data::Logarithm WizardSettingsPage::getLogarithmicBase()
{
    if ( ui->boxLogarithm->currentText() == "Natural" )
    {
        return Data::Logarithm::Natural;
    }
    else
    {
        return Data::Logarithm::Decimal;
    }
}
