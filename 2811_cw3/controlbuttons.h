#ifndef CONTROLBUTTONS_H
#define CONTROLBUTTONS_H

#include <QMediaPlayer>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
class QAbstractSlider;
QT_END_NAMESPACE

class ControlButtons : public QWidget {
    Q_OBJECT
    public:
        ControlButtons(QWidget *parent);
        QComboBox* getRateBox();

        bool isMuted() const;
        bool isNight() const;
    private:
        bool volumeMute = false;
        bool nightMode = false;
        int preVloume = 0;
        QPushButton* mOpenFile;
        QPushButton* mPlayBtn;
        QPushButton* mStopBtn;
        QPushButton* mSkipForward;
        QPushButton* mSkipBackward;
        QPushButton* mMuteBtn;
        QPushButton* mBrightBtn;
        QAbstractSlider* mVolumeSlider;
        QLabel* mVolumeValue;
        QComboBox* mRateBox;
        QPushButton* mFullScreenBtn;
        QMediaPlayer::State mPlayerState = QMediaPlayer::StoppedState;

        //pop up error messages for missing functionality
        QMessageBox* messageFile= new QMessageBox();;


    signals:
        void play();
        void pasue();
        void stop();
        void playerMute(bool mute);
        void playerDark(bool bright);
        void changeVoulme(int volume);
        void isVolumeSliderMute(bool mute);
        void setFullScreen(bool state);
        void setPlayRate(qreal rate);
        void setSkipForward();
        void setSkipBackward();

    private slots:
        void clicked();
        void muteClicked();
        void nightCliked();
        void volumeSliderChanged();
        void volumeValueChanged();
        void changeRate();
        void sendSkipForward();
        void sendSkipBackward();
        void fileOpened();

    public slots:
        void setState(QMediaPlayer::State state);
        void setMuted(bool mute);
        void setNight(bool light);
        void changeVolumeSlider(bool mute);
        void setVolume(int volume);
        void changeMuteIcon(int volume);
        void fullScreenClicked();
};

#endif // CONTROLBUTTONS_H
