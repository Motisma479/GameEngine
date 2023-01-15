#include "Resources/Loader.hpp"
#include "Core/Debug/Debug.hpp"

#include <fstream>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

float ReadFloat(const char* data, size_t& index, const size_t maxeSize)
{
    float temp = 0;
    bool isM = false;
    if (data[index] == '-')
    {
        isM = true;
        index++;
    }
    while (data[index] != '.')
    {
        temp *= 10;
        //DEBUG_LOG("%d\n", (data[index] - '0'));
        temp += (data[index] - '0');
        index++;
    }
    index++;
    float x = 10;
    while (data[index] >= '0' && data[index] <= '9')
    {
        temp += (data[index] - '0') / x;
        x *= 10;
        index++;
    }
    index++;
    if (isM)
        temp *= -1;
    return temp;
}
void ReadLineNMF(char* nmf, const char* data, size_t& index, const size_t maxeSize)
{
    for (int i = 0; i < sizeof(nmf); i++)
    {
        nmf[i] = NULL;
    }
    index++;
    for (int i = 0; i < maxeSize; i++)
    {
        if (data[index + i] != '\n' && data[index + i] != 0)
        {
            nmf[i] = data[index + i];
            nmf[i + 1] = 0;
        }
        else
        {
            nmf[i] = 0;
            index += i;
            break;
        }
    }
}

void addPathToOBJ(char* name)
{
    std::string temp = "Resources/Obj/";
    temp += name;
    for (int i = 0; i < sizeof(name); i++)
    {
        name[i] = 0;
    }
    for (int i = 0; i < temp.length(); i++)
    {
        name[i] = temp.c_str()[i];
        name[i + 1] = 0;
    }
}
void addPathToTexture(char* name)
{
    std::string temp = "Resources/Textures/";
    temp += name;
    for (int i = 0; i < sizeof(name); i++)
    {
        name[i] = 0;
    }
    for (int i = 0; i < temp.length(); i++)
    {
        name[i] = temp.c_str()[i];
        name[i + 1] = 0;
    }
}

#pragma region MaterialLoader
void ReadLineVec(Maths::sVector::Vector3& storage, const char* data, size_t& index, const size_t maxeSize)
{
    index++;
    storage = { ReadFloat(data,index,maxeSize), ReadFloat(data, index, maxeSize), ReadFloat(data, index, maxeSize) };
    index--;
}

void SetMaterial(const char* name, const char* nameOfMaterial, Resources::ResourcesManager* resourceManager, Resources::MaterialManager* materialManager,Maths::sVector::Vector3& ambient, Maths::sVector::Vector3& difuse, Maths::sVector::Vector3& specular, Maths::sVector::Vector3& emisive, float& shininess, Resources::Texture* TextureRef)
{
    Resources::Material* tempMaterial = new Resources::Material;

    tempMaterial->ambient = ambient;
    tempMaterial->diffuse = difuse;
    tempMaterial->emisive = emisive;
    tempMaterial->shininess = shininess;
    tempMaterial->specular = specular;

    tempMaterial->TextureRef = TextureRef;

    std::string tempName = name;
    tempName += "/";
    tempName += nameOfMaterial;

    tempMaterial->name = tempName;

    resourceManager->AddData(tempName.c_str(), tempMaterial);
    materialManager->AddData(tempMaterial);
}

