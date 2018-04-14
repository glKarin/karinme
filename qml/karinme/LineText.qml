import QtQuick 1.1

Item{
	id:root;
	property alias text:title.text;
	property alias pointSize:title.font.pointSize;
	property alias textAnchors:title.anchors;
	property string style:"middle";
	property alias textColor:title.color;

	width:parent.width;
	height:title.height + 10;
	Rectangle{
		anchors{
			left:parent.left;
			right:title.left;
			leftMargin:5;
			rightMargin:5;
			verticalCenter:parent.verticalCenter;
		}
		height:3;
		radius:5;
		smooth:true;
		color:"lightslategrey";
		opacity:0.8;
	}
	Text{
		id:title;
		anchors.verticalCenter:parent.verticalCenter;
		anchors.left:root.style === "left" ? root.left : undefined;
		anchors.leftMargin:13;
		anchors.horizontalCenter:root.style === "middle" ? root.horizontalCenter : undefined;
		z:2;
		font.pointSize:20;
		font.family: "Nokia Pure Text";
		color:"black";
	}
	Rectangle{
		anchors{
			left:title.right;
			right:parent.right;
			leftMargin:5;
			rightMargin:5;
			verticalCenter:parent.verticalCenter;
		}
		width:parent.width;
		height:3;
		radius:5;
		smooth:true;
		opacity:0.8;
		color:"lightslategrey";
	}
}
