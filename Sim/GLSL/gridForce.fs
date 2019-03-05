layout (location = 0) out vec4 vel;

uniform sampler2D V;
uniform vec2 exf;
uniform vec2 size;
uniform float dt;

void main() {
    ivec2 c = ivec2(gl_FragCoord.xy);
    vec4 vel0 = texelFetch(V, c, 0);
    vel0.xy += exf * dt;
    
    /*
    if(gl_FragCoord.x < 1.0 || gl_FragCoord.x > size.x - 1.0) {
        vel0.xz = vec2(0.0);
    }
    if(gl_FragCoord.y < 1.0 || gl_FragCoord.y > size.y - 1.0) {
        vel0.yw = vec2(0.0);
    }
     */
    
    vec2 pos = gl_FragCoord.xy + vel0.xy * dt * 0.5;
    
    float s = 0.0;
    
    if(pos.x < 1.0) {
        vel0.x = exf.x * s;
    }
    if(pos.y < 1.0) {
        vel0.y = exf.y * s;
    }
    
    if(pos.x > size.x - 1.0) {
        vel0.x = -exf.x * s;
    }
    if(pos.y > size.y - 1.0) {
        vel0.y = -exf.y * s;
    }
    
    
    
    
    vel = vel0;
}

