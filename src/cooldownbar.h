#ifndef COOLDOWNBAR_H
#define COOLDOWNBAR_H

#include <QProgressBar>
#include <QWidget>

class CooldownBar : public QProgressBar
{
    Q_OBJECT

public:
    CooldownBar(QWidget *parent = nullptr);
    void beginCoolingSequence();
    bool cooling();
    void incrementProgessBar();
signals:
    void cooled();
private:
    static const int DEFAULT_COOLDOWN = 2000;
    static const int DEFAULT_STEPS = 50;

    QTimer *timer;

    int msPerStep;
    int cooldownMs;
    int numSteps;
    int stepCount = 0;
    bool alreadyCooling = false;

};

#endif // COOLDOWNBAR_H
