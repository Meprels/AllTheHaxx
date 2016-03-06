const char *SOURCE_BLUR_FRAGMENT =

"#version 120\n"
"uniform vec2 u_Resolution;\n"
"uniform float u_IsTex;\n"
"uniform sampler2D u_Tex;\n"
"uniform vec2 u_Shift;\n"
"varying vec4 v_Color;\n"
"const int radius = 11;\n"
"float filter[radius] = float[radius] (0.0402,0.0623,0.0877,0.1120,0.1297,0.1362,0.1297,0.1120,0.0877,0.0623,0.0402);\n"
"void main(void)\n"
"{\n"
"	vec2 texCoord = gl_TexCoord[0].xy - float(int(radius/2)) * u_Shift;\n"
"	vec3 color = vec3(0.0, 0.0, 0.0);\n"
"	for(int i = 0; i < radius; i++)\n"
"	{\n"
"		color += filter[i] * texture2D(u_Tex, texCoord).xyz;\n"
"		texCoord += u_Shift;\n"
"	}\n"
"	gl_FragColor = vec4(color, 1.0);\n"
"}\n";