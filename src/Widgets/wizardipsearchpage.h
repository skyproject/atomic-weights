/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of atomic-weights program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#ifndef WIZARDIPSEARCHPAGE_H
#define WIZARDIPSEARCHPAGE_H

#include <QWidget>

namespace Ui
{
    class WizardIpSearchPage;
}

class WizardIpSearchPage : public QWidget
{
        Q_OBJECT

    public:
        explicit WizardIpSearchPage ( QWidget *parent = 0 );
        ~WizardIpSearchPage();
        bool getExtendedIpSearch();
        std::vector<double> getIpSearch();

    private slots:
        void ipCheckStateChanged ( int newState );

    private:
        Ui::WizardIpSearchPage *ui;
};

#endif // WIZARDIPSEARCHPAGE_H
