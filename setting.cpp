#include "setting.h"
#include "ui_setting.h"
#include <iostream>
#include<QBoxLayout>
#include<QPushButton>
#include<QFile>
#include<QTextStream>

Setting::Setting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting)
{

    ui->setupUi(this);
    showView();
}

Setting::~Setting()
{
    delete ui;
}



void Setting::on_volumeDown_clicked()
{
    write("volume","down");
    ui->volume_label->setText(QString::number(read("volume")));
}

void Setting::on_volumeUp_clicked()
{
    write("volume","up");
    ui->volume_label->setText(QString::number(read("volume")));
}

void Setting::on_jumpTimeDown_clicked()
{
    write("jumpTime","down");
    ui->jump_label->setText(QString::number(read("jumpTime")));
}

void Setting::on_jumpTimeUp_clicked()
{
    write("jumpTime","up");
    ui->jump_label->setText(QString::number(read("jumpTime")));
}

int Setting::read(QString name){
    QString fileAddress = "C:/Users/admin/Desktop/write/setting.txt";
    QFile MyFile(fileAddress);

    int line1;
    int line2;

    if(MyFile.open(QIODevice::ReadWrite)){
        QTextStream input(&MyFile);
            line1 = input.readLine().toInt();
            line2 = input.readLine().toInt();
    }

    if (name == "volume")
        return line1;
    else if(name == "jumpTime")
        return line2;
}

void Setting::write(QString name, QString action){
    int volume = read("volume");
    int jumpTime = read("jumpTime");

    if (name == "volume"){
        if(action == "up" && volume<100)
            volume+=1;
        else if(action == "down" && volume>0)
            volume-=1;
    }


    else if(name == "jumpTime"){
        if(action == "up")
            jumpTime+=1;
        else if(action == "down" && jumpTime>0)
            jumpTime-=1;
    }

    QString fileAddress = "C:/Users/admin/Desktop/write/setting.txt";
    QFile MyFile(fileAddress);

    if(MyFile.open(QIODevice::ReadWrite)){
        QTextStream input(&MyFile);
            input<<volume<<endl;
            input<<jumpTime<<endl;
    }

}

void Setting::showView(){
    ui->volume_label->setText(QString::number(read("volume")));
    ui->jump_label->setText(QString::number(read("jumpTime")));
}
