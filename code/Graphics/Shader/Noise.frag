#version 330 core

in vec2 texcoord;
in vec4 color;

uniform sampler2D Texture0;

uniform float persistence;
uniform float octaves;
uniform float offset;
uniform float stride;

vec2 hash22( vec2 p )  
{  
    p = vec2(dot(p,vec2(127.1,311.7)), dot(p,vec2(269.5,183.3)));  
  
    return -1.0 + 2.0 * fract(sin(p) * 43758.5453123);  
}  
  
float hash21(vec2 p)  
{  
    return fract(sin(dot(p, vec2(12.9898, 78.233))) * 43758.5453);  
} 

vec3 hash33( vec3 p )
{
	p = vec3(dot(p,vec3(12.98,78.23, 98.25)), dot(p,vec3(127.1,311.7, 412.8)), dot(p,vec3(269.5,183.3, 201.5)));
	
	return -1.0 + 2.0 * fract(sin(p) * 43758.5453123);  
}

float noise( in vec2 p )  
{  
    vec2 i = floor( p );  
    vec2 f = fract( p );  

    vec2 u = f*f*f*(6.0*f*f - 15.0*f + 10.0);  
  
    return mix( mix( dot( hash22( i + vec2(0.0,0.0) ), f - vec2(0.0,0.0) ),   
                     dot( hash22( i + vec2(1.0,0.0) ), f - vec2(1.0,0.0) ), u.x),  
                mix( dot( hash22( i + vec2(0.0,1.0) ), f - vec2(0.0,1.0) ),   
                     dot( hash22( i + vec2(1.0,1.0) ), f - vec2(1.0,1.0) ), u.x), u.y);  
} 

// 3D 柏林噪声
float perlin_noise_3d(vec3 p)
{
	vec3 i = floor(p);
	vec3 f = fract(p);
	
	vec3 u = f * f * f * (6.0 * f * f - 15.0 * f + 10);
	
	float z0 = mix( mix( dot(hash33(i + vec3(0, 0, 0)), f - vec3(0, 0, 0)),
						 dot(hash33(i + vec3(1, 0, 0)), f - vec3(1, 0, 0)), u.x),
					mix( dot(hash33(i + vec3(0, 1, 0)), f - vec3(0, 1, 0)),
						 dot(hash33(i + vec3(1, 1, 0)), f - vec3(1, 1, 0)), u.x), u.y);
						 
	float z1 = mix( mix( dot(hash33(i + vec3(0, 0, 1)), f - vec3(0, 0, 1)),
						 dot(hash33(i + vec3(1, 0, 1)), f - vec3(1, 0, 1)), u.x),
					mix( dot(hash33(i + vec3(0, 1, 1)), f - vec3(0, 1, 1)),
						 dot(hash33(i + vec3(1, 1, 1)), f - vec3(1, 1, 1)), u.x), u.y);
						 
	return mix(z0, z1, u.z);
}

float noise_fractal(in vec2 p)  
{  
    p *= 5.0;  
    mat2 m = mat2( 1.6,  1.2, -1.2,  1.6 );  
    float f  = 0.5000*noise(p); p = m*p;  
    f += 0.2500*noise(p); p = m*p;  
    f += 0.1250*noise(p); p = m*p;  
    f += 0.0625*noise(p); p = m*p;  
      
    return f;  
} 

float noise_sum_abs(vec2 p)  
{  
    float f = 0.0;  
    p = p * 7.0;  
    f += 1.0000 * abs(noise(p)); p = 2.0 * p;  
    f += 0.5000 * abs(noise(p)); p = 2.0 * p;  
    f += 0.2500 * abs(noise(p)); p = 2.0 * p;  
    f += 0.1250 * abs(noise(p)); p = 2.0 * p;  
    f += 0.0625 * abs(noise(p)); p = 2.0 * p;  
  
    return f;  
} 

float value_noise(vec2 p)  
{  
    p *= 56.0;  
    vec2 pi = floor(p);  
    vec2 pf = fract(p);  
  
    vec2 w = pf * pf * (3.0 - 2.0 * pf);  
    
    return mix(mix(hash21(pi + vec2(0.0, 0.0)), hash21(pi + vec2(1.0, 0.0)), w.x),  
              mix(hash21(pi + vec2(0.0, 1.0)), hash21(pi + vec2(1.0, 1.0)), w.x),  
              w.y);  
} 

float simplex_noise(vec2 p)  
{  
    const float K1 = 0.366025404; // (sqrt(3)-1)/2;  
    const float K2 = 0.211324865; // (3-sqrt(3))/6;  
    // 变换到新网格的(0, 0)点  
    vec2 i = floor(p + (p.x + p.y) * K1);  
    // i - (i.x+i.y)*K2换算到旧网格点  
    // a:变形前输入点p到该网格点的距离  
    vec2 a = p - (i - (i.x + i.y) * K2);  
    vec2 o = (a.x < a.y) ? vec2(0.0, 1.0) : vec2(1.0, 0.0);  
    // 新网格(1.0, 0.0)或(0.0, 1.0)  
    // b = p - (i+o - (i.x + i.y + 1.0)*K2);  
    vec2 b = a - o + K2;  
    // 新网格(1.0, 1.0)  
    // c = p - (i+vec2(1.0, 1.0) - (i.x+1.0 + i.y+1.0)*K2);  
    vec2 c = a - 1.0 + 2.0 * K2;  
    // 计算每个顶点的权重向量，r^2 = 0.5  
    vec3 h = max(0.5 - vec3(dot(a, a), dot(b, b), dot(c, c)), 0.0);  
    // 每个顶点的梯度向量和距离向量的点乘，然后再乘上权重向量  
    vec3 n = h * h * h * h * vec3(dot(a, hash22(i)), dot(b, hash22(i + o)), dot(c, hash22(i + 1.0)));  
      
    // 之所以乘上70，是在计算了n每个分量的和的最大值以后得出的，这样才能保证将n各个分量相加以后的结果在[-1, 1]之间  
    return dot(vec3(70.0, 70.0, 70.0), n);  
} 

float AddNoise(vec2 p)
{
	float total = 0;
	for(int i = 0; i < octaves; i++){
		float frequency = pow(2, i);
		float amplitude = pow(persistence, i);
		total += noise(p * frequency) * amplitude;
	}
	return total;
}

float AddNoise(vec3 p)
{
	float total = 0;
	for(int i = 0; i < octaves; i++){
		float frequency = pow(2, i);
		float amplitude = pow(persistence, i);
		total += perlin_noise_3d(p * frequency) * amplitude;
	}
	return total;
}

void main()
{
	

	float f = AddNoise((texcoord + vec2(offset, -offset)) * stride);
	
	f = (f + 1) * 0.5;
	
	float f2 = AddNoise((texcoord) * 50);
	
	f2 = (f2 + 1) * 0.5;
	
	vec2 oo = vec2(f, f2);
	
	vec4 tex_color = texture(Texture0, texcoord + oo * 0.05 - 0.025) * color;
	//vec4 tex_color = texture(Texture0, texcoord) * color;
	
	vec4 tex_color1 = vec4(0, 0.8, 0.4, 1);
	tex_color1.a = 1 - tex_color.b;
	
	gl_FragColor = tex_color1;
	
	//gl_FragColor = vec4(f, f, f, 1);
}














