/*
(c) Fundamentos de Sistemas Inteligenties en Vision
University of Cordoba, Spain
*/

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
//#include <unistd.h>
#include <ctype.h>
#include <cmath>
#include <string>

#include <tclap/CmdLine.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/video.hpp>

using namespace std;
using namespace cv;

/*
Use CMake to compile
*/

int main (int argc, char * const argv[])
{
  /* Default values */
  bool cameraInput=false;
  bool useWhitePatchCorrecction=false;
  bool useChromaticCooridnates=false;
  int threshold;
  int radius;
  const char * filein = 0;
  const char * fileout = 0;
  char opt;

  int optind = 1; // TODO: mjmarin!!!

  TCLAP::CmdLine cmd("Video segmentation", ' ', "0.1");

  TCLAP::ValueArg<std::string> filename("v", "videoname", "Video path", true, "video.avi", "string");
  cmd.add(filename);
  TCLAP::ValueArg<std::string> outname("o", "outfilename", "Output video path", true, "out.avi", "string");
  cmd.add(outname);

  TCLAP::ValueArg<int> thres("t", "threshold", "Threshold value", false, 0, "int");
  cmd.add(thres);

  TCLAP::ValueArg<int> rad("s", "radius", "Radius value", false, 0, "int");
  cmd.add(rad);

  // Parse input arguments
  cmd.parse(argc, argv);

  filein = filename.getValue().c_str();
  fileout = outname.getValue().c_str();

  std::cout << "Input stream:" << filein << endl;
  std::cout << "Output:" << fileout << endl;

  VideoCapture input;

  if (cameraInput)
  input.open(atoi(filein));
  else
  input.open(filein);


  if (!input.isOpened())
  {
    cerr << "Error: the input stream is not opened.\n";
    abort();
  }

  Mat inFrame;
  bool wasOk = input.read(inFrame);
  if (!wasOk)
  {
    cerr << "Error: could not read any image from stream.\n";
    abort();
  }

  double fps=25.0;
  if (!cameraInput)
  fps=input.get(CV_CAP_PROP_FPS);

  Mat outFrame = Mat::zeros(inFrame.size(), CV_8UC1);

  VideoWriter output;
  output.open(fileout, CV_FOURCC('M','J','P','G'), fps, inFrame.size(), 1);
  if (!output.isOpened())
  {
    cerr << "Error: the ouput stream is not opened.\n";
  }

  int frameNumber=0;
  int key = 0;

  Mat changingFrame = inFrame;
  Mat oldFrame;

  Mat absdiffImage;
  Mat originalMask;
  Mat openingImage;
  Mat closingImage;

  Mat finalImage;
  Mat finalMask;

  string OutFileName;

  cv::namedWindow("Output");

  int SliderValue = thres.getValue();
  createTrackbar("Threshold", "Output", &SliderValue, 255);

  while(wasOk && key!=27)
  {

    frameNumber++;

    cv::imshow ("Input", changingFrame);

    if(frameNumber == 1){
      finalImage = Mat::zeros(inFrame.size(), CV_8UC3);
    }
    else{

      absdiff(oldFrame, changingFrame, absdiffImage);

      originalMask = absdiffImage > SliderValue;

      if(rad.getValue() != 0){
        Mat rgb[3];

        split(originalMask, rgb);

        Mat temporalMat;
        Mat refinedMask;

        bitwise_and(rgb[0], rgb[1], temporalMat);
        bitwise_and(temporalMat, rgb[2], refinedMask);

        Mat element = getStructuringElement(MORPH_CROSS, Size(rad.getValue(), rad.getValue()));

        morphologyEx(refinedMask, openingImage, 2, element);
        morphologyEx(openingImage, closingImage, 3, element);

        Mat copiesofMask[3];

        closingImage.copyTo(copiesofMask[0]);
        closingImage.copyTo(copiesofMask[1]);
        closingImage.copyTo(copiesofMask[2]);

        merge(copiesofMask, 3, finalMask);

        finalImage = changingFrame & finalMask;

        cv::imshow ("Binary Mask", finalMask);
      }
      else{
        finalImage = changingFrame & originalMask;

        cv::imshow ("Binary Mask", originalMask);
      }
    }

    changingFrame.copyTo(oldFrame);

    cv::imshow ("Output", finalImage);

    output << finalImage;


    wasOk=input.read(changingFrame);
    key = cv::waitKey(20);

    if(key == 32){

      OutFileName = "out_";
      OutFileName = OutFileName + std::to_string(frameNumber);
      OutFileName = OutFileName + ".png";

      cv::imwrite(OutFileName, finalImage);
    }

  }
  return 0;
}
