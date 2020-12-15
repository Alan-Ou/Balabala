#include "controlbuttons.h"
#include <QStyle>
#include <QHBoxLayout>
#include <QSlider>
#include <QAudio>

ControlButtons::ControlButtons(QWidget *parent): QWidget(parent) {



    mPlayBtn = new QPushButton();
    mPlayBtn->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    connect(mPlayBtn, &QPushButton::clicked, this, &ControlButtons::clicked);


    mStopBtn = new QPushButton();
    mStopBtn->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    mStopBtn->setEnabled(false);
    connect(mStopBtn, &QPushButton::clicked, this, &ControlButtons::stop);

    mMuteBtn = new QPushButton();
    mMuteBtn->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
    connect(mMuteBtn, &QPushButton::clicked, this, &ControlButtons::muteClicked);

    mVolumeSlider = new QSlider(Qt::Horizontal, this);
    mVolumeSlider->setRange(0, 100);
    mVolumeSlider->setMaximumWidth(400);
    connect(mVolumeSlider, &QSlider::valueChanged, this, &ControlButtons::volumeSliderChanged);
    preVloume = mVolumeSlider->value();

    // eastablish the horizontal layout
    QHBoxLayout* controls = new QHBoxLayout();
    controls->addWidget(mStopBtn);
    controls->addWidget(mPlayBtn);
    controls->addWidget(mMuteBtn);
    controls->addWidget(mVolumeSlider);

    setLayout(controls);
}

bool ControlButtons::isMuted() const {
    return volumeMute;
}

int ControlButtons::volume() const {
    qreal linearVolume =  QAudio::convertVolume(mVolumeSlider->value() / qreal(100),
                                                QAudio::LogarithmicVolumeScale,
                                                QAudio::LinearVolumeScale);

    return qRound(linearVolume * 100);
}

// click button and emit the signal
void ControlButtons::clicked() {
    switch (mPlayerState) {
    case QMediaPlayer::StoppedState:
        emit play();
        break;
    case QMediaPlayer::PlayingState:
        emit pasue();
        break;
    case QMediaPlayer::PausedState:
        emit play();
        break;
    }
}

void ControlButtons::muteClicked() {
    emit playerMute(!volumeMute);
}

void ControlButtons::volumeSliderChanged() {
    emit changeVoulme(volume());
}

// accroding the media player state to change the button's icon
void ControlButtons::setState(QMediaPlayer::State state) {
    if (state != mPlayerState) {
        mPlayerState = state;

        switch (state) {
        case QMediaPlayer::StoppedState:
            mStopBtn->setEnabled(false);
            mPlayBtn->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
            break;
        case QMediaPlayer::PlayingState:
            mStopBtn->setEnabled(true);
            mPlayBtn->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
            break;
        case QMediaPlayer::PausedState:
            mStopBtn->setEnabled(true);
            mPlayBtn->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
            break;
        }
    }
}

// according the volume state to change the volume button's icon
void ControlButtons::setMuted(bool mute) {
    if (mute != volumeMute) {
        volumeMute = mute;

        if (mute) {
            mMuteBtn->setIcon(style()->standardIcon(QStyle::SP_MediaVolumeMuted));
        } else {
            mMuteBtn->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
        }
    }
}

// when press the mute button, change the value of volume slider
void ControlButtons::changeVolumeSlider(bool mute) {
    if (mute != volumeMute) {
        volumeMute = mute;
    }

    if (volumeMute) {
        preVloume = mVolumeSlider->value();

        mVolumeSlider->setValue(0);
    } else {
        mVolumeSlider->setValue(preVloume);
    }

}

// set the media's volume
void ControlButtons::setVolume(int volume) {
    qreal logarithmicVolume = QAudio::convertVolume(volume / qreal(100),
                                                    QAudio::LinearVolumeScale,
                                                    QAudio::LogarithmicVolumeScale);

    mVolumeSlider->setValue(qRound(logarithmicVolume * 100));
}

// when volume slider is set zero, change the mute button
void ControlButtons::changeMuteIcon(int volume) {
    if (volume == 0) {
        mMuteBtn->setIcon(style()->standardIcon(QStyle::SP_MediaVolumeMuted));
        volumeMute = true;
    } else {
        mMuteBtn->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
        volumeMute = false;
    }
}
