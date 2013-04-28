/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of atomic-weights program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#include <QDesktopServices>
#include <QUrl>

#include "Widgets\calculationresults.h"
#include "ui_calculationresults.h"

CalculationResults::CalculationResults(Data::CalculationInfo calculation,
                                       QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CalculationResults)
{
    ui->setupUi(this);
    ui->labelFile->setText(calculation.resultsFilePath);
    ui->labelCalculations->setText("Total calculations: " + QString::number(calculation.calculationsNumber));
    ui->labelCoincidences->setText("Total coincidences: " + QString::number(calculation.coincidencesNumber));
    connect(ui->buttonClose, SIGNAL(clicked()),
            this, SLOT(closeResultsInfo()));
    connect(ui->buttonOpenResults, SIGNAL(clicked()),
            this, SLOT(openResultsFile()));
}

CalculationResults::~CalculationResults()
{
    delete ui;
}

void CalculationResults::openResultsFile()
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(ui->labelFile->text()));
}

void CalculationResults::closeResultsInfo()
{
    emit resultsClosed();
}
