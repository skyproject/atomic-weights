/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of atomic-weights program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#include "Widgets\calculationinfo.h"
#include "ui_calculationinfo.h"

CalculationInfo::CalculationInfo ( Data::UserInput userInputData, QWidget *parent ) :
    QWidget ( parent ), ui ( new Ui::CalculationInfo )
{
    ui->setupUi ( this );
    ui->labelFile->setText ( userInputData.resultsFilePath );
    connect ( ui->buttonStop, SIGNAL ( clicked() ),
              this, SLOT ( stopCalculations() ) );
    connect ( ui->buttonPause, SIGNAL ( clicked() ),
              this, SLOT ( pauseCalculations() ) );
    core = new CalculationsCore ( userInputData );
    connect ( this->core, SIGNAL ( ipFound ( uint64_t ) ),
              this, SLOT ( updateGUI ( uint64_t ) ) );
    connect ( this->core, SIGNAL ( finished() ),
              this, SLOT ( stopCalculations() ) );
    core->start();
}

CalculationInfo::~CalculationInfo()
{
    delete ui;
}

void CalculationInfo::pauseCalculations()
{
    if ( ui->buttonPause->text() == "Pause" )
    {
        core->pauseCalculations();
        ui->progressBar->setMaximum ( 1 );
        ui->buttonPause->setText ( "Resume" );
    }
    else
    {
        core->resumeCalculations();
        ui->progressBar->setMaximum ( 0 );
        ui->buttonPause->setText ( "Pause" );
    }
}

void CalculationInfo::stopCalculations()
{
    std::vector<uint64_t> calculations = this->core->cancelCalculations();
    this->core->deleteLater();
    Data::CalculationInfo info;
    info.calculationsNumber = calculations[0];
    info.coincidencesNumber = calculations[1];
    info.resultsFilePath = ui->labelFile->text();
    emit calculationFinished ( info );
}

void CalculationInfo::updateGUI ( uint64_t coincidences )
{
    ui->labelCoincidences->setText ( "Total coincidences: " + QString::number ( coincidences ) );
}
