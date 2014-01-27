#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(const char*, int, QWidget *parent = 0);
    ~MainWindow();
    int get_actual_backlight() const;
    int get_saved_backlight() const;
    void set_actual_backlight(int) const;
    void set_saved_backlight(int) const;
    void save_backlight() const;

private:
    void toggle_blank();
    void set_value_from_percent(float) const;
    void createTrayIcon();
    void closeEvent(QCloseEvent *);

    Ui::MainWindow *ui;
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;

    const char* actual_bl_path;
    const char* saved_bl_path;
    int maximum_backlight;

private slots:
    void quit_application();
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
    void on_action15_triggered();
    void on_action20_triggered();
    void on_pushButton_5_clicked();
    void on_pushButton_4_clicked();
    void trayIconClicked(QSystemTrayIcon::ActivationReason);
    void on_action50_triggered();
    void on_action75_triggered();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_actionSee_savedbacklight_file_triggered();
    void on_horizontalSlider_sliderPressed();
    void on_horizontalSlider_actionTriggered(int action);
};

#endif // MAINWINDOW_H
