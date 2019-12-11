#include "FaceDescription.h"

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
    virtual IFaceFinder(const IFaceFinder& other) = default;
    virtual IFaceFinder(IFaceFinder&& other) noexcept = default;
    virtual ~IFaceFinder() = default;
    virtual IFaceFinder& operator=(const IFaceFinder& other) = 0;
    virtual IFaceFinder& operator=(IFaceFinder&& other) noexcept = 0;

    //������ ������� ������� ��������� ������, ���������������� �� ������� ������������ ������
    static IFaceFinder* createFaceFinder();

    //������ ����� ���� �� ������
    //�������������� ������ ��������� �����
    virtual void init() = 0;
    //��������� �������� - ����� ������, ������, scanLine � ������� �����
    //��� ������� ������ ���������� � �����
    virtual void addImage(void* _inputVideoBuffer, const int _xPictureSize, const int _yPictureSize, const int _scanLine, const ColorDepth _colorDepth) = 0;
    //����������� ��������� ������
    virtual void finish() = 0;

    //�������� ���������
    //���������� ���, ��������� � ���� ���������
    virtual int faceCount() const = 0;
    //�������� ���� �� ����������� ������
    virtual FaceDescription* getFaceInfo(int index) const = 0;
    //�������� ��� ����
    virtual std::list<FaceDescription*> getFaceDescriptions() const = 0;

protected:
    //����� ����������� ������ ���� ������� �����, �������� ��� � ���� protected
    virtual IFaceFinder() = default;

}
