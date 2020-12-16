//
// Created by twak on 11/11/2019.
//

#include "the_player.h"

using namespace std;

ThePlayer::ThePlayer(): QMediaPlayer(NULL) {

    mTimer = new QTimer(NULL);
    mTimer->setInterval(1000); // 1000ms is one second between ...
    mTimer->start();


}

// all buttons have been setup, store pointers here
void ThePlayer::setContent(std::vector<TheButton*>* b, std::vector<TheButtonInfo>* i) {
    buttons = b;
    infos = i;
    jumpTo(buttons -> at(0) -> info);
}



void ThePlayer::jumpTo (TheButtonInfo* button) {
    setMedia( * button -> url);
    emit show( button);
    this->play(); // change the video with stopping state
}
