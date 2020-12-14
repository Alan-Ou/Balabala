#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
#include <QSlider>
#include <QVBoxLayout>
#include <QVideoWidget>
#include <QPushButton>
#include "the_player.h"
#include "the_button.h"
#include "controlbuttons.h"

class Player: public QWidget {
    Q_OBJECT
    public:
        Player();
        void setContent(vector<TheButton*>* buttons, vector<TheButtonInfo>* videos);
        void buttonConnect(TheButton* button);
    private:
        void setStatusInfo(const QString &info);

        ThePlayer* mPlayer;
        QVideoWidget* mVideoWidget;
        QSlider* mSlider;
        qint64 mDuration;
    private slots:
        void durationChanged(qint64 duration);
        void positionChanged(qint64 progress);

        void seekPosition(int seconds);

        void setMediaSlider0();


};

#endif // PLAYER_H
