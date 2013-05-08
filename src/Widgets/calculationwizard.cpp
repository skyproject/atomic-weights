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
#include "Widgets/calculationwizard.h"
#include "ui_calculationwizard.h"

CalculationWizard::CalculationWizard ( QWidget *parent ) :
    QWidget ( parent ),
    ui ( new Ui::CalculationWizard )
{
    ui->setupUi ( this );
    wsp = new WizardSettingsPage();
    ui->pageLayout->addWidget ( wsp );
    wisp = new WizardIpSearchPage();
    ui->pageLayout->addWidget ( wisp );
    connect ( ui->buttonNext, SIGNAL ( clicked() ),
              this, SLOT ( stepNext() ) );
    connect ( ui->buttonBack, SIGNAL ( clicked() ),
              this, SLOT ( stepBack() ) );
    switchPage();
}

CalculationWizard::~CalculationWizard()
{
    delete wsp;
    delete wisp;
    delete ui;
}

void CalculationWizard::stepNext()
{
    if ( currentPage < 1 )
    {
        currentPage++;
        switchPage();
    }
    else
    {
        QFileDialog *fd = new QFileDialog ( this, tr ( "Select file for saving calculation results" ) );
        fd->setDefaultSuffix ( ".txt" );
        fd->setNameFilter ( "Text Documents (*.txt)" );
        fd->setAcceptMode ( QFileDialog::AcceptSave );
        if ( fd->exec() == true )
        {
            Data::UserInput input;
            input.resultsFilePath = fd->selectedFiles().at ( 0 );
            input.maximumValue = this->wsp->getMaximumValue();
            input.ipComparison = this->wsp->getIpComparison();
            input.extendedIpSearch = this->wisp->getExtendedIpSearch();
            input.log = this->wsp->getLogarithmicBase();
            input.search = this->wisp->getIpSearch();
            emit userInputCompleted ( input );
        }
    }
}

void CalculationWizard::stepBack()
{
    currentPage--;
    switchPage();
}

void CalculationWizard::switchPage()
{
    switch ( currentPage )
    {
        case 0:
        {
            wsp->setVisible ( true );
            wisp->setVisible ( false );
            ui->buttonBack->setVisible ( false );
            break;
        }
        case 1:
        {
            wsp->setVisible ( false );
            wisp->setVisible ( true );
            ui->buttonBack->setVisible ( true );
            break;
        }
    }
}
