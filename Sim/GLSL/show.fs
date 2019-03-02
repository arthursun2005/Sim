layout (location = 0) out vec4 A;

uniform sampler2D V;
uniform sampler2D M;
uniform vec2 invSize;

void main() {
    vec2 coord = gl_FragCoord.xy * invSize;
    float m = texture(M, coord).x;
    if(m == 0.0) {
        A = vec4(0.0, 0.0, 0.0, 1.0);
        discard;
    }
    A = vec4(0.1, 0.1, 1.0, 1.0);// + vec4(0.003, 0.003, 0.0, 0.0) * length(w.xy);
}



