layout (location = 0) out vec4 vel;

uniform sampler2D V;
uniform sampler2D U;
uniform sampler2D W;
uniform vec2 invSize;

void main() {
    ivec2 coord = ivec2(gl_FragCoord.xy);
    vec4 vel0 = texelFetch(V, coord, 0);
    float n = texture(U, gl_FragCoord.xy * invSize).x;
    float x = texture(U, (gl_FragCoord.xy - vec2(1.0, 0.0)) * invSize).x;
    float y = texture(U, (gl_FragCoord.xy - vec2(0.0, 1.0)) * invSize).x;
    vec2 s = n - vec2(x, y);
    vel0.xy -= s;
    vel = vel0;
}


