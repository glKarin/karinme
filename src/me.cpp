#include <QProcess>
#include <QSettings>
#include <QStringList>
#include <QApplication>
#include <QDebug>

#include "me.h"

#ifdef _DEBUG
#include <QDir>
static const QString defaultJavaPath = QDir::currentPath() + "/jre/bin/java";
static const QString mePath = QDir::currentPath() + "/microemulator/";
static const QString shellPath = QDir::currentPath() + "/script/";
static const QString skinPath = QDir::currentPath() + "/skin/";
#else
static const QString defaultJavaPath = "/opt/karinme/jre/bin/java";
static const QString mePath = "/opt/karinme/microemulator/";
static const QString shellPath = "/opt/karinme/script/";
static const QString skinPath = "/opt/karinme/skin/";
#endif

_karin_::me_booter::me_booter(QObject *parent)
	: QObject(parent),
	process(new QProcess(this)),
	settings(new QSettings(this)),
	cpp_running(false)
{
	settingsMap.insert("java_path", QVariant(defaultJavaPath));
	settingsMap.insert("jsr75", QVariant(true));
	settingsMap.insert("jsr82", QVariant(true));
	settingsMap.insert("jsr120", QVariant(true));
	settingsMap.insert("jsr135", QVariant(true));
	settingsMap.insert("nokiaui", QVariant(true));
	settingsMap.insert("siemens", QVariant(true));
	settingsMap.insert("skin", QVariant(4));
	settingsMap.insert("user_skin", QVariant(""));
	settingsMap.insert("user_skin_xml", QVariant(""));
	settingsMap.insert("fullscreen", QVariant(false));
	settingsMap.insert("output", QVariant(true));
	readSettings();
	connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(readStdout()));
	connect(process, SIGNAL(readyReadStandardError()), this, SLOT(readStderr()));
	connect(process, SIGNAL(started()), this, SLOT(setRunning()));
	connect(process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(setNotRunning(int)));
}

_karin_::me_booter::~me_booter()
{
	if(process -> state() != QProcess::NotRunning)
		kill();
}

QString _karin_::me_booter::javaPath() const
{
	return cpp_javaPath;
}

bool _karin_::me_booter::jsr75Enabled() const
{
	return cpp_jsr75Enabled;
}

bool _karin_::me_booter::jsr120Enabled() const
{
	return cpp_jsr120Enabled;
}

bool _karin_::me_booter::jsr135Enabled() const
{
	return cpp_jsr135Enabled;
}

bool _karin_::me_booter::jsr82Enabled() const
{
	return cpp_jsr82Enabled;
}

bool _karin_::me_booter::nokiauiApiEnabled() const
{
	return cpp_nokiauiApiEnabled;
}

bool _karin_::me_booter::siemensApiEnabled() const
{
	return cpp_siemensApiEnabled;
}

bool _karin_::me_booter::running() const
{
	return cpp_running;
}

bool _karin_::me_booter::fullscreen() const
{
	return cpp_fullscreen;
}

bool _karin_::me_booter::output() const
{
	return cpp_output;
}

void _karin_::me_booter::setJavaPath(const QString &var)
{
	if(cpp_javaPath != var)
	{
		cpp_javaPath = var;
		settings -> setValue("java_path", QVariant(cpp_javaPath));
		emit javaPathChanged();
	}
}

void _karin_::me_booter::setJsr120Enabled(bool b)
{
	if(cpp_jsr120Enabled != b)
	{
		cpp_jsr120Enabled = b;
		settings -> setValue("jsr120", QVariant(cpp_jsr120Enabled));
		emit jsr120EnabledChanged();
	}
}

void _karin_::me_booter::setJsr75Enabled(bool b)
{
	if(cpp_jsr75Enabled != b)
	{
		cpp_jsr75Enabled = b;
		settings -> setValue("jsr75", QVariant(cpp_jsr75Enabled));
		emit jsr75EnabledChanged();
	}
}

void _karin_::me_booter::setJsr135Enabled(bool b)
{
	if(cpp_jsr135Enabled != b)
	{
		cpp_jsr135Enabled = b;
		settings -> setValue("jsr135", QVariant(cpp_jsr135Enabled));
		emit jsr135EnabledChanged();
	}
}

void _karin_::me_booter::setJsr82Enabled(bool b)
{
	if(cpp_jsr82Enabled != b)
	{
		cpp_jsr82Enabled = b;
		settings -> setValue("jsr82", QVariant(cpp_jsr82Enabled));
		emit jsr82EnabledChanged();
	}
}

void _karin_::me_booter::setNokiauiApiEnabled(bool b)
{
	if(cpp_nokiauiApiEnabled != b)
	{
		cpp_nokiauiApiEnabled = b;
		settings -> setValue("nokiaui", QVariant(cpp_nokiauiApiEnabled));
		emit nokiauiApiEnabledChanged();
	}
}

