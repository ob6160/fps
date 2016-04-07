#version 330 core
in vec4 TexCoord;

out vec4 color;

uniform sampler2D ourTexture;

void main()
{
  //  color = texture(ourTexture, TexCoord) * vec4(1.0);

     if(TexCoord.w < 0)
        color = texture(ourTexture, vec2((fract(TexCoord.x) + TexCoord.w) / 32.0, TexCoord.z));
      else
        color = texture(ourTexture, vec2((fract(TexCoord.x + TexCoord.z) + TexCoord.w) / 32.0, TexCoord.y));
}