void Loader::LoadMatrerial(const char* name, Resources::ResourcesManager* resourceManager, Resources::MaterialManager* materialManager)
{
    Maths::sVector::Vector3 ambient; //Ka
    Maths::sVector::Vector3 difuse; //Kd
    Maths::sVector::Vector3 specular; //Ks
    Maths::sVector::Vector3 emisive; //Ke
    float shininess; //Ns or Ni
    bool isFirst = true;
    char* nameOfMaterial = new char[64];

    Resources::Texture* Ref = nullptr;

    //oppen the mtl
    std::ifstream mtl(name, std::ios::in | std::ios::ate);
    if (!mtl.is_open()) {
        DEBUG_LOG("Could not open the file - ' %s '\n", name);
        return;
    }
    size_t size = mtl.tellg();
    mtl.seekg(0);
    char* lines = new char[size + 1];
    mtl.read(lines, size);
    mtl.close();
    lines[size] = 0; // Set the last char of the file to 0
    //read the mtl
    
    for (size_t i = 0; i < size; i++)
    {

        if (i == 0 || lines[i - 1] == '\n')
        {
            if (lines[i] == 'K' && lines[i + 1] == 'a')
            {
                i += 2;
                ReadLineVec(ambient, lines, i, size);
            }
            if (lines[i] == 'K' && lines[i + 1] == 'd')
            {
                i += 2;
                ReadLineVec(difuse, lines, i, size);
            }
            if (lines[i] == 'K' && lines[i + 1] == 's')
            {
                i += 2;
                ReadLineVec(specular, lines, i, size);
            }
            if (lines[i] == 'K' && lines[i + 1] == 'e')
            {
                i += 2;
                ReadLineVec(emisive, lines, i, size);
            }
            if (lines[i] == 'N' && lines[i + 1] == 'i')
            {
                i += 2;
                shininess = ReadFloat(lines, i, size);
            }
            
            if (lines[i] == 'n' && lines[i + 1] == 'e' && lines[i + 2] == 'w' && lines[i + 3] == 'm' && lines[i + 4] == 't' && lines[i + 5] == 'l')
            {
                i += 6;
                if (!isFirst)
                {
                    SetMaterial(name, nameOfMaterial, resourceManager, materialManager, ambient, difuse, specular, emisive, shininess, Ref);
                }
                ReadLineNMF(nameOfMaterial, lines, i, size);
                isFirst = false;
            }
            if (lines[i] == 'm' && lines[i+1] == 'a' && lines[i+2] == 'p' && lines[i+3] == '_' && lines[i+4] == 'K' && lines[i+5] == 'd')
            {
                i += 6;
                char* nameOfTexture = new char[64];
                ReadLineNMF(nameOfTexture, lines, i, size);
                addPathToTexture(nameOfTexture);
                Ref = resourceManager->Create<Resources::Texture>(nameOfTexture);//LoadMatrerial(nameOffMTL, resourceManager, materialManager);
                delete[] nameOfTexture;
            }
        }
    }
    SetMaterial(name, nameOfMaterial, resourceManager, materialManager, ambient, difuse, specular, emisive, shininess, Ref);
    delete[] lines;
    delete[] nameOfMaterial;
    
}

#pragma endregion


#pragma region ModelLoader

int ReadVertexOrder(const char* data, size_t& index, const size_t maxeSize)
{
    int temp = 0;
    while (data[index] >= '0' && data[index] <= '9')
    {
        temp *= 10;
        temp += (data[index] - '0');
        index++;
    }
    index++;
    return temp - 1;
}

void ReadLineV(std::vector<Maths::sVector::Vector3>& position, const char* data, size_t& index, const size_t maxeSize)
{
    index++;
    position.push_back({ ReadFloat(data,index,maxeSize), ReadFloat(data, index, maxeSize), ReadFloat(data, index, maxeSize) });
    index--;
}
void ReadLineVT(std::vector<Maths::sVector::Vector2>& textureUV, const char* data, size_t& index, const size_t maxeSize)
{
    index++;
    textureUV.push_back({ ReadFloat(data, index, maxeSize),ReadFloat(data, index, maxeSize) });
    index--;
}
void ReadLineVN(std::vector<Maths::sVector::Vector3>& normal, const char* data, size_t& index, const size_t maxeSize)
{
    index++;
    normal.push_back({ ReadFloat(data, index, maxeSize) ,ReadFloat(data, index, maxeSize) ,ReadFloat(data, index, maxeSize) });
    index--;
}
void ReadLineF(std::vector<int>& vertexOrder, const char* data, size_t& index, const size_t maxeSize, short& orderType, bool& orderTestDone)
{
    index++;
    if (!orderTestDone)
    {
        if (data[index + 1] == ' ')
            orderType = 0;
        else
        {
            if (data[index + 3] == ' ')
                orderType = 1;
            else if (data[index + 3] == '/')
                orderType = 2;
            else if (data[index + 3] >= '0' && data[index] <= '9')
                orderType = 3;
        }
        orderTestDone = true;
    }


    if (orderType == 0)
    {
        vertexOrder.push_back(ReadVertexOrder(data, index, maxeSize));
        vertexOrder.push_back(ReadVertexOrder(data, index, maxeSize));
        vertexOrder.push_back(ReadVertexOrder(data, index, maxeSize));
    }
    if (orderType == 1)
    {
        vertexOrder.push_back(ReadVertexOrder(data, index, maxeSize));
        vertexOrder.push_back(ReadVertexOrder(data, index, maxeSize));

        vertexOrder.push_back(ReadVertexOrder(data, index, maxeSize));
        vertexOrder.push_back(ReadVertexOrder(data, index, maxeSize));

        vertexOrder.push_back(ReadVertexOrder(data, index, maxeSize));
        vertexOrder.push_back(ReadVertexOrder(data, index, maxeSize));
    }
    if (orderType == 2)
    {
        vertexOrder.push_back(ReadVertexOrder(data, index, maxeSize));
        vertexOrder.push_back(ReadVertexOrder(data, index, maxeSize));
        vertexOrder.push_back(ReadVertexOrder(data, index, maxeSize));

        vertexOrder.push_back(ReadVertexOrder(data, index, maxeSize));
        vertexOrder.push_back(ReadVertexOrder(data, index, maxeSize));
        vertexOrder.push_back(ReadVertexOrder(data, index, maxeSize));

        vertexOrder.push_back(ReadVertexOrder(data, index, maxeSize));
        vertexOrder.push_back(ReadVertexOrder(data, index, maxeSize));
        vertexOrder.push_back(ReadVertexOrder(data, index, maxeSize));
    }
    if (orderType == 3)
    {
        vertexOrder.push_back(ReadVertexOrder(data, index, maxeSize));
        index++;
        vertexOrder.push_back(ReadVertexOrder(data, index, maxeSize));

        vertexOrder.push_back(ReadVertexOrder(data, index, maxeSize));
        index++;
        vertexOrder.push_back(ReadVertexOrder(data, index, maxeSize));

        vertexOrder.push_back(ReadVertexOrder(data, index, maxeSize));
        index++;
        vertexOrder.push_back(ReadVertexOrder(data, index, maxeSize));
    }
    index--;
}


