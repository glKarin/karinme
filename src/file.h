#ifndef _ME_FILE_H
#define _ME_FILE_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QList>
#include <QFile>

class QFileSystemWatcher;

namespace _karin_
{
	class file : public QObject
	{
		Q_OBJECT
			Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged FINAL)
			Q_PROPERTY(QList<QObject *> filelist READ filelist NOTIFY filelistChanged FINAL)
			Q_PROPERTY(QStringList filters READ filters WRITE setFilters NOTIFY filtersChanged FINAL)
			Q_PROPERTY(QStringList dirlist READ dirlist NOTIFY dirlistChanged FINAL)
			Q_PROPERTY(bool showHidden READ showHidden WRITE setShowHidden NOTIFY showHiddenChanged)
			//Q_PROPERTY(READ WRITE NOTIFY)

		private:
			QString cpp_path;
			QList<QObject *> cpp_filelist;
			QStringList cpp_filters;
			QStringList cpp_dirlist;
			bool cpp_showHidden;
			QFileSystemWatcher *watcher;

		private:
			void reset();
			void init();
			QString permissionCode2String(QFile::Permissions per);
			QString size2FormatString(qint64 size, bool isdir = false);
			void addPath();
			void setShowHidden(bool b);
			bool showHidden() const;

			private Q_SLOTS:
				void doDirectoryChanged(const QString &);

		public:
			file(QObject *object=0);
			~file();
			QString path() const;
			QList<QObject *> filelist() const;
			void setPath(const QString &path);
			void setFilters(const QStringList &list);
			QStringList filters() const;
			QStringList dirlist() const;

Q_SIGNALS:
			void pathChanged();
			void filelistChanged();
			void filtersChanged();
			void dirlistChanged();
			void showHiddenChanged();
	};
};

#endif
