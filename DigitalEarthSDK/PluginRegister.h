#pragma once

#ifndef PLUGINREGISTER_H
#define PLUGINREGISTER_H
#include <QObject>
#include <QtPlugin>
#include <QString>
#include <QWidget>

struct PluginInfos
{
	QString Name;
	QString IconPath;
	bool IsVisible;
};

class PluginRegister
{
public:
	virtual ~PluginRegister() {}
	virtual PluginInfos PluginInfo() = 0;
	virtual void ActivePlugin(QWidget*) = 0;
	virtual void UnActivePlugin() = 0;
};
Q_DECLARE_INTERFACE(PluginRegister, "org.galaxyworld.plugins.PluginRegister/1.0")
#endif // !PLUGINREGISTER_H