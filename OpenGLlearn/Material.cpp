#include "Material.h"



Material::Material(glm::vec3 _diffuse, glm::vec3 _specular, float _Gloss, float _metallic, float _Smoothness)
	:diffuse(_diffuse),specular(_specular), gloss(_Gloss),metallic(_metallic),Smoothness(_Smoothness)
{

}


Material::~Material()
{
}
