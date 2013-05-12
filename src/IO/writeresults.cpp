/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of atomic-weights program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#include <QFile>
#include <QTextStream>

#include "IO\writeresults.h"

#include "Core\math.h"

WriteResults::WriteResults ( Data::UserInput userInputData )
{
    this->resultsFile = userInputData.resultsFilePath;
    writeInitialDataToFile ( userInputData );
}

void WriteResults::saveResult ( Data::CalculationResult result )
{
    QString output;
    output += "\n\n------------------------\n\n";
    output += ( "Coincidences:\t" + QString::number ( result.coincidences ) + "\n" );
    output += ( "Calculations:\t" + QString::number ( result.calculations ) + "\n" );
    for ( int y = 0; y < 3; ++y )
    {
        output += "\n";
        output += "Field " + QString::number ( y + 1 ) + "\n";
        output += "\n";
        output += ( QString::number ( result.ipVolume[y][0] ) + "\t" + QString::number ( result.ipVolume[y][1] )
                    + "\t" + QString::number ( result.ipVolume[y][2] ) + "\n" );
        output += ( QString::number ( result.ipVolume[y][3] ) + "\t" + QString::number ( result.ipVolume[y][4] )
                    + "\t" + QString::number ( result.ipVolume[y][5] ) + "\n" );
        output += ( QString::number ( result.ipVolume[y][6] ) + "\t" + QString::number ( result.ipVolume[y][7] )
                    + "\t" + QString::number ( result.ipVolume[y][8] ) + "\n" );
        output += "\n";
    }
    output += "XY field\n";
    output += "\n";
    output += ( QString::number ( result.r_input[0][1] ) + "\t" + QString::number ( result.r_input[0][2] )
                + "\t" + QString::number ( result.r_input[0][3] ) + "\n" );
    output += ( QString::number ( result.r_input[0][4] ) + "\t" + QString::number ( result.r_input[0][5] )
                + "\t" + QString::number ( result.r_input[0][6] ) + "\n" );
    output += ( QString::number ( result.r_input[0][7] ) + "\t" + QString::number ( result.r_input[0][8] )
                + "\t" + QString::number ( result.r_input[0][9] ) + "\n" );
    output += "\n";
    output += ( "ZX field\n" );
    output += "\n";
    output += ( QString::number ( result.r_input[1][1] ) + "\t" + QString::number ( result.r_input[1][2] )
                + "\t" + QString::number ( result.r_input[1][3] ) + "\n" );
    output += ( QString::number ( result.r_input[1][4] ) + "\t" + QString::number ( result.r_input[1][5] )
                + "\t" + QString::number ( result.r_input[1][6] ) + "\n" );
    output += ( QString::number ( result.r_input[1][7] ) + "\t" + QString::number ( result.r_input[1][8] )
                + "\t" + QString::number ( result.r_input[1][9] ) + "\n" );
    output += "\n";
    output += ( "ZY field\n" );
    output += "\n";
    output += ( QString::number ( result.r_input[2][1] ) + "\t" + QString::number ( result.r_input[2][2] )
                + "\t" + QString::number ( result.r_input[2][3] ) + "\n" );
    output += ( QString::number ( result.r_input[2][4] ) + "\t" + QString::number ( result.r_input[2][5] )
                + "\t" + QString::number ( result.r_input[2][6] ) + "\n" );
    output += ( QString::number ( result.r_input[2][7] ) + "\t" + QString::number ( result.r_input[2][8] )
                + "\t" + QString::number ( result.r_input[2][9] ) + "\n" );
    output += "\n";
    output += ( "Iab (XY):\t" + QString::number ( result.r_input[0][0] ) + "\n" );
    output += ( "Iab (ZX):\t" + QString::number ( result.r_input[1][0] ) + "\n" );
    output += ( "Iab (ZY):\t" + QString::number ( result.r_input[2][0] ) );
    QFile results ( this->resultsFile );
    if ( results.open ( QIODevice::Append | QFile::Text ) )
    {
        QTextStream stream ( &results );
        stream << output;
    }
    for ( int x = 0; x < 3; ++x )
    {
        std::map<double, uint64_t>::iterator it = ipValues.find ( result.r_input[x][0] );
        if ( it != ipValues.end() )
        {
            it->second += 1;
        }
        else
        {
            ipValues.insert ( std::pair<double, uint64_t> ( result.r_input[x][0], 1 ) );
        }
    }
}

void WriteResults::writeInitialDataToFile ( Data::UserInput userInputData )
{
    QFile results ( this->resultsFile );
    if ( results.open ( QIODevice::WriteOnly | QFile::Text ) )
    {
        QTextStream stream ( &results );
        stream << "Atomic Weights results file\n";
        stream << "\n";
        stream << "Maximum generation value:\t" + QString::number ( userInputData.maximumValue ) + "\n";
        stream << "\n";
        stream << "Ip comparison:\t\t" + QString::number ( userInputData.ipComparison ) + "\n";
        stream << "\n";
        if ( userInputData.log == Data::Logarithm::Natural )
        {
            stream << "Logarithmic base:\tNatural\n";
        }
        else
        {
            stream << "Logarithmic base:\tDecimal\n";
        }
        stream << "\n";

        for ( int x = 0; x < 3; ++x )
        {
            if ( userInputData.search[x] == IP_SEARCH_DISABLED )
            {
                stream << "Ip search (" + QString::number ( ( x + 1 ) ) + "):\t\tDisabled";
            }
            else
            {
                stream << "Ip search (" + QString::number ( ( x + 1 ) ) + "):\t\t" + QString::number ( userInputData.search[x] );
            }
            stream << "\n";
        }
        if ( userInputData.extendedIpSearch == true )
        {
            stream << "Reverse Ip search:\tEnabled" ;
        }
        else
        {
            stream << "Reverse Ip search:\tDisabled" ;
        }
    }
}

void WriteResults::writeEndingToFile()
{
    QFile results ( this->resultsFile );
    if ( results.open ( QIODevice::Append | QFile::Text ) )
    {
        QTextStream stream ( &results );
        stream << "\n\n------------------------\n\n";
        stream << "Nuclear affinity\n\n";
        stream << "[#]\t[Ip]\t\t[Frequency]\t[Relative frequency]\n";

        uint64_t totalFrequency = 0;
        for ( std::map<double, uint64_t>::const_iterator it = this->ipValues.begin();
              it != this->ipValues.end(); ++it )
        {
            totalFrequency += it->second;
        }

        uint64_t designation = 0;
        for ( std::map<double, uint64_t>::const_iterator it = this->ipValues.begin();
              it != this->ipValues.end(); ++it )
        {
            ++designation;
            if ( QString::number ( it->first ).length() < 8 )
            {
                stream << QString::number ( designation ) + "\t" + QString::number ( it->first )
                       + "\t\t" + QString::number ( it->second ) + "\t\t"
                       + QString::number ( Math::roundDouble ( ( ( double ) it->second / totalFrequency ), 10 ) ) + "\n";
            }
            else
            {
                stream << QString::number ( designation ) + "\t" + QString::number ( it->first )
                       + "\t" + QString::number ( it->second ) + "\t\t"
                       + QString::number ( Math::roundDouble ( ( ( double ) it->second / totalFrequency ), 10 ) ) + "\n";
            }
        }
    }
}
