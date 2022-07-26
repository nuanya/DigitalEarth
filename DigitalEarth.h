#ifndef DIGITALEARTH_H
#define DIGITALEARTH_H

#include <QDesktopWidget>
#include <QDir>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QPluginLoader>
#include <QPushButton>

#include "DigitalEarthSDK/PluginRegister.h"
#include "DigitalEarthSDK/DigitalEarthSDK.h"
#include "FramelessHelper.h"

QT_BEGIN_NAMESPACE
namespace Ui { class DigitalEarth; }
QT_END_NAMESPACE

class DigitalEarth : public QMainWindow
{
    Q_OBJECT

public:
    DigitalEarth(QWidget *parent = nullptr);
    ~DigitalEarth();

private:
    /**
     * @brief InitMap 初始化地图
     */
    void InitMap();
    /**
     * @brief LoadPlugins 加载插件
     */
    void LoadPlugins();

private slots:
    /**
     * @brief on_pluginBtn_clicked 插件激活/关闭
     * @param pluginName 插件名称
     */
    void on_pluginBtn_clicked(QString pluginName);

private:
    Ui::DigitalEarth *ui;

    FramelessHelper* helper = 0;

    QHBoxLayout* pluginLayout = 0;

    QMap<QString, PluginRegister*>* plugins = 0;
};
#endif // DIGITALEARTH_H
