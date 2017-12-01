#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"

using namespace cv;
using namespace ofxCv;

class ofApp : public ofBaseApp{
  
public:
  void setup();
  void update();
  void draw();
  
  // Video images
  ofVideoGrabber         vidGrabber;
  int                 camWidth;
  int                 camHeight;
  Mat                 inImageMat,inImageMatGray;
  
  CascadeClassifier face_cascade;
  vector<cv::Rect> faces;
  vector<ofPoint> center;
  vector<Mat> face;
  ofImage smallFace;
};
