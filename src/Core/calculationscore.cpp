/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of atomic-weights program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#include "calculationscore.h"
#include "math.h"

CalculationsCore::CalculationsCore ( Data::UserInput userInputData, short decimals )
{
    this->maximumValue = userInputData.maximumValue;
    this->ipComparison = userInputData.ipComparison;
    this->ipSearch = userInputData.search;
    this->extendedIpSearch = userInputData.extendedIpSearch;
    this->logarithm = userInputData.log;
    this->roundDecimals = decimals;
    this->wr = new WriteResults ( userInputData );
}

void CalculationsCore::pauseCalculations()
{
    sync.lock();
    pause = true;
    sync.unlock();
}

void CalculationsCore::resumeCalculations()
{
    sync.lock();
    pause = false;
    sync.unlock();
    pauseCond.wakeAll();
}

std::vector<long long> CalculationsCore::cancelCalculations()
{
    cancel = true;
    std::vector<long long> info;
    info.push_back ( this->calculations );
    info.push_back ( this->coincidences );
    return info;
}

void CalculationsCore::run()
{
    while ( true )
    {
        if ( cancel == true )
        {
            break;
        }
        sync.lock();
        if ( pause == true )
        {
            pauseCond.wait ( &sync );
        }
        sync.unlock();
        this->calculations++;
        std::vector<int> input = getRandomIp();
        std::vector< std::vector<int> > volume = getIpVolume ( input );
        std::vector< std::vector<double> > r_input = writeIp ( input, volume );
        double ip[3] = { r_input[0][0], r_input[1][0], r_input[2][0] };
        if ( searchIp ( ip ) == true )
        {
            this->coincidences++;
            Data::CalculationResult result;
            result.r_input = r_input;
            result.ipVolume = volume;
            result.calculations = this->calculations;
            result.coincidences = this->coincidences;
            emit ipFound ( this->coincidences );
            this->wr->saveResult ( result );
        }
    }
}

std::vector<int> CalculationsCore::getRandomIp()
{
    std::vector<int> input;
    while ( input.size() < 9 )
    {
        input.push_back ( 0 );
    }
    int inputSum = 0;
    int loopTime = 0;
    do
    {
        inputSum = 0;
        for ( int x = 0; x < 9; x++ )
        {
            do
            {
                input[x] = rnd->getRandomInt ( 0, ( 10 - inputSum ) );
                if ( loopTime <= 4 )
                {
                    loopTime++;
                }
                else
                {
                    loopTime = 0;
                    break;
                }
            }
            while ( input[x] > this->maximumValue );
            inputSum += input[x];
        }
    }
    while ( inputSum != 9 );
    return input;
}

std::vector< std::vector<int> > CalculationsCore::getIpVolume ( std::vector<int> input )
{
    std::vector< std::vector<int> > volume;
    while ( volume.size() < 3 )
    {
        std::vector<int> vol;
        while ( vol.size() < 9 )
        {
            vol.push_back ( 0 );
        }
        volume.push_back ( vol );
    }
    for ( int x = 0; x < 9; x++ )
    {
        while ( volume[0][x] + volume[1][x] + volume[2][x] != input[x] )
        {
            if ( input[x] > 0 )
            {
                volume[0][x] = rnd->getRandomInt ( 0, input[x] );
            }
            if ( ( input[x] - volume[0][x] ) > 0 )
            {
                volume[1][x] = rnd->getRandomInt ( 0, ( input[x] - volume[0][x] ) );
            }
            if ( ( input[x] - volume[1][x] ) > 0 )
            {
                volume[2][x] = rnd->getRandomInt ( 1, ( input[x] - volume[1][x] ) );
            }
        }
    }
    return volume;
}

