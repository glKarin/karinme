import QtQuick 1.1
import com.nokia.meego 1.1

Rectangle{
	id:root;
	property alias text:textfield.text;
	property alias readOnly:textfield.readOnly;
	property alias textFieldWidth:textfield.width;
	property alias inputing:textfield.activeFocus;
	property alias enabled:search.enabled;
	property alias iconSource:search.iconSource;
    property alias placeholderText: textfield.placeholderText;

	signal clicked;

	width:parent.width;
	height:50;
	radius:10;
	color:"#e2e1e2";
	TextField{
		id:textfield;
		anchors{
			verticalCenter:parent.verticalCenter;
			left:parent.left;
			right:search.left;
			rightMargin:5;
		}
		height:parent.height;
		readOnly:true;
	}
	Button{
		id:search;
		iconSource:"image://theme/icon-m-toolbar-search";
		anchors.verticalCenter:parent.verticalCenter;
		anchors.right:parent.right;
		platformStyle:ButtonStyle{
			buttonHeight:root.height;
			buttonWidth:buttonHeight;
		}
		onClicked:{
			root.clicked();
		}
	}
}

