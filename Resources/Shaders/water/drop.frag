#version 330 core
out vec4 FragColor;
    const float PI = 3.141592653589793;
    uniform sampler2D texture1;
    uniform vec2 center;
    uniform float radius;
    uniform float strength;
    in vec2 coord;
    void main() {
      /* get vertex info */
      vec4 info = texture(texture1, coord);

      /* add the drop to the height */
      float drop = max(0.0, 1.0 - length(center * 0.5 + 0.5 - coord) / radius);
      drop = 0.5 - cos(drop * PI) * 0.5;
      info.r += drop * strength;

      FragColor = info;
//      FragColor = vec4(0.03,0,1,1);
    }
