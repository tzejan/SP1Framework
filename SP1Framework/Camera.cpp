#include "Camera.h"

Camera::Camera() {
	camx = 0;
	camy = 0;
}
Camera::~Camera() {

}

void Camera::setCamX(int x) {
	camx = x;
}
void Camera::setCamY(int y) {
	camy = y;
}

int Camera::getCamX() {
	return camx;
}
int Camera::getCamY() {
	return camy;
}