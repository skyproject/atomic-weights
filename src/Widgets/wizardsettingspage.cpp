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
    QValidator *validate1 = new QIntValidator();
    ui->lineMaxCalculations->setValidator ( validate1 );
    QValidator *validate2 = new QIntValidator();
    ui->lineMaxCoincidences->setValidator ( validate2 );
    connect ( ui->lineMaxCalculations, SIGNAL ( textChanged ( QString ) ),
              this, SLOT ( checkRadioButtons() ) );
    connect ( ui->lineMaxCoincidences, SIGNAL ( textChanged ( QString ) ),
              this, SLOT ( checkRadioButtons() ) );
}

WizardSettingsPage::~WizardSettingsPage()
{
    delete ui;
}

void WizardSettingsPage::checkRadioButtons()
{
    if ( sender()->objectName() == "lineMaxCalculations" )
    {
        ui->radioMaxCalculations->setChecked ( true );
    }
    else
    {
        ui->radioMaxCoincidences->setChecked ( true );
    }
}

int WizardSettingsPage::getMaximumValue()
{
    return ui->boxMaximumValue->currentText().toInt();
}

int WizardSettingsPage::getIpComparison()
{
    return ui->boxComparison->currentText().toInt();
}

uint64_t WizardSettingsPage::getMaximumCalculations()
{
    if ( ui->radioMaxCalculations->isChecked() == true )
    {
        return ui->lineMaxCalculations->text().toULongLong();
    }
    return 0;
}

uint64_t WizardSettingsPage::getMaximumCoincidences()
{
    if ( ui->radioMaxCoincidences->isChecked() == true )
    {
        return ui->lineMaxCoincidences->text().toULongLong();
    }
    return 0;
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
