#include "ctrlbuttons.h"


myWidget::myWidget(vector<TheButtonInfo> videos) : videos(videos)
{
    player->setVideoOutput(videoWidget);

    // a list of the buttons
    vector<TheButton*> buttons;

//contrl buttons
    ctrlWidget->setLayout(layout0);
    fullScreenButton->setBackgroundRole(QPalette::Light);
    fullScreenButton->setText("FullScreen");
    playPauseButton->setIcon(QIcon(":/pause.svg"));
    forward->setIcon(QIcon(":/fast-forward.svg"));
    backward->setIcon(QIcon(":/rewind.svg"));
    previous->setIcon(QIcon(":/back.svg"));
    next->setIcon(QIcon(":/next.svg"));


    //connect
    connect(playPauseButton, SIGNAL(clicked()), this, SLOT(playpause()));



//    volumeSlider->setRange(0, 100);
//    volumeSlider->setValue(player->volume());
//    volumeLabel->hide();
//    volumeLabel->setPixmap(QPixmap(":/speaker.svg"));
//    volumeLabel->setScaledContents(true);
    layout0->addWidget(fullScreenButton);
   // layout0->addWidget(volumeSlider);
    layout0->addWidget(slider);
    layout0->addWidget(previous);
    layout0->addWidget(backward);

    layout0->addWidget(playPauseButton);
    layout0->addWidget(forward);
    layout0->addWidget(next);



//add videos
    buttonWidget->setLayout(layout);

    for ( int i = 0; i < 6; i++ ) {
        TheButton *button = new TheButton(buttonWidget);
        connect(button, SIGNAL(jumpTo(TheButtonInfo* )), player, SLOT (jumpTo(TheButtonInfo* ))); // when clicked, tell the player to play.
        buttons.push_back(button);
        layout->addWidget(button,i/3,i%3,1,1);
        button->init(&videos.at(i));
    }

    player->setContent(&buttons, & videos);
    //add widgets
    top->addWidget(videoWidget);
    top->addWidget(ctrlWidget);
    top->addWidget(buttonWidget);


    // create the main window and layout

    setWindowTitle("tomeo");
    setMinimumSize(800, 680);


}

void myWidget::playpause(){
   i++;
   if(i%2==1){
    playPauseButton->setIcon(QIcon(":/play-button.svg"));
    player->pause();}
   else{
   playPauseButton->setIcon(QIcon(":/pause.svg"));
   player->play();}

}


