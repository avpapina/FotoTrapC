#include <opencv2/opencv.hpp>
#include <iostream>
#include <filesystem>

using namespace cv;
using namespace std;
namespace fs = std::filesystem;

int main()
{
    // Пути к файлам
    string inputDir = "C:/Users/avpap/source/repos/FotoTrap2130/datas/";
    string outputDir = "C:/Users/avpap/source/repos/FotoTrap2130/res/";
    string cascadePath = "C:/Users/avpap/source/repos/FotoTrap2130/datas/haarcascade_frontalcatface_extended.xml";

    // Создаем папку для результатов, если её нет
    fs::create_directory(outputDir);

    // Загружаем каскад Хаара
    CascadeClassifier objectCascade;
    if (!objectCascade.load(cascadePath)) {
        cerr << "Ошибка загрузки каскада: " << cascadePath << endl;
        return -1;
    }

    // Обрабатываем все видео от video1 до video10
    for (int i = 1; i <= 10; ++i) {
        string videoName = "video" + to_string(i) + ".mp4";
        string videoPath = inputDir + videoName;
        string outputPath = outputDir + "result_" + videoName;

        cout << "Обработка видео: " << videoPath << endl;

        // Открываем видео
        VideoCapture cap(videoPath);
        if (!cap.isOpened()) {
            cerr << "Ошибка открытия видео: " << videoPath << endl;
            continue;
        }

        // Получаем параметры видео для создания выходного файла
        int frameWidth = static_cast<int>(cap.get(CAP_PROP_FRAME_WIDTH));
        int frameHeight = static_cast<int>(cap.get(CAP_PROP_FRAME_HEIGHT));
        double fps = cap.get(CAP_PROP_FPS);
        VideoWriter writer(outputPath, VideoWriter::fourcc('m', 'p', '4', 'v'), fps, Size(frameWidth, frameHeight));

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

            // Рисуем прямоугольники вокруг обнаруженных объектов
            for (const auto& rect : objects) {
                rectangle(frame, rect, Scalar(0, 255, 0), 2);
            }

            // Записываем кадр в выходное видео
            writer.write(frame);
        }

        cout << "Обработка завершена. Результат сохранен в: " << outputPath << endl;
        cap.release();
        writer.release();
    }

    return 0;
}