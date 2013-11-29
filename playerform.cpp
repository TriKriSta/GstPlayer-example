#include "playerform.h"
#include <QFileDialog>

PlayerForm::PlayerForm(QWidget *parent) : QWidget(parent) {
    setupUi(this);

    pEngine = new AudioEngine();
    pTimer = new QTimer();
    pEngine->Init();

    isPlay = false;
    pSliderVolume->setSliderPosition(50);
    pEngine->SetVolume(0.5);

    connect(pBtnSelect, SIGNAL(clicked()), this, SLOT(sSelectFile()));
    connect(pBtnPlay, SIGNAL(clicked()), this, SLOT(sMusicPlay()));
    connect(pBtnPause, SIGNAL(clicked()), this, SLOT(sMusicPause()));
    connect(pSliderVolume, SIGNAL(sliderMoved(int)), this, SLOT(sChengetVolume(int)));
    connect(pSliderVolume, SIGNAL(valueChanged(int)), this, SLOT(sChengetVolume(int)));
    connect(pSliderDuration, SIGNAL(sliderMoved(int)), this, SLOT(sChengetPosition(int)));
    //connect(pSliderDuration, SIGNAL(valueChanged(int)), this, SLOT(sChengetPosition(int)));
    connect(pTimer, SIGNAL(timeout()), this, SLOT(sTimer()));
}

PlayerForm::~PlayerForm() {
}

void PlayerForm::sSelectFile() {
    QString str = QFileDialog::getOpenFileName(this, trUtf8("Открыть файл"), "/home");
    pEdit->setText(str);
    pEngine->AddFile(str.toLocal8Bit().data());
}

void PlayerForm::sMusicPlay() {
    if (isPlay == false) {
        pEngine->MusicPlay();
        isPlay = true;
        pBtnPlay->setText(trUtf8("Стоп"));
        pTimer->start(1000);
    } else {
        pEngine->MusicStop();
        isPlay = false;
        pBtnPlay->setText(trUtf8("Играть"));
        pTimer->stop();
    }
}

void PlayerForm::sMusicPause() {
    pEngine->MusicPaused();
    isPlay = false;
    pBtnPlay->setText(trUtf8("Играть"));
    pTimer->stop();
}

void PlayerForm::sTimer() {
    quint64 len = static_cast<quint64>(pEngine->GetMusicDuration());
    quint64 pos = static_cast<quint64>(pEngine->GetMusicPosition());
    pSliderDuration->setSliderPosition(100*pos/len);
}

void PlayerForm::sChengetVolume(int val) {
    pEngine->SetVolume((double)val/100);
}

void PlayerForm::sChengetPosition(int val) {
    quint64 len = static_cast<quint64>(pEngine->GetMusicDuration());
    pEngine->SetMusicPosition(len * val / 100);
}
