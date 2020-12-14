//
// Created by twak on 11/11/2019.
//

#include "the_player.h"

using namespace std;

ThePlayer::ThePlayer(): QMediaPlayer(NULL) {
//    setVolume(0); // be slightly less annoying
//    connect (this, SIGNAL (stateChanged(QMediaPlayer::State)), this, SLOT (playStateChanged(QMediaPlayer::State)) );

    mTimer = new QTimer(NULL);
    mTimer->setInterval(1000); // 1000ms is one second between ...
    mTimer->start();
    connect( mTimer, SIGNAL (timeout()), SLOT ( shuffle() ) ); // ...running shuffle method

}

// all buttons have been setup, store pointers here
void ThePlayer::setContent(std::vector<TheButton*>* b, std::vector<TheButtonInfo>* i) {
    buttons = b;
    infos = i;
    jumpTo(buttons -> at(0) -> info);
}

// change the image and video for one button every one second
void ThePlayer::shuffle() {
    TheButtonInfo* i = & infos -> at (rand() % infos->size() );
//        setMedia(*i->url);
    buttons -> at( updateCount++ % buttons->size() ) -> init( i );
}

//void ThePlayer::playStateChanged (QMediaPlayer::State ms) {
//    switch (ms) {
//        case QMediaPlayer::State::StoppedState:
//            this->stop(); // starting playing again...
//            break;
//    default:
//        break;
//    }
//}

void ThePlayer::jumpTo (TheButtonInfo* button) {
    setMedia( * button -> url);
    this->stop(); // change the video with stopping state
}
