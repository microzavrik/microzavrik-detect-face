#ifndef FACE_RECOGNIZER_HPP
#define FACE_RECOGNIZER_HPP

#include <opencv2/opencv.hpp>

#include "PhotoSender.hpp"

using namespace cv;

class FaceRecognizer
{
private:
	CascadeClassifier face_cascade;
	VideoCapture camera;
	Mat frame;
	int frame_skip;
public:
	FaceRecognizer();
	~FaceRecognizer();
	void detectAndDrawFraces();
	void captureAndSaveScreenshot(const std::string& filename);
};

#endif
