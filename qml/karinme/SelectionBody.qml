import QtQuick 1.1

Item{
	id:root;

	width:parent.width;
	property int theight:100;
	property bool fullShow:height === theight;
	state:"show";
	states:[
		State{
			name:"show";
			PropertyChanges {
				target: root;
				height:theight;
			}
		}
		,
		State{
			name:"noshow";
			PropertyChanges {
				target: root;
				height:0;
			}
		}
	]
	transitions: [
		Transition {
			from:"noshow";
			to:"show";
			NumberAnimation{
				target:root;
				property:"height";
				duration:400;
				easing.type:Easing.OutExpo;
			}
		}
		,
		Transition {
			from:"show";
			to:"noshow";
			NumberAnimation{
				target:root;
				property:"height";
				duration:400;
				easing.type:Easing.InExpo;
			}
		}
	]

}
