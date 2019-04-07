layout (location = 0) out vec4 vel;

uniform sampler2D V;
uniform vec2 exf;
uniform vec2 size;
uniform float dt;

void main() {
    ivec2 c = ivec2(gl_FragCoord.xy);
    vec4 vel0 = texelFetch(V, c, 0);
    vel0.xy += exf * dt;
    
    vec2 pos = gl_FragCoord.xy + vel0.xy * dt * 0.5 - vec2(0.5, 0.5);
    
    vec2 d;
    d.x = (sign(pos.x - 1.0) * 0.5 + 0.5) * (sign(size.x - pos.x - 1.0) * 0.5 + 0.5);
    d.y = (sign(pos.y - 1.0) * 0.5 + 0.5) * (sign(size.y - pos.y - 1.0) * 0.5 + 0.5);
    
    vel0.xy *= d;

    vel = vel0;
}