std::vector< std::vector<double> >CalculationsCore::writeIp ( std::vector<int> input,
        std::vector< std::vector<int> > volume )
{
    std::vector< std::vector<double> > output;
    while ( output.size() < 3 )
    {
        std::vector<double> out;
        while ( out.size() < 10 )
        {
            out.push_back ( 0 );
        }
        output.push_back ( out );
    }
    std::vector<int> cur_input;
    for ( int x = 0; x < 9; x++ )
    {
        cur_input.push_back ( double ( input[x] ) );
        output[0][ ( x + 1 )] = cur_input[x];
    }
    output[0][0] = Math::ip ( cur_input, this->logarithm );
    output[0][0] = Math::roundDouble ( output[0][0], this->roundDecimals );
    cur_input[0] = ( volume[2][0] + volume[2][1] + volume[2][2] );
    cur_input[1] = ( volume[2][3] + volume[2][4] + volume[2][5] );
    cur_input[2] = ( volume[2][6] + volume[2][7] + volume[2][8] );
    cur_input[3] = ( volume[1][0] + volume[1][1] + volume[1][2] );
    cur_input[4] = ( volume[1][3] + volume[1][4] + volume[1][5] );
    cur_input[5] = ( volume[1][6] + volume[1][7] + volume[1][8] );
    cur_input[6] = ( volume[0][0] + volume[0][1] + volume[0][2] );
    cur_input[7] = ( volume[0][3] + volume[0][4] + volume[0][5] );
    cur_input[8] = ( volume[0][6] + volume[0][7] + volume[0][8] );
    for ( int x = 0; x < 9; x++ )
    {
        output[1][ ( x + 1 )] = cur_input[x];
    }
    output[1][0] = Math::ip ( cur_input, this->logarithm );
    output[1][0] = Math::roundDouble ( output[1][0], this->roundDecimals );
    cur_input[0] = ( volume[2][0] + volume[2][3] + volume[2][6] );
    cur_input[1] = ( volume[2][1] + volume[2][4] + volume[2][7] );
    cur_input[2] = ( volume[2][2] + volume[2][5] + volume[2][8] );
    cur_input[3] = ( volume[1][0] + volume[1][3] + volume[1][6] );
    cur_input[4] = ( volume[1][1] + volume[1][4] + volume[1][7] );
    cur_input[5] = ( volume[1][2] + volume[1][5] + volume[1][8] );
    cur_input[6] = ( volume[0][0] + volume[0][3] + volume[0][6] );
    cur_input[7] = ( volume[0][1] + volume[0][4] + volume[0][7] );
    cur_input[8] = ( volume[0][2] + volume[0][5] + volume[0][8] );
    for ( int x = 0; x < 9; x++ )
    {
        output[2][ ( x + 1 )] = cur_input[x];
    }
    output[2][0] = Math::ip ( cur_input, this->logarithm );
    output[2][0] = Math::roundDouble ( output[2][0], this->roundDecimals );
    return output;
}

bool CalculationsCore::searchIp ( double inputIp[3] )
{
    double ip[3] = { inputIp[0], inputIp[1], inputIp[2] };
    if ( this->ipSearch[0] == 0 )
    {
        if ( this->ipComparison == 3 )
        {
            if ( ( ip[0] == ip[1] ) && ( ip[0] == ip[2] ) && ( ip[0] != 0 ) )
            {
                return true;
            }
        }
        else
        {
            if ( ( ( ip[0] == ip[1] ) && ( ip[0] != 0 ) ) || ( ( ip[0] == ip[2] ) && ( ip[0] != 0 ) ) || ( ( ip[1] == ip[2] ) && ( ip[1] != 0 ) ) )
            {
                return true;
            }
        }
    }
    else if ( this->ipSearch[0] != 0 && this->ipSearch[1] != 0 && this->ipSearch[2] != 0 )
    {
        bool found[3];
        bool iabUsed[3];
        for ( int x = 0; x < 3; x++ )
        {
            for ( int y = 0; y < 3; y++ )
            {
                if ( ip[x] == this->ipSearch[y] && iabUsed[y] == false )
                {
                    iabUsed[y] = true;
                    found[x] = true;
                    break;
                }
            }
            if ( found[x] == false )
            {
                break;
            }
            if ( x == 2 )
            {
                return true;
            }
        }
    }
    else if ( this->ipSearch[0] != 0 && this->ipSearch[1] != 0 && this->ipSearch[2] == 0 )
    {
        bool found[2] = { false, false };
        bool iabUsed[2] = { false, false };
        for ( int x = 0; x < 3; x++ )
        {
            for ( int y = 0; y < 2; y++ )
            {
                if ( ip[x] == this->ipSearch[y] && iabUsed[y] == false )
                {
                    iabUsed[y] = true;
                    if ( found[0] == false )
                    {
                        found[0] = true;
                    }
                    else if ( found[1] == false )
                    {
                        found[1] = true;
                    }
                    break;
                }
            }
            if ( found[0] == true && found[1] == true )
            {
                return true;
            }
        }
    }
    else if ( this->ipSearch[0] != 0 && this->ipSearch[1] == 0 && this->ipSearch[2] == 0 )
    {
        if ( this->extendedIpSearch == true )
        {
            if ( ip[0] == this->ipSearch[0] && ip[1] == ip[2] )
            {
                return true;
            }
            else if ( ip[1] == this->ipSearch[0] && ip[0] == ip[2] )
            {
                return true;
            }
            else if ( ip[2] == this->ipSearch[0] && ip[0] == ip[1] )
            {
                return true;
            }
        }
        else
        {
            if ( ip[0] == this->ipSearch[0] )
            {
                return true;
            }
            else if ( ip[1] == this->ipSearch[0] )
            {
                return true;
            }
            else if ( ip[2] == this->ipSearch[0] )
            {
                return true;
            }
        }
    }
    return false;
}
