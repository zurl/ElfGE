#version 330 core
// LICENSE: MIT
// Copyright (c) 2017 by Mike Linkovich


uniform sampler2D map;
uniform sampler2D heightMap;
uniform vec3 fogColor;
uniform float fogNear;
uniform float fogFar;
uniform float grassFogFar;

in vec2 vSamplePos;
in vec4 vColor;
in vec2 vUv;
out vec4 FragColor;

void main() {
///*
	vec4 color = vec4(vColor) * texture(map, vUv);
	vec4 hdata = texture(heightMap, vSamplePos);

	float depth = gl_FragCoord.z / gl_FragCoord.w;

	// make grass transparent as it approachs outer view distance perimeter
	color.a = 1.0 - smoothstep(grassFogFar * 0.55, grassFogFar * 0.8, depth);
//	color.a = 1.0;

	// apply terrain lightmap
	float light = hdata.g;
	color.r *= light;
	color.g *= light;
	color.b *= light;

	// then apply atmosphere fog
	float fogFactor = smoothstep(fogNear, fogFar, depth);
	color.rgb = mix(color.rgb, fogColor, fogFactor);
	// output
//	*/
	FragColor = color;
//	FragColor = vec4(1.0,1.0,1.0,1.0);
}
