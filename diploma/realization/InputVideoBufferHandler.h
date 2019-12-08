#ifndef _INPUT_VIDEO_BUFFER_HANDLER_
#define _INPUT_VIDEO_BUFFER_HANDLER_

#include <list>

//��� ����� ��������������� �����, ������� ����� ������� ������
class OperationStatus;
//������ ���� �� ����������. ������, �� ���������, � �� �����
struct FSDK_FaceTemplate;
//������������ �����, ���������� �����������
class HImage;

//���� �������� ����. 
//��� ����� ������: ������ �� ��� ���� �����, � ������������ �������� ����� ������, ��� �� ���������, �������� ���� � �������?
struct/*class*/ FaceDescription {
    //������ ��������� ������ ���������� � �������� � �������������� ���� �� ���
    struct PictureWithFace {
        //��������� �� ��������
        HImage* image;
        //�����, ��� ��������� ���� - ���������� ����, ������ � ������
        int x;
        int y;
        int width;
        int height;
    };
    //���������, ��� ����� �������, �� ����� ����� �� ��������� ���� � ������� ������ ���� �������� ����� ������
    struct FragmentFrames {
        int start;
        int duration;
    };

    //���� ���������
    FSDK_FaceTemplate faceTemplate;
    PictureWithFace bestPicture;
    //��������� ���� ���� ����� ����������� ����� � ���������� �� ��������� ���� � ������ ����������, ����� ����
    std::list<FragmentFrames> fragments;
};

class InputVideoBufferHandler {
public:
    //���������� FaceSDK ����� ����������� enum ��������� ����, �� � �� ������ ������, ����� �� ������������ � ����� ���� ������ ���
    //��������, ����� ����� ������� ����������� ����������� enum � ������� � ������������ ������ �������� �������� ����������
    //��� ��� ����, ��� �� � ��� �� "������ ������" �����-���� ��� ����������.
    //���������, �� ������ ������, ���� enum �������� ��� ������������ �������-����������� ������ InputVideoBufferHandler, � �������� ��� ����� ������ ������.
    enum class ColorDepth {
        Bit8,
        Bit24,
        Bit32
    };

    //�����������. �����������, ��� ������ ������������� ���� �� ������.
    InputVideoBufferHandler(void* _inputVideoBuffer, const int _xPictureSize, const int _yPictureSize, const int _scanLine, const ColorDepth _colorDepth);

    //����������� ������ ������������ �����
    InputVideoBufferHandler(const InputVideoBufferHandler& other);
    InputVideoBufferHandler(InputVideoBufferHandler&& other) noexcept;
    ~InputVideoBufferHandler();
    InputVideoBufferHandler& operator=(const InputVideoBufferHandler& other);
    InputVideoBufferHandler& operator=(InputVideoBufferHandler&& other) noexcept;

    //�������, ���������� ����, � ������� ����� �������������� �������� ���� �� �����
    void init(OperationStatus& os);
    //�������, ����������� ���������
    void finish(OperationStatus& os);
    //�� �, ��������������, ������� ��� ������ ���������� �����
    std::list<FaceDescription> getFaceDescriptions() const;    

private:
    //������� ������
    void* inputVideoBuffer;
    int xPictureSize;
    int yPictureSize;
    int scanLine;
    ColorDepth colorDepth;
    //� ���� ����� ����������� ��������� ���������
    std::list<FaceDescription> descriptions;
};

#endif // !_INPUT_VIDEO_BUFFER_HANDLER_
