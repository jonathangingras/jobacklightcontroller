#include "mainwindow.h"
#include <QApplication>
#include <cstring>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>

#define MAX_B get_back_int("/sys/class/backlight/intel_backlight/max_brightness")
#define PATH "/sys/class/backlight/intel_backlight/brightness"

int main(int argc, char *argv[])
{
    if(argc == 1)
    {
        QApplication a(argc, argv);
        MainWindow w (PATH, MAX_B);
        w.show();
        return a.exec();
    }
    else
    {
        if(strcmp(argv[1], "-n") == 0 || strcmp(argv[1], "--quiet") == 0)
        {
            QApplication a(argc, argv);
            MainWindow w (PATH, MAX_B);
            return a.exec();
        }
        else if(strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)
        {
            std::cout << std::endl << "Usage: " << argv[0] << " [ option ]"
                      << std::endl << std::endl
                      << "Options:" << std::endl << std::endl
                      << "no option : Start normally" << std::endl
                      << "-n / --quiet : Start w/o popup window" << std::endl
                      << "-h / --help : show this message" << std::endl << std::endl;
            return 0;
        }
        else
        {
            std::cerr << std::endl << "Bad option : " << "Usage: " << argv[0] << " [ option ]"
                      << std::endl << std::endl
                      << "Options:" << std::endl << std::endl
                      << "no option : Start normally" << std::endl
                      << "-n / --quiet : Start w/o popup window" << std::endl
                      << "-h / --help : show this message" << std::endl << std::endl;
            return 1;
        }
    }
}
