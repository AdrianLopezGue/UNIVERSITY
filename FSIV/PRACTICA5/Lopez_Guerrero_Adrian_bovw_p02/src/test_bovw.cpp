/*! \file train_bovw.cpp
\brief Train a Bag of Visual Words model
\authors Fundamentos de Sistemas Inteligentes en Vision
*/

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <tclap/CmdLine.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/ml/ml.hpp>
#include "common_code.hpp"

#define IMG_WIDTH 300

int main(int argc, char * argv[]){

  TCLAP::CmdLine cmd("Test file", ' ', "0.0");

  TCLAP::ValueArg<std::string> basenameArg("b", "basename", "basename for the dataset.", false, "./data", "pathname");
  cmd.add(basenameArg);

  TCLAP::ValueArg<std::string> inputimage("i", "img", "Input image", false, "", "string");
  cmd.add(inputimage);

  TCLAP::ValueArg<std::string> inputvideo("v", "vid", "Input video", false, "", "string");
  cmd.add(inputvideo);

  TCLAP::ValueArg<int> webcamvalue("w", "cam", "Allow webcam or not. Default 0", false, 0, "int");   // 1 ---> WEBCAM ON. 0 ----> WEBCAM OFF
  cmd.add(webcamvalue);

  TCLAP::ValueArg<std::string> classifierFile("x", "classifier", "Name of classifier file", false, "classifier.yml", "/data/");
  cmd.add(classifierFile);

  TCLAP::ValueArg<std::string> dictionaryFile("d", "dict", "Name of dictionary file", false, "dictionary.yml", "/data/");
  cmd.add(dictionaryFile);

  TCLAP::ValueArg<std::string> configFile("c", "config_file", "configuration file for the dataset.", false, "02_ObjectCategories_conf.txt", "/data/");
  cmd.add(configFile);

  TCLAP::ValueArg<int> ndesc("n", "ndesc", "[SIFT] Number of descriptors per image. Value 0 means extract all. Default 0.", false, 0, "int");
  cmd.add(ndesc);

  TCLAP::ValueArg<int> knn("k", "kNN", "Number of neighbours for the kNN classifier. Default 1.", false, 1, "int");
  cmd.add(knn);

  TCLAP::ValueArg<int> nthres("s", "nthres", "[SURF] Threshold for surf descriptor. Default 300.", false, 300, "int");
  cmd.add(nthres);

  TCLAP::ValueArg<int> typeDescriptor("t", "type", "Type of descriptor used for describe the keypoints. Default 1.", false, 1, "int");			// 1 ---> SIFT. 0 ---> SURF
  cmd.add(typeDescriptor);

  TCLAP::ValueArg<int> typeClassifier("a", "tyca", "Type of classifier used to make the classifier. Default 1.", false, 1, "int");			// 0 ---> KNN. 1 ---> SVM
  cmd.add(typeClassifier);

  cmd.parse(argc, argv);

  std::string config_file = basenameArg.getValue() + "/" + configFile.getValue();
  std::string dict_file = "./models/" + dictionaryFile.getValue();
  std::string class_file = "./models/" + classifierFile.getValue();


  std::clog << "Configuration file: "<< config_file << std::endl;
  std::clog << "Image: "<< inputimage.getValue() << std::endl;

  // DICTIONARY

  cv::FileStorage dictFile;
  dictFile.open(dict_file, cv::FileStorage::READ);

  int keywords;
  dictFile["keywords"]>>keywords;

  cv::Ptr<cv::ml::KNearest> dict = cv::Algorithm::read<cv::ml::KNearest>(dictFile.root());

  dictFile.release();

  //CLASSIFY

  std::clog << "Classifying image..." << std::endl;

  cv::FileStorage classFile;
  classFile.open(class_file, cv::FileStorage::READ);

  cv::Ptr<cv::ml::StatModel> classifier;

  if(typeClassifier.getValue()==0){
    cv::Ptr<cv::ml::KNearest> knnClassifier = cv::Algorithm::load<cv::ml::KNearest>(class_file);
    knnClassifier->setDefaultK(knn.getValue());
    classifier = knnClassifier;
  }
  else if(typeClassifier.getValue()==1){
    cv::Ptr<cv::ml::SVM> svm = cv::Algorithm::load<cv::ml::SVM>(class_file);
    classifier = svm;
  }

  classFile.release();


  // LOADING CATEGORIES

  std::vector<std::string> categorias;
  std::vector<int> samples_per_cat;

  load_dataset_information(config_file, categorias, samples_per_cat);


  // IMAGE OR VIDEO?

  if(inputimage.getValue()!=""){
    cv::Mat input = cv::imread(inputimage.getValue(), cv::IMREAD_GRAYSCALE);

    cv::Mat descs;

    if (input.empty())
    {
      std::cerr << "Error: could not read image '" << inputimage.getValue() << "'." << std::endl;
      exit(-1);
    }
    else
    {
      // Fix size
      std::clog << "Extracting Descriptors..." << std::endl;

      resize(input, input, cv::Size(IMG_WIDTH, round(IMG_WIDTH*input.rows / input.cols)));

      if(typeDescriptor.getValue() == 1){
        descs = extractSIFTDescriptors(input, ndesc.getValue());
      }
      else if(typeDescriptor.getValue() == 0){
        descs = extractSURFDescriptors(input, nthres.getValue());
      }
    }

    std::clog << "Computing bowv..." << std::endl;
    cv::Mat bovw = compute_bovw(dict, keywords, descs);

    cv::Mat predicted_labels;
    classifier->predict(bovw, predicted_labels);

    std::clog << "\t\tNearest knn found..." << std::endl;

    CV_Assert(predicted_labels.depth() == CV_32F);
    CV_Assert(predicted_labels.rows == bovw.rows);

    std::cout<<"Category: "<<categorias[predicted_labels.at<float>(0)]<<"\n";

  }

  else if(inputvideo.getValue()!=""){

    cv::VideoCapture input;

    if(webcamvalue.getValue() == 1){
      input.open(0);
    }
    else{
      input.open(inputvideo.getValue());
    }


    cv::Mat currentFrame;
    cv::Mat changingFrame;
    bool wasOk = input.read(currentFrame);

    int key = 0;
    int frameNumber = 0;

    cv::Mat descs;

    while(wasOk && key!=27)
    {

      frameNumber++;

      cv::imshow ("Input", currentFrame);

      changingFrame = currentFrame.clone();

      resize(changingFrame, changingFrame, cv::Size(IMG_WIDTH, round(IMG_WIDTH*changingFrame.rows / changingFrame.cols)));

      if(typeDescriptor.getValue() == 1){
        descs = extractSIFTDescriptors(changingFrame, ndesc.getValue());
      }
      else if(typeDescriptor.getValue() == 0){
        descs = extractSURFDescriptors(changingFrame, nthres.getValue());
      }

      cv::Mat bovw = compute_bovw(dict, keywords, descs);

      cv::Mat predicted_labels;
      classifier->predict(bovw, predicted_labels);

      CV_Assert(predicted_labels.depth() == CV_32F);
      CV_Assert(predicted_labels.rows == bovw.rows);

      std::cout<<"Category frame "<< frameNumber <<": "<<categorias[predicted_labels.at<float>(0)]<<"\n";

      wasOk=input.read(currentFrame);
      key = cv::waitKey(20);
    }
  }
}
