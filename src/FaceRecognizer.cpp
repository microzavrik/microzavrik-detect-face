#include "FaceRecognizer.hpp"
#include <thread>

FaceRecognizer::FaceRecognizer()
{
	face_cascade.load("haarcascade_frontalface_alt.xml");
	camera.open(0);
	if (!camera.isOpened()) {
		std::cerr << "Error: Could not open camera." << std::endl;
	}
}

FaceRecognizer::~FaceRecognizer()
{
	camera.release();
	destroyAllWindows();
}

void FaceRecognizer::detectAndDrawFraces()
{
	while (true)
	{
		camera >> frame;
		
		if (frame.empty()) {
			std::cerr << "Error: Cannot gram frame." << std::endl;
			break;
		}

		if (frame_skip % 2 == 0) {
			resize(frame, frame, Size(frame.cols / 2, frame.rows / 2));
			Mat gray_frame;
			cvtColor(frame, gray_frame, COLOR_BGR2GRAY);
			equalizeHist(gray_frame, gray_frame);

			std::vector<Rect> faces;
			face_cascade.detectMultiScale(gray_frame, faces);

			for (const auto& face : faces) {
				rectangle(frame, face, Scalar(255, 0, 0), 2);
				std::cout << "Face detected" << std::endl;
				captureAndSaveScreenshot("bebra_face.jpg");
				PhotoSender sender;
				sender.connectToServer("127.0.0.1", "8080");
				sender.sendPhoto("bebra_face.jpg");
				sender.run();

				std::this_thread::sleep_for(std::chrono::seconds(5));
			}

			imshow("Face Detection", frame);

			if (waitKey(1) == 'q') {
				break;
			}
		}
		frame_skip++;
	}
}

void FaceRecognizer::captureAndSaveScreenshot(const std::string& filename)
{
	if (!frame.empty()) {
		imwrite(filename, frame);
		std::cout << "Screenshot saved as " << filename << std::endl;
	}
	else {
		std::cerr << "Error: Empty frame, cannot save screenshot" << std::endl;
	}
}