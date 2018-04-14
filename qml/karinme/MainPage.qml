import QtQuick 1.1
import com.nokia.meego 1.1

MEPage{
	id:root;
    title:"<b><big>KarinME</big></b>";

	property variant jrePathDialog:null;
	property variant jarPathDialog:null;
	property variant skinPathDialog:null;

	Flickable{
		anchors.fill:parent;
		anchors.topMargin:headheight;
		contentWidth:width;
		clip:true;
		contentHeight:mainlayout.height;
		Column{
			id:mainlayout;
			width:parent.width;
			spacing:3;
			SelectionHeader{
				text:qsTr("JRE Path");
				item:jrepathitem;
			}
			SelectionBody{
				id:jrepathitem;
				theight:childrenRect.height;
				Column{
					width:parent.width;
					visible:parent.fullShow;
					LineText{
						anchors.horizontalCenter:parent.horizontalCenter;
						text:qsTr("Choose JRE binary path");
					}
					SearchBox{
						text:booter.javaPath;
                        placeholderText: qsTr("Java binary file path");
						onClicked:{
							if(!jrePathDialog){
								var component = Qt.createComponent(Qt.resolvedUrl("FileDialog.qml"));
								if(component.status === Component.Ready){
									jrePathDialog = component.createObject(root, {titleText: qsTr("Find JRE binary")});
									jrePathDialog.fileChoosed.connect(function(file){
										booter.javaPath = file;
									});
									jrePathDialog.open();
								}else{
									console.log(component.errorString);
								}
							}else{
								jrePathDialog.open();
							}
						}
					}
					Row{
						width:parent.width;
						height:childrenRect.height;
						Button{
							text:qsTr("Using Default");
							platformStyle:ButtonStyle{
								buttonWidth:parent.width / 2;
							}
							onClicked:{
								booter.setDefaultJre();
							}
						}
						Button{
							text:qsTr("Using $PATH");
							platformStyle:ButtonStyle{
								buttonWidth:parent.width / 2;
							}
							onClicked:{
								booter.javaPath = "java";
							}
						}
					}
				}
			}

			SelectionHeader{
				text:qsTr("Setting");
				item:settingitem;
			}
			SelectionBody{
				id:settingitem;
				theight:childrenRect.height;
				Column{
					width:parent.width;
					visible:parent.fullShow;
					spacing:2;
					LineText{
						anchors.horizontalCenter:parent.horizontalCenter;
						text:qsTr("J2ME API");
					}
					ButtonColumn{
						width:parent.width;
						exclusive:false;
						spacing:2;
						CheckBox{
							width:parent.width;
							checked:booter.jsr75Enabled;
							text:"jsr75";
							onClicked:{
								booter.jsr75Enabled = !booter.jsr75Enabled;
							}
						}
						CheckBox{
							width:parent.width;
							checked:booter.jsr120Enabled;
							text:"jsr120";
							onClicked:{
								booter.jsr120Enabled = !booter.jsr120Enabled;
							}
						}
						CheckBox{
							width:parent.width;
							checked:booter.jsr135Enabled;
							text:"jsr135";
							onClicked:{
								booter.jsr135Enabled = !booter.jsr135Enabled;
							}
						}
						CheckBox{
							width:parent.width;
							checked:booter.jsr82Enabled;
							text:"jsr82";
							onClicked:{
								booter.jsr82Enabled = !booter.jsr82Enabled;
							}
						}
						CheckBox{
							width:parent.width;
							checked:booter.nokiauiApiEnabled;
							text:"Nokia UI";
							onClicked:{
								booter.nokiauiApiEnabled = !booter.nokiauiApiEnabled;
							}
						}
						CheckBox{
							width:parent.width;
							checked:booter.siemensApiEnabled;
							text:"Siemens API";
							onClicked:{
								booter.siemensApiEnabled = !booter.siemensApiEnabled;
							}
						}
					}
					LineText{
						anchors.horizontalCenter:parent.horizontalCenter;
						text:qsTr("Skin");
					}
					ButtonColumn{
						width:parent.width;
						exclusive:true;
						spacing:2;
						CheckBox{
							width:parent.width;
							checked:booter.skin === 0;
							text:qsTr("MicroEmulator Default Settings");
							onClicked:{
								booter.skin = 0;
							}
						}
						/*
						CheckBox{
							width:parent.width;
							checked:booter.skin === 1;
							text:qsTr("ME Minimum 176x220");
							onClicked:{
								booter.skin = 1;
							}
						}
						CheckBox{
							width:parent.width;
							checked:booter.skin === 2;
							text:qsTr("ME Large 240x320");
							onClicked:{
								booter.skin = 2;
							}
						}
						CheckBox{
							width:parent.width;
							checked:booter.skin === 3;
							text:qsTr("ME Resizable");
							onClicked:{
								booter.skin = 3;
							}
						}
						*/
						CheckBox{
							width:parent.width;
							checked:booter.skin === 4;
							text:qsTr("T9 Virtual Keyboard + 240x320");
							onClicked:{
								booter.skin = 4;
							}
						}
						CheckBox{
							width:parent.width;
							checked:booter.skin === 5;
							text:qsTr("Navigation Virtual Keyboard + 640x360");
							onClicked:{
								booter.skin = 5;
							}
						}
						CheckBox{
							width:parent.width;
							checked:booter.skin === 6;
							text:qsTr("User");
							onClicked:{
								booter.skin = 6;
							}
						}
					}
					SearchBox{
						text:booter.userSkin;
						enabled:booter.skin === 6;
                        placeholderText: qsTr("Skin archive path");
						onClicked:{
							if(!skinPathDialog){
								var component = Qt.createComponent(Qt.resolvedUrl("FileDialog.qml"));
								if(component.status === Component.Ready){
									skinPathDialog = component.createObject(root, {titleText: qsTr("Find skin archive"), filters: [{name: qsTr("jar/zip archive"), filter: ["*.jar", "*.zip"]}]});
									skinPathDialog.fileChoosed.connect(function(file){
										booter.userSkin = file;
									});
									skinPathDialog.open();
								}else{
									console.log(component.errorString);
								}
							}else{
								skinPathDialog.open();
							}
						}
					}
					SearchBox{
						text:booter.userSkinXml;
						readOnly:!(booter.skin === 6);
						enabled:booter.skin === 6;
                        placeholderText: qsTr("Input XML path of skin descriptor in your archive");
						iconSource:"image://theme/icon-m-toolbar-done";
						onClicked:{
							booter.userSkinXml = text;
						}
					}
					Row{
						width:parent.width;
						height:50;
						LineText{
							anchors.verticalCenter:parent.verticalCenter;
							style:"left";
							width:parent.width - switcher.width;
							text:qsTr("Fullscreen");
						}
						Switch{
							id:switcher;
							anchors.verticalCenter:parent.verticalCenter;
							enabled:false;
							//checked:booter.fullscreen;
                            checked:false;
							onCheckedChanged:{
								//booter.fullscreen = checked;
							}
						}
					}
					Row{
						width:parent.width;
						height:50;
						LineText{
							anchors.verticalCenter:parent.verticalCenter;
							style:"left";
							width:parent.width - switcher.width;
							text:qsTr("Terminal Output");
						}
						Switch{
							anchors.verticalCenter:parent.verticalCenter;
							checked:booter.output;
							onCheckedChanged:{
								booter.output = checked;
							}
						}
					}
				}
			}

			SelectionHeader{
				text:qsTr("jar Path");
				item:jarpathitem;
			}
			SelectionBody{
				id:jarpathitem;
				theight:childrenRect.height;
				Column{
					width:parent.width;
					spacing:2;
					visible:parent.fullShow;
					LineText{
						anchors.horizontalCenter:parent.horizontalCenter;
						text:qsTr("Choose jar file path");
					}
					SearchBox{
						id:jarfilebox;
                        placeholderText: qsTr("jar/jad file path (Allow empty)");
						onClicked:{
							if(!jarPathDialog){
								var component = Qt.createComponent(Qt.resolvedUrl("FileDialog.qml"));
								if(component.status === Component.Ready){
									var arr = [];
									arr.push({
										name: qsTr("jar file"),
										filter: ["*.jar"]
									});
									arr.push({
										name: qsTr("jar/zip archive file"),
										filter: ["*.jar", "*.zip"]
									});
									jarPathDialog = component.createObject(root, {titleText: qsTr("Choose a jar file"), filters: arr});
									jarPathDialog.fileChoosed.connect(function(file){
										jarfilebox.text = file;
									});
									jarPathDialog.open();
								}else{
									console.log(component.errorString);
								}
							}else{
								jarPathDialog.open();
							}
						}
					}
				}
			}

		}
	}

	tools:ToolBarLayout{
		Button{
			text:qsTr("Parallel Boot");
			platformStyle:ButtonStyle{
				buttonWidth:200;
			}
			onClicked:{
				setMsg(qsTr("MicroEmulator is booting..."));
				pageStack.push(Qt.resolvedUrl("ConsolePage.qml"));
				booter.internalBoot(jarfilebox.text);
			}
		}
		ToolIcon{
			iconId:"toolbar-application";
			onClicked:{
				pageStack.push(Qt.resolvedUrl("AboutPage.qml"));
			}
		}
		Button{
			text:qsTr("Sequential Boot");
			platformStyle:ButtonStyle{
				buttonWidth:200;
			}
			onClicked:{
				setMsg(qsTr("Front end application is exiting...\nMicroEmulator is booting..."));
				booter.externalBoot(jarfilebox.text);
			}
		}
	}

}
