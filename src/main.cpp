/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of atomic-weights program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#include <QFontDatabase>
#include <QApplication>
#include <QMetaType>

#include "Windows\mainwindow.h"
#include "silentmode.h"

int main ( int argc, char *argv[] )
{
    QApplication a ( argc, argv );

    QApplication::setQuitOnLastWindowClosed ( true );

    qRegisterMetaType<Data::UserInput> ( "Data::UserInput" );
    qRegisterMetaType<uint64_t> ( "uint64_t" );
    qRegisterMetaType<Data::CalculationInfo> ( "Data::CalculationInfo" );
    qRegisterMetaType<Data::CalculationResult> ( "Data::CalculationResult" );

    if ( argc == 11 )
    {
        SilentMode *m = new SilentMode ( argv );
    }
    else
    {
        QFontDatabase::addApplicationFont ( "OpenSans-Bold.ttf" );
        QFontDatabase::addApplicationFont ( "OpenSans-Regular.ttf" );
        MainWindow *w = new MainWindow ( NULL, true );
    }

    return a.exec();
}
