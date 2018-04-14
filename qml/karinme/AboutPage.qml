import QtQuick 1.1
import com.nokia.meego 1.1

MEPage{
	id:root;
	title:"<b>" + qsTr("More") + "</b>";

	Flickable{
		anchors.fill:parent;
		anchors.topMargin:headheight;
		contentWidth:width;
		contentHeight:layout.height;
		clip:true;
		Column{
			id:layout;
			width:parent.width;
			SelectionHeader{
				text:qsTr("Tips");
				item:tipsitem;
			}
			SelectionBody{
				id:tipsitem;
				theight:childrenRect.height;
				Column {
					width:parent.width;
					visible:parent.fullShow;
					Text{
						font.pointSize: 20
						font.family: "Nokia Pure Text";
						width:parent.width;
						color:"black";
						text: qsTr("MicroEmulator version is 3.0.0-SNAPSHOT.114.");
						wrapMode:Text.WordWrap;
					}
					Text{
						font.pointSize: 20
						font.family: "Nokia Pure Text";
						width:parent.width;
						color:"black";
						text: qsTr("Internal JRE version is 1.7.0_update_60, arm soft-float Oracle version. But you can use other JRE in you system.");
						wrapMode:Text.WordWrap;
					}
					Text{
						font.pointSize: 20
						font.family: "Nokia Pure Text";
						width:parent.width;
						color:"black";
                        text: qsTr("If you have installed wmctrl, you can run with fullscreen.(REMOVED. MicroEmulator has run with fullscreen now.)");
						wrapMode:Text.WordWrap;
					}
					Text{
						font.pointSize: 20
						font.family: "Nokia Pure Text";
						width:parent.width;
						color:"black";
						text: qsTr("If you have a skin archive, choose user skin, and choose the skin archive, but must input xml path of descriptor.");
						wrapMode:Text.WordWrap;
					}
					Text{
						font.pointSize: 20
						font.family: "Nokia Pure Text";
						width:parent.width;
						color:"black";
						text: qsTr("MicroEmulator boots with parellel, the ME process is under booter process.");
						wrapMode:Text.WordWrap;
					}
					Text{
						font.pointSize: 20
						font.family: "Nokia Pure Text";
						width:parent.width;
						color:"black";
						text: qsTr("MicroEmulator boots with sequential, the booter will quit, and ME is booting. When ME process exit, the booter will running.");
						wrapMode:Text.WordWrap;
					}
					Text{
						font.pointSize: 20
						font.family: "Nokia Pure Text";
						width:parent.width;
						color:"black";
						text: qsTr("The skins can also be setting in MicroEmulator.");
						wrapMode:Text.WordWrap;
					}
					Text{
						font.family: "Nokia Pure Text";
						font.pointSize: 20
						width:parent.width;
						color:"black";
						text: qsTr("Do not choose a jar file, can also run MicroEmulator.");
						wrapMode:Text.WordWrap;
					}
				}
			}
			SelectionHeader{
				text:qsTr("About");
				item:aboutitem;
			}
			SelectionBody{
				id:aboutitem;
				theight:childrenRect.height;
				Column {
					width:parent.width;
					visible:parent.fullShow;
					Image{
						anchors.horizontalCenter:parent.horizontalCenter;
						smooth:true;
						source:Qt.resolvedUrl("./microemulator.png");
					}
					Text{
						font.pointSize: 20
						font.family: "Nokia Pure Text";
						width:parent.width;
                        text: "<b><big>KarinME</big></b>";
						wrapMode:Text.WordWrap;
					}
					Text{
						font.pointSize: 20
						font.family: "Nokia Pure Text";
						width:parent.width;
                        text: "<b>" + qsTr("Version: ") + "0.3.1harmattan5+3.0.0snapshot.114</b>";
						wrapMode:Text.WrapAnywhere;
					}
					Text{
						font.pointSize: 20
						font.family: "Nokia Pure Text";
						width:parent.width;
                        text: "<b>" + qsTr("KarinME is a MicroEmulator front-end GUI booter by Qt Qml on MeeGo Harmattan.") + "</b>";
						wrapMode:Text.WordWrap;
					}
					Text{
						font.pointSize: 20
						font.family: "Nokia Pure Text";
						width:parent.width;
						text: "<b>" + qsTr("MicroEmulator is J2ME emulator, based on pure J2SE. More: ") + "<a href=\"www.microemu.org\">&lt;www.microemu.org&gt;</a></b>";
						wrapMode:Text.WordWrap;
						onLinkActivated:{
							Qt.openUrlExternally(link);
						}
					}
					Text{
						font.pointSize: 20
						font.family: "Nokia Pure Text";
						width:parent.width;
						text: "<b>Karin Zhao @ 2015 Dospy - 香磷ヽ <a href=\"mailto:beyondk2000@gmail.com\">&lt;beyondk2000@gmail.com&gt;</a></b>";
						wrapMode:Text.WrapAnywhere;
						onLinkActivated:{
							Qt.openUrlExternally(link);
						}
					}
				}
			}
		}
	}

	tools:ToolBarLayout{
		ToolIcon{
			iconId: "toolbar-back";
			onClicked:{
				pageStack.pop();
			}
		}
	}
}

