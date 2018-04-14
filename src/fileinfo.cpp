#include "fileinfo.h"

	_karin_::file_info::file_info(QObject *object)
:QObject(object),
	cpp_type(false)
{
}

_karin_::file_info::~file_info()
{
}

void _karin_::file_info::setName(const QString &name)
{
	cpp_name = name;
}

void _karin_::file_info::setPath(const QString &path)
{
	cpp_path = path;
}

void _karin_::file_info::setOwner(const QString &owner)
{
	cpp_owner = owner;
}

void _karin_::file_info::setGroup(const QString &group)
{
	cpp_group = group;
}

void _karin_::file_info::setPermission(const QString &per)
{
	cpp_permission = per;
}

void _karin_::file_info::setType(bool b){
	cpp_type = b;
}

void _karin_::file_info::setSize(const QString &size)
{
	cpp_size = size;
}

QString _karin_::file_info::path() const
{
	return cpp_path;
}

QString _karin_::file_info::name() const
{
	return cpp_name;
}

QString _karin_::file_info::owner() const
{
	return cpp_owner;
}

QString _karin_::file_info::group() const
{
	return cpp_group;
}

QString _karin_::file_info::permission() const
{
	return cpp_permission;
}

QString _karin_::file_info::size() const
{
	return cpp_size;
}

bool _karin_::file_info::type() const
{
	return cpp_type;
}


