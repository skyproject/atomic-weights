/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of atomic-weights program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#include "Windows/aboutwindow.h"
#include "ui_aboutwindow.h"
#include "application.h"

AboutWindow::AboutWindow ( QWidget *parent ) :
    QDialog ( parent ),
    ui ( new Ui::AboutWindow )
{
    ui->setupUi ( this );
    ui->labelVersion->setText ( "Version " + QString ( APP_PRODUCTVERSION_STR )
                                + " (released on " + QString ( APP_RELEASE_DATE_STR ) + ")" );
    connect ( ui->buttonClose, SIGNAL ( clicked() ),
              this, SLOT ( close() ) );
}

AboutWindow::~AboutWindow()
{
    delete ui;
}

void AboutWindow::close()
{
    this->destroy();
}
