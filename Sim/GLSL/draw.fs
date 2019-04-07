layout (location = 0) out vec4 A;

uniform sampler2D V;
uniform float dt;

in vec2 coord;

void main() {
    vec2 v = texture(V, coord).xy;
    float l = length(v);
    vec4 d1 = vec4(2.0, 1.0, -1.0, 0.0);
    vec4 d2 = vec4(0.2, 0.2, -0.0, 0.0);
    A = vec4(0.0, 0.0, 1.0, 1.0) + vec4(l, l, l, 0.0) * d2 * dt;
}



