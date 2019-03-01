layout (location = 0) out vec2 pos;

uniform sampler2D V;
uniform sampler2D P;
uniform sampler2D G;
uniform float dt;
uniform vec2 invSize;
uniform vec2 size;

void main() {
    vec2 coord = gl_FragCoord.xy * invSize;
    //vec2 vel0 = texture(V, coord).xy;
    vec2 pos0 = texture(P, coord).xy;
    vec2 vel0 = get(G, (pos0 + size) * 0.5).xy;
    vec2 h = pos0 + vel0 * dt * 0.5;
    vec2 vel1 = get(G, (h + size) * 0.5).xy;
    pos = pos0 + vel1 * dt;
}
