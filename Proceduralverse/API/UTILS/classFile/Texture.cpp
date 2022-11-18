#include <Texture.h>
#include <iostream>
#include <GLEW/Include/GL/glew.h>
#include <STB_IMAGE/Include/stb_image.h>


Texture::Texture(const char* fileName)
{
	/*I set the view option (Repeat, Clamp border, ecc...) of each axe (S and T -> U and V)
	 * Target: specify the type of texture, we have a 2D texture so we put GL_TEXTURE_2D*/
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	/*I set the filter for magnifying and minifying*/
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	/*I load the texture, the weight, height and number of channels are overwritten in
	 *'width', 'height' and 'NOChannels' vars*/
	int width, height, NOChannels;
	unsigned char* data = stbi_load(fileName, &width, &height, &NOChannels, 0);

	if(data)
	{
		//Like any of the previous objects in OpenGL, textures are referenced with an ID
		unsigned int textureID;
		glGenTextures(1, &textureID);
		//We bind the texture obj with GL_TEXTURE_2D
		glBindTexture(GL_TEXTURE_2D, textureID);
		/*Specify the settings for the two-dimensional texture loaded before
		 *level: indicates the LoD used for the texture
		 *internalFormat: specifies the number of color components in the texture
		 *format: specifies the format of the pixel data
		 *border: this value must be 0
		 *type: the type of data
		 */
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		//This will automatically generate all the required mipmaps for the currently bound texture
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_set_flip_vertically_on_load(true);

	}
	else
	{
		std::cout << "Failed to load texture" << "\n";
	}
	stbi_image_free(data);
	
}