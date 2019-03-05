layout (location = 0) out vec4 vel;

uniform sampler2D V;
uniform sampler2D U;
uniform sampler2D W;

float pressure(in ivec2 c) {
    return texelFetch(U, max(c, 0), 0).x;
}

void main() {
    ivec2 coord = ivec2(gl_FragCoord.xy);
    
    float w = texelFetch(W, coord, 0).x;
    
    if(w == 0.0)
        discard;
    
    vec4 vel0 = texelFetch(V, coord, 0);
    float n = texelFetch(U, coord, 0).x;
    float x = pressure(coord - ivec2(1, 0));
    float y = pressure(coord - ivec2(0, 1));
    vec2 s = n - vec2(x, y);
    vel0.xy -= s;
    vel = vel0;
}


