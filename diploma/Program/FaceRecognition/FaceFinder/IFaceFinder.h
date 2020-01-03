#pragma once

#include "FaceDescription.h"
#include "FrameRegion.h"

//������� ���������, ������� ����� ������� ��� ������-����������� �����
class IFaceFinder {
public:
    //���������� FaceSDK ����� ����������� enum ��������� ����, �� � �� ������ ������, ����� �� ������������ � ����� ���� ������ ���
    //��������, ����� ����� ������� ����������� ����������� enum � ������� � ������������ ������ �������� �������� ����������
    //��� ��� ����, ��� �� � ��� �� "������ ������" �����-���� ��� ����������.
    //���������, �� ������ ������, ���� enum �������� ��� ������������ �������-����������� ������ FaceFinder, � �������� ��� ����� ������ ������.
    enum class ColorDepth {
        Bit8,
        Bit24,
        Bit32
    };

    //����� ���� - ������ ������������ �����
    IFaceFinder(const IFaceFinder& other) = default;
    IFaceFinder(IFaceFinder&& other) noexcept = default;
    virtual ~IFaceFinder() = default;
    IFaceFinder& operator=(const IFaceFinder& other) = default;
    IFaceFinder& operator=(IFaceFinder&& other) noexcept = default;

    //������ ������� ������� ��������� ������, ���������������� �� ������� ������������ ������
    static IFaceFinder* createFaceFinder();

    //������ ����� ���� �� ������
    //�������������� ������ ��������� �����
    virtual void init() = 0;
    //��������� �������� - ����� ������, ������, scanLine � ������� �����
    //��� ������� ������ ���������� � �����
    virtual void addImage(const int frameNumber, void* _inputVideoBuffer, const int _xPictureSize, const int _yPictureSize, const int _scanLine, const ColorDepth _colorDepth) = 0;
    //����������� ��������� ������
    virtual void finish() = 0;

    //�������� ���������
    //���������� ���, ��������� � ���� ���������
    virtual int faceCount() const = 0;
    //�������� ���� �� ����������� ������
    virtual FaceDescription* getFaceInfo(int index) const = 0;
    //������� ���������� ��������, � ������� ����������� ��� ����
    virtual int frameRegionsNum(int index) const = 0;
    //�������� ������, ��� ����������� ��� ����. ���� �������� ���������, �� ��-��������� ������� ������
    virtual FrameRegion* getFaceRegionByIndex(int index, int frameNum = 0) const = 0;

//protected:
    //����� ����������� ������ ���� ������� �����, �������� ��� � ���� protected
    IFaceFinder() = default;

};
