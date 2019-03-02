layout (location = 0) out vec4 A;

uniform sampler2D T;

void main() {
    A = texelFetch(T, ivec2(gl_FragCoord.xy), 0);
}

