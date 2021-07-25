#version 330 core 
layout (location = 0) in vec4 vertex; // 坐标+纹理

out vec2 TexCoords;

//因为是静态平面游戏，所以无需摄像坐标，且projection也不同
uniform mat4 model;
uniform mat4 projection;


void main(){
	TexCoords = vertex.zw;
	gl_Position = projection * model * vec4(vertex.xy,0.0,1.0);
}