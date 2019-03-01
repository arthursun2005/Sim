layout (location = 0) out vec2 vel;

uniform sampler2D V;
uniform sampler2D P;
uniform float dt;
uniform vec2 invSize;
uniform vec2 exf;
uniform vec2 bound;

void main() {
    vec2 coord = gl_FragCoord.xy * invSize;
    vec2 vel0 = texture(V, coord).xy;
    vec2 pos0 = texture(P, coord).xy;
    vel0.xy += exf * dt;
    pos0 += vel0 * dt;
    /*
    vel0.x *= sign(pos0.x + bound.x);
    vel0.x *= sign(bound.x - pos0.x);
    vel0.y *= sign(pos0.y + bound.y);
    vel0.y *= sign(bound.y - pos0.y);
     */
    vel = vel0;
}
