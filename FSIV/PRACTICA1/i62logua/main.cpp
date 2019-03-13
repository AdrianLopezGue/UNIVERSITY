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


/**
    Calculate the histogram of a certain image.

    @param img: original image that user wants to calculate histogram
    @param bins: int that represents number of colour possibilities of an image
    @param numberPixels: int counting number of pixels of the Image
    @param mask: possible mask that user can apply

    @return float array with the result of calculating normalized histogram in the image.

*/


/*std::vector<float> calculate_histogram(cv::Mat& img, int bins=256, int numberPixels=0, cv::Mat mask=cv::Mat()){

  vector<float> histogramArray(bins, 0);

  // No mask
  if(mask.empty()){

    // In case we dont pass a mask as an argument, we move through the original image with a pointer and increment
    // it in each iteration.
    for(int y=0;y<img.rows;y++){
      uchar *ptr=img.ptr<uchar>(y); //pointer to the y-th image row
      for(int x=0;x<img.cols;x++,ptr++){
        histogramArray[(int)ptr[0]]++;
      }
    }
  }

  // Mask
  else{

    // We only increment the value of the array if the value of the same pixel in the mask is white.
    for(int y=0;y<img.rows;y++){
      uchar *ptr=img.ptr<uchar>(y); //pointer to the y-th image row
      uchar *ptr2=mask.ptr<uchar>(y); //pointer to the y-th mask row
      for(int x=0;x<img.cols;x++,ptr++, ptr2++){
        if(ptr2[0] == bins-1){
          histogramArray[(int)ptr[0]]++;
        }
      }
    }
  }

  // Calculating cumulative array
  for(int i=1; i<bins; i++){
    histogramArray[i] += histogramArray [i-1];
  }

  // Calculating normalized cumulative array
  for(int i=1; i<bins; i++){
    histogramArray[i] = (histogramArray[i] * bins-1)/numberPixels;
  }

  return histogramArray;
}*/

/**
    Create the final image after calculating normalized cumulative array.

    @param normalizedcumulativeArray: normalized histogram array previously made in another function
    @param img: original image
    @param mask: possible mask that user can apply

    @return final image after using normalized histogram array to create it.

*/
/*cv::Mat create_normalizedImage(std::vector<float> normalizedcumulativeArray, cv::Mat originalImage, cv::Mat mask=cv::Mat()){

  cv::Mat configuredImage(originalImage.rows, originalImage.cols, CV_8UC1);

  // No mask
  if(mask.empty()){

    // Move through the new image and set the value of the current pixel depending on the value of the normalized cumulative array in the
    // position of the pointer to the original image in the exact pixel of the new image.

    for(int y=0;y<configuredImage.rows;y++){
      uchar *ptr=configuredImage.ptr<uchar>(y); //pointer to the y-th final image row
      uchar *ptr2=originalImage.ptr<uchar>(y);  //pointer to the y-th original image row

      for(int x=0;x<configuredImage.cols;x++,ptr++, ptr2++){

        ptr[0] = normalizedcumulativeArray[ptr2[0]];

      }
    }
  }

  // Mask
  else{

    // It moves through the new image and set the value of the current pixel depending on the value of the normalized cumulative array in the
    // position of the pointer to the original image in the exact pixel of the new image. It will only occur if the value of the pixel in
    // the mask is white (255).
    // If the value of the pixel in the mask is zero, the value of the pixel in the new image will be the same as the original image(it will
    // not change at all).

    for(int y=0;y<configuredImage.rows;y++){
      uchar *ptr=configuredImage.ptr<uchar>(y); //pointer to the y-th final image row
      uchar *ptr2=originalImage.ptr<uchar>(y);  //pointer to the y-th original image row
      uchar *ptr3=mask.ptr<uchar>(y);           //pointer to the y-th mask row

      for(int x=0;x<configuredImage.cols;x++,ptr++, ptr2++, ptr3++){
        if(ptr3[0] == 255){
          ptr[0] = normalizedcumulativeArray[ptr2[0]];
        }
        else{
          ptr[0] = ptr2[0];
        }
      }
    }
  }

  return configuredImage;
}*/


