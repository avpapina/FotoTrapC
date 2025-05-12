#include <opencv2/opencv.hpp>
#include <iostream>
#include <filesystem>

using namespace cv;
using namespace std;
namespace fs = std::filesystem;

int main()
{
    // ���� � ������
    string inputDir = "C:/Users/avpap/source/repos/FotoTrap2130/datas/";
    string outputDir = "C:/Users/avpap/source/repos/FotoTrap2130/res/";
    string cascadePath = "C:/Users/avpap/source/repos/FotoTrap2130/datas/haarcascade_frontalcatface_extended.xml";

    // ������� ����� ��� �����������, ���� � ���
    fs::create_directory(outputDir);

    // ��������� ������ �����
    CascadeClassifier objectCascade;
    if (!objectCascade.load(cascadePath)) {
        cerr << "������ �������� �������: " << cascadePath << endl;
        return -1;
    }

    // ������������ ��� ����� �� video1 �� video10
    for (int i = 1; i <= 10; ++i) {
        string videoName = "video" + to_string(i) + ".mp4";
        string videoPath = inputDir + videoName;
        string outputPath = outputDir + "result_" + videoName;

        cout << "��������� �����: " << videoPath << endl;

        // ��������� �����
        VideoCapture cap(videoPath);
        if (!cap.isOpened()) {
            cerr << "������ �������� �����: " << videoPath << endl;
            continue;
        }

        // �������� ��������� ����� ��� �������� ��������� �����
        int frameWidth = static_cast<int>(cap.get(CAP_PROP_FRAME_WIDTH));
        int frameHeight = static_cast<int>(cap.get(CAP_PROP_FRAME_HEIGHT));
        double fps = cap.get(CAP_PROP_FPS);
        VideoWriter writer(outputPath, VideoWriter::fourcc('m', 'p', '4', 'v'), fps, Size(frameWidth, frameHeight));

        Mat frame;
        while (cap.read(frame)) {
            if (frame.empty()) {
                cerr << "����� ����� ��� ������ ������ �����" << endl;
                break;
            }

            Mat gray;
            cvtColor(frame, gray, COLOR_BGR2GRAY);
            equalizeHist(gray, gray);

            // �������� ��������
            vector<Rect> objects;
            objectCascade.detectMultiScale(gray, objects, 1.1, 3, 0, Size(30, 30));

            // ������ �������������� ������ ������������ ��������
            for (const auto& rect : objects) {
                rectangle(frame, rect, Scalar(0, 255, 0), 2);
            }

            // ���������� ���� � �������� �����
            writer.write(frame);
        }

        cout << "��������� ���������. ��������� �������� �: " << outputPath << endl;
        cap.release();
        writer.release();
    }

    return 0;
}