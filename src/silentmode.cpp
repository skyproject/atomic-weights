/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of atomic-weights program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#include <QApplication>
#include <QStringList>

#include "softwareupdate.h"
#include "application.h"
#include "silentmode.h"

SilentMode::SilentMode ( char *arguments[] )
{
    Data::UserInput input;
    input.maximumValue = QString ( arguments[1] ).toInt();
    if ( QString ( arguments[2] ) == "Natural" )
    {
        input.log = Data::Logarithm::Natural;
    }
    else
    {
        input.log = Data::Logarithm::Decimal;
    }
    input.ipComparison = QString ( arguments[3] ).toInt();
    for ( int x = 0; x < 3; ++x )
    {
        input.search.push_back ( QString ( arguments[ ( 4 + x ) ] ).toDouble() );
    }
    if ( QString ( arguments[7] ) == "Enabled" )
    {
        input.extendedIpSearch = true;
    }
    else
    {
        input.extendedIpSearch = false;
    }
    input.resultsFilePath = QString ( arguments[8] );
    input.maximumCalculations = QString ( arguments[10] ).toULongLong();
    input.maximumCoincidences = QString ( arguments[9] ).toULongLong();
    this->core = new CalculationsCore ( input );
    checkForUpdates();
}

void SilentMode::checkForUpdates()
{
    SUL::Structs::Application currentApp;
    currentApp.installedVersion = QString ( APP_PRODUCTVERSION_STR );
    currentApp.updateXmlUrl = QUrl ( "http://www.skyproject.org/programs/atoms/xmlupdate.xml" );
    currentApp.updateFilesXmlUrl = QUrl ( "http://www.skyproject.org/programs/atoms/xmlupdatefiles.xml" );
    currentApp.updateTasksXmlUrl = QUrl ( "http://www.skyproject.org/programs/atoms/xmlupdatetasks.xml" );
    this->su = new SUL::SoftwareUpdate ( currentApp );
    connect ( this->su, SIGNAL ( finished() ),
              this, SLOT ( start() ) );
}

void SilentMode::start()
{
    delete this->su;
    connect ( this->core, SIGNAL ( finished() ),
              this, SLOT ( close() ) );
    this->core->start();
}

void SilentMode::close()
{
    QApplication::exit ( 0 );
}