/**
    Create the final image after calculating normalized cumulative array and with a windows with certain radius.

    @param radius: radius of the window
    @param originalImage: original image
    @param bins: int that represents number of colour possibilities of an image
    @param mask: possible mask that user can apply

    @return final image after using windows to create it.

*/
/*cv::Mat create_normalizedImage_Radius(int radius, cv::Mat originalImage, int bins, cv::Mat mask=cv::Mat()){


  cv::Mat configuredImage(originalImage.rows, originalImage.cols, CV_8UC1);  // Final image
  cv::Mat imgAux((2*radius) + 1, (2*radius) + 1, CV_8UC1);                   // Auxiliary image that user will use to create windows.

  vector<float> normalizedcumulativeArray;
  int numberPixels = imgAux.rows * imgAux.cols;

  // No mask
  if(mask.empty()){

    for(int y=0;y<configuredImage.rows;y++){
      uchar *ptr=configuredImage.ptr<uchar>(y); //pointer to the y-th final image row
      uchar *ptr2=originalImage.ptr<uchar>(y);  //pointer to the y-th original image row

      for(int x=0;x<configuredImage.cols;x++,ptr++, ptr2++){

        // Checks if it possible to create the windows without overpassing borders of the image.
        if((x+radius <= configuredImage.cols) && (x-radius >= 0) && (y+radius <= configuredImage.rows) && (y-radius >= 0)){

          cv::Range rowRange(y-radius,y+radius);
          cv::Range colRange(x-radius,x+radius);

          imgAux = originalImage.operator()(rowRange, colRange);                        // .operator() creates the window around the pixel that the pointer is pointing with specific radius
          normalizedcumulativeArray = calculate_histogram(imgAux, bins, numberPixels);  // Calculate histogram of that window

          ptr[0] = normalizedcumulativeArray[ptr2[0]];                                  // Set the value of the pixel
        }

        // If it is not possible to create the window, it set the value of the original pixel.
        else{
          ptr[0] = ptr2[0];
        }
      }
    }
  }

  // Mask
  else{

    for(int y=0;y<configuredImage.rows;y++){
      uchar *ptr=configuredImage.ptr<uchar>(y);   //pointer to the y-th final image row
      uchar *ptr2=originalImage.ptr<uchar>(y);    //pointer to the y-th original image row
      uchar *ptr3=mask.ptr<uchar>(y);             //pointer to the y-th mask row

      for(int x=0;x<configuredImage.cols;x++,ptr++, ptr2++, ptr3++){

        // Checks if it possible to create the windows without overpassing borders of the image.
        if((x+radius <= configuredImage.cols) && (x-radius >= 0) && (y+radius <= configuredImage.rows) && (y-radius >= 0)){

          // Checks if the value of pixel in the mask is white
          if(ptr3[0] == 255){

            cv::Range rowRange(y-radius,y+radius);
            cv::Range colRange(x-radius,x+radius);

            imgAux = originalImage.operator()(rowRange, colRange);                        // .operator() creates the window around the pixel that the pointer is pointing with specific radius
            normalizedcumulativeArray = calculate_histogram(imgAux, bins, numberPixels);  // Calculate histogram of that window

            ptr[0] = normalizedcumulativeArray[ptr2[0]];                                  // Set the value of the pixel
          }

          // If the value of the pixel in the mask is different to white, it set the value of the original pixel.
          else{
            ptr[0] = ptr2[0];
          }
        }

        // If it is not possible to create the window, it set the value of the original pixel.
        else{
          ptr[0] = ptr2[0];
        }
      }
    }
  }

  return configuredImage;
}*/


