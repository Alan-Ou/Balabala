#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include<QPushButton>
#include <iostream>
#include <QApplication>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QMediaPlaylist>
#include <string>
#include <vector>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QGridLayout>
#include <QtCore/QFileInfo>
#include <QtWidgets/QFileIconProvider>
#include <QDesktopServices>
#include <QImageReader>
#include <QMessageBox>
#include <QtCore/QDir>
#include <QtCore/QDirIterator>
#include <QStyle>
#include<QToolButton>
#include "the_player.h"
#include "the_button.h"
#include <QSlider>

class myWidget : public QWidget
{
    Q_OBJECT

public:
    myWidget(vector<TheButtonInfo> videos);

private:
    vector<TheButtonInfo> videos;

    ThePlayer *player = new ThePlayer();
    QPushButton* fullScreenButton = new QPushButton();
    QPushButton* playPauseButton = new QPushButton;
    //QSlider *volumeSlider = new QSlider(Qt::Horizontal);
    QSlider *slider = new QSlider(Qt::Horizontal);
    QPushButton* forward = new QPushButton;
    QPushButton* backward = new QPushButton;
    QPushButton* previous = new QPushButton;
    QPushButton* next = new QPushButton;
    int i=0;



    //widgets
     QVideoWidget *videoWidget = new QVideoWidget;
     QWidget *ctrlWidget = new QWidget();
     QWidget *buttonWidget = new QWidget();

     //layout
     QHBoxLayout* layout0 = new QHBoxLayout();
     QGridLayout* layout = new QGridLayout();
     QVBoxLayout *top = new QVBoxLayout(this);

private slots:

    void playpause();
//    void seekForward();
//    void seekBackward();
//    void vidNext();
//    void vidPrevious();
//    void searchVideo();
};
#endif // MYWIDGET_H
