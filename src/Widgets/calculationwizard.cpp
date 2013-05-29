/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of atomic-weights program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#include <QFileDialog>

#include "Widgets/wizardsettingspage.h"
#include "Widgets/wizardipsearchpage.h"
#include "Widgets/wizardautostoppage.h"
#include "Widgets/calculationwizard.h"
#include "ui_calculationwizard.h"

CalculationWizard::CalculationWizard ( QWidget *parent ) :
    QWidget ( parent ),
    ui ( new Ui::CalculationWizard )
{
    ui->setupUi ( this );
    connect ( ui->wizard, SIGNAL ( wizardFinished() ),
              this, SLOT ( wizardFinished() ) );
    ui->wizard->wizardPages.push_back ( new WizardSettingsPage() );
    ui->wizard->wizardPages.push_back ( new WizardIpSearchPage() );
    ui->wizard->wizardPages.push_back ( new WizardAutoStopPage() );
    ui->wizard->loadPages();
}

CalculationWizard::~CalculationWizard()
{
    delete ui;
}

void CalculationWizard::wizardFinished()
{
    QFileDialog *fd = new QFileDialog ( this, tr ( "Select file for saving calculation results" ) );
    fd->setDefaultSuffix ( ".txt" );
    fd->setNameFilter ( "Text Documents (*.txt)" );
    fd->setAcceptMode ( QFileDialog::AcceptSave );
    if ( fd->exec() == true )
    {
        Data::UserInput input;
        input.resultsFilePath = fd->selectedFiles().at ( 0 );
        input.maximumValue = qobject_cast<WizardSettingsPage *> ( ui->wizard->wizardPages[0] )->getMaximumValue();
        input.ipComparison = qobject_cast<WizardSettingsPage *> ( ui->wizard->wizardPages[0] )->getIpComparison();
        input.log = qobject_cast<WizardSettingsPage *> ( ui->wizard->wizardPages[0] )->getLogarithmicBase();
        input.maximumCalculations = qobject_cast<WizardAutoStopPage *> ( ui->wizard->wizardPages[2] )->getMaximumCalculations();
        input.maximumCoincidences = qobject_cast<WizardAutoStopPage *> ( ui->wizard->wizardPages[2] )->getMaximumCoincidences();
        input.extendedIpSearch = qobject_cast<WizardIpSearchPage *> ( ui->wizard->wizardPages[1] )->getExtendedIpSearch();
        input.search = qobject_cast<WizardIpSearchPage *> ( ui->wizard->wizardPages[1] )->getIpSearch();
        fd->deleteLater();
        emit userInputCompleted ( input );
    }
}
