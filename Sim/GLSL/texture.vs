layout (location = 0) in vec2 uv;

uniform sampler2D T;
uniform vec2 scl;
uniform float size;

void main() {
    gl_PointSize = size;
    gl_Position = vec4(texture(T, uv).xy * scl, 0.0, 1.0);
}


