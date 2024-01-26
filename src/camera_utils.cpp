#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <iterator>
#include "camera_utils.h"


bool CameraUtils::recording = false;
std::string CameraUtils::frameRate = "30";

void CameraUtils::start(QString mode) {
	switch (resolve(mode)) {
	case IMG: start_still(); break;
	case VID: start_vid(); break;
	case LPS: start_lapse(); break;
	default: break;
	};
};


void CameraUtils::stop(void) {
	stop_still();
	stop_vid();
	stop_lapse();
};


bool CameraUtils::get_status(void) {
	return recording;
};


void CameraUtils::capture(QString mode) {
	switch (resolve(mode)) {
	case IMG: capture_still(); break;
	case FRM: capture_frame(); break;
	default: break;
	};
};


void CameraUtils::record(void) {
	std::string cmd;
	cmd = "pgrep libcamera-vid | xargs -I % kill -USR1 % && \
		cd /usr/share/hypercube/FIles/Projects/" + project + " && \
		ls -1 | grep VID | wc -l | xargs printf \"%04d\" | xargs -I % mv vid.mp4 VID_%.mp4";
	system(cmd.c_str());
	recording ^= 1;
	std::cout << "Flipped: " << recording << std::endl;
};


void CameraUtils::update_annotations(signed int anot) {
	annotation += anot;
}



void CameraUtils::set_project(QString proj) {
	project = proj.toStdString();
};


void CameraUtils::set_homeDir(std::string dir) {
	homeDir = dir;
}


// Private
//home directory
std::string CameraUtils::homeDir = "/usr/share/hypercube/FIles";
std::string CameraUtils::project = "example";
int CameraUtils::annotation = 0;



std::string CameraUtils::get_preview_arg(void) {
	std::string arg = " -p '" +
			std::to_string(CAMERA_VIEWPORT_X) + "," +
			std::to_string(CAMERA_VIEWPORT_Y) + "," +
			std::to_string(CAMERA_VIEWPORT_WIDTH) + "," +
			std::to_string(CAMERA_VIEWPORT_HEIGHT) + "'";
	return arg;
};


void CameraUtils::start_still(void) {
	stop();
	std::string cmd = "libcamera-still" + get_preview_arg() +
			" -t 0 " + get_annotation_arg() +
					  "-s -o /usr/share/hypercube/FIles/Projects/" +
		project + "/img.jpg &";
	system(cmd.c_str());
};


void CameraUtils::capture_still(void) {
	std::string cmd;
	cmd = "pgrep libcamera-still | xargs -I % kill -USR1 % && \
		cd /usr/share/hypercube/FIles/Projects/" + project + " && \
		ls -1 | grep IMG | wc -l | xargs printf \"%04d\" | xargs -I % mv img.jpg IMG_%.jpg";
	system(cmd.c_str());
};


void CameraUtils::stop_still(void) {
	std::string cmd = "killall -q libcamera-still";
	system(cmd.c_str());
};


void CameraUtils::update_frameRate(int rate) {
	frameRate = std::to_string(rate);
};

//Changed to libcamera-vid added codec and bitrate
void CameraUtils::start_vid(void) {
	stop();
	std::string cmd = "libcamera-vid " + get_preview_arg() +
			"  " + "-t 0 " + get_annotation_arg() +
					  "-b 9000000 -fps " + frameRate + " --codec libav -o /usr/share/hypercube/FIles/Projects/" +
		project + "/vid.mp4 &";
	system(cmd.c_str());
};


void CameraUtils::stop_vid(void) {
	std::string cmd = "killall -q libcamera-vid";
	system(cmd.c_str());
};


void CameraUtils::start_lapse(void) {
	stop();
	std::string cmd = "libcamera-still " + get_preview_arg() +
			" --mode 4 -t 0 " + get_annotation_arg() +
					  "-s -o /usr/share/hypercube/FIles/Projects/" +
		project + "/lps.jpg &";
	system(cmd.c_str());
};


std::string CameraUtils::get_annotation_arg(void) {
	std::string cmd;
	if (annotation) {
		cmd = "-a " + std::to_string(annotation) + " ";
	} else {
		cmd = "";
	}
	return cmd;
}


void CameraUtils::capture_image_EXT(void) {
	capture_still();
};


void CameraUtils::capture_frame_EXT(void) {
	capture_frame();
};


void CameraUtils::capture_video_EXT(void) {
	record();
};


void CameraUtils::capture_frame(void) {
	std::string cmd;
	cmd = "pgrep libcamera-still | xargs -I % kill -USR1 % && \
		cd /usr/share/hypercube/FIles/Projects/" + project + " && \
		ls -1 | grep FRM | wc -l | xargs printf \"%04d\" | xargs -I % mv lps.jpg FRM_%.jpg";
	system(cmd.c_str());
};


void CameraUtils::stop_lapse(void) {
	std::string cmd = "killall -q libcamera-still";
	system(cmd.c_str());
};


Mode CameraUtils::resolve(QString mode) {
	if (mode == "IMG") return IMG;
	if (mode == "VID") return VID;
	if (mode == "LPS") return LPS;
	if (mode == "FRM") return FRM;
	return NUL;
}