void _karin_::me_booter::setSiemensApiEnabled(bool b)
{
	if(cpp_siemensApiEnabled != b)
	{
		cpp_siemensApiEnabled = b;
		settings -> setValue("siemens", QVariant(cpp_siemensApiEnabled));
		emit siemensApiEnabledChanged();
	}
}

void _karin_::me_booter::setFullscreen(bool b)
{
	if(cpp_fullscreen != b)
	{
		cpp_fullscreen = b;
		settings -> setValue("fullscreen", QVariant(cpp_fullscreen));
		emit fullscreenChanged();
	}
}

void _karin_::me_booter::setOutput(bool b)
{
	if(cpp_output != b)
	{
		cpp_output = b;
		settings -> setValue("output", QVariant(cpp_output));
		emit outputChanged();
	}
}

QStringList _karin_::me_booter::makeCommands(const QString &file) const
{
	QStringList args, libs;
	libs<<mePath + "microemulator.jar";
	//libs<<mePath + "midpapi20.jar"
		//<<mePath + "cldcapi11.jar";
	if(cpp_jsr75Enabled)
		libs.push_back(mePath + "lib/microemu-jsr-75.jar");
	if(cpp_jsr82Enabled)
		libs.push_back(mePath + "lib/microemu-jsr-82.jar");
	if(cpp_jsr120Enabled)
		libs.push_back(mePath + "lib/microemu-jsr-120.jar");
	if(cpp_jsr135Enabled)
		libs.push_back(mePath + "lib/microemu-jsr-135.jar");
	if(cpp_nokiauiApiEnabled)
		libs.push_back(mePath + "lib/microemu-nokiaui.jar");
	if(cpp_siemensApiEnabled)
		libs.push_back(mePath + "lib/microemu-siemensapi.jar");
	switch(cpp_skin)
	{
		case 1:
			//libs.push_back(mePath + "devices/microemu-device-large.jar");
			break;
		case 2:
			//libs.push_back(mePath + "devices/microemu-device-resizable.jar");
			break;
		case 3:
			//libs.push_back(mePath + "devices/microemu-device-minimum.jar");
			break;
		case 4:
			libs.push_back(skinPath + "microemu-n900-240x320.jar");
			break;
		case 5:
			libs.push_back(skinPath + "microemu-n900-640x360.jar");
			break;
		case 6:
			libs.push_back(cpp_userSkin);
			break;
		default:
			break;
	}
	args<<"-cp"
		<<libs.join(":")
		<<"org.microemu.app.Main";
	switch(cpp_skin)
	{
		case 1:
		//	args<<"--device"
			//	<<"org/microemu/device/minimum/device.xml";
			break;
		case 2:
			//args<<"--device"
			//	<<"org/microemu/device/large/device.xml";
			break;
		case 3:
			//args<<"--device"
			//	<<"org/microemu/device/resizable/device-ru.xml";
			break;
		case 4:
			args<<"--device"
				<<"org/microemu/devices/custom/SymbianS60_3rd_240x320/device.xml";
			break;
		case 5:
			args<<"--device"
				<<"org/microemu/devices/custom/SymbianS60_5th_552x385/device.xml";
			break;
		case 6: 
			args<<"--device"
				<<cpp_userSkinXml;
			break;
		default:
			break;
	}
	if(!file.isEmpty())
		args<<file;
	return args;
}

void _karin_::me_booter::internalBoot(const QString &file)
{
	if(process -> state() != QProcess::NotRunning)
		return;
	QStringList args = makeCommands(file);
	if(cpp_fullscreen)
	{
		QProcess::startDetached(shellPath + "wmctrl_scan_window.sh", QStringList("MicroEmulator"));/*<<"&"*/;
		qDebug()<<shellPath + "wmctrl_scan_window.sh MicroEmulator";
	}
	process -> start(cpp_javaPath, args);
	qDebug()<<cpp_javaPath + " " + args.join(" ");
	emit output(0, tr("Command") + " -> " + cpp_javaPath + " " + args.join(" ") + "\n");
}

void _karin_::me_booter::externalBoot(const QString &file)
{
	QStringList args = makeCommands(file);
	if(cpp_fullscreen)
	{
		QProcess::startDetached(shellPath + "wmctrl_scan_window.sh", QStringList("MicroEmulator"));/*<<"&"*/;
		qDebug()<<shellPath + "wmctrl_scan_window.sh MicroEmulator";
	}
	args.push_front(cpp_javaPath);
	qDebug()<<shellPath + "microemulator_sequential.sh " + args.join(" ");
	QProcess::startDetached(shellPath + "microemulator_sequential.sh", args);
	qApp -> quit();
}

void _karin_::me_booter::kill()
{
	if(process -> state() != QProcess::NotRunning)
	{
		process -> kill();
	}
}

void _karin_::me_booter::readStdout()
{
	if(cpp_output)
	{
		process -> setReadChannel(QProcess::StandardOutput);
		emit output(1, process -> readAllStandardOutput());
	}
}

void _karin_::me_booter::readStderr()
{
	if(cpp_output)
	{
		process -> setReadChannel(QProcess::StandardError);
		emit output(2, process -> readAllStandardError());
	}
}

