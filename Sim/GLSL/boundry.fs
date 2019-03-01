layout (location = 0) out vec4 vel;

uniform sampler2D V;
uniform vec2 invSize;

void main() {
    vec2 coord = gl_FragCoord.xy * invSize;
    vec4 vel0 = texture(V, coord).xyzw;
    if(coord.x < invSize.x || coord.x > 1.0 - invSize.x) {
        vel0.xz = vec2(0.0);
    }
    if(coord.y < invSize.y || coord.y > 1.0 - invSize.y) {
        vel0.yw = vec2(0.0);
    }
    vel = vel0;
}






