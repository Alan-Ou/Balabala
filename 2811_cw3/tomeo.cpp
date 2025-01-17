/*
 *
 *    ______
 *   /_  __/___  ____ ___  ___  ____
 *    / / / __ \/ __ `__ \/ _ \/ __ \
 *   / / / /_/ / / / / / /  __/ /_/ /
 *  /_/  \____/_/ /_/ /_/\___/\____/
 *              video for sports enthusiasts...
 *
 *  2811 cw3 : twak
 */

#include <iostream>
#include <QApplication>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QMediaPlaylist>
#include <string>
#include <vector>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <QtCore/QFileInfo>
#include <QtWidgets/QFileIconProvider>
#include <QDesktopServices>
#include <QImageReader>
#include <QMessageBox>
#include <QtCore/QDir>
#include <QtCore/QDirIterator>
#include <QToolButton>
#include <QStyle>
#include <QSlider>
#include "the_player.h"
#include "the_button.h"
#include "player.h"
#include<QScrollArea>

using namespace std;

// read in videos and thumbnails to this directory
vector<TheButtonInfo> getInfoIn (string loc) {

    vector<TheButtonInfo> out =  vector<TheButtonInfo>();
    QDir dir(QString::fromStdString(loc) );
    QDirIterator it(dir);

    while (it.hasNext()) { // for all files

        QString f = it.next();

            if (f.contains("."))

#if defined(_WIN32)
            if (f.contains(".wmv"))  { // windows
#else
            if (f.contains(".mp4"))  { // mac/linux
#endif

            QString thumb = f.left( f .length() - 4) +".png";
            if (QFile(thumb).exists()) { // if a png thumbnail exists
                QImageReader *imageReader = new QImageReader(thumb);
                    QImage sprite = imageReader->read(); // read the thumbnail
                    if (!sprite.isNull()) {
                        QIcon* ico = new QIcon(QPixmap::fromImage(sprite)); // voodoo to create an icon for the button
                        QUrl* url = new QUrl(QUrl::fromLocalFile( f )); // convert the file location to a generic url
                        thumb = f.right(f.length()-loc.length()-1);
                        thumb = thumb.left( thumb .length() - 4);
                        out . push_back(TheButtonInfo( url , ico, thumb  ) ); // add to the output list
                    }
                    else
                        qDebug() << "warning: skipping video because I couldn't process thumbnail " << thumb << endl;
            }
            else
                qDebug() << "warning: skipping video because I couldn't find thumbnail " << thumb << endl;
        }
    }

    return out;
}


int main(int argc, char *argv[]) {

    // let's just check that Qt is operational first
    qDebug() << "Qt version: " << QT_VERSION_STR << endl;

    // create the Qt Application
    QApplication app(argc, argv);

    // collect all the videos in the folder
    vector<TheButtonInfo> videos;

    if (argc == 2)
        videos = getInfoIn( string(argv[1]) );

    if (videos.size() == 0) {

        const int result = QMessageBox::question(
                    NULL,
                    QString("Tomeo"),
                    QString("no videos found! download, unzip, and add command line argument to \"quoted\" file location. Download videos from Tom's OneDrive?"),
                    QMessageBox::Yes |
                    QMessageBox::No );

        switch( result )
        {
        case QMessageBox::Yes:
          QDesktopServices::openUrl(QUrl("https://leeds365-my.sharepoint.com/:u:/g/personal/scstke_leeds_ac_uk/EcGntcL-K3JOiaZF4T_uaA4BHn6USbq2E55kF_BTfdpPag?e=n1qfuN"));
          break;
        default:
            break;
        }
        exit(-1);
    }



    Player* player = new Player();

    // a row of buttons
    QWidget *buttonWidget = new QWidget();
    // a list of the buttons
    vector<TheButton*> buttons;
    // the buttons are arranged horizontally
    QGridLayout *layout = new QGridLayout();

    QScrollArea *scrollArea = new QScrollArea();

    vector<QLabel*> labels;
    player->setLabels(&labels);
    // create the four buttons
    for ( unsigned int i = 0; i < videos.size(); i++ ) {
        TheButton *button = new TheButton(buttonWidget);
        QLabel * label = new QLabel();
        label->setText(videos.at(i).thumb);
        label->setAlignment(Qt::AlignCenter);
        labels.push_back(label);
        button->setFixedWidth(220);
        player->buttonConnect(button);
        buttons.push_back(button);
        layout->addWidget(button,0,i,1,1);
        layout->addWidget(label,1,i,1,1);
        button->init(&videos.at(i));
    }
     buttonWidget->setLayout(layout);
    layout->setSpacing(5);
    scrollArea->setWidget(buttonWidget);
    scrollArea->widget()->setLayout(layout);
    scrollArea->setAlignment(Qt::AlignCenter);
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    // tell the player what buttons and videos are available
    player->setContent(&buttons, &videos);

    // create the main window and layout
    QWidget* window = new QWidget();
    player->setWindow(window);


    QVBoxLayout *top = new QVBoxLayout();
    window->setLayout(top);
    window->setWindowTitle("tomeo");
    window->setMinimumSize(1000, 1000);


    // add the video and the buttons to the top level widget
    top->addWidget(player);
    top->addWidget(scrollArea);

    top->setStretchFactor(player, 3);
    top->setStretchFactor(buttonWidget, 1);

    // showtime!
    window->show();

    // wait for the app to terminate
    return app.exec();
}
