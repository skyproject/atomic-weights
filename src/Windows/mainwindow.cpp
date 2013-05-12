/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of atomic-weights program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#include <QUrl>

#include "Widgets/calculationresults.h"
#include "Widgets/calculationwizard.h"
#include "Widgets/calculationinfo.h"
#include "Widgets/welcomeinfo.h"
#include "Windows/aboutwindow.h"
#include "Windows/mainwindow.h"
#include "ui_mainwindow.h"
#include "application.h"

#include "softwareupdate.h"

MainWindow::MainWindow ( QWidget *parent, bool checkUpdates ) :
    QMainWindow ( parent ),
    ui ( new Ui::MainWindow )
{
    ui->setupUi ( this );
    connect ( ui->actionAbout, SIGNAL ( triggered() ),
              this, SLOT ( showAbout() ) );
    connect ( ui->actionExit, SIGNAL ( triggered() ),
              QApplication::instance(), SLOT ( quit() ) );
    if ( checkUpdates == true )
    {
        SUL::Structs::Application currentApp;
        currentApp.installedVersion = QString ( APP_PRODUCTVERSION_STR );
        currentApp.updateXmlUrl = QUrl ( "http://www.skyproject.org/programs/atoms/xmlupdate.xml" );
        currentApp.updateFilesXmlUrl = QUrl ( "http://www.skyproject.org/programs/atoms/xmlupdatefiles.xml" );
        currentApp.updateTasksXmlUrl = QUrl ( "http://www.skyproject.org/programs/atoms/xmlupdatetasks.xml" );
        this->su = new SUL::SoftwareUpdate ( currentApp );
        connect ( this->su, SIGNAL ( finished() ),
                  this, SLOT ( updateCheckFinished() ) );
    }
    WelcomeInfo *welcomePage =  new WelcomeInfo();
    ui->calculationLayout->addWidget ( welcomePage );
    connect ( welcomePage, SIGNAL ( showCalculationWizard() ),
              this, SLOT ( startNewCalculation() ) );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateCheckFinished()
{
    this->show();
    delete this->su;
}

void MainWindow::showAbout()
{
    AboutWindow *aw = new AboutWindow ( this );
    aw->show();
}

void MainWindow::startNewCalculation()
{
    clearLayout();
    CalculationWizard *wizardPage = new CalculationWizard();
    ui->calculationLayout->addWidget ( wizardPage );
    connect ( wizardPage, SIGNAL ( userInputCompleted ( Data::UserInput ) ),
              this, SLOT ( initializeCalculation ( Data::UserInput ) ) );
}

void MainWindow::initializeCalculation ( Data::UserInput userInputData )
{
    clearLayout();
    CalculationInfo *calculationPage = new CalculationInfo ( userInputData );
    ui->calculationLayout->addWidget ( calculationPage );
    connect ( calculationPage, SIGNAL ( calculationFinished ( Data::CalculationInfo ) ),
              this, SLOT ( calculationFinished ( Data::CalculationInfo ) ) );
}

void MainWindow::calculationFinished ( Data::CalculationInfo info )
{
    clearLayout();
    CalculationResults *resultsPage = new CalculationResults ( info );
    ui->calculationLayout->addWidget ( resultsPage );
    connect ( resultsPage, SIGNAL ( resultsClosed() ),
              this, SLOT ( resultsClosed() ) );
}

void MainWindow::resultsClosed()
{
    clearLayout();
    startNewCalculation();
}

void MainWindow::clearLayout()
{
    QLayoutItem *item;
    while ( ( item = ui->calculationLayout->takeAt ( 0 ) ) != NULL )
    {
        delete item->widget();
        delete item;
    }
}
