#version 330

in vec2 uv;
layout(location = 0) out vec4 color;
//layout(location = 1) out vec3 normal;


uniform sampler2D renderedTexture;
uniform sampler2D normalTexture;
uniform sampler2D positionTexture;
uniform sampler2D depthTexture;
uniform sampler1D bounceTexture;

uniform int displayMode;
uniform int bounceLightCount;
uniform vec2 screen;

float LinearizeDepth(vec2 uv)
{
  float n = 1.0; // camera z near
  float f = 2000.0; // camera z far
  float z = texture2D(depthTexture, uv).x;
  return 1 - ((2.0 * n) / (f + n - z * (f - n)));
}


void main(){
	float d = LinearizeDepth(uv);
	
	if(displayMode == 1){
		if(uv.x < 0.5 && uv.y > 0.5){
			color = texture2D(renderedTexture,uv*2);
		}else if(uv.x > 0.5 && uv.y > 0.5){
			color = texture2D(normalTexture,uv*2);
		
		}else if(uv.x < 0.5 && uv.y < 0.5){
			color = texture2D(positionTexture,uv*2);
		}else{
			color = texture2D(renderedTexture,uv*2);
			float hsv =  max(color.r , color.g );
			hsv = max(hsv,color.b);
			
			color = vec4(hsv * hsv*6,hsv,hsv/(hsv*6),1.0);

		}
	}else if(displayMode == 2){
		color = texture2D(renderedTexture,uv);
	}else{
	
		vec3 px_color = texture2D(renderedTexture,uv).rgb;
		vec3 px_normal = texture2D(normalTexture,uv).rgb*2-1;
		vec3 px_position = texture2D(positionTexture,uv).rgb;
		vec3 rad_color = vec3(0,0,0);
		
		float size = bounceLightCount*3;
		for(int i = 0; i < size; i+=3){
			vec3 gi_position = texelFetch(bounceTexture,i,0).rgb;
			
			
			
			
			
			
			vec3 ray = normalize(gi_position - px_position);
			float face = dot(ray,px_normal);

			
			if(face > 0){
				float phi = dot(texelFetch(bounceTexture,i+1,0).rgb,ray);
				if(phi < 0){
					vec3 gi_color = texelFetch(bounceTexture,i+2,0).rgb;
					
					float brightnes = 0.0f;
					brightnes -= phi /3;
					brightnes *= face;
					brightnes /= 8 / (gi_color.r + gi_color.g + gi_color.b) * pow(length(gi_position - px_position)*8,2);

					// Todo		Material farbe
					rad_color += gi_color * brightnes;
					//px_color += 100;
				}
			}

		}
		// todo multiply pixel color
		px_color += rad_color;
		// test
		//vec3 test_color = texelFetch(bounceTexture,int(gl_FragCoord.x/4),0).rgb;
		//test_color += 1;
		//test_color /= 2;
		//color = vec4(test_color,1.0);
		color = vec4(px_color,1.0);

		
	}
}
