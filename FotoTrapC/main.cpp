// FotoTrapC.cpp: определяет точку входа для приложения.
//

#include <opencv2/opencv.hpp>
#include <iostream>
#include <chrono>

using namespace cv;
using namespace std;
using namespace std::chrono;

int main()
{
    // Пути к файлам
    string inputDir = "C:/Users/avpap/source/repos/FotoTrapC/FotoTrapC/datas/";
    string cascadePath = "C:/Users/avpap/source/repos/FotoTrapC/FotoTrapC/datas/haarcascade_frontalcatface_extended.xml";

    // Загружаем каскад Хаара
    CascadeClassifier objectCascade;
    if (!objectCascade.load(cascadePath)) {
        cerr << "Ошибка загрузки каскада: " << cascadePath << endl;
        return -1;
    }

    for (int i = 1; i <= 10; ++i) {
        string videoName = "video" + to_string(i) + ".mp4";
        string videoPath = inputDir + videoName;

        cout << "Обработка видео: " << videoPath << endl;

        // Открываем видео
        VideoCapture cap(videoPath);
        if (!cap.isOpened()) {
            cerr << "Ошибка открытия видео: " << videoPath << endl;
            continue;  // Изменили return на continue
        }

        // Переменные для расчёта FPS
        int frameCount = 0;
        auto startTime = high_resolution_clock::now();

        Mat frame;
        while (cap.read(frame)) {
            if (frame.empty()) {
                cerr << "Конец видео или ошибка чтения кадра" << endl;
                break;
            }

            Mat gray;
            cvtColor(frame, gray, COLOR_BGR2GRAY);
            equalizeHist(gray, gray);

            // Детекция объектов
            vector<Rect> objects;
            objectCascade.detectMultiScale(gray, objects, 1.1, 3, 0, Size(30, 30));

            frameCount++;
        }

        auto endTime = high_resolution_clock::now();
        double totalTime = duration_cast<milliseconds>(endTime - startTime).count() / 1000.0;
        double avgFps = (totalTime > 0) ? frameCount / totalTime : 0;

        cout << "The video has been processed. Video path: " << videoPath << endl;
        cout << "====================================" << endl;
        cout << "Total Frames: " << frameCount << endl;
        cout << "Total processing time: " << totalTime << " сек" << endl;
        cout << "Average FPS: " << avgFps << endl;
        cout << "====================================" << endl;

        cap.release();  // Освобождаем ресурсы внутри цикла
    }

    destroyAllWindows();
    return 0;
}