#include "cooldownbar.h"
#include "tacotuesdayconfig.h"

#include <QDebug>
#include <QTimer>

CooldownBar::CooldownBar(QWidget *parent) : QProgressBar(parent)
{
    TacoTuesdayConfig *ttc = TacoTuesdayConfig::Instance();
    cooldownMs = ttc->CooldownMs();
    numSteps = ttc->NumSteps();

    connect(ttc, &TacoTuesdayConfig::on_cooldownMs_changed, [=](int ms){
        qDebug() << "Updating cooldown rate!";
        cooldownMs = ms;
    });

    connect(ttc, &TacoTuesdayConfig::on_numSteps_changed, [=](int steps){
        qDebug() << "Updating steps!";
        numSteps = steps;
    });
}

void CooldownBar::beginCoolingSequence()
{
    setRange(0, cooldownMs);
    setValue(0);

    msPerStep = cooldownMs / numSteps;

    timer = new QTimer();
    timer->setInterval(msPerStep);
    connect(timer, &QTimer::timeout, this, &CooldownBar::incrementProgessBar);

    timer->start();
}

void CooldownBar::incrementProgessBar()
{
    int progress = value() + msPerStep;

    qDebug() << progress << "/" << cooldownMs;

    if (progress <= cooldownMs)
    {
        setValue(progress);
    }
    else if (progress > cooldownMs)
    {
        setValue(0);

        timer->stop();
        delete timer;

        emit cooled();
    }
}
