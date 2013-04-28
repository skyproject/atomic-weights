/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of atomic-weights program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#include <QValidator>

#include "Widgets/wizardipsearchpage.h"
#include "ui_wizardipsearchpage.h"

WizardIpSearchPage::WizardIpSearchPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WizardIpSearchPage)
{
    ui->setupUi(this);
    QValidator *validateIp1 = new QDoubleValidator(0, 10, 100);
    ui->lineIp1->setValidator(validateIp1);
    QValidator *validateIp2 = new QDoubleValidator(0, 10, 100);
    ui->lineIp2->setValidator(validateIp2);
    QValidator *validateIp3 = new QDoubleValidator(0, 10, 100);
    ui->lineIp3->setValidator(validateIp3);
    connect(ui->checkIp1, SIGNAL(stateChanged(int)),
            this, SLOT(ipCheckStateChanged(int)));
    connect(ui->checkIp2, SIGNAL(stateChanged(int)),
            this, SLOT(ipCheckStateChanged(int)));
    connect(ui->checkIp3, SIGNAL(stateChanged(int)),
            this, SLOT(ipCheckStateChanged(int)));
    connect(ui->checkExtSearch, SIGNAL(stateChanged(int)),
            this, SLOT(ipCheckStateChanged(int)));
}

WizardIpSearchPage::~WizardIpSearchPage()
{
    delete ui;
}

void WizardIpSearchPage::ipCheckStateChanged(int newState)
{
    if (sender()->objectName() == "checkIp1")
    {
        if (newState == 2) //checked
        {
            ui->checkExtSearch->setEnabled(true);
            ui->checkIp2->setEnabled(true);
            ui->lineIp1->setEnabled(true);
            if (ui->checkIp2->checkState() == Qt::Checked)
            {
                ui->checkExtSearch->setEnabled(false);
                ui->checkIp3->setEnabled(true);
                ui->lineIp2->setEnabled(true);
                if (ui->checkIp3->checkState() == Qt::Checked)
                {
                    ui->lineIp3->setEnabled(true);
                }
            }
        }
        else
        {
            ui->checkExtSearch->setEnabled(false);
            ui->checkIp2->setEnabled(false);
            ui->checkIp3->setEnabled(false);
            ui->lineIp1->setEnabled(false);
            ui->lineIp2->setEnabled(false);
            ui->lineIp3->setEnabled(false);
        }
    }
    else if (sender()->objectName() == "checkIp2")
    {
        if (newState == 2) //checked
        {
            ui->checkExtSearch->setEnabled(false);
            ui->checkIp3->setEnabled(true);
            ui->lineIp2->setEnabled(true);
            if (ui->checkIp3->checkState() == Qt::Checked)
            {
                ui->lineIp3->setEnabled(true);
            }
        }
        else
        {
            ui->checkExtSearch->setEnabled(true);
            ui->checkIp3->setEnabled(false);
            ui->lineIp2->setEnabled(false);
            ui->lineIp3->setEnabled(false);
        }
    }
    else if (sender()->objectName() == "checkIp3")
    {
        if (newState == 2) //checked
        {
            ui->lineIp3->setEnabled(true);
        }
        else
        {
            ui->lineIp3->setEnabled(false);
        }
    }
    else if (sender()->objectName() == "checkExtSearch")
    {
        if (newState == 2)
        {
            ui->checkIp2->setEnabled(false);
            ui->checkIp3->setEnabled(false);
            ui->lineIp2->setEnabled(false);
            ui->lineIp3->setEnabled(false);
        }
        else
        {
            ui->checkIp2->setEnabled(true);
            if (ui->checkIp2->checkState() == Qt::Checked)
            {
                ui->lineIp2->setEnabled(true);
                ui->checkIp3->setEnabled(true);
                if (ui->checkIp3->checkState() == Qt::Checked)
                {
                    ui->lineIp3->setEnabled(true);
                }
            }
        }
    }
}

std::vector<double> WizardIpSearchPage::getIpSearch()
{
    std::vector<double> search;
    search.push_back((ui->checkIp1->checkState() == Qt::CheckState::Unchecked) ? 0 : ui->lineIp1->text().toDouble());
    search.push_back((ui->checkIp2->checkState() == Qt::CheckState::Unchecked) ? 0 : ui->lineIp2->text().toDouble());
    search.push_back((ui->checkIp3->checkState() == Qt::CheckState::Unchecked) ? 0 : ui->lineIp3->text().toDouble());
    return search;
}

bool WizardIpSearchPage::getExtendedIpSearch()
{
    return (ui->checkExtSearch->checkState() == Qt::CheckState::Unchecked) ? false : true;
}
