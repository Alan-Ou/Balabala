#include "player.h"
#include <QVBoxLayout>

Player::Player() {
    mPlayer = new ThePlayer;
    connect(mPlayer, &QMediaPlayer::durationChanged, this, &Player::durationChanged);
    connect(mPlayer, &QMediaPlayer::positionChanged, this, &Player::positionChanged);

    mVideoWidget = new QVideoWidget(this);
    mPlayer->setVideoOutput(mVideoWidget);

    mSlider = new QSlider(Qt::Horizontal, this);
    mSlider->setRange(0, mPlayer->duration() / 1000);
    connect(mSlider, &QSlider::sliderMoved, this, &Player::seekPosition);

    ControlButtons* controlBtns = new ControlButtons(this);
    controlBtns->setState(mPlayer->state());
    controlBtns->setMuted(controlBtns->isMuted());
    controlBtns->setVolume(mPlayer->volume());


    connect(mPlayer, &QMediaPlayer::stateChanged, controlBtns, &ControlButtons::setState);
    connect(mPlayer, &QMediaPlayer::mutedChanged, controlBtns, &ControlButtons::setMuted);
    connect(mPlayer, &QMediaPlayer::volumeChanged, controlBtns, &ControlButtons::setVolume);

    connect(controlBtns, &ControlButtons::play, mPlayer, &QMediaPlayer::play);
    connect(controlBtns, &ControlButtons::pasue, mPlayer, &QMediaPlayer::pause);
    connect(controlBtns, &ControlButtons::stop, mPlayer, &QMediaPlayer::stop);
//    connect(controlBtns, &ControlButtons::stop, mVideoWidget, QOverload<>::of(&QVideoWidget::update));
    connect(controlBtns, &ControlButtons::stop, this, &Player::setMediaSlider0);
    connect(controlBtns, &ControlButtons::playerMute, mPlayer, &QMediaPlayer::setMuted);
    connect(controlBtns, &ControlButtons::playerMute, controlBtns, &ControlButtons::changeVolumeSlider);
    connect(controlBtns, &ControlButtons::changeVoulme, mPlayer, &QMediaPlayer::setVolume);

    QVBoxLayout* displayLayout = new QVBoxLayout;
    displayLayout->addWidget(mVideoWidget);
    displayLayout->addWidget(mSlider);
    displayLayout->addWidget(controlBtns);

    // modify the components' proportion
    displayLayout->setStretchFactor(mVideoWidget, 10);
    displayLayout->setStretchFactor(mSlider, 1);
    displayLayout->setStretchFactor(controlBtns, 1);

    setLayout(displayLayout);
}

void Player::setContent(vector<TheButton *> *buttons, vector<TheButtonInfo>* videos) {
    mPlayer->setContent(buttons, videos);
}

void Player::buttonConnect(TheButton *button) {
    connect(button, SIGNAL(jumpTo(TheButtonInfo*)), mPlayer, SLOT(jumpTo(TheButtonInfo*)));

}

// change the processing slider's maximum length
void Player::durationChanged(qint64 duration) {
    mDuration = duration / 1000;
    mSlider->setMaximum(mDuration);
}

// change the processing slider's position
void Player::positionChanged(qint64 progress) {
    if (!mSlider->isSliderDown()) {
        mSlider->setValue(progress / 1000);
    }
}

void Player::seekPosition(int seconds) {
    mPlayer->setPosition(seconds * 1000);
}

// when click the stop button, set the processing slider to zero
void Player::setMediaSlider0() {
    mSlider->setValue(0);
}

