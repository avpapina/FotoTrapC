#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    string inputDir = "C:/Users/avpap/source/repos/FotoTrapC/FotoTrapC/datas/";
    string cascadePath = "C:/Users/avpap/source/repos/FotoTrapC/FotoTrapC/datas/haarcascade_frontalcatface_extended.xml";

    CascadeClassifier objectCascade;
    if (!objectCascade.load(cascadePath)) {
        cerr << "Error loading cascade: " << cascadePath << endl;
        return -1;
    }

    for (int i = 1; i <= 10; ++i) {
        string videoName = "video" + to_string(i) + ".mp4";
        string videoPath = inputDir + videoName;

        cout << "Processing video: " << videoPath << endl;

        VideoCapture cap(videoPath);
        if (!cap.isOpened()) {
            cerr << "Error opening video: " << videoPath << endl;
            continue;
        }

        int frameCount = 0;
        int correctFrames = 0;  // Кадры с правильным количеством объектов
        int totalObjects = 0;   // Всего объектов во всех кадрах
        int expectedObjects = (i <= 6) ? 1 : 0;  // Ожидаемое количество объектов

        Mat frame;
        while (cap.read(frame)) {
            if (frame.empty()) {
                cerr << "End of video or frame reading error" << endl;
                break;
            }

            Mat gray;
            cvtColor(frame, gray, COLOR_BGR2GRAY);
            equalizeHist(gray, gray);

            vector<Rect> objects;
            objectCascade.detectMultiScale(gray, objects, 1.1, 3, 0, Size(30, 30));

            // Проверяем правильность распознавания
            if (objects.size() == expectedObjects) {
                correctFrames++;
            }
            totalObjects += objects.size();

            frameCount++;
        }

        // Выводим статистику для текущего видео
        cout << "----- Video " << i << " Report -----" << endl;
        cout << "Total frames: " << frameCount << endl;
        cout << "Expected objects per frame: " << expectedObjects << endl;
        cout << "Correct frames: " << correctFrames << " ("
            << 100.0 * correctFrames / max(1, frameCount) << "%)" << endl;
        cout << "Incorrect frames: " << (frameCount - correctFrames) << " ("
            << 100.0 * (frameCount - correctFrames) / max(1, frameCount) << "%)" << endl;
        cout << "Average objects per frame: " << (float)totalObjects / max(1, frameCount) << endl;
        cout << "--------------------------------" << endl << endl;

        cap.release();
    }

    destroyAllWindows();
    return 0;
}