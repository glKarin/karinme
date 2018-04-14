#include <QVariant>
#include <QDir>
#include <QDebug>
#include <QFileInfo>
#include <QFileSystemWatcher>

#include "file.h"
#include "fileinfo.h"

#define KB 1024
#define MB (KB * KB)
#define GB (MB * KB)

_karin_::file::file(QObject *object)
	:QObject(object),
	cpp_showHidden(false),
	watcher(new QFileSystemWatcher(this))
{
	connect(watcher, SIGNAL(directoryChanged(const QString &)), this, SLOT(doDirectoryChanged(const QString &)));
	setPath(QDir::homePath());
}

_karin_::file::~file()
{
	reset();
}

void _karin_::file::reset()
{
	while(!cpp_filelist.isEmpty())
		delete dynamic_cast<_karin_::file_info *>(cpp_filelist.takeAt(0));
	emit filelistChanged();
}

void _karin_::file::init()
{
	reset();
	static const QDir::SortFlags flags = QDir::DirsFirst | QDir::Name | QDir::IgnoreCase;
	static const QDir::Filters qfilters = QDir::Files | QDir::AllDirs | QDir::Drives |  QDir::NoDot;
	QDir::Filters f = qfilters;
	if(cpp_showHidden)
		f |= QDir::Hidden;
	QFileInfoList list = QDir(cpp_path).entryInfoList(cpp_filters, f, flags);
	for(QFileInfoList::const_iterator itor = list.begin();
			itor != list.end();
			++itor)
	{
		if(cpp_path == "/" && itor -> fileName() == "..")
			continue;
		_karin_::file_info *info = new _karin_::file_info;
		info -> setName(itor->fileName());
		info -> setPath(itor->absoluteFilePath());
		info -> setType(itor -> isDir());
		info -> setOwner(itor -> owner());
		info -> setGroup(itor -> group());
		info -> setSize(size2FormatString(itor -> size(), itor -> isDir()));
		info -> setPermission(permissionCode2String(itor -> permissions()));
		cpp_filelist.push_back(dynamic_cast<QObject *>(info));
	}
	emit filelistChanged();
}

QString _karin_::file::size2FormatString(qint64 size, bool isdir)
{
	QString result;
	QString p("%1%2");
	if(isdir)
	{
		if(size <= 4 * KB)
			result = p.arg(size).arg('b');
		else if(size > 4 * KB && size <= 64 * KB)
			result = p.arg(size / KB).arg('k');
	}
	else
	{
        QVariant var(size);
        double d = var.value<double>();
        if(size > 2 * KB && size < 2 * MB){
            result = p.arg(d / KB, 1, 'f', 1).arg('k');
		}
        else if(size >= 2 * MB && size < GB){
            result = p.arg(d / MB, 1, 'f', 1).arg('M');
		}
        else if(size <= 2 * KB){
            result = p.arg(size).arg('b');
        }else{
            result = p.arg(d / GB, 1, 'f', 1).arg('G');
		}
	}
	return result;
}

QString _karin_::file::path() const
{
	return cpp_path;
}

void _karin_::file::setPath(const QString &path)
{
	//QString cleanpath = QDir::cleanPath(path);
	if(cpp_path != path)
	{
		cpp_path = path;
		emit pathChanged();
		QStringList list = watcher -> directories();
		if(list.size() > 0)
			watcher -> removePaths(list);
		watcher -> addPath(cpp_path);
		addPath();
		init();
	}
}

QList<QObject *> _karin_::file::filelist() const
{
	return cpp_filelist;
}

QStringList _karin_::file::filters() const
{
	return cpp_filters;
}

void _karin_::file::setFilters(const QStringList &list)
{
	if(cpp_filters != list)
	{
		cpp_filters = list;
		init();
		emit filtersChanged();
	}
}

QString _karin_::file::permissionCode2String(QFile::Permissions per)
{
	QString result("---------");
	if(per & 0x4000)
		result.replace(0, 1, "r");
	if(per & 0x2000)
		result.replace(1, 1, "w");
	if(per & 0x1000)
		result.replace(2, 1, "x");
	if(per & 0x0040)
		result.replace(3, 1, "r");
	if(per & 0x0020)
		result.replace(4, 1, "w");
	if(per & 0x0010)
		result.replace(5, 1, "x");
	if(per & 0x0004)
		result.replace(6, 1, "r");
	if(per & 0x0002)
		result.replace(7, 1, "w");
	if(per & 0x0001)
		result.replace(8, 1, "x");
	return result;
}

QStringList _karin_::file::dirlist() const
{
	return cpp_dirlist;
}

void _karin_::file::addPath()
{
	for(int i = 0; i < cpp_dirlist.size(); i++){
		if(cpp_dirlist[i] == cpp_path)
		{
			cpp_dirlist.move(i, 0);
			emit dirlistChanged();
			return;
		}
	}
	cpp_dirlist.push_front(cpp_path);
	emit dirlistChanged();
}

bool _karin_::file::showHidden() const
{
	return cpp_showHidden;
}

void _karin_::file::setShowHidden(bool b)
{
	if(cpp_showHidden != b)
	{
		cpp_showHidden = b;
		init();
		emit showHiddenChanged();
	}
}

void _karin_::file::doDirectoryChanged(const QString &path)
{
	if(path == cpp_path)
		init();
}
