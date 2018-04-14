#ifndef _ME_BOOTER_H
#define _ME_BOOTER_H

#include <QObject>
#include <QString>
#include <QMap>
#include <QVariant>

class QProcess;
class QSettings;

namespace _karin_
{
	class me_booter : public QObject
	{
		Q_OBJECT
			Q_PROPERTY(QString javaPath READ javaPath WRITE setJavaPath NOTIFY javaPathChanged FINAL)
			//pt/jdk1.7.0_60/jre/bin/java -cp /opt/micr //oemulator/microemulator.jar:/opt/microemulator/ //lib/microemu-nokiaui.jar:/opt/microemulator/lib ///microemu-siemensapi.jar:/opt/microemulator/lib ///microemu-jsr-120.jar:/opt/microemulator/lib/mi //croemu-jsr-135.jar:/opt/microemulator/lib/micro //emu-jsr-75.jar:/opt/microemulator/lib/microemu- //jsr-82.jar org.microemu.app.Main
			Q_PROPERTY(bool running READ running NOTIFY runningChanged FINAL)
			Q_PROPERTY(bool jsr120Enabled READ jsr120Enabled WRITE setJsr120Enabled NOTIFY jsr120EnabledChanged FINAL)
			Q_PROPERTY(bool jsr135Enabled READ jsr135Enabled WRITE setJsr135Enabled NOTIFY jsr135EnabledChanged FINAL)
			Q_PROPERTY(bool jsr75Enabled READ jsr75Enabled WRITE setJsr75Enabled NOTIFY jsr75EnabledChanged FINAL)
			Q_PROPERTY(bool jsr82Enabled READ jsr82Enabled WRITE setJsr82Enabled NOTIFY jsr82EnabledChanged FINAL)
			Q_PROPERTY(bool nokiauiApiEnabled READ nokiauiApiEnabled WRITE setNokiauiApiEnabled NOTIFY nokiauiApiEnabledChanged FINAL)
			Q_PROPERTY(bool siemensApiEnabled READ siemensApiEnabled WRITE setSiemensApiEnabled NOTIFY siemensApiEnabledChanged FINAL)
			Q_PROPERTY(int skin READ skin WRITE setSkin NOTIFY skinChanged FINAL)
			Q_PROPERTY(QString userSkin READ userSkin WRITE setUserSkin NOTIFY userSkinChanged FINAL)
			Q_PROPERTY(QString userSkinXml READ userSkinXml WRITE setUserSkinXml NOTIFY userSkinXmlChanged FINAL)
			Q_PROPERTY(bool fullscreen READ fullscreen WRITE setFullscreen NOTIFY fullscreenChanged FINAL)
			Q_PROPERTY(bool output READ output WRITE setOutput NOTIFY outputChanged FINAL)

		public:
			//constructor n destructor
			me_booter(QObject *parent = 0);
			virtual ~me_booter();

			//read property
			QString javaPath() const;
			bool jsr120Enabled() const;
			bool jsr135Enabled() const;
			bool jsr75Enabled() const;
			bool jsr82Enabled() const;
			bool nokiauiApiEnabled() const;
			bool siemensApiEnabled() const;
			bool running() const;
			int skin() const;
			QString userSkin() const;
			QString userSkinXml() const;
			bool fullscreen() const;
			bool output() const;

			//write property
			void setJavaPath(const QString &path);
			void setJsr120Enabled(bool b);
			void setJsr75Enabled(bool b);
			void setJsr135Enabled(bool b);
			void setJsr82Enabled(bool b);
			void setNokiauiApiEnabled(bool b);
			void setSiemensApiEnabled(bool b);
			void setSkin(int type);
			void setUserSkin(const QString &skin);
			void setUserSkinXml(const QString &skin);
			void setFullscreen(bool b);
			void setOutput(bool b);

			void boot(const QString &file);

			//notify property
Q_SIGNALS:
			void javaPathChanged();
			void jsr75EnabledChanged();
			void jsr120EnabledChanged();
			void jsr135EnabledChanged();
			void jsr82EnabledChanged();
			void nokiauiApiEnabledChanged();
			void siemensApiEnabledChanged();
			void runningChanged();
			void skinChanged();
			void userSkinChanged();
			void userSkinXmlChanged();
			void fullscreenChanged();
			void outputChanged();

		public:
			//invokable function
			Q_INVOKABLE void externalBoot(const QString &file = QString());
			Q_INVOKABLE void internalBoot(const QString &file = QString());
			Q_INVOKABLE void kill();
			Q_INVOKABLE void setDefaultJre();

Q_SIGNALS:
			//extras signals
			void output(int type, const QString &text); //type = 0 -> cmd, = 1 stdout, = 2 stderr

		private:
			//private function
			void readSettings();
			QStringList makeCommands(const QString &file) const;

			private Q_SLOTS:
				//private slots
				void readStdout();
			void readStderr();
			void setRunning();
			void setNotRunning(int code);

		private:
			//member
			QProcess *process;
			QSettings *settings;
			bool cpp_running;

			QString cpp_javaPath;
			bool cpp_jsr75Enabled;
			bool cpp_jsr82Enabled;
			bool cpp_jsr135Enabled;
			bool cpp_jsr120Enabled;
			bool cpp_nokiauiApiEnabled;
			bool cpp_siemensApiEnabled;
			bool cpp_fullscreen;
			bool cpp_output;
			int cpp_skin; //0 ME Setting 1 mid 2 large 3 resize 4 s60v3 5 s60v5 6 user
			QString cpp_userSkin;
			QString cpp_userSkinXml;
			QMap<QString, QVariant> settingsMap;
	};
};

#endif
