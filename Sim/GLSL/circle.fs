layout (location = 0) out vec2 A;

uniform vec2 pos;
uniform float radius;

void main() {
    float s = gl_FragCoord.x * 0.12345;
    vec2 k = rand2(s, gl_FragCoord.xy) * radius;
    while(k.x * k.x + k.y * k.y >= radius * radius) {
        s += s + 4.1231;
        k = rand2(s, gl_FragCoord.xy) * radius;
    }
    A = pos + k;
}


