#include "Cube.h"

Cube::Cube()
{
	m_center = glm::vec3(0.0f);
	m_halfSide = 0.5f;
	m_color = glm::vec3(1.0f);
	Cube::fillBuffers();
	glGenVertexArrays(1, &VertexArray);
	glBindVertexArray(VertexArray);

	glGenBuffers(3, VertexBuffer);

	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer[0]);
	glBufferData(GL_ARRAY_BUFFER, 3 * _points * sizeof(GL_FLOAT), &_v[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer[1]);
	glBufferData(GL_ARRAY_BUFFER, 3 * _points * sizeof(GL_FLOAT), &_n[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer[2]);
	glBufferData(GL_ARRAY_BUFFER, 3 * _points * sizeof(GL_FLOAT), &_c[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glGenBuffers(1, &IndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices * sizeof(GL_UNSIGNED_INT), &_index[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Cube::Cube(glm::vec3 center, float sideLength, glm::vec3 color)
{
	m_center = center;
	m_halfSide = sideLength/2.0f;
	m_color = color;
	Cube::fillBuffers();
	glGenVertexArrays(1, &VertexArray);
	glBindVertexArray(VertexArray);

	glGenBuffers(3, VertexBuffer);

	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer[0]);
	glBufferData(GL_ARRAY_BUFFER, 3 * _points * sizeof(GL_FLOAT), &_v[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer[1]);
	glBufferData(GL_ARRAY_BUFFER, 3 * _points * sizeof(GL_FLOAT), &_n[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer[2]);
	glBufferData(GL_ARRAY_BUFFER, 3 * _points * sizeof(GL_FLOAT), &_c[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glGenBuffers(1, &IndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices * sizeof(GL_UNSIGNED_INT), &_index[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


Cube::~Cube()
{
}

void Cube::fillBuffers(){
	_v[0]  = m_center.x - m_halfSide; _v[1]  = m_center.y + m_halfSide; _v[2]  = m_center.z + m_halfSide;  _v[3]  = m_center.x - m_halfSide; _v[4]  = m_center.y - m_halfSide; _v[5]  = m_center.z + m_halfSide; _v[6]  = m_center.x + m_halfSide; _v[7]  = m_center.y - m_halfSide; _v[8]  = m_center.z + m_halfSide; _v[9]  = m_center.x + m_halfSide; _v[10] = m_center.y + m_halfSide; _v[11] = m_center.z + m_halfSide;
	_v[12] = m_center.x - m_halfSide; _v[13] = m_center.y + m_halfSide; _v[14] = m_center.z - m_halfSide;  _v[15] = m_center.x - m_halfSide; _v[16] = m_center.y - m_halfSide; _v[17] = m_center.z - m_halfSide; _v[18] = m_center.x - m_halfSide; _v[19] = m_center.y - m_halfSide; _v[20] = m_center.z + m_halfSide; _v[21] = m_center.x - m_halfSide; _v[22] = m_center.y + m_halfSide; _v[23] = m_center.z + m_halfSide;
	_v[24] = m_center.x + m_halfSide; _v[25] = m_center.y + m_halfSide; _v[26] = m_center.z + m_halfSide;  _v[27] = m_center.x + m_halfSide; _v[28] = m_center.y - m_halfSide; _v[29] = m_center.z + m_halfSide; _v[30] = m_center.x + m_halfSide; _v[31] = m_center.y - m_halfSide; _v[32] = m_center.z - m_halfSide; _v[33] = m_center.x + m_halfSide; _v[34] = m_center.y + m_halfSide; _v[35] = m_center.z - m_halfSide;
	_v[36] = m_center.x - m_halfSide; _v[37] = m_center.y + m_halfSide; _v[38] = m_center.z - m_halfSide;  _v[39] = m_center.x - m_halfSide; _v[40] = m_center.y + m_halfSide; _v[41] = m_center.z + m_halfSide; _v[42] = m_center.x + m_halfSide; _v[43] = m_center.y + m_halfSide; _v[44] = m_center.z + m_halfSide; _v[45] = m_center.x + m_halfSide; _v[46] = m_center.y + m_halfSide; _v[47] = m_center.z - m_halfSide;
	_v[48] = m_center.x - m_halfSide; _v[49] = m_center.y - m_halfSide; _v[50] = m_center.z + m_halfSide;  _v[51] = m_center.x - m_halfSide; _v[52] = m_center.y - m_halfSide; _v[53] = m_center.z - m_halfSide; _v[54] = m_center.x + m_halfSide; _v[55] = m_center.y - m_halfSide; _v[56] = m_center.z - m_halfSide; _v[57] = m_center.x + m_halfSide; _v[58] = m_center.y - m_halfSide; _v[59] = m_center.z + m_halfSide;
	_v[60] = m_center.x + m_halfSide; _v[61] = m_center.y + m_halfSide; _v[62] = m_center.z - m_halfSide;  _v[63] = m_center.x + m_halfSide; _v[64] = m_center.y - m_halfSide; _v[65] = m_center.z - m_halfSide; _v[66] = m_center.x - m_halfSide; _v[67] = m_center.y - m_halfSide; _v[68] = m_center.z - m_halfSide; _v[69] = m_center.x - m_halfSide; _v[70] = m_center.y + m_halfSide; _v[71] = m_center.z - m_halfSide;

	_n[0]  =  0.0f; _n[1]  =  0.0f; _n[2]  =  1.0f; _n[3]  =  0.0f; _n[4]  =  0.0f; _n[5]  =  1.0f; _n[6]  =  0.0f; _n[7]  =  0.0f; _n[8]  =  1.0f; _n[9]  =  0.0f; _n[10] =  0.0f; _n[11] =  1.0f;
	_n[12] = -1.0f; _n[13] =  0.0f; _n[14] =  0.0f; _n[15] = -1.0f; _n[16] =  0.0f; _n[17] =  0.0f; _n[18] = -1.0f; _n[19] =  0.0f; _n[20] =  0.0f; _n[21] = -1.0f; _n[22] =  0.0f; _n[23] =  0.0f;
	_n[24] =  1.0f; _n[25] =  0.0f; _n[26] =  0.0f; _n[27] =  1.0f; _n[28] =  0.0f; _n[29] =  0.0f; _n[30] =  1.0f; _n[31] =  0.0f; _n[32] =  0.0f; _n[33] =  1.0f; _n[34] =  0.0f; _n[35] =  0.0f;
	_n[36] =  0.0f; _n[37] =  1.0f; _n[38] =  0.0f; _n[39] =  0.0f; _n[40] =  1.0f; _n[41] =  0.0f; _n[42] =  0.0f; _n[43] =  1.0f; _n[44] =  0.0f; _n[45] =  0.0f; _n[46] =  1.0f; _n[47] =  0.0f;
	_n[48] =  0.0f; _n[49] = -1.0f; _n[50] =  0.0f; _n[51] =  0.0f; _n[52] = -1.0f; _n[53] =  0.0f; _n[54] =  0.0f; _n[55] = -1.0f; _n[56] =  0.0f; _n[57] =  0.0f; _n[58] = -1.0f; _n[59] =  0.0f;
	_n[60] =  0.0f; _n[61] =  0.0f; _n[62] = -1.0f; _n[63] =  0.0f; _n[64] =  0.0f; _n[65] = -1.0f; _n[66] =  0.0f; _n[67] =  0.0f; _n[68] = -1.0f; _n[69] =  0.0f; _n[70] =  0.0f; _n[71] = -1.0f;

	_c[0]  = m_color.x; _c[1]  = m_color.y; _c[2]  = m_color.z; _c[3]  = m_color.x; _c[4]  = m_color.y; _c[5]  = m_color.z; _c[6]  = m_color.x; _c[7]  = m_color.y; _c[8]  = m_color.z; _c[9]  = m_color.x; _c[10] = m_color.y; _c[11] = m_color.z;
	_c[12] = m_color.x; _c[13] = m_color.y; _c[14] = m_color.z; _c[15] = m_color.x; _c[16] = m_color.y; _c[17] = m_color.z; _c[18] = m_color.x; _c[19] = m_color.y; _c[20] = m_color.z; _c[21] = m_color.x; _c[22] = m_color.y; _c[23] = m_color.z;
	_c[24] = m_color.x; _c[25] = m_color.y; _c[26] = m_color.z; _c[27] = m_color.x; _c[28] = m_color.y; _c[29] = m_color.z; _c[30] = m_color.x; _c[31] = m_color.y; _c[32] = m_color.z; _c[33] = m_color.x; _c[34] = m_color.y; _c[35] = m_color.z;
	_c[36] = m_color.x; _c[37] = m_color.y; _c[38] = m_color.z; _c[39] = m_color.x; _c[40] = m_color.y; _c[41] = m_color.z; _c[42] = m_color.x; _c[43] = m_color.y; _c[44] = m_color.z; _c[45] = m_color.x; _c[46] = m_color.y; _c[47] = m_color.z;
	_c[48] = m_color.x; _c[49] = m_color.y; _c[50] = m_color.z; _c[51] = m_color.x; _c[52] = m_color.y; _c[53] = m_color.z; _c[54] = m_color.x; _c[55] = m_color.y; _c[56] = m_color.z; _c[57] = m_color.x; _c[58] = m_color.y; _c[59] = m_color.z;
	_c[60] = m_color.x; _c[61] = m_color.y; _c[62] = m_color.z; _c[63] = m_color.x; _c[64] = m_color.y; _c[65] = m_color.z; _c[66] = m_color.x; _c[67] = m_color.y; _c[68] = m_color.z; _c[69] = m_color.x; _c[70] = m_color.y; _c[71] = m_color.z;

	_index[0] = 0; 	 _index[1] = 1;   _index[2] = 2;   _index[3] = 0;   _index[4] = 2;   _index[5] = 3;
	_index[6] = 4; 	 _index[7] = 5;   _index[8] = 6;   _index[9] = 4;   _index[10] = 6;  _index[11] = 7;
	_index[12] = 8;  _index[13] = 9;  _index[14] = 10; _index[15] = 8;  _index[16] = 10; _index[17] = 11;
	_index[18] = 12; _index[19] = 13; _index[20] = 14; _index[21] = 12; _index[22] = 14; _index[23] = 15;
	_index[24] = 16; _index[25] = 17; _index[26] = 18; _index[27] = 16; _index[28] = 18; _index[29] = 19;
	_index[30] = 20; _index[31] = 21; _index[32] = 22; _index[33] = 20; _index[34] = 22; _index[35] = 23;
}

void Cube::render() 
{
	glBindVertexArray(VertexArray);
	glDrawElements(GL_TRIANGLES, _indices, GL_UNSIGNED_INT, 0);
}
