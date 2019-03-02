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
    //vec2 rand = vec2(cos(gl_FragCoord.x * sp * 634.234567 + gl_FragCoord.y * pos.x * 123.432 + float(count * pos.x)), sin(gl_FragCoord.y * sp * 13.123456 + 121.1239 * pos.y * float(k * hx * hy)));
    //vec2 rand = vec2(cos(float(k)), sin(float(k)));
    A = pos + vec2(dx * sp, dy * sp);// + rand;
}