cv::Mat equalizeImageNoRadius(cv::Mat& img, int bins=256, int numberPixels=0, cv::Mat mask=cv::Mat()){

  std::vector<float> histogram(bins, 0);
  cv::Mat out(img.rows, img.cols, img.type());

  if(mask.empty()){
    //EXAMEN ENERO PRACTICA 1
    numberPixels = img.rows*img.cols;

    for(int y = 0; y < img.rows; y++){
      uchar *ptr = img.ptr<uchar>(y);
      for(int x = 0; x < img.cols; x++, ptr++){
        histogram[ptr[0]]++;
      }
    }

    for(int i = 1; i<histogram.size(); i++){
      histogram[i] += histogram[i-1];
    }

    for(int i = 0; i<histogram.size(); i++){
      histogram[i] = (histogram[i]*(bins-1))/numberPixels;
    }

    for(int y = 0; y < img.rows; y++){
      uchar *ptr = img.ptr<uchar>(y);
      uchar *ptr2 = out.ptr<uchar>(y);
      for(int x = 0; x < img.cols; x++, ptr++, ptr2++){
        ptr2[0] = histogram[ptr[0]];
      }
    }
  }
  else{
    numberPixels = cv::countNonZero(mask);

    for(int y = 0; y < img.rows; y++){
      uchar *ptr = img.ptr<uchar>(y);
      uchar *ptrmask = mask.ptr<uchar>(y);
      for(int x = 0; x < img.cols; x++, ptr++, ptrmask++){
        if(ptrmask[0] == 255){
          histogram[ptr[0]]++;
        }
      }
    }

    for(int i = 1; i<histogram.size(); i++){
      histogram[i] += histogram[i-1];
    }

    for(int i = 0; i<histogram.size(); i++){
      histogram[i] = (histogram[i]*(bins-1))/numberPixels;
    }

    for(int y = 0; y < img.rows; y++){
      uchar *ptr = img.ptr<uchar>(y);
      uchar *ptr2 = out.ptr<uchar>(y);
      uchar *ptrmask = mask.ptr<uchar>(y);
      for(int x = 0; x < img.cols; x++, ptr++, ptr2++, ptrmask++){
        if(ptrmask[0] == 255){
          ptr2[0] = histogram[ptr[0]];
        }
        else{
          ptr2[0] = ptr[0];
        }
      }
    }
  }

  return out;
}

cv::Mat equalizeImageRadius(int radius, cv::Mat& img, int bins=256, int numberPixels=0, cv::Mat mask=cv::Mat()){

  cv::Mat out(img.rows, img.cols, img.type());
  cv::Mat imgAux((2*radius)+1, (2*radius)+1, CV_8UC1);

  if(mask.empty()){
    for(int y = 0; y<img.rows; y++){
      uchar *ptr = img.ptr<uchar>(y);
      uchar *ptr2 = out.ptr<uchar>(y);
      for(int x = 0; x<img.cols; x++, ptr++, ptr2++){
        if(y-radius>=0 && y+radius<=img.rows && x-radius>=0 && x+radius<=img.cols){

          std::vector<float> histogram(bins, 0);
          cv::Range rowRange(y-radius, y+radius);
          cv::Range colRange(x-radius, x+radius);

          imgAux = img.operator()(rowRange, colRange);

          numberPixels = imgAux.rows*imgAux.cols;

          for(int w = 0; w<imgAux.rows; w++){
            uchar *ptr3 = imgAux.ptr<uchar>(w);
            for(int z = 0; z<imgAux.cols; z++, ptr3++){
              histogram[ptr3[0]]++;
            }
          }

          for(int i = 1; i<histogram.size(); i++){
            histogram[i] += histogram[i-1];
          }

          for(int i = 0; i<histogram.size(); i++){
            histogram[i] = (histogram[i]*(bins-1))/numberPixels;
          }

          ptr2[0] = histogram[ptr[0]];
        }
        else{
          ptr2[0] = ptr[0];
        }
      }
    }
  }
  else{
    for(int y = 0; y<img.rows; y++){
      uchar *ptr = img.ptr<uchar>(y);
      uchar *ptr2 = out.ptr<uchar>(y);
      uchar *ptrmask = mask.ptr<uchar>(y);
      for(int x = 0; x<img.cols; x++, ptr++, ptr2++, ptrmask++){
        if(y-radius>=0 && y+radius<=img.rows && x-radius>=0 && x+radius<=img.cols){
          if(ptrmask[0] == 255){
            std::vector<float> histogram(bins, 0);
            cv::Range rowRange(y-radius, y+radius);
            cv::Range colRange(x-radius, x+radius);

            imgAux = img.operator()(rowRange, colRange);

            numberPixels = imgAux.rows*imgAux.cols;

            for(int w = 0; w<imgAux.rows; w++){
              uchar *ptr3 = imgAux.ptr<uchar>(w);
              for(int z = 0; z<imgAux.cols; z++, ptr3++){
                histogram[ptr3[0]]++;
              }
            }

            for(int i = 1; i<histogram.size(); i++){
              histogram[i] += histogram[i-1];
            }

            for(int i = 0; i<histogram.size(); i++){
              histogram[i] = (histogram[i]*(bins-1))/numberPixels;
            }

            ptr2[0] = histogram[ptr[0]];
          }
          else{
            ptr2[0] = ptr[0];
          }
        }
        else{
          ptr2[0] = ptr[0];
        }
      }
    }
  }

  return out;
}


