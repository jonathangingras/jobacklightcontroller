#include <stdlib.h>

#include <QString>
#include <QCloseEvent>
#include <QMenu>
#include <QIcon>

#include "utils.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::set_value_from_percent(float _v) const{
    int value = (int)(_v * maximum_backlight);
    ui->horizontalSlider->setValue(value);
    set_actual_backlight(value);
    save_backlight();
}

void MainWindow::set_actual_backlight(int _bl) const{
    set_back_int(actual_bl_path, _bl);
}

void MainWindow::set_saved_backlight(int _bl) const{
    set_back_int(saved_bl_path, _bl);
}

int MainWindow::get_actual_backlight() const{
    return get_back_int(actual_bl_path);
}

int MainWindow::get_saved_backlight() const{
    return get_back_int(saved_bl_path);
}

void MainWindow::save_backlight() const{
    set_saved_backlight(get_actual_backlight());
}

void MainWindow::toggle_blank(){
    if(!get_actual_backlight())
        set_actual_backlight(get_saved_backlight());
    else
        set_actual_backlight(0);
}

void MainWindow::quit_application(){
    qApp->quit();
}

MainWindow::MainWindow(
        const char * _actual_bl_path,
        int _max_bl,
        QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    actual_bl_path(_actual_bl_path),
    maximum_backlight(_max_bl)
{
    saved_bl_path = get_homefile();
    ui->setupUi(this);

    ui->horizontalSlider->setMaximum(_max_bl);

    int ac_b = get_actual_backlight();
    ui->textLabel->setText(QString::number(ac_b));
    ui->horizontalSlider->setValue(ac_b);

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

    QAction *_15 = trayIconMenu->addAction("&15%");
    connect(_15, SIGNAL(triggered()), this, SLOT(on_action15_triggered()));

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
    connect(_quit, SIGNAL(triggered()), this, SLOT(quit_application()));

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

void MainWindow::trayIconClicked(QSystemTrayIcon::ActivationReason _reason)
{
    if(_reason == QSystemTrayIcon::DoubleClick)
    {
        this->activateWindow();
        this->ui->horizontalSlider->setValue(get_actual_backlight());
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
    quit_application();
}

void MainWindow::on_horizontalSlider_valueChanged(int _value)
{
    int value_2nd = (_value/(float)maximum_backlight)*100;

    ui->textLabel->setText(
                QString::fromUtf8("<html><h1>")
                + QString::number(_value)
                + QString::fromUtf8("/")
                + QString::number(maximum_backlight)
                + QString::fromUtf8(" ( ")
                + QString::number(value_2nd)
                + QString::fromUtf8("% )")
                + QString::fromUtf8("</h1></html>")
                );

    set_actual_backlight(_value);
}

void MainWindow::on_horizontalSlider_sliderReleased() {
    save_backlight();
}

void MainWindow::on_horizontalSlider_sliderPressed() {
    save_backlight();
}

void MainWindow::on_horizontalSlider_actionTriggered(int action) {
    switch(action){
    case 4:
        set_saved_backlight(get_actual_backlight() - 10);
    case 3:
        set_saved_backlight(get_actual_backlight() + 10);
    default:
        break;
    }
}

void MainWindow::on_actionBlank_triggered() {
    toggle_blank();
}

void MainWindow::on_actionRestore_triggered() {
    ui->horizontalSlider->setValue(get_actual_backlight());
}

void MainWindow::on_actionFull_triggered() {
    set_value_from_percent(1.0);
}

void MainWindow::on_action5_triggered() {
    set_value_from_percent(0.05);
}

void MainWindow::on_action15_triggered() {
    set_value_from_percent(0.15);
}

void MainWindow::on_action20_triggered() {
    set_value_from_percent(0.2);
}

void MainWindow::on_action50_triggered() {
    set_value_from_percent(0.50);
}

void MainWindow::on_action75_triggered() {
    set_value_from_percent(0.75);
}

void MainWindow::on_pushButton_clicked() {
    on_actionFull_triggered();
}

void MainWindow::on_pushButton_2_clicked() {
    on_action5_triggered();
}

void MainWindow::on_pushButton_3_clicked() {
    on_actionBlank_triggered();
}

void MainWindow::on_pushButton_5_clicked() {
    on_action20_triggered();
}

void MainWindow::on_pushButton_4_clicked() {
    on_actionRestore_triggered();
}

void MainWindow::on_pushButton_6_clicked() {
    on_action50_triggered();
}

void MainWindow::on_pushButton_7_clicked() {
    on_action75_triggered();
}

void MainWindow::on_pushButton_8_clicked() {
    on_action15_triggered();
}

void MainWindow::on_actionSee_savedbacklight_file_triggered() {
    system("gedit ~/.savedbacklight &");
}
