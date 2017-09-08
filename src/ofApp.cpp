#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	minDistance = 10;
	leftMouseButtonPressed = false;
}

//--------------------------------------------------------------
void ofApp::update(){
	if (leftMouseButtonPressed) {
		ofVec2f mousePos(ofGetMouseX(), ofGetMouseY());
		if (lastPoint.distance(mousePos) >= minDistance) {
			// a.distance(b) calculates the Euclidean distance between point a and b.  It's
			// the length of the straight line distance between the points.
			currentPolyline.curveTo(mousePos);  // Here we are using an ofVec2f with curveTo(...)
			lastPoint = mousePos;
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0);
	ofSetColor(255);  // White color for saved polylines
	for (int i = 0; i<polylines.size(); i++) {
		ofPolyline polyline = polylines[i];
		polyline.draw();

		//vector<ofVec3f> vertices = polyline.getVertices();
		//for (int vertexIndex = 0; vertexIndex<vertices.size(); vertexIndex++) {
		//	ofVec3f vertex = vertices[vertexIndex];  // ofVec3f is like ofVec2f, but with a third dimension, z
		//	ofDrawCircle(vertex, 5);
		//}
		//for (int p = 0; p<100; p += 10) {
		//	ofVec3f point = polyline.getPointAtPercent(p / 100.0);  // Returns a point at a percentage along the polyline
		//	ofDrawCircle(point, 5);
		//}

		//vector<ofVec3f> vertices = polyline.getVertices();
		//float normalLength = 50;
		//for (int vertexIndex = 0; vertexIndex<vertices.size(); vertexIndex++) {
		//	ofVec3f vertex = vertices[vertexIndex];  // Get the vertex
		//	ofVec3f normal = polyline.getNormalAtIndex(vertexIndex) * normalLength;  // Scale the normal
		//	ofDrawLine(vertex - normal / 2, vertex + normal / 2);  // Center the scaled normal around the vertex
		//}

		/*float normalLength = 50;
		ofSetColor(255, 100);
		for (int p = 0; p<1000; p += 1) {
			ofVec3f point = polyline.getPointAtPercent(p / 1000.0);
			float floatIndex = polyline.getIndexAtPercent(p / 1000.0);
			ofVec3f normal = polyline.getNormalAtIndexInterpolated(floatIndex) * normalLength;
			ofDrawLine(point - normal / 2, point + normal / 2);
		}*/

		vector<ofVec3f> vertices = polyline.getVertices();
		float tangentLength = 180;
		ofSetColor(255, 100);
		/*for (int vertexIndex = 0; vertexIndex<vertices.size(); vertexIndex++) {
			ofVec3f vertex = vertices[vertexIndex];
			ofVec3f tangent = polyline.getTangentAtIndex(vertexIndex) * tangentLength;
			ofDrawLine(vertex - tangent / 2, vertex + tangent / 2);
		}*/

		for (float i=0; i < polyline.getPerimeter(); i+=1.2f)
		{
			ofVec3f point = polyline.getPointAtLength(i);
			ofVec3f tangent = polyline.getTangentAtIndexInterpolated(polyline.getIndexAtLength(i)) * tangentLength;
			ofDrawLine(point - tangent / 2, point + tangent / 2);
		}

	}
	ofSetColor(255, 100, 0);  // Orange color for active polyline
	currentPolyline.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'z')
	{
		if (polylines.size() != 0)
		{
			redo.push_back(polylines.back());
			polylines.pop_back();
		}
	}
	if (key == 'y')
	{
		if (redo.size() != 0)
		{
			polylines.push_back(redo.back());
			redo.pop_back();
		}
	}
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	if (button == OF_MOUSE_BUTTON_LEFT) {
		leftMouseButtonPressed = true;
		currentPolyline.curveTo(x, y);  // Remember that x and y are the location of the mouse
		currentPolyline.curveTo(x, y);  // Necessary duplicate for first control point
		lastPoint.set(x, y);  // Set the x and y of a ofVec2f in a single line
	}
	if (button == OF_MOUSE_BUTTON_RIGHT)
	{
		polylines.clear();
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	if (button == OF_MOUSE_BUTTON_LEFT) {
		leftMouseButtonPressed = false;
		currentPolyline.curveTo(x, y); // Necessary duplicate for last control point
		polylines.push_back(currentPolyline);
		currentPolyline.clear();  // Erase the vertices, allows us to start a new brush stroke
	}
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
