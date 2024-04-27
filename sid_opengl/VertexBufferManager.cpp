#include"VertexBufferManager.h"
#include<glad/glad.h>
VertexBufferManager::VertexBufferManager(std::vector<Vertex>* vertexBufferPtr, std::vector<int>* indexBufferPtr)
{
	m_vertexBufferData = vertexBufferPtr;

    // Ensure the pointer is not null before proceeding
    if (m_vertexBufferData != nullptr) {
        // Iterate through the vertex data and push it into the vector
        for (const auto& vertex : *m_vertexBufferData) {

            m_reformattedVertexBufferData.push_back(vertex.x);
            m_reformattedVertexBufferData.push_back(vertex.y);
            m_reformattedVertexBufferData.push_back(vertex.z);

            m_reformattedVertexBufferData.push_back(vertex.r);
            m_reformattedVertexBufferData.push_back(vertex.g);
            m_reformattedVertexBufferData.push_back(vertex.b);
        }
    }

    m_vaoBuffer = new VAO();
    m_vertexBuffer = new VBO(m_reformattedVertexBufferData.data(), m_reformattedVertexBufferData.size()*sizeof(float));
   

    int offset = 0;
    int layout = 0;
    int num_ele = 3;
    int total_num_ele = 6;
    glVertexAttribPointer(layout, num_ele, GL_FLOAT, GL_FALSE, total_num_ele * sizeof(float), (void*)(offset * sizeof(float))); //slot 0 if for vertices
    glEnableVertexAttribArray(0);


    layout = 1;
    offset = 3;
    glVertexAttribPointer(layout, num_ele, GL_FLOAT, GL_FALSE, total_num_ele * sizeof(float), (void*)(offset * sizeof(float))); //slot 0 if for vertices
    glEnableVertexAttribArray(1);

    m_indexBuffer = new EBO(indexBufferPtr->data(), (int)indexBufferPtr->size()*sizeof(int));

    m_vaoBuffer->Unbind();
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    m_vertexBuffer->Unbind();
    m_indexBuffer->Unbind();



}

int VertexBufferManager::BuildVertexBuffer()
{
    return 0;
}

VBO* VertexBufferManager::getVertexBuffer()
{
    return m_vertexBuffer;
}

EBO* VertexBufferManager::getIndexBuffer()
{
    return m_indexBuffer;
}

VAO* VertexBufferManager::getVAOBuffer()
{
    return m_vaoBuffer;
}