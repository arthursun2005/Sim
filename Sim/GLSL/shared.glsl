#version 410 core

#define pi 3.141592654

precision mediump float;

vec4 get(in sampler2D T, ivec2 p) {
    vec4 n = texelFetch(T, p, 0);
    vec2 x = texelFetch(T, p + ivec2(1, 0), 0).xz;
    vec2 y = texelFetch(T, p + ivec2(0, 1), 0).yw;
    return (n + vec4(x.x, y.x, x.y, y.y)) * 0.5;
}

vec4 get(in sampler2D T, vec2 p, vec2 s) {
    vec2 g = 1.0 + s;
    p = (p + s)/(2.0 * g);
    vec4 n = texture(T, p);
    vec2 x = texture(T, p + vec2(1.0/g.x, 0.0)).xz;
    vec2 y = texture(T, p + vec2(0.0, 1.0/g.y)).yw;
    return (n + vec4(x.x, y.x, x.y, y.y)) * 0.5;
}

vec2 rand2(float seed, vec2 coord) {
    float x = fract(cos(distance(vec2(seed * 12.22334 + 2.2123311, 9.12524 + seed * 0.1631), coord.yx)) * seed);
    float y = fract(sin(distance(vec2(121.151236 + seed * 0.12631, seed * 141.923453 + 8.9162422), coord.xy)) * seed);
    return vec2(x, y) * 2.0 - 1.0;
}

vec2 rand(float seed, vec2 coord) {
    float x = mod(cos(distance(vec2(seed * 9.22334 + 2.2123311, 9.12524 + seed * 0.1631), coord.yx)) * seed, 2.0 * pi);
    float y = fract(sin(distance(vec2(12.9188346 + seed * 0.112631, seed * 141.923453 + 8.9162422), coord.xy)) * seed);
    return vec2(cos(x), sin(x)) * y;
}