void Loader::LoadinGL(Resources::Mesh* tempMesh)
{
    // glGenBuffers(1, &VBO);
    glGenBuffers(1, &tempMesh->VBO);
    glGenBuffers(1, &tempMesh->EBO);

    glGenVertexArrays(1, &tempMesh->VAO);

    /// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(tempMesh->VAO);

    float* vertex = new float[tempMesh->d_Vertex.size() * 8];
    int ttt = 0;
    for (int j = 0; j < tempMesh->d_Vertex.size(); j++)
    {
        vertex[ttt] = tempMesh->d_Vertex[j].position.x;
        vertex[ttt + 1] = tempMesh->d_Vertex[j].position.y;
        vertex[ttt + 2] = tempMesh->d_Vertex[j].position.z;

        vertex[ttt + 3] = tempMesh->d_Vertex[j].textureUV.x;
        vertex[ttt + 4] = tempMesh->d_Vertex[j].textureUV.y;

        vertex[ttt + 5] = tempMesh->d_Vertex[j].normal.x;
        vertex[ttt + 6] = tempMesh->d_Vertex[j].normal.y;
        vertex[ttt + 7] = tempMesh->d_Vertex[j].normal.z;
        ttt += 8;
    }
    unsigned int* index = new unsigned int[tempMesh->d_Index.size()];
    for (int j = 0; j < tempMesh->d_Index.size(); j++)
    {
        index[j] = tempMesh->d_Index[j];
    }

    //glNamedBufferData(VBO, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, tempMesh->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Resources::Vertex) * tempMesh->d_Vertex.size(), vertex, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tempMesh->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * tempMesh->d_Index.size(), index, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // normal attribute
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);
}
void Loader::SetVertex(const char* name, const char* nameOffMesh, Resources::ResourcesManager* resourceManager, Resources::MeshManager* meshManager, std::vector<Maths::sVector::Vector3> position, std::vector<Maths::sVector::Vector2> textureUV, std::vector<Maths::sVector::Vector3> normal, std::vector<int> vertexOrder, short orderType)
{
    int z;
    switch (orderType)
    {
    case 0:
        z = 1;
        break;
    case 2:
        z = 3;
        break;
    default:
        z = 2;
        break;
    }
    Resources::Mesh* tempMesh = new Resources::Mesh;
    for (size_t i = 0; i < vertexOrder.size(); i += z)
    {
        Resources::Vertex temp;
        switch (orderType)
        {
        case 0:
            temp.position = position[vertexOrder[i]];
            temp.textureUV = { 0,0 };
            temp.normal = { 1,1,1 };
            break;
        case 1:
            temp.position = position[vertexOrder[i]];
            temp.textureUV = textureUV[vertexOrder[i + 1]];
            temp.normal = { 1,1,1 };
            break;
        case 2:

            temp.position = position[vertexOrder[i]];
            temp.textureUV = textureUV[vertexOrder[i + 1]];
            temp.normal = normal[vertexOrder[i + 2]];
            break;
        case 3:
            temp.position = position[vertexOrder[i]];
            temp.textureUV = { 0,0 };
            temp.normal = normal[vertexOrder[i + 1]];
            break;
        default:
            break;
        }
        bool existing = false;
        uint32_t id;
        for (uint32_t j = 0; j < tempMesh->d_Vertex.size(); j++)
        {
            if (tempMesh->d_Vertex[j] == temp)
            {
                existing = true;
                id = j;
            }
        }

        if (!existing)
        {
            tempMesh->d_Vertex.push_back(temp);
            tempMesh->d_Index.push_back((uint32_t)tempMesh->d_Vertex.size() - 1);
        }
        else
        {
            tempMesh->d_Index.push_back(id);
        }
    }
    LoadinGL(tempMesh);
    std::string tempName = name;
    tempName += "/";
    tempName += nameOffMesh;

    tempMesh->name = tempName;

    resourceManager->AddData(tempName.c_str(), tempMesh);
    meshManager->AddData(tempMesh);
    
    vertexOrder.clear();
}
void Loader::loadModel(const char* name, Resources::ResourcesManager* resourceManager, Resources::MeshManager* meshManager, Resources::MaterialManager* materialManager)
{
    std::vector<Maths::sVector::Vector3> t_Position;
    std::vector<Maths::sVector::Vector2> t_TextureUV;
    std::vector<Maths::sVector::Vector3> t_Normal;
    // TO MODIFY
    std::vector<int> t_VertexOrder;
    bool isFirst = true;

    char* nameOffMesh = new char[64];

    short orderType = 0;
    bool orderTestDone = false;

    //oppen the obj
    std::ifstream model(name, std::ios::in  | std::ios::ate);
    if (!model.is_open()) {
        DEBUG_LOG("Could not open the file - ' %s %s", name, "'\n");
        return;
    }
    size_t size = model.tellg();
    model.seekg(0);
    char* lines = new char[size + 1];
    model.read(lines, size);
    model.close();
    lines[size] = 0; // Set the last char of the file to 0
    //DEBUG_LOG("%s\n",lines);
    //read the obj
    for (size_t i = 0; i < size; i++)
    {

        if (i == 0 || lines[i - 1] == '\n')
        {
            if (lines[i] == 'v' && lines[i + 1] == ' ')
            {
                i++;
                ReadLineV(t_Position, lines, i, size);
            }
            if (lines[i] == 'v' && lines[i + 1] == 't')
            {
                i += 2;
                ReadLineVT(t_TextureUV, lines, i, size);
            }
            if (lines[i] == 'v' && lines[i + 1] == 'n')
            {
                i += 2;
                ReadLineVN(t_Normal, lines, i, size);
            }
            if (lines[i] == 'f' && lines[i + 1] == ' ')
            {
                i++;
                ReadLineF(t_VertexOrder, lines, i, size, orderType, orderTestDone);
            }
            if (lines[i] == 'u' && lines[i + 1] == 's' && lines[i + 2] == 'e' && lines[i + 3] == 'm' && lines[i + 4] == 't' && lines[i + 5] == 'l')
            {
                i += 6;
                if (!isFirst)
                {
                    SetVertex(name, nameOffMesh, resourceManager, meshManager, t_Position, t_TextureUV, t_Normal, t_VertexOrder, orderType);
                }
                ReadLineNMF(nameOffMesh, lines, i, size);
                isFirst = false;
            }
            if (lines[i] == 'm' && lines[i + 1] == 't' && lines[i + 2] == 'l' && lines[i + 3] == 'l' && lines[i + 4] == 'i' && lines[i + 5] == 'b')
            {
                i += 6;
                char* nameOffMTL = new char[64];
                ReadLineNMF(nameOffMTL, lines, i, size);
                addPathToOBJ(nameOffMTL);
                LoadMatrerial(nameOffMTL, resourceManager, materialManager);
                delete[] nameOffMTL;
            }
        }
    }
    SetVertex(name, nameOffMesh, resourceManager, meshManager, t_Position, t_TextureUV, t_Normal, t_VertexOrder, orderType);
    delete[] lines;
    delete[] nameOffMesh;
}

#pragma endregion