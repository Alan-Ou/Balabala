#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
#include <QSlider>
#include <QVBoxLayout>
#include <QVideoWidget>
#include <QPushButton>
#include <QLabel>
#include <vector>
#include <QKeyEvent>
#include "the_player.h"
#include "the_button.h"
#include "controlbuttons.h"

class Player: public QWidget {
    Q_OBJECT
    public:
        Player();
        void setContent(vector<TheButton*>* buttons, vector<TheButtonInfo>* videos);
        void buttonConnect(TheButton* button);
        void show(TheButtonInfo *button);
        void setWindow(QWidget* window);
        void setRateBox(QComboBox* rateBox);
        void setLabels(vector<QLabel*>* labels);

    protected:
        void keyPressEvent(QKeyEvent* event) override;

    private:
        ThePlayer* mPlayer;
        QVideoWidget* mVideoWidget;
        QSlider* mSlider;
        QLabel*playing;
        QLabel* mDurationL;
        qint64 mDuration;
        QWidget* mWindow;
        QComboBox* mRateBox;
        vector<QLabel*>* mLabels;

        bool mBackgroundLight = true;
        void connectCtrBtn(ControlButtons* controlBtns);

    private slots:
        void durationChanged(qint64 duration);
        void positionChanged(qint64 progress);
        void updateDurationL(qint64 progress);
        void skipForward();
        void skipBackward();
        void seekPosition(int seconds);
        void setMediaSlider0();
        void setBackground();



};

#endif // PLAYER_H
