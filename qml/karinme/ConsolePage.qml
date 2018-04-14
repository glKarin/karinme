import QtQuick 1.1
import com.nokia.meego 1.1

MEPage{
	id:root;

	title:"<b>" + qsTr("Console") + "</b>";

	Flickable{
		id:flick;
		anchors.fill:parent;
		anchors.topMargin:headheight;
		contentWidth:width;
		contentHeight:textbox.height;
		clip:true;

		Text{
			id:textbox;
			wrapMode:Text.WrapAnywhere;
			anchors.top:parent.top;
			anchors.left:parent.left;
			width:parent.width;
			font.family: "Nokia Pure Text";
			font.pointSize:16;
		}

	}
	ScrollDecorator{
		flickableItem:flick;
	}
	Connections{
		target:booter;
		onOutput:{
			if(type === 0){
				textbox.text += ("<font color=\"blue\">" + text + "</font>");
			}else if(type === 2){
				textbox.text += ("<font color=\"red\">" + text + "</font>");
			}else{
				textbox.text += ("<font color=\"black\">" + text + "</font>");
			}
			textbox.text += "<br>";
		}
	}

	tools:ToolBarLayout{
		ToolIcon{
			iconId:"toolbar-back";
			enabled:!booter.running;
			onClicked:{
				pageStack.pop();
			}
		}
		/*
		 Label{
			 text:qsTr("Output");
		 }
		 Switch{
			 checked:booter.output;
			 onCheckedChanged:{
				 booter.output = checked;
			 }
		 }
		 */
		Button{
			text:qsTr("Terminate");
			enabled:booter.running;
			platformStyle:ButtonStyle{
				buttonWidth:200;
			}
			onClicked:{
				setMsg(qsTr("Killing MicroEmulator process..."));
				booter.kill();
			}
		}
	}
}
