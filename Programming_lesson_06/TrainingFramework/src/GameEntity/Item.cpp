#include"Item.h"
#include"ResourceManagers.h"
#include "Map.h"
Item::Item(std::shared_ptr<Vec2i> location, int type) :Entity(location), m_type(type)
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("BlockCantDestroy");
	auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	
	switch (type)
	{
	case ITEM_ADDHP:
		texture = ResourceManagers::GetInstance()->GetTexture("ItemAddHP");
		break;
	case ITEM_ADDBOM:
		texture = ResourceManagers::GetInstance()->GetTexture("ItemAddBom");
		break;
	case ITEM_ADDPOWER:
		texture = ResourceManagers::GetInstance()->GetTexture("ItemAddPower");
		break;
	case ITEM_ADDSPEED:
		texture = ResourceManagers::GetInstance()->GetTexture("ItemAddSpeed");
		break;
	default:
		break;
	}
	m_animation = std::make_shared<Animation>(model, shader, texture, NUM_FRAME, ANIM_SPEED, TYPE_SPRITE, NUM_LINE);
	m_animation->Set2DPosition(m_location->m_x, m_location->m_y);
	m_animation->SetSize(ENTITY_SIZE, ENTITY_SIZE);
}