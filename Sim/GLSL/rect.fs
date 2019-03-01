layout (location = 0) out vec2 A;

uniform vec2 pos;
uniform float sp;
uniform int hx;
uniform int hy;
uniform int root;
uniform int count;

void main() {
    ivec2 u = ivec2(gl_FragCoord.xy);
    int on = u.x + u.y * root - count;
    int dx = (on%hx) - (hx >> 1);
    int dy = (on/hx) - (hy >> 1);
    A = pos + vec2(dx * sp, dy * sp);
}

