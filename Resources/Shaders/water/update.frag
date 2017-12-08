#version 330 core
out vec4 FragColor;
    uniform sampler2D texture1;
    uniform vec2 delta;
    in vec2 coord;
    void main() {
      /* get vertex info */
      vec4 info = texture(texture1, coord);

      /* calculate average neighbor height */
      vec2 dx = vec2(delta.x, 0.0);
      vec2 dy = vec2(0.0, delta.y);
      float average = (
        texture(texture1, coord - dx).r +
        texture(texture1, coord - dy).r +
        texture(texture1, coord + dx).r +
        texture(texture1, coord + dy).r
      ) * 0.25;

      /* change the velocity to move toward the average */
      info.g += (average - info.r) * 2.0;

      /* attenuate the velocity a little so waves do not last forever */
      info.g *= 0.995;

      /* move the vertex along the velocity */
      info.r += info.g;

      FragColor = info;
//      FragColor = vec4(0.03,0,0,1);
    }
