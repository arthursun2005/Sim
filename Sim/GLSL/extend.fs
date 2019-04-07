layout (location = 0) out vec4 A;

uniform sampler2D V;
uniform vec2 invSize;

const float R = 7.0;

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
            float distSq = (x * x + y * y);
            distSq = distSq + (1.0 - sign(distSq));
            sum += w * v.xy * v.zw / distSq;
            weight += w * v.zw / distSq;
            ww += w * v.zw * v.zw / distSq;
        }
    }
    weight = weight + (1.0 - sign(weight));
    A = ct + vec4(sum / weight, ww / weight);
}

