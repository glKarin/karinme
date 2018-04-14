import QtQuick 1.1
import com.nokia.meego 1.1

CheckBox{
	property variant filter:[];
	property string name:"";
	anchors.verticalCenter:parent.verticalCenter;

	text:name.length === 0 ? "" : "%1 (%2)".arg(name).arg(filter.join(", "));
	checked:file.filters === filter;
	onClicked:{
		file.filters = filter;
	}
}
