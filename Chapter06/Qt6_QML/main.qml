import QtQuick

Window {
	width: 640
	height: 480
	visible: true
	title: qsTr("Hello World")

	//property variant myColor: "red"
	//property url imageFolder: "/images"

	property variant myColor: Qt.color("red")
	property url imageFolder: Qt.resolvedUrl("/images")

	Rectangle {
		id: rect
		x: 100
		y: 100
		width: 100
		height: 100
		color: myColor
	}

	Image {
		id: img
		x: 300
		y: 100
		width: 150
		height: 180
		source: imageFolder + "/tux.png"
	}
}
