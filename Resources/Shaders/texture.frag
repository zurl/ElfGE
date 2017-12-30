#version 120

in vec2 aPos;
uniform sampler2D t;

void main() {
	gl_FragColor = texture(t,aPos);
}
