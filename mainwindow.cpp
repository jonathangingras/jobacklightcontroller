#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <fstream>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <QString>
#include <QCloseEvent>
#include <QMenu>
#include <QIcon>
#include <iostream>

int get_back_int(const char * file)
{
    FILE * p = fopen(file , "r");
    char s_maxb[6];
    fgets(s_maxb, 6, p);
    fclose(p);
    return atoi(s_maxb);
}

void set_back_int(const char * file, int backlight)
{
    FILE * p = fopen(file , "w+");
    fprintf(p, "%i", backlight);
    fclose(p);
}

MainWindow::MainWindow(const char * p_path, int p_maxb, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    path(p_path),
    maxb(p_maxb)
{
    ui->setupUi(this);

    std::ifstream l_f;
    std::string ac_b;
    l_f.open(path);
    l_f >> ac_b;
    l_f.close();
    ui->label->setText(QString::fromUtf8((ac_b).c_str()));
    ui->horizontalSlider->setValue(atoi(ac_b.c_str()));    

    createTrayIcon();

    trayIcon->show();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete trayIcon;
    delete trayIconMenu;
}

void MainWindow::createTrayIcon()
{
    trayIconMenu = new QMenu(this);

    QAction *_show = trayIconMenu->addAction("&Show Window");
    connect(_show, SIGNAL(triggered()), this, SLOT(show()));

    trayIconMenu->addSeparator();

    QAction *_5 = trayIconMenu->addAction("&5%");
    connect(_5, SIGNAL(triggered()), this, SLOT(on_action5_triggered()));

    QAction *_20 = trayIconMenu->addAction("&20%");
    connect(_20, SIGNAL(triggered()), this, SLOT(on_action20_triggered()));

    QAction *_50 = trayIconMenu->addAction("&50%");
    connect(_50, SIGNAL(triggered()), this, SLOT(on_action50_triggered()));

    QAction *_75 = trayIconMenu->addAction("&75%");
    connect(_75, SIGNAL(triggered()), this, SLOT(on_action75_triggered()));

    QAction *_full = trayIconMenu->addAction("&Full");
    connect(_full, SIGNAL(triggered()), this, SLOT(on_actionFull_triggered()));

    QAction *_blank = trayIconMenu->addAction("&Blank");
    connect(_blank, SIGNAL(triggered()), this, SLOT(on_actionBlank_triggered()));

    QAction *_restore = trayIconMenu->addAction("&Restore");
    connect(_restore, SIGNAL(triggered()), this, SLOT(on_actionRestore_triggered()));

    trayIconMenu->addSeparator();

    QAction *_quit = trayIconMenu->addAction("&Quit");
    connect(_quit, SIGNAL(triggered()), qApp, SLOT(quit()));

    trayIcon = new QSystemTrayIcon(this);

    trayIcon->setIcon(QIcon(":/images/sys_tray_ic.png"));
    trayIcon->setContextMenu(trayIconMenu);

    connect(
            trayIcon,
            SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this,
            SLOT(trayIconClicked(QSystemTrayIcon::ActivationReason))
           );
}

void MainWindow::trayIconClicked(QSystemTrayIcon::ActivationReason reason)
{
    if(reason == QSystemTrayIcon::DoubleClick)
    {
        this->activateWindow();
        this->show();
        this->setFocus();
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    hide();
    event->ignore();
}

void MainWindow::on_actionQuit_triggered()
{
    qApp->quit();
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    int value_2nd = (value/(float)maxb)*100;

    ui->label->setText(  QString::fromUtf8("<html><h1>")
                       + QString::number(value)
                       + QString::fromUtf8("/")
                       + QString::number(maxb)
                       + QString::fromUtf8(" ( ")
                       + QString::number(value_2nd)
                       + QString::fromUtf8("% )")
                       + QString::fromUtf8("</h1></html>")
                      );

    set_back_int(path, value);
}

void MainWindow::on_horizontalSlider_sliderReleased()
{
    set_back_int(get_homefile(), get_back_int(path));
}

void MainWindow::on_horizontalSlider_sliderPressed()
{
    MainWindow::on_horizontalSlider_sliderReleased();
}

void MainWindow::on_horizontalSlider_actionTriggered(int action)
{
    if(action == 4)
        set_back_int(get_homefile(), get_back_int(path) - 10);
    else if(action == 3)
        set_back_int(get_homefile(), get_back_int(path) + 10);
}

void MainWindow::on_actionBlank_triggered()
{
    if(get_back_int(path) == 0)
        set_back_int(path, get_back_int(get_homefile()));
    else
        set_back_int(path, 0);
}

void MainWindow::on_actionRestore_triggered()
{
    ui->horizontalSlider->setValue(get_back_int(path));
}

void MainWindow::on_actionFull_triggered()
{
    ui->horizontalSlider->setValue(maxb);
    set_back_int(path, maxb);
    set_back_int(get_homefile(), maxb);
}

void MainWindow::on_action5_triggered()
{
    int perval = 0.05 * maxb + 1;
    ui->horizontalSlider->setValue(perval);
    set_back_int(path, perval);
    set_back_int(get_homefile(), perval);
}

void MainWindow::on_action20_triggered()
{
    int perval = 0.2 * maxb + 1;
    ui->horizontalSlider->setValue(perval);
    set_back_int(path, perval);
    set_back_int(get_homefile(), perval);
}

void MainWindow::on_action50_triggered()
{
    int perval = 0.5 * maxb;
    ui->horizontalSlider->setValue(perval);
    set_back_int(path, perval);
    set_back_int(get_homefile(), perval);
}

void MainWindow::on_action75_triggered()
{
    int perval = 0.75 * maxb + 1;
    ui->horizontalSlider->setValue(perval);
    set_back_int(path, perval);
    set_back_int(get_homefile(), perval);
}

void MainWindow::on_pushButton_clicked()
{
    MainWindow::on_actionFull_triggered();
}

void MainWindow::on_pushButton_2_clicked()
{
    MainWindow::on_action5_triggered();
}

void MainWindow::on_pushButton_3_clicked()
{
    MainWindow::on_actionBlank_triggered();
}

void MainWindow::on_pushButton_5_clicked()
{
    MainWindow::on_action20_triggered();
}

void MainWindow::on_pushButton_4_clicked()
{
    MainWindow::on_actionRestore_triggered();
}

void MainWindow::on_pushButton_6_clicked()
{
    MainWindow::on_action50_triggered();
}

void MainWindow::on_pushButton_7_clicked()
{
    MainWindow::on_action75_triggered();
}

void MainWindow::on_actionSee_savedbacklight_file_triggered()
{
    system("gedit ~/.savedbacklight &");
}
