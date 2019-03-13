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



void convolve(cv::Mat& in, int radius, cv::Mat& out){

  int imageSize = (2*radius)+1;
  cv::Mat filter(imageSize, imageSize, CV_32FC1);

  filter = 1.0/(imageSize*imageSize);

  if((filter.type()!=CV_32FC1)){
    std::cout<<"Incorrected filters type\n";
    exit(-1);
  }
  if((in.type()!=CV_32FC1)){
    std::cout<<"Incorrected inputs type\n";
    exit(-1);
  }

  int radio = (filter.rows-1)/2;
  float sumatorio = 0.0;

  for(int y = radio; y<(out.rows-radio); y++){
    float *ptr2 = out.ptr<float>(y, radio);

    for(int x = radio; x<(out.cols-radio); x++, ptr2++){
      cv::Mat imgAux = in(cv::Rect(x-radio, y-radio, filter.rows, filter.cols));

      for(int w = 0; w<imgAux.rows; w++){
        for(int z = 0; z<imgAux.cols; z++){
          sumatorio += imgAux.at<float>(w,z)*filter.at<float>(w,z);
        }
      }

      ptr2[0] = sumatorio;
      sumatorio = 0.0;
    }
  }
}

int main(int argc, char *argv[]) {

  try{

    CmdLineParser cml(argc,argv);

    int radius;
    int gain;
    cv::Mat image;
    string OutFileName;

    // Checking number of arguments

    // Parameter "-r" is in command line
    if (cml["-r"]){
      radius = stoi(cml("-r"));

      // If user pass negative radius, it is converted to 0.
      if(radius < 0){
        radius = 1;
        cout<<"Radius must have positive value. It has been changed to zero.\n";
      }
      // Parameter "-g" is in command line
      if (cml["-g"]){
        gain = stoi(cml("-g"));

        // Gain is less than 0 or greater than 10
        if(gain>10 || gain<0){
          gain = 1;
          cout<<"Gain must between 0 and 10. Set value to 1\n";
        }

        image=cv::imread(argv[5], 0);
        if( image.rows==0) {cerr<<"Error reading image"<<endl;return 0;}

        OutFileName = string(argv[6]) + ".jpg";
      }
      // Gain not provided
      else{

        gain = 1;

        image=cv::imread(argv[3], 0);
        if( image.rows==0) {cerr<<"Error reading image"<<endl;return 0;}

        OutFileName = string(argv[4]) + ".jpg";
      }
    }
    // Radius not provided
    else{

      radius = 1;

      // Parameter "-g" is in command line
      if (cml["-g"]){
        gain = stoi(cml("-g"));

        if(gain>10 || gain<0){
          gain = 1;
          cout<<"Gain must between 0 and 10. Set value to 1\n";
        }

        image=cv::imread(argv[3], 0);
        if( image.rows==0) {cerr<<"Error reading image"<<endl;return 0;}

        OutFileName = string(argv[4]) + ".jpg";
      }
      // Gain not provided
      else{

        gain = 1;

        image=cv::imread(argv[1], 0);
        if( image.rows==0) {cerr<<"Error reading image"<<endl;return 0;}

        OutFileName = string(argv[2]) + ".jpg";
      }
    }

    // Converting original image with uchar values to floating points values
    cv::Mat originalImageOnFloat;
    image.convertTo(originalImageOnFloat, CV_32FC1);

    //cv::Mat BoxFilter;
    cv::Mat outImage(originalImageOnFloat.rows, originalImageOnFloat.cols, CV_32FC1);

    // Creating box filter
    //BoxFilter = createBoxFilter(radius);

    // Convolution
    convolve(originalImageOnFloat, radius, outImage);

    // Final Operation
    cv::Mat outImage2 = ((gain+1)*originalImageOnFloat) - (gain*outImage);

    cv::imwrite(OutFileName, outImage2);

    cv::waitKey(0);
  }

  catch(std::exception &ex){
    cout<<ex.what()<<endl;
  }

}
