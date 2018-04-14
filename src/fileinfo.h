#ifndef _ME_FILEINFO_H
#define _ME_FILEINFO_H

#include <QObject>
#include <QString>

namespace _karin_
{
	class file_info : public QObject
	{
		Q_OBJECT
			Q_PROPERTY(QString path READ path CONSTANT FINAL)
			Q_PROPERTY(QString owner READ owner CONSTANT FINAL)
			Q_PROPERTY(QString group READ group CONSTANT FINAL)
			Q_PROPERTY(QString size READ size CONSTANT FINAL)
			Q_PROPERTY(QString permission READ permission CONSTANT FINAL)
			Q_PROPERTY(bool type READ type CONSTANT FINAL)
			Q_PROPERTY(QString name READ name CONSTANT FINAL)

		private:
		QString cpp_path;
		QString cpp_name;
		QString cpp_owner;
		QString cpp_group;
		QString cpp_permission;
		QString cpp_size;
		bool cpp_type;

		public:
		file_info(QObject *object = 0);
		virtual ~file_info();
		void setName(const QString &name);
		void setPath(const QString &path);
		void setOwner(const QString &owner);
		void setGroup(const QString &group);
		void setPermission(const QString &per);
		void setType(bool b);
		void setSize(const QString &size);

		QString path() const;
		QString name() const;
		QString owner() const;
		QString group() const;
		QString permission() const;
		QString size() const;
		bool type() const;

	};
};
#endif
