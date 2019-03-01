layout (location = 0) out vec4 A;

uniform sampler2D V;
uniform vec2 invSize;

const float R = 4.0;

void main() {
    vec2 coord = gl_FragCoord.xy * invSize;
    vec4 ct = texture(V, coord);
    vec2 w = 1.0 - sign(ct.zw);
    vec2 sum = vec2(0.0);
    vec2 weight = vec2(0.0);
    vec2 ww = vec2(0.0);
    for(float x = -R; x <= R; x += 1.0) {
        for(float y = -R; y <= R; y += 1.0) {
            vec4 v = texture(V, coord + vec2(x, y) * invSize);
            sum += w * v.zw * v.xy;
            weight += w * v.zw;
        }
    }
    A = ct + vec4(sum / (weight + (1.0 - sign(weight))), 0.0, 0.0);
}

