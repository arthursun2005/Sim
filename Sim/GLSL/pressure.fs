layout (location = 0) out float U;

uniform sampler2D P;
uniform sampler2D D;
uniform sampler2D M;
uniform vec2 invSize;

void main() {
    vec2 coord = gl_FragCoord.xy * invSize;
    
    float w = texture(M, coord - vec2(invSize.x, 0.0)).x;
    float e = texture(M, coord + vec2(invSize.x, 0.0)).x;
    float n = texture(M, coord + vec2(0.0, invSize.y)).x;
    float s = texture(M, coord - vec2(0.0, invSize.y)).x;
    
    w = min(w, 1.0);
    e = min(e, 1.0);
    n = min(n, 1.0);
    s = min(s, 1.0);
    
    float E = texture(P, coord + vec2(invSize.x, 0.0)).x * e;
    float N = texture(P, coord + vec2(0.0, invSize.y)).x * n;
    float W = texture(P, coord - vec2(invSize.x, 0.0)).x * w;
    float S = texture(P, coord - vec2(0.0, invSize.y)).x * s;
    
    float d = texture(D, coord).x;
    U = (W + E + N + S - d) * 0.25;
}
