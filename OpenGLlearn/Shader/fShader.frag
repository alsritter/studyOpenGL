#version 330 core
out vec4 FragColor;
in vec2 TexCoord;
uniform sampler2D Texture1;
uniform sampler2D Texture2;

void main()
{
	//linearly interpolate between two values(mix函数:两个值之间的线性插值)
    FragColor = mix(texture(Texture1,TexCoord) , texture(Texture2,TexCoord) ,0.2);
}
