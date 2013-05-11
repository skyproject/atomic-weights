/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of atomic-weights program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#ifndef SILENTMODE_H
#define SILENTMODE_H

#include <QObject>

#include "Core/calculationscore.h"
#include "softwareupdate.h"
#include "data.h"

class SilentMode : public QObject
{
        Q_OBJECT

    public:
        SilentMode ( char *arguments[] );

    private slots:
        void start();
        void close();

    private:
        void checkForUpdates();
        SUL::SoftwareUpdate *su;
        CalculationsCore *core;
};

#endif // SILENTMODE_H
