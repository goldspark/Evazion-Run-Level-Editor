#pragma once
#include <string>

//ONLY FOR SHADER CODES!

std::string vertexShader =
R"(#version 300 core
layout(location = 0) in vec3 vPos;
layout(location = 1) in vec4 vColor;
layout(location = 2) in vec2 vTexture;
layout(location = 3) in float vIndex;

out vec2 fTexture;
out vec3 fColor;
out float fIndex;

uniform mat4 u_MVP = mat4(1.0);

void main()
{
	gl_Position = u_MVP * vec4(vPos, 1.0f);

    fIndex = vIndex;
    fTexture = vTexture;
    fColor = vColor;
}

)";


std::string fragmentShader = 
R"(#version 300 

out vec4 oColor;

out vec2 fTexture;
out vec4 fColor;
out float fIndex;

uniform sampler2D tex[8];

void main(){

 int index = int(fTexId);
    switch(index){
        case 0:
        color = fColor;
        break;
        case 1:
        color = texture(tex[0], fTexture) * fColor;
        break;
        case 2:
        color = texture(tex[1], fTexture) * fColor;
        break;
        case 3:
        color = texture(tex[2], fTexture) * fColor;
        break;
        case 4:
        color = texture(tex[3], fTexture) * fColor;
        break;
        case 5:
        color = texture(tex[4], fTexture) * fColor;
        break;
        case 6:
        color = texture(tex[5], fTexture) * fColor;
        break;
        case 7:
        color = texture(tex[6], fTexture) * fColor;
        break;
        case 8:
        color = texture(tex[7], fTexture) * fColor;
        break;
        default:
        break;
    }

}

)";

