layout (location = 0) out float D;

uniform sampler2D V;
uniform sampler2D M;

void main() {
    ivec2 coord = ivec2(gl_FragCoord.xy);
    float w = texelFetch(M, coord, 0).x;
    vec2 n = texelFetch(V, coord, 0).xy;
    float x = texelFetch(V, coord + ivec2(1, 0), 0).x;
    float y = texelFetch(V, coord + ivec2(0, 1), 0).y;
    float div = ((x - n.x) + (y - n.y));
    float mw = 8.0;
    div -= max((w - mw) * 1.0, 0.0);
    D = div;
}


