#include "choosetoplay.h"
#include "ui_choosetoplay.h"
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QFileDialog>
#include <QProgressBar>
#include <iostream>
#include <QMediaPlaylist>
#include "playlist.h"

using namespace std;

void Write(QString text) {
    QString Filename = "C:/Users/admin/Desktop/write/a.txt";
    QFile MyFile(Filename);
    if(!MyFile.open(QFile::WriteOnly | QFile::Text))
    {
    qDebug() << "could not open file for reading";
    return; }

    QTextStream out(&MyFile);
    out << text;
    std::cout << "The text is written!";
    MyFile.flush();
    MyFile.close();
}

ChooseToPlay::ChooseToPlay(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChooseToPlay)
{
    ui->setupUi(this);

    player = new QMediaPlayer(this);
    videoWidget = new QVideoWidget(this);
    playlist = new QMediaPlaylist(player);

    // open a file
    QString Filename = QFileDialog::getOpenFileName(this,"Open a File","","Video File(*.mp4 , *.wmv)");

  //  for(const QString & name: Filename){
     playlist->addMedia(QMediaContent(QUrl::fromLocalFile(Filename)));
   // }


//     Write(Filename);


    player->setPlaylist(playlist);

    player->setMedia(QUrl::fromLocalFile(Filename));
    player->setVideoOutput(videoWidget);
    this->setCentralWidget(videoWidget);


//  create a slider
    slider = new QSlider(this);
    slider->setOrientation(Qt::Horizontal);
    ui->toolBar->addWidget(slider);

    connect(player,&QMediaPlayer::durationChanged,slider,&QSlider::setMaximum);
    connect(player,&QMediaPlayer::positionChanged,slider,&QSlider::setValue);

    connect(slider,&QSlider::sliderMoved,player,&QMediaPlayer::setPosition);



//  show volum
    QLabel *l = new QLabel;
    l->setText("  volume:");
    ui->toolBar->addWidget(l);

    volume_label = new QLabel;
    QString volume = QString::number( player->volume());
    volume_label->setText(volume);
    ui->toolBar->addWidget(volume_label);

    videoWidget->show();

    player->play();
}

ChooseToPlay::~ChooseToPlay()
{
    delete ui;
}

void ChooseToPlay::on_actionPlay_triggered()
{

    player->play();
}

void ChooseToPlay::on_actionPause_triggered()
{
    player->pause();
}

void ChooseToPlay::on_actionaAtFirst_triggered()
{
    player->setPosition(0);
}

void ChooseToPlay::on_actionJump_back_triggered()
{
    int pos = player->position();
//    std::cout<<pos<<std::endl;
    player->setPosition(pos-2000);
}

void ChooseToPlay::on_actionJump_forward_triggered()
{
    int pos = player->position();
    player->setPosition(pos+2000);
}

void ChooseToPlay::on_actionmute_triggered()
{
    player->setVolume(0);
    volume_label->setText("0");
}

void ChooseToPlay::on_actionvolume_increase_triggered()
{
    int volum = player->volume();
    player->setVolume(volum+1);
    volume_label->setText(QString::number( player->volume()));

}

void ChooseToPlay::on_actionvolume_dencrease_triggered()
{
    int volum = player->volume();
    player->setVolume(volum-1);
    volume_label->setText(QString::number( player->volume()));

}

void ChooseToPlay::on_actionopen_triggered()
{
    QString Filename = QFileDialog::getOpenFileName(this,"Open a File","","Video File(*.mp4 , *.wmv)");

    player->setMedia(QUrl::fromLocalFile(Filename));
    player->setVideoOutput(videoWidget);
    this->setCentralWidget(videoWidget);

    on_actionPlay_triggered();
}
