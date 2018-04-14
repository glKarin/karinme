#include <QApplication>
#include <QDeclarativeEngine>
#include <QDeclarativeComponent>
#include "qmlapplicationviewer.h"
#include <QLocale>
#include <QTranslator>
#include <QTextCodec>
#include <QDir>
#include "QDebug"
#include "me.h"
#include "file.h"
#include "fileinfo.h"

#define APPLICATION_NAME "KarinME"
#define APPLICATION_VERSION "0.3.1harmattan5+3.0.0snapshot.114"
#define APPLICATION_DEVELOPER "Karin"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
	if(argc > 1)
	{
		_karin_::me_booter booter;
        booter.boot(QDir::cleanPath(argv[1]));
		return 0;
	}

	QApplication *a = createApplication(argc, argv);
	a->setApplicationName(APPLICATION_NAME);
	a->setOrganizationName(APPLICATION_DEVELOPER);
	a->setApplicationVersion(APPLICATION_VERSION);
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

	QTranslator translator;
#ifdef _DEBUG
    if(translator.load(QString("karinme.zh_CN.qm"),"i18n/"))
	{
		qDebug()<<"Load i18n karinme.zh_CN.qm\"";
#else
	QString locale = QLocale::system().name();

    if(translator.load(QString("karinme.") + locale,"/opt/karinme/i18n/"))
	{
		qDebug()<<"Load i18n karinme."<<locale<<".qm\"";
#endif
		a->installTranslator(&translator);
	}

	QScopedPointer<QApplication> app(a);

	qmlRegisterType<_karin_::me_booter>("karin.microemulator", 1, 0, "MEBooter");
	qmlRegisterType<_karin_::file>("karin.file", 2, 0, "File");
	qmlRegisterType<_karin_::file_info>("karin.file", 2, 0, "FileInfo");

	QmlApplicationViewer viewer;
	viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);

    viewer.setMainQmlFile(QLatin1String("qml/karinme/main.qml"));
    viewer.showExpanded();

	return app->exec();
}
