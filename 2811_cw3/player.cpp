#include "player.h"
#include <QVBoxLayout>
#include <QTime>
#include <QKeyEvent>

Player::Player() {
    playing = new QLabel();
    playing->setAlignment(Qt::AlignCenter);
    QFont ft;
    ft.setPointSize(30);
    playing->setFont(ft);

    mPlayer = new ThePlayer;
    connect(mPlayer, &QMediaPlayer::durationChanged, this, &Player::durationChanged);
    connect(mPlayer, &QMediaPlayer::positionChanged, this, &Player::positionChanged);

    mVideoWidget = new QVideoWidget(this);
    mPlayer->setVideoOutput(mVideoWidget);

    mSlider = new QSlider(Qt::Horizontal, this);
    mSlider->setRange(0, mPlayer->duration() / 1000);
    connect(mSlider, &QSlider::sliderMoved, this, &Player::seekPosition);

    mDurationL = new QLabel(this);

    ControlButtons* controlBtns = new ControlButtons(this);
    controlBtns->setState(mPlayer->state());
    controlBtns->setMuted(controlBtns->isMuted());
    controlBtns->setVolume(mPlayer->volume());
    setRateBox(controlBtns->getRateBox());


    connect(mPlayer, &QMediaPlayer::stateChanged, controlBtns, &ControlButtons::setState);
    connect(mPlayer, &QMediaPlayer::mutedChanged, controlBtns, &ControlButtons::setMuted);
    connect(mPlayer, &QMediaPlayer::volumeChanged, controlBtns, &ControlButtons::setVolume);
    connect(mPlayer, &QMediaPlayer::volumeChanged, controlBtns, &ControlButtons::changeMuteIcon);

    connectCtrBtn(controlBtns);

    connect(mPlayer,&ThePlayer::show,this,&Player::show);

    connect(controlBtns, &ControlButtons::setFullScreen, mVideoWidget, &QVideoWidget::setFullScreen);


    QHBoxLayout* durationLayout = new QHBoxLayout();
    durationLayout->addWidget(mSlider);
    durationLayout->addWidget(mDurationL);

    QVBoxLayout* displayLayout = new QVBoxLayout;
    displayLayout->addWidget(playing);
    displayLayout->addWidget(mVideoWidget);
    displayLayout->addLayout(durationLayout);
    displayLayout->addWidget(controlBtns);

    // modify the components' proportion
    displayLayout->setStretchFactor(mVideoWidget, 10);
    displayLayout->setStretchFactor(displayLayout, 1);
    displayLayout->setStretchFactor(controlBtns, 1);

    setLayout(displayLayout);

    this->grabKeyboard();
}

// Set video content
void Player::setContent(vector<TheButton *> *buttons, vector<TheButtonInfo>* videos) {
    mPlayer->setContent(buttons, videos);
}

void Player::buttonConnect(TheButton *button) {
    connect(button, SIGNAL(jumpTo(TheButtonInfo*)), mPlayer, SLOT(jumpTo(TheButtonInfo*)));

}

// Show thumbnail information
void Player::show(TheButtonInfo* button) {
    playing->setText(button->thumb);

}

void Player::setWindow(QWidget* window) {
    mWindow = window;
}

void Player::setRateBox(QComboBox *rateBox) {
    mRateBox = rateBox;
}

void Player::setLabels(vector<QLabel*>* labels) {
    mLabels = labels;
}

// Add key press event
void Player::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape && mVideoWidget->isFullScreen()) {
        mVideoWidget->setFullScreen(false);
        event->accept();
    } else if (event->key() == Qt::Key_Space) {
        if (mPlayer->state() == QMediaPlayer::State::PlayingState) {
            mPlayer->pause();
        } else if (mPlayer->state() == QMediaPlayer::State::PausedState) {
            mPlayer->play();
        }
    } else if (event->key() == Qt::Key_Up) {
        int newVolume = mPlayer->volume() + 10;
        if (newVolume > 100) {
            newVolume = 100;
        }

        mPlayer->setVolume(newVolume);
    } else if (event->key() == Qt::Key_Down) {
        int newVolume = mPlayer->volume() - 10;
        if (newVolume < 0) {
            newVolume = 0;
        }

        mPlayer->setVolume(newVolume);
    } else if (event->key() == Qt::Key_Right) {
        int newPosition = mPlayer->position() + 3*1000;
        if (newPosition > mDuration*1000) {
            newPosition = mDuration*1000;
        }

        mPlayer->setPosition(newPosition);
    } else if (event->key() == Qt::Key_Left) {
        int newPosition = mPlayer->position() - 3*1000;
        if (newPosition < 0) {
            newPosition = 0;
        }

        mPlayer->setPosition(newPosition);
    }
}

