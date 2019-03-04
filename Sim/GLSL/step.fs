layout (location = 0) out vec2 pos;

uniform sampler2D V;
uniform sampler2D P;
uniform sampler2D G;
uniform float dt;
uniform vec2 invSize;
uniform vec2 size;
uniform float seed;

void main() {
    vec2 coord = gl_FragCoord.xy * invSize;
    vec2 pos0 = texture(P, coord).xy;
    vec2 vel0 = get(G, pos0, size).xy;
    vec2 h = pos0 + vel0 * dt * 0.5;
    vec2 vel1 = get(G, h, size).xy;
    pos0 += vel1 * dt;
    pos0 = clamp(pos0, -size, size);
    pos = pos0;
}
