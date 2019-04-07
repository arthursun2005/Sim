layout (location = 0) out vec4 A;

uniform sampler2D V;
uniform sampler2D M;
uniform vec2 invSize;
uniform vec2 size;
uniform vec2 gridSize;

void main() {
    vec2 coord = gl_FragCoord.xy * invSize;
    float m = texture(M, coord).x;
    vec4 w = get(V, ivec2(gl_FragCoord.xy * gridSize / size));
    A = vec4(1.0) - (vec4(0.007, 0.003, 0.001, 0.0) * length(w.xy) + vec4(0.1)) * m * 0.005;
}



