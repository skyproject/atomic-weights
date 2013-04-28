/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of atomic-weights program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#include "Widgets\calculationinfo.h"
#include "ui_calculationinfo.h"

CalculationInfo::CalculationInfo(Data::UserInput userInputData, QWidget *parent) :
                                 QWidget(parent), ui(new Ui::CalculationInfo)
{
    ui->setupUi(this);
    ui->labelFile->setText(userInputData.resultsFilePath);
    connect(ui->buttonStop, SIGNAL(clicked()),
            this, SLOT(stopCalculations()));
    connect(ui->buttonPause, SIGNAL(clicked()),
            this, SLOT(pauseCalculations()));
    short decimals = 0;
    for (int x = 0; x < 3; x++)
    {
        if (userInputData.search[x] != 0)
        {
            QStringList value = (QString::number(userInputData.search[x])).split(".");
            if ((short)value[1].length() > decimals)
            {
                decimals = (short)value[1].length();
            }
        }
    }
    decimals = (decimals == 0) ? 10 : decimals;
    core = new CalculationsCore(userInputData, decimals);
    connect(core, SIGNAL(ipFound(long long)),
            this, SLOT(updateGUI(long long)));
    core->start();
}

CalculationInfo::~CalculationInfo()
{
    delete ui;
}

void CalculationInfo::pauseCalculations()
{
    if (ui->buttonPause->text() == "Pause")
    {
        core->pauseCalculations();
        ui->progressBar->setMaximum(1);
        ui->buttonPause->setText("Resume");
    }
    else
    {
        core->resumeCalculations();
        ui->progressBar->setMaximum(0);
        ui->buttonPause->setText("Pause");
    }
}

void CalculationInfo::stopCalculations()
{
    std::vector<long long> calculations = core->cancelCalculations();
    Data::CalculationInfo info;
    info.calculationsNumber = calculations[0];
    info.coincidencesNumber = calculations[1];
    info.resultsFilePath = ui->labelFile->text();
    emit calculationFinished(info);
}

void CalculationInfo::updateGUI(long long coincidences)
{
    ui->labelCoincidences->setText("Total coincidences: " + QString::number(coincidences));
}
