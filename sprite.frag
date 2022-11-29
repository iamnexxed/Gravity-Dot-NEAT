
#version 330 core
out vec4 FragColor;

// inputs the color from vertex shader
// must have same name as in the vertex shader
in vec3 color;

void main()
{
	FragColor = vec4(color,1.0);
	//FragColor = rDirectionalLight();
	//FragColor = vec4(currentPos, 1.0);
	// FragColor = texture(diffuse0, texCoord) * (diffuse + ambient) * lightColor;
}
