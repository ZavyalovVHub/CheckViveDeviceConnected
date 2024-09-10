#include "dialogCheckVR.h"
#include "ui_dialogCheckVR.h"
#include <iostream>
#include <fstream>
#include <string>
#include <QDebug>
#include <QString>

#ifdef _WIN32
    #include <Windows.h>
    #include <SetupAPI.h>
    #include <conio.h>
    #include <combaseapi.h>
    #pragma comment(lib, "SetupAPI.lib")
#endif

#define MAX_DEV_LEN 128

DialogCheckVR::DialogCheckVR(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogCheckVR) {
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this, &DialogCheckVR::push_button_clicked);
}

DialogCheckVR::~DialogCheckVR() {
    delete ui;
}

bool DialogCheckVR::checkVR() {
#ifdef _WIN32
    GUID ClassGuid;

    HDEVINFO info = SetupDiGetClassDevs(&ClassGuid, 0, 0, DIGCF_ALLCLASSES | DIGCF_PRESENT);
    if (info == INVALID_HANDLE_VALUE) {
        qDebug()<<"ERROR не удалось получить список устройств";
        return false;
    }
    SP_DEVINFO_DATA data;
    data.cbSize = sizeof(SP_DEVINFO_DATA);
    BOOL result = TRUE;
    DWORD i = 0;
    while(result) {
        DWORD datatype;
        PBYTE output = new BYTE[MAX_DEV_LEN];
        DWORD RequiredSize;
        result = SetupDiEnumDeviceInfo(info, i, &data);
        if (result) {
            BOOL res = SetupDiGetDeviceRegistryProperty(info, &data, SPDRP_FRIENDLYNAME, &datatype, output, MAX_DEV_LEN, &RequiredSize);
            if (!res) {
                int error = GetLastError();
            } else {
                QString str2 = QString::fromUtf16((char16_t*)output);
                if (str2.contains("vive", Qt::CaseInsensitive)) {
                    return true;
                    delete[] output;
                    break;
                }
            }
        } else {
            qDebug() << "SetupDiEnumDeviceInfo error\n";
            delete[] output;
        }
        ++i;
    }
    return false;
    SetupDiDestroyDeviceInfoList(info);
#endif
}

void DialogCheckVR::push_button_clicked() {
    qApp->quit();
}

