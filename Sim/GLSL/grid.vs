layout (location = 0) in vec2 uv;

uniform sampler2D P;
uniform sampler2D V;
uniform vec2 size;

out vec4 a;

void main() {
    int x = gl_VertexID % 2;
    int y = (x + 1) % 2;
    vec2 p = texture(P, uv).xy + size;
    vec2 v = texture(V, uv).xy;
    float kx[2] = float[](p.x + 0.0, p.x + 1.0);
    float ky[2] = float[](p.y + 0.0, p.y + 1.0);
    float k[2] = float[](0.0, 1.0);
    vec2 kv = vec2(k[x], k[y]);
    a = vec4(v * kv, kv);
    
    gl_PointSize = 1.0;
    gl_Position = vec4(vec2(kx[x], ky[y]) / (size + 1.0) - 1.0, 0.0, 1.0);
}
