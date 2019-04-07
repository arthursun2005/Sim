layout (location = 0) in vec2 uv;

uniform sampler2D P;
uniform sampler2D V;
uniform int x;
uniform int y;
uniform vec2 size;

out vec4 a;

void main() {
    vec2 p = texture(P, uv).xy + size;
    vec2 v = texture(V, uv).xy;
    float kx[2] = float[](p.x, p.x + 1.0f);
    float ky[2] = float[](p.y, p.y + 1.0f);
    float k[2] = float[](0.0f, 1.0f);
    vec2 kv = vec2(k[x], k[y]);
    a = vec4(v * kv, kv);
    
    gl_PointSize = 1.0f;
    gl_Position = vec4(vec2(kx[x], ky[y]) / (size + 1.0f) - 1.0f, 0.0f, 1.0f);
}
