#ifndef FRMMAIN_H
#define FRMMAIN_H

#include <QMainWindow>

#include<opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>
#include <opencv2/videoio.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/imgcodecs.hpp>

namespace Ui {
class frmMain;
}

class frmMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit frmMain(QWidget *parent = 0);
    ~frmMain();   
    void help();
    void processImages(char* firstFrameFilename);
    void processVideo(char* videoFilename);

    cv::Mat frame; // current frame
    cv::Mat fgMaskMOG2; // fg mask (generated by MOG2 method)
    cv::Ptr<cv::BackgroundSubtractor> pMOG2;
    char keyboard;  // input from keyboard

private slots:
    void on_btnOpenFile_clicked();

private:
    Ui::frmMain *ui;
    QImage frmMain::convertOpenCVMatToQtQImage(cv::Mat mat);           // function prototype
};

#endif // FRMMAIN_H
