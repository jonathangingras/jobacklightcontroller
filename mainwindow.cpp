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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    std::ifstream l_f;
    std::string ac_b;
    l_f.open("/sys/class/backlight/intel_backlight/brightness");
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
    //if (trayIcon->isVisible()) {
    //    trayIcon->showMessage(tr("Still here!!!"),
    //    tr("This application is still running. To quit please click this icon and select Quit"));
        hide();


        event->ignore(); // Don't let the event propagate to the base class
    //}
}

void MainWindow::on_actionQuit_triggered()
{
    qApp->quit();
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    std::ofstream l_f;
    l_f.open("/sys/class/backlight/intel_backlight/brightness");

    int value_2nd = (value/(float)4882)*100;

    ui->label->setText(  QString::fromUtf8("<html><h1>")
                       + QString::number(value)
                       + QString::fromUtf8("/4882 ( ")
                       + QString::number(value_2nd)
                       + QString::fromUtf8("% )")
                       + QString::fromUtf8("</h1></html>")
                      );
    l_f << value;
    l_f.close();
}

void MainWindow::on_horizontalSlider_sliderReleased()
{
    std::ifstream l_f;
    std::ofstream l_hf;
    l_f.open("/sys/class/backlight/intel_backlight/brightness");
    l_hf.open((getenv("HOME") + (std::string)"/.savedbacklight").c_str());
    std::string curr;
    l_f >> curr;
    l_hf << curr; //<< std::endl;
    l_f.close();
    l_hf.close();
}

void MainWindow::on_horizontalSlider_sliderPressed()
{
    MainWindow::on_horizontalSlider_sliderReleased();
}

void MainWindow::on_horizontalSlider_actionTriggered(int action)
{
    // if 4 --> -10 ;;;; if 3 --> +10
    std::ifstream l_f;
    std::ofstream l_hf;
    int curr;
    l_f.open("/sys/class/backlight/intel_backlight/brightness");
    l_hf.open((getenv("HOME") + (std::string)"/.savedbacklight").c_str());
    l_f >> curr;
    l_f.close();

    if(action == 4)
        l_hf << curr - 10;
    else if(action == 3)
        l_hf << curr + 10;

    l_hf.close();
}

void MainWindow::on_actionBlank_triggered()
{
    std::ifstream l_if;
    std::ifstream l_ihf;
    int lnb, lnbh;
    bool blank_status = false;
    l_if.open("/sys/class/backlight/intel_backlight/brightness");
    l_ihf.open((getenv("HOME") + (std::string)"/.savedbacklight").c_str());
    l_if >> lnb;
    l_ihf >> lnbh;

    if(lnb == 0 && lnbh != 0)
        blank_status = true;

    if(blank_status)
    {
        blank_status = false;
        MainWindow::on_actionRestore_triggered();
    }

    else
    {
        std::ofstream l_f;
        l_f.open("/sys/class/backlight/intel_backlight/brightness");
        l_f << 0;
        ui->horizontalSlider->setValue(0);
        l_f.close();
        blank_status = true;
    }
}

void MainWindow::on_actionRestore_triggered()
{
    std::ofstream l_f;
    std::ifstream l_hf;
    l_f.open("/sys/class/backlight/intel_backlight/brightness");
    l_hf.open((getenv("HOME") + (std::string)"/.savedbacklight").c_str());
    std::string curr;
    l_hf >> curr;
    l_f << curr << std::endl;
    ui->horizontalSlider->setValue(atoi(curr.c_str()));
    l_hf.close();
    l_f.close();
}

void MainWindow::on_actionFull_triggered()
{
    std::ofstream l_f;
    std::ofstream l_hf;
    l_f.open("/sys/class/backlight/intel_backlight/brightness");
    l_hf.open((getenv("HOME") + (std::string)"/.savedbacklight").c_str());
    l_f << 4882;
    l_hf << 4882;
    ui->horizontalSlider->setValue(4882);
    l_f.close();
    l_hf.close();
}

void MainWindow::on_action5_triggered()
{
    std::ofstream l_f;
    std::ofstream l_hf;
    l_f.open("/sys/class/backlight/intel_backlight/brightness");
    l_hf.open((getenv("HOME") + (std::string)"/.savedbacklight").c_str());
    l_f << 245;
    l_hf << 245;
    ui->horizontalSlider->setValue(245);
    l_f.close();
    l_hf.close();
}

void MainWindow::on_action20_triggered()
{
    std::ofstream l_f;
    std::ofstream l_hf;
    l_f.open("/sys/class/backlight/intel_backlight/brightness");
    l_hf.open((getenv("HOME") + (std::string)"/.savedbacklight").c_str());
    l_f << 995;
    l_hf << 995;
    ui->horizontalSlider->setValue(995);
    l_f.close();
    l_hf.close();
}

void MainWindow::on_action50_triggered()
{
    std::ofstream l_f;
    std::ofstream l_hf;
    l_f.open("/sys/class/backlight/intel_backlight/brightness");
    l_hf.open((getenv("HOME") + (std::string)"/.savedbacklight").c_str());
    l_f << 2441;
    l_hf << 2441;
    ui->horizontalSlider->setValue(2441);
    l_f.close();
    l_hf.close();
}

void MainWindow::on_action75_triggered()
{
    std::ofstream l_f;
    std::ofstream l_hf;
    l_f.open("/sys/class/backlight/intel_backlight/brightness");
    l_hf.open((getenv("HOME") + (std::string)"/.savedbacklight").c_str());
    l_f << 3668;
    l_hf << 3668;
    ui->horizontalSlider->setValue(3668);
    l_f.close();
    l_hf.close();
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
