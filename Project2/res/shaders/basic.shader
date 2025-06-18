#shader vertex
#version 330 core
layout (location=0) in vect4 position;

void main(){
	gl_Position=position;
};

#shader fragment
#version 330 core
layout (location=0) out vect4 color;

void main(){
	color=vect4(1.0,0.0,0.0,1.0);
};