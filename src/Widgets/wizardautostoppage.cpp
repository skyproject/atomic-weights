#include "Widgets\wizardautostoppage.h"
#include "ui_wizardautostoppage.h"

WizardAutoStopPage::WizardAutoStopPage ( QWidget *parent ) :
    QWidget ( parent ),
    ui ( new Ui::WizardAutoStopPage )
{
    ui->setupUi ( this );
    connect ( ui->lineMaxCalculations, SIGNAL ( textChanged ( QString ) ),
              this, SLOT ( checkRadioButtons() ) );
    connect ( ui->lineMaxCoincidences, SIGNAL ( textChanged ( QString ) ),
              this, SLOT ( checkRadioButtons() ) );
}

WizardAutoStopPage::~WizardAutoStopPage()
{
    delete ui;
}

void WizardAutoStopPage::checkRadioButtons()
{
    if ( sender()->objectName() == "lineMaxCalculations" )
    {
        ui->radioMaxCalculations->setChecked ( true );
    }
    else
    {
        ui->radioMaxCoincidences->setChecked ( true );
    }
}

uint64_t WizardAutoStopPage::getMaximumCalculations()
{
    if ( ui->radioMaxCalculations->isChecked() == true )
    {
        return ui->lineMaxCalculations->text().toULongLong();
    }
    return 0;
}

uint64_t WizardAutoStopPage::getMaximumCoincidences()
{
    if ( ui->radioMaxCoincidences->isChecked() == true )
    {
        return ui->lineMaxCoincidences->text().toULongLong();
    }
    return 0;
}
