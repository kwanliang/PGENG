#pragma once

#include "SingletonTemplate.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;

class UIManager : public Singleton<UIManager>
{
    friend Singleton<UIManager>;
public:
    Label* GenerateText(const std::string labelname, const std::string text, const std::string filepath, const float size, const Vec2 pos);
    Label* RemoveText(const std::string labelname);

    ui::Button* GenerateButton(const std::string text, const std::string buttonfilepath, const std::string pressedfilepath, const float fontsize, const Vec2 pos);

private:
    UIManager();
    ~UIManager();
    
    std::map<std::string, Label*> m_LabelMap;
};