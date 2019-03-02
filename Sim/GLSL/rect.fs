layout (location = 0) out vec2 A;

uniform vec2 pos;
uniform float sp;
uniform int hx;
uniform int hy;
uniform int root;
uniform int count;

void main() {
    ivec2 u = ivec2(gl_FragCoord.xy);
    int k = u.x + u.y * root;
    int on = k - count;
    int dx = (on%hx) - (hx >> 1);
    int dy = (on/hx) - (hy >> 1);
    A = pos + vec2(dx * sp, dy * sp) + rand(float(u), gl_FragCoord.xy) - 0.5;
}

