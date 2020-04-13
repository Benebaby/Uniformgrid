#version 330 core

in vec3 passPosition;
in vec3 passNormal;
in vec3 passColor;

uniform mat4 viewMatrix;
uniform vec3 light_ambient;


uniform vec3 mat_diffuse;
uniform vec3 mat_specular;
uniform float mat_shininess;

uniform vec4 light_pos;
uniform vec3 light_col;

out vec4 fragmentColor;

void main(){
	vec3 normal = normalize(passNormal);
	vec3 lightVector;
	// Diffuse
	vec3 light_camcoord = (viewMatrix * light_pos).xyz;
	if (light_pos.w > 0.001f)
		lightVector = normalize( light_camcoord - passPosition);
	else
		lightVector = normalize(light_camcoord);
	float cos_phis = dot( normal, lightVector);
	float cos_phi = max(cos_phis, 0.0);
	// Specular
	vec3 eye = normalize( -passPosition);
	vec3 reflection = normalize( reflect( -lightVector, normal));
	float cos_psi_n = pow( max( dot( reflection, eye), 0.0f), mat_shininess);

	fragmentColor = vec4(passColor * light_ambient + (passColor * cos_phi + mat_specular * cos_psi_n) * light_col, 1.0f);
}