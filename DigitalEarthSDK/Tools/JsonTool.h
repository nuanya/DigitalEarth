#ifndef JSONTOOL_H
#define JSONTOOL_H

#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonDocument>

#include "DigitalEarthSDK_global.h"

class DIGITALEARTHSDK_EXPORT JsonTool
{
public:
    static QJsonDocument Read(QString fileName);
};

#endif // JSONTOOL_H
