#include "DigitalEarth.h"
#include "ui_DigitalEarth.h"

#include "Helpers/ConfigHelper.h"

#include <QMetaEnum>

DigitalEarth::DigitalEarth(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DigitalEarth)
{
    ui->setupUi(this);
    setMinimumSize(1420, 800);
    //去除边界线
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
    //窗口最大化
    setWindowState(Qt::WindowFullScreen);
    setWindowTitle(QString::fromLocal8Bit("数字地球"));
    setStyleSheet("Background-color:#02FFFFFF;");

    helper = new FramelessHelper(this);
    helper->activateOn(this);              //激活当前窗体
    helper->setTitleHeight(30);            //设置窗体的标题栏高度
    helper->setWidgetMovable(true);        //设置窗体可移动
    helper->setWidgetResizable(true);      //设置窗体可缩放

    InitMap();
    ui->mainLayout->addWidget(DigitalEarthSDK::Instance()->LoadEarth(),0,0,2,1);

    pluginLayout = new QHBoxLayout();
    pluginLayout->setContentsMargins(0, 0, 5, 0);
    pluginLayout->setAlignment(Qt::AlignRight);
    ui->mainLayout->setRowMinimumHeight(1, 20);
    ui->mainLayout->addLayout(pluginLayout, 1, 0);
    pluginLayout->addSpacing(10000);

    LoadPlugins();
}

DigitalEarth::~DigitalEarth()
{
    delete ui;
}

void DigitalEarth::InitMap()
{
    ConfigHelper::ReadBaseConfigs();
    QJsonValue res = ConfigHelper::GetBaseConfigByName("MapSource");
    std::vector<MapObject> maps;
    if(!res.isNull()&&!res.isUndefined()&&res.isArray())
    {
        QJsonArray array = res.toArray();
        size_t len = array.size();
        for(size_t index = 0;index<len;index++)
        {
            if(array.at(index).isObject())
            {
                MapObject map;
                QJsonObject obj = array.at(index).toObject();
                map.name = obj["Name"].toString().toStdString();
                map.mapType = map.MapType(obj["MapType"].toString().toStdString());
                map.driverType = map.MapDriverType(obj["Driver"].toString().toStdString());
                map.url = obj["Url"].toString().toStdString();
                map.enabled = obj["Enabled"].toBool();
                map.isVisible = obj["Visibility"].toBool();
                maps.push_back(map);
            }
        }
    }

    DigitalEarthSDK::Instance()->InitMaps(maps);
}

void DigitalEarth::LoadPlugins()
{
    plugins = new QMap<QString, PluginRegister*>;
    QString path = QCoreApplication::applicationDirPath();
    path += "/plugins";
    QDir dir(path);
    if (!dir.exists())
    {
        return;
    }
    dir.setFilter(QDir::Dirs | QDir::Files);
    dir.setSorting(QDir::DirsFirst);//文件夹排在前面
    QFileInfoList list = dir.entryInfoList();
    Q_FOREACH(QFileInfo file, list)
    {
        QString dllPath = file.absoluteFilePath() + "/" + file.fileName() + ".dll";
        QPluginLoader pluginLoader(dllPath);
        QObject* obj = pluginLoader.instance();
        pluginLoader.load();
        PluginRegister* plugin = qobject_cast<PluginRegister*>(obj);
        if (plugin)
        {
            PluginInfos info = plugin->PluginInfo();
            QPushButton* btn = new QPushButton();
            btn->setObjectName(info.Name);
            btn->setMaximumSize(25, 25);
            btn->setMinimumSize(25, 25);
            btn->setToolTip(info.Name);
            btn->setStyleSheet("background-color:#02FFFFFF;");
            btn->setIcon(QIcon(":/DigitalEarth/DigitalEarth_x64/Imags/earth.png"));
            btn->setIconSize(QSize(25, 25));
            connect(btn, &QPushButton::clicked, this, [=]() {on_pluginBtn_clicked(btn->objectName()); });
            pluginLayout->addWidget(btn);
            plugins->insert(info.Name, plugin);

            if (info.IsVisible)
            {
                plugin->ActivePlugin(this);
            }
        }
    }
}

void DigitalEarth::on_pluginBtn_clicked(QString pluginName)
{
    PluginRegister* plugin = plugins->find(pluginName).value();
    if (plugin->PluginInfo().IsVisible)
    {
        plugin->UnActivePlugin();
    }
}

