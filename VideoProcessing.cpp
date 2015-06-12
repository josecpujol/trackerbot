#include "opencv2/opencv.hpp"
#include <iostream>

const char marker_file[] = "./marker.png";

using namespace cv;

int main(int, char**)
{
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    // Read marker and detect features
    cv::Mat marker = cv::imread(marker_file, CV_LOAD_IMAGE_GRAYSCALE );
    if( !marker.data) {
      std::cout<< " Error reading marker: " << marker_file << std::endl;
      return -1;
    }

    FastFeatureDetector detector(10, false);
    std::vector<KeyPoint> keypoints_1;
    detector.detect(marker, keypoints_1 );
    std::cout << "Num keypoints: " << keypoints_1.size() << std::endl;
    std::vector<Point2f> raw_keypoints_marker, filtered_keypoints_marker;
    KeyPoint::convert(keypoints_1, raw_keypoints_marker);

    // Remove those close to each other
    for (auto point : raw_keypoints_marker) {

    }


    Mat img_keypoints_1;

    drawKeypoints( marker, keypoints_1, img_keypoints_1, Scalar::all(-1), DrawMatchesFlags::DEFAULT );
    imshow("Keypoints 1", img_keypoints_1 );

    cv::waitKey();
    return 0;

    cv::namedWindow("edges",1);
    for(;;)
    {
      Mat image;
      cv::Mat frame;
      cap >> frame; // get a new frame from camera
      cv::cvtColor(frame, frame, CV_BGR2GRAY);
      detector.detect(frame, keypoints_1 );
      //        std::cout << "Num keypoints: " << keypoints_1.size() << std::endl;
      drawKeypoints( frame, keypoints_1, img_keypoints_1, Scalar::all(-1), DrawMatchesFlags::DEFAULT );


      cv::imshow("edges", img_keypoints_1);
      if(cv::waitKey(30) >= 0) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
