#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(39);
	ofSetLineWidth(3);
	ofEnableDepthTest();
}
//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	
	auto radius = 15;
	auto flag = true;
	float sqrt_3 = sqrt(3);
	for (float y = -ofGetHeight() * 0.5 - radius; y < ofGetHeight() * 0.5 + radius; y += radius * 1.5) {

		for (float x = -ofGetWidth() * 0.5 - radius; x < ofGetWidth() * 0.5 + radius; x += radius * sqrt_3) {

			auto location = flag ? glm::vec2(x, y) : glm::vec2(x + radius * sqrt_3 * 0.5, y);
			this->draw_hexagon(location, radius);
		}

		flag = !flag;
	}

	this->cam.end();
}

//--------------------------------------------------------------
void ofApp::draw_hexagon(glm::vec2 location, float radius) {

	ofPushMatrix();
	ofTranslate(location);

	auto noise_value = ofNoise(location.x * 0.05, location.y * 0.05, ofGetFrameNum() * 0.005);
	auto threshold = 0.68;
	auto z = 0;
	auto height = 50;
	if (noise_value > threshold) {
		
		z = ofMap(noise_value, threshold, 1, 0, height);
	}

	vector<glm::vec3> vertices, fill_vertices;
	for (int deg = 30; deg <= 390; deg += 60) {

		vertices.push_back(glm::vec3(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), z));
		fill_vertices.push_back(glm::vec3(radius * 0.999 * cos(deg * DEG_TO_RAD), radius * sin(deg * 0.999 * DEG_TO_RAD), z));
	}

	ofFill();
	ofSetColor(ofMap(z, 0, height, 39, 139));
	ofBeginShape();
	ofVertices(fill_vertices);
	ofEndShape(true);

	ofNoFill();
	ofSetColor(ofMap(z, 0, height, 239, 39));
	ofBeginShape();
	ofVertices(vertices);
	ofEndShape(true);

	ofPopMatrix();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}