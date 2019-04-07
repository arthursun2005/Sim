layout (location = 0) out float U;

uniform sampler2D P;
uniform sampler2D D;
uniform sampler2D M;
uniform vec2 invSize;

void main() {
    vec2 coord = gl_FragCoord.xy * invSize;
    
    float w = texelFetch(M, ivec2(gl_FragCoord.xy), 0).x;
    
    float E = texture(P, coord + vec2(invSize.x, 0.0)).x;
    float N = texture(P, coord + vec2(0.0, invSize.y)).x;
    float W = texture(P, coord - vec2(invSize.x, 0.0)).x;
    float S = texture(P, coord - vec2(0.0, invSize.y)).x;
    
    float d = texelFetch(D, ivec2(gl_FragCoord.xy), 0).x;
    U = (W + E + N + S - d) * 0.25 * min(w, 1.0);
}
