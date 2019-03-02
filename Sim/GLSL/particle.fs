layout (location = 0) out vec2 vel;

uniform sampler2D V;
uniform sampler2D P;
uniform sampler2D G;
uniform sampler2D T;
uniform vec2 invSize;
uniform vec2 size;

void main() {
    ivec2 coord = ivec2(gl_FragCoord.xy);
    vec2 vel0 = texelFetch(V, coord, 0).xy;
    vec2 pos0 = texelFetch(P, coord, 0).xy;
    vec2 gv = get(G, (pos0 + size) * 0.5).xy;
    vec2 gt = get(T, (pos0 + size) * 0.5).xy;
    vec2 fv = vel0 + (gv - gt);
    vel = mix(gv, fv, 0.0);
}





