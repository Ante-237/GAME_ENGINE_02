#include "Mesh.h"

void Mesh::setTriData(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices) {

	std::vector<Vertex> _vertices = {
		{ { 0.0f, -1.0f, 0.0f }, // Position
		  { 0.0f,  0.0f, 1.0f }, // Normal
		  { 1.0f,  0.0f, 0.0},   // Color
		  { 0.0 , 1.0 }			 // Texture Coordinate
		}, // First Vertex
		{
			{ 1.0f, 1.0f, 0.0f},
		    { 0.0f , 0.0f, 1.0},
		    { 0.0f, 1.0f, 0.0},
		    { 0.0, 0.0}
	    }, // Second Vertex

		{
			{ -1.0f, 1.0f, 0.0f },
		    { 0.0f, 0.0f, 1.0},
	        { 0.0f, 1.0f, 0.0},
		    { 1.0, 0.0},

		}, // Third Vertex

	};


	std::vector<uint32_t> _indices = {
		0 , 1 , 2,
	};

	vertices = _vertices;
	indices = _indices;
}
