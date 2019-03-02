layout (location = 0) out vec4 vel;

uniform sampler2D V;
uniform vec2 size;

void main() {
    vec4 vel0 = texelFetch(V, ivec2(gl_FragCoord.xy), 0);
    if(gl_FragCoord.x < 1.0 || gl_FragCoord.x > size.x - 1.0) {
        vel0.xz = vec2(0.0);
    }
    if(gl_FragCoord.y < 1.0 || gl_FragCoord.y > size.y - 1.0) {
        vel0.yw = vec2(0.0);
    }
    vel = vel0;
}






