#include "controlbuttons.h"
#include <QStyle>
#include <QHBoxLayout>
#include <QSlider>
#include <QAudio>

ControlButtons::ControlButtons(QWidget *parent): QWidget(parent) {
    // Playing button
    mPlayBtn = new QPushButton();
    mPlayBtn->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    connect(mPlayBtn, &QPushButton::clicked, this, &ControlButtons::clicked);

    // Stop play button
    mStopBtn = new QPushButton();
    mStopBtn->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    mStopBtn->setEnabled(false);
    connect(mStopBtn, &QPushButton::clicked, this, &ControlButtons::stop);

    // Video fast forward button
    mSkipForward = new QPushButton();
    mSkipForward->setIcon(style()->standardIcon(QStyle::SP_MediaSeekForward));
    connect(mSkipForward, &QPushButton::clicked, this, &ControlButtons::sendSkipForward);

    // Video play back button
    mSkipBackward = new QPushButton();
    mSkipBackward->setIcon(style()->standardIcon(QStyle::SP_MediaSeekBackward));
    connect(mSkipBackward, &QPushButton::clicked, this, &ControlButtons::sendSkipBackward);

    // Mute button
    mMuteBtn = new QPushButton();
    mMuteBtn->setIcon(QIcon(":/volume.svg"));
    connect(mMuteBtn, &QPushButton::clicked, this, &ControlButtons::muteClicked);

    // Volume slider
    mVolumeSlider = new QSlider(Qt::Horizontal, this);
    mVolumeSlider->setRange(0, 100);
    mVolumeSlider->setFixedWidth(300);
    connect(mVolumeSlider, &QSlider::valueChanged, this, &ControlButtons::volumeSliderChanged);
    preVloume = mVolumeSlider->value();

    mVolumeValue = new QLabel();
    connect(mVolumeSlider, &QSlider::valueChanged, this, &ControlButtons::volumeValueChanged);

    // Play rate comboBox
    mRateBox = new QComboBox();
    mRateBox->addItem("0.5x", QVariant(0.5));
    mRateBox->addItem("1.0x", QVariant(1.0));
    mRateBox->addItem("2.0x", QVariant(2.0));
    mRateBox->setCurrentIndex(1);
    connect(mRateBox, QOverload<int>::of(&QComboBox::activated), this, &ControlButtons::changeRate);

    // Full screen button
    mFullScreenBtn = new QPushButton();
    mFullScreenBtn->setIcon(QIcon(":/fullScreen.svg"));
    connect(mFullScreenBtn, &QPushButton::clicked, this, &ControlButtons::fullScreenClicked);

    // eastablish the horizontal layout
    QHBoxLayout* controls = new QHBoxLayout();
    controls->addWidget(mStopBtn);
    controls->addWidget(mSkipBackward);
    controls->addWidget(mPlayBtn);
    controls->addWidget(mSkipForward);
    controls->addWidget(mMuteBtn);
    controls->addWidget(mVolumeSlider);
    controls->addWidget(mVolumeValue);
    controls->addStretch();
    controls->addWidget(mRateBox);
    controls->addWidget(mFullScreenBtn);

    setLayout(controls);
}

bool ControlButtons::isMuted() const {
    return volumeMute;
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
    emit changeVoulme(mVolumeSlider->value());
}

// when volume slider is changed, change the text of the volume value label
void ControlButtons::volumeValueChanged() {
    QString volumeValue = QString::number(mVolumeSlider->value());
    mVolumeValue->setText(volumeValue + "%");
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
            mMuteBtn->setIcon(QIcon(":/mute.svg"));
        } else {
            mMuteBtn->setIcon(QIcon(":/volume.svg"));
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

void ControlButtons::changeRate() {
    qreal rate = mRateBox->itemData(mRateBox->currentIndex()).toDouble();
    emit setPlayRate(rate);
}

void ControlButtons::sendSkipForward() {
    emit setSkipForward();
}

void ControlButtons::sendSkipBackward() {
    emit setSkipBackward();
}

// set the media's volume
void ControlButtons::setVolume(int volume) {
    mVolumeSlider->setValue(volume);
}

// when volume slider is set zero, change the mute button
void ControlButtons::changeMuteIcon(int volume) {
    if (volume == 0) {
        mMuteBtn->setIcon(QIcon(":/mute.svg"));
        volumeMute = true;
        emit isVolumeSliderMute(true);
    } else {
        mMuteBtn->setIcon(QIcon(":/volume.svg"));
        volumeMute = false;
        emit isVolumeSliderMute(false);
    }
}

// when full screen button is clicked, emit a setFullScreen signal
void ControlButtons::fullScreenClicked() {
    emit setFullScreen(true);
}
