#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>

int get_back_int(const char * file);
void set_back_int(const char * file, int backlight);
inline const char * get_homefile()
{
    return (getenv("HOME") + (std::string)"/.savedbacklight").c_str();
}

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(const char * p_path, int p_maxb, QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_actionQuit_triggered();

    void on_horizontalSlider_sliderReleased();

    void on_horizontalSlider_valueChanged(int value);

    void on_actionBlank_triggered();

    void on_actionRestore_triggered();

    void on_actionFull_triggered();

    void on_action5_triggered();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_action20_triggered();

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

    void trayIconClicked(QSystemTrayIcon::ActivationReason);

    void on_action50_triggered();

    void on_action75_triggered();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_actionSee_savedbacklight_file_triggered();

    void on_horizontalSlider_sliderPressed();

    void on_horizontalSlider_actionTriggered(int action);

private:

    void createTrayIcon();
    void closeEvent(QCloseEvent *);

    Ui::MainWindow *ui;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;

    const char * path;
    int maxb;

};

/*class SysTray : public QSystemTrayIcon
{
    Q_OBJECT

public:
    explicit QSystemTrayIcon(QObject * parent = 0);
    ~SysTray();
};*/

#endif // MAINWINDOW_H
