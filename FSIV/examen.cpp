cv::Mat cargar_y_suavizar (const std::string& filename, float sigma){
  cv::Mat image = cv::imread(filename, IMREAD_GRAYSCALE);

  cv::Mat finalImage(image.rows, image.cols, image.type());

  cv::GaussianBlur(image, finalImage, cv::Size(), sigma, sigma);

  return finalImage;
}

void calcular_media_desviacion(const cv::Mat& img, float& media, float& desv){

  media = 0.0;

  for(int y = 0; y<img.rows; y++){
    uchar *ptr = img.ptr<uchar>(y);
    for(int x = 0; x < img.cols; y++, ptr++){
      media += ptr[0];
    }
  }

  media /= img.rows*img.cols;

  desv = 0.0;
  float aux = 0.0;

  for(int y = 0; y<img.rows; y++){
    uchar *ptr = img.ptr<uchar>(y);
    for(int x = 0; x < img.cols; y++, ptr++){
      aux = ptr[0]-media;
      desv += aux*aux;
    }
  }

  desv /= img.rows*img.cols;

  desv = sqrt(desv);
}

void calcular_y_umbralizar_gradiente(const cv::Mat& img, float umbral, cv::Mat& segmentada){

  cv::Mat dx;
  cv::Mat dy;

  cv::Sobel(img, dx, -1, 1, 0, 3);
  cv::Sobel(img, dy, -1, 0, 1, 3);

  cv::magnitude(dx, dy, segmentada);

  for(int y = 0; y<segmentada.rows; y++){
    floar *ptr = segmentada.ptr<float>(y);
    for(int x = 0; x<segmentada.cols; x++, ptr++){
      if(ptr[0] >= umbral){
        ptr[0] = 0;
      }
      else{
        ptr[0] = 1;
      }
    }
  }
}

cv::Mat calcularBOVW(const std::vector<int> & wordsId, int dict_size){

  cv::Mat bovw = cv::zero(1, dict_size, CV_32F);

  for(int i = 0; i<dict_size; i++){
    bovw.at<float>(wordsId[i])++;
  }

  bovw /= dict_size;

  return bovw;
}

bool detectar_tablero(const cv::Mat& img, const cv::Size& tam, std::vector<cv::Point2f>& esquinas,const cv::TermCriteria& termcrit  ){

  if(cv::findChessboardCorners(img, tam, esquinas)){
    cv::cornerSubPix(img, esquinas, tam, tam, termcrit);
    return true;
  }
  else{
    return false;
  }
}

void calcular_media (const cv::Mat& img, float& r, float& g, float& b){
  r = 0.0;
  g = 0.0;
  b = 0.0;

  for(int y = 0; y<img.rows; y++){
    uchar *ptr = img.ptr<uchar>(y);
    for(int x = 0; x < img.cols; y++, ptr++){
      r += ptr[0];
      g += ptr[1];
      b += ptr[2];
    }
  }

  r/=img.rows*img.cols;
  g/=img.rows*img.cols;
  b/=img.rows*img.cols;
}

std::vector<float> calcular_histograma(const cv::Mat& img){

  std::vector<float> histogram(256, 0);
  int numberPixels = img.rows*img.cols;

  for(int y = 0; y<img.rows; y++){
    uchar *ptr = img.ptr<uchar>(y);
    for(int x = 0; x<img.cols; x++, ptr++){
      histogram[ptr[0]]++;
    }
  }

  for(int i = 1; i<histogram.size(); i++){
    histogram[i] += histogram[i-1];
  }

  for(int i = 0; i<histogram.size(); i++){
    histogram[i] = (histogram[i]-255)/numberPixels;
  }

  return histogram;
}

void calcular_gradiente(const cv::Mat& imgGray, cv::Mat& gX, cv::Mat& gX){

  cv::Sobel(imgGray, gX, -1, 1, 0, 3);
  cv::Sobel(imgGray, gY, -1, 0, 1, 3);

  cv::magnitude(gX, gX, imgGray);
}

void vecino_mas_cercano(const std::vector<cv::Mat> & src, const std::vector<cv::Mat> & dst, std::vector<int> & match){
  
}

bool almacenar_calibracion(const std::string& filename,
                            const cv::Mat& k,
                            const cv::Mat& d,
                            const cv::Mat& r,
                            const cv::Mat& t)
{

}


bool leer_calibracion(cv::Mat &cameraMatrix, cv::Mat &distCoeffs, cv::Mat &rotation, cv::Mat &translation, string ymlFile){

}