int main(int argc, char *argv[]) {

  try{

    CmdLineParser cml(argc,argv);

    int radius;
    cv::Mat image, mask;
    string OutFileName;


    // Checking number of arguments

    // Parameter "-r" is in command line
    if (cml["-r"]){
      radius = stoi(cml("-r"));

      // If user pass negative radius, it is converted to 0.
      if(radius < 0){
        radius = 0;
        cout<<"Radius must have positive value. It has been changed to zero.\n";
      }

      image=cv::imread(argv[3], 0);

      if( image.rows==0) {cerr<<"Error reading image"<<endl;return 0;}

      // Mask is provided
      if(argc == 6){
        mask = cv::imread(argv[5], 0);

        if( mask.rows==0) {cerr<<"Error reading image"<<endl;return 0;}
      }
    }

    // Parameter "-r" is not in command line
    else{
      radius = 0;
      image=cv::imread(argv[1], 0);

      if( image.rows==0) {cerr<<"Error reading image"<<endl;return 0;}

      // Mask is provided
      if(argc == 4){
        mask = cv::imread(argv[3], 0);

        if( mask.rows==0) {cerr<<"Error reading image"<<endl;return 0;}
      }
    }


    int bins = 256;
    int numberPixels = image.rows * image.cols;
    cv::Mat configuredImage;

    // Radius has been provided in command line
    if(radius > 0){ // ./ecuImg -r 25 cells.png out cells-mask.png

      std::cout<<"RADIUS\n";

      configuredImage = equalizeImageRadius(radius, image, bins, numberPixels, mask);
      OutFileName = string(argv[4]) + ".jpg";
    }

    // Radius has not been provided in command line
    else{

      // Mask
      if(argc == 4){  //./ecuImg cells.png out cells-mask.png

        std::cout<<"MASK NO RADIUS\n";
        configuredImage = equalizeImageNoRadius(image, bins, numberPixels, mask);
      }

      // No mask
      else{ // ./ecuImg cells.png out
        std::cout<<"NO MASK NO RADIUS\n";
        configuredImage = equalizeImageNoRadius(image, bins, numberPixels);
      }

      OutFileName = string(argv[2]) + ".jpg";
    }

//    cv::Mat dst;
//    cv::equalizeHist( image,  dst );
//    cv::imshow("Equalized with opencv",dst);

    cv::imshow("Configured Image",configuredImage);
    cv::imshow("original",image);
    cv::imwrite(OutFileName, configuredImage);

    cv::waitKey(0);
  }

  catch(std::exception &ex){
    cout<<ex.what()<<endl;
  }

}
