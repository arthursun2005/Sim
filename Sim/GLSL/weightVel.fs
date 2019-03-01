layout (location = 0) out vec4 A;

uniform sampler2D V;
uniform vec2 invSize;

void main() {
    vec2 coord = gl_FragCoord.xy * invSize;
    vec4 vel = texture(V, coord);
    vel.xy /= vel.zw + (1.0 - sign(vel.zw));
    A = vel;
}

