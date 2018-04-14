import com.nokia.meego 1.1

Page{
	id:root;
	property alias title:head.title;
	property alias headheight:head.height;
	property alias headbottom:head.bottom;
	
	//orientationLock: PageOrientation.LockPortrait;

	PageHeader{
		id:head;
		anchors.top:parent.top;
		anchors.left:parent.left;
	}

}
