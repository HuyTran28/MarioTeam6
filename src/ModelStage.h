#pragma once


#include "raylib.h"
#include <string>
#include <unordered_map>

class ModelStage
{
public:
    void addModel(std::string name, Model model);
    static std::unordered_map<std::string, Model> listModels;
    ~ModelStage();
};