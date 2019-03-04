layout (location = 0) out float D;

uniform sampler2D V;
uniform sampler2D M;
uniform vec2 invSize;
uniform vec2 size;

void main() {
    vec2 coord = gl_FragCoord.xy * invSize;
    float w = texelFetch(M, ivec2(gl_FragCoord.xy), 0).x;
    vec2 n = texture(V, coord).xy;
    float x = texture(V, coord + vec2(invSize.x, 0.0)).x;
    float y = texture(V, coord + vec2(0.0, invSize.y)).y;
    float div = ((x - n.x) + (y - n.y));
    float mw = 8.0;
    div -= max((w - mw) * 1.0, 0.0);
    D = div;
}


