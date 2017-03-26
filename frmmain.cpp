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

    //print help information
    help();
    //check for the input parameter correctness
    /*if(argc != 3) {
        cerr <<"Incorret input list" << endl;
        cerr <<"exiting..." << endl;
        return EXIT_FAILURE;
    }*/
    //create GUI windows
    //namedWindow("Frame");
    //namedWindow("FG Mask MOG 2");
    //create Background Subtractor objects
    pMOG2 = cv::createBackgroundSubtractorMOG2(); //MOG2 approach
    /*if(strcmp(argv[1], "-vid") == 0) {
        //input data coming from a video
        processVideo(argv[2]);
    }*/
    /*else*/// if(strcmp(argv[1], "-img") == 0) {
        //input data coming from a sequence of images
        //processImages(argv[2]);

   // }
   /* else {
        //error in reading input parameters
        cerr <<"Please, check the input parameters." << endl;
        cerr <<"Exiting..." << endl;
        return EXIT_FAILURE;
    } */


    //destroy GUI windows
    //destroyAllWindows();
    //return EXIT_SUCCESS;
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

    std::string str = strFileName.toStdString();
    char *cstr = &str[0u];
    //processImages(cstr);
    processVideo(cstr);


    cv::waitKey(0);
    return;

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
    //read the first file of the sequence
     frame = cv::imread(firstFrameFilename);
     if(frame.empty()){
         //error in opening the first image
         std::cerr << "Unable to open first image frame: " << firstFrameFilename << endl;
         exit(EXIT_FAILURE);
     }
     //current image filename
     std::string fn(firstFrameFilename);
     //read input data. ESC or 'q' for quitting
     keyboard = 0;
     while( keyboard != 'q' && keyboard != 27 ) {
         //update the background model
         pMOG2->apply(frame, fgMaskMOG2);
         //get the frame number and write it on the current frame
         size_t index = fn.find_last_of("/");
         if(index == std::string::npos) {
             index = fn.find_last_of("\\");
         }
         size_t index2 = fn.find_last_of(".");
         std::string prefix = fn.substr(0,index+1);
         std::string suffix = fn.substr(index2);
         std::string frameNumberString = fn.substr(index+1, index2-index-1);
         std::istringstream iss(frameNumberString);
         int frameNumber = 0;
         iss >> frameNumber;
         rectangle(frame, cv::Point(10, 2), cv::Point(100,20),
                   cv::Scalar(255,255,255), -1);
         putText(frame, frameNumberString.c_str(), cv::Point(15, 15),
                 cv::FONT_HERSHEY_SIMPLEX, 0.5 , cv::Scalar(0,0,0));
         //show the current frame and the fg masks
         //imshow("Frame", frame);
         QImage qimgOriginal = convertOpenCVMatToQtQImage(frame);
         ui->lblOriginal->setPixmap(QPixmap::fromImage(qimgOriginal));

         //imshow("FG Mask MOG 2", fgMaskMOG2);
         QImage qimgFG = convertOpenCVMatToQtQImage(fgMaskMOG2);
         ui->lblOriginal->setPixmap(QPixmap::fromImage(qimgFG));

         //get the input from the keyboard
         keyboard = (char)cv::waitKey( 30 );
         //search for the next image in the sequence
         std::ostringstream oss;
         oss << (frameNumber + 1);
         std::string nextFrameNumberString = oss.str();
         std::string nextFrameFilename = prefix + nextFrameNumberString + suffix;
         //read the next frame
         frame = cv::imread(nextFrameFilename);
         if(frame.empty()){
             //error in opening the next image in the sequence
             std::cerr << "Unable to open image frame: " << nextFrameFilename << endl;
             exit(EXIT_FAILURE);
         }
         //update the path of the current frame
         fn.assign(nextFrameFilename);
    }

}

void frmMain::processVideo(char* videoFilename) {
    //create the capture object
    cv::VideoCapture capture(videoFilename);
    if(!capture.isOpened()){
        //error in opening the video input
        std::cerr << "Unable to open video file: " << videoFilename << endl;
        exit(EXIT_FAILURE);
    }
    //read input data. ESC or 'q' for quitting
    keyboard = 0;
    while( keyboard != 'q' && keyboard != 27 ){
        //read the current frame
        if(!capture.read(frame)) {
            std::cerr << "Unable to read next frame." << endl;
            std::cerr << "Exiting..." << endl;
            exit(EXIT_FAILURE);
        }
        //update the background model
        pMOG2->apply(frame, fgMaskMOG2);
        //get the frame number and write it on the current frame
        std::stringstream ss;
        rectangle(frame, cv::Point(10, 2), cv::Point(100,20),
                  cv::Scalar(255,255,255), -1);
        ss << capture.get(cv::CAP_PROP_POS_FRAMES);
        std::string frameNumberString = ss.str();
        putText(frame, frameNumberString.c_str(), cv::Point(15, 15),
                cv::FONT_HERSHEY_SIMPLEX, 0.5 , cv::Scalar(0,0,0));
        //show the current frame and the fg masks
        imshow("Frame", frame);
        imshow("FG Mask MOG 2", fgMaskMOG2);
        //get the input from the keyboard
        keyboard = (char)cv::waitKey( 30 );
    }
    //delete capture object
    capture.release();
}
