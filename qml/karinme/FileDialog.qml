import QtQuick 1.1
import com.nokia.meego 1.1
import karin.file 2.0

Dialog {
	id: root

	width:screen.currentOrientation === Screen.Portrait || screen.currentOrientation === Screen.PortraitInverted ? 460 : 800;
	height:screen.currentOrientation === Screen.Portrait || screen.currentOrientation === Screen.PortraitInverted ? 600 : 360;

	property alias titleText:titletext.text;
	property string acceptButtonText:qsTr("Ok");
	property string acceptButtonText2:qsTr("Open");
	property alias rejectButtonText: rejectButton.text;
	property variant filters:[];
	onFiltersChanged:{
		if(Array.isArray(filters)){
			for(var i = 1; i < sublayout.children.length; i++){
				sublayout.children[i].destroyed();
			}
			if(filters.length > 0){
				filters.forEach(function(e){
					var component = Qt.createComponent(Qt.resolvedUrl("mecheckbox.qml"));
					if(component.status === Component.Ready){
						var obj = component.createObject(sublayout, {filter: e.filter, name: e.name});
					}else{
						console.log(component.errorString);
					}
				});
			}
		}
	}
	signal fileChoosed(string file);


	File{
		id:file;
	}

	title: Rectangle {
		id:head;
		height: 60;
		width: parent.width;
		color: "black";
		z:2;
		Column{
			anchors.fill:parent;
			Row{
				height:55;
				width:parent.width;
				Text{
					id:titletext;
					width:parent.width - space.width - tool.width;
					anchors.verticalCenter:parent.verticalCenter;
					font.family: "Nokia Pure Text";
					font.pointSize:24;
					color:"deeppink";
				}
				Rectangle{
					id:space;
					anchors.verticalCenter:parent.verticalCenter;
					width:5;
					height:parent.height;
					color:"white"
				}
				ToolIcon{
					id:tool;
					height:parent.height;
					width:height;
					iconId: "toolbar-close-white";
					anchors.verticalCenter:parent.verticalCenter;
					onClicked:{
						root.reject();
					}
				}
			}
			Rectangle{
				width:parent.width;
				height:5;
				color:"white"
			}
		}
	}

	content:Item{
		width:parent.width;
		height:screen.currentOrientation === Screen.Portrait || screen.currentOrientation === Screen.PortraitInverted ? 480 : 240;
		SearchBox{
			id:searchbox;
			z:1;
			anchors.top:parent.top;
			anchors.left:parent.left;
			anchors.right:parent.right;
            text: file.path === "/" ? file.path : file.path + "/";
			readOnly:false;
			onClicked:{
				file.path = text;
			}
			onInputingChanged:{
				if(inputing){
					dirbar.visible = true;
				}else{
					timer.running = true;
				}
			}
		}
		Rectangle{
			id:dirbar;
			z:1;
			anchors.top:searchbox.bottom;
			anchors.left:parent.left;
			width:searchbox.textFieldWidth;
			height:200;
			visible:false;
			color:"black";
			opacity:0.8;
			radius:10;
			smooth:true;
			ListView{
				anchors.fill:parent;
				clip:true;
				spacing:2;
				model:file.dirlist;
				delegate:Component{
					Item{
						width:ListView.view.width;
						height:40;
						Text{
							color:"white";
							font.pointSize:18;
							font.family: "Nokia Pure Text";
							anchors.verticalCenter:parent.verticalCenter;
							anchors.left:parent.left;
							text:modelData;
						}
						MouseArea{
							anchors.fill:parent;
							onClicked:{
								file.path = modelData;
							}
						}
					}
				}
				ScrollDecorator{
					flickableItem:parent;
				}
			}
		}
		ListView{
			id:lst;
			anchors.fill:parent;
			anchors.topMargin:searchbox.height + 5;
			anchors.bottomMargin:filterbar.height + 5;
			clip:true;
			focus:true;
			spacing:2;
			delegate:Component{
				Rectangle{
					width:ListView.view.width;
					height:80;
					color:ListView.isCurrentItem ? "grey" : "black";
					radius:10;
					smooth:true;
					Column{
						anchors.fill:parent;
						Text{
							width:parent.width;
							height:55;
							text:modelData.type ? modelData.name + "/" : modelData.name;
							font.pointSize:18;
							font.family: "Nokia Pure Text";
							color:parent.parent.ListView.isCurrentItem ? "black" : "white";
							elide:Text.ElideMiddle;
							maximumLineCount:2;
							wrapMode:Text.WrapAnywhere;
						}
						Text{
							width:parent.width;
							height:25;
							text:"%1  %2:%3  %4".arg(modelData.size).arg(modelData.owner).arg(modelData.group).arg(modelData.permission);
							font.pointSize:12;
							font.family: "Nokia Pure Text";
							color:parent.parent.ListView.isCurrentItem ? "black" : "white";
							elide:Text.ElideMiddle;
						}
					}
					MouseArea{
						anchors.fill:parent;
						onClicked:{
							parent.ListView.view.currentIndex = index;
						}
						onDoubleClicked:{
							parent.ListView.view.currentIndex = index;
							if(modelData.type){
								file.path = modelData.path;
							}else{
								root.fileChoosed(modelData.path);
								root.accept()
							}
						}
					}
				}
			}
			model:file.filelist;
			onModelChanged:{
				if(model && count > 0){
					currentIndex = 0;
				}else{
					currentIndex = -1;
				}
			}
			ScrollDecorator{
				flickableItem:parent;
			}
		}
		Rectangle{
			id:filterbar;
			z:1;
			height:childrenRect.height;
			anchors.bottom:parent.bottom;
			anchors.right:parent.right;
			anchors.left:parent.left;
			radius:10;
			smooth:true;
			color:"lightgray";
			Column{
				width:parent.width;
				Flickable{
					width:parent.width;
					height:60;
					contentWidth:childrenRect.width;
					contentHeight:height;
					clip:true;
					ButtonRow{
						id:sublayout;
						height:parent.height;
						CheckBox{
							anchors.verticalCenter:parent.verticalCenter;
							checked:file.filters === [];
							text:qsTr("All File (*.*)");
							onClicked:{
								file.filters = [];
							}
						}
					}
				}
				Flickable{
					width:parent.width;
					height:50;
					contentWidth:childrenRect.width;
					contentHeight:height;
					clip:true;
					Row{
						height:parent.height;
						spacing:2;
						Text{
							anchors.verticalCenter:parent.verticalCenter;
							font.pointSize:20;
							font.family: "Nokia Pure Text";
							color:"gray";
							text:qsTr("Show Hidden File");
						}
						Switch{
							anchors.verticalCenter:parent.verticalCenter;
							checked:file.showHidden;
							onCheckedChanged:{
								file.showHidden = checked;
							}
						}
					}
				}
			}
		}
	}

	Timer{
		id:timer;
		repeat:false;
		running:false;
		interval:400;
		onTriggered:{
			dirbar.visible = false;
			running = false;
		}
	}

	buttons: Item {
		id: buttonRowFiller
		width: parent.width
		height: childrenRect.height
		y: root.platformStyle.buttonsTopMargin

		onWidthChanged: {
			if ( (acceptButton.width + rejectButton.width > width) ||
			(acceptButton.implicitWidth + rejectButton.implicitWidth > width) ) {
				acceptButton.width = width / 2
				rejectButton.width = width / 2
			} else {
				acceptButton.width = acceptButton.implicitWidth
				rejectButton.width = rejectButton.implicitWidth
			}
		}

		Row {
			id: buttonRow
			height: childrenRect.height
			anchors.horizontalCenter: parent.horizontalCenter
			Button {
				id: acceptButton
				height: implicitHeight
				objectName: "acceptButton"
				text: file.filelist.length === 0 ? "" : file.filelist[lst.currentIndex].type ? acceptButtonText2 : acceptButtonText;
				onClicked:{
					if(file.filelist[lst.currentIndex].type){
						file.path = file.filelist[lst.currentIndex].path;
					}else{
						root.fileChoosed(file.filelist[lst.currentIndex].path);
						root.accept()
					}
				}
				visible: text != ""
				platformStyle: ButtonStyle {inverted: true}
			}
			Button {
				id: rejectButton
				height: implicitHeight
				objectName: "rejectButton"
				text: qsTr("Cancel");
				onClicked: reject()
				visible: text != ""
				platformStyle: ButtonStyle {inverted: true}
			}
		}
	}
}

