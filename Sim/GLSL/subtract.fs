layout (location = 0) out vec4 vel;

uniform sampler2D V;
uniform sampler2D U;
uniform sampler2D W;
uniform vec2 invSize;
uniform vec2 invGrid;

void main() {
    vec2 coord = gl_FragCoord.xy * invGrid;
    vec2 coord2 = gl_FragCoord.xy * invSize;
    vec4 vel0 = texture(V, coord);
    float n = texture(U, coord2).x;
    float x = texture(U, coord2 - vec2(invSize.x, 0.0)).x;
    float y = texture(U, coord2 - vec2(0.0, invSize.y)).x;
    vec2 s = n - vec2(x, y);
    vel0.xy -= s;
    vel = vel0;
}


