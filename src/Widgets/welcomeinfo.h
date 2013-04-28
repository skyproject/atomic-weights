/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of atomic-weights program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#ifndef WELCOMEINFO_H
#define WELCOMEINFO_H

#include <QWidget>

namespace Ui {
class WelcomeInfo;
}

class WelcomeInfo : public QWidget
{
    Q_OBJECT
    
public:
    explicit WelcomeInfo(QWidget *parent = 0);
    ~WelcomeInfo();
    
private slots:
    void startCalculation();

signals:
    void showCalculationWizard();

private:
    Ui::WelcomeInfo *ui;
};

#endif // WELCOMEINFO_H
