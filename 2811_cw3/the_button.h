//
// Created by twak on 11/11/2019.
//

#ifndef CW2_THE_BUTTON_H
#define CW2_THE_BUTTON_H


#include <QPushButton>
#include <QUrl>


class TheButtonInfo {

public:
    QUrl* url; // video file to play
    QIcon* icon; // icon to display
    QString  thumb;

    TheButtonInfo ( QUrl* url, QIcon* icon, QString  thumb) : url (url), icon (icon), thumb(thumb) {}
};

class TheButton : public QPushButton {
    Q_OBJECT

public:
    TheButtonInfo* info;

     TheButton(QWidget *parent) :  QPushButton(parent) {
         setIconSize(QSize(200,110));
         connect(this, SIGNAL(released()), this, SLOT (clicked() )); // if QPushButton clicked...then run clicked() below
    }

    void init(TheButtonInfo* i);

private slots:
    void clicked();

signals:
    void jumpTo(TheButtonInfo*);

};

#endif //CW2_THE_BUTTON_H
