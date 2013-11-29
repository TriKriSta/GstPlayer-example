#ifndef PLAYERFORM_H
#define PLAYERFORM_H

#include <QWidget>
#include <QTimer>
#include "ui_playerform.h"
#include "audioengine.h"

class PlayerForm : public QWidget, public Ui::PlayerForm {
    Q_OBJECT

public:
    explicit PlayerForm(QWidget *parent = 0);
    ~PlayerForm();

private:
    AudioEngine *pEngine;
    QTimer *pTimer;
    bool isPlay;

private slots:
    void sSelectFile();
    void sMusicPlay();
    void sMusicPause();
    void sTimer();
    void sChengetVolume(int val);
    void sChengetPosition(int val);
};

#endif // PLAYERFORM_H
