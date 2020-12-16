#ifndef CONTROLBUTTONS_H
#define CONTROLBUTTONS_H

#include <QMediaPlayer>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>

QT_BEGIN_NAMESPACE
class QAbstractSlider;
QT_END_NAMESPACE

class ControlButtons : public QWidget {
    Q_OBJECT
    public:
        ControlButtons(QWidget *parent);
        bool isMuted() const;

    private:
        bool volumeMute = false;
        int preVloume = 0;
        QPushButton* mPlayBtn;
        QPushButton* mStopBtn;
        QPushButton* mSkipForward;
        QPushButton* mSkipBackward;
        QPushButton* mMuteBtn;
        QAbstractSlider* mVolumeSlider;
        QLabel* mVolumeValue;
        QAbstractSlider* mBrightSlider;
        QLabel* mBrightValue;
        QComboBox* mRateBox;
        QPushButton* mFullScreenBtn;
        QMediaPlayer::State mPlayerState = QMediaPlayer::StoppedState;

    signals:
        void play();
        void pasue();
        void stop();
        void playerMute(bool mute);
        void changeVoulme(int volume);
        void changeBright(int bright);
        void isVolumeSliderMute(bool mute);
        void setFullScreen(bool state);
        void setPlayRate(qreal rate);
        void setSkipForward();
        void setSkipBackward();

    private slots:
        void clicked();
        void muteClicked();
        void volumeSliderChanged();
        void volumeValueChanged();
        void changeRate();
        void sendSkipForward();
        void sendSkipBackward();

    public slots:
        void setState(QMediaPlayer::State state);
        void setMuted(bool mute);
        void changeVolumeSlider(bool mute);
        void setVolume(int volume);
        void changeMuteIcon(int volume);
        void fullScreenClicked();
};

#endif // CONTROLBUTTONS_H
