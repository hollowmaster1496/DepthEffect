#ifndef FRMMAIN_H
#define FRMMAIN_H

#include <QMainWindow>

#include<opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

namespace Ui {
class frmMain;
}

class frmMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit frmMain(QWidget *parent = 0);
    ~frmMain();

private slots:
    void on_btnOpenFile_clicked();

private:
    Ui::frmMain *ui;
    QImage frmMain::convertOpenCVMatToQtQImage(cv::Mat mat);           // function prototype
};

#endif // FRMMAIN_H
