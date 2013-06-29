#include "mainwindow.h"
#include <QApplication>
#include <cstring>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>

#define MAX_B get_back_int("/sys/class/backlight/intel_backlight/max_brightness")
#define BL_PATH "/sys/class/backlight/intel_backlight/brightness"

int main(int argc, char *argv[])
{
    if(argc == 1)
    {
        QApplication a(argc, argv);
        MainWindow w (BL_PATH, MAX_B);
        w.show();
        return a.exec();
    }
    else
    {
        if(strcmp(argv[1], "up") == 0)
        {
            int current = get_back_int(BL_PATH);
            int _new_ = current + (0.05 * MAX_B);
            set_back_int(BL_PATH, _new_);
            set_back_int(get_homefile(), _new_);
        }
        else if(strcmp(argv[1], "down") == 0)
        {
            int current = get_back_int(BL_PATH);
            int _new_ = current - (0.05 * MAX_B);
            set_back_int(BL_PATH, _new_);
            set_back_int(get_homefile(), _new_);
        }
        else if(strcmp(argv[1], "-f") == 0 || strcmp(argv[1], "--files") == 0)
        {
            std::cout << std::endl << "Files:" << std::endl << std::endl
                      << "BL system file :      " << get_back_int(BL_PATH) << std::endl
                      << "home saved BL file :  " << get_back_int(get_homefile()) << std::endl
                      << std::endl;
        }
        else if(strcmp(argv[1], "-n") == 0 || strcmp(argv[1], "--quiet") == 0)
        {
            QApplication a(argc, argv);
            MainWindow w (BL_PATH, MAX_B);
            return a.exec();
        }
        else if(strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)
        {
            std::cout << std::endl << "Usage: " << argv[0] << " [ option ]"
                      << std::endl << std::endl
                      << "Options:" << std::endl << std::endl
                      << "no option    : Start normally" << std::endl
                      << "-n / --quiet : Start w/o popup window" << std::endl
                      << "-h / --help  : show this message" << std::endl
                      << "-f / --files : Show content of BL files" << std::endl
                      << "up           : Increase BL of 5%" << std::endl
                      << "down         : Decrease BL of 5%" << std::endl
                      << std::endl;
            return 0;
        }
        else
        {
            std::cerr << std::endl << "Bad option : " << "Usage: " << argv[0] << " [ option ]"
                      << std::endl
                      << "Type -h / --help for help message"
                      << std::endl;
            return 1;
        }
    }
}
