#include "JsonTool.h"

#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>
#include <QJsonParseError>

QJsonDocument JsonTool::Read(QString fileName)
{
    if(fileName.isNull()||fileName.isEmpty())
    {
        return QJsonDocument();
    }

    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        // 解析 Json
        QJsonParseError error;
        QJsonDocument res = QJsonDocument::fromJson(file.readAll(), &error);
        if (QJsonParseError::NoError == error.error) {
            return res;
        }
    }
    return QJsonDocument();
}
