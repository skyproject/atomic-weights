#ifndef WIZARDAUTOSTOPPAGE_H
#define WIZARDAUTOSTOPPAGE_H

#include <QWidget>

namespace Ui
{
    class WizardAutoStopPage;
}

class WizardAutoStopPage : public QWidget
{
        Q_OBJECT

    public:
        explicit WizardAutoStopPage ( QWidget *parent = 0 );
        ~WizardAutoStopPage();
        uint64_t getMaximumCalculations();
        uint64_t getMaximumCoincidences();

    private slots:
        void checkRadioButtons();

    private:
        Ui::WizardAutoStopPage *ui;
};

#endif // WIZARDAUTOSTOPPAGE_H