void _karin_::me_booter::setRunning()
{
	cpp_running = true;
	emit runningChanged();
}

void _karin_::me_booter::setNotRunning(int code)
{
	cpp_running = false;
	emit runningChanged();
	emit output(0, tr("Command exit. Exit code -> ") + QString::number(code));
}

void _karin_::me_booter::readSettings()
{
	if(settings -> contains("java_path"))
	{
		cpp_javaPath = settings -> value("java_path").toString();
		emit javaPathChanged();
	}
	else
	{
		setJavaPath(settingsMap["java_path"].toString());
	}
	if(settings -> contains("jsr75"))
	{
		cpp_jsr75Enabled = settings -> value("jsr75").toBool();
		emit jsr75EnabledChanged();
	}
	else
	{
		setJsr75Enabled(settingsMap["jsr75"].toBool());
	}
	if(settings -> contains("jsr82"))
	{
		cpp_jsr82Enabled = settings -> value("jsr82").toBool();
		emit jsr82EnabledChanged();
	}
	else
	{
		setJsr82Enabled(settingsMap["jsr82"].toBool());
	}
	if(settings -> contains("jsr120"))
	{
		cpp_jsr120Enabled = settings -> value("jsr120").toBool();
		emit jsr120EnabledChanged();
	}
	else
	{
		setJsr120Enabled(settingsMap["jsr120"].toBool());
	}
	if(settings -> contains("jsr135"))
	{
		cpp_jsr135Enabled = settings -> value("jsr135").toBool();
		emit jsr135EnabledChanged();
	}
	else
	{
		setJsr135Enabled(settingsMap["jsr135"].toBool());
	}
	if(settings -> contains("nokiaui"))
	{
		cpp_nokiauiApiEnabled = settings -> value("nokiaui").toBool();
		emit nokiauiApiEnabledChanged();
	}
	else
	{
		setNokiauiApiEnabled(settingsMap["nokiaui"].toBool());
	}
	if(settings -> contains("siemens"))
	{
		cpp_siemensApiEnabled = settings -> value("siemens").toBool();
		emit siemensApiEnabledChanged();
	}
	else
	{
		setSiemensApiEnabled(settingsMap["siemens"].toBool());
	}
	if(settings -> contains("skin"))
	{
		cpp_skin = settings -> value("skin").toInt();
		emit skinChanged();
	}
	else
	{
		setSkin(settingsMap["skin"].toInt());
	}
	if(settings -> contains("user_skin"))
	{
		cpp_userSkin = settings -> value("user_skin").toString();
		emit userSkinChanged();
	}
	else
	{
		setUserSkin(settingsMap["user_skin"].toString());
	}
	if(settings -> contains("user_skin_xml"))
	{
		cpp_userSkinXml = settings -> value("user_skin_xml").toString();
		emit userSkinXmlChanged();
	}
	else
	{
		setUserSkinXml(settingsMap["user_skin_xml"].toString());
	}
	if(settings -> contains("fullscreen"))
	{
		cpp_fullscreen = settings -> value("fullscreen").toBool();
		emit fullscreenChanged();
	}
	else
	{
		setFullscreen(settingsMap["fullscreen"].toBool());
	}
	if(settings -> contains("output"))
	{
		cpp_output = settings -> value("output").toBool();
		emit outputChanged();
	}
	else
	{
		setOutput(settingsMap["output"].toBool());
	}
}

void _karin_::me_booter::setDefaultJre()
{
	setJavaPath(defaultJavaPath);
}

int _karin_::me_booter::skin() const
{
	return cpp_skin;
}

QString _karin_::me_booter::userSkin() const
{
	return cpp_userSkin;
}

QString _karin_::me_booter::userSkinXml() const
{
	return cpp_userSkinXml;
}

void _karin_::me_booter::setSkin(int type)
{
	if(cpp_skin != type)
	{
		cpp_skin = type;
		settings -> setValue("skin", cpp_skin);
		emit skinChanged();
	}
}

void _karin_::me_booter::setUserSkin(const QString &skin)
{
	if(cpp_userSkin != skin)
	{
		cpp_userSkin = skin;
		settings -> setValue("user_skin", cpp_userSkin);
		emit userSkinChanged();
	}
}

void _karin_::me_booter::setUserSkinXml(const QString &skin)
{
	if(cpp_userSkinXml != skin)
	{
		cpp_userSkinXml = skin;
		settings -> setValue("user_skin_xml", cpp_userSkinXml);
		emit userSkinXmlChanged();
	}
}

void _karin_::me_booter::boot(const QString &file)
{
	QStringList args = makeCommands(file);
	if(cpp_fullscreen)
	{
		QProcess::startDetached(shellPath + "wmctrl_scan_window.sh", QStringList("MicroEmulator"));/*<<"&"*/;
		qDebug()<<shellPath + "wmctrl_scan_window.sh MicroEmulator";
	}
    qDebug()<<defaultJavaPath + " " + args.join(" ");
    QProcess::startDetached(defaultJavaPath, args);
}

