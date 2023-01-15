#include "Resources/Mesh.hpp"
#include "Core/Debug/Debug.hpp"


#include <glad/glad.h>
#include <GLFW/glfw3.h>

Resources::Mesh::Mesh()
{

}
bool Resources::Vertex::operator==(const Vertex& v)
{
    return(position == v.position) && (textureUV == v.textureUV) && (normal == v.normal);
}

void Resources::Mesh::Create(const char* name)
{
    ASSERT(true);
}

void Resources::Mesh::Draw()
{
    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glDrawElements(GL_TRIANGLES, (GLsizei)d_Index.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Resources::Mesh::Delete()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}