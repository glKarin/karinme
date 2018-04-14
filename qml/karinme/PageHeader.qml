import QtQuick 1.1
import com.nokia.meego 1.1

Rectangle{
	id:root;
	property alias title:show.text;

	height:80;
	z:1;
	color:"lightskyblue";
	width:parent.width;

	Text{
		id:show;
		anchors.centerIn:parent;
		font.pointSize:24;
		font.family: "Nokia Pure Text";
		z:3;
		color:"seagreen";
		clip:true;
	}

}
