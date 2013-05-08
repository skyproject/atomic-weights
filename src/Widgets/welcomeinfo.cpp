/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of atomic-weights program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#include "Widgets\welcomeinfo.h"
#include "ui_welcomeinfo.h"

WelcomeInfo::WelcomeInfo ( QWidget *parent ) :
    QWidget ( parent ),
    ui ( new Ui::WelcomeInfo )
{
    ui->setupUi ( this );
    connect ( ui->buttonStart, SIGNAL ( clicked() ),
              this, SLOT ( startCalculation() ) );
}

WelcomeInfo::~WelcomeInfo()
{
    delete ui;
}

void WelcomeInfo::startCalculation()
{
    emit showCalculationWizard();
}
