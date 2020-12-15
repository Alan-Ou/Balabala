#ifndef CONTROLBUTTONS_H
#define CONTROLBUTTONS_H

#include <QMediaPlayer>
#include <QWidget>
#include <QPushButton>

QT_BEGIN_NAMESPACE
class QAbstractSlider;
QT_END_NAMESPACE

class ControlButtons : public QWidget {
    Q_OBJECT
    public:
        ControlButtons(QWidget *parent);
        bool isMuted() const;
        int volume() const;
    private:
        bool volumeMute = false;
        int preVloume = 0;
        QPushButton* mPlayBtn;
        QPushButton* mStopBtn;
        QPushButton* mMuteBtn;
        QAbstractSlider* mVolumeSlider;
        QMediaPlayer::State mPlayerState = QMediaPlayer::StoppedState;

    signals:
        void play();
        void pasue();
        void stop();
        void playerMute(bool mute);
        void changeVoulme(int volume);

    private slots:
        void clicked();
        void muteClicked();
        void volumeSliderChanged();

    public slots:
        void setState(QMediaPlayer::State state);
        void setMuted(bool mute);
        void changeVolumeSlider(bool mute);
        void setVolume(int volume);
        void changeMuteIcon(int volume);
};

#endif // CONTROLBUTTONS_H
