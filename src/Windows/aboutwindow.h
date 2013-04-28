/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of atomic-weights program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <QDialog>

namespace Ui {
class AboutWindow;
}

class AboutWindow : public QDialog
{
    Q_OBJECT
    
public:
    explicit AboutWindow(QWidget *parent = 0);
    ~AboutWindow();
    
private slots:
    void close();

private:
    Ui::AboutWindow *ui;
};

#endif // ABOUTWINDOW_H
