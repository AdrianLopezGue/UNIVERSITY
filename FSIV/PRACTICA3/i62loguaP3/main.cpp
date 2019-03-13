#include <opencv2/core/core.hpp> //core routines
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>//imread,imshow,namedWindow,waitKey
#include "opencv2/imgproc/imgproc.hpp"
#include <vector>
#include <iostream>
#include <string>

using namespace std;


class CmdLineParser{
  int argc;
  char **argv;
public:
  CmdLineParser(int _argc,char **_argv):argc(_argc),argv(_argv){}
  bool operator[] ( string param ) {int idx=-1; for ( int i=0; i<argc && idx==-1; i++ ) if ( string ( argv[i] ) ==param ) idx=i; return ( idx!=-1 ) ; }
  string operator()(string param,string defvalue="-1"){int idx=-1; for ( int i=0; i<argc && idx==-1; i++ ) if ( string ( argv[i] ) ==param ) idx=i; if ( idx==-1 ) return defvalue; else return ( argv[ idx+1] ); }
};

void readYml(cv::Mat &cameraMatrix, cv::Mat &distCoeffs, cv::Mat &rotation, cv::Mat &translation, string ymlFile){
  cv::FileStorage file(ymlFile, cv::FileStorage::READ);

  if (file.isOpened())
  {
    file["camera-matrix"] >> cameraMatrix;
    file["distortion-coefficients"] >> distCoeffs;
    file["rotation-matrix"] >> rotation;
    file["translation-vector"] >> translation;

    file.release();
  }
}


int main(int argc, char *argv[]) {

  try{

    CmdLineParser cml(argc,argv);

    if(argc != 6){
      std::cout<<"Arguments introduced incorrectly, properly way: /augReal rows cols size intrinsics.yml <input video-file|cam-idx>\n";
      exit(-1);
    }

    int rows = atoi(argv[2]);
    int cols = atoi(argv[1]);
    int size = atoi(argv[3]);

    string ymlFile = argv[4];

    string videoName(argv[5]);
    cv::VideoCapture video(videoName);

    if( !video.isOpened()){
      cout << "Cannot open the video file\n" << endl;
      exit(-1);
    }

    cv::Mat colourFrame;
    cv::Mat grayFrame;

    cv::Mat cameraMatrix, distCoeffs, rotation, translation;
    readYml(cameraMatrix, distCoeffs, rotation, translation, ymlFile);

    while(video.grab()) {

      std::vector<cv::Point2f> imagePoints;
      std::vector<cv::Point3f> objectPoints;

      video.retrieve(colourFrame);

      cv::cvtColor(colourFrame, grayFrame, cv::COLOR_BGR2GRAY);

      for (int i = 0; i < cols; i++) {
        for(int j = 0; j < rows; j++){
          objectPoints.push_back(cv::Point3f(j*size,i*size, 0.0f));
        }
      }

      if(findChessboardCorners(colourFrame, cv::Size(rows, cols), imagePoints)){
        cv::cornerSubPix(grayFrame, imagePoints, cv::Size(5,5), cv::Size(-1,-1), cv::TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 30, 0.1));

        cv::Mat rvec, tvec;

        // Obtaining the pose of the camera giving 3D points, their 2D projections, and data from a calibrated camera
        cv::solvePnP(objectPoints, imagePoints, cameraMatrix, distCoeffs, rvec, tvec);

        std::vector<cv::Point3f> points3D;

        // Calculating center of the reference system
        points3D.push_back(cv::Point3f((rows/2)*size,(cols/2)*size,0));
        points3D.push_back(cv::Point3f(((rows/2)+1)*size,(cols/2)*size,0));
        points3D.push_back(cv::Point3f((rows/2)*size,((cols/2)+1)*size,0));
        points3D.push_back(cv::Point3f((rows/2)*size,(cols/2)*size,-size));

        std::vector<cv::Point2f> imagePoints;

        // Project 3D points in a image plane (imagePoints). imagePoint will keep the position in the image of x,y,z of the center of the reference system
        cv::projectPoints(points3D ,rvec, tvec, cameraMatrix, distCoeffs, imagePoints);

        cv::Scalar red(255,0,0);
        cv::Scalar green(0,255,0);
        cv::Scalar blue(0,0,255);


        cv::line(colourFrame,imagePoints[0],imagePoints[1], blue,2); // red
        cv::line(colourFrame,imagePoints[0],imagePoints[2], red,2); // green
        cv::line(colourFrame,imagePoints[0],imagePoints[3], green,2); // blue
      }

      cv::imshow("image", colourFrame);
      if (cv::waitKey(10) >= 0) break;
    }
  }

  catch(std::exception &ex){
    cout<<ex.what()<<endl;
  }

}
