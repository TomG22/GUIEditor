#include <utility>

#include "Mesh.h"

Mesh::Mesh(VertexArray* va, VertexBuffer* vb, IndexBuffer* ib)
    : va(va), vb(vb), ib(ib) {
    printf("[Mesh] vb constructed: %p\n", vb);
}

void Mesh::UpdateVertices(const void* data, unsigned int size, unsigned int offset) {
    vb->UpdateData(data, size, offset);
}

/*
const VertexArray& Mesh::GetVertexArray() const {
    return *va;
}

const IndexBuffer& Mesh::GetIndexBuffer() const {
    return *ib;
}
*/

/*
void Mesh::Draw(Shader& shader,
				Camera& camera,
				glm::mat4 uMatrix,
				glm::vec3 translation,
				glm::quat rotation,
				glm::vec3 scale) {
	va.Bind();
	ib.Bind();
	shader.Bind();

	unsigned int numDiffuse = 0;
	unsigned int numSpecular = 0;

	for (unsigned int i = 0; i < textures.size(); i++) {
		std::string num;
		std::string type = textures[i].type;
		if (type == "diffuse") {
			num = std::to_string(numDiffuse++);
		} else if (type == "specular") {
			num = std::to_string(numSpecular++);
		}
		textures[i].bindTexUnit(shader, (type + num).c_str(), i);
	}
	glUniform3f(shader.GetUniformLocation("u_CamPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	camera.Matrix(shader, "u_CamMatrix");

	glm::mat4 uTranslation = glm::mat4(1.0f);
	glm::mat4 uRotation = glm::mat4(1.0f);
	glm::mat4 uScale = glm::mat4(1.0f);

	uTranslation = glm::translate(uTranslation, translation);
	uRotation = glm::mat4_cast(rotation);
	uScale = glm::scale(uScale, scale);

	shader.SetUniformMat4f("u_Translation", uTranslation);
	shader.SetUniformMat4f("u_Rotation", uRotation);
	shader.SetUniformMat4f("u_Scale", uScale);
	shader.SetUniformMat4f("u_Model", uMatrix);

	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, 0);
}
*/
