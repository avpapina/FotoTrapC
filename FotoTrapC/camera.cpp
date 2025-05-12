#include <opencv2/opencv.hpp>
#include <iostream>
#include <chrono>

using namespace cv;
using namespace std;
using namespace std::chrono;

int main()
{
    // Пути к файлам
    string inputDir = "C:/Users/avpap/source/repos/FotoTrap2130/datas/";
    string cascadePath = "C:/Users/avpap/source/repos/FotoTrap2130/datas/haarcascade_frontalcatface_extended.xml";

    // Загружаем каскад Хаара
    CascadeClassifier objectCascade;
    if (!objectCascade.load(cascadePath)) {
        cerr << "Error loading cascade file: " << cascadePath << endl;
        return -1;
    }

    // Открываем видеопоток с камеры
    VideoCapture cap(0);
    if (!cap.isOpened()) {
        cerr << "Error opening camera" << endl;
        return -1;
    }

    // Переменные для расчёта FPS
    int frameCount = 0;
    int totalFrames = 0;
    auto lastFpsTime = high_resolution_clock::now();
    auto startTime = lastFpsTime;
    double totalProcessingTime = 0.0;

    // Интервал вывода FPS (секунды)
    const double fpsUpdateInterval = 2.0;

    Mat frame;
    while (true) {
        auto frameStartTime = high_resolution_clock::now();

        cap >> frame;
        if (frame.empty()) {
            cerr << "Error reading frame" << endl;
            break;
        }

        // Обработка кадра
        Mat gray;
        cvtColor(frame, gray, COLOR_BGR2GRAY);
        equalizeHist(gray, gray);

        // Детекция объектов
        vector<Rect> objects;
        objectCascade.detectMultiScale(gray, objects, 1.1, 3, 0, Size(30, 30));

        // Отрисовка прямоугольников вокруг обнаруженных объектов
        for (const auto& obj : objects) {
            rectangle(frame, obj, Scalar(0, 255, 0), 2);
        }

        // Подсчёт FPS
        frameCount++;
        totalFrames++;
        auto currentTime = high_resolution_clock::now();
        double elapsedTime = duration_cast<duration<double>>(currentTime - lastFpsTime).count();
        double frameTime = duration_cast<duration<double>>(currentTime - frameStartTime).count();
        totalProcessingTime += frameTime;

        // Вывод FPS каждые fpsUpdateInterval секунд
        if (elapsedTime >= fpsUpdateInterval) {
            double fps = frameCount / elapsedTime;
            cout << "Current FPS: " << fps << endl;

            // Сброс счётчика
            frameCount = 0;
            lastFpsTime = currentTime;
        }

        // Отображение кадра
        imshow("Camera Feed", frame);

        // Выход по нажатию ESC
        if (waitKey(1) == 27) break;
    }

    // Вывод общей статистики
    auto endTime = high_resolution_clock::now();
    double totalTime = duration_cast<duration<double>>(endTime - startTime).count();
    double avgFps = totalFrames / totalTime;
    double avgProcessingFps = totalFrames / totalProcessingTime;

    cout << "\n=== Final Statistics ===" << endl;
    cout << "Total processing time: " << totalTime << " seconds" << endl;
    cout << "Total frames processed: " << totalFrames << endl;
    cout << "Average FPS (display): " << avgFps << endl;
    cout << "Average FPS (processing): " << avgProcessingFps << endl;

    cap.release();
    destroyAllWindows();
    return 0;
}