void Player::connectCtrBtn(ControlButtons* controlBtns) {
    connect(controlBtns, &ControlButtons::play, mPlayer, &QMediaPlayer::play);
    connect(controlBtns, &ControlButtons::pasue, mPlayer, &QMediaPlayer::pause);
    connect(controlBtns, &ControlButtons::stop, mPlayer, &QMediaPlayer::stop);
    connect(controlBtns, &ControlButtons::stop, this, &Player::setMediaSlider0);
    connect(controlBtns, &ControlButtons::playerMute, mPlayer, &QMediaPlayer::setMuted);
    connect(controlBtns, &ControlButtons::playerDark, this, &Player::setBackground);
    connect(controlBtns, &ControlButtons::playerDark, controlBtns, &ControlButtons::setNight);

    connect(controlBtns, &ControlButtons::playerMute, controlBtns, &ControlButtons::changeVolumeSlider);
    connect(controlBtns, &ControlButtons::changeVoulme, mPlayer, &QMediaPlayer::setVolume);
    connect(controlBtns, &ControlButtons::isVolumeSliderMute, mPlayer, &QMediaPlayer::setMuted);
    connect(controlBtns, &ControlButtons::setPlayRate, mPlayer, &QMediaPlayer::setPlaybackRate);
    connect(controlBtns, &ControlButtons::setSkipForward, this, &Player::skipForward);
    connect(controlBtns, &ControlButtons::setSkipBackward, this, &Player::skipBackward);


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

    updateDurationL(progress / 1000);
}

void Player::updateDurationL(qint64 currentPosition) {
    QString time;
    if (currentPosition || mDuration) {
        int currentH = currentPosition / 3600;
        currentPosition = currentPosition % 3600;
        int currentM = currentPosition / 60;
        int currentS = currentPosition % 60;
        QTime currentTime(currentH, currentM, currentS);

        int totalH = mDuration / 3600;
        int container = mDuration % 3600;
        int totalM = container / 60;
        int totalS = container % 60;
        QTime totalTime(totalH, totalM, totalS);

        QString format = "mm:ss";
        if (totalH > 0) {
            format = "hh:mm:ss";
        }

        time = currentTime.toString(format) + " / " + totalTime.toString(format);
    }

    mDurationL->setText(time);
}

// Video fast forward
void Player::skipForward() {
    qint64 position = (mSlider->value() + 3) * 1000;
    if (position > mDuration*1000) {
        position = mDuration*1000;
    }

    mPlayer->setPosition(position);
}

// Video play back
void Player::skipBackward() {
    qint64 position = (mSlider->value() - 3) * 1000;
    if (position < 0) {
        position = 0;
    }

    mPlayer->setPosition(position);
}

void Player::seekPosition(int seconds) {
    mPlayer->setPosition(seconds * 1000);
}

// when click the stop button, set the processing slider to zero
void Player::setMediaSlider0() {
    mSlider->setValue(0);
}

void Player::setBackground() {
   mBackgroundLight = !mBackgroundLight;

   if (!mBackgroundLight) {
       QPalette pal(mWindow->palette());

       pal.setColor(QPalette::Background, QColor (34, 34, 34)); //设置背景黑色
       mWindow->setAutoFillBackground(true);
       mWindow->setPalette(pal);

       setStyleSheet("color: white;");
       mRateBox->setStyleSheet("color: black;");

       for (unsigned int i=0; i < mLabels->size(); i++) {
           mLabels->at(i)->setStyleSheet("color: white;");
       }
   } else if (mBackgroundLight) {
       QPalette pal(mWindow->palette());

       pal.setColor(QPalette::Background, QColor (255, 255, 255)); //设置背景黑色
       mWindow->setAutoFillBackground(true);
       mWindow->setPalette(pal);

       setStyleSheet("color: black;");
       mRateBox->setStyleSheet("color: black;");

       for (unsigned int i=0; i < mLabels->size(); i++) {
           mLabels->at(i)->setStyleSheet("color: black;");
       }
   }
}

