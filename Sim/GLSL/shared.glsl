#version 410 core

vec4 get(in sampler2D T, ivec2 p) {
    vec4 n = texelFetch(T, p, 0);
    vec2 x = texelFetch(T, p + ivec2(1, 0), 0).xz;
    vec2 y = texelFetch(T, p + ivec2(0, 1), 0).yw;
    return (n + vec4(x.x, y.x, x.y, y.y)) * 0.5;
}

vec4 get(in sampler2D T, vec2 p) {
    vec2 k = floor(p - 0.5) + 0.5;
    vec2 d = abs(p - k);
    ivec2 q = ivec2(k);
    vec4 n00 = get(T, q + ivec2(0, 0)) * (1.0 - d.x) * (1.0 - d.y);
    vec4 n01 = get(T, q + ivec2(0, 1)) * (1.0 - d.x) * (d.y);
    vec4 n10 = get(T, q + ivec2(1, 0)) * (d.x) * (1.0 - d.y);
    vec4 n11 = get(T, q + ivec2(1, 1)) * (d.x) * (d.y);
    return n00 + n01 + n10 + n11;
}
