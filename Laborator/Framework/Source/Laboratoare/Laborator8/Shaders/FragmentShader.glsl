#version 330

// TODO: get color value from vertex shader
in vec3 world_position;
in vec3 world_normal;

// Uniforms for light properties
uniform vec3 light_direction;
uniform vec3 light_position;
uniform vec3 eye_position;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

uniform int is_spot;
uniform float cut_off_angle;

uniform vec3 object_color;

layout(location = 0) out vec4 out_color;

void main()
{
	vec3 N = normalize(world_normal);
	vec3 L = normalize(light_position - world_position);
	vec3 V = normalize(eye_position - world_position);
	vec3 H = normalize(L + V);

	// define ambient light component
	float ambient_light = material_kd * 0.25;

	// compute diffuse light component
	float light_intensity = 1.5;
	float diffuse_light = material_kd * light_intensity * max(dot(N, L), 0);

	// compute specular light component
	float specular_light = 0;

	if (diffuse_light > 0)
	{
		specular_light = material_ks * light_intensity * pow(max(dot(N, H), 0), material_shininess);
	}

	// compute light
	float light;
	if (is_spot == 0) {
		float d = distance(light_position, world_position);
		float attenuation_factor = 1 / (d * d + 1);
		light	= ambient_light + attenuation_factor * (diffuse_light + specular_light);
	} else {
		float cut_off = radians(cut_off_angle);
		float spot_light = dot(-L, light_direction);
		float spot_light_limit = cos(cut_off);
		if (spot_light > spot_light_limit) {
			// Quadratic attenuation
			float linear_att = (spot_light - spot_light_limit) / (1 - spot_light_limit);
			float light_att_factor = pow(linear_att, 2);
			light	= ambient_light + light_att_factor * (diffuse_light + specular_light);
		} else {
			light = ambient_light;
		}
	}

	// write pixel out color
	vec3 color = object_color * light;
	out_color = vec4(color, 1);
}