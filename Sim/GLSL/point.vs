layout (location = 0) in vec2 uv;

void main() {
    gl_PointSize = 1.0;
    gl_Position = vec4(uv * 2.0 - 1.0, 0.0, 1.0);
}
