#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(39);
	ofSetColor(239);
	ofEnableDepthTest();
	//ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum());

	auto noise_seed = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));

	for (int param = 50; param <= 350; param += 50) {

		ofMesh mesh;

		int angle_x = ofMap(ofNoise(noise_seed.x, ofGetFrameNum() * -0.006 + param * 0.0003), 0, 1, -180, 180);
		auto rotation_x = glm::rotate(glm::mat4(), angle_x * (float)DEG_TO_RAD, glm::vec3(1, 0, 0));

		int angle_y = ofMap(ofNoise(noise_seed.y, ofGetFrameNum() * -0.006 + param * 0.0003), 0, 1, -180, 180);
		auto rotation_y = glm::rotate(glm::mat4(), angle_y * (float)DEG_TO_RAD, glm::vec3(0, 1, 0));

		int angle_z = ofMap(ofNoise(noise_seed.z, ofGetFrameNum() * -0.006 + param * 0.0003), 0, 1, -180, 180);
		auto rotation_z = glm::rotate(glm::mat4(), angle_y * (float)DEG_TO_RAD, glm::vec3(0, 0, 1));

		vector<glm::vec3> vertices;
		vertices.push_back(glm::vec3(param, param, param));
		vertices.push_back(glm::vec3(param, -param, -param));
		vertices.push_back(glm::vec3(-param, param, -param));
		vertices.push_back(glm::vec3(-param, -param, param));

		for (auto& vertex : vertices) {

			vertex = glm::vec4(vertex, 0)  * rotation_y * rotation_x;
		}

		mesh.addVertices(vertices);

		mesh.addIndex(0); mesh.addIndex(1); mesh.addIndex(2);
		mesh.addIndex(0); mesh.addIndex(1); mesh.addIndex(3);
		mesh.addIndex(0); mesh.addIndex(2); mesh.addIndex(3);
		mesh.addIndex(1); mesh.addIndex(2); mesh.addIndex(3);

		ofSetLineWidth(ofMap(param, 50, 350, 3, 0.5));

		mesh.drawWireframe();
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}