#version 330 core

out vec4 FragColor;
// uniform vec3 color;

in vec2 TexCoords;
in vec3 WorldPos;
in vec3 Normal;

uniform vec3 camPos;

uniform vec3 albedo;
uniform float metallic;
uniform float roughness;
uniform float ao; // !!

uniform vec3 lightColors[4];
uniform vec3 lightPositions[4];

const float PI = 3.14159265359;

// highlighted spot sulla superficie sulla base
// della roughness
float DistributionGGX(vec3 N, vec3 H, float roughness){
	float a = roughness * roughness;
	float a2 = a*a;

	float NdotH  = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;
	
    float num   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;
	
    return num / denom; 

}

vec3 fresnelSchlick(float cosTheta, vec3 F0){
	return F0 + (1.0-F0)*pow((clamp(1.0-cosTheta, 0.0, 1.0)), 5.0);
}

float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float num   = NdotV;
    float denom = NdotV * (1.0 - k) + k;
	
    return num / denom;
}
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2  = GeometrySchlickGGX(NdotV, roughness);
    float ggx1  = GeometrySchlickGGX(NdotL, roughness);
	
    return ggx1 * ggx2;
}

void main(){

	// FragColor = vec4(1, 1, 1, 1.0);
	
	vec3 Lo;
	vec3 F0 = vec3(0.04);
	F0 = mix(F0, albedo, metallic);

	for(int i = 0; i < 4; i++){
		// calcolare la quantità di energia percepita
		// dalla superficie/frammento
		vec3 N = normalize(Normal);
		vec3 L = normalize(lightPositions[i] - WorldPos);
		float dist = length(lightPositions[i] - WorldPos);
		float attenuation = 1.0/(dist * dist); // attenuazione fisicamente corretta
		vec3 radiance = lightColors[i] * attenuation;

		// teoria delle microfaces
		
		vec3 V = normalize(camPos - WorldPos);
		vec3 H = normalize(L+V);

		vec3 F = fresnelSchlick(max(dot(H, V), 0.0), F0);
		float D = DistributionGGX(N, H, roughness);
		float G   = GeometrySmith(N, V, L, roughness);      

		vec3 num = D*G*F;
		float den = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0)  + 0.0001;
		vec3 specular = num / den;  

		vec3 kS = F;
		vec3 kD = vec3(1.0) - kS;

		// se il materiale è metallico, allora non abbiamo alcun fattore di rifrazione
		kD *= (1.0 - metallic);
		float NdotL = max(dot(N, L), 0.0);   
		Lo += (kD * albedo / PI + specular)  * radiance * NdotL;
	}

	FragColor = vec4(Lo, 1.0);
	
}