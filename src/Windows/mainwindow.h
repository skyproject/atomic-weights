/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of atomic-weights program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "softwareupdate.h"
#include "data.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0, bool checkUpdates = false);
    ~MainWindow();

private slots:
    void showAbout();
    void resultsClosed();
    void updateCheckFinished();
    void startNewCalculation();
    void calculationFinished(Data::CalculationInfo info);
    void initializeCalculation(Data::UserInput userInputData);

private:
    void clearLayout();
    Ui::MainWindow *ui;
    SUL::SoftwareUpdate *su;
};

#endif // MAINWINDOW_H
