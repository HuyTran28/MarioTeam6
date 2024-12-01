#include "ModelStage.h"

void ModelStage::addModel(std::string name, Model model)
{
    if (listModels.find(name) == listModels.end())
    {
        listModels[name] = model;
    }
}

ModelStage::~ModelStage() {
    for (auto& model : listModels) {
        UnloadModel(model.second);
    }
    listModels.clear();
}

std::unordered_map<std::string, Model> ModelStage::listModels;