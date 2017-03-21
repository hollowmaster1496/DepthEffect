#include "frmmain.h"
#include "ui_frmmain.h"

#include<QFileDialog>
#include<QtCore>


void frmMain::help()
{
    std::cout
    << "--------------------------------------------------------------------------" << endl
    << "This program shows how to use background subtraction methods provided by "  << endl
    << " OpenCV. You can process both videos (-vid) and images (-img)."             << endl
                                                                                    << endl
    << "Usage:"                                                                     << endl
    << "./bg_sub {-vid <video filename>|-img <image filename>}"                     << endl
    << "for example: ./bg_sub -vid video.avi"                                       << endl
    << "or: ./bg_sub -img /data/images/1.png"                                       << endl
    << "--------------------------------------------------------------------------" << endl
    << endl;
}


frmMain::frmMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::frmMain)
{
    ui->setupUi(this);
}

frmMain::~frmMain()
{
    delete ui;
}

void frmMain::on_btnOpenFile_clicked()
{
    QString strFileName = QFileDialog::getOpenFileName();       // bring up open file dialog

    if(strFileName == "") {                                     // if file was not chosen
        ui->lblChosenFile->setText("file not chosen");          // update label
        return;                                                 // and exit function
    }

    cv::Mat imgOriginal;            // input image
    cv::Mat imgGrayscale;           // grayscale of input image
    cv::Mat imgBlurred;             // intermediate blured image
    cv::Mat imgCanny;               // Canny edge image

    imgOriginal = cv::imread(strFileName.toStdString());        // open image

    if (imgOriginal.empty()) {									// if unable to open image
        ui->lblChosenFile->setText("error: image not read from file");      // update lable with error message
        return;            // and exit function
    }
    // if we get to this point image was opened successfully
    ui->lblChosenFile->setText(strFileName);                // update label with file name

    cv::cvtColor(imgOriginal, imgGrayscale, CV_BGR2GRAY);               // convert to grayscale
    cv::GaussianBlur(imgGrayscale, imgBlurred, cv::Size(5, 5), 1.5);    // blur
    cv::Canny(imgBlurred, imgCanny, 100, 200);                          // get Canny edges


    // http://docs.opencv.org/trunk/d2/dbd/tutorial_distance_transform.html
    // Change the background from white to black, since that will help later to extract
    // better results during the use of Distance Transform
    for( int x = 0; x < imgOriginal.rows; x++ ) {
      for( int y = 0; y < imgOriginal.cols; y++ ) {
          if ( imgOriginal.at<cv::Vec3b>(x, y) == cv::Vec3b(255,255,255) ) {
            imgOriginal.at<cv::Vec3b>(x, y)[0] = 0;
            imgOriginal.at<cv::Vec3b>(x, y)[1] = 0;
            imgOriginal.at<cv::Vec3b>(x, y)[2] = 0;
          }
        }
    }


    //cv::dilate(imgOriginal, imgBlurred, NULL, cv::Point(-1,-1), 56);
    //cv::resize(imgOriginal, imgBlurred, cv::Size(100, 100), 0, 0, cv::INTER_LINEAR);
    //cv::pyrDown(imgOriginal, imgBlurred, cv::Size(5, 5), cv::BORDER_DEFAULT);

    QImage qimgOriginal = convertOpenCVMatToQtQImage(imgOriginal);         // convert original and Canny images to QImage
    QImage qimgBlurred = convertOpenCVMatToQtQImage(imgBlurred);               //

    ui->lblOriginal->setPixmap(QPixmap::fromImage(qimgOriginal));   // show original and Canny images on labels
    ui->lblCanny->setPixmap(QPixmap::fromImage(qimgBlurred));         //
}


QImage frmMain::convertOpenCVMatToQtQImage(cv::Mat mat) {
    if(mat.channels() == 1) {                   // if grayscale image
        return QImage((uchar*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Indexed8);     // declare and return a QImage
    } else if(mat.channels() == 3) {            // if 3 channel color image
        cv::cvtColor(mat, mat, CV_BGR2RGB);     // invert BGR to RGB
        return QImage((uchar*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);       // declare and return a QImage
    } else {
        qDebug() << "in convertOpenCVMatToQtQImage, image was not 1 channel or 3 channel, should never get here";
    }
    return QImage();        // return a blank QImage if the above did not work
}


void frmMain::processImages(char* firstFrameFilename)
{

}
