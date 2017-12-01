#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  
  // Set the video grabber
  camWidth         = 640;    // try to grab at this size.
  camHeight         = 480;
  vidGrabber.setDeviceID(0);
  vidGrabber.initGrabber(camWidth,camHeight);
  
  // Load haarcascade
  String face_cascade_name = ofToDataPath("haarcascade_frontalface_alt.xml");
  if( !face_cascade.load(face_cascade_name) ){
    cout << "Error loading 1" << endl;
  };
}

//--------------------------------------------------------------
void ofApp::update(){
  vidGrabber.update();
  inImageMat = ofxCv::toCv(vidGrabber);
  cv::cvtColor(inImageMat, inImageMatGray, CV_BGR2GRAY);
  cv::equalizeHist(inImageMatGray, inImageMatGray);
  
  // Detect faces
  face_cascade.detectMultiScale(inImageMatGray, faces, 1.1, 3, 0|CV_HAAR_SCALE_IMAGE, cv::Size(30, 30) );
  
  // Count faces
  for(int i=0; i<faces.size(); i++){
    ofPoint center_tmp;
    center_tmp.x = faces[i].x + faces[i].width  * 0.5;
    center_tmp.y = faces[i].y + faces[i].height * 0.5;
    center.push_back(center_tmp);
    // Record faces
    Mat faceROI;
    faceROI = inImageMatGray(faces[i]);
    face.push_back(faceROI.clone());
  }
}

//--------------------------------------------------------------
void ofApp::draw(){
  ofSetHexColor(0xffffff);
  vidGrabber.draw(0,0);
  ofNoFill();
  int i = 0;
  // Draw faces
  for(i=0;i<face.size();i++){
    ofCircle(center[i], faces[i].width*0.5);
    toOf(face[i], smallFace);
    smallFace.update();
    if (i != 0){
//    smallFace.draw(100*i, vidGrabber.getHeight() - 100, 100, 100);
    smallFace.draw(faces[0].width+100, faces[0].height+100, 150, 150);
    }
  }
  
  // Don't forget to clear vectors
  face.clear();
  center.clear();
  
  // Show fps
  ofDrawBitmapString(ofToString((int) ofGetFrameRate()), 10, 20);
}
