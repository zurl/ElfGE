#version 420 core
layout (points) in;
layout (triangle_strip, max_vertices = 6) out;

in vec3 _tone[];
in vec3 ori[];
in vec4 v[];
out vec2 TexCoord;
out vec3 tone;
uniform vec3 cameraPos;
uniform mat4 ortho;
uniform int width;
uniform int height;

void main()
{
    float _d = abs(distance(cameraPos,ori[0])); 
    float _t = (25-1.0) / (_d - 1.0);
    tone = _tone[0];
    vec4 tmp = vec4(width,height,0,0) * vec4(_t,_t,0,0) * ortho;
    float _x = tmp.x > 0 ? tmp.x : -tmp.x;
    float _y = tmp.y > 0 ? tmp.y : -tmp.y;
    float radis = atan(-v[0].x,v[0].y);
    mat4 trans = mat4(1.0);
    trans[0][0] = cos(radis);
    trans[0][1] = sin(radis);
    trans[1][0] = -sin(radis);
    trans[1][1] = cos(radis);
    gl_Position = gl_in[0].gl_Position + trans * vec4(-_x, -_y, 0.0, 0.0);
    TexCoord = vec2(0,0);
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + trans * vec4(_x, -_y, 0.0, 0.0);
    TexCoord = vec2(1,0);
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + trans * vec4(_x, _y, 0.0, 0.0);
    TexCoord = vec2(1,1);
    EmitVertex();
    EndPrimitive();

    gl_Position = gl_in[0].gl_Position + trans * vec4(_x, _y, 0.0, 0.0);
    TexCoord = vec2(1,1);
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + trans * vec4(-_x, _y, 0.0, 0.0);
    TexCoord = vec2(0,1);
    EmitVertex();
   
    gl_Position = gl_in[0].gl_Position + trans * vec4(-_x, -_y, 0.0, 0.0);
    TexCoord = vec2(0,0);
    EmitVertex();

    EndPrimitive();
}  
