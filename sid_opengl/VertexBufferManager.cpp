#include"VertexBufferManager.h"
#include<glad/glad.h>
#include"glm/gtc/matrix_transform.hpp"
#include"glm/gtc/type_ptr.hpp"

VertexBufferManager::VertexBufferManager(std::vector<Vertex2D>* const vertexBufferPtr, std::vector<int>* const indexBufferPtr)
{

    m_vertex2DBufferData = vertexBufferPtr;

    // Ensure the pointer is not null before proceeding
    if (m_vertex2DBufferData != nullptr) {
        // Iterate through the vertex data and push it into the vector
        for (const auto& vertex : *m_vertex2DBufferData) {

            m_reformattedVertexBufferData.push_back(vertex.x);
            m_reformattedVertexBufferData.push_back(vertex.y);

        }
    }

    m_vaoBuffer = new VAO();
    m_vertexBuffer = new VBO(m_reformattedVertexBufferData.data(), m_reformattedVertexBufferData.size() * sizeof(float));


    int offset = 0;
    int layout = 0;
    int num_ele = 2;
    int total_num_ele = 2;
    glVertexAttribPointer(layout, num_ele, GL_FLOAT, GL_FALSE, total_num_ele * sizeof(float), (void*)(offset * sizeof(float)));
    glEnableVertexAttribArray(0);


    m_indexBuffer = new EBO(indexBufferPtr->data(), (int)indexBufferPtr->size() * sizeof(int));


    m_vaoBuffer->Unbind();
    glEnableVertexAttribArray(0);

    m_vertexBuffer->Unbind();
    m_indexBuffer->Unbind();
}

VertexBufferManager::VertexBufferManager(std::vector<Vertex>* const vertexBufferPtr, std::vector<int>* const indexBufferPtr, const Location& loc, const bool& hasTextures, const std::string& texture_path)
{

    mLoc = loc;
    mHasTextures = hasTextures;
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

            m_reformattedVertexBufferData.push_back(vertex.s);
            m_reformattedVertexBufferData.push_back(vertex.t);
        }
    }

    m_vaoBuffer = new VAO();
    m_vertexBuffer = new VBO(m_reformattedVertexBufferData.data(), m_reformattedVertexBufferData.size()*sizeof(float));
   

    int offset = 0;
    int layout = 0;
    int num_ele = 3;
    int total_num_ele = 8;
    glVertexAttribPointer(layout, num_ele, GL_FLOAT, GL_FALSE, total_num_ele * sizeof(float), (void*)(offset * sizeof(float)));
    glEnableVertexAttribArray(0);


    layout = 1;
    offset = 3;
    glVertexAttribPointer(layout, num_ele, GL_FLOAT, GL_FALSE, total_num_ele * sizeof(float), (void*)(offset * sizeof(float)));
    glEnableVertexAttribArray(1);

    layout = 2;
    offset = 6;
    num_ele = 2;
    glVertexAttribPointer(layout, num_ele, GL_FLOAT, GL_FALSE, total_num_ele * sizeof(float), (void*)(offset * sizeof(float)));
    glEnableVertexAttribArray(2);

    m_indexBuffer = new EBO(indexBufferPtr->data(), (int)indexBufferPtr->size()*sizeof(int));

    if (mHasTextures)
    {
        m_textBuffer = new TEXTURE(texture_path);
        m_textBuffer->setSlot(0);
        m_textBuffer->Bind_and_Write();
    }

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

glm::mat4 VertexBufferManager::getModelMatrix()
{
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 model_mat = glm::translate(model, glm::vec3(mLoc.x,mLoc.y, mLoc.z));
    return model_mat;
}

bool VertexBufferManager::hasTexture()
{
    return mHasTextures;
}