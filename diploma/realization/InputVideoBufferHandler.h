#ifndef _INPUT_VIDEO_BUFFER_HANDLER_
#define _INPUT_VIDEO_BUFFER_HANDLER_

#include <list>

#include "FaceDescription.h"

//� �� ������ �����, ��� ������� ����� ��� "��� ������ ���� ���������"? ���������� ���� �� ���� �� ����� ���������� - ����� ������ ���� ����� ��������?
//��� ������� ����� ������ ��������� ��, ��� �� �� ������ ����� ������� ������� ��������?

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
    //� �����������, ��� ��� ���������� ����� ���� �������� � ��� ������ ������������ ��� �����
    //��� � �����, ��� ����������� ������������ � ���� ������� ������ ������ (����� ��������� �� "���-��"), 
    //�� ��������� ��� ��� void-��������� � ������ dynamic_cast � ������� ��� ���� ������
    //��������, � �� ������ ��������� ����� ����, ����� ���� �� ������, ���� �� �� ��� ��� ��������
    InputVideoBufferHandler(void* _inputVideoBuffer, const int _xPictureSize, const int _yPictureSize, const int _scanLine, const ColorDepth _colorDepth);

    //����������� ������ ������������ �����
    InputVideoBufferHandler(const InputVideoBufferHandler& other);
    InputVideoBufferHandler(InputVideoBufferHandler&& other) noexcept;
    ~InputVideoBufferHandler();
    InputVideoBufferHandler& operator=(const InputVideoBufferHandler& other);
    InputVideoBufferHandler& operator=(InputVideoBufferHandler&& other) noexcept;

    //�������, ���������� ����, � ������� ����� �������������� �������� ���� �� �����
    void init();
    //�������, ����������� ���������
    void finish();
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
