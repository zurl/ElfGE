
inout vec2 aPos;
void main() {
	gl_Position = vec4(aPos.xy,0, 1.0);
}
