import QtQuick 1.1
import com.nokia.meego 1.1
import com.nokia.extras 1.1
import karin.microemulator 1.0

PageStackWindow{
	id:app;

	showStatusBar: true;
	initialPage:MainPage{ id:mainpage; }

	InfoBanner {
		id: infobanner; 
		topMargin: 50;
		leftMargin:5;
		height:text.height + 10;
	}

	function setMsg(text) {
		infobanner.text = text;
		infobanner.show();
	}

	MEBooter{
		id:booter;
	}

